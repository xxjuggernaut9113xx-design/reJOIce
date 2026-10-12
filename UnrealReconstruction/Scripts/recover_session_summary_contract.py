"""Record and verify the recovered WBP_SessionSummaryWidget contract."""

import hashlib
import json
import os
import struct
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
WIDGET_DIR = EVIDENCE / "blueprint-functions" / "WBP_SessionSummaryWidget"
MASTER_GRAPH = EVIDENCE / "blueprint-functions" / "WBP_PostGameFlow_Master" / "ExecuteUbergraph_WBP_PostGameFlow_Master.json"
CLASS_DEFAULTS = EVIDENCE / "widget-class-defaults.json"
ALIAS_FILE = EVIDENCE / "resource-aliases.json"
IMPORT_REPORT = EVIDENCE / "session-summary-audio-import-recovery.json"
DECODE_REPORT = EVIDENCE / "session-summary-audio-decoding-report.json"
STREAM_REPORT = EVIDENCE / "session-summary-audio-stream-catalog.json"
OUTPUT = EVIDENCE / "session-summary-contract-recovery.json"
ORIGINAL_EXE = Path(os.environ.get(
    "COCKHERO_ORIGINAL_EXE",
    r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero\Binaries\Win64\CockHero.exe",
))
GHIDRA_DECOMPILED = Path(os.environ.get(
    "COCKHERO_GHIDRA_DECOMPILED",
    r"C:\Users\webma\analysis\cockhero-v004\ghidra\integration-decompiled.c",
))

VOICE_PROPERTY_MAP = {
    "Villainess Post Game Victory Lines": "VillainessPostGameVictoryLines",
    "Villainess Post Game Defeat Lines": "VillainessPostGameDefeatLines",
    "Brat Post Game Victory Lines": "BratPostGameVictoryLines",
    "Brat Post Game Defeat Lines": "BratPostGameDefeatLines",
    "Dommy Mommy Post Game Victory Lines": "DommyMommyPostGameVictoryLines",
    "Dommy Mommy Post Game Defeat Lines": "DommyMommyPostGameDefeatLines",
    "Sweetheart Post Game Victory Lines": "SweetheartPostGameVictoryLines",
    "Sweetheart Post Game Defeat Lines": "SweetheartPostGameDefeatLines",
}
EXPECTED_VOICE_COUNTS = {
    "VillainessPostGameVictoryLines": 8,
    "VillainessPostGameDefeatLines": 8,
    "BratPostGameVictoryLines": 7,
    "BratPostGameDefeatLines": 8,
    "DommyMommyPostGameVictoryLines": 10,
    "DommyMommyPostGameDefeatLines": 10,
    "SweetheartPostGameVictoryLines": 10,
    "SweetheartPostGameDefeatLines": 9,
}
EXPECTED_ANIMATIONS = [
    "BeginDisplay",
    "PatreonHover",
    "PatreonUnhover",
    "PatreonClick",
    "DiscordHover",
    "DiscordUnhover",
    "DiscordClick",
    "TwitterHover",
    "TwitterUnhover",
    "TwitterClick",
]
EXPECTED_SOCIAL_URLS = {
    "Patreon": "https://www.patreon.com/CockHeroGame",
    "Discord": "https://discord.gg/dQXRpF6Uhf",
    "Twitter": "https://x.com/CockHeroGame",
}
EXPECTED_DETAIL_FORMATS = {
    "succubi_defeated": "SUCCUBI DEFEATED: %d\n",
    "enemies_defeated": "ENEMIES DEFEATED: %d\n",
    "times_taunted": "TIMES TAUNTED: %d\n",
    "time_at_high_heat": "TIME AT HIGH HEAT: %d:%02d\n",
    "draws_at_max_heat": "DRAWS AT MAX HEAT: %d\n",
    "items_used": "ITEMS USED: %d\n",
    "perfect_edges": "PERFECT EDGES: %d\n",
    "best_edge_streak": "BEST EDGE STREAK: %d",
}
DETAIL_STRING_ADDRESSES = {
    "succubi_defeated": 0x14CF76DC8,
    "enemies_defeated": 0x14CF76DF8,
    "times_taunted": 0x14CF76E28,
    "time_at_high_heat": 0x14CF76E50,
    "draws_at_max_heat": 0x14CF76E88,
    "items_used": 0x14CF76EB8,
    "perfect_edges": 0x14CF76ED8,
    "best_edge_streak": 0x14CF76F00,
}


