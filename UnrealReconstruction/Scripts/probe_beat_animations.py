from pathlib import Path
import json
import unreal
project=Path(unreal.Paths.project_dir())
source=project.parent/'decoded-widget-functions/UMG_BeatIcon-functions.json'
report=json.loads(unreal.RecoveredWidgetRecovery.probe_animation_data(str(source)))
(project/'Saved/animation-probe-report.json').write_text(json.dumps(report,indent=2),encoding='utf8')
decoded=sum(item['decoded'] for item in report.get('objects',[]))
unreal.log(f'ANIMATION_NATIVE_PROBE: {decoded}/{len(report.get("objects",[]))} exact payload lengths; no assets saved')
