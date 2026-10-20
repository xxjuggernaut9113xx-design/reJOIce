#include "RecoveredRules.h"
#include "RecoveredDialogueAudio.h"
#include "RecoveredProgressionResources.h"
#include "Sound/SoundBase.h"
#include "DataTableUtils.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HAL/PlatformTime.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredEventRules.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredMenu.h"
#include "RecoveredFileImportManager.h"
#include "RecoveredSuccuEconomy.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"

void URecoveredGameInstance::Init() {
    Super::Init();
    DeviceManager=NewObject<URecoveredDeviceManager>(this);
    LoadRecoveredSave();
    if (!FileImportManager) FileImportManager=NewObject<URecoveredFileImportManager>(this);
    if (CurrentSave) FileImportManager->LoadFromSave(CurrentSave);
}

void ARecoveredGlobalManager::SuccessfulCum() {
    if (ActiveRecoveredMode==1 && TowerRuntime && (TowerRuntime->Phase==ERecoveredRoundPhase::Playing || TowerRuntime->Phase==ERecoveredRoundPhase::BossRound)) {
        TowerRuntime->CompleteRound(true);
        return;
    }
    if (ActiveRecoveredMode==2 && PlaylistRuntime) {
        SessionStats.BestMusicModeWinRounds=FMath::Max(SessionStats.BestMusicModeWinRounds,PlaylistRuntime->CompletedRounds);
        if (SessionStats.BestMusicModeWinRounds>0) OnMetricUpdateRequested.Broadcast(ERecoveredMetric::BestMusicModeWinRounds,SessionStats.BestMusicModeWinRounds);
        StopRecoveredModes();
    }
    LastOutcomeEffects=URecoveredOutcomeLibrary::ApplyOutcome(PlayerVariables,SessionStats,BeatContext.CardType,true,bHasTaunted,false);
    if (CurrentDifficulty==ERecoveredDifficulty::InsaneMode) {
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::SessionsWonAtMaxDifficulty,1);
        LastOutcomeEffects.MetricRequests.Add(ERecoveredMetric::SessionsWonAtMaxDifficulty);
    }
    if (CurrentSessionObjective==8 || CurrentSessionObjective==3) {
        const auto ObjectiveMetric=CurrentSessionObjective==8 ? ERecoveredMetric::SuccuSlayerSessionsWon : ERecoveredMetric::EdgeSessionsWon;
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ObjectiveMetric,1);
        LastOutcomeEffects.MetricRequests.Add(ObjectiveMetric);
    }
    for(const auto Metric:LastOutcomeEffects.MetricRequests) OnMetricUpdateRequested.Broadcast(Metric,1);
    OnOutcomeRequested.Broadcast(LastOutcomeEffects);
}

void ARecoveredGlobalManager::PrematureCum() {
    if (ActiveRecoveredMode==1 && TowerRuntime && (TowerRuntime->Phase==ERecoveredRoundPhase::Playing || TowerRuntime->Phase==ERecoveredRoundPhase::BossRound)) {
        TowerRuntime->CompleteRound(false);
        return;
    }
    if (ActiveRecoveredMode==2) {
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::DisabledBreakSectionFailures,1);
        OnMetricUpdateRequested.Broadcast(ERecoveredMetric::DisabledBreakSectionFailures,1);
        SessionStats.BestMusicModeWinRounds=0;
        StopRecoveredModes();
    }
    const bool bIronManActive=BeatContext.ActiveModifiers.ContainsByPredicate([](const FString& Tag) { return Tag.Equals(TEXT("Iron Man"),ESearchCase::IgnoreCase); });
    LastOutcomeEffects=URecoveredOutcomeLibrary::ApplyOutcome(PlayerVariables,SessionStats,BeatContext.CardType,false,bHasTaunted,bIronManActive);
    for(const auto Metric:LastOutcomeEffects.MetricRequests) OnMetricUpdateRequested.Broadcast(Metric,1);
    OnOutcomeRequested.Broadcast(LastOutcomeEffects);
}

void ARecoveredGlobalManager::RecordRecoveredMilking() {
    if (CurrentSessionObjective!=7 || PlayerVariables.bHasCame) return;
    const bool Devil=BeatContext.ActiveModifiers.ContainsByPredicate([](const FString& Modifier) {
        return Modifier.Equals(TEXT("Deal With The Devil"),ESearchCase::IgnoreCase);
    });
    if (Devil && BeatContext.CardType!=3) return;
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::MilkingCount,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::MilkingCount,1);
    if (ActiveRecoveredMode==1 && TowerRuntime && SessionStats.MilkingCount-TowerRuntime->BaselineMilking>=TowerRuntime->SelectedOption.ObjectiveParam) TowerRuntime->CompleteRound(true);
    else if (ActiveRecoveredMode==0 && CurrentSessionObjective==7 && ClassicObjectiveRuntime.bActive && RecoveredObjectives::IsComplete(ClassicObjectiveRuntime,PlayerVariables,SessionStats,CumMeterPercentage)) SuccessfulCum();
}

