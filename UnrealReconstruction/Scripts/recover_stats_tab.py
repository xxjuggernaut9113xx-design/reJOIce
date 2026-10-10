from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
EVIDENCE = PROJECT / "RecoveryEvidence"
FUNCTIONS = EVIDENCE / "widget-functions" / "StatsTabWidget"


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def entrypoint(path: Path) -> int:
    statement = load_json(path)["statements"][0]
    require(statement["op"] == "EX_LocalFinalFunction", f"{path.name} does not enter the source graph")
    values = statement.get("Parameters", [])
    require(len(values) == 1 and values[0]["op"] == "EX_IntConst", f"{path.name} entrypoint encoding changed")
    return values[0]["Value"]


stats = load_json(FUNCTIONS / "InitializeStats.json")
graph = load_json(FUNCTIONS / "ExecuteUbergraph_StatsTabWidget.json")
construct = entrypoint(FUNCTIONS / "Construct.json")
edit = entrypoint(FUNCTIONS / "BndEvt__StatsTabWidget_EditPlayerCardButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json")
closed = entrypoint(FUNCTIONS / "OnEditBoxClosed.json")

expected_calls = [
    "GetLifetimeStatsText",
    "GetHighscoresText",
    "GetAverageDurationText",
    "GetAverageEdgesText",
    "GetAverageStrokesPerMinuteText",
    "GetAverageStrokesText",
    "GetEquippedPlayerCard",
    "GetPlayerCardData",
    "GetXPForNextLevel",
    "GetXPProgressInCurrentLevel",
    "GetLevelProgressPercent",
    "SetBrushFromTexture",
    "SetPercent",
]
for call in expected_calls:
    require(call in stats["function"]["calls"], f"InitializeStats no longer calls {call}")
require(construct == 286, "StatsTabWidget construct entrypoint changed")
require(edit == 291, "StatsTabWidget edit entrypoint changed")
require(closed == 450, "StatsTabWidget close entrypoint changed")
require(graph["function"]["calls"] == ["AddToViewport", "Create", "GetGameInstance", "GetGameMode", "InitializeStats"], "StatsTabWidget graph contract changed")

source_paths = [
    FUNCTIONS / "Construct.json",
    FUNCTIONS / "InitializeStats.json",
    FUNCTIONS / "ExecuteUbergraph_StatsTabWidget.json",
    FUNCTIONS / "BndEvt__StatsTabWidget_EditPlayerCardButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json",
    FUNCTIONS / "OnEditBoxClosed.json",
    ANALYSIS / "ghidra-native" / "integration-decompiled.c",
]
reconstruction_paths = [
    PROJECT / "Content" / "Recovery" / "UI" / "StatsTabWidget.uasset",
    PROJECT / "Content" / "Recovery" / "UI" / "EditUsernameOverlay.uasset",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredStatsTabWidget.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredStatsTabWidget.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredEditUsernameOverlay.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredEditUsernameOverlay.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredProgression.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredRewards.cpp",
]
for path in reconstruction_paths:
    require(path.exists(), f"Missing reconstructed stats artifact: {path}")

report = {
    "recovery": "stats-tab-widget",
    "source_executed": False,
    "source_entrypoints": {
        "Construct": construct,
        "EditPlayerCardButton": edit,
        "OnEditBoxClosed": closed,
    },
    "ui_fields": [
        "LifetimeStatsText",
        "HighscoresText",
        "AvgDurationText",
        "AvgEdgesText",
        "AvgStrokesPerMinText",
        "AvgStrokesText",
        "SelectedPlayerCard",
        "LevelText",
        "LevelProgressBar",
        "PlayerCardTitle",
    ],
    "native_calls": expected_calls,
    "edit_overlay": {
        "asset": "/Game/Recovery/UI/EditUsernameOverlay",
        "close_refreshes_stats": True,
        "maximum_username_length": 14,
    },
    "source_sha256": {str(path): sha256(path) for path in source_paths},
    "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
}

output = EVIDENCE / "stats-tab-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
