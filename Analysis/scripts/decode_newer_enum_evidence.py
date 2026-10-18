"""Decode a newer user-defined enum using standard UE metadata with a byte-exact check."""
from pathlib import Path
import base64,hashlib,json
root=Path(__file__).resolve().parents[1]
dest=root/'ReferenceBuilds/newer-20261017'
scope={'__file__':str(root/'decode_defaults.py')}
exec((root/'decode_defaults.py').read_text(encoding='utf8').split('results=[];failures=[];checks=[]')[0],scope)
scope['schemas']['UserDefinedEnum']=[{'name':'DisplayNameMap','type':'MapProperty','key':{'type':'NameProperty'},'value':{'type':'TextProperty'}}]
rows=[]
for path in [*dest.glob('*_ENUM-raw.json'),*(dest/'decoded-data').glob('*-raw.json')]:
    a=json.loads(path.read_text(encoding='utf8'))
    for e in a['Exports']:
        if e['ClassIndex']>=0 or a['Imports'][-e['ClassIndex']-1]['ObjectName']!='UserDefinedEnum': continue
        raw=base64.b64decode(e['Data']);r=scope['Reader'](raw,a)
        props=r.properties('UserDefinedEnum');assert r.num('I')==0
        count=r.num('i');entries=[{'name':r.name(),'value':r.num('q')} for _ in range(count)]
        cpp=r.num('B');assert r.pos==len(raw)
        display={k:v['text'] for k,v in props['DisplayNameMap']['entries']}
        for entry in entries:entry['display']=display.get(entry['name'].split('::')[-1])
        w=scope['Writer'](r);w.properties('UserDefinedEnum',props);w.num('I',0);w.num('i',count)
        for entry in entries:w.name(entry['name']);w.num('q',entry['value'])
        w.num('B',cpp);assert bytes(w.data)==raw
        if not any(row['enum']==e['ObjectName'] for row in rows):
            rows.append({'enum':e['ObjectName'],'entries':entries,'payload_sha256':hashlib.sha256(raw).hexdigest(),'byte_identical_roundtrip':True})
(dest/'decoded-blueprint-enums.json').write_text(json.dumps(rows,indent=2),encoding='utf8')
print(json.dumps(rows,indent=2))
