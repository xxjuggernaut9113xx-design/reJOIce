"""Independent UE5.3 unversioned-property decoder with strict payload checks."""
import json,pathlib,struct,base64
base=pathlib.Path(__file__).parent
bp=json.loads((base/'blueprint-class-fields.json').read_text())['classes']
native=json.loads((base/'native-reflection-schemas.json').read_text())
schemas={c['class']:c['properties'] for c in bp}
supers={c['class']:c['super'] for c in bp};supers.update(GameModeBase='Info',Info='Actor',ActorTickFunction='TickFunction')
types={0:'ByteProperty',1:'Int8Property',2:'Int16Property',3:'IntProperty',4:'Int64Property',5:'UInt16Property',6:'UInt32Property',7:'UInt64Property',10:'FloatProperty',11:'DoubleProperty',12:'BoolProperty',13:'SoftObjectProperty',14:'ObjectProperty',15:'ObjectProperty',16:'SoftObjectProperty',17:'ObjectProperty',18:'ObjectProperty',19:'ObjectProperty',20:'NameProperty',21:'StrProperty',22:'ArrayProperty',23:'MapProperty',24:'SetProperty',25:'StructProperty',26:'DelegateProperty',27:'DelegateProperty',28:'DelegateProperty',29:'TextProperty',30:'EnumProperty'}
def nt(p,children=[]):
 d={'name':p['name'],'type':types[p['kind']],'array_dim':1}
 if p['kind'] in (25,30):
  import re
  pat=r'Z_Construct_UScriptStruct_F([^@]+)' if p['kind']==25 else r'Z_Construct_UEnum_[^_]+_([^@]+)'
  m=re.search(pat,p['extra_symbol'] or '');assert m,p;d['target']=m[1]
 if p['kind']==0 and p['extra_symbol']:
  import re
  m=re.search(r'Z_Construct_UEnum_[^_]+_([^@]+)',p['extra_symbol']);d['target']=m[1] if m else None
 if p['kind'] in (22,24):
  assert children,('Missing container inner metadata',p)
  d['inner']=nt(children[0])
 if p['kind']==23:d['key']=nt(children[1]);d['value']=nt(children[0])
 if p['kind']==30:d['underlying']=nt(children[0])
 return d
for name,props in native.items():
 result=[];pending=[]
 for p in props:
  if any(s in p['symbol'] for s in ('_Inner@','_Underlying@','_ValueProp@','_KeyProp@','_Key@','_Value@','_ElementProp@')) and not p['symbol'].startswith(('?NewProp_Value@','?NewProp_Key@')):pending.append(p);continue
  if not int(p['flags'],16)&0x800000000:result.append(nt(p,pending))
  pending=[]
 schemas[name]=result
