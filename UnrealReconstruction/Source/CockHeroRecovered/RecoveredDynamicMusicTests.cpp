#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/PackageName.h"
#include "Misc/ScopeExit.h"
#include "Sound/SoundBase.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredDynamicMusicTest,"CockHero.Recovery.DynamicMusicContract",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredDynamicMusicTest::RunTest(const FString& Parameters) {
    struct FExpectedTrack { uint8 Type; const TCHAR* Name; const TCHAR* Path; float Volume; };
    static const FExpectedTrack Tracks[] = {
        {0,TEXT("dt_110_kit15_loop_within_pad_Dmaj__2_"),TEXT("/Game/Recovery/Resources/DynamicMusic/dt_110_kit15_loop_within_pad_Dmaj__2_.dt_110_kit15_loop_within_pad_Dmaj__2_"),.1f},
        {1,TEXT("HuntingPerc_02_100bpm__3_"),TEXT("/Game/Recovery/Resources/DynamicMusic/HuntingPerc_02_100bpm__3_.HuntingPerc_02_100bpm__3_"),.1f},
        {2,TEXT("AMP2_90_A_2_3"),TEXT("/Game/Recovery/Resources/DynamicMusic/AMP2_90_A_2_3.AMP2_90_A_2_3"),.15f},
        {3,TEXT("NW_OSHRS_80_kit_loop_krakenfall_full_Dmin__3_"),TEXT("/Game/Recovery/Resources/DynamicMusic/NW_OSHRS_80_kit_loop_krakenfall_full_Dmin__3_.NW_OSHRS_80_kit_loop_krakenfall_full_Dmin__3_"),.2f},
    };
    for (const FExpectedTrack& Track:Tracks) {
        const FString ObjectPath(Track.Path);
        TestTrue(*FString::Printf(TEXT("Recovered source music package exists: %s"),Track.Name),FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(ObjectPath)));
        TestNotNull(*FString::Printf(TEXT("Recovered source music SoundWave loads: %s"),Track.Name),LoadObject<USoundBase>(nullptr,*ObjectPath));
    }

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>(World);
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Initialize source save defaults for music"),Save->InitializeRecoveredDefaults())) return false;
    Instance->CurrentSave=Save;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Spawn dynamic music manager"),Manager)) return false;
    TestTrue(TEXT("Enable decoded source dynamic music setting"),Save->SetBoolSetting(TEXT("IsDynamicMusicEnabled?"),true));
    TestTrue(TEXT("Set source background music scalar"),Save->SetNumberSetting(TEXT("BackgroundMusicVolume"),.5));
    for (const FExpectedTrack& Track:Tracks) {
        Manager->PlayRecoveredMusic(Track.Type);
        TestEqual(*FString::Printf(TEXT("Source card type routes dynamic track %d"),Track.Type),Manager->ActiveMusicTrack,FName(Track.Name));
    }
    const FName LastTrack=Manager->ActiveMusicTrack;
    TestTrue(TEXT("Disable source dynamic music setting"),Save->SetBoolSetting(TEXT("IsDynamicMusicEnabled?"),false));
    Manager->PlayRecoveredMusic(0);
    TestEqual(TEXT("Disabled source setting does not replace stopped music component"),Manager->ActiveMusicTrack,LastTrack);
    return true;
}
#endif
