#include "RecoveredEventRules.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredEventTraceTest, "CockHero.Recovery.EventWeightFixtures", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredEventTraceTest::RunTest(const FString& Parameters) {
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *(FPaths::ProjectDir() / TEXT("RecoveryEvidence/event-weight-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root)) return false;
    FString IndexText;
    if (!FFileHelper::LoadFileToString(IndexText, *(FPaths::ProjectDir() / TEXT("RecoveryEvidence/event-rule-index.json")))) return false;
    TArray<TSharedPtr<FJsonValue>> Index;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(IndexText), Index)) return false;
    int32 Count = 0;
    for (const auto& Item : Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture = Item->AsObject();
        const auto Inputs = Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes = Fixture->GetObjectField(TEXT("writes"));
        const FString Function = Fixture->GetStringField(TEXT("function"));
        int32 RuleSet = INDEX_NONE;
        for (int32 i = 0; i < Index.Num(); ++i) {
            FString Name = Index[i]->AsString();
            Name.ReplaceInline(TEXT("_"), TEXT(" "));
            if (Name == Function || Index[i]->AsString() == Function) RuleSet = i;
        }
        if (RuleSet == INDEX_NONE) { AddError(TEXT("Unknown source event function")); continue; }
        FRecoveredEventRecord Event;
        Event.EventName = Inputs->GetNumberField(TEXT("SpecialEventInput.EventName"));
        Event.BaseWeight = Inputs->GetNumberField(TEXT("SpecialEventInput.BaseWeight"));
        FRecoveredEventRecord Expected;
        const TSharedPtr<FJsonObject>* Output;
        if (Writes->TryGetObjectField(TEXT("SpecialEventModified"), Output)) {
            Expected.EventName = (*Output)->GetNumberField(TEXT("EventName"));
            Expected.BaseWeight = (*Output)->GetNumberField(TEXT("BaseWeight"));
        }
        const auto Actual = URecoveredEventRuleLibrary::AdjustEventWeight(Event, RuleSet);
        const FString Label = FString::Printf(TEXT("Weight fixture %d %s"), Count, *Function);
        TestEqual(Label + TEXT(" identity"), Actual.EventName, Expected.EventName);
        TestEqual(Label + TEXT(" weight"), Actual.BaseWeight, Expected.BaseWeight);
        ++Count;
    }
    TestEqual(TEXT("All event cases covered"), Count, 2016);
    TArray<FRecoveredEventRecord> Events;
    FRecoveredEventRecord First; First.BaseWeight = 10; First.WeightMultiplier = 999;
    FRecoveredEventRecord Second; Second.BaseWeight = 20; Second.IsEligible = false;
    Events.Add(First); Events.Add(Second);
    TestEqual(TEXT("Selector sums base weights without multiplier"), URecoveredEventRuleLibrary::GetTotalWeight(Events), 30.0);
    TestEqual(TEXT("Zero roll selects first"), URecoveredEventRuleLibrary::ChooseEventAtRoll(Events, 0), 0);
    TestEqual(TEXT("Boundary roll advances to next"), URecoveredEventRuleLibrary::ChooseEventAtRoll(Events, 10), 1);
    TestEqual(TEXT("Inclusive random upper bound can produce no selection"), URecoveredEventRuleLibrary::ChooseEventAtRoll(Events, 30), INDEX_NONE);
    TestEqual(TEXT("Empty list does not invent selection"), URecoveredEventRuleLibrary::ChooseEventAtRoll({}, 0), INDEX_NONE);
    TestEqual(TEXT("Heat 30 first range wins"), URecoveredEventRuleLibrary::RefreshHeatCategory(30, 0), static_cast<uint8>(2));
    TestEqual(TEXT("Heat 70 second range wins"), URecoveredEventRuleLibrary::RefreshHeatCategory(70, 0), static_cast<uint8>(1));
    TestEqual(TEXT("Invalid heat retains previous"), URecoveredEventRuleLibrary::RefreshHeatCategory(-1, 7), static_cast<uint8>(7));
    return true;
}
#endif
