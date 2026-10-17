#include "RecoveredEdgeRestWidget.h"

#include "RecoveredDeviceInterface.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

URecoveredEdgeRestWidget::URecoveredEdgeRestWidget() {
    LoadScreenTipsArray={
        FText::FromString(TEXT("Edge early if you must, but your payout will shrink.")),
        FText::FromString(TEXT("Every edge stacks rewards. The higher you climb, the bigger the payout.")),
        FText::FromString(TEXT("Cash out at Mercy to keep rewards safe.")),
        FText::FromString(TEXT("Mercy is your only escape. Take it or stay trapped.")),
        FText::FromString(TEXT("Tasks only get harder. Survive or lose it all.")),
        FText::FromString(TEXT("Breaks get shorter with every edge.")),
        FText::FromString(TEXT("Each edge is harder, faster, riskier. Survival is never guaranteed.")),
        FText::FromString(TEXT("Once an Edge Streak begins, it cannot be exited until Mercy or failure.")),
        FText::FromString(TEXT("Mercy Grants a 60 Second Break")),
        FText::FromString(TEXT("No items or failsafes apply during an active streak. Only Mercy can end it.")),
        FText::FromString(TEXT("Pending rewards scale with streak count. Higher streak = higher payout.")),
        FText::FromString(TEXT("How long can you really last?")),
        FText::FromString(TEXT("Upgrading your Edge item in the store increases the Perfect Edge window.")),
        FText::FromString(TEXT("the Perfect Edge Threshold can be upgraded in the store for easier edging."))
    };
}

ARecoveredGlobalManager* URecoveredEdgeRestWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredEdgeRestWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredEdgeRestWidget::HandleCancelBreakClicked);
}

void URecoveredEdgeRestWidget::NativeConstruct() {
    Super::NativeConstruct();
    SetIsFocusable(true);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredEdgeRestWidget::HandleCancelBreakClicked);
    BeginRecoveredEdgeRest(ResolveRecoveredGlobalManager(),EdgesLeft);
    SetKeyboardFocus();
}

void URecoveredEdgeRestWidget::NativeDestruct() {
    if (UWorld* World=GetWorld()) World->GetTimerManager().ClearTimer(UpdateProgressTimerHandle);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CancelBreakButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredEdgeRestWidget::HandleCancelBreakClicked);
    Super::NativeDestruct();
}

void URecoveredEdgeRestWidget::BeginRecoveredEdgeRest(ARecoveredGlobalManager* Manager,int32 InEdgesLeft) {
    bBreakFinished=false;
    bBreakActive=false;
    bIsButtonInputAllowed=true;
    ActiveManager=Manager;
    EdgesLeft=InEdgesLeft;
    UpdateEdgesLeftUntilMercy(EdgesLeft);
    UpdateRecoveredTip();

    UWorld* World=GetWorld();
    if (!World) return;
    World->GetTimerManager().ClearTimer(UpdateProgressTimerHandle);
    BreakDuration=1.0;
    CurrentProgress=0.0;
    if (auto* Progress=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_0")))) Progress->SetPercent(0.0f);

    if (Manager) {
        StopRecoveredDevices(Manager);
        if (Manager->BeatTimeline) Manager->BeatTimeline->PauseSequence();
        Manager->PlayerVariables.bCanUseItems=false;
        Manager->PlayerVariables.bCanDraw=false;
        BreakDuration=FMath::Max(Manager->EdgeBreakDurationScaled,0.01);
    }

    StartTime=World->GetUnpausedTimeSeconds();
    World->GetTimerManager().SetTimer(UpdateProgressTimerHandle,this,&URecoveredEdgeRestWidget::UpdateProgress,0.009999999776482582f,true,0.0f);
    bBreakActive=true;
}

void URecoveredEdgeRestWidget::UpdateProgress() {
    UWorld* World=GetWorld();
    if (!World || !bBreakActive || bBreakFinished) return;
    CurrentProgress=FMath::Clamp((World->GetUnpausedTimeSeconds()-StartTime)/FMath::Max(BreakDuration,0.01),0.0,1.0);
    if (auto* Progress=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_0")))) Progress->SetPercent(static_cast<float>(CurrentProgress));
    if (CurrentProgress>=1.0) CompleteRecoveredEdgeRest();
}

void URecoveredEdgeRestWidget::UpdateEdgesLeftUntilMercy(int32 InEdgesLeft) {
    EdgesLeft=InEdgesLeft;
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("EdgesLeftText")))) {
        Label->SetText(FText::FromString(EdgesLeft==1 ? TEXT("1 Edge Left Until Mercy") : FString::Printf(TEXT("%d Edges Left Until Mercy"),EdgesLeft)));
    }
}

void URecoveredEdgeRestWidget::CancelRecoveredEdgeRest() {
    if (!bIsButtonInputAllowed || bBreakFinished) return;
    bIsButtonInputAllowed=false;
    CompleteRecoveredEdgeRest();
}

bool URecoveredEdgeRestWidget::IsRecoveredEdgeRestActive() const {
    return bBreakActive && !bBreakFinished;
}

FReply URecoveredEdgeRestWidget::NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) {
    if (InKeyEvent.GetKey()==EKeys::G && bIsButtonInputAllowed && !bBreakFinished) {
        CancelRecoveredEdgeRest();
        return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry,InKeyEvent);
}

void URecoveredEdgeRestWidget::HandleCancelBreakClicked() {
    CancelRecoveredEdgeRest();
}

void URecoveredEdgeRestWidget::CompleteRecoveredEdgeRest() {
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

void URecoveredEdgeRestWidget::StopRecoveredDevices(ARecoveredGlobalManager* Manager) const {
    if (!Manager) return;
    auto* Instance=Cast<URecoveredGameInstance>(Manager->GetGameInstance());
    if (!Instance || !Instance->DeviceManager) return;
    for (const ERecoveredDeviceKind Device:{ERecoveredDeviceKind::Handy,ERecoveredDeviceKind::Lovense,ERecoveredDeviceKind::Intiface}) Instance->DeviceManager->StopDevice(Device);
}

void URecoveredEdgeRestWidget::UpdateRecoveredTip() {
    if (LoadScreenTipsArray.IsEmpty()) return;
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("TooltipTextVar")))) {
        const FText& Tip=LoadScreenTipsArray[FMath::RandRange(0,LoadScreenTipsArray.Num()-1)];
        Label->SetText(FText::FromString(TEXT("Tip: ")+Tip.ToString()));
    }
}
