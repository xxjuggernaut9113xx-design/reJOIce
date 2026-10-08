from pathlib import Path
import json
import unreal

path='/Game/NewSetup/BP_EdgeManager'
bp=unreal.load_asset(path)
if not bp:
    raise RuntimeError('Missing recovered edge manager blueprint')
cls=unreal.EditorAssetLibrary.load_blueprint_class(path)
if not cls:
    raise RuntimeError('Missing recovered edge manager generated class')
changed=False
if not isinstance(unreal.get_default_object(cls),unreal.RecoveredEdgeManager):
    unreal.BlueprintEditorLibrary.reparent_blueprint(bp,unreal.RecoveredEdgeManager)
    unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    cls=unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not cls or not isinstance(unreal.get_default_object(cls),unreal.RecoveredEdgeManager):
        raise RuntimeError('Recovered edge manager parent verification failed')
    changed=True
if changed and not unreal.EditorAssetLibrary.save_loaded_asset(bp,only_if_is_dirty=False):
    raise RuntimeError('Could not save recovered edge manager blueprint')
report={'asset':path,'parent':unreal.RecoveredEdgeManager.static_class().get_path_name(),'changed':changed}
output=Path(unreal.Paths.project_dir())/'Saved'/'edge-manager-reparent.json'
output.write_text(json.dumps(report,indent=2),encoding='utf-8')
unreal.log('RECOVERED_EDGE_MANAGER_PARENT '+json.dumps(report))
