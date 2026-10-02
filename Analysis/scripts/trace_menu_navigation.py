"""Trace selected original menu navigation paths; never run the shipping game."""
from pathlib import Path
import ast
import hashlib
import json

root = Path(__file__).resolve().parents[1]
source = (root / 'trace_difficulty.py').read_text(encoding='utf8')
node = next(n for n in ast.parse(source).body if isinstance(n, ast.FunctionDef) and n.name == 'size')
namespace = {}
exec(ast.get_source_segment(source, node), namespace)
size = namespace['size']
raw_path = root / 'decoded/MainMenu-functions.json'
raw = json.loads(raw_path.read_text(encoding='utf8'))
code = json.loads((root / 'blueprint-functions/MainMenu/ExecuteUbergraph_MainMenu.json').read_text(encoding='utf8'))['statements']
offsets = {}
offset = 0
for statement in code:
    offsets[offset] = statement
    offset += size(statement)
native = next(e for e in raw['Exports'] if e['ObjectName'] == 'ExecuteUbergraph_MainMenu')
assert offset == native['ScriptBytecodeSize'], (offset, native['ScriptBytecodeSize'])

def walk(value):
    if isinstance(value, dict):
        yield value
        for child in value.values():
            yield from walk(child)
    elif isinstance(value, list):
        for child in value:
            yield from walk(child)

def trace(entry, cast_success=True):
    events = []
    visited = []
    for _ in range(200):
        statement = offsets[entry]
        visited.append(entry)
        op = statement['op']
        if op in ('EX_PopExecutionFlow', 'EX_Return'):
            return {'offsets': visited, 'calls': events}
        if op == 'EX_Jump':
            entry = statement['CodeOffset']
            continue
        if op == 'EX_PopExecutionFlowIfNot':
            assert statement['BooleanExpression']['Variable']['field'].startswith('K2Node_DynamicCast_bSuccess')
            if not cast_success:
                return {'offsets': visited, 'calls': events}
        elif op.startswith('EX_Jump'):
            raise ValueError(('Unsupported branch', statement))
        for item in walk(statement):
            name = item.get('StackNode', item.get('VirtualFunctionName'))
            if name:
                event = {'name': name}
                if name == 'Create':
                    index = item['Parameters'][1]['Value']
                    assert index < 0
                    event['class'] = raw['Imports'][-index - 1]['ObjectName']
                if name == 'AddToViewport':
                    event['z_order'] = item['Parameters'][0]['Value']
                events.append(event)
        entry += size(statement)
    raise RuntimeError('Menu trace did not terminate')

routes = []
for button, target, entry in [
    ('StartGameButton', 'DifficultySelectScreen_Widget_C', 2359),
    ('StatsButton', 'ChallengesMenuWidget_C', 1700),
    ('Settings', 'SettingsMenuWidget_C', 1838),
    ('UnlockStoreButton', 'UnlockStoreWidget_C', 2221),
]:
    wrappers = [e for e in raw['Exports'] if e['ObjectName'].startswith('BndEvt__MainMenu_' + button + '_') and 'OnButtonClickedEvent' in e['ObjectName']]
    assert len(wrappers) == 1, button
    wrapper = wrappers[0]
    assert wrapper['ScriptBytecode'][0]['Parameters'][0]['Value'] == entry
    result = trace(entry)
    assert [call['class'] for call in result['calls'] if call['name'] == 'Create'] == [target]
    assert [call['z_order'] for call in result['calls'] if call['name'] == 'AddToViewport'] == [0]
    assert not any(call['name'] == 'RemoveFromParent' for call in result['calls'])
    routes.append({'button': button, 'target': target, 'entry': entry, **result})
failed_start = trace(2359, False)
assert not any(call['name'] == 'Create' for call in failed_start['calls'])
report = {'source_sha256': hashlib.sha256(raw_path.read_bytes()).hexdigest(),
          'original_executed': False, 'routes': routes,
          'start_cast_failure': failed_start, 'animation_parity': False,
          'session_startup_complete': False}
destination = root / 'UnrealReconstruction/RecoveryEvidence/menu-navigation-traces.json'
destination.write_text(json.dumps(report, indent=2), encoding='utf8')
print('Verified four original menu routes and the failed game-mode cast branch')
