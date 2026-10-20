#include "RecoveredNativeLoot.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNativeLootTest,"CockHero.Recovery.NewerInventory.NativeLootDistribution",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNativeLootTest::RunTest(const FString& Parameters) {
    auto* Inventory=NewObject<URecoveredNewerInventory>();
    FRecoveredNativeLootContext Context;
    TestEqual(TEXT("Source ctor cash fallback"),RecoveredNativeLoot::Roll(*Inventory,Context,0).Amount,10);
    Inventory->UnlockItem(ERecoveredShopItemType::DecreaseHeat);
    Inventory->HotbarItems={ERecoveredShopItemType::DecreaseHeat};
    TestEqual(TEXT("Source weight15 includes boundary"),RecoveredNativeLoot::Roll(*Inventory,Context,15).Type,uint8(4));
    TestEqual(TEXT("Outside weight falls to cash"),RecoveredNativeLoot::Roll(*Inventory,Context,15.01f).Type,uint8(0));
    Context.bPrizeMachine=true;
    TestEqual(TEXT("Prize Machine source4x"),RecoveredNativeLoot::Roll(*Inventory,Context,60).Type,uint8(4));
    TestEqual(TEXT("Prize source4x upper bound"),RecoveredNativeLoot::Roll(*Inventory,Context,60.01f).Type,uint8(0));
    Context.bBurningProfits=true;
    TestEqual(TEXT("Combined source6x"),RecoveredNativeLoot::Roll(*Inventory,Context,90).Type,uint8(4));
    Context.bBadRNG=true;
    TestEqual(TEXT("Bad RNG subtracts fifty points"),RecoveredNativeLoot::Roll(*Inventory,Context,40.01f).Type,uint8(0));
    Context=FRecoveredNativeLootContext();
    Inventory->HotbarItems.Add(ERecoveredShopItemType::DecreaseHeat);
    TestEqual(TEXT("Native duplicate hotbar entries double weight"),RecoveredNativeLoot::Roll(*Inventory,Context,30).Type,uint8(4));
    Inventory->OwnedItems[ERecoveredShopItemType::DecreaseHeat].Charges=3;
    TestEqual(TEXT("Native table cap removes entries"),RecoveredNativeLoot::Roll(*Inventory,Context,0).Type,uint8(0));
    Context.bBiggerPockets=true;
    TestEqual(TEXT("Pockets adds one to native table capacity"),RecoveredNativeLoot::Roll(*Inventory,Context,0).Type,uint8(4));
    Context.bJackpotDrops=true;
    TestEqual(TEXT("Jackpot source ctor probability7.5"),RecoveredNativeLoot::Roll(*Inventory,Context,7.5f).Type,uint8(6));
    TestEqual(TEXT("Jackpot replaces item weights"),RecoveredNativeLoot::Roll(*Inventory,Context,7.51f).Type,uint8(0));
    Context.bDrySpell=true;
    TestEqual(TEXT("Dry spell overrides jackpots"),RecoveredNativeLoot::Roll(*Inventory,Context,0).Type,uint8(0));
    const TArray<FString> Panic={TEXT("Panic Button")};
    TestTrue(TEXT("Panic blocks source defensive class at exact threshold"),RecoveredNativeLoot::IsPanicBlocked(TEXT("DecreaseHeat"),75,Panic));
    TestFalse(TEXT("Panic clears above threshold"),RecoveredNativeLoot::IsPanicBlocked(TEXT("DecreaseHeat"),75.01,Panic));
    TestFalse(TEXT("Panic leaves offensive class available"),RecoveredNativeLoot::IsPanicBlocked(TEXT("Bounty"),20,Panic));
    return true;
}
#endif
