#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Dom/JsonObject.h"
#include "Misc/ScopeExit.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSaveTest,"CockHero.Recovery.IsolatedSaveMemoryRoundTrip",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSaveTest::RunTest(const FString& Parameters) {
    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Verified source defaults initialize"),Save->InitializeRecoveredDefaults())) return false;
    TestEqual(TEXT("Entire source default document retained"),Save->StateJson,Save->RecoveredDefinition->SerializedDefaultsJson);
    TestTrue(TEXT("Cooked numeric bool read"),Save->GetBoolSetting(TEXT("IsScreenShakeEnabled")));
    TestEqual(TEXT("Source unlock balance"),Save->GetNumberSetting(TEXT("UnlockPoints")),5.0);
    TestEqual(TEXT("Source FPS string"),Save->GetStringSetting(TEXT("FPSLimit"),TEXT("")),FString(TEXT("60")));
    TestEqual(TEXT("Enabled pack list is readable by startup"),Save->GetStringArraySetting(TEXT("EnabledPacks"))[0],FString(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Scalar setting is not interpreted as an array"),Save->GetStringArraySetting(TEXT("FPSLimit")).Num(),0);
    TestTrue(TEXT("Missing bool keeps explicit fallback"),Save->GetBoolSetting(TEXT("missing"),true));
    TestTrue(TEXT("Change a setting"),Save->SetBoolSetting(TEXT("IsScreenShakeEnabled"),false));
    TestTrue(TEXT("Change a balance"),Save->SetNumberSetting(TEXT("UnlockPoints"),19));
    TestTrue(TEXT("Change a text setting"),Save->SetStringSetting(TEXT("FPSLimit"),TEXT("120")));
    TArray<uint8> Data;
    if (!TestTrue(TEXT("Serialize without touching any save slot"),UGameplayStatics::SaveGameToMemory(Save,Data))) return false;
    auto* Restored=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromMemory(Data));
    if (!TestNotNull(TEXT("Load recovery save from memory"),Restored)) return false;
    TestTrue(TEXT("Recovery format validated"),Restored->IsStateValid());
    TestEqual(TEXT("Every state field survives save/load"),Restored->StateJson,Save->StateJson);
    TestFalse(TEXT("Changed bool survives"),Restored->GetBoolSetting(TEXT("IsScreenShakeEnabled"),true));
    TestEqual(TEXT("Changed balance survives"),Restored->GetNumberSetting(TEXT("UnlockPoints")),19.0);
    TSharedPtr<FJsonObject> Object;
    if (!TestTrue(TEXT("Nested state remains valid JSON"),FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Restored->StateJson),Object))) return false;
    TestEqual(TEXT("Pack arrays retained"),Object->GetArrayField(TEXT("EnabledPacks"))[0]->AsString(),FString(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Nested latency default retained"),Object->GetObjectField(TEXT("LatencyProfile"))->GetNumberField(TEXT("SystemBufferMs")),60.0);
    Restored->RecoveryFormatVersion=2;
    TestFalse(TEXT("Unsupported version rejected"),Restored->IsStateValid());
    Restored->RecoveryFormatVersion=1; Restored->StateJson=TEXT("malformed");
    TestFalse(TEXT("Malformed state rejected"),Restored->IsStateValid());
    TestFalse(TEXT("Malformed state is not silently overwritten"),Restored->SetBoolSetting(TEXT("example"),true));
    TestEqual(TEXT("Corrupt state remains available for diagnosis"),Restored->StateJson,FString(TEXT("malformed")));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNamedSaveSlotIndexTest,"CockHero.Recovery.NamedSaveSlotIndexRoundTrip",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNamedSaveSlotIndexTest::RunTest(const FString& Parameters) {
    const FString RegistrySlot=TEXT("CockHeroRecovered_AutomationSlotIndex_")+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    ON_SCOPE_EXIT { UGameplayStatics::DeleteGameInSlot(RegistrySlot,0); };
    const FString SlotA=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("Alpha");
    const FString SlotB=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("Beta");
    TestTrue(TEXT("Named recovery profile accepts a bounded identifier"),URecoveredGameInstance::IsRecoverySlotNameValid(SlotA));
    TestTrue(TEXT("Default recovery profile is an accepted target"),URecoveredGameInstance::IsRecoverySlotNameValid(URecoveredGameInstance::GetDefaultRecoverySlotName()));
    TestFalse(TEXT("Original-slot traversal is rejected"),URecoveredGameInstance::IsRecoverySlotNameValid(TEXT("../PlayerSave")));
    TestFalse(TEXT("Malformed named profile is rejected"),URecoveredGameInstance::IsRecoverySlotNameValid(URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("bad/name")));
    const TArray<FString> WrittenSlots={SlotB,SlotA};
    if (!TestTrue(TEXT("Dedicated recovery registry writes"),URecoveredGameInstance::WriteRecoverySlotIndex(WrittenSlots,SlotB,RegistrySlot))) return false;
    TArray<FString> ReadSlots;
    FString ActiveSlot;
    if (!TestTrue(TEXT("Dedicated recovery registry reads"),URecoveredGameInstance::ReadRecoverySlotIndex(ReadSlots,ActiveSlot,RegistrySlot))) return false;
    if (!TestEqual(TEXT("Registry returns every named profile"),ReadSlots.Num(),2)) return false;
    TestEqual(TEXT("Registry canonicalizes the named slot order"),ReadSlots[0],SlotA);
    TestEqual(TEXT("Registry preserves the active recovery profile"),ActiveSlot,SlotB);
    TArray<FString> DuplicateSlots={SlotA,SlotA.ToUpper()};
    const TArray<FString> SingleSlot={SlotA};
    TestFalse(TEXT("Registry rejects duplicate profile names without case ambiguity"),URecoveredGameInstance::WriteRecoverySlotIndex(DuplicateSlots,SlotA,RegistrySlot));
    TestFalse(TEXT("Registry rejects a path-like active profile"),URecoveredGameInstance::WriteRecoverySlotIndex(SingleSlot,TEXT("../PlayerSave"),RegistrySlot));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNamedSaveProfileSwitchTest,"CockHero.Recovery.NamedSaveProfileSwitch",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNamedSaveProfileSwitchTest::RunTest(const FString& Parameters) {
    const FString RegistrySlot=URecoveredGameInstance::GetRecoverySlotIndexName();
    const bool bHadRegistry=UGameplayStatics::DoesSaveGameExist(RegistrySlot,0);
    TArray<uint8> OriginalRegistryBytes;
    if (bHadRegistry) {
        auto* OriginalRegistry=Cast<URecoveredSaveSlotIndex>(UGameplayStatics::LoadGameFromSlot(RegistrySlot,0));
        if (!TestNotNull(TEXT("Existing recovery registry is readable before isolation"),OriginalRegistry)) return false;
        if (!TestTrue(TEXT("Existing recovery registry is preserved before isolation"),UGameplayStatics::SaveGameToMemory(OriginalRegistry,OriginalRegistryBytes))) return false;
    }
    const FString ProfileSlot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("Automation_")+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    bool bProfileWritten=false;
    ON_SCOPE_EXIT {
        if (bProfileWritten) UGameplayStatics::DeleteGameInSlot(ProfileSlot,0);
        if (bHadRegistry) {
            if (auto* OriginalRegistry=Cast<URecoveredSaveSlotIndex>(UGameplayStatics::LoadGameFromMemory(OriginalRegistryBytes))) {
                UGameplayStatics::SaveGameToSlot(OriginalRegistry,RegistrySlot,0);
            }
        } else {
            UGameplayStatics::DeleteGameInSlot(RegistrySlot,0);
        }
    };

    auto* Source=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Isolated named profile initializes source defaults"),Source->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Isolated named profile records distinct progress"),Source->SetNumberSetting(TEXT("UnlockPoints"),41))) return false;
    bProfileWritten=UGameplayStatics::SaveGameToSlot(Source,ProfileSlot,0);
    if (!TestTrue(TEXT("Isolated named profile writes"),bProfileWritten)) return false;

    TArray<FString> Profiles;
    FString ActiveProfile;
    if (!TestTrue(TEXT("Existing profile registry reads before switch"),URecoveredGameInstance::ReadRecoverySlotIndex(Profiles,ActiveProfile,RegistrySlot))) return false;
    Profiles.Add(ProfileSlot);
    if (!TestTrue(TEXT("Isolated named profile enters the registry"),URecoveredGameInstance::WriteRecoverySlotIndex(Profiles,ActiveProfile,RegistrySlot))) return false;

    auto* Instance=NewObject<URecoveredGameInstance>();
    if (!TestTrue(TEXT("Named profile rehydrates into a game instance"),Instance->LoadRecoveredSaveSlot(ProfileSlot))) return false;
    TestEqual(TEXT("Named profile becomes the active persistence target"),Instance->GetActiveRecoverySlot(),ProfileSlot);
    if (!TestNotNull(TEXT("Named profile exposes its recovery save"),Instance->CurrentSave.Get())) return false;
    TestEqual(TEXT("Named profile restores its unlock balance"),Instance->CurrentSave->GetNumberSetting(TEXT("UnlockPoints")),41.0);
    if (!TestNotNull(TEXT("Named profile rehydrates progression"),Instance->ProgressionManager.Get())) return false;
    TestEqual(TEXT("Named profile progression receives its unlock balance"),Instance->ProgressionManager->UnlockPoints,41);
    TestNotNull(TEXT("Named profile rehydrates challenge tracking"),Instance->ChallengeTracker.Get());
    TestNotNull(TEXT("Named profile rehydrates calibration"),Instance->CalibrationManager.Get());
    if (!TestTrue(TEXT("Named profile mutates its own active save"),Instance->CurrentSave->SetNumberSetting(TEXT("UnlockPoints"),73))) return false;
    if (!TestTrue(TEXT("Named profile persists to its own target"),Instance->SaveRecoveredState())) return false;
    auto* Persisted=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(ProfileSlot,0));
    if (!TestNotNull(TEXT("Named profile reloads after persistence"),Persisted)) return false;
    TestEqual(TEXT("Named profile does not fall back to the default target"),Persisted->GetNumberSetting(TEXT("UnlockPoints")),73.0);
    TestFalse(TEXT("Invalid profile cannot replace the active recovery target"),Instance->LoadRecoveredSaveSlot(TEXT("../PlayerSave")));
    TestEqual(TEXT("Rejected profile leaves active target intact"),Instance->GetActiveRecoverySlot(),ProfileSlot);
    return true;
}
#endif
