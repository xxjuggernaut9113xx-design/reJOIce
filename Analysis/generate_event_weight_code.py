"""Translate the independently traced weight transformations into compact C++ tables."""
from pathlib import Path
import json

root = Path(__file__).parent
project = root/'UnrealReconstruction'
data = json.loads((root/'event-weight-traces.json').read_text())
defaults = json.loads((root/'struct-default-values.json').read_text())['SpecialEventDataStruct']['defaults']
names = list(data['deltas_at_50'])
table = []
for name in names:
    row = []
    for event in range(32):
        fixtures = [f for f in data['fixtures'] if f['function']==name.replace('_',' ') or f['function']==name]
        fixtures = [f for f in fixtures if f['inputs']['SpecialEventInput.EventName']==event]
        assert len(fixtures)==7,(name,event,len(fixtures))
        output = lambda f:f['writes'].get('SpecialEventModified', defaults)
        if all(output(f)==defaults for f in fixtures):
            rule = (2,0,0)
        elif all(output(f).get('BaseWeight')==f['inputs']['SpecialEventInput.BaseWeight'] and output(f).get('EventName')==event for f in fixtures):
            rule = (0,event,0)
        elif all(output(f).get('BaseWeight')==0 and output(f).get('EventName')==output(fixtures[0]).get('EventName') for f in fixtures):
            rule = (3,output(fixtures[0])['EventName'],0)
        else:
            candidates = {output(f)['BaseWeight']-f['inputs']['SpecialEventInput.BaseWeight'] for f in fixtures if 0 < output(f)['BaseWeight'] < 100}
            assert len(candidates)==1,(name,event,candidates)
            delta = candidates.pop()
            assert all(output(f)['EventName']==event and output(f)['BaseWeight']==min(max(f['inputs']['SpecialEventInput.BaseWeight']+delta,0),100) for f in fixtures),(name,event)
            rule = (1,event,delta)
        row.append(rule)
    table.append(row)
cpp = '#include "RecoveredEventRules.h"\n\nnamespace { struct FWeightRule { int32 Kind; int32 Event; double Delta; };\nstatic const FWeightRule WeightRules[9][32] = {\n'
for row in table:
    cpp += '{' + ','.join('{'+','.join(map(str,r))+'}' for r in row) + '},\n'
cpp += '''}; }
FRecoveredEventRecord URecoveredEventRuleLibrary::AdjustEventWeight(const FRecoveredEventRecord& Event, uint8 RuleSet) {
    if (RuleSet >= 9 || Event.EventName < 0 || Event.EventName >= 32) return FRecoveredEventRecord();
    const FWeightRule& Rule = WeightRules[RuleSet][Event.EventName];
    if (Rule.Kind == 2 || Rule.Kind == 3) {
        FRecoveredEventRecord Result;
        Result.EventName = Rule.Event;
        return Result;
    }
    FRecoveredEventRecord Result = Event;
    if (Rule.Kind == 1) Result.BaseWeight = FMath::Clamp(Event.BaseWeight + Rule.Delta, 0.0, 100.0);
    return Result;
}
int32 URecoveredEventRuleLibrary::ChooseEventAtRoll(const TArray<FRecoveredEventRecord>& Events, double Roll) {
    double Sum = 0;
    for (int32 Index = 0; Index < Events.Num(); ++Index) {
        Sum += Events[Index].BaseWeight;
        if (Sum > Roll) return Index;
    }
    return INDEX_NONE;
}
double URecoveredEventRuleLibrary::GetTotalWeight(const TArray<FRecoveredEventRecord>& Events) {
    double Sum = 0;
    for (const auto& Event : Events) Sum += Event.BaseWeight;
    return Sum;
}
uint8 URecoveredEventRuleLibrary::RefreshHeatCategory(double Heat, uint8 Previous) {
    if (Heat >= 0 && Heat <= 30) return 2;
    if (Heat >= 30 && Heat <= 70) return 1;
    if (Heat >= 70 && Heat <= 100) return 0;
    return Previous;
}
'''
(project/'Source/CockHeroRecovered/RecoveredEventRules.cpp').write_text(cpp,encoding='utf-8')
(project/'RecoveryEvidence/event-rule-index.json').write_text(json.dumps(names,indent=2),encoding='utf-8')
print('Generated',len(names),'event rule sets from',len(data['fixtures']),'source traces')
