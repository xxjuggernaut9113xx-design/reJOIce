"""Recover the exact post-game voice streams referenced by WBP_SessionSummaryWidget."""

from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct


PROJECT = Path(__file__).resolve().parents[1]
SOURCE_ROOT = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-session-summary-audio\CockHero\Content\Audio\Voicelines")
OUTPUT_ROOT = PROJECT / "RecoveryEvidence" / "AudioEncoded" / "PostGame"
CATALOG = PROJECT / "RecoveryEvidence" / "session-summary-audio-stream-catalog.json"


def source_specs():
    specs = []

    def append_series(pack, outcome, count, directory, stem):
        for index in range(1, count + 1):
            source_name = stem(index)
            asset_path = f"/Game/Audio/Voicelines/{directory}/{source_name}"
            specs.append(
                {
                    "pack": pack,
                    "outcome": outcome,
                    "index": index,
                    "source_name": source_name,
                    "source_directory": directory,
                    "original": f"{asset_path}/{source_name}",
                    "name": f"{pack}PostGame{outcome}{index:02d}",
                }
            )

    append_series("Villainess", "Victory", 8, "Default/PostGame/Victory", lambda index: f"Villainess_PostGame_Victory__{index}_")
    append_series("Villainess", "Defeat", 8, "Default/PostGame/Defeat", lambda index: f"Villainess_PostGame_Defeat__{index}_")
    append_series("Brat", "Victory", 7, "Brat/PostGame/Victory", lambda index: f"Brat_PostGame_Victory__{index}_")
    append_series("Brat", "Defeat", 8, "Brat/PostGame/Defeat", lambda index: f"Brat_PostGame_Defeat__{index}_")
    append_series("DommyMommy", "Victory", 10, "DommyMommy/postgamevictory", lambda index: f"Line_{index}")
    append_series("DommyMommy", "Defeat", 10, "DommyMommy/postgamedefeat", lambda index: f"Line_{index}")
    append_series("Sweetheart", "Victory", 10, "Sweetheart/postgamevictory", lambda index: f"Line_{index}")
    append_series("Sweetheart", "Defeat", 9, "Sweetheart/postgamedefeat", lambda index: f"Line_{index}")
    return specs


def sha256(payload: bytes) -> str:
    return hashlib.sha256(payload).hexdigest()


def recover_bink_stream(package: bytes, bulk: bytes, label: str):
    start = package.find(b"ABEU")
    if start < 0:
        raise RuntimeError(f"{label}: Bink header not found")
    header = package[start : start + 28]
    if len(header) != 28:
        raise RuntimeError(f"{label}: truncated Bink header")
    fields = struct.unpack("<IBBHIIHHIHH", header)
    offsets = []
    cursor = 0
    while True:
        cursor = bulk.find(b"SEEK", cursor)
        if cursor < 0:
            break
        offsets.append(cursor)
        cursor += 4
    if not offsets or offsets[0] != 0:
        raise RuntimeError(f"{label}: invalid Bink stream chunks")

    chunks = []
    seek_bytes = 0
    for index, offset in enumerate(offsets):
        if offset + 15 > len(bulk) or bulk[offset + 4] != 0:
            raise RuntimeError(f"{label}: invalid SEEK record")
        count = struct.unpack_from("<i", bulk, offset + 11)[0]
        content = offset + 15 + 2 * count
        end = offsets[index + 1] if index + 1 < len(offsets) else len(bulk)
        if content >= end or bulk[content : content + 2] != b"\x99\x99":
            raise RuntimeError(f"{label}: invalid Bink packet")
        chunks.append(bulk[content:end])
        seek_bytes += 2 * count

    encoded = header + b"".join(chunks)
    if fields[8] != len(encoded) + seek_bytes:
        raise RuntimeError(f"{label}: Bink length mismatch")
    return encoded, fields, len(offsets)


def main():
    specs = source_specs()
    if len(specs) != 70 or len({spec["name"] for spec in specs}) != 70:
        raise RuntimeError("Session summary voice inventory is incomplete")
    OUTPUT_ROOT.mkdir(parents=True, exist_ok=True)
    rows = []
    for spec in specs:
        base = SOURCE_ROOT / spec["source_directory"] / spec["source_name"]
        package_path = base.with_suffix(".uexp")
        bulk_path = base.with_suffix(".ubulk")
        if not package_path.is_file() or not bulk_path.is_file():
            raise RuntimeError(f"Missing extracted source stream: {base}")
        package = package_path.read_bytes()
        bulk = bulk_path.read_bytes()
        encoded, fields, chunk_count = recover_bink_stream(package, bulk, spec["name"])
        encoded_path = OUTPUT_ROOT / f"{spec['name']}.binka"
        encoded_path.write_bytes(encoded)
        rows.append(
            {
                **spec,
                "source_package": str(package_path),
                "source_package_sha256": sha256(package),
                "source_bulk_sha256": sha256(bulk),
                "encoded": str(encoded_path),
                "encoded_sha256": sha256(encoded),
                "sample_rate": fields[4],
                "channels": fields[2],
                "frames": fields[5],
                "stream_chunks": chunk_count,
                "source_executed": False,
            }
        )

    report = {
        "recovery": "session-summary-post-game-voice-streams",
        "source_executed": False,
        "source_asset": "/Game/UI/PostGameFlow/WBP_SessionSummaryWidget",
        "voice_arrays": {
            "VillainessPostGameVictoryLines": 8,
            "VillainessPostGameDefeatLines": 8,
            "BratPostGameVictoryLines": 7,
            "BratPostGameDefeatLines": 8,
            "DommyMommyPostGameVictoryLines": 10,
            "DommyMommyPostGameDefeatLines": 10,
            "SweetheartPostGameVictoryLines": 10,
            "SweetheartPostGameDefeatLines": 9,
        },
        "sounds": rows,
    }
    CATALOG.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"report": str(CATALOG), "sounds": len(rows)}, indent=2))


if __name__ == "__main__":
    main()
