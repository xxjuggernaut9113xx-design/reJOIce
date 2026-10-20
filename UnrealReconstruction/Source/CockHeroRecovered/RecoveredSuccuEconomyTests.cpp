#include "RecoveredSuccuEconomy.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSuccuEconomyTest,"CockHero.Recovery.NewerInventory.SuccuShopTransactions",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSuccuEconomyTest::RunTest(const FString& Parameters) {
    auto* Economy=NewObject<URecoveredSuccuEconomy>();
    TestEqual(TEXT("Source catalog has twenty-one rows"),Economy->GetCatalog().Num(),21);
    TestEqual(TEXT("Run starts with zero currency"),Economy->SuccuCoins,0);
    TestFalse(TEXT("No purchase without currency"),Economy->Purchase(0));
    TestTrue(TEXT("Round reward credits wallet"),Economy->AddSuccuCoins(100));
    TestFalse(TEXT("Unknown enum cannot debit wallet"),Economy->Purchase(15));
    TestEqual(TEXT("Invalid purchase leaves balance"),Economy->SuccuCoins,100);
    TestTrue(TEXT("Pot lid uses source price"),Economy->Purchase(0));
    TestEqual(TEXT("Source price deducted"),Economy->SuccuCoins,90);
    TestEqual(TEXT("Pot lid heat cap"),Economy->GetHeatCap(),75.0);
    TestFalse(TEXT("Repeated ownership cannot charge twice"),Economy->Purchase(0));
    TestEqual(TEXT("Duplicate purchase preserves currency"),Economy->SuccuCoins,90);
    TestTrue(TEXT("Lube purchase"),Economy->Purchase(2));
    TestEqual(TEXT("Heat gain halved"),Economy->AdjustHeatGain(20),10.0);
    TestEqual(TEXT("Source normal cooling path is also halved"),Economy->AdjustHeatGain(-20),-10.0);
    TestFalse(TEXT("Negative reward rejected"),Economy->AddSuccuCoins(-1));
    Economy->ResetRun();
    TestEqual(TEXT("New run clears wallet"),Economy->SuccuCoins,0);
    TestTrue(TEXT("Run-only modifiers cleared"),Economy->OwnedModifiers.IsEmpty());
    TestEqual(TEXT("New run restores default heat cap"),Economy->GetHeatCap(),100.0);
    return true;
}
#endif
