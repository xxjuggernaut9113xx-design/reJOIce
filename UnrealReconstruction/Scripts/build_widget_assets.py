"""Create editable widget trees from byte-verified evidence, retaining an honest gap report."""
from pathlib import Path
import json
import unreal
project=Path(unreal.Paths.project_dir())
report=json.loads(unreal.RecoveredWidgetRecovery.build_widget_assets(str(project/'RecoveryEvidence/ui-layout-values.json')))
(project/'Saved/widget-recovery-report.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
assert not report['errors'],report['errors']
evidence=json.loads((project/'RecoveryEvidence/ui-layout-values.json').read_text(encoding='utf-8'))
expected={record['asset'] for record in evidence['widgets']}
assert len(report['assets'])==len(expected),(len(report['assets']),len(expected))
unreal.log('RECOVERED_WIDGET_TREES_VERIFIED '+str(len(report['assets'])))
