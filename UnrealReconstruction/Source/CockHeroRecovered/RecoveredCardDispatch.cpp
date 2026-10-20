#include "RecoveredRules.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredSuccuEconomy.h"
#include "RecoveredMusicUpgrades.h"
#include "RecoveredNativeLoot.h"
#include "RecoveredEdgeManager.h"
#include "RecoveredEventRules.h"
#include "RecoveredEventWidgets.h"
#include "RecoveredMenu.h"
#include "RecoveredPG2TabbedInventoryWidget.h"
#include "RecoveredSessionWidget.h"
#include "RecoveredTabbedInventoryWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
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

struct FRecoveredLootDrop {
    FName ItemID;
    FName IconName;
    const TCHAR* Description;
};

const FRecoveredLootDrop GRecoveredLootDrops[] = {
    {TEXT("DecreaseHeat"),TEXT("DecreaseHealthBarItem"),TEXT("+1 Decrease Heat")},
    {TEXT("XCumChance"),TEXT("CumChangeItem"),TEXT("+1 Cum Meter Increase")},
    {TEXT("Edge"),TEXT("EdgeItem"),TEXT("+1 Edge")},
    {TEXT("Break"),TEXT("BreakItem"),TEXT("+1 Break")},
    {TEXT("BonerPill"),TEXT("BonerPillItem"),TEXT("+1 Boner Pill")},
    {TEXT("Resupply"),TEXT("ResupplyItem"),TEXT("+1 Resupply")},
    {TEXT("Slowdown"),TEXT("SlowdownItem"),TEXT("+1 Slowdown")}
};

void EmitRecoveredLootDebugMessage(const TCHAR* Message) {
    UE_LOG(LogTemp,Display,TEXT("%s"),Message);
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1,2.0f,FLinearColor(0.0f,0.66f,1.0f,1.0f).ToFColor(true),Message);
}

void PresentRecoveredLootReceipt(ARecoveredGlobalManager& Manager,FName ItemID) {
    auto* Screen=Cast<URecoveredSessionWidget>(Manager.SessionScreen);
    if (!Screen) return;
    if (ItemID==TEXT("BonerPill") || ItemID==TEXT("Resupply") || ItemID==TEXT("SuccuShield")) {
        auto* Inventory=Cast<URecoveredPG2TabbedInventoryWidget>(Screen->GetWidgetFromName(TEXT("PG2TabbedInventory_Widget")));
        if (!Inventory) return;
        if (ItemID==TEXT("BonerPill")) Inventory->ReceiveBonerPillItem();
        else if (ItemID==TEXT("SuccuShield")) Inventory->ReceiveSuccuShieldItems();
        else Inventory->ReceiveStoreItem();
        return;
    }
    auto* Inventory=Cast<URecoveredTabbedInventoryWidget>(Screen->GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")));
    if (!Inventory) return;
    if (ItemID==TEXT("DecreaseHeat")) Inventory->ReceiveHeatItem();
    else if (ItemID==TEXT("XCumChance")) Inventory->ReceiveCumChanceItem();
    else if (ItemID==TEXT("Edge")) Inventory->ReceiveEdgeItem();
    else if (ItemID==TEXT("Break")) Inventory->ReceiveBreakItem();
    else if (ItemID==TEXT("Slowdown")) Inventory->ReceiveSlowdownItem();
}

void AwardRecoveredLootDrop(ARecoveredGlobalManager& Manager,const FRecoveredLootDrop& Drop) {
    const int32 Maximum=Manager.GetRecoveredItemMaximum(Drop.ItemID);
    if (Maximum>0 && Manager.GetOwnedItemCount(Drop.ItemID)>=Maximum) {
        Manager.AddCoins(Manager.SuccuEconomy ? Manager.SuccuEconomy->AdjustLootCoinReward(50) : 50);
        Manager.CreateRecoveredNotification(TEXT("CoinRewardIcon"),TEXT("Loot Bar Filled"),TEXT("+50 Coins - Cash Reward Unlocked"));
        return;
    }
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(Manager)) {
        ERecoveredShopItemType Type;
        if (!RecoveredNewerInventoryAdapter::ResolveType(Drop.ItemID,Type) || !Inventory->OwnedItems.Contains(Type)) {
            Manager.AddCoins(Manager.SuccuEconomy ? Manager.SuccuEconomy->AdjustLootCoinReward(50) : 50);
            return;
        }
        Manager.AcquireStoreItem(Drop.ItemID);
    } else ++Manager.OwnedItemCounts.FindOrAdd(Drop.ItemID);
    Manager.PlayerVariables.bHasItems=true;
    PresentRecoveredLootReceipt(Manager,Drop.ItemID);
    Manager.CreateRecoveredNotification(Drop.IconName,TEXT("Loot Bar Filled"),Drop.Description);
}

