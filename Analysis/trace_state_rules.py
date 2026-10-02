"""Strict static evaluation of selected numeric Kismet rules.
UI, logging and hardware calls are explicitly modeled as external effects.
Never executes the original game.
"""
from pathlib import Path
import ast
import hashlib
import itertools
import json
import math
import re
import copy
import struct

ROOT = Path(__file__).parent
source = (ROOT / 'trace_difficulty.py').read_text(encoding='utf-8')
tree = ast.parse(source)
size_source = ast.get_source_segment(source, next(n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name == 'size'))
namespace = {}
exec(compile(size_source, 'verified_instruction_size', 'exec'), namespace)
size = namespace['size']
exports = {e['ObjectName']: e for e in json.loads((ROOT / 'decoded/BP_GlobalManager-functions.json').read_text())['Exports']}

def clean(name):
    return re.sub(r'_\d+_[A-Fa-f0-9]{32}$', '', name)

def reference(n):
    op = n['op']
    if op in ('EX_InstanceVariable', 'EX_LocalVariable', 'EX_LocalOutVariable'):
        return clean(n['Variable']['field'])
    if op == 'EX_StructMemberContext':
        return reference(n['StructExpression']) + '.' + clean(n['StructMemberExpression']['field'])
    if op == 'EX_Context' and n['ContextExpression']['op'] == 'EX_InstanceVariable':
        return reference(n['ObjectExpression']) + '.' + reference(n['ContextExpression'])
    raise ValueError(('Unsupported reference', n))

def wrap(value):
    return ((value + 2**31) % 2**32) - 2**31

