from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
REPORT = PROJECT / "RecoveryEvidence" / "voice-pack-audio-decoding-report.json"
ALIASES = PROJECT / "RecoveryEvidence" / "resource-aliases.json"
IMPORT_REPORT = PROJECT / "RecoveryEvidence" / "voice-pack-audio-import-recovery.json"
DESTINATION = "/Game/Recovery/Resources/Voicelines"


def main() -> None:
    decoded_report = json.loads(REPORT.read_text(encoding="utf-8"))
    aliases = json.loads(ALIASES.read_text(encoding="utf-8"))
    imported = []
    for row in decoded_report["sounds"]:
        decoded = row.get("decoded", {})
        wav_path = PROJECT / "RecoveryEvidence" / "AudioSource" / f"{row['asset_name']}.wav"
        if not decoded.get("success") or not wav_path.is_file():
            raise RuntimeError(f"{row['asset_name']}: decoded PCM is unavailable")
        task = unreal.AssetImportTask()
        task.filename = str(wav_path)
        task.destination_path = DESTINATION
        task.destination_name = row["asset_name"]
        task.automated = True
        task.replace_existing = True
        task.save = True
        unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
        asset_path = row["asset_path"]
        sound = unreal.load_asset(asset_path)
        if not isinstance(sound, unreal.SoundWave):
            raise RuntimeError(f"{row['asset_name']}: SoundWave import failed: {task.imported_object_paths}")
        if sound.get_editor_property("num_channels") != row["channels"]:
            raise RuntimeError(f"{row['asset_name']}: imported channel count differs from source")
        if not unreal.EditorAssetLibrary.save_loaded_asset(sound, only_if_is_dirty=False):
            raise RuntimeError(f"{row['asset_name']}: recovered SoundWave save failed")
        aliases[row["source_package"]] = asset_path
        imported.append(
            {
                "asset_name": row["asset_name"],
                "original": row["source_package"],
                "asset": asset_path,
                "sample_rate": row["sample_rate"],
                "channels": row["channels"],
                "frames": row["frames"],
            }
        )
    ALIASES.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    IMPORT_REPORT.write_text(
        json.dumps(
            {
                "recovery": "voice-pack-preview-audio-import",
                "source_executed": False,
                "destination": DESTINATION,
                "sounds": imported,
                "unavailable_source_references": decoded_report["unavailable_source_references"],
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("VOICE_PACK_AUDIO_IMPORTED " + str(len(imported)))


if __name__ == "__main__":
    main()
