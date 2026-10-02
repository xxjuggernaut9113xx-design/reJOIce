from pathlib import Path
import json
import base64
import hashlib

root=Path(__file__).resolve().parents[1]
schema_script=(root/'recover_ui_schemas.py').read_text()
schema_script=schema_script.replace("wanted={'WidgetTree'", "wanted={'Font','FontFace','CompositeFont','Typeface','TypefaceEntry','FontData','WidgetTree'")
schema_script=schema_script.replace("root/'ui-reflection-schemas.json'", "root/'font-reflection-schemas.json'")
if not (root/'font-reflection-schemas.json').exists():
    exec(compile(schema_script,str(root/'recover_ui_schemas.py'),'exec'),{'__file__':str(root/'recover_ui_schemas.py')})
decoder=(root/'decode_ui_layout.py').read_text().split('records=[];failures=[]')[0]
decoder=decoder.replace("root/'ui-reflection-schemas.json'", "root/'font-reflection-schemas.json'")
ns={'__file__':str(root/'decode_ui_layout.py')}
exec(decoder,ns)
Reader,Writer=ns['ns']['Reader'],ns['ns']['Writer']
class FontReader(Reader):
    def value(self,p,zero=False):
        if p['type']=='StructProperty' and p['target']=='FontData' and not zero:
            cooked=self.num('I'); assert cooked==1
            face=self.ref(); assert face is not None
            return {'cooked':cooked,'face':face,'subface_index':self.num('i')}
        return super().value(p,zero)
class FontWriter(Writer):
    def value(self,p,v,zero=False):
        if p['type']=='StructProperty' and p['target']=='FontData' and not zero:
            self.num('I',v['cooked']); self.num('i',v['face']['index']); self.num('i',v['subface_index']); return
        return super().value(p,v,zero)
report={}
for filename,cls in [('font-composite','Font'),('font-face','FontFace')]:
    asset=json.loads((root/(filename+'.json')).read_text())
    raw=base64.b64decode(asset['Exports'][0]['Data'])
    reader=FontReader(raw,asset)
    values=reader.properties(cls)
    guid=reader.num('I'); assert guid==0
    tail=raw[reader.pos:]
    if cls=='Font': assert tail==bytes(4),tail.hex() # Empty native CharRemap.
    else: assert tail==bytes.fromhex('0100000000000000'),tail.hex() # Cooked, streamed (not inline).
    writer=FontWriter(reader); writer.properties(cls,values); writer.num('I',guid); writer.data.extend(tail)
    assert bytes(writer.data)==raw
    report[cls]={'values':values,'native_tail':tail.hex(),'sha256':hashlib.sha256(raw).hexdigest(),'byte_identical_roundtrip':True}
(root/'UnrealReconstruction/RecoveryEvidence/font-values.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
