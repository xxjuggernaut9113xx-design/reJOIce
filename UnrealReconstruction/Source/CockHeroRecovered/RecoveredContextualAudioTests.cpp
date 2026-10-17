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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredContextualAudioTest,"CockHero.Recovery.ContextualAudioContract",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredContextualAudioTest::RunTest(const FString& Parameters) {
    FString ReportText;
    const FString ReportPath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/contextual-audio-import-recovery.json");
    if (!TestTrue(TEXT("Recovered contextual-audio import report is available"),FFileHelper::LoadFileToString(ReportText,*ReportPath))) return false;
    TSharedPtr<FJsonObject> Report;
    if (!TestTrue(TEXT("Recovered contextual-audio import report parses"),FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(ReportText),Report) && Report.IsValid())) return false;
    const TArray<TSharedPtr<FJsonValue>>* Tracks=nullptr;
    if (!TestTrue(TEXT("Recovered contextual-audio import report lists tracks"),Report->TryGetArrayField(TEXT("tracks"),Tracks) && Tracks)) return false;
    TestEqual(TEXT("Recovered contextual-audio track count matches source"),Tracks->Num(),1321);

    TMap<FString,int32> PoolCounts;
    for (const TSharedPtr<FJsonValue>& Value:*Tracks) {
        const TSharedPtr<FJsonObject>* Row=nullptr;
        if (!Value.IsValid() || !Value->TryGetObject(Row) || !Row || !Row->IsValid()) {
            AddError(TEXT("Recovered contextual-audio report contains an invalid track row"));
            continue;
        }
        FString Name;
        FString Asset;
        FString Tag;
        (*Row)->TryGetStringField(TEXT("name"),Name);
        (*Row)->TryGetStringField(TEXT("asset"),Asset);
        (*Row)->TryGetStringField(TEXT("tag"),Tag);
        TestFalse(*FString::Printf(TEXT("Recovered contextual-audio asset path is present: %s"),*Name),Asset.IsEmpty());
        TestTrue(*FString::Printf(TEXT("Recovered contextual-audio package exists: %s"),*Name),FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(Asset)));
        TestNotNull(*FString::Printf(TEXT("Recovered contextual-audio SoundWave loads: %s"),*Name),LoadObject<USoundBase>(nullptr,*Asset));
        PoolCounts.FindOrAdd(Tag)++;
    }
    TestEqual(TEXT("Assjob contextual pool count"),PoolCounts.FindRef(TEXT("assjob")),138);
    TestEqual(TEXT("Blowjob contextual pool count"),PoolCounts.FindRef(TEXT("blowjob")),211);
    TestEqual(TEXT("Cowgirl contextual pool count"),PoolCounts.FindRef(TEXT("cowgirl")),19);
    TestEqual(TEXT("Cum contextual pool count"),PoolCounts.FindRef(TEXT("cum")),247);
    TestEqual(TEXT("Handjob contextual pool count"),PoolCounts.FindRef(TEXT("handjob")),208);
    TestEqual(TEXT("Paizuri contextual pool count"),PoolCounts.FindRef(TEXT("paizuri")),269);
    TestEqual(TEXT("Sex contextual pool count"),PoolCounts.FindRef(TEXT("sex")),199);
    TestEqual(TEXT("Succubus contextual pool count"),PoolCounts.FindRef(TEXT("succubus")),30);

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>(World);
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Contextual-audio save defaults initialize"),Save->InitializeRecoveredDefaults())) return false;
    Instance->CurrentSave=Save;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Contextual-audio manager spawns"),Manager)) return false;

    TestTrue(TEXT("Enable source contextual SFX"),Save->SetBoolSetting(TEXT("AreContextualBeatSFXEnabled?"),true));
    TestTrue(TEXT("Set source contextual scalar"),Save->SetNumberSetting(TEXT("ContextBeatSFXVolume"),.5));
    Manager->SelectedRandomCard.Tags={TEXT("cowgirl"),TEXT("sex")};
    Manager->PlayRecoveredTagContextualBeatCompleteSFX();
    TestEqual(TEXT("One candidate is sampled per recognized source tag"),Manager->RecoveredEligibleContextualSounds.Num(),2);
    TestFalse(TEXT("Source tags select a contextual sound"),Manager->LastRecoveredContextualSound.IsNone());
    TestTrue(TEXT("Contextual sound resolves from a recovered category"),Manager->LastRecoveredContextualSound.ToString().Contains(TEXT("SFX__")));
    TestTrue(TEXT("Contextual volume applies source two-times scalar"),FMath::IsNearlyEqual(Manager->LastRecoveredContextualVolume,1.0f));
    TestTrue(TEXT("Contextual pitch matches source"),FMath::IsNearlyEqual(Manager->LastRecoveredContextualPitch,1.5f));
    TestTrue(TEXT("Contextual start time matches source"),FMath::IsNearlyEqual(Manager->LastRecoveredContextualStartTime,-.28f));

    Manager->SelectedRandomCard.Tags={TEXT("unknown")};
    Manager->PlayRecoveredTagContextualBeatCompleteSFX();
    TestEqual(TEXT("Unknown source tag produces no eligible sound"),Manager->RecoveredEligibleContextualSounds.Num(),0);
    TestTrue(TEXT("Unknown source tag plays no contextual sound"),Manager->LastRecoveredContextualSound.IsNone());

    Manager->SelectedRandomCard.Tags={TEXT("cowgirl")};
    Manager->BeatContext.CardType=2;
    Manager->RecoveredFastMoanPool.Reset();
    Manager->RecoveredContextualPlayCount=0;
    Manager->PlayRecoveredBeatCompleteAudio();
    TestEqual(TEXT("Fast source reset invokes contextual routing twice"),Manager->RecoveredContextualPlayCount,2);
    TestEqual(TEXT("Fast source reset restores the full fast moan pool"),Manager->RecoveredFastMoanPool.Num(),72);

    TestTrue(TEXT("Disable source contextual SFX"),Save->SetBoolSetting(TEXT("AreContextualBeatSFXEnabled?"),false));
    Manager->RecoveredContextualPlayCount=0;
    Manager->RecoveredSlowMoanPool.Reset();
    Manager->BeatContext.CardType=0;
    Manager->PlayRecoveredBeatCompleteAudio();
    TestEqual(TEXT("Disabled contextual setting suppresses the nested source route"),Manager->RecoveredContextualPlayCount,0);
    return true;
}
#endif
