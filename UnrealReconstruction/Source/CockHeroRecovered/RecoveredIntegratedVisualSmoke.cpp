#include "RecoveredIntegratedVisualSmoke.h"
#include "RecoveredRules.h"
#include "RecoveredMenu.h"
#include "RecoveredModesWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Framework/Application/SlateApplication.h"
#include "Input/Events.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "GameFramework/PlayerController.h"
#include "MediaPlayer.h"
#include "TimerManager.h"
#include "UnrealClient.h"
#include "UObject/StrongObjectPtr.h"

#if WITH_DEV_AUTOMATION_TESTS
namespace {
struct FIntegratedSmoke : TSharedFromThis<FIntegratedSmoke> {
    TWeakObjectPtr<ARecoveredGlobalManager> Manager;
    FString Slot, Beatmap;
    FString OriginalSlot;
    TStrongObjectPtr<URecoveredSaveGame> OriginalSave;
    int32 Stage=0;
    bool bCreated=false;
    void Next(float Delay=2.f) {
        if (auto* Actor=Manager.Get()) {
            FTimerHandle Timer;
            Actor->GetWorldTimerManager().SetTimer(Timer,[Self=AsShared()](){ Self->Step(); },Delay,false);
        }
    }
    void Finish(bool Passed,const FString& Detail) {
        auto* Actor=Manager.Get();if (!Actor) return;
        UE_LOG(LogTemp,Display,TEXT("RECOVERED_INTEGRATED_VISUAL_SMOKE_%s: stage%d %s"),Passed?TEXT("PASS"):TEXT("FAIL"),Stage,*Detail);
        Actor->ReturnToMainMenu();
        if (auto* Instance=Cast<URecoveredGameInstance>(Actor->GetGameInstance())) {
            if (OriginalSave.IsValid()) { Instance->CurrentSave=OriginalSave.Get();Instance->ActiveRecoverySlot=OriginalSlot; }
        }
        if (bCreated) UGameplayStatics::DeleteGameInSlot(Slot,0);
        if (auto* Controller=UGameplayStatics::GetPlayerController(Actor,0)) Controller->ConsoleCommand(TEXT("quit"));
    }
    bool Check(bool Condition,const TCHAR* Detail) {
        if (!Condition) Finish(false,Detail);
        else UE_LOG(LogTemp,Display,TEXT("RECOVERED_INTEGRATED_CHECK_PASS: %s"),Detail);
        return Condition;
    }
    bool Click(UUserWidget* Screen,const TCHAR* Name) {
        auto* Button=Screen?Cast<UButton>(Screen->GetWidgetFromName(FName(Name))):nullptr;
        if (!Check(Button!=nullptr,Name)) return false;
        Button->OnClicked.Broadcast();return true;
    }
    void Capture(const TCHAR* Name) {
        const FString Path=FPaths::ConvertRelativePathToFull(FPaths::ProjectDir()/TEXT("RecoveryEvidence/visual-parity")/FString::Printf(TEXT("integrated-%s.png"),Name));
        if (auto* Actor=Manager.Get()) {
            FTimerHandle CaptureTimer;
            Actor->GetWorldTimerManager().SetTimer(CaptureTimer,[Path]() {
                FScreenshotRequest::RequestScreenshot(Path,true,false);
                UE_LOG(LogTemp,Display,TEXT("RECOVERED_INTEGRATED_CAPTURE_REQUESTED: %s"),*Path);
            },.25f,false);
        }
    }
    void ClickAfterCapture(UUserWidget* Screen,const TCHAR* Name) {
        if (auto* Actor=Manager.Get()) {
            FTimerHandle ClickTimer;const FString ButtonName(Name);TWeakObjectPtr<UUserWidget> Target(Screen);
            Actor->GetWorldTimerManager().SetTimer(ClickTimer,[Self=AsShared(),Target,ButtonName]() { Self->Click(Target.Get(),*ButtonName); },.75f,false);
        }
    }
    void Step() {
        auto* Actor=Manager.Get();if (!Actor) return;
        auto* Instance=Cast<URecoveredGameInstance>(Actor->GetGameInstance());
        if (!Check(Instance && Instance->CurrentSave,TEXT("Active recovery profile"))) return;
        switch (Stage++) {
        case 0: {
            if (!Check(Slot.StartsWith(URecoveredGameInstance::GetNamedRecoverySlotPrefix()) && URecoveredGameInstance::IsRecoverySlotNameValid(Slot) && !UGameplayStatics::DoesSaveGameExist(Slot,0),TEXT("Explicit isolated slot is valid and absent"))) return;
            OriginalSave.Reset(Instance->CurrentSave.Get());OriginalSlot=Instance->ActiveRecoverySlot;
            Instance->CurrentSave=DuplicateObject<URecoveredSaveGame>(Instance->CurrentSave,Instance);
            Instance->ActiveRecoverySlot=Slot;
            FRecoveredLatencyProfile Calibration;Calibration.bIsCalibrated=true;Instance->CurrentSave->SetLatencyProfile(Calibration);
            Instance->CurrentSave->SetNumberSetting(TEXT("LastObjectiveIndex_Classic"),0);
            Instance->CurrentSave->SetIntArraySetting(TEXT("LastSavedHotBarItems"),{8,8,8,8,8});
            if (!Check(Instance->SaveRecoveredState(),TEXT("Isolated profile created without index mutation"))) return;
            bCreated=true;
            if (auto* Menu=Cast<URecoveredMainMenu>(Actor->MainMenu)) { Menu->CloseAdultWarning();Menu->CloseTutorialSplash();Menu->CloseUpdateSplash(); }
            Capture(TEXT("main-menu"));break;
        }
        case 1:
            if (!Click(Actor->MainMenu,TEXT("StartGameButton"))) return;
            break;
        case 2:
            if (!Check(Actor->ModesScreen && Actor->ModesScreen->IsInViewport(),TEXT("Main menu opens real modes chooser"))) return;
            Capture(TEXT("modes"));
            ClickAfterCapture(Actor->ModesScreen,TEXT("StartClassic"));
            break;
        case 3:
            Capture(TEXT("classic-loadout"));
            ClickAfterCapture(Actor->ModesScreen,TEXT("ConfirmLoadout"));
            break;
        case 4: {
            auto* Menu=Cast<URecoveredMainMenu>(Actor->MainMenu);
            if (!Click(Menu?Menu->LastOpenedScreen.Get():nullptr,TEXT("EasyDifficultyButton"))) return;
            break;
        }
        case 5: {
            if (!Check(Actor->SessionScreen && Actor->SessionScreen->IsInViewport() && Actor->ClassicObjectiveRuntime.bActive,TEXT("Classic difficulty initializes actual session"))) return;
            auto* FinishButton=Cast<UButton>(Actor->SessionScreen->GetWidgetFromName(TEXT("CumTextButton_1")));
            auto* FinishCaption=FinishButton?Cast<UTextBlock>(FinishButton->GetContent()):nullptr;
            if (!Check(FinishCaption && FinishCaption->GetText().ToString()==TEXT("Finish: Enter"),TEXT("Visible completion button caption matches Enter input"))) return;
            Actor->CumMeterPercentage=1;Actor->TriggerMeterOverride();
            if (!Check(Actor->PlayerVariables.bIsAllowedToCum,TEXT("Classic meter producer opens release window"))) return;
            Capture(TEXT("classic-release"));break;
        }
        case 6: {
            FSlateApplication::Get().SetKeyboardFocus(Actor->SessionScreen->TakeWidget(),EFocusCause::SetDirectly);
            FSlateApplication::Get().ProcessKeyDownEvent(FKeyEvent(EKeys::Enter,FModifierKeysState(),0,false,0,0));
            if (!Check(Actor->PlayerVariables.bHasCame && Actor->SessionStats.SessionsWon>0,TEXT("Actual Slate Enter reaches winning outcome"))) return;
            Capture(TEXT("classic-outcome"));break;
        }
        case 7:
            Actor->ReturnToMainMenu();
            if (!Click(Actor->MainMenu,TEXT("StartGameButton"))) return;
            if (!Click(Actor->ModesScreen,TEXT("StartTower"))) return;
            break;
        case 8:
            Capture(TEXT("tower-loadout"));
            ClickAfterCapture(Actor->ModesScreen,TEXT("ConfirmLoadout"));
            break;
        case 9:
            if (!Check(Actor->TowerRuntime && Actor->TowerRuntime->Phase==ERecoveredRoundPhase::RoundSelection && Actor->TowerRuntime->CurrentOptions.Num()==3,TEXT("Tower creates three native-backed draft choices"))) return;
            Capture(TEXT("tower-draft"));break;
        case 10:
            if (!Click(Actor->ModesScreen,TEXT("Draft0"))) return;
            if (!Check(Actor->TowerRuntime->Phase==ERecoveredRoundPhase::Playing || Actor->TowerRuntime->Phase==ERecoveredRoundPhase::BossRound,TEXT("Tower draft button starts actual round"))) return;
            Capture(TEXT("tower-playing"));break;
        case 11:
            Actor->ReturnToMainMenu();
            if (!Check(IFileManager::Get().FileExists(*Beatmap),TEXT("Explicit source beatmap exists"))) return;
            if (!Check(Actor->StartPlaylistSession({Beatmap}),TEXT("Source beatmap initializes actual Playlist"))) return;
            break;
        case 12:
            if (!Check(Actor->ActiveRecoveredMode==2 && Actor->PlaylistRuntime->bPlaying,TEXT("Playlist remains active after asynchronous audio open"))) return;
            Next(4.f);return;
        case 13:
            if (!Check(Actor->PlaylistAudio && Actor->PlaylistAudio->IsPlaying() && Actor->PlaylistRuntime->GetAudioTime()>0,TEXT("Playlist audio transport is playing beyond intro"))) return;
            if (!Click(Actor->ModesScreen,TEXT("CloseModes"))) return;
            FSlateApplication::Get().SetKeyboardFocus(Actor->SessionScreen->TakeWidget(),EFocusCause::SetDirectly);
            FSlateApplication::Get().ProcessKeyDownEvent(FKeyEvent(EKeys::SpaceBar,FModifierKeysState(),0,false,0,0));
            if (!Check(Actor->BeatTimeline && !Actor->BeatTimeline->bIsRunning,TEXT("Playlist ignores manual normal-card draws"))) return;
            Capture(TEXT("playlist-playing"));break;
        case 14: {
            Actor->ReturnToMainMenu();
            auto* Menu=Cast<URecoveredMainMenu>(Actor->MainMenu);
            if (!Check(Menu!=nullptr,TEXT("Returned main menu exists"))) return;
            Menu->OpenUnlockStore();
            if (!Check(Menu->LastOpenedScreen && Menu->LastOpenedScreen->IsInViewport(),TEXT("Unlock store navigation opens visible screen"))) return;
            Capture(TEXT("unlock-store"));break;
        }
        case 15: {
            Actor->ReturnToMainMenu();
            if (!Check(Instance->SaveRecoveredState(),TEXT("Isolated profile saved after mode transitions"))) return;
            auto* Reloaded=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot,0));
            if (!Check(Reloaded && Reloaded->StateJson==Instance->CurrentSave->StateJson,TEXT("Profile disk roundtrip preserves complete state"))) return;
            Capture(TEXT("returned-menu"));break;
        }
        default:Finish(true,TEXT("Menu, loadout, Classic Enter, Tower draft, Playlist audio and isolated profile roundtrip completed"));return;
        }
        Next();
    }
};
}
#endif
void StartRecoveredIntegratedVisualSmoke(ARecoveredGlobalManager& Manager) {
#if WITH_DEV_AUTOMATION_TESTS
    if (!FParse::Param(FCommandLine::Get(),TEXT("RecoveredIntegratedVisualSmoke"))) return;
    auto State=MakeShared<FIntegratedSmoke>();State->Manager=&Manager;
    FParse::Value(FCommandLine::Get(),TEXT("RecoveredIntegratedSmokeSlot="),State->Slot);
    FParse::Value(FCommandLine::Get(),TEXT("RecoveredIntegratedSmokeBeatmap="),State->Beatmap);
    State->Next(1.f);
#endif
}
