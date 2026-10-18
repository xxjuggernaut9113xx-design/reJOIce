"""Print compact static bytecode statements; jump offsets remain original UE offsets."""
from pathlib import Path
import ast,json,sys
root=Path(__file__).resolve().parents[1]/'ReferenceBuilds/newer-20261017/functions'
source=(Path(__file__).resolve().parents[1]/'trace_difficulty.py').read_text(encoding='utf8')
node=next(n for n in ast.parse(source).body if isinstance(n,ast.FunctionDef) and n.name=='size')
scope={};exec(ast.get_source_segment(source,node),scope);size=scope['size']
def brief(n):
    if isinstance(n,list):return '['+', '.join(map(brief,n))+']'
    if not isinstance(n,dict):return str(n)
    if 'field' in n:return n['field']
    op=n.get('op','')
    if op.endswith('Variable'):return brief(n.get('Variable',{}))
    if op in ('EX_CallMath','EX_FinalFunction','EX_LocalFinalFunction','EX_LocalVirtualFunction','EX_VirtualFunction'):
        return str(n.get('StackNode',n.get('VirtualFunctionName','?')))+'('+', '.join(brief(p) for p in n.get('Parameters',[]))+')'
    if op=='EX_Context':return brief(n['ObjectExpression'])+'.'+brief(n['ContextExpression'])
    if op=='EX_StructMemberContext':return brief(n['StructExpression'])+'.'+brief(n['StructMemberExpression'])
    if op=='EX_StructConst':return str(n.get('Struct'))+'{'+brief(n['Value'])+'}'
    if op in ('EX_Let','EX_LetBool','EX_LetObj','EX_LetWeakObjPtr'):return brief(n.get('Variable',n.get('VariableExpression')))+' = '+brief(n.get('Expression',n.get('AssignmentExpression')))
    if op=='EX_JumpIfNot':return 'if !('+brief(n['BooleanExpression'])+') goto '+str(n['CodeOffset'])
    if op in ('EX_Jump','EX_PushExecutionFlow'):return op+' '+str(n.get('CodeOffset',n.get('PushingAddress')))
    if op=='EX_Return':return 'return '+brief(n['ReturnExpression'])
    if op=='EX_TextConst':return str(n['Value'])
    if op=='EX_ObjectConst':return str(n.get('Value',n.get('Object')))
    if op=='EX_SwitchValue':return str(n)
    return brief(n['Value']) if 'Value' in n else op
for function in sys.argv[2:]:
    p=root/sys.argv[1]/(function+'.json');a=json.loads(p.read_text(encoding='utf8'))
    print('\nFUNCTION',a['function'])
    offset=0
    for i,s in enumerate(a['statements'] or []):
        print(i,offset,brief(s));offset+=size(s)
