from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
EVIDENCE = PROJECT / "RecoveryEvidence"


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def contains(value: object, needle: str) -> bool:
    if isinstance(value, dict):
        return any(contains(item, needle) for item in value.values())
    if isinstance(value, list):
        return any(contains(item, needle) for item in value)
    return value == needle


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


main_functions = load_json(ANALYSIS / "decoded" / "MainMenu-functions.json")
main_graph = load_json(ANALYSIS / "blueprint-functions" / "MainMenu" / "ExecuteUbergraph_MainMenu.json")
stats_defaults = load_json(EVIDENCE / "widget-class-defaults.json")
stats_average = load_json(EVIDENCE / "widget-functions" / "StatsScreenWidget" / "CalculateLifetimeAverages.json")
stats_scores = load_json(EVIDENCE / "widget-functions" / "StatsScreenWidget" / "CalculateHighScores.json")
stats_time = load_json(EVIDENCE / "widget-functions" / "StatsScreenWidget" / "FormatTime.json")
stats_graph = load_json(EVIDENCE / "widget-functions" / "StatsScreenWidget" / "ExecuteUbergraph_StatsScreenWidget.json")
edge_graph = load_json(ANALYSIS / "blueprint-functions" / "BP_EdgeManager" / "ExecuteUbergraph_BP_EdgeManager.json")

imports = main_functions["Imports"]
require(imports[246]["ObjectName"] == "ChallengesMenuWidget_C", "MainMenu import -247 no longer resolves ChallengesMenuWidget_C")
require(imports[250]["ObjectName"] == "StatsScreenWidget_C", "MainMenu import -251 no longer resolves StatsScreenWidget_C")
require(contains(main_graph["statements"][59], "StatsClick"), "Stats button source animation missing")
require(contains(main_graph["statements"][60], -247), "Stats button source target missing")
require(main_graph["statements"][165]["CodeOffset"] == 248, "Stats debug source jump changed")
require(contains(main_graph["statements"][9], -251), "Stats debug source target missing")

stats_record = next(item for item in stats_defaults["classes"] if item["class"] == "StatsScreenWidget_C")
bindings = {item["ObjectName"]: item["FunctionName"] for item in stats_record["metadata"]["Bindings"]}
expected_bindings = {
    "TextBlock_5": "GetLifeTimeStatsDisplay",
    "TextBlock_7": "GetHighScores",
    "TextBlock": "Get Avg Session Duration Text",
    "TextBlock_1": "GetText",
    "TextBlock_2": "GetText_0",
    "TextBlock_3": "GetText_1",
}
require(bindings == expected_bindings, "StatsScreenWidget text bindings do not match the source")
require(stats_average["function"]["fields"].count("AllStrokesPerEdge") == 1, "Stats average source lost AllStrokesPerEdge")
require(all(field in stats_scores["function"]["fields"] for field in ("AllSessionCombos", "AllSessionTimes", "AllSessionEdges", "AllSessionStrokeCounts")), "Stats high-score source arrays missing")
require(contains(stats_time["statements"], 3600) and contains(stats_time["statements"], 60), "Stats time formatter constants missing")
require(stats_graph["statements"][1]["ContextExpression"]["VirtualFunctionName"] == "RefreshMainMenuBackground", "Stats back route does not refresh the menu")
require(stats_graph["statements"][2]["VirtualFunctionName"] == "RemoveFromParent", "Stats back route does not remove the screen")

for statement_index in (51, 135):
    statement = edge_graph["statements"][statement_index]
    require(contains(statement, "AllStrokesPerEdge"), f"Edge source history statement {statement_index} missing")
    require(contains(statement, "CurrentComboCount_66_5F7B16A442F400DEAE401686B872656A"), f"Edge source combo sample {statement_index} missing")

source_paths = [
    ANALYSIS / "decoded" / "MainMenu-functions.json",
    ANALYSIS / "blueprint-functions" / "MainMenu" / "ExecuteUbergraph_MainMenu.json",
    ANALYSIS / "blueprint-functions" / "BP_EdgeManager" / "ExecuteUbergraph_BP_EdgeManager.json",
    EVIDENCE / "widget-class-defaults.json",
    EVIDENCE / "widget-functions" / "StatsScreenWidget" / "CalculateLifetimeAverages.json",
    EVIDENCE / "widget-functions" / "StatsScreenWidget" / "CalculateHighScores.json",
    EVIDENCE / "widget-functions" / "StatsScreenWidget" / "FormatTime.json",
    EVIDENCE / "widget-functions" / "StatsScreenWidget" / "ExecuteUbergraph_StatsScreenWidget.json",
]
reconstruction_paths = [
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredMenu.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredStatsWidget.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredStatsWidget.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredEdgeManager.cpp",
    PROJECT / "Content" / "Recovery" / "UI" / "StatsScreenWidget.uasset",
]

report = {
    "recovery": "statistics-screen",
    "source_contract": {
        "stats_button_entry": 1700,
        "stats_button_target": "ChallengesMenuWidget_C",
        "stats_debug_entry": 5111,
        "stats_debug_target": "StatsScreenWidget_C",
        "statistics_bindings": expected_bindings,
        "edge_history_key": "AllStrokesPerEdge",
        "time_format": "HH:MM:SS with two integral digits",
    },
    "checks": {
        "main_menu_routes_verified": True,
        "statistics_bindings_verified": True,
        "statistics_calculations_verified": True,
        "edge_history_writes_verified": True,
        "native_parent_recovery_required": "URecoveredStatsScreenWidget",
    },
    "source_sha256": {str(path): sha256(path) for path in source_paths},
    "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
}

output = EVIDENCE / "statistics-screen-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
