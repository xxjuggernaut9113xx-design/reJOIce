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

def values_with_op(value,op):
    if isinstance(value,dict):
        if value.get('op')==op:
            yield value
        for child in value.values():
            yield from values_with_op(child,op)
    elif isinstance(value,list):
        for child in value:
            yield from values_with_op(child,op)

def entrypoint(filename):
    payload=json.loads((ui_manager/filename).read_text(encoding='utf-8'))
    values=[node['Value'] for node in values_with_op(payload,'EX_IntConst')]
    if len(values)!=1:
        raise RuntimeError(f'Expected one entry point in {filename}, found {values}')
    return values[0]

events={
    'One':'InpActEvt_One_K2Node_InputKeyEvent_7.json',
    'Two':'InpActEvt_Two_K2Node_InputKeyEvent_6.json',
    'Three':'InpActEvt_Three_K2Node_InputKeyEvent_4.json',
    'Q':'InpActEvt_Q_K2Node_InputKeyEvent_8.json',
    'Tab':'InpActEvt_Tab_K2Node_InputKeyEvent_9.json',
}
entrypoints={key:entrypoint(filename) for key,filename in events.items()}
expected_entrypoints={'One':13463,'Two':12735,'Three':11131,'Q':13672,'Tab':13677}
if entrypoints!=expected_entrypoints:
    raise RuntimeError(f'Unexpected UI_Manager input event entries: {entrypoints}')

graph=json.loads(graph_path.read_text(encoding='utf-8'))['statements']
offset=0
statements={}
for statement in graph:
    statements[offset]=statement
    offset+=expression_size(statement)

def call_at(offset):
    statement=statements.get(offset)
    if not statement:
        raise RuntimeError(f'No UI_Manager statement at {offset}')
    while statement.get('op')=='EX_Context':
        statement=statement['ContextExpression']
    return statement.get('StackNode',statement.get('VirtualFunctionName'))

expected_calls={
    11131:None,
    11266:'TabbedInventoryResupplyTrigger',
    11341:'TabbedInventoryEdgeTrigger',
    12735:None,
    12870:'ToggleSuccuShields',
    12945:'UseReduceHeatItem',
    12986:'PlaySound2D',
    13181:None,
    13223:'TriggerInventorySwitchAnimation',
    13303:'SetFocusToGameViewport',
    13336:None,
    13378:'TriggerInventorySwitchAnimation',
    13463:None,
    13598:'UseBonerPillItem',
    13635:'UseCumChanceItem',
}
for statement_offset,expected_call in expected_calls.items():
    actual=call_at(statement_offset)
    if expected_call is not None and actual!=expected_call:
        raise RuntimeError(f'UI_Manager call at {statement_offset} changed: {actual!r}')

widgets_root=analysis/'decoded-ui'/'CockHero'/'Content'/'Widgets'
animation_names={}
for widget,expected_animation in {
    'PG1TabbedInventory_Widget':'SwitchInventoryTabAnimation',
    'PG2TabbedInventory_Widget':'SwitchTabAnimation',
}.items():
    asset=json.loads((widgets_root/f'{widget}.json').read_text(encoding='utf-8'))
    names=set(asset['NameMap'])
    if 'TriggerInventorySwitchAnimation' not in names or expected_animation not in names:
        raise RuntimeError(f'Expected tab switch symbols are missing from {widget}')
    animation_names[widget]=expected_animation

audio_report_path=project/'RecoveryEvidence'/'inventory-switch-audio-recovery.json'
audio=json.loads(audio_report_path.read_text(encoding='utf-8'))
if audio['original']!='/Game/SoundFX/swapitem.swapitem' or not audio.get('decoded',{}).get('success'):
    raise RuntimeError('Inventory switch audio was not decoded from the source cue')
if not (project/'Content'/'Recovery'/'Resources'/'Audio'/'swapitem.uasset').is_file():
    raise RuntimeError('Recovered inventory switch sound asset is missing')

report={
    'source_executed':False,
    'sources':{
        'ui_manager_graph':str(graph_path),
        'ui_manager_graph_sha256':hashlib.sha256(graph_path.read_bytes()).hexdigest(),
        'pg1_widget':str(widgets_root/'PG1TabbedInventory_Widget.json'),
        'pg2_widget':str(widgets_root/'PG2TabbedInventory_Widget.json'),
    },
    'entrypoints':entrypoints,
    'inventory_key_dispatch':{
        'One':{'tab_0':'UseCumChanceItem','tab_1':'UseBonerPillItem'},
        'Two':{'tab_0':'UseReduceHeatItem','tab_1':'ToggleSuccuShields','tab_1_dialogue':12},
        'Three':{'tab_0':'TabbedInventoryEdgeTrigger','tab_1':'TabbedInventoryResupplyTrigger','tab_1_dialogue':12},
    },
    'tab_switch':{
        'keys':['Q','Tab'],
        'shared_route_offset':12986,
        'sound':{
            'source':'/Game/SoundFX/swapitem.swapitem',
            'volume_multiplier':0.25,
            'pitch_multiplier':0.7,
            'ui_sound':True,
        },
        'routes':{
            'tab_0_to_1':{'next_tab':1,'widget':'PG2TabbedInventory_Widget','animation':animation_names['PG2TabbedInventory_Widget'],'source_animation_function':'TriggerInventorySwitchAnimation'},
            'tab_1_to_0':{'next_tab':0,'widget':'PG1TabbedInventory_Widget','animation':animation_names['PG1TabbedInventory_Widget'],'source_animation_function':'TriggerInventorySwitchAnimation'},
        },
        'focus':'SetFocusToGameViewport',
        'invalid_tab_preserves_state':True,
    },
    'audio':audio,
    'runtime_mapping':{
        'implementation':'URecoveredSessionWidget::SwitchInventoryTabs',
        'state_helper':'URecoveredSessionWidget::GetSwitchedInventoryTab',
        'sound_asset':'/Game/Recovery/Resources/Audio/swapitem.swapitem',
    },
}
(project/'RecoveryEvidence'/'input-control-parity-recovery.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
