"""Recover newer PE/PDB native reflection using new addresses only; static, read-only inputs."""
from pathlib import Path
import json,struct,re
root=Path(__file__).resolve().parents[1]
dest=root/'ReferenceBuilds/newer-20261017'
source=(root/'recover_native_schemas.py').read_text(encoding='utf8')
source=source.replace("base=pathlib.Path(__file__).parent", "base=pathlib.Path(r'"+str(dest)+"')")
source=source.replace("C:\\Users\\webma\\Downloads\\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\\PrepV2\\Windows\\CockHero\\Binaries\\Win64", "C:\\Users\\webma\\Downloads\\cock-hero-windows (1)\\Windows\\CockHero\\Binaries\\Win64")
old="sections=json.loads((base/'pe-sections.json').read_text());imagebase=0x140000000"
new="""peoff=u32(pe,0x3c);opt=peoff+24;imagebase=struct.unpack_from('<Q',pe,opt+24)[0]
sections=[]
for idx in range(struct.unpack_from('<H',pe,peoff+6)[0]):
 a=opt+struct.unpack_from('<H',pe,peoff+20)[0]+40*idx
 sections.append(dict(name=pe[a:a+8].rstrip(b'\\0').decode(),rva=u32(pe,a+12),rawsize=u32(pe,a+16),raw=u32(pe,a+20)))
(base/'pe-sections.json').write_text(json.dumps(sections,indent=2),encoding='utf8')"""
assert old in source;source=source.replace(old,new)
lines=source.splitlines()
lines=[(" if not re.search(r'^Actor$|^Info$|Item|Round|Music|Beat|Challenge|Reward|PlayerCard|LevelData|Session|Succu|Progression|BlueprintGeneratedClass|UserDefinedStruct|SaveGame|GameInstance|GameModeBase|ActorTickFunction|TickFunction|Dialogue|CHPack|Objective|DifficultyTier|VoicePacks',owner):continue" if line.startswith(' if owner not in (') else line) for line in lines]
source='\n'.join(lines)
source=source.replace('for owner,props in schemas.items():', "pointer_symbols={}\nfor k in public:\n m=re.match(r'^\\?PropPointers@Z_Construct_U(?:ScriptStruct_F|Class_U|Class_A)([^@]+)_Statics@@',k)\n if m:pointer_symbols[m[1]]=k\nfor owner,props in schemas.items():")
source='\n'.join(' pointer_symbol=pointer_symbols.get(owner)' if line.startswith(' pointer_symbol=next(') else line for line in source.splitlines())
source=source.replace("byva={v:k for k,v in public.items()}","""print('Parsed newer public symbols',len(public),flush=True)
music_symbols=[{'name':name,'address':hex(address),'file_offset':off(address)} for name,address in public.items() if re.search(r'@U(?:MusicModeManager|[A-Za-z0-9_]*[Bb]eatmap[A-Za-z0-9_]*)@@',name) and re.match(r'^\\?[^@]+@U',name)]
music_symbols.sort(key=lambda item:int(item['address'],16))
(base/'native-music-symbol-addresses.json').write_text(json.dumps(music_symbols,indent=2),encoding='utf8')
(base/'native-music-symbol-addresses.tsv').write_text(''.join(item['address']+'\\t'+item['name']+'\\n' for item in music_symbols),encoding='utf8')
byva={v:k for k,v in public.items()}""")
exec(compile(source,str(root/'recover_native_schemas.py'),'exec'),{'__file__':str(dest/'recover_native_schemas.py')})