void ARecoveredGlobalManager::ResolveRecoveredClimaxRequest() {
    if (ActiveRecoveredMode==2 && (!PlaylistRuntime || !PlaylistRuntime->bPlaying || PlaylistRuntime->bAwaitingNextTrack || PlaylistRuntime->bPaused)) return;
    if (ActiveRecoveredMode==1 && TowerRuntime && TowerRuntime->Phase!=ERecoveredRoundPhase::Playing && TowerRuntime->Phase!=ERecoveredRoundPhase::BossRound) return;
    if (CurrentSessionObjective==6 && ActiveRecoveredMode==1 && TowerRuntime) {
        if (PlayerVariables.SessionLength-TowerRuntime->BaselineDuration<=TowerRuntime->SelectedOption.ObjectiveParam) SuccessfulCum();
        return;
    }
    if (CurrentSessionObjective==6 && ActiveRecoveredMode==0 && ClassicObjectiveRuntime.bActive) {
        if (PlayerVariables.bHasCame) return;
        if (PlayerVariables.SessionLength-ClassicObjectiveRuntime.BaselineDuration<=ClassicObjectiveRuntime.Target) SuccessfulCum();else PrematureCum();
        return;
    }
    if (BeatContext.CardType==5) { PrematureCum(); return; }
    if (PlayerVariables.bHasCame) return;
    if (PlayerVariables.bIsAllowedToCum) SuccessfulCum();
    else PrematureCum();
}

FRecoveredDifficultyConfig URecoveredRuleLibrary::GetDifficultyConfig(ERecoveredDifficulty Difficulty) {
    FRecoveredDifficultyConfig Result;
    switch (Difficulty) {
    case ERecoveredDifficulty::EasyMode:
        Result.DifficultyHeatGainMultiplier = 0.5;
        Result.DifficultyCoinEarnMultiplier = 2.0;
        Result.DifficultyStrokeCounterMultiplier = 0.5;
        Result.DifficultyStrokeSpeedMultiplier = 1.85;
        Result.CumMeterMultiplier = 8.0;
        Result.CumIncreaseItemSpawnChance = 20.0;
        Result.DecreaseHeatItemSpawnChance = 40.0;
        Result.EdgeItemSpawnChance = 45.0;
        Result.BreakItemSpawnChance = 35.0;
        Result.SlowdownItemSpawnChance = 40.0;
        Result.BonerPillSpawnChance = 75.0;
        Result.SuccuShieldSpawnChance = 20.0;
        break;
    case ERecoveredDifficulty::NormalMode:
        Result.DifficultyHeatGainMultiplier = 1.0;
        Result.DifficultyCoinEarnMultiplier = 1.0;
        Result.DifficultyStrokeCounterMultiplier = 1.0;
        Result.DifficultyStrokeSpeedMultiplier = 1.0;
        Result.CumMeterMultiplier = 1.0;
        Result.CumIncreaseItemSpawnChance = 8.0;
        Result.DecreaseHeatItemSpawnChance = 25.0;
        Result.EdgeItemSpawnChance = 15.0;
        Result.BreakItemSpawnChance = 15.0;
        Result.SlowdownItemSpawnChance = 15.0;
        Result.BonerPillSpawnChance = 50.0;
        Result.SuccuShieldSpawnChance = 10.0;
        break;
    case ERecoveredDifficulty::InsaneMode:
        Result.DifficultyHeatGainMultiplier = 3.0;
        Result.DifficultyCoinEarnMultiplier = 0.5;
        Result.DifficultyStrokeCounterMultiplier = 2.0;
        Result.DifficultyStrokeSpeedMultiplier = 0.6;
        Result.CumMeterMultiplier = 0.5;
        Result.CumIncreaseItemSpawnChance = 3.0;
        Result.DecreaseHeatItemSpawnChance = 10.0;
        Result.EdgeItemSpawnChance = 5.0;
        Result.BreakItemSpawnChance = 5.0;
        Result.SlowdownItemSpawnChance = 10.0;
        Result.BonerPillSpawnChance = 35.0;
        Result.SuccuShieldSpawnChance = 5.0;
        break;
    default: return GetDifficultyConfig(ERecoveredDifficulty::NormalMode);
    }
    return Result;
}

