"""Read generated native reflection metadata; never executes the game."""
import pathlib,struct,json,re
base=pathlib.Path(__file__).parent
game=pathlib.Path(r'C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero\Binaries\Win64')
data=(game/'CockHero.pdb').read_bytes()
u32=lambda b,o:struct.unpack_from('<I',b,o)[0]
block,_,_,size,_,blockmap=struct.unpack_from('<6I',data,32)
ids=struct.unpack_from('<'+'I'*((size+block-1)//block),data,blockmap*block)
directory=b''.join(data[i*block:(i+1)*block] for i in ids)[:size]
n=u32(directory,0);sizes=struct.unpack_from('<'+'I'*n,directory,4);pos=4+4*n;streams=[]
for s in sizes:
 c=0 if s==0xffffffff else (s+block-1)//block
 ids=struct.unpack_from('<'+'I'*c,directory,pos) if c else []
 pos+=4*c;streams.append((s,ids))
def stream(i):
 s,ids=streams[i];return b''.join(data[x*block:(x+1)*block] for x in ids)[:s]
symbols=stream(struct.unpack_from('<H',stream(3),20)[0])
pe=(game/'CockHero.exe').read_bytes();sections=json.loads((base/'pe-sections.json').read_text());imagebase=0x140000000
def off(va):
 rva=va-imagebase
 s=next(s for s in sections if s['rva']<=rva<s['rva']+s['rawsize'])
 return s['raw']+rva-s['rva']
def q(va):return struct.unpack_from('<Q',pe,off(va))[0]
def string(va):
 a=off(va);return pe[a:pe.index(b'\0',a)].decode('utf8')
public={};at=0
while at+4<=len(symbols):
 length,kind=struct.unpack_from('<HH',symbols,at)
 if length<2 or at+length+2>len(symbols):break
 rec=symbols[at:at+length+2]
 if kind==0x110e and len(rec)>=15:
  flags,offset,segment=struct.unpack_from('<IIH',rec,4)
  if 0<segment<=len(sections):
   va=imagebase+sections[segment-1]['rva']+offset
   name=rec[14:].split(b'\0')[0].decode('utf8',errors='replace')
   public[name]=va
 at+=length+2
byva={v:k for k,v in public.items()}
schemas={}
for name,va in public.items():
 m=re.search(r'NewProp_(.+)@Z_Construct_U(?:ScriptStruct_F|Class_[UA])([^@]+)_Statics@@',name)
 if not m or not name.startswith('?NewProp_'):continue
 prop,owner=m.groups();a=off(va)
 if owner not in ('LevelData','ChallengeData','ChallengeCondition','ChallengeRequirement','CHRewardData','PlayerCardData','SessionStats','ChallengeProgress','BlueprintGeneratedClass','WidgetBlueprintGeneratedClass','GameModeBase','GameInstance','SaveGame','UserDefinedStruct','Actor','Info','PlayerItemUpgradeLevels','PlayerItemCounts','ItemUseFlags','CHPackMediaEntry','BeatPattern','BeatEvent','BeatSpawnerManager','MediaPlaybackController','ProgressionManager','SessionRewardData','CHPackManifest','CHPackInfo','DialogueLineStruct','BPComponentClassOverride','FieldNotificationId','BlueprintCookedComponentInstancingData','LatencyProfile','ActorTickFunction','TickFunction'):continue
 kind=pe[a+24]&63
 flags=struct.unpack_from('<Q',pe,a+16)[0]
 dim,offset=struct.unpack_from('<HH',pe,a+48)
 extra=struct.unpack_from('<Q',pe,a+56)[0] if kind in (0,25,30) else None
 try: propname=string(q(va))
 except (StopIteration,UnicodeDecodeError):continue
 schemas.setdefault(owner,[]).append({'symbol':name,'address':hex(va),'name':propname,'kind':kind,'flags':hex(flags),'dim':dim,'offset':offset,'extra_symbol':byva.get(extra),'extra_address':hex(extra) if extra else None})
for owner,props in schemas.items():
 pointer_symbol=next((k for k in public if any(k.startswith('?PropPointers@Z_Construct_U'+prefix+owner+'_Statics@@') for prefix in ('ScriptStruct_F','Class_U','Class_A'))),None)
 if pointer_symbol:
  addresses={int(p['address'],16):p for p in props};ptr=public[pointer_symbol];ordered=[]
  for i in range(len(props)):
   v=q(ptr+8*i)
   if v not in addresses:break
   ordered.append(addresses[v])
  if len(ordered)==len(props):schemas[owner]=ordered
(base/'native-reflection-schemas.json').write_text(json.dumps(schemas,indent=2),encoding='utf8')
enums={}
for name,va in public.items():
 m=re.search(r'^\?Enumerators@Z_Construct_UEnum_CockHero_([^@]+)_Statics@@',name)
 if not m:continue
 entries=[]
 for i in range(256):
  try:
   text=string(q(va+i*16));value=struct.unpack_from('<q',pe,off(va+i*16+8))[0]
  except (StopIteration,ValueError,UnicodeDecodeError):break
  if not text.startswith(m[1]+'::'):break
  entries.append({'name':text,'value':value})
 if entries:enums[m[1]]=entries
(base/'native-reflection-enums.json').write_text(json.dumps(enums,indent=2),encoding='utf8')
print('Recovered',len(schemas),'native struct reflection definitions')
for owner in ('LevelData','ChallengeData','ChallengeCondition','PlayerCardData'):
 print(owner,[(p['name'],p['kind'],p['extra_symbol']) for p in schemas.get(owner,[])])
