"""Audit newer progression content against the current recovered runtime, without editor writes."""
from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1];dest=root/'ReferenceBuilds/newer-20261017'
runtime=root.parent/'UnrealReconstruction/Source/CockHeroRecovered'
catalog=json.loads((dest/'normalized-content-catalog.json').read_text(encoding='utf8'))
header=(runtime/'RecoveredGameplay.h').read_text(encoding='utf8')
metric_block=re.search(r'enum class ERecoveredMetric[^\{]+\{(.*?)\};',header,re.S)[1]
metrics={name:int(value) for name,value in re.findall(r'(\w+)\s*=\s*(\d+)',metric_block)}
newmetrics={e['name'].split('::')[-1]:e['value'] for e in catalog['native_enums']['EMetricType']}
conditions_code=(runtime/'RecoveredChallengeRules.cpp').read_text(encoding='utf8')
conditions=set(re.findall(r'Condition\.ConditionType==TEXT\("([^"]+)"\)',conditions_code))
rewards_code=(runtime/'RecoveredRewards.cpp').read_text(encoding='utf8')
rewards=set(re.findall(r'Kind==TEXT\("([^"]+)"\)',rewards_code))
comparisons=set(re.findall(r'TEXT\("(GreaterOrEqual|LessOrEqual|Equal|Greater|Less)"\)',conditions_code))
challenges=catalog['tables']['DT_Challenges'];cards=catalog['tables']['DT_PlayerCards']
metric_rows={};condition_rows={};reward_rows={};comparison_rows={};unknown_fields={}
challenge_fields={'row','ChallengeID','DisplayName','Description','Icon','IconTint','Requirements','Scope','Conditions','Rewards','XPReward','UnlockPointsReward','bHidden'}
card_fields={'row','CardID','CardName','CardImage','RequiredChallengeID','RequiredLevel','CardColor'}
for row in challenges:
    ident=row['ChallengeID']
    for req in row['Requirements']:
        name=req['MetricType'].split('::')[-1]
        if name not in metrics:metric_rows.setdefault(name,[]).append(ident)
        comp=req['ComparisonType'].split('::')[-1]
        if comp not in comparisons:comparison_rows.setdefault(comp,[]).append(ident)
    for cond in row['Conditions']:
        if cond['ConditionType'] not in conditions:condition_rows.setdefault(cond['ConditionType'],[]).append(ident)
    for reward in row['Rewards']:
        kind=reward['RewardType'].split('::')[-1]
        if kind not in rewards:reward_rows.setdefault(kind,[]).append(ident)
    if set(row)-challenge_fields:unknown_fields[ident]=sorted(set(row)-challenge_fields)
for row in cards:
    if set(row)-card_fields:unknown_fields[row['CardID']]=sorted(set(row)-card_fields)
known_ids={r['ChallengeID'] for r in challenges}
orphan_cards=[r['CardID'] for r in cards if r['RequiredChallengeID'] and r['RequiredChallengeID'] not in known_ids]
blocked={ident for group in [metric_rows,condition_rows,reward_rows,comparison_rows] for ids in group.values() for ident in ids}
result={'runtime_metrics':metrics,'newer_metrics':newmetrics,'numeric_shifts':{n:{'runtime':v,'reference':newmetrics[n]} for n,v in metrics.items() if n in newmetrics and v!=newmetrics[n]},'missing_metrics_used':metric_rows,'native_metric_additions':{n:v for n,v in newmetrics.items() if n not in metrics},'unsupported_conditions_used':condition_rows,'unsupported_rewards_used':reward_rows,'unsupported_comparisons_used':comparison_rows,'unrepresented_row_fields':unknown_fields,'orphan_card_challenges':orphan_cards,'blocked_challenges':sorted(blocked),'challenge_count':len(challenges),'card_count':len(cards),'blocked_cards':[r['CardID'] for r in cards if r['RequiredChallengeID'] in blocked],'full_runtime_mapping_complete':not bool(blocked or unknown_fields or orphan_cards),'notes':['String-valued row fields can load unknown metrics without error but tracker dispatch cannot produce them.','Existing saved Requirements are retained verbatim by InitializeChallenges for existing same-scope rows.','Card artwork and new challenge artwork require independent resource recovery; their string paths can be preserved losslessly.']}
(dest/'progression-runtime-compatibility.json').write_text(json.dumps(result,indent=2),encoding='utf8')
print(json.dumps(result,indent=2))