double URecoveredRuleLibrary::CalculateHeat(double Heat, double HeatAdd, double HeatGainMultiplier) {
    return FMath::Clamp(Heat + HeatAdd * HeatGainMultiplier, 0.0, 100.0);
}
bool URecoveredRuleLibrary::EvaluateChance(double Roll, double Chance) { return Roll <= Chance; }
float URecoveredRuleLibrary::ClampBeatInterval(float Interval) { return Interval <= 0.01f ? 0.01f : Interval; }
float URecoveredRuleLibrary::ClampSpeedItemMultiplier(float Multiplier) {
    if (5.0f <= Multiplier) Multiplier = 5.0f;
    if (Multiplier <= 0.1f) Multiplier = 0.1f;
    return Multiplier;
}
UScriptStruct* URecoveredRuleLibrary::GetChallengeRowStruct() { return FRecoveredChallengeRow::StaticStruct(); }
UScriptStruct* URecoveredRuleLibrary::GetLevelRowStruct() { return FRecoveredLevelRow::StaticStruct(); }
UScriptStruct* URecoveredRuleLibrary::GetPlayerCardRowStruct() { return FRecoveredPlayerCardRow::StaticStruct(); }
UScriptStruct* URecoveredRuleLibrary::GetHeatCategoryRowStruct() { return FRecoveredHeatCategoryRow::StaticStruct(); }
UScriptStruct* URecoveredRuleLibrary::GetModifierRowStruct() { return FRecoveredModifierRow::StaticStruct(); }
FString URecoveredRuleLibrary::ExportTableJson(UDataTable* Table) {
#if WITH_EDITOR
    return Table ? Table->GetTableAsJSON(EDataTableExportFlags::UseJsonObjectsForStructs | EDataTableExportFlags::UseSimpleText) : TEXT("[]");
#else
    if (!Table || !Table->GetRowStruct()) return TEXT("[]");
    TArray<TSharedPtr<FJsonValue>> Rows;
    for (const auto& Entry:Table->GetRowMap()) {
        auto Row=MakeShared<FJsonObject>();Row->SetStringField(TEXT("Name"),Entry.Key.ToString());
        for (TFieldIterator<FProperty> Property(Table->GetRowStruct());Property;++Property) {
            auto Value=FJsonObjectConverter::UPropertyToJsonValue(*Property,Property->ContainerPtrToValuePtr<void>(Entry.Value));
            if (!Value.IsValid()) return FString();
            Row->SetField(Property->GetName(),Value);
        }
        Rows.Add(MakeShared<FJsonValueObject>(Row));
    }
    FString Result;
    return FJsonSerializer::Serialize(Rows,TJsonWriterFactory<>::Create(&Result)) ? Result : FString();
#endif
}
ARecoveredGlobalManager::ARecoveredGlobalManager() {
    PrimaryActorTick.bCanEverTick=true;
    ActiveDifficulty = URecoveredRuleLibrary::GetDifficultyConfig(CurrentDifficulty);
    BeatTimeline = CreateDefaultSubobject<URecoveredBeatTimeline>(TEXT("RecoveredBeatTimeline"));
    InitializeRecoveredModes();
    SuccuEconomy=CreateDefaultSubobject<URecoveredSuccuEconomy>(TEXT("RecoveredSuccuEconomy"));
}
void ARecoveredGlobalManager::Tick(float DeltaSeconds) {
    Super::Tick(DeltaSeconds);
    TickRecoveredNewerItems(DeltaSeconds);
    if (ActiveRecoveredMode==0) TickRecoveredObjectives();
}
void ARecoveredGlobalManager::ApplyDifficulty(ERecoveredDifficulty Difficulty) {
    CurrentDifficulty = Difficulty;
    ActiveDifficulty = URecoveredRuleLibrary::GetDifficultyConfig(Difficulty);
    PlayerVariables.CumMeterMultiplier = ActiveDifficulty.CumMeterMultiplier;
}
void ARecoveredGlobalManager::InitializeDifficultyVariables(uint8 SavedEdgePacingIndex, uint8 SavedStrokeMultiplierIndex) {
    ApplyDifficulty(CurrentDifficulty);
    EdgePacingMultiplier = URecoveredStateRuleLibrary::GetPreferenceMultiplier(SavedEdgePacingIndex, EdgePacingMultiplier);
    UserStrokeCountMultiplier = URecoveredStateRuleLibrary::GetPreferenceMultiplier(SavedStrokeMultiplierIndex, UserStrokeCountMultiplier);
}
void ARecoveredGlobalManager::AddHeat(double HeatAdd) {
    const double Adjusted=SuccuEconomy ? SuccuEconomy->AdjustHeatGain(HeatAdd) : HeatAdd;
    HeatLevel = URecoveredRuleLibrary::CalculateHeat(HeatLevel, Adjusted, ActiveDifficulty.DifficultyHeatGainMultiplier);
    if (SuccuEconomy) HeatLevel=FMath::Min(HeatLevel,SuccuEconomy->GetHeatCap());
}
void ARecoveredGlobalManager::AddCoins(int32 Coins) {
    if (SuccuEconomy && SuccuEconomy->RollBankingError()) Coins=URecoveredStateRuleLibrary::AddInt32Wrapping(Coins,Coins);
    const int32 Earned = URecoveredStateRuleLibrary::AddCoinsToState(PlayerVariables, Coins);
    if (Earned>0) PlayerVariables.SessionCoinsEarned=URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.SessionCoinsEarned,Earned);
    OnCoinsAdded.Broadcast(Earned, PlayerVariables.PlayerCoins);
}
void ARecoveredGlobalManager::AddToCumMeter(double Amount) {
    CumMeterPercentage = URecoveredStateRuleLibrary::AddToCumMeter(CumMeterPercentage, Amount);
}
void ARecoveredGlobalManager::AddToLootBar(double Amount) {
    if (SuccuEconomy && SuccuEconomy->HasModifier(9) && BeatContext.CardType==3) Amount*=2;
    double EffectiveMultiplier=LootBarMultiplier;
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        if (BeatContext.ActiveModifiers.Contains(TEXT("Overencumbered"))) {
            int64 Total=0;
            for (const auto Type:Inventory->HotbarItems) Total+=Inventory->GetItemState(Type).Charges;
            if (Total>=2) EffectiveMultiplier-=.5;
        }
        if (BeatContext.ActiveModifiers.Contains(TEXT("Greed Machine"))) {
            const double Combo=PlayerVariables.CurrentComboCount;
            if (Combo+1667!=0) EffectiveMultiplier+=2*Combo/(Combo+1667);
        }
    }
    LootBarPercentage = URecoveredStateRuleLibrary::AddToLootBar(LootBarPercentage, Amount, EffectiveMultiplier);
}
void ARecoveredGlobalManager::AddToEdgeBank(int32 Coins) {
    EdgeBank = URecoveredStateRuleLibrary::AddInt32Wrapping(EdgeBank, Coins);
    OnEdgeBankAdded.Broadcast(Coins, EdgeBank);
}
void ARecoveredGlobalManager::AddToPointsSpent(int32 Amount) {
    PointsSpent = URecoveredStateRuleLibrary::AddInt32Wrapping(PointsSpent, Amount);
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::MoneySpent, Amount);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::MoneySpent, Amount);
}
void ARecoveredGlobalManager::DetermineComboType() {
    CurrentComboTypeEnum = URecoveredStateRuleLibrary::DetermineComboTier(PlayerVariables.CurrentComboCount, CurrentComboTypeEnum);
}
void ARecoveredGlobalManager::UpdateMinimumBeatInterval(const FRecoveredDeviceState& Devices) {
    MinimumBeatInterval = URecoveredStateRuleLibrary::GetMinimumBeatInterval(static_cast<uint8>(CurrentDifficulty), Devices, MinimumBeatInterval);
    BeatTimeline->MinimumBeatInterval = MinimumBeatInterval;
}
void ARecoveredGlobalManager::CalculateBeatPitch(int32 TotalBeats, int32 RemainingBeats) {
    CurrentPitch = URecoveredStateRuleLibrary::CalculateBeatPitch(TotalBeats, RemainingBeats);
}
void ARecoveredGlobalManager::UpdateBeatCompleteMetrics() {
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::Strokes, 1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::Strokes, 1);
    URecoveredStateRuleLibrary::SetMaximumCombo(SessionStats, PlayerVariables.CurrentComboCount);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::StrokeCombo, PlayerVariables.CurrentComboCount);
}
void ARecoveredGlobalManager::SetSessionDuration() {
    URecoveredStateRuleLibrary::AdvanceSessionDuration(PlayerVariables, SessionStats, HeatLevel);
    if (HeatLevel >= 70.0) OnMetricUpdateRequested.Broadcast(ERecoveredMetric::TimeAtHighHeat, 1);
}
void ARecoveredGlobalManager::BreakCombo() {
    URecoveredSessionRuleLibrary::BreakCombo(PlayerVariables);
}
void ARecoveredGlobalManager::AddBeatLootReward() {
    if (!bLootBarEnabled) return;
    if (LootBarPercentage >= 1.0) {
        OnSessionAction.Broadcast(TEXT("RollAndGiveLootDropsV2"));
        OnSessionAction.Broadcast(TEXT("CreateLootRewardWidget"));
        LootBarPercentage = 0;
    }
    const double Amount = URecoveredSessionRuleLibrary::GetLootIncrement(BeatContext.CardType, BeatContext.ActiveModifiers.Contains(TEXT("Mr. Money Bandz")));
    if (Amount != 0) AddToLootBar(Amount);
}
void ARecoveredGlobalManager::BeatComplete() {
    PlayerVariables.TotalStrokeCount = URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.TotalStrokeCount, 1);
    PlayerVariables.CurrentComboCount = URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.CurrentComboCount, 1);
    OnSessionAction.Broadcast(TEXT("DetermineBeatCompleteSFX"));
    OnSessionAction.Broadcast(TEXT("AddOneToLifetimeStrokesSave"));
    PlayerVariables.CurrentStrokeCount = URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.CurrentStrokeCount, -1);
    OnSessionAction.Broadcast(TEXT("DetermineAndPlayMainImageBeatComplete"));
    OnSessionAction.Broadcast(TEXT("DetermineAndPlayHeatGainAnimsOnBeatComplete"));
    DetermineComboType();
    OnSessionAction.Broadcast(TEXT("DetermineAndPlayComboTypeAnimBeatCompletes"));
    const int32 CoinAward = URecoveredSessionRuleLibrary::GetCoinAward(BeatContext.CardType);
    if (RecoveredNewerInventoryAdapter::GetInventory(*this) && BeatContext.CardType==3 && BeatContext.ActiveModifiers.Contains(TEXT("Avarice"))) PlayerVariables.PlayerCoins-=1;
    else if (CoinAward != 0) AddCoins(CoinAward);
    if (BeatContext.HeatCategory <= 2) AddHeat(URecoveredSessionRuleLibrary::GetHeatAward(BeatContext));
    URecoveredSessionRuleLibrary::AddBeatMeter(PlayerVariables, BeatContext, HeatLevel, BaseMeterGain, CumMeterPercentage);
    OnSessionAction.Broadcast(TEXT("DetermineAndTriggerMeterOverride"));
    OnSessionAction.Broadcast(TEXT("SpawnWidget_Onomatopoeia"));
    AddBeatLootReward();
    OnSessionAction.Broadcast(TEXT("PlayBrainMelter"));
    OnSessionAction.Broadcast(TEXT("BeatCompleteClothesBreaker"));
    OnSessionAction.Broadcast(TEXT("UpdateEdgeStreakProgressBar"));
    UpdateBeatCompleteMetrics();
}
void ARecoveredGlobalManager::HandleBeatHitCenter(const FRecoveredBeatEvent& Event) {
    if (MediaPlayback && MediaPlayback->bBeatSyncEnabled) {
        MediaPlayback->SyncToBeat(Event.TargetHitTime,FPlatformTime::Seconds(),0.0);
    }
    if (URecoveredGameInstance* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->DeviceManager) Instance->DeviceManager->DispatchBeatHitCenter(Event);
    }
    BeatComplete();
}
void ARecoveredGlobalManager::HandleRecoveredDeviceBeat(const FRecoveredBeatEvent& Event) {
    if (URecoveredGameInstance* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->DeviceManager) Instance->DeviceManager->DispatchBeat(Event);
    }
}
void ARecoveredGlobalManager::HandleRecoveredDeviceStateChanged(ERecoveredDeviceKind DeviceType, bool bConnected) {
    if (URecoveredGameInstance* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->DeviceManager) UpdateMinimumBeatInterval(Instance->DeviceManager->GetGameplayDeviceState());
    }
}
void ARecoveredGlobalManager::ApplySavedCalibrationToTimeline() {
    if (!BeatTimeline) return;
    double OffsetSeconds = 0;
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CalibrationManager && Instance->CalibrationManager->CurrentProfile.IsValid()) {
            OffsetSeconds = Instance->CalibrationManager->GetCompensatedTimelineOffset();
        }
    }
    BeatTimeline->ApplyCalibrationOffset(OffsetSeconds);
}
bool ARecoveredGlobalManager::ApplyStoreItemEffect(FName ItemID, int32 Level) {
    const FString ID = ItemID.ToString();
    const float Potency = 1.0f + 0.25f * static_cast<float>(Level);
    bool bApplied = false;
    if (ID == TEXT("Slowdown")) {
        if (BeatTimeline && bCanUseSlowdown) {
            BeatTimeline->ApplySpeedModifier(0.6f);
            bCanUseSlowdown = false;
            bApplied = true;
        }
    } else if (ID == TEXT("BonerPill")) {
        return UseRecoveredBonerPillItem()==ERecoveredDefensiveItemUseResult::Triggered;
    } else if (ID == TEXT("DecreaseHeat")) {
        AddHeat(-25.0 * Potency);
        bApplied = true;
    } else if (ID == TEXT("SuccuShield")) {
        return ToggleRecoveredSuccuShields()==ERecoveredDefensiveItemUseResult::Triggered;
    } else if (ID == TEXT("Edge")) {
        PlayerVariables.bIsPlayerEdgeable = true;
        bApplied = true;
    } else if (ID == TEXT("Resupply")) {
        bCanUseSlowdown = true;
        bCanUseBonerPill = true;
        PlayerVariables.bCanUseItems = true;
        bApplied = true;
    } else if (ID == TEXT("XCumChance")) {
        PlayerVariables.bIsAllowedToCum = true;
        bApplied = true;
    } else if (ID == TEXT("Break")) {
        if (BeatTimeline) BeatTimeline->PauseSequence();
        if (MediaPlayback) MediaPlayback->SetPaused(true);
        bApplied = true;
    }
    if (!bApplied) return false;
    PlayerVariables.TotalDefenseItemUses += 1;
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::ItemsUsed, 1);
    OnSessionAction.Broadcast(FName(*(FString(TEXT("StoreItemUsed_")) + ID)));
    return true;
}
bool ARecoveredGlobalManager::StartRecoveredBeatSequence(const FRecoveredBeatPattern& Pattern, double BaseInterval, int32 StrokeCount, float SpeedModifier, double TravelTime) {
    if (SuccuEconomy && SuccuEconomy->HasModifier(6)) BaseInterval*=2;
    // Bind to the live actor after subobject instancing, rather than the class-default actor.
    BeatTimeline->OnBeatFired.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleRecoveredDeviceBeat);
    BeatTimeline->OnBeatHitCenter.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleBeatHitCenter);
    BeatTimeline->OnSequenceEnd.AddUniqueDynamic(this, &ARecoveredGlobalManager::CompleteBeatSequence);
    if (URecoveredGameInstance* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->DeviceManager) UpdateMinimumBeatInterval(Instance->DeviceManager->GetGameplayDeviceState());
    }
    ApplySavedCalibrationToTimeline();
    if (MediaPlayback && MediaPlayback->bBeatSyncEnabled) {
        const double MasterTime=FPlatformTime::Seconds();
        MediaPlayback->SetBeatInterval(BaseInterval);
        MediaPlayback->BeginPatternSynchronization(MasterTime,0.0,TravelTime);
    }
    if (!BeatTimeline->StartPattern(Pattern, BaseInterval, StrokeCount, SpeedModifier, TravelTime)) return false;
    PlayerVariables.CurrentStrokeCount = StrokeCount;
    PlayerVariables.AssignedStrokeCount = StrokeCount;
    bStopSequence = false;
    return true;
}
void ARecoveredGlobalManager::CompleteBeatSequence() {
    if (!IsAutoDrawEnabled) return;
    bCanUseSlowdown = true;
    bCanUseBonerPill = true;
    if (bStopSequence || BeatTimeline->GetBeatsRemaining() > 0 || BeatContext.CardType > 8) return;
    RollAndGiveLootDrops();
    if (BeatContext.CardType == 3) {
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::SuccubiDefeated, 1);
        OnMetricUpdateRequested.Broadcast(ERecoveredMetric::SuccubiDefeated, 1);
        ConsecutiveSuccubiSurvived = URecoveredStateRuleLibrary::AddInt32Wrapping(ConsecutiveSuccubiSurvived, 1);
    } else {
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::EnemiesDefeated, 1);
        OnMetricUpdateRequested.Broadcast(ERecoveredMetric::EnemiesDefeated, 1);
        ConsecutiveSuccubiSurvived = 0;
    }
    URecoveredStateRuleLibrary::SetSessionMetric(SessionStats, ERecoveredMetric::ConsecutiveSuccubiSurvived, ConsecutiveSuccubiSurvived);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::ConsecutiveSuccubiSurvived, ConsecutiveSuccubiSurvived);
    OnSessionAction.Broadcast(TEXT("PlayDrawButtonAnimation"));
    if (BeatContext.CardType != 5) RequestNextRecoveredCard(true);
}

