#include "RecoveredRules.h"
#include "RecoveredEdgeManager.h"
#include "RecoveredEventRules.h"
#include "RecoveredMenu.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "Engine/World.h"

namespace {
struct FRecoveredBonerPillEffect {
    double StrokeMultiplier;
    double IntervalDivisor;
    double CoinMultiplier;
    float TimelineSpeedMultiplier;
    int32 TimelineStrokeMultiplier;
    const TCHAR* NotificationDescription;
};

const FRecoveredBonerPillEffect GRecoveredBonerPillEffects[] = {
    {2.0,2.0,2.0,2.0f,2,TEXT("X2 Coins | X2 Strokes | X2 Speed")},
    {2.5,2.0,2.0,2.0f,2,TEXT("X2 Coins | X2 Strokes | X2 Speed")},
    {3.0,2.0,2.0,3.0f,3,TEXT("X2 Coins | X3 Strokes | X3 Speed")},
    {3.0,3.0,3.0,5.0f,3,TEXT("X2 Coins | X3 Strokes | X5 Speed")},
    {4.0,5.0,3.0,6.0f,4,TEXT("X3 Coins | X4 Strokes | X6 Speed")},
};

const FRecoveredBonerPillEffect& GetRecoveredBonerPillEffect(int32 UpgradeLevel) {
    return GRecoveredBonerPillEffects[FMath::Clamp(UpgradeLevel,0,UE_ARRAY_COUNT(GRecoveredBonerPillEffects)-1)];
}

int32 GetRecoveredSuccuShieldPurchaseAmount(int32 UpgradeLevel) {
    static constexpr int32 Amounts[]={1,4,7,10,15};
    return Amounts[FMath::Clamp(UpgradeLevel,0,UE_ARRAY_COUNT(Amounts)-1)];
}

FRecoveredEligibilityState BuildRecoveredEligibilityState(const ARecoveredGlobalManager& Manager) {
    FRecoveredEligibilityState State;
    State.HeatCategory=Manager.BeatContext.HeatCategory;
    State.Combo=Manager.PlayerVariables.CurrentComboCount;
    State.Coins=Manager.PlayerVariables.PlayerCoins;
    State.bCanSuccubiSpawn=Manager.PlayerVariables.bCanSuccubiSpawn;
    State.bBrainMelterEnabled=Manager.bBrainMelterEnabled;
    State.bStoreOnCooldown=Manager.bStoreOnCooldown;
    State.Shields=Manager.GetOwnedItemCount(TEXT("SuccuShield"));
    State.bShieldToggled=Manager.bShieldToggled;
    State.Modifiers=Manager.BeatContext.ActiveModifiers;
    return State;
}

void CommitRecoveredSuccuShieldEligibility(ARecoveredGlobalManager& Manager,const FRecoveredEligibilityState& State) {
    Manager.SyncRecoveredSuccuShieldInventory(State.Shields);
    Manager.bShieldToggled=State.bShieldToggled;
    if (State.ShieldsConsumed<=0) return;
    URecoveredStateRuleLibrary::RecordSessionMetric(Manager.SessionStats,ERecoveredMetric::ItemsUsed,State.ShieldsConsumed);
    Manager.OnMetricUpdateRequested.Broadcast(ERecoveredMetric::ItemsUsed,State.ShieldsConsumed);
    Manager.OnSessionAction.Broadcast(TEXT("InventoryUsed_SuccuShield"));
    if (State.Shields<=0) {
        Manager.SpawnRecoveredOverlay(TEXT("NoShieldsLeft_OverlayWidget"));
        Manager.OnSessionAction.Broadcast(TEXT("InventoryExhausted_SuccuShield"));
        Manager.CreateRecoveredNotification(TEXT("SuccuShield"),TEXT("No SuccuShields Left"),TEXT("No Shields Left. Succubi May Appear"));
        return;
    }
    Manager.CreateRecoveredNotification(TEXT("SuccuShield"),TEXT("SuccuShield Active"),TEXT("1 Shield Consumed This Draw"));
}
}

