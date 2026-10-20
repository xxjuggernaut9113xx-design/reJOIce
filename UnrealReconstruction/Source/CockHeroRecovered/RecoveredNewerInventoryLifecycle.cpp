#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredRules.h"
#include "RecoveredSuccuEconomy.h"

namespace {
bool IsSourceLoadoutType(int32 Type) {
    return Type==1||Type==3||Type==4||Type==5||Type==6||Type==7||Type==8||Type==9||Type==10||Type==11||Type==12||Type==13;
}
}

void RecoveredNewerInventoryAdapter::RestoreClassicHotbar(URecoveredNewerInventory& Inventory, const URecoveredSaveGame* Save) {
    if (!Save) return;
    const auto Saved=Save->GetIntArraySetting(TEXT("LastSavedHotBarItems"));
    Inventory.HotbarItems.Init(ERecoveredShopItemType::None,5);
    for (int32 Index=0;Index<FMath::Min(5,Saved.Num());++Index)
        if (IsSourceLoadoutType(Saved[Index])) Inventory.HotbarItems[Index]=static_cast<ERecoveredShopItemType>(Saved[Index]);
}

bool RecoveredNewerInventoryAdapter::SaveClassicHotbar(const URecoveredNewerInventory& Inventory, URecoveredSaveGame* Save) {
    if (!Save) return false;
    TArray<int32> Slots;
    for (int32 Index=0;Index<5;++Index) {
        const int32 Type=Inventory.HotbarItems.IsValidIndex(Index)?static_cast<int32>(Inventory.HotbarItems[Index]):8;
        Slots.Add(IsSourceLoadoutType(Type)?Type:8);
    }
    return Save->SetIntArraySetting(TEXT("LastSavedHotBarItems"),Slots);
}

void RecoveredNewerInventoryAdapter::PrepareFreshLoadout(URecoveredNewerInventory& Inventory, uint8 Mode, FRandomStream& Random) {
    // DT_ItemInformation row order and ItemClass, retained in the source table.
    using Item=ERecoveredShopItemType;
    const uint8 SourceRows[]={1,3,4,5,6,7,9,11,12,13,10};
    // Source game-instance defaults provide five None entries. This integration
    // helper also supports a newly constructed temporary chooser inventory.
    Inventory.HotbarItems.Init(Item::None,5);
    Inventory.ResetHotbar();
    Inventory.OwnedItems.Reset();
    if (Mode==0) {
        for (const uint8 Type:SourceRows) Inventory.UnlockItem(static_cast<Item>(Type));
    } else if (Mode==1) {
        TArray<uint8> Candidates;
        for (const uint8 Type:SourceRows) if (Type!=7) Candidates.Add(Type);
        // Kismet Array_Shuffle uses an ascending Fisher-Yates shuffle.
        for (int32 Index=0;Index<Candidates.Num()-1;++Index) Candidates.Swap(Index,Random.RandRange(Index,Candidates.Num()-1));
        for (int32 Classification=0;Classification<2;++Classification)
            for (const uint8 Type:Candidates) {
                const bool Offensive=Type==5||Type==9||Type==11||Type==12;
                if (Offensive!=(Classification==1)) continue;
                Inventory.UnlockItem(static_cast<Item>(Type));
                break;
            }
    } else if (Mode==2) {
        SetupMusicHotbar(Inventory);
    }
}

void RecoveredNewerInventoryAdapter::ResetItemStates(URecoveredNewerInventory& Inventory) {
    // BP_CHGameInstance.ResetItemStates preserves map keys and HotBarItems.
    for (auto& Entry:Inventory.OwnedItems) Entry.Value=FRecoveredNewerItemState();
}

void RecoveredNewerInventoryAdapter::PopulateOwnedItemsFromHotbar(URecoveredNewerInventory& Inventory) {
    // Source uses UnlockItem, including its existing-key rejection semantics.
    for (const auto Item:Inventory.HotbarItems) Inventory.UnlockItem(Item);
}

TMap<ERecoveredShopItemType,FRecoveredNewerItemState> RecoveredNewerInventoryAdapter::MakeNativeTowerInventory(const URecoveredNewerInventory& Inventory) {
    // StartRoundSession 0x148314ce0 copies incoming owned states before this
    // normalization. Do not mutate the caller's setup inventory here.
    auto Result=Inventory.OwnedItems;
    for (auto& Entry:Result) {
        Entry.Value.bIsUnlocked=true;
        Entry.Value.Level=FMath::Max(1,Entry.Value.Level);
    }
    return Result;
}

void RecoveredNewerInventoryAdapter::ResetForFreshRun(ARecoveredGlobalManager& Manager) {
    if (auto* Inventory=GetInventory(Manager)) ResetItemStates(*Inventory);
    Manager.PlayerVariables.PlayerCoins=0;
    Manager.OwnedItemCounts.Reset();
    Manager.ItemUpgradeLevels.Reset();
    Manager.SuccubusShields=0;
    Manager.bShieldToggled=false;
    Manager.PlayerVariables.bHasItems=false;
    if (Manager.SuccuEconomy) Manager.SuccuEconomy->ResetRun();
}

void RecoveredNewerInventoryAdapter::SetupMusicHotbar(URecoveredNewerInventory& Inventory) {
    Inventory.SetRhythmModeHotbar();
    PopulateOwnedItemsFromHotbar(Inventory);
}