bool ARecoveredGlobalManager::LoadMediaPack(const FString& ManifestPath,const TArray<FString>& ExcludedTags) {
    TArray<FRecoveredMediaEntry> Entries;
    if(!URecoveredMediaLibrary::ReadPackManifest(ManifestPath,Entries,LastSessionError)) return false;
    if (const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->FileImportManager) {
            // BP_CardManager appends imported entries before enabled-pack media.
            TArray<FRecoveredMediaEntry> ImportedEntries=Instance->FileImportManager->GetImportedMediaEntries();
            ImportedEntries.Append(Entries);
            Entries=MoveTemp(ImportedEntries);
        }
    }
    if(!MediaDeckState) MediaDeckState=NewObject<URecoveredDeckState>(this);
    MediaDeckState->Master=URecoveredMediaLibrary::FilterMedia(Entries,ExcludedTags,BeatContext.ActiveModifiers.Contains(TEXT("Ass Fanatic")),BeatContext.ActiveModifiers.Contains(TEXT("Boobs Fanatic")),BeatContext.ActiveModifiers.Contains(TEXT("Feet Fanatic")));
    MediaDeckState->SetChildDecks();
    if (const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (const URecoveredSaveGame* Save=Instance->CurrentSave) {
            for (uint8 Deck=0;Deck<5;++Deck) {
                const FString Key=URecoveredDeckState::FavoriteSaveKey(Deck);
                TArray<FString> Paths=Save->GetStringArraySetting(Key);
                // Preserve favorites created before categories were recovered.
                if (Paths.IsEmpty() && !Save->HasSetting(Key)) Paths=Save->GetStringArraySetting(TEXT("FavoriteMedia"));
                MediaDeckState->RestoreFavoritePaths(Deck,Paths);
            }
        }
    }
    if(!MediaPlayback) {
        MediaPlayback=NewObject<URecoveredMediaPlayback>(this);
        MediaPlayback->SetLooping(bVideoLoopEnabled);
        MediaPlayback->OnMediaError.AddUniqueDynamic(this, &ARecoveredGlobalManager::HandleMediaPlaybackError);
    }
    return true;
}

