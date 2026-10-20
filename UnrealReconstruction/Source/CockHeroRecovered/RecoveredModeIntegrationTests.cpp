#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredModeIntegrationTest,"CockHero.Recovery.ModeActorIntegration",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredModeIntegrationTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    if (!TestNotNull(TEXT("Isolated runtime world"),World)) return false;
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { GEngine->DestroyWorldContext(World);World->DestroyWorld(false); };
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Spawn live recovered manager"),Manager)) return false;
    if (!TestNotNull(TEXT("Playlist component survives actor instancing"),Manager->PlaylistRuntime.Get()) || !TestNotNull(TEXT("Tower component survives actor instancing"),Manager->TowerRuntime.Get())) return false;
    FRecoveredBeatmapEvent Event;
    Event.Type=TEXT("disable_break");Event.Value=TEXT("START");
    Manager->PlayerVariables.bCanUseItems=true;
    Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Event);
    TestFalse(TEXT("Live playlist event reaches manager item gate"),Manager->PlayerVariables.bCanUseItems);
    Event.Value=TEXT("end");Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Event);
    TestTrue(TEXT("Break end restores manager item gate"),Manager->PlayerVariables.bCanUseItems);
    Event.Type=TEXT("media_change");Event.Value=TEXT("FAST");
    Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Event);
    TestEqual(TEXT("Live playlist category reaches presentation state"),Manager->BeatContext.CardType,uint8(2));
    Manager->PlaylistRuntime->OnSongComplete.Broadcast(3);
    TestEqual(TEXT("Live playlist completion records best rounds"),Manager->SessionStats.BestMusicModeWinRounds,3);
    Manager->PlaylistRuntime->OnSongComplete.Broadcast(2);
    TestEqual(TEXT("Smaller completion cannot lower peak"),Manager->SessionStats.BestMusicModeWinRounds,3);
    Manager->CurrentDifficulty=ERecoveredDifficulty::InsaneMode;
    Manager->SuccessfulCum();
    TestEqual(TEXT("Source difficulty two records verified maximum-difficulty win"),Manager->SessionStats.SessionsWonAtMaxDifficulty,1);
    Manager->PlayerVariables.bHasCame=false;
    Manager->CurrentSessionObjective=7;
    Manager->BeatContext.ActiveModifiers={TEXT("Deal With The Devil")};
    Manager->BeatContext.CardType=0;
    Manager->RecordRecoveredMilking();
    TestEqual(TEXT("Devil modifier blocks tribute outside succubus media"),Manager->SessionStats.MilkingCount,0);
    Manager->BeatContext.CardType=3;
    Manager->RecordRecoveredMilking();
    TestEqual(TEXT("Succubus tribute produces native metric 36"),Manager->SessionStats.MilkingCount,1);
    Manager->BeatContext.ActiveModifiers.Reset();
    Manager->BeatContext.CardType=0;
    Manager->RecordRecoveredMilking();
    TestEqual(TEXT("Unmodified tribute accepts ordinary media"),Manager->SessionStats.MilkingCount,2);
    Manager->ActiveRecoveredMode=2;
    Manager->PlayerVariables.bCanUseItems=true;
    Manager->PrematureCum();
    TestEqual(TEXT("Native music loss path records metric 45 after disabling items"),Manager->SessionStats.DisabledBreakSectionFailures,1);
    Manager->CurrentSessionObjective=0;
    Manager->ActiveRecoveredMode=0;
    Manager->PlayerVariables.bHasCame=false;
    Manager->PlayerVariables.bIsAllowedToCum=true;
    Manager->BeatContext.CardType=0;
    const int32 WinsBefore=Manager->SessionStats.SessionsWon;
    Manager->ResolveRecoveredClimaxRequest();
    TestEqual(TEXT("Authorized user climax routes to the actual success outcome"),Manager->SessionStats.SessionsWon,WinsBefore+1);
    Manager->ResolveRecoveredClimaxRequest();
    TestEqual(TEXT("Repeated user climax cannot award a second outcome"),Manager->SessionStats.SessionsWon,WinsBefore+1);
    Manager->PlayerVariables.bHasCame=false;
    Manager->PlayerVariables.bIsAllowedToCum=false;
    Manager->BeatContext.CardType=0;
    const int32 LossesBefore=Manager->SessionStats.EarlyClimax;
    Manager->ResolveRecoveredClimaxRequest();
    TestEqual(TEXT("Unauthorized user climax routes to the failure outcome"),Manager->SessionStats.EarlyClimax,LossesBefore+1);
    Manager->StopRecoveredModes();
    TestFalse(TEXT("Mode stop terminates playlist clock"),Manager->PlaylistRuntime->bPlaying);
    TestEqual(TEXT("Mode stop returns tower to inactive"),Manager->TowerRuntime->Phase,ERecoveredRoundPhase::Inactive);
    return true;
}
#endif
