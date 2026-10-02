from pathlib import Path
import json,ast
r=Path(__file__).resolve().parents[1];p=r/'UnrealReconstruction';source=(r/'trace_difficulty.py').read_text();node=next(n for n in ast.parse(source).body if isinstance(n,ast.FunctionDef) and n.name=='size');ns={};exec(ast.get_source_segment(source,node),ns);size=ns['size']
cat=json.loads((p/'RecoveryEvidence/animation-source-catalog.json').read_text());reports=json.loads((p/'Saved/all-animation-probe-report.json').read_text());result={};reject={}
def fn(name,f):
    for d in ('blueprint-functions','widget-functions'):
        x=r/d/name/(f+'.json')
        if x.exists():return json.loads(x.read_text())['statements']
    raise ValueError(f)
def entry(name,f):
    first=fn(name,f)[0]
    if first['op']=='EX_LocalFinalFunction':return first['StackNode'],first['Parameters'][0]['Value']
    if first['op']=='EX_LocalVirtualFunction':return entry(name,first['VirtualFunctionName'])
    raise ValueError(first['op'])
def trace(name,function,start):
    st=fn(name,function);offset=0;by={}
    for n in st:by[offset]=n;offset+=size(n)
    body=[];pos=start
    for step in range(100):
        n=by[pos];op=n['op']
        if op=='EX_Jump':pos=n['CodeOffset'];continue
        if op in ('EX_Return','EX_EndOfScript','EX_PopExecutionFlow'):return body
        body.append(n);pos+=size(n)
    raise ValueError('trace limit')
for name,report in reports.items():
    a=json.loads(Path(cat[name]['source']).read_text(encoding='utf-8-sig'));indices=sorted({i for o in report['objects'] for i in o['unresolved_references'] if i>0})
    if not indices:continue
    try:
        functions=[]
        for idx in indices:
            if idx<0:raise ValueError('unresolved import')
            callback=a['Exports'][idx-1]['ObjectName'];f,start=entry(name,callback);body=trace(name,f,start)
            assert len(body)==1 and body[0]['op']=='EX_VirtualFunction' and body[0]['VirtualFunctionName']=='RemoveFromParent' and body[0]['Parameters']==[],body
            functions.append(callback)
        f,start=entry(name,'Construct');body=trace(name,f,start);plays=[]
        for n in body:
            if n['op']=='EX_LetObj' and n['AssignmentExpression'].get('StackNode')=='PlayAnimation':plays.append(n['AssignmentExpression'])
        assert len(plays)==1,plays
        params=plays[0]['Parameters'];assert params[0]['op']=='EX_InstanceVariable',params
        result[name]={'callbacks':functions,'construct_animation':params[0]['Variable']['field'],'parameters':params[1:],'construct_trace':body}
    except (ValueError,AssertionError,KeyError) as e:reject[name]=str(e)[:300]
(p/'RecoveryEvidence/overlay-animation-callbacks.json').write_text(json.dumps({'verified':result,'pending':reject},indent=2))
print('Verified',len(result),'simple overlay lifecycles');print('Pending',reject)
