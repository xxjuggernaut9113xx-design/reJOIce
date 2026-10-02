"""Readable source listings from resolved Kismet AST; not executable C++."""
import json
from pathlib import Path

root = Path(__file__).parent
graph = json.loads((root / 'main-event-graph.json').read_text())
code = json.loads((root / 'blueprint-functions/BP_GlobalManager/ExecuteUbergraph_BP_GlobalManager.json').read_text())['statements']
entries = {e['event']: e for e in graph['event_entries']}

def expr(n):
    if n is None:
        return 'null'
    op = n.get('op', '')
    if op in ('EX_InstanceVariable', 'EX_LocalVariable', 'EX_LocalOutVariable'):
        return n['Variable']['field']
    if op == 'EX_StructMemberContext':
        return expr(n['StructExpression']) + '.' + n['StructMemberExpression']['field']
    if op in ('EX_True', 'EX_False', 'EX_NoObject', 'EX_Nothing', 'EX_Self'):
        return {'EX_True':'true', 'EX_False':'false', 'EX_NoObject':'nullptr', 'EX_Nothing':'void', 'EX_Self':'this'}[op]
    if op.endswith('Const') and 'Value' in n:
        if isinstance(n['Value'], (str, int, float)):
            return str(n['Value']) if n['Value'] == '+0' else json.dumps(n['Value'], ensure_ascii=False)
    if op == 'EX_ObjectConst':
        return str(n.get('Value'))
    if op == 'EX_Context':
        return expr(n['ObjectExpression']) + '->' + expr(n['ContextExpression'])
    if op in ('EX_CallMath', 'EX_FinalFunction', 'EX_LocalFinalFunction', 'EX_VirtualFunction', 'EX_LocalVirtualFunction'):
        name = n.get('StackNode', n.get('VirtualFunctionName'))
        return name + '(' + ', '.join(expr(p) for p in n['Parameters']) + ')'
    if op == 'EX_DynamicCast':
        return 'cast<' + str(n.get('ClassPtr', n.get('Class'))) + '>(' + expr(n['Target']) + ')'
    if op == 'EX_PrimitiveCast':
        return 'cast_' + str(n['ConversionType']) + '(' + expr(n['Target']) + ')'
    if op == 'EX_StructConst':
        return str(n.get('Struct', n.get('StructType'))) + '{' + ', '.join(expr(v) for v in n['Value']) + '}'
    if op == 'EX_TextConst':
        value = n['Value']
        if value['TextLiteralType'] == 'Empty':
            return 'Text("")'
        key = {'LocalizedText':'LocalizedSource', 'InvariantText':'InvariantLiteralString', 'LiteralString':'LiteralString'}.get(value['TextLiteralType'])
        if key:
            return 'Text(' + expr(value[key]) + ')'
    if op in ('EX_Let', 'EX_LetBool', 'EX_LetObj'):
        return expr(n.get('Variable', n.get('VariableExpression'))) + ' = ' + expr(n.get('Expression', n.get('AssignmentExpression')))
    if op == 'EX_Jump':
        return 'goto L' + str(n['CodeOffset'])
    if op == 'EX_JumpIfNot':
        return 'if (!' + expr(n['BooleanExpression']) + ') goto L' + str(n['CodeOffset'])
    if op == 'EX_PushExecutionFlow':
        return 'flow.push(L' + str(n['PushingAddress']) + ')'
    if op == 'EX_PopExecutionFlow':
        return 'goto flow.pop_or_return()'
    if op == 'EX_PopExecutionFlowIfNot':
        return 'if (!' + expr(n['BooleanExpression']) + ') goto flow.pop_or_return()'
    if op == 'EX_ComputedJump':
        return 'goto evaluated_offset(' + expr(n['CodeOffsetExpression']) + ')'
    if op == 'EX_Return':
        return 'return ' + expr(n['ReturnExpression'])
    if op == 'EX_SetArray':
        return expr(n['AssigningProperty']) + ' = [' + ', '.join(expr(e) for e in n['Elements']) + ']'
    return op + '(' + json.dumps({k:v for k,v in n.items() if k != 'op'}, ensure_ascii=False, separators=(',', ':')) + ')'

if __name__ == '__main__':
    chosen = ['ReceiveBeginPlay', 'StartGameButton', 'InitializeWidgets&Managers', 'ReinitGameVariables', 'SuccessfulCum', 'PrematureCum', 'BeatCompleteBind', 'BeatSequenceEnd']
    output = []
    for name in chosen:
        entry = entries[name]
        output.append('\n// ' + name + ' entry L' + str(entry['entry_offset']))
        start = entry['entry_statement']
        # Show contiguous code only; labels and flow instructions retain nonlocal edges.
        for i in range(start, min(start + 160, len(code))):
            output.append('L' + str(graph['statements'][i]['offset']) + ': ' + expr(code[i]) + ';')
            if code[i]['op'] in ('EX_PopExecutionFlow', 'EX_Return', 'EX_EndOfScript'):
                break
    destination = root / 'startup-outcome-pseudocode.txt'
    destination.write_text('\n'.join(output), encoding='utf-8')
    print(destination)
