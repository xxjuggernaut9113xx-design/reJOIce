"""Decode the original modifier table and require a byte-identical round trip."""
from pathlib import Path
import base64, hashlib, json
root=Path(__file__).resolve().parents[1]
reflection={'__file__':str(root/'recover_blueprint_fields.py')}
exec((root/'recover_blueprint_fields.py').read_text(encoding='utf8').split('results=[];failures=[]')[0],reflection)
schema=reflection['read_asset'](root/'decoded-textures/UI/ModifierIcons/ModifierInfoStruct.json')[0]
namespace={'__file__':str(root/'decode_defaults.py')}
exec((root/'decode_defaults.py').read_text(encoding='utf8').split('results=[];failures=[];checks=[]')[0],namespace)
namespace['schemas']['DataTable']=[{'name':n,'type':t} for n,t in [('RowStruct','ObjectProperty'),('bStripFromClientBuilds','BoolProperty'),('bIgnoreExtraFields','BoolProperty'),('bIgnoreMissingFields','BoolProperty'),('ImportKeyField','StrProperty')]]
namespace['schemas']['ModifierInfoStruct']=schema['properties']
namespace['supers']['ModifierInfoStruct']=None
asset=json.loads((root/'decoded-textures/UI/ModifierIcons/ModifierInfoDataTable.json').read_text(encoding='utf8'))
raw=base64.b64decode(asset['Exports'][0]['Data'])
reader=namespace['Reader'](raw,asset)
properties=reader.properties('DataTable')
guid=reader.num('I');assert guid==0
count=reader.num('i');assert 0<count<1000
rows=[{'row':reader.name(),'values':reader.properties('ModifierInfoStruct')} for _ in range(count)]
assert reader.pos==len(raw),(reader.pos,len(raw))
writer=namespace['Writer'](reader)
writer.properties('DataTable',properties);writer.num('I',guid);writer.num('i',count)
for row in rows:writer.name(row['row']);writer.properties('ModifierInfoStruct',row['values'])
assert bytes(writer.data)==raw
def import_path(index):
    item=asset['Imports'][-index-1]
    parent=import_path(item['OuterIndex']) if item['OuterIndex']<0 else None
    return parent+'.'+item['ObjectName'] if parent else item['ObjectName']
result={'original_executed':False,'byte_identical_roundtrip':True,'source_sha256':hashlib.sha256(raw).hexdigest(),'schema':schema,'properties':properties,'rows':rows,'imports':{str(-i-1):import_path(-i-1) for i in range(len(asset['Imports']))}}
target=root/'UnrealReconstruction/RecoveryEvidence/modifier-table-values.json'
target.write_text(json.dumps(result,indent=2),encoding='utf8')
print('Verified modifier rows',count)
