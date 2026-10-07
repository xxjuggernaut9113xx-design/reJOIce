#include "RecoveredRules.h"
#include "RecoveredRewards.h"
#include "RecoveredProgression.h"
#include "RecoveredPostGameSequence.h"
#include "RecoveredChallengeTracker.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Sound/SoundBase.h"
#include "Misc/PackageName.h"

namespace {
UWidget* FindNestedWidget(UUserWidget* Root, FName Name) {
    if (!Root) return nullptr;
    if (UWidget* Direct = Root->GetWidgetFromName(Name)) return Direct;
    if (!Root->WidgetTree) return nullptr;
    TArray<UWidget*> Widgets;
    Root->WidgetTree->GetAllWidgets(Widgets);
    for (UWidget* Widget : Widgets) {
        if (!Widget) continue;
        if (Widget->GetFName() == Name) return Widget;
        if (auto* Nested = Cast<UUserWidget>(Widget)) {
            if (UWidget* Found = FindNestedWidget(Nested, Name)) return Found;
        }
    }
    return nullptr;
}

void SetNestedText(UUserWidget* Root, const TCHAR* Name, const FText& Value) {
    if (auto* Text = Cast<UTextBlock>(FindNestedWidget(Root, FName(Name)))) Text->SetText(Value);
}

void BindNestedButton(UUserWidget* Root, const TCHAR* Name, ARecoveredGlobalManager* Manager) {
    if (auto* Button = Cast<UButton>(FindNestedWidget(Root, FName(Name)))) Button->OnClicked.AddUniqueDynamic(Manager, &ARecoveredGlobalManager::HandleReturnToMenuClicked);
}

void AddXPSource(FRecoveredSessionRewardData& Data, const TCHAR* Label, int32 Amount, const FString& Detail) {
    if (Amount <= 0) return;
    FRecoveredXPSourceData Source;
    Source.Label = FText::FromString(Label);
    Source.XPAmount = Amount;
    Source.DetailText = FText::FromString(Detail);
    Data.XPSources.Add(MoveTemp(Source));
}

void AddUPSource(FRecoveredSessionRewardData& Data, const TCHAR* Label, int32 Amount, const FString& Detail, bool bFromLevelUp = false) {
    if (Amount <= 0) return;
    FRecoveredUPSourceData Source;
    Source.Label = FText::FromString(Label);
    Source.UPAmount = Amount;
    Source.DetailText = FText::FromString(Detail);
    Source.bFromLevelUp = bFromLevelUp;
    Data.UPSources.Add(MoveTemp(Source));
    Data.TotalUPEarned += Amount;
}

float GetRecoveredModifierMultiplier(const FRecoveredSessionStats& Stats) {
    float Multiplier = 1.0f;
    if (Stats.ActiveModifiers.ContainsByPredicate([](const FString& Tag) { return Tag.Equals(TEXT("ironman"), ESearchCase::IgnoreCase); })) Multiplier = 1.2f;
    if (Stats.ActiveModifiers.ContainsByPredicate([](const FString& Tag) { return Tag.Equals(TEXT("hardcore"), ESearchCase::IgnoreCase); })) Multiplier += 0.15f;
    return Multiplier;
}

int32 GetRecoveredStoreUnlockPoints(const URecoveredGameInstance* Instance, const URecoveredProgressionManager* FallbackProgression) {
    if (Instance && Instance->CurrentSave) {
        const double SavedPoints = Instance->CurrentSave->GetNumberSetting(TEXT("UnlockPoints"), 0.0);
        if (FMath::IsFinite(SavedPoints)) return static_cast<int32>(FMath::Clamp(SavedPoints, static_cast<double>(MIN_int32), static_cast<double>(MAX_int32)));
    }
    return FallbackProgression ? FallbackProgression->UnlockPoints : 0;
}
}

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
    FRecoveredSessionRewardData RewardData = bRecoveredSessionFinalized
        ? PendingPostGameRewardData
        : BuildRecoveredSessionRewardData(CalculateRecoveredSessionXP());
    const FText RewardsText = URecoveredProgressionLibrary::GetRewardsText(RewardData);
    const FText DurationText = FText::FromString(FString::Printf(TEXT("%d:%02d"), SessionStats.SessionDuration / 60, SessionStats.SessionDuration % 60));
    const FText ResultText = FText::FromString(RewardData.bWon ? TEXT("Victory") : TEXT("Defeat (-50% Rewards)"));
    const FString DetailString = FString::Printf(TEXT("Strokes: %d\nEdges: %d\nHighest Combo: %d\nEnemies Defeated: %d\nSuccubi Defeated: %d"),
        SessionStats.Strokes, SessionStats.Edges, SessionStats.MaxCombo, SessionStats.EnemiesDefeated, SessionStats.SuccubiDefeated);

    // WBP_SessionSummaryWidget fields recovered from its Initialize body.
    SetNestedText(Results, TEXT("VictoryText"), ResultText);
    SetNestedText(Results, TEXT("RewardsString"), RewardsText);
    SetNestedText(Results, TEXT("DurationText"), DurationText);
    SetNestedText(Results, TEXT("TotalStrokesText"), FText::AsNumber(SessionStats.Strokes));
    SetNestedText(Results, TEXT("EdgeAmountText"), FText::AsNumber(SessionStats.Edges));
    SetNestedText(Results, TEXT("HighestComboText"), FText::AsNumber(SessionStats.MaxCombo));
    SetNestedText(Results, TEXT("DetailedStatsString"), FText::FromString(DetailString));

    BindNestedButton(Results, TEXT("ReturnToMenu"), this);
    BindNestedButton(Results, TEXT("ReturnToMenuButton"), this);
    if (!PostGameSequence) PostGameSequence = NewObject<URecoveredPostGameSequence>(this);
    PostGameSequence->Begin(this, Results, RewardData);
}

