"""Decode and retain byte-verified newer texture mips as PNG source assets."""
import hashlib
import json
from pathlib import Path
from decode_challenge_icons import decode
from newer_content_contract import PROJECT, DEFINITION, require, all_artwork

report_path = PROJECT / "RecoveryEvidence/newer-20261017-artwork.json"
report = json.loads(report_path.read_text(encoding="utf-8"))
contract = json.loads(DEFINITION.read_text(encoding="utf-8"))
require({r["original"] for r in report["textures"]} == set(all_artwork(contract)), "Artwork source set mismatch")
destination = PROJECT / "RecoveryEvidence/TextureSource/Newer20261017"
destination.mkdir(parents=True, exist_ok=True)
for row in report["textures"]:
    payload = Path(row["payload"]).read_bytes()
    require(hashlib.sha256(payload).hexdigest() == row["payload_sha256"], f"Corrupt mip: {row['original']}")
    image = decode(payload, row["width"], row["height"], row["format"], row["srgb"])
    require(image.size == (row["width"], row["height"]), f"Incorrect image size: {row['original']}")
    output = destination / (row["relative_package"] + ".png")
    output.parent.mkdir(parents=True, exist_ok=True)
    image.save(output)
    row.update(png=str(output), png_sha256=hashlib.sha256(output.read_bytes()).hexdigest(), decoded=True)
report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(f"NEWER_ARTWORK_DECODED {len(report['textures'])}")
