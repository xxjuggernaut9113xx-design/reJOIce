from __future__ import annotations

import json
import os
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
EVIDENCE = PROJECT / "RecoveryEvidence"
REPORT_PATH = EVIDENCE / "challenge-icon-recovery.json"
ALIASES_PATH = EVIDENCE / "resource-aliases.json"
DESTINATION = "/Game/Recovery/Resources/ChallengeIcons"
TABLE_PATH = "/Game/Recovery/Progression/DT_Challenges.DT_Challenges"
VALIDATE_ONLY = os.environ.get("RECOVERY_VALIDATE_ONLY") == "1"


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def expected_source_icons() -> dict[str, str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    rows = rules["progression"]["DT_Challenges"]
    mapping = {row["row"]: row["Icon"] for row in rows}
    require(len(rows) == 55 and len(mapping) == 55 and len(set(mapping.values())) == 55, "DT_Challenges no longer has 55 source icon bindings")
    return mapping


def table_icon_bindings() -> dict[str, str]:
    table = unreal.load_asset(TABLE_PATH)
    require(isinstance(table, unreal.DataTable), f"Recovered challenge table is unavailable: {TABLE_PATH}")
    exported = json.loads(unreal.RecoveredRuleLibrary.export_table_json(table))
    bindings = {row["Name"]: row["Icon"] for row in exported}
    require(len(bindings) == 55, "Recovered challenge table no longer has 55 rows")
    return bindings


def main() -> None:
    report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    rows = report.get("textures", [])
    require(report.get("expected_icons") == 55 and report.get("exported_icons") == 55 and report.get("decoded_icons") == 55, "Challenge icon evidence is incomplete")
    require(len(rows) == 55 and all(row.get("decoded") for row in rows), "Challenge icon PNG decode is incomplete")

    expected = expected_source_icons()
    by_original = {row["original"]: row for row in rows}
    require(set(by_original) == set(expected.values()), "Challenge icon evidence differs from DT_Challenges")

    aliases = json.loads(ALIASES_PATH.read_text(encoding="utf-8")) if ALIASES_PATH.exists() else {}
    imported = []
    for original in sorted(by_original):
        row = by_original[original]
        png = Path(row["png"])
        require(png.is_file(), f"Decoded challenge icon is unavailable: {png}")
        name = Path(row["relative_package"]).name
        if not VALIDATE_ONLY:
            task = unreal.AssetImportTask()
            task.filename = str(png)
            task.destination_path = DESTINATION
            task.destination_name = name
            task.automated = True
            task.replace_existing = True
            task.save = False
            unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

        asset_path = f"{DESTINATION}/{name}.{name}"
        texture = unreal.load_asset(asset_path)
        require(isinstance(texture, unreal.Texture2D), f"Challenge icon import failed: {original}")
        require(texture.blueprint_get_size_x() == int(row["width"]), f"Challenge icon width changed during import: {original}")
        require(texture.blueprint_get_size_y() == int(row["height"]), f"Challenge icon height changed during import: {original}")
        if not VALIDATE_ONLY:
            texture.set_editor_property("srgb", bool(row["srgb"]))
            texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
            texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
            require(unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False), f"Could not save challenge icon: {original}")
        require(bool(texture.get_editor_property("srgb")) == bool(row["srgb"]), f"Challenge icon color space changed during import: {original}")
        require(
            texture.get_editor_property("compression_settings") == unreal.TextureCompressionSettings.TC_EDITOR_ICON,
            f"Challenge icon compression changed during import: {original}",
        )
        require(
            texture.get_editor_property("mip_gen_settings") == unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS,
            f"Challenge icon mip configuration changed during import: {original}",
        )

        aliases[original] = asset_path
        row["recovered_asset"] = asset_path
        row["imported"] = True
        imported.append(asset_path)

    require(len(imported) == 55, "Challenge icon import is incomplete")
    bindings = table_icon_bindings()
    require(bindings == expected, "Recovered challenge table source icon bindings changed")

    ALIASES_PATH.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    report["destination"] = DESTINATION
    report["imported_icons"] = 55
    report["asset_properties_verified"] = True
    report["asset_validation_mode"] = "validation-only" if VALIDATE_ONLY else "import-and-validate"
    report["imported_assets"] = imported
    report["challenge_table"] = {
        "asset": TABLE_PATH,
        "rows": len(bindings),
        "source_icon_bindings_verified": bindings == expected,
        "bindings": bindings,
    }
    REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    (PROJECT / "Saved" / "challenge-icon-texture-import-report.json").write_text(
        json.dumps({"imported": len(imported), "destination": DESTINATION, "assets": imported}, indent=2) + "\n",
        encoding="utf-8",
    )
    unreal.log("CHALLENGE_ICON_TEXTURES_IMPORTED " + json.dumps({"count": len(imported), "destination": DESTINATION}))


if __name__ == "__main__":
    main()
