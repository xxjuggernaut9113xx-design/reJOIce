from pathlib import Path
import json
from render_gameplay_pseudocode import expr
from trace_state_rules import size

root = Path(__file__).parent
names = ['AnalyzePlayerState', 'CheckEventConditions_ReturnArray', 'AdjustComboLevelWeights', 'AdjustHeatLevelWeights', 'Determine_CoinAdd', 'Determine_HeatAdd', 'AddtoCumMeteronBeatComplete', 'Beat_Complete_Add_Lootbar_Reward', 'BreakCombo', 'ApplyModifiers', 'BeatComplete', 'Complete_Beat_Sequence', 'CheckIntervalMultipliers', 'DetermineComboBasedNoteMultiplier', 'GetRandomCard', 'FastStrokeEvent', 'MediumStrokeEvent', 'SlowStrokeEvent']
out = []
for name in names:
    data = json.loads((root / 'blueprint-functions/BP_GlobalManager' / (name + '.json')).read_text())
    out.append('\n// ' + name)
    offset = 0
    for n in data['statements']:
        out.append('L' + str(offset) + ': ' + expr(n) + ';')
        offset += size(n)
(root / 'session-rules-pseudocode.txt').write_text('\n'.join(out), encoding='utf-8')