def load(path: Path):
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path):
    digest = hashlib.sha256()
    with path.open("rb") as source:
        for chunk in iter(lambda: source.read(1 << 20), b""):
            digest.update(chunk)
    return digest.hexdigest()


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


def first_entrypoint(graph):
    values = [node["Value"] for node in walk(graph["statements"]) if node.get("op") == "EX_IntConst"]
    if len(values) != 1:
        raise RuntimeError(f"Expected one entrypoint in {graph['function']['name']}, got {values}")
    return values[0]


def string_constants(graph):
    return [node["Value"] for node in walk(graph["statements"]) if node.get("op") == "EX_StringConst"]


def slate_colors(graph):
    colors = {}
    for node in walk(graph["statements"]):
        if node.get("op") != "EX_Let":
            continue
        member = node.get("Variable", {}).get("StructMemberExpression", {}).get("field")
        variable = node.get("Variable", {}).get("StructExpression", {}).get("Variable", {}).get("field")
        expression = node.get("Expression", {})
        if member != "SpecifiedColor" or not variable or expression.get("op") != "EX_StructConst":
            continue
        colors[variable] = [float(value["Value"]) for value in expression["Value"]]
    return colors


def pe_image_base_and_sections(data):
    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise RuntimeError("Original executable does not have a PE signature")
    section_count = struct.unpack_from("<H", data, pe_offset + 6)[0]
    optional_size = struct.unpack_from("<H", data, pe_offset + 20)[0]
    optional_offset = pe_offset + 24
    if struct.unpack_from("<H", data, optional_offset)[0] != 0x20B:
        raise RuntimeError("Original executable is not PE32+")
    image_base = struct.unpack_from("<Q", data, optional_offset + 24)[0]
    section_offset = optional_offset + optional_size
    sections = []
    for index in range(section_count):
        offset = section_offset + index * 40
        name = data[offset:offset + 8].rstrip(b"\0").decode("ascii", errors="replace")
        virtual_size, virtual_address, raw_size, raw_offset = struct.unpack_from("<IIII", data, offset + 8)
        sections.append((name, virtual_address, virtual_size, raw_offset, raw_size))
    return image_base, sections


def original_wide_strings():
    if not ORIGINAL_EXE.is_file():
        raise RuntimeError(f"Original executable is missing: {ORIGINAL_EXE}")
    data = ORIGINAL_EXE.read_bytes()
    image_base, sections = pe_image_base_and_sections(data)

    def offset_for(address):
        rva = address - image_base
        for _, virtual_address, virtual_size, raw_offset, raw_size in sections:
            if virtual_address <= rva < virtual_address + max(virtual_size, raw_size):
                return raw_offset + rva - virtual_address
        raise RuntimeError(f"Cannot map original executable address 0x{address:x}")

    values = {}
    for name, address in DETAIL_STRING_ADDRESSES.items():
        offset = offset_for(address)
        end = offset
        while data[end:end + 2] != b"\0\0":
            end += 2
        values[name] = data[offset:end].decode("utf-16le")
    integer_format_address = 0x14BCF1B74
    offset = offset_for(integer_format_address)
    end = offset
    while data[end:end + 2] != b"\0\0":
        end += 2
    values["integer"] = data[offset:end].decode("utf-16le")
    return image_base, values


def decompiled_function_body(source, address):
    marker = f"/* {address:x} "
    start = source.find(marker)
    if start < 0:
        raise RuntimeError(f"Ghidra function marker missing: {marker}")
    end = source.find("\n/* ", start + len(marker))
    return source[start:] if end < 0 else source[start:end]


