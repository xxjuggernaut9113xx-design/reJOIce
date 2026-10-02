from pathlib import Path
import itertools,json,struct
from trace_state_rules import evaluate
root=Path(__file__).parent
f32=lambda v:struct.unpack('<f',struct.pack('<f',v))[0]
patterns=[f['multipliers'] for f in json.loads((root/'beat-queue-traces.json').read_text())['fixtures'][::3]]
fixtures=[]
for multipliers,interval in itertools.product(patterns,[0,0.199999,0.2,0.200001,1]):
    fixtures.append(evaluate('CheckIntervalMultipliers',{'BeatPatternStruct':{'IntervalMultipliers':[f32(v) for v in multipliers]},'call:GetCurrentInterval':f32(interval)}))
text=json.dumps({'original_game_executed':False,'fixtures':fixtures,'limitations':['Only interval arrays are modeled; other beat-pattern fields are retained unchanged.']},indent=2)
(root/'pattern-adjustment-traces.json').write_text(text)
(root/'UnrealReconstruction/RecoveryEvidence/pattern-adjustment-traces.json').write_text(text)
print('Traced',len(fixtures),'pattern adjustments')
