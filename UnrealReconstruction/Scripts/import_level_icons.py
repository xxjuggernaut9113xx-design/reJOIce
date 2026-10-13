from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
EVIDENCE = PROJECT / "RecoveryEvidence"
REPORT_PATH = EVIDENCE / "level-icon-recovery.json"
ALIASES_PATH = EVIDENCE / "resource-aliases.json"
DESTINATION = "/Game/Recovery/Resources/UI/PostGameFlow/LevelIcons"


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    rows = report.get("textures", [])
    require(report.get("expected_icons") == 20 and report.get("decoded_icons") == 20, "Level-icon source decode is incomplete")
    require(len(rows) == 20 and all(row.get("decoded") for row in rows), "Level-icon decode rows are incomplete")
    aliases = json.loads(ALIASES_PATH.read_text(encoding="utf-8")) if ALIASES_PATH.exists() else {}

    imported = []
    for row in rows:
        name = Path(row["relative_package"]).name
        task = unreal.AssetImportTask()
        task.filename = row["png"]
        task.destination_path = DESTINATION
        task.destination_name = name
        task.automated = True
        task.replace_existing = True
        task.save = False
        unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

        asset_path = f"{DESTINATION}/{name}.{name}"
        texture = unreal.load_asset(asset_path)
        require(isinstance(texture, unreal.Texture2D), f"Level-icon import failed: {row['original']}")
        require(texture.blueprint_get_size_x() == int(row["width"]) and texture.blueprint_get_size_y() == int(row["height"]), f"Level-icon dimensions changed: {row['original']}")
        texture.set_editor_property("srgb", bool(row["srgb"]))
        texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
        texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
        require(unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False), f"Could not save recovered level icon: {row['original']}")
        aliases[row["original"]] = asset_path
        row["recovered_asset"] = asset_path
        row["imported"] = True
        imported.append(asset_path)

    require(len(imported) == 20, "Level-icon import is incomplete")
    ALIASES_PATH.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    report["imported_icons"] = len(imported)
    report["imported_assets"] = imported
    REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    (PROJECT / "Saved" / "level-icon-import-report.json").write_text(json.dumps({"imported": len(imported), "assets": imported}, indent=2) + "\n", encoding="utf-8")
    unreal.log("POST_GAME_LEVEL_ICONS_IMPORTED " + json.dumps({"count": len(imported), "destination": DESTINATION}))


if __name__ == "__main__":
    main()
