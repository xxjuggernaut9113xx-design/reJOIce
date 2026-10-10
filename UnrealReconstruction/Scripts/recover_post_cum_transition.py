import hashlib
import json
from pathlib import Path


analysis = Path(r"C:\Users\webma\analysis\cockhero-v004")
project = Path(__file__).resolve().parents[1]
widget_functions = analysis / "widget-functions" / "PostCumContinue_Widget"
shipping_executable = Path(
    r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive"
    r"\PrepV2\Windows\CockHero\Binaries\Win64\CockHero.exe"
)


def read_json(path: Path):
    return json.loads(path.read_text(encoding="utf-8-sig"))


def sha256(path: Path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def stack_nodes(value):
    if isinstance(value, dict):
        if "StackNode" in value:
            yield value["StackNode"]
        for child in value.values():
            yield from stack_nodes(child)
    elif isinstance(value, list):
        for child in value:
            yield from stack_nodes(child)


def includes_field(value, fragment):
    if isinstance(value, dict):
        if value.get("field", "").find(fragment) >= 0:
            return True
        return any(includes_field(child, fragment) for child in value.values())
    if isinstance(value, list):
        return any(includes_field(child, fragment) for child in value)
    return False


handler_path = widget_functions / (
    "BndEvt__PostCumContinue_Widget_ViewResultsButton_"
    "K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json"
)
graph_path = widget_functions / "ExecuteUbergraph_PostCumContinue_Widget.json"
handler = read_json(handler_path)
graph = read_json(graph_path)

handler_call = handler["statements"][0]
if (
    handler_call.get("op") != "EX_LocalFinalFunction"
    or handler_call.get("StackNode") != "ExecuteUbergraph_PostCumContinue_Widget"
    or handler_call.get("Parameters", [{}])[0].get("Value") != 67
):
    raise RuntimeError("ViewResultsButton no longer routes to ExecuteUbergraph entry 67")

required_calls = {"PauseSequence", "Create", "AddToViewport", "Array_Add"}
calls = set(graph["function"]["calls"])
if required_calls - calls:
    raise RuntimeError(f"Post-cum graph lacks calls: {sorted(required_calls - calls)}")

statements = graph["statements"]
source_indices = {}
for index, statement in enumerate(statements):
    names = set(stack_nodes(statement))
    for name in required_calls:
        if name in names:
            source_indices.setdefault(name, index)

expected_indices = {
    "PauseSequence": 8,
    "Create": 9,
    "AddToViewport": 10,
    "Array_Add": 11,
}
if source_indices != expected_indices:
    raise RuntimeError(f"Unexpected post-cum operation order: {source_indices}")
if not includes_field(statements[11], "BrokenComboArray"):
    raise RuntimeError("Post-cum Array_Add no longer targets BrokenComboArray")
if not includes_field(statements[11], "CurrentComboCount"):
    raise RuntimeError("Post-cum Array_Add no longer records CurrentComboCount")
if not includes_field(statements[13], "EdgeStreak"):
    raise RuntimeError("Post-cum graph no longer clears EdgeStreak")
if not includes_field(statements[14], "CurrentComboCount"):
    raise RuntimeError("Post-cum graph no longer clears CurrentComboCount")

report = {
    "source_executed": False,
    "sources": {
        "view_results_handler": str(handler_path),
        "view_results_handler_sha256": sha256(handler_path),
        "post_cum_graph": str(graph_path),
        "post_cum_graph_sha256": sha256(graph_path),
        "shipping_executable": str(shipping_executable),
        "shipping_executable_sha256": sha256(shipping_executable),
    },
    "handler": {
        "widget": "PostCumContinue_Widget",
        "control": "ViewResultsButton",
        "function": "ExecuteUbergraph_PostCumContinue_Widget",
        "entry_point": 67,
    },
    "source_operation_order": [
        {"statement_index": 8, "operation": "PauseSequence"},
        {"statement_index": 9, "operation": "Create", "class": "WBP_PostGameFlow_Master"},
        {"statement_index": 10, "operation": "AddToViewport", "z_order": 0},
        {
            "statement_index": 11,
            "operation": "Array_Add",
            "target": "PlayerVariablesStruct.BrokenComboArray",
            "value": "PlayerVariablesStruct.CurrentComboCount",
        },
        {"statement_index": 13, "operation": "Set", "target": "PlayerVariablesStruct.EdgeStreak", "value": 0},
        {"statement_index": 14, "operation": "Set", "target": "PlayerVariablesStruct.CurrentComboCount", "value": 0},
    ],
    "runtime_mapping": {
        "source_handler": "ARecoveredGlobalManager::OpenPostGameResults",
        "pause": "BeatTimeline->PauseSequence()",
        "results_widget": "/Game/Recovery/UI/WBP_PostGameFlow_Master",
        "combo_history": "PlayerVariables.BrokenComboArray.Add(PlayerVariables.CurrentComboCount)",
        "state_clear": [
            "PlayerVariables.EdgeStreak = 0",
            "PlayerVariables.CurrentComboCount = 0",
            "EdgeStreak = 0",
        ],
        "return_cleanup": "PostGameSequence->Stop(); PostGameSequence = nullptr",
    },
}

output = project / "RecoveryEvidence" / "post-cum-transition-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(output)
