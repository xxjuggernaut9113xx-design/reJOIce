#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSaveBackupTest,"CockHero.Recovery.ProfileBackupBeforeMigration",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSaveBackupTest::RunTest(const FString& Parameters) {
    const FString Slot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    FString Backup,Repeated,Changed,Error;
    ON_SCOPE_EXIT {
        UGameplayStatics::DeleteGameInSlot(Slot,0);
        for (const FString& Name:{Backup,Changed}) if (!Name.IsEmpty()) UGameplayStatics::DeleteGameInSlot(Name,0);
    };
    TestFalse(TEXT("Original profiles cannot be targeted"),URecoveredGameInstance::BackupRecoverySlot(TEXT("PlayerSave"),Repeated,Error));
    TestTrue(TEXT("Absent recovery profile needs no backup"),URecoveredGameInstance::BackupRecoverySlot(Slot,Repeated,Error));
    TestTrue(TEXT("Absent profile leaves backup name empty"),Repeated.IsEmpty());
    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Initialize source defaults"),Save->InitializeRecoveredDefaults())) return false;
    Save->SetNumberSetting(TEXT("UnlockPoints"),17);
    if (!TestTrue(TEXT("Write isolated test profile"),UGameplayStatics::SaveGameToSlot(Save,Slot,0))) return false;
    if (!TestTrue(TEXT("Create verified backup"),URecoveredGameInstance::BackupRecoverySlot(Slot,Backup,Error))) return false;
    TestTrue(TEXT("Repeated backup succeeds"),URecoveredGameInstance::BackupRecoverySlot(Slot,Repeated,Error));
    TestEqual(TEXT("Identical bytes reuse snapshot"),Repeated,Backup);
    Save->SetNumberSetting(TEXT("UnlockPoints"),29);
    if (!TestTrue(TEXT("Simulate migrated profile write"),UGameplayStatics::SaveGameToSlot(Save,Slot,0))) return false;
    if (!TestTrue(TEXT("Changed bytes create separate snapshot"),URecoveredGameInstance::BackupRecoverySlot(Slot,Changed,Error))) return false;
    TestNotEqual(TEXT("Previous snapshot identity retained"),Changed,Backup);
    auto* Restored=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(Backup,0));
    if (!TestNotNull(TEXT("Pre-migration snapshot deserializes"),Restored)) return false;
    TestEqual(TEXT("Pre-migration balance is recoverable"),Restored->GetNumberSetting(TEXT("UnlockPoints")),17.0);
    const TArray<uint8> Corrupt={1,2,3};
    if (!TestTrue(TEXT("Inject damaged snapshot"),UGameplayStatics::SaveDataToSlot(Corrupt,Backup,0))) return false;
    UGameplayStatics::SaveGameToSlot(Restored,Slot,0);
    TestFalse(TEXT("Existing damaged snapshot fails closed"),URecoveredGameInstance::BackupRecoverySlot(Slot,Repeated,Error));
    TestFalse(TEXT("Backup failure carries diagnostic"),Error.IsEmpty());
    return true;
}
#endif
