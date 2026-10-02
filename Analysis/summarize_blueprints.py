import pathlib,json,collections,re
base=pathlib.Path(__file__).parent
out=base/'blueprint-functions';out.mkdir(exist_ok=True)
def typename(n):return n.get('$type','').split('.')[-1].split(',')[0]
def walk(n):
 if isinstance(n,dict):
  yield n
  for v in n.values():yield from walk(v)
 elif isinstance(n,list):
  for v in n:yield from walk(v)
summary=[]
for p in sorted((base/'decoded').glob('*-functions.json')):
 asset=json.loads(p.read_text(encoding='utf8'))
 def ref(i):
  if not isinstance(i,int):return str(i)
  if i==0:return 'null'
  pool=asset['Exports'] if i>0 else asset['Imports'];idx=i-1 if i>0 else -i-1
  return pool[idx]['ObjectName'] if idx<len(pool) else f'index:{i}'
 def compact(n):
  if isinstance(n,list):return [compact(x) for x in n]
  if not isinstance(n,dict):return n
  kind=typename(n)
  if kind=='KismetPropertyPointer':return compact(n.get('New') or n.get('Old'))
  if kind=='FFieldPath':return {'field':'.'.join(n['Path']),'owner':ref(n['ResolvedOwner'])}
  result={'op':kind}
  for k,v in n.items():
   if k=='$type':continue
   if k in ('StackNode','Object','ResolvedOwner') and isinstance(v,int):result[k]=ref(v)
   else:result[k]=compact(v)
  return result
 funcs=[]
 for e in asset['Exports']:
  if 'FunctionExport' not in e['$type']:continue
  code=e.get('ScriptBytecode');nodes=list(walk(code))
  calls=sorted({ref(n['StackNode']) for n in nodes if 'StackNode' in n}|{str(n['VirtualFunctionName']) for n in nodes if 'VirtualFunctionName' in n})
  fields=sorted({'.'.join(n['Path']) for n in nodes if typename(n)=='FFieldPath'})
  item={'name':e['ObjectName'],'statements':len(code or []),'raw_fallback':bool(e.get('ScriptBytecodeRaw')),'calls':calls,'fields':fields}
  funcs.append(item)
  safe=re.sub(r'[^A-Za-z0-9_.-]+','_',e['ObjectName'])
  folder=out/p.stem.replace('-functions','');folder.mkdir(exist_ok=True)
  (folder/(safe+'.json')).write_text(json.dumps({'function':item,'statements':compact(code)},indent=2),encoding='utf8')
 counts=collections.Counter(typename(e) for e in asset['Exports'])
 summary.append({'asset':p.stem.replace('-functions',''),'exports':dict(counts),'functions':funcs})
(base/'blueprint-analysis-summary.json').write_text(json.dumps(summary,indent=2),encoding='utf8')
print('Assets',len(summary),'functions',sum(len(s['functions']) for s in summary),'raw bytecode fallbacks',sum(f['raw_fallback'] for s in summary for f in s['functions']))
for s in summary:
 if s['functions']:print(s['asset'],len(s['functions']))
