from pathlib import Path
import json
import unreal

path = "/Game/Recovery/UI/FileEntry"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing recovered FileEntry widget")

widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing recovered FileEntry generated class")

changed = False
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredImportFileEntryWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredImportFileEntryWidget)
    unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredImportFileEntryWidget):
        raise RuntimeError("Recovered FileEntry parent verification failed")
    changed = True

if changed and not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Could not save recovered FileEntry widget")

report = {
    "asset": path,
    "parent": unreal.RecoveredImportFileEntryWidget.static_class().get_path_name(),
    "changed": changed,
}
output = Path(unreal.Paths.project_dir()) / "Saved" / "import-file-entry-reparent.json"
output.write_text(json.dumps(report, indent=2), encoding="utf-8")
unreal.log("RECOVERED_IMPORT_FILE_ENTRY_PARENT " + json.dumps(report))