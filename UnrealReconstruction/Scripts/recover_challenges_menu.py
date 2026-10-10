from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
EVIDENCE = PROJECT / "RecoveryEvidence"
FUNCTIONS = EVIDENCE / "widget-functions" / "ChallengesMenuWidget"


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def contains(value: object, needle: object) -> bool:
    if isinstance(value, dict):
        return any(contains(item, needle) for item in value.values())
    if isinstance(value, list):
        return any(contains(item, needle) for item in value)
    return value == needle


def entrypoint(name: str) -> int:
    statements = load_json(FUNCTIONS / name)["statements"]
    first = statements[0]
    require(first["op"] == "EX_LocalFinalFunction", f"{name} no longer enters the source graph")
    parameters = first.get("Parameters", [])
    require(len(parameters) == 1 and parameters[0]["op"] == "EX_IntConst", f"{name} entrypoint encoding changed")
    return parameters[0]["Value"]


source_graph = load_json(FUNCTIONS / "ExecuteUbergraph_ChallengesMenuWidget.json")
source_statements = source_graph["statements"]
widget_defaults = load_json(EVIDENCE / "widget-class-defaults.json")
layout = load_json(EVIDENCE / "ui-layout-values.json")
tooltips = load_json(EVIDENCE / "static-tooltip-values.json")
source_package = ANALYSIS / "decoded-ui" / "CockHero" / "Content" / "Widgets" / "ChallengesMenuWidget.json"

require(source_statements[8]["ContextExpression"]["VirtualFunctionName"] == "PlayBackgroundMediaManual", "construct background call changed")
require(source_statements[8]["ContextExpression"]["Parameters"][0]["Value"] == "backgroundmenuloop", "construct background media changed")
require(source_statements[14]["ContextExpression"]["VirtualFunctionName"] == "RefreshMainMenuBackground", "back refresh call changed")
require(source_statements[15]["VirtualFunctionName"] == "RemoveFromParent", "back removal call changed")
require(source_statements[10]["AssignmentExpression"]["Parameters"][0]["Variable"]["field"] == "HoverBackButton", "back hover animation changed")
require(source_statements[12]["AssignmentExpression"]["Parameters"][0]["Variable"]["field"] == "UnhoverBackButton", "back unhover animation changed")

route_specs = [
    ("ChallengesButton", "BndEvt__ChallengesMenuWidget_ChallengesButton_K2Node_ComponentBoundEvent_1_OnButtonClickedEvent__DelegateSignature.json", 681, 0, "ChallengesButton", ["ClickedStyle", "UnclickedStyle"]),
    ("PlayerCardButton", "BndEvt__ChallengesMenuWidget_PlayerCardButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json", 399, 1, "PlayerCardButton", ["PopulatePlayerCards", "UpdateLevelDisplay", "ClickedStyle", "UnclickedStyle"]),
    ("StatsButton", "BndEvt__ChallengesMenuWidget_StatsButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature.json", 891, 2, "StatsButton", ["InitializeStats", "ClickedStyle", "UnclickedStyle"]),
    ("ModifiersButton", "BndEvt__ChallengesMenuWidget_ModifiersButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature.json", 1137, 3, "ModifiersButton", ["PopulateModifiers", "ClickedStyle", "UnclickedStyle"]),
]

routes = []
for button, filename, expected_entry, active_index, active_button, expected_calls in route_specs:
    actual_entry = entrypoint(filename)
    require(actual_entry == expected_entry, f"{button} source entrypoint changed")
    graph_text = json.dumps(source_statements, ensure_ascii=False)
    for call in expected_calls:
        require(call in graph_text, f"{button} source call {call} missing")
    routes.append(
        {
            "button": button,
            "entrypoint": actual_entry,
            "active_widget_index": active_index,
            "active_button": active_button,
            "expected_calls": expected_calls,
        }
    )

require(entrypoint("Construct.json") == 51, "construct source entrypoint changed")
require(entrypoint("BndEvt__ChallengesMenuWidget_BackButton_K2Node_ComponentBoundEvent_8_OnButtonClickedEvent__DelegateSignature.json") == 344, "back source entrypoint changed")
require(entrypoint("BndEvt__SettingsMenuWidget_BackButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature.json") == 240, "hover source entrypoint changed")
require(entrypoint("BndEvt__SettingsMenuWidget_BackButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature.json") == 292, "unhover source entrypoint changed")