void ARecoveredGlobalManager::HandleRecoveredSessionAction(FName Action) {
    if (Action==TEXT("DetermineCardV2")) RequestNextRecoveredCard(true);
    else if (Action==TEXT("SuccubusCardStarted")) SpawnRecoveredOverlay(TEXT("SuccubusSpawnOverlay_Widget"));
    else if (Action==TEXT("PermissionCardStarted")) SpawnRecoveredOverlay(TEXT("PermissionToCumOverlay_Widget"));
    else if (Action==TEXT("FrenzyCardStarted")) SpawnRecoveredOverlay(BeatContext.CardType==7 ? TEXT("AssFrenzyWidget") : TEXT("BoobFrenzyWidget"));
    else if (Action==TEXT("EdgeCardStarted")) SpawnRecoveredOverlay(TEXT("EdgeOverlay_Widget"));
    else if (Action==TEXT("PostEdgeCardStarted")) SpawnRecoveredOverlay(TEXT("PostEdgeOverlay_Widget"));
    else if (Action==TEXT("PaceCardStarted")) OnSessionAction.Broadcast(TEXT("PlayDrawButtonAnimation"));
    // StoreCardStarted is a completion notification from SpawnRecoveredStore.
    else if (Action==TEXT("CumOverride")) DrawRecoveredSpecialCard(TEXT("CumOverride"), true);
    // Beat-presentation notifications.
    else if (Action==TEXT("DetermineAndPlayMainImageBeatComplete")) PlayMainImageBeatComplete();
    else if (Action==TEXT("DetermineAndPlayComboTypeAnimBeatCompletes")) PlayComboTypeBeatComplete();
    else if (Action==TEXT("DetermineAndPlayHeatGainAnimsOnBeatComplete")) PlayHeatGainBeatComplete();
    else if (Action==TEXT("DetermineBeatCompleteSFX")) PlayBeatCompleteSFX();
    else if (Action==TEXT("BeatCompleteClothesBreaker")) TriggerClothesBreaker();
    else if (Action==TEXT("PlayBrainMelter")) TriggerBrainMelter();
    else if (Action==TEXT("DetermineAndSpawnTaskModifier")) SpawnTaskModifier();
    else if (Action==TEXT("DetermineAndTriggerMeterOverride")) TriggerMeterOverride();
    // Widget/notification lifecycle.
    else if (Action==TEXT("ClearNotificationBoxes")) ClearNotificationBoxes();
    else if (Action==TEXT("RemoveAllActiveBeatWidgets")) RemoveAllActiveBeatWidgets();
    else if (Action==TEXT("SpawnWidget_Onomatopoeia")) SpawnOnomatopoeia();
    else if (Action==TEXT("PlayDrawButtonAnimation")) PlayDrawButtonAnimation();
    else if (Action==TEXT("CreateLootRewardWidget")) CreateLootRewardWidget();
    else if (Action==TEXT("RollAndGiveLootDropsV2")) RollAndGiveLootDrops();
    // Edge-streak presentation.
    else if (Action==TEXT("HideEdgeStreakCounter") || Action==TEXT("ToggleEdgeStreakCounterVisibilityFalse")) SetEdgeStreakCounterVisible(false);
    else if (Action==TEXT("UpdateEdgeStreakProgressBar")) UpdateEdgeStreakProgressBar();
    // Timers and persistence.
    else if (Action==TEXT("ClearIdleTimer")) ClearIdleTimer();
    else if (Action==TEXT("AddLifetimeDrawAndSave")) AddLifetimeDrawAndSave();
    else if (Action==TEXT("AddOneToLifetimeStrokesSave")) AddOneToLifetimeStrokesSave();
    else if (Action==TEXT("SessionFinalized")) OnSessionFinalizedBroadcast();
    // Event families.
    else if (Action==TEXT("MercyEventStarted")) StartMercyEvent();
    else if (Action==TEXT("MercyAccepted")) AcceptMercy();
    else if (Action==TEXT("MercyDeclined")) DeclineMercy();
    else if (Action==TEXT("TemptationEventStarted")) StartTemptationEvent();
    else if (Action==TEXT("TemptationAccepted")) AcceptTemptation();
    else if (Action==TEXT("TemptationDeclined")) DeclineTemptation();
    else if (Action==TEXT("PunishmentEventStarted")) StartPunishmentEvent();
    else if (Action==TEXT("TauntRequested")) ExecuteTaunt();
}
bool ARecoveredGlobalManager::RequestNextRecoveredCard(bool bPlayMedia) {
    LastDispatchedEvent=NAME_None;
    if (!Rules || !MediaDeckState) { LastSessionError=TEXT("Recovered draw rules or media decks are unavailable"); return false; }
    if (PlayerVariables.bHasCame) {
        OnSessionAction.Broadcast(TEXT("ClearNotificationBoxes"));OnSessionAction.Broadcast(TEXT("HideEdgeStreakCounter"));
        LastDispatchedEvent=TEXT("CumOverride");return DrawRecoveredSpecialCard(LastDispatchedEvent,bPlayMedia);
    }
    if (!PrepareDrawState()) return false;
    if (PlayerVariables.bHasEdged || PlayerVariables.bIsAllowedToCum) {
        LastDispatchedEvent=PlayerVariables.bHasEdged ? TEXT("EdgingEventV2") : TEXT("CumEventOverride");
        return DrawRecoveredSpecialCard(LastDispatchedEvent,bPlayMedia);
    }
    if (GetOwnedItemCount(TEXT("SuccuShield"))==0 && SuccubusShields>0) SyncRecoveredSuccuShieldInventory(SuccubusShields);
    FRecoveredEligibilityState State=BuildRecoveredEligibilityState(*this);
    const auto Eligible=URecoveredEventRuleLibrary::BuildEligibleEvents(Rules->EventRecords,State);
    CommitRecoveredSuccuShieldEligibility(*this,State);
    const auto Weighted=URecoveredEventRuleLibrary::ApplyDrawEventWeights(Eligible,State.HeatCategory,CurrentComboTypeEnum);
    const double Total=URecoveredEventRuleLibrary::GetTotalWeight(Weighted);
    const int32 Index=URecoveredEventRuleLibrary::ChooseEventAtRoll(Weighted,UKismetMathLibrary::RandomFloatInRange(0,Total));
    // The source retains its instance FoundEvent when no weight exceeds the roll.
    if (Weighted.IsValidIndex(Index)) FoundEvent=Weighted[Index];
    bool bClearIdle=false;
    LastDispatchedEvent=URecoveredEventRuleLibrary::DetermineDispatchedEvent(static_cast<uint8>(FoundEvent.EventName),State.Modifiers.Contains(TEXT("Succufrenzy")),State.Modifiers.Contains(TEXT("Slow and Steady")),State.Modifiers.Contains(TEXT("Double Time")),UKismetMathLibrary::RandomIntegerInRange(0,1),bClearIdle);
    if (bClearIdle) OnSessionAction.Broadcast(TEXT("ClearIdleTimer"));
    if (LastDispatchedEvent==TEXT("SpawnStoreEvent")) return SpawnRecoveredStore();
    uint8 Pace=255;
    if (LastDispatchedEvent==TEXT("SlowStrokeEvent")) Pace=0;
    else if (LastDispatchedEvent==TEXT("MediumStrokeEvent")) Pace=1;
    else if (LastDispatchedEvent==TEXT("FastStrokeEvent")) Pace=2;
    if (Pace==255) {
        if (!DrawRecoveredSpecialCard(LastDispatchedEvent,bPlayMedia)) return false;
    } else if (!StartPaceCard(Pace,bPlayMedia,false)) return false;
    PlayerVariables.bCanDraw=true;
    OnSessionAction.Broadcast(TEXT("ToggleEdgeStreakCounterVisibilityFalse"));
    OnSessionAction.Broadcast(TEXT("DetermineAndSpawnTaskModifier"));
    return true;
}

void ARecoveredGlobalManager::PlayMainImageBeatComplete() {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave || !Instance->CurrentSave->GetBoolSetting(TEXT("IsScreenShakeEnabled"))) return;
    // Triggers the main image beat-complete animation on the session widget.
    if (IsValid(SessionScreen)) {
        if (auto* Menu = Cast<URecoveredMenuWidget>(SessionScreen)) Menu->PlayRecoveredAnimation(TEXT("BeatCompleteMainImage"));
    }
}

void ARecoveredGlobalManager::PlayComboTypeBeatComplete() {
    if (IsValid(SessionScreen)) {
        const FString AnimName = CurrentComboTypeEnum<=2 ? TEXT("LowComboBeatComplete") : CurrentComboTypeEnum<=4 ? TEXT("MediumComboBeatComplete") : TEXT("HighComboBeatComplete");
        if (auto* Menu = Cast<URecoveredMenuWidget>(SessionScreen)) Menu->PlayRecoveredAnimation(*AnimName);
    }
}

void ARecoveredGlobalManager::PlayHeatGainBeatComplete() {
    if (IsValid(SessionScreen)) {
        const FString AnimName = BeatContext.CardType==0 ? TEXT("AddHeatAnimSlow") : BeatContext.CardType==1 ? TEXT("AddHeatAnimMedium") : TEXT("AddHeatAnimFast");
        if (auto* Menu = Cast<URecoveredMenuWidget>(SessionScreen)) Menu->PlayRecoveredAnimation(*AnimName);
    }
}

void ARecoveredGlobalManager::PlayBeatCompleteSFX() {
    PlayRecoveredSessionSound(TEXT("BeatComplete"));
}