bool ARecoveredGlobalManager::OpenRecoveredCumMedia(bool bPlayMedia) {
    LastSessionError.Reset();
    if (!MediaDeckState) {
        LastSessionError=TEXT("Cum media deck is unavailable");
        return false;
    }
    if (!MediaDeckState->ChooseRandom(4,false,SelectedRandomCard,true)) {
        LastSessionError=TEXT("Cum media deck is empty");
        return false;
    }
    if (bPlayMedia && MediaPlayback && !MediaPlayback->OpenEntry(SelectedRandomCard)) {
        LastSessionError=TEXT("Cum media could not be opened");
        return false;
    }
    OnSessionAction.Broadcast(TEXT("CumMediaOpened"));
    return true;
}
bool ARecoveredGlobalManager::DrawPaceCard(uint8 Pace,bool bPlayMedia) {
    return StartPaceCard(Pace,bPlayMedia,true);
}
bool ARecoveredGlobalManager::StartPaceCard(uint8 Pace,bool bPlayMedia,bool bPrepare) {
    LastSessionError.Reset();
    if(Pace>2 || !Rules || !HeatCategoryDataTable || !MediaDeckState) { LastSessionError=TEXT("Pace, rules, timing table or media deck is unavailable");return false; }
    const FName RowName=Pace==0 ? TEXT("SlowHeat") : Pace==1 ? TEXT("MediumHeat") : TEXT("HighHeat");
    const auto* Row=HeatCategoryDataTable->FindRow<FRecoveredHeatCategoryRow>(RowName,TEXT("Recovered pace draw"));
    const auto& Patterns=Pace==0 ? Rules->SlowBeatPatterns : Pace==1 ? Rules->MediumBeatPatterns : Rules->FastBeatPatterns;
    if(!Row || Patterns.IsEmpty()) { LastSessionError=TEXT("Pace timing row or pattern bank is missing");return false; }
    if(bPrepare && !PrepareDrawState()) return false;
    MediaDeckState->ReplaceEmptyDecks();
    if(!MediaDeckState->Draw(Pace,false,SelectedRandomCard)) { LastSessionError=TEXT("Selected media deck is empty");return false; }
    const double MinInterval=Pace==2 ? 0.15 : Row->MinIntervalSeconds;
    const int32 RolledStrokes=UKismetMathLibrary::RandomIntegerInRange(Row->MinStrokeCount,Row->MaxStrokeCount);
    const double RolledInterval=UKismetMathLibrary::RandomFloatInRange(MinInterval,Row->MaxIntervalSeconds);
    const auto Timing=URecoveredCardRuleLibrary::CalculateCardTiming(RolledStrokes,RolledInterval,StrokeCountMultiplier,UserStrokeCountMultiplier,StrokeTimeMultiplier);
    PlayerVariables.BeatSpawnInterval=Timing.BeatInterval;
    // SpawnCustomCardEvent assigns the beat interval before it starts the media.
    if (bPlayMedia && MediaPlayback) {
        MediaPlayback->SetBeatInterval(Timing.BeatInterval);
        MediaPlayback->OpenEntry(SelectedRandomCard,BeatTravelTime);
    }
    const auto Pattern=URecoveredSessionRuleLibrary::CheckIntervalMultipliers(Patterns[UKismetMathLibrary::RandomIntegerInRange(0,Patterns.Num()-1)],BeatTimeline->GetCurrentInterval());
    if(!StartRecoveredBeatSequence(Pattern,Timing.BeatInterval,Timing.StrokeCount,1.0f,BeatTravelTime)) { LastSessionError=TEXT("Beat timeline rejected card timing");return false; }
    bPlayerEdgedLastDraw=false;
    BeatContext.CardType=Pace;
    PlayRecoveredSessionSound(Pace==0 ? TEXT("SlowPace") : Pace==1 ? TEXT("MediumPace") : TEXT("FastPace"));
    if (auto* Menu=Cast<URecoveredMenuWidget>(SessionScreen)) {
        Menu->PlayRecoveredAnimation(Pace==0 ? TEXT("SlowPaceAnim") : Pace==1 ? TEXT("MediumPaceAnim") : TEXT("FastPaceAnim"));
    }
    if (IsRecoveredNewerProgressionEnabled()&&GetWorld()) {
        FString Pronoun=TEXT("Male");
        bool bSPHEnabled=true;
        bool bVoiceEnabled=true;
        if (const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
            if (Instance->CurrentSave) {
                const int32 Selection=FMath::Clamp(FMath::RoundToInt(Instance->CurrentSave->GetNumberSetting(TEXT("PlayerPronounSelection"),0)),0,2);
                Pronoun=GetRecoveredDialoguePronoun(Selection);
                bSPHEnabled=Instance->CurrentSave->GetBoolSetting(TEXT("SPHEnabled?"),true);
                bVoiceEnabled=Instance->CurrentSave->GetBoolSetting(TEXT("bVoiceLinesEnabled?"),true);
            }
        }
        if (bVoiceEnabled) {
            if (USoundBase* Voice=SelectRecoveredPaceDialogue(VoicePack.ToString(),Pace,SelectedRandomCard.Tags,Pronoun,bSPHEnabled)) {
                UGameplayStatics::PlaySound2D(this,Voice,GetRecoveredVolume(TEXT("VoicelinesVolume"),0.8f));
            }
        }
    }
    ChangeRecoveredBeatBackground(3);
    PlayRecoveredMusic(Pace);
    OnSessionAction.Broadcast(TEXT("PaceCardStarted"));
    return true;
}

