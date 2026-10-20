#include "RecoveredPlaylistRuntime.h"
#include "RecoveredTowerRuntime.h"
#include "RecoveredRules.h"
#include "RecoveredMusicUpgrades.h"
#include "Misc/AutomationTest.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPlaylistTimingTest, "CockHero.Recovery.PlaylistAuthoredTiming", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredPlaylistTimingTest::RunTest(const FString& Parameters) {
    auto* Runtime = NewObject<URecoveredPlaylistRuntime>();
    FRecoveredBeatmapData Data; FString Error;
    TestTrue(TEXT("Parse authored scheduling fixture"), URecoveredBeatmapLibrary::ParseBeatmapJson(TEXT(R"JSON({"meta":{"duration":10,"bpm":120,"offset":99},"beats":[{"time":1},{"time":2,"type":"rest"},{"time":3,"type":"accent"}],"events":[{"time":1,"type":"disable_break"},{"time":2,"type":"restore_break"},{"time":3,"type":"text","value":"retained"}]})JSON"), Data, Error));
    TestTrue(TEXT("Start authored song data"), Runtime->StartSongData(Data, 2, 1.75, .025, Error));
    TestTrue(TEXT("Pre-roll clock starts negative"), Runtime->GetAudioTime() < 0);
    Runtime->PausePlayback();
    const double Frozen = Runtime->GetAudioTime();
    Runtime->AdvanceTo(8);
    TestTrue(TEXT("Paused advance does not dispatch events"), Runtime->EventHistory.IsEmpty());
    TestEqual(TEXT("Paused clock remains fixed"), Runtime->GetAudioTime(), Frozen);
    Runtime->ResumePlayback(); Runtime->bSuppressBreakControls = true;
    Runtime->AdvanceTo(2);
    TestTrue(TEXT("Suppressed break events are consumed without history"), Runtime->EventHistory.IsEmpty());
    Runtime->AdvanceTo(3);
    TestEqual(TEXT("Nonbreak event survives suppression"), Runtime->EventHistory.Num(), 1);
    TestEqual(TEXT("Authored event payload survives"), Runtime->EventHistory[0].Value, FString(TEXT("retained")));
    Runtime->AdvanceTo(10);
    TestEqual(TEXT("Metadata duration completes exactly one round"), Runtime->CompletedRounds, 1);
    Runtime->AdvanceTo(11);
    TestEqual(TEXT("Repeated tick cannot complete twice"), Runtime->CompletedRounds, 1);
    TestFalse(TEXT("Completion stops advancement"), Runtime->bPlaying);
    TestTrue(TEXT("Restart song"), Runtime->StartSongData(Data, 0, 1, 0, Error));
    Runtime->StopPlayback(); Runtime->AdvanceTo(20);
    TestEqual(TEXT("Stop is distinct from completion"), Runtime->CompletedRounds, 1);
    Data.Meta.Duration = 0;
    TestFalse(TEXT("Runtime rejects zero-duration track without tightening parser"), Runtime->StartSongData(Data, 0, 1, 0, Error));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPlaylistHistoryTest, "CockHero.Recovery.PlaylistBoundedHistory", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredPlaylistHistoryTest::RunTest(const FString& Parameters) {
    auto* Runtime = NewObject<URecoveredPlaylistRuntime>(); FRecoveredBeatmapData Data; FString Error;
    Data.Meta.Duration = 100; Data.Beats.AddDefaulted();
    for (int32 I = 0; I < 20; ++I) { auto& Event = Data.Events.AddDefaulted_GetRef(); Event.Time = I; Event.Value = FString::FromInt(I); }
    TestTrue(TEXT("Start history fixture"), Runtime->StartSongData(Data, 0, 1, 0, Error));
    Runtime->AdvanceTo(20);
    TestEqual(TEXT("History retains newest fifteen entries"), Runtime->EventHistory.Num(), 15);
    TestEqual(TEXT("Oldest retained record is sixth dispatch"), Runtime->EventHistory[0].Value, FString(TEXT("5")));
    TestEqual(TEXT("Newest dispatch is retained"), Runtime->EventHistory.Last().Value, FString(TEXT("19")));
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTowerFlowTest, "CockHero.Recovery.TowerRoundLifecycle", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredTowerFlowTest::RunTest(const FString& Parameters) {
    auto* Runtime = NewObject<URecoveredTowerRuntime>(); FString Error;
    TArray<FRecoveredTowerOption> Pool;
    for (uint8 I = 0; I < 3; ++I) { auto& Option = Pool.AddDefaulted_GetRef(); Option.Objective = I; Option.ObjectiveParam = 10; }
    TestTrue(TEXT("Start finite three-round tower"), Runtime->StartSession(3, false, 2, Pool, 193, Error));
    TestEqual(TEXT("Native session waits at round zero before selection"), Runtime->CurrentRound, 0);
    TestEqual(TEXT("Three draft lanes generated"), Runtime->CurrentOptions.Num(), 3);
    TSet<uint8> Objectives; for (const auto& Option : Runtime->CurrentOptions) Objectives.Add(Option.Objective);
    TestEqual(TEXT("Draft samples without replacement"), Objectives.Num(), 3);
    TestFalse(TEXT("Cannot complete before selection"), Runtime->CompleteRound(true));
    TestFalse(TEXT("Out of bounds selection rejected"), Runtime->SelectOption(3));
    TestTrue(TEXT("Select first round"), Runtime->SelectOption(0));
    TestTrue(TEXT("Complete successful round"), Runtime->CompleteRound(true));
    TestFalse(TEXT("Duplicate completion rejected"), Runtime->CompleteRound(true));
    TestTrue(TEXT("Continue to second round"), Runtime->ContinueAfterRound());
    TestTrue(TEXT("Select second round"), Runtime->SelectOption(1));
    TestTrue(TEXT("Record failed round"), Runtime->CompleteRound(false));
    TestTrue(TEXT("Continue into scheduled shop"), Runtime->ContinueAfterRound());
    TestEqual(TEXT("Shop opens after configured two rounds"), Runtime->Phase, ERecoveredRoundPhase::Shop);
    TestFalse(TEXT("Cannot play while shop open"), Runtime->SelectOption(0));
    TestTrue(TEXT("Leaving shop drafts next round"), Runtime->LeaveShop());
    TestTrue(TEXT("Select final round"), Runtime->SelectOption(2));
    TestTrue(TEXT("Complete final round"), Runtime->CompleteRound(true));
    TestTrue(TEXT("Finalize finite session"), Runtime->ContinueAfterRound());
    TestEqual(TEXT("Finite session terminal state"), Runtime->Phase, ERecoveredRoundPhase::SessionComplete);
    TestEqual(TEXT("Native completed rounds track highest completed round including failure"), Runtime->CompletedRounds, 3);
    TestEqual(TEXT("Failures preserved separately"), Runtime->FailedRounds, 1);
    TestFalse(TEXT("Terminal state cannot advance"), Runtime->ContinueAfterRound());
    TestTrue(TEXT("Endless accepts no finite round target"), Runtime->StartSession(0, true, 0, Pool, 193, Error));
    TestTrue(TEXT("Select endless round"), Runtime->SelectOption(0)); Runtime->CompleteRound(true); Runtime->ContinueAfterRound();
    TestEqual(TEXT("Endless session drafts another round"), Runtime->Phase, ERecoveredRoundPhase::RoundSelection);
    Runtime->StopSession(); TestEqual(TEXT("Explicit stop returns inactive"), Runtime->Phase, ERecoveredRoundPhase::Inactive);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPlaylistBreakTest, "CockHero.Recovery.PlaylistBreakClock", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredPlaylistBreakTest::RunTest(const FString& Parameters) {
    auto* Runtime = NewObject<URecoveredPlaylistRuntime>(); FRecoveredBeatmapData Data; FString Error;
    Data.Meta.Duration = 100; Data.Beats.AddDefaulted();
    auto& Event = Data.Events.AddDefaulted_GetRef(); Event.Time = 1; Event.Value = TEXT("During break");
    TestTrue(TEXT("Start song for break lifecycle"), Runtime->StartSongData(Data, 0, 1, 0, Error));
    TestTrue(TEXT("Playing song starts break"), Runtime->BeginBreak());
    TestFalse(TEXT("Break keeps native audio clock running"), Runtime->bPaused);
    TestFalse(TEXT("Cannot nest breaks"), Runtime->BeginBreak());
    Runtime->AdvanceTo(2);
    TestEqual(TEXT("Control events continue while on break"), Runtime->EventHistory.Num(), 1);
    Runtime->EndBreak(); TestFalse(TEXT("Break ends without random-card restart"), Runtime->bOnBreak);
    Runtime->PausePlayback(); TestFalse(TEXT("Paused playlist cannot start break"), Runtime->BeginBreak());
    Runtime->StopPlayback(); TestFalse(TEXT("Stopped playlist cannot start break"), Runtime->BeginBreak());
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTowerCatalogTest, "CockHero.Recovery.TowerSourceCatalog", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredTowerCatalogTest::RunTest(const FString& Parameters) {
    auto* Runtime = NewObject<URecoveredTowerRuntime>(); FString Error;
    TestTrue(TEXT("Load six native tiers and 42 authored objective parameter rows"), Runtime->LoadSourceCatalog(Error));
    TArray<FRecoveredTowerOption> Pool;
    for (uint8 Objective = 0; Objective <= 8; ++Objective) { auto& Option = Pool.AddDefaulted_GetRef(); Option.Objective = Objective; Option.DifficultyTier = 1; Option.ObjectiveParam = 1; }
    TestTrue(TEXT("Start source-catalog tower"), Runtime->StartSession(2, false, 0, Pool, 417, Error));
    for (const auto& Option : Runtime->CurrentOptions) {
        TestTrue(TEXT("Prejac and Tribute are final-round-only objectives"), Option.Objective != 6 && Option.Objective != 7);
        TestTrue(TEXT("First calibration tiers use source 2,3,4"), Option.DifficultyTier >= 2 && Option.DifficultyTier <= 4);
        TestTrue(TEXT("Source tier reward uses authored positive interval"), Option.RewardCoins > 0);
    }
    Runtime->SelectOption(0); Runtime->CompleteRound(true); Runtime->ContinueAfterRound();
    for (const auto& Option : Runtime->CurrentOptions) {
        TestEqual(TEXT("Final native round uses boss tier six"), Option.DifficultyTier, 6);
        TestEqual(TEXT("Final source tier retains its authored coin sentinel"), Option.RewardCoins, -1);
        if (Option.Objective != 0 && Option.Objective != 4) TestTrue(TEXT("Authored parameter roll found exact objective/tier row"), Option.ObjectiveParam > 0);
    }
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredMusicUpgradeTest, "CockHero.Recovery.MusicUpgradeSourceValues", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredMusicUpgradeTest::RunTest(const FString& Parameters) {
    auto* Save = NewObject<URecoveredSaveGame>(); Save->StateJson = TEXT("{}");
    const double Values[3][5] = {{5,8,12,15,18}, {1,2,3,4,5}, {500,400,300,250,180}};
    for (uint8 Type = 0; Type < 3; ++Type) {
        TestEqual(TEXT("Missing music upgrade defaults to level one"), RecoveredMusicUpgrades::GetLevel(Save, Type), 1);
        for (int32 Level = 1; Level <= 5; ++Level) {
            TestTrue(TEXT("Persist valid independent music upgrade level"), RecoveredMusicUpgrades::SetLevel(Save, Type, Level));
            TestEqual(TEXT("Music upgrade uses exact source progression value"), RecoveredMusicUpgrades::GetValue(Save, Type), Values[Type][Level - 1]);
        }
    }
    TestFalse(TEXT("Music upgrades reject level six"), RecoveredMusicUpgrades::SetLevel(Save, 0, 6));
    TestFalse(TEXT("Unknown music upgrade rejected"), RecoveredMusicUpgrades::SetLevel(Save, 3, 1));
    TestEqual(TEXT("Duration level never aliases charge upgrade level"), RecoveredMusicUpgrades::GetValue(Save, 0), 18.0);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTowerAdaptiveTest, "CockHero.Recovery.TowerAdaptivePressure", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredTowerAdaptiveTest::RunTest(const FString& Parameters) {
    auto* Runtime = NewObject<URecoveredTowerRuntime>(); Runtime->TotalRounds = 10; Runtime->CurrentRound = 4;
    TestEqual(TEXT("Native pressure starts neutral without prior rounds"), Runtime->CalculateAdaptivePressure(), 0.f);
    TestTrue(TEXT("Finite round progress excludes opening round"), FMath::IsNearlyEqual(Runtime->GetDifficultyProgress(4), 1.f / 3));
    FRecoveredSessionStats Stats; Stats.SessionDuration = 60; Stats.Edges = 20; Stats.DefensiveItemsUsed = 10;
    Runtime->RoundHistory.Add(Stats);
    TestTrue(TEXT("High edge and defensive rates increase easing pressure"), Runtime->CalculateAdaptivePressure() > 0);
    Runtime->bEndlessMode = true;
    TestTrue(TEXT("Endless difficulty progress caps at native .9"), FMath::IsNearlyEqual(Runtime->GetDifficultyProgress(100), .9f));
    for (int32 I = 0; I < 100; ++I) TestTrue(TEXT("Adaptive tier remains source ordinary range one through five"), Runtime->RollAdaptiveTier() >= 1 && Runtime->RollAdaptiveTier() <= 5);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPlaylistProgressionTest, "CockHero.Recovery.PlaylistUpgradeTransition", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredPlaylistProgressionTest::RunTest(const FString& Parameters) {
    const FString Directory = FPaths::ProjectSavedDir() / TEXT("Automation/PlaylistTransition") / FGuid::NewGuid().ToString(EGuidFormats::Digits);
    if (!TestTrue(TEXT("Create isolated track fixtures"), IFileManager::Get().MakeDirectory(*Directory, true))) return false;
    TArray<uint8> Audio; Audio.Add(0);
    TestTrue(TEXT("Write existence-only audio fixture"), FFileHelper::SaveArrayToFile(Audio, *(Directory / TEXT("song.wav"))));
    TArray<FString> Paths;
    for (int32 I = 0; I < 2; ++I) {
        Paths.Add(Directory / FString::Printf(TEXT("track%d.json"), I));
        const FString Json = FString::Printf(TEXT("{\"meta\":{\"title\":\"Track %d\",\"audioFile\":\"song.wav\",\"duration\":2},\"beats\":[{\"time\":1}]}"), I);
        TestTrue(TEXT("Write source-shaped beatmap fixture"), FFileHelper::SaveStringToFile(Json, *Paths.Last()));
    }
    auto* Runtime = NewObject<URecoveredPlaylistRuntime>(); FString Error;
    TestTrue(TEXT("Start ordered two-track playlist"), Runtime->StartPlaylist(Paths, false, 0, 1, 0, Error));
    Runtime->AdvanceTo(2);
    TestTrue(TEXT("Nonfinal song waits for progression choice"), Runtime->bAwaitingNextTrack);
    TestFalse(TEXT("Progression screen stops musical clock"), Runtime->bPlaying);
    TestEqual(TEXT("Only first track counted before upgrade"), Runtime->CompletedRounds, 1);
    TestTrue(TEXT("Progression choice starts prepared next track"), Runtime->ContinuePlaylist(Error));
    TestEqual(TEXT("Source ordered playlist advances exactly once"), Runtime->CurrentSong.Meta.Title, FString(TEXT("Track 1")));
    TestFalse(TEXT("Pending transition consumed"), Runtime->bAwaitingNextTrack);
    TestFalse(TEXT("Duplicate progression choice rejected"), Runtime->ContinuePlaylist(Error));
    Runtime->AdvanceTo(2);
    TestEqual(TEXT("Final track completes finite playlist"), Runtime->CompletedRounds, 2);
    TestFalse(TEXT("Finite playlist has no pending next track"), Runtime->bAwaitingNextTrack);
    TestTrue(TEXT("Clean isolated track fixtures"), IFileManager::Get().DeleteDirectory(*Directory, false, true));
    return true;
}
#endif
