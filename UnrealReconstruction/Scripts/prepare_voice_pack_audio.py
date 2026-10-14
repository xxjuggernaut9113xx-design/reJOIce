"""Reconstruct Bink preview streams referenced by VoicePackInfo_DataTable."""
from __future__ import annotations

import hashlib
import json
import struct
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
CATALOG = PROJECT / "RecoveryEvidence" / "voice-pack-catalog.json"
OUTPUT = PROJECT / "RecoveryEvidence" / "AudioEncoded" / "VoicePack"
REPORT = PROJECT / "RecoveryEvidence" / "voice-pack-audio-stream-catalog.json"


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


def sound_rows(catalog: dict) -> list[dict]:
    return [sound for pack in catalog["packs"] for sound in [*pack["samples"], pack["selection_line"]]]


def main() -> None:
    catalog = json.loads(CATALOG.read_text(encoding="utf-8"))
    OUTPUT.mkdir(parents=True, exist_ok=True)
    recovered: list[dict] = []
    unavailable: list[dict] = []
    for sound in sound_rows(catalog):
        if not sound["source_available"]:
            unavailable.append(sound)
            continue
        asset = Path(sound["source_asset"])
        package = asset.with_suffix(".uexp")
        bulk = asset.with_suffix(".ubulk")
        for path in (asset, package, bulk):
            if not path.is_file():
                raise RuntimeError(f"{sound['asset_name']}: missing extracted source component: {path}")
        encoded, fields, chunks = reconstruct_bink_stream(package.read_bytes(), bulk.read_bytes(), sound["asset_name"])
        encoded_path = OUTPUT / f"{sound['asset_name']}.binka"
        encoded_path.write_bytes(encoded)
        recovered.append(
            {
                **sound,
                "source_asset_sha256": sha256(asset.read_bytes()),
                "source_package_sha256": sha256(package.read_bytes()),
                "source_bulk_sha256": sha256(bulk.read_bytes()),
                "encoded": str(encoded_path),
                "encoded_sha256": sha256(encoded),
                "sample_rate": fields[4],
                "channels": fields[2],
                "frames": fields[5],
                "stream_chunks": chunks,
                "source_executed": False,
            }
        )
    REPORT.write_text(
        json.dumps(
            {
                "recovery": "voice-pack-preview-audio-streams",
                "source_executed": False,
                "catalog": str(CATALOG),
                "sounds": recovered,
                "unavailable_source_references": unavailable,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(json.dumps({"report": str(REPORT), "recovered": len(recovered), "unavailable": len(unavailable)}, indent=2))


if __name__ == "__main__":
    main()