def evaluate(name, inputs, prefix=None, modeled_calls=(), owner='BP_GlobalManager', start_index=0):
    path = ROOT / 'blueprint-functions' / owner / (name + '.json')
    data = json.loads(path.read_text())
    code = data['statements']
    offsets = []
    offset = 0
    for n in code:
        offsets.append(offset)
        offset += size(n)
    owner_exports = exports if owner == 'BP_GlobalManager' else {e['ObjectName']:e for e in json.loads((ROOT / 'decoded' / (owner+'-functions.json')).read_text())['Exports']}
    assert offset == owner_exports[data['function']['name']]['ScriptBytecodeSize'], name
    byoffset = {v: i for i, v in enumerate(offsets)}
    for n in code:
        if n['op'] in ('EX_Jump', 'EX_JumpIfNot'):
            assert n['CodeOffset'] in byoffset
    state = copy.deepcopy(inputs)
    effects = []
    visited = []
    writes = {}
    flow = []
    injected = {k[len('call:'):]: v for k, v in inputs.items() if k.startswith('call:')}
    out_injected = {k[len('outcall:'):]: v for k, v in inputs.items() if k.startswith('outcall:')}
    functions = {
        'NotEqual_ByteByte': lambda a,b: a != b,
        'EqualEqual_ByteByte': lambda a,b: a == b,
        'EqualEqual_IntInt': lambda a,b: a == b,
        'BooleanAND': lambda a,b: a and b,
        'GreaterEqual_IntInt': lambda a,b: a >= b,
        'GreaterEqual_DoubleDouble': lambda a,b: a >= b,
        'LessEqual_DoubleDouble': lambda a,b: a <= b,
        'LessEqual_IntInt': lambda a,b: a <= b,
        'Less_IntInt': lambda a,b: a < b,
        'Greater_IntInt': lambda a,b: a > b,
        'Array_Length': len,
        'InRange_FloatFloat': lambda v,a,b,inc_a,inc_b: (v >= a if inc_a else v > a) and (v <= b if inc_b else v < b),
        'Subtract_IntInt': lambda a,b: wrap(a-b),
        'Divide_IntInt': lambda a,b: 0 if b == 0 else math.trunc(a/b),
        'InRange_IntInt': lambda v,a,b,inc_a,inc_b: (v >= a if inc_a else v > a) and (v <= b if inc_b else v < b),
        'Add_IntInt': lambda a,b: wrap(a+b),
        'Add_DoubleDouble': lambda a,b: a+b,
        'Subtract_DoubleDouble': lambda a,b: a-b,
        'Multiply_DoubleDouble': lambda a,b: a*b,
        'Divide_DoubleDouble': lambda a,b: 0.0 if b == 0 else a/b,
        'Conv_IntToDouble': float,
        'Conv_IntToString': str,
        'Concat_StrStr': lambda a,b: a+b,
        'Conv_IntToInt64': int,
        'FTrunc': math.trunc,
        'FClamp': lambda v,a,b: min(max(v,a),b),
    }
    def value(n):
        op = n['op']
        if op == 'EX_TextConst' and n['Value']['TextLiteralType'] == 'Empty':
            return {'flags':0, 'history':'None', 'text':''}
        if op == 'EX_StructConst':
            asset = json.loads((ROOT / 'decoded' / (owner+'-functions.json')).read_text())
            index = n['Struct']
            struct_name = (asset['Exports'] if index > 0 else asset['Imports'])[index-1 if index > 0 else -index-1]['ObjectName']
            if struct_name=='LatentActionInfo':
                assert len(n['Value'])==4
                return dict(zip(['Linkage','UUID','ExecutionFunction','CallbackTarget'],[value(v) for v in n['Value']]))
            schema = next(c for c in json.loads((ROOT / 'blueprint-class-fields.json').read_text())['classes'] if c['class'] == struct_name)
            assert len(schema['properties']) == len(n['Value'])
            return {clean(p['name']):value(v) for p,v in zip(schema['properties'], n['Value'])}
        if op in ('EX_InstanceVariable', 'EX_LocalVariable', 'EX_LocalOutVariable', 'EX_StructMemberContext'):
            key = reference(n)
            if key not in state and op == 'EX_StructMemberContext':
                return value(n['StructExpression'])[clean(n['StructMemberExpression']['field'])]
            assert key in state, ('Missing input', name, key)
            return state[key]
        if op == 'EX_PrimitiveCast' and n['ConversionType'] in (3,4):
            operand=value(n['Target'])
            return struct.unpack('<f',struct.pack('<f',operand))[0] if n['ConversionType']==3 else float(operand)
        if op in ('EX_IntConst', 'EX_ByteConst', 'EX_Int64Const', 'EX_DoubleConst', 'EX_FloatConst', 'EX_StringConst', 'EX_UnicodeStringConst', 'EX_NameConst', 'EX_SkipOffsetConst'):
            return 0.0 if n['Value'] == '+0' else n['Value']
        if op in ('EX_True', 'EX_False'):
            return op == 'EX_True'
        if op=='EX_NoObject':return None
        if op=='EX_ObjectConst':return n['Value']
        if op == 'EX_Self':
            return 'this'
        if op == 'EX_Context':
            child = n['ContextExpression']
            if child['op'] == 'EX_InstanceVariable':
                return state[reference(n)]
            if child['op'] in ('EX_FinalFunction', 'EX_VirtualFunction', 'EX_LocalVirtualFunction', 'EX_LocalFinalFunction'):
                return value(child)
        if op in ('EX_CallMath', 'EX_FinalFunction', 'EX_VirtualFunction', 'EX_LocalVirtualFunction', 'EX_LocalFinalFunction'):
            call = n.get('StackNode', n.get('VirtualFunctionName'))
            if call in out_injected:
                assert n['Parameters'] and n['Parameters'][-1]['op'] in ('EX_LocalOutVariable','EX_LocalVariable')
                state[reference(n['Parameters'][-1])] = copy.deepcopy(out_injected[call])
                effects.append({'call':call,'injected_out_parameter':True})
                return None
            if call == 'IsModifierActive?':
                modifier = value(n['Parameters'][0])
                key = reference(n['Parameters'][1])
                state[key] = bool(inputs.get('modifier:' + modifier, False))
                return None
            if call == 'Array_Clear':
                key=reference(n['Parameters'][0]);state[key]=[];writes[key]=[]
                return None
            if call == 'Array_Add':
                key = reference(n['Parameters'][0])
                item = value(n['Parameters'][1])
                state[key] = list(state[key]) + [item]
                writes[key] = state[key]
                return len(state[key]) - 1
            if call == 'Array_Get':
                array=value(n['Parameters'][0]); index=value(n['Parameters'][1])
                key=reference(n['Parameters'][2])
                if 0 <= index < len(array):
                    state[key]=copy.deepcopy(array[index])
                else:
                    field=clean(n['Parameters'][2]['Variable']['field'])
                    metadata=next(p for p in owner_exports[data['function']['name']]['LoadedProperties'] if clean(p['Name'])==field)
                    assert metadata['SerializedType']=='IntProperty', ('Unmodeled invalid array type',name,metadata['SerializedType'])
                    state[key]=0
                    effects.append({'call':call,'invalid_int_array_read':True,'index':index})
                return None
            if call == 'Array_RemoveItem':
                key=reference(n['Parameters'][0]);item=value(n['Parameters'][1]);array=value(n['Parameters'][0])
                updated=[v for v in array if v!=item]
                state[key]=updated;writes[key]=updated
                return len(updated)!=len(array)
            if call == 'Array_Set':
                target=n['Parameters'][0];key=reference(target)
                array=copy.deepcopy(value(target));index=value(n['Parameters'][1])
                assert 0 <= index < len(array) and not value(n['Parameters'][3]), ('Unmodeled array growth',name,index)
                array[index]=value(n['Parameters'][2]);state[key]=array;writes[key]=array
                if target['op']=='EX_StructMemberContext':
                    state[reference(target['StructExpression'])][clean(target['StructMemberExpression']['field'])]=array
                return None
            if call == 'PrintString':
                effects.append({'call': call, 'presentation_only': True})
                return None
            params = [value(p) for p in n['Parameters']]
            if call in functions:
                return functions[call](*params)
            if call in injected:
                if call in ('Create','PlayAnimation'):effects.append({'call':call,'injected_return':True,'arguments':params})
                return injected[call]
            if call == 'SetMinimumBeatInterval':
                effects.append({'call': call, 'arguments': params})
                return None
            if call in modeled_calls:
                effects.append({'call': call, 'arguments': params})
                return None
        raise ValueError(('Unsupported expression', name, n))
    assert 0 <= start_index < len(code)
    i = start_index
    for _ in range(1000):
        if prefix is not None and i >= prefix:
            break
        n = code[i]
        op = n['op']
        visited.append(i)
        if op == 'EX_Jump':
            i = byoffset[n['CodeOffset']]
            continue
        if op == 'EX_PushExecutionFlow':
            flow.append(byoffset[n['PushingAddress']])
        elif op == 'EX_PopExecutionFlow':
            if not flow:
                break
            i = flow.pop()
            continue
        elif op == 'EX_PopExecutionFlowIfNot':
            if not value(n['BooleanExpression']):
                if not flow:
                    break
                i = flow.pop()
                continue
        elif op == 'EX_JumpIfNot':
            if not value(n['BooleanExpression']):
                i = byoffset[n['CodeOffset']]
                continue
        elif op in ('EX_Let', 'EX_LetBool', 'EX_LetObj'):
            target = n.get('Variable', n.get('VariableExpression'))
            key = reference(target)
            state[key] = value(n.get('Expression', n.get('AssignmentExpression')))
            state[key] = copy.deepcopy(state[key])
            if target['op'] == 'EX_StructMemberContext':
                parent = reference(target['StructExpression'])
                if parent in state:
                    state[parent][clean(target['StructMemberExpression']['field'])] = state[key]
            if target['op'] != 'EX_LocalVariable':
                writes[key] = state[key]
        elif op in ('EX_Return', 'EX_EndOfScript'):
            break
        elif op in ('EX_Context', 'EX_CallMath', 'EX_LocalVirtualFunction', 'EX_VirtualFunction', 'EX_FinalFunction'):
            value(n)
        else:
            raise ValueError(('Unsupported statement', name, i, n))
        i += 1
    else:
        raise ValueError(('Step limit', name))
    return {'function': data['function']['name'], 'inputs': inputs, 'writes': writes, 'external_effects': effects,
            'visited_statements': visited, 'memory_size_verified': True, 'prefix_only': prefix is not None or start_index != 0,
            'start_statement': start_index,
            'source_sha256': hashlib.sha256(path.read_bytes()).hexdigest()}

