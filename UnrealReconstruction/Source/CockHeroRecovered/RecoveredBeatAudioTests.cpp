#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/PackageName.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundBase.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBeatAudioTest,"CockHero.Recovery.BeatAudioContract",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredBeatAudioTest::RunTest(const FString& Parameters) {
    FString ReportText;
    const FString ReportPath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/beat-audio-import-recovery.json");
    if (!TestTrue(TEXT("Recovered beat-audio import report is available"),FFileHelper::LoadFileToString(ReportText,*ReportPath))) return false;
    TSharedPtr<FJsonObject> Report;
    if (!TestTrue(TEXT("Recovered beat-audio import report parses"),FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(ReportText),Report) && Report.IsValid())) return false;
    const TArray<TSharedPtr<FJsonValue>>* Tracks=nullptr;
    if (!TestTrue(TEXT("Recovered beat-audio import report lists tracks"),Report->TryGetArrayField(TEXT("tracks"),Tracks) && Tracks)) return false;
    TestEqual(TEXT("Recovered beat-audio track count matches source"),Tracks->Num(),182);

    TMap<FString,int32> PoolCounts;
    for (const TSharedPtr<FJsonValue>& Value:*Tracks) {
        const TSharedPtr<FJsonObject>* Row=nullptr;
        if (!Value.IsValid() || !Value->TryGetObject(Row) || !Row || !Row->IsValid()) {
            AddError(TEXT("Recovered beat-audio report contains an invalid track row"));
            continue;
        }
        FString Name;
        FString Asset;
        FString Pool;
        (*Row)->TryGetStringField(TEXT("name"),Name);
        (*Row)->TryGetStringField(TEXT("asset"),Asset);
        (*Row)->TryGetStringField(TEXT("pool"),Pool);
        TestFalse(*FString::Printf(TEXT("Recovered beat-audio asset path is present: %s"),*Name),Asset.IsEmpty());
        TestTrue(*FString::Printf(TEXT("Recovered beat-audio package exists: %s"),*Name),FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(Asset)));
        TestNotNull(*FString::Printf(TEXT("Recovered beat-audio SoundWave loads: %s"),*Name),LoadObject<USoundBase>(nullptr,*Asset));
        if (!Pool.IsEmpty()) PoolCounts.FindOrAdd(Pool)++;
    }
    TestEqual(TEXT("Slow source moan-pool count"),PoolCounts.FindRef(TEXT("Slow")),47);
    TestEqual(TEXT("Medium source moan-pool count"),PoolCounts.FindRef(TEXT("Medium")),61);
    TestEqual(TEXT("Fast source moan-pool count"),PoolCounts.FindRef(TEXT("Fast")),72);

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>(World);
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Beat-audio save defaults initialize"),Save->InitializeRecoveredDefaults())) return false;
    Instance->CurrentSave=Save;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Beat-audio manager spawns"),Manager) || !TestNotNull(TEXT("Beat-audio timeline is available"),Manager->BeatTimeline.Get())) return false;

    TestTrue(TEXT("Set source metronome scalar"),Save->SetNumberSetting(TEXT("MetronomeVolume"),.5));
    TestTrue(TEXT("Set source moan scalar"),Save->SetNumberSetting(TEXT("MoansVolume"),.25));
    TestTrue(TEXT("Set source SFX scalar"),Save->SetNumberSetting(TEXT("SFXVolume"),.5));
    TestTrue(TEXT("Enable source moan SFX"),Save->SetBoolSetting(TEXT("bMoanSFXEnabled?"),true));
    Manager->BeatTimeline->TotalStrokes=10;
    Manager->BeatTimeline->CompletedBeats=10;
    Manager->BeatContext.CardType=0;
    Manager->BeatContext.HeatCategory=1;

    Manager->PlayRecoveredBeatCompleteAudio();
    TestTrue(TEXT("Slow source metronome identity"),Manager->LastRecoveredMetronome==FName(TEXT("casual-click-pop-ui-10-262126")));
    TestTrue(TEXT("Slow source metronome volume applies the .8 threshold"),FMath::IsNearlyEqual(Manager->LastRecoveredMetronomeVolume,.35f));
    TestTrue(TEXT("Slow source metronome pitch follows completed beat progress"),FMath::IsNearlyEqual(Manager->LastRecoveredMetronomePitch,1.5f));
    TestTrue(TEXT("Initial source slow slave pool has no playable moan"),Manager->LastRecoveredBeatMoan.IsNone());
    TestEqual(TEXT("Initial source slow slave pool resets from its master list"),Manager->RecoveredSlowMoanPool.Num(),47);
    TestTrue(TEXT("Heat source identity"),Manager->LastRecoveredHeatSound==FName(TEXT("heatfiresfx")));
    TestTrue(TEXT("Medium heat category source volume"),FMath::IsNearlyEqual(Manager->LastRecoveredHeatVolume,.4f));
    TestTrue(TEXT("Medium heat category source pitch"),FMath::IsNearlyEqual(Manager->LastRecoveredHeatPitch,.8f));

    Manager->PlayRecoveredBeatCompleteAudio();
    TestFalse(TEXT("Seeded slow slave pool selects a recovered moan"),Manager->LastRecoveredBeatMoan.IsNone());
    TestTrue(TEXT("Selected slow moan uses the source asset namespace"),Manager->LastRecoveredBeatMoan.ToString().StartsWith(TEXT("slow_beatmoansfx__")));
    TestEqual(TEXT("Slow source slave removes an independent random element"),Manager->RecoveredSlowMoanPool.Num(),46);
    TestTrue(TEXT("Slow source moan volume applies source pitch and slider"),FMath::IsNearlyEqual(Manager->LastRecoveredMoanVolume,.35f));
    TestTrue(TEXT("Slow source moan pitch follows completed beat progress"),FMath::IsNearlyEqual(Manager->LastRecoveredMoanPitch,1.4f));
    for (int32 Index=0; Index<46; ++Index) Manager->PlayRecoveredBeatCompleteAudio();
    TestEqual(TEXT("Slow source slave resets after the full selection cycle"),Manager->RecoveredSlowMoanPool.Num(),47);

    Manager->BeatContext.CardType=1;
    Manager->PlayRecoveredBeatCompleteAudio();
    TestEqual(TEXT("Initial medium source slave pool resets from its master list"),Manager->RecoveredMediumMoanPool.Num(),61);
    Manager->BeatContext.CardType=2;
    Manager->PlayRecoveredBeatCompleteAudio();
    TestEqual(TEXT("Initial fast source slave pool resets from its master list"),Manager->RecoveredFastMoanPool.Num(),72);
    Manager->BeatContext.CardType=3;
    Manager->PlayRecoveredBeatCompleteAudio();
    TestTrue(TEXT("Source punishment card shares the fast moan pool"),Manager->LastRecoveredBeatMoan.ToString().StartsWith(TEXT("fast_beatmoansfx__")));
    TestTrue(TEXT("Fast pool uses the .55 source metronome threshold"),Manager->LastRecoveredMetronome==FName(TEXT("casual-click-pop-ui-10-262126")));
    TestTrue(TEXT("Fast source metronome volume applies the .55 threshold"),FMath::IsNearlyEqual(Manager->LastRecoveredMetronomeVolume,.475f));

    TestTrue(TEXT("Disable source moan SFX"),Save->SetBoolSetting(TEXT("bMoanSFXEnabled?"),false));
    Manager->BeatContext.CardType=1;
    Manager->RecoveredMediumMoanPool.Reset();
    Manager->PlayRecoveredBeatCompleteAudio();
    TestTrue(TEXT("Disabled source moan setting suppresses moan playback"),Manager->LastRecoveredBeatMoan.IsNone());
    TestEqual(TEXT("Disabled source moan setting leaves the slave pool untouched"),Manager->RecoveredMediumMoanPool.Num(),0);

    Manager->BeatContext.CardType=4;
    Manager->BeatContext.HeatCategory=2;
    Manager->PlayRecoveredBeatCompleteAudio();
    TestTrue(TEXT("Source card type four does not route a pace metronome"),Manager->LastRecoveredMetronome.IsNone());
    TestTrue(TEXT("High heat source volume remains independently routed"),FMath::IsNearlyEqual(Manager->LastRecoveredHeatVolume,.3f));
    TestTrue(TEXT("High heat source pitch remains independently routed"),FMath::IsNearlyEqual(Manager->LastRecoveredHeatPitch,.6f));
    return true;
}
#endif
