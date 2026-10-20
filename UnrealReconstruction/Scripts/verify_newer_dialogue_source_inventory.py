"""Verify unresolved dialogue paths against the entire shipped IoStore directory."""
import hashlib
import importlib.util
import json
from pathlib import Path
from newer_content_contract import PROJECT, SOURCE, require

module_path = PROJECT.parent / "Analysis/scripts/compare_reference_containers.py"
spec = importlib.util.spec_from_file_location("recovery_container_inventory", module_path)
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
container = Path("C:/Users/webma/Downloads/cock-hero-windows (1)/Windows/CockHero/Content/Paks/CockHero-Windows.utoc")
records = module.inventory(Path("C:/Users/webma/analysis/cockhero-v004/tools/retoc/retoc.exe"), container)
voice_paths = sorted({r["path"] for r in records.values() if r["path"].startswith("Audio/Voicelines/")})
lookup = {path.lower(): path for path in voice_paths}
catalog = json.loads((PROJECT / "Content/Recovery/Definitions/newer-20261017-dialogue-catalog.json").read_text(encoding="utf-8"))
unresolved = []
for row in catalog["missing_source_audio"]:
    expected = "Audio/Voicelines/" + row["source"]
    stem = Path(expected).stem.casefold()
    prefix = "Audio/Voicelines/" + row["pack"] + "/"
    candidates = sorted({p for p in voice_paths if p.lower().startswith(prefix.lower()) and Path(p).stem.casefold() == stem})
    unresolved.append({**row, "declared_package": expected, "case_insensitive_exact_exists": expected.lower() in lookup,
                       "same_pack_same_filename_candidates": candidates})
require(not any(row["case_insensitive_exact_exists"] for row in unresolved), "Converted extraction missed existing source references")
report = {"source_executed": False, "container": str(container), "container_sha256": hashlib.sha256(container.read_bytes()).hexdigest(),
          "directory_game_chunk_count": len(records), "voice_directory_paths": len(voice_paths),
          "case_insensitive_missing_references": len(unresolved), "references": unresolved,
          "policy": "Retain exact source paths; no cross-pack or guessed category substitutions"}
(PROJECT / "RecoveryEvidence/newer-20261017-dialogue-source-inventory.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
(SOURCE / "voice-container-directory.json").write_text(json.dumps({"container_sha256": report["container_sha256"], "paths": voice_paths}, indent=2) + "\n", encoding="utf-8")
print(json.dumps({k: report[k] for k in ("directory_game_chunk_count", "voice_directory_paths", "case_insensitive_missing_references")}))
