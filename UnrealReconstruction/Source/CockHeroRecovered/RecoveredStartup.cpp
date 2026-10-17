#include "RecoveredRules.h"
#include "RecoveredMenu.h"
#include "RecoveredUnlockStoreWidget.h"
#include "RecoveredEventWidgets.h"
#include "RecoveredDecisionWidgets.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "TimerManager.h"
#include "UnrealClient.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredEventWidgets.h"
#include "RecoveredEdgeManager.h"
#include "RecoveredPostGameSequence.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"

void ARecoveredGlobalManager::BeginPlay() {
    Super::BeginPlay();
    ReloadRecoveredProfile();
    CreateMainMenuUI();
#if WITH_DEV_AUTOMATION_TESTS
    if (FParse::Param(FCommandLine::Get(),TEXT("RecoveredMenuVisualSmoke"))) {
        FTimerHandle VisualTimer;
        GetWorldTimerManager().SetTimer(VisualTimer,[this]() {
            auto* Menu=Cast<URecoveredMainMenu>(MainMenu);
            auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
            if (!Menu || !Instance || !Instance->CurrentSave) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_MENU_VISUAL_SMOKE_FAIL: recovered main menu unavailable"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            FRecoveredLatencyProfile VisualProfile;
            if (!Instance->CurrentSave->GetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_MENU_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            VisualProfile.bIsCalibrated=true;
            if (!Instance->CurrentSave->SetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_MENU_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            Menu->CloseAdultWarning();
            Menu->CloseTutorialSplash();
            Menu->CloseUpdateSplash();
            FTimerHandle CaptureTimer;
            GetWorldTimerManager().SetTimer(CaptureTimer,[this]() {
                const FString ScreenshotPath=FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()/TEXT("RecoveryEvidence/visual-parity/reconstruction-main-menu-repaired.png"));
                FScreenshotRequest::RequestScreenshot(ScreenshotPath,true,false);
                UE_LOG(LogTemp,Display,TEXT("RECOVERED_MENU_VISUAL_SMOKE_CAPTURE_REQUESTED: %s"),*ScreenshotPath);
                FTimerHandle QuitTimer;
                GetWorldTimerManager().SetTimer(QuitTimer,[this]() {
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                },4.0f,false);
            },5.0f,false);
        },1.0f,false);
    }
    if (FParse::Param(FCommandLine::Get(),TEXT("RecoveredUnlockStoreVisualSmoke"))) {
        FTimerHandle VisualTimer;
        GetWorldTimerManager().SetTimer(VisualTimer,[this]() {
            auto* Menu=Cast<URecoveredMainMenu>(MainMenu);
            auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
            if (!Menu || !Instance || !Instance->CurrentSave) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_UNLOCK_STORE_VISUAL_SMOKE_FAIL: recovered main menu unavailable"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            FRecoveredLatencyProfile VisualProfile;
            if (!Instance->CurrentSave->GetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_UNLOCK_STORE_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            VisualProfile.bIsCalibrated=true;
            if (!Instance->CurrentSave->SetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_UNLOCK_STORE_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            Menu->CloseAdultWarning();
            Menu->CloseTutorialSplash();
            Menu->CloseUpdateSplash();
            Menu->OpenUnlockStore();
            FTimerHandle CaptureTimer;
            GetWorldTimerManager().SetTimer(CaptureTimer,[this,Menu]() {
                auto* Store=Cast<URecoveredUnlockStoreWidget>(Menu->LastOpenedScreen);
                if (!Store || !Store->IsInViewport() || Store->GetCreatedPackEntryCount()!=14 || Store->GetCreatedSocialIconCount()!=3) {
                    UE_LOG(LogTemp,Error,TEXT("RECOVERED_UNLOCK_STORE_VISUAL_SMOKE_FAIL: store initialization incomplete"));
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                    return;
                }
                const FString ScreenshotPath=FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()/TEXT("RecoveryEvidence/visual-parity/reconstruction-unlock-store.png"));
                FScreenshotRequest::RequestScreenshot(ScreenshotPath,true,false);
                UE_LOG(LogTemp,Display,TEXT("RECOVERED_UNLOCK_STORE_VISUAL_SMOKE_CAPTURE_REQUESTED: %s"),*ScreenshotPath);
                FTimerHandle QuitTimer;
                GetWorldTimerManager().SetTimer(QuitTimer,[this]() {
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                },4.0f,false);
            },1.0f,false);
        },1.0f,false);
    }
    if (FParse::Param(FCommandLine::Get(),TEXT("RecoveredStoreVisualSmoke"))) {
        FTimerHandle VisualTimer;
        GetWorldTimerManager().SetTimer(VisualTimer,[this]() {
            auto* Menu=Cast<URecoveredMainMenu>(MainMenu);
            auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
            if (!Menu || !Instance || !Instance->CurrentSave) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_STORE_VISUAL_SMOKE_FAIL: recovered store prerequisites unavailable"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            FRecoveredLatencyProfile VisualProfile;
            if (!Instance->CurrentSave->GetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_STORE_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            VisualProfile.bIsCalibrated=true;
            if (!Instance->CurrentSave->SetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_STORE_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            Menu->CloseAdultWarning();
            Menu->CloseTutorialSplash();
            Menu->CloseUpdateSplash();
            PlayerVariables.PlayerCoins=10000;
            if (!SpawnRecoveredStore()) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_STORE_VISUAL_SMOKE_FAIL: recovered store did not open"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            FTimerHandle CaptureTimer;
            GetWorldTimerManager().SetTimer(CaptureTimer,[this]() {
                URecoveredStoreWidget* Store=nullptr;
                for (const TObjectPtr<UUserWidget>& Overlay:EventOverlays) {
                    if (auto* Candidate=Cast<URecoveredStoreWidget>(Overlay)) { Store=Candidate;break; }
                }
                if (!Store || !Store->IsInViewport()) {
                    UE_LOG(LogTemp,Error,TEXT("RECOVERED_STORE_VISUAL_SMOKE_FAIL: recovered store viewport initialization incomplete"));
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                    return;
                }
                const FString ScreenshotPath=FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()/TEXT("RecoveryEvidence/visual-parity/reconstruction-store.png"));
                FScreenshotRequest::RequestScreenshot(ScreenshotPath,true,false);
                UE_LOG(LogTemp,Display,TEXT("RECOVERED_STORE_VISUAL_SMOKE_CAPTURE_REQUESTED: %s"),*ScreenshotPath);
                FTimerHandle QuitTimer;
                GetWorldTimerManager().SetTimer(QuitTimer,[this]() {
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                },4.0f,false);
            },1.0f,false);
        },1.0f,false);
    }
    if (FParse::Param(FCommandLine::Get(),TEXT("RecoveredVoiceSettingsVisualSmoke"))) {
        FTimerHandle VisualTimer;
        GetWorldTimerManager().SetTimer(VisualTimer,[this]() {
            auto* Menu=Cast<URecoveredMainMenu>(MainMenu);
            auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
            if (!Menu || !Instance || !Instance->CurrentSave) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_VOICE_SETTINGS_VISUAL_SMOKE_FAIL: recovered main menu unavailable"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            FRecoveredLatencyProfile VisualProfile;
            if (!Instance->CurrentSave->GetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_VOICE_SETTINGS_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            VisualProfile.bIsCalibrated=true;
            if (!Instance->CurrentSave->SetLatencyProfile(VisualProfile)) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_VOICE_SETTINGS_VISUAL_SMOKE_FAIL: recovery calibration profile could not be staged"));
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            Menu->CloseAdultWarning();
            Menu->CloseTutorialSplash();
            Menu->CloseUpdateSplash();
            Menu->OpenSettings();
            FTimerHandle CaptureTimer;
            GetWorldTimerManager().SetTimer(CaptureTimer,[this,Menu]() {
                auto* Settings=Cast<URecoveredSettingsMenu>(Menu->LastOpenedScreen);
                auto* Voice=Settings ? Cast<URecoveredVoiceSettings>(Settings->GetWidgetFromName(TEXT("VoicelineSettingsMenu"))) : nullptr;
                if (!Settings || !Settings->IsInViewport() || !Voice || Voice->GetVoicePackEntryCount()!=4 || Voice->VoicePacks.Num()!=4 || !Voice->SelectedEntryWidget) {
                    UE_LOG(LogTemp,Error,TEXT("RECOVERED_VOICE_SETTINGS_VISUAL_SMOKE_FAIL: voice settings initialization incomplete"));
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                    return;
                }
                Settings->OpenVoiceTab();
                FTimerHandle VoiceTabTimer;
                GetWorldTimerManager().SetTimer(VoiceTabTimer,[this,Settings,Voice]() {
                    auto* Switcher=Cast<UWidgetSwitcher>(Settings ? Settings->GetWidgetFromName(TEXT("WidgetSwitcher")) : nullptr);
                    if (!Settings || !Settings->IsInViewport() || !Voice || !Switcher || Switcher->GetActiveWidgetIndex()!=3) {
                        UE_LOG(LogTemp,Error,TEXT("RECOVERED_VOICE_SETTINGS_VISUAL_SMOKE_FAIL: voice tab did not become active"));
                        if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                        return;
                    }
                    const FString ScreenshotPath=FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()/TEXT("RecoveryEvidence/visual-parity/reconstruction-voiceline-settings.png"));
                    FScreenshotRequest::RequestScreenshot(ScreenshotPath,true,false);
                    UE_LOG(LogTemp,Display,TEXT("RECOVERED_VOICE_SETTINGS_VISUAL_SMOKE_CAPTURE_REQUESTED: %s"),*ScreenshotPath);
                    FTimerHandle QuitTimer;
                    GetWorldTimerManager().SetTimer(QuitTimer,[this]() {
                        if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                    },4.0f,false);
                },0.25f,false);
            },1.0f,false);
        },1.0f,false);
    }
    if (FParse::Param(FCommandLine::Get(),TEXT("RecoveredSessionSmoke"))) {
        // Only this explicit test switch starts a session without user input.
        FTimerHandle SmokeTimer;
        GetWorldTimerManager().SetTimer(SmokeTimer,[this]() {
            bool bStarted=InitializeRecoveredSession();
            if (bStarted && FParse::Param(FCommandLine::Get(),TEXT("RecoveredPaceSmoke"))) {
                auto* Image=Cast<UImage>(SessionScreen->GetWidgetFromName(TEXT("MainImage")));
                bStarted=bStarted && MediaPlayback && MediaPlayback->CurrentTexture && Image && Image->GetBrush().GetResourceObject()==MediaPlayback->CurrentTexture;
                if (bStarted) { UE_LOG(LogTemp,Display,TEXT("RECOVERED_PACE_MEDIA_SMOKE_PASS: beat queue=%d"),BeatTimeline->BeatQueue.Num()); }
                if (bStarted && FParse::Param(FCommandLine::Get(),TEXT("RecoveredBeatPresentationSmoke"))) {
                    for (const auto& Event:BeatTimeline->BeatQueue) if (Event.CustomMultiplier>=0) { BeatTimeline->AdvanceTo(Event.AbsoluteFireTime);break; }
                    TArray<UUserWidget*> Widgets;UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this,Widgets,URecoveredBeatWidget::StaticClass(),true);
                    bool Playing=false;
                    for (UUserWidget* Widget:Widgets) if (auto* Class=Cast<UWidgetBlueprintGeneratedClass>(Widget->GetClass())) for (UWidgetAnimation* Animation:Class->Animations) Playing |= Widget->IsAnimationPlaying(Animation);
                    bStarted=Widgets.Num()>0 && Playing;
                    if (bStarted) { UE_LOG(LogTemp,Display,TEXT("RECOVERED_BEAT_PRESENTATION_SMOKE_PASS: %d animated widgets"),Widgets.Num()); }
                    else LastSessionError=TEXT("Beat delegate did not create a playing recovered animation");
                }
                BeatTimeline->StopSequence();
            }
            if (bStarted) { UE_LOG(LogTemp,Display,TEXT("RECOVERED_SESSION_SMOKE_PASS")); }
            else { UE_LOG(LogTemp,Error,TEXT("RECOVERED_SESSION_SMOKE_FAIL: %s"),*LastSessionError); }
            if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
        },0.25f,false);
    }
    const bool bMercyDecisionVisualSmoke=FParse::Param(FCommandLine::Get(),TEXT("RecoveredMercyDecisionVisualSmoke"));
    const bool bTemptationDecisionVisualSmoke=FParse::Param(FCommandLine::Get(),TEXT("RecoveredTemptationDecisionVisualSmoke"));
    if (bMercyDecisionVisualSmoke || bTemptationDecisionVisualSmoke) {
        FTimerHandle VisualTimer;
        GetWorldTimerManager().SetTimer(VisualTimer,[this,bMercyDecisionVisualSmoke]() {
            bool bStarted=InitializeRecoveredSession();
            if (bStarted && IsValid(MainMenu)) MainMenu->RemoveFromParent();
            if (bStarted) {
                if (bMercyDecisionVisualSmoke) StartMercyEvent();
                else StartTemptationEvent();
            }
            if (!bStarted) {
                UE_LOG(LogTemp,Error,TEXT("RECOVERED_DECISION_VISUAL_SMOKE_FAIL: %s"),*LastSessionError);
                if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                return;
            }
            FTimerHandle CaptureTimer;
            GetWorldTimerManager().SetTimer(CaptureTimer,[this,bMercyDecisionVisualSmoke]() {
                const bool bExpectedOverlay=EventOverlays.ContainsByPredicate([bMercyDecisionVisualSmoke](const TObjectPtr<UUserWidget>& Overlay) {
                    return bMercyDecisionVisualSmoke ? Cast<URecoveredMercyEventWidget>(Overlay)!=nullptr : Cast<URecoveredTemptationEventWidget>(Overlay)!=nullptr;
                });
                const int32 ExpectedBackground=bMercyDecisionVisualSmoke ? 2 : 9;
                if (!bExpectedOverlay || CurrentBeatBackgroundStyle!=ExpectedBackground) {
                    UE_LOG(LogTemp,Error,TEXT("RECOVERED_DECISION_VISUAL_SMOKE_FAIL: overlay or background state unavailable"));
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                    return;
                }
                const FString ScreenshotName=bMercyDecisionVisualSmoke ? TEXT("reconstruction-mercy-decision.png") : TEXT("reconstruction-temptation-decision.png");
                const FString ScreenshotPath=FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()/TEXT("RecoveryEvidence/visual-parity")/ScreenshotName);
                FScreenshotRequest::RequestScreenshot(ScreenshotPath,true,false);
                UE_LOG(LogTemp,Display,TEXT("RECOVERED_DECISION_VISUAL_SMOKE_CAPTURE_REQUESTED: %s"),*ScreenshotPath);
                FTimerHandle QuitTimer;
                GetWorldTimerManager().SetTimer(QuitTimer,[this]() {
                    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->ConsoleCommand(TEXT("quit"));
                },4.0f,false);
            },1.0f,false);
        },0.25f,false);
    }
#endif
}

void ARecoveredGlobalManager::ReloadRecoveredProfile() {
    // Uses the reconstruction's isolated save. Original save slots are never loaded.
    LoadLifetimeStats();
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) {
            BeatSoundBank=FName(*Instance->CurrentSave->GetStringSetting(TEXT("BeatSoundBank"),TEXT("Default")));
            VoicePack=FName(*Instance->CurrentSave->GetStringSetting(TEXT("VoicePack"),TEXT("Default")));
            BeatContext.ActiveModifiers.Reset();
            if (Instance->CurrentSave->HasSetting(TEXT("EnabledModifiers")) && Instance->ProgressionManager) {
                for (const FName ModifierID:Instance->ProgressionManager->EnabledModifiers) BeatContext.ActiveModifiers.Add(ModifierID.ToString());
            } else {
                BeatContext.ActiveModifiers=Instance->CurrentSave->GetStringArraySetting(TEXT("ActiveModifiers"));
            }
        }
        if (Instance->ProgressionManager && Instance->ChallengeTracker) {
            Instance->ProgressionManager->OnMetricUpdateRequested.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleProgressionMetric);
        }
    }
}

