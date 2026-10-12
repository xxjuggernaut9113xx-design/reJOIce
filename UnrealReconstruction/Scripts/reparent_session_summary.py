from pathlib import Path
import json
import unreal


path = "/Game/Recovery/UI/WBP_SessionSummaryWidget"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing recovered session summary widget")

widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing recovered session summary generated class")

changed = False
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredSessionSummaryWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredSessionSummaryWidget)
    changed = True

unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredSessionSummaryWidget):
    raise RuntimeError("Session summary widget reparent failed")

if not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Session summary widget save failed")

report = {
    "asset": path,
    "parent": unreal.RecoveredSessionSummaryWidget.static_class().get_path_name(),
    "changed": changed,
}
output = Path(unreal.Paths.project_dir()) / "Saved" / "session-summary-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("SESSION_SUMMARY_WIDGET_REPARENTED " + json.dumps(report))
