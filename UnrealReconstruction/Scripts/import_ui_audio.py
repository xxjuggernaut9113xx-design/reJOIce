from pathlib import Path
import json
import unreal

project=Path(unreal.Paths.project_dir())
rows=json.loads((project/'RecoveryEvidence/audio-decoding-report.json').read_text(encoding='utf-8'))
alias_file=project/'RecoveryEvidence/resource-aliases.json'
aliases=json.loads(alias_file.read_text(encoding='utf-8'))
imported=[]
for row in rows:
    task=unreal.AssetImportTask()
    task.filename=row['decoded']['file']
    task.destination_path='/Game/Recovery/Resources/Audio'
    task.automated=True
    task.replace_existing=True
    task.save=True
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
    path='/Game/Recovery/Resources/Audio/'+row['name']+'.'+row['name']
    sound=unreal.load_asset(path)
    assert isinstance(sound,unreal.SoundWave),(path,task.imported_object_paths)
    assert sound.get_editor_property('num_channels')==row['channels'],row
    aliases[row['original']]=path
    imported.append(path)
alias_file.write_text(json.dumps(aliases,indent=2),encoding='utf-8')
(project/'Saved/audio-import-report.json').write_text(json.dumps({'imported':imported,'source_pcm_preserved':True,'original_sound_settings_restored':False},indent=2),encoding='utf-8')
unreal.log('RECOVERED_EDITABLE_UI_SOUNDS '+str(len(imported)))
