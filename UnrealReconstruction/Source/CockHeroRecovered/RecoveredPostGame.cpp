#include "RecoveredRules.h"
#include "RecoveredRewards.h"
#include "RecoveredProgression.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundBase.h"
#include "Misc/PackageName.h"

void ARecoveredGlobalManager::BindPostGameResultsButton(UUserWidget* PostCumWidget) {
    if (!PostCumWidget) return;
    // Reproduces the original BndEvt__PostCumContinue_Widget_ViewResultsButton
    // routing (ExecuteUbergraph entry 67): the results button opens the
    // recovered post-game master screen.
    if (auto* Button = Cast<UButton>(PostCumWidget->GetWidgetFromName(TEXT("ViewResultsButton")))) {
        Button->OnClicked.AddUniqueDynamic(this, &ARecoveredGlobalManager::OpenPostGameResults);
    }
}

void ARecoveredGlobalManager::OpenPostGameResults() {
    if (!GetWorld()) return;
    // Finalize first so the results screen presents finalized numbers.
    FinalizeRecoveredSession();
    // Hide the continue widget; it served its purpose once results open.
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay) && Overlay->GetName().Contains(TEXT("PostCumContinue"))) {
            Overlay->RemoveFromParent();
        }
    }
    APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
    UClass* ResultsClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_PostGameFlow_Master.WBP_PostGameFlow_Master_C"));
    if (!Controller || !ResultsClass) {
        LastSessionError = TEXT("Recovered post-game master screen is unavailable");
        return;
    }
    if (auto* Results = CreateWidget<UUserWidget>(Controller, ResultsClass)) {
        Results->AddToViewport(0);
        EventOverlays.Add(Results);
        BindPostGameResultsData(Results);
    }
}

void ARecoveredGlobalManager::BindPostGameResultsData(UUserWidget* Results) {
    if (!Results) return;
    // Build the display texts from the native-confirmed builders.
    const int32 SessionXP = CalculateRecoveredSessionXP();
    const TArray<FRecoveredReward> Rewards = PrepareRecoveredSessionRewards(SessionXP);
    const FText LifetimeText = URecoveredProgressionLibrary::GetLifetimeStatsText(LifetimeStats);
    const FText RewardsText = URecoveredProgressionLibrary::GetRewardsText(Rewards);
    const FText XPText = FText::AsNumber(SessionXP);
    // Bind defensively: set any text block whose name matches the data role.
    // Field names come from the native widget; only existing widgets are touched.
    TArray<UWidget*> AllWidgets;
    if (Results->WidgetTree) Results->WidgetTree->GetAllWidgets(AllWidgets);
    for (UWidget* W : AllWidgets) {
        if (auto* Text = Cast<UTextBlock>(W)) {
            const FString Name = Text->GetName();
            if (Name.Contains(TEXT("Lifetime")) || Name.Contains(TEXT("Stats"))) Text->SetText(LifetimeText);
            else if (Name.Contains(TEXT("Reward"))) Text->SetText(RewardsText);
            else if (Name.Contains(TEXT("XP")) && !Name.Contains(TEXT("Lifetime"))) Text->SetText(XPText);
        }
    }
}

int32 ARecoveredGlobalManager::CalculateRecoveredSessionXP() const {
    return URecoveredProgressionLibrary::CalculateSessionXP(SessionStats, FRecoveredXPSettings());
}

TArray<FRecoveredReward> ARecoveredGlobalManager::PrepareRecoveredSessionRewards(int32 SessionXP) const {
    // Verified XP only. Additional post-game rewards remain unresolved.
    TArray<FRecoveredReward> Rewards;
    if (SessionXP > 0) {
        FRecoveredReward XPReward;
        XPReward.RewardType = TEXT("XP");
        XPReward.Value = SessionXP;
        Rewards.Add(XPReward);
    }
    // Additional reward quantities have not been verified; do not invent bonuses.
    return Rewards;
}

