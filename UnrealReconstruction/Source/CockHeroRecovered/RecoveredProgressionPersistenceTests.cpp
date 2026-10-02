#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/ScopeExit.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredProgressionStateTest,"CockHero.Recovery.ProgressionStateMemoryRoundTrip",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredProgressionStateTest::RunTest(const FString& Parameters) {
    auto* Source=NewObject<URecoveredProgressionManager>();
    Source->CurrentXP=37; Source->CurrentLevel=4; Source->TotalXPEarned=582; Source->UnlockPoints=15;
    Source->UnlockedPlayerCards.Add(TEXT("FirstCard")); Source->UnlockedPlayerCards.Add(TEXT("SecondCard"));
    Source->UnlockedModifiers.Add(TEXT("Slow and Steady"));
    const FString Json=Source->ExportRecoveryState();
    auto* Destination=NewObject<URecoveredProgressionManager>();
    if (!TestTrue(TEXT("Recovery progression state loads"),Destination->ImportRecoveryState(Json))) return false;
    TestEqual(TEXT("All recovery progression values survive"),Destination->ExportRecoveryState(),Json);
    const FString Invalid[]={TEXT("not JSON"),TEXT("{}"),TEXT("{\"Version\":2}"),TEXT("{\"Version\":1,\"CurrentXP\":1.5}")};
    for (const auto& Value:Invalid) {
        TestFalse(TEXT("Malformed or unsupported progression is rejected"),Destination->ImportRecoveryState(Value));
        TestEqual(TEXT("Rejected input does not partially change progression"),Destination->ExportRecoveryState(),Json);
    }
    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Isolated source save defaults load"),Save->InitializeRecoveredDefaults())) return false;
    TestTrue(TEXT("Recovery state stored without replacing the source document"),Save->SetStringSetting(TEXT("RecoveryProgressionState"),Json));
    TestEqual(TEXT("Original pack list survives new progression state"),Save->GetStringArraySetting(TEXT("EnabledPacks"))[0],FString(TEXT("Base_Game_CG")));
    TestTrue(TEXT("Embedded progression restores"),Destination->ImportRecoveryState(Save->GetStringSetting(TEXT("RecoveryProgressionState"),TEXT(""))));
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredProgressionDiskTest,"CockHero.Recovery.IsolatedProgressionDiskRoundTrip",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredProgressionDiskTest::RunTest(const FString& Parameters) {
    const FString Slot=TEXT("CockHeroRecovered_Automation_")+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    if (!TestFalse(TEXT("Validation slot cannot overwrite an existing save"),UGameplayStatics::DoesSaveGameExist(Slot,0))) return false;
    bool bCreated=false;
    ON_SCOPE_EXIT { if (bCreated) UGameplayStatics::DeleteGameInSlot(Slot,0); };
    auto* Source=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Source defaults load for disk validation"),Source->InitializeRecoveredDefaults())) return false;
    auto* Progression=NewObject<URecoveredProgressionManager>();
    Progression->CurrentXP=55; Progression->CurrentLevel=3; Progression->UnlockPoints=23;
    Progression->UnlockedModifiers.Add(TEXT("Slow and Steady"));
    Source->SetStringSetting(TEXT("RecoveryProgressionState"),Progression->ExportRecoveryState());
    bCreated=UGameplayStatics::SaveGameToSlot(Source,Slot,0);
    if (!TestTrue(TEXT("Engine writes the dedicated validation slot"),bCreated)) return false;
    auto* Loaded=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot,0));
    if (!TestNotNull(TEXT("Engine loads the recovery save class"),Loaded)) return false;
    TestEqual(TEXT("Entire source and recovery state survives disk"),Loaded->StateJson,Source->StateJson);
    TestTrue(TEXT("Recovery format remains valid"),Loaded->IsStateValid());
    auto* Restored=NewObject<URecoveredProgressionManager>();
    TestTrue(TEXT("Progression is restored from disk state"),Restored->ImportRecoveryState(Loaded->GetStringSetting(TEXT("RecoveryProgressionState"),TEXT(""))));
    TestEqual(TEXT("Disk progression matches"),Restored->ExportRecoveryState(),Progression->ExportRecoveryState());
    return true;
}
#endif
