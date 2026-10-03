#include "RecoveredTagSettings.h"
#include "RecoveredRules.h"
#include "Components/CheckBox.h"
#include "Components/PanelWidget.h"

void URecoveredTagSettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    InitDefaultsFromSaveGame();
}

void URecoveredTagSettingsMenu::InitDefaultsFromSaveGame() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    const TArray<FString> Excluded = Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags"));
    // Sync every tag entry checkbox with the saved exclusion list.
    TArray<UWidget*> Entries;
    // Tag entries live under a named container; fall back to a full subtree scan.
    if (auto* Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("TagListContainer")))) {
        Entries = Container->GetAllChildren();
    }
    for (UWidget* Entry : Entries) {
        auto* EntryWidget = Cast<UUserWidget>(Entry);
        auto* Check = EntryWidget ? Cast<UCheckBox>(EntryWidget->GetWidgetFromName(TEXT("TagCheckBox"))) : nullptr;
        if (!Check) Check = Cast<UCheckBox>(Entry);
        if (!Check) continue;
        const FString Tag = Entry->GetName();
        if (!Tag.IsEmpty()) Check->SetCheckedState(Excluded.Contains(Tag) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
    }
}

bool URecoveredTagSettingsMenu::IsTagExcluded(const FString& Tag) const {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    return Instance && Instance->CurrentSave && Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags")).Contains(Tag);
}

void URecoveredTagSettingsMenu::SetTagExcluded(const FString& Tag, bool bExcluded) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave || Tag.IsEmpty()) return;
    TArray<FString> Excluded = Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags"));
    if (bExcluded) Excluded.AddUnique(Tag);
    else Excluded.Remove(Tag);
    if (Instance->CurrentSave->SetStringArraySetting(TEXT("ExcludedTags"), Excluded)) {
        Instance->SaveRecoveredState();
    }
}

void URecoveredTagSettingsMenu::ClearExcludedTags() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetStringArraySetting(TEXT("ExcludedTags"), TArray<FString>())) {
        Instance->SaveRecoveredState();
        InitDefaultsFromSaveGame();
    }
}
