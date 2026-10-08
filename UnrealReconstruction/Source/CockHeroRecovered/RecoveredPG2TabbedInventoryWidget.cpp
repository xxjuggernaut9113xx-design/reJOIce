#include "RecoveredPG2TabbedInventoryWidget.h"

#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

ARecoveredGlobalManager* URecoveredPG2TabbedInventoryWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredPG2TabbedInventoryWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResupplyButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyClicked);
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleRecoveredSessionAction);
    RefreshRecoveredResupplyInventory();
}

void URecoveredPG2TabbedInventoryWidget::NativeDestruct() {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResupplyButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyClicked);
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleRecoveredSessionAction);
    Super::NativeDestruct();
}

FText URecoveredPG2TabbedInventoryWidget::GetResupplyCount() const {
    const auto* Manager=ResolveRecoveredGlobalManager();
    const int32 Count=Manager ? Manager->GetOwnedItemCount(TEXT("Resupply")) : 0;
    return FText::FromString(FString::Printf(TEXT("(%d)"),Count));
}

void URecoveredPG2TabbedInventoryWidget::RefreshRecoveredResupplyInventory() {
    if (auto* Quantity=Cast<UTextBlock>(GetWidgetFromName(TEXT("QuantityAmount")))) {
        Quantity->SetText(GetResupplyCount());
        return;
    }
    if (auto* Item=Cast<UUserWidget>(GetWidgetFromName(TEXT("ItemButton")))) {
        if (auto* Quantity=Cast<UTextBlock>(Item->GetWidgetFromName(TEXT("QuantityAmount")))) Quantity->SetText(GetResupplyCount());
    }
}

void URecoveredPG2TabbedInventoryWidget::ReceiveStoreItem() {
    RefreshRecoveredResupplyInventory();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResupplyButton")))) Button->SetColorAndOpacity(FLinearColor::White);
    PlayRecoveredAnimation(TEXT("ReceiveStoreItem"));
}

void URecoveredPG2TabbedInventoryWidget::HandleResupplyClicked() {
    TabbedInventoryResupplyTrigger();
}

void URecoveredPG2TabbedInventoryWidget::HandleRecoveredSessionAction(FName Action) {
    if (Action==TEXT("InventoryAcquired_Resupply")) ReceiveStoreItem();
    else if (Action==TEXT("InventoryUseInitiated_Resupply")) PlayRecoveredAnimation(TEXT("ResupplyKeyPress"));
    else if (Action==TEXT("InventoryUsed_Resupply")) RefreshRecoveredResupplyInventory();
    else if (Action==TEXT("InventoryExhausted_Resupply")) PlayRecoveredAnimation(TEXT("UsedLastStoreItem"));
}

bool URecoveredPG2TabbedInventoryWidget::TabbedInventoryResupplyTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseStoreItem"));
        return false;
    }
    const ERecoveredResupplyItemUseResult Result=Manager->UseRecoveredResupplyItem();
    if (Result==ERecoveredResupplyItemUseResult::CannotUseItems || Result==ERecoveredResupplyItemUseResult::NoResupplyAvailable) {
        PlayRecoveredAnimation(TEXT("CantUseStoreItem"));
    }
    RefreshRecoveredResupplyInventory();
    return Result==ERecoveredResupplyItemUseResult::Triggered;
}
