"""Verify staged dialogue audio bytes and bind source special-event categories."""
import hashlib
import json
from pathlib import Path
from newer_content_contract import PROJECT, SOURCE, require

path = PROJECT / "Content/Recovery/Definitions/newer-20261017-dialogue-catalog.json"
catalog = json.loads(path.read_text(encoding="utf-8"))
enums_path = SOURCE / "decoded-blueprint-enums.json"
enums = json.loads(enums_path.read_text(encoding="utf-8"))
special = next(e for e in enums if e["enum"] == "DialogueSpecialEventsEnum")
require(special["byte_identical_roundtrip"], "Special dialogue event enum is unverified")
catalog["event_categories"] = {str(e["value"]): e["display"] for e in special["entries"] if e.get("display")}
catalog["event_category_source_sha256"] = hashlib.sha256(enums_path.read_bytes()).hexdigest()
for relative, row in catalog["audio_streams"].items():
    data = (PROJECT / "Content" / relative).read_bytes()
    require(hashlib.sha256(data).hexdigest() == row["sha256"], f"Staged source stream checksum mismatch: {relative}")
    require(hashlib.sha1(data).hexdigest() == row["sha1"], f"Staged runtime checksum mismatch: {relative}")
    require(len(data) == row["bytes"], f"Staged source stream length mismatch: {relative}")
coverage = {}
for pack, rows in catalog["packs"].items():
    available = [row for row in rows if row.get("AudioStream")]
    require(available, f"No source audio available for voice pack {pack}")
    require(any(row["Category"] == "boobs" and row["Pronoun"] == "Neutral" for row in available), f"Missing decoder test category for {pack}")
    coverage[pack] = {"source_rows": len(rows), "available_audio": len(available), "unavailable_source_references": len(rows)-len(available)}
path.write_text(json.dumps(catalog, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
report = {"source_executed": False, "voice_packs": coverage, "source_table_roundtrips": catalog["proof"],
          "unique_streams": len(catalog["audio_streams"]), "retained_bytes": sum(r["bytes"] for r in catalog["audio_streams"].values()),
          "all_staged_source_checksums_verified": True, "catalog_sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
          "unavailable_source_references": catalog["missing_source_audio"], "runtime_decoder_test": "pending editor automation"}
(PROJECT / "RecoveryEvidence/newer-20261017-dialogue-validation.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps({k: report[k] for k in ("voice_packs", "unique_streams", "retained_bytes", "catalog_sha256")}))
