#include "RecoveredEventRules.h"

TArray<FRecoveredEventRecord> URecoveredEventRuleLibrary::BuildEligibleEvents(const TArray<FRecoveredEventRecord>& Events,FRecoveredEligibilityState& State) {
    TArray<FRecoveredEventRecord> Result;
    for(const auto& Event:Events) {
        bool Eligible=false;
        switch(Event.EventName) {
            case 3: case 4: case 5: Eligible=true; break;
            case 8: Eligible=CheckSuccubusEligibility(State); break;
            case 14: case 15: Eligible=CheckBodyFrenzyEligibility(State); break;
            case 30: Eligible=CheckStoreEligibility(State); break;
            // Source invokes temptation/mercy queries but never adds either event.
            default: break;
        }
        if(Eligible) Result.Add(Event);
    }
    return Result;
}

TArray<FRecoveredEventRecord> URecoveredEventRuleLibrary::ApplyDrawEventWeights(const TArray<FRecoveredEventRecord>& EligibleEvents,uint8 HeatCategory,uint8 ComboTier) {
    TArray<FRecoveredEventRecord> Result;
    // The source's tier 6 and 7 loops append nothing.
    if(HeatCategory>2 || ComboTier>5) return Result;
    for(const auto& Event:EligibleEvents) Result.Add(AdjustEventWeight(AdjustEventWeight(Event,8-HeatCategory),ComboTier));
    return Result;
}

FName URecoveredEventRuleLibrary::DetermineDispatchedEvent(uint8 Event, bool bSuccufrenzyActive, bool bSlowAndSteadyActive, bool bDoubleTimeActive, int32 RandomRoll, bool& bClearIdleTimer) {
    bClearIdleTimer=false;
    if(bSuccufrenzyActive) return TEXT("SpawnSuccubus");
    if(bSlowAndSteadyActive) return RandomRoll==0 ? TEXT("MediumStrokeEvent") : TEXT("SlowStrokeEvent");
    if(bDoubleTimeActive) return RandomRoll==0 ? TEXT("SpawnSuccubus") : TEXT("FastStrokeEvent");
    bClearIdleTimer=true;
    switch(Event) {
        case 0: return TEXT("PostEdgeSlow");
        case 1: return TEXT("PostEdgeFast");
        case 3: return TEXT("SlowStrokeEvent");
        case 4: return TEXT("MediumStrokeEvent");
        case 5: return TEXT("FastStrokeEvent");
        case 7: return TEXT("TemptationEvent");
        case 8: return TEXT("SpawnSuccubus");
        case 10: return TEXT("MercyEvent");
        case 14: return TEXT("AssFrenzyEvent");
        case 15: return TEXT("BoobFrenzyEvent");
        case 30: return TEXT("SpawnStoreEvent");
        case 31: return TEXT("VideoLoopStrokeEvent");
        default: return NAME_None;
    }
}

bool URecoveredEventRuleLibrary::CheckSuccubusEligibility(FRecoveredEligibilityState& State) {
    if (State.Modifiers.Contains(TEXT("Demon Proof"))) return false;
    if (State.Modifiers.Contains(TEXT("Succufrenzy"))) {
        // The original writes weight 50 to an Array_Get value copy, without Array_Set.
        return true;
    }
    if (!State.bCanSuccubiSpawn && State.Shields > 0 && State.bShieldToggled) {
        --State.Shields;
        ++State.ShieldsConsumed;
        if (State.Shields <= 0) State.bShieldToggled=false;
        return false;
    }
    return State.HeatCategory == 0 || State.Combo >= 2000;
}
bool URecoveredEventRuleLibrary::CheckStoreEligibility(const FRecoveredEligibilityState& State) { return !State.bStoreOnCooldown && State.Coins >= 200; }
bool URecoveredEventRuleLibrary::CheckBodyFrenzyEligibility(const FRecoveredEligibilityState& State) { return State.bBrainMelterEnabled && State.HeatCategory == 0; }

