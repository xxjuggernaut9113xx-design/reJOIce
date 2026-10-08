from pathlib import Path
import json
import unreal


path='/Game/Recovery/UI/RestWidget'
bp=unreal.load_asset(path)
if not bp:
    raise RuntimeError('Missing recovered RestWidget')
cls=unreal.EditorAssetLibrary.load_blueprint_class(path)
if not cls:
    raise RuntimeError('Missing recovered RestWidget generated class')
changed=False
if not isinstance(unreal.get_default_object(cls),unreal.RecoveredRestWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(bp,unreal.RecoveredRestWidget)
    unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    cls=unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not cls or not isinstance(unreal.get_default_object(cls),unreal.RecoveredRestWidget):
        raise RuntimeError('Recovered RestWidget parent verification failed')
    changed=True
if changed and not unreal.EditorAssetLibrary.save_loaded_asset(bp,only_if_is_dirty=False):
    raise RuntimeError('Could not save recovered RestWidget')
report={'asset':path,'parent':unreal.RecoveredRestWidget.static_class().get_path_name(),'changed':changed}
output=Path(unreal.Paths.project_dir())/'Saved'/'rest-widget-reparent.json'
output.write_text(json.dumps(report,indent=2),encoding='utf-8')
unreal.log('RECOVERED_REST_WIDGET_PARENT '+json.dumps(report))
