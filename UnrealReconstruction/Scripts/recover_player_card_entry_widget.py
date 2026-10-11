from __future__ import annotations

import collections
import hashlib
import json
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
UASSETGUI = ANALYSIS / "tools" / "uassetgui" / "UAssetGUI.exe"
LEGACY_ASSET = ANALYSIS / "player-cards-legacy-v2" / "CockHero" / "Content" / "PlayerCards" / "PlayerCardEntryWidget.uasset"
LEGACY_EXPORTS = LEGACY_ASSET.with_suffix(".uexp")
RAW_HEADER = ANALYSIS / "player-cards-extract" / "CockHero" / "Content" / "PlayerCards" / "PlayerCardEntryWidget.uheader"
RAW_EXPORTS = RAW_HEADER.with_suffix(".uexp")
EVIDENCE = PROJECT / "RecoveryEvidence"
SAVED_SOURCE = PROJECT / "Saved" / "SourceDecode" / "PlayerCardEntryWidget"
FULL_DECODE = SAVED_SOURCE / "PlayerCardEntryWidget.json"
FUNCTION_DECODE = SAVED_SOURCE / "PlayerCardEntryWidget-functions.json"
FUNCTION_OUTPUT = EVIDENCE / "widget-functions" / "PlayerCardEntryWidget"
LAYOUT_OUTPUT = EVIDENCE / "player-card-entry-widget-layout-values.json"
REPORT_OUTPUT = EVIDENCE / "player-card-entry-widget-recovery.json"


EXPECTED_FUNCTIONS = {
    "BndEvt__PlayerCardEntryWidget_PlayerCardButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature": 3,
    "BndEvt__PlayerCardEntryWidget_PlayerCardButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature": 3,
    "BndEvt__PlayerCardEntryWidget_PlayerCardButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature": 3,
    "ExecuteUbergraph_PlayerCardEntryWidget": 17,
    "GetToolTipWidget": 20,
    "OnClicked__DelegateSignature": 2,
    "PopulatePlayerCard": 49,
}
EXPECTED_ENTRYPOINTS = {
    "Hover": 75,
    "Unhover": 187,
    "Click": 239,
}
SOURCE_ANIMATIONS = ["Hover", "Unhover", "Click", "UnsuccessfulClick"]


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def run_uassetgui(destination: Path, function_only: bool = False) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    command = [str(UASSETGUI), "tojson", str(LEGACY_ASSET), str(destination), "VER_UE5_3"]
    if function_only:
        command.append("FunctionOnly")
    completed = subprocess.run(command, cwd=ANALYSIS, capture_output=True, text=True)
    if completed.returncode != 0 or not destination.is_file():
        raise RuntimeError(
            f"UAssetGUI decode failed ({completed.returncode}): {completed.stdout}\n{completed.stderr}"
        )


def type_name(value: dict) -> str:
    return value.get("$type", "").split(".")[-1].split(",")[0]


def walk(value: object):
    if isinstance(value, dict):
        yield value
        for item in value.values():
            yield from walk(item)
    elif isinstance(value, list):
        for item in value:
            yield from walk(item)


def compact(value: object, asset: dict) -> object:
    if isinstance(value, list):
        return [compact(item, asset) for item in value]
    if not isinstance(value, dict):
        return value
    kind = type_name(value)
    if kind == "KismetPropertyPointer":
        return compact(value.get("New") or value.get("Old"), asset)

    def object_name(index: int) -> str:
        if index == 0:
            return "null"
        pool = asset["Exports"] if index > 0 else asset["Imports"]
        offset = index - 1 if index > 0 else -index - 1
        return pool[offset]["ObjectName"] if 0 <= offset < len(pool) else f"index:{index}"

    if kind == "FFieldPath":
        return {
            "field": ".".join(value["Path"]),
            "owner": object_name(value["ResolvedOwner"]),
        }
    result = {"op": kind}
    for key, item in value.items():
        if key == "$type":
            continue
        if key in {"StackNode", "Object", "ResolvedOwner"} and isinstance(item, int):
            result[key] = object_name(item)
        else:
            result[key] = compact(item, asset)
    return result


