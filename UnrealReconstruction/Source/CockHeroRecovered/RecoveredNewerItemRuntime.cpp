#include "RecoveredNewerItemEffects.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredRules.h"
#include "RecoveredBeatTimeline.h"
#include "RecoveredSuccuEconomy.h"
#include "RecoveredNativeLoot.h"

namespace {
void RecordNewerItemMetric(ARecoveredGlobalManager& Manager,ERecoveredMetric Metric) {
    URecoveredStateRuleLibrary::RecordSessionMetric(Manager.SessionStats,Metric,1);
    Manager.OnMetricUpdateRequested.Broadcast(Metric,1);
}
bool GrantNewerBountyReward(ARecoveredGlobalManager& Manager) {
    auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(Manager);
    if (!Inventory) return false;
    // Native 0x14830dc20 selects uniformly from eligible hotbar entries, not
    // from the loot table's weights. Table and grant charge caps can differ.
    static constexpr int32 TableCaps[]={0,3,0,3,2,5,15,1,0,3,1,2,2,2};
    TArray<ERecoveredShopItemType> Eligible;
    for (const auto Type:Inventory->HotbarItems) {
        const int32 Index=static_cast<uint8>(Type);
        if (Index>=UE_ARRAY_COUNT(TableCaps) || TableCaps[Index]<=0) continue;
        const int32 Capacity=TableCaps[Index]+(Manager.SuccuEconomy && Manager.SuccuEconomy->HasModifier(13) ? 1 : 0);
        if (Inventory->GetItemState(Type).Charges<Capacity) Eligible.Add(Type);
    }
    if (Eligible.IsEmpty()) {
        Manager.PlayerVariables.PlayerCoins=URecoveredStateRuleLibrary::AddInt32Wrapping(Manager.PlayerVariables.PlayerCoins,75);
        Manager.OnCoinsAdded.Broadcast(75,Manager.PlayerVariables.PlayerCoins);
        return true;
    }
    const auto Type=Eligible[FMath::RandRange(0,Eligible.Num()-1)];
    Manager.AcquireStoreItem(RecoveredNewerInventoryAdapter::ResolveID(Type));
    return true;
}
}

