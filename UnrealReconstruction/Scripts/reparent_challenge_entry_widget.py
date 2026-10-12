from pathlib import Path
import json
import unreal


path = "/Game/Recovery/UI/ChallengeEntryWidget"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing recovered challenge entry widget")

widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing recovered challenge entry widget generated class")

reparented = False
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredChallengeEntryWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredChallengeEntryWidget)
    reparented = True

unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredChallengeEntryWidget):
    raise RuntimeError("Challenge entry widget native parent validation failed")

if not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Challenge entry widget save failed")

report = {
    "asset": path,
    "parent": unreal.RecoveredChallengeEntryWidget.static_class().get_path_name(),
    "reparented": reparented,
}
output = Path(unreal.Paths.project_dir()) / "Saved" / "challenge-entry-widget-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("CHALLENGE_ENTRY_WIDGET_REPARENTED " + json.dumps(report))