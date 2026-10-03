#include "RecoveredRules.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"
#include "RecoveredAudioSettings.h"
#include "Components/Slider.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPatchLifecycleTest,"CockHero.Recovery.PatchLifecycle",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPatchLifecycleTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    GEngine->CreateNewWorldContext(EWorldType::Game).SetCurrentWorld(World);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Manager"),Manager)) return false;
    Manager->SessionStats.SessionDuration=120;
    Manager->SessionStats.Strokes=100;
    Manager->SessionStats.bWon=true;
    TestEqual(TEXT("Post-game uses verified native XP"),Manager->CalculateRecoveredSessionXP(),URecoveredProgressionLibrary::CalculateSessionXP(Manager->SessionStats,FRecoveredXPSettings()));
    Manager->FinalizeRecoveredSession();
    const int32 XP=Manager->LifetimeStats.TotalXPEarned;
    Manager->FinalizeRecoveredSession();
    TestEqual(TEXT("Repeated finalization is harmless"),Manager->LifetimeStats.TotalSessionsCompleted,1);
    TestEqual(TEXT("Repeated finalization does not duplicate XP accounting"),Manager->LifetimeStats.TotalXPEarned,XP);
    FRecoveredBeatPattern Pattern; Pattern.IntervalMultipliers={1.0};
    Manager->BeatTimeline->ApplyCalibrationOffset(0.15);
    TestTrue(TEXT("Start calibrated timeline"),Manager->BeatTimeline->StartPattern(Pattern,1.0,10,1.0f,1.0));
    Manager->BeatTimeline->PauseSequence();
    const double Paused=Manager->BeatTimeline->GetMasterTimelinePosition();
    Manager->BeatTimeline->ResumeSequence();
    Manager->BeatTimeline->PauseSequence();
    TestTrue(TEXT("Pause/resume does not add calibration twice"),FMath::Abs(Manager->BeatTimeline->GetMasterTimelinePosition()-Paused)<0.02);
    World->DestroyWorld(false); GEngine->DestroyWorldContext(World);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPatchAudioTest,"CockHero.Recovery.PatchAudioBindings",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPatchAudioTest::RunTest(const FString& Parameters) {
    UClass* Class=LoadClass<URecoveredAudioSettingsMenu>(nullptr,TEXT("/Game/Recovery/UI/AudioSettingsMenu.AudioSettingsMenu_C"));
    if (!TestNotNull(TEXT("Audio Blueprint native parent"),Class)) return false;
    auto* Widget=NewObject<URecoveredAudioSettingsMenu>(GetTransientPackage(),Class);
    if (!TestTrue(TEXT("Audio tree initializes"),Widget->Initialize())) return false;
    auto Slate=Widget->TakeWidget();
    const TCHAR* Names[]={TEXT("BackgroundMusicVolSlider"),TEXT("SFXVolSlider"),TEXT("MoansVolSlider"),TEXT("VoicelinesVolSlider"),TEXT("ContextBeatSFXVolSlider"),TEXT("MetronomeVolSlider")};
    for (const TCHAR* Name:Names) {
        auto* Slider=Cast<USlider>(Widget->GetWidgetFromName(Name));
        if (!TestNotNull(Name,Slider)) continue;
        TestTrue(FString(Name)+TEXT(" has a resolved callback"),Slider->OnMouseCaptureEnd.IsBound());
        Slider->OnMouseCaptureEnd.Broadcast();
    }
    return true;
}
#endif
