from __future__ import annotations

import hashlib
import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
SOURCE_REPORT = PROJECT / "RecoveryEvidence" / "dynamic-music-audio-source.json"
REPORT = PROJECT / "RecoveryEvidence" / "dynamic-music-audio-decoding-report.json"


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def main() -> None:
    source = json.loads(SOURCE_REPORT.read_text(encoding="utf-8"))
    decoded_rows = []
    for row in source["tracks"]:
        encoded_path = Path(row["encoded"])
        if not encoded_path.is_file() or sha256(encoded_path) != row["encoded_sha256"]:
            raise RuntimeError(f"{row['name']}: encoded Bink stream differs from recovery evidence")
        decoded = json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(str(encoded_path), row["name"]))
        if not decoded.get("success"):
            raise RuntimeError(f"{row['name']}: Bink decoder failed: {decoded}")
        for field in ("sample_rate", "channels", "frames"):
            if decoded.get(field) != row[field]:
                raise RuntimeError(f"{row['name']}: decoded {field} differs from source metadata")
        wave = PROJECT / "RecoveryEvidence" / "AudioSource" / f"{row['name']}.wav"
        if not wave.is_file():
            raise RuntimeError(f"{row['name']}: PCM output was not created")
        decoded_rows.append({**row, "decoded": {**decoded, "file": str(wave.resolve()), "sha256": sha256(wave)}})
    REPORT.write_text(
        json.dumps(
            {
                "recovery": "dynamic-music-audio-decoding",
                "source_executed": False,
                "tracks": decoded_rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("DYNAMIC_MUSIC_AUDIO_DECODED " + str(len(decoded_rows)))


if __name__ == "__main__":
    main()
