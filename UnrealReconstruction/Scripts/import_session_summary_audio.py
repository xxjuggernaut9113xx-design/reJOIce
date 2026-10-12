from pathlib import Path
import json
import re
import unreal


project = Path(unreal.Paths.project_dir())
report_path = project / "RecoveryEvidence" / "session-summary-audio-decoding-report.json"
evidence_path = project / "RecoveryEvidence" / "session-summary-audio-import-recovery.json"
alias_path = project / "RecoveryEvidence" / "resource-aliases.json"
widget_path = "/Game/Recovery/UI/WBP_SessionSummaryWidget"
destination = "/Game/Recovery/Resources/PostGameVoicelines"
report = json.loads(report_path.read_text(encoding="utf-8"))
aliases = json.loads(alias_path.read_text(encoding="utf-8"))


def snake(name):
    return re.sub(r"(?<!^)(?=[A-Z])", "_", name).lower()


groups = {name: [] for name in report["voice_arrays"]}
imported = []
for row in report["sounds"]:
    property_name = f"{row['pack']}PostGame{row['outcome']}Lines"
    if property_name not in groups:
        raise RuntimeError(f"Unexpected source voice route: {property_name}")
    wav_path = project / "RecoveryEvidence" / "AudioSource" / f"{row['name']}.wav"
    if not wav_path.is_file():
        raise RuntimeError(f"Missing decoded PCM: {wav_path}")
    task = unreal.AssetImportTask()
    task.filename = str(wav_path)
    task.destination_path = destination
    task.automated = True
    task.replace_existing = True
    task.save = True
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
    asset_path = f"{destination}/{row['name']}.{row['name']}"
    sound = unreal.load_asset(asset_path)
    if not isinstance(sound, unreal.SoundWave):
        raise RuntimeError(f"SoundWave import failed: {asset_path}; {task.imported_object_paths}")
    if sound.get_editor_property("num_channels") != row["channels"]:
        raise RuntimeError(f"Channel mismatch after import: {asset_path}")
    groups[property_name].append(sound)
    aliases[row["original"]] = asset_path
    imported.append({
        "name": row["name"],
        "original": row["original"],
        "asset": asset_path,
        "sample_rate": row["sample_rate"],
        "channels": row["channels"],
        "frames": row["frames"],
        "voice_array": property_name,
    })

for property_name, expected_count in report["voice_arrays"].items():
    if len(groups[property_name]) != expected_count:
        raise RuntimeError(f"{property_name}: expected {expected_count}, imported {len(groups[property_name])}")

blueprint = unreal.load_asset(widget_path)
if not blueprint:
    raise RuntimeError(f"Missing session summary widget: {widget_path}")
unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
widget_class = unreal.EditorAssetLibrary.load_blueprint_class(widget_path)
if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredSessionSummaryWidget):
    raise RuntimeError("Session summary widget does not use URecoveredSessionSummaryWidget")
defaults = unreal.get_default_object(widget_class)
for property_name, sounds in groups.items():
    python_property = snake(property_name)
    defaults.set_editor_property(python_property, sounds)
    stored = defaults.get_editor_property(python_property)
    if len(stored) != len(sounds) or any(actual != expected for actual, expected in zip(stored, sounds)):
        raise RuntimeError(f"Failed to persist {property_name}")

if not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Failed to save session summary voice assignments")
aliases["/Game/UI/PostGameFlow/WBP_SessionSummaryWidget"] = widget_path
alias_path.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
evidence = {
    "recovery": report["recovery"],
    "source_executed": False,
    "source_asset": report["source_asset"],
    "widget": widget_path,
    "native_parent": unreal.RecoveredSessionSummaryWidget.static_class().get_path_name(),
    "destination": destination,
    "voice_arrays": {name: [sound.get_path_name() for sound in sounds] for name, sounds in groups.items()},
    "sounds": imported,
}
evidence_path.write_text(json.dumps(evidence, indent=2) + "\n", encoding="utf-8")
unreal.log("IMPORTED_SESSION_SUMMARY_AUDIO " + str(len(imported)))
