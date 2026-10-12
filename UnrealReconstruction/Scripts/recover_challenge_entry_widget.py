from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
EVIDENCE = PROJECT / "RecoveryEvidence"
FUNCTIONS = EVIDENCE / "widget-functions" / "ChallengeEntryWidget"
LAYOUT_PATH = EVIDENCE / "ui-layout-values.json"
DEFAULTS_PATH = EVIDENCE / "widget-class-defaults.json"
ICON_REPORT_PATH = EVIDENCE / "challenge-icon-recovery.json"
OUTPUT_PATH = EVIDENCE / "challenge-entry-widget-recovery.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def read_function(name: str) -> dict:
    path = FUNCTIONS / f"{name}.json"
    require(path.is_file(), f"Missing decoded ChallengeEntryWidget function: {path}")
    return json.loads(path.read_text(encoding="utf-8"))


def entrypoint(function: dict) -> int:
    statements = function["statements"]
    require(len(statements) >= 1 and statements[0].get("op") == "EX_LocalFinalFunction", "Source event wrapper no longer enters the graph")
    parameters = statements[0].get("Parameters", [])
    require(len(parameters) == 1 and parameters[0].get("op") == "EX_IntConst", "Source event wrapper entrypoint changed")
    return int(parameters[0]["Value"])


def find_widget(records: list[dict], name: str) -> dict:
    matches = [record for record in records if record["name"] == name]
    require(len(matches) == 1, f"Expected one source widget named {name}, found {len(matches)}")
    return matches[0]


def value(record: dict, field: str) -> object:
    return record["values"][field]