bool RollRecoveredLootChance(double Chance) {
    return UKismetMathLibrary::RandomFloatInRange(0.0f,100.0f)<=Chance;
}

void GrantRecoveredLegacyLoot(ARecoveredGlobalManager& Manager,FName ItemID,int32 Amount=1) {
    int32& Count=Manager.OwnedItemCounts.FindOrAdd(ItemID);
    Count=URecoveredStateRuleLibrary::AddInt32Wrapping(Count,Amount);
    Manager.PlayerVariables.bHasItems=true;
    PresentRecoveredLootReceipt(Manager,ItemID);
}

int32 GetRecoveredLegacyShieldGrant(int32 UpgradeLevel) {
    static constexpr int32 Amounts[]={10,15,20,25,35};
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
    if (State.ShieldsConsumed>0 && Manager.SuccuEconomy && Manager.SuccuEconomy->HasModifier(14)) {
        ++Manager.SuccuEconomy->ShieldDraws;
        if (Manager.SuccuEconomy->ShieldDraws%2==1) {
            Manager.SyncRecoveredSuccuShieldInventory(State.Shields+State.ShieldsConsumed);
            return;
        }
    }
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
    else if (Action==TEXT("RollAndGiveLootDropsV2")) RollAndGiveLootDropsV2();
    // Edge-streak presentation.
    else if (Action==TEXT("HideEdgeStreakCounter") || Action==TEXT("ToggleEdgeStreakCounterVisibilityFalse")) SetEdgeStreakCounterVisible(false);
    else if (Action==TEXT("UpdateEdgeStreakProgressBar")) UpdateEdgeStreakProgressBar();
    // Timers and persistence.
    else if (Action==TEXT("ClearIdleTimer")) ClearIdleTimer();
    else if (Action==TEXT("AddLifetimeDrawAndSave")) AddLifetimeDrawAndSave();
    else if (Action==TEXT("AddOneToLifetimeStrokesSave")) AddOneToLifetimeStrokesSave();
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
    if (SuccuEconomy && SuccuEconomy->IsSuccubusOnCooldown()) State.bCanSuccubiSpawn=false;
    auto SourceEvents=Rules->EventRecords;
    if (SuccuEconomy && SuccuEconomy->HasModifier(8)) for (auto& Event:SourceEvents) if (Event.EventName==8) Event.BaseWeight*=2;
    const auto Eligible=URecoveredEventRuleLibrary::BuildEligibleEvents(SourceEvents,State);
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
    PlayRecoveredBeatCompleteAudio();
}

void ARecoveredGlobalManager::TriggerClothesBreaker() {
    SpawnRecoveredOverlay(TEXT("ClothesBreakerOverlay_Widget"));
}

void ARecoveredGlobalManager::TriggerBrainMelter() {
    bLastBrainMelterSwapSucceeded=false;
    LastBrainMelterSwapDeck=INDEX_NONE;
    if (!bBrainMelterEnabled || !BeatTimeline || BeatTimeline->GetBeatsRemaining()>1 || !MediaDeckState) return;

    --CurrentBrainMelterSwapInterval;
    if (CurrentBrainMelterSwapInterval>0) return;
    CurrentBrainMelterSwapInterval=MasterBrainMelterSwapInterval;

    int32 Deck=INDEX_NONE;
    switch (BeatContext.CardType) {
        case 0: Deck=0; break;
        case 1: Deck=1; break;
        case 2:
        case 5: Deck=2; break;
        case 3: Deck=3; break;
        case 6: Deck=4; break;
        case 7: Deck=5; break;
        case 8: Deck=6; break;
        default: return;
    }

    if (!MediaDeckState->Draw(static_cast<uint8>(Deck),false,SelectedRandomCard)) return;
    MediaDeckState->ResetDeckFromMasterWhenEmpty(static_cast<uint8>(Deck));
    if (MediaPlayback) {
        MediaPlayback->SetBeatInterval(PlayerVariables.BeatSpawnInterval);
        MediaPlayback->OpenEntry(SelectedRandomCard,BeatTravelTime);
    }
    LastBrainMelterSwapDeck=Deck;
    bLastBrainMelterSwapSucceeded=true;
}

