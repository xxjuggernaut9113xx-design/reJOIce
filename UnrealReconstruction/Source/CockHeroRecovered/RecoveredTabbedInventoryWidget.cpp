#include "RecoveredTabbedInventoryWidget.h"

#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

namespace {
FText RecoveredInventoryCount(const ARecoveredGlobalManager* Manager, FName ItemID) {
    const int32 Count=Manager ? Manager->GetOwnedItemCount(ItemID) : 0;
    return FText::FromString(FString::Printf(TEXT("(%d)"),Count));
}

bool IsUnavailable(ERecoveredDefensiveItemUseResult Result) {
    return Result==ERecoveredDefensiveItemUseResult::CannotUseItems || Result==ERecoveredDefensiveItemUseResult::NoItemAvailable;
}
}

ARecoveredGlobalManager* URecoveredTabbedInventoryWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredTabbedInventoryWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("EdgeItemButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleEdgeItemClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("DecreaseHeatButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleDecreaseHeatClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("10SecBreakButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleBreakClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SlowdownItemButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleSlowdownClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CumChanceIncreaseButton")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleCumChanceClicked);
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.AddUniqueDynamic(this,&URecoveredTabbedInventoryWidget::HandleRecoveredSessionAction);
    RefreshRecoveredEdgeInventory();
    RefreshRecoveredDefensiveInventory();
}

void URecoveredTabbedInventoryWidget::NativeDestruct() {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("EdgeItemButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleEdgeItemClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("DecreaseHeatButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleDecreaseHeatClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("10SecBreakButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleBreakClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SlowdownItemButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleSlowdownClicked);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CumChanceIncreaseButton")))) Button->OnClicked.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleCumChanceClicked);
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.RemoveDynamic(this,&URecoveredTabbedInventoryWidget::HandleRecoveredSessionAction);
    Super::NativeDestruct();
}

FText URecoveredTabbedInventoryWidget::GetEdgeAvailableText() const {
    return RecoveredInventoryCount(ResolveRecoveredGlobalManager(),TEXT("Edge"));
}

FText URecoveredTabbedInventoryWidget::GetHeatDecreaseAvailableText() const {
    return RecoveredInventoryCount(ResolveRecoveredGlobalManager(),TEXT("DecreaseHeat"));
}

FText URecoveredTabbedInventoryWidget::GetBreakAmountText() const {
    return RecoveredInventoryCount(ResolveRecoveredGlobalManager(),TEXT("Break"));
}

FText URecoveredTabbedInventoryWidget::GetSlowdownQuantityText() const {
    return RecoveredInventoryCount(ResolveRecoveredGlobalManager(),TEXT("Slowdown"));
}

