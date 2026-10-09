import ast
import hashlib
import json
from pathlib import Path

analysis=Path(r'C:\Users\webma\analysis\cockhero-v004')
project=Path(__file__).resolve().parents[1]
ui_manager=analysis/'blueprint-functions'/'UI_Manager'
graph_path=ui_manager/'ExecuteUbergraph_UI_Manager.json'

source=(analysis/'trace_difficulty.py').read_text(encoding='utf-8')
tree=ast.parse(source)
size_node=next(node for node in tree.body if isinstance(node,ast.FunctionDef) and node.name=='size')
namespace={}
exec(ast.get_source_segment(source,size_node),namespace)
expression_size=namespace['size']

def integer_constants(value):
    if isinstance(value,dict):
        if value.get('op')=='EX_IntConst':
            yield value['Value']
        for child in value.values():
            yield from integer_constants(child)
    elif isinstance(value,list):
        for child in value:
            yield from integer_constants(child)

def entrypoint(filename):
    payload=json.loads((ui_manager/filename).read_text(encoding='utf-8'))
    values=list(integer_constants(payload))
    if len(values)!=1:
        raise RuntimeError(f'Expected one entry point in {filename}, found {values}')
    return values[0]

entries={
    'Escape':entrypoint('InpActEvt_Escape_K2Node_InputKeyEvent_10.json'),
    'ToggleSettingsMenu':entrypoint('ToggleSettingsMenu.json'),
    'ResumeButton':entrypoint('BndEvt__UI_Manager_ResumeButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature.json'),
    'SettingsMenuButton':entrypoint('BndEvt__UI_Manager_SettingsMenuButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature.json'),
}
expected_entries={'Escape':13976,'ToggleSettingsMenu':13981,'ResumeButton':13986,'SettingsMenuButton':12730}
if entries!=expected_entries:
    raise RuntimeError(f'Unexpected settings-menu entry points: {entries}')

offset=0
statements={}
for statement in json.loads(graph_path.read_text(encoding='utf-8'))['statements']:
    statements[offset]=statement
    offset+=expression_size(statement)

def context_expression(statement):
    while statement.get('op')=='EX_Context':
        statement=statement['ContextExpression']
    return statement

def expect_jump(statement_offset,target):
    statement=statements[statement_offset]
    if statement.get('op')!='EX_Jump' or statement.get('CodeOffset')!=target:
        raise RuntimeError(f'Expected jump {statement_offset}->{target}, found {statement}')

expect_jump(12730,2414)
expect_jump(13976,2414)
expect_jump(13981,2414)
resume_call=context_expression(statements[13986])
if resume_call.get('VirtualFunctionName')!='ToggleSettingsMenu':
    raise RuntimeError(f'Unexpected resume-button call: {resume_call}')

def visibility_value(statement_offset):
    statement=context_expression(statements[statement_offset])
    if statement.get('VirtualFunctionName')!='SetVisibility':
        raise RuntimeError(f'Expected SetVisibility at {statement_offset}')
    return statement['Parameters'][0]['Value']

if visibility_value(2476)!=0 or visibility_value(2862)!=0:
    raise RuntimeError('Source menu-open visibility does not use Visible')
if visibility_value(3036)!=1 or visibility_value(3422)!=1:
    raise RuntimeError('Source menu-close visibility does not use Collapsed')

def sound_parameters(statement_offset):
    statement=context_expression(statements[statement_offset])
    if statement.get('StackNode')!='PlaySound2D':
        raise RuntimeError(f'Expected PlaySound2D at {statement_offset}')
    return statement['Parameters']

open_sound=sound_parameters(2975)
close_sound=sound_parameters(3535)
if open_sound[1].get('Value')!=-327 or close_sound[1].get('Value')!=-327:
    raise RuntimeError('Source settings menu sound reference changed')
if open_sound[2].get('Value')!=0.20000000298023224 or close_sound[2].get('Value')!=0.20000000298023224:
    raise RuntimeError('Source settings menu volume changed')
if open_sound[3].get('Value')!=4.0 or close_sound[3].get('Value')!=1.0:
    raise RuntimeError('Source settings menu pitch changed')

decoded=json.loads((analysis/'decoded'/'UI_Manager-functions.json').read_text(encoding='utf-8'))
sound_import=decoded['Imports'][326]
sound_package=decoded['Imports'][-sound_import['OuterIndex']-1]
if sound_import['ObjectName']!='VR_ungrab' or sound_package['ObjectName']!='/Engine/VREditor/Sounds/VR_ungrab':
    raise RuntimeError('Source settings-menu sound asset changed')

report={
    'source_executed':False,
    'sources':{
        'ui_manager_graph':str(graph_path),
        'ui_manager_graph_sha256':hashlib.sha256(graph_path.read_bytes()).hexdigest(),
        'ui_manager_function_package':str(analysis/'decoded'/'UI_Manager-functions.json'),
    },
    'entrypoints':entries,
    'shared_toggle_entry':2414,
    'open':{
        'border_visibility':'Visible',
        'direct_children_visibility':'Visible',
        'sound':'/Engine/VREditor/Sounds/VR_ungrab.VR_ungrab',
        'volume_multiplier':0.2,
        'pitch_multiplier':4.0,
        'show_mouse_cursor':True,
    },
    'close':{
        'border_visibility':'Collapsed',
        'direct_children_visibility':'Collapsed',
        'sound':'/Engine/VREditor/Sounds/VR_ungrab.VR_ungrab',
        'volume_multiplier':0.2,
        'pitch_multiplier':1.0,
        'show_mouse_cursor':True,
    },
    'runtime_mapping':{
        'toggle':'URecoveredSessionWidget::ToggleRecoveredSettingsMenu',
        'open':'URecoveredSessionWidget::PauseSession',
        'close':'URecoveredSessionWidget::ResumeSession',
        'buttons':['ResumeButton','SettingsMenuButton'],
    },
}
(project/'RecoveryEvidence'/'settings-menu-input-recovery.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
