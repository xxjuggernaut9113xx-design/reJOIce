#include "RecoveredChallengeTracker.h"
#include "RecoveredChallengeRules.h"
#include "RecoveredRewards.h"

namespace {
FString DefinitionContext(const FRecoveredChallengeRow& Row) {
    FString Scope=Row.Scope;Scope.RemoveFromStart(TEXT("EChallengeScope::"));
    TArray<FString> Conditions;
    for (const auto& Condition:Row.Conditions) {
        Conditions.AddUnique(FString::Printf(TEXT("%d:%s%d:%s"),Condition.ConditionType.Len(),*Condition.ConditionType,Condition.ConditionValue.Len(),*Condition.ConditionValue));
    }
    Conditions.Sort();
    FString Result=Scope+TEXT("|");
    for (const FString& Condition:Conditions) Result+=FString::Printf(TEXT("%d:%s"),Condition.Len(),*Condition);
    return Result;
}
bool SameRequirement(const FRecoveredRequirement& A,const FRecoveredRequirement& B) {
    return A.MetricType==B.MetricType && A.ComparisonType==B.ComparisonType && A.TargetValue==B.TargetValue;
}
const FRecoveredChallengeRow* FindRowByID(const UDataTable* Table,FName ID) {
    if (!Table || Table->GetRowStruct()!=FRecoveredChallengeRow::StaticStruct()) return nullptr;
    for (const auto& Pair:Table->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (FName(*Row->ChallengeID)==ID) return Row;
    }
    return nullptr;
}
FString PreviousContext(const FRecoveredChallengeProgress& Progress,FName ID,const UDataTable* LegacyTable,bool bWasSession) {
    if (!Progress.DefinitionContext.IsEmpty()) return Progress.DefinitionContext;
    // Legacy saves did not retain conditions. Recover provenance only from
    // the retained baseline definition, never from the replacement table.
    const auto* Legacy=FindRowByID(LegacyTable,ID);
    if (!Legacy || Legacy->Requirements.Num()!=Progress.Requirements.Num()) return FString();
    FString Scope=Legacy->Scope;Scope.RemoveFromStart(TEXT("EChallengeScope::"));
    if ((Scope==TEXT("Session"))!=bWasSession) return FString();
    for (int32 I=0;I<Progress.Requirements.Num();++I) if (!SameRequirement(Progress.Requirements[I],Legacy->Requirements[I])) return FString();
    return DefinitionContext(*Legacy);
}
}

