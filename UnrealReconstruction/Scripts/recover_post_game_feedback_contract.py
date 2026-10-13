from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
CATALOG = EVIDENCE / "post-game-feedback-audio-stream-catalog.json"
DECODED = EVIDENCE / "post-game-feedback-audio-decoding-report.json"
IMPORTED = EVIDENCE / "post-game-feedback-audio-import-recovery.json"
ALIASES = EVIDENCE / "resource-aliases.json"
OUTPUT = EVIDENCE / "post-game-feedback-audio-contract-recovery.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    catalog = json.loads(CATALOG.read_text(encoding="utf-8"))
    decoded = json.loads(DECODED.read_text(encoding="utf-8"))
    imported = json.loads(IMPORTED.read_text(encoding="utf-8"))
    aliases = json.loads(ALIASES.read_text(encoding="utf-8"))
    expected = ["whoosh-cinematic-161021_sfx", "drop-coin-384921", "Juice_SFX__11_", "Juice_SFX__9_"]
    catalog_rows = catalog["sounds"]
    decoded_rows = decoded["sounds"]
    imported_rows = imported["sounds"]
    require([row["name"] for row in catalog_rows] == expected, "Post-game source audio inventory changed")
    require([row["name"] for row in decoded_rows] == expected, "Post-game decoded audio inventory changed")
    require([row["name"] for row in imported_rows] == expected, "Post-game imported audio inventory changed")
    assets = []
    for source, decoded_row, imported_row in zip(catalog_rows, decoded_rows, imported_rows):
        for path_name, hash_name in (("source_asset", "source_asset_sha256"), ("source_package", "source_package_sha256"), ("source_bulk", "source_bulk_sha256"), ("encoded", "encoded_sha256")):
            path = Path(source[path_name])
            require(path.is_file() and sha256(path) == source[hash_name], f"{source['name']}: {path_name} hash differs")
        wav = PROJECT / "RecoveryEvidence" / "AudioSource" / f"{source['name']}.wav"
        require(decoded_row["decoded"].get("success") and wav.is_file(), f"{source['name']}: decoded PCM is unavailable")
        require(decoded_row["decoded"]["sample_rate"] == source["sample_rate"] and decoded_row["decoded"]["channels"] == source["channels"] and decoded_row["decoded"]["frames"] == source["frames"], f"{source['name']}: decoded stream metadata differs")
        asset_path = imported_row["asset"]
        package, _, _ = asset_path.partition(".")
        disk_path = PROJECT / "Content" / package.removeprefix("/Game/").replace("/", "\\")
        require(disk_path.with_suffix(".uasset").is_file(), f"{source['name']}: imported SoundWave is missing")
        require(aliases.get(source["original"]) == asset_path, f"{source['name']}: resource alias is missing")
        assets.append(asset_path)
    report = {
        "recovery": "post-game-feedback-audio-contract",
        "source_executed": False,
        "source_widgets": catalog["source_widgets"],
        "sounds": assets,
        "verified": {
            "four_source_streams_reconstructed": len(catalog_rows) == 4,
            "source_component_hashes_verified": True,
            "pcm_decode_metadata_verified": True,
            "soundwaves_imported": len(assets) == 4,
            "resource_aliases_complete": True,
            "all_verified": True,
        },
        "source_sha256": {str(path): sha256(path) for path in (CATALOG, DECODED, IMPORTED, ALIASES)},
        "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in (
            PROJECT / "Scripts" / "prepare_post_game_feedback_audio.py",
            PROJECT / "Scripts" / "decode_post_game_feedback_audio.py",
            PROJECT / "Scripts" / "import_post_game_feedback_audio.py",
            PROJECT / "Scripts" / "recover_post_game_feedback_contract.py",
        )},
    }
    OUTPUT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"sounds": len(assets), "report": str(OUTPUT), "verified": report["verified"]}, indent=2))


if __name__ == "__main__":
    main()