void ARecoveredGlobalManager::UpdateRecoveredLifetimeStats(int32 SessionXP) {
    // Mirrors the native RecordSessionMetric lifetime behavior: counters
    // accumulate, peaks keep the maximum ever observed.
    const FRecoveredSessionStats& S = SessionStats;
    LifetimeStats.TotalSessionsCompleted += 1;
    if (S.bWon) LifetimeStats.TotalSessionsWon += 1;
    LifetimeStats.TotalStrokes += S.Strokes;
    LifetimeStats.TotalEdges += S.Edges;
    LifetimeStats.TotalSuccubiDefeated += S.SuccubiDefeated;
    LifetimeStats.TotalEnemiesDefeated += S.EnemiesDefeated;
    LifetimeStats.TotalXPEarned += SessionXP;
    LifetimeStats.TotalCoinsEarned += PlayerVariables.PlayerCoins;
    LifetimeStats.BestCombo = FMath::Max(LifetimeStats.BestCombo, S.MaxCombo);
    LifetimeStats.BestEdgeStreak = FMath::Max(LifetimeStats.BestEdgeStreak, S.EdgeStreak);
    LifetimeStats.LongestSessionSeconds = FMath::Max(LifetimeStats.LongestSessionSeconds, S.SessionDuration);
    LifetimeStats.MostStrokesInSession = FMath::Max(LifetimeStats.MostStrokesInSession, S.Strokes);
    SaveLifetimeStats();
}

void ARecoveredGlobalManager::SaveLifetimeStats() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    URecoveredSaveGame* Save = Instance->CurrentSave;
    Save->SetNumberSetting(TEXT("Lifetime_TotalSessionsCompleted"), LifetimeStats.TotalSessionsCompleted);
    Save->SetNumberSetting(TEXT("Lifetime_TotalSessionsWon"), LifetimeStats.TotalSessionsWon);
    Save->SetNumberSetting(TEXT("Lifetime_TotalStrokes"), LifetimeStats.TotalStrokes);
    Save->SetNumberSetting(TEXT("Lifetime_TotalEdges"), LifetimeStats.TotalEdges);
    Save->SetNumberSetting(TEXT("Lifetime_TotalSuccubiDefeated"), LifetimeStats.TotalSuccubiDefeated);
    Save->SetNumberSetting(TEXT("Lifetime_TotalEnemiesDefeated"), LifetimeStats.TotalEnemiesDefeated);
    Save->SetNumberSetting(TEXT("Lifetime_TotalXPEarned"), LifetimeStats.TotalXPEarned);
    Save->SetNumberSetting(TEXT("Lifetime_TotalCoinsEarned"), LifetimeStats.TotalCoinsEarned);
    Save->SetNumberSetting(TEXT("Lifetime_BestCombo"), LifetimeStats.BestCombo);
    Save->SetNumberSetting(TEXT("Lifetime_BestEdgeStreak"), LifetimeStats.BestEdgeStreak);
    Save->SetNumberSetting(TEXT("Lifetime_LongestSessionSeconds"), LifetimeStats.LongestSessionSeconds);
    Save->SetNumberSetting(TEXT("Lifetime_MostStrokesInSession"), LifetimeStats.MostStrokesInSession);
    Instance->SaveRecoveredState();
}

void ARecoveredGlobalManager::LoadLifetimeStats() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    URecoveredSaveGame* Save = Instance->CurrentSave;
    LifetimeStats.TotalSessionsCompleted = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalSessionsCompleted"), 0);
    LifetimeStats.TotalSessionsWon = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalSessionsWon"), 0);
    LifetimeStats.TotalStrokes = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalStrokes"), 0);
    LifetimeStats.TotalEdges = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalEdges"), 0);
    LifetimeStats.TotalSuccubiDefeated = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalSuccubiDefeated"), 0);
    LifetimeStats.TotalEnemiesDefeated = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalEnemiesDefeated"), 0);
    LifetimeStats.TotalXPEarned = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalXPEarned"), 0);
    LifetimeStats.TotalCoinsEarned = (int32)Save->GetNumberSetting(TEXT("Lifetime_TotalCoinsEarned"), 0);
    LifetimeStats.BestCombo = (int32)Save->GetNumberSetting(TEXT("Lifetime_BestCombo"), 0);
    LifetimeStats.BestEdgeStreak = (int32)Save->GetNumberSetting(TEXT("Lifetime_BestEdgeStreak"), 0);
    LifetimeStats.LongestSessionSeconds = (int32)Save->GetNumberSetting(TEXT("Lifetime_LongestSessionSeconds"), 0);
    LifetimeStats.MostStrokesInSession = (int32)Save->GetNumberSetting(TEXT("Lifetime_MostStrokesInSession"), 0);
}

