"""Reparent only the supplied patch widgets; preserve recovered trees/animations."""
import json
from pathlib import Path
import unreal
parents = {
    "AudioSettingsMenu": unreal.RecoveredAudioSettingsMenu,
    "VideoSettingsMenu": unreal.RecoveredVideoSettingsMenu,
    "TagSettingsMenu": unreal.RecoveredTagSettingsMenu,
    "ToySettingsMenu": unreal.RecoveredToySettingsMenu,
    "ImportMenuWidget": unreal.RecoveredImportWidget,
    "ChallengesTabWidget": unreal.RecoveredChallengeWidget,
    "ModifiersTabWidget": unreal.RecoveredModifierWidget,
}
items = {
    "SlowdownStoreItem": "Slowdown", "BonerPillStoreItem": "BonerPill",
    "BreakStoreItem": "Break", "DecreaseHeatLevel_StoreItem": "DecreaseHeat",
    "EdgeStoreItem": "Edge", "ResupplyStoreItem": "Resupply",
    "SuccuShieldStoreItem": "SuccuShield", "+XCumChance_StoreItem": "XCumChance",
}
parents.update({name: unreal.RecoveredStoreItemWidget for name in items})
report = []
for name, parent in parents.items():
    path = "/Game/Recovery/UI/" + name
    bp = unreal.load_asset(path)
    if not bp:
        raise RuntimeError("Missing widget: " + path)
    cls = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not cls:
        raise RuntimeError("Missing generated class: " + path)
    changed = False
    if not isinstance(unreal.get_default_object(cls), parent):
        unreal.BlueprintEditorLibrary.reparent_blueprint(bp, parent)
        unreal.BlueprintEditorLibrary.compile_blueprint(bp)
        cls = unreal.EditorAssetLibrary.load_blueprint_class(path)
        if not cls:
            raise RuntimeError("Missing generated class after reparent: " + path)
        changed = True
    if name in items:
        defaults = unreal.get_default_object(cls)
        if str(defaults.get_editor_property("item_id")) != items[name]:
            defaults.set_editor_property("item_id", items[name])
            changed = True
    if changed and not unreal.EditorAssetLibrary.save_loaded_asset(bp, only_if_is_dirty=False):
        raise RuntimeError("Save failed: " + path)
    report.append({"asset": path, "parent": parent.static_class().get_path_name(), "item_id": items.get(name)})
output = Path(unreal.Paths.project_dir()) / "Saved/patch-widget-integration.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("PATCH_WIDGET_INTEGRATION_SAVED " + str(len(report)))