bool ARecoveredGlobalManager::PrepareDrawState() {
    OnSessionAction.Broadcast(TEXT("ClearNotificationBoxes"));
    if(PlayerVariables.bHasCame) {
        OnSessionAction.Broadcast(TEXT("CumOverride"));
        OnSessionAction.Broadcast(TEXT("HideEdgeStreakCounter"));
        LastSessionError=TEXT("Session outcome override is active");
        return false;
    }
    bHasTaunted=false;
    PlayerVariables.bHasTaunted=false;
    if(HeatLevel>=100) {
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::DrawsAtMaxHeat,1);
        OnMetricUpdateRequested.Broadcast(ERecoveredMetric::DrawsAtMaxHeat,1);
    }
    OnSessionAction.Broadcast(TEXT("AddLifetimeDrawAndSave"));
    PlayerVariables.CumMeterMultiplier=1;
    PlayerVariables.CoinEarnMultiplier=1;
    URecoveredSessionRuleLibrary::DetermineDrawMultipliers(CurrentComboTypeEnum,ActiveDifficulty.DifficultyStrokeCounterMultiplier,ActiveDifficulty.DifficultyStrokeSpeedMultiplier,StrokeCountMultiplier,StrokeTimeMultiplier);
    OnSessionAction.Broadcast(TEXT("RemoveAllActiveBeatWidgets"));
    PlayerVariables.bCanUseItems=!BeatContext.ActiveModifiers.Contains(TEXT("Raw Dog"));
    if(MediaDeckState) MediaDeckState->ReplaceEmptyDecks();
    RecentDrawTimestamps.Add(PlayerVariables.SessionLength);
    PlayerVariables.DrawsLast5Sec=URecoveredSessionRuleLibrary::UpdateRecentDrawCount(RecentDrawTimestamps,PlayerVariables.SessionLength);
    if(HeatLevel>=100) {
        PlayerVariables.ConsecutiveHighHeatDraws=URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.ConsecutiveHighHeatDraws,1);
        PlayerVariables.SessionDrawsAtMaxHeat=URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.SessionDrawsAtMaxHeat,1);
        SessionDrawsAtMaxHeat=PlayerVariables.SessionDrawsAtMaxHeat;
    } else PlayerVariables.ConsecutiveHighHeatDraws=0;
    PlayerVariables.TotalDrawCount=URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.TotalDrawCount,1);
    OnSessionAction.Broadcast(TEXT("ClearIdleTimer"));
    BeatContext.HeatCategory=URecoveredEventRuleLibrary::RefreshHeatCategory(HeatLevel,BeatContext.HeatCategory);
    bStopSequence=false;
    return true;
}

