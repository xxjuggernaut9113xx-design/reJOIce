import hashlib
import json
from pathlib import Path


analysis = Path(r"C:\Users\webma\analysis\cockhero-v004")
project = Path(__file__).resolve().parents[1]
source = analysis / "widget-functions" / "SessionCompletionScreen" / "AddStatstoSave.json"
shipping_executable = Path(
    r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive"
    r"\PrepV2\Windows\CockHero\Binaries\Win64\CockHero.exe"
)
runtime_sources = {
    "post_game": project / "Source" / "CockHeroRecovered" / "RecoveredPostGame.cpp",
    "save": project / "Source" / "CockHeroRecovered" / "RecoveredSave.cpp",
    "rules": project / "Source" / "CockHeroRecovered" / "RecoveredRules.cpp",
    "rules_header": project / "Source" / "CockHeroRecovered" / "RecoveredRules.h",
}


def read_json(path: Path):
    return json.loads(path.read_text(encoding="utf-8-sig"))


def sha256(path: Path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def names(value):
    if isinstance(value, dict):
        for key in ("StackNode", "VirtualFunctionName"):
            if key in value:
                yield value[key]
        for child in value.values():
            yield from names(child)
    elif isinstance(value, list):
        for child in value:
            yield from names(child)


def contains_field(value, fragment):
    if isinstance(value, dict):
        if fragment in value.get("field", ""):
            return True
        return any(contains_field(child, fragment) for child in value.values())
    if isinstance(value, list):
        return any(contains_field(child, fragment) for child in value)
    return False


decoded = read_json(source)
function = decoded["function"]
statements = decoded["statements"]
if function["name"] != "AddStatstoSave" or len(statements) != 26:
    raise RuntimeError("Session completion persistence source function changed")
required_calls = {"Add_IntInt", "Array_Add", "Array_Append", "GetGameInstance", "SaveAllData"}
if required_calls - set(function["calls"]):
    raise RuntimeError(f"Source calls are incomplete: {sorted(required_calls - set(function['calls']))}")

checks = (
    (4, "Add_IntInt", "TotalLifetimeItemUses", "TotalDefenseItemUses"),
    (6, "Array_Add", "AllSessionStrokeCounts", "TotalStrokeCount"),
    (7, "Array_Add", "AllSessionEdges", "TotalEdgeCount"),
    (8, "Array_Append", "AllSessionCombos", "BrokenComboArray"),
    (9, "Array_Add", "AllSessionTimes", "SessionLength"),
    (10, "Add_IntInt", "LifetimeTauntCount", "TotalTauntsUsed"),
    (12, "Add_IntInt", "LifetimeMaxHeatDraws", "SessionDrawsAtMaxHeat"),
    (15, "Add_IntInt", "SessionsWon", ""),
    (20, "Add_IntInt", "SessionsLost", ""),
)
for index, operation, target, source_field in checks:
    if operation not in set(names(statements[index])):
        raise RuntimeError(f"Source statement {index} no longer invokes {operation}")
    if not contains_field(statements[index], target):
        raise RuntimeError(f"Source statement {index} no longer targets {target}")
    if source_field and not contains_field(statements[index], source_field):
        raise RuntimeError(f"Source statement {index} no longer reads {source_field}")
if not contains_field(statements[14], "IsAllowedToCum"):
    raise RuntimeError("Session completion outcome branch changed")
if "SaveAllData" not in set(names(statements[18])):
    raise RuntimeError("Winning completion branch no longer persists the save")

report = {
    "source_executed": False,
    "sources": {
        "session_completion_add_stats": str(source),
        "session_completion_add_stats_sha256": sha256(source),
        "shipping_executable": str(shipping_executable),
        "shipping_executable_sha256": sha256(shipping_executable),
    },
    "reconstruction_sources": {
        name: {"path": str(path), "sha256": sha256(path)}
        for name, path in runtime_sources.items()
    },
    "source_operation_order": [
        {
            "statement_index": 4,
            "operation": "Add_IntInt",
            "target": "CurrentSave.TotalLifetimeItemUses",
            "value": "PlayerVariablesStruct.TotalDefenseItemUses",
        },
        {
            "statement_index": 6,
            "operation": "Array_Add",
            "target": "CurrentSave.AllSessionStrokeCounts",
            "value": "PlayerVariablesStruct.TotalStrokeCount",
        },
        {
            "statement_index": 7,
            "operation": "Array_Add",
            "target": "CurrentSave.AllSessionEdges",
            "value": "PlayerVariablesStruct.TotalEdgeCount",
        },
        {
            "statement_index": 8,
            "operation": "Array_Append",
            "target": "CurrentSave.AllSessionCombos",
            "value": "PlayerVariablesStruct.BrokenComboArray",
        },
        {
            "statement_index": 9,
            "operation": "Array_Add",
            "target": "CurrentSave.AllSessionTimes",
            "value": "PlayerVariablesStruct.SessionLength",
        },
        {
            "statement_index": 10,
            "operation": "Add_IntInt",
            "target": "CurrentSave.LifetimeTauntCount",
            "value": "PlayerVariablesStruct.TotalTauntsUsed",
        },
        {
            "statement_index": 12,
            "operation": "Add_IntInt",
            "target": "CurrentSave.LifetimeMaxHeatDraws",
            "value": "PlayerVariablesStruct.SessionDrawsAtMaxHeat",
        },
        {
            "statement_index": 14,
            "operation": "Branch",
            "condition": "PlayerVariablesStruct.IsAllowedToCum?",
        },
        {
            "statement_index": 15,
            "operation": "Add_IntInt",
            "target": "CurrentSave.SessionsWon",
            "value": 1,
        },
        {
            "statement_index": 20,
            "operation": "Add_IntInt",
            "target": "CurrentSave.SessionsLost",
            "value": 1,
        },
        {
            "statement_index": 18,
            "operation": "SaveAllData",
        },
    ],
    "runtime_mapping": {
        "entry": "ARecoveredGlobalManager::OpenPostGameResults",
        "post_cum_combo_order": "append active combo before persistence",
        "completion_write": "ARecoveredGlobalManager::PersistRecoveredSessionCompletionStats",
        "numeric_arrays": [
            "URecoveredSaveGame::GetIntArraySetting",
            "URecoveredSaveGame::SetIntArraySetting",
        ],
        "max_heat_source_field": "PlayerVariables.SessionDrawsAtMaxHeat",
        "save": "URecoveredGameInstance::SaveRecoveredState",
        "idempotency": "bRecoveredSessionCompletionStatsPersisted",
    },
}

output = project / "RecoveryEvidence" / "session-completion-persistence-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(output)