def contains_string(value: object, expected: str) -> bool:
    if isinstance(value, str):
        return value == expected
    if isinstance(value, dict):
        return any(contains_string(item, expected) for item in value.values())
    if isinstance(value, list):
        return any(contains_string(item, expected) for item in value)
    return False


def function_entrypoint(statements: list[dict]) -> int:
    for statement in statements:
        if statement.get("op") != "EX_LocalFinalFunction":
            continue
        parameters = statement.get("Parameters", [])
        if len(parameters) == 1 and parameters[0].get("op") == "EX_IntConst":
            return int(parameters[0]["Value"])
    raise RuntimeError("Source delegate wrapper does not enter the player-card event graph")


def decode_layout(full_decode: Path) -> dict:
    dependencies = (
        "decode_defaults.py",
        "blueprint-class-fields.json",
        "native-reflection-schemas.json",
        "ui-reflection-schemas.json",
        "decode_ui_layout.py",
    )
    with tempfile.TemporaryDirectory(prefix="player-card-entry-layout-", dir=PROJECT / "Saved") as temporary:
        root = Path(temporary)
        for name in dependencies:
            shutil.copy2(ANALYSIS / name, root / name)
        copied = root / "decoded-ui" / "PlayerCards" / "PlayerCardEntryWidget.json"
        copied.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(full_decode, copied)
        (root / "UnrealReconstruction" / "RecoveryEvidence").mkdir(parents=True, exist_ok=True)
        completed = subprocess.run(
            [sys.executable, str(root / "decode_ui_layout.py")],
            cwd=root,
            capture_output=True,
            text=True,
        )
        if completed.returncode != 0:
            raise RuntimeError(f"Widget layout decoder failed: {completed.stdout}\n{completed.stderr}")
        decoded = json.loads((root / "ui-layout-values.json").read_text(encoding="utf-8"))
    widgets = [item for item in decoded["widgets"] if item["asset"] == "PlayerCardEntryWidget"]
    failures = [item for item in decoded["failures"] if item["asset"] == "PlayerCardEntryWidget"]
    omitted = [item for item in decoded["omitted_custom_widgets"] if item["asset"] == "PlayerCardEntryWidget"]
    require(not failures, f"PlayerCardEntryWidget layout has decode failures: {failures}")
    require(not omitted, f"PlayerCardEntryWidget layout has omitted custom widgets: {omitted}")
    require(len(widgets) == 26, f"Unexpected PlayerCardEntryWidget component count: {len(widgets)}")
    return {
        "original_game_executed": False,
        "widgets": widgets,
        "failures": failures,
        "imports": {"PlayerCardEntryWidget": decoded["imports"]["PlayerCardEntryWidget"]},
        "omitted_custom_widgets": omitted,
        "original_graphs_restored": False,
        "animations_restored": False,
    }


def property_value(records: dict[str, dict], name: str, field: str) -> object:
    return records[name]["values"][field]


