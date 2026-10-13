from pathlib import Path
import json

import unreal


PROJECT = Path(unreal.Paths.project_dir())
TARGETS = {
    "WBP_XPBar": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_XPBar-functions.json",
    "WBP_LevelUpScreen": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_LevelUpScreen-functions.json",
}
EXPECTED = {
    "WBP_XPBar": "ReceiveXP_INST",
    "WBP_LevelUpScreen": "Anim_LevelUp_INST",
}


def main() -> None:
    reports = {}
    for asset_name, source in TARGETS.items():
        target = f"/Game/Recovery/UI/{asset_name}.{asset_name}"
        report = json.loads(unreal.RecoveredWidgetRecovery.restore_animation_data(source, target))
        if not report.get("saved_assets"):
            raise RuntimeError(f"Animation recovery did not save {asset_name}: {report}")
        actual = {entry.get("name") for entry in report.get("objects", [])}
        if EXPECTED[asset_name] not in actual:
            raise RuntimeError(f"Source animation missing for {asset_name}: {actual}")
        reports[asset_name] = report
        unreal.SystemLibrary.collect_garbage()

    output = PROJECT / "RecoveryEvidence" / "post-game-animation-recovery.json"
    output.write_text(json.dumps(reports, indent=2) + "\n", encoding="utf-8")
    unreal.log("POST_GAME_ANIMATIONS_RESTORED " + json.dumps({
        name: report.get("animation_count", 0) for name, report in reports.items()
    }))


if __name__ == "__main__":
    main()