bool ARecoveredGlobalManager::UseRecoveredNewerItem(FName ItemID) {
    auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*this);
    ERecoveredShopItemType Type;
    if (!Inventory || !RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) return false;
    if (RecoveredNativeLoot::IsPanicBlocked(ItemID,HeatLevel,BeatContext.ActiveModifiers)) return false;
    const bool bAllowedDuringSuccubus=BeatContext.CardType==3 && (Type==ERecoveredShopItemType::LootRush || Type==ERecoveredShopItemType::Bounty || Type==ERecoveredShopItemType::EscapeRope || Type==ERecoveredShopItemType::ComboCruncher);
    if (!PlayerVariables.bCanUseItems && !bAllowedDuringSuccubus) return false;
    auto* State=Inventory->OwnedItems.Find(Type);
    if (!State || State->Charges<=0) return false;
    if (!NewerItemEffects) NewerItemEffects=NewObject<URecoveredNewerItemEffects>(this);
    ERecoveredMetric Metric=ERecoveredMetric::ItemsUsed;
    bool bDefensive=false;
    if (Type==ERecoveredShopItemType::LootRush) {
        if (NewerItemEffects->LootRushRemaining>0) return false;
        NewerItemEffects->StartLootRush(State->Level);
        LootBarMultiplier+=NewerItemEffects->LootRushBonus;
        Metric=ERecoveredMetric::LootRushesUsed;
        CreateRecoveredNotification(ItemID,TEXT("Loot Rush Active"),FString::Printf(TEXT("Loot gain +%.0f%% for %.0f seconds"),NewerItemEffects->LootRushBonus*100,NewerItemEffects->LootRushRemaining));
    } else if (Type==ERecoveredShopItemType::Bounty) {
        if (NewerItemEffects->BountyRemaining>0) return false;
        FRandomStream Random(FMath::Rand());
        NewerItemEffects->StartBounty(State->Level,SessionStats.Strokes,Random);
        CreateRecoveredNotification(ItemID,TEXT("Bounty Active"),FString::Printf(TEXT("Complete %d strokes in %.0f seconds"),NewerItemEffects->BountyRequiredStrokes,NewerItemEffects->BountyRemaining));
    } else if (Type==ERecoveredShopItemType::ApexLure) {
        if (!DrawRecoveredSpecialCard(TEXT("SpawnSuccubus"),true)) return false;
        const double ExtraStroking=static_cast<double>(5-FMath::Clamp(State->Level,1,5))*.5;
        if (BeatTimeline) BeatTimeline->ApplyStrokeCountModifier(static_cast<float>(1+ExtraStroking));
    } else if (Type==ERecoveredShopItemType::EscapeRope) {
        if (!BeatTimeline || BeatTimeline->GetBeatsRemaining()<=0 || BeatContext.CardType==5 || BeatContext.CardType==4) return false;
        BeatTimeline->StopSequence();
        CompleteBeatSequence();
        BreakCombo();
        Metric=ERecoveredMetric::EscapeRopesUsed;
        bDefensive=true;
    } else if (Type==ERecoveredShopItemType::ComboCruncher) {
        if (PlayerVariables.CurrentComboCount<=0) return false;
        static constexpr double Retained[]={0,.05,.1,.15,.2};
        const double Progress=static_cast<double>(PlayerVariables.CurrentComboCount)/5000.0;
        AddToCumMeter(Progress);
        PlayerVariables.CurrentComboCount=static_cast<int32>(PlayerVariables.CurrentComboCount*Retained[FMath::Clamp(State->Level-1,0,4)]);
        Metric=ERecoveredMetric::ComboCrunchersUsed;
        bDefensive=true;
    } else return false;
    auto* Consumed=Inventory->OwnedItems.Find(Type);
    if (!Consumed || Consumed->Charges<=0) return false;
    if (!SuccuEconomy || !SuccuEconomy->RollRecycler()) --Consumed->Charges;
    OwnedItemCounts.Add(ItemID,Consumed->Charges);
    RecordNewerItemMetric(*this,ERecoveredMetric::ItemsUsed);
    RecordNewerItemMetric(*this,bDefensive ? ERecoveredMetric::DefensiveItemsUsed : ERecoveredMetric::OffensiveItemsUsed);
    if (Metric!=ERecoveredMetric::ItemsUsed) RecordNewerItemMetric(*this,Metric);
    OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryUsed_%s"),*ItemID.ToString())));
    if (Consumed->Charges==0) OnSessionAction.Broadcast(FName(*FString::Printf(TEXT("InventoryExhausted_%s"),*ItemID.ToString())));
    RecoveredNewerInventoryAdapter::Persist(*this);
    return true;
}

void ARecoveredGlobalManager::TickRecoveredNewerItems(float DeltaSeconds) {
    if (!NewerItemEffects || !FMath::IsFinite(DeltaSeconds) || DeltaSeconds<=0) return;
    const double PreviousBonus=NewerItemEffects->LootRushBonus;
    if (NewerItemEffects->AdvanceLootRush(DeltaSeconds)) {
        LootBarMultiplier=FMath::Max(0.0,LootBarMultiplier-PreviousBonus);
        OnSessionAction.Broadcast(TEXT("LootRushExpired"));
    }
    const int32 Outcome=NewerItemEffects->AdvanceBounty(DeltaSeconds,SessionStats.Strokes);
    if (Outcome>0) {
        RecordNewerItemMetric(*this,ERecoveredMetric::BountiesCollected);
        GrantNewerBountyReward(*this);
        CreateRecoveredNotification(TEXT("Bounty"),TEXT("Bounty Claimed"),TEXT("Reward applied"));
        OnSessionAction.Broadcast(TEXT("BountyClaimed"));
    } else if (Outcome<0) {
        RecordNewerItemMetric(*this,ERecoveredMetric::BountyCollectionFailures);
        CreateRecoveredNotification(TEXT("Bounty"),TEXT("Bounty Failed"),TEXT("Time limit exceeded"));
        OnSessionAction.Broadcast(TEXT("BountyFailed"));
    }
}