void ARecoveredGlobalManager::TriggerClothesBreaker() {
    SpawnRecoveredOverlay(TEXT("ClothesBreakerOverlay_Widget"));
}

void ARecoveredGlobalManager::TriggerBrainMelter() {
    if (!bBrainMelterEnabled) return;
    SpawnRecoveredOverlay(TEXT("BrainMelterOverlay_Widget"));
    PlayRecoveredSessionSound(TEXT("BrainMelter"));
}

void ARecoveredGlobalManager::ToggleRecoveredBrainMelter() {
    bBrainMelterEnabled=!bBrainMelterEnabled;
    bBrainMelterOverrideEnabled=bBrainMelterEnabled;
    if (UUserWidget* Toggle=SpawnRecoveredOverlay(TEXT("BrainMelterToggleUI_Widget"))) {
        if (UFunction* Function=Toggle->FindFunction(TEXT("PlayBMToggleAnim"))) {
            struct FToggleStatusParameters { bool ToggleStatus; } Parameters{bBrainMelterEnabled};
            Toggle->ProcessEvent(Function,&Parameters);
        }
    }
    OnSessionAction.Broadcast(bBrainMelterEnabled ? TEXT("BrainMelterEnabled") : TEXT("BrainMelterDisabled"));
}

void ARecoveredGlobalManager::AddRecoveredPermanentSuccubusWeight() {
    if (!Rules) return;
    for (FRecoveredEventRecord& Event : Rules->EventRecords) {
        if (Event.EventName==8) Event.BaseWeight+=15.0;
    }
}

void ARecoveredGlobalManager::SpawnTaskModifier() {
    // Selects and presents a task modifier for the current beat.
    if (!Rules) return;
    SpawnRecoveredOverlay(TEXT("TaskModifierWidget"));
}

void ARecoveredGlobalManager::TriggerMeterOverride() {
    if (CumMeterPercentage<1.0) return;
    // Meter-triggered override: forces the override card flow.
    LastDispatchedEvent = TEXT("MeterOverride");
    DrawRecoveredSpecialCard(LastDispatchedEvent, true);
}

void ARecoveredGlobalManager::ClearNotificationBoxes() {
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay) && Overlay->GetName().Contains(TEXT("NotificationBox"))) {
            Overlay->RemoveFromParent();
        }
    }
}

void ARecoveredGlobalManager::RemoveAllActiveBeatWidgets() {
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay) && Overlay->GetName().Contains(TEXT("BeatWidget"))) {
            Overlay->RemoveFromParent();
        }
    }
}

void ARecoveredGlobalManager::SpawnOnomatopoeia() {
    SpawnRecoveredOverlay(TEXT("OnomatopoeiaWidget"));
}

void ARecoveredGlobalManager::PlayDrawButtonAnimation() {
    if (IsValid(SessionScreen)) {
        if (auto* Menu = Cast<URecoveredMenuWidget>(SessionScreen)) Menu->PlayRecoveredAnimation(TEXT("DrawCardAnim"));
    }
}

void ARecoveredGlobalManager::CreateLootRewardWidget() {
    SpawnRecoveredOverlay(TEXT("LootRewardWidget"));
}

void ARecoveredGlobalManager::RollAndGiveLootDrops() {
    // Rolls loot drops and grants them through the reward path.
    if (!Rules) return;
    const int32 Roll = FMath::RandRange(1, 100);
    if (Roll <= 25) {
        GrantPlayerCoins(10);
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::TotalXPEarned, 5);
    }
}

void ARecoveredGlobalManager::SetEdgeStreakCounterVisible(bool bVisible) {
    if (IsValid(SessionScreen)) {
        if (auto* Counter = SessionScreen->GetWidgetFromName(TEXT("EdgeStreakBox"))) {
            Counter->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
        }
    }
}

void ARecoveredGlobalManager::UpdateEdgeStreakProgressBar() {
    if (IsValid(SessionScreen)) {
        if (auto* Bar = Cast<UProgressBar>(SessionScreen->GetWidgetFromName(TEXT("EdgeStreakProgressBar")))) {
            const float Progress = FMath::Clamp(static_cast<float>(SessionStats.EdgeStreak) / 10.0f, 0.0f, 1.0f);
            Bar->SetPercent(Progress);
        }
    }
}

void ARecoveredGlobalManager::ClearIdleTimer() {
    if (UWorld* World=GetWorld()) World->GetTimerManager().ClearTimer(IdleTimer);
}

void ARecoveredGlobalManager::ResetIdleTimer() {
    ClearIdleTimer();
    // 5-minute idle timeout; on expiry, pause the session.
    GetWorldTimerManager().SetTimer(IdleTimer, this, &ARecoveredGlobalManager::OnIdleTimeout, 300.0f, false);
}

void ARecoveredGlobalManager::OnIdleTimeout() {
    if (MediaPlayback) MediaPlayback->SetPaused(true);
    if (BeatTimeline) BeatTimeline->PauseSequence();
    OnSessionAction.Broadcast(TEXT("IdleTimeout"));
}

void ARecoveredGlobalManager::SyncVideoLoopToBeat() {
    // Video-loop event: restarts the video aligned to the beat boundary.
    if (MediaPlayback) {
        MediaPlayback->SetPaused(false);
        OnSessionAction.Broadcast(TEXT("VideoLoopSynced"));
    }
}

void ARecoveredGlobalManager::AddLifetimeDrawAndSave() {
    // Increments lifetime draws and persists.
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave) {
        const int32 Draws = static_cast<int32>(Instance->CurrentSave->GetNumberSetting(TEXT("LifetimeDraws"), 0)) + 1;
        if (Instance->CurrentSave->SetNumberSetting(TEXT("LifetimeDraws"), Draws)) {
            Instance->SaveRecoveredState();
        }
    }
}

void ARecoveredGlobalManager::AddOneToLifetimeStrokesSave() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave) {
        const int32 Strokes = static_cast<int32>(Instance->CurrentSave->GetNumberSetting(TEXT("LifetimeStrokes"), 0)) + 1;
        if (Instance->CurrentSave->SetNumberSetting(TEXT("LifetimeStrokes"), Strokes)) {
            Instance->SaveRecoveredState();
        }
    }
}

void ARecoveredGlobalManager::OnSessionFinalizedBroadcast() {
    // SessionFinalized notification received; finalization already ran.
    // Refresh any live HUD elements here.
}

void ARecoveredGlobalManager::StartMercyEvent() {
    SpawnRecoveredOverlay(TEXT("MercyEventWidget"));
}

void ARecoveredGlobalManager::AcceptMercy() {
    // Mercy accepted: clear the current threat, start cooldown.
    PlayerVariables.bHasEdged = false;
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats, ERecoveredMetric::ItemsUsed, 0);
    GetWorldTimerManager().SetTimer(MercyCooldownTimer, this, &ARecoveredGlobalManager::OnMercyCooldownExpired, 60.0f, false);
}

