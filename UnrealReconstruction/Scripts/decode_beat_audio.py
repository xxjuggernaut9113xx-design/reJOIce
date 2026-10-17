from __future__ import annotations

import hashlib
import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
SOURCE_REPORT = PROJECT / "RecoveryEvidence" / "beat-audio-source.json"
REPORT = PROJECT / "RecoveryEvidence" / "beat-audio-decoding-report.json"


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def main() -> None:
    source = json.loads(SOURCE_REPORT.read_text(encoding="utf-8"))
    decoded_rows = []
    names: set[str] = set()
    for row in source["tracks"]:
        name = row["name"]
        if name in names:
            raise RuntimeError(f"Duplicate recovered asset name: {name}")
        names.add(name)
        encoded_path = Path(row["encoded"])
        if not encoded_path.is_file() or sha256(encoded_path) != row["encoded_sha256"]:
            raise RuntimeError(f"{name}: encoded Bink stream differs from recovery evidence")
        decoded = json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(str(encoded_path), name))
        if not decoded.get("success"):
            raise RuntimeError(f"{name}: Bink decoder failed: {decoded}")
        for field in ("sample_rate", "channels", "frames"):
            if decoded.get(field) != row[field]:
                raise RuntimeError(f"{name}: decoded {field} differs from source metadata")
        wave = PROJECT / "RecoveryEvidence" / "AudioSource" / f"{name}.wav"
        if not wave.is_file():
            raise RuntimeError(f"{name}: PCM output was not created")
        decoded_rows.append({**row, "decoded": {**decoded, "file": str(wave.resolve()), "sha256": sha256(wave)}})
    REPORT.write_text(
        json.dumps(
            {
                "recovery": "beat-audio-decoding",
                "source_executed": False,
                "pools": source["pools"],
                "tracks": decoded_rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("BEAT_AUDIO_DECODED " + str(len(decoded_rows)))


if __name__ == "__main__":
    main()