void ARecoveredGlobalManager::BindRecoveredBrainMelterInterval() {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const double SavedInterval=Instance && Instance->CurrentSave
        ? Instance->CurrentSave->GetNumberSetting(TEXT("BrainMelterMediaBeatSwapInterval"),1.0)
        : 1.0;
    MasterBrainMelterSwapInterval=FMath::TruncToInt(SavedInterval);
    CurrentBrainMelterSwapInterval=MasterBrainMelterSwapInterval;
    LastBrainMelterSwapDeck=INDEX_NONE;
    bLastBrainMelterSwapSucceeded=false;
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
    // The source routes all supported objective thresholds through permission
    // and the release window; MeterOverride is not a valid special-card ID.
    TickRecoveredObjectives();
    if (CurrentSessionObjective==0 && !ClassicObjectiveRuntime.bActive && ActiveRecoveredMode==0 && CumMeterPercentage>=1.0) OpenRecoveredReleaseWindow();
}

void ARecoveredGlobalManager::ClearNotificationBoxes() {
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay) && Overlay->GetName().Contains(TEXT("NotificationBox"))) {
            Overlay->RemoveFromParent();
        }
    }
}

void ARecoveredGlobalManager::RemoveAllActiveBeatWidgets() {
    TArray<UUserWidget*> BeatWidgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this,BeatWidgets,URecoveredBeatWidget::StaticClass(),true);
    for (UUserWidget* Widget : BeatWidgets) {
        if (!IsValid(Widget)) continue;
        Widget->StopAllAnimations();
        Widget->RemoveFromParent();
        EventOverlays.Remove(Widget);
    }
    for (int32 Index=EventOverlays.Num()-1;Index>=0;--Index) {
        UUserWidget* Overlay=EventOverlays[Index];
        if (!IsValid(Overlay) || (!Overlay->IsA<URecoveredBeatWidget>() && !Overlay->GetName().Contains(TEXT("BeatWidget")))) continue;
        Overlay->StopAllAnimations();
        Overlay->RemoveFromParent();
        EventOverlays.RemoveAt(Index);
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
    EmitRecoveredLootDebugMessage(TEXT("Loot Drop Added!"));
    if (GetOwnedItemCount(TEXT("XCumChance"))<GetRecoveredItemMaximum(TEXT("XCumChance")) && RollRecoveredLootChance(ActiveDifficulty.CumIncreaseItemSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("XCumChance"));
    if (GetOwnedItemCount(TEXT("DecreaseHeat"))<GetRecoveredItemMaximum(TEXT("DecreaseHeat")) && RollRecoveredLootChance(ActiveDifficulty.DecreaseHeatItemSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("DecreaseHeat"));
    if (GetOwnedItemCount(TEXT("Edge"))<GetRecoveredItemMaximum(TEXT("Edge")) && RollRecoveredLootChance(ActiveDifficulty.EdgeItemSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("Edge"));
    if (GetOwnedItemCount(TEXT("Slowdown"))<GetRecoveredItemMaximum(TEXT("Slowdown")) && RollRecoveredLootChance(ActiveDifficulty.SlowdownItemSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("Break"));
    if (GetOwnedItemCount(TEXT("Break"))<GetRecoveredItemMaximum(TEXT("Break")) && RollRecoveredLootChance(ActiveDifficulty.BreakItemSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("Slowdown"));
    if (GetOwnedItemCount(TEXT("BonerPill"))<GetRecoveredItemMaximum(TEXT("BonerPill")) && RollRecoveredLootChance(ActiveDifficulty.BonerPillSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("BonerPill"));
    if (GetOwnedItemCount(TEXT("SuccuShield"))<GetRecoveredItemMaximum(TEXT("SuccuShield")) && RollRecoveredLootChance(ActiveDifficulty.SuccuShieldSpawnChance)) GrantRecoveredLegacyLoot(*this,TEXT("SuccuShield"),GetRecoveredLegacyShieldGrant(GetRecoveredItemUpgradeLevel(TEXT("SuccuShield"))));
}

void ARecoveredGlobalManager::RollAndGiveLootDropsV2() {
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        const auto Active=[this](const TCHAR* Modifier) { return BeatContext.ActiveModifiers.Contains(Modifier); };
        FRecoveredNativeLootContext Context;
        Context.bBurningProfits=SuccuEconomy && SuccuEconomy->HasModifier(5) && HeatLevel>=100;
        Context.bBiggerPockets=SuccuEconomy && SuccuEconomy->HasModifier(13);
        Context.bPrizeMachine=Active(TEXT("Prize Machine")); Context.bBadRNG=Active(TEXT("Bad RNG"));
        Context.bDrySpell=Active(TEXT("Dry Spell")); Context.bJackpotDrops=Active(TEXT("Jackpot Drops"));
        const auto Reward=RecoveredNativeLoot::Roll(*Inventory,Context,UKismetMathLibrary::RandomFloatInRange(0,100));
        if (Reward.Type==4) AcquireStoreItem(RecoveredNewerInventoryAdapter::ResolveID(Reward.Item));
        else if (Reward.Type==6) {
            const auto Slots=Inventory->HotbarItems;
            for (const auto Item:Slots) if (Item!=ERecoveredShopItemType::None) AcquireStoreItem(RecoveredNewerInventoryAdapter::ResolveID(Item));
            CreateRecoveredNotification(TEXT("LootReward"),TEXT("Jackpot Drop!"),TEXT("A charge for every equipped item"));
        } else {
            if (Active(TEXT("Fap Tax"))) {
                const int32 Tax=FMath::Clamp(FMath::RoundToInt(PlayerVariables.PlayerCoins*.05),0,999999999);
                PlayerVariables.PlayerCoins-=Tax;
            }
            const int32 Coins=SuccuEconomy ? SuccuEconomy->AdjustLootCoinReward(Reward.Amount) : Reward.Amount;
            PlayerVariables.PlayerCoins=URecoveredStateRuleLibrary::AddInt32Wrapping(PlayerVariables.PlayerCoins,Coins);
            OnCoinsAdded.Broadcast(Coins,PlayerVariables.PlayerCoins);
            CreateRecoveredNotification(TEXT("CoinRewardIcon"),TEXT("Loot Bar Filled"),FString::Printf(TEXT("+%d Coins"),Coins));
        }
        RecoveredNewerInventoryAdapter::Persist(*this);
        return;
    }
    // BP_GlobalManager.RollAndGiveLootDropsV2 selects a one-in-six cash
    // reward, otherwise one of seven items. A capped item becomes cash.
    const bool bDoubleDrop=SuccuEconomy && SuccuEconomy->HasModifier(5) && HeatLevel>=SuccuEconomy->GetHeatCap();
    if (!bDoubleDrop && UKismetMathLibrary::RandomIntegerInRange(0,5)==0) {
        AddCoins(SuccuEconomy ? SuccuEconomy->AdjustLootCoinReward(50) : 50);
        EmitRecoveredLootDebugMessage(TEXT("Coins Rewarded!"));
        CreateRecoveredNotification(TEXT("CoinRewardIcon"),TEXT("Loot Bar Filled"),TEXT("+50 Coins - Cash Reward Unlocked"));
        return;
    }
    EmitRecoveredLootDebugMessage(TEXT("Loot Drop Added!"));
    const int32 RewardIndex=UKismetMathLibrary::RandomIntegerInRange(0,UE_ARRAY_COUNT(GRecoveredLootDrops)-1);
    AwardRecoveredLootDrop(*this,GRecoveredLootDrops[RewardIndex]);
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

void ARecoveredGlobalManager::StartMercyEvent() {
    PlayerVariables.bHasEdged=false;
    if (BeatTimeline) BeatTimeline->PauseSequence();
    bStopSequence=true;
    ClearIdleTimer();
    BeatContext.CardType=5;
    LastDispatchedEvent=TEXT("MercyEvent");
    SpawnRecoveredOverlay(TEXT("MercyEventWidget"));
    ChangeRecoveredBeatBackground(2);
}

void ARecoveredGlobalManager::AcceptMercy() {
    HeatLevel=0.0;
    bIsMercyOnCooldown=true;
    SpawnRecoveredMercyBreak();
    GetWorldTimerManager().SetTimer(MercyCooldownTimer,this,&ARecoveredGlobalManager::OnMercyCooldownExpired,static_cast<float>(MercyCooldownDuration),false);
    AddCoins(EdgeBank);
    EdgeBank=0;
}

void ARecoveredGlobalManager::OnMercyCooldownExpired() {
    bIsMercyOnCooldown=false;
}

void ARecoveredGlobalManager::DeclineMercy() {
    ContinueRecoveredEdgeStreak();
}

bool ARecoveredGlobalManager::ContinueRecoveredEdgeStreak() {
    // MercyEvent clears bHasEdged before showing its decision. The original
    // rejection branch therefore calls EdgingEventV2 itself rather than
    // re-entering the general card-selection path.
    LastDispatchedEvent=TEXT("EdgingEventV2");
    return DrawRecoveredSpecialCard(LastDispatchedEvent,true);
}

void ARecoveredGlobalManager::StartTemptationEvent() {
    if (BeatTimeline) BeatTimeline->PauseSequence();
    bIsTemptationOnCooldown=true;
    bStopSequence=true;
    ClearIdleTimer();
    BeatContext.CardType=4;
    LastDispatchedEvent=TEXT("TemptationEvent");
    SpawnRecoveredOverlay(TEXT("TemptationEventWidget"));
    GetWorldTimerManager().SetTimer(TemptationCooldownTimer,this,&ARecoveredGlobalManager::CompleteRecoveredTemptationCooldown,60.0f,false);
    ChangeRecoveredBeatBackground(9);
}

void ARecoveredGlobalManager::AcceptTemptation() {
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::AcceptedTemptation,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::AcceptedTemptation,1);
    HeatLevel=100.0;
    SpawnRecoveredOverlay(TEXT("TemptationAcceptOverlay_Widget"));
    StartPaceCard(2,true,false);
}

void ARecoveredGlobalManager::DeclineTemptation() {
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::DeclinedTemptation,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::DeclinedTemptation,1);
    RequestNextRecoveredCard(true);
}

void ARecoveredGlobalManager::CompleteRecoveredTemptationCooldown() {
    bIsTemptationOnCooldown=false;
}

void ARecoveredGlobalManager::StartPunishmentEvent() {
    SpawnRecoveredOverlay(TEXT("PunishmentSpawn_Overlay_Widget"));
    ClearIdleTimer();
    LastDispatchedEvent=TEXT("SpawnPunishmentEvent");
    DrawRecoveredSpecialCard(LastDispatchedEvent,true);
    if (auto* Menu=Cast<URecoveredMenuWidget>(SessionScreen)) Menu->PlayRecoveredAnimation(TEXT("FastPaceAnim"));
    PlayDialogueLine(TEXT("SpecialEvent_1"));
    ChangeRecoveredBeatBackground(8);
    CreateRecoveredNotification(TEXT("PunishmentIcon"),TEXT("Punishment"),TEXT("Your boasts have consequences."));
    PlayRecoveredMusic(3);
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
    const auto Timing=URecoveredCardRuleLibrary::CalculateCardTiming(
        UKismetMathLibrary::RandomIntegerInRange(Row->MinStrokeCount,Row->MaxStrokeCount),
        UKismetMathLibrary::RandomFloatInRange(.18,Row->MaxIntervalSeconds),
        2.0,
        UserStrokeCountMultiplier,
        .75);
    PlayerVariables.BeatSpawnInterval=Timing.BeatInterval;
    if (MediaPlayback) {
        MediaPlayback->SetBeatInterval(Timing.BeatInterval);
        if (!MediaPlayback->OpenEntry(SelectedRandomCard,BeatTravelTime)) {
            LastSessionError=TEXT("Taunt media could not be opened");
            return false;
        }
    }
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
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        ERecoveredShopItemType Type;
        if (!RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) return;
        FRecoveredNewerChargeContext Context;
        Context.bBiggerPockets=SuccuEconomy && SuccuEconomy->HasModifier(13);
        if (ActiveRecoveredMode==2) {
            Context.GameModeSelection=2;
            Context.bGlobalManagerValid=true;
            const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
            Context.EffectiveMaxBreakCharges=static_cast<int32>(RecoveredMusicUpgrades::GetValue(Instance ? Instance->CurrentSave.Get() : nullptr,1));
        }
        const int32 Previous=Inventory->GetItemState(Type).Charges;
        if (!Inventory->GrantItem(Type,1,Context)) return;
        const int32 Count=Inventory->GetItemState(Type).Charges;
        OwnedItemCounts.Add(ItemID,Count);
        if (ItemID==TEXT("SuccuShield")) SuccubusShields=Count;
        PlayerVariables.bHasItems=true;
        if (Count!=Previous) OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryAcquired_%s"),*ItemID.ToString())));
        RecoveredNewerInventoryAdapter::Persist(*this);
        return;
    }
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
    if (RecoveredNewerInventoryAdapter::GetInventory(*this) && RecoveredNativeLoot::IsPanicBlocked(ItemID,HeatLevel,BeatContext.ActiveModifiers)) return false;
    if (ItemID==TEXT("ApexLure") || ItemID==TEXT("EscapeRope") || ItemID==TEXT("LootRush") || ItemID==TEXT("Bounty") || ItemID==TEXT("ComboCruncher")) return UseRecoveredNewerItem(ItemID);
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        ERecoveredShopItemType Type;
        if (!RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type) || !Inventory->OwnedItems.Contains(Type)) return false;
        const auto State=Inventory->GetItemState(Type);
        OwnedItemCounts.Add(ItemID,State.Charges);
        ItemUpgradeLevels.Add(ItemID,FMath::Clamp(State.Level-1,0,4));
    }
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
    RecoveredNewerInventoryAdapter::SynchronizeConsumed(*this,ItemID);
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryUsed_%s"),*ItemID.ToString())));
    ShowDefensiveItemOverlay(ItemID);
    return true;
}

int32 ARecoveredGlobalManager::GetOwnedItemCount(FName ItemID) const {
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        ERecoveredShopItemType Type;
        if (RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) return Inventory->GetItemState(Type).Charges;
    }
    const int32* Count = OwnedItemCounts.Find(ItemID);
    return Count ? *Count : 0;
}