void ARecoveredGlobalManager::OnMercyCooldownExpired() {
    // Mercy is available again.
}

void ARecoveredGlobalManager::DeclineMercy() {
    // Mercy declined: continue the threat.
    OnSessionAction.Broadcast(TEXT("DetermineCardV2"));
}

void ARecoveredGlobalManager::StartTemptationEvent() {
    SpawnRecoveredOverlay(TEXT("TemptationAcceptOverlay_Widget"));
}

void ARecoveredGlobalManager::AcceptTemptation() {
    // Temptation accepted: grant the reward, apply the cost.
    GrantPlayerCoins(25);
    AddHeat(10.0);
}

void ARecoveredGlobalManager::DeclineTemptation() {
    OnSessionAction.Broadcast(TEXT("DetermineCardV2"));
}

void ARecoveredGlobalManager::StartPunishmentEvent() {
    SpawnRecoveredOverlay(TEXT("PunishmentSpawn_Overlay_Widget"));
    // Punishment: heat penalty and combo reset.
    AddHeat(15.0);
    PlayerVariables.CurrentComboCount = 0;
}

void ARecoveredGlobalManager::ExecuteTaunt() {
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::TimesTaunted,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::TimesTaunted,1);
    bIsTauntOnCooldown=true;
    if (bHasTaunted) return;
    bHasTaunted=true;
    PlayerVariables.bHasTaunted=true;
    if (BeatContext.CardType==3 && BeatTimeline) {
        BeatTimeline->ApplyStrokeCountModifier(4);
        BeatTimeline->ApplySpeedModifier(5.0f);
    }
    ClearIdleTimer();
    AddHeat(25.0);
    if (StartRecoveredTauntCard()) {
        PlayerVariables.TotalTauntsUsed=URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.TotalTauntsUsed,1);
        PlayDialogueLine(TEXT("SpecialEvent_1"));
        ChangeRecoveredBeatBackground(8);
    }
    StartRecoveredTauntCooldown();
    AddToCumMeter(.01);
}

void ARecoveredGlobalManager::StartRecoveredTauntCooldown() {
    bIsTauntOnCooldown=true;
    TauntCooldownTimerDuration=5.0;
    if (UWorld* World=GetWorld()) World->GetTimerManager().SetTimer(TauntCooldownTimer,this,&ARecoveredGlobalManager::OnTauntCooldownExpired,1.0f,true);
}

void ARecoveredGlobalManager::OnTauntCooldownExpired() {
    TauntCooldownTimerDuration=FMath::Max(0.0,TauntCooldownTimerDuration-1.0);
    if (TauntCooldownTimerDuration<=0.0) {
        bIsTauntOnCooldown=false;
        if (UWorld* World=GetWorld()) World->GetTimerManager().ClearTimer(TauntCooldownTimer);
        TauntCooldownTimer.Invalidate();
    }
}

bool ARecoveredGlobalManager::StartRecoveredTauntCard() {
    LastSessionError.Reset();
    if (!Rules || !HeatCategoryDataTable || !MediaDeckState || !BeatTimeline) {
        LastSessionError=TEXT("Taunt card requires recovered rules, timing, media, and beat timeline");
        return false;
    }
    const FRecoveredHeatCategoryRow* Row=HeatCategoryDataTable->FindRow<FRecoveredHeatCategoryRow>(TEXT("HighHeat"),TEXT("Recovered taunt card"));
    if (!Row || Rules->FastBeatPatterns.IsEmpty()) {
        LastSessionError=TEXT("Taunt timing row or pattern bank is unavailable");
        return false;
    }
    MediaDeckState->ReplaceEmptyDecks();
    if (!MediaDeckState->Draw(2,false,SelectedRandomCard)) {
        LastSessionError=TEXT("Taunt media deck is empty");
        return false;
    }
    if (MediaPlayback && !MediaPlayback->OpenEntry(SelectedRandomCard)) {
        LastSessionError=TEXT("Taunt media could not be opened");
        return false;
    }
    const auto Timing=URecoveredCardRuleLibrary::CalculateCardTiming(
        UKismetMathLibrary::RandomIntegerInRange(Row->MinStrokeCount,Row->MaxStrokeCount),
        UKismetMathLibrary::RandomFloatInRange(.18,Row->MaxIntervalSeconds),
        2.0,
        UserStrokeCountMultiplier,
        .75);
    PlayerVariables.BeatSpawnInterval=Timing.BeatInterval;
    const auto Pattern=URecoveredSessionRuleLibrary::CheckIntervalMultipliers(Rules->FastBeatPatterns[UKismetMathLibrary::RandomIntegerInRange(0,Rules->FastBeatPatterns.Num()-1)],BeatTimeline->GetCurrentInterval());
    if (!StartRecoveredBeatSequence(Pattern,Timing.BeatInterval,Timing.StrokeCount,1.0f,BeatTravelTime)) {
        LastSessionError=TEXT("Taunt beat timeline rejected source timing");
        return false;
    }
    BeatContext.CardType=2;
    MediaDeckState->ReplaceEmptyDecks();
    return true;
}

void ARecoveredGlobalManager::GrantPlayerCoins(int32 Amount) {
    if (Amount <= 0) return;
    PlayerVariables.PlayerCoins += Amount;
    PlayerVariables.SessionCoinsEarned += Amount;
}

void ARecoveredGlobalManager::AcquireStoreItem(FName ItemID) {
    int32& Count = OwnedItemCounts.FindOrAdd(ItemID);
    const int32 PreviousCount=Count;
    const int32 Maximum=GetRecoveredItemMaximum(ItemID);
    const int32 AcquiredAmount=ItemID==TEXT("SuccuShield") ? GetRecoveredSuccuShieldPurchaseAmount(GetRecoveredItemUpgradeLevel(ItemID)) : 1;
    Count=Maximum>0 ? FMath::Min(Count+AcquiredAmount,Maximum) : Count+AcquiredAmount;
    if (Count==PreviousCount) return;
    if (ItemID==TEXT("SuccuShield")) SuccubusShields=Count;
    PlayerVariables.bHasItems=true;
    OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryAcquired_%s"),*ItemID.ToString())));
}

