#include "RecoveredStoreItem.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void URecoveredStoreItemWidget::BindControls(bool bBind) {
#define BIND(Name, Method) \
    if (auto* Button_##Method = Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button_##Method->OnClicked.AddUniqueDynamic(this, &URecoveredStoreItemWidget::Method); \
        else Button_##Method->OnClicked.RemoveDynamic(this, &URecoveredStoreItemWidget::Method); \
    }
    BIND("BuyButton", OnBuyClicked)
    BIND("UpgradeButton", OnUpgradeClicked)
#undef BIND
}

void URecoveredStoreItemWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
    CurrentLevel = ReadLevelFromSave();
    RefreshPrices();
}

void URecoveredStoreItemWidget::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

FString URecoveredStoreItemWidget::LevelSettingName() const {
    return TEXT("StoreItemLevel_") + ItemID.ToString();
}

int32 URecoveredStoreItemWidget::ReadLevelFromSave() const {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave) {
        return static_cast<int32>(Instance->CurrentSave->GetNumberSetting(LevelSettingName(), 0));
    }
    return 0;
}

void URecoveredStoreItemWidget::WriteLevelToSave(int32 Level) const {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(LevelSettingName(), Level)) {
        Instance->SaveRecoveredState();
    }
}

int32 URecoveredStoreItemWidget::GetBuyAmount() const {
    // First purchase costs the base; re-buys after use cost base * (level + 1).
    return BasePurchaseCost * (CurrentLevel + 1);
}

int32 URecoveredStoreItemWidget::GetUpgradeAmount() const {
    if (CurrentLevel >= MaxLevel) return 0;
    return BaseUpgradeCost * (CurrentLevel + 1);
}

FText URecoveredStoreItemWidget::GetEffectDescription() const {
    // Per-item effect text mirrors the native Get_EffectDescription bindings.
    const FString ID = ItemID.ToString();
    if (ID == TEXT("Slowdown")) return FText::FromString(TEXT("Slows the beat timeline for 15 seconds."));
    if (ID == TEXT("BonerPill")) return FText::FromString(TEXT("Restores full hardness and clears the edge lockout."));
    if (ID == TEXT("Break")) return FText::FromString(TEXT("Pauses the session for a 60 second break."));
    if (ID == TEXT("DecreaseHeat")) return FText::FromString(TEXT("Immediately reduces heat by 25."));
    if (ID == TEXT("Edge")) return FText::FromString(TEXT("Forces an edge attempt on the next beat window."));
    if (ID == TEXT("Resupply")) return FText::FromString(TEXT("Restores one use of every consumable item."));
    if (ID == TEXT("SuccuShield")) return FText::FromString(TEXT("Blocks the next succubus special attack."));
    if (ID == TEXT("XCumChance")) return FText::FromString(TEXT("Grants an extra cum-window chance this session."));
    return FText::FromString(TEXT("Unknown store item."));
}

FText URecoveredStoreItemWidget::GetUpgradeText() const {
    if (CurrentLevel >= MaxLevel) return FText::FromString(TEXT("MAX"));
    return FText::FromString(FString::Printf(TEXT("Upgrade to Lv.%d (%d coins)"), CurrentLevel + 1, GetUpgradeAmount()));
}

void URecoveredStoreItemWidget::RefreshPrices() {
    auto SetText = [this](const TCHAR* Name, const FText& Value) {
        if (auto* Text = Cast<UTextBlock>(GetWidgetFromName(Name))) Text->SetText(Value);
    };
    SetText(TEXT("BuyAmountText"), FText::AsNumber(GetBuyAmount()));
    SetText(TEXT("UpgradeText"), GetUpgradeText());
    SetText(TEXT("LevelText"), FText::FromString(FString::Printf(TEXT("Lv.%d"), CurrentLevel)));
    SetText(TEXT("EffectDescriptionText"), GetEffectDescription());
    // Disable buy when the player cannot afford it.
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    const bool bAfford = Manager && Manager->PlayerVariables.PlayerCoins >= GetBuyAmount();
    if (auto* Buy = Cast<UButton>(GetWidgetFromName(TEXT("BuyButton")))) Buy->SetIsEnabled(bAfford);
}

bool URecoveredStoreItemWidget::TryBuy() {
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return false;
    const int32 Cost = GetBuyAmount();
    if (Manager->PlayerVariables.PlayerCoins < Cost) return false;
    Manager->PlayerVariables.PlayerCoins -= Cost;
    URecoveredStateRuleLibrary::RecordSessionMetric(Manager->SessionStats, ERecoveredMetric::MoneySpent, Cost);
    Manager->ApplyStoreItemEffect(ItemID, CurrentLevel);
    RefreshPrices();
    return true;
}

bool URecoveredStoreItemWidget::TryUpgrade() {
    if (CurrentLevel >= MaxLevel) return false;
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return false;
    const int32 Cost = GetUpgradeAmount();
    if (Manager->PlayerVariables.PlayerCoins < Cost) return false;
    Manager->PlayerVariables.PlayerCoins -= Cost;
    CurrentLevel += 1;
    WriteLevelToSave(CurrentLevel);
    RefreshPrices();
    return true;
}

void URecoveredStoreItemWidget::OnBuyClicked() { TryBuy(); }
void URecoveredStoreItemWidget::OnUpgradeClicked() { TryUpgrade(); }
