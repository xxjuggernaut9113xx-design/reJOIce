#include "RecoveredTabbedInventoryWidget.h"

#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

ARecoveredGlobalManager* URecoveredTabbedInventoryWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredTabbedInventoryWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("EdgeItemButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleEdgeItemClicked);
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleRecoveredSessionAction);
    RefreshRecoveredEdgeInventory();
}

void URecoveredTabbedInventoryWidget::NativeDestruct() {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("EdgeItemButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleEdgeItemClicked);
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleRecoveredSessionAction);
    Super::NativeDestruct();
}

FText URecoveredTabbedInventoryWidget::GetEdgeAvailableText() const {
    const auto* Manager=ResolveRecoveredGlobalManager();
    const int32 Count=Manager ? Manager->GetOwnedItemCount(TEXT("Edge")) : 0;
    return FText::FromString(FString::Printf(TEXT("(%d)"),Count));
}

void URecoveredTabbedInventoryWidget::RefreshRecoveredEdgeInventory() {
    if (auto* Quantity=Cast<UTextBlock>(GetWidgetFromName(TEXT("QuantityAmount_2")))) {
        Quantity->SetText(GetEdgeAvailableText());
        return;
    }
    if (auto* Item=Cast<UUserWidget>(GetWidgetFromName(TEXT("ItemButton_2")))) {
        if (auto* Quantity=Cast<UTextBlock>(Item->GetWidgetFromName(TEXT("QuantityAmount")))) Quantity->SetText(GetEdgeAvailableText());
    }
}

void URecoveredTabbedInventoryWidget::ReceiveEdgeItem() {
    RefreshRecoveredEdgeInventory();
    PlayRecoveredAnimation(TEXT("ReceiveEdgeItem"));
}

void URecoveredTabbedInventoryWidget::HandleEdgeItemClicked() {
    TabbedInventoryEdgeTrigger();
}

void URecoveredTabbedInventoryWidget::HandleRecoveredSessionAction(FName Action) {
    if (Action==TEXT("InventoryAcquired_Edge")) ReceiveEdgeItem();
    else if (Action==TEXT("InventoryUsed_Edge")) RefreshRecoveredEdgeInventory();
}

bool URecoveredTabbedInventoryWidget::TabbedInventoryEdgeTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager || !Manager->CanUseRecoveredEdgeItem()) {
        PlayRecoveredAnimation(TEXT("CantUseEdgeItem"));
        return false;
    }
    if (Manager->RollRecoveredPunishmentChance()) {
        Manager->TriggerRecoveredEdgeItemPunishment();
        return false;
    }
    PlayRecoveredAnimation(TEXT("EdgeItemKeyPress"));
    if (!Manager->CommitRecoveredEdgeItemUse()) {
        RefreshRecoveredEdgeInventory();
        return false;
    }
    RefreshRecoveredEdgeInventory();
    if (Manager->GetOwnedItemCount(TEXT("Edge"))<=0) PlayRecoveredAnimation(TEXT("UsedLastEdgeItem"));
    return true;
}
