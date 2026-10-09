#include "RecoveredPG2TabbedInventoryWidget.h"

#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

namespace {
FText RecoveredPG2InventoryCount(const ARecoveredGlobalManager* Manager,FName ItemID) {
    const int32 Count=Manager ? Manager->GetOwnedItemCount(ItemID) : 0;
    return FText::FromString(FString::Printf(TEXT("(%d)"),Count));
}

bool ShouldPlayUnavailable(ERecoveredDefensiveItemUseResult Result) {
    return Result==ERecoveredDefensiveItemUseResult::CannotUseItems || Result==ERecoveredDefensiveItemUseResult::NoItemAvailable || Result==ERecoveredDefensiveItemUseResult::CooldownActive;
}
}

ARecoveredGlobalManager* URecoveredPG2TabbedInventoryWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

void URecoveredPG2TabbedInventoryWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("BonerPillItemButton")))) {
        Button->OnClicked.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBonerPillClicked);
        Button->OnHovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBonerPillHovered);
        Button->OnUnhovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBonerPillUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SuccubusShieldButton")))) {
        Button->OnClicked.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldClicked);
        Button->OnHovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldHovered);
        Button->OnUnhovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResupplyButton")))) {
        Button->OnClicked.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyClicked);
        Button->OnHovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyHovered);
        Button->OnUnhovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SlowdownItemButton")))) {
        Button->OnClicked.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSlowdownClicked);
        Button->OnHovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSlowdownHovered);
        Button->OnUnhovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSlowdownUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("10SecBreakButton")))) {
        Button->OnClicked.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBreakClicked);
        Button->OnHovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBreakHovered);
        Button->OnUnhovered.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBreakUnhovered);
    }
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.AddUniqueDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleRecoveredSessionAction);
    RefreshRecoveredPG2Inventory();
}

void URecoveredPG2TabbedInventoryWidget::NativeDestruct() {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("BonerPillItemButton")))) {
        Button->OnClicked.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBonerPillClicked);
        Button->OnHovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBonerPillHovered);
        Button->OnUnhovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBonerPillUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SuccubusShieldButton")))) {
        Button->OnClicked.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldClicked);
        Button->OnHovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldHovered);
        Button->OnUnhovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResupplyButton")))) {
        Button->OnClicked.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyClicked);
        Button->OnHovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyHovered);
        Button->OnUnhovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleResupplyUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SlowdownItemButton")))) {
        Button->OnClicked.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSlowdownClicked);
        Button->OnHovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSlowdownHovered);
        Button->OnUnhovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleSlowdownUnhovered);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("10SecBreakButton")))) {
        Button->OnClicked.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBreakClicked);
        Button->OnHovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBreakHovered);
        Button->OnUnhovered.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleBreakUnhovered);
    }
    if (auto* Manager=ResolveRecoveredGlobalManager()) Manager->OnSessionAction.RemoveDynamic(this,&URecoveredPG2TabbedInventoryWidget::HandleRecoveredSessionAction);
    Super::NativeDestruct();
}

FText URecoveredPG2TabbedInventoryWidget::GetResupplyCount() const {
    return RecoveredPG2InventoryCount(ResolveRecoveredGlobalManager(),TEXT("Resupply"));
}

FText URecoveredPG2TabbedInventoryWidget::GetBonerPillCount() const {
    return RecoveredPG2InventoryCount(ResolveRecoveredGlobalManager(),TEXT("BonerPill"));
}

FText URecoveredPG2TabbedInventoryWidget::GetSuccuShieldAvailableText() const {
    return RecoveredPG2InventoryCount(ResolveRecoveredGlobalManager(),TEXT("SuccuShield"));
}

FText URecoveredPG2TabbedInventoryWidget::GetBreakAmountText() const {
    return RecoveredPG2InventoryCount(ResolveRecoveredGlobalManager(),TEXT("Break"));
}

FText URecoveredPG2TabbedInventoryWidget::GetSlowdownQuantityText() const {
    return RecoveredPG2InventoryCount(ResolveRecoveredGlobalManager(),TEXT("Slowdown"));
}

