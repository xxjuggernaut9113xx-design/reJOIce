from pathlib import Path
import json
import unreal

project=Path(unreal.Paths.project_dir())
rows=json.loads((project/'RecoveryEvidence/audio-stream-catalog.json').read_text(encoding='utf-8'))
for row in rows:
    row['decoded']=json.loads(unreal.RecoveredAudioRecovery.decode_bink_audio(row['encoded'],row['name']))
    assert row['decoded']['success'],row
    for field in ('sample_rate','channels','frames'):assert row['decoded'][field]==row[field],(field,row)
(project/'RecoveryEvidence/audio-decoding-report.json').write_text(json.dumps(rows,indent=2),encoding='utf-8')
unreal.log('RECOVERED_UI_AUDIO '+str(len(rows)))
