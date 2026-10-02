#include "RecoveredChallengeRules.h"

namespace {
int32 Comparison(const FString& Original) {
    FString Name=Original; int32 Colon;
    if(Name.FindLastChar(TEXT(':'),Colon)) Name=Name.Mid(Colon+1);
    const TCHAR* Names[]={TEXT("GreaterOrEqual"),TEXT("LessOrEqual"),TEXT("Equal"),TEXT("Greater"),TEXT("Less")};
    for(int32 Index=0;Index<UE_ARRAY_COUNT(Names);++Index) if(Name==Names[Index]) return Index;
    return -1;
}
}

bool URecoveredChallengeRules::AreAllRequirementsMet(const TArray<FRecoveredRequirement>& Requirements) {
    // Native 0x1481b4920 returns true for an empty list and fails at the first unmet predicate.
    for(const auto& Requirement:Requirements) {
        const int32 Current=Requirement.CurrentValue,Target=Requirement.TargetValue;
        bool Met=false;
        switch(Comparison(Requirement.ComparisonType)) {
            case 0:Met=Current>=Target;break;
            case 1:Met=Current<=Target;break;
            case 2:Met=Current==Target;break;
            case 3:Met=Current>Target;break;
            case 4:Met=Current<Target;break;
            default:break;
        }
        if(!Met) return false;
    }
    return true;
}

bool URecoveredChallengeRules::CheckChallengeConditions(const TArray<FRecoveredCondition>& Conditions,const TArray<FString>& ActiveModifiers,int32 ItemsUsed,int32 SessionDuration) {
    // Native 0x1481b4d80 consults manager session state; its third call argument is unused.
    for(const auto& Condition:Conditions) {
        if(Condition.ConditionType==TEXT("modifier")) {
            if(!ActiveModifiers.ContainsByPredicate([&](const FString& Modifier){return Modifier==Condition.ConditionValue;})) return false;
        } else if(Condition.ConditionType==TEXT("no_items")) {
            if(ItemsUsed>0) return false;
        } else if(Condition.ConditionType==TEXT("max_time")) {
            if(SessionDuration>FCString::Atoi(*Condition.ConditionValue)) return false;
        }
        // Unknown condition types are ignored by the original implementation.
    }
    return true;
}

float URecoveredChallengeRules::GetRequirementProgressPercent(const FRecoveredRequirement& Requirement) {
    // Native 0x1481c23f0: nonpositive targets are full progress before comparison dispatch.
    if(Requirement.TargetValue<=0) return 1.0f;
    const int32 Type=Comparison(Requirement.ComparisonType);
    if(Type<0) return 0.0f;
    volatile float Ratio=float(Requirement.CurrentValue)/float(Requirement.TargetValue);
    if(Type==1 || Type==4) {
        volatile float Inverse=1.0f-static_cast<float>(Ratio);
        return FMath::Clamp(static_cast<float>(Inverse),0.0f,1.0f);
    }
    return FMath::Clamp(static_cast<float>(Ratio),0.0f,1.0f);
}
