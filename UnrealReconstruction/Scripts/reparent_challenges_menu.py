from pathlib import Path
import json
import unreal


path = "/Game/Recovery/UI/ChallengesMenuWidget"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing recovered challenges menu widget")

widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing recovered challenges menu generated class")

changed = False
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredChallengesMenu):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredChallengesMenu)
    unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredChallengesMenu):
        raise RuntimeError("Challenges menu widget reparent failed")
    changed = True

if changed and not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Challenges menu widget save failed")

report = {
    "asset": path,
    "parent": unreal.RecoveredChallengesMenu.static_class().get_path_name(),
    "changed": changed,
}
output = Path(unreal.Paths.project_dir()) / "Saved" / "challenges-menu-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("CHALLENGES_MENU_WIDGET_REPARENTED " + json.dumps(report))