bool ARecoveredGlobalManager::CreateMainMenuUI() {
    StartupError.Reset();
    // A removed-from-viewport widget is still IsValid; only reuse the menu if
    // it is actually on screen. Otherwise drop the stale reference and build fresh.
    if (IsValid(MainMenu) && MainMenu->IsInViewport()) return true;
    MainMenu = nullptr;
    APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0);
    if (!Controller) { StartupError=TEXT("Main menu requires a local player controller"); return false; }
    UClass* MenuClass=LoadClass<URecoveredMainMenu>(nullptr,TEXT("/Game/Recovery/UI/MainMenu.MainMenu_C"));
    if (!MenuClass) { StartupError=TEXT("Recovered MainMenu class is unavailable"); return false; }
    MainMenu=CreateWidget<UUserWidget>(Controller,MenuClass);
    if (!MainMenu) { StartupError=TEXT("Could not construct the recovered main menu"); return false; }
    MainMenu->AddToViewport(0);
    UE_LOG(LogTemp,Display,TEXT("Recovered startup: main menu added to viewport"));
    FInputModeGameAndUI Input;
    Input.SetWidgetToFocus(MainMenu->TakeWidget());
    Input.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    Controller->SetInputMode(Input);
    Controller->bShowMouseCursor=true;
    return true;
}