bool ARecoveredGlobalManager::UseOwnedItem(FName ItemID, int32 Level) {
    if (ItemID==TEXT("Edge")) return UseRecoveredEdgeItem()==ERecoveredEdgeItemUseResult::Triggered;
    if (ItemID==TEXT("Resupply")) return UseRecoveredResupplyItem()==ERecoveredResupplyItemUseResult::Triggered;
    if (!ItemUpgradeLevels.Contains(ItemID)) SetRecoveredItemUpgradeLevel(ItemID,Level);
    if (ItemID==TEXT("DecreaseHeat")) return UseRecoveredDecreaseHeatItem()==ERecoveredDefensiveItemUseResult::Triggered;
    if (ItemID==TEXT("Break")) return UseRecoveredBreakItem()==ERecoveredDefensiveItemUseResult::Triggered;
    if (ItemID==TEXT("Slowdown")) return UseRecoveredSlowdownItem()==ERecoveredDefensiveItemUseResult::Triggered;
    if (ItemID==TEXT("XCumChance")) return UseRecoveredCumChanceItem()==ERecoveredDefensiveItemUseResult::Triggered;
    if (ItemID==TEXT("BonerPill")) return UseRecoveredBonerPillItem()==ERecoveredDefensiveItemUseResult::Triggered;
    if (ItemID==TEXT("SuccuShield")) return ToggleRecoveredSuccuShields()==ERecoveredDefensiveItemUseResult::Triggered;
    int32* Count = OwnedItemCounts.Find(ItemID);
    if (!Count || *Count <= 0) return false;
    if (!ApplyStoreItemEffect(ItemID, Level)) return false;
    *Count -= 1;
    if (*Count <= 0) OwnedItemCounts.Remove(ItemID);
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryUsed_%s"),*ItemID.ToString())));
    ShowDefensiveItemOverlay(ItemID);
    return true;
}

int32 ARecoveredGlobalManager::GetOwnedItemCount(FName ItemID) const {
    const int32* Count = OwnedItemCounts.Find(ItemID);
    return Count ? *Count : 0;
}

int32 ARecoveredGlobalManager::GetRecoveredItemMaximum(FName ItemID) const {
    if (ItemID==TEXT("XCumChance")) return 1;
    if (ItemID==TEXT("DecreaseHeat")) return 3;
    if (ItemID==TEXT("Edge")) return 10;
    if (ItemID==TEXT("Slowdown")) return 3;
    if (ItemID==TEXT("Break")) return 2;
    if (ItemID==TEXT("BonerPill")) return 5;
    if (ItemID==TEXT("SuccuShield")) return 15;
    return 0;
}

int32 ARecoveredGlobalManager::GetRecoveredItemUpgradeLevel(FName ItemID) const {
    if (const int32* Level=ItemUpgradeLevels.Find(ItemID)) return FMath::Clamp(*Level,0,4);
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return 0;
    return FMath::Clamp(static_cast<int32>(Instance->CurrentSave->GetNumberSetting(TEXT("StoreItemLevel_")+ItemID.ToString(),0)),0,4);
}

void ARecoveredGlobalManager::SetRecoveredItemUpgradeLevel(FName ItemID, int32 Level) {
    const int32 ClampedLevel=FMath::Clamp(Level,0,4);
    ItemUpgradeLevels.Add(ItemID,ClampedLevel);
    if (ItemID==TEXT("Break")) {
        static constexpr double Durations[]={5.0,10.0,15.0,25.0,50.0};
        MasterBreakDuration=Durations[ClampedLevel];
    }
}