const FRecoveredChallengeRow* URecoveredChallengeTracker::FindDefinition(FName ID) const {
    if (!ChallengeTable || ChallengeTable->GetRowStruct()!=FRecoveredChallengeRow::StaticStruct()) return nullptr;
    for (const auto& Pair:ChallengeTable->GetRowMap()) {
        const auto* Definition=reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (FName(*Definition->ChallengeID)==ID) return Definition;
    }
    return nullptr;
}
bool URecoveredChallengeTracker::InitializeChallenges() {
    if (!ChallengeTable || ChallengeTable->GetRowStruct()!=FRecoveredChallengeRow::StaticStruct()) return false;
    TSet<FName> DefinedIDs;
    for (const auto& Pair:ChallengeTable->GetRowMap()) {
        const auto& Row=*reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        const FName ID(*Row.ChallengeID);
        FString Scope=Row.Scope;Scope.RemoveFromStart(TEXT("EChallengeScope::"));
        if (ID.IsNone() || DefinedIDs.Contains(ID) || (Scope!=TEXT("Session") && Scope!=TEXT("Lifetime"))) return false;
        DefinedIDs.Add(ID);
    }
    const auto OldSession=SessionProgress;const auto OldLifetime=LifetimeProgress;
    UDataTable* LegacyTable=nullptr;
    const auto NeedsLegacy=[](const TMap<FName,FRecoveredChallengeProgress>& Map) {
        for (const auto& Pair:Map) if (Pair.Value.DefinitionContext.IsEmpty()) return true;
        return false;
    };
    if (NeedsLegacy(OldSession) || NeedsLegacy(OldLifetime)) LegacyTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    // Missing definitions remain serialized in their original maps. Their
    // tracking intent is retained with the entry, outside the active list.
    for (auto* Map:{&SessionProgress,&LifetimeProgress}) for (auto& Pair:*Map) if (!DefinedIDs.Contains(Pair.Key)) {
        Pair.Value.bDefinitionArchived=true;
        Pair.Value.bWasTrackedWhenArchived|=TrackedChallenges.Contains(Pair.Key);
        TrackedChallenges.Remove(Pair.Key);
    }
    for (const auto& Pair:ChallengeTable->GetRowMap()) {
        const auto& Definition=*reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        FString Scope=Definition.Scope;Scope.RemoveFromStart(TEXT("EChallengeScope::"));
        const bool bSession=Scope==TEXT("Session");
        auto& Map=bSession ? SessionProgress : LifetimeProgress;
        auto& OtherMap=bSession ? LifetimeProgress : SessionProgress;
        const FName ID(*Definition.ChallengeID);
        const FRecoveredChallengeProgress* Candidates[]={
            bSession ? OldSession.Find(ID) : OldLifetime.Find(ID),
            bSession ? OldLifetime.Find(ID) : OldSession.Find(ID)
        };
        FRecoveredChallengeProgress Progress;
        Progress.Requirements=Definition.Requirements;
        Progress.BestValues.SetNumZeroed(Progress.Requirements.Num());
        Progress.DefinitionContext=DefinitionContext(Definition);
        for (auto& Requirement:Progress.Requirements) Requirement.CurrentValue=0;
        bool bRestoreTracking=false;
        for (int32 CandidateIndex=0;CandidateIndex<2;++CandidateIndex) {
            const auto* Existing=Candidates[CandidateIndex];if (!Existing) continue;
            Progress.bCompleted|=Existing->bCompleted || Existing->bRewardsClaimed;
            Progress.bRewardsClaimed|=Existing->bRewardsClaimed;
            bRestoreTracking|=Existing->bWasTrackedWhenArchived;
            if (Existing->CompletionTime>0 && (Progress.CompletionTime<=0 || Existing->CompletionTime<Progress.CompletionTime)) Progress.CompletionTime=Existing->CompletionTime;
        }
        const bool bRecordedComplete=CompletedChallenges.Contains(ID);
        Progress.bCompleted|=bRecordedComplete;
        // A completion identity with no surviving ledger has unknown claim
        // history. Do not make it newly claimable during reconciliation.
        if (bRecordedComplete && !Candidates[0] && !Candidates[1]) Progress.bRewardsClaimed=true;
        const auto* Existing=Candidates[0];
        if (Existing && PreviousContext(*Existing,ID,LegacyTable,bSession)==Progress.DefinitionContext) {
            for (int32 I=0;I<Progress.Requirements.Num();++I) {
                const int32 PriorIndex=Existing->Requirements.IndexOfByPredicate([&](const FRecoveredRequirement& Prior) { return SameRequirement(Prior,Progress.Requirements[I]); });
                if (PriorIndex==INDEX_NONE) continue;
                Progress.Requirements[I].CurrentValue=Existing->Requirements[PriorIndex].CurrentValue;
                Progress.BestValues[I]=Existing->BestValues.IsValidIndex(PriorIndex) ? FMath::Max(Existing->BestValues[PriorIndex],Progress.Requirements[I].CurrentValue) : FMath::Max(0,Progress.Requirements[I].CurrentValue);
            }
        }
        if (Progress.bCompleted) { CompletedChallenges.Add(ID);TrackedChallenges.Remove(ID); }
        else if (bRestoreTracking) TrackedChallenges.AddUnique(ID);
        OtherMap.Remove(ID);
        Map.Add(ID,MoveTemp(Progress));
    }
    return true;
}
void URecoveredChallengeTracker::UpdateChallengeProgress(FName ID,ERecoveredMetric Metric,int32 Amount,const FRecoveredSessionStats& Stats,int32 ElapsedSeconds,float WorldSeconds) {
    const auto* Definition=FindDefinition(ID);if (!Definition) return;
    FString Scope=Definition->Scope;Scope.RemoveFromStart(TEXT("EChallengeScope::"));
    const bool bSession=Scope==TEXT("Session");
    auto* Progress=(bSession ? SessionProgress : LifetimeProgress).Find(ID);if (!Progress) return;
    bool bChanged=false,bBestChanged=false;
    const bool bWasCompleted=Progress->bCompleted;
    const UEnum* MetricEnum=StaticEnum<ERecoveredMetric>();
    for (int32 I=0;I<Progress->Requirements.Num();++I) {
        auto& Requirement=Progress->Requirements[I];
        FString Type=Requirement.MetricType;Type.RemoveFromStart(TEXT("EMetricType::"));
        if (Type!=MetricEnum->GetNameStringByValue(static_cast<int64>(Metric))) continue;
        int32 Value=URecoveredStateRuleLibrary::AddInt32Wrapping(Requirement.CurrentValue,Amount);
        if (bSession) {
            switch (Metric) {
                case ERecoveredMetric::Strokes:Value=Stats.Strokes;break;
                case ERecoveredMetric::Edges:Value=Stats.Edges;break;
                case ERecoveredMetric::SuccubiDefeated:Value=Stats.SuccubiDefeated;break;
                case ERecoveredMetric::EnemiesDefeated:Value=Stats.EnemiesDefeated;break;
                case ERecoveredMetric::MaxCombo:Value=Stats.MaxCombo;break;
                case ERecoveredMetric::MissedCumWindows:Value=Stats.MissedCumWindows;break;
                case ERecoveredMetric::TimesTaunted:Value=Stats.TimesTaunted;break;
                case ERecoveredMetric::ItemsUsed:Value=Stats.ItemsUsed;break;
                case ERecoveredMetric::DrawsAtMaxHeat:Value=Stats.DrawsAtMaxHeat;break;
                case ERecoveredMetric::EarlyClimax:Value=Stats.EarlyClimax;break;
                case ERecoveredMetric::SessionDuration:Value=ElapsedSeconds;break;
                case ERecoveredMetric::MoneySpent:Value=Stats.MoneySpent;break;
                case ERecoveredMetric::EdgeStreak:Value=Stats.EdgeStreak;break;
                case ERecoveredMetric::ConsecutiveSuccubiSurvived:Value=Stats.ConsecutiveSuccubiSurvived;break;
                case ERecoveredMetric::CumWindowsHit:Value=Stats.CumWindowsHit;break;
                case ERecoveredMetric::TimeAtHighHeat:Value=Stats.TimeAtHighHeat;break;
                case ERecoveredMetric::PercentAtHighHeat:Value=ElapsedSeconds<1 ? 0 : FMath::RoundToInt((static_cast<float>(Stats.TimeAtHighHeat)/ElapsedSeconds)*100.0f);break;
                case ERecoveredMetric::GamesWithSexToy:Value=Stats.GamesWithSexToy;break;
                case ERecoveredMetric::PerfectEdges:Value=Stats.PerfectEdges;break;
                case ERecoveredMetric::BonerPillsUsed:Value=Stats.BonerPillsUsed;break;
                case ERecoveredMetric::AcceptedTemptation:Value=Stats.AcceptedTemptation;break;
                case ERecoveredMetric::CameDuringTaunt:Value=Stats.CameDuringTaunt;break;
                default:break;
            }
        }
        Requirement.CurrentValue=Value;bChanged=true;
        if (Progress->BestValues.IsValidIndex(I) && Progress->BestValues[I]<Value) { Progress->BestValues[I]=Value;bBestChanged=true; }
    }
    if (bBestChanged && RewardManager) RewardManager->OnSaveRequested.Broadcast();
    if (bChanged && !bWasCompleted && URecoveredChallengeRules::AreAllRequirementsMet(Progress->Requirements)) CompleteChallenge(ID,WorldSeconds);
    OnChallengeProgress.Broadcast(ID);
}
bool URecoveredChallengeTracker::CompleteChallenge(FName ID,float WorldSeconds) {
    if (!FindDefinition(ID)) return false;
    auto* Progress=SessionProgress.Find(ID);if (!Progress) Progress=LifetimeProgress.Find(ID);
    if (!Progress) return false;
    if (Progress->bCompleted || Progress->bRewardsClaimed || CompletedChallenges.Contains(ID)) return false;
    Progress->bCompleted=true;Progress->bRewardsClaimed=false;Progress->CompletionTime=WorldSeconds;
    CompletedChallenges.Add(ID);TrackedChallenges.Remove(ID);
    if (FindDefinition(ID)) OnChallengeCompleted.Broadcast(ID);
    if (RewardManager) RewardManager->OnSaveRequested.Broadcast();
    return true;
}
TArray<FRecoveredReward> URecoveredChallengeTracker::ClaimChallengeRewards(FName ID) {
    if (!CompletedChallenges.Contains(ID)) return {};
    const auto* Definition=FindDefinition(ID);if (!Definition) return {};
    auto* Progress=LifetimeProgress.Find(ID);if (!Progress) Progress=SessionProgress.Find(ID);
    if (Progress && Progress->bRewardsClaimed) return {};
    TArray<FRecoveredReward> Rewards=Definition->Rewards;
    if (Rewards.IsEmpty()) {
        if (Definition->XPReward>0) { FRecoveredReward Reward;Reward.RewardType=TEXT("XP");Reward.Value=Definition->XPReward;Rewards.Add(Reward); }
        if (Definition->UnlockPointsReward>0) { FRecoveredReward Reward;Reward.RewardType=TEXT("UnlockPoints");Reward.Value=Definition->UnlockPointsReward;Rewards.Add(Reward); }
    }
    URecoveredRewardLibrary::GrantRecoveredRewards(RewardManager,Rewards);
    if (Progress) { Progress->bRewardsClaimed=true;if (RewardManager) RewardManager->OnSaveRequested.Broadcast(); }
    return Rewards;
}
void URecoveredChallengeTracker::StartNewSession() {
    // Native StartNewSession resets current values only for unfinished session challenges.
    for (auto& Pair:SessionProgress) if (FindDefinition(Pair.Key) && !Pair.Value.bCompleted) for (auto& Requirement:Pair.Value.Requirements) Requirement.CurrentValue=0;
}
int32 URecoveredChallengeTracker::GetCompletedChallengeCount() const {
    int32 Count=0;
    for (FName ID:CompletedChallenges) if (FindDefinition(ID)) ++Count;
    return Count;
}
int32 URecoveredChallengeTracker::GetTotalChallengeCount() const {
    return ChallengeTable && ChallengeTable->GetRowStruct()==FRecoveredChallengeRow::StaticStruct()
        ? ChallengeTable->GetRowMap().Num()
        : 0;
}
void URecoveredChallengeTracker::UpdateMetricWithConditions(ERecoveredMetric Metric,int32 Amount,const FRecoveredSessionStats& Stats,const TArray<FString>& ActiveModifiers,int32 ElapsedSeconds,float WorldSeconds) {
    if (!ChallengeTable || ChallengeTable->GetRowStruct()!=FRecoveredChallengeRow::StaticStruct()) return;
    TArray<FName> IDs;
    FString Type=StaticEnum<ERecoveredMetric>()->GetNameStringByValue(static_cast<int64>(Metric));
    for (const auto& Pair:ChallengeTable->GetRowMap()) {
        const auto& Row=*reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (!Row.Requirements.ContainsByPredicate([&Type](const FRecoveredRequirement& Requirement) { FString Name=Requirement.MetricType;Name.RemoveFromStart(TEXT("EMetricType::"));return Name==Type; })) continue;
        if (URecoveredChallengeRules::CheckChallengeConditions(Row.Conditions,ActiveModifiers,Stats.ItemsUsed,ElapsedSeconds)) IDs.AddUnique(FName(*Row.ChallengeID));
    }
    for (FName ID:IDs) UpdateChallengeProgress(ID,Metric,Amount,Stats,ElapsedSeconds,WorldSeconds);
}
