from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct


PROJECT = Path(__file__).resolve().parents[1]
SOURCE_ROOT = Path(
    r"C:\Users\webma\analysis\cockhero-v004\cooked-animation-audio\CockHero\Content\SoundFX\TestMusic"
)
OUTPUT = PROJECT / "RecoveryEvidence" / "AudioEncoded" / "DynamicMusic"
REPORT = PROJECT / "RecoveryEvidence" / "dynamic-music-audio-source.json"
SOURCE_FUNCTION = (
    PROJECT
    / "RecoveryEvidence"
    / "blueprint-functions"
    / "BP_GlobalManager"
    / "PlayMusic.json"
)


TRACKS = (
    {
        "card_type": 0,
        "name": "dt_110_kit15_loop_within_pad_Dmaj__2_",
        "original": "/Game/SoundFX/TestMusic/dt_110_kit15_loop_within_pad_Dmaj__2_.dt_110_kit15_loop_within_pad_Dmaj__2_",
        "volume": 0.1,
    },
    {
        "card_type": 1,
        "name": "HuntingPerc_02_100bpm__3_",
        "original": "/Game/SoundFX/TestMusic/HuntingPerc_02_100bpm__3_.HuntingPerc_02_100bpm__3_",
        "volume": 0.1,
    },
    {
        "card_type": 2,
        "name": "AMP2_90_A_2_3",
        "original": "/Game/SoundFX/TestMusic/AMP2_90_A_2_3.AMP2_90_A_2_3",
        "volume": 0.15,
    },
    {
        "card_type": 3,
        "name": "NW_OSHRS_80_kit_loop_krakenfall_full_Dmin__3_",
        "original": "/Game/SoundFX/TestMusic/NW_OSHRS_80_kit_loop_krakenfall_full_Dmin__3_.NW_OSHRS_80_kit_loop_krakenfall_full_Dmin__3_",
        "volume": 0.2,
    },
)


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def reconstruct_bink_stream(package: bytes, bulk: bytes, name: str) -> tuple[bytes, tuple[int, ...], int]:
    header_offset = package.find(b"ABEU")
    if header_offset < 0:
        raise RuntimeError(f"{name}: Bink header was not found")
    header = package[header_offset : header_offset + 28]
    if len(header) != 28:
        raise RuntimeError(f"{name}: Bink header is truncated")
    fields = struct.unpack("<IBBHIIHHIHH", header)
    if fields[1] != 1 or fields[-2] != 0:
        raise RuntimeError(f"{name}: unexpected Bink header layout")

    offsets: list[int] = []
    cursor = 0
    while True:
        cursor = bulk.find(b"SEEK", cursor)
        if cursor < 0:
            break
        offsets.append(cursor)
        cursor += 4
    if not offsets or offsets[0] != 0:
        raise RuntimeError(f"{name}: Bink stream chunks were not found")

    chunks: list[bytes] = []
    seek_bytes = 0
    for index, offset in enumerate(offsets):
        if offset + 15 > len(bulk) or bulk[offset + 4] != 0:
            raise RuntimeError(f"{name}: invalid Bink SEEK record")
        seek_count = struct.unpack_from("<i", bulk, offset + 11)[0]
        if seek_count <= 0 or seek_count >= 100000:
            raise RuntimeError(f"{name}: invalid Bink seek-table count")
        content_offset = offset + 15 + 2 * seek_count
        end = offsets[index + 1] if index + 1 < len(offsets) else len(bulk)
        if content_offset >= end or bulk[content_offset : content_offset + 2] != b"\x99\x99":
            raise RuntimeError(f"{name}: invalid Bink packet boundary")
        chunks.append(bulk[content_offset:end])
        seek_bytes += 2 * seek_count

    encoded = header + b"".join(chunks)
    if fields[8] != len(encoded) + seek_bytes:
        raise RuntimeError(f"{name}: reconstructed Bink length differs from source metadata")
    return encoded, fields, len(offsets)


def main() -> None:
    if not SOURCE_FUNCTION.is_file():
        raise RuntimeError(f"Source PlayMusic evidence is unavailable: {SOURCE_FUNCTION}")
    OUTPUT.mkdir(parents=True, exist_ok=True)
    rows = []
    for track in TRACKS:
        name = track["name"]
        asset_path = SOURCE_ROOT / f"{name}.uasset"
        package_path = SOURCE_ROOT / f"{name}.uexp"
        bulk_path = SOURCE_ROOT / f"{name}.ubulk"
        for path in (asset_path, package_path, bulk_path):
            if not path.is_file():
                raise RuntimeError(f"{name}: source component is missing: {path}")
        package = package_path.read_bytes()
        bulk = bulk_path.read_bytes()
        encoded, fields, chunk_count = reconstruct_bink_stream(package, bulk, name)
        encoded_path = OUTPUT / f"{name}.binka"
        encoded_path.write_bytes(encoded)
        rows.append(
            {
                **track,
                "source_asset": str(asset_path),
                "source_package": str(package_path),
                "source_bulk": str(bulk_path),
                "source_asset_sha256": sha256(asset_path.read_bytes()),
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
    REPORT.write_text(
        json.dumps(
            {
                "recovery": "dynamic-music-audio-streams",
                "source_executed": False,
                "source_function": str(SOURCE_FUNCTION),
                "source_function_sha256": sha256(SOURCE_FUNCTION.read_bytes()),
                "tracks": rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(json.dumps({"report": str(REPORT), "tracks": len(rows)}, indent=2))


if __name__ == "__main__":
    main()
