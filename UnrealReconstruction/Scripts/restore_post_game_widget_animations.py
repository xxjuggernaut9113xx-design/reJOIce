from pathlib import Path
import json

import unreal


PROJECT = Path(unreal.Paths.project_dir())
TARGETS = {
    "WBP_XPBar": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_XPBar-functions.json",
    "XBP_XPSourceText": "C:/Users/webma/analysis/cockhero-v004/decoded/XBP_XPSourceText-functions.json",
    "WBP_XPScreen": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_XPScreen-functions.json",
    "WBP_UPRewardScreen": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_UPRewardScreen-functions.json",
    "WBP_UPSourceText": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_UPSourceText-functions.json",
    "WBP_LevelUpScreen": "C:/Users/webma/analysis/cockhero-v004/decoded/WBP_LevelUpScreen-functions.json",
}
EXPECTED = {
    "WBP_XPBar": {"ReceiveXP_INST"},
    "XBP_XPSourceText": {"SpawnAndSlam_INST"},
    "WBP_XPScreen": {"FadeIn_INST", "Play50PercentPenalty_INST"},
    "WBP_UPRewardScreen": {"FadeIn_INST", "ReceiveUP_INST"},
    "WBP_UPSourceText": {"AnimSlam_INST"},
    "WBP_LevelUpScreen": {"Anim_LevelUp_INST"},
}


def main() -> None:
    reports = {}
    for asset_name, source in TARGETS.items():
        target = f"/Game/Recovery/UI/{asset_name}.{asset_name}"
        report = json.loads(unreal.RecoveredWidgetRecovery.restore_animation_data(source, target))
        if not report.get("saved_assets"):
            raise RuntimeError(f"Animation recovery did not save {asset_name}: {report}")
        actual = {entry.get("name") for entry in report.get("objects", [])}
        missing = EXPECTED[asset_name] - actual
        if missing:
            raise RuntimeError(f"Source animation missing for {asset_name}: {sorted(missing)} from {actual}")
        reports[asset_name] = report
        unreal.SystemLibrary.collect_garbage()

    output = PROJECT / "RecoveryEvidence" / "post-game-animation-recovery.json"
    output.write_text(json.dumps(reports, indent=2) + "\n", encoding="utf-8")
    unreal.log("POST_GAME_ANIMATIONS_RESTORED " + json.dumps({
        name: report.get("animation_count", 0) for name, report in reports.items()
    }))


if __name__ == "__main__":
    main()
