#include "RecoveredNewerInventory.h"

namespace {
bool SetHotbarSlot(TArray<ERecoveredShopItemType>& Items, int32 SlotIndex, ERecoveredShopItemType Item) {
    if (SlotIndex < 0 || SlotIndex == MAX_int32) return false;
    // Blueprint Array_Set(size-to-fit=true) initializes gaps with the enum's zero,
    // IncreaseCumMeter, rather than EShopItemType::None (8).
    if (SlotIndex >= Items.Num()) Items.SetNum(SlotIndex + 1);
    Items[SlotIndex] = Item;
    return true;
}
}

FRecoveredNewerItemState URecoveredNewerInventory::GetItemState(ERecoveredShopItemType ItemType) const {
    if (const auto* State = OwnedItems.Find(ItemType)) return *State;
    return FRecoveredNewerItemState();
}

bool URecoveredNewerInventory::UnlockItem(ERecoveredShopItemType ItemType) {
    // Source rejects only None and existing keys, not the stored IsUnlocked field.
    if (ItemType == ERecoveredShopItemType::None || OwnedItems.Contains(ItemType)) return false;
    FRecoveredNewerItemState State;
    State.bIsUnlocked = true;
    OwnedItems.Add(ItemType, State);
    return true;
}

bool URecoveredNewerInventory::UpgradeItem(ERecoveredShopItemType ItemType, bool bHotbarWidgetValid, bool& SourceSuccess) {
    auto* State = OwnedItems.Find(ItemType);
    if (ItemType == ERecoveredShopItemType::None || !State || State->Level >= 5) {
        SourceSuccess = false;
        return false;
    }
    ++State->Level;
    if (bHotbarWidgetValid) SourceSuccess = true;
    return true;
}

bool URecoveredNewerInventory::GetMaxCharges(ERecoveredShopItemType ItemType, const FRecoveredNewerChargeContext& Context, int32& MaxCount) {
    int32 Maximum = 0;
    switch (ItemType) {
    case ERecoveredShopItemType::IncreaseCumMeter: Maximum = 1; break;
    case ERecoveredShopItemType::DecreaseHeat:
    case ERecoveredShopItemType::Slowdown:
    case ERecoveredShopItemType::ApexLure: Maximum = 3; break;
    case ERecoveredShopItemType::Break:
        if (Context.GameModeSelection == 2) {
            if (!Context.bGlobalManagerValid) return false;
            Maximum = Context.EffectiveMaxBreakCharges;
        } else Maximum = 2;
        break;
    case ERecoveredShopItemType::BonerPill: Maximum = 5; break;
    case ERecoveredShopItemType::SuccuShield: Maximum = 15; break;
    case ERecoveredShopItemType::Resupply:
    case ERecoveredShopItemType::EscapeRope:
    case ERecoveredShopItemType::ComboCruncher: Maximum = 1; break;
    case ERecoveredShopItemType::LootRush:
    case ERecoveredShopItemType::Bounty: Maximum = 2; break;
    default: return false;
    }
    MaxCount = static_cast<int32>(static_cast<uint32>(Maximum) + (Context.bBiggerPockets ? 1u : 0u));
    return true;
}

bool URecoveredNewerInventory::GrantItem(ERecoveredShopItemType ItemType, int32 Count, const FRecoveredNewerChargeContext& Context) {
    auto* State = OwnedItems.Find(ItemType);
    if (ItemType == ERecoveredShopItemType::None || !State) return false;
    // The generated Blueprint call-site output local begins at zero, including
    // when GetMaxCharges skips assignment (e.g. Edge).
    int32 Maximum = 0;
    GetMaxCharges(ItemType, Context, Maximum);
    if (State->Charges >= Maximum) return false;
    State->Charges = static_cast<int32>(static_cast<uint32>(State->Charges) + static_cast<uint32>(Count));
    return true;
}

bool URecoveredNewerInventory::EquipToSlot(ERecoveredShopItemType ItemType, int32 SlotIndex) {
    if (!OwnedItems.Contains(ItemType)) return false;
    // Deliberately preserve bytecode enum0 clearing (offset380), not None=8.
    for (auto& Item : HotbarItems) if (Item == ItemType) Item = ERecoveredShopItemType::IncreaseCumMeter;
    return SetHotbarSlot(HotbarItems, SlotIndex, ItemType);
}

bool URecoveredNewerInventory::UnEquipSlot(int32 SlotIndex) {
    return SetHotbarSlot(HotbarItems, SlotIndex, ERecoveredShopItemType::IncreaseCumMeter);
}

void URecoveredNewerInventory::ResetHotbar() {
    for (auto& Item : HotbarItems) Item = ERecoveredShopItemType::None;
}

void URecoveredNewerInventory::SetRhythmModeHotbar() {
    ResetHotbar();
    // Source Array_Set(size-to-fit=false) does nothing for an empty array.
    if (!HotbarItems.IsEmpty()) HotbarItems[0] = ERecoveredShopItemType::Break;
}
