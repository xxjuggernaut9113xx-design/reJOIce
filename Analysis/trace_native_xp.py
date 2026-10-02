from pathlib import Path
import struct,json,itertools,hashlib,math
root=Path(__file__).parent
code=(root/'ghidra-progression-helpers/runtime-helpers.c').read_text()
for instruction in ['MOV dword ptr [RBX + 0x78],0x41200000','MOV dword ptr [RBX + 0x7c],0x3e3851ec','MOV dword ptr [RBX + 0x84],0x41700000','MOV dword ptr [RBX + 0x88],0x42700000','MOV dword ptr [RBX + 0x8c],0x168','MOV qword ptr [RBX + 0x90],0x3c','CVTSS2SI ECX,XMM1','SAR ECX,0x1']:
    assert instruction in code,instruction
rdata=(root/'native-rdata.bin').read_bytes()
read=lambda a:struct.unpack_from('<f',rdata,a-0x14bcab000)[0]
f32=lambda x:struct.unpack('<f',struct.pack('<f',x))[0]
floor_sse=lambda x:round(f32(f32(x+x)-read(0x14bcfdb28)))>>1
stroke_scale=struct.unpack('<f',struct.pack('<I',0x3e3851ec))[0]
fixtures=[]
for strokes,duration,edges,enemy,won,mods in itertools.product([0,5,6,100,1999,2000,10000],[0,59,60,61,600],[0,1,5],[0,59,60,61],[False,True],[[],['ironman'],['hardcore'],['IRONMAN','HARDCORE'],['Iron Man']]):
    stroke=min(floor_sse(f32(f32(strokes)*stroke_scale)),360)
    time=floor_sse(f32(f32(f32(duration)*read(0x14bcfdb20))*10.0))
    points=math.trunc(f32(f32(time+stroke+min(enemy,60))+f32(f32(edges)*15.0)))
    if won:points=math.trunc(f32(f32(points)+60.0))
    mult=read(0x14bd17818) if 'ironman' in [m.lower() for m in mods] else 1.0
    if 'hardcore' in [m.lower() for m in mods]:mult=f32(mult+read(0x14bd774a8))
    xp=floor_sse(f32(f32(points)*mult))
    fixtures.append({'stats':{'Strokes':strokes,'SessionDuration':duration,'Edges':edges,'EnemiesDefeated':enemy,'bWon':won,'ActiveModifiers':mods},'expected_xp':xp})
result={'original_game_executed':False,'fixture_count':len(fixtures),'source_sha256':hashlib.sha256(code.encode()).hexdigest(),'fixtures':fixtures,'limitations':['CalculateSessionXP only; reward preparation, challenge and save effects are excluded. SSE conversion assumes the default round-to-nearest-even mode.']}
text=json.dumps(result,indent=2)
(root/'native-xp-traces.json').write_text(text)
(root/'UnrealReconstruction/RecoveryEvidence/native-xp-traces.json').write_text(text)
print('Verified',len(fixtures),'XP instruction traces')
