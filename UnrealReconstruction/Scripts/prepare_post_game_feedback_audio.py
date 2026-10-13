from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct


PROJECT = Path(__file__).resolve().parents[1]
ANIMATION_AUDIO = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-animation-audio\CockHero\Content\SoundFX")
UI_AUDIO = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-ui\CockHero\Content\UI\PostGameFlow\JuiceSFX")
OUTPUT = PROJECT / "RecoveryEvidence" / "AudioEncoded" / "PostGameFeedback"
CATALOG = PROJECT / "RecoveryEvidence" / "post-game-feedback-audio-stream-catalog.json"


SPECS = (
    ("whoosh-cinematic-161021_sfx", "/Game/SoundFX/whoosh-cinematic-161021_sfx.whoosh-cinematic-161021_sfx", ANIMATION_AUDIO),
    ("drop-coin-384921", "/Game/SoundFX/drop-coin-384921.drop-coin-384921", ANIMATION_AUDIO),
    ("Juice_SFX__11_", "/Game/UI/PostGameFlow/JuiceSFX/Juice_SFX__11_.Juice_SFX__11_", UI_AUDIO),
    ("Juice_SFX__9_", "/Game/UI/PostGameFlow/JuiceSFX/Juice_SFX__9_.Juice_SFX__9_", UI_AUDIO),
    ("Juice_SFX__5_", "/Game/UI/PostGameFlow/JuiceSFX/Juice_SFX__5_.Juice_SFX__5_", UI_AUDIO),
)


def sha256(payload: bytes) -> str:
    return hashlib.sha256(payload).hexdigest()


def reconstruct_bink_stream(package: bytes, bulk: bytes, name: str) -> tuple[bytes, tuple[int, ...], int]:
    header_offset = package.find(b"ABEU")
    if header_offset < 0:
        raise RuntimeError(f"{name}: Bink header was not found")
    header = package[header_offset : header_offset + 28]
    if len(header) != 28:
        raise RuntimeError(f"{name}: Bink header is truncated")
    fields = struct.unpack("<IBBHIIHHIHH", header)
    if fields[1] != 1 or fields[-2] != 0:
        raise RuntimeError(f"{name}: unexpected Bink header")
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
        raise RuntimeError(f"{name}: reconstructed Bink stream length differs from source")
    return encoded, fields, len(offsets)


def main() -> None:
    OUTPUT.mkdir(parents=True, exist_ok=True)
    rows = []
    for name, original, source_root in SPECS:
        package_path = source_root / f"{name}.uexp"
        bulk_path = source_root / f"{name}.ubulk"
        asset_path = source_root / f"{name}.uasset"
        for path in (asset_path, package_path, bulk_path):
            if not path.is_file():
                raise RuntimeError(f"{name}: missing extracted source component: {path}")
        package = package_path.read_bytes()
        bulk = bulk_path.read_bytes()
        encoded, fields, chunk_count = reconstruct_bink_stream(package, bulk, name)
        encoded_path = OUTPUT / f"{name}.binka"
        encoded_path.write_bytes(encoded)
        rows.append(
            {
                "name": name,
                "original": original,
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
    report = {
        "recovery": "post-game-feedback-audio-streams",
        "source_executed": False,
        "source_widgets": [
            "/Game/UI/PostGameFlow/WBP_XPBar",
            "/Game/UI/PostGameFlow/WBP_LevelUpScreen",
            "/Game/UI/PostGameFlow/WBP_UPSourceText",
        ],
        "sounds": rows,
    }
    CATALOG.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"report": str(CATALOG), "sounds": len(rows)}, indent=2))


if __name__ == "__main__":
    main()
