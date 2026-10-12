"""Record the decoded source contract for modifier-card interaction."""

import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
ENTRY_DIR = EVIDENCE / "widget-functions" / "ModifierCardEntryWidget"
TAB_GRAPH = EVIDENCE / "widget-functions" / "ModifiersTabWidget" / "ExecuteUbergraph_ModifiersTabWidget.json"
CLASS_DEFAULTS = EVIDENCE / "widget-class-defaults.json"
OUTPUT = EVIDENCE / "modifier-card-contract-recovery.json"


def load(path: Path):
    return json.loads(path.read_text(encoding="utf-8"))


def walk(value):
    if isinstance(value, dict):
        yield value
        for child in value.values():
            yield from walk(child)
    elif isinstance(value, list):
        for child in value:
            yield from walk(child)


def calls(graph, name):
    return any(
        node.get("op") in {"EX_FinalFunction", "EX_LocalFinalFunction", "EX_VirtualFunction", "EX_LocalVirtualFunction", "EX_CallMath"}
        and (node.get("StackNode") == name or node.get("VirtualFunctionName") == name)
        for node in walk(graph["statements"])
    )


def main():
    entry_graph = load(ENTRY_DIR / "ExecuteUbergraph_ModifierCardEntryWidget.json")
    tooltip_graph = load(ENTRY_DIR / "GetToolTipWidget.json")
    details_graph = load(ENTRY_DIR / "Populate_Details.json")
    tab_graph = load(TAB_GRAPH)
    defaults = load(CLASS_DEFAULTS)

    modifier_class = next(item for item in defaults["classes"] if item["class"] == "ModifierCardEntryWidget_C")
    bindings = modifier_class["metadata"]["Bindings"]
    tooltip_targets = [binding["ObjectName"] for binding in bindings if binding["FunctionName"] == "GetToolTipWidget"]

    click_events = sorted(path.stem for path in ENTRY_DIR.glob("BndEvt*.json") if "OnButtonClickedEvent" in path.stem)
    hover_events = sorted(path.stem for path in ENTRY_DIR.glob("BndEvt*.json") if "OnButtonHoverEvent" in path.stem)
    parent_bindings = [
        statement
        for statement in tab_graph["statements"]
        if statement.get("op") == "EX_BindDelegate" and statement.get("FunctionName") == "ToggleModifier"
    ]
    parent_delegate_adds = [
        statement
        for statement in tab_graph["statements"]
        if statement.get("op") == "EX_AddMulticastDelegate"
        and statement.get("Delegate", {}).get("ContextExpression", {}).get("Variable", {}).get("field") == "OnClicked"
    ]

    expected_tooltip_targets = ["SizeBox_15", "VerticalBox_149", "LockOverlay", "Overlay_388"]
    report = {
        "source_executed": False,
        "source": {
            "entry_graph": str(ENTRY_DIR.relative_to(PROJECT)),
            "tab_graph": str(TAB_GRAPH.relative_to(PROJECT)),
            "class_defaults": str(CLASS_DEFAULTS.relative_to(PROJECT)),
        },
        "entry_contract": {
            "toggle_click_events": click_events,
            "hover_events": hover_events,
            "on_clicked_delegate_parameters": ["ModifierTitle_Text", "Self"],
            "click_animation": "ClickButton",
            "hover_animations": ["HoverModifier", "UnHoverModifier", "HoverButton", "UnHoverButton"],
            "toggle_labels": ["Enabled", "Disabled"],
            "toggle_colors": {
                "enabled": [0.0, 0.5209959745407104, 0.12477199733257294, 1.0],
                "disabled": [1.0, 0.015208999626338482, 0.01298299990594387, 1.0],
            },
        },
        "tooltip_contract": {
            "targets": tooltip_targets,
            "unlocked_title": "{modifier title} - Unlocked",
            "locked_title": "{modifier title} - Locked",
            "unlocked_description_source": "ModifierDescription_Text",
            "locked_description_source": "Challenge Description",
        },
        "tab_contract": {
            "delegate_owner": "ModifierCardEntryWidget_C.OnClicked",
            "delegate_handler": "ToggleModifier",
            "grid_columns": 4,
            "direct_toggle_updates_entry": "SetButtonToggleWSound",
            "conflict_confirmation": ["remove conflicts", "add selected modifier", "PopulateModifiers", "PlayToggleSound"],
        },
        "verification": {
            "single_toggle_click_event": click_events == ["BndEvt__ModifierCardEntryWidget_ToggleModifierButton_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature"],
            "background_has_no_click_event": not any("BackgroundButton" in event for event in click_events),
            "source_broadcasts_click_delegate": any(node.get("op") == "EX_CallMulticastDelegate" and node.get("StackNode") == "OnClicked__DelegateSignature" for node in walk(entry_graph["statements"])),
            "source_populates_entry": all(calls(details_graph, name) for name in ["SetText", "SetBrushFromTexture", "SetButtonToggle", "SetVisibility"]),
            "tooltip_targets_exact": tooltip_targets == expected_tooltip_targets,
            "tooltip_branches_exact": calls(tooltip_graph, "Set Title & Description"),
            "tab_binds_card_delegate": len(parent_bindings) == 1 and len(parent_delegate_adds) == 1,
            "tab_uses_source_grid_math": all(calls(tab_graph, name) for name in ["Divide_IntInt", "Percent_IntInt", "AddChildToUniformGrid"]),
            "tab_direct_toggle_contract": all(calls(tab_graph, name) for name in ["SetButtonToggleWSound", "Array_Add", "Array_RemoveItem", "SaveAllData"]),
        },
    }
    report["verification"]["all_verified"] = all(report["verification"].values())
    if not report["verification"]["all_verified"]:
        raise RuntimeError(json.dumps(report["verification"], indent=2))
    OUTPUT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"report": str(OUTPUT), "verified": report["verification"]}, indent=2))


if __name__ == "__main__":
    main()
