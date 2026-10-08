from pathlib import Path
import json
import unreal


path='/Game/Recovery/UI/PG2TabbedInventory_Widget'
bp=unreal.load_asset(path)
if not bp:
    raise RuntimeError('Missing recovered PG2 inventory widget')
cls=unreal.EditorAssetLibrary.load_blueprint_class(path)
if not cls:
    raise RuntimeError('Missing recovered PG2 inventory generated class')
changed=False
if not isinstance(unreal.get_default_object(cls),unreal.RecoveredPG2TabbedInventoryWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(bp,unreal.RecoveredPG2TabbedInventoryWidget)
    unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    cls=unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not cls or not isinstance(unreal.get_default_object(cls),unreal.RecoveredPG2TabbedInventoryWidget):
        raise RuntimeError('Recovered PG2 inventory parent verification failed')
    changed=True
if changed and not unreal.EditorAssetLibrary.save_loaded_asset(bp,only_if_is_dirty=False):
    raise RuntimeError('Could not save recovered PG2 inventory widget')
report={'asset':path,'parent':unreal.RecoveredPG2TabbedInventoryWidget.static_class().get_path_name(),'changed':changed}
output=Path(unreal.Paths.project_dir())/'Saved'/'pg2-inventory-reparent.json'
output.write_text(json.dumps(report,indent=2),encoding='utf-8')
unreal.log('RECOVERED_PG2_INVENTORY_PARENT '+json.dumps(report))
