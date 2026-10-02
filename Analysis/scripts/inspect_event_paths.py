import ast,json,pathlib,sys
root=pathlib.Path(__file__).resolve().parents[1]
source=(root/'trace_difficulty.py').read_text(encoding='utf8')
node=next(n for n in ast.parse(source).body if isinstance(n,ast.FunctionDef) and n.name=='size')
ns={};exec(ast.get_source_segment(source,node),ns);size=ns['size']
def brief(n):
    if not isinstance(n,dict): return str(n)
    op=n.get('op','')
    if op.endswith('Variable'): return n.get('Variable',{}).get('field','?')
    if op in ('EX_CallMath','EX_FinalFunction','EX_LocalFinalFunction','EX_LocalVirtualFunction','EX_VirtualFunction'):
        return n.get('StackNode',n.get('VirtualFunctionName','?'))+'('+', '.join(brief(p) for p in n.get('Parameters',[]))+')'
    if op=='EX_Context': return brief(n['ObjectExpression'])+'.'+brief(n['ContextExpression'])
    if op=='EX_StructMemberContext': return brief(n['StructExpression'])+'.'+n['StructMemberExpression']['field']
    if op=='EX_StructConst': return '{'+','.join(brief(v) for v in n['Value'])+'}'
    if op in ('EX_Let','EX_LetBool','EX_LetObj'): return brief(n.get('Variable',n.get('VariableExpression')))+' = '+brief(n.get('Expression',n.get('AssignmentExpression')))
    if op=='EX_JumpIfNot':return 'if !('+brief(n['BooleanExpression'])+') goto '+str(n['CodeOffset'])
    if op in ('EX_Jump','EX_PushExecutionFlow'):return op+' '+str(n.get('CodeOffset',n.get('PushingAddress')))
    if op=='EX_TextConst':return str(n['Value'])
    return str(n.get('Value',op))
function=sys.argv[3] if len(sys.argv)>3 else 'ExecuteUbergraph_BP_GlobalManager'
asset_name=sys.argv[4] if len(sys.argv)>4 else 'BP_GlobalManager'
path=root/'blueprint-functions'/asset_name/(function+'.json')
if not path.exists():path=root/'widget-functions'/asset_name/(function+'.json')
asset=json.loads(path.read_text(encoding='utf8'))
offset=0;code=[]
for n in asset['statements']:
    code.append((offset,n));offset+=size(n)
start=int(sys.argv[1]);end=int(sys.argv[2])
for pos,n in code:
    if start<=pos<end: print(pos,brief(n))
