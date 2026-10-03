"""Read back persisted patch parents in a fresh editor process; no asset writes."""
import json
from pathlib import Path
import unreal
project=Path(unreal.Paths.project_dir())
expected=json.loads((project/'RecoveryEvidence/patch-widget-integration.json').read_text())
for item in expected:
    bp=unreal.load_asset(item['asset'])
    assert bp, item['asset']
    cls=unreal.EditorAssetLibrary.load_blueprint_class(item['asset'])
    assert cls, item['asset']
    expected_type=getattr(unreal,item['parent'].rsplit('.',1)[1])
    assert isinstance(unreal.get_default_object(cls),expected_type), item['asset']
    if item['item_id']:
        assert str(unreal.get_default_object(cls).get_editor_property('item_id'))==item['item_id'], item['asset']
(project/'Saved/patch-widget-readback.json').write_text(json.dumps({'verified_count':len(expected),'assets':expected},indent=2))
unreal.log('PATCH_WIDGET_READBACK_VERIFIED '+str(len(expected)))
