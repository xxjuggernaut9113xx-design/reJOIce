"""Recover the VoicelineSettingsMenu catalog from the shipping data-table payload."""
from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
SOURCE_ROOT = Path(r"C:\Users\webma\analysis\cockhero-v004\voicepacks-extract\CockHero\Content\Voicelines")
SOURCE_AUDIO_ROOT = Path(r"C:\Users\webma\analysis\cockhero-v004\voicepack-audio-extract\CockHero\Content\Audio\Voicelines")
TABLE_ASSET = SOURCE_ROOT / "VoicePackInfo_DataTable.uasset"
TABLE_EXPORT = SOURCE_ROOT / "VoicePackInfo_DataTable.uexp"
CATALOG = EVIDENCE / "voice-pack-catalog.json"
COOKED_CATALOG = PROJECT / "Content" / "Recovery" / "Definitions" / "voice-pack-catalog.json"
REPORT = EVIDENCE / "voice-pack-recovery.json"

TABLE_ASSET_SHA256 = "1c03bd910f3f7b48d5e7674c3feafd3b60ad88d886913ee0e7386e6c96104dc0"
TABLE_EXPORT_SHA256 = "7fdb4ecb731104251666e7348b719fbf7205eb0ef938125abf835a639b9043a9"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def source_package(path: str) -> Path:
    relative = path.removeprefix("/Game/Audio/Voicelines/")
    parts = relative.split("/")
    require(len(parts) >= 2, f"Unexpected shipping voice-pack path: {path}")

    directory = SOURCE_AUDIO_ROOT
    for component in parts[:-1]:
        exact = directory / component
        if exact.is_dir():
            directory = exact
            continue
        matches = [candidate for candidate in directory.iterdir() if candidate.is_dir() and candidate.name.casefold() == component.casefold()]
        require(len(matches) == 1, f"Cannot resolve source directory with Unreal path casing: {path}")
        directory = matches[0]
    return directory / f"{parts[-1]}.uasset"


PACKS = (
    {
        "row_name": "Villainess",
        "display_name": "Villainess",
        "description": "A beautifully dangerous foe who mixes pleasure with cruelty. She seduces with purpose, taunts with intent, and uses your arousal like a leash pulling you toward inevitable ruin.",
        "tags": ["dominant", "evil", "tempting", "teasing"],
        "voice_pack_enum": 0,
        "source_import_refs": [-27, -26, -25, -28],
        "samples": [
            ("/Game/Audio/Voicelines/Default/succubus/Line_33", "VP_Villainess_Sample1"),
            ("/Game/Audio/Voicelines/Default/medium/Line_1", "VP_Villainess_Sample2"),
            ("/Game/Audio/Voicelines/Default/fast/Line_2", "VP_Villainess_Sample3"),
        ],
        "selection_line": ("/Game/Audio/Voicelines/Default/Villainess_Selection_Audio", "VP_Villainess_Selection"),
    },
    {
        "row_name": "Teasing Brat",
        "display_name": "Teasing Brat",
        "description": "A full-time bully with a razor-sharp tongue. Nothing you do is good enough, and she enjoys rubbing that in.",
        "tags": ["cruel", "dominant", "bratty", "bully"],
        "voice_pack_enum": 1,
        "source_import_refs": [-23, -24, -22, -21],
        "samples": [
            ("/Game/Audio/Voicelines/Brat/PostGame/Defeat/Brat_PostGame_Defeat__2_", "VP_TeasingBrat_Sample1"),
            ("/Game/Audio/Voicelines/Brat/taunt/Line_41", "VP_TeasingBrat_Sample2"),
            ("/Game/Audio/Voicelines/Brat/paizuri/Line_36", "VP_TeasingBrat_Sample3"),
        ],
        "selection_line": ("/Game/Audio/Voicelines/Brat/brat_selection_audio", "VP_TeasingBrat_Selection"),
    },
    {
        "row_name": "Dommy Mommy",
        "display_name": "Dommy Mommy",
        "description": "A warm, dominant presence who knows how to make you behave. She rewards good boys, corrects bad ones, and keeps you right where she wants you — needy and obedient.",
        "tags": ["praise", "dominant", "soft", "caring"],
        "voice_pack_enum": 2,
        "source_import_refs": [-29, -30, -31, -32],
        "samples": [
            ("/Game/Audio/Voicelines/DommyMommy/bentover/Line_1", "VP_DommyMommy_Sample1"),
            ("/Game/Audio/Voicelines/DommyMommy/boobs/Line_8", "VP_DommyMommy_Sample2"),
            ("/Game/Audio/Voicelines/DommyMommy/cummingontime/Line_4", "VP_DommyMommy_Sample3"),
        ],
        "selection_line": ("/Game/Audio/Voicelines/DommyMommy/dommymommy_selection_audio", "VP_DommyMommy_Selection"),
    },
    {
        "row_name": "Sweetheart",
        "display_name": "Sweetheart",
        "description": "A tender, affectionate lover who adores you. She guides softly, praises freely, and pulls you close with warm, romantic sweetness.",
        "tags": ["needy", "gentle", "soft", "subby"],
        "voice_pack_enum": 3,
        "source_import_refs": [-34, -33, -36, -35],
        "samples": [
            ("/Game/Audio/Voicelines/Sweetheart/succubus/Line_1", "VP_Sweetheart_Sample1"),
            ("/Game/Audio/Voicelines/Sweetheart/boobs/Line_2", "VP_Sweetheart_Sample2"),
            ("/Game/Audio/Voicelines/Sweetheart/upskirt/Line_2", "VP_Sweetheart_Sample3"),
        ],
        "selection_line": ("/Game/Audio/Voicelines/Sweetheart/sweetheart_selection_line", "VP_Sweetheart_Selection"),
    },
)


