from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
EVIDENCE = PROJECT / "RecoveryEvidence"
FUNCTIONS = EVIDENCE / "widget-functions" / "PlayerCardsTabWidget"
TEXTURE_REPORT = EVIDENCE / "player-card-texture-recovery.json"
ENTRY_WIDGET_REPORT = EVIDENCE / "player-card-entry-widget-recovery.json"
ENTRY_WIDGET_LAYOUT = EVIDENCE / "player-card-entry-widget-layout-values.json"
RAW_ENTRY_WIDGET = ANALYSIS / "player-cards-extract" / "CockHero" / "Content" / "PlayerCards" / "PlayerCardEntryWidget.uheader"
RAW_ENTRY_WIDGET_EXPORTS = RAW_ENTRY_WIDGET.with_suffix(".uexp")
LEGACY_ENTRY_WIDGET = ANALYSIS / "player-cards-legacy-v2" / "CockHero" / "Content" / "PlayerCards" / "PlayerCardEntryWidget.uasset"
LEGACY_ENTRY_WIDGET_EXPORTS = LEGACY_ENTRY_WIDGET.with_suffix(".uexp")


def load_json(path: Path) -> dict:
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def entrypoint(path: Path) -> int:
    statements = load_json(path)["statements"]
    statement = next((item for item in statements if item["op"] == "EX_LocalFinalFunction"), None)
    require(statement is not None, f"{path.name} does not enter the source graph")
    values = statement.get("Parameters", [])
    require(len(values) == 1 and values[0]["op"] == "EX_IntConst", f"{path.name} entrypoint encoding changed")
    return values[0]["Value"]


def contains_string(value: object, expected: str) -> bool:
    if isinstance(value, str):
        return value == expected
    if isinstance(value, dict):
        return any(contains_string(item, expected) for item in value.values())
    if isinstance(value, list):
        return any(contains_string(item, expected) for item in value)
    return False


entrypoint_paths = {
    "Construct": FUNCTIONS / "Construct.json",
    "PopulatePlayerCards": FUNCTIONS / "PopulatePlayerCards.json",
    "PlayerCardClick": FUNCTIONS / "PlayerCardClick.json",
    "ChangeSelectedPlayerCardDisplay": FUNCTIONS / "ChangeSelectedPlayerCardDisplay.json",
    "UpdateLevelDisplay": FUNCTIONS / "UpdateLevelDisplay.json",
    "EditPlayerCardButton": FUNCTIONS / "BndEvt__PlayerCardsTabWidget_EditPlayerCardButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json",
    "OnEditBoxClosed": FUNCTIONS / "OnEditBoxClosed.json",
}
entrypoints = {name: entrypoint(path) for name, path in entrypoint_paths.items()}
expected_entrypoints = {
    "Construct": 1705,
    "PopulatePlayerCards": 2306,
    "PlayerCardClick": 2436,
    "ChangeSelectedPlayerCardDisplay": 2654,
    "UpdateLevelDisplay": 2863,
    "EditPlayerCardButton": 3799,
    "OnEditBoxClosed": 3804,
}
require(entrypoints == expected_entrypoints, "PlayerCardsTabWidget entrypoint contract changed")

graph = load_json(FUNCTIONS / "ExecuteUbergraph_PlayerCardsTabWidget.json")
expected_calls = [
    "ClearChildren",
    "GetAllPlayerCardData",
    "UnlockPlayerCard",
    "GetChallengeData",
    "PopulatePlayerCard",
    "AddChildToUniformGrid",
    "GetUnlockedPlayerCards",
    "EquipPlayerCard",
    "IsPlayerCardUnlocked",
    "GetEquippedPlayerCard",
    "GetPlayerCardData",
    "SetBrushFromTexture",
    "GetCurrentPlayerTitle",
    "GetLevelProgressPercent",
    "SetPercent",
    "SetText",
    "PlayAnimation",
    "AddToViewport",
]
for call in expected_calls:
    require(call in graph["function"]["calls"], f"PlayerCardsTabWidget source graph no longer calls {call}")
