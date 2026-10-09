from pathlib import Path
import json
import unreal

project=Path(unreal.Paths.project_dir())
path=project/'RecoveryEvidence'/'inventory-switch-audio-recovery.json'
report=json.loads(path.read_text(encoding='utf-8'))
decoded=json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(report['encoded'],report['name']))
if not decoded['success']:
    raise RuntimeError(decoded)
for field in ('sample_rate','channels','frames'):
    if decoded[field]!=report[field]:
        raise RuntimeError(field+' did not match recovered Bink metadata')
report['decoded']=decoded
path.write_text(json.dumps(report,indent=2),encoding='utf-8')
unreal.log('RECOVERED_INVENTORY_SWITCH_AUDIO_DECODED '+decoded['file'])
