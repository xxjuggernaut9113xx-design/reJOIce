from pathlib import Path
import base64,json,hashlib
root=Path(__file__).parent
path=root/'decode_defaults.py'
ns={'__file__':str(path)}
exec(path.read_text().split('results=[];failures=[];checks=[]')[0],ns)
ns['schemas']['DataTable']=[{'name':n,'type':t} for n,t in [('RowStruct','ObjectProperty'),('bStripFromClientBuilds','BoolProperty'),('bIgnoreExtraFields','BoolProperty'),('bIgnoreMissingFields','BoolProperty'),('ImportKeyField','StrProperty')]]
asset=json.loads((root/'decoded/HeatCategoryDataTable-functions.json').read_text())
raw=base64.b64decode(asset['Exports'][0]['Data'])
r=ns['Reader'](raw,asset)
properties=r.properties('DataTable')
guid=r.num('I');assert guid==0
count=r.num('i');assert count==4
rows=[{'row':r.name(),'values':r.properties('FHeatCategoryProperties')} for _ in range(count)]
assert r.pos==len(raw),(r.pos,len(raw))
w=ns['Writer'](r)
w.properties('DataTable',properties);w.num('I',guid);w.num('i',count)
for row in rows:w.name(row['row']);w.properties('FHeatCategoryProperties',row['values'])
assert bytes(w.data)==raw
result={'rows':rows,'byte_identical_roundtrip':True,'source_sha256':hashlib.sha256(raw).hexdigest()}
text=json.dumps(result,indent=2)
(root/'heat-category-rows.json').write_text(text)
(root/'UnrealReconstruction/RecoveryEvidence/heat-category-rows.json').write_text(text)
print(text)
