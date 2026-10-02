from pathlib import Path
import json
import unreal
project=Path(unreal.Paths.project_dir())
catalog=json.loads((project/'RecoveryEvidence/animation-source-catalog.json').read_text())
reports={}
for name,entry in catalog.items():
    report=json.loads(unreal.RecoveredWidgetRecovery.restore_animation_data(entry['source'],f'/Game/Recovery/UI/{name}.{name}'))
    reports[name]=report
    (project/'Saved/all-animation-restore-report.json').write_text(json.dumps(reports,indent=2),encoding='utf8')
    unreal.log(f'ANIMATION_RESTORE {name}: saved={report.get("saved_assets")}, count={report.get("animation_count",0)}')
    unreal.SystemLibrary.collect_garbage()
unreal.log('ALL_ANIMATION_RESTORE_COMPLETE')
