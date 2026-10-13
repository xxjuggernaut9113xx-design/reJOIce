from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
FUNCTIONS = EVIDENCE / "blueprint-functions"

SOURCE_FUNCTIONS = {
    "WBP_XPBar": {
        "InitializeBar.json": {"CurrentLevelEmblemIcon", "NextLevelEmblem", "CurrentLevel", "TargetLevel", "MaxXP"},
        "UpdateDisplay.json": {"CurrentLevelEmblemIcon", "NextLevelEmblem", "XPProgressBar", "XPText", "CurrentXP", "MaxXP"},
        "AddXPAnimated.json": {"ReceiveXP", "AnimationStartXP", "AnimationTargetXP", "AnimationDuration", "bIsAnimating"},
    },
    "WBP_PlayerCard": {
        "InitializePlayerCard.json": {"SelectedPlayerCard", "PlayerNameText", "Playercard_Name", "ProgressionManager", "CurrentSave"},
    },
    "WBP_LevelUpScreen": {
        "InitializeScreen.json": {"LevelUpData", "LevelText", "RankTitle", "Anim_LevelUp", "WBP_PlayerCard", "RankIcon", "ProgressionManager"},
        "PlaySoundFX.json": set(),
        "SequenceEvent.json": set(),
    },
    "XBP_XPSourceText": {
        "Initialize.json": {"XPSourceData", "XPAmountText", "XPDetailText", "SpawnAndSlam"},
        "SequenceEvent.json": set(),
    },
    "WBP_XPScreen": {
        "InitializeScreen.json": {"RewardData", "CurrentSourceIndex", "WBP_PlayerCard", "WBP_XPBar", "DidPlayerWin?", "UPSources"},
        "PlayNextSource.json": {"bWaitingForLevelUp", "CurrentSourceIndex", "OnAllSourcesComplete", "XBP_XPSourceText", "XPSources"},
        "HandleBarFilled.json": set(),
        "ResumeAfterLevelUp.json": set(),
    },
    "WBP_UPSourceText": {
        "Initialize.json": {"UPData", "UPAmountText", "DetailText", "AnimSlam"},
        "SequenceEvent.json": set(),
    },
    "WBP_UPRewardScreen": {
        "InitializeScreen.json": {"RewardData", "CurrentSourceIndex", "DisplayedUP", "UPTotalText", "50PercentPenaltyText", "Did Player Win?", "UPSources"},
        "PlayNextSource.json": {"CurrentSourceIndex", "OnAllSourcesComplete", "UPSources", "WBP_UPSourceText"},
        "OnSourceAnimationComplete.json": set(),
    },
}

REQUIRED_NATIVE_MARKERS = {
    "Source/CockHeroRecovered/RecoveredPostGameWidgets.cpp": {
        "void URecoveredXPBarWidget::InitializeBar",
        "void URecoveredXPBarWidget::AddXPAnimated",
        "void URecoveredXPBarWidget::AdvanceRecoveredXPAnimation",
        "whoosh-cinematic-161021_sfx",
        "drop-coin-384921",
        "void URecoveredPlayerCardWidget::InitializePlayerCard",
        "void URecoveredLevelUpScreenWidget::InitializeScreen",
        "Juice_SFX__11_",
        "Juice_SFX__9_",
        "void URecoveredLevelUpScreenWidget::SequenceEvent",
        "void URecoveredXPSourceTextWidget::InitializeSource",
        "void URecoveredXPSourceTextWidget::SequenceEvent__ENTRYPOINTXBP_XPSourceText",
        "void URecoveredUPSourceTextWidget::InitializeSource",
        "void URecoveredUPSourceTextWidget::SequenceEvent__ENTRYPOINTWBP_UPSourceText",
        "Juice_SFX__5_",
    },
    "Source/CockHeroRecovered/RecoveredPostGameWidgetsTests.cpp": {
        "CockHero.Recovery.PostGameWidgetContracts",
        "Source XP animation retains overflow",
        "Source level-up rank image",
        "Recovered post-game PCM",
        "Source XP source text",
        "Source UP source text",
    },
    "Source/CockHeroRecovered/RecoveredPostGameSequence.cpp": {
        "BindPostGameWidgetInstance",
        "RecoveredBar->InitializeBar",
        "RecoveredLevelUp->InitializeScreen",
        "URecoveredXPSourceTextWidget",
        "URecoveredUPSourceTextWidget",
        "Play50PercentPenalty",
        "Juice_SFX__12_",
        "Juice_SFX__16_",
        "VR_teleport",
    },
    "Source/CockHeroRecovered/RecoveredPostGame.cpp": {
        "RecoveredLevelUp->SetRecoveredPostGameGameInstance",
        "RecoveredLevelUp->InitializeScreen",
    },
}


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def load_json(path: Path) -> object:
    return json.loads(path.read_text(encoding="utf-8"))


def require(value: bool, message: str) -> None:
    if not value:
        raise RuntimeError(message)


