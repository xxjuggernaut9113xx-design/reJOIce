"""Compose independently evaluated original heat/combo functions in source call order."""
from pathlib import Path
import json,itertools
from trace_state_rules import evaluate
root=Path(__file__).parent
heat_functions=['Update_Fast_Heat_Weights','Update_Medium_Heat_Weights','Update_Slow_Heat_Weights']
combo_functions=['UpdateFTierComboWeights','UpdateDTierComboWeights','UpdateCTierComboWeights','UpdateBTierComboWeights','UpdateATierComboWeights','UpdateSTierComboWeights']
fixtures=[]
defaults=json.loads((root/'struct-default-values.json').read_text())['SpecialEventDataStruct']['defaults']
def run(name,event,weight):
    inputs={'SpecialEventInput':{'EventName':event,'BaseWeight':weight},'SpecialEventInput.EventName':event,'SpecialEventInput.BaseWeight':weight}
    data=json.loads((root/'blueprint-functions/BP_GlobalManager'/(name+'.json')).read_text())
    for field in data['function']['fields']:
        if field.startswith('K2Node_SetFieldsInStruct_StructOut') or field in ('Local Eligible Event','SpecialEventModified'):inputs[field]=defaults
    return evaluate(name,inputs)['writes'].get('SpecialEventModified',defaults)
for heat,tier,event in itertools.product(range(3),range(8),range(32)):
    expected=[]
    if tier<6:
        stage=run(heat_functions[heat],event,1.0)
        stage=run(combo_functions[tier],stage['EventName'],stage['BaseWeight'])
        expected=[stage]
    fixtures.append({'HeatCategory':heat,'ComboTier':tier,'EventName':event,'BaseWeight':1.0,'expected':expected})
result={'original_game_executed':False,'fixtures':fixtures,'limitations':['Heat/combo arithmetic is traced separately and composed in the verified caller order. Full random draw and event execution are excluded.']}
text=json.dumps(result,indent=2)
for path in [root/'weight-pipeline-traces.json',root/'UnrealReconstruction/RecoveryEvidence/weight-pipeline-traces.json']:path.write_text(text)
print('Traced',len(fixtures),'composed weight cases')
