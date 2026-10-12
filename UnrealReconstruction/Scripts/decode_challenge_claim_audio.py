from __future__ import annotations

from pathlib import Path
import hashlib
import json
import unreal


PROJECT = Path(unreal.Paths.project_dir())
REPORT_PATH = PROJECT / "RecoveryEvidence" / "challenge-claim-audio-recovery.json"


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


if not REPORT_PATH.is_file():
    raise RuntimeError("Challenge-claim audio preparation evidence is unavailable")
report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
encoded = report.get("encoded", {})
encoded_path = Path(encoded.get("path", ""))
if not encoded_path.is_file():
    raise RuntimeError(f"Challenge-claim Bink stream is unavailable: {encoded_path}")
if sha256(encoded_path) != encoded.get("sha256"):
    raise RuntimeError("Challenge-claim Bink stream hash differs from preparation evidence")

decoded = json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(str(encoded_path), report["name"]))
if not decoded.get("success"):
    raise RuntimeError(decoded)
for field in ("sample_rate", "channels", "frames"):
    if decoded.get(field) != report["bink"][field]:
        raise RuntimeError(
            f"Decoded {field} differs from recovered Bink metadata: "
            f"{decoded.get(field)} != {report['bink'][field]}"
        )
decoded_path = Path(decoded.get("file", ""))
if not decoded_path.is_file():
    raise RuntimeError(f"Bink decoder did not produce a wave file: {decoded_path}")
decoded["bytes"] = decoded_path.stat().st_size
decoded["sha256"] = sha256(decoded_path)
report["decoded"] = decoded
REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
unreal.log("RECOVERED_CHALLENGE_CLAIM_AUDIO_DECODED " + str(decoded_path))
