#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "TimerManager.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTowerWindowTest, "CockHero.Recovery.TowerFinalReleaseWindow", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredTowerWindowTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false);
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false, NAME_None, nullptr, true, ERHIFeatureLevel::Num, &Initialization);
    if (!TestNotNull(TEXT("Create isolated final-round world"), World)) return false;
    FWorldContext& Context = GEngine->CreateNewWorldContext(EWorldType::Game); Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { GEngine->DestroyWorldContext(World); World->DestroyWorld(false); };
    auto* Manager = World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Spawn final-round consumer"), Manager)) return false;
    auto* Tower = Manager->TowerRuntime.Get();
    Manager->ActiveRecoveredMode = 1; Tower->CurrentRound = Tower->TotalRounds = 1;
    Tower->Phase = ERecoveredRoundPhase::BossRound; Tower->SelectedOption.Objective = 2; Tower->SelectedOption.ObjectiveParam = 10;
    Manager->SessionStats.Strokes = 10;
    Manager->TickPlaylistAudio();
    TestEqual(TEXT("Meeting final stroke target does not bypass actual confirmation"), Tower->Phase, ERecoveredRoundPhase::BossRound);
    TestTrue(TEXT("Final target grants permission"), Manager->PlayerVariables.bIsAllowedToCum);
    TestEqual(TEXT("Native start-window metric emitted once"), Manager->SessionStats.CumWindowsHit, 1);
    Manager->TickPlaylistAudio();
    TestEqual(TEXT("Repeated ready tick does not create a second window"), Manager->SessionStats.CumWindowsHit, 1);
    World->GetTimerManager().Tick(0.f);
    ++GFrameCounter;
    World->GetTimerManager().Tick(60.1f);
    TestFalse(TEXT("Window expiry revokes permission"), Manager->PlayerVariables.bIsAllowedToCum);
    TestEqual(TEXT("Source default reset policy keeps final round live"), Tower->Phase, ERecoveredRoundPhase::BossRound);
    TestEqual(TEXT("Source reset requires another original-sized stroke objective"), Tower->BaselineStrokes, 10);
    TestEqual(TEXT("Expiry records one missed window"), Manager->SessionStats.MissedCumWindows, 1);
    Manager->SessionStats.Strokes = 20; Manager->TickPlaylistAudio();
    TestTrue(TEXT("Completing reset target opens a fresh window"), Manager->PlayerVariables.bIsAllowedToCum);
    TestEqual(TEXT("Reset target produces second real window"), Manager->SessionStats.CumWindowsHit, 2);
    Manager->StopRecoveredModes();
    return true;
}
#endif