def main():
    construct = load(WIDGET_DIR / "Construct.json")
    initialize = load(WIDGET_DIR / "Initialize.json")
    voicelines = load(WIDGET_DIR / "PlayPostGameVoicelines.json")
    ubergraph = load(WIDGET_DIR / "ExecuteUbergraph_WBP_SessionSummaryWidget.json")
    return_handler = load(WIDGET_DIR / "BndEvt__WBP_SessionSummaryWidget_ReturnToMenu_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json")
    master = load(MASTER_GRAPH)
    defaults = load(CLASS_DEFAULTS)
    aliases = load(ALIAS_FILE)
    imported = load(IMPORT_REPORT)
    decoded = load(DECODE_REPORT)
    catalog = load(STREAM_REPORT)
    source_class = next(item for item in defaults["classes"] if item["class"] == "WBP_SessionSummaryWidget_C")
    source_default = next(item for item in defaults["defaults"] if item["class"] == "WBP_SessionSummaryWidget_C")

    source_animations = [entry["name"].removesuffix("_INST") for entry in source_class["metadata"]["Animations"]]
    source_voice_arrays = {
        native_name: [entry["name"] for entry in source_default["values"][source_name]]
        for source_name, native_name in VOICE_PROPERTY_MAP.items()
    }
    source_properties = {property_["name"] for property_ in source_class["properties"]}
    handler_files = sorted(WIDGET_DIR.glob("BndEvt*.json"))
    handler_entrypoints = {path.stem: first_entrypoint(load(path)) for path in handler_files}
    source_urls = [value for value in string_constants(ubergraph) if value.startswith("https://")]
    colors = slate_colors(initialize)
    image_base, original_formats = original_wide_strings()
    if not GHIDRA_DECOMPILED.is_file():
        raise RuntimeError(f"Ghidra output is missing: {GHIDRA_DECOMPILED}")
    decompiled = GHIDRA_DECOMPILED.read_text(encoding="utf-8", errors="replace")
    detailed_body = decompiled_function_body(decompiled, 0x1481BFC20)
    duration_body = decompiled_function_body(decompiled, 0x1481BFED0)
    edges_body = decompiled_function_body(decompiled, 0x1481BFF20)
    combo_body = decompiled_function_body(decompiled, 0x1481BBAF0)
    strokes_body = decompiled_function_body(decompiled, 0x1481C2FD0)

    source_text_targets = []
    for statement in initialize["statements"]:
        if statement.get("op") != "EX_Context":
            continue
        context = statement.get("ContextExpression", {})
        if context.get("VirtualFunctionName") == "SetText":
            source_text_targets.append(statement["ObjectExpression"]["Variable"]["field"])
    master_summary_calls = []
    for statement in master["statements"]:
        if statement.get("op") != "EX_Context":
            continue
        target = statement.get("ObjectExpression", {}).get("Variable", {}).get("field")
        method = statement.get("ContextExpression", {}).get("VirtualFunctionName")
        if target == "WBP_SessionSummaryWidget" and method:
            master_summary_calls.append(method)

    implementation = (PROJECT / "Source" / "CockHeroRecovered" / "RecoveredSessionSummaryWidget.cpp").read_text(encoding="utf-8")
    progression = (PROJECT / "Source" / "CockHeroRecovered" / "RecoveredProgression.cpp").read_text(encoding="utf-8")
    audio_names = {entry["name"] for entry in catalog["sounds"]}
    imported_names = {entry["name"] for entry in imported["sounds"]}
    decoded_names = {entry["name"] for entry in decoded["sounds"]}

    report = {
        "recovery": "session-summary-widget-contract",
        "source_executed": False,
        "source": {
            "widget_asset": "/Game/UI/PostGameFlow/WBP_SessionSummaryWidget",
            "widget_graphs": [str(path.relative_to(PROJECT)) for path in sorted(WIDGET_DIR.glob("*.json"))],
            "master_graph": str(MASTER_GRAPH.relative_to(PROJECT)),
            "class_defaults": str(CLASS_DEFAULTS.relative_to(PROJECT)),
            "original_executable": str(ORIGINAL_EXE),
            "original_executable_sha256": sha256(ORIGINAL_EXE),
            "ghidra_decompiled": str(GHIDRA_DECOMPILED),
            "ghidra_decompiled_sha256": sha256(GHIDRA_DECOMPILED),
        },
        "entrypoints": {
            "construct": first_entrypoint(construct),
            "return_to_menu": first_entrypoint(return_handler),
            "social_handlers": handler_entrypoints,
        },
        "presentation_contract": {
            "source_calls": initialize["function"]["calls"],
            "text_targets": source_text_targets,
            "labels": ["Victory", "Defeat (-50% Rewards)"],
            "colors": {
                "victory": colors["K2Node_MakeStruct_SlateColor_1"],
                "defeat": colors["K2Node_MakeStruct_SlateColor"],
            },
            "native_formatter": {
                "image_base": f"0x{image_base:x}",
                "functions": {
                    "GetDetailedStatsText": "0x1481bfc20",
                    "GetDurationText": "0x1481bfed0",
                    "GetEdgesText": "0x1481bff20",
                    "GetComboText": "0x1481bbaf0",
                    "GetStrokesText": "0x1481c2fd0",
                },
                "formats": original_formats,
                "detailed_stat_offsets": {
                    "succubi_defeated": "0x08",
                    "enemies_defeated": ["0x0c", "0x08"],
                    "times_taunted": "0x18",
                    "time_at_high_heat": "0x58",
                    "draws_at_max_heat": "0x20",
                    "items_used": "0x1c",
                    "perfect_edges": "0x6c",
                    "best_edge_streak": "0x50",
                },
                "duration_seconds_offset": "0x28",
                "integer_format": original_formats["integer"],
            },
        },
        "interaction_contract": {
            "animations": source_animations,
            "social_urls": source_urls,
            "return_sequence_calls": [name for name in ubergraph["function"]["calls"] if name in {"Create", "PauseSequence", "ReinitGameVariables", "RemoveFromParent"}],
            "master_summary_calls": master_summary_calls,
        },
        "voice_contract": {
            "source_arrays": source_voice_arrays,
            "source_counts": {name: len(values) for name, values in source_voice_arrays.items()},
            "source_calls": voicelines["function"]["calls"],
            "play_sound_2d_persistent": any(
                node.get("op") == "EX_FinalFunction"
                and node.get("StackNode") == "PlaySound2D"
                and node.get("Parameters", [])[-1].get("op") == "EX_True"
                for node in walk(voicelines["statements"])
            ),
            "stream_report": str(STREAM_REPORT.relative_to(PROJECT)),
            "decode_report": str(DECODE_REPORT.relative_to(PROJECT)),
            "import_report": str(IMPORT_REPORT.relative_to(PROJECT)),
            "imported_asset_count": len(imported["sounds"]),
        },
        "recovery_artifacts": {
            "widget": "Content/Recovery/UI/WBP_SessionSummaryWidget.uasset",
            "native_parent": imported["native_parent"],
            "native_widget": "Source/CockHeroRecovered/RecoveredSessionSummaryWidget.cpp",
            "native_formatter": "Source/CockHeroRecovered/RecoveredProgression.cpp",
            "automation_test": "Source/CockHeroRecovered/RecoveredSessionSummaryWidgetTests.cpp",
            "audio_assets": "Content/Recovery/Resources/PostGameVoicelines",
            "encoded_audio": "RecoveryEvidence/AudioEncoded/PostGame",
            "decoded_audio": "RecoveryEvidence/AudioSource",
        },
    }
    verification = {
        "source_defaults_are_static_artifacts": defaults["original_executed"] is False,
        "source_default_roundtrip_is_exact": source_default["byte_identical_roundtrip"] is True,
        "construct_routes_to_source_entrypoint": report["entrypoints"]["construct"] == 807,
        "return_click_routes_to_source_entrypoint": report["entrypoints"]["return_to_menu"] == 1372,
        "all_ten_delegate_handlers_recovered": len(handler_files) == 10,
        "source_animations_exact": source_animations == EXPECTED_ANIMATIONS,
        "source_widget_bindings_present": {
            "DetailedStatsString", "DiscordInvButton", "DurationText", "EdgeAmountText", "HighestComboText", "PatreonButton", "ReturnToMenu", "RewardsString", "TotalStrokesText", "TwitterButton", "VictoryText", "WBP_PlayerCard", "WBP_XPBar"
        }.issubset(source_properties),
        "source_initializer_calls_exact": set(["GetDetailedStatsText", "GetRewardsText", "GetDurationText", "GetEdgesText", "GetComboText", "GetStrokesText", "GetXPForNextLevel", "InitializeBar", "SetColorAndOpacity", "SetText"]).issubset(initialize["function"]["calls"]),
        "source_text_targets_exact": set(source_text_targets) == {"DetailedStatsString", "RewardsString", "DurationText", "EdgeAmountText", "HighestComboText", "TotalStrokesText", "VictoryText"},
        "source_labels_exact": all(label in string_constants(initialize) for label in report["presentation_contract"]["labels"]),
        "source_colors_exact": report["presentation_contract"]["colors"] == {
            "victory": [0.0, 0.5209959745407104, 0.12477199733257294, 1.0],
            "defeat": [0.838798999786377, 0.0, 0.0006070000235922635, 1.0],
        },
        "native_detail_format_strings_exact": {name: original_formats[name] for name in EXPECTED_DETAIL_FORMATS} == EXPECTED_DETAIL_FORMATS,
        "native_integer_text_is_unprefixed": original_formats["integer"] == "%d",
        "native_detailed_formatter_offsets_verified": all(fragment in detailed_body for fragment in [
            "param_3 + 8", "param_3 + 0xc", "param_3 + 0x18", "param_3 + 0x58", "param_3 + 0x20", "param_3 + 0x1c", "param_3 + 0x6c", "param_3 + 0x50",
        ]),
        "native_duration_formatter_offset_verified": "param_3 + 0x28" in duration_body,
        "native_number_formatters_verified": all("UNK_14bcf1b74" in body for body in [edges_body, combo_body, strokes_body]),
        "source_social_urls_exact": set(source_urls) == set(EXPECTED_SOCIAL_URLS.values()),
        "return_sequence_is_complete": {"Create", "PauseSequence", "ReinitGameVariables", "RemoveFromParent"}.issubset(ubergraph["function"]["calls"]),
        "master_invokes_summary_initialize_and_voice": master_summary_calls == ["Initialize", "PlayPostGameVoicelines"],
        "source_voice_arrays_exact": {name: len(values) for name, values in source_voice_arrays.items()} == EXPECTED_VOICE_COUNTS,
        "source_voice_routing_calls_exact": {"Array_Random", "PlaySound2D"}.issubset(voicelines["function"]["calls"]),
        "source_voice_playback_persists": report["voice_contract"]["play_sound_2d_persistent"],
        "catalog_and_decode_arrays_agree": catalog["voice_arrays"] == decoded["voice_arrays"] == EXPECTED_VOICE_COUNTS,
        "all_seventy_voice_streams_decoded": len(audio_names) == len(decoded_names) == 70 and audio_names == decoded_names and all(
            item["decoded"]["success"] and item["sample_rate"] == 44100 and item["channels"] == 2 and item["frames"] > 0
            for item in decoded["sounds"]
        ),
        "all_seventy_voice_assets_imported": len(imported_names) == 70 and imported_names == audio_names and all(
            item["sample_rate"] == 44100 and item["channels"] == 2 and item["frames"] > 0
            for item in imported["sounds"]
        ),
        "voice_array_assignments_exact": {name: len(values) for name, values in imported["voice_arrays"].items()} == EXPECTED_VOICE_COUNTS,
        "voice_aliases_complete": all(aliases.get(item["original"]) == item["asset"] for item in imported["sounds"]),
        "voice_artifact_files_complete": all(
            (EVIDENCE / "AudioEncoded" / "PostGame" / f"{name}.binka").is_file()
            and (EVIDENCE / "AudioSource" / f"{name}.wav").is_file()
            and (PROJECT / "Content" / "Recovery" / "Resources" / "PostGameVoicelines" / f"{name}.uasset").is_file()
            for name in audio_names
        ),
        "native_summary_uses_source_formatters": all(token in implementation for token in [
            "GetDetailedStatsText", "GetDurationText", "GetEdgesText", "GetComboText", "GetStrokesText", "GetRecoveredSummarySocialURL", "PlayPostGameVoicelines",
        ]),
        "native_formatter_uses_original_literals": all(value.replace("\n", "\\n") in progression for value in EXPECTED_DETAIL_FORMATS.values()) and "FString::FromInt" in progression,
    }
    verification["all_verified"] = all(verification.values())
    report["verification"] = verification
    if not verification["all_verified"]:
        raise RuntimeError(json.dumps(verification, indent=2))
    OUTPUT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"report": str(OUTPUT), "verified": verification}, indent=2))


if __name__ == "__main__":
    main()
