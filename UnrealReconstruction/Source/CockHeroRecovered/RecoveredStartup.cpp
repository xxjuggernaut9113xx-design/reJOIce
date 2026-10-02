#include "RecoveredRules.h"
#include "RecoveredMenu.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "TimerManager.h"
#include "Components/Image.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredEventWidgets.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"

void ARecoveredGlobalManager::BeginPlay() {
    Super::BeginPlay();
    // Uses the reconstruction's isolated save. Original save slots are never loaded.
    CreateMainMenuUI();
#if WITH_DEV_AUTOMATION_TESTS
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
#endif
}

bool ARecoveredGlobalManager::CreateMainMenuUI() {
    StartupError.Reset();
    if (IsValid(MainMenu)) return true;
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

bool ARecoveredGlobalManager::InitializeRecoveredSession() {
    LastSessionError.Reset();
    if (IsValid(SessionScreen)) return true;
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) { LastSessionError=TEXT("Recovered session requires a valid isolated save"); return false; }
    URecoveredSaveGame* Save=Instance->CurrentSave;
    InitializeDifficultyVariables(static_cast<uint8>(Save->GetNumberSetting(TEXT("EdgePacingMultiplierEnum"),0)),static_cast<uint8>(Save->GetNumberSetting(TEXT("StrokeMultiplierEnum"),0)));
    UpdateMinimumBeatInterval(FRecoveredDeviceState());
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
    if (Instance->ChallengeTracker) Instance->ChallengeTracker->StartNewSession();
    BeatTimeline->OnBeatFired.AddUniqueDynamic(this,&ARecoveredGlobalManager::PresentRecoveredBeat);
    OnMetricUpdateRequested.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredMetric);
    OnOutcomeRequested.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredOutcome);
    OnSessionAction.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredSessionAction);
    GetWorldTimerManager().SetTimer(SessionDurationTimer,this,&ARecoveredGlobalManager::SetSessionDuration,1.0f,true,1.0f);
    UE_LOG(LogTemp,Display,TEXT("Recovered session: media decks and gameplay screen initialized"));
    // Event dispatch, dialogue, challenge tracking and device managers are reconstructed separately.
    return RequestNextRecoveredCard(true);
}
void ARecoveredGlobalManager::HandleRecoveredMetric(ERecoveredMetric Metric,int32 Amount) {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->ChallengeTracker) Instance->ChallengeTracker->UpdateMetricWithConditions(Metric,Amount,SessionStats,BeatContext.ActiveModifiers,PlayerVariables.SessionLength,GetWorld() ? GetWorld()->GetTimeSeconds() : 0);
}
