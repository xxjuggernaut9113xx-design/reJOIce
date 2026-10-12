from __future__ import annotations

import json
import os
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
EVIDENCE = PROJECT / "RecoveryEvidence"
REPORT_PATH = EVIDENCE / "challenge-pack-preview-recovery.json"
DESTINATION = "/Game/Recovery/Resources/Packs"
VALIDATE_ONLY = os.environ.get("RECOVERY_VALIDATE_ONLY") == "1"


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def expected_reward_ids() -> set[str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    return {
        reward["ItemIdentifier"]
        for row in rules["progression"]["DT_Challenges"]
        for reward in row.get("Rewards", [])
        if reward.get("RewardType") == "ECHRewardType::UnlockPack"
    }


def main() -> None:
    report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    previews = report.get("previews", [])
    require(report.get("expected_pack_rewards") == 9 and report.get("copied_previews") == 9, "Challenge pack preview evidence is incomplete")
    require(len(previews) == 9, "Challenge pack preview row count changed")
    require({row["pack_id"] for row in previews} == expected_reward_ids(), "Challenge pack previews differ from challenge reward data")

    imported = []
    for row in previews:
        source = Path(row["recovered_source"])
        require(source.is_file(), f"Recovered pack preview source is unavailable: {source}")
        if not VALIDATE_ONLY:
            task = unreal.AssetImportTask()
            task.filename = str(source)
            task.destination_path = DESTINATION
            task.automated = True
            task.replace_existing = True
            task.save = False
            unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
        asset_path = f"{DESTINATION}/{row['asset_name']}.{row['asset_name']}"
        texture = unreal.load_asset(asset_path)
        require(isinstance(texture, unreal.Texture2D), f"Challenge pack preview import failed: {row['pack_id']}")
        require(texture.blueprint_get_size_x() == int(row["width"]), f"Challenge pack preview width changed: {row['pack_id']}")
        require(texture.blueprint_get_size_y() == int(row["height"]), f"Challenge pack preview height changed: {row['pack_id']}")
        if not VALIDATE_ONLY:
            texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
            texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
            texture.set_editor_property("srgb", True)
            require(unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False), f"Could not save challenge pack preview: {row['pack_id']}")
        require(bool(texture.get_editor_property("srgb")), f"Challenge pack preview color space changed: {row['pack_id']}")
        require(texture.get_editor_property("compression_settings") == unreal.TextureCompressionSettings.TC_EDITOR_ICON, f"Challenge pack preview compression changed: {row['pack_id']}")
        require(texture.get_editor_property("mip_gen_settings") == unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS, f"Challenge pack preview mip configuration changed: {row['pack_id']}")
        row["recovered_asset"] = asset_path
        row["imported"] = True
        imported.append(asset_path)

    require(len(imported) == 9, "Challenge pack preview import is incomplete")
    report["destination"] = DESTINATION
    report["imported_previews"] = len(imported)
    report["asset_properties_verified"] = True
    report["asset_validation_mode"] = "validation-only" if VALIDATE_ONLY else "import-and-validate"
    report["imported_assets"] = imported
    REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    (PROJECT / "Saved" / "challenge-pack-preview-import-report.json").write_text(json.dumps({"imported": len(imported), "destination": DESTINATION, "assets": imported}, indent=2) + "\n", encoding="utf-8")
    unreal.log("CHALLENGE_PACK_PREVIEWS_IMPORTED " + json.dumps({"count": len(imported), "destination": DESTINATION}))


if __name__ == "__main__":
    main()