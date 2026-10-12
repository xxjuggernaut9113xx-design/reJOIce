from __future__ import annotations

from pathlib import Path
import hashlib
import json
import unreal


PROJECT = Path(unreal.Paths.project_dir())
REPORT_PATH = PROJECT / "RecoveryEvidence" / "challenge-claim-audio-recovery.json"
DESTINATION = "/Game/Recovery/Resources/Audio"


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


if not REPORT_PATH.is_file():
    raise RuntimeError("Challenge-claim audio recovery evidence is unavailable")
report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
decoded = report.get("decoded")
if not decoded or not decoded.get("success"):
    raise RuntimeError("Decoded challenge-claim audio evidence is unavailable")
decoded_path = Path(decoded.get("file", ""))
if not decoded_path.is_file():
    raise RuntimeError(f"Decoded challenge-claim wave file is unavailable: {decoded_path}")
if sha256(decoded_path) != decoded.get("sha256"):
    raise RuntimeError("Decoded challenge-claim wave hash differs from decode evidence")

task = unreal.AssetImportTask()
task.filename = str(decoded_path)
task.destination_path = DESTINATION
task.automated = True
task.replace_existing = True
task.save = True
unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
asset_path = f"{DESTINATION}/{report['name']}.{report['name']}"
sound = unreal.load_asset(asset_path)
if not isinstance(sound, unreal.SoundWave):
    raise RuntimeError(f"Challenge-claim sound import failed: {task.imported_object_paths}")
channels = sound.get_editor_property("num_channels")
if channels != report["bink"]["channels"]:
    raise RuntimeError(
        f"Recovered sound channel count differs from source: {channels} != {report['bink']['channels']}"
    )

aliases_path = PROJECT / "RecoveryEvidence" / "resource-aliases.json"
aliases = json.loads(aliases_path.read_text(encoding="utf-8")) if aliases_path.is_file() else {}
previous_alias = aliases.get(report["original"])
aliases[report["original"]] = asset_path
aliases_path.write_text(json.dumps(aliases, indent=2) + "\n", encoding="utf-8")
report["imported"] = {
    "asset_path": asset_path,
    "asset_class": sound.get_class().get_name(),
    "channels": channels,
    "source_pcm_preserved": True,
    "previous_alias": previous_alias,
    "alias": asset_path,
}
REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
unreal.log("RECOVERED_CHALLENGE_CLAIM_AUDIO_IMPORTED " + asset_path)
