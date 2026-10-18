#include "RecoveredNewerInventory.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
// Expectations are the retained newer Blueprint branches, not old 0..4 store levels.
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerInventoryOwnershipTest, "CockHero.Recovery.NewerInventory.Ownership", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerInventoryOwnershipTest::RunTest(const FString& Parameters) {
    using Item = ERecoveredShopItemType;
    auto* Inventory = NewObject<URecoveredNewerInventory>();
    const auto Missing = Inventory->GetItemState(Item::Break);
    TestFalse(TEXT("Missing state is locked"), Missing.bIsUnlocked);
    TestEqual(TEXT("Missing state uses source level one"), Missing.Level, 1);
    TestEqual(TEXT("Missing state has zero charges"), Missing.Charges, 0);
    TestEqual(TEXT("Missing lookup does not insert"), Inventory->OwnedItems.Num(), 0);
    TestFalse(TEXT("None cannot unlock"), Inventory->UnlockItem(Item::None));
    TestTrue(TEXT("Unlock creates state"), Inventory->UnlockItem(Item::Break));
    TestTrue(TEXT("Unlock marks state unlocked"), Inventory->GetItemState(Item::Break).bIsUnlocked);
    Inventory->OwnedItems[Item::Break].Charges = 2;
    TestFalse(TEXT("Repeated unlock fails"), Inventory->UnlockItem(Item::Break));
    TestEqual(TEXT("Repeated unlock preserves charges"), Inventory->GetItemState(Item::Break).Charges, 2);

    bool SourceSuccess = true;
    TestFalse(TEXT("Upgrade rejects missing key"), Inventory->UpgradeItem(Item::Bounty, true, SourceSuccess));
    TestFalse(TEXT("Rejected upgrade writes false"), SourceSuccess);
    for (int32 Level = 2; Level <= 5; ++Level) {
        SourceSuccess = false;
        TestTrue(TEXT("Owned item upgrades through level five"), Inventory->UpgradeItem(Item::Break, true, SourceSuccess));
        TestTrue(TEXT("Valid hotbar writes true"), SourceSuccess);
        TestEqual(TEXT("One level per upgrade"), Inventory->GetItemState(Item::Break).Level, Level);
    }
    TestFalse(TEXT("Level five is capped"), Inventory->UpgradeItem(Item::Break, true, SourceSuccess));
    TestFalse(TEXT("Capped upgrade clears output"), SourceSuccess);
    TestEqual(TEXT("Upgrade preserves charges"), Inventory->GetItemState(Item::Break).Charges, 2);

    Inventory->UnlockItem(Item::Slowdown);
    SourceSuccess = false;
    TestTrue(TEXT("Invalid hotbar still permits state upgrade"), Inventory->UpgradeItem(Item::Slowdown, false, SourceSuccess));
    TestFalse(TEXT("Source invalid-hotbar branch skips success output"), SourceSuccess);
    SourceSuccess = true;
    Inventory->UpgradeItem(Item::Slowdown, false, SourceSuccess);
    TestTrue(TEXT("Skipped output preserves true as well"), SourceSuccess);
    Inventory->OwnedItems[Item::Slowdown].bIsUnlocked = false;
    TestFalse(TEXT("Present but locked key still prevents unlock"), Inventory->UnlockItem(Item::Slowdown));
    TestTrue(TEXT("Upgrade checks presence, not unlocked field"), Inventory->UpgradeItem(Item::Slowdown, true, SourceSuccess));
    TestFalse(TEXT("Upgrade preserves stored unlocked flag"), Inventory->GetItemState(Item::Slowdown).bIsUnlocked);

    Inventory->OwnedItems.Add(Item::None, FRecoveredNewerItemState());
    TestFalse(TEXT("None still cannot upgrade when present"), Inventory->UpgradeItem(Item::None, true, SourceSuccess));
    const Item Unknown = static_cast<Item>(99);
    TestTrue(TEXT("Source unlock only guards None, not unknown bytes"), Inventory->UnlockItem(Unknown));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerInventoryChargesTest, "CockHero.Recovery.NewerInventory.Charges", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerInventoryChargesTest::RunTest(const FString& Parameters) {
    using Item = ERecoveredShopItemType;
    FRecoveredNewerChargeContext Context;
    // Literal enum-indexed source expectations; -1 means no output assignment.
    const int32 SourceMaximums[] = {1, 3, -1, 3, 2, 5, 15, 1, -1, 3, 1, 2, 2, 1};
    for (uint8 Index = 0; Index < UE_ARRAY_COUNT(SourceMaximums); ++Index) {
        for (bool bPockets : {false, true}) {
            Context.bBiggerPockets = bPockets;
            int32 Output = 77;
            const bool bWritten = URecoveredNewerInventory::GetMaxCharges(static_cast<Item>(Index), Context, Output);
            TestEqual(TEXT("Every source charge switch branch"), bWritten, SourceMaximums[Index] >= 0);
            TestEqual(TEXT("BiggerPockets only follows assigned branches"), Output, SourceMaximums[Index] < 0 ? 77 : SourceMaximums[Index] + (bPockets ? 1 : 0));
        }
    }
    int32 Output = 77;
    TestFalse(TEXT("Unknown enum skips output"), URecoveredNewerInventory::GetMaxCharges(static_cast<Item>(99), Context, Output));
    TestEqual(TEXT("Unknown output stays untouched"), Output, 77);
    Context.GameModeSelection = 2;
    TestFalse(TEXT("Playlist break needs global manager"), URecoveredNewerInventory::GetMaxCharges(Item::Break, Context, Output));
    TestEqual(TEXT("Missing manager skips output, including pockets"), Output, 77);
    Context.bGlobalManagerValid = true;
    Context.EffectiveMaxBreakCharges = 6;
    TestTrue(TEXT("Playlist break uses effective manager maximum"), URecoveredNewerInventory::GetMaxCharges(Item::Break, Context, Output));
    TestEqual(TEXT("Pockets applies after playlist override"), Output, 7);

    auto* Inventory = NewObject<URecoveredNewerInventory>();
    Context = FRecoveredNewerChargeContext();
    TestFalse(TEXT("Grant does not unlock missing keys"), Inventory->GrantItem(Item::DecreaseHeat, 1, Context));
    TestEqual(TEXT("Failed grant leaves map empty"), Inventory->OwnedItems.Num(), 0);
    Inventory->UnlockItem(Item::DecreaseHeat);
    TestTrue(TEXT("Grant below cap"), Inventory->GrantItem(Item::DecreaseHeat, 2, Context));
    TestTrue(TEXT("Multi-charge grant may exceed cap"), Inventory->GrantItem(Item::DecreaseHeat, 5, Context));
    TestEqual(TEXT("Source overflow past max is deliberately retained"), Inventory->GetItemState(Item::DecreaseHeat).Charges, 7);
    TestFalse(TEXT("Further grant rejected while above cap"), Inventory->GrantItem(Item::DecreaseHeat, -10, Context));
    TestEqual(TEXT("Rejected grant does not subtract"), Inventory->GetItemState(Item::DecreaseHeat).Charges, 7);
    Inventory->OwnedItems[Item::DecreaseHeat].Charges = 0;
    Inventory->OwnedItems[Item::DecreaseHeat].bIsUnlocked = false;
    TestTrue(TEXT("Grant ignores stored unlocked flag"), Inventory->GrantItem(Item::DecreaseHeat, -2, Context));
    TestEqual(TEXT("Source does not reject negative grants below cap"), Inventory->GetItemState(Item::DecreaseHeat).Charges, -2);
    TestTrue(TEXT("Zero grant below cap follows success path"), Inventory->GrantItem(Item::DecreaseHeat, 0, Context));
    Inventory->UnlockItem(Item::Edge);
    TestFalse(TEXT("Unhandled Edge maximum defaults to call-site zero"), Inventory->GrantItem(Item::Edge, 1, Context));
    Inventory->OwnedItems.Add(Item::None, FRecoveredNewerItemState());
    TestFalse(TEXT("None grant rejects even when key exists"), Inventory->GrantItem(Item::None, 1, Context));
    Inventory->UnlockItem(Item::Break);
    Context.GameModeSelection = 2;
    TestFalse(TEXT("Missing playlist manager leaves grant maximum at zero"), Inventory->GrantItem(Item::Break, 1, Context));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerInventoryHotbarTest, "CockHero.Recovery.NewerInventory.Hotbar", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerInventoryHotbarTest::RunTest(const FString& Parameters) {
    using Item = ERecoveredShopItemType;
    auto* Inventory = NewObject<URecoveredNewerInventory>();
    Inventory->SetRhythmModeHotbar();
    TestTrue(TEXT("Rhythm mode does not grow empty source hotbar"), Inventory->HotbarItems.IsEmpty());
    TestFalse(TEXT("Unowned item cannot equip"), Inventory->EquipToSlot(Item::Break, 4));
    TestTrue(TEXT("Failed equip does not grow bar"), Inventory->HotbarItems.IsEmpty());
    Inventory->UnlockItem(Item::Break);
    Inventory->HotbarItems = {Item::Break, Item::Slowdown, Item::Break};
    TestTrue(TEXT("Equip grows destination"), Inventory->EquipToSlot(Item::Break, 4));
    TestEqual(TEXT("Destination size"), Inventory->HotbarItems.Num(), 5);
    TestEqual(TEXT("First duplicate clears to enum0, not None8"), Inventory->HotbarItems[0], Item::IncreaseCumMeter);
    TestEqual(TEXT("Second duplicate clears to enum0"), Inventory->HotbarItems[2], Item::IncreaseCumMeter);
    TestEqual(TEXT("Growth gap defaults to enum0"), Inventory->HotbarItems[3], Item::IncreaseCumMeter);
    TestEqual(TEXT("Unrelated slot unchanged"), Inventory->HotbarItems[1], Item::Slowdown);
    TestEqual(TEXT("Requested slot receives item"), Inventory->HotbarItems[4], Item::Break);
    TestFalse(TEXT("Negative slot cannot be assigned"), Inventory->EquipToSlot(Item::Break, -1));
    TestEqual(TEXT("Source clears duplicate even for negative destination"), Inventory->HotbarItems[4], Item::IncreaseCumMeter);
    TestTrue(TEXT("UnEquip also uses size-to-fit"), Inventory->UnEquipSlot(5));
    TestEqual(TEXT("UnEquip writes enum0"), Inventory->HotbarItems[5], Item::IncreaseCumMeter);
    Inventory->ResetHotbar();
    TestEqual(TEXT("Reset retains configured size"), Inventory->HotbarItems.Num(), 6);
    for (const Item Value : Inventory->HotbarItems) TestEqual(TEXT("Reset uses true None8"), Value, Item::None);
    Inventory->SetRhythmModeHotbar();
    TestEqual(TEXT("Rhythm first slot is Break"), Inventory->HotbarItems[0], Item::Break);
    for (int32 Index = 1; Index < Inventory->HotbarItems.Num(); ++Index) TestEqual(TEXT("Rhythm clears remaining slots"), Inventory->HotbarItems[Index], Item::None);
    Inventory->OwnedItems[Item::Break].bIsUnlocked = false;
    TestTrue(TEXT("Equip requires map presence, not unlocked flag"), Inventory->EquipToSlot(Item::Break, 1));
    return true;
}
#endif
