from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
REPORT_PATH = PROJECT / "RecoveryEvidence" / "player-card-texture-recovery.json"
DESTINATION = "/Game/Recovery/Resources/PlayerCards"


report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
if report["expected_card_images"] != 36 or report["exported_images"] != 37:
    raise RuntimeError("Player-card texture evidence is incomplete")

aliases_path = PROJECT / "RecoveryEvidence" / "resource-aliases.json"
aliases = json.loads(aliases_path.read_text(encoding="utf-8")) if aliases_path.exists() else {}
imported = []
for row in report["textures"]:
    if not row.get("decoded"):
        raise RuntimeError(f"Undecoded player-card texture: {row['original']}")
    name = Path(row["relative_package"]).name
    task = unreal.AssetImportTask()
    task.filename = row["png"]
    task.destination_path = DESTINATION
    task.automated = True
    task.replace_existing = True
    task.save = False
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

    asset_path = f"{DESTINATION}/{name}.{name}"
    texture = unreal.load_asset(asset_path)
    if not isinstance(texture, unreal.Texture2D):
        raise RuntimeError(f"Player-card texture import failed: {row['original']}")
    if texture.blueprint_get_size_x() != row["width"] or texture.blueprint_get_size_y() != row["height"]:
        raise RuntimeError(f"Player-card texture dimensions changed during import: {row['original']}")
    texture.set_editor_property("srgb", row["srgb"])
    texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
    texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
    if not unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False):
        raise RuntimeError(f"Could not save imported player-card texture: {row['original']}")
    aliases[row["original"]] = asset_path
    row["recovered_asset"] = asset_path
    imported.append(asset_path)

legacy_default = "/Game/PlayerCards/Catgirl_Booties_PC_-_1.Catgirl_Booties_PC_-_1"
recovered_default = f"{DESTINATION}/Cat_Girl_Booties.Cat_Girl_Booties"
if not unreal.load_asset(recovered_default):
    raise RuntimeError("Player-card entry default artwork was not imported")
aliases[legacy_default] = recovered_default

aliases_path.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
report["imported_assets"] = imported
REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
(PROJECT / "Saved" / "player-card-texture-import-report.json").write_text(
    json.dumps({"imported": len(imported), "assets": imported}, indent=2) + "\n", encoding="utf-8"
)
unreal.log("PLAYER_CARD_TEXTURES_IMPORTED " + json.dumps({"count": len(imported), "destination": DESTINATION}))
