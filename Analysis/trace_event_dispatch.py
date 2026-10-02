from pathlib import Path
import itertools,json
from trace_state_rules import evaluate
root=Path(__file__).parent
actions=['PostEdgeSlow','PostEdgeFast','SlowStrokeEvent','MediumStrokeEvent','FastStrokeEvent','TemptationEvent','SpawnSuccubus','MercyEvent','AssFrenzyEvent','BoobFrenzyEvent','SpawnStoreEvent','VideoLoopStrokeEvent']
fixtures=[]
for succu,slow,double,event,roll in itertools.product([False,True],[False,True],[False,True],list(range(32))+[255],[0,1,2]):
    fixtures.append(evaluate('TriggerSelectedEvent',{'outcall:Is Succu Frenzy Active':succu,'outcall:Is Slow and Steady Active':slow,'outcall:Is Double Time Active':double,'FoundEvent.EventName':event,'GlobalManager.IdleTimerHandle':0,'call:RandomIntegerInRange':roll},owner='BP_DrawManager',modeled_calls=actions+['K2_ClearAndInvalidateTimerHandle']))
result={'original_game_executed':False,'fixtures':fixtures,'limitations':['Modifier-query results and random draws are injected; dispatched event bodies are not executed by these fixtures.']}
text=json.dumps(result,indent=2)
(root/'event-dispatch-traces.json').write_text(text,encoding='utf-8')
(root/'UnrealReconstruction/RecoveryEvidence/event-dispatch-traces.json').write_text(text,encoding='utf-8')
print('Traced',len(fixtures),'dispatch cases')
