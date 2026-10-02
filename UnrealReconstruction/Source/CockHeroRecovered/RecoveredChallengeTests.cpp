#include "RecoveredChallengeRules.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredChallengePredicateTest,"CockHero.Recovery.NativeChallengePredicates",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredChallengePredicateTest::RunTest(const FString& Parameters) {
    FString Text; TSharedPtr<FJsonObject> Evidence;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/challenge-predicate-traces.json"))) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) { AddError(TEXT("Missing native challenge evidence"));return false; }
    int32 Count=0;
    for(const auto& Value:Evidence->GetArrayField(TEXT("requirements"))) {
        const auto Fixture=Value->AsObject(); TArray<FRecoveredRequirement> Requirements;
        const auto& Progress=Fixture->GetArrayField(TEXT("progress"));
        for(const auto& Entry:Fixture->GetArrayField(TEXT("requirements"))) {
            const auto Row=Entry->AsObject(); FRecoveredRequirement Requirement;
            Requirement.MetricType=Row->GetStringField(TEXT("MetricType"));
            Requirement.ComparisonType=Row->GetStringField(TEXT("ComparisonType"));
            Requirement.CurrentValue=int32(Row->GetNumberField(TEXT("CurrentValue")));
            Requirement.TargetValue=int32(Row->GetNumberField(TEXT("TargetValue")));
            TestEqual(TEXT("Native signed progress display"),URecoveredChallengeRules::GetRequirementProgressPercent(Requirement),float(Progress[Requirements.Num()]->AsNumber()));
            Requirements.Add(Requirement);
        }
        TestEqual(TEXT("Native all-requirement predicate"),URecoveredChallengeRules::AreAllRequirementsMet(Requirements),Fixture->GetBoolField(TEXT("expected_met")));
        ++Count;
    }
    for(const auto& Value:Evidence->GetArrayField(TEXT("conditions"))) {
        const auto Fixture=Value->AsObject(); TArray<FRecoveredCondition> Conditions; TArray<FString> Modifiers;
        for(const auto& Entry:Fixture->GetArrayField(TEXT("conditions"))) {
            FRecoveredCondition Condition;
            Condition.ConditionType=Entry->AsObject()->GetStringField(TEXT("ConditionType"));
            Condition.ConditionValue=Entry->AsObject()->GetStringField(TEXT("ConditionValue"));
            Conditions.Add(Condition);
        }
        for(const auto& Entry:Fixture->GetArrayField(TEXT("active_modifiers"))) Modifiers.Add(Entry->AsString());
        TestEqual(TEXT("Native challenge condition gates"),URecoveredChallengeRules::CheckChallengeConditions(Conditions,Modifiers,int32(Fixture->GetNumberField(TEXT("items_used"))),int32(Fixture->GetNumberField(TEXT("duration")))),Fixture->GetBoolField(TEXT("expected_met")));
        ++Count;
    }
    TestEqual(TEXT("Native challenge cases"),Count,1101);
    return true;
}
#endif