namespace { struct FWeightRule { int32 Kind; int32 Event; double Delta; };
static const FWeightRule WeightRules[9][32] = {
{{0,0,0},{0,1,0},{0,2,0},{1,3,10.0},{0,4,0},{1,5,-10.0},{0,6,0},{1,7,5.0},{0,8,0},{1,9,-10.0},{1,10,-10.0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,10.0},{0,21,0},{1,22,-10.0},{1,23,10.0},{0,24,0},{1,25,-10.0},{0,26,0},{0,27,0},{1,28,-10.0},{0,29,0},{1,30,-5.0},{0,31,0}},
{{0,0,0},{0,1,0},{0,2,0},{1,3,5.0},{1,4,5.0},{0,5,0},{1,6,5.0},{1,7,5.0},{0,8,0},{2,0,0},{0,10,0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,5.0},{0,21,0},{1,22,-10.0},{1,23,10.0},{1,24,5.0},{0,25,0},{0,26,0},{1,27,5.0},{0,28,0},{0,29,0},{0,30,0},{0,31,0}},
{{1,0,-100.0},{0,1,0},{0,2,0},{0,3,0},{1,4,10.0},{1,5,5.0},{1,6,5.0},{2,0,0},{1,8,5.0},{1,9,5.0},{0,10,0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{0,20,0},{1,21,10.0},{1,22,5.0},{0,23,0},{1,24,5.0},{1,25,5.0},{0,26,0},{1,27,5.0},{1,28,5.0},{0,29,0},{1,30,10.0},{0,31,0}},
{{0,0,0},{0,1,0},{0,2,0},{1,3,-5.0},{1,4,5.0},{1,5,10.0},{1,6,5.0},{0,7,0},{1,8,10.0},{1,9,10.0},{1,10,10.0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,-5.0},{1,21,10.0},{1,22,10.0},{1,23,-5.0},{1,24,5.0},{1,25,5.0},{0,26,0},{1,27,5.0},{1,28,10.0},{0,29,0},{1,30,10.0},{0,31,0}},
{{0,0,0},{0,1,0},{0,2,0},{1,3,-10.0},{0,4,0},{1,5,25.0},{1,6,5.0},{0,7,0},{1,8,25.0},{1,9,25.0},{1,10,10.0},{0,11,0},{0,12,0},{0,13,0},{1,14,10.0},{1,15,10.0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,-10.0},{0,21,0},{1,22,25.0},{1,23,-10.0},{0,24,0},{1,25,25.0},{0,26,0},{0,27,0},{1,28,25.0},{0,29,0},{1,30,25.0},{0,31,0}},
{{0,0,0},{1,1,30.0},{2,0,0},{1,3,-25.0},{1,4,-10.0},{1,5,50.0},{1,6,25.0},{0,7,0},{1,8,30.0},{1,9,30.0},{1,10,-10.0},{0,11,0},{0,12,0},{0,13,0},{1,14,25.0},{1,15,25.0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,-25.0},{1,21,-10.0},{1,22,30.0},{1,23,-25.0},{1,24,-15.0},{1,25,40.0},{0,26,0},{1,27,-15.0},{1,28,30.0},{1,29,30.0},{1,30,30.0},{0,31,0}},
{{0,0,0},{0,1,0},{0,2,0},{1,3,75.0},{1,4,25.0},{1,5,5.0},{0,6,0},{1,7,5.0},{0,8,0},{0,9,0},{0,10,0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,30.0},{1,21,25.0},{1,22,5.0},{1,23,75.0},{1,24,25.0},{1,25,5.0},{0,26,0},{1,27,60.0},{1,28,5.0},{0,29,0},{1,30,5.0},{0,31,0}},
{{0,0,0},{0,1,0},{0,2,0},{1,3,25.0},{1,4,50.0},{1,5,25.0},{1,6,5.0},{1,7,10.0},{0,8,0},{1,9,5.0},{1,10,10.0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,25.0},{1,21,50.0},{1,22,25.0},{1,23,25.0},{1,24,50.0},{1,25,25.0},{0,26,0},{1,27,50.0},{1,28,25.0},{0,29,0},{1,30,5.0},{0,31,0}},
{{0,0,0},{0,1,0},{0,2,0},{1,3,10.0},{1,4,25.0},{1,5,85.0},{1,6,25.0},{0,7,0},{1,8,25.0},{1,9,25.0},{1,10,10.0},{0,11,0},{0,12,0},{0,13,0},{0,14,0},{0,15,0},{0,16,0},{0,17,0},{0,18,0},{0,19,0},{1,20,10.0},{1,21,25.0},{1,22,85.0},{1,23,10.0},{1,24,25.0},{1,25,85.0},{0,26,0},{1,27,25.0},{1,28,85.0},{0,29,0},{1,30,10.0},{0,31,0}},
}; }
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
