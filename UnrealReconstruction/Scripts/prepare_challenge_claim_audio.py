from __future__ import annotations

from pathlib import Path
import hashlib
import json
import struct


PROJECT = Path(__file__).resolve().parents[1]
NAME = "Juice_SFX__16_"
ORIGINAL = "/Game/UI/PostGameFlow/JuiceSFX/Juice_SFX__16_.Juice_SFX__16_"
SOURCE_UEXP = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-ui\CockHero\Content\UI\PostGameFlow\JuiceSFX\Juice_SFX__16_.uexp")
EXPECTED_COMPONENT_SHA256 = {
    ".uasset": "aa767c2034ca17ccbf366a9b8c3d8cd04b27830d1bbac871665a082adccdb56c",
    ".uexp": "5e03e4d0943d25e67681c31c9d4188a83186209056a534ef86eca3a8a25c8218",
    ".ubulk": "477f6952430b528a678f2b3539889bf57e92c145808119b01cac76e325593345",
}
EXPECTED_ENCODED_SHA256 = "7d4490b5f922d861ed6642699fca96aabbe4e280c888a81f43e9d4c204d42c9f"


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def component(path: Path) -> dict[str, object]:
    if not path.is_file():
        raise RuntimeError(f"Missing cooked challenge-claim audio component: {path}")
    digest = sha256(path)
    expected = EXPECTED_COMPONENT_SHA256[path.suffix]
    if digest != expected:
        raise RuntimeError(f"Source hash mismatch for {path.name}: {digest} != {expected}")
    return {"path": str(path), "bytes": path.stat().st_size, "sha256": digest}


uasset = SOURCE_UEXP.with_suffix(".uasset")
ubulk = SOURCE_UEXP.with_suffix(".ubulk")
source_components = {
    "uasset": component(uasset),
    "uexp": component(SOURCE_UEXP),
    "ubulk": component(ubulk),
}
package = SOURCE_UEXP.read_bytes()
payload = ubulk.read_bytes()
header_offset = package.find(b"ABEU")
if header_offset < 0 or header_offset + 28 > len(package):
    raise RuntimeError(f"Bink audio header was not found in {NAME}")
header = package[header_offset:header_offset + 28]
fields = struct.unpack("<IBBHIIHHIHH", header)
if header[:4] != b"ABEU" or fields[1] != 1 or fields[-2] != 0:
    raise RuntimeError(f"Unexpected Bink audio header layout for {NAME}")
if fields[2] != 2 or fields[4] != 44100 or fields[5] != 48384:
    raise RuntimeError(f"Unexpected Bink source metadata for {NAME}: {fields}")

starts: list[int] = []
cursor = 0
while True:
    cursor = payload.find(b"SEEK", cursor)
    if cursor < 0:
        break
    starts.append(cursor)
    cursor += 4
if not starts or starts[0] != 0:
    raise RuntimeError(f"Bink stream chunks were not found at the source offset for {NAME}")

chunks: list[bytes] = []
seek_table_bytes = 0
seek_counts: list[int] = []
for index, start in enumerate(starts):
    end = starts[index + 1] if index + 1 < len(starts) else len(payload)
    if start + 15 > end or payload[start + 4] != 0:
        raise RuntimeError(f"Unexpected Bink stream chunk header for {NAME} at {start}")
    seek_count = struct.unpack_from("<i", payload, start + 11)[0]
    if not 0 < seek_count < 100000:
        raise RuntimeError(f"Unexpected Bink seek-table count for {NAME} at {start}: {seek_count}")
    content_start = start + 15 + 2 * seek_count
    if content_start >= end or payload[content_start:content_start + 2] != b"\x99\x99":
        raise RuntimeError(f"Unexpected Bink stream packet boundary for {NAME} at {start}")
    chunks.append(payload[content_start:end])
    seek_table_bytes += 2 * seek_count
    seek_counts.append(seek_count)

encoded = header + b"".join(chunks)
if fields[8] != len(encoded) + seek_table_bytes:
    raise RuntimeError(
        f"Bink audio reconstruction length mismatch for {NAME}: "
        f"declared {fields[8]}, recovered {len(encoded) + seek_table_bytes}"
    )
encoded_digest = hashlib.sha256(encoded).hexdigest()
if encoded_digest != EXPECTED_ENCODED_SHA256:
    raise RuntimeError(f"Encoded hash mismatch for {NAME}: {encoded_digest} != {EXPECTED_ENCODED_SHA256}")

encoded_path = PROJECT / "RecoveryEvidence" / "AudioEncoded" / f"{NAME}.binka"
encoded_path.parent.mkdir(parents=True, exist_ok=True)
encoded_path.write_bytes(encoded)
report = {
    "recovery": "challenge-claim-audio",
    "original": ORIGINAL,
    "name": NAME,
    "source": source_components,
    "bink": {
        "header_offset": header_offset,
        "sample_rate": fields[4],
        "channels": fields[2],
        "frames": fields[5],
        "declared_stream_bytes": fields[8],
        "stream_chunks": len(starts),
        "seek_counts": seek_counts,
        "seek_table_bytes": seek_table_bytes,
    },
    "encoded": {
        "path": str(encoded_path),
        "bytes": len(encoded),
        "sha256": encoded_digest,
    },
}
report_path = PROJECT / "RecoveryEvidence" / "challenge-claim-audio-recovery.json"
report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
