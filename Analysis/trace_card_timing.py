from pathlib import Path
import itertools,json
from trace_state_rules import evaluate
root=Path(__file__).parent
code=json.loads((root/'blueprint-functions/BP_DrawManager/SpawnCustomCardEvent.json').read_text())['statements']
start=next(i for i,n in enumerate(code) if n.get('Expression',{}).get('StackNode')=='RandomIntegerInRange')
stop=next(i for i,n in enumerate(code) if n.get('Variable',{}).get('Variable',{}).get('field')=='SlateBrush')
fixtures=[]
for strokes,interval,count,user,time in itertools.product([-1,0,8,25],[0.1,0.3,1.2,10],[0.8,1.5],[1,3],[0.85,1.4]):
    fixtures.append(evaluate('SpawnCustomCardEvent',{'MinStrokes':0,'MaxStrokes':30,'MinInterval':0.1,'MaxInterval':10,'call:RandomIntegerInRange':strokes,'call:RandomFloatInRange':interval,'StrokeCountMultiplier':count,'GlobalManager.UserStrokeCountMultiplier':user,'TimeSpeedMultiplier':time},owner='BP_DrawManager',start_index=start,prefix=stop))
result={'original_game_executed':False,'fixtures':fixtures,'limitations':['Only the numeric timing section is traced; media and widget effects are excluded. Random values are injected to exercise boundary behavior.']}
text=json.dumps(result,indent=2)
(root/'card-timing-traces.json').write_text(text)
(root/'UnrealReconstruction/RecoveryEvidence/card-timing-traces.json').write_text(text)
print('Traced',len(fixtures),'card timing cases; source statements',start,stop)
