from pathlib import Path
import io
import json
import struct

from PIL import Image

project = Path(__file__).resolve().parents[1]
report_path = project / "Saved" / "outcome-notification-icon-recovery-report.json"
rows = json.loads(report_path.read_text(encoding="utf-8"))
output = project / "RecoveryEvidence" / "TextureSource" / "Widgets" / "NotificationBoxIcons"
output.mkdir(parents=True, exist_ok=True)


def decode(raw, width, height, fmt, srgb):
    if fmt in ("DXT1", "DXT3", "DXT5", "BC4", "BC5", "BC7"):
        fourcc = {"BC4": "ATI1", "BC5": "ATI2", "BC7": "DX10"}.get(fmt, fmt)
        header = struct.pack("<7I", 124, 0x81007, height, width, len(raw), 0, 1)
        header += bytes(44)
        header += struct.pack("<II4s5I", 32, 4, fourcc.encode("ascii"), 0, 0, 0, 0, 0)
        header += struct.pack("<5I", 0x1000, 0, 0, 0, 0)
        extension = struct.pack("<5I", 99 if srgb else 98, 3, 0, 1, 0) if fmt == "BC7" else b""
        return Image.open(io.BytesIO(b"DDS " + header + extension + raw)).convert("RGBA")
    if fmt in ("B8G8R8A8", "R8G8B8A8"):
        order = "BGRA" if fmt == "B8G8R8A8" else "RGBA"
        return Image.frombytes("RGBA", (width, height), raw, "raw", order)
    if fmt == "G8":
        return Image.frombytes("L", (width, height), raw)
    raise RuntimeError("Unsupported pixel format " + fmt)


for row in rows:
    raw_path = Path(row["file"])
    if not raw_path.is_absolute():
        candidates = ((Path.cwd() / raw_path).resolve(), (project.parent / raw_path).resolve())
        raw_path = next((candidate for candidate in candidates if candidate.exists()), candidates[0])
    raw = raw_path.read_bytes()
    image = decode(raw, row["width"], row["height"], row["format"], row["srgb"])
    if image.size != (row["width"], row["height"]):
        raise RuntimeError("Decoded size mismatch for " + row["original"])
    png = output / (Path(row["original"].split(".", 1)[0]).name + ".png")
    image.save(png)
    row["png"] = str(png)
    row["decoded"] = True

report_path.write_text(json.dumps(rows, indent=2), encoding="utf-8")
print(json.dumps({"decoded": len(rows), "output": str(output)}))
