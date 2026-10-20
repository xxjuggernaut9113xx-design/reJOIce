#include "RecoveredObjectiveRuntime.h"
#include "RecoveredRules.h"
#include "TimerManager.h"

namespace {
constexpr int32 ObjectiveMinimums[]={1,300,100,2,30,2,5};
constexpr int32 ObjectiveMaximums[]={1,10800,20000,100,600,20,100};
}

const TArray<FRecoveredObjectiveSpec>& RecoveredObjectives::GetSpecs() {
    static const TArray<FRecoveredObjectiveSpec> Specs = {
        {0,TEXT("Cum meter"),TEXT(""),1,1},
        {1,TEXT("Timer (seconds)"),TEXT("LastObjective_Timer"),300,300},
        {2,TEXT("Strokes"),TEXT("LastObjective_Strokes"),1000,50},
        {3,TEXT("Edges"),TEXT("LastObjective_Edges"),2,1},
        {6,TEXT("Prejac (seconds)"),TEXT("LastObjective_Prejac"),60,30},
        {7,TEXT("Tribute"),TEXT("LastObjective_Tribute"),2,1},
        {8,TEXT("Succu Slayer"),TEXT("LastObjective_SuccuSlayer"),5,5}
    };
    return Specs;
}
int32 RecoveredObjectives::GetSelectedIndex(const URecoveredSaveGame* Save) {
    const double Value = Save ? Save->GetNumberSetting(TEXT("LastObjectiveIndex_Classic"),0) : 0;
    return FMath::IsFinite(Value) ? FMath::RoundToInt(FMath::Clamp(Value,0.0,static_cast<double>(GetSpecs().Num()-1))) : 0;
}
int32 RecoveredObjectives::GetSavedTarget(const URecoveredSaveGame* Save, int32 Index) {
    if (!GetSpecs().IsValidIndex(Index)) return 0;
    const auto& Spec = GetSpecs()[Index];
    if (Spec.Objective == 0) return 1;
    const double Value = Save ? Save->GetNumberSetting(Spec.SaveKey,Spec.DefaultTarget) : Spec.DefaultTarget;
    return FMath::IsFinite(Value) ? FMath::RoundToInt(FMath::Clamp(Value,static_cast<double>(ObjectiveMinimums[Index]),static_cast<double>(ObjectiveMaximums[Index]))) : Spec.DefaultTarget;
}
bool RecoveredObjectives::IsComplete(const FRecoveredObjectiveRuntime& State, const FRecoveredPlayerVariables& Player, const FRecoveredSessionStats& Stats, double Meter) {
    if (!State.bActive) return false;
    switch (State.Objective) {
        case 0:return Meter >= 1;
        case 1:return Player.SessionLength - State.BaselineDuration >= State.Target;
        case 2:return Stats.Strokes - State.BaselineStrokes >= State.Target;
        case 3:return Stats.Edges - State.BaselineEdges >= State.Target;
        case 7:return Stats.MilkingCount - State.BaselineMilking >= State.Target;
        case 8:return Stats.SuccubiDefeated - State.BaselineSuccubi >= State.Target;
        default:return false;
    }
}
bool RecoveredObjectives::IsPrejacExpired(const FRecoveredObjectiveRuntime& State, const FRecoveredPlayerVariables& Player) {
    return State.bActive && State.Objective == 6 && Player.SessionLength - State.BaselineDuration >= State.Target;
}
bool RecoveredObjectives::ResetAfterMiss(FRecoveredObjectiveRuntime& State, bool ResetSetting, double& Meter) {
    switch (State.Objective) {
        case 0:Meter=0;return true;
        case 1:State.BaselineDuration=URecoveredStateRuleLibrary::AddInt32Wrapping(State.BaselineDuration,State.Target);return true;
        case 3:State.BaselineEdges=URecoveredStateRuleLibrary::AddInt32Wrapping(State.BaselineEdges,State.Target);return true;
        case 2:if (ResetSetting) { State.BaselineStrokes=URecoveredStateRuleLibrary::AddInt32Wrapping(State.BaselineStrokes,State.Target);return true; }return false;
        case 8:if (ResetSetting) { State.BaselineSuccubi=URecoveredStateRuleLibrary::AddInt32Wrapping(State.BaselineSuccubi,State.Target);return true; }return false;
        default:return false;
    }
}