void ARecoveredGlobalManager::HandleReturnToMenuClicked() {
    ReturnToMainMenu();
}

int32 ARecoveredGlobalManager::CalculateRecoveredSessionXP() const {
    return URecoveredProgressionLibrary::CalculateSessionXP(SessionStats, FRecoveredXPSettings());
}

FRecoveredSessionRewardData ARecoveredGlobalManager::BuildRecoveredSessionRewardData(int32 /*SessionXP*/) const {
    FRecoveredSessionRewardData Data;
    const auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    const URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    const FRecoveredXPSettings Settings;
    Data.StartingXP = Progression ? Progression->CurrentXP : 0;
    Data.StartingLevel = Progression ? Progression->CurrentLevel : 1;
    Data.XPToNextLevel = URecoveredProgressionLibrary::GetXPForNextLevel(Data.StartingLevel);
    Data.StartingUP = GetRecoveredStoreUnlockPoints(Instance, Progression);
    Data.SessionStats = SessionStats;
    Data.bWon = SessionStats.SessionsWon > 0;

    const float RewardScale = Data.bWon ? 1.0f : 0.5f;
    const int32 Minutes = FMath::FloorToInt(static_cast<float>(SessionStats.SessionDuration) * (1.0f / 60.0f));
    const int32 TimeXP = FMath::FloorToInt(static_cast<float>(Minutes) * Settings.XPPerMinute * RewardScale);
    const int32 StrokeRaw = FMath::Min(FMath::FloorToInt(static_cast<float>(SessionStats.Strokes) * Settings.XPPerStroke), Settings.StrokeXPCap);
    const int32 StrokeXP = FMath::FloorToInt(static_cast<float>(StrokeRaw) * RewardScale);
    const int32 EnemyRaw = FMath::Min(URecoveredStateRuleLibrary::AddInt32Wrapping(SessionStats.EnemiesDefeated, SessionStats.SuccubiDefeated), Settings.EnemyXPCap);
    const int32 EnemyXP = FMath::FloorToInt(static_cast<float>(EnemyRaw) * RewardScale);
    const int32 EdgeXP = FMath::FloorToInt(static_cast<float>(SessionStats.Edges) * Settings.XPPerEdge * RewardScale);
    const int32 VictoryXP = Data.bWon ? FMath::TruncToInt(Settings.WinBonus) : 0;

    AddXPSource(Data, TEXT("TIME PLAYED"), TimeXP, FString::Printf(TEXT("%d MIN"), Minutes));
    AddXPSource(Data, TEXT("STROKES"), StrokeXP, StrokeRaw < Settings.StrokeXPCap
        ? FString::Printf(TEXT("%d STROKES"), SessionStats.Strokes)
        : FString::Printf(TEXT("%d STROKES (MAX)"), SessionStats.Strokes));
    const int32 EnemyCount = URecoveredStateRuleLibrary::AddInt32Wrapping(SessionStats.EnemiesDefeated, SessionStats.SuccubiDefeated);
    AddXPSource(Data, TEXT("ENEMIES"), EnemyXP, EnemyCount < Settings.EnemyXPCap
        ? FString::Printf(TEXT("%d DEFEATED"), EnemyCount)
        : FString::Printf(TEXT("%d DEFEATED (MAX)"), EnemyCount));
    AddXPSource(Data, TEXT("EDGES"), EdgeXP, FString::Printf(TEXT("%d EDGES"), SessionStats.Edges));
    AddXPSource(Data, TEXT("VICTORY BONUS"), VictoryXP, TEXT("WIN"));

    int32 BaseXP = 0;
    for (const FRecoveredXPSourceData& Source : Data.XPSources) BaseXP = URecoveredStateRuleLibrary::AddInt32Wrapping(BaseXP, Source.XPAmount);
    const float ModifierMultiplier = GetRecoveredModifierMultiplier(SessionStats);
    const int32 ModifierXP = FMath::FloorToInt(static_cast<float>(BaseXP) * (ModifierMultiplier - 1.0f));
    if (ModifierXP > 0) AddXPSource(Data, TEXT("MODIFIER BONUS"), ModifierXP, FString::Printf(TEXT("+%d%%"), FMath::FloorToInt((ModifierMultiplier - 1.0f) * 100.0f)));
    Data.TotalXPEarned = URecoveredStateRuleLibrary::AddInt32Wrapping(BaseXP, ModifierXP);
    Data.XPGranted = Data.TotalXPEarned;

    int32 SimulatedXP = URecoveredStateRuleLibrary::AddInt32Wrapping(Data.StartingXP, Data.TotalXPEarned);
    int32 SimulatedLevel = Data.StartingLevel;
    while (SimulatedLevel < 20) {
        const int32 Threshold = URecoveredProgressionLibrary::GetXPForNextLevel(SimulatedLevel);
        if (SimulatedXP < Threshold) break;
        SimulatedXP = URecoveredStateRuleLibrary::AddInt32Wrapping(SimulatedXP, -Threshold);
        ++SimulatedLevel;
        FRecoveredLevelUpEventData Event;
        Event.NewLevel = SimulatedLevel;
        Event.XPThresholdCrossed = Threshold;
        int32 LevelUP = 0;
        if (Progression && Progression->LevelDataTable && Progression->LevelDataTable->GetRowStruct() == FRecoveredLevelRow::StaticStruct()) {
            const FName RowName(*FString::Printf(TEXT("Level_%d"), SimulatedLevel));
            if (const FRecoveredLevelRow* Row = Progression->LevelDataTable->FindRow<FRecoveredLevelRow>(RowName, TEXT("Recovered post-game level event"), false)) {
                Event.Title = FName(*Row->TitleUnlock.ToString());
                LevelUP = Row->UnlockPointsReward;
            }
        }
        if (Event.Title.IsNone()) Event.Title = FName(*FString::Printf(TEXT("LEVEL %d"), SimulatedLevel));
        Event.UPReward = LevelUP;
        Data.LevelUpEvents.Add(Event);
        AddUPSource(Data, TEXT("LEVEL UP"), LevelUP, FString::Printf(TEXT("LVL %d"), SimulatedLevel), true);
    }

    const int32 StrokeUP = FMath::FloorToInt(static_cast<float>(SessionStats.Strokes / 300) * RewardScale);
    const int32 ComboUP = FMath::FloorToInt(static_cast<float>(SessionStats.MaxCombo / 400) * RewardScale);
    const int32 EdgeUP = FMath::FloorToInt(static_cast<float>(SessionStats.Edges / 2) * RewardScale);
    const int32 TimeUP = FMath::FloorToInt(static_cast<float>(Minutes / 3) * RewardScale);
    const int32 HeatUP = FMath::FloorToInt(static_cast<float>(SessionStats.DrawsAtMaxHeat / 10) * RewardScale);
    AddUPSource(Data, TEXT("STROKES"), StrokeUP, FString::Printf(TEXT("%d STROKES"), SessionStats.Strokes));
    AddUPSource(Data, TEXT("MAX COMBO"), ComboUP, FString::Printf(TEXT("%d COMBO"), SessionStats.MaxCombo));
    AddUPSource(Data, TEXT("EDGES"), EdgeUP, FString::Printf(TEXT("%d EDGES"), SessionStats.Edges));
    AddUPSource(Data, TEXT("TIME PLAYED"), TimeUP, FString::Printf(TEXT("%d MIN"), Minutes));
    AddUPSource(Data, TEXT("MAX HEAT DRAWS"), HeatUP, FString::Printf(TEXT("%d DRAWS"), SessionStats.DrawsAtMaxHeat));
    if (Data.bWon) AddUPSource(Data, TEXT("VICTORY"), 5, TEXT("CAME ON TIME"));
    if (SessionStats.ItemsUsed == 0) AddUPSource(Data, TEXT("PURIST"), FMath::FloorToInt(5.0f * RewardScale), TEXT("NO ITEMS"));

    Data.EndingXP = SimulatedXP;
    Data.EndingLevel = SimulatedLevel;
    Data.Rewards = PrepareRecoveredSessionRewards(Data.XPGranted);
    return Data;
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

void ARecoveredGlobalManager::ApplyRecoveredPostGameStorePoints(int32 Amount) {
    if (Amount <= 0) return;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    const int32 Previous = GetRecoveredStoreUnlockPoints(Instance, nullptr);
    const int32 Updated = URecoveredStateRuleLibrary::AddInt32Wrapping(Previous, Amount);
    if (!Instance->CurrentSave->SetNumberSetting(TEXT("UnlockPoints"), Updated) || !Instance->SaveRecoveredState()) {
        HandleSaveFailure(TEXT("Post-game store points failed to persist"));
        return;
    }
    if (Instance->ProgressionManager) Instance->ProgressionManager->OnStorePointsRequested.Broadcast(Amount);
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
    PendingPostGameLevel = INDEX_NONE;
    PendingPostGameUnlockPoints = 0;
    PendingPostGameContentUnlocks.Reset();
    PendingPostGameRewardData = BuildRecoveredSessionRewardData(SessionXP);
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
    if (bRecoveredSessionFinalized) {
        PendingPostGameLevel = Level;
        PendingPostGameUnlockPoints = UnlockPoints;
        PendingPostGameContentUnlocks = ContentUnlocks;
        return;
    }
    // Non-session progression (for example a claimed challenge reward) still
    // uses the standalone level-up overlay.
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