if __name__ == '__main__':
    fixtures = []
    for name, key, target in [('SetEdgingPaceModifier', 'EdgePacingMultiplierEnum', 'EdgePacingMultiplier'),
                              ('SetUserStrokeMultiplier', 'StrokeMultiplierEnum', 'UserStrokeCountMultiplier')]:
        for index in [0,1,2,3,4,5,255]:
            fixtures.append(evaluate(name, {'GameInstance.CurrentSave.' + key: index, target: 17.0}))
    for count in [-1,0,99,100,249,250,499,500,749,750,1249,1250,1999,2000,5000]:
        fixtures.append(evaluate('DetermineComboType', {'PlayerVariablesStruct.CurrentComboCount': count, 'CurrentComboTypeEnum': 6}))
    for difficulty in [0,1,2,255]:
        for flags in itertools.product([False, True], repeat=5):
            lovense, handy, vibrator, stroker, full = flags
            fixtures.append(evaluate('SetMinimumBeatSpawnerInterval', {
                'CurrentDifficulty': difficulty, 'GameInstance.AdultToyManager.bButtplugFullStrokePerBeat': full,
                'call:HasConnectedLovenseDevices': lovense, 'call:IsHandyConnected': handy,
                'call:HasConnectedButtplugVibrators': vibrator, 'call:HasConnectedButtplugStrokers': stroker
            }))
    for total, remaining in [(10,10),(10,4),(10,2),(10,0),(0,0),(10,15),(10,-1)]:
        fixtures.append(evaluate('CalculateBeatPitch', {'call:GetTotalBeatsInQueue': total, 'call:GetBeatsRemaining': remaining}))
    for coins, multiplier in [(5,1.5),(-5,1.5),(5,0),(5,0.5)]:
        fixtures.append(evaluate('AddCoins', {'CoinAdd': coins, 'PlayerVariablesStruct.CoinEarnMultiplier': multiplier,
                                            'PlayerVariablesStruct.PlayerCoins': 10}, prefix=7))
    fixtures.append(evaluate('AddToCumMeter', {'CumMeterPercentage':0.95, 'Percentage (0-1.0)':0.1}))
    fixtures.append(evaluate('AddToLootBar', {'LootBarPercentage':0.95, 'Add (0.0-1.0)':0.1, 'LootBarMultiplier':2.0}))
    result = {'fixtures':fixtures, 'original_game_executed':False, 'limitations':[
        'Static traces validate selected state effects; widget, audio and complete progression behavior are not verified.',
        'Injected hardware/query results test rule branches, not real device compatibility.',
        'AddCoins traces stop before presentation statements.'
    ]}
    (ROOT / 'state-rule-traces.json').write_text(json.dumps(result, indent=2), encoding='utf-8')
    print('Validated', len(fixtures), 'static cases across', len({f['function'] for f in fixtures}), 'functions')