namespace {
void RecordRecoveredDefensiveItemUse(ARecoveredGlobalManager& Manager, bool bCountDefensiveUse) {
    if (bCountDefensiveUse) ++Manager.PlayerVariables.TotalDefenseItemUses;
    ++Manager.PlayerVariables.UsedDefensiveItemsInLast2Minutes;
    Manager.PlayerVariables.bHasUsedDefensiveItems=true;
    URecoveredStateRuleLibrary::RecordSessionMetric(Manager.SessionStats,ERecoveredMetric::ItemsUsed,1);
    Manager.OnMetricUpdateRequested.Broadcast(ERecoveredMetric::ItemsUsed,1);
}

void ConsumeRecoveredDefensiveItem(ARecoveredGlobalManager& Manager, FName ItemID, float LastItemDelay, FTimerHandle& LastItemTimer) {
    if (int32* Count=Manager.OwnedItemCounts.Find(ItemID)) {
        --*Count;
        if (*Count<=0) Manager.OwnedItemCounts.Remove(ItemID);
    }
    Manager.PlayerVariables.bHasItems=!Manager.OwnedItemCounts.IsEmpty();
    Manager.OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryUsed_%s"),*ItemID.ToString())));
    if (Manager.GetOwnedItemCount(ItemID)>0) return;
    const FName ExhaustedAction(*FString::Printf(TEXT("InventoryExhausted_%s"),*ItemID.ToString()));
    if (UWorld* World=Manager.GetWorld()) {
        const TWeakObjectPtr<ARecoveredGlobalManager> WeakManager(&Manager);
        World->GetTimerManager().SetTimer(LastItemTimer,FTimerDelegate::CreateLambda([WeakManager,ExhaustedAction]() {
            if (ARecoveredGlobalManager* LiveManager=WeakManager.Get()) LiveManager->OnSessionAction.Broadcast(ExhaustedAction);
        }),LastItemDelay,false);
    } else {
        Manager.OnSessionAction.Broadcast(ExhaustedAction);
    }
}

int32 GetRecoveredHeatReduction(int32 UpgradeLevel) {
    static constexpr int32 Amounts[]={15,25,35,45,60};
    return Amounts[FMath::Clamp(UpgradeLevel,0,UE_ARRAY_COUNT(Amounts)-1)];
}

double GetRecoveredCumChanceGain(int32 UpgradeLevel) {
    static constexpr double Amounts[]={.05,.08,.12,.18,.35};
    return Amounts[FMath::Clamp(UpgradeLevel,0,UE_ARRAY_COUNT(Amounts)-1)];
}
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::UseRecoveredDecreaseHeatItem() {
    const FName ItemID=TEXT("DecreaseHeat");
    PlayDialogueLine(TEXT("Generic_DefensiveItemUse_DLS"));
    if (!PlayerVariables.bCanUseItems) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CannotUseItems;
        return LastDefensiveItemUseResult;
    }
    if (GetOwnedItemCount(ItemID)<=0) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::NoItemAvailable;
        return LastDefensiveItemUseResult;
    }
    ApplyRecoveredAllOrNothingModifierEffects();
    RecordRecoveredDefensiveItemUse(*this,false);
    if (RollRecoveredPunishmentChance()) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::PunishmentTriggered;
        StartPunishmentEvent();
        return LastDefensiveItemUseResult;
    }
    AddToCumMeter(.01);
    OnSessionAction.Broadcast(TEXT("InventoryUseInitiated_DecreaseHeat"));
    SpawnRecoveredOverlay(TEXT("UseDecreaseHeatOverlay_Widget"));
    const int32 HeatReduction=GetRecoveredHeatReduction(GetRecoveredItemUpgradeLevel(ItemID));
    AddHeat(-HeatReduction);
    CreateRecoveredNotification(TEXT("DecreaseHealthBarItem"),TEXT("Heat Reduced"),FString::Printf(TEXT("Heat Decreased by %d"),HeatReduction));
    ConsumeRecoveredDefensiveItem(*this,ItemID,.3f,DecreaseHeatLastItemTimerHandle);
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::UseRecoveredBreakItem() {
    const FName ItemID=TEXT("Break");
    if (!PlayerVariables.bCanUseItems) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CannotUseItems;
        return LastDefensiveItemUseResult;
    }
    if (GetOwnedItemCount(ItemID)<=0) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::NoItemAvailable;
        return LastDefensiveItemUseResult;
    }
    RecordRecoveredDefensiveItemUse(*this,false);
    if (RollRecoveredPunishmentChance()) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::PunishmentTriggered;
        StartPunishmentEvent();
        return LastDefensiveItemUseResult;
    }
    PlayDialogueLine(TEXT("SpecialEvent_12"));
    AddToCumMeter(.01);
    OnSessionAction.Broadcast(TEXT("InventoryUseInitiated_Break"));
    SetRecoveredItemUpgradeLevel(ItemID,GetRecoveredItemUpgradeLevel(ItemID));
    if (BeatTimeline) BeatTimeline->PauseSequence();
    ClearIdleTimer();
    SpawnRecoveredOverlay(TEXT("RestWidget"));
    BreakCombo();
    bStopSequence=true;
    ConsumeRecoveredDefensiveItem(*this,ItemID,.2f,BreakLastItemTimerHandle);
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::UseRecoveredSlowdownItem() {
    const FName ItemID=TEXT("Slowdown");
    if (!PlayerVariables.bCanUseItems) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CannotUseItems;
        return LastDefensiveItemUseResult;
    }
    if (GetOwnedItemCount(ItemID)<=0) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::NoItemAvailable;
        return LastDefensiveItemUseResult;
    }
    if (!bCanUseSlowdown || !bCanUseBonerPill) {
        CreateRecoveredNotification(TEXT("SlowdownItem"),TEXT("Can't Use Slowdown"),TEXT("Can only be used once per task"));
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CooldownActive;
        return LastDefensiveItemUseResult;
    }
    RecordRecoveredDefensiveItemUse(*this,false);
    if (RollRecoveredPunishmentChance()) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::PunishmentTriggered;
        StartPunishmentEvent();
        return LastDefensiveItemUseResult;
    }
    const double Multiplier=static_cast<double>(GetRecoveredItemUpgradeLevel(ItemID)+2);
    bCanUseSlowdown=false;
    PlayDialogueLine(TEXT("SpecialEvent_12"));
    AddToCumMeter(.01);
    OnSessionAction.Broadcast(TEXT("InventoryUseInitiated_Slowdown"));
    SpawnRecoveredOverlay(TEXT("SlowdownItemUseOverlay_Widget"));
    PlayerVariables.BeatSpawnInterval*=Multiplier;
    if (BeatTimeline) BeatTimeline->ApplySpeedModifier(static_cast<float>(1.0/Multiplier));
    PlayerVariables.LastDefensiveItemUsageTime=PlayerVariables.SessionLength;
    if (UWorld* World=GetWorld()) {
        World->GetTimerManager().SetTimer(DefensiveItemUsageTimerHandle,this,&ARecoveredGlobalManager::UpdateRecoveredTimeSinceLastDefenseItem,1.0f,true);
    }
    CreateRecoveredNotification(TEXT("SlowdownItem"),TEXT("Slowdown Applied"),FString::Printf(TEXT("Stroking Slowed by x%d"),static_cast<int32>(Multiplier)));
    ConsumeRecoveredDefensiveItem(*this,ItemID,.3f,SlowdownLastItemTimerHandle);
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::UseRecoveredCumChanceItem() {
    const FName ItemID=TEXT("XCumChance");
    if (!PlayerVariables.bCanUseItems) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CannotUseItems;
        return LastDefensiveItemUseResult;
    }
    if (GetOwnedItemCount(ItemID)<=0) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::NoItemAvailable;
        return LastDefensiveItemUseResult;
    }
    ApplyRecoveredAllOrNothingModifierEffects();
    RecordRecoveredDefensiveItemUse(*this,true);
    if (RollRecoveredPunishmentChance()) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::PunishmentTriggered;
        StartPunishmentEvent();
        return LastDefensiveItemUseResult;
    }
    const double Gain=GetRecoveredCumChanceGain(GetRecoveredItemUpgradeLevel(ItemID));
    PlayerVariables.LastDefensiveItemUsageTime=PlayerVariables.SessionLength;
    AddToCumMeter(Gain);
    OnSessionAction.Broadcast(TEXT("InventoryUseInitiated_XCumChance"));
    SpawnRecoveredOverlay(TEXT("PlusCumChanceOverlay_Widget"));
    CreateRecoveredNotification(TEXT("CumChangeItem"),TEXT("Cum Meter Increased"),FString::Printf(TEXT("+%d%% Cum Meter"),FMath::RoundToInt(Gain*100.0)));
    ConsumeRecoveredDefensiveItem(*this,ItemID,.3f,CumChanceLastItemTimerHandle);
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::UseRecoveredBonerPillItem() {
    const FName ItemID=TEXT("BonerPill");
    if (!PlayerVariables.bCanUseItems) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CannotUseItems;
        return LastDefensiveItemUseResult;
    }
    if (GetOwnedItemCount(ItemID)<=0) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::NoItemAvailable;
        return LastDefensiveItemUseResult;
    }
    if (!bCanUseBonerPill) {
        CreateRecoveredNotification(TEXT("BonerPillItem"),TEXT("Can't Use Boner Pill"),TEXT("Can only be used once per task"));
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CooldownActive;
        return LastDefensiveItemUseResult;
    }

    ApplyRecoveredAllOrNothingModifierEffects();
    RecordRecoveredDefensiveItemUse(*this,true);
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::BonerPillsUsed,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::BonerPillsUsed,1);

    bCanUseBonerPill=false;
    bIsTemptationOnCooldown=true;
    BeatContext.CardType=2;
    PlayDialogueLine(TEXT("SpecialEvent_13"));
    OnSessionAction.Broadcast(TEXT("InventoryUseInitiated_BonerPill"));
    SpawnRecoveredOverlay(TEXT("BonerPillItemUseOverlay_Widget"));
    PlayRecoveredSessionSound(TEXT("BonerPill"));

    const FRecoveredBonerPillEffect& Effect=GetRecoveredBonerPillEffect(GetRecoveredItemUpgradeLevel(ItemID));
    PlayerVariables.CurrentStrokeCount=static_cast<int32>(static_cast<double>(PlayerVariables.CurrentStrokeCount)*Effect.StrokeMultiplier);
    PlayerVariables.BeatSpawnInterval=FMath::Clamp(PlayerVariables.BeatSpawnInterval/Effect.IntervalDivisor,MinimumBeatInterval,1.0);
    PlayerVariables.CoinEarnMultiplier=Effect.CoinMultiplier;
    if (BeatTimeline) {
        BeatTimeline->ApplySpeedModifier(Effect.TimelineSpeedMultiplier);
        BeatTimeline->ApplyStrokeCountModifier(Effect.TimelineStrokeMultiplier);
    }
    CreateRecoveredNotification(TEXT("BonerPillItem"),TEXT("Boner Pill"),Effect.NotificationDescription);
    ChangeRecoveredBeatBackground(9);

    if (int32* Count=OwnedItemCounts.Find(ItemID)) {
        --*Count;
        if (*Count<=0) OwnedItemCounts.Remove(ItemID);
    }
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    OnSessionAction.Broadcast(TEXT("InventoryUsed_BonerPill"));
    if (GetOwnedItemCount(ItemID)<=0) OnSessionAction.Broadcast(TEXT("InventoryExhausted_BonerPill"));

    if (UWorld* World=GetWorld()) World->GetTimerManager().SetTimer(BonerPillCooldownTimerHandle,this,&ARecoveredGlobalManager::CompleteRecoveredBonerPillCooldown,60.0f,false);
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::ToggleRecoveredSuccuShields() {
    const FName ItemID=TEXT("SuccuShield");
    if (!PlayerVariables.bCanUseItems) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CannotUseItems;
        return LastDefensiveItemUseResult;
    }
    if (GetOwnedItemCount(ItemID)==0 && SuccubusShields>0) SyncRecoveredSuccuShieldInventory(SuccubusShields);
    if (GetOwnedItemCount(ItemID)<=0) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::NoItemAvailable;
        return LastDefensiveItemUseResult;
    }
    if (RollRecoveredPunishmentChance()) {
        StartPunishmentEvent();
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::PunishmentTriggered;
        return LastDefensiveItemUseResult;
    }

    bShieldToggled=!bShieldToggled;
    OnSessionAction.Broadcast(bShieldToggled ? TEXT("SuccuShieldToggledOn") : TEXT("SuccuShieldToggledOff"));
    SpawnRecoveredOverlay(bShieldToggled ? TEXT("ShieldOn_OverlayWidget") : TEXT("ShieldOff_OverlayWidget"));
    CreateRecoveredNotification(TEXT("SuccuShield"),bShieldToggled ? TEXT("SuccuShield On") : TEXT("SuccuShield Off"),bShieldToggled ? TEXT("All Succubi Spawns Blocked") : TEXT("Succubus Threat Active"));
    PlayRecoveredSessionSound(TEXT("Click"));
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

