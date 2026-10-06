#include "RecoveredRules.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"
#include "RecoveredAudioSettings.h"
#include "Components/Slider.h"
#include "RecoveredDeviceInterface.h"
#include "RecoveredVideoSettings.h"
#include "Components/ComboBoxString.h"
#include "Blueprint/WidgetTree.h"
#include "RecoveredSaveSlotWidget.h"
#include "RecoveredImportWidget.h"
#include "RecoveredChallengeWidget.h"
#include "RecoveredModifierWidget.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPatchLifecycleTest,"CockHero.Recovery.PatchLifecycle",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPatchLifecycleTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    GEngine->CreateNewWorldContext(EWorldType::Game).SetCurrentWorld(World);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Manager"),Manager)) return false;
    Manager->HandleRecoveredSessionAction(TEXT("StoreCardStarted"));
    TestFalse(TEXT("Store completion does not start another store"),Manager->bStoreOnCooldown);
    Manager->SessionStats.SessionDuration=120;
    Manager->SessionStats.Strokes=100;
    Manager->SessionStats.bWon=true;
    TestEqual(TEXT("Post-game uses verified native XP"),Manager->CalculateRecoveredSessionXP(),URecoveredProgressionLibrary::CalculateSessionXP(Manager->SessionStats,FRecoveredXPSettings()));
    Manager->FinalizeRecoveredSession();
    const int32 XP=Manager->LifetimeStats.TotalXPEarned;
    Manager->FinalizeRecoveredSession();
    TestFalse(TEXT("Untouched session is not a win"),Manager->SessionStats.bWon);
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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredFinalPatchRegressionTest,"CockHero.Recovery.FinalPatchRegressions",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredFinalPatchRegressionTest::RunTest(const FString& Parameters) {
    auto* Device=NewObject<URecoveredDeviceManager>();
    TestFalse(TEXT("Unimplemented transport cannot claim connection"),Device->ConnectDevice(ERecoveredDeviceKind::Handy,TEXT("test")));
    TestFalse(TEXT("Connection remains unavailable"),Device->IsDeviceConnected(ERecoveredDeviceKind::Handy));
    FRecoveredSessionRewardData Bundle;Bundle.XPGranted=123;
    FRecoveredReward XP;XP.RewardType=TEXT("XP");XP.Value=123;Bundle.Rewards.Add(XP);
    TestEqual(TEXT("XP appears once in session reward text"),URecoveredProgressionLibrary::GetRewardsText(Bundle).ToString(),FString(TEXT("+123 XP")));
    auto* Slots=NewObject<URecoveredSaveSlotWidget>();
    TestFalse(TEXT("Cannot create path-like save slot"),Slots->CreateSaveSlot(TEXT("../original")));
    TestFalse(TEXT("Cannot delete path-like save slot"),Slots->DeleteSaveSlot(TEXT("../original")));
    TestFalse(TEXT("Incomplete slot switching does not replace live state"),Slots->LoadSaveSlot(TEXT("test")));
    auto* Progression=NewObject<URecoveredProgressionManager>();
    Progression->ModifierDataTable=NewObject<UDataTable>();
    Progression->ModifierDataTable->RowStruct=FRecoveredReward::StaticStruct();
    TestEqual(TEXT("Wrong modifier schema is rejected"),Progression->GetAllModifierData().Num(),0);
    auto* Save=NewObject<URecoveredSaveGame>();Save->StateJson=TEXT("{}");
    TestTrue(TEXT("Write exact multiplier preference"),URecoveredVideoSettingsMenu::WritePreference(Save,TEXT("StrokeCountMultiplier"),TEXT("4x")));
    TestEqual(TEXT("Stores native enum index"),Save->GetNumberSetting(TEXT("StrokeMultiplierEnum"),-1),3.0);
    TestEqual(TEXT("Reads enum back to option"),URecoveredVideoSettingsMenu::ReadPreference(Save,TEXT("StrokeCountMultiplier"),TEXT("missing")),FString(TEXT("4x")));
    TestTrue(TEXT("Write canonical bool"),URecoveredVideoSettingsMenu::WritePreference(Save,TEXT("ScreenshakeComboBox"),TEXT("Off")));
    TestFalse(TEXT("Canonical bool reaches its consumer key"),Save->GetBoolSetting(TEXT("IsScreenShakeEnabled"),true));
    TestFalse(TEXT("Invalid enum option rejected"),URecoveredVideoSettingsMenu::WritePreference(Save,TEXT("StrokeCountMultiplier"),TEXT("9x")));
    UClass* Class=LoadClass<URecoveredVideoSettingsMenu>(nullptr,TEXT("/Game/Recovery/UI/VideoSettingsMenu.VideoSettingsMenu_C"));
    if (!TestNotNull(TEXT("Video settings class"),Class)) return false;
    auto* Widget=NewObject<URecoveredVideoSettingsMenu>(GetTransientPackage(),Class);
    if (!TestTrue(TEXT("Video settings initializes"),Widget->Initialize())) return false;
    auto Slate=Widget->TakeWidget();
    TArray<UWidget*> Widgets;Widget->WidgetTree->GetAllWidgets(Widgets);
    int32 ComboCount=0;
    for (auto* Child:Widgets) if (auto* Combo=Cast<UComboBoxString>(Child)) {
        ++ComboCount;TestTrue(Combo->GetName()+TEXT(" callback bound"),Combo->OnSelectionChanged.IsBound());
        const FString Option=Combo->GetOptionAtIndex(0);
        TestTrue(Combo->GetName()+TEXT(" has typed save mapping"),URecoveredVideoSettingsMenu::WritePreference(Save,Combo->GetFName(),Option));
        TestEqual(Combo->GetName()+TEXT(" option roundtrip"),URecoveredVideoSettingsMenu::ReadPreference(Save,Combo->GetFName(),TEXT("missing")),Option);
    }
    TestEqual(TEXT("All video/preference combos covered"),ComboCount,27);
    auto* Deck=NewObject<URecoveredDeckState>();FRecoveredMediaEntry Entry;Entry.FullPath=TEXT("example");Deck->Master.Slow.Add(Entry);
    Deck->ReplaceEmptyDecks();TestEqual(TEXT("Original deck refill preserved"),Deck->Child.Slow.Num(),1);
    Deck->Child.Slow.Reset();Deck->SetDeckRepeat(0,false);Deck->ReplaceEmptyDecks();TestEqual(TEXT("Explicit no-repeat is honored"),Deck->Child.Slow.Num(),0);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredWidgetAttachmentTest,"CockHero.Recovery.WidgetAttachments",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredWidgetAttachmentTest::RunTest(const FString& Parameters) {
    UClass* ImportClass=LoadClass<URecoveredImportWidget>(nullptr,TEXT("/Game/Recovery/UI/ImportMenuWidget.ImportMenuWidget_C"));
    if (!TestNotNull(TEXT("Import widget native parent"),ImportClass)) return false;
    auto* Import=NewObject<URecoveredImportWidget>(GetTransientPackage(),ImportClass);
    if (!TestTrue(TEXT("Import widget initializes"),Import->Initialize())) return false;
    Import->TakeWidget();
    TestNotNull(TEXT("Import file list survives native attachment"),Import->GetWidgetFromName(TEXT("EntryScrollBox")));
    TestNotNull(TEXT("Import directory action survives native attachment"),Import->GetWidgetFromName(TEXT("AddDirectoryButton")));

    UClass* ChallengeClass=LoadClass<URecoveredChallengeWidget>(nullptr,TEXT("/Game/Recovery/UI/ChallengesTabWidget.ChallengesTabWidget_C"));
    if (!TestNotNull(TEXT("Challenge widget native parent"),ChallengeClass)) return false;
    auto* Challenges=NewObject<URecoveredChallengeWidget>(GetTransientPackage(),ChallengeClass);
    if (!TestTrue(TEXT("Challenge widget initializes"),Challenges->Initialize())) return false;
    Challenges->TakeWidget();
    TestNotNull(TEXT("Challenge list survives native attachment"),Challenges->GetWidgetFromName(TEXT("ChallengesVerticalBox")));
    TestNotNull(TEXT("Challenge interaction survives native attachment"),Challenges->GetWidgetFromName(TEXT("InteractionButton")));

    UClass* ModifierClass=LoadClass<URecoveredModifierWidget>(nullptr,TEXT("/Game/Recovery/UI/ModifiersTabWidget.ModifiersTabWidget_C"));
    if (!TestNotNull(TEXT("Modifier widget native parent"),ModifierClass)) return false;
    auto* Modifiers=NewObject<URecoveredModifierWidget>(GetTransientPackage(),ModifierClass);
    if (!TestTrue(TEXT("Modifier widget initializes"),Modifiers->Initialize())) return false;
    Modifiers->TakeWidget();
    TestNotNull(TEXT("Modifier grid survives native attachment"),Modifiers->GetWidgetFromName(TEXT("UniformGridPanel_94")));
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPostGameHandoffTest,"CockHero.Recovery.PostGameHandoff",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPostGameHandoffTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    GEngine->CreateNewWorldContext(EWorldType::Game).SetCurrentWorld(World);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Post-game manager"),Manager)) return false;
    Manager->SessionStats.Strokes=42;
    Manager->SessionStats.Edges=7;
    Manager->SessionStats.MaxCombo=11;
    Manager->SessionStats.EnemiesDefeated=3;
    Manager->SessionStats.SuccubiDefeated=2;
    Manager->SessionStats.SessionDuration=125;
    Manager->SessionStats.bWon=true;
    UClass* ResultsClass=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/WBP_PostGameFlow_Master.WBP_PostGameFlow_Master_C"));
    if (!TestNotNull(TEXT("Post-game master class"),ResultsClass)) return false;
    auto* Results=NewObject<UUserWidget>(GetTransientPackage(),ResultsClass);
    if (!TestTrue(TEXT("Post-game master initializes"),Results->Initialize())) return false;
    Results->TakeWidget();
    Manager->BindPostGameResultsData(Results);
    auto* Summary=Cast<UUserWidget>(Results->GetWidgetFromName(TEXT("WBP_SessionSummaryWidget")));
    if (!TestNotNull(TEXT("Post-game summary child"),Summary)) return false;
    auto* Strokes=Cast<UTextBlock>(Summary->GetWidgetFromName(TEXT("TotalStrokesText")));
    if (!TestNotNull(TEXT("Post-game strokes field"),Strokes)) return false;
    TestEqual(TEXT("Post-game summary receives final strokes"),Strokes->GetText().ToString(),FString(TEXT("42")));
    auto* Switcher=Cast<UWidgetSwitcher>(Results->GetWidgetFromName(TEXT("WidgetSwitcher")));
    if (!TestNotNull(TEXT("Post-game switcher"),Switcher)) return false;
    TestEqual(TEXT("Post-game lands on summary"),Switcher->GetActiveWidgetIndex(),3);
    World->DestroyWorld(false); GEngine->DestroyWorldContext(World);
    return true;
}
#endif
