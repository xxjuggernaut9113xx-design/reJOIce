from pathlib import Path
import json
import unreal


targets = (
    ("/Game/Recovery/UI/StatsTabWidget", unreal.RecoveredStatsTabWidget),
    ("/Game/Recovery/UI/EditUsernameOverlay", unreal.RecoveredEditUsernameOverlay),
)
report = {"widgets": []}

for path, parent in targets:
    blueprint = unreal.load_asset(path)
    if not blueprint:
        raise RuntimeError(f"Missing recovered widget: {path}")
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not widget_class:
        raise RuntimeError(f"Missing recovered generated class: {path}")
    changed = False
    if not isinstance(unreal.get_default_object(widget_class), parent):
        unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, parent)
        unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
        widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
        if not widget_class or not isinstance(unreal.get_default_object(widget_class), parent):
            raise RuntimeError(f"Widget reparent failed: {path}")
        changed = True
    if changed and not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
        raise RuntimeError(f"Widget save failed: {path}")
    report["widgets"].append({"asset": path, "parent": parent.static_class().get_path_name(), "changed": changed})

output = Path(unreal.Paths.project_dir()) / "Saved" / "stats-tab-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("STATS_TAB_WIDGET_REPARENTED " + json.dumps(report))
