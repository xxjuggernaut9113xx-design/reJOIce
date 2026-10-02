#include "RecoveredChallengeTracker.h"
#include "RecoveredChallengeRules.h"
#include "RecoveredRewards.h"

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
    auto OldSession=MoveTemp(SessionProgress);auto OldLifetime=MoveTemp(LifetimeProgress);
    for (const auto& Pair:ChallengeTable->GetRowMap()) {
        const auto& Definition=*reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        FString Scope=Definition.Scope;Scope.RemoveFromStart(TEXT("EChallengeScope::"));
        auto& Map=Scope==TEXT("Session") ? SessionProgress : LifetimeProgress;
        const auto& OldMap=Scope==TEXT("Session") ? OldSession : OldLifetime;
        const FName ID(*Definition.ChallengeID);
        const auto* Existing=OldMap.Find(ID);
        if (!Existing) {
            FRecoveredChallengeProgress Progress;Progress.Requirements=Definition.Requirements;
            Progress.BestValues.SetNumZeroed(Progress.Requirements.Num());
            Map.Add(ID,MoveTemp(Progress));
        } else {
            auto Progress=*Existing;Progress.BestValues.SetNumZeroed(Definition.Requirements.Num());
            Map.Add(ID,MoveTemp(Progress));
        }
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
    auto* Progress=SessionProgress.Find(ID);if (!Progress) Progress=LifetimeProgress.Find(ID);
    if (!Progress) return false;
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
    for (auto& Pair:SessionProgress) if (!Pair.Value.bCompleted) for (auto& Requirement:Pair.Value.Requirements) Requirement.CurrentValue=0;
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
