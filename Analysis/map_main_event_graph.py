import json,pathlib
from trace_difficulty import size
base=pathlib.Path(__file__).parent
main='ExecuteUbergraph_BP_GlobalManager'
asset=json.loads((base/'decoded/BP_GlobalManager-functions.json').read_text())
exp=next(e for e in asset['Exports'] if e['ObjectName']==main)
source=json.loads((base/'blueprint-functions/BP_GlobalManager'/(main+'.json')).read_text())
nodes=[];offset=0
def walk(n):
 if isinstance(n,dict):
  yield n
  for v in n.values():yield from walk(v)
 elif isinstance(n,list):
  for v in n:yield from walk(v)
for i,n in enumerate(source['statements']):
 length=size(n);jump=n.get('CodeOffset') if n['op'] in ('EX_Jump','EX_JumpIfNot') else n.get('PushingAddress') if n['op']=='EX_PushExecutionFlow' else None
 calls=sorted({x['StackNode'] for x in walk(n) if 'StackNode' in x}|{x['VirtualFunctionName'] for x in walk(n) if 'VirtualFunctionName' in x})
 nodes.append({'statement':i,'offset':offset,'memory_bytes':length,'op':n['op'],'calls':calls,'target_offset':jump});offset+=length
assert offset==exp['ScriptBytecodeSize'],(offset,exp['ScriptBytecodeSize'])
byoffset={n['offset']:n['statement'] for n in nodes}
for n in nodes:
 if n['target_offset'] is not None:n['target_statement']=byoffset[n['target_offset']]
entries=[]
for path in sorted((base/'blueprint-functions/BP_GlobalManager').glob('*.json')):
 if path.stem==main:continue
 f=json.loads(path.read_text())
 for n in walk(f['statements']):
  if n.get('StackNode',n.get('VirtualFunctionName'))!=main:continue
  params=n.get('Parameters') or []
  assert len(params)==1 and params[0]['op']=='EX_IntConst',(path,params)
  address=params[0]['Value'];entries.append({'event':f['function']['name'],'entry_offset':address,'entry_statement':byoffset[address]})
report={'function':main,'memory_bytes':offset,'declared_memory_bytes':exp['ScriptBytecodeSize'],'size_verified':True,'statement_count':len(nodes),'aligned_jump_targets':sum(n['target_offset'] is not None for n in nodes),'event_entries':entries,'statements':nodes,'limitations':'Structural graph only. Conditional expressions, flow-stack behavior and engine callbacks still require semantic interpretation and original-game traces.'}
(base/'main-event-graph.json').write_text(json.dumps(report,indent=2),encoding='utf8')
print('Graph bytes',offset,'statements',len(nodes),'aligned branch/flow targets',report['aligned_jump_targets'],'event entries',len(entries))
print([(e['event'],e['entry_offset']) for e in entries])
