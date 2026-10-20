#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredRules.h"
#include "RecoveredProgressionResources.h"
#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
const FName ItemIDs[] = {TEXT("XCumChance"),TEXT("DecreaseHeat"),TEXT("Edge"),TEXT("Slowdown"),TEXT("Break"),TEXT("BonerPill"),TEXT("SuccuShield"),TEXT("Resupply"),NAME_None,TEXT("ApexLure"),TEXT("EscapeRope"),TEXT("LootRush"),TEXT("Bounty"),TEXT("ComboCruncher")};
}

bool RecoveredNewerInventoryAdapter::GetPresentation(FName ItemID,int32 Level,FString& Title,FString& Description) {
    static const TSharedPtr<FJsonObject> Data=[]() {
        FString Text;
        TSharedPtr<FJsonObject> Root;
        if (FFileHelper::LoadFileToString(Text,*(FPaths::ProjectContentDir()/TEXT("Recovery/Definitions/newer-20261017-mode-data.json")))) FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root);
        return Root;
    }();
    const TArray<TSharedPtr<FJsonValue>>* Items=nullptr;
    if (!Data || !Data->TryGetArrayField(TEXT("items"),Items)) return false;
    ERecoveredShopItemType Type;
    if (!ResolveType(ItemID,Type)) return false;
    const FString TypeName=StaticEnum<ERecoveredShopItemType>()->GetNameStringByValue(static_cast<int64>(Type));
    for (const auto& Value:*Items) {
        const auto Item=Value->AsObject();
        FString Name;
        if (!Item || !Item->TryGetStringField(TEXT("ItemType"),Name)) continue;
        Name.RemoveFromStart(TEXT("EShopItemType::"));
        if (Name!=TypeName) continue;
        const FString Prefix=FString::Printf(TEXT("Level%dTooltip"),FMath::Clamp(Level,0,4)+1);
        return Item->TryGetStringField(Prefix+TEXT("Title"),Title) && Item->TryGetStringField(Prefix,Description);
    }
    return false;
}

bool RecoveredNewerInventoryAdapter::ResolveType(FName ItemID,ERecoveredShopItemType& Type) {
    if (ItemID.IsNone()) return false;
    if (ItemID==TEXT("IncreaseCumMeter")) ItemID=TEXT("XCumChance");
    for (int32 Index=0;Index<UE_ARRAY_COUNT(ItemIDs);++Index) {
        if (ItemIDs[Index]==ItemID) { Type=static_cast<ERecoveredShopItemType>(Index); return true; }
    }
    return false;
}

FName RecoveredNewerInventoryAdapter::ResolveID(ERecoveredShopItemType Type) {
    const int32 Index=static_cast<uint8>(Type);
    return Index<UE_ARRAY_COUNT(ItemIDs) ? ItemIDs[Index] : NAME_None;
}

URecoveredNewerInventory* RecoveredNewerInventoryAdapter::GetInventory(const ARecoveredGlobalManager& Manager) {
    if (!IsRecoveredNewerProgressionEnabled()) return nullptr;
    auto* Instance=Cast<URecoveredGameInstance>(Manager.GetGameInstance());
    return Instance && Instance->NewerInventory && (!Instance->NewerInventory->OwnedItems.IsEmpty() || !Instance->NewerInventory->HotbarItems.IsEmpty()) ? Instance->NewerInventory.Get() : nullptr;
}

void RecoveredNewerInventoryAdapter::Persist(ARecoveredGlobalManager& Manager) {
    if (auto* Instance=Cast<URecoveredGameInstance>(Manager.GetGameInstance())) Instance->SaveRecoveredState();
}

void RecoveredNewerInventoryAdapter::SynchronizeConsumed(ARecoveredGlobalManager& Manager,FName ItemID) {
    auto* Inventory=GetInventory(Manager);
    ERecoveredShopItemType Type;
    if (!Inventory || !ResolveType(ItemID,Type)) return;
    auto* State=Inventory->OwnedItems.Find(Type);
    if (!State) return;
    const int32* Count=Manager.OwnedItemCounts.Find(ItemID);
    State->Charges=Count ? FMath::Max(0,*Count) : 0;
    Persist(Manager);
}

void RecoveredNewerInventoryAdapter::Initialize(ARecoveredGlobalManager& Manager) {
    auto* Instance=Cast<URecoveredGameInstance>(Manager.GetGameInstance());
    if (!Instance || !Instance->NewerInventory) return;
    auto& Inventory=*Instance->NewerInventory;
    if (Inventory.HotbarItems.IsEmpty()) Inventory.HotbarItems.Init(ERecoveredShopItemType::None,5);
    for (const auto& Entry:Manager.OwnedItemCounts) {
        ERecoveredShopItemType Type;
        if (Entry.Value<=0 || !ResolveType(Entry.Key,Type) || Inventory.OwnedItems.Contains(Type)) continue;
        Inventory.UnlockItem(Type);
        auto& State=Inventory.OwnedItems[Type];
        State.Charges=Entry.Value;
        if (const int32* Level=Manager.ItemUpgradeLevels.Find(Entry.Key)) State.Level=FMath::Clamp(*Level+1,1,5);
    }
}

bool RecoveredNewerInventoryAdapter::GetPricing(FName ItemID,int32 Level,int32& Buy,int32& Upgrade) {
    // DT_ItemInformation recovered from newer-20261017/table-values.json.
    struct FPrice { ERecoveredShopItemType Type; int32 Buy[5]; int32 Upgrade[5]; };
    static constexpr FPrice Prices[]={
        {ERecoveredShopItemType::DecreaseHeat,{100,150,175,200,350},{100,300,500,1250,0}},
        {ERecoveredShopItemType::Slowdown,{75,100,175,200,250},{100,200,500,750,0}},
        {ERecoveredShopItemType::Break,{75,150,300,600,0},{150,200,500,950,0}},
        {ERecoveredShopItemType::BonerPill,{50,100,150,175,200},{150,300,450,750,0}},
        {ERecoveredShopItemType::SuccuShield,{150,125,100,75,50},{100,250,500,750,0}},
        {ERecoveredShopItemType::Resupply,{650,0,0,0,0},{0,0,0,0,0}},
        {ERecoveredShopItemType::ApexLure,{50,75,100,150,200},{200,350,500,800,0}},
        {ERecoveredShopItemType::LootRush,{100,150,200,250,300},{150,250,400,750,0}},
        {ERecoveredShopItemType::Bounty,{100,125,175,200,250},{50,150,300,450,0}},
        {ERecoveredShopItemType::ComboCruncher,{300,300,300,300,300},{75,100,200,400,0}},
        {ERecoveredShopItemType::EscapeRope,{1250,1250,1250,1250,1250},{0,0,0,0,0}}
    };
    ERecoveredShopItemType Type;
    if (!ResolveType(ItemID,Type)) return false;
    for (const auto& Price:Prices) if (Price.Type==Type) {
        const int32 Index=FMath::Clamp(Level,0,4);
        Buy=Price.Buy[Index]; Upgrade=Price.Upgrade[Index]; return true;
    }
    return false;
}
