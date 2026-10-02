#include "RecoveredSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredRecentDrawTest,"CockHero.Recovery.RecentDrawTraceFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredRecentDrawTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/recent-draw-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Input=Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes=Fixture->GetObjectField(TEXT("writes"));
        TArray<int32> Timestamps;
        for(const auto& Time:Input->GetArrayField(TEXT("RecentDrawTimestamps"))) Timestamps.Add(Time->AsNumber());
        const int32 Actual=URecoveredSessionRuleLibrary::UpdateRecentDrawCount(Timestamps,Input->GetNumberField(TEXT("GlobalManager.PlayerVariablesStruct.SessionLength")));
        TestEqual(FString::Printf(TEXT("Recent draws trace %d"),Count),Actual,static_cast<int32>(Writes->GetNumberField(TEXT("GlobalManager.PlayerVariablesStruct.DrawsLast5Sec"))));
        const TArray<TSharedPtr<FJsonValue>>* Expected=nullptr;
        if(!Writes->TryGetArrayField(TEXT("RecentDrawTimestamps"),Expected)) Expected=&Input->GetArrayField(TEXT("RecentDrawTimestamps"));
        TestEqual(TEXT("Timestamp count"),Timestamps.Num(),Expected->Num());
        for(int32 Index=0;Index<Expected->Num();++Index) TestEqual(TEXT("Timestamp values"),Timestamps[Index],static_cast<int32>((*Expected)[Index]->AsNumber()));
        ++Count;
    }
    TestEqual(TEXT("All recent draw cases"),Count,55);
    return true;
}
#endif
