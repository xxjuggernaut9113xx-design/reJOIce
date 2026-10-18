"""Compare decoded newer Blueprint bytecode against retained V0.04 evidence."""
from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1]
dest=root/'ReferenceBuilds/newer-20261017'
def kind(n): return n.get('$type','').split('.')[-1].split(',')[0]
def walk(n):
    if isinstance(n,dict):
        yield n
        for v in n.values(): yield from walk(v)
    elif isinstance(n,list):
        for v in n: yield from walk(v)
def compact_asset(asset):
    def ref(i):
        if not isinstance(i,int): return str(i)
        if i==0: return 'null'
        pool=asset['Exports'] if i>0 else asset['Imports'];idx=i-1 if i>0 else -i-1
        return pool[idx]['ObjectName'] if idx<len(pool) else f'index:{i}'
    def compact(n):
        if isinstance(n,list): return [compact(x) for x in n]
        if not isinstance(n,dict): return n
        t=kind(n)
        if t=='KismetPropertyPointer': return compact(n.get('New') or n.get('Old'))
        if t=='FFieldPath': return {'field':'.'.join(n['Path']),'owner':ref(n['ResolvedOwner'])}
        return dict(op=t,**{k:ref(v) if k in ('StackNode','Object','ResolvedOwner') and isinstance(v,int) else compact(v) for k,v in n.items() if k!='$type'})
    return {e['ObjectName']:compact(e.get('ScriptBytecode')) for e in asset['Exports'] if 'FunctionExport' in e['$type']}
sources=list((dest/'decoded-blueprints').glob('*.json'))+[dest/'BP_GlobalManager-functions.json']
report=[]
for source in sources:
    name=source.stem.replace('-functions','')
    asset=json.loads(source.read_text(encoding='utf8'))
    functions=compact_asset(asset)
    output=dest/'functions'/name;output.mkdir(parents=True,exist_ok=True)
    oldpath=next((p for p in [root/'decoded'/(name+'-functions.json'),root/'decoded-widget-functions'/(name+'-functions.json')] if p.exists()),None)
    old=compact_asset(json.loads(oldpath.read_text(encoding='utf8'))) if oldpath else {}
    changed=[]
    for function,code in functions.items():
        (output/(re.sub(r'[^A-Za-z0-9_.-]+','_',function)+'.json')).write_text(json.dumps({'function':function,'statements':code},indent=2),encoding='utf8')
        if function not in old or code!=old[function]:
            nodes=list(walk(code));oldnodes=list(walk(old.get(function,[])))
            calls=lambda ns:sorted({n.get('StackNode',n.get('VirtualFunctionName')) for n in ns if 'StackNode' in n or 'VirtualFunctionName' in n})
            fields=lambda ns:sorted({n['field'] for n in ns if 'field' in n})
            changed.append({'function':function,'new':function not in old,'new_calls':sorted(set(calls(nodes))-set(calls(oldnodes))),'new_fields':sorted(set(fields(nodes))-set(fields(oldnodes)))})
    report.append({'asset':name,'functions':len(functions),'old_functions':len(old),'raw_fallbacks':[e['ObjectName'] for e in asset['Exports'] if 'FunctionExport' in e['$type'] and e.get('ScriptBytecodeRaw')],'changed_functions':changed,'absent_functions':sorted(set(old)-set(functions))})
(dest/'blueprint-function-delta.json').write_text(json.dumps(report,indent=2),encoding='utf8')
for entry in report: print(entry['asset'],entry['functions'],'old',entry['old_functions'],'changed',len(entry['changed_functions']),'fallbacks',entry['raw_fallbacks'])
