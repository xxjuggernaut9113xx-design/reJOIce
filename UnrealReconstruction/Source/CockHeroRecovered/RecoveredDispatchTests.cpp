#include "RecoveredEventRules.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredDispatchTest,"CockHero.Recovery.EventDispatchTraceFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredDispatchTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/event-dispatch-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Inputs=Fixture->GetObjectField(TEXT("inputs"));
        FName Expected=NAME_None;
        bool bExpectedClear=false;
        for(const auto& EffectValue:Fixture->GetArrayField(TEXT("external_effects"))) {
            const auto Effect=EffectValue->AsObject();
            const FString Call=Effect->GetStringField(TEXT("call"));
            if(Call==TEXT("K2_ClearAndInvalidateTimerHandle")) bExpectedClear=true;
            else if(Call!=TEXT("PrintString") && !Effect->HasField(TEXT("injected_out_parameter"))) Expected=FName(*Call);
        }
        bool bActualClear=false;
        const FName Actual=URecoveredEventRuleLibrary::DetermineDispatchedEvent(Inputs->GetNumberField(TEXT("FoundEvent.EventName")),Inputs->GetBoolField(TEXT("outcall:Is Succu Frenzy Active")),Inputs->GetBoolField(TEXT("outcall:Is Slow and Steady Active")),Inputs->GetBoolField(TEXT("outcall:Is Double Time Active")),Inputs->GetNumberField(TEXT("call:RandomIntegerInRange")),bActualClear);
        TestEqual(FString::Printf(TEXT("Dispatch trace %d"),Count),Actual,Expected);
        TestEqual(FString::Printf(TEXT("Idle timer trace %d"),Count),bActualClear,bExpectedClear);
        ++Count;
    }
    TestEqual(TEXT("All dispatch traces"),Count,792);
    return true;
}
#endif