for field in [
    "CardID",
    "CardImage",
    "CardName",
    "RequiredChallengeID",
    "RequiredLevel",
    "PlayerCardUniformGrid",
    "SelectedPlayerCard",
    "TitleLevelText",
    "LevelMeter",
    "PlayerCardName",
    "Playercard_Name",
    "UpdateEquippedCard",
]:
    require(field in graph["function"]["fields"], f"PlayerCardsTabWidget source graph no longer exposes {field}")
require(contains_string(graph, "none"), "PlayerCardsTabWidget source no-gate sentinel changed")
require(contains_string(graph, "Level: {level} - {title}"), "PlayerCardsTabWidget source level format changed")

rules = load_json(EVIDENCE / "game-rules-draft.json")
cards = rules["progression"]["DT_PlayerCards"]
require(len(cards) == 36, "Player-card source table count changed")
free_cards = [card for card in cards if not card["RequiredChallengeID"]]
require([card["CardID"] for card in free_cards] == ["cybergirls_pc_2"], "Player-card no-gate source rows changed")
require(cards[0]["CardID"] == "catgirl_booties_pc_1", "Player-card source first row changed")
require(cards[3]["CardID"] == "hypnoboobs_pc_1", "Player-card source fourth row changed")

texture_report = load_json(TEXTURE_REPORT)
require(texture_report["expected_card_images"] == 36, "Player-card texture source count changed")
require(texture_report["exported_images"] == 37, "Player-card texture export is incomplete")
textures = texture_report["textures"]
require(len(textures) == 37, "Player-card texture evidence row count changed")
require(all(row.get("decoded") for row in textures), "Player-card texture decode evidence is incomplete")
require(all(row.get("recovered_asset") for row in textures), "Player-card texture import evidence is incomplete")
require(len({row["recovered_asset"] for row in textures}) == 37, "Player-card recovered texture names are not unique")
require({row["original"] for row in textures} == {card["CardImage"] for card in cards} | {"/Game/PlayerCards/LockedPlayerCard.LockedPlayerCard"}, "Player-card texture source set changed")
for path in (RAW_ENTRY_WIDGET, RAW_ENTRY_WIDGET_EXPORTS, LEGACY_ENTRY_WIDGET, LEGACY_ENTRY_WIDGET_EXPORTS, ENTRY_WIDGET_REPORT, ENTRY_WIDGET_LAYOUT):
    require(path.exists(), f"Missing recovered source PlayerCardEntryWidget component: {path}")

entry_recovery = load_json(ENTRY_WIDGET_REPORT)
require(entry_recovery["source_asset"] == "/Game/PlayerCards/PlayerCardEntryWidget", "PlayerCardEntryWidget source asset changed")
require(entry_recovery["source_entrypoints"] == {"Hover": 75, "Unhover": 187, "Click": 239}, "PlayerCardEntryWidget source event entrypoints changed")
require(len(entry_recovery["functions"]) == 7, "PlayerCardEntryWidget function recovery is incomplete")
require(not any(function["raw_fallback"] for function in entry_recovery["functions"]), "PlayerCardEntryWidget function recovery fell back to raw bytecode")
require(entry_recovery["layout"]["components"] == 26, "PlayerCardEntryWidget layout recovery is incomplete")
require(entry_recovery["layout"]["byte_identical_component_payloads"], "PlayerCardEntryWidget layout payloads are not byte verified")
require(entry_recovery["reconstruction"]["widget_tree_restored"], "PlayerCardEntryWidget tree was not restored")
require(entry_recovery["reconstruction"]["animations_restored"], "PlayerCardEntryWidget animations were not restored")
require(entry_recovery["reconstruction"]["animation_restore"]["animation_count"] == 4, "PlayerCardEntryWidget animation recovery is incomplete")

