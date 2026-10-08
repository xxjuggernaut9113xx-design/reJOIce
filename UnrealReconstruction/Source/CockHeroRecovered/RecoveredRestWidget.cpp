#include "RecoveredRestWidget.h"

#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Engine/World.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ARecoveredGlobalManager* URecoveredRestWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredRestWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredRestWidget::HandleCancelBreakClicked);
}

void URecoveredRestWidget::NativeConstruct() {
    Super::NativeConstruct();
    SetIsFocusable(true);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredRestWidget::HandleCancelBreakClicked);
    BeginRecoveredBreak(ResolveRecoveredGlobalManager());
    SetKeyboardFocus();
}

void URecoveredRestWidget::NativeDestruct() {
    if (UWorld* World=GetWorld()) World->GetTimerManager().ClearTimer(UpdateProgressTimerHandle);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredRestWidget::HandleCancelBreakClicked);
    Super::NativeDestruct();
}

void URecoveredRestWidget::BeginRecoveredBreak(ARecoveredGlobalManager* Manager) {
    bBreakFinished=false;
    bBreakActive=false;
    bIsButtonInputAllowed=true;
    ActiveManager=Manager;
    UWorld* World=GetWorld();
    if (!World || !Manager) return;
    if (Manager->BeatTimeline) Manager->BeatTimeline->PauseSequence();
    Manager->PlayerVariables.bCanUseItems=false;
    Manager->PlayerVariables.bCanDraw=false;
    BreakDuration=FMath::Max(Manager->MasterBreakDuration,0.01);
    CurrentProgress=0.0;
    if (auto* Progress=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_0")))) Progress->SetPercent(0.0f);
    StartTime=World->GetUnpausedTimeSeconds();
    World->GetTimerManager().SetTimer(UpdateProgressTimerHandle,this,&URecoveredRestWidget::UpdateProgress,0.01f,true,0.0f);
    bBreakActive=true;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"),Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage"))));
    }
}

void URecoveredRestWidget::UpdateProgress() {
    UWorld* World=GetWorld();
    if (!World || !bBreakActive || bBreakFinished) return;
    CurrentProgress=FMath::Clamp((World->GetUnpausedTimeSeconds()-StartTime)/FMath::Max(BreakDuration,0.01),0.0,1.0);
    if (auto* Progress=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_0")))) Progress->SetPercent(static_cast<float>(CurrentProgress));
    if (CurrentProgress>=1.0) CompleteRecoveredBreak();
}

void URecoveredRestWidget::CancelRecoveredBreak() {
    if (!bIsButtonInputAllowed || bBreakFinished) return;
    bIsButtonInputAllowed=false;
    CompleteRecoveredBreak();
}

bool URecoveredRestWidget::IsRecoveredBreakActive() const {
    return bBreakActive && !bBreakFinished;
}

FReply URecoveredRestWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {
    if (InKeyEvent.GetKey()==EKeys::G && bIsButtonInputAllowed && !bBreakFinished) {
        CancelRecoveredBreak();
        return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry,InKeyEvent);
}

void URecoveredRestWidget::HandleCancelBreakClicked() {
    CancelRecoveredBreak();
}

void URecoveredRestWidget::CompleteRecoveredBreak() {
    if (bBreakFinished) return;
    bBreakFinished=true;
    bBreakActive=false;
    if (UWorld* World=GetWorld()) World->GetTimerManager().ClearTimer(UpdateProgressTimerHandle);
    ARecoveredGlobalManager* Manager=ActiveManager.Get();
    if (!Manager) Manager=ResolveRecoveredGlobalManager();
    if (Manager) {
        Manager->RequestNextRecoveredCard(true);
        Manager->EventOverlays.Remove(this);
    }
    RemoveFromParent();
}