def main() -> None:
    for path in (UASSETGUI, LEGACY_ASSET, LEGACY_EXPORTS, RAW_HEADER, RAW_EXPORTS):
        require(path.is_file(), f"Missing recovered PlayerCardEntryWidget source artifact: {path}")
    run_uassetgui(FULL_DECODE)
    run_uassetgui(FUNCTION_DECODE, function_only=True)

    function_asset = json.loads(FUNCTION_DECODE.read_text(encoding="utf-8"))
    function_exports = [item for item in function_asset["Exports"] if "FunctionExport" in item.get("$type", "")]
    summaries: dict[str, dict] = {}
    compact_statements: dict[str, list[dict]] = {}
    FUNCTION_OUTPUT.mkdir(parents=True, exist_ok=True)
    for export in function_exports:
        name = export["ObjectName"]
        statements = compact(export.get("ScriptBytecode") or [], function_asset)
        nodes = list(walk(statements))
        calls = sorted(
            {
                str(node["StackNode"])
                for node in nodes
                if "StackNode" in node
            }
            | {
                str(node["VirtualFunctionName"])
                for node in nodes
                if "VirtualFunctionName" in node
            }
        )
        fields = sorted(
            {
                str(node["field"])
                for node in nodes
                if node.get("op") == "FFieldPath" and "field" in node
            }
        )
        summary = {
            "name": name,
            "statements": len(statements),
            "raw_fallback": bool(export.get("ScriptBytecodeRaw")),
            "calls": calls,
            "fields": fields,
        }
        summaries[name] = summary
        compact_statements[name] = statements
        safe = re.sub(r"[^A-Za-z0-9_.-]+", "_", name)
        (FUNCTION_OUTPUT / f"{safe}.json").write_text(
            json.dumps({"function": summary, "statements": statements}, indent=2) + "\n",
            encoding="utf-8",
        )

    require(set(summaries) == set(EXPECTED_FUNCTIONS), "PlayerCardEntryWidget function inventory changed")
    require(
        {name: summary["statements"] for name, summary in summaries.items()} == EXPECTED_FUNCTIONS,
        "PlayerCardEntryWidget function sizes changed",
    )
    require(not any(summary["raw_fallback"] for summary in summaries.values()), "PlayerCardEntryWidget bytecode decode fell back to raw")
    entrypoints = {
        "Hover": function_entrypoint(compact_statements[
            "BndEvt__PlayerCardEntryWidget_PlayerCardButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature"
        ]),
        "Unhover": function_entrypoint(compact_statements[
            "BndEvt__PlayerCardEntryWidget_PlayerCardButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature"
        ]),
        "Click": function_entrypoint(compact_statements[
            "BndEvt__PlayerCardEntryWidget_PlayerCardButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature"
        ]),
    }
    require(entrypoints == EXPECTED_ENTRYPOINTS, "PlayerCardEntryWidget source event entrypoints changed")
    execute = summaries["ExecuteUbergraph_PlayerCardEntryWidget"]
    for call in ("PlayAnimation", "PlaySound2D", "OnClicked__DelegateSignature"):
        require(call in execute["calls"], f"Source player-card interaction no longer calls {call}")
    tooltip_statements = compact_statements["GetToolTipWidget"]
    for literal in ("Unlocked", "{card name} - locked", "card name"):
        require(contains_string(tooltip_statements, literal), f"Source player-card tooltip lost {literal!r}")
    population_statements = compact_statements["PopulatePlayerCard"]
    require(contains_string(population_statements, "Complete Challenge: \r\n\"{challenge}\""), "Source requirement literal changed")

    layout = decode_layout(FULL_DECODE)
    LAYOUT_OUTPUT.write_text(json.dumps(layout, indent=2) + "\n", encoding="utf-8")
    records = {item["name"]: item for item in layout["widgets"]}
    required_components = {
        "SizeBox_60",
        "Border_0",
        "PlayerCardButton",
        "LockOverlay",
        "Border_122",
        "ScaleBox_1",
        "SizeBox_1",
        "HorizontalBox_76",
        "SizeBox_0",
        "ScaleBox_0",
        "UnlockRequirementText",
        "Image_257",
        "Image_86",
        "WidgetTree",
    }
    require(required_components <= set(records), "PlayerCardEntryWidget layout lost a required component")
    require(property_value(records, "SizeBox_60", "WidthOverride") == 613.0, "Source card width changed")
    require(property_value(records, "SizeBox_60", "HeightOverride") == 136.0, "Source card height changed")
    require(property_value(records, "SizeBox_1", "WidthOverride") == 600.0, "Source lock overlay width changed")
    require(property_value(records, "SizeBox_0", "WidthOverride") == 586.0, "Source requirement width changed")
    require(property_value(records, "Border_122", "BrushColor")["A"] == 0.5, "Source lock opacity changed")
    require(property_value(records, "UnlockRequirementText", "Font")["Size"] == 16.5, "Source requirement font size changed")
    require(property_value(records, "UnlockRequirementText", "Justification") == 1, "Source requirement alignment changed")
    for image_name in ("Image_257", "Image_86"):
        image = records[image_name]["values"]
        require(image["Brush"]["ResourceObject"]["name"] == "LockedPlayerCard", f"{image_name} lock artwork changed")
        require(image["RenderTransform"]["Scale"] == {"X": 1.5, "Y": 1.5}, f"{image_name} scale changed")

    source_paths = [
        RAW_HEADER,
        RAW_EXPORTS,
        LEGACY_ASSET,
        LEGACY_EXPORTS,
        FULL_DECODE,
        FUNCTION_DECODE,
    ]
    reconstruction_paths = [
        PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardEntryWidget.h",
        PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardEntryWidget.cpp",
        PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardsTabWidget.cpp",
        PROJECT / "Source" / "CockHeroRecovered" / "RecoveredWidgetRecovery.cpp",
        PROJECT / "Scripts" / "recover_player_card_entry_widget.py",
        PROJECT / "Scripts" / "build_player_card_entry_widget.py",
        PROJECT / "Scripts" / "import_player_card_textures.py",
        LAYOUT_OUTPUT,
    ]
    for path in reconstruction_paths:
        require(path.is_file(), f"Missing entry-widget reconstruction artifact: {path}")

    report = {
        "recovery": "player-card-entry-widget",
        "source_executed": False,
        "source_asset": "/Game/PlayerCards/PlayerCardEntryWidget",
        "source_package": {
            "raw_uheader_sha256": sha256(RAW_HEADER),
            "raw_uexp_sha256": sha256(RAW_EXPORTS),
            "legacy_uasset_sha256": sha256(LEGACY_ASSET),
            "legacy_uexp_sha256": sha256(LEGACY_EXPORTS),
        },
        "functions": [summaries[name] for name in sorted(summaries)],
        "source_entrypoints": entrypoints,
        "source_contract": {
            "button_style": {
                "draw_as": "Image",
                "image_size": [32.0, 32.0],
                "normal_hovered_pressed_share_card_art": True,
                "source_button_slate_sounds_cleared_on_population": True,
            },
            "lock_overlay": {
                "unlocked_visibility": "Collapsed",
                "locked_visibility": "Visible",
                "opacity": 0.5,
                "locked_artwork": "LockedPlayerCard",
                "lock_scale": [1.5, 1.5],
                "requirement_format": "Complete Challenge: \\r\\n\\\"{challenge}\\\"",
                "challenge_identifier_replaces_underscores": True,
            },
            "tooltip": {
                "unlocked_title": "Card Name",
                "unlocked_description": "Unlocked",
                "locked_title": "{card name} - locked",
                "locked_description_format": "ChallengeDescription with {card name}",
            },
            "interaction": {
                "hover": {"animation": "Hover", "sound": "click4_sfx", "volume": 1.0, "pitch": 1.0},
                "unhover": {"animation": "Unhover"},
                "unlocked_click": {"animation": "Click", "sound": "Juice_SFX__12_", "volume": 2.0, "pitch": 1.3},
                "locked_click": {"animation": "UnsuccessfulClick", "sound": "anime-46068", "volume": 0.8, "pitch": 0.9},
                "click_broadcasts_before_unlock_branch": True,
            },
        },
        "layout": {
            "components": len(layout["widgets"]),
            "root": "SizeBox_60",
            "root_size": [613.0, 136.0],
            "lock_content_width": 600.0,
            "requirement_content_width": 586.0,
            "requirement_font_size": 16.5,
            "required_components": sorted(required_components),
            "byte_identical_component_payloads": all(item["byte_identical_roundtrip"] for item in layout["widgets"]),
        },
        "animation_source": {
            "names": SOURCE_ANIMATIONS,
            "count": len(SOURCE_ANIMATIONS),
            "source_animation_payloads_decoded": False,
        },
        "reconstruction": {
            "asset": "/Game/Recovery/UI/PlayerCardEntryWidget.PlayerCardEntryWidget",
            "widget_tree_restored": False,
            "animations_restored": False,
        },
        "source_sha256": {str(path): sha256(path) for path in source_paths},
        "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
    }
    REPORT_OUTPUT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({
        "functions": len(summaries),
        "layout_components": len(layout["widgets"]),
        "report": str(REPORT_OUTPUT),
        "layout": str(LAYOUT_OUTPUT),
    }, indent=2))


if __name__ == "__main__":
    main()
