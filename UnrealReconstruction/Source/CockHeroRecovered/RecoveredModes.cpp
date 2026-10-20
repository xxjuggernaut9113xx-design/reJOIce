#include "RecoveredRules.h"
#include "RecoveredModesWidget.h"
#include "RecoveredSuccuEconomy.h"
#include "RecoveredMusicUpgrades.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MediaPlayer.h"
#include "MediaSoundComponent.h"
#include "TimerManager.h"
#include "HAL/PlatformTime.h"

namespace {
uint8 PlaylistDeckForCard(uint8 CardType) {
    return CardType == 6 ? 4 : CardType == 7 ? 5 : CardType == 8 ? 6 : CardType;
}
}

void ARecoveredGlobalManager::InitializeRecoveredModes() {
    PlaylistRuntime = CreateDefaultSubobject<URecoveredPlaylistRuntime>(TEXT("RecoveredPlaylist"));
    TowerRuntime = CreateDefaultSubobject<URecoveredTowerRuntime>(TEXT("RecoveredTower"));
    PlaylistSound = CreateDefaultSubobject<UMediaSoundComponent>(TEXT("RecoveredPlaylistSound"));
    SetRootComponent(PlaylistSound);
    PlaylistSound->bIsUISound = true;
    PlaylistRuntime->OnBeatFired.AddUniqueDynamic(this, &ARecoveredGlobalManager::PresentRecoveredBeat);
    PlaylistRuntime->OnBeatFired.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleRecoveredDeviceBeat);
    PlaylistRuntime->OnBeatHitCenter.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleBeatHitCenter);
    PlaylistRuntime->OnSongStarted.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandlePlaylistSongStarted);
    PlaylistRuntime->OnBeatmapEvent.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandlePlaylistEvent);
    PlaylistRuntime->OnSongComplete.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandlePlaylistSongComplete);
    PlaylistRuntime->OnPlaylistComplete.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandlePlaylistComplete);
    TowerRuntime->OnRoundStarted.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleTowerRoundStarted);
    TowerRuntime->OnRoundCompleted.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleTowerRoundCompleted);
    TowerRuntime->OnSessionComplete.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleTowerComplete);
}
void ARecoveredGlobalManager::StopRecoveredModes() {
    ResetRecoveredObjectiveRuntime();
    if (ActiveRecoveredMode == 1 && GetWorld()) GetWorldTimerManager().ClearTimer(OutcomeContinuationTimer);
    if (PlaylistRuntime) PlaylistRuntime->StopPlayback();
    if (TowerRuntime) TowerRuntime->StopSession();
    if (PlaylistAudio) PlaylistAudio->Close();
    if (GetWorld()) GetWorldTimerManager().ClearTimer(PlaylistAudioTimer);
    ActiveRecoveredMode = 0;
    if (ModesScreen) { ModesScreen->RemoveFromParent(); ModesScreen = nullptr; }
}
void ARecoveredGlobalManager::OpenRecoveredModes() {
    if (!ModesScreen) ModesScreen = CreateWidget<URecoveredModesWidget>(UGameplayStatics::GetPlayerController(this, 0), URecoveredModesWidget::StaticClass());
    if (ModesScreen && !ModesScreen->IsInViewport()) ModesScreen->AddToViewport(20);
}
bool ARecoveredGlobalManager::StartPlaylistSession(const TArray<FString>& Paths, bool Loop) {
    if (Paths.IsEmpty()) { LastSessionError = TEXT("Playlist contains no tracks"); return false; }
    for (const FString& Path : Paths) {
        FRecoveredBeatmapData Data; FString Audio;
        if (!URecoveredBeatmapLibrary::LoadBeatmapFile(Path, Data, Audio, LastSessionError)) return false;
    }
    if (!InitializeRecoveredSession()) return false;
    StopRecoveredModes(); ActiveRecoveredMode = 2; IsAutoDrawEnabled = false;
    CurrentSessionObjective=0;PlayerVariables.bIsAllowedToCum=false;
    if (auto* Inventory = RecoveredNewerInventoryAdapter::GetInventory(*this)) RecoveredNewerInventoryAdapter::SetupMusicHotbar(*Inventory);
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        for (uint8 UpgradeType = 0; UpgradeType < 3; ++UpgradeType) RecoveredMusicUpgrades::SetLevel(Instance->CurrentSave.Get(), UpgradeType, 1);
    }
    if (BeatTimeline) BeatTimeline->StopSequence();
    if (ActiveMusicComponent) ActiveMusicComponent->Stop();
    if (MainMenu) MainMenu->RemoveFromParent();
    BeatContext.CardType = 0;
    PlaylistRuntime->BreakRechargeStrokes = 250;
    PlaylistRuntime->LastObservedStrokes = SessionStats.Strokes;
    const double Calibration = BeatTimeline ? BeatTimeline->GetCalibrationOffset() : 0;
    if (!PlaylistRuntime->StartPlaylist(Paths, Loop, 2.0, BeatTravelTime, Calibration, LastSessionError) || !PlaylistRuntime->bPlaying) {
        const FString Error = LastSessionError; ReturnToMainMenu(); LastSessionError = Error; return false;
    }
    GetWorldTimerManager().SetTimer(PlaylistAudioTimer, this, &ARecoveredGlobalManager::TickPlaylistAudio, .025f, true);
    OpenRecoveredModes();
    return true;
}
void ARecoveredGlobalManager::HandlePlaylistSongStarted(const FString& AudioPath) {
    PlayerVariables.bCanUseItems = true;
    PlayerVariables.bIsAllowedToCum=false;
    BeatContext.CardType = 0;
    if (!PlaylistAudio) {
        PlaylistAudio = NewObject<UMediaPlayer>(this);
        PlaylistAudio->PlayOnOpen = false;
        PlaylistAudio->OnMediaOpened.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandlePlaylistAudioOpened);
        PlaylistAudio->OnMediaOpenFailed.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandlePlaylistAudioFailed);
        PlaylistSound->SetMediaPlayer(PlaylistAudio);
        PlaylistSound->SetVolumeMultiplier(GetRecoveredVolume(TEXT("BackgroundMusicVolume"), 1));
    }
    PlaylistAudio->Close();
    if (!PlaylistAudio->OpenFile(AudioPath)) HandlePlaylistAudioFailed(AudioPath);
}
void ARecoveredGlobalManager::HandlePlaylistAudioOpened(FString OpenedUrl) { TickPlaylistAudio(); }
void ARecoveredGlobalManager::HandlePlaylistAudioFailed(FString FailedUrl) {
    const FString Error = TEXT("Playlist audio could not be opened: ") + FailedUrl;
    ReturnToMainMenu(); LastSessionError = Error; PendingNotifications.Add(Error);
}
void ARecoveredGlobalManager::TickPlaylistAudio() {
    TickRecoveredObjectives();
    if (ActiveRecoveredMode == 2 && PlaylistRuntime && PlaylistRuntime->bPlaying) {
        const auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
        const int32 Threshold = FMath::Max(1, FMath::RoundToInt(RecoveredMusicUpgrades::GetValue(Instance ? Instance->CurrentSave.Get() : nullptr, 2)));
        PlaylistRuntime->BreakRechargeStrokes += FMath::Max(SessionStats.Strokes - PlaylistRuntime->LastObservedStrokes, 0);
        PlaylistRuntime->LastObservedStrokes = SessionStats.Strokes;
        while (PlaylistRuntime->BreakRechargeStrokes >= Threshold) {
            PlaylistRuntime->BreakRechargeStrokes -= Threshold;
            if (GetOwnedItemCount(TEXT("Break")) < GetRecoveredItemMaximum(TEXT("Break"))) AcquireStoreItem(TEXT("Break"));
        }
    }
    if (!PlaylistRuntime || !PlaylistAudio || ActiveRecoveredMode != 2) return;
    if (PlaylistRuntime->bPreviousBreak != PlaylistRuntime->bOnBreak) {
        PlaylistRuntime->BreakFilterOrigin = FPlatformTime::Seconds();
        PlaylistRuntime->BreakFilterStart = PlaylistRuntime->CurrentBreakFilter;
        PlaylistRuntime->bPreviousBreak = PlaylistRuntime->bOnBreak;
    }
    const float RampAlpha = FMath::Clamp(static_cast<float>(FPlatformTime::Seconds() - PlaylistRuntime->BreakFilterOrigin), 0.f, 1.f);
    PlaylistRuntime->CurrentBreakFilter = FMath::Lerp(PlaylistRuntime->BreakFilterStart, PlaylistRuntime->bOnBreak ? 300.f : 20000.f, RampAlpha);
    PlaylistSound->SetLowPassFilterEnabled(PlaylistRuntime->bOnBreak || RampAlpha < 1);
    PlaylistSound->SetLowPassFilterFrequency(PlaylistRuntime->CurrentBreakFilter);
    if (!PlaylistRuntime->bPlaying || PlaylistRuntime->bPaused || PlaylistRuntime->GetAudioTime() < 0) { PlaylistAudio->Pause(); return; }
    if (!PlaylistAudio->IsReady()) return;
    const double ExpectedTime = PlaylistRuntime->GetAudioTime();
    if (!PlaylistAudio->IsPlaying()) {
        PlaylistAudio->Seek(FTimespan::FromSeconds(FMath::Max(ExpectedTime, 0.0)));
        PlaylistAudio->Play();
    }
}
void ARecoveredGlobalManager::HandlePlaylistEvent(const FRecoveredBeatmapEvent& Event) {
    if (Event.Type == TEXT("media_change")) {
        const FString Category = Event.Value.ToLower();
        const TArray<FString> Names = {TEXT("slow"), TEXT("medium"), TEXT("fast"), TEXT("succubus"), TEXT("cum"), TEXT("ass"), TEXT("boobs")};
        const uint8 Types[] = {0, 1, 2, 3, 6, 7, 8};
        const int32 Index = Names.IndexOfByKey(Category);
        if (Index != INDEX_NONE) {
            BeatContext.CardType = Types[Index];
            if (MediaDeckState && MediaDeckState->ChooseRandom(PlaylistDeckForCard(Types[Index]), false, SelectedRandomCard, true) && MediaPlayback) MediaPlayback->OpenEntry(SelectedRandomCard);
        }
    } else if (Event.Type == TEXT("cycle_media")) {
        if (MediaDeckState && MediaDeckState->ChooseRandom(PlaylistDeckForCard(BeatContext.CardType), false, SelectedRandomCard, true) && MediaPlayback) MediaPlayback->OpenEntry(SelectedRandomCard);
    } else if (Event.Type == TEXT("disable_break")) {
        if (Event.Value.Equals(TEXT("start"), ESearchCase::IgnoreCase)) { PlayerVariables.bCanUseItems = false; PlaylistRuntime->bBreakSectionDisabled = true; }
        else if (Event.Value.Equals(TEXT("end"), ESearchCase::IgnoreCase)) { PlayerVariables.bCanUseItems = !PlaylistRuntime->bOnBreak; PlaylistRuntime->bBreakSectionDisabled = false; }
    } else if (Event.Type == TEXT("restore_break")) { PlayerVariables.bCanUseItems = !PlaylistRuntime->bOnBreak; PlaylistRuntime->bBreakSectionDisabled = false; }
    else if (Event.Type == TEXT("grant_break")) AcquireStoreItem(TEXT("Break"));
    else if (Event.Type == TEXT("dialogue")) PlayDialogueLine(FName(*Event.Value));
    else if (Event.Type == TEXT("text")) PendingNotifications.Add(Event.Value);
    else if (Event.Type == TEXT("background")) ChangeRecoveredBeatBackground(FCString::Atoi(*Event.Value));
    else if (Event.Type == TEXT("edge")) OnSessionAction.Broadcast(TEXT("Edge"));
    else if (Event.Type == TEXT("cum_event") && !PlayerVariables.bHasCame) {
        if (Event.Value.Equals(TEXT("start"), ESearchCase::IgnoreCase)) { PlayerVariables.bIsAllowedToCum = true; BeatContext.CardType = 6; OpenRecoveredCumMedia(); }
        else if (Event.Value.Equals(TEXT("end"), ESearchCase::IgnoreCase)) PlayerVariables.bIsAllowedToCum = false;
    }
}
void ARecoveredGlobalManager::HandlePlaylistSongComplete(int32 CompletedRounds) {
    SessionStats.BestMusicModeWinRounds = FMath::Max(SessionStats.BestMusicModeWinRounds, CompletedRounds);
    if (PlaylistAudio) PlaylistAudio->Close();
    if (PlaylistRuntime->bAwaitingNextTrack) {
        const auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
        const URecoveredSaveGame* Save = Instance ? Instance->CurrentSave.Get() : nullptr;
        const bool Maxed = RecoveredMusicUpgrades::GetLevel(Save, 0) >= 5 && RecoveredMusicUpgrades::GetLevel(Save, 1) >= 5 && RecoveredMusicUpgrades::GetLevel(Save, 2) >= 5;
        if (Maxed) { if (!PlaylistRuntime->ContinuePlaylist(LastSessionError)) HandlePlaylistAudioFailed(LastSessionError); }
        else OpenRecoveredModes();
    }
}
void ARecoveredGlobalManager::HandlePlaylistComplete(int32 CompletedRounds) {
    if (GetWorld()) GetWorldTimerManager().ClearTimer(PlaylistAudioTimer);
    if (CompletedRounds > 0) SuccessfulCum();
}
bool ARecoveredGlobalManager::StartTowerSession(int32 Rounds, bool Endless) {
    if (!TowerRuntime->LoadSourceCatalog(LastSessionError)) return false;
    if (!InitializeRecoveredSession()) return false;
    StopRecoveredModes(); ActiveRecoveredMode = 1;
    if (auto* Inventory = RecoveredNewerInventoryAdapter::GetInventory(*this)) Inventory->OwnedItems=RecoveredNewerInventoryAdapter::MakeNativeTowerInventory(*Inventory);
    if (BeatTimeline) BeatTimeline->StopSequence();
    if (MainMenu) MainMenu->RemoveFromParent();
    TArray<FRecoveredTowerOption> Pool;
    for (uint8 Objective : {uint8(0), uint8(1), uint8(2), uint8(3), uint8(6), uint8(7), uint8(8)}) {
        auto& Option = Pool.AddDefaulted_GetRef(); Option.Objective = Objective;
        // Parameters are rolled from the source's objective/tier row when the
        // option is drafted, not inferred from baseline difficulty settings.
        Option.ObjectiveParam = 1;
        Option.DifficultyTier = 1;
    }
    const int32 ShopEvery = Rounds <= 3 ? 1 : FMath::Clamp(FMath::RoundToInt(FMath::Sqrt(static_cast<float>(Rounds))), 1, 4);
    if (!TowerRuntime->StartSession(Rounds, Endless, ShopEvery, Pool, FMath::Rand(), LastSessionError)) { const FString Error = LastSessionError; ReturnToMainMenu(); LastSessionError = Error; return false; }
    GetWorldTimerManager().SetTimer(PlaylistAudioTimer, this, &ARecoveredGlobalManager::TickPlaylistAudio, .1f, true);
    OpenRecoveredModes(); return true;
}
void ARecoveredGlobalManager::HandleTowerRoundStarted(const FRecoveredTowerOption& Option) {
    CurrentSessionObjective = Option.Objective;
    TowerRuntime->BaselineStats = SessionStats;
    TowerRuntime->BaselineStrokes = SessionStats.Strokes; TowerRuntime->BaselineEdges = SessionStats.Edges; TowerRuntime->BaselineDuration = PlayerVariables.SessionLength;
    TowerRuntime->BaselineSuccubi = SessionStats.SuccubiDefeated; TowerRuntime->BaselineMilking = SessionStats.MilkingCount; TowerRuntime->BaselineCoins = PlayerVariables.PlayerCoins;
    BeatContext.ActiveModifiers.Reset(); for (const FName Modifier : Option.Modifiers) BeatContext.ActiveModifiers.Add(Modifier.ToString());
    CumMeterPercentage = 0; PlayerVariables.bHasCame = false; PlayerVariables.bIsAllowedToCum = Option.Objective == 6 || Option.Objective == 7; bStopSequence = false; IsAutoDrawEnabled = true;
    RequestNextRecoveredCard(true);
}
void ARecoveredGlobalManager::HandleTowerRoundCompleted(int32 CompletedRounds) {
    if (BeatTimeline) BeatTimeline->StopSequence();
    IsAutoDrawEnabled = false;
    FRecoveredSessionStats RoundStats = SessionStats;
    RoundStats.Strokes -= TowerRuntime->BaselineStats.Strokes;
    RoundStats.Edges -= TowerRuntime->BaselineStats.Edges;
    RoundStats.DefensiveItemsUsed -= TowerRuntime->BaselineStats.DefensiveItemsUsed;
    RoundStats.OffensiveItemsUsed -= TowerRuntime->BaselineStats.OffensiveItemsUsed;
    RoundStats.TimesTaunted -= TowerRuntime->BaselineStats.TimesTaunted;
    RoundStats.AcceptedTemptation -= TowerRuntime->BaselineStats.AcceptedTemptation;
    RoundStats.SessionDuration = PlayerVariables.SessionLength - TowerRuntime->BaselineDuration;
    TowerRuntime->RoundHistory.Add(RoundStats);
    if (TowerRuntime->bLastRoundSucceeded) {
        if (!TowerRuntime->SelectedOption.NativeRewards.IsEmpty()) RecoveredTowerRewards::Apply(*this,TowerRuntime->SelectedOption.NativeRewards);
        else {
            AddCoins(TowerRuntime->SelectedOption.RewardCoins);
            if (SuccuEconomy) SuccuEconomy->AddSuccuCoins(TowerRuntime->SelectedOption.RewardSuccuCoins);
        }
    }
    OpenRecoveredModes();
}
void ARecoveredGlobalManager::HandleTowerComplete(int32 CompletedRounds) {
    if (GetWorld()) GetWorldTimerManager().ClearTimer(PlaylistAudioTimer);
    const bool Won = CompletedRounds > 0 && TowerRuntime->FailedRounds == 0;
    if (Won) {
        SessionStats.BestTowerWinRounds=FMath::Max(SessionStats.BestTowerWinRounds,CompletedRounds);
        OnMetricUpdateRequested.Broadcast(ERecoveredMetric::BestTowerWinRounds,CompletedRounds);
    }
    StopRecoveredModes();
    if (Won) SuccessfulCum(); else PrematureCum();
}
