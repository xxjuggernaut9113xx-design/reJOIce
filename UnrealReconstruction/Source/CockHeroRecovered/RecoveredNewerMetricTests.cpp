#include "RecoveredGameplay.h"
#include "RecoveredChallengeTracker.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerMetricTest,"CockHero.Recovery.NewerMetrics.SessionAndLifetimeDispatch",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerMetricTest::RunTest(const FString& Parameters) {
    const TCHAR* Names[]={TEXT("DefensiveItemsUsed"),TEXT("OffensiveItemsUsed"),TEXT("DeclinedTemptation"),TEXT("BountiesCollected"),TEXT("LootRushesUsed"),TEXT("EscapeRopesUsed"),TEXT("MilkingCount"),TEXT("SuccuSlayerSessionsWon"),TEXT("EdgeSessionsWon"),TEXT("ComboCrunchersUsed"),TEXT("SuccuCoinsSpent"),TEXT("SessionsWonAtMaxDifficulty"),TEXT("BestMusicModeWinRounds"),TEXT("BestTowerWinRounds"),TEXT("MusicBreaksUsed"),TEXT("DisabledBreakSectionFailures"),TEXT("BountyCollectionFailures")};
    for (int32 Index=0;Index<UE_ARRAY_COUNT(Names);++Index) {
        const auto Metric=static_cast<ERecoveredMetric>(30+Index);
        TestEqual(TEXT("Newer native enum value retained"),StaticEnum<ERecoveredMetric>()->GetNameStringByValue(30+Index),FString(Names[Index]));
        FRecoveredSessionStats Stats;
        auto* Tracker=NewObject<URecoveredChallengeTracker>();
        auto* Table=NewObject<UDataTable>();
        Table->RowStruct=FRecoveredChallengeRow::StaticStruct();
        Tracker->ChallengeTable=Table;
        for (const TCHAR* Scope:{TEXT("Session"),TEXT("Lifetime")}) {
            FRecoveredChallengeRow Row;
            Row.ChallengeID=Scope;Row.Scope=Scope;
            FRecoveredRequirement Requirement;
            Requirement.MetricType=FString(TEXT("EMetricType::"))+Names[Index];
            Requirement.ComparisonType=TEXT("EComparisonType::GreaterOrEqual");
            Requirement.TargetValue=100;
            Row.Requirements.Add(Requirement);
            Table->AddRow(FName(Scope),Row);
        }
        if (!TestTrue(TEXT("Initialize both metric scopes"),Tracker->InitializeChallenges())) return false;
        for (int32 Amount:{2,3}) {
            URecoveredStateRuleLibrary::RecordSessionMetric(Stats,Metric,Amount);
            Tracker->UpdateMetricWithConditions(Metric,Amount,Stats,{},0,0);
        }
        const bool bMaximum=Metric==ERecoveredMetric::BestMusicModeWinRounds || Metric==ERecoveredMetric::BestTowerWinRounds;
        const int32 Expected=bMaximum ? 3 : 5;
        TestEqual(TEXT("Session challenge reads updated session field"),Tracker->SessionProgress[TEXT("Session")].Requirements[0].CurrentValue,Expected);
        TestEqual(TEXT("Lifetime challenge uses counter or peak semantics"),Tracker->LifetimeProgress[TEXT("Lifetime")].Requirements[0].CurrentValue,Expected);
        const FString Saved=Tracker->ExportRecoveryState();
        auto* Reloaded=NewObject<URecoveredChallengeTracker>();Reloaded->ChallengeTable=Table;
        TestTrue(TEXT("Newer metric counters persist"),Reloaded->ImportRecoveryState(Saved));
        TestTrue(TEXT("Newer metric definitions reconcile"),Reloaded->InitializeChallenges());
        TestEqual(TEXT("Newer lifetime progress survives reload"),Reloaded->LifetimeProgress[TEXT("Lifetime")].Requirements[0].CurrentValue,Expected);
    }
    return true;
}
#endif
