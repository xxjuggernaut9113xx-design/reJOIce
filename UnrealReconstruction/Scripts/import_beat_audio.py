from __future__ import annotations

import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
SOURCE_REPORT = PROJECT / "RecoveryEvidence" / "beat-audio-decoding-report.json"
ALIASES = PROJECT / "RecoveryEvidence" / "resource-aliases.json"
REPORT = PROJECT / "RecoveryEvidence" / "beat-audio-import-recovery.json"


def import_sound(row: dict) -> str:
    name = row["name"]
    decoded = row.get("decoded", {})
    source_wave = Path(decoded.get("file", ""))
    if not decoded.get("success") or not source_wave.is_file():
        raise RuntimeError(f"{name}: verified PCM source is unavailable")
    task = unreal.AssetImportTask()
    task.filename = str(source_wave)
    task.destination_path = row["destination"]
    task.destination_name = name
    task.automated = True
    task.replace_existing = True
    task.save = True
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
    asset_path = f"{row['destination']}/{name}.{name}"
    sound = unreal.load_asset(asset_path)
    if not isinstance(sound, unreal.SoundWave):
        raise RuntimeError(f"{name}: SoundWave import failed: {task.imported_object_paths}")
    if sound.get_editor_property("num_channels") != row["channels"]:
        raise RuntimeError(f"{name}: imported channel count differs from source")
    if not unreal.EditorAssetLibrary.save_loaded_asset(sound, only_if_is_dirty=False):
        raise RuntimeError(f"{name}: recovered SoundWave save failed")
    return asset_path


def main() -> None:
    source = json.loads(SOURCE_REPORT.read_text(encoding="utf-8"))
    aliases = json.loads(ALIASES.read_text(encoding="utf-8"))
    imported_rows = []
    for index, row in enumerate(source["tracks"], start=1):
        asset_path = import_sound(row)
        aliases[row["original"]] = asset_path
        if row.get("original_wave"):
            aliases[row["original_wave"]] = asset_path
        imported_rows.append(
            {
                "name": row["name"],
                "kind": row["kind"],
                "pool": row["pool"],
                "original": row["original"],
                "asset": asset_path,
                "sample_rate": row["sample_rate"],
                "channels": row["channels"],
                "frames": row["frames"],
            }
        )
        if index % 25 == 0:
            unreal.log(f"BEAT_AUDIO_IMPORTED {index}")
    ALIASES.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
    REPORT.write_text(
        json.dumps(
            {
                "recovery": "beat-audio-import",
                "source_executed": False,
                "pools": source["pools"],
                "tracks": imported_rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("BEAT_AUDIO_IMPORTED " + str(len(imported_rows)))


if __name__ == "__main__":
    main()
