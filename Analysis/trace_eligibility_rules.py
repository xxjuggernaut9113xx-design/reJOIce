from pathlib import Path
import itertools,json
from trace_state_rules import evaluate
root=Path(__file__).parent
fixtures=[]
for cooldown,coins in itertools.product([False,True],[-1,0,199,200,201]):
    fixtures.append(evaluate('StoreEventCheck',{'IsStoreOnCooldown':cooldown,'PlayerVariablesStruct.PlayerCoins':coins}))
for name in ['AssFrenzyEligibilityCheck','BoobFrenzyEligibilityCheck']:
    for enabled,heat in itertools.product([False,True],[0,1,2,255]):
        fixtures.append(evaluate(name,{'IsBrainMelterEnabled?':enabled,'HeatCategory':heat}))
for demon,frenzy,can_spawn,heat,combo in itertools.product([False,True],[False,True],[False,True],[0,1,2],[1999,2000]):
    fixtures.append(evaluate('SuccubusEligibilityCheck',{'modifier:Demon Proof':demon,'modifier:Succufrenzy':frenzy,'PlayerVariablesStruct.CanSuccubiSpawn?':can_spawn,'HeatCategory':heat,'PlayerVariablesStruct.CurrentComboCount':combo,'PlayerItemCounts.SuccubusShieldsAvailable':0,'AllSpecialEventsArray':[]}))
result={'original_game_executed':False,'fixtures':fixtures,'limitations':['Shield UI and progression effects are excluded; array-copy weight branch uses an empty source array.']}
text=json.dumps(result,indent=2)
(root/'eligibility-rule-traces.json').write_text(text,encoding='utf-8')
(root/'UnrealReconstruction/RecoveryEvidence/eligibility-rule-traces.json').write_text(text,encoding='utf-8')
print('Traced',len(fixtures),'eligibility cases')
