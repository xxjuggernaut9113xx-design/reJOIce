from pathlib import Path
import json,itertools
from trace_state_rules import evaluate
root=Path(__file__).parent
fixtures=[]
arrays=[[],[0],[0,0],[1],[1,2,3],[0,1,2],[1,0,2],[1,2,0],[1,1,2,2],[0,0,4,5,6],[1,6,2,7,3,8]]
for timestamps,length in itertools.product(arrays,[0,1,5,6,10]):
    fixtures.append(evaluate('Update_Recent_Draws_Count',{'RecentDrawTimestamps':timestamps,'GlobalManager.PlayerVariablesStruct.SessionLength':length},owner='BP_DrawManager'))
text=json.dumps({'original_game_executed':False,'fixtures':fixtures,'limitations':['Invalid integer Array_Get values are modeled using reflected IntProperty initialization; print effects are excluded.']},indent=2)
(root/'recent-draw-traces.json').write_text(text)
(root/'UnrealReconstruction/RecoveryEvidence/recent-draw-traces.json').write_text(text)
print('Traced',len(fixtures),'recent-draw cases')
