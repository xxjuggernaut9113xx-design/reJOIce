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


REPORT_PATH = PROJECT / "RecoveryEvidence" / "challenge-icon-recovery.json"
OUTPUT_DIRECTORY = PROJECT / "RecoveryEvidence" / "TextureSource" / "ChallengeIcons"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


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
    raise RuntimeError(f"Unsupported challenge-icon pixel format: {pixel_format}")


def expected_source_icons() -> set[str]:
    rules = json.loads((PROJECT / "RecoveryEvidence" / "game-rules-draft.json").read_text(encoding="utf-8"))
    rows = rules["progression"]["DT_Challenges"]
    icons = {row["Icon"] for row in rows}
    require(len(rows) == 55 and len(icons) == 55, "DT_Challenges no longer has 55 unique icon references")
    return icons


def main() -> None:
    report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    rows = report.get("textures", [])
    require(report.get("expected_icons") == 55 and report.get("exported_icons") == 55, "Challenge icon export report is incomplete")
    require(len(rows) == 55, "Challenge icon export rows are incomplete")
    require({row["original"] for row in rows} == expected_source_icons(), "Exported challenge icons differ from DT_Challenges")

    OUTPUT_DIRECTORY.mkdir(parents=True, exist_ok=True)
    for row in rows:
        source = row.get("source", {})
        for component_name in ("uasset", "uexp", "ubulk"):
            component = Path(source[component_name])
            require(component.is_file(), f"Source component is unavailable: {component}")
            require(sha256(component) == source[f"{component_name}_sha256"], f"Source component hash changed: {component}")

        payload = Path(row["payload"])
        require(payload.is_file(), f"Challenge icon payload is unavailable: {payload}")
        require(sha256(payload) == row["payload_sha256"], f"Challenge icon payload hash changed: {row['original']}")
        require(payload.stat().st_size == int(row["bytes"]), f"Challenge icon payload byte count changed: {row['original']}")

        image = decode(payload.read_bytes(), int(row["width"]), int(row["height"]), row["format"], bool(row["srgb"]))
        require(image.size == (int(row["width"]), int(row["height"])), f"Decoded dimensions differ for {row['original']}")
        destination = OUTPUT_DIRECTORY / f"{Path(row['relative_package']).name}.png"
        image.save(destination)
        require(destination.is_file(), f"PNG output was not created: {destination}")
        row["png"] = str(destination)
        row["png_sha256"] = sha256(destination)
        row["png_width"] = image.width
        row["png_height"] = image.height
        row["decoded"] = True

    require(sum(bool(row.get("decoded")) for row in rows) == 55, "Challenge icon PNG decode is incomplete")
    report["decoded_icons"] = 55
    report["png_directory"] = str(OUTPUT_DIRECTORY)
    REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"decoded": 55, "report": str(REPORT_PATH), "output": str(OUTPUT_DIRECTORY)}))


if __name__ == "__main__":
    main()
