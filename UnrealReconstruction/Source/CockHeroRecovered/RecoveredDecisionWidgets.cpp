#include "RecoveredDecisionWidgets.h"

#include "RecoveredEdgeManager.h"
#include "RecoveredRules.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "InputCoreTypes.h"
#include "Kismet/GameplayStatics.h"

ARecoveredGlobalManager* URecoveredMercyEventWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredMercyEventWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    if (auto* Yes=Cast<UButton>(GetWidgetFromName(TEXT("YesButton")))) Yes->OnClicked.AddUniqueDynamic(this,&URecoveredMercyEventWidget::HandleYesClicked);
    if (auto* No=Cast<UButton>(GetWidgetFromName(TEXT("NoButton")))) No->OnClicked.AddUniqueDynamic(this,&URecoveredMercyEventWidget::HandleNoClicked);
}

void URecoveredMercyEventWidget::NativeConstruct() {
    Super::NativeConstruct();
    SetIsFocusable(true);
    if (auto* Yes=Cast<UButton>(GetWidgetFromName(TEXT("YesButton")))) Yes->OnClicked.AddUniqueDynamic(this,&URecoveredMercyEventWidget::HandleYesClicked);
    if (auto* No=Cast<UButton>(GetWidgetFromName(TEXT("NoButton")))) No->OnClicked.AddUniqueDynamic(this,&URecoveredMercyEventWidget::HandleNoClicked);
    bButtonPressEnabled=true;
    bCloseAfterNoSelection=false;
    ActiveManager=ResolveRecoveredGlobalManager();
    if (ARecoveredGlobalManager* Manager=ActiveManager.Get()) Manager->PlayerVariables.bCanDraw=false;
    PlayRecoveredAnimation(TEXT("IdleAnimYesButton"),0);
    PlayRecoveredAnimation(TEXT("IdleAnimNoButton"),0);
    PlayRecoveredAnimation(TEXT("IdleAnimMainImage"),0);
    SetKeyboardFocus();
}

void URecoveredMercyEventWidget::NativeDestruct() {
    if (auto* Yes=Cast<UButton>(GetWidgetFromName(TEXT("YesButton")))) Yes->OnClicked.RemoveDynamic(this,&URecoveredMercyEventWidget::HandleYesClicked);
    if (auto* No=Cast<UButton>(GetWidgetFromName(TEXT("NoButton")))) No->OnClicked.RemoveDynamic(this,&URecoveredMercyEventWidget::HandleNoClicked);
    Super::NativeDestruct();
}

FReply URecoveredMercyEventWidget::NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) {
    if (InKeyEvent.GetKey()==EKeys::F) {
        SelectRecoveredMercyYes();
        return FReply::Handled();
    }
    if (InKeyEvent.GetKey()==EKeys::G) {
        SelectRecoveredMercyNo();
        return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry,InKeyEvent);
}

void URecoveredMercyEventWidget::SelectRecoveredMercyYes() {
    if (!bButtonPressEnabled) return;
    bButtonPressEnabled=false;
    ARecoveredGlobalManager* Manager=ActiveManager.Get();
    if (!Manager) Manager=ResolveRecoveredGlobalManager();
    if (Manager) Manager->AcceptMercy();
    RemoveRecoveredOverlay(Manager);
    RemoveFromParent();
}

void URecoveredMercyEventWidget::SelectRecoveredMercyNo() {
    if (!bButtonPressEnabled) return;
    bButtonPressEnabled=false;
    bCloseAfterNoSelection=true;
    if (!PlayRecoveredAnimation(TEXT("SelectedNoAnim"))) CloseRecoveredMercyEvent();
}

void URecoveredMercyEventWidget::CloseRecoveredMercyEvent() {
    if (!bCloseAfterNoSelection) return;
    bCloseAfterNoSelection=false;
    ARecoveredGlobalManager* Manager=ActiveManager.Get();
    if (!Manager) Manager=ResolveRecoveredGlobalManager();
    RemoveRecoveredOverlay(Manager);
    if (Manager && Manager->EdgingManager) Manager->EdgingManager->UpdateRecoveredMasterEdgeCountAndSet();
    if (Manager) Manager->ContinueRecoveredEdgeStreak();
    RemoveFromParent();
}

void URecoveredMercyEventWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) {
    Super::OnAnimationFinished_Implementation(Animation);
    if (bCloseAfterNoSelection && Animation && Animation->GetName()==TEXT("SelectedNoAnim_INST")) CloseRecoveredMercyEvent();
}

