from pathlib import Path
import json
import unreal

project=Path(unreal.Paths.project_dir())
report_path=project/'RecoveryEvidence'/'inventory-switch-audio-recovery.json'
report=json.loads(report_path.read_text(encoding='utf-8'))
decoded=report.get('decoded')
if not decoded or not decoded.get('success'):
    raise RuntimeError('Decoded inventory-switch audio evidence is unavailable')
task=unreal.AssetImportTask()
task.filename=decoded['file']
task.destination_path='/Game/Recovery/Resources/Audio'
task.automated=True
task.replace_existing=True
task.save=True
unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
asset_path='/Game/Recovery/Resources/Audio/swapitem.swapitem'
sound=unreal.load_asset(asset_path)
if not isinstance(sound,unreal.SoundWave):
    raise RuntimeError('Recovered inventory switch sound import failed: '+str(task.imported_object_paths))
if sound.get_editor_property('num_channels')!=report['channels']:
    raise RuntimeError('Recovered inventory switch sound channel count differs from source')
aliases_path=project/'RecoveryEvidence'/'resource-aliases.json'
aliases=json.loads(aliases_path.read_text(encoding='utf-8'))
aliases[report['original']]=asset_path
aliases_path.write_text(json.dumps(aliases,indent=2),encoding='utf-8')
result={'imported':asset_path,'source_pcm_preserved':True,'sample_rate':report['sample_rate'],'channels':report['channels'],'frames':report['frames']}
(project/'Saved'/'inventory-switch-audio-import-report.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
unreal.log('RECOVERED_INVENTORY_SWITCH_AUDIO_IMPORTED '+asset_path)
