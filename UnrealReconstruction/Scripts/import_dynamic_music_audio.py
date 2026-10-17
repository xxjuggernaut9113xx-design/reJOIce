from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
SOURCE_REPORT = PROJECT / "RecoveryEvidence" / "dynamic-music-audio-decoding-report.json"
ALIASES = PROJECT / "RecoveryEvidence" / "resource-aliases.json"
IMPORT_REPORT = PROJECT / "RecoveryEvidence" / "dynamic-music-audio-import-recovery.json"
DESTINATION = "/Game/Recovery/Resources/DynamicMusic"


def main() -> None:
    source = json.loads(SOURCE_REPORT.read_text(encoding="utf-8"))
    aliases = json.loads(ALIASES.read_text(encoding="utf-8"))
    imported_rows = []
    for row in source["tracks"]:
        decoded = row.get("decoded", {})
        source_wave = Path(decoded.get("file", ""))
        if not decoded.get("success") or not source_wave.is_file():
            raise RuntimeError(f"{row['name']}: verified PCM source is unavailable")
        task = unreal.AssetImportTask()
        task.filename = str(source_wave)
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
        imported_rows.append(
            {
                "card_type": row["card_type"],
                "name": row["name"],
                "original": row["original"],
                "asset": asset_path,
                "volume": row["volume"],
                "sample_rate": row["sample_rate"],
                "channels": row["channels"],
                "frames": row["frames"],
            }
        )
    ALIASES.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    IMPORT_REPORT.write_text(
        json.dumps(
            {
                "recovery": "dynamic-music-audio-import",
                "source_executed": False,
                "destination": DESTINATION,
                "tracks": imported_rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("DYNAMIC_MUSIC_AUDIO_IMPORTED " + str(len(imported_rows)))


if __name__ == "__main__":
    main()
