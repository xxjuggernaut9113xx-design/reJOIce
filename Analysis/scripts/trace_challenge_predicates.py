"""Independent static models of native signed comparisons, SSE progress and condition gates."""
from pathlib import Path
import json
import struct
import ctypes
import itertools
import hashlib

root=Path(__file__).resolve().parents[1]
project=root/'UnrealReconstruction'
native=(root/'ghidra-challenge-rules/runtime-helpers.c').read_text()
required=['1481b49bd SETGE AL','1481b49b2 SETLE AL','1481b49a7 SETZ AL','1481b499c SETG AL','1481b4991 SETL AL',
          '1481c26a4 SUBSS XMM0,XMM1','1481c26c5 DIVSS XMM0,XMM1','1481b4ed6 JG 0x1481b4ee1']
for instruction in required:assert instruction in native,instruction
f32=lambda v:struct.unpack('<f',struct.pack('<f',v))[0]
names=['GreaterOrEqual','LessOrEqual','Equal','Greater','Less','Unknown']
def compare(current,target,name):
    return {'GreaterOrEqual':current>=target,'LessOrEqual':current<=target,'Equal':current==target,
            'Greater':current>target,'Less':current<target}.get(name,False)
def percent(current,target,name):
    if target<=0:return 1.0
    if name not in names[:5]:return 0.0
    value=f32(f32(current)/f32(target))
    if name in ('LessOrEqual','Less'):value=f32(1.0-value)
    return max(0.0,min(value,1.0))
requirements=[]
for name,target,current in itertools.product(names,[-1,0,1,2,15,100,2147483647],[-2147483648,-1,0,1,2,14,15,99,100,2147483647]):
    requirements.append({'requirements':[{'MetricType':'EMetricType::Edges','TargetValue':target,'CurrentValue':current,'ComparisonType':'EComparisonType::'+name}],
                         'expected_met':compare(current,target,name),'progress':[percent(current,target,name)]})
table=json.loads((root/'progression-tables.json').read_text())['DT_Challenges']
for row in table:
    for offset in (-1,0,1):
        items=[dict(r,CurrentValue=r['TargetValue']+offset) for r in row['Requirements']]
        requirements.append({'challenge':row['ChallengeID'],'requirements':items,
                             'expected_met':all(compare(r['CurrentValue'],r['TargetValue'],r['ComparisonType'].split('::')[-1]) for r in items),
                             'progress':[percent(r['CurrentValue'],r['TargetValue'],r['ComparisonType'].split('::')[-1]) for r in items]})
requirements.append({'requirements':[],'expected_met':True,'progress':[]})
wtoi=ctypes.CDLL('ucrtbase')._wtoi;wtoi.argtypes=[ctypes.c_wchar_p];wtoi.restype=ctypes.c_int
def condition_met(items,active,used,duration):
    for condition in items:
        kind=condition['ConditionType'].lower();value=condition['ConditionValue']
        if kind=='modifier' and value.lower() not in [m.lower() for m in active]:return False
        if kind=='no_items' and used>0:return False
        if kind=='max_time' and duration>wtoi(value):return False
    return True
conditions=[]
def add(items,active,used,duration):
    conditions.append({'conditions':items,'active_modifiers':active,'items_used':used,'duration':duration,
                       'expected_met':condition_met(items,active,used,duration)})
for row in table:
    items=row['Conditions'];modifiers=[c['ConditionValue'] for c in items if c['ConditionType']=='modifier']
    for active in (modifiers,modifiers[1:],[v.upper() for v in modifiers],[v.strip() for v in modifiers],[v+' ' for v in modifiers]):
        add(items,active,0,100)
for kind,value,used,duration in itertools.product(['no_items','NO_ITEMS','max_time','unknown'],['','60','  +60junk','-1','invalid'],[-1,0,1],[0,59,60,61]):
    add([{'ConditionType':kind,'ConditionValue':value}],[],used,duration)
report={'original_game_executed':False,'model':'native signed branch and float32 instruction model',
        'requirements':requirements,'conditions':conditions,'native_sha256':hashlib.sha256(native.encode()).hexdigest()}
(project/'RecoveryEvidence/challenge-predicate-traces.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
(project/'RecoveryEvidence/native-challenge-rules.c').write_text(native,encoding='utf-8')
print('Challenge predicate fixtures:',len(requirements),len(conditions),'total',len(requirements)+len(conditions))