int32 ARecoveredGlobalManager::GetRecoveredItemMaximum(FName ItemID) const {
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        ERecoveredShopItemType Type;
        FRecoveredNewerChargeContext Context;
        Context.bBiggerPockets=SuccuEconomy && SuccuEconomy->HasModifier(13);
        if (ActiveRecoveredMode==2) {
            Context.GameModeSelection=2;
            Context.bGlobalManagerValid=true;
            const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
            Context.EffectiveMaxBreakCharges=static_cast<int32>(RecoveredMusicUpgrades::GetValue(Instance ? Instance->CurrentSave.Get() : nullptr,1));
        }
        int32 Maximum=0;
        if (RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type) && URecoveredNewerInventory::GetMaxCharges(Type,Context,Maximum)) return Maximum;
    }
    if (ItemID==TEXT("XCumChance")) return 1;
    if (ItemID==TEXT("DecreaseHeat")) return 3;
    if (ItemID==TEXT("Edge")) return 10;
    if (ItemID==TEXT("Slowdown")) return 3;
    if (ItemID==TEXT("Break")) return 2;
    if (ItemID==TEXT("BonerPill")) return 5;
    if (ItemID==TEXT("Resupply")) return 1;
    if (ItemID==TEXT("SuccuShield")) return 15;
    return 0;
}

