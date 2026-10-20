#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredMusicUpgrades.h"
#include "RecoveredRules.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerInventoryLifecycleTest,"CockHero.Recovery.NewerInventory.FreshRunLifecycle",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerInventoryLifecycleTest::RunTest(const FString& Parameters) {
    using Item=ERecoveredShopItemType;
    auto* Inventory=NewObject<URecoveredNewerInventory>();
    Inventory->UnlockItem(Item::Slowdown);
    Inventory->OwnedItems[Item::Slowdown].Level=5;
    Inventory->OwnedItems[Item::Slowdown].Charges=3;
    Inventory->HotbarItems={Item::Slowdown,Item::None,Item::None,Item::None,Item::None};
    const auto Slots=Inventory->HotbarItems;
    const FString SavedCheckpoint=Inventory->ExportRecoveryState();
    RecoveredNewerInventoryAdapter::ResetItemStates(*Inventory);
    TestEqual(TEXT("Fresh reset preserves owned map keys"),Inventory->OwnedItems.Num(),1);
    TestTrue(TEXT("Fresh reset preserves hotbar"),Inventory->HotbarItems==Slots);
    const auto Reset=Inventory->GetItemState(Item::Slowdown);
    TestFalse(TEXT("Fresh reset locks prior run item"),Reset.bIsUnlocked);
    TestEqual(TEXT("Fresh reset level is one"),Reset.Level,1);
    TestEqual(TEXT("Fresh reset charge is zero"),Reset.Charges,0);
    RecoveredNewerInventoryAdapter::PopulateOwnedItemsFromHotbar(*Inventory);
    TestFalse(TEXT("Populate preserves source existing-key no-op"),Inventory->GetItemState(Item::Slowdown).bIsUnlocked);
    auto Normalized=RecoveredNewerInventoryAdapter::MakeNativeTowerInventory(*Inventory);
    TestTrue(TEXT("Native Tower copy unlocks incoming key"),Normalized[Item::Slowdown].bIsUnlocked);
    TestFalse(TEXT("Native Tower copy does not mutate caller setup"),Inventory->GetItemState(Item::Slowdown).bIsUnlocked);
    Inventory->OwnedItems=MoveTemp(Normalized);
    Inventory->OwnedItems[Item::Slowdown].Level=4;
    Inventory->OwnedItems[Item::Slowdown].Charges=2;
    const auto RoundCopy=RecoveredNewerInventoryAdapter::MakeNativeTowerInventory(*Inventory);
    TestEqual(TEXT("Within-run normalization preserves upgrade"),RoundCopy[Item::Slowdown].Level,4);
    TestEqual(TEXT("Within-run normalization preserves charges"),RoundCopy[Item::Slowdown].Charges,2);
    RecoveredNewerInventoryAdapter::SetupMusicHotbar(*Inventory);
    TestEqual(TEXT("Music hotbar installs only source Break"),Inventory->HotbarItems[0],Item::Break);
    TestEqual(TEXT("Music remaining slots cleared"),Inventory->HotbarItems[1],Item::None);
    TestTrue(TEXT("Hotbar population creates absent Break ownership"),Inventory->GetItemState(Item::Break).bIsUnlocked);
    FRecoveredNewerChargeContext Context;
    Context.GameModeSelection=2; Context.bGlobalManagerValid=true;
    Context.EffectiveMaxBreakCharges=static_cast<int32>(RecoveredMusicUpgrades::GetValue(nullptr,1));
    int32 Maximum=0;
    TestTrue(TEXT("Music charge cap resolves through upgrade system"),URecoveredNewerInventory::GetMaxCharges(Item::Break,Context,Maximum));
    TestEqual(TEXT("Source default music max is one"),Maximum,1);
    Context.bBiggerPockets=true;
    URecoveredNewerInventory::GetMaxCharges(Item::Break,Context,Maximum);
    TestEqual(TEXT("Music cap composes with Bigger Pockets"),Maximum,2);
    auto* Restored=NewObject<URecoveredNewerInventory>();
    TestTrue(TEXT("Pre-reset recovery checkpoint remains independently readable"),Restored->ImportRecoveryState(SavedCheckpoint));
    TestEqual(TEXT("Migration checkpoint retains old run level"),Restored->GetItemState(Item::Slowdown).Level,5);
    FRandomStream Random(90210);
    auto* FreshChooser=NewObject<URecoveredNewerInventory>();
    RecoveredNewerInventoryAdapter::PrepareFreshLoadout(*FreshChooser,1,Random);
    TestEqual(TEXT("Temporary chooser receives source game-instance five-slot defaults"),FreshChooser->HotbarItems.Num(),5);
    Inventory->OwnedItems.Add(Item::Edge,FRecoveredNewerItemState());
    RecoveredNewerInventoryAdapter::PrepareFreshLoadout(*Inventory,0,Random);
    TestEqual(TEXT("Classic fresh pool contains all eleven source rows"),Inventory->OwnedItems.Num(),11);
    TestFalse(TEXT("Classic clears stale non-table key"),Inventory->OwnedItems.Contains(Item::Edge));
    for (const auto& Entry:Inventory->OwnedItems) {
        TestTrue(TEXT("Classic pool starts unlocked"),Entry.Value.bIsUnlocked);
        TestEqual(TEXT("Classic pool starts level one"),Entry.Value.Level,1);
        TestEqual(TEXT("Classic pool has no invented charges"),Entry.Value.Charges,0);
    }
    for (int32 Seed=0;Seed<64;++Seed) {
        Random.Initialize(Seed);
        RecoveredNewerInventoryAdapter::PrepareFreshLoadout(*Inventory,1,Random);
        TestEqual(TEXT("Tower fresh pool contains exactly two items"),Inventory->OwnedItems.Num(),2);
        TestFalse(TEXT("Tower excludes Resupply"),Inventory->OwnedItems.Contains(Item::Resupply));
        int32 Offensive=0;
        for (const auto& Entry:Inventory->OwnedItems) {
            const uint8 Type=static_cast<uint8>(Entry.Key);
            Offensive+=(Type==5||Type==9||Type==11||Type==12)?1:0;
            TestTrue(TEXT("Tower pool unlocked"),Entry.Value.bIsUnlocked);
            TestEqual(TEXT("Tower pool no charges"),Entry.Value.Charges,0);
            TestEqual(TEXT("Tower pool level one"),Entry.Value.Level,1);
        }
        TestEqual(TEXT("Tower has one item from each class"),Offensive,1);
        for (const auto Slot:Inventory->HotbarItems) TestEqual(TEXT("Fresh chooser never invents equipped defaults"),Slot,Item::None);
    }
    RecoveredNewerInventoryAdapter::PrepareFreshLoadout(*Inventory,2,Random);
    TestEqual(TEXT("Fresh music pool contains only Break"),Inventory->OwnedItems.Num(),1);
    TestEqual(TEXT("Music initial Break has zero charges"),Inventory->GetItemState(Item::Break).Charges,0);
    auto* Save=NewObject<URecoveredSaveGame>();
    Save->SetIntArraySetting(TEXT("LastSavedHotBarItems"),{1,99,4,8,12,3});
    RecoveredNewerInventoryAdapter::RestoreClassicHotbar(*Inventory,Save);
    TestEqual(TEXT("Classic saved slots bounded to five"),Inventory->HotbarItems.Num(),5);
    TestEqual(TEXT("Classic restores source saved selection"),Inventory->HotbarItems[0],Item::DecreaseHeat);
    TestEqual(TEXT("Classic invalid saved entry becomes None"),Inventory->HotbarItems[1],Item::None);
    TestTrue(TEXT("Classic slot selection saves"),RecoveredNewerInventoryAdapter::SaveClassicHotbar(*Inventory,Save));
    TestEqual(TEXT("Classic source key persists five slots"),Save->GetIntArraySetting(TEXT("LastSavedHotBarItems")).Num(),5);
    return true;
}
#endif