bool ARecoveredGlobalManager::ConfigureRecoveredClassicObjective(int32 Index, int32 Target, FString& Error) {
    Error.Reset();
    if (!RecoveredObjectives::GetSpecs().IsValidIndex(Index)) { Error=TEXT("Choose a valid Classic objective");return false; }
    if (Target<ObjectiveMinimums[Index] || Target>ObjectiveMaximums[Index]) { Error=FString::Printf(TEXT("Objective target must be between %d and %d"),ObjectiveMinimums[Index],ObjectiveMaximums[Index]);return false; }
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) { Error=TEXT("Classic customization requires an active recovery profile");return false; }
    auto* Save=Instance->CurrentSave.Get(); const FString Before=Save->StateJson;
    const auto& Spec=RecoveredObjectives::GetSpecs()[Index];
    if (!Save->SetNumberSetting(TEXT("LastObjectiveIndex_Classic"),Index) || (Index!=0 && !Save->SetNumberSetting(Spec.SaveKey,Target)) || !Instance->SaveRecoveredState()) {
        Save->StateJson=Before;Error=TEXT("Classic objective selection could not be saved");return false;
    }
    return true;
}
void ARecoveredGlobalManager::InitializeRecoveredClassicObjective() {
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const URecoveredSaveGame* Save=Instance ? Instance->CurrentSave.Get() : nullptr;
    const int32 Index=RecoveredObjectives::GetSelectedIndex(Save);
    ClassicObjectiveRuntime=FRecoveredObjectiveRuntime();ClassicObjectiveRuntime.bActive=true;
    ClassicObjectiveRuntime.Objective=RecoveredObjectives::GetSpecs()[Index].Objective;
    ClassicObjectiveRuntime.Target=RecoveredObjectives::GetSavedTarget(Save,Index);
    ClassicObjectiveRuntime.BaselineDuration=PlayerVariables.SessionLength;
    ClassicObjectiveRuntime.BaselineStrokes=SessionStats.Strokes;ClassicObjectiveRuntime.BaselineEdges=SessionStats.Edges;
    ClassicObjectiveRuntime.BaselineSuccubi=SessionStats.SuccubiDefeated;ClassicObjectiveRuntime.BaselineMilking=SessionStats.MilkingCount;
    CurrentSessionObjective=ClassicObjectiveRuntime.Objective;
    PlayerVariables.bIsAllowedToCum=CurrentSessionObjective==6 || CurrentSessionObjective==7;
}
void ARecoveredGlobalManager::ResetRecoveredObjectiveRuntime() {
    ClassicObjectiveRuntime=FRecoveredObjectiveRuntime();
    if (GetWorld()) GetWorldTimerManager().ClearTimer(ObjectiveReleaseTimer);
}
void ARecoveredGlobalManager::TickRecoveredObjectives() {
    if (PlayerVariables.bHasCame) return;
    if (ActiveRecoveredMode==0 && ClassicObjectiveRuntime.bActive) {
        if (RecoveredObjectives::IsPrejacExpired(ClassicObjectiveRuntime,PlayerVariables)) { PrematureCum();return; }
        if (RecoveredObjectives::IsComplete(ClassicObjectiveRuntime,PlayerVariables,SessionStats,CumMeterPercentage)) {
            if (CurrentSessionObjective==7) SuccessfulCum(); else OpenRecoveredReleaseWindow();
        }
        return;
    }
    if (ActiveRecoveredMode!=1 || !TowerRuntime || (TowerRuntime->Phase!=ERecoveredRoundPhase::Playing && TowerRuntime->Phase!=ERecoveredRoundPhase::BossRound)) return;
    FRecoveredObjectiveRuntime State;State.bActive=true;State.Objective=TowerRuntime->SelectedOption.Objective;State.Target=FMath::RoundToInt(TowerRuntime->SelectedOption.ObjectiveParam);
    State.BaselineDuration=TowerRuntime->BaselineDuration;State.BaselineStrokes=TowerRuntime->BaselineStrokes;State.BaselineEdges=TowerRuntime->BaselineEdges;State.BaselineSuccubi=TowerRuntime->BaselineSuccubi;State.BaselineMilking=TowerRuntime->BaselineMilking;
    if (RecoveredObjectives::IsPrejacExpired(State,PlayerVariables)) { TowerRuntime->CompleteRound(false);return; }
    if (!RecoveredObjectives::IsComplete(State,PlayerVariables,SessionStats,CumMeterPercentage)) return;
    if (TowerRuntime->Phase==ERecoveredRoundPhase::BossRound && State.Objective!=7) OpenRecoveredReleaseWindow(); else TowerRuntime->CompleteRound(true);
}
void ARecoveredGlobalManager::OpenRecoveredReleaseWindow() {
    if (PlayerVariables.bIsAllowedToCum || PlayerVariables.bHasCame || !GetWorld()) return;
    PlayerVariables.bIsAllowedToCum=true;
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::CumWindowsHit,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::CumWindowsHit,1);
    DrawRecoveredSpecialCard(TEXT("CumEventOverride"),true);
    PendingNotifications.Add(TEXT("Objective complete. 60 second release window."));
    GetWorldTimerManager().SetTimer(ObjectiveReleaseTimer,this,&ARecoveredGlobalManager::ExpireRecoveredReleaseWindow,60.f,false);
}
void ARecoveredGlobalManager::ExpireRecoveredReleaseWindow() {
    if (PlayerVariables.bHasCame) return;
    const bool Tower=ActiveRecoveredMode==1 && TowerRuntime && TowerRuntime->Phase==ERecoveredRoundPhase::BossRound;
    if (!Tower && !(ActiveRecoveredMode==0 && ClassicObjectiveRuntime.bActive)) return;
    FRecoveredObjectiveRuntime State=ClassicObjectiveRuntime;
    if (Tower) {
        State.bActive=true;State.Objective=TowerRuntime->SelectedOption.Objective;State.Target=FMath::RoundToInt(TowerRuntime->SelectedOption.ObjectiveParam);
        State.BaselineDuration=TowerRuntime->BaselineDuration;State.BaselineStrokes=TowerRuntime->BaselineStrokes;State.BaselineEdges=TowerRuntime->BaselineEdges;State.BaselineSuccubi=TowerRuntime->BaselineSuccubi;
    }
    PlayerVariables.bIsAllowedToCum=false;
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::MissedCumWindows,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::MissedCumWindows,1);
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const bool Reset=!Instance || !Instance->CurrentSave || Instance->CurrentSave->GetBoolSetting(TEXT("DoesNotCummingInWindowResetObjective?"),true);
    if (!RecoveredObjectives::ResetAfterMiss(State,Reset,CumMeterPercentage)) { if (Tower) TowerRuntime->CompleteRound(true);else SuccessfulCum();return; }
    if (Tower) { TowerRuntime->BaselineDuration=State.BaselineDuration;TowerRuntime->BaselineStrokes=State.BaselineStrokes;TowerRuntime->BaselineEdges=State.BaselineEdges;TowerRuntime->BaselineSuccubi=State.BaselineSuccubi; }
    else ClassicObjectiveRuntime=State;
    SpawnRecoveredOverlay(TEXT("CumWindowClosedOverlay_Widget"));PendingNotifications.Add(TEXT("Release window closed. Objective reset."));RequestNextRecoveredCard(true);
}