FText URecoveredTabbedInventoryWidget::GetCumChanceAvailableText() const {
    return RecoveredInventoryCount(ResolveRecoveredGlobalManager(),TEXT("XCumChance"));
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

void URecoveredTabbedInventoryWidget::RefreshRecoveredDefensiveInventory() {
    auto SetCount=[this](const TCHAR* Name,const FText& Count) {
        if (auto* Quantity=Cast<UTextBlock>(GetWidgetFromName(Name))) Quantity->SetText(Count);
    };
    SetCount(TEXT("QuantityAmount"),GetHeatDecreaseAvailableText());
    SetCount(TEXT("QuantityAmount_1"),GetBreakAmountText());
    SetCount(TEXT("QuantityAmount_3"),GetSlowdownQuantityText());
    SetCount(TEXT("QuantityAmount_4"),GetCumChanceAvailableText());
}

void URecoveredTabbedInventoryWidget::ReceiveEdgeItem() {
    RefreshRecoveredEdgeInventory();
    PlayRecoveredAnimation(TEXT("ReceiveEdgeItem"));
}

void URecoveredTabbedInventoryWidget::ReceiveHeatItem() {
    RefreshRecoveredDefensiveInventory();
    PlayRecoveredAnimation(TEXT("ReceiveHeatItem"));
}

void URecoveredTabbedInventoryWidget::ReceiveBreakItem() {
    RefreshRecoveredDefensiveInventory();
    PlayRecoveredAnimation(TEXT("ReceiveBreakItem"));
}

void URecoveredTabbedInventoryWidget::ReceiveSlowdownItem() {
    RefreshRecoveredDefensiveInventory();
    PlayRecoveredAnimation(TEXT("ReceiveSlowdownItem"));
}

void URecoveredTabbedInventoryWidget::ReceiveCumChanceItem() {
    RefreshRecoveredDefensiveInventory();
    PlayRecoveredAnimation(TEXT("ReceiveCumChanceItem"));
}

void URecoveredTabbedInventoryWidget::HandleEdgeItemClicked() {
    TabbedInventoryEdgeTrigger();
}

void URecoveredTabbedInventoryWidget::HandleDecreaseHeatClicked() {
    UseReduceHeatItem();
}

void URecoveredTabbedInventoryWidget::HandleBreakClicked() {
    TabbedInventoryBreakTrigger();
}

void URecoveredTabbedInventoryWidget::HandleSlowdownClicked() {
    TabbedInventorySlowdownTrigger();
}

void URecoveredTabbedInventoryWidget::HandleCumChanceClicked() {
    UseCumChanceItem();
}

void URecoveredTabbedInventoryWidget::HandleRecoveredSessionAction(FName Action) {
    if (Action==TEXT("InventoryAcquired_Edge")) ReceiveEdgeItem();
    else if (Action==TEXT("InventoryUsed_Edge")) RefreshRecoveredEdgeInventory();
    else if (Action==TEXT("InventoryAcquired_DecreaseHeat")) ReceiveHeatItem();
    else if (Action==TEXT("InventoryUseInitiated_DecreaseHeat")) PlayRecoveredAnimation(TEXT("DecreaseHeatItemKeyPress"));
    else if (Action==TEXT("InventoryUsed_DecreaseHeat")) RefreshRecoveredDefensiveInventory();
    else if (Action==TEXT("InventoryExhausted_DecreaseHeat")) PlayRecoveredAnimation(TEXT("UsedLastDecreaseHeatItem"));
    else if (Action==TEXT("InventoryAcquired_Break")) ReceiveBreakItem();
    else if (Action==TEXT("InventoryUseInitiated_Break")) PlayRecoveredAnimation(TEXT("BreakKeyPress"));
    else if (Action==TEXT("InventoryUsed_Break")) RefreshRecoveredDefensiveInventory();
    else if (Action==TEXT("InventoryExhausted_Break")) PlayRecoveredAnimation(TEXT("UsedLastBreakItem"));
    else if (Action==TEXT("InventoryAcquired_Slowdown")) ReceiveSlowdownItem();
    else if (Action==TEXT("InventoryUseInitiated_Slowdown")) PlayRecoveredAnimation(TEXT("SlowdownKeyPress"));
    else if (Action==TEXT("InventoryUsed_Slowdown")) RefreshRecoveredDefensiveInventory();
    else if (Action==TEXT("InventoryExhausted_Slowdown")) PlayRecoveredAnimation(TEXT("UsedLastSlowdownItem"));
    else if (Action==TEXT("InventoryAcquired_XCumChance")) ReceiveCumChanceItem();
    else if (Action==TEXT("InventoryUseInitiated_XCumChance")) PlayRecoveredAnimation(TEXT("CumChanceItemKeyPress"));
    else if (Action==TEXT("InventoryUsed_XCumChance")) RefreshRecoveredDefensiveInventory();
    else if (Action==TEXT("InventoryExhausted_XCumChance")) PlayRecoveredAnimation(TEXT("UsedLastCumChanceItem"));
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

bool URecoveredTabbedInventoryWidget::UseReduceHeatItem() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseHeatItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredDecreaseHeatItem();
    if (IsUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseHeatItem"));
    RefreshRecoveredDefensiveInventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}

bool URecoveredTabbedInventoryWidget::TabbedInventoryBreakTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseBreakItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredBreakItem();
    if (IsUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseBreakItem"));
    RefreshRecoveredDefensiveInventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}

bool URecoveredTabbedInventoryWidget::TabbedInventorySlowdownTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseSlowdownItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredSlowdownItem();
    if (IsUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseSlowdownItem"));
    RefreshRecoveredDefensiveInventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}

bool URecoveredTabbedInventoryWidget::UseCumChanceItem() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseCumChanceItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredCumChanceItem();
    if (IsUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseCumChanceItem"));
    RefreshRecoveredDefensiveInventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}
