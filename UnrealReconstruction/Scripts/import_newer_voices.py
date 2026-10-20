"""Decode and import exact referenced voice samples; verify PCM/source metadata."""
import hashlib
import json
from pathlib import Path
import unreal

project = Path(unreal.Paths.project_dir()).resolve()
report = json.loads((project / "RecoveryEvidence/newer-20261017-voice-streams.json").read_text(encoding="utf-8"))
tools = unreal.AssetToolsHelpers.get_asset_tools()
for row in report["sounds"]:
    encoded = Path(row["encoded"])
    if hashlib.sha256(encoded.read_bytes()).hexdigest() != row["encoded_sha256"]:
        raise RuntimeError(f"Encoded voice checksum mismatch: {row['original']}")
    decoded = json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(str(encoded), row["asset_name"]))
    if not decoded.get("success"):
        raise RuntimeError(f"Voice decoding failed: {row['original']}: {decoded}")
    for field in ("sample_rate", "channels", "frames"):
        if decoded[field] != row[field]:
            raise RuntimeError(f"Voice {field} differs from source: {row['original']}")
    wav = project / "RecoveryEvidence/AudioSource" / (row["asset_name"] + ".wav")
    task = unreal.AssetImportTask()
    task.filename = str(wav)
    task.destination_path = "/Game/Recovery/Newer20261017/Resources/VoicePreviews"
    task.destination_name = row["asset_name"]
    task.automated = True
    task.replace_existing = True
    task.save = True
    tools.import_asset_tasks([task])
    sound = unreal.load_asset(row["asset_path"])
    if not isinstance(sound, unreal.SoundWave) or sound.get_editor_property("num_channels") != row["channels"]:
        raise RuntimeError(f"Voice import differs from source: {row['original']}")
    if not unreal.EditorAssetLibrary.save_loaded_asset(sound, False):
        raise RuntimeError(f"Voice save failed: {row['original']}")
    row["decoded"] = decoded
    row["pcm_sha256"] = hashlib.sha256(wav.read_bytes()).hexdigest()
    row["imported"] = True
(project / "RecoveryEvidence/newer-20261017-voice-import.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
unreal.log(f"NEWER_VOICE_SAMPLES_IMPORTED {len(report['sounds'])}")
