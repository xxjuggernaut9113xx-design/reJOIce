from pathlib import Path
import json
import hashlib
import shutil
import unreal

project=Path(unreal.Paths.project_dir())
root=project.parent
source=root/'pak-files/Engine/Content/EngineFonts/horizon.ufont'
payload=project/'RecoveryEvidence/FontSource/horizon.otf'
payload.parent.mkdir(parents=True,exist_ok=True)
shutil.copyfile(source,payload)
assert source.read_bytes()==payload.read_bytes()
result=json.loads(unreal.RecoveredTextureRecovery.recover_horizon_font(str(project/'RecoveryEvidence/font-values.json'),str(payload)))
result['payload_sha256']=hashlib.sha256(payload.read_bytes()).hexdigest()
(project/'RecoveryEvidence/font-recovery-report.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
assert result['success'],result
alias_file=project/'RecoveryEvidence/resource-aliases.json'
aliases=json.loads(alias_file.read_text(encoding='utf-8'))
aliases['/Engine/EngineFonts/horizon_Font.horizon_Font']=result['font']
aliases['/Engine/EngineFonts/horizon.horizon']=result['face']
alias_file.write_text(json.dumps(aliases,indent=2),encoding='utf-8')
unreal.log('RECOVERED_HORIZON_FONT '+str(result['payload_bytes']))
