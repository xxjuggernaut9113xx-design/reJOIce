from pathlib import Path
import json
import unreal


path = "/Game/Recovery/UI/PlayerCardsTabWidget"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing recovered player cards tab widget")

widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing recovered player cards tab generated class")

changed = False
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredPlayerCardsTabWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredPlayerCardsTabWidget)
    unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredPlayerCardsTabWidget):
        raise RuntimeError("Player cards tab widget reparent failed")
    changed = True

if changed and not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Player cards tab widget save failed")

report = {
    "asset": path,
    "parent": unreal.RecoveredPlayerCardsTabWidget.static_class().get_path_name(),
    "changed": changed,
}
output = Path(unreal.Paths.project_dir()) / "Saved" / "player-cards-tab-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("PLAYER_CARDS_TAB_WIDGET_REPARENTED " + json.dumps(report))
