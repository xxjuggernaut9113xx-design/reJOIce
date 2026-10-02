from pathlib import Path
import json
import unreal
project=Path(unreal.Paths.project_dir())
catalog=json.loads((project/'RecoveryEvidence/animation-source-catalog.json').read_text())
reports={}
for name,entry in catalog.items():
    report=json.loads(unreal.RecoveredWidgetRecovery.probe_animation_data(entry['source']))
    reports[name]=report
    (project/'Saved/all-animation-probe-report.json').write_text(json.dumps(reports,indent=2),encoding='utf8')
    bad=[item for item in report.get('objects',[]) if not item['decoded']]
    unreal.log(f'ANIMATION_PROBE {name}: {len(report.get("objects",[]))} objects, {len(bad)} failures')
    unreal.SystemLibrary.collect_garbage()
unreal.log('ALL_ANIMATION_PROBE_COMPLETE')