bool ARecoveredGlobalManager::ReturnToMainMenu() {
    // Full session teardown before returning: stop playback, clear every
    // session timer, unbind every session delegate, remove session widgets,
    // then rebuild the main menu. Without this, looping timers and stale
    // delegates survive the menu return and duplicate on the next session.
    if (BeatTimeline) BeatTimeline->StopSequence();
    if (MediaPlayback) MediaPlayback->SetPaused(true);
    if (PostGameSequence) {
        PostGameSequence->Stop();
        PostGameSequence = nullptr;
    }
    if (IsValid(EdgingManager)) {
        EdgingManager->ClearRecoveredEdgeHold();
        EdgingManager->Destroy();
        EdgingManager=nullptr;
    }
    FTimerManager& Timers = GetWorldTimerManager();
    Timers.ClearTimer(SessionDurationTimer);
    Timers.ClearTimer(StoreCooldownTimer);
    Timers.ClearTimer(ResupplyStoreTimerHandle);
    Timers.ClearTimer(ResupplyLastItemTimerHandle);
    Timers.ClearTimer(DecreaseHeatLastItemTimerHandle);
    Timers.ClearTimer(BreakLastItemTimerHandle);
    Timers.ClearTimer(SlowdownLastItemTimerHandle);
    Timers.ClearTimer(CumChanceLastItemTimerHandle);
    Timers.ClearTimer(BonerPillCooldownTimerHandle);
    Timers.ClearTimer(TemptationCooldownTimer);
    Timers.ClearTimer(DefensiveItemUsageTimerHandle);
    Timers.ClearTimer(OutcomeContinuationTimer);
    Timers.ClearTimer(IdleTimer);
    Timers.ClearTimer(MercyCooldownTimer);
    Timers.ClearTimer(TauntCooldownTimer);
    if (BeatTimeline) {
        BeatTimeline->OnSequenceEnd.RemoveDynamic(this, &ARecoveredGlobalManager::CompleteBeatSequence);
        BeatTimeline->OnBeatFired.RemoveDynamic(this, &ARecoveredGlobalManager::PresentRecoveredBeat);
        BeatTimeline->OnBeatFired.RemoveDynamic(this, &ARecoveredGlobalManager::HandleRecoveredDeviceBeat);
        BeatTimeline->OnBeatHitCenter.RemoveDynamic(this, &ARecoveredGlobalManager::HandleBeatHitCenter);
    }
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->DeviceManager) Instance->DeviceManager->OnDeviceStateChanged.RemoveDynamic(this, &ARecoveredGlobalManager::HandleRecoveredDeviceStateChanged);
    }
    OnMetricUpdateRequested.RemoveDynamic(this, &ARecoveredGlobalManager::HandleRecoveredMetric);
    OnOutcomeRequested.RemoveDynamic(this, &ARecoveredGlobalManager::HandleRecoveredOutcome);
    OnSessionAction.RemoveDynamic(this, &ARecoveredGlobalManager::HandleRecoveredSessionAction);
    for (const auto& Overlay : EventOverlays) {
        if (IsValid(Overlay)) Overlay->RemoveFromParent();
    }
    EventOverlays.Reset();
    if (IsValid(SessionScreen)) {
        SessionScreen->RemoveFromParent();
        SessionScreen = nullptr;
    }
    // Reset ALL per-session state; lifetime stats and progression persist.
    bRecoveredSessionFinalized = false;
    bRecoveredSessionCompletionStatsPersisted = false;
    SessionStats = FRecoveredSessionStats();
    PlayerVariables = FRecoveredPlayerVariables();
    BeatContext = FRecoveredBeatContext();
    HeatLevel = 10.0;
    CumMeterPercentage = 0;
    LootBarPercentage = 0;
    bStopSequence = false;
    OwnedItemCounts.Reset();
    PendingNotifications.Reset();
    bStoreOnCooldown = false;
    bIsMercyOnCooldown = false;
    bIsTemptationOnCooldown = false;
    bBrainMelterEnabled = false;
    SuccubusShields = 0;
    bShieldToggled = false;
    bCanUseSlowdown = true;
    bCanUseBonerPill = true;
    EdgeStreak = 0;
    SessionDrawsAtMaxHeat = 0;
    MasterEdgeBreakDuration = 10.0;
    EdgeBreakDurationScaled = 1.0;
    CurrentInventoryTab = 0;
    LastEdgeItemUseResult = ERecoveredEdgeItemUseResult::NoEdgesAvailable;
    LastResupplyItemUseResult = ERecoveredResupplyItemUseResult::NoResupplyAvailable;
    LastDispatchedEvent = NAME_None;
    LastSessionError.Reset();
    return CreateMainMenuUI();
}

