#include "RecoveredNewerInventory.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerInventoryPersistenceTest,"CockHero.Recovery.NewerInventory.Persistence",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerInventoryPersistenceTest::RunTest(const FString& Parameters) {
    using Item=ERecoveredShopItemType;
    auto* Inventory=NewObject<URecoveredNewerInventory>();
    Inventory->UnlockItem(Item::Break);
    Inventory->OwnedItems[Item::Break].Level=5;
    Inventory->OwnedItems[Item::Break].Charges=7;
    Inventory->UnlockItem(static_cast<Item>(99));
    Inventory->OwnedItems[static_cast<Item>(99)].Charges=-2;
    Inventory->HotbarItems={Item::None,Item::Break,static_cast<Item>(99),Item::IncreaseCumMeter};
    const FString Original=Inventory->ExportRecoveryState();
    auto* Restored=NewObject<URecoveredNewerInventory>();
    if (!TestTrue(TEXT("Versioned state reloads"),Restored->ImportRecoveryState(Original))) return false;
    TestEqual(TEXT("All fields survive deterministic round trip"),Restored->ExportRecoveryState(),Original);
    TestEqual(TEXT("Source over-cap charges preserved"),Restored->GetItemState(Item::Break).Charges,7);
    TestEqual(TEXT("Unknown source enum and signed charges preserved"),Restored->GetItemState(static_cast<Item>(99)).Charges,-2);
    const TArray<FString> Invalid={
        TEXT("{}"),
        TEXT("{\"version\":2,\"ownedItems\":[],\"hotbarItems\":[]}"),
        TEXT("{\"version\":1,\"ownedItems\":[],\"hotbarItems\":[256]}"),
        TEXT("{\"version\":1,\"ownedItems\":[],\"hotbarItems\":[-1]}"),
        TEXT("{\"version\":1,\"ownedItems\":[],\"hotbarItems\":[1.5]}"),
        TEXT("{\"version\":1,\"ownedItems\":[{\"type\":4,\"unlocked\":true,\"level\":1,\"charges\":0},{\"type\":4,\"unlocked\":false,\"level\":2,\"charges\":1}],\"hotbarItems\":[]}"),
        TEXT("{\"version\":1,\"ownedItems\":[{\"type\":4,\"unlocked\":true,\"level\":1,\"charges\":2147483648}],\"hotbarItems\":[]}")
    };
    for (const FString& Json:Invalid) {
        TestFalse(TEXT("Malformed state rejected"),Restored->ImportRecoveryState(Json));
        TestEqual(TEXT("Rejected import cannot partially replace inventory"),Restored->ExportRecoveryState(),Original);
    }
    auto* Empty=NewObject<URecoveredNewerInventory>();
    TestTrue(TEXT("Empty baseline-compatible state round trips"),Restored->ImportRecoveryState(Empty->ExportRecoveryState()));
    TestTrue(TEXT("Profile switch clears prior ownership"),Restored->OwnedItems.IsEmpty());
    TestTrue(TEXT("Profile switch clears prior hotbar"),Restored->HotbarItems.IsEmpty());
    return true;
}
#endif
