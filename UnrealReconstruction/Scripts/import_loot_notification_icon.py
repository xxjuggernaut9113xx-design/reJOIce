from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
REPORT = PROJECT / "RecoveryEvidence" / "loot-notification-icon-recovery-report.json"
DESTINATION = "/Game/Recovery/Resources/Widgets/NotificationBoxIcons"
ASSET_NAME = "CoinRewardIcon"
ALIASES = PROJECT / "RecoveryEvidence" / "resource-aliases.json"


def main() -> None:
    row = json.loads(REPORT.read_text(encoding="utf-8"))
    if not row.get("decoded"):
        raise RuntimeError("CoinRewardIcon PNG decode has not completed")
    png = Path(row["png"])
    if not png.is_file():
        raise RuntimeError(f"CoinRewardIcon PNG is unavailable: {png}")

    task = unreal.AssetImportTask()
    task.filename = str(png)
    task.destination_path = DESTINATION
    task.destination_name = ASSET_NAME
    task.automated = True
    task.replace_existing = True
    task.save = False
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])

    asset_path = f"{DESTINATION}/{ASSET_NAME}.{ASSET_NAME}"
    texture = unreal.load_asset(asset_path)
    if not isinstance(texture, unreal.Texture2D):
        raise RuntimeError("CoinRewardIcon texture import failed")
    texture.set_editor_property("srgb", bool(row["srgb"]))
    texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
    texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
    if not unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False):
        raise RuntimeError("CoinRewardIcon texture save failed")

    aliases = json.loads(ALIASES.read_text(encoding="utf-8")) if ALIASES.is_file() else {}
    aliases[row["original"]] = asset_path
    ALIASES.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    row["asset"] = asset_path
    row["imported"] = True
    REPORT.write_text(json.dumps(row, indent=2) + "\n", encoding="utf-8")
    unreal.log("LOOT_NOTIFICATION_ICON_IMPORTED " + asset_path)


main()