bool ARecoveredGlobalManager::InitializeRecoveredSession() {
    LastSessionError.Reset();
    if (IsValid(SessionScreen)) return true;
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) { LastSessionError=TEXT("Recovered session requires a valid isolated save"); return false; }
    URecoveredSaveGame* Save=Instance->CurrentSave;
    InitializeDifficultyVariables(static_cast<uint8>(Save->GetNumberSetting(TEXT("EdgePacingMultiplierEnum"),0)),static_cast<uint8>(Save->GetNumberSetting(TEXT("StrokeMultiplierEnum"),0)));
    BindRecoveredBrainMelterInterval();
    UpdateMinimumBeatInterval(Instance->DeviceManager ? Instance->DeviceManager->GetGameplayDeviceState() : FRecoveredDeviceState());
    BeatContext.ActiveModifiers=Save->GetStringArraySetting(TEXT("ActiveModifiers"));
    Rules=LoadObject<URecoveredRulesAsset>(nullptr,TEXT("/Game/Recovery/Definitions/DA_GameRules.DA_GameRules"));
    HeatCategoryDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_HeatCategories.DT_HeatCategories"));
    if (!Rules || !HeatCategoryDataTable) { LastSessionError=TEXT("Recovered session rule assets are missing"); return false; }
    if (!LoadMediaPack(MediaManifestPath,Save->GetStringArraySetting(TEXT("ExcludedTags")))) return false;
    APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0);
    UClass* ScreenClass=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/UI_Manager.UI_Manager_C"));
    if (!Controller || !ScreenClass) { LastSessionError=TEXT("Recovered gameplay screen or controller is unavailable"); return false; }
    SessionScreen=CreateWidget<UUserWidget>(Controller,ScreenClass);
    if (!SessionScreen) { LastSessionError=TEXT("Could not construct the recovered gameplay screen"); return false; }
    SessionScreen->AddToViewport(0);
    UClass* EdgeClass=LoadClass<ARecoveredEdgeManager>(nullptr,TEXT("/Game/NewSetup/BP_EdgeManager.BP_EdgeManager_C"));
    EdgingManager=GetWorld()->SpawnActor<ARecoveredEdgeManager>(EdgeClass && EdgeClass->IsChildOf(ARecoveredEdgeManager::StaticClass()) ? EdgeClass : ARecoveredEdgeManager::StaticClass());
    if (!IsValid(EdgingManager)) {
        SessionScreen->RemoveFromParent();
        SessionScreen=nullptr;
        LastSessionError=TEXT("Recovered edge manager could not be constructed");
        return false;
    }
    EdgingManager->SetRecoveredGlobalManager(this);
    if (Instance->ChallengeTracker) Instance->ChallengeTracker->StartNewSession();
    ApplySavedCalibrationToTimeline();
    BeatTimeline->OnBeatFired.AddUniqueDynamic(this,&ARecoveredGlobalManager::PresentRecoveredBeat);
    BeatTimeline->OnBeatFired.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredDeviceBeat);
    if (Instance->DeviceManager) Instance->DeviceManager->OnDeviceStateChanged.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredDeviceStateChanged);
    OnMetricUpdateRequested.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredMetric);
    OnOutcomeRequested.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredOutcome);
    OnSessionAction.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredSessionAction);
    GetWorldTimerManager().SetTimer(SessionDurationTimer,this,&ARecoveredGlobalManager::SetSessionDuration,1.0f,true,1.0f);
    UE_LOG(LogTemp,Display,TEXT("Recovered session: media decks and gameplay screen initialized"));
    const bool bStarted=RequestNextRecoveredCard(true);
    if (!bStarted) {
        const FString Failure=LastSessionError;
        ReturnToMainMenu();
        LastSessionError=Failure;
    } else {
        FInputModeGameAndUI Input;Input.SetWidgetToFocus(SessionScreen->TakeWidget());Controller->SetInputMode(Input);
    }
    return bStarted;
}
void ARecoveredGlobalManager::HandleRecoveredMetric(ERecoveredMetric Metric,int32 Amount) {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->ChallengeTracker) Instance->ChallengeTracker->UpdateMetricWithConditions(Metric,Amount,SessionStats,BeatContext.ActiveModifiers,PlayerVariables.SessionLength,GetWorld() ? GetWorld()->GetTimeSeconds() : 0);
}

void ARecoveredGlobalManager::HandleProgressionMetric(ERecoveredMetric Metric, int32 Amount) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredChallengeTracker* Tracker = Instance ? Instance->ChallengeTracker.Get() : nullptr;
    if (!Tracker) return;
    const int32 Elapsed = SessionStats.SessionDuration;
    const float WorldSeconds = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f;
    Tracker->UpdateMetricWithConditions(Metric, Amount, SessionStats, SessionStats.ActiveModifiers, Elapsed, WorldSeconds);
}