defaults = next(item["values"] for item in widget_defaults["defaults"] if item["class"] == "ChallengesMenuWidget_C")
for name in ("ClickedStyle", "UnclickedStyle"):
    require(name in defaults, f"{name} source default missing")
    require(defaults[name]["Normal"]["DrawAs"] == 1, f"{name} source normal draw mode changed")
    require(defaults[name]["Hovered"]["DrawAs"] == 4, f"{name} source hover draw mode changed")
    require(defaults[name]["Pressed"]["DrawAs"] == 4, f"{name} source pressed draw mode changed")

switcher = next(item for item in layout["widgets"] if item["asset"] == "ChallengesMenuWidget" and item["name"] == "WidgetSwitcher")
slot_records = {
    item["export_index"]: item
    for item in layout["widgets"]
    if item["asset"] == "ChallengesMenuWidget" and item["class"] == "WidgetSwitcherSlot"
}
children = [slot_records[slot["index"]]["values"]["Content"]["name"] for slot in switcher["values"]["Slots"]]
require(children == ["ChallengesTabWidget", "PlayerCardsTabWidget", "StatsTabWidget", "ModifiersTabWidget"], "widget switcher source order changed")

challenge_tooltips = [record for record in tooltips["records"] if record["asset"] == "ChallengesMenuWidget"]
require([record["widget"] for record in challenge_tooltips] == ["ChallengesButton", "StatsButton", "PlayerCardButton", "ModifiersButton"], "challenge tooltip source bindings changed")
require(all(record["title"]["text"] and record["description"]["text"] for record in challenge_tooltips), "challenge tooltip source text missing")

source_paths = [
    FUNCTIONS / "Construct.json",
    FUNCTIONS / "ExecuteUbergraph_ChallengesMenuWidget.json",
    *(FUNCTIONS / spec[1] for spec in route_specs),
    FUNCTIONS / "BndEvt__ChallengesMenuWidget_BackButton_K2Node_ComponentBoundEvent_8_OnButtonClickedEvent__DelegateSignature.json",
    FUNCTIONS / "BndEvt__SettingsMenuWidget_BackButton_K2Node_ComponentBoundEvent_4_OnButtonHoverEvent__DelegateSignature.json",
    FUNCTIONS / "BndEvt__SettingsMenuWidget_BackButton_K2Node_ComponentBoundEvent_5_OnButtonHoverEvent__DelegateSignature.json",
    EVIDENCE / "widget-class-defaults.json",
    EVIDENCE / "ui-layout-values.json",
    EVIDENCE / "static-tooltip-values.json",
    source_package,
]
reconstruction_paths = [
    PROJECT / "Content" / "Recovery" / "UI" / "ChallengesMenuWidget.uasset",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredChallengesMenu.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredChallengesMenu.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredWidgetRecovery.cpp",
]

report = {
    "recovery": "challenges-menu-navigation",
    "source_executed": False,
    "source_entrypoints": {
        "Construct": 51,
        "BackButton": 344,
        "BackButtonHover": 240,
        "BackButtonUnhover": 292,
    },
    "routes": routes,
    "switcher_children": children,
    "background_media": "backgroundmenuloop",
    "back_animations": ["HoverBackButton", "UnhoverBackButton"],
    "style_contract": {
        "unclicked_normal_tint": defaults["UnclickedStyle"]["Normal"]["TintColor"]["SpecifiedColor"],
        "clicked_normal_tint": defaults["ClickedStyle"]["Normal"]["TintColor"]["SpecifiedColor"],
        "normal_draw_as": defaults["ClickedStyle"]["Normal"]["DrawAs"],
        "interactive_draw_as": defaults["ClickedStyle"]["Hovered"]["DrawAs"],
        "padding": defaults["ClickedStyle"]["NormalPadding"],
    },
    "tooltips": [
        {
            "widget": record["widget"],
            "title": record["title"]["text"],
            "description": record["description"]["text"],
        }
        for record in challenge_tooltips
    ],
    "source_sha256": {str(path): sha256(path) for path in source_paths},
    "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
}

output = EVIDENCE / "challenges-menu-navigation-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
