from pathlib import Path
import json,itertools
from trace_state_rules import evaluate
root=Path(__file__).parent
graph=json.loads((root/'main-event-graph.json').read_text())
entries={e['event']:e['entry_statement'] for e in graph['event_entries']}
fixtures=[]
external=['UpdateMetric','K2_ClearAndInvalidateTimerHandle','CreateNotificationBox','Change Beat Background','AddToViewport','Set Dialogue and Play Voiceline','ApplySpeedModifier','ApplyStrokeCountModifier','PlaySpecialEventDialogue','ApplyIronManPenalty','Delay']
for event,card,taunted,iron in itertools.product(['SuccessfulCum','PrematureCum'],[0,3,5,6,9],[False,True],[False,True]):
    inputs={'CurrentCardTypeEnum':card,'HasTaunted?':taunted,'modifier:Iron Man':iron,
            'PlayerVariablesStruct.CurrentComboCount':123,'PlayerVariablesStruct.BrokenComboArray':[10,20],
            'PlayerVariablesStruct.EdgeStreak':7,'PlayerVariablesStruct.CanDraw?':False,'PlayerVariablesStruct.HasCame?':False,
            'PlayerVariablesStruct.CanUseItems?':True,'EdgingManager.EdgeHoldTimerHandle':0,
            'call:Create':'created-widget','call:PlayAnimation':None,'outcall:FindSpecialEventDialogueStructs':[],'UIManager.EarlyCumAnim':None}
    fixtures.append({'event':event,'trace':evaluate('ExecuteUbergraph_BP_GlobalManager',inputs,modeled_calls=external,start_index=entries[event])})
result={'original_game_executed':False,'fixtures':fixtures,'limitations':['Only synchronous entry-point state and external call requests are evaluated. UI, dialogue, devices, delayed continuation and complete postgame rewards are excluded.']}
text=json.dumps(result,indent=2)
for path in [root/'outcome-traces.json',root/'UnrealReconstruction/RecoveryEvidence/outcome-traces.json']:path.write_text(text)
print('Traced',len(fixtures),'outcome cases')
