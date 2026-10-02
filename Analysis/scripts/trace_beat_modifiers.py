"""Static instruction model; does not execute the shipping binary."""
from pathlib import Path
import json
import struct
import hashlib

root=Path(__file__).resolve().parents[1]
project=root/'UnrealReconstruction'
native=(root/'ghidra-beat-modifiers/runtime-helpers.c').read_text()
for instruction in ('1481cfb0c IMUL R13D,R14D', '1481cfbd4 MOV dword ptr [RBX + 0x104],ESI',
                    '1481d1e21 ADDSD XMM8,qword ptr [0x14bd774b8]'):
    assert instruction in native, instruction
data=(root/'native-rdata.bin').read_bytes()
delay=struct.unpack_from('<d',data,0x14bd774b8-0x14bcab000)[0]
assert delay==0.1
f32=lambda value:struct.unpack('<f',struct.pack('<f',value))[0]
fixtures=[]
original=json.loads((project/'RecoveryEvidence/beat-queue-traces.json').read_text())['fixtures']
for source in original:
    for fired in (0,1,len(source['queue'])//2):
        for factor,speed in ((1,0.77),(2,5.0),(10,0.5)):
            queue=source['queue']
            index=queue[fired]['PatternIndex']
            time=queue[fired]['AbsoluteFireTime']+0.03125
            count=(len(queue)-fired)*factor
            result=[dict(entry) for entry in queue[:fired]]
            fire=time+delay
            reciprocal=1.0/f32(speed)
            for offset in range(count):
                multiplier=f32(source['multipliers'][index])
                interval=(abs(multiplier)*source['base_interval'])*reciprocal
                if interval<=source['minimum_interval']:interval=source['minimum_interval']
                result.append({'AbsoluteFireTime':fire,'TargetHitTime':fire+source['travel_time'],
                               'PatternIndex':index,'Interval':interval,'BeatNumber':fired+offset+1,
                               'CustomMultiplier':multiplier})
                fire+=interval
                index=(index+1)%len(source['multipliers'])
            fixtures.append({'multipliers':source['multipliers'],'base_interval':source['base_interval'],
                             'speed':speed,'travel_time':source['travel_time'],'minimum_interval':source['minimum_interval'],
                             'current_time':time,'fired_entries':fired,'future_entries':count,
                             'input_queue':queue,'queue':result})
report={'original_game_executed':False,'model':'static x64 instruction model',
        'native_evidence_sha256':hashlib.sha256(native.encode()).hexdigest(),'rebuild_delay':delay,'fixtures':fixtures}
(project/'RecoveryEvidence/beat-modifier-traces.json').write_text(json.dumps(report,separators=(',',':')),encoding='utf-8')
(project/'RecoveryEvidence/native-beat-modifiers.c').write_text(native,encoding='utf-8')
print('Beat modifier fixtures:',len(fixtures))
