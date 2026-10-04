#include "RecoveredRules.h"
#include "RecoveredRewards.h"
#include "RecoveredProgression.h"
#include "RecoveredChallengeTracker.h"
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
    // Deduplicate: don't open a second results screen if one is already up.
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay) && Overlay->GetName().Contains(TEXT("PostGameFlow_Master"))) {
            return;
        }
    }
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
    FRecoveredSessionRewardData RewardData;
    RewardData.XPGranted = SessionXP;
    RewardData.Rewards = Rewards;
    const FText LifetimeText = URecoveredProgressionLibrary::GetLifetimeStatsText(LifetimeStats);
    const FText RewardsText = URecoveredProgressionLibrary::GetRewardsText(RewardData);
    const FText XPText = FText::AsNumber(SessionXP);
    const FText DurationText = FText::FromString(FString::Printf(TEXT("%d:%02d"), SessionStats.SessionDuration / 60, SessionStats.SessionDuration % 60));
    const FText ResultText = FText::FromString(SessionStats.bWon ? TEXT("Victory") : TEXT("Defeat"));
    // Bind defensively: set any text block whose name matches the data role.
    // Field names come from the native widget; only existing widgets are touched.
    TArray<UWidget*> AllWidgets;
    if (Results->WidgetTree) Results->WidgetTree->GetAllWidgets(AllWidgets);
    for (UWidget* W : AllWidgets) {
        if (auto* Text = Cast<UTextBlock>(W)) {
            const FString Name = Text->GetName();
            if (Name.Contains(TEXT("Lifetime")) || Name.Contains(TEXT("Stats"))) Text->SetText(LifetimeText);
            else if (Name.Contains(TEXT("Reward"))) Text->SetText(RewardsText);
            else if (Name.Contains(TEXT("Duration")) || Name.Contains(TEXT("TimePlayed"))) Text->SetText(DurationText);
            else if (Name.Contains(TEXT("Result")) || Name.Contains(TEXT("Outcome"))) Text->SetText(ResultText);
            else if (Name.Contains(TEXT("XP")) && !Name.Contains(TEXT("Lifetime"))) Text->SetText(XPText);
        }
        // Wire return-to-menu buttons: the results screen's menu return control.
        if (auto* Button = Cast<UButton>(W)) {
            const FString Name = Button->GetName();
            if (Name.Contains(TEXT("ReturnToMenu")) || Name.Contains(TEXT("MainMenu")) || Name.Contains(TEXT("MenuButton"))) {
                Button->OnClicked.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleReturnToMenuClicked);
            }
        }
    }
}

void ARecoveredGlobalManager::HandleReturnToMenuClicked() {
    ReturnToMainMenu();
}

int32 ARecoveredGlobalManager::CalculateRecoveredSessionXP() const {
    return URecoveredProgressionLibrary::CalculateSessionXP(SessionStats, FRecoveredXPSettings());
}

TArray<FRecoveredReward> ARecoveredGlobalManager::PrepareRecoveredSessionRewards(int32 SessionXP) const {
    TArray<FRecoveredReward> Rewards;
    if (SessionXP > 0) {
        FRecoveredReward XPReward;
        XPReward.RewardType = TEXT("XP");
        XPReward.Value = SessionXP;
        Rewards.Add(XPReward);
    }
    // Coins earned during the session (tracked separately from the spendable balance).
    if (PlayerVariables.SessionCoinsEarned > 0) {
        FRecoveredReward CoinReward;
        CoinReward.RewardType = TEXT("Coins");
        CoinReward.Value = PlayerVariables.SessionCoinsEarned;
        Rewards.Add(CoinReward);
    }
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
    LifetimeStats.TotalCoinsEarned += PlayerVariables.SessionCoinsEarned;
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
    if (!Instance->SaveRecoveredState()) HandleSaveFailure(TEXT("Lifetime stats failed to persist"));
}

void ARecoveredGlobalManager::HandleSaveFailure(const FString& Context) {
    LastSessionError = FString::Printf(TEXT("Save failed: %s"), *Context);
    UE_LOG(LogTemp, Error, TEXT("Recovered save failure: %s"), *Context);
    OnSessionAction.Broadcast(TEXT("SaveFailed"));
}

void ARecoveredGlobalManager::LoadLifetimeStats() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    URecoveredSaveGame* Save = Instance->CurrentSave;
    auto ReadCounter=[Save](const TCHAR* Key) {
        const double Value=Save->GetNumberSetting(Key,0);
        return FMath::IsFinite(Value) && Value>=0 && Value<=MAX_int32 && Value==FMath::FloorToDouble(Value) ? static_cast<int32>(Value) : 0;
    };
    LifetimeStats.TotalSessionsCompleted = ReadCounter(TEXT("Lifetime_TotalSessionsCompleted"));
    LifetimeStats.TotalSessionsWon = ReadCounter(TEXT("Lifetime_TotalSessionsWon"));
    LifetimeStats.TotalStrokes = ReadCounter(TEXT("Lifetime_TotalStrokes"));
    LifetimeStats.TotalEdges = ReadCounter(TEXT("Lifetime_TotalEdges"));
    LifetimeStats.TotalSuccubiDefeated = ReadCounter(TEXT("Lifetime_TotalSuccubiDefeated"));
    LifetimeStats.TotalEnemiesDefeated = ReadCounter(TEXT("Lifetime_TotalEnemiesDefeated"));
    LifetimeStats.TotalXPEarned = ReadCounter(TEXT("Lifetime_TotalXPEarned"));
    LifetimeStats.TotalCoinsEarned = ReadCounter(TEXT("Lifetime_TotalCoinsEarned"));
    LifetimeStats.BestCombo = ReadCounter(TEXT("Lifetime_BestCombo"));
    LifetimeStats.BestEdgeStreak = ReadCounter(TEXT("Lifetime_BestEdgeStreak"));
    LifetimeStats.LongestSessionSeconds = ReadCounter(TEXT("Lifetime_LongestSessionSeconds"));
    LifetimeStats.MostStrokesInSession = ReadCounter(TEXT("Lifetime_MostStrokesInSession"));
}

