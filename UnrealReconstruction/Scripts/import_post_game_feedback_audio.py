from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
REPORT = PROJECT / "RecoveryEvidence" / "post-game-feedback-audio-decoding-report.json"
ALIASES = PROJECT / "RecoveryEvidence" / "resource-aliases.json"
IMPORT_REPORT = PROJECT / "RecoveryEvidence" / "post-game-feedback-audio-import-recovery.json"
DESTINATION = "/Game/Recovery/Resources/PostGameSoundFX"


def main() -> None:
    decoded_report = json.loads(REPORT.read_text(encoding="utf-8"))
    aliases = json.loads(ALIASES.read_text(encoding="utf-8"))
    imported = []
    for row in decoded_report["sounds"]:
        decoded = row.get("decoded", {})
        wav_path = PROJECT / "RecoveryEvidence" / "AudioSource" / f"{row['name']}.wav"
        if not decoded.get("success") or not wav_path.is_file():
            raise RuntimeError(f"{row['name']}: decoded PCM is unavailable")
        task = unreal.AssetImportTask()
        task.filename = str(wav_path)
        task.destination_path = DESTINATION
        task.destination_name = row["name"]
        task.automated = True
        task.replace_existing = True
        task.save = True
        unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
        asset_path = f"{DESTINATION}/{row['name']}.{row['name']}"
        sound = unreal.load_asset(asset_path)
        if not isinstance(sound, unreal.SoundWave):
            raise RuntimeError(f"{row['name']}: SoundWave import failed: {task.imported_object_paths}")
        if sound.get_editor_property("num_channels") != row["channels"]:
            raise RuntimeError(f"{row['name']}: imported channel count differs from source")
        if not unreal.EditorAssetLibrary.save_loaded_asset(sound, only_if_is_dirty=False):
            raise RuntimeError(f"{row['name']}: recovered SoundWave save failed")
        aliases[row["original"]] = asset_path
        imported.append({"name": row["name"], "original": row["original"], "asset": asset_path, "sample_rate": row["sample_rate"], "channels": row["channels"], "frames": row["frames"]})
    ALIASES.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    IMPORT_REPORT.write_text(
        json.dumps(
            {
                "recovery": "post-game-feedback-audio-import",
                "source_executed": False,
                "destination": DESTINATION,
                "sounds": imported,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("POST_GAME_FEEDBACK_AUDIO_IMPORTED " + str(len(imported)))


if __name__ == "__main__":
    main()
