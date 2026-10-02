"""Reference queue arithmetic checked against recovered native instructions and reflection."""
from pathlib import Path
import json
import struct
import math

root = Path(__file__).parent
rdata = (root/'native-rdata.bin').read_bytes()
base = int((root/'native-rdata-address.txt').read_text().strip(),16)
assert struct.unpack_from('<d',rdata,0x14bce5180-base)[0] == 1.0
assert struct.unpack_from('<I',rdata,0x14bd17880-base)[0] == 0x7fffffff
schemas = json.loads((root/'native-reflection-schemas.json').read_text())
assert {p['name']:p['offset'] for p in schemas['BeatEvent']} == {
    'AbsoluteFireTime':0,'TargetHitTime':8,'PatternIndex':16,'Interval':24,'BeatNumber':32,'CustomMultiplier':36}
rules = json.loads((root/'game-rules-draft.json').read_text())
f32 = lambda n:struct.unpack('<f',struct.pack('<f',n))[0]
fixtures = []
for bank, patterns in rules['beat_pattern_banks'].items():
    for index, pattern in enumerate(patterns):
        # Native defaults are normalized with these exact field names.
        values = pattern['IntervalMultipliers']
        for speed in [0.5,1.0,2.5]:
            queue = []
            hit = 2.0
            strokes = 0
            position = 0
            assert not values or any(v >= 0 for v in values)
            while values and strokes < 8:
                multiplier = f32(values[position])
                interval = max((1.0/f32(speed))*(abs(multiplier)*0.25),0.14)
                queue.append({'AbsoluteFireTime':hit-2.0,'TargetHitTime':hit,'PatternIndex':position,
                              'Interval':interval,'BeatNumber':len(queue)+1,'CustomMultiplier':multiplier})
                hit += interval
                if multiplier >= 0:
                    strokes += 1
                position = (position+1)%len(values)
            fixtures.append({'bank':bank,'pattern_slot':index,'multipliers':values,'base_interval':0.25,
                             'stroke_count':8,'speed':speed,'travel_time':2.0,'minimum_interval':0.14,'queue':queue})
(root/'beat-queue-traces.json').write_text(json.dumps({'fixtures':fixtures,'native_function':'0x1481d02a0',
    'original_game_executed':False,'constants_and_layout_verified':True,
    'limitations':['Native widget movement, deferred completion callback, speed-change queue rebuilding and media synchronization require separate verification.']},indent=2),encoding='utf-8')
print('Traced',len(fixtures),'native beat queues')
