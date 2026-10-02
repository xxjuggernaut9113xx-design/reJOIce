#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS
#include "RecoveredChallengeTracker.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredChallengeTrackingTest,"CockHero.Recovery.NativeChallengeTrackingAndClaims",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredChallengeTrackingTest::RunTest(const FString& Parameters) {
    auto* Tracker=NewObject<URecoveredChallengeTracker>();
    auto* Table=NewObject<UDataTable>();Table->RowStruct=FRecoveredChallengeRow::StaticStruct();Tracker->ChallengeTable=Table;
    auto* Manager=NewObject<URecoveredProgressionManager>();Tracker->RewardManager=Manager;
    FRecoveredChallengeRow Row;Row.ChallengeID=TEXT("session_strokes");Row.Scope=TEXT("EChallengeScope::Session");Row.XPReward=25;Row.UnlockPointsReward=3;
    FRecoveredRequirement Requirement;Requirement.MetricType=TEXT("EMetricType::Strokes");Requirement.ComparisonType=TEXT("EComparisonType::GreaterOrEqual");Requirement.TargetValue=10;Row.Requirements.Add(Requirement);
    Table->AddRow(TEXT("UnrelatedSessionRowName"),Row);
    Row.ChallengeID=TEXT("lifetime_strokes");Row.Scope=TEXT("EChallengeScope::Lifetime");Row.Requirements[0].TargetValue=15;Table->AddRow(TEXT("UnrelatedLifetimeRowName"),Row);
    TestTrue(TEXT("Initialize native challenge maps"),Tracker->InitializeChallenges());
    TestEqual(TEXT("Session scope uses session map"),Tracker->SessionProgress.Num(),1);
    TestEqual(TEXT("Lifetime scope uses lifetime map"),Tracker->LifetimeProgress.Num(),1);
    TestTrue(TEXT("Unfinished challenge cannot be claimed"),Tracker->ClaimChallengeRewards(TEXT("session_strokes")).IsEmpty());
    FRecoveredSessionStats Stats;Stats.Strokes=10;Tracker->TrackedChallenges.Add(TEXT("session_strokes"));
    Tracker->UpdateChallengeProgress(TEXT("session_strokes"),ERecoveredMetric::Strokes,1,Stats,0,2.5f);
    auto* SessionPointer=Tracker->SessionProgress.Find(TEXT("session_strokes"));
    if (!TestNotNull(TEXT("Session progress exists after initialization"),SessionPointer)) return false;
    auto& Session=*SessionPointer;
    TestEqual(TEXT("Session uses current stats instead of adding passed delta"),Session.Requirements[0].CurrentValue,10);
    TestTrue(TEXT("Meeting requirements completes challenge"),Session.bCompleted);
    TestEqual(TEXT("Source completion timestamp"),Session.CompletionTime,2.5f);
    TestFalse(TEXT("Completed tracker is removed"),Tracker->TrackedChallenges.Contains(TEXT("session_strokes")));
    TestEqual(TEXT("Legacy rewards synthesized when typed list is empty"),Tracker->ClaimChallengeRewards(TEXT("session_strokes")).Num(),2);
    TestEqual(TEXT("Claim grants native XP"),Manager->TotalXPEarned,25);
    TestEqual(TEXT("Claim grants native points"),Manager->UnlockPoints,3);
    TestTrue(TEXT("Duplicate claim returns empty"),Tracker->ClaimChallengeRewards(TEXT("session_strokes")).IsEmpty());
    Tracker->UpdateChallengeProgress(TEXT("lifetime_strokes"),ERecoveredMetric::Strokes,5,Stats,0,3);
    Tracker->UpdateChallengeProgress(TEXT("lifetime_strokes"),ERecoveredMetric::Strokes,7,Stats,0,4);
    auto* LifetimePointer=Tracker->LifetimeProgress.Find(TEXT("lifetime_strokes"));
    if (!TestNotNull(TEXT("Lifetime progress exists after initialization"),LifetimePointer)) return false;
    auto& Lifetime=*LifetimePointer;
    TestEqual(TEXT("Lifetime accumulates deltas"),Lifetime.Requirements[0].CurrentValue,12);
    TestFalse(TEXT("Lifetime below target remains active"),Lifetime.bCompleted);
    Tracker->UpdateChallengeProgress(TEXT("lifetime_strokes"),ERecoveredMetric::Strokes,-4,Stats,0,5);
    TestEqual(TEXT("Best progress retains previous maximum"),Lifetime.BestValues[0],12);
    TestTrue(TEXT("Reinitialization preserves progress"),Tracker->InitializeChallenges());
    TestEqual(TEXT("Existing requirement values retained"),Tracker->LifetimeProgress[TEXT("lifetime_strokes")].Requirements[0].CurrentValue,8);
    TestEqual(TEXT("Existing best values retained"),Tracker->LifetimeProgress[TEXT("lifetime_strokes")].BestValues[0],12);
    const FString State=Tracker->ExportRecoveryState();
    auto* Reloaded=NewObject<URecoveredChallengeTracker>();Reloaded->ChallengeTable=Table;Reloaded->RewardManager=Manager;
    if (!TestTrue(TEXT("Challenge state round trip"),Reloaded->ImportRecoveryState(State))) { AddInfo(State);return false; }
    if (!TestNotNull(TEXT("Round trip lifetime entry"),Reloaded->LifetimeProgress.Find(TEXT("lifetime_strokes"))) || !TestNotNull(TEXT("Round trip session entry"),Reloaded->SessionProgress.Find(TEXT("session_strokes")))) { AddInfo(State);AddInfo(Reloaded->ExportRecoveryState());return false; }
    TestEqual(TEXT("Challenge requirements persist"),Reloaded->LifetimeProgress[TEXT("lifetime_strokes")].Requirements[0].CurrentValue,8);
    TestTrue(TEXT("Claimed flag persists"),Reloaded->SessionProgress[TEXT("session_strokes")].bRewardsClaimed);
    TestTrue(TEXT("Reload prevents a duplicate reward grant"),Reloaded->ClaimChallengeRewards(TEXT("session_strokes")).IsEmpty());
    TestFalse(TEXT("Incomplete challenge JSON rejected"),Reloaded->ImportRecoveryState(TEXT("{\"version\":1}")));
    TestEqual(TEXT("Rejected state leaves values untouched"),Reloaded->ExportRecoveryState(),State);
    Reloaded->StartNewSession();
    TestEqual(TEXT("Completed session requirements remain intact"),Reloaded->SessionProgress[TEXT("session_strokes")].Requirements[0].CurrentValue,10);
    TestEqual(TEXT("Lifetime progress survives new session"),Reloaded->LifetimeProgress[TEXT("lifetime_strokes")].Requirements[0].CurrentValue,8);
    Tracker->ChallengeTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    if (TestNotNull(TEXT("Source challenge definitions"),Tracker->ChallengeTable.Get())) {
        auto* SourceTracker=NewObject<URecoveredChallengeTracker>();SourceTracker->ChallengeTable=Tracker->ChallengeTable;
        TestTrue(TEXT("Initialize all source challenge definitions"),SourceTracker->InitializeChallenges());
        TestEqual(TEXT("All 55 source rows assigned to maps"),SourceTracker->SessionProgress.Num()+SourceTracker->LifetimeProgress.Num(),55);
    }
    return true;
}
#endif
