#include "RecoveredChallengeTracker.h"
#include "Misc/AutomationTest.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS
namespace {
FRecoveredChallengeRow MigrationRow(const FString& ID, const FString& Scope, const FString& Metric) {
    FRecoveredChallengeRow Row;
    Row.ChallengeID=ID;Row.Scope=Scope;Row.XPReward=25;
    FRecoveredRequirement Requirement;
    Requirement.MetricType=Metric;Requirement.ComparisonType=TEXT("EComparisonType::GreaterOrEqual");Requirement.TargetValue=5;
    Row.Requirements.Add(Requirement);
    return Row;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredChallengeMigrationTest,"CockHero.Recovery.ChallengeDefinitionMigration",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredChallengeMigrationTest::RunTest(const FString& Parameters) {
    auto* Tracker=NewObject<URecoveredChallengeTracker>();
    auto* Table=NewObject<UDataTable>();Table->RowStruct=FRecoveredChallengeRow::StaticStruct();Tracker->ChallengeTable=Table;
    FRecoveredChallengeRow Stable=MigrationRow(TEXT("stable"),TEXT("Lifetime"),TEXT("EMetricType::Strokes"));
    FRecoveredChallengeRow Changed=MigrationRow(TEXT("speed_freak"),TEXT("Lifetime"),TEXT("EMetricType::SessionsWon"));
    FRecoveredCondition Modifier;Modifier.ConditionType=TEXT("EChallengeConditionType::ModifierActive");Modifier.ConditionValue=TEXT("insanemode");Changed.Conditions.Add(Modifier);
    FRecoveredChallengeRow Moved=MigrationRow(TEXT("built_different"),TEXT("Session"),TEXT("EMetricType::SessionsWon"));
    FRecoveredChallengeRow Retired=MigrationRow(TEXT("retired"),TEXT("Lifetime"),TEXT("EMetricType::Strokes"));
    Table->AddRow(TEXT("stable"),Stable);Table->AddRow(TEXT("speed_freak"),Changed);Table->AddRow(TEXT("built_different"),Moved);Table->AddRow(TEXT("retired"),Retired);
    if (!TestTrue(TEXT("Initial definitions"),Tracker->InitializeChallenges())) return false;
    Tracker->LifetimeProgress[TEXT("stable")].Requirements[0].CurrentValue=3;
    Tracker->LifetimeProgress[TEXT("stable")].BestValues[0]=4;
    Tracker->LifetimeProgress[TEXT("speed_freak")].Requirements[0].CurrentValue=4;
    Tracker->LifetimeProgress[TEXT("speed_freak")].BestValues[0]=4;
    Tracker->LifetimeProgress[TEXT("retired")].Requirements[0].CurrentValue=2;
    Tracker->TrackedChallenges={TEXT("stable"),TEXT("speed_freak"),TEXT("retired")};
    auto& OldCompleted=Tracker->SessionProgress[TEXT("built_different")];
    OldCompleted.bCompleted=true;OldCompleted.bRewardsClaimed=true;OldCompleted.CompletionTime=12.0f;
    Tracker->CompletedChallenges.Add(TEXT("built_different"));
    const FString Before=Tracker->ExportRecoveryState();
    auto* Restored=NewObject<URecoveredChallengeTracker>();Restored->ChallengeTable=Table;
    if (!TestTrue(TEXT("Definition provenance serializes"),Restored->ImportRecoveryState(Before))) return false;
    TestEqual(TEXT("Provenance round trip"),Restored->LifetimeProgress[TEXT("stable")].DefinitionContext,Tracker->LifetimeProgress[TEXT("stable")].DefinitionContext);

    Changed.Requirements[0].MetricType=TEXT("EMetricType::SessionsWonAtMaxDifficulty");Changed.Conditions.Reset();
    Moved.Scope=TEXT("Lifetime");Moved.Requirements[0].MetricType=TEXT("EMetricType::SessionsWonAtMaxDifficulty");
    Table->AddRow(TEXT("speed_freak"),Changed);Table->AddRow(TEXT("built_different"),Moved);Table->RemoveRow(TEXT("retired"));
    Table->AddRow(TEXT("added"),MigrationRow(TEXT("added"),TEXT("Session"),TEXT("EMetricType::Strokes")));
    if (!TestTrue(TEXT("Reconcile changed definitions"),Restored->InitializeChallenges())) return false;
    TestEqual(TEXT("Unchanged requirements retain current value"),Restored->LifetimeProgress[TEXT("stable")].Requirements[0].CurrentValue,3);
    TestEqual(TEXT("Unchanged requirements retain best value"),Restored->LifetimeProgress[TEXT("stable")].BestValues[0],4);
    TestEqual(TEXT("Changed metric replaces stale requirement"),Restored->LifetimeProgress[TEXT("speed_freak")].Requirements[0].MetricType,Changed.Requirements[0].MetricType);
    TestEqual(TEXT("Unrelated progress is not credited to new requirement"),Restored->LifetimeProgress[TEXT("speed_freak")].Requirements[0].CurrentValue,0);
    TestTrue(TEXT("Scope move removes obsolete active entry"),!Restored->SessionProgress.Contains(TEXT("built_different")));
    const auto* Current=Restored->LifetimeProgress.Find(TEXT("built_different"));
    if (!TestNotNull(TEXT("Scope move creates lifetime entry"),Current)) return false;
    TestTrue(TEXT("Completed status survives scope move"),Current->bCompleted);
    TestTrue(TEXT("Claim flag survives scope move"),Current->bRewardsClaimed);
    TestEqual(TEXT("Original completion timestamp survives"),Current->CompletionTime,12.0f);
    TestTrue(TEXT("Scope move does not allow another reward"),Restored->ClaimChallengeRewards(TEXT("built_different")).IsEmpty());
    TestEqual(TEXT("Added row begins at zero"),Restored->SessionProgress[TEXT("added")].Requirements[0].CurrentValue,0);
    TestEqual(TEXT("Retired progress retained"),Restored->LifetimeProgress[TEXT("retired")].Requirements[0].CurrentValue,2);
    TestTrue(TEXT("Retired definition is archived"),Restored->LifetimeProgress[TEXT("retired")].bDefinitionArchived);
    TestFalse(TEXT("Retired definition leaves active tracking"),Restored->TrackedChallenges.Contains(TEXT("retired")));
    TestTrue(TEXT("Unchanged definition stays tracked"),Restored->TrackedChallenges.Contains(TEXT("stable")));
    const FString Migrated=Restored->ExportRecoveryState();
    auto* Again=NewObject<URecoveredChallengeTracker>();Again->ChallengeTable=Table;
    TestTrue(TEXT("Migrated state reloads"),Again->ImportRecoveryState(Migrated));
    TestTrue(TEXT("Migration is repeatable"),Again->InitializeChallenges());
    TestEqual(TEXT("Repeated migration preserves current value"),Again->LifetimeProgress[TEXT("stable")].Requirements[0].CurrentValue,3);
    TestTrue(TEXT("Repeated migration prevents duplicate rewards"),Again->ClaimChallengeRewards(TEXT("built_different")).IsEmpty());
    Table->AddRow(TEXT("retired"),Retired);
    TestTrue(TEXT("Restored old definition can rejoin active catalog"),Again->InitializeChallenges());
    TestEqual(TEXT("Restored definition recovers old progress"),Again->LifetimeProgress[TEXT("retired")].Requirements[0].CurrentValue,2);
    TestTrue(TEXT("Restored definition recovers tracking intent"),Again->TrackedChallenges.Contains(TEXT("retired")));
    TestFalse(TEXT("Restored definition is no longer archived"),Again->LifetimeProgress[TEXT("retired")].bDefinitionArchived);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredLegacyChallengeMigrationTest,"CockHero.Recovery.LegacyChallengeDefinitionMigration",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredLegacyChallengeMigrationTest::RunTest(const FString& Parameters) {
    auto* Baseline=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    if (!TestNotNull(TEXT("Retained baseline definitions"),Baseline)) return false;
    auto* Tracker=NewObject<URecoveredChallengeTracker>();Tracker->ChallengeTable=Baseline;
    if (!TestTrue(TEXT("Initialize retained baseline"),Tracker->InitializeChallenges())) return false;
    const FName ID(TEXT("speed_freak"));
    auto* Progress=Tracker->LifetimeProgress.Find(ID);if (!Progress) Progress=Tracker->SessionProgress.Find(ID);
    if (!TestNotNull(TEXT("Existing changed challenge identity"),Progress) || Progress->Requirements.IsEmpty()) return false;
    Progress->Requirements[0].CurrentValue=4;Progress->BestValues[0]=4;
    TSharedPtr<FJsonObject> Stored;
    if (!TestTrue(TEXT("Read exported recovery state"),FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Tracker->ExportRecoveryState()),Stored))) return false;
    for (const TCHAR* Field:{TEXT("sessionProgress"),TEXT("lifetimeProgress")}) {
        for (const auto& Pair:Stored->GetObjectField(Field)->Values) {
            auto Object=Pair.Value->AsObject();
            Object->RemoveField(TEXT("definitionContext"));Object->RemoveField(TEXT("bDefinitionArchived"));Object->RemoveField(TEXT("bWasTrackedWhenArchived"));
        }
    }
    FString LegacyJson;FJsonSerializer::Serialize(Stored.ToSharedRef(),TJsonWriterFactory<>::Create(&LegacyJson));
    auto* Loaded=NewObject<URecoveredChallengeTracker>();Loaded->ChallengeTable=Baseline;
    if (!TestTrue(TEXT("Version-one saves without provenance remain readable"),Loaded->ImportRecoveryState(LegacyJson))) return false;
    if (!TestTrue(TEXT("Reconcile against retained baseline provenance"),Loaded->InitializeChallenges())) return false;
    Progress=Loaded->LifetimeProgress.Find(ID);if (!Progress) Progress=Loaded->SessionProgress.Find(ID);
    if (!TestNotNull(TEXT("Legacy progress remains"),Progress)) return false;
    TestEqual(TEXT("Unchanged legacy progress is preserved"),Progress->Requirements[0].CurrentValue,4);
    TestEqual(TEXT("Unchanged legacy best value is preserved"),Progress->BestValues[0],4);
    TestFalse(TEXT("Legacy provenance is recovered from baseline"),Progress->DefinitionContext.IsEmpty());
    return true;
}
#endif