bool ARecoveredGlobalManager::CheckRecoveredSuccubusEligibility() {
    if (GetOwnedItemCount(TEXT("SuccuShield"))==0 && SuccubusShields>0) SyncRecoveredSuccuShieldInventory(SuccubusShields);
    FRecoveredEligibilityState State=BuildRecoveredEligibilityState(*this);
    const bool bEligible=URecoveredEventRuleLibrary::CheckSuccubusEligibility(State);
    CommitRecoveredSuccuShieldEligibility(*this,State);
    return bEligible;
}

void ARecoveredGlobalManager::SyncRecoveredSuccuShieldInventory(int32 Count) {
    const int32 SanitizedCount=FMath::Max(0,Count);
    if (SanitizedCount>0) OwnedItemCounts.Add(TEXT("SuccuShield"),SanitizedCount);
    else OwnedItemCounts.Remove(TEXT("SuccuShield"));
    SuccubusShields=SanitizedCount;
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
}

void ARecoveredGlobalManager::ChangeRecoveredBeatBackground(int32 Style) {
    CurrentBeatBackgroundStyle=Style;
    if (Style!=9 || !IsValid(SessionScreen)) return;
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance) Instance->PlayRecoveredBackgroundMedia(TEXT("temptationbackgroundloop"),Cast<UImage>(SessionScreen->GetWidgetFromName(TEXT("BackgroundImage"))));
}

void ARecoveredGlobalManager::CompleteRecoveredBonerPillCooldown() {
    if (GetWorld()) GetWorldTimerManager().ClearTimer(BonerPillCooldownTimerHandle);
    BonerPillCooldownTimerHandle.Invalidate();
    bIsTemptationOnCooldown=false;
}

void ARecoveredGlobalManager::UpdateRecoveredTimeSinceLastDefenseItem() {
    PlayerVariables.TimeSinceLastDefensiveItem=static_cast<double>(PlayerVariables.SessionLength)-PlayerVariables.LastDefensiveItemUsageTime;
}

bool ARecoveredGlobalManager::CanUseRecoveredEdgeItem() const {
    return GetOwnedItemCount(TEXT("Edge"))>0 && (PlayerVariables.bCanUseItems || BeatContext.CardType==5);
}

double ARecoveredGlobalManager::GetRecoveredPunishmentChance() const {
    return static_cast<double>((PlayerVariables.TotalTauntsUsed/5)*20);
}

bool ARecoveredGlobalManager::RollRecoveredPunishmentChance() {
    return FMath::FRandRange(0.0f,100.0f)<=GetRecoveredPunishmentChance();
}

void ARecoveredGlobalManager::TriggerRecoveredEdgeItemPunishment() {
    LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::PunishmentTriggered;
    StartPunishmentEvent();
}

bool ARecoveredGlobalManager::CommitRecoveredEdgeItemUse() {
    int32* Count=OwnedItemCounts.Find(TEXT("Edge"));
    if (!Count || *Count<=0 || !IsValid(EdgingManager) || !EdgingManager->TriggerRecoveredEdgeV2()) {
        LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::EdgeManagerUnavailable;
        return false;
    }
    *Count-=1;
    if (*Count<=0) OwnedItemCounts.Remove(TEXT("Edge"));
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::Triggered;
    OnSessionAction.Broadcast(TEXT("InventoryUsed_Edge"));
    return true;
}

ERecoveredEdgeItemUseResult ARecoveredGlobalManager::UseRecoveredEdgeItem() {
    if (!(PlayerVariables.bCanUseItems || BeatContext.CardType==5)) {
        LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::CannotUseItems;
        return LastEdgeItemUseResult;
    }
    if (GetOwnedItemCount(TEXT("Edge"))<=0) {
        LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::NoEdgesAvailable;
        return LastEdgeItemUseResult;
    }
    if (RollRecoveredPunishmentChance()) {
        TriggerRecoveredEdgeItemPunishment();
        return LastEdgeItemUseResult;
    }
    CommitRecoveredEdgeItemUse();
    return LastEdgeItemUseResult;
}

bool ARecoveredGlobalManager::CanUseRecoveredResupplyItem() const {
    return PlayerVariables.bCanUseItems && GetOwnedItemCount(TEXT("Resupply"))>0;
}