schemas.update(PointerToUberGraphFrame=[],SaveGame=[],Info=[],ActorTickFunction=[],TimerHandle=[{'name':'Handle','type':'UInt64Property'}])
def allprops(name):return schemas[name]+(allprops(supers[name]) if supers.get(name) else [])
class Reader:
 def __init__(self,data,asset):self.data=data;self.asset=asset;self.pos=0;self.trace=[];self.headers=[];self.strings=[]
 def num(self,f):v=struct.unpack_from('<'+f,self.data,self.pos)[0];self.pos+=struct.calcsize('<'+f);return v
 def name(self):
  i=self.num('i');n=self.num('i');assert 0<=i<len(self.asset['NameMap']),(self.pos,i)
  text=self.asset['NameMap'][i];return text+('_'+str(n-1) if n else '')
 def string(self):
  n=self.num('i');assert abs(n)<1000000,(self.pos,n)
  self.strings.append(n)
  if not n:return ''
  size=n if n>0 else -n*2;b=self.data[self.pos:self.pos+size];assert len(b)==size;self.pos+=size
  return b.decode('utf8' if n>0 else 'utf-16le').rstrip('\0')
 def ref(self):
  i=self.num('i')
  if not i:return None
  pool=self.asset['Exports'] if i>0 else self.asset['Imports'];e=pool[i-1 if i>0 else -i-1]
  return {'index':i,'name':e['ObjectName']}
 def properties(self,schema):
  fields=allprops(schema);fragments=[];packed=[];index=0;zeroes=0
  while True:
   f=self.num('H');packed.append(f);index+=f&127;n=f>>9;mask=bool(f&128)
   fragments.append((index,n,mask));index+=n
   if mask:zeroes+=n
   if f&256:break
  bits=0
  if zeroes:
   size=1 if zeroes<=8 else 2 if zeroes<=16 else ((zeroes+31)//32)*4
   bits=int.from_bytes(self.data[self.pos:self.pos+size],'little');self.pos+=size
  self.headers.append({'schema':schema,'packed':packed,'fragments':fragments,'zeroes':zeroes,'bits':bits})
  result={};bit=0
  for index,n,mask in fragments:
   for i in range(index,index+n):
    assert i<len(fields),(schema,i,len(fields),self.pos)
    zero=mask and bool(bits>>bit&1)
    if mask:bit+=1
    prop=fields[i];start=self.pos;result[prop['name']]=self.value(prop,zero)
    self.trace.append({'schema':schema,'field':prop['name'],'index':i,'start':start,'end':self.pos,'zero':zero})
  return result
 def value(self,p,zero=False):
  t=p['type'];fmt={'ByteProperty':'B','BoolProperty':'B','Int8Property':'b','Int16Property':'h','IntProperty':'i','Int64Property':'q','UInt16Property':'H','UInt32Property':'I','UInt64Property':'Q','FloatProperty':'f','DoubleProperty':'d'}
  if t in fmt:return False if zero and t=='BoolProperty' else 0 if zero else self.num(fmt[t])
  if t=='EnumProperty':return {'enum':p['target'],'value':self.value(p['underlying'],zero)}
  if t=='NameProperty':return None if zero else self.name()
  if t=='StrProperty':return '' if zero else self.string()
  if t=='ObjectProperty':return None if zero else self.ref()
  if t=='SoftObjectProperty':return None if zero else {'package':self.name(),'asset':self.name(),'subpath':self.string()}
  if t=='DelegateProperty':return None if zero else {'object':self.ref(),'function':self.name()}
  if t in ('ArrayProperty','SetProperty'):
   if zero:return []
   if t=='SetProperty':assert self.num('i')==0,'Removed set items require handling'
   n=self.num('i');assert 0<=n<100000,(self.pos,n)
   return [self.value(p['inner']) for _ in range(n)]
  if t=='MapProperty':
   if zero:return []
   removed=[self.value(p['key']) for _ in range(self.num('i'))]
   entries=[[self.value(p['key']),self.value(p['value'])] for _ in range(self.num('i'))]
   return {'removed':removed,'entries':entries}
  if t=='StructProperty':
   target=p['target']
   if zero:return {'zero_initialized_struct':target}
   if target=='Guid':v=self.data[self.pos:self.pos+16].hex();self.pos+=16;return v
   if target=='DateTime':return {'ticks':self.num('q')}
   if target=='LinearColor':return dict(zip('RGBA',[self.num('f') for _ in range(4)]))
   if target=='Vector':return dict(zip('XYZ',[self.num('d') for _ in range(3)]))
   if target=='Vector4':return dict(zip('XYZW',[self.num('d') for _ in range(4)]))
   if target=='Rotator':return dict(zip(('Pitch','Yaw','Roll'),[self.num('d') for _ in range(3)]))
   if target in ('Vector2D','Vector2d','Vector2f','DeprecateSlateVector2D'):
    return dict(zip('XY',[self.num('f' if target in ('Vector2f','DeprecateSlateVector2D') else 'd') for _ in range(2)]))
   return self.properties(target)
  if t=='TextProperty':
   if zero:return ''
   flags=self.num('I');history=self.num('b')
   if history==-1:
    invariant=self.num('I');assert invariant in (0,1)
    return {'flags':flags,'history':'None','text':self.string() if invariant else ''}
   if history==0:return {'flags':flags,'namespace':self.string(),'key':self.string(),'text':self.string()}
   raise ValueError(('Unsupported FText history',history,self.pos))
  raise ValueError(('Unsupported property',p,self.pos))
class Writer:
 def __init__(self,reader):self.asset=reader.asset;self.headers=iter(reader.headers);self.strings=iter(reader.strings);self.data=bytearray()
 def num(self,f,v):self.data+=struct.pack('<'+f,v)
 def name(self,v):
  names=self.asset['NameMap']
  if v in names:i=names.index(v);n=0
  else:
   stem,suffix=v.rsplit('_',1);i=names.index(stem);n=int(suffix)+1
  self.num('i',i);self.num('i',n)
 def string(self,v):
  original=next(self.strings)
  if original==0:self.num('i',0);return
  wide=original<0;encoded=(v+'\0').encode('utf-16le' if wide else 'utf8')
  self.num('i',-len(encoded)//2 if wide else len(encoded));self.data+=encoded
 def properties(self,schema,values):
  plan=next(self.headers);assert plan['schema']==schema
  for f in plan['packed']:self.num('H',f)
  n=plan['zeroes']
  if n:
   size=1 if n<=8 else 2 if n<=16 else ((n+31)//32)*4
   self.data+=plan['bits'].to_bytes(size,'little')
  fields=allprops(schema);bit=0
  for index,count,mask in plan['fragments']:
   for i in range(index,index+count):
    zero=mask and bool(plan['bits']>>bit&1)
    if mask:bit+=1
    p=fields[i];self.value(p,values[p['name']],zero)
 def value(self,p,v,zero=False):
  if zero:return
  t=p['type'];fmt={'ByteProperty':'B','BoolProperty':'B','Int8Property':'b','Int16Property':'h','IntProperty':'i','Int64Property':'q','UInt16Property':'H','UInt32Property':'I','UInt64Property':'Q','FloatProperty':'f','DoubleProperty':'d'}
  if t in fmt:self.num(fmt[t],v)
  elif t=='EnumProperty':self.value(p['underlying'],v['value'])
  elif t=='NameProperty':self.name(v)
  elif t=='StrProperty':self.string(v)
  elif t=='ObjectProperty':self.num('i',v['index'] if v else 0)
  elif t=='SoftObjectProperty':self.name(v['package']);self.name(v['asset']);self.string(v['subpath'])
  elif t=='DelegateProperty':self.num('i',v['object']['index'] if v['object'] else 0);self.name(v['function'])
  elif t in ('ArrayProperty','SetProperty'):
   if t=='SetProperty':self.num('i',0)
   self.num('i',len(v))
   for x in v:self.value(p['inner'],x)
  elif t=='MapProperty':
   self.num('i',len(v['removed']))
   for x in v['removed']:self.value(p['key'],x)
   self.num('i',len(v['entries']))
   for key,val in v['entries']:self.value(p['key'],key);self.value(p['value'],val)
  elif t=='StructProperty':
   target=p['target']
   if target=='Guid':self.data+=bytes.fromhex(v)
   elif target=='DateTime':self.num('q',v['ticks'])
   elif target in ('LinearColor','Vector','Vector4','Rotator'):
    keys='RGBA' if target=='LinearColor' else 'XYZ' if target=='Vector' else 'XYZW' if target=='Vector4' else ('Pitch','Yaw','Roll')
    for key in keys:self.num('f' if target=='LinearColor' else 'd',v[key])
   elif target in ('Vector2D','Vector2d','Vector2f','DeprecateSlateVector2D'):
    for key in 'XY':self.num('f' if target in ('Vector2f','DeprecateSlateVector2D') else 'd',v[key])
   else:self.properties(target,v)
  elif t=='TextProperty':
   self.num('I',v['flags']);self.num('b',-1 if v.get('history')=='None' else 0)
   if v.get('history')=='None':
    self.num('I',bool(v['text']))
    if v['text']:self.string(v['text'])
   else:self.string(v['namespace']);self.string(v['key']);self.string(v['text'])
  else:raise ValueError(('Unsupported writer property',p))
results=[];failures=[];checks=[]
for path in sorted((base/'decoded').glob('BP_*-functions.json')):
 a=json.loads(path.read_text(encoding='utf8'))
 for e in a['Exports']:
  if not e['ObjectName'].startswith('Default__'):continue
  cls=e['ObjectName'].removeprefix('Default__')
  if not isinstance(e.get('Data'),str):continue
  r=Reader(base64.b64decode(e['Data']),a)
  try:
   values=r.properties(cls);guid=r.num('I');assert guid==0
   assert r.pos==len(r.data),(r.pos,len(r.data))
   w=Writer(r);w.properties(cls,values);w.num('I',guid)
   import hashlib
   checks.append({'object':e['ObjectName'],'bytes':len(r.data),'original_sha256':hashlib.sha256(r.data).hexdigest(),'rebuilt_sha256':hashlib.sha256(w.data).hexdigest(),'identical':r.data==w.data})
   assert r.data==w.data,'Independent value writer round trip mismatch'
   results.append({'object':e['ObjectName'],'class':cls,'serialized_properties':values,'consumed_bytes':r.pos,'payload_bytes':len(r.data)})
  except Exception as ex:failures.append({'object':e['ObjectName'],'offset':r.pos,'error':repr(ex),'recent_fields':r.trace[-12:],'next_bytes':r.data[r.pos:r.pos+40].hex()})
(base/'blueprint-default-values.json').write_text(json.dumps({'objects':results,'failures':failures},indent=2),encoding='utf8')
(base/'default-roundtrip-check.json').write_text(json.dumps(checks,indent=2),encoding='utf8')
print('Complete default objects',len(results));print('Failures',failures)