void ARecoveredGlobalManager::FinalizeRecoveredSession() {
    if (bRecoveredSessionFinalized || !GetWorld()) return;
    bRecoveredSessionFinalized = true;
    // Session finalization, in order: stop the running session, compute the
    // session XP, roll lifetime accounting, grant rewards through the native
    // consumers, then persist. The results screen is presented separately by
    // OpenPostGameResults so it always shows finalized numbers.
    if (BeatTimeline) BeatTimeline->StopSequence();
    if (MediaPlayback) MediaPlayback->SetPaused(true);
    GetWorldTimerManager().ClearTimer(SessionDurationTimer);
    GetWorldTimerManager().ClearTimer(OutcomeContinuationTimer);

    const int32 SessionXP = CalculateRecoveredSessionXP();
    UpdateRecoveredLifetimeStats(SessionXP);

    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager : nullptr;
    if (Progression) {
        Progression->AddXP(SessionXP, TEXT("Session Complete"));
        if (Instance) Instance->PersistRecoveredProgression();
    }

    SessionStats.SessionsCompleted += 1;
    if (SessionStats.bWon) SessionStats.SessionsWon += 1;
    OnSessionAction.Broadcast(TEXT("SessionFinalized"));
}

float ARecoveredGlobalManager::GetRecoveredVolume(const FString& SettingName, float Fallback) const {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave) {
        return static_cast<float>(Instance->CurrentSave->GetNumberSetting(SettingName, Fallback));
    }
    return Fallback;
}

void ARecoveredGlobalManager::PlayRecoveredSessionSound(FName SoundID) {
    if (!GetWorld()) return;
    // Sound asset per ID; volume from the matching saved slider setting.
    struct FSoundDef { const TCHAR* ID; const TCHAR* Path; const TCHAR* VolumeSetting; float Fallback; };
    static const FSoundDef Sounds[] = {
        { TEXT("BeatTick"), TEXT("/Game/Recovery/Resources/Audio/beat_tick.beat_tick"), TEXT("BeatSFXVolume"), 0.8f },
        { TEXT("Moan"), TEXT("/Game/Recovery/Resources/Audio/moan_sfx.moan_sfx"), TEXT("MoansVolume"), 0.8f },
        { TEXT("Voiceline"), TEXT("/Game/Recovery/Resources/Audio/voiceline_sfx.voiceline_sfx"), TEXT("VoicelinesVolume"), 0.8f },
        { TEXT("Success"), TEXT("/Game/Recovery/Resources/Audio/success_sfx.success_sfx"), TEXT("SFXVolume"), 0.8f },
        { TEXT("Fail"), TEXT("/Game/Recovery/Resources/Audio/fail_sfx.fail_sfx"), TEXT("SFXVolume"), 0.8f },
        { TEXT("Click"), TEXT("/Game/Recovery/Resources/Audio/click3_sfx.click3_sfx"), TEXT("SFXVolume"), 0.8f },
    };
    const FString ID = SoundID.ToString();
    for (const auto& Def : Sounds) {
        if (ID != Def.ID) continue;
        if (!FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(FString(Def.Path)))) return;
        if (USoundBase* Sound = LoadObject<USoundBase>(nullptr, Def.Path)) {
            const float Volume = GetRecoveredVolume(Def.VolumeSetting, Def.Fallback);
            float Pitch = 1.0f;
            if (ID == TEXT("BeatTick") && BeatTimeline) {
                CalculateBeatPitch(BeatTimeline->TotalStrokes, BeatTimeline->GetBeatsRemaining());
                Pitch = static_cast<float>(CurrentPitch.BeatPitch);
            }
            UGameplayStatics::PlaySound2D(this, Sound, Volume, Pitch);
        }
        return;
    }
}