source_paths = [
    *entrypoint_paths.values(),
    FUNCTIONS / "ExecuteUbergraph_PlayerCardsTabWidget.json",
    FUNCTIONS / "PopulateDetailsPanel.json",
    EVIDENCE / "game-rules-draft.json",
    ANALYSIS / "ghidra-native" / "integration-decompiled.c",
    TEXTURE_REPORT,
    RAW_ENTRY_WIDGET,
    RAW_ENTRY_WIDGET_EXPORTS,
    LEGACY_ENTRY_WIDGET,
    LEGACY_ENTRY_WIDGET_EXPORTS,
    ENTRY_WIDGET_REPORT,
    ENTRY_WIDGET_LAYOUT,
]
reconstruction_paths = [
    PROJECT / "Content" / "Recovery" / "UI" / "PlayerCardsTabWidget.uasset",
    PROJECT / "Content" / "Recovery" / "UI" / "PlayerCardEntryWidget.uasset",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardsTabWidget.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardsTabWidget.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardEntryWidget.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardEntryWidget.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredProgression.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredRewards.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredChallengesMenu.cpp",
    PROJECT / "Scripts" / "reparent_player_cards_tab.py",
    PROJECT / "Scripts" / "export_player_card_textures.py",
    PROJECT / "Scripts" / "decode_player_card_textures.py",
    PROJECT / "Scripts" / "import_player_card_textures.py",
    PROJECT / "Scripts" / "recover_player_card_entry_widget.py",
    PROJECT / "Scripts" / "build_player_card_entry_widget.py",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredWidgetRecovery.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardsTabWidgetTests.cpp",
]
for path in reconstruction_paths:
    require(path.exists(), f"Missing reconstructed player-card artifact: {path}")

report = {
    "recovery": "player-cards-tab-widget",
    "source_executed": False,
    "source_entrypoints": entrypoints,
    "source_graph_calls": expected_calls,
    "source_ui_fields": [
        "EditPlayerCardButton",
        "LevelMeter",
        "PlayerCardName",
        "PlayerCardScrollbox",
        "PlayerCardUniformGrid",
        "SelectedPlayerCard",
        "TitleLevelText",
    ],
    "population_contract": {
        "source_card_count": len(cards),
        "columns": 3,
        "slot_padding": 8,
        "free_card_ids": [card["CardID"] for card in free_cards],
        "locked_card_clicks_do_not_equip": True,
        "equipped_card_refreshes_selected_brush": True,
    },
    "entry_widget": {
        "source_asset": "/Game/PlayerCards/PlayerCardEntryWidget",
        "reconstruction": "URecoveredPlayerCardEntryWidget",
        "source_asset_recovered": True,
        "raw_uheader_sha256": sha256(RAW_ENTRY_WIDGET),
        "raw_uexp_sha256": sha256(RAW_ENTRY_WIDGET_EXPORTS),
        "legacy_uasset_sha256": sha256(LEGACY_ENTRY_WIDGET),
        "legacy_uexp_sha256": sha256(LEGACY_ENTRY_WIDGET_EXPORTS),
        "source_layout_recovered": entry_recovery["layout"]["components"] == 26,
        "source_animation_payloads_restored": entry_recovery["reconstruction"]["animations_restored"],
        "runtime_asset": entry_recovery["reconstruction"]["asset"],
        "runtime_animation_count": entry_recovery["reconstruction"]["animation_restore"]["animation_count"],
    },
    "texture_recovery": {
        "source_card_images": texture_report["expected_card_images"],
        "recovered_texture_assets": texture_report["exported_images"],
        "locked_placeholder_recovered": True,
        "all_source_card_art_imported": True,
    },
    "source_sha256": {str(path): sha256(path) for path in source_paths},
    "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
}

output = EVIDENCE / "player-cards-tab-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
