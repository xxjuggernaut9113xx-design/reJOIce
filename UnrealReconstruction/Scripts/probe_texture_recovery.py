from pathlib import Path
import json
import unreal
project=Path(unreal.Paths.project_dir())
source=project.parent/'cooked-ui/CockHero/Content'
result=json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(source),'UI/SettingsIcon'))
(project/'Saved/texture-probe.json').write_text(json.dumps(result,indent=2),encoding='utf-8')
assert result['success'],result
unreal.log('RECOVERED_TEXTURE_MIP '+result['format']+' '+str(result['width'])+'x'+str(result['height']))
