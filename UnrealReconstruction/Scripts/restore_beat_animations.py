from pathlib import Path
import json
import unreal
project=Path(unreal.Paths.project_dir())
source=project.parent/'decoded-widget-functions/UMG_BeatIcon-functions.json'
report=json.loads(unreal.RecoveredWidgetRecovery.restore_animation_data(str(source),'/Game/Recovery/UI/UMG_BeatIcon.UMG_BeatIcon'))
(project/'Saved/animation-restore-report.json').write_text(json.dumps(report,indent=2),encoding='utf8')
assert report.get('saved_assets'), report
assert report.get('animation_count')==3, report
unreal.log('ANIMATION_RESTORE_PASS: three editable animations saved')
