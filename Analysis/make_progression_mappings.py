"""Generate mappings from PDB-matched native reflection and installed UE5.3 headers."""
import json,pathlib,struct,re
base=pathlib.Path(__file__).parent
native=json.loads((base/'native-reflection-schemas.json').read_text())
enums=json.loads((base/'native-reflection-enums.json').read_text())
kindmap={0:0,1:23,2:22,3:2,4:21,5:20,6:19,7:18,10:3,11:7,12:1,13:17,14:14,15:15,16:17,17:4,18:4,19:12,20:5,21:10,26:6,27:13,28:13,29:11}
names=[]
def ni(n):
 if n is None:return -1
 if n not in names:names.append(n)
 return names.index(n)
def target(p,kind):
 match=re.search(r'Z_Construct_U'+('ScriptStruct_F' if kind=='struct' else 'Enum_[^_]+_')+r'([^@]+)',p['extra_symbol'] or '')
 if not match:raise ValueError(p)
 return match[1]
def tp(p,children):
 k=p['kind']
 if k==25:return bytes([9])+struct.pack('<i',ni(target(p,'struct')))
 if k==30:return bytes([26])+tp(children[0],[])+struct.pack('<i',ni(target(p,'enum')))
 if k==22:return bytes([8])+tp(children[0],[])
 if k==23:return bytes([24])+tp(children[1],[])+tp(children[0],[])
 if k==24:return bytes([25])+tp(children[0],[])
 return bytes([kindmap[k]])
schemas={'Function':[],'DataTable':[(n,bytes([t])) for n,t in [('RowStruct',4),('bStripFromClientBuilds',1),('bIgnoreExtraFields',1),('bIgnoreMissingFields',1),('ImportKeyField',10)]]}
for owner,props in native.items():
 result=[];pending=[]
 for p in props:
  # Generated inner/underlying properties precede their owning container in PropPointers.
  if any(s in p['symbol'] for s in ('_Inner@','_Underlying@','_Key@','_Value@','_ValueProp@','_KeyProp@')):
   pending.append(p);continue
  if not int(p['flags'],16)&0x0000000800000000:
   result.append((p['name'],tp(p,pending)))
  pending=[]
 if pending:raise ValueError(('unconsumed nested properties',owner,pending))
 schemas[owner]=result
supers={'GameModeBase':'Info','Info':'Actor','Actor':None,'GameInstance':None,'SaveGame':None}
schemas.setdefault('SaveGame',[])
schemas.setdefault('Info',[])
schemas.setdefault('PointerToUberGraphFrame',[])
schemas.setdefault('TimerHandle',[('Handle',bytes([18]))])
blueprint_fields=base/'blueprint-class-fields.json'
if blueprint_fields.exists():
 blueprint=json.loads(blueprint_fields.read_text())
 typeids={'ByteProperty':0,'BoolProperty':1,'IntProperty':2,'FloatProperty':3,'ObjectProperty':4,'NameProperty':5,'DelegateProperty':6,'DoubleProperty':7,'ArrayProperty':8,'StructProperty':9,'StrProperty':10,'TextProperty':11,'InterfaceProperty':12,'MulticastInlineDelegateProperty':13,'WeakObjectProperty':14,'LazyObjectProperty':15,'SoftObjectProperty':17,'UInt64Property':18,'UInt32Property':19,'UInt16Property':20,'Int64Property':21,'Int16Property':22,'Int8Property':23,'MapProperty':24,'SetProperty':25,'EnumProperty':26,'ClassProperty':4,'SoftClassProperty':17}
 def bptype(p):
  t=p['type'];data=bytes([typeids[t]])
  if t=='StructProperty':data+=struct.pack('<i',ni(p['target']))
  elif t in ('ArrayProperty','SetProperty'):data+=bptype(p['inner'])
  elif t=='MapProperty':data+=bptype(p['key'])+bptype(p['value'])
  elif t=='EnumProperty':data+=bptype(p['underlying'])+struct.pack('<i',ni(p['target']))
  return data
 for c in blueprint['classes']:
  schemas[c['class']]=[(p['name'],bptype(p)) for p in c['properties'] if not int(p['flags'],16)&0x0000000800000000]
  supers[c['class']]=c['super']
  ni(c['super'])
for owner,props in schemas.items():
 ni(owner)
 for n,_ in props:ni(n)
for owner,entries in enums.items():
 ni(owner)
 for e in entries:ni(e['name'])
body=struct.pack('<I',len(names))
for name in names:
 b=name.encode('utf8');body+=struct.pack('<H',len(b))+b
body+=struct.pack('<I',len(enums))
for owner,entries in enums.items():
 body+=struct.pack('<iH',ni(owner),len(entries))
 for e in entries:body+=struct.pack('<qi',e['value'],ni(e['name']))
body+=struct.pack('<I',len(schemas))
for owner,props in schemas.items():
 body+=struct.pack('<iiHH',ni(owner),ni(supers.get(owner)),len(props),len(props))
 for i,(n,t) in enumerate(props):body+=struct.pack('<HBi',i,1,ni(n))+t
data=struct.pack('<HBiBII',0x30c4,4,0,0,len(body),len(body))+body
targetpath=pathlib.Path.home()/'AppData/Local/UAssetGUI/Mappings/CockHeroProgression.usmap'
targetpath.write_bytes(data)
(base/'progression-schema-fields.json').write_text(json.dumps({k:[n for n,_ in v] for k,v in schemas.items()},indent=2),encoding='utf8')
print(targetpath,'schemas',len(schemas),'enums',len(enums))
