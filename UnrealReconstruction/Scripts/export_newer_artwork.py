"""Export newer artwork from converted packages without executing the source game."""
import hashlib
import json
import shutil
import sys
from pathlib import Path
import unreal

PROJECT = Path(unreal.Paths.project_dir()).resolve()
sys.path.insert(0, str(PROJECT / "Scripts"))
from newer_content_contract import DEFINITION, all_artwork, require

contract = json.loads(DEFINITION.read_text(encoding="utf-8"))
source = PROJECT / "Saved/NewerArtworkLegacy/CockHero/Content"
destination = PROJECT / "Saved/TextureRecovery/Newer20261017"
destination.mkdir(parents=True, exist_ok=True)
rows = []
for original in all_artwork(contract):
    relative = original.split(".")[0].removeprefix("/Game/")
    components = [source / (relative + ext) for ext in (".uasset", ".uexp")]
    require(all(p.is_file() for p in components), f"Missing converted source: {original}")
    result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(source), relative))
    require(result.get("success"), f"Mip export failed: {original}: {result}")
    payload = destination / (relative + ".bin")
    payload.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(result["file"], payload)
    require(payload.stat().st_size == result["bytes"], f"Mip export length mismatch: {original}")
    rows.append({"original": original, "relative_package": relative, "payload": str(payload),
                 "payload_sha256": hashlib.sha256(payload.read_bytes()).hexdigest(),
                 "source_sha256": {p.name: hashlib.sha256(p.read_bytes()).hexdigest() for p in components},
                 **{k: result[k] for k in ("width", "height", "format", "srgb", "bytes")}})
report = PROJECT / "RecoveryEvidence/newer-20261017-artwork.json"
reference = json.loads((PROJECT.parent / "Analysis/ReferenceBuilds/newer-20261017/reference-inventory.json").read_text(encoding="utf-8"))
containers = [f for f in reference["files"] if f["path"].endswith((".utoc", ".ucas", ".pak"))]
report.write_text(json.dumps({"source_executed": False, "source_root": reference["source_root"],
                             "source_containers": containers,
                             "conversion": "retoc to-legacy <source Paks directory> Saved/NewerArtworkLegacy --filter CockHero/Content/{ChallengeIcons,PlayerCards} --no-shaders --version UE5_3",
                             "textures": rows}, indent=2) + "\n", encoding="utf-8")
unreal.log(f"NEWER_ARTWORK_EXPORTED {len(rows)}")
