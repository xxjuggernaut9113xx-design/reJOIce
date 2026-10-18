"""Decode selected newer CDO defaults using recovered class fields, requiring exact payload roundtrip."""
from pathlib import Path
import base64,hashlib,json
root=Path(__file__).resolve().parents[1];dest=root/'ReferenceBuilds/newer-20261017'
source=(root/'decode_defaults.py').read_text(encoding='utf8').split('results=[];failures=[];checks=[]')[0]
source=source.replace("native=json.loads((base/'native-reflection-schemas.json').read_text())","native=json.loads((pathlib.Path(r'"+str(dest)+"')/'native-reflection-schemas.json').read_text())")
scope={'__file__':str(root/'decode_defaults.py')};exec(source,scope)
enum_names={name:{e['name']:e['value'] for e in entries} for name,entries in json.loads((dest/'native-reflection-enums.json').read_text(encoding='utf8')).items()}
for enum in json.loads((dest/'decoded-blueprint-enums.json').read_text(encoding='utf8')):enum_names[enum['enum']]={e['name']:e['value'] for e in enum['entries']}
BaseReader,BaseWriter=scope['Reader'],scope['Writer']
class DefaultReader(BaseReader):
    def value(self,p,zero=False):
        if p['type']=='ArrayProperty' and p['inner']['type']=='EnumProperty':
            if zero:return []
            count=self.num('i');assert 0<=count<100000
            result=[]
            for _ in range(count):
                name=self.name();result.append({'enum':p['inner']['target'],'value':enum_names[p['inner']['target']][name],'serialized_name':name})
            return result
        return super().value(p,zero)
class DefaultWriter(BaseWriter):
    def value(self,p,v,zero=False):
        if p['type']=='ArrayProperty' and p['inner']['type']=='EnumProperty':
            if zero:return
            self.num('i',len(v))
            for item in v:self.name(item['serialized_name'])
            return
        return super().value(p,v,zero)
scope['Reader'],scope['Writer']=DefaultReader,DefaultWriter
for cls in json.loads((dest/'table-values.json').read_text(encoding='utf8'))['recovered_struct_schemas']:
    scope['schemas'][cls['class']]=cls['properties'];scope['supers'][cls['class']]=cls['super']
reflection={'__file__':str(root/'recover_blueprint_fields.py')};exec((root/'recover_blueprint_fields.py').read_text(encoding='utf8').split('results=[];failures=[]')[0],reflection)
classes=[];failures=[];defaults=[]
paths=[dest/'BP_GlobalManager-functions.json',*(dest/'decoded-blueprints').glob('BP_*-functions.json')]
for path in paths:
    try:
        for cls in reflection['read_asset'](path):
            classes.append(cls);scope['schemas'][cls['class']]=cls['properties'];scope['supers'][cls['class']]=cls['super']
    except Exception as exc:failures.append({'file':path.name,'stage':'fields','error':repr(exc)})
for path in paths:
    a=json.loads(path.read_text(encoding='utf8'))
    for e in a['Exports']:
        if not e['ObjectName'].startswith('Default__') or not isinstance(e.get('Data'),str):continue
        cls=e['ObjectName'].removeprefix('Default__');r=None
        try:
            raw=base64.b64decode(e['Data']);r=scope['Reader'](raw,a);values=r.properties(cls);guid=r.num('I');assert guid==0
            assert r.pos==len(raw),(r.pos,len(raw))
            w=scope['Writer'](r);w.properties(cls,values);w.num('I',guid);assert bytes(w.data)==raw
            defaults.append({'class':cls,'values':values,'payload_sha256':hashlib.sha256(raw).hexdigest(),'byte_identical_roundtrip':True})
        except Exception as exc:failures.append({'file':path.name,'stage':'defaults','error':repr(exc),'offset':r.pos if r else None,'recent_fields':r.trace[-3:] if r else []})
(dest/'blueprint-class-defaults.json').write_text(json.dumps({'classes':classes,'defaults':defaults,'failures':failures},indent=2),encoding='utf8')
print('Classes',len(classes),'defaults',len(defaults));print('Failures',failures)
