#include "RecoveredModifierWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/CheckBox.h"

void URecoveredModifierWidget::NativeConstruct() {
    Super::NativeConstruct();
    RefreshModifierList();
}

void URecoveredModifierWidget::RefreshModifierList() {
    auto* Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("ModifierListContainer")));
    if (!Container) return;
    Container->ClearChildren();
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression) return;
    for (const FRecoveredModifierRow& Row : Progression->GetAllModifierData()) {
        // Row name lookup: use the display title as the ID key.
        const FName ModifierID(*Row.ModifierTitle.ToString());
        auto* Entry = NewObject<UHorizontalBox>(this);
        auto* Title = NewObject<UTextBlock>(this);
        Title->SetText(Row.ModifierTitle);
        auto* Desc = NewObject<UTextBlock>(this);
        Desc->SetText(Row.ModifierDescription);
        auto* Toggle = NewObject<UCheckBox>(this);
        const bool bEnabled = Progression->EnabledModifiers.Contains(ModifierID);
        const bool bCanEnable = Progression->CanEnableModifier(ModifierID);
        Toggle->SetCheckedState(bEnabled ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
        Toggle->SetIsEnabled(bCanEnable || bEnabled);
        Entry->AddChildToHorizontalBox(Title);
        Entry->AddChildToHorizontalBox(Desc);
        Entry->AddChildToHorizontalBox(Toggle);
        Container->AddChild(Entry);
    }
}

bool URecoveredModifierWidget::ToggleModifier(FName ModifierID) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression) return false;
    if (Progression->EnabledModifiers.Contains(ModifierID)) {
        Progression->EnabledModifiers.Remove(ModifierID);
    } else {
        if (!Progression->CanEnableModifier(ModifierID)) return false;
        Progression->EnabledModifiers.Add(ModifierID);
    }
    // Persist the enabled set.
    if (Instance->CurrentSave) {
        TArray<FString> Enabled;
        for (FName M : Progression->EnabledModifiers) Enabled.Add(M.ToString());
        if (Instance->CurrentSave->SetStringArraySetting(TEXT("EnabledModifiers"), Enabled)) {
            Instance->SaveRecoveredState();
        }
    }
    RefreshModifierList();
    return true;
}
