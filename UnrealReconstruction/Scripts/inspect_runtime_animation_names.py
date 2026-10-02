from pathlib import Path
import unreal,json
project=Path(unreal.Paths.project_dir())
result={}
for name in ['UMG_BeatIcon','MainMenu','AssFrenzyWidget']:
    bp=unreal.load_asset(f'/Game/Recovery/UI/{name}')
    result[name]=[a.get_name() for a in bp.get_editor_property('animations')]
(project/'Saved/runtime-animation-names.json').write_text(json.dumps(result,indent=2))
