from __future__ import annotations

import hashlib
import json
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
EVIDENCE = PROJECT / "RecoveryEvidence"
LAYOUT = EVIDENCE / "player-card-entry-widget-layout-values.json"
REPORT = EVIDENCE / "player-card-entry-widget-recovery.json"
SOURCE = PROJECT / "Saved" / "SourceDecode" / "PlayerCardEntryWidget" / "PlayerCardEntryWidget.json"
ASSET_PATH = "/Game/Recovery/UI/PlayerCardEntryWidget.PlayerCardEntryWidget"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


if not LAYOUT.is_file() or not REPORT.is_file() or not SOURCE.is_file():
    raise RuntimeError("Player-card entry-widget source evidence is missing")

build = json.loads(unreal.RecoveredWidgetRecovery.build_widget_assets(str(LAYOUT)))
if build.get("errors"):
    raise RuntimeError(f"Player-card entry-widget layout build failed: {build['errors']}")
if len(build.get("assets", [])) != 1 or build["assets"][0].get("asset") != "/Game/Recovery/UI/PlayerCardEntryWidget":
    raise RuntimeError(f"Player-card entry-widget layout build returned the wrong asset set: {build}")
if build["assets"][0].get("warnings"):
    raise RuntimeError(f"Player-card entry-widget layout build warnings: {build['assets'][0]['warnings']}")

animations = json.loads(unreal.RecoveredWidgetRecovery.restore_animation_data(str(SOURCE), ASSET_PATH))
if not animations.get("complete_references") or not animations.get("saved_assets"):
    raise RuntimeError(f"Player-card entry-widget animation restore failed: {animations}")
objects = animations.get("objects", [])
if not objects or not all(item.get("decoded") and not item.get("unresolved_references") for item in objects):
    raise RuntimeError(f"Player-card entry-widget animation payload verification failed: {animations}")
if animations.get("animation_count") != 4:
    raise RuntimeError(f"Player-card entry-widget animation count changed: {animations.get('animation_count')}")

asset = unreal.load_asset(ASSET_PATH)
if not asset:
    raise RuntimeError("Player-card entry-widget asset did not save")
asset_file = PROJECT / "Content" / "Recovery" / "UI" / "PlayerCardEntryWidget.uasset"
if not asset_file.is_file():
    raise RuntimeError("Player-card entry-widget asset file is missing")

report = json.loads(REPORT.read_text(encoding="utf-8"))
report["animation_source"]["source_animation_payloads_decoded"] = True
report["reconstruction"] = {
    "asset": ASSET_PATH,
    "widget_tree_restored": True,
    "animations_restored": True,
    "layout_build": build["assets"][0],
    "animation_restore": animations,
    "asset_sha256": sha256(asset_file),
}
report["reconstruction_sha256"][str(asset_file.relative_to(PROJECT))] = sha256(asset_file)
REPORT.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
(PROJECT / "Saved" / "player-card-entry-widget-build-report.json").write_text(
    json.dumps({"layout": build, "animations": animations}, indent=2) + "\n",
    encoding="utf-8",
)
unreal.log("PLAYER_CARD_ENTRY_WIDGET_RESTORED " + json.dumps({"asset": ASSET_PATH, "animations": animations["animation_count"]}))