void URecoveredPG2TabbedInventoryWidget::RefreshRecoveredPG2Inventory() {
    auto SetCount=[this](const TCHAR* Name,const FText& Count) {
        if (auto* Quantity=Cast<UTextBlock>(GetWidgetFromName(Name))) Quantity->SetText(Count);
    };
    SetCount(TEXT("QuantityAmount"),GetBonerPillCount());
    SetCount(TEXT("QuantityAmount_1"),GetSuccuShieldAvailableText());
    SetCount(TEXT("QuantityAmount_2"),GetResupplyCount());
    SetCount(TEXT("QuantityAmount_3"),GetSlowdownQuantityText());
    SetCount(TEXT("QuantityAmount_4"),GetBreakAmountText());
}

void URecoveredPG2TabbedInventoryWidget::ReceiveStoreItem() {
    RefreshRecoveredPG2Inventory();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResupplyButton")))) Button->SetColorAndOpacity(FLinearColor::White);
    PlayRecoveredAnimation(TEXT("ReceiveStoreItem"));
}

void URecoveredPG2TabbedInventoryWidget::ReceiveBonerPillItem() {
    RefreshRecoveredPG2Inventory();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("BonerPillItemButton")))) Button->SetColorAndOpacity(FLinearColor::White);
    PlayRecoveredAnimation(TEXT("ReceiveBonerPillItem"));
}

void URecoveredPG2TabbedInventoryWidget::ReceiveSuccuShieldItems() {
    RefreshRecoveredPG2Inventory();
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SuccubusShieldButton")))) Button->SetColorAndOpacity(FLinearColor::White);
    PlayRecoveredAnimation(TEXT("ReceiveSuccuShieldItems"));
}

void URecoveredPG2TabbedInventoryWidget::HandleResupplyClicked() { TabbedInventoryResupplyTrigger(); }
void URecoveredPG2TabbedInventoryWidget::HandleBonerPillClicked() { UseBonerPillItem(); }
void URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldClicked() { ToggleSuccuShields(); }
void URecoveredPG2TabbedInventoryWidget::HandleBreakClicked() { TabbedInventoryBreakTrigger(); }
void URecoveredPG2TabbedInventoryWidget::HandleSlowdownClicked() { TabbedInventorySlowdownTrigger(); }
void URecoveredPG2TabbedInventoryWidget::HandleBonerPillHovered() { PlayRecoveredAnimation(TEXT("BonerPillItemHover")); }
void URecoveredPG2TabbedInventoryWidget::HandleBonerPillUnhovered() { PlayRecoveredAnimation(TEXT("BonerPillItemUnhover")); }
void URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldHovered() { PlayRecoveredAnimation(TEXT("SuccushieldItemsHover")); }
void URecoveredPG2TabbedInventoryWidget::HandleSuccuShieldUnhovered() { PlayRecoveredAnimation(TEXT("SuccushieldItemsUnhover")); }
void URecoveredPG2TabbedInventoryWidget::HandleResupplyHovered() { PlayRecoveredAnimation(TEXT("ResupplyItemHover")); }
void URecoveredPG2TabbedInventoryWidget::HandleResupplyUnhovered() { PlayRecoveredAnimation(TEXT("ResupplyItemUnhover")); }
void URecoveredPG2TabbedInventoryWidget::HandleBreakHovered() { PlayRecoveredAnimation(TEXT("BreakHover")); }
void URecoveredPG2TabbedInventoryWidget::HandleBreakUnhovered() { PlayRecoveredAnimation(TEXT("BreakUnhover")); }
void URecoveredPG2TabbedInventoryWidget::HandleSlowdownHovered() { PlayRecoveredAnimation(TEXT("SlowdownHover")); }
void URecoveredPG2TabbedInventoryWidget::HandleSlowdownUnhovered() { PlayRecoveredAnimation(TEXT("SlowdownUnhover")); }