void ARecoveredGlobalManager::SetMediaPackEnabled(const FString& PackID, bool bEnabled) {
    MediaPackEnabled.Add(PackID, bEnabled);
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) {
            TArray<FString> Disabled;
            for (const auto& Pair : MediaPackEnabled) {
                if (!Pair.Value) Disabled.Add(Pair.Key);
            }
            if (Instance->CurrentSave->SetStringArraySetting(TEXT("DisabledMediaPacks"), Disabled)) {
                Instance->SaveRecoveredState();
            }
        }
    }
}

bool ARecoveredGlobalManager::IsMediaPackEnabled(const FString& PackID) const {
    const bool* bEnabled = MediaPackEnabled.Find(PackID);
    return bEnabled ? *bEnabled : true; // Default enabled.
}

void ARecoveredGlobalManager::SetMediaPackPriority(const FString& PackID, int32 Priority) {
    MediaPackPriority.Add(PackID, Priority);
}

TArray<FString> ARecoveredGlobalManager::GetEnabledMediaPacks() const {
    TArray<FString> Enabled;
    for (const auto& Pair : MediaPackEnabled) {
        if (Pair.Value) Enabled.Add(Pair.Key);
    }
    // Sort by priority (lower first).
    Enabled.Sort([this](const FString& A, const FString& B) {
        const int32* PA = MediaPackPriority.Find(A);
        const int32* PB = MediaPackPriority.Find(B);
        return (PA ? *PA : 0) < (PB ? *PB : 0);
    });
    return Enabled;
}

void ARecoveredGlobalManager::LaunchCalibrationFlow() {
    APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (!Controller) return;
    UClass* CalibClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_CalibrationUI.WBP_CalibrationUI_C"));
    if (!CalibClass) return;
    if (auto* Calib = CreateWidget<UUserWidget>(Controller, CalibClass)) {
        Calib->AddToViewport(10);
        EventOverlays.Add(Calib);
        OnSessionAction.Broadcast(TEXT("CalibrationLaunched"));
    }
}

void ARecoveredGlobalManager::SetVideoLoopEnabled(bool bEnabled) {
    bVideoLoopEnabled = bEnabled;
    if (MediaPlayback) MediaPlayback->SetLooping(bEnabled);
}

bool ARecoveredGlobalManager::IsVideoLoopEnabled() const {
    return bVideoLoopEnabled;
}
