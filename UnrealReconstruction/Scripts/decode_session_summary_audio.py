from pathlib import Path
import hashlib
import json
import unreal


project = Path(unreal.Paths.project_dir())
catalog_path = project / "RecoveryEvidence" / "session-summary-audio-stream-catalog.json"
report_path = project / "RecoveryEvidence" / "session-summary-audio-decoding-report.json"
catalog = json.loads(catalog_path.read_text(encoding="utf-8"))
decoded_rows = []

for row in catalog["sounds"]:
    encoded_path = Path(row["encoded"])
    if hashlib.sha256(encoded_path.read_bytes()).hexdigest() != row["encoded_sha256"]:
        raise RuntimeError(f"{row['name']}: encoded stream hash differs from preparation evidence")
    decoded = json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(str(encoded_path), row["name"]))
    if not decoded.get("success"):
        raise RuntimeError(f"{row['name']}: {decoded}")
    for field in ("sample_rate", "channels", "frames"):
        if decoded.get(field) != row[field]:
            raise RuntimeError(f"{row['name']}: {field} differs from source stream")
    decoded_rows.append({**row, "decoded": decoded})

report = {
    "recovery": catalog["recovery"],
    "source_executed": False,
    "source_asset": catalog["source_asset"],
    "voice_arrays": catalog["voice_arrays"],
    "sounds": decoded_rows,
}
report_path.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
unreal.log("RECOVERED_SESSION_SUMMARY_AUDIO " + str(len(decoded_rows)))
