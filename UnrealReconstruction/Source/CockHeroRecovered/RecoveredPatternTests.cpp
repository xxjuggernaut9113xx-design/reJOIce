#include "RecoveredSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPatternAdjustmentTest,"CockHero.Recovery.PatternAdjustmentTraceFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPatternAdjustmentTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/pattern-adjustment-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Inputs=Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes=Fixture->GetObjectField(TEXT("writes"));
        FRecoveredBeatPattern Pattern;
        for(const auto& Number:Inputs->GetObjectField(TEXT("BeatPatternStruct"))->GetArrayField(TEXT("IntervalMultipliers"))) Pattern.IntervalMultipliers.Add(Number->AsNumber());
        const auto Actual=URecoveredSessionRuleLibrary::CheckIntervalMultipliers(Pattern,Inputs->GetNumberField(TEXT("call:GetCurrentInterval")));
        const auto& Expected=Writes->GetObjectField(TEXT("BeatPatternStructOut"))->GetArrayField(TEXT("IntervalMultipliers"));
        TestEqual(TEXT("Pattern length retained"),Actual.IntervalMultipliers.Num(),Expected.Num());
        for(int32 Index=0;Index<Expected.Num();++Index) TestEqual(FString::Printf(TEXT("Pattern trace %d multiplier %d"),Count,Index),Actual.IntervalMultipliers[Index],Expected[Index]->AsNumber());
        ++Count;
    }
    TestEqual(TEXT("All pattern traces"),Count,310);
    return true;
}
#endif
