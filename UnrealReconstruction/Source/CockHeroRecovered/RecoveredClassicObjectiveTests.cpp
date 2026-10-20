#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "TimerManager.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredClassicThresholdTest,"CockHero.Recovery.ClassicObjectiveThresholds",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredClassicThresholdTest::RunTest(const FString& Parameters) {
    const TArray<uint8> Expected={0,1,2,3,6,7,8};
    TestEqual(TEXT("Source exposes seven Classic objectives"),RecoveredObjectives::GetSpecs().Num(),Expected.Num());
    FRecoveredPlayerVariables Player; FRecoveredSessionStats Stats;
    for (int32 Index=0;Index<Expected.Num();++Index) {
        TestEqual(TEXT("Customization index preserves source objective enum"),RecoveredObjectives::GetSpecs()[Index].Objective,Expected[Index]);
        FRecoveredObjectiveRuntime State;State.bActive=true;State.Objective=Expected[Index];State.Target=10;
        State.BaselineDuration=20;State.BaselineStrokes=20;State.BaselineEdges=20;State.BaselineMilking=20;State.BaselineSuccubi=20;
        Player.SessionLength=29;Stats.Strokes=29;Stats.Edges=29;Stats.MilkingCount=29;Stats.SuccubiDefeated=29;
        TestFalse(TEXT("One below target does not complete"),RecoveredObjectives::IsComplete(State,Player,Stats,.99));
        Player.SessionLength=30;Stats.Strokes=30;Stats.Edges=30;Stats.MilkingCount=30;Stats.SuccubiDefeated=30;
        if (State.Objective==6) TestTrue(TEXT("Prejac deadline expires at authored limit"),RecoveredObjectives::IsPrejacExpired(State,Player));
        else TestTrue(TEXT("Exact target completes each source objective"),RecoveredObjectives::IsComplete(State,Player,Stats,1));
        double Meter=1;
        if (State.Objective==0 || State.Objective==1 || State.Objective==2 || State.Objective==3 || State.Objective==8) {
            TestTrue(TEXT("Default missed-window policy resets objective"),RecoveredObjectives::ResetAfterMiss(State,true,Meter));
            TestFalse(TEXT("Reset requires a fresh target"),RecoveredObjectives::IsComplete(State,Player,Stats,Meter));
        }
        if (State.Objective==2 || State.Objective==8) TestFalse(TEXT("Disabled reset reaches source EndSession"),RecoveredObjectives::ResetAfterMiss(State,false,Meter));
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredClassicMeterWindowTest,"CockHero.Recovery.ClassicMeterReleaseWindow",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredClassicMeterWindowTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    if (!TestNotNull(TEXT("Isolated Classic world"),World)) return false;
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { GEngine->DestroyWorldContext(World);World->DestroyWorld(false); };
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Classic consumer"),Manager)) return false;
    Manager->InitializeRecoveredClassicObjective();Manager->CumMeterPercentage=1;
    Manager->TriggerMeterOverride();
    TestTrue(TEXT("Actual meter producer opens release permission"),Manager->PlayerVariables.bIsAllowedToCum);
    TestEqual(TEXT("One real window metric"),Manager->SessionStats.CumWindowsHit,1);
    Manager->TriggerMeterOverride();TestEqual(TEXT("Repeated producer does not reopen window"),Manager->SessionStats.CumWindowsHit,1);
    World->GetTimerManager().Tick(0.f);
    ++GFrameCounter;
    World->GetTimerManager().Tick(60.1f);
    TestFalse(TEXT("Expiry revokes permission"),Manager->PlayerVariables.bIsAllowedToCum);
    TestEqual(TEXT("Source meter expiry resets meter"),Manager->CumMeterPercentage,0.0);
    TestEqual(TEXT("Expiry records missed window"),Manager->SessionStats.MissedCumWindows,1);
    Manager->CumMeterPercentage=1;Manager->TriggerMeterOverride();Manager->ResetRecoveredObjectiveRuntime();
    TestFalse(TEXT("Return/reset clears release timer"),World->GetTimerManager().IsTimerActive(Manager->ObjectiveReleaseTimer));
    Manager->PlayerVariables=FRecoveredPlayerVariables();Manager->SessionStats=FRecoveredSessionStats();
    Manager->ClassicObjectiveRuntime.bActive=true;Manager->ClassicObjectiveRuntime.Objective=6;Manager->ClassicObjectiveRuntime.Target=30;Manager->CurrentSessionObjective=6;
    Manager->PlayerVariables.SessionLength=30;Manager->ResolveRecoveredClimaxRequest();
    TestTrue(TEXT("Prejac confirmation at deadline wins"),Manager->PlayerVariables.bHasCame);
    Manager->PlayerVariables=FRecoveredPlayerVariables();Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables.SessionLength=31;Manager->ResolveRecoveredClimaxRequest();
    TestTrue(TEXT("Prejac after deadline records early loss"),Manager->SessionStats.EarlyClimax>0);
    Manager->PlayerVariables=FRecoveredPlayerVariables();Manager->SessionStats=FRecoveredSessionStats();
    Manager->ClassicObjectiveRuntime.Objective=7;Manager->ClassicObjectiveRuntime.Target=2;Manager->CurrentSessionObjective=7;
    Manager->RecordRecoveredMilking();TestFalse(TEXT("Tribute waits for full target"),Manager->PlayerVariables.bHasCame);
    Manager->RecordRecoveredMilking();TestTrue(TEXT("Real Tribute producer completes exact target"),Manager->PlayerVariables.bHasCame);
    return true;
}
#endif