def main() -> None:
    source_asset = ANALYSIS / "cooked-ui" / "CockHero" / "Content" / "Widgets" / "ChallengeEntryWidget.uasset"
    source_exports = source_asset.with_suffix(".uexp")
    recovered_asset = PROJECT / "Content" / "Recovery" / "UI" / "ChallengeEntryWidget.uasset"
    for path in (source_asset, source_exports, recovered_asset, LAYOUT_PATH, DEFAULTS_PATH, ICON_REPORT_PATH):
        require(path.is_file(), f"Missing ChallengeEntryWidget recovery artifact: {path}")

    functions = {
        name: read_function(name)
        for name in (
            "BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature",
            "BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature",
            "BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature",
            "BndEvt__ChallengeEntryWidget_TrackButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature",
            "ExecuteUbergraph_ChallengeEntryWidget",
            "OnChallengeClicked__DelegateSignature",
            "OnTrackButtonClicked__DelegateSignature",
            "PopulateChallengeEntry",
            "SetTrackButtonText",
        )
    }
    expected_sizes = {
        "BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature": 3,
        "BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature": 3,
        "BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature": 3,
        "BndEvt__ChallengeEntryWidget_TrackButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature": 3,
        "ExecuteUbergraph_ChallengeEntryWidget": 10,
        "OnChallengeClicked__DelegateSignature": 2,
        "OnTrackButtonClicked__DelegateSignature": 2,
        "PopulateChallengeEntry": 49,
        "SetTrackButtonText": 3,
    }
    actual_sizes = {name: function["function"]["statements"] for name, function in functions.items()}
    require(actual_sizes == expected_sizes, "ChallengeEntryWidget source function sizes changed")
    require(not any(function["function"].get("raw_fallback") for function in functions.values()), "ChallengeEntryWidget bytecode decode fell back to raw")

    entries = {
        "hover": entrypoint(functions["BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature"]),
        "unhover": entrypoint(functions["BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature"]),
        "challenge_click": entrypoint(functions["BndEvt__ChallengeEntryWidget_ChallengeEntryButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature"]),
        "track_click": entrypoint(functions["BndEvt__ChallengeEntryWidget_TrackButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature"]),
    }
    require(entries == {"hover": 10, "unhover": 62, "challenge_click": 114, "track_click": 147}, "ChallengeEntryWidget source event entrypoints changed")

    graph = functions["ExecuteUbergraph_ChallengeEntryWidget"]["function"]
    require(set(graph["calls"]) == {"OnChallengeClicked__DelegateSignature", "OnTrackButtonClicked__DelegateSignature", "PlayAnimation"}, "ChallengeEntryWidget graph calls changed")
    require({"ButtonHover", "ButtonUnhover", "Challenge_ID", "OnChallengeClicked", "OnTrackButtonClicked"} <= set(graph["fields"]), "ChallengeEntryWidget graph bindings changed")
    populate = functions["PopulateChallengeEntry"]["function"]
    require({"SetBrushFromTexture", "SetColorAndOpacity", "SetText", "Format", "Conv_IntToInt64"} <= set(populate["calls"]), "ChallengeEntryWidget populate contract changed")
    require({"Challenge_ID", "ChallengeTitle", "ChallengeIcon", "ChallengeCompletionStatus", "TrackButtonText", "IsChallengeTracked", "IsClaimed", "TrackedChallengesLength"} <= set(populate["fields"]), "ChallengeEntryWidget state fields changed")
    setter = functions["SetTrackButtonText"]["function"]
    require(set(setter["calls"]) == {"SetText"}, "ChallengeEntryWidget track-label setter changed")

    layout_all = json.loads(LAYOUT_PATH.read_text(encoding="utf-8"))
    layout = [record for record in layout_all["widgets"] if record["asset"] == "ChallengeEntryWidget"]
    require(len(layout) == 24, f"Unexpected ChallengeEntryWidget component count: {len(layout)}")
    require(not any(record["asset"] == "ChallengeEntryWidget" for record in layout_all.get("failures", [])), "ChallengeEntryWidget layout has decode failures")
    require(not any(record["asset"] == "ChallengeEntryWidget" for record in layout_all.get("omitted_custom_widgets", [])), "ChallengeEntryWidget layout omitted custom widgets")
    for name in ("SizeBox_1", "ChallengeEntryButton", "TrackButton", "ChallengeIcon", "ChallengeCompletionStatus", "ChallengeTitle", "TrackButtonText", "WidgetTree"):
        find_widget(layout, name)
    root = find_widget(layout, "SizeBox_1")
    icon_box = find_widget(layout, "SizeBox_0")
    track_box = find_widget(layout, "SizeBox_2")
    status = find_widget(layout, "ChallengeCompletionStatus")
    track_text = find_widget(layout, "TrackButtonText")
    require(value(root, "HeightOverride") == 128.0, "ChallengeEntryWidget root height changed")
    require(value(icon_box, "WidthOverride") == 100.0 and value(icon_box, "HeightOverride") == 100.0, "Challenge icon display size changed")
    require(value(track_box, "WidthOverride") == 256.0, "Challenge track control width changed")
    require(value(status, "Text")["text"] == "Completed", "Challenge completion default changed")
    require(value(status, "ColorAndOpacity")["SpecifiedColor"] == {"R": 0.0, "G": 0.5209959745407104, "B": 0.12477199733257294, "A": 1.0}, "Challenge completion color changed")
    require(value(track_text, "Text")["text"] == "track (1/2)", "Challenge tracking label default changed")
    require(value(track_text, "Font")["Size"] == 16.5, "Challenge tracking label font size changed")
    require(all(record["byte_identical_roundtrip"] for record in layout), "ChallengeEntryWidget layout component source decode is incomplete")

    defaults = json.loads(DEFAULTS_PATH.read_text(encoding="utf-8"))["defaults"]
    default = next((item for item in defaults if item["class"] == "ChallengeEntryWidget_C"), None)
    require(default is not None and default["byte_identical_roundtrip"], "ChallengeEntryWidget class defaults are incomplete")
    require(default["values"]["OnChallengeClicked"] == [] and default["values"]["OnTrackButtonClicked"] == [], "ChallengeEntryWidget delegate defaults changed")

    icon_report = json.loads(ICON_REPORT_PATH.read_text(encoding="utf-8"))
    icon_rows = icon_report.get("textures", [])
    icon_complete = (
        icon_report.get("expected_icons") == 55
        and icon_report.get("exported_icons") == 55
        and icon_report.get("decoded_icons") == 55
        and icon_report.get("imported_icons") == 55
        and len(icon_rows) == 55
        and all(row.get("decoded") and row.get("imported") and row.get("recovered_asset") for row in icon_rows)
    )
    require(icon_complete, "Challenge entry source artwork recovery is incomplete")

    source_paths = [source_asset, source_exports, LAYOUT_PATH, DEFAULTS_PATH, ICON_REPORT_PATH, *(FUNCTIONS / f"{name}.json" for name in functions)]
    reconstruction_paths = [
        recovered_asset,
        PROJECT / "Scripts" / "export_challenge_icons.py",
        PROJECT / "Scripts" / "decode_challenge_icons.py",
        PROJECT / "Scripts" / "import_challenge_icons.py",
        PROJECT / "Scripts" / "recover_challenge_entry_widget.py",
    ]
    report = {
        "recovery": "challenge-entry-widget",
        "source_executed": False,
        "source_asset": "/Game/Widgets/ChallengeEntryWidget",
        "recovered_asset": "/Game/Recovery/UI/ChallengeEntryWidget",
        "source_package": {"uasset_sha256": sha256(source_asset), "uexp_sha256": sha256(source_exports)},
        "function_statement_counts": actual_sizes,
        "source_entrypoints": entries,
        "source_contract": {
            "animations": ["ButtonHover", "ButtonUnhover", "ButtonClick"],
            "main_button": {"hover": "ButtonHover", "unhover": "ButtonUnhover", "click_broadcast": "OnChallengeClicked(Challenge_ID)"},
            "track_button": {"click_broadcast": "OnTrackButtonClicked(Challenge_ID, self)"},
            "presentation": {
                "completed_claimed": {"completion_label": "Completed", "track_label": "Done", "color": [0.0, 0.5209959745407104, 0.12477199733257294, 1.0]},
                "completed_unclaimed": {"completion_label": "Claim Rewards", "color": [0.0, 0.5209959745407104, 0.12477199733257294, 1.0]},
                "incomplete": {"completion_label": "Incomplete", "color": [1.0, 0.015208999626338482, 0.01298299990594387, 1.0]},
                "tracking_format": {"tracked": "Untrack {totaltracked}/2", "untracked": "Track {totaltracked}/2"},
            },
        },
        "layout": {
            "components": len(layout),
            "root": "SizeBox_1",
            "root_height": 128.0,
            "icon_size": [100.0, 100.0],
            "track_button_width": 256.0,
            "required_components": ["ChallengeEntryButton", "TrackButton", "ChallengeIcon", "ChallengeCompletionStatus", "ChallengeTitle", "TrackButtonText"],
            "byte_identical_component_payloads": True,
        },
        "source_artwork": {"expected_icons": 55, "all_imported": True, "report": str(ICON_REPORT_PATH)},
        "source_sha256": {str(path): sha256(path) for path in source_paths},
        "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
    }
    OUTPUT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"functions": len(functions), "layout_components": len(layout), "icons": 55, "report": str(OUTPUT_PATH)}, indent=2))


if __name__ == "__main__":
    main()
