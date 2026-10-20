"""Import independently versioned newer tables and decoded artwork; verify all fields."""
import hashlib
import json
import sys
from pathlib import Path
import unreal

PROJECT = Path(unreal.Paths.project_dir()).resolve()
sys.path.insert(0, str(PROJECT / "Scripts"))
from newer_content_contract import DEFINITION, DESTINATION, canonical, table_rows, require, all_artwork, load_source

contract = json.loads(DEFINITION.read_text(encoding="utf-8"))
require(contract["version"] == "newer-20261017", "Unsupported progression contract version")
require(contract == load_source(), "Progression definition differs from verified retained source")
used_metrics = {r["MetricType"].split("::")[-1] for c in contract["tables"]["DT_Challenges"] for r in c["Requirements"]}
enum_names = {name.replace("_", "").lower() for name in dir(unreal.RecoveredMetric) if name.isupper()}
missing_metrics = sorted(name for name in used_metrics if name.lower() not in enum_names)
require(not missing_metrics, f"Runtime metric enum lacks required newer producers: {missing_metrics}; reflected names: {sorted(enum_names)}")
artwork = json.loads((PROJECT / "RecoveryEvidence/newer-20261017-artwork.json").read_text(encoding="utf-8"))
require({r["original"] for r in artwork["textures"]} == set(all_artwork(contract)), "Newer artwork coverage mismatch")
aliases_path = PROJECT / "RecoveryEvidence/newer-20261017-resource-aliases.json"
aliases = {}
tools = unreal.AssetToolsHelpers.get_asset_tools()
assets = unreal.EditorAssetLibrary
for row in artwork["textures"]:
    png = Path(row["png"])
    require(row.get("decoded") and hashlib.sha256(png.read_bytes()).hexdigest() == row["png_sha256"], f"Invalid source PNG: {row['original']}")
    category = row["relative_package"].rsplit("/", 1)[0]
    name = Path(row["relative_package"]).name
    path = f"{DESTINATION}/Resources/{category}"
    task = unreal.AssetImportTask()
    task.filename = str(png)
    task.destination_path = path
    task.destination_name = name
    task.automated = True
    task.replace_existing = True
    task.save = False
    tools.import_asset_tasks([task])
    asset_path = f"{path}/{name}.{name}"
    texture = unreal.load_asset(asset_path)
    require(isinstance(texture, unreal.Texture2D), f"Newer artwork import failed: {asset_path}")
    require((texture.blueprint_get_size_x(), texture.blueprint_get_size_y()) == (row["width"], row["height"]), f"Newer artwork dimensions differ: {asset_path}")
    texture.set_editor_property("srgb", row["srgb"])
    texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
    texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
    require(assets.save_loaded_asset(texture, False), f"Could not save {asset_path}")
    aliases[row["original"]] = asset_path

structs = {"DT_Challenges": unreal.RecoveredRuleLibrary.get_challenge_row_struct(),
           "DT_PlayerCards": unreal.RecoveredRuleLibrary.get_player_card_row_struct(),
           "DT_LevelData": unreal.RecoveredRuleLibrary.get_level_row_struct(),
           "DT_Modifiers": unreal.RecoveredRuleLibrary.get_modifier_row_struct(),
           "DT_HeatCategories": unreal.RecoveredRuleLibrary.get_heat_category_row_struct()}
report = {"version": contract["version"], "source_executed": False, "tables": {}, "artwork": len(aliases), "sources": contract["sources"]}
supported = {**contract["tables"], "DT_Modifiers": contract["supplemental_tables"]["ModifierInfoDataTable"],
             "DT_HeatCategories": contract["supplemental_tables"]["HeatCategoryDataTable"]}
for name, source in supported.items():
    path = f"{DESTINATION}/Progression/{name}"
    table = unreal.load_asset(path)
    if table is None:
        factory = unreal.DataTableFactory()
        factory.set_editor_property("struct", structs[name])
        table = tools.create_asset(name, f"{DESTINATION}/Progression", unreal.DataTable, factory)
    expected = table_rows(source)
    if name == "DT_Modifiers":
        for row in expected:
            row["ModifierIcon"] = aliases[row["ModifierIcon"]]
    require(unreal.DataTableFunctionLibrary.fill_data_table_from_json_string(table, json.dumps(expected)), f"Newer table import failed: {name}")
    actual = json.loads(unreal.RecoveredRuleLibrary.export_table_json(table))
    if name == "DT_Modifiers":
        for row in actual:
            value = row["ModifierIcon"]
            if "'" in value:
                row["ModifierIcon"] = value.split("'", 1)[1].rstrip("'")
    require({r["Name"]: canonical(r) for r in actual} == {r["Name"]: canonical(r) for r in expected}, f"Newer table values differ: {name}")
    require(assets.save_loaded_asset(table, False), f"Could not save newer table: {name}")
    report["tables"][name] = {"asset": path + "." + name, "rows": len(actual), "all_fields_match": True}
report["retained_source_tables"] = {k: len(v) for k,v in {**contract["tables"], **contract["supplemental_tables"]}.items()}
aliases_path.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
(PROJECT / "Content/Recovery/Definitions/newer-20261017-resource-aliases.json").write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
(PROJECT / "RecoveryEvidence/newer-20261017-progression-import.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
unreal.log("NEWER_PROGRESSION_IMPORTED " + json.dumps(report))