int32 ARecoveredGlobalManager::GetRecoveredItemUpgradeLevel(FName ItemID) const {
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        ERecoveredShopItemType Type;
        if (RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) return FMath::Clamp(Inventory->GetItemState(Type).Level-1,0,4);
    }
    if (const int32* Level=ItemUpgradeLevels.Find(ItemID)) return FMath::Clamp(*Level,0,4);
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return 0;
    return FMath::Clamp(static_cast<int32>(Instance->CurrentSave->GetNumberSetting(TEXT("StoreItemLevel_")+ItemID.ToString(),0)),0,4);
}

void ARecoveredGlobalManager::SetRecoveredItemUpgradeLevel(FName ItemID, int32 Level) {
    const int32 ClampedLevel=FMath::Clamp(Level,0,4);
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this)) {
        ERecoveredShopItemType Type;
        if (RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) {
            if (auto* State=Inventory->OwnedItems.Find(Type)) State->Level=ClampedLevel+1;
        }
    }
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
    const int32 PreviousCount=Manager.GetOwnedItemCount(ItemID);
    if (RecoveredNewerInventoryAdapter::GetInventory(Manager)) Manager.OwnedItemCounts.Add(ItemID,PreviousCount);
    if (int32* Count=Manager.OwnedItemCounts.Find(ItemID)) {
        if (!Manager.SuccuEconomy || !Manager.SuccuEconomy->RollRecycler()) --*Count;
        if (*Count<=0) Manager.OwnedItemCounts.Remove(ItemID);
    }
    Manager.PlayerVariables.bHasItems=!Manager.OwnedItemCounts.IsEmpty();
    RecoveredNewerInventoryAdapter::SynchronizeConsumed(Manager,ItemID);
    URecoveredStateRuleLibrary::RecordSessionMetric(Manager.SessionStats,ERecoveredMetric::DefensiveItemsUsed,1);
    Manager.OnMetricUpdateRequested.Broadcast(ERecoveredMetric::DefensiveItemsUsed,1);
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
    if (!PlayerVariables.bCanUseItems || (RecoveredNewerInventoryAdapter::GetInventory(*this) && RecoveredNativeLoot::IsPanicBlocked(ItemID,HeatLevel,BeatContext.ActiveModifiers))) {
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
        // The heat-item failure path applies its own fifteen-point penalty
        // before it routes into the shared punishment-card presentation.
        // SpawnPunishmentEvent itself does not alter heat.
        AddHeat(15.0);
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
    if (ActiveRecoveredMode==2 && (!PlaylistRuntime || !PlaylistRuntime->bPlaying || PlaylistRuntime->bPaused || PlaylistRuntime->bOnBreak)) {
        LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CooldownActive;
        return LastDefensiveItemUseResult;
    }
    if (!PlayerVariables.bCanUseItems || (RecoveredNewerInventoryAdapter::GetInventory(*this) && RecoveredNativeLoot::IsPanicBlocked(ItemID,HeatLevel,BeatContext.ActiveModifiers))) {
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
    if (ActiveRecoveredMode==2) {
        if (!PlaylistRuntime->BeginBreak()) { LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::CooldownActive;return LastDefensiveItemUseResult; }
        URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::MusicBreaksUsed,1);
        OnMetricUpdateRequested.Broadcast(ERecoveredMetric::MusicBreaksUsed,1);
        RemoveAllActiveBeatWidgets();
    }
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
    if (!PlayerVariables.bCanUseItems || (RecoveredNewerInventoryAdapter::GetInventory(*this) && RecoveredNativeLoot::IsPanicBlocked(ItemID,HeatLevel,BeatContext.ActiveModifiers))) {
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

    if (RecoveredNewerInventoryAdapter::GetInventory(*this)) OwnedItemCounts.Add(ItemID,GetOwnedItemCount(ItemID));
    if (int32* Count=OwnedItemCounts.Find(ItemID)) {
        if (!SuccuEconomy || !SuccuEconomy->RollRecycler()) --*Count;
        if (*Count<=0) OwnedItemCounts.Remove(ItemID);
    }
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    OnSessionAction.Broadcast(TEXT("InventoryUsed_BonerPill"));
    RecoveredNewerInventoryAdapter::SynchronizeConsumed(*this,ItemID);
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::OffensiveItemsUsed,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::OffensiveItemsUsed,1);
    if (GetOwnedItemCount(ItemID)<=0) OnSessionAction.Broadcast(TEXT("InventoryExhausted_BonerPill"));

    if (UWorld* World=GetWorld()) World->GetTimerManager().SetTimer(BonerPillCooldownTimerHandle,this,&ARecoveredGlobalManager::CompleteRecoveredBonerPillCooldown,60.0f,false);
    LastDefensiveItemUseResult=ERecoveredDefensiveItemUseResult::Triggered;
    return LastDefensiveItemUseResult;
}

