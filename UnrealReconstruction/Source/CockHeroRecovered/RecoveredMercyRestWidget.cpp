#include "RecoveredMercyRestWidget.h"

#include "RecoveredDeviceInterface.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ARecoveredGlobalManager* URecoveredMercyRestWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredMercyRestWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredMercyRestWidget::HandleCancelBreakClicked);
}

void URecoveredMercyRestWidget::NativeConstruct() {
    Super::NativeConstruct();
    SetIsFocusable(true);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredMercyRestWidget::HandleCancelBreakClicked);
    BeginRecoveredMercyRest(ResolveRecoveredGlobalManager());
    SetKeyboardFocus();
}

void URecoveredMercyRestWidget::NativeDestruct() {
    if (UWorld* World=GetWorld()) World->GetTimerManager().ClearTimer(UpdateProgressTimerHandle);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredMercyRestWidget::HandleCancelBreakClicked);
    Super::NativeDestruct();
}

void URecoveredMercyRestWidget::BeginRecoveredMercyRest(ARecoveredGlobalManager* Manager) {
    bBreakFinished=false;
    bBreakActive=false;
    bIsButtonInputAllowed=true;
    ActiveManager=Manager;
    UWorld* World=GetWorld();
    if (!World) return;
    World->GetTimerManager().ClearTimer(UpdateProgressTimerHandle);
    BreakDuration=60.0;
    CurrentProgress=0.0;
    if (auto* Progress=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_0")))) Progress->SetPercent(0.0f);
    if (Manager) {
        StopRecoveredDevices(Manager);
        if (Manager->BeatTimeline) Manager->BeatTimeline->PauseSequence();
        Manager->PlayerVariables.bCanUseItems=false;
        Manager->PlayerVariables.bCanDraw=false;
    }
    StartTime=World->GetUnpausedTimeSeconds();
    World->GetTimerManager().SetTimer(UpdateProgressTimerHandle,this,&URecoveredMercyRestWidget::UpdateProgress,0.009999999776482582f,true,0.0f);
    bBreakActive=true;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"),Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage"))));
    }
}

void URecoveredMercyRestWidget::UpdateProgress() {
    UWorld* World=GetWorld();
    if (!World || !bBreakActive || bBreakFinished) return;
    CurrentProgress=FMath::Clamp((World->GetUnpausedTimeSeconds()-StartTime)/BreakDuration,0.0,1.0);
    if (auto* Progress=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_0")))) Progress->SetPercent(static_cast<float>(CurrentProgress));
    if (CurrentProgress>=1.0) CompleteRecoveredMercyRest();
}

void URecoveredMercyRestWidget::CancelRecoveredMercyRest() {
    if (!bIsButtonInputAllowed || bBreakFinished) return;
    bIsButtonInputAllowed=false;
    CompleteRecoveredMercyRest();
}

bool URecoveredMercyRestWidget::IsRecoveredMercyRestActive() const {
    return bBreakActive && !bBreakFinished;
}

FReply URecoveredMercyRestWidget::NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) {
    if (InKeyEvent.GetKey()==EKeys::G && bIsButtonInputAllowed && !bBreakFinished) {
        CancelRecoveredMercyRest();
        return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry,InKeyEvent);
}

void URecoveredMercyRestWidget::HandleCancelBreakClicked() {
    CancelRecoveredMercyRest();
}

void URecoveredMercyRestWidget::CompleteRecoveredMercyRest() {
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

void URecoveredMercyRestWidget::StopRecoveredDevices(ARecoveredGlobalManager* Manager) const {
    if (!Manager) return;
    auto* Instance=Cast<URecoveredGameInstance>(Manager->GetGameInstance());
    if (!Instance || !Instance->DeviceManager) return;
    for (const ERecoveredDeviceKind Device:{ERecoveredDeviceKind::Handy,ERecoveredDeviceKind::Lovense,ERecoveredDeviceKind::Intiface}) Instance->DeviceManager->StopDevice(Device);
}