void ARecoveredGlobalManager::ApplyRecoveredAllOrNothingModifierEffects() {
    const bool bActive=BeatContext.ActiveModifiers.ContainsByPredicate([](const FString& Modifier) {
        return Modifier.Equals(TEXT("All or Nothing"),ESearchCase::IgnoreCase);
    });
    if (!bActive) return;
    PlayerVariables.PlayerCoins=0;
    CumMeterPercentage=0.0;
}

bool ARecoveredGlobalManager::IsRecoveredResupplyPending() const {
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(ResupplyStoreTimerHandle);
}

ERecoveredResupplyItemUseResult ARecoveredGlobalManager::UseRecoveredResupplyItem() {
    if (!PlayerVariables.bCanUseItems) {
        LastResupplyItemUseResult=ERecoveredResupplyItemUseResult::CannotUseItems;
        return LastResupplyItemUseResult;
    }
    if (GetOwnedItemCount(TEXT("Resupply"))<=0) {
        LastResupplyItemUseResult=ERecoveredResupplyItemUseResult::NoResupplyAvailable;
        return LastResupplyItemUseResult;
    }
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::ItemsUsed,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::ItemsUsed,1);
    if (RollRecoveredPunishmentChance()) {
        LastResupplyItemUseResult=ERecoveredResupplyItemUseResult::PunishmentTriggered;
        StartPunishmentEvent();
        return LastResupplyItemUseResult;
    }
    ApplyRecoveredAllOrNothingModifierEffects();
    OnSessionAction.Broadcast(TEXT("InventoryUseInitiated_Resupply"));
    SpawnRecoveredOverlay(TEXT("ResupplyItem_OverlayWidget"));
    CreateRecoveredNotification(TEXT("ResupplyItem"),TEXT("Resupply Used"),TEXT("Store Will Open Shortly"));
    if (USoundBase* NotificationSound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/new-notification-020-352772.new-notification-020-352772"))) {
        UGameplayStatics::PlaySound2D(this,NotificationSound);
    }
    LastResupplyItemUseResult=ERecoveredResupplyItemUseResult::Triggered;
    if (GetWorld()) GetWorldTimerManager().SetTimer(ResupplyStoreTimerHandle,this,&ARecoveredGlobalManager::CompleteRecoveredResupplyItemUse,2.0f,false);
    else CompleteRecoveredResupplyItemUse();
    return LastResupplyItemUseResult;
}

void ARecoveredGlobalManager::CompleteRecoveredResupplyItemUse() {
    if (GetWorld()) GetWorldTimerManager().ClearTimer(ResupplyStoreTimerHandle);
    ResupplyStoreTimerHandle.Invalidate();
    SpawnRecoveredStore();
    if (int32* Count=OwnedItemCounts.Find(TEXT("Resupply"))) {
        --*Count;
        if (*Count<=0) OwnedItemCounts.Remove(TEXT("Resupply"));
    }
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    OnSessionAction.Broadcast(TEXT("InventoryUsed_Resupply"));
    if (GetOwnedItemCount(TEXT("Resupply"))>0) return;
    if (GetWorld()) {
        GetWorldTimerManager().SetTimer(ResupplyLastItemTimerHandle,FTimerDelegate::CreateWeakLambda(this,[this]() {
            if (IsValid(this)) OnSessionAction.Broadcast(TEXT("InventoryExhausted_Resupply"));
        }),0.3f,false);
    } else {
        OnSessionAction.Broadcast(TEXT("InventoryExhausted_Resupply"));
    }
}

void ARecoveredGlobalManager::ShowDefensiveItemOverlay(FName ItemID) {
    APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
    if (!Controller) return;
    UClass* OverlayClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_DefensiveItemOverlay.WBP_DefensiveItemOverlay_C"));
    if (!OverlayClass) return;
    if (auto* Overlay = CreateWidget<UUserWidget>(Controller, OverlayClass)) {
        Overlay->AddToViewport(8);
        EventOverlays.Add(Overlay);
        // Bind item name and remaining count.
        if (auto* NameText = Cast<UTextBlock>(Overlay->GetWidgetFromName(TEXT("ItemNameText")))) {
            NameText->SetText(FText::FromName(ItemID));
        }
        if (auto* CountText = Cast<UTextBlock>(Overlay->GetWidgetFromName(TEXT("ItemCountText")))) {
            CountText->SetText(FText::AsNumber(GetOwnedItemCount(ItemID)));
        }
        // Auto-dismiss after 2 seconds.
        FTimerHandle DismissTimer;
        GetWorldTimerManager().SetTimer(DismissTimer, FTimerDelegate::CreateWeakLambda(this, [this, WeakOverlay=TWeakObjectPtr<UUserWidget>(Overlay)]() {
            if (auto* Widget = WeakOverlay.Get()) { Widget->RemoveFromParent(); EventOverlays.Remove(Widget); }
        }), 2.0f, false);
    }
}

void ARecoveredGlobalManager::HandleMediaPlaybackError(const FString& ErrorMessage) {
    LastSessionError = ErrorMessage;
    UE_LOG(LogTemp, Warning, TEXT("Recovered media error: %s"), *ErrorMessage);
    // OpenEntry can fail synchronously. A recursive redraw would exhaust the
    // stack for an unavailable deck; stop and expose the error for an explicit retry.
    if (BeatTimeline) BeatTimeline->PauseSequence();
    if (MediaPlayback) MediaPlayback->SetPaused(true);
}

void ARecoveredGlobalManager::DismissAllOverlays() {
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay)) Overlay->RemoveFromParent();
    }
    EventOverlays.Reset();
}

void ARecoveredGlobalManager::DismissOverlay(UUserWidget* Overlay) {
    if (!IsValid(Overlay)) return;
    Overlay->RemoveFromParent();
    EventOverlays.Remove(Overlay);
}

void ARecoveredGlobalManager::EnqueueNotification(const FString& NotificationText) {
    PendingNotifications.Add(NotificationText);
    OnSessionAction.Broadcast(TEXT("NotificationEnqueued"));
}

bool ARecoveredGlobalManager::DequeueNotification(FString& OutText) {
    if (PendingNotifications.Num() == 0) return false;
    OutText = PendingNotifications[0];
    PendingNotifications.RemoveAt(0);
    return true;
}

int32 ARecoveredGlobalManager::GetPendingNotificationCount() const {
    return PendingNotifications.Num();
}

FString ARecoveredGlobalManager::ExportSessionStatsJson() const {
    // Session-end statistics export for external tooling.
    return FString::Printf(TEXT("{\"strokes\":%d,\"edges\":%d,\"succubi\":%d,\"duration\":%d,\"won\":%s,\"xp\":%d,\"coins_earned\":%d}"),
        SessionStats.Strokes, SessionStats.Edges, SessionStats.SuccubiDefeated,
        SessionStats.SessionDuration, SessionStats.bWon ? TEXT("true") : TEXT("false"),
        CalculateRecoveredSessionXP(), PlayerVariables.SessionCoinsEarned);
}