ERecoveredDefensiveItemUseResult ARecoveredGlobalManager::ToggleRecoveredSuccuShields() {
    const FName ItemID=TEXT("SuccuShield");
    if (!PlayerVariables.bCanUseItems || (RecoveredNewerInventoryAdapter::GetInventory(*this) && RecoveredNativeLoot::IsPanicBlocked(ItemID,HeatLevel,BeatContext.ActiveModifiers))) {
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
    if (SuccuEconomy && SuccuEconomy->IsSuccubusOnCooldown()) return false;
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
    RecoveredNewerInventoryAdapter::SynchronizeConsumed(*this,TEXT("SuccuShield"));
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
}

void ARecoveredGlobalManager::ChangeRecoveredBeatBackground(int32 Style) {
    CurrentBeatBackgroundStyle=Style;
    if (!IsValid(SessionScreen)) return;
    const TCHAR* MediaName=nullptr;
    switch (Style) {
    case 0: MediaName=TEXT("backgroundmenuloop"); break;
    case 1: MediaName=TEXT("decisionbackgroundloop"); break;
    case 2: MediaName=TEXT("mercybackgroundloop"); break;
    case 3: MediaName=TEXT("normalbeatbackgroundloop"); break;
    case 4: MediaName=TEXT("prematurecumbackgroundloop"); break;
    case 5: MediaName=TEXT("successfulcumbackgroundloop"); break;
    case 6: MediaName=TEXT("succubusbackgroundloop"); break;
    case 7: MediaName=TEXT("succubuscumbackgroundloop"); break;
    case 8: MediaName=TEXT("tauntbackgroundloop"); break;
    case 9: MediaName=TEXT("temptationbackgroundloop"); break;
    default: return;
    }
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance) Instance->PlayRecoveredBackgroundMedia(MediaName,Cast<UImage>(SessionScreen->GetWidgetFromName(TEXT("BackgroundImage"))));
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
    if (RecoveredNewerInventoryAdapter::GetInventory(*this)) OwnedItemCounts.Add(TEXT("Edge"),GetOwnedItemCount(TEXT("Edge")));
    int32* Count=OwnedItemCounts.Find(TEXT("Edge"));
    if (!Count || *Count<=0 || !IsValid(EdgingManager) || !EdgingManager->TriggerRecoveredEdgeV2()) {
        LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::EdgeManagerUnavailable;
        return false;
    }
    if (!SuccuEconomy || !SuccuEconomy->RollRecycler()) *Count-=1;
    if (*Count<=0) OwnedItemCounts.Remove(TEXT("Edge"));
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    LastEdgeItemUseResult=ERecoveredEdgeItemUseResult::Triggered;
    RecoveredNewerInventoryAdapter::SynchronizeConsumed(*this,TEXT("Edge"));
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::DefensiveItemsUsed,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::DefensiveItemsUsed,1);
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
    if (!PlayerVariables.bCanUseItems || (RecoveredNewerInventoryAdapter::GetInventory(*this) && RecoveredNativeLoot::IsPanicBlocked(TEXT("Resupply"),HeatLevel,BeatContext.ActiveModifiers))) {
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
    if (RecoveredNewerInventoryAdapter::GetInventory(*this)) OwnedItemCounts.Add(TEXT("Resupply"),GetOwnedItemCount(TEXT("Resupply")));
    if (int32* Count=OwnedItemCounts.Find(TEXT("Resupply"))) {
        if (!SuccuEconomy || !SuccuEconomy->RollRecycler()) --*Count;
        if (*Count<=0) OwnedItemCounts.Remove(TEXT("Resupply"));
    }
    PlayerVariables.bHasItems=!OwnedItemCounts.IsEmpty();
    OnSessionAction.Broadcast(TEXT("InventoryUsed_Resupply"));
    RecoveredNewerInventoryAdapter::SynchronizeConsumed(*this,TEXT("Resupply"));
    URecoveredStateRuleLibrary::RecordSessionMetric(SessionStats,ERecoveredMetric::OffensiveItemsUsed,1);
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::OffensiveItemsUsed,1);
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
