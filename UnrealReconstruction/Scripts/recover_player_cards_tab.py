from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
EVIDENCE = PROJECT / "RecoveryEvidence"
FUNCTIONS = EVIDENCE / "widget-functions" / "PlayerCardsTabWidget"


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

source_paths = [
    *entrypoint_paths.values(),
    FUNCTIONS / "ExecuteUbergraph_PlayerCardsTabWidget.json",
    FUNCTIONS / "PopulateDetailsPanel.json",
    EVIDENCE / "game-rules-draft.json",
    ANALYSIS / "ghidra-native" / "integration-decompiled.c",
]
reconstruction_paths = [
    PROJECT / "Content" / "Recovery" / "UI" / "PlayerCardsTabWidget.uasset",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardsTabWidget.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardsTabWidget.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardEntryWidget.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredPlayerCardEntryWidget.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredProgression.h",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredRewards.cpp",
    PROJECT / "Source" / "CockHeroRecovered" / "RecoveredChallengesMenu.cpp",
    PROJECT / "Scripts" / "reparent_player_cards_tab.py",
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
        "source_asset_recovered": False,
    },
    "source_sha256": {str(path): sha256(path) for path in source_paths},
    "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in reconstruction_paths},
}

output = EVIDENCE / "player-cards-tab-recovery.json"
output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