void URecoveredPG2TabbedInventoryWidget::HandleRecoveredSessionAction(FName Action) {
    if (Action==TEXT("InventoryAcquired_Resupply")) ReceiveStoreItem();
    else if (Action==TEXT("InventoryUseInitiated_Resupply")) PlayRecoveredAnimation(TEXT("ResupplyKeyPress"));
    else if (Action==TEXT("InventoryUsed_Resupply")) RefreshRecoveredPG2Inventory();
    else if (Action==TEXT("InventoryExhausted_Resupply")) PlayRecoveredAnimation(TEXT("UsedLastStoreItem"));
    else if (Action==TEXT("InventoryAcquired_BonerPill")) ReceiveBonerPillItem();
    else if (Action==TEXT("InventoryUseInitiated_BonerPill")) PlayRecoveredAnimation(TEXT("BonerPillItemButtonClick"));
    else if (Action==TEXT("InventoryUsed_BonerPill")) RefreshRecoveredPG2Inventory();
    else if (Action==TEXT("InventoryExhausted_BonerPill")) PlayRecoveredAnimation(TEXT("UsedLastBonerPillItem"));
    else if (Action==TEXT("InventoryAcquired_SuccuShield")) ReceiveSuccuShieldItems();
    else if (Action==TEXT("InventoryUsed_SuccuShield")) RefreshRecoveredPG2Inventory();
    else if (Action==TEXT("InventoryExhausted_SuccuShield")) PlayRecoveredAnimation(TEXT("UsedLastSuccuShieldItems"));
    else if (Action==TEXT("SuccuShieldToggledOn")) PlayRecoveredAnimation(TEXT("SuccuShieldToggleEnable"));
    else if (Action==TEXT("SuccuShieldToggledOff")) PlayRecoveredAnimation(TEXT("SuccushieldToggleDisable"));
    else if (Action==TEXT("InventoryAcquired_Break")) { RefreshRecoveredPG2Inventory(); PlayRecoveredAnimation(TEXT("ReceiveBreakItem")); }
    else if (Action==TEXT("InventoryUseInitiated_Break")) PlayRecoveredAnimation(TEXT("BreakKeyPress"));
    else if (Action==TEXT("InventoryUsed_Break")) RefreshRecoveredPG2Inventory();
    else if (Action==TEXT("InventoryExhausted_Break")) PlayRecoveredAnimation(TEXT("UsedLastBreakItem"));
    else if (Action==TEXT("InventoryAcquired_Slowdown")) { RefreshRecoveredPG2Inventory(); PlayRecoveredAnimation(TEXT("ReceiveSlowdownItem")); }
    else if (Action==TEXT("InventoryUseInitiated_Slowdown")) PlayRecoveredAnimation(TEXT("SlowdownKeyPress"));
    else if (Action==TEXT("InventoryUsed_Slowdown")) RefreshRecoveredPG2Inventory();
    else if (Action==TEXT("InventoryExhausted_Slowdown")) PlayRecoveredAnimation(TEXT("UsedLastSlowdownItem"));
}

bool URecoveredPG2TabbedInventoryWidget::TabbedInventoryResupplyTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseStoreItem"));
        return false;
    }
    const ERecoveredResupplyItemUseResult Result=Manager->UseRecoveredResupplyItem();
    if (Result==ERecoveredResupplyItemUseResult::CannotUseItems || Result==ERecoveredResupplyItemUseResult::NoResupplyAvailable) PlayRecoveredAnimation(TEXT("CantUseStoreItem"));
    RefreshRecoveredPG2Inventory();
    return Result==ERecoveredResupplyItemUseResult::Triggered;
}

bool URecoveredPG2TabbedInventoryWidget::UseBonerPillItem() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseBonerPillItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredBonerPillItem();
    if (ShouldPlayUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseBonerPillItem"));
    RefreshRecoveredPG2Inventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}

bool URecoveredPG2TabbedInventoryWidget::ToggleSuccuShields() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseSuccuShieldItems"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->ToggleRecoveredSuccuShields();
    if (ShouldPlayUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseSuccuShieldItems"));
    RefreshRecoveredPG2Inventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}

bool URecoveredPG2TabbedInventoryWidget::TabbedInventoryBreakTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseBreakItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredBreakItem();
    if (ShouldPlayUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseBreakItem"));
    RefreshRecoveredPG2Inventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}

bool URecoveredPG2TabbedInventoryWidget::TabbedInventorySlowdownTrigger() {
    auto* Manager=ResolveRecoveredGlobalManager();
    if (!Manager) {
        PlayRecoveredAnimation(TEXT("CantUseSlowdownItem"));
        return false;
    }
    const ERecoveredDefensiveItemUseResult Result=Manager->UseRecoveredSlowdownItem();
    if (ShouldPlayUnavailable(Result)) PlayRecoveredAnimation(TEXT("CantUseSlowdownItem"));
    RefreshRecoveredPG2Inventory();
    return Result==ERecoveredDefensiveItemUseResult::Triggered;
}
