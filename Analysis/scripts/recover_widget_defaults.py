"""Recover cooked widget class fields and CDO values with exact payload round trips."""
from pathlib import Path
import ast
import base64
import hashlib
import json

root=Path(__file__).resolve().parents[1]
schema_path=root/'widget-default-reflection-schemas.json'
if not schema_path.exists() or not {'PreciseBeatWidget','LevelUpEventData','UPSourceData'}.issubset(json.loads(schema_path.read_text(encoding='utf8'))['schemas']):
    schema_script=(root/'recover_ui_schemas.py').read_text(encoding='utf8')
    schema_script=schema_script.replace("wanted={'WidgetTree'", "wanted={'PreciseBeatWidget','LevelUpEventData','UPSourceData','CachedPropertyPath','PropertyPathSegment','DynamicPropertyPath','WidgetTree'")
    schema_script=schema_script.replace("root/'ui-reflection-schemas.json'", "root/'widget-default-reflection-schemas.json'")
    schema_scope={'__file__':str(root/'recover_ui_schemas.py')}
    exec(compile(schema_script,str(root/'recover_ui_schemas.py'),'exec'),schema_scope)
    symbols=schema_scope['public'];read_pointer=schema_scope['q'];by_address=schema_scope['byva']
    symbol=next(k for k in symbols if k.startswith('?DependentSingletons@Z_Construct_UClass_UPreciseBeatWidget_Statics@@'))
    dependency=by_address[read_pointer(symbols[symbol])]
    assert 'Z_Construct_UClass_UUserWidget' in dependency,dependency
    print('Verified native precise-beat widget parent:',dependency)
schema=json.loads(schema_path.read_text(encoding='utf8'))
schema['supers']['DynamicPropertyPath']='CachedPropertyPath'
schema['supers']['PreciseBeatWidget']='UserWidget'
schema_path.write_text(json.dumps(schema,indent=2),encoding='utf8')
decoder=(root/'decode_ui_layout.py').read_text().split('records=[];failures=[]')[0]
decoder=decoder.replace("root/'ui-reflection-schemas.json'", "root/'widget-default-reflection-schemas.json'")
namespace={'__file__':str(root/'decode_ui_layout.py')}
exec(decoder,namespace)
runtime=namespace['ns']
BaseReader,BaseWriter=runtime['Reader'],runtime['Writer']
class WidgetReader(BaseReader):
    def value(self,prop,zero=False):
        if prop['type'] in ('MulticastInlineDelegateProperty','MulticastDelegateProperty','MulticastSparseDelegateProperty'):
            if zero: return []
            count=self.num('i'); assert 0<=count<100000
            return [{'object':self.ref(),'function':self.name()} for _ in range(count)]
        return super().value(prop,zero)
class WidgetWriter(BaseWriter):
    def value(self,prop,value,zero=False):
        if prop['type'] in ('MulticastInlineDelegateProperty','MulticastDelegateProperty','MulticastSparseDelegateProperty'):
            if zero: return
            self.num('i',len(value))
            for item in value:
                self.num('i',item['object']['index'] if item['object'] else 0);self.name(item['function'])
            return
        return super().value(prop,value,zero)
runtime['Reader'],runtime['Writer']=WidgetReader,WidgetWriter
source=(root/'recover_blueprint_fields.py').read_text(encoding='utf8')
node=next(n for n in ast.parse(source).body if isinstance(n,ast.FunctionDef) and n.name=='read_asset')
function=ast.get_source_segment(source,node)
function=function.replace("('BlueprintGeneratedClass','UserDefinedStruct')", "('WidgetBlueprintGeneratedClass','BlueprintGeneratedClass','UserDefinedStruct')")
begin=function.index('frags=[];idx=0')
end=function.index("hasguid=r.num('I')",begin)
function=function[:begin]+"\n  native_reader=NativeReader(r.data,a)\n  metadata=native_reader.properties(classname)\n  native_writer=NativeWriter(native_reader)\n  native_writer.properties(classname,metadata)\n  assert bytes(native_writer.data)==r.data[:native_reader.pos], 'Class metadata round trip differs'\n  r.pos=native_reader.pos\n  "+function[end:]
function=function.replace("if classname=='BlueprintGeneratedClass' else {}", "if classname in ('WidgetBlueprintGeneratedClass','BlueprintGeneratedClass') else {}")
function=function.replace("'class_tail_offset':r.pos", "'class_tail_offset':r.pos,'native_property_bytes':native_reader.pos")
scope={'json':json,'base64':base64,'struct':runtime['struct'],'NativeReader':runtime['Reader'],'NativeWriter':runtime['Writer']}
exec(function,scope)
selected={path.stem:path for path in (root/'decoded-widget-functions').glob('*-functions.json')}
for path in (root/'decoded').glob('*-functions.json'):
    asset=json.loads(path.read_text(encoding='utf8'))
    if any(item['ObjectName']=='WidgetBlueprintGeneratedClass' for item in asset.get('Imports',[])):
        selected[path.stem]=path
files=list(selected.values())
classes=[];failures=[];assets={}
for path in files:
    try:
        asset=json.loads(path.read_text(encoding='utf8'))
        recovered=scope['read_asset'](path)
        classes.extend(recovered)
        for cls in recovered:
            runtime['schemas'][cls['class']]=cls['properties']
            runtime['supers'][cls['class']]=cls['super']
            assets[cls['class']]=asset
    except Exception as error:
        failures.append({'asset':path.stem,'stage':'class_fields','error':repr(error)})
defaults=[]
for cls,asset in assets.items():
    cdo=next((e for e in asset['Exports'] if e['ObjectName']=='Default__'+cls),None)
    if cdo is None: continue
    raw=base64.b64decode(cdo['Data'])
    reader=runtime['Reader'](raw,asset)
    try:
        values=reader.properties(cls)
        guid=reader.num('I'); assert guid==0
        assert reader.pos==len(raw),(reader.pos,len(raw))
        writer=runtime['Writer'](reader);writer.properties(cls,values);writer.num('I',guid)
        assert bytes(writer.data)==raw,'Round trip differs'
        defaults.append({'class':cls,'values':values,'sha256':hashlib.sha256(raw).hexdigest(),'byte_identical_roundtrip':True})
    except Exception as error:
        failures.append({'class':cls,'stage':'defaults','offset':reader.pos,'error':repr(error),'recent_fields':reader.trace[-5:]})
report={'original_executed':False,'classes':classes,'defaults':defaults,'failures':failures}
destination=root/'UnrealReconstruction/RecoveryEvidence/widget-class-defaults.json'
destination.write_text(json.dumps(report,indent=2,ensure_ascii=False),encoding='utf8')
print('Classes',len(classes),'verified defaults',len(defaults),'failures',len(failures))
print(failures[:6])
