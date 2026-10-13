from __future__ import annotations

import hashlib
import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
CATALOG = PROJECT / "RecoveryEvidence" / "post-game-feedback-audio-stream-catalog.json"
REPORT = PROJECT / "RecoveryEvidence" / "post-game-feedback-audio-decoding-report.json"


def main() -> None:
    catalog = json.loads(CATALOG.read_text(encoding="utf-8"))
    decoded_rows = []
    for row in catalog["sounds"]:
        encoded = Path(row["encoded"])
        if not encoded.is_file() or hashlib.sha256(encoded.read_bytes()).hexdigest() != row["encoded_sha256"]:
            raise RuntimeError(f"{row['name']}: encoded stream hash differs from preparation evidence")
        decoded = json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(str(encoded), row["name"]))
        if not decoded.get("success"):
            raise RuntimeError(f"{row['name']}: {decoded}")
        for field in ("sample_rate", "channels", "frames"):
            if decoded.get(field) != row[field]:
                raise RuntimeError(f"{row['name']}: {field} differs from source stream")
        wav_path = PROJECT / "RecoveryEvidence" / "AudioSource" / f"{row['name']}.wav"
        if not wav_path.is_file():
            raise RuntimeError(f"{row['name']}: decoder did not create PCM output")
        decoded["file"] = str(wav_path.resolve())
        decoded_rows.append({**row, "decoded": decoded})
    REPORT.write_text(
        json.dumps(
            {
                "recovery": catalog["recovery"],
                "source_executed": False,
                "source_widgets": catalog["source_widgets"],
                "sounds": decoded_rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("POST_GAME_FEEDBACK_AUDIO_DECODED " + str(len(decoded_rows)))


if __name__ == "__main__":
    main()
