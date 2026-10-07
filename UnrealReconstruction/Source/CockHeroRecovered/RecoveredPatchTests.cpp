#include "RecoveredRules.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
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
#include "RecoveredPostGameSequence.h"
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
    TestFalse(TEXT("Slot switching requires an active recovered game instance"),Slots->LoadSaveSlot(TEXT("test")));
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
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredIronManStorePenaltyTest,"CockHero.Recovery.IronManStorePenalty",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredIronManStorePenaltyTest::RunTest(const FString& Parameters) {
    const FString Slot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("AutomationIronMan_")+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    bool bSlotWritten=false;
    ON_SCOPE_EXIT { if (bSlotWritten) UGameplayStatics::DeleteGameInSlot(Slot,0); };

    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Iron Man test save initializes"),Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Iron Man test unlock ledger writes"),Save->SetStringArraySetting(TEXT("UnlockedPacks"),{TEXT("Base_Game_CG"),TEXT("PremiumPack")}))) return false;
    if (!TestTrue(TEXT("Iron Man test enabled ledger writes"),Save->SetStringArraySetting(TEXT("EnabledPacks"),{TEXT("Base_Game_CG"),TEXT("PremiumPack")}))) return false;
    if (!TestTrue(TEXT("Iron Man test point ledger writes"),Save->SetNumberSetting(TEXT("UnlockPoints"),73))) return false;
    bSlotWritten=UGameplayStatics::SaveGameToSlot(Save,Slot,0);
    if (!TestTrue(TEXT("Iron Man test save persists"),bSlotWritten)) return false;

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>();
    Instance->CurrentSave=Save;
    Instance->ActiveRecoverySlot=Slot;
    Instance->ProgressionManager=NewObject<URecoveredProgressionManager>(Instance);
    Instance->ProgressionManager->UnlockPoints=19;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Iron Man manager"),Manager)) return false;
    Manager->MediaPackEnabled.Add(TEXT("Base_Game_CG"),true);
    Manager->MediaPackEnabled.Add(TEXT("PremiumPack"),true);
    Manager->MediaPackEnabled.Add(TEXT("RetiredPack"),false);
    Manager->BeatContext.ActiveModifiers.Add(TEXT("Iron Man"));
    Manager->OnOutcomeRequested.AddUniqueDynamic(Manager,&ARecoveredGlobalManager::HandleRecoveredOutcome);
    Manager->PrematureCum();

    const TArray<FString> Unlocked=Save->GetStringArraySetting(TEXT("UnlockedPacks"));
    const TArray<FString> Enabled=Save->GetStringArraySetting(TEXT("EnabledPacks"));
    TestEqual(TEXT("Iron Man retains exactly the base unlocked pack"),Unlocked.Num(),1);
    if (Unlocked.Num()==1) TestEqual(TEXT("Iron Man base unlocked pack"),Unlocked[0],FString(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Iron Man retains exactly the base enabled pack"),Enabled.Num(),1);
    if (Enabled.Num()==1) TestEqual(TEXT("Iron Man base enabled pack"),Enabled[0],FString(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Iron Man clears the store point ledger"),Save->GetNumberSetting(TEXT("UnlockPoints"),-1),0.0);
    TestFalse(TEXT("Iron Man disables prior unlocked media"),Manager->IsMediaPackEnabled(TEXT("PremiumPack")));
    TestTrue(TEXT("Iron Man preserves base media"),Manager->IsMediaPackEnabled(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Iron Man leaves progression-level points separate"),Instance->ProgressionManager->UnlockPoints,19);
    auto* Persisted=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot,0));
    if (!TestNotNull(TEXT("Iron Man penalty persists the active recovery profile"),Persisted)) return false;
    TestEqual(TEXT("Persisted Iron Man point balance"),Persisted->GetNumberSetting(TEXT("UnlockPoints"),-1),0.0);
    TestEqual(TEXT("Persisted Iron Man unlocked pack count"),Persisted->GetStringArraySetting(TEXT("UnlockedPacks")).Num(),1);
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
    TestEqual(TEXT("Post-game begins on XP source stage"),Switcher->GetActiveWidgetIndex(),0);
    TestNotNull(TEXT("Post-game sequence controller"),Manager->PostGameSequence.Get());
    World->DestroyWorld(false); GEngine->DestroyWorldContext(World);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPostGameSequenceTest,"CockHero.Recovery.PostGameSourceSequence",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPostGameSequenceTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    GEngine->CreateNewWorldContext(EWorldType::Game).SetCurrentWorld(World);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Sequence manager"),Manager)) return false;
    Manager->SessionStats.Strokes=42;
    Manager->SessionStats.SessionsWon=1;
    FRecoveredSessionRewardData Data;
    Data.StartingXP=95;Data.StartingLevel=1;Data.XPToNextLevel=100;Data.StartingUP=3;Data.bWon=true;
    FRecoveredXPSourceData XP;XP.Label=FText::FromString(TEXT("TIME PLAYED"));XP.XPAmount=10;XP.DetailText=FText::FromString(TEXT("1 MIN"));Data.XPSources.Add(XP);
    FRecoveredLevelUpEventData Level;Level.NewLevel=2;Level.Title=TEXT("Rookie");Level.UPReward=2;Level.XPThresholdCrossed=100;Data.LevelUpEvents.Add(Level);
    FRecoveredUPSourceData LevelUP;LevelUP.Label=FText::FromString(TEXT("LEVEL UP"));LevelUP.UPAmount=2;LevelUP.DetailText=FText::FromString(TEXT("LVL 2"));LevelUP.bFromLevelUp=true;Data.UPSources.Add(LevelUP);
    FRecoveredUPSourceData StatsUP;StatsUP.Label=FText::FromString(TEXT("STROKES"));StatsUP.UPAmount=1;StatsUP.DetailText=FText::FromString(TEXT("42 STROKES"));Data.UPSources.Add(StatsUP);
    Manager->bRecoveredSessionFinalized=true;
    Manager->PendingPostGameRewardData=Data;
    UClass* ResultsClass=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/WBP_PostGameFlow_Master.WBP_PostGameFlow_Master_C"));
    if (!TestNotNull(TEXT("Sequence master class"),ResultsClass)) return false;
    auto* Results=NewObject<UUserWidget>(GetTransientPackage(),ResultsClass);
    if (!TestTrue(TEXT("Sequence master initializes"),Results->Initialize())) return false;
    Results->TakeWidget();
    Manager->BindPostGameResultsData(Results);
    auto* Switcher=Cast<UWidgetSwitcher>(Results->GetWidgetFromName(TEXT("WidgetSwitcher")));
    auto* Sequence=Manager->PostGameSequence.Get();
    if (!TestNotNull(TEXT("Sequence controller"),Sequence) || !TestNotNull(TEXT("Sequence switcher"),Switcher)) return false;
    TestEqual(TEXT("Sequence begins on XP"),Sequence->GetStage(),ERecoveredPostGameStage::XP);
    Sequence->AdvanceForTesting();
    TestEqual(TEXT("Source text completes before the XP bar"),Sequence->GetStage(),ERecoveredPostGameStage::XP);
    Sequence->AdvanceForTesting();
    TestEqual(TEXT("Threshold crossing opens level screen"),Sequence->GetStage(),ERecoveredPostGameStage::LevelUp);
    TestEqual(TEXT("Level screen is active"),Switcher->GetActiveWidgetIndex(),1);
    Sequence->AdvanceForTesting();
    TestEqual(TEXT("Level completion resumes XP"),Sequence->GetStage(),ERecoveredPostGameStage::XP);
    TestEqual(TEXT("XP screen resumes after level"),Switcher->GetActiveWidgetIndex(),0);
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    TestEqual(TEXT("XP sources advance to unlock points"),Sequence->GetStage(),ERecoveredPostGameStage::UnlockPoints);
    TestEqual(TEXT("Unlock-point screen is active"),Switcher->GetActiveWidgetIndex(),2);
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    Sequence->AdvanceForTesting();
    TestEqual(TEXT("Unlock-point sources advance to summary"),Sequence->GetStage(),ERecoveredPostGameStage::Summary);
    TestEqual(TEXT("Summary is active after source flow"),Switcher->GetActiveWidgetIndex(),3);
    TestEqual(TEXT("Unlock-point display includes staged sources"),Sequence->GetDisplayedUP(),6);
    World->DestroyWorld(false); GEngine->DestroyWorldContext(World);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPostGameRewardBundleTest,"CockHero.Recovery.PostGameRewardBundle",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPostGameRewardBundleTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    GEngine->CreateNewWorldContext(EWorldType::Game).SetCurrentWorld(World);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Reward bundle manager"),Manager)) return false;
    Manager->SessionStats.SessionDuration=600;
    Manager->SessionStats.Strokes=1000;
    Manager->SessionStats.EnemiesDefeated=40;
    Manager->SessionStats.SuccubiDefeated=30;
    Manager->SessionStats.Edges=4;
    Manager->SessionStats.MaxCombo=800;
    Manager->SessionStats.DrawsAtMaxHeat=20;
    Manager->SessionStats.SessionsWon=1;
    Manager->SessionStats.ActiveModifiers={TEXT("ironman"),TEXT("hardcore")};
    const FRecoveredSessionRewardData Data=Manager->BuildRecoveredSessionRewardData(Manager->CalculateRecoveredSessionXP());
    TestEqual(TEXT("Native presentation XP total"),Data.TotalXPEarned,621);
    TestEqual(TEXT("Presentation XP sources retain six source categories"),Data.XPSources.Num(),6);
    TestEqual(TEXT("Post-game visual level events preserve threshold crossings"),Data.LevelUpEvents.Num(),4);
    TestEqual(TEXT("Post-game simulated level"),Data.EndingLevel,5);
    TestEqual(TEXT("Post-game simulated XP remainder"),Data.EndingXP,81);
    TestEqual(TEXT("Native UP sources preserve reward total"),Data.TotalUPEarned,22);
    TestEqual(TEXT("UP sources include victory and purist rewards"),Data.UPSources.Last().Label.ToString(),FString(TEXT("PURIST")));
    World->DestroyWorld(false); GEngine->DestroyWorldContext(World);
    return true;
}
#endif
