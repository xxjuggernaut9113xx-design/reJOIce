from __future__ import annotations

import hashlib
import io
import json
import struct
import sys
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
TOOLS = Path(r"C:\Users\webma\analysis\cockhero-v004\tools\pillow")
if str(TOOLS) not in sys.path:
    sys.path.insert(0, str(TOOLS))

from PIL import Image


REPORT_PATH = PROJECT / "RecoveryEvidence" / "player-card-texture-recovery.json"
OUTPUT_DIRECTORY = PROJECT / "RecoveryEvidence" / "TextureSource" / "PlayerCards"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def decode(payload: bytes, width: int, height: int, pixel_format: str, srgb: bool) -> Image.Image:
    if pixel_format in ("DXT1", "DXT3", "DXT5", "BC4", "BC5", "BC7"):
        fourcc = {"BC4": "ATI1", "BC5": "ATI2", "BC7": "DX10"}.get(pixel_format, pixel_format)
        header = struct.pack("<7I", 124, 0x81007, height, width, len(payload), 0, 1)
        header += bytes(44)
        header += struct.pack("<II4s5I", 32, 4, fourcc.encode("ascii"), 0, 0, 0, 0, 0)
        header += struct.pack("<5I", 0x1000, 0, 0, 0, 0)
        extension = struct.pack("<5I", 99 if srgb else 98, 3, 0, 1, 0) if pixel_format == "BC7" else b""
        return Image.open(io.BytesIO(b"DDS " + header + extension + payload)).convert("RGBA")
    if pixel_format == "B8G8R8A8":
        return Image.frombytes("RGBA", (width, height), payload, "raw", "BGRA")
    if pixel_format == "R8G8B8A8":
        return Image.frombytes("RGBA", (width, height), payload, "raw", "RGBA")
    raise RuntimeError(f"Unsupported player-card pixel format: {pixel_format}")


report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
if report["expected_card_images"] != 36 or report["exported_images"] != 37:
    raise RuntimeError("Player-card export count is incomplete")

OUTPUT_DIRECTORY.mkdir(parents=True, exist_ok=True)
for row in report["textures"]:
    payload = Path(row["payload"])
    if not payload.is_file() or sha256(payload) != row["payload_sha256"]:
        raise RuntimeError(f"Player-card payload integrity check failed: {row['original']}")
    image = decode(payload.read_bytes(), row["width"], row["height"], row["format"], row["srgb"])
    if image.size != (row["width"], row["height"]):
        raise RuntimeError(f"Decoded dimensions differ for {row['original']}")
    destination = OUTPUT_DIRECTORY / (Path(row["relative_package"]).name + ".png")
    image.save(destination)
    row["png"] = str(destination)
    row["png_sha256"] = sha256(destination)
    row["decoded"] = True

REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"decoded": len(report["textures"]), "report": str(REPORT_PATH)}))
