"""Decode newer table rows using newer native reflection and recovered struct fields; verify bytes."""
from pathlib import Path
import base64,hashlib,json
root=Path(__file__).resolve().parents[1];dest=root/'ReferenceBuilds/newer-20261017'
source=(root/'decode_defaults.py').read_text(encoding='utf8').split('results=[];failures=[];checks=[]')[0]
source=source.replace("native=json.loads((base/'native-reflection-schemas.json').read_text())","native=json.loads((pathlib.Path(r'"+str(dest)+"')/'native-reflection-schemas.json').read_text())")
scope={'__file__':str(root/'decode_defaults.py')};exec(source,scope)
native_enums=json.loads((dest/'native-reflection-enums.json').read_text(encoding='utf8'))
# Generated enum arrays have an underlying node and an enum node before the array.
# The legacy flat helper chooses the first child; bind the actual enum child explicitly.
for field in scope['schemas']['DifficultyTierData']:
    if field['name']=='UnlockableSuccuModifiers':field['inner']={'type':'EnumProperty','target':'ESuccuShopModifier','underlying':{'type':'ByteProperty'}}
BaseReader,BaseWriter=scope['Reader'],scope['Writer']
class TableReader(BaseReader):
    def value(self,p,zero=False):
        if p['type']=='ArrayProperty' and p['inner']['type']=='EnumProperty':
            if zero:return []
            count=self.num('i');assert 0<=count<100000
            entries={e['name']:e['value'] for e in native_enums[p['inner']['target']]}
            result=[]
            for _ in range(count):
                name=self.name();result.append({'enum':p['inner']['target'],'value':entries[name],'serialized_name':name})
            return result
        return super().value(p,zero)
class TableWriter(BaseWriter):
    def value(self,p,v,zero=False):
        if p['type']=='ArrayProperty' and p['inner']['type']=='EnumProperty':
            if zero:return
            self.num('i',len(v))
            for item in v:self.name(item['serialized_name'])
            return
        return super().value(p,v,zero)
scope['Reader'],scope['Writer']=TableReader,TableWriter
scope['schemas']['DataTable']=[{'name':n,'type':t} for n,t in [('RowStruct','ObjectProperty'),('bStripFromClientBuilds','BoolProperty'),('bIgnoreExtraFields','BoolProperty'),('bIgnoreMissingFields','BoolProperty'),('ImportKeyField','StrProperty')]]
reflection={'__file__':str(root/'recover_blueprint_fields.py')}
exec((root/'recover_blueprint_fields.py').read_text(encoding='utf8').split('results=[];failures=[]')[0],reflection)
classes=[];failures=[];tables=[]
for path in (dest/'decoded-data').glob('*.json'):
    try:
        for cls in reflection['read_asset'](path):
            classes.append(cls);scope['schemas'][cls['class']]=cls['properties'];scope['supers'][cls['class']]=cls['super']
    except Exception as exc:failures.append({'file':path.name,'stage':'struct','error':repr(exc)})
for path in (dest/'decoded-data').glob('*.json'):
    asset=json.loads(path.read_text(encoding='utf8'))
    for e in asset['Exports']:
        if e['ClassIndex']>=0 or asset['Imports'][-e['ClassIndex']-1]['ObjectName']!='DataTable':continue
        reader=None
        try:
            raw=base64.b64decode(e['Data']);reader=scope['Reader'](raw,asset)
            properties=reader.properties('DataTable');guid=reader.num('I');assert guid==0
            count=reader.num('i');assert 0<=count<100000
            rowclass=properties['RowStruct']['name']
            rows=[]
            for _ in range(count):rows.append({'row':reader.name(),'values':reader.properties(rowclass)})
            assert reader.pos==len(raw),(reader.pos,len(raw))
            writer=scope['Writer'](reader);writer.properties('DataTable',properties);writer.num('I',guid);writer.num('i',count)
            for row in rows:writer.name(row['row']);writer.properties(rowclass,row['values'])
            assert bytes(writer.data)==raw
            tables.append({'table':e['ObjectName'],'row_class':rowclass,'rows':rows,'source':str(path.relative_to(dest)),'payload_sha256':hashlib.sha256(raw).hexdigest(),'byte_identical_roundtrip':True})
        except Exception as exc:failures.append({'file':path.name,'stage':'table','offset':reader.pos if reader else None,'error':repr(exc),'recent_fields':reader.trace[-3:] if reader else [],'partial_unverified_rows':rows})
result={'original_game_executed':False,'native_reflection_source':'newer executable/PDB','recovered_struct_schemas':classes,'tables':tables,'failures':failures}
(dest/'table-values.json').write_text(json.dumps(result,indent=2,ensure_ascii=False),encoding='utf8')
print('Tables',[(t['table'],len(t['rows'])) for t in tables]);print('Failures',[(f['file'],f['stage'],f['error']) for f in failures])
