from pathlib import Path
import json

import unreal

project = Path(unreal.Paths.project_dir())
report_path = project / "Saved" / "outcome-notification-icon-recovery-report.json"
rows = json.loads(report_path.read_text(encoding="utf-8"))
asset_folder = "/Game/Recovery/Resources/Widgets/NotificationBoxIcons"
aliases_path = project / "RecoveryEvidence" / "resource-aliases.json"
aliases = json.loads(aliases_path.read_text(encoding="utf-8")) if aliases_path.exists() else {}

for row in rows:
    if not row.get("decoded"):
        raise RuntimeError("Missing decoded image for " + row["original"])
    name = Path(row["original"].split(".", 1)[0]).name
    task = unreal.AssetImportTask()
    task.filename = row["png"]
    task.destination_path = asset_folder
    task.destination_name = name
    task.automated = True
    task.replace_existing = True
    task.save = False
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
    asset_path = asset_folder + "/" + name + "." + name
    texture = unreal.load_asset(asset_path)
    if not isinstance(texture, unreal.Texture2D):
        raise RuntimeError("Texture import failed for " + name)
    texture.set_editor_property("srgb", row["srgb"])
    texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
    texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
    if not unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False):
        raise RuntimeError("Texture save failed for " + name)
    aliases[row["original"]] = asset_path
    row["asset"] = asset_path

aliases_path.write_text(json.dumps(aliases, indent=2), encoding="utf-8")
report_path.write_text(json.dumps(rows, indent=2), encoding="utf-8")
unreal.log("OUTCOME_NOTIFICATION_ICONS_IMPORTED " + str(len(rows)))
