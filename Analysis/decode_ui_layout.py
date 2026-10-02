"""Decode widget/slot payloads; require exact re-encoding before accepting values."""
from pathlib import Path
import base64,json,hashlib
root=Path(__file__).parent
path=root/'decode_defaults.py'
ns={'__file__':str(path)}
exec(path.read_text().split('results=[];failures=[];checks=[]')[0],ns)
ns['types'][31]='FieldPathProperty'
ns['types'][32]='DoubleProperty'
ui=json.loads((root/'ui-reflection-schemas.json').read_text())
for owner,props in ui['schemas'].items():
    result=[];pending=[]
    for prop in props:
        if any(s in prop['symbol'] for s in ('_Inner@','_Underlying@','_ValueProp@','_KeyProp@','_Key@','_Value@','_ElementProp@')) and not prop['symbol'].startswith(('?NewProp_Value@','?NewProp_Key@')):pending.append(prop);continue
        if not int(prop['flags'],16)&0x800000000:result.append(ns['nt'](prop,pending))
        pending=[]
    ns['schemas'][owner]=result
for owner,parent in ui['supers'].items():
    ns['supers'][owner]=parent
    ns['schemas'].setdefault(owner,[])
records=[];failures=[]
imports={};omitted=[];seen=set()
for asset_path in list((root/'decoded').glob('*-functions.json'))+list((root/'decoded-ui').rglob('*.json')):
    asset=json.loads(asset_path.read_text(encoding='utf-8'))
    if not any(i['ObjectName']=='WidgetTree' for i in asset.get('Imports',[])):continue
    asset_name=asset_path.stem.removesuffix('-functions')
    if asset_name in seen:continue
    seen.add(asset_name)
    def import_path(index):
        if index>=0:return None
        item=asset['Imports'][-index-1]
        parent=import_path(item['OuterIndex']) if item['OuterIndex']<0 else None
        return (parent+'.'+item['ObjectName']) if parent else item['ObjectName']
    imports[asset_name]={str(-i-1):import_path(-i-1) for i in range(len(asset['Imports']))}
    for index,export in enumerate(asset['Exports'],1):
        cls=asset['Imports'][-export['ClassIndex']-1]['ObjectName'] if export['ClassIndex']<0 else None
        if cls in ('WidgetAnimation','WidgetBlueprintGeneratedClass') or (cls and cls.startswith('MovieScene')):continue
        if cls not in ui['supers'] or cls not in ns['schemas'] or not isinstance(export.get('Data'),str):
            if cls and cls.endswith('_C'):omitted.append({'asset':asset_name,'export_index':index,'name':export['ObjectName'],'class':cls})
            continue
        raw=base64.b64decode(export['Data']);reader=ns['Reader'](raw,asset)
        try:
            values=reader.properties(cls);guid=reader.num('I');assert guid==0
            assert reader.pos==len(raw),(reader.pos,len(raw))
            writer=ns['Writer'](reader);writer.properties(cls,values);writer.num('I',guid)
            assert bytes(writer.data)==raw,'Re-encoded payload differs'
            records.append({'asset':asset_name,'export_index':index,'name':export['ObjectName'],'class':cls,'outer_index':export['OuterIndex'],'values':values,'payload_bytes':len(raw),'byte_identical_roundtrip':True,'sha256':hashlib.sha256(raw).hexdigest()})
        except Exception as error:
            failures.append({'asset':asset_name,'name':export['ObjectName'],'class':cls,'offset':reader.pos,'bytes':len(raw),'error':repr(error),'recent_fields':reader.trace[-6:]})
result={'original_game_executed':False,'widgets':records,'failures':failures,'imports':imports,'omitted_custom_widgets':omitted,'original_graphs_restored':False,'animations_restored':False}
text=json.dumps(result,indent=2,ensure_ascii=False)
(root/'ui-layout-values.json').write_text(text,encoding='utf-8')
(root/'UnrealReconstruction/RecoveryEvidence/ui-layout-values.json').write_text(text,encoding='utf-8')
print('Verified',len(records),'UI object payloads; failures',len(failures))
print([(f['class'],f['error']) for f in failures[:12]])
