"""Independent source traces for the per-beat gameplay state effects."""
from pathlib import Path
import itertools
import json
from trace_state_rules import evaluate

root = Path(__file__).parent
fixtures = []
modifier_names = ['Hungry Succubi', 'Sacrificial', 'Mr. Money Bandz', 'Deal With The Devil']
for flags in itertools.product([False, True], repeat=4):
    for card in [0, 3, 5, 255]:
        for came in [False, True]:
            inputs = dict(zip(('modifier:' + n for n in modifier_names), flags))
            inputs.update({'PlayerVariablesStruct.HasCame?':came, 'CurrentCardTypeEnum':card,
                          'CumMeterPercentage':0.95, 'BaseCumGain':0.002,
                          'PlayerVariablesStruct.CumMeterMultiplier':1.5, 'Heat Level':85.0,
                          'PlayerVariablesStruct.ConsecutiveHighHeatDraws':8,
                          'PlayerVariablesStruct.TotalEdgeCount':3,
                          'PlayerVariablesStruct.CurrentComboCount':1500,
                          'PlayerVariablesStruct.SessionLength':600})
            fixtures.append(evaluate('AddtoCumMeteronBeatComplete', inputs))
for card in list(range(9)) + [255]:
    fixtures.append(evaluate('Determine_CoinAdd', {'CurrentCardTypeEnum':card}, modeled_calls=['AddCoins']))
for category in [0,1,2,255]:
    fixtures.append(evaluate('Determine_HeatAdd', {'HeatCategory':category, 'HighCategory_HeatAdd':1.25,
                                             'MedCategory_HeatAdd':0.75, 'SlowCategory_HeatAdd':0.5},
                            modeled_calls=['AddHeat']))
for combo in [0,100,2000,-1]:
    fixtures.append(evaluate('BreakCombo', {'PlayerVariablesStruct.BrokenComboArray':[10,20],
                                          'PlayerVariablesStruct.CurrentComboCount':combo}))
result = {'original_game_executed':False, 'fixtures':fixtures,
          'limitations':['Presentation, progression side effects and real device calls are excluded.']}
(root / 'session-rule-traces.json').write_text(json.dumps(result, indent=2), encoding='utf-8')
print('Traced', len(fixtures), 'session state cases')
