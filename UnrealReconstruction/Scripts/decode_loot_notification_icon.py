from __future__ import annotations

import hashlib
import io
import json
import struct
import sys
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
PILLOW_TOOLS = Path(r"C:\Users\webma\analysis\cockhero-v004\tools\pillow")
if str(PILLOW_TOOLS) not in sys.path:
    sys.path.insert(0, str(PILLOW_TOOLS))

from PIL import Image


REPORT = PROJECT / "RecoveryEvidence" / "loot-notification-icon-recovery-report.json"
PNG = PROJECT / "RecoveryEvidence" / "TextureSource" / "Widgets" / "NotificationBoxIcons" / "CoinRewardIcon.png"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def decode(payload: bytes, width: int, height: int, pixel_format: str, srgb: bool) -> Image.Image:
    if pixel_format in ("DXT1", "DXT3", "DXT5", "BC4", "BC5", "BC7"):
        fourcc = {"BC4": "ATI1", "BC5": "ATI2", "BC7": "DX10"}.get(pixel_format, pixel_format)
        header = struct.pack("<7I", 124, 0x81007, height, width, len(payload), 0, 1)
        header += bytes(44)
        header += struct.pack("<II4s5I", 32, 4, fourcc.encode("ascii"), 0, 0, 0, 0, 0)
        header += struct.pack("<5I", 0x1000, 0, 0, 0, 0)
        if pixel_format == "BC7":
            header += struct.pack("<5I", 99 if srgb else 98, 3, 0, 1, 0)
        return Image.open(io.BytesIO(b"DDS " + header + payload)).convert("RGBA")
    if pixel_format == "B8G8R8A8":
        return Image.frombytes("RGBA", (width, height), payload, "raw", "BGRA")
    if pixel_format == "R8G8B8A8":
        return Image.frombytes("RGBA", (width, height), payload, "raw", "RGBA")
    if pixel_format == "G8":
        return Image.frombytes("L", (width, height), payload)
    raise RuntimeError(f"Unsupported loot notification icon pixel format: {pixel_format}")


def main() -> None:
    row = json.loads(REPORT.read_text(encoding="utf-8"))
    payload = Path(row["payload"])
    if not payload.is_absolute():
        payload = (PROJECT / payload).resolve()
    if not payload.is_file():
        raise RuntimeError(f"Recovered payload is unavailable: {payload}")
    if sha256(payload) != row["payload_sha256"]:
        raise RuntimeError("Recovered payload hash changed")
    if payload.stat().st_size != int(row["bytes"]):
        raise RuntimeError("Recovered payload byte count changed")

    image = decode(payload.read_bytes(), int(row["width"]), int(row["height"]), str(row["format"]), bool(row["srgb"]))
    if image.size != (int(row["width"]), int(row["height"])):
        raise RuntimeError("Decoded CoinRewardIcon dimensions differ from source metadata")
    PNG.parent.mkdir(parents=True, exist_ok=True)
    image.save(PNG)
    row.update({
        "png": str(PNG),
        "png_sha256": sha256(PNG),
        "png_width": image.width,
        "png_height": image.height,
        "decoded": True,
    })
    REPORT.write_text(json.dumps(row, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"decoded": row["original"], "png": str(PNG), "size": image.size}))


main()
