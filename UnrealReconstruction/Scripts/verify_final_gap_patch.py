"""Read-only class-attachment inventory for the final supplied patch."""
import json
from pathlib import Path
import unreal
project=Path(unreal.Paths.project_dir())
types=[unreal.RecoveredChallengeWidget,unreal.RecoveredModifierWidget,unreal.RecoveredImportWidget,unreal.RecoveredCheatWidget,unreal.RecoveredSaveSlotWidget]
rows=[]
for path in sorted((project/'Content/Recovery/UI').rglob('*.uasset')):
    package='/Game/'+path.relative_to(project/'Content').with_suffix('').as_posix()
    cls=unreal.EditorAssetLibrary.load_blueprint_class(package)
    if cls:
        default=unreal.get_default_object(cls)
        rows.append({'asset':package,'new_native_types':[t.__name__ for t in types if isinstance(default,t)]})
result={'assets':rows,'new_types_attached':{t.__name__:sum(t.__name__ in r['new_native_types'] for r in rows) for t in types},'asset_writes':False}
(project/'Saved/final-gap-widget-attachments.json').write_text(json.dumps(result,indent=2))
unreal.log('FINAL_GAP_ATTACHMENTS '+json.dumps(result['new_types_attached']))
