"""Static native instruction model: no original executable is run."""
from pathlib import Path
import struct,json,hashlib,itertools
root=Path(__file__).parent
code=(root/'ghidra-level-rules/runtime-helpers.c').read_text()
for instruction in ['1481c331b MOVDQA XMM6,xmmword ptr [0x14cf77870]','1481c3425 MOV EBX,0xf423f','1481c3420 MOV EBX,dword ptr [RCX + RAX*0x4]','1481b4f29 CMP dword ptr [RCX + 0x50],0x14','1481b4f5c SUB EDX,EAX','1481b4f65 MOV dword ptr [RSI + 0x50],R8D','1481b4202 JLE 0x1481b4297','1481b4221 ADD dword ptr [RCX + 0x40],EDX','1481b4224 ADD dword ptr [RCX + 0x54],EDX']:
    assert instruction in code,instruction
data=(root/'native-rdata.bin').read_bytes()
thresholds=struct.unpack_from('<20i',data,0x14cf77870-0x14bcab000)
wrap=lambda n:(n+2**31)%2**32-2**31
f32=lambda n:struct.unpack('<f',struct.pack('<f',n))[0]
rows={row['row']:row for row in json.loads((root/'progression-tables.json').read_text())['DT_LevelData']}
fixtures=[]
for level,xp,total,points,amount,table in itertools.product([-1,0,1,2,10,19,20,21],[0,99,100,119,120,9999,2147483640],[0,2147483640],[0,2147483640],[-1,0,1,100,10000],[False,True]):
    inputs=dict(CurrentLevel=level,CurrentXP=xp,TotalXPEarned=total,UnlockPoints=points,Amount=amount,TableEnabled=table)
    rewards=[];progress=False
    if amount>0:
        xp=wrap(xp+amount);total=wrap(total+amount)
        if level<20:
            progress=True
            required=thresholds[level-1] if 1<=level<=20 else 999999
            while xp>=required and level<20:
                xp=wrap(xp-required);level=wrap(level+1)
                row_name=f'Level_{level}'
                if table and row_name in rows:
                    reward=rows[row_name]['UnlockPointsReward'];points=wrap(points+reward);rewards.append(level)
                required=thresholds[level-1] if 1<=level<=20 else 999999
    required=thresholds[level-1] if 1<=level<=20 else 999999
    ratio=min(max(f32(f32(xp)/f32(required)),0.0),1.0)
    fixtures.append({'input':inputs,'expected':dict(CurrentLevel=level,CurrentXP=xp,TotalXPEarned=total,UnlockPoints=points,LevelRewardEvents=rewards,ProgressEvent=progress,LevelProgress=ratio,XPEvent=amount>0,MetricEvent=amount>0)})
result={'original_game_executed':False,'source_sha256':hashlib.sha256(code.encode()).hexdigest(),'thresholds':thresholds,'fixture_count':len(fixtures),'fixtures':fixtures,'limitations':['Native XP, level and unlock-point arithmetic only. Reward consumers, challenge execution and persistence are excluded.']}
text=json.dumps(result,indent=2)
for path in [root/'native-level-traces.json',root/'UnrealReconstruction/RecoveryEvidence/native-level-traces.json']:path.write_text(text)
print('Verified',len(fixtures),'native level cases')
