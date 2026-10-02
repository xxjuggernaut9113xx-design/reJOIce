#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Dom/JsonObject.h"
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
#endif
