#include "RecoveredNewerItemEffects.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerItemEffectsTest,"CockHero.Recovery.NewerInventory.TimedEffects",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerItemEffectsTest::RunTest(const FString& Parameters) {
    auto* Effects=NewObject<URecoveredNewerItemEffects>();
    Effects->StartLootRush(5);
    TestEqual(TEXT("Recovered maximum loot rush duration"),Effects->LootRushRemaining,50.0);
    TestEqual(TEXT("Recovered maximum additive multiplier"),Effects->LootRushBonus,1.5);
    TestFalse(TEXT("Partial interval remains active"),Effects->AdvanceLootRush(49));
    TestFalse(TEXT("Invalid interval cannot expire effect"),Effects->AdvanceLootRush(-1));
    TestTrue(TEXT("Exact deadline expires effect"),Effects->AdvanceLootRush(1));
    TestEqual(TEXT("Expiry clears bonus"),Effects->LootRushBonus,0.0);
    TestFalse(TEXT("Expiry fires once"),Effects->AdvanceLootRush(1));
    FRandomStream Random(7123);
    Effects->StartBounty(1,100,Random);
    TestTrue(TEXT("Recovered level one duration"),Effects->BountyRemaining>=14 && Effects->BountyRemaining<=17);
    TestTrue(TEXT("Recovered level one requirement"),Effects->BountyRequiredStrokes>=38 && Effects->BountyRequiredStrokes<=48);
    TestEqual(TEXT("Preexisting strokes cannot complete bounty"),Effects->AdvanceBounty(0,100),0);
    TestEqual(TEXT("Required new strokes complete bounty"),Effects->AdvanceBounty(1,100+Effects->BountyRequiredStrokes),1);
    TestEqual(TEXT("Reward cannot be claimed twice"),Effects->AdvanceBounty(1,999),0);
    Effects->StartBounty(5,500,Random);
    TestEqual(TEXT("Deadline without strokes fails"),Effects->AdvanceBounty(31,500),-1);
    TestEqual(TEXT("Failure cannot fire twice"),Effects->AdvanceBounty(1,999),0);
    ERecoveredShopItemType Type;
    TestTrue(TEXT("Existing store ID resolves to native enum"),RecoveredNewerInventoryAdapter::ResolveType(TEXT("XCumChance"),Type));
    TestEqual(TEXT("Cum meter enum identity"),Type,ERecoveredShopItemType::IncreaseCumMeter);
    TestFalse(TEXT("Unknown store cannot mutate another item"),RecoveredNewerInventoryAdapter::ResolveType(TEXT("Missing"),Type));
    return true;
}
#endif