def main() -> None:
    function_reports: dict[str, dict[str, object]] = {}
    source_files: list[Path] = []
    for widget, requirements in SOURCE_FUNCTIONS.items():
        for file_name, required_fields in requirements.items():
            path = FUNCTIONS / widget / file_name
            require(path.is_file(), f"missing source function evidence: {path}")
            payload = load_json(path)
            details = payload.get("function", {})
            fields = set(details.get("fields", []))
            require(not details.get("raw_fallback", True), f"undecoded source function: {path}")
            require(details.get("statements", 0) > 0, f"empty source function: {path}")
            missing_fields = sorted(required_fields - fields)
            require(not missing_fields, f"source fields missing from {path}: {missing_fields}")
            key = f"{widget}/{file_name}"
            function_reports[key] = {
                "statements": details["statements"],
                "calls": details.get("calls", []),
                "required_fields": sorted(required_fields),
                "decoded": True,
                "sha256": sha256(path),
            }
            source_files.append(path)

    native_reports: dict[str, dict[str, object]] = {}
    for relative, markers in REQUIRED_NATIVE_MARKERS.items():
        path = PROJECT / relative
        require(path.is_file(), f"missing native recovery file: {relative}")
        contents = path.read_text(encoding="utf-8-sig")
        missing = sorted(marker for marker in markers if marker not in contents)
        require(not missing, f"native recovery markers missing from {relative}: {missing}")
        native_reports[relative] = {"markers": sorted(markers), "sha256": sha256(path)}

    level_contract_path = EVIDENCE / "level-icon-contract-recovery.json"
    audio_contract_path = EVIDENCE / "post-game-feedback-audio-contract-recovery.json"
    animation_path = EVIDENCE / "post-game-animation-recovery.json"
    level_contract = load_json(level_contract_path)
    audio_contract = load_json(audio_contract_path)
    animation_contract = load_json(animation_path)
    require(level_contract["verified"]["all_verified"], "rank icon recovery contract failed")
    require(audio_contract["verified"]["all_verified"], "post-game audio recovery contract failed")
    animation_expectations = {
        "WBP_XPBar": {"ReceiveXP_INST"},
        "XBP_XPSourceText": {"SpawnAndSlam_INST"},
        "WBP_XPScreen": {"FadeIn_INST", "Play50PercentPenalty_INST"},
        "WBP_UPRewardScreen": {"FadeIn_INST", "ReceiveUP_INST"},
        "WBP_UPSourceText": {"AnimSlam_INST"},
        "WBP_LevelUpScreen": {"Anim_LevelUp_INST"},
    }
    for widget, expected_animations in animation_expectations.items():
        report = animation_contract.get(widget, {})
        require(report.get("saved_assets"), f"animation was not saved for {widget}")
        require(report.get("complete_references"), f"animation references incomplete for {widget}")
        recovered_names = {entry.get("name") for entry in report.get("objects", [])}
        missing_animations = sorted(expected_animations - recovered_names)
        require(not missing_animations, f"source animation missing for {widget}: {missing_animations}")

    recovered_assets = [
        PROJECT / "Content/Recovery/UI/WBP_XPBar.uasset",
        PROJECT / "Content/Recovery/UI/XBP_XPSourceText.uasset",
        PROJECT / "Content/Recovery/UI/WBP_XPScreen.uasset",
        PROJECT / "Content/Recovery/UI/WBP_UPRewardScreen.uasset",
        PROJECT / "Content/Recovery/UI/WBP_UPSourceText.uasset",
        PROJECT / "Content/Recovery/UI/WBP_PlayerCard.uasset",
        PROJECT / "Content/Recovery/UI/WBP_LevelUpScreen.uasset",
        PROJECT / "Content/Recovery/Resources/PostGameSoundFX/whoosh-cinematic-161021_sfx.uasset",
        PROJECT / "Content/Recovery/Resources/PostGameSoundFX/drop-coin-384921.uasset",
        PROJECT / "Content/Recovery/Resources/PostGameSoundFX/Juice_SFX__11_.uasset",
        PROJECT / "Content/Recovery/Resources/PostGameSoundFX/Juice_SFX__9_.uasset",
        PROJECT / "Content/Recovery/Resources/PostGameSoundFX/Juice_SFX__5_.uasset",
    ]
    recovered_assets.extend(
        PROJECT / "Content/Recovery/Resources/UI/PostGameFlow/LevelIcons" / f"{icon.rsplit('.', 1)[-1]}.uasset"
        for icon in level_contract["recovered_assets"]
    )
    missing_assets = [str(path.relative_to(PROJECT)) for path in recovered_assets if not path.is_file()]
    require(not missing_assets, f"recovered post-game assets missing: {missing_assets}")

    report = {
        "recovery": "post-game-widget-contract",
        "source_executed": False,
        "source_widgets": [
            "WBP_XPBar",
            "XBP_XPSourceText",
            "WBP_XPScreen",
            "WBP_UPRewardScreen",
            "WBP_UPSourceText",
            "WBP_PlayerCard",
            "WBP_LevelUpScreen",
        ],
        "source_functions": function_reports,
        "native_recovery": native_reports,
        "animation_recovery": {
            name: {
                "saved_assets": animation_contract[name]["saved_assets"],
                "complete_references": animation_contract[name]["complete_references"],
                "animation_count": animation_contract[name]["animation_count"],
            }
            for name in animation_expectations
        },
        "verified": {
            "source_functions_decoded": True,
            "native_widget_logic_present": True,
            "post_game_animations_restored": True,
            "source_panel_feedback_recovered": True,
            "level_icons_contract_verified": True,
            "feedback_audio_contract_verified": True,
            "widget_and_feedback_assets_present": True,
            "automation_contract_present": True,
            "all_verified": True,
        },
        "source_sha256": {
            str(path.relative_to(PROJECT)).replace("\\", "/"): sha256(path)
            for path in sorted(source_files + [level_contract_path, audio_contract_path, animation_path])
        },
        "reconstruction_sha256": {
            str(Path(__file__).relative_to(PROJECT)).replace("\\", "/"): sha256(Path(__file__))
        },
    }
    output = EVIDENCE / "post-game-widget-contract-recovery.json"
    output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(output), "all_verified": True}, indent=2))


if __name__ == "__main__":
    main()
