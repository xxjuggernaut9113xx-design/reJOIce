"""Verify the four unrestricted settings tab paths against decoded instructions."""
from pathlib import Path
import ast
import hashlib
import json

root=Path(__file__).resolve().parents[1]
source=(root/'trace_difficulty.py').read_text(encoding='utf8')
node=next(n for n in ast.parse(source).body if isinstance(n,ast.FunctionDef) and n.name=='size')
namespace={};exec(ast.get_source_segment(source,node),namespace);size=namespace['size']
raw_path=root/'decoded-widget-functions/SettingsMenuWidget-functions.json'
raw=json.loads(raw_path.read_text(encoding='utf8'))
original=next(e for e in raw['Exports'] if e['ObjectName']=='ExecuteUbergraph_SettingsMenuWidget')
code=json.loads((root/'widget-functions/SettingsMenuWidget/ExecuteUbergraph_SettingsMenuWidget.json').read_text(encoding='utf8'))['statements']
offsets={};offset=0
for statement in code:
    offsets[offset]=statement;offset+=size(statement)
assert offset==original['ScriptBytecodeSize']
routes=[]
for button,entry in [('VideoSettingsButton',213),('AudioSettingsButton',500),('TagsSettingsButton',1380),('VoiceSettingsButton',1667)]:
    calls=[];visited=[];current=entry
    while True:
        assert current not in visited
        visited.append(current);statement=offsets[current]
        if statement['op']=='EX_Return':break
        if statement['op']=='EX_Jump':current=statement['CodeOffset'];continue
        assert statement['op']=='EX_Context',statement
        receiver=statement['ObjectExpression']['Variable']['field']
        call=statement['ContextExpression'];name=call.get('StackNode',call.get('VirtualFunctionName'))
        parameters=call['Parameters'];item={'receiver':receiver,'name':name}
        if name=='SetActiveWidgetIndex':item['index']=parameters[0]['Value']
        if name=='SetStyle':item['style']=parameters[0]['Variable']['field']
        calls.append(item);current+=size(statement)
    indices=[x['index'] for x in calls if x['name']=='SetActiveWidgetIndex'];assert len(indices)==1
    clicked=[x['receiver'] for x in calls if x.get('style')=='Clicked Style'];assert clicked==[button]
    wrappers=[e for e in raw['Exports'] if 'OnButtonClickedEvent' in e['ObjectName'] and e.get('ScriptBytecode') and e['ScriptBytecode'][0].get('Parameters',[{}])[0].get('Value')==entry]
    assert len(wrappers)==1
    routes.append({'button':button,'entry':entry,'wrapper':wrappers[0]['ObjectName'],'active_index':indices[0],'offsets':visited,'calls':calls})
assert [x['active_index'] for x in routes]==[0,4,2,3]
report={'original_executed':False,'source_sha256':hashlib.sha256(raw_path.read_bytes()).hexdigest(),'routes':routes,'all_settings_controls_complete':False,'background_media_consumer_complete':False}
(root/'UnrealReconstruction/RecoveryEvidence/settings-navigation-traces.json').write_text(json.dumps(report,indent=2),encoding='utf8')
print('Verified four settings tab handlers, styles and preview-stop ordering')