void URecoveredMercyEventWidget::HandleYesClicked() {
    SelectRecoveredMercyYes();
}

void URecoveredMercyEventWidget::HandleNoClicked() {
    SelectRecoveredMercyNo();
}

void URecoveredMercyEventWidget::RemoveRecoveredOverlay(ARecoveredGlobalManager* Manager) {
    if (Manager) Manager->EventOverlays.Remove(this);
}

ARecoveredGlobalManager* URecoveredTemptationEventWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredTemptationEventWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    if (auto* Yes=Cast<UButton>(GetWidgetFromName(TEXT("YesButton")))) Yes->OnClicked.AddUniqueDynamic(this,&URecoveredTemptationEventWidget::HandleYesClicked);
    if (auto* No=Cast<UButton>(GetWidgetFromName(TEXT("NoButton")))) No->OnClicked.AddUniqueDynamic(this,&URecoveredTemptationEventWidget::HandleNoClicked);
}

void URecoveredTemptationEventWidget::NativeConstruct() {
    Super::NativeConstruct();
    SetIsFocusable(true);
    if (auto* Yes=Cast<UButton>(GetWidgetFromName(TEXT("YesButton")))) Yes->OnClicked.AddUniqueDynamic(this,&URecoveredTemptationEventWidget::HandleYesClicked);
    if (auto* No=Cast<UButton>(GetWidgetFromName(TEXT("NoButton")))) No->OnClicked.AddUniqueDynamic(this,&URecoveredTemptationEventWidget::HandleNoClicked);
    bButtonPressEnabled=true;
    ActiveManager=ResolveRecoveredGlobalManager();
    if (ARecoveredGlobalManager* Manager=ActiveManager.Get()) {
        Manager->PlayerVariables.bCanUseItems=false;
        Manager->PlayerVariables.bCanDraw=false;
    }
    PlayRecoveredAnimation(TEXT("IdleAnimYesButton"),0);
    PlayRecoveredAnimation(TEXT("IdleAnimNoButton"),0);
    PlayRecoveredAnimation(TEXT("IdleAnimMainImage"),0);
    SetKeyboardFocus();
}

void URecoveredTemptationEventWidget::NativeDestruct() {
    if (auto* Yes=Cast<UButton>(GetWidgetFromName(TEXT("YesButton")))) Yes->OnClicked.RemoveDynamic(this,&URecoveredTemptationEventWidget::HandleYesClicked);
    if (auto* No=Cast<UButton>(GetWidgetFromName(TEXT("NoButton")))) No->OnClicked.RemoveDynamic(this,&URecoveredTemptationEventWidget::HandleNoClicked);
    Super::NativeDestruct();
}

FReply URecoveredTemptationEventWidget::NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) {
    if (InKeyEvent.GetKey()==EKeys::F) {
        SelectRecoveredTemptationYes();
        return FReply::Handled();
    }
    if (InKeyEvent.GetKey()==EKeys::G) {
        SelectRecoveredTemptationNo();
        return FReply::Handled();
    }
    return Super::NativeOnKeyDown(InGeometry,InKeyEvent);
}

void URecoveredTemptationEventWidget::SelectRecoveredTemptationYes() {
    if (!bButtonPressEnabled) return;
    bButtonPressEnabled=false;
    ARecoveredGlobalManager* Manager=ActiveManager.Get();
    if (!Manager) Manager=ResolveRecoveredGlobalManager();
    if (Manager) Manager->AcceptTemptation();
    RemoveRecoveredOverlay(Manager);
    RemoveFromParent();
}

void URecoveredTemptationEventWidget::SelectRecoveredTemptationNo() {
    if (!bButtonPressEnabled) return;
    bButtonPressEnabled=false;
    ARecoveredGlobalManager* Manager=ActiveManager.Get();
    if (!Manager) Manager=ResolveRecoveredGlobalManager();
    if (Manager) Manager->DeclineTemptation();
    RemoveRecoveredOverlay(Manager);
    RemoveFromParent();
}

void URecoveredTemptationEventWidget::HandleYesClicked() {
    SelectRecoveredTemptationYes();
}

void URecoveredTemptationEventWidget::HandleNoClicked() {
    SelectRecoveredTemptationNo();
}

void URecoveredTemptationEventWidget::RemoveRecoveredOverlay(ARecoveredGlobalManager* Manager) {
    if (Manager) Manager->EventOverlays.Remove(this);
}