void ARecoveredGlobalManager::FinalizeRecoveredSession() {
    if (bRecoveredSessionFinalized || !GetWorld()) return;
    bRecoveredSessionFinalized = true;
    // Populate derived session fields BEFORE accounting reads them.
    // Use the recorded outcome; an untouched session is not a win.
    SessionStats.bWon = SessionStats.SessionsWon > 0;
    // The XP calculation reads SessionStats.ActiveModifiers; gameplay loads
    // modifiers into BeatContext.ActiveModifiers. Connect them here.
    SessionStats.ActiveModifiers = BeatContext.ActiveModifiers;
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
        // Subscribe to level-up for presentation before granting XP.
        Progression->OnLevelUp.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleRecoveredLevelUp);
        Progression->AddXP(SessionXP, TEXT("Session Complete"));
        if (Instance) Instance->PersistRecoveredProgression();
    }

    SessionStats.SessionsCompleted += 1;
    // The outcome already recorded SessionsWon; do not count it twice.
    // End-session challenge updates: push final metrics for all tracked stats.
    if (Instance && Instance->ChallengeTracker) {
        URecoveredChallengeTracker* Tracker = Instance ? Instance->ChallengeTracker.Get() : nullptr;
        const int32 Elapsed = SessionStats.SessionDuration;
        const float WorldSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
        // Per-event totals were already delivered to lifetime challenges during
        // play. Replaying them here would double their accumulated progress.
        Tracker->UpdateMetricWithConditions(ERecoveredMetric::SessionsCompleted, 1, SessionStats, SessionStats.ActiveModifiers, Elapsed, WorldSeconds);
    }
    if (Instance && !Instance->PersistRecoveredProgression()) HandleSaveFailure(TEXT("Final session state failed to persist"));
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

void ARecoveredGlobalManager::HandleRecoveredLevelUp(int32 Level, int32 UnlockPoints, const TArray<FString>& ContentUnlocks) {
    // Present the level-up screen with unlock points and content unlocks.
    APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
    UClass* LevelUpClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_LevelUpScreen.WBP_LevelUpScreen_C"));
    if (!Controller || !LevelUpClass) return;
    if (auto* LevelUp = CreateWidget<UUserWidget>(Controller, LevelUpClass)) {
        LevelUp->AddToViewport(10);
        EventOverlays.Add(LevelUp);
        // Bind level, unlock points, and content unlocks to text fields.
        TArray<UWidget*> AllWidgets;
        if (LevelUp->WidgetTree) LevelUp->WidgetTree->GetAllWidgets(AllWidgets);
        FString UnlocksStr = FString::Join(ContentUnlocks, TEXT("\n"));
        for (UWidget* W : AllWidgets) {
            if (auto* Text = Cast<UTextBlock>(W)) {
                const FString Name = Text->GetName();
                if (Name.Contains(TEXT("Level"))) Text->SetText(FText::AsNumber(Level));
                else if (Name.Contains(TEXT("UnlockPoints"))) Text->SetText(FText::AsNumber(UnlockPoints));
                else if (Name.Contains(TEXT("ContentUnlock"))) Text->SetText(FText::FromString(UnlocksStr));
            }
        }
    }
}

void ARecoveredGlobalManager::SetBeatSoundBank(FName BankID) {
    BeatSoundBank = BankID;
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) {
            Instance->CurrentSave->SetStringSetting(TEXT("BeatSoundBank"), BankID.ToString());
            Instance->SaveRecoveredState();
        }
    }
}

FName ARecoveredGlobalManager::GetBeatSoundBank() const {
    return BeatSoundBank;
}

void ARecoveredGlobalManager::SetVoicePack(FName PackID) {
    VoicePack = PackID;
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) {
            Instance->CurrentSave->SetStringSetting(TEXT("VoicePack"), PackID.ToString());
            Instance->SaveRecoveredState();
        }
    }
}

FName ARecoveredGlobalManager::GetVoicePack() const {
    return VoicePack;
}

void ARecoveredGlobalManager::PlayDialogueLine(FName LineID) {
    if (!GetWorld()) return;
    // Voice-pack routing: pack ID selects the dialogue variant subdirectory.
    const FString PackPath = FString::Printf(TEXT("/Game/Recovery/Resources/Audio/Dialogue/%s/%s.%s"),
        *VoicePack.ToString(), *LineID.ToString(), *LineID.ToString());
    const FString FallbackPath = FString::Printf(TEXT("/Game/Recovery/Resources/Audio/voiceline_sfx.voiceline_sfx"));
    const FString UsePath = FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(PackPath)) ? PackPath : FallbackPath;
    if (!FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(UsePath))) return;
    if (USoundBase* Sound = LoadObject<USoundBase>(nullptr, *UsePath)) {
        const float Volume = GetRecoveredVolume(TEXT("VoicelinesVolume"), 0.8f);
        UGameplayStatics::PlaySound2D(this, Sound, Volume);
    }
}