def asset_record(source_path: str, asset_name: str) -> dict[str, object]:
    package = source_package(source_path)
    return {
        "source_package": source_path,
        "source_object": source_path.rsplit("/", 1)[-1],
        "source_asset": str(package),
        "source_available": package.is_file(),
        "asset_name": asset_name,
        "asset_path": f"/Game/Recovery/Resources/Voicelines/{asset_name}.{asset_name}",
    }


def main() -> None:
    require(TABLE_ASSET.is_file(), f"Missing shipping DataTable package: {TABLE_ASSET}")
    require(TABLE_EXPORT.is_file(), f"Missing shipping DataTable export: {TABLE_EXPORT}")
    require(sha256(TABLE_ASSET) == TABLE_ASSET_SHA256, "VoicePackInfo_DataTable.uasset hash differs from the recovered source")
    require(sha256(TABLE_EXPORT) == TABLE_EXPORT_SHA256, "VoicePackInfo_DataTable.uexp hash differs from the recovered source")
    payload = TABLE_EXPORT.read_bytes()
    require(len(PACKS) == 4, "Voice-pack row count changed")

    records = []
    for pack in PACKS:
        display = pack["display_name"]
        description = pack["description"]
        require(display.encode("utf-8") + b"\0" in payload, f"Shipping row name missing: {display}")
        description_payload = description.encode("utf-16le") + b"\0\0" if display == "Dommy Mommy" else description.encode("utf-8") + b"\0"
        require(description_payload in payload, f"Shipping description missing: {display}")
        for tag in pack["tags"]:
            require(tag.encode("utf-8") + b"\0" in payload, f"Shipping tag missing: {display}/{tag}")
        refs = struct.pack("<4i", *pack["source_import_refs"])
        require(refs in payload, f"Shipping SoundWave import sequence missing: {display}")
        samples = [asset_record(source, name) for source, name in pack["samples"]]
        selection = asset_record(*pack["selection_line"])
        records.append(
            {
                "row_name": pack["row_name"],
                "display_name": display,
                "description": description,
                "tags": pack["tags"],
                "voice_pack_enum": pack["voice_pack_enum"],
                "source_import_refs": pack["source_import_refs"],
                "samples": samples,
                "selection_line": selection,
                "sample_1_asset_path": samples[0]["asset_path"],
                "sample_2_asset_path": samples[1]["asset_path"],
                "sample_3_asset_path": samples[2]["asset_path"],
                "selection_line_asset_path": selection["asset_path"],
            }
        )

    catalog = {
        "catalog_version": 1,
        "source_data_table": str(TABLE_ASSET),
        "source_data_table_sha256": TABLE_ASSET_SHA256,
        "source_export": str(TABLE_EXPORT),
        "source_export_sha256": TABLE_EXPORT_SHA256,
        "source_row_order": [record["row_name"] for record in records],
        "packs": records,
    }
    catalog_text = json.dumps(catalog, ensure_ascii=False, indent=2) + "\n"
    CATALOG.write_text(catalog_text, encoding="utf-8")
    COOKED_CATALOG.parent.mkdir(parents=True, exist_ok=True)
    COOKED_CATALOG.write_text(catalog_text, encoding="utf-8")

    sounds = [sound for record in records for sound in [*record["samples"], record["selection_line"]]]
    REPORT.write_text(
        json.dumps(
            {
                "recovery": "voiceline-settings-catalog",
                "source_executed": False,
                "source_widget": "/Game/Voicelines/VoicelineSettingsMenu",
                "source_entry_widget": "/Game/Voicelines/VoicePackEntryWidget",
                "source_data_table": str(TABLE_ASSET),
                "catalog": str(CATALOG),
                "cooked_catalog": str(COOKED_CATALOG),
                "row_count": len(records),
                "sound_reference_count": len(sounds),
                "available_sound_payload_count": sum(bool(sound["source_available"]) for sound in sounds),
                "unavailable_sound_payloads": [sound["source_package"] for sound in sounds if not sound["source_available"]],
                "source_entrypoints": {
                    "Construct": 1083,
                    "PopulateVoicepacks": 1988,
                    "PackClicked": 2091,
                    "EquipSelected": 3849,
                    "SPHSelectionChanged": 3954,
                },
                "catalog_contract": {
                    "selection_label": "Equipped",
                    "unselected_label": "Equip",
                    "selection_volume": 1.0,
                    "selection_pitch": 1.0,
                    "sample_volume": 1.0,
                    "sample_pitch": 1.0,
                },
            },
            ensure_ascii=False,
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(json.dumps({"catalog": str(CATALOG), "rows": len(records), "available_sounds": sum(bool(sound["source_available"]) for sound in sounds)}, indent=2))


if __name__ == "__main__":
    main()
