#include "RecoveredSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredDrawMultiplierTest,"CockHero.Recovery.DrawMultiplierTraceFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredDrawMultiplierTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/draw-multiplier-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Inputs=Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes=Fixture->GetObjectField(TEXT("writes"));
        double CountMultiplier=Inputs->GetNumberField(TEXT("GlobalManager.Stroke Count Multiplier"));
        double TimeMultiplier=Inputs->GetNumberField(TEXT("GlobalManager.Stroke Time Speed Multiplier"));
        URecoveredSessionRuleLibrary::DetermineDrawMultipliers(Inputs->GetNumberField(TEXT("GlobalManager.CurrentComboTypeEnum")),Inputs->GetNumberField(TEXT("GlobalManager.DifficultyStrokeCounterMultiplier")),Inputs->GetNumberField(TEXT("GlobalManager.DifficultyStrokeSpeedMultiplier")),CountMultiplier,TimeMultiplier);
        double ExpectedCount=17,ExpectedTime=19;
        Writes->TryGetNumberField(TEXT("GlobalManager.Stroke Count Multiplier"),ExpectedCount);
        Writes->TryGetNumberField(TEXT("GlobalManager.Stroke Time Speed Multiplier"),ExpectedTime);
        TestEqual(FString::Printf(TEXT("Count source trace %d"),Count),CountMultiplier,ExpectedCount);
        TestEqual(FString::Printf(TEXT("Time source trace %d"),Count),TimeMultiplier,ExpectedTime);
        ++Count;
    }
    TestEqual(TEXT("All source traces"),Count,144);
    return true;
}
#endif
