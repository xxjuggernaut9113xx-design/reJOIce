from pathlib import Path
import itertools,json
from trace_state_rules import evaluate
root=Path(__file__).parent
records=[{'EventName':i,'BaseWeight':float(i+1),'WeightMultiplier':0.0,'IsEligible':False,'IsOnCooldown':True} for i in list(range(32))+[8,3]]
fixtures=[]
for succu,body,store,temptation,mercy in itertools.product([False,True],repeat=5):
    inputs={'AllSpecialEventsArray':records,'EligibleSpecialEvents':[],
            'outcall:SuccubusEligibilityCheck':succu,'outcall:AssFrenzyEligibilityCheck':body,'outcall:BoobFrenzyEligibilityCheck':body,'outcall:StoreEventCheck':store,'outcall:TemptationEligibilityCheck':temptation,'outcall:MercyEligibilityCheck':mercy}
    trace=evaluate('CheckEventConditions_ReturnArray',inputs,modeled_calls=['SlowStrokeEventCheck','MediumStrokeEventCheck','FastStrokeEventCheck'])
    fixtures.append({'checks':dict(Succubus=succu,Body=body,Store=store,Temptation=temptation,Mercy=mercy),'trace':trace})
result={'original_game_executed':False,'source_records':records,'fixtures':fixtures,'limitations':['Child eligibility query outputs are injected. Child query rules have separate fixtures; presentation effects are excluded.']}
text=json.dumps(result,indent=2)
for path in [root/'event-filter-traces.json',root/'UnrealReconstruction/RecoveryEvidence/event-filter-traces.json']:path.write_text(text)
print('Traced',len(fixtures),'event filter cases')
