"""Recover cooked UStruct FProperty definitions without running the game.
Uses UE5.3 FField/FProperty serialization layouts from the installed source.
"""
import json,pathlib,base64,struct
base=pathlib.Path(__file__).parent
def read_asset(path):
 a=json.loads(path.read_text(encoding='utf8'));names=a['NameMap']
 class Reader:
  def __init__(self,data):self.data=data;self.pos=0
  def num(self,fmt):
   v=struct.unpack_from('<'+fmt,self.data,self.pos)[0];self.pos+=struct.calcsize('<'+fmt);return v
  def fname(self):
   i=self.num('i');n=self.num('i');assert 0<=i<len(names),(self.pos,i)
   return names[i]+('_'+str(n-1) if n else '')
  def ref(self):
   i=self.num('i')
   if not i:return None
   return (a['Exports'] if i>0 else a['Imports'])[i-1 if i>0 else -i-1]['ObjectName']
  def prop(self):
   start=self.pos;t=self.fname();n=self.fname();flags=self.num('I');dim=self.num('i');size=self.num('i');pf=self.num('Q');rep=self.num('H');notify=self.fname();cond=self.num('B')
   p={'name':n,'type':t,'array_dim':dim,'element_size':size,'flags':hex(pf),'start':start}
   if t in ('StructProperty','ObjectProperty','SoftObjectProperty','WeakObjectProperty','LazyObjectProperty','InterfaceProperty','ByteProperty','DelegateProperty','MulticastDelegateProperty','MulticastInlineDelegateProperty','MulticastSparseDelegateProperty'):p['target']=self.ref()
   elif t in ('ClassProperty','SoftClassProperty'):
    p['target']=self.ref();p['meta_class']=self.ref()
   elif t=='BoolProperty':p['bool_layout']=[self.num('B') for _ in range(6)]
   elif t in ('ArrayProperty','SetProperty'):p['inner']=self.prop()
   elif t=='MapProperty':p['key']=self.prop();p['value']=self.prop()
   elif t=='EnumProperty':p['target']=self.ref();p['underlying']=self.prop()
   elif t not in ('IntProperty','Int64Property','Int8Property','Int16Property','UInt16Property','UInt32Property','UInt64Property','FloatProperty','DoubleProperty','NameProperty','StrProperty','TextProperty'):raise ValueError((t,n,start))
   p['end']=self.pos;return p
 results=[]
 for e in a['Exports']:
  if e['ClassIndex']>=0:continue
  classname=a['Imports'][-e['ClassIndex']-1]['ObjectName']
  if classname not in ('BlueprintGeneratedClass','UserDefinedStruct') or 'RawExport' not in e['$type']:continue
  r=Reader(base64.b64decode(e['Data']));frags=[];idx=0
  while True:
   f=r.num('H');idx+=f&127;count=f>>9
   assert not f&128,'Zero-masked class metadata needs explicit support'
   frags.extend(range(idx,idx+count));idx+=count
   if f&256:break
  metadata={}
  for idx in frags:
   if classname=='UserDefinedStruct':
    if idx==0:metadata['Status']=r.num('B')
    elif idx==1:metadata['Guid']=r.data[r.pos:r.pos+16].hex();r.pos+=16
    else:raise ValueError(('Unknown struct metadata',idx,e['ObjectName']))
   elif idx==4:metadata['ComponentTemplates']=[r.ref() for _ in range(r.num('i'))]
   elif idx==8:metadata['SimpleConstructionScript']=r.ref()
   elif idx==11:metadata['UberGraphFunction']=r.ref()
   elif idx==12:
    removed=[r.fname() for _ in range(r.num('i'))]
    entries={}
    for _ in range(r.num('i')):
     key=r.fname();entries[key]=r.data[r.pos:r.pos+16].hex();r.pos+=16
    metadata['CookedPropertyGuids']={'removed':removed,'entries':entries}
   else:raise ValueError(('Unimplemented class metadata property',idx,e['ObjectName']))
  hasguid=r.num('I');assert hasguid==0,(e['ObjectName'],hasguid)
  supername=r.ref();children=[r.ref() for _ in range(r.num('i'))]
  count=r.num('i');assert 0<=count<10000
  props=[r.prop() for _ in range(count)]
  mem=r.num('i');storage=r.num('i');assert storage==0,(e['ObjectName'],storage)
  functions={r.fname():r.ref() for _ in range(r.num('i'))} if classname=='BlueprintGeneratedClass' else {}
  results.append({'class':e['ObjectName'],'super':supername,'metadata':metadata,'properties':props,'functions':functions,'class_tail_offset':r.pos,'serial_size':len(r.data)})
 return results
results=[];failures=[]
for p in sorted((base/'decoded').glob('*-functions.json')):
 try:results.extend(read_asset(p))
 except Exception as ex:failures.append({'asset':p.stem,'error':repr(ex)})
(base/'blueprint-class-fields.json').write_text(json.dumps({'classes':results,'failures':failures},indent=2),encoding='utf8')
print('Classes',len(results),'properties',sum(len(c['properties']) for c in results))
print('Failures',failures)
