from pathlib import Path
import json
from trace_state_rules import evaluate

root = Path(__file__).parent
functions = ['Update' + tier + 'TierComboWeights' for tier in ['F','D','C','B','A','S']]
functions += ['Update_Slow_Heat_Weights','Update_Medium_Heat_Weights','Update_Fast_Heat_Weights']
fixtures = []
table = {}
defaults = json.loads((root/'struct-default-values.json').read_text())['SpecialEventDataStruct']['defaults']
for name in functions:
    deltas = []
    for event in range(32):
        for weight in [-5,0,10,50,99,100,110]:
            inputs = {'SpecialEventInput':{'EventName':event,'BaseWeight':weight},
                      'SpecialEventInput.EventName':event,'SpecialEventInput.BaseWeight':weight}
            data = json.loads((root/'blueprint-functions/BP_GlobalManager'/(name+'.json')).read_text())
            for field in data['function']['fields']:
                if field.startswith('K2Node_SetFieldsInStruct_StructOut') or field in ('Local Eligible Event', 'SpecialEventModified'):
                    inputs[field] = defaults
            trace = evaluate(name, inputs)
            fixtures.append(trace)
            if weight == 50:
                writes = trace['writes']
                output = writes.get('SpecialEventModified', defaults)
                deltas.append({'output_event':output['EventName'], 'output_weight':output['BaseWeight'],
                               'updated_weight':writes.get('SpecialEventInput.BaseWeight')})
    table[name] = deltas
(root/'event-weight-traces.json').write_text(json.dumps({'fixtures':fixtures,'original_game_executed':False,'deltas_at_50':table},indent=2),encoding='utf-8')
print('Traced',len(fixtures),'event-weight cases')
