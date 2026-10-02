"""Recover material properties without loading cooked material/shader objects."""
from pathlib import Path
import base64
import hashlib
import json

root=Path(__file__).resolve().parents[1]
namespace={'__file__':str(root/'decode_ui_layout.py')}
exec((root/'decode_ui_layout.py').read_text().split('records=[];failures=[]')[0],namespace)
runtime=namespace['ns']
catalog=json.loads((root/'native-reflection-catalog.json').read_text(encoding='utf8'))
for owner,props in catalog['schemas'].items():
    converted=[];pending=[]
    try:
        for prop in props:
            if any(s in prop['symbol'] for s in ('_Inner@','_Underlying@','_ValueProp@','_KeyProp@','_Key@','_Value@','_ElementProp@')) and not prop['symbol'].startswith(('?NewProp_Value@','?NewProp_Key@')):
                pending.append(prop);continue
            if not int(prop['flags'],16)&0x800000000:
                descriptor=runtime['nt'](prop,pending)
                for index in range(prop['dim']):
                    item=dict(descriptor)
                    if prop['dim']>1:item['name']=descriptor['name']+'['+str(index)+']'
                    converted.append(item)
            pending=[]
        runtime['schemas'][owner]=converted
    except (AssertionError,KeyError,IndexError):
        continue
runtime['supers'].update(catalog['supers'])
asset=json.loads((root/'background-material.json').read_text(encoding='utf8'))
raw=base64.b64decode(asset['Exports'][0]['Data'])
reader=runtime['Reader'](raw,asset)
try:
    values=reader.properties('Material')
    guid=reader.num('I');assert guid==0
    writer=runtime['Writer'](reader);writer.properties('Material',values);writer.num('I',guid)
    assert bytes(writer.data)==raw[:reader.pos]
    report={'original_executed':False,'original_expression_graph_restored':False,'values':values,'property_prefix_bytes':reader.pos,'native_tail_bytes':len(raw)-reader.pos,'source_payload_sha256':hashlib.sha256(raw).hexdigest(),'property_prefix_byte_identical_roundtrip':True}
    (root/'UnrealReconstruction/RecoveryEvidence/background-material-values.json').write_text(json.dumps(report,indent=2),encoding='utf8')
    print('Verified material property bytes',reader.pos,'native shader/resource tail',len(raw)-reader.pos)
    print(json.dumps(values,indent=2)[:6000])
except Exception as error:
    print('Material decode failed at',reader.pos,repr(error),'recent fields',reader.trace[-8:])
    raise
