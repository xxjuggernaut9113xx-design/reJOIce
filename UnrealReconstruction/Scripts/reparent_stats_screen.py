from pathlib import Path
import json
import unreal


path = "/Game/Recovery/UI/StatsScreenWidget"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing recovered statistics screen widget")

widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing recovered statistics screen generated class")

changed = False
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredStatsScreenWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredStatsScreenWidget)
    unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredStatsScreenWidget):
        raise RuntimeError("Statistics screen widget reparent failed")
    changed = True

if changed and not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Statistics screen widget save failed")

report = {
    "asset": path,
    "parent": unreal.RecoveredStatsScreenWidget.static_class().get_path_name(),
    "changed": changed,
}
output = Path(unreal.Paths.project_dir()) / "Saved" / "statistics-screen-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("STATISTICS_SCREEN_WIDGET_REPARENTED " + json.dumps(report))
