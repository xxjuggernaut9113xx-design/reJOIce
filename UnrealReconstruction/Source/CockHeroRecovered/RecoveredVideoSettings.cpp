#include "RecoveredVideoSettings.h"
#include "RecoveredRules.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"

namespace {
// Combo widget name; the save setting name is derived by stripping "ComboBox".
const TCHAR* GVideoCombos[] = {
    TEXT("AssFrenzyComboBox"), TEXT("AutoToggleBrainMelterSuccubusComboBox"),
    TEXT("AutoToggleBrainMelterCumComboBox"), TEXT("BackgroundMusicComboBox"),
    TEXT("BallRubbingComboBox"), TEXT("BoobFrenzyComboBox"),
    TEXT("BrainMelterMediaSwapComboBox"), TEXT("BreathplayComboBox"),
    TEXT("ContextualBeatSFXComboBox"), TEXT("DynamicBackgroundsComboBox"),
    TEXT("LootDropComboBox"), TEXT("MoanSFXComboBox"),
    TEXT("NippleRubbingComboBox"), TEXT("NotificationBoxesComboBox"),
    TEXT("OnomatopoeiaComboBox_1"), TEXT("ResolutionComboBox"),
    TEXT("ScreenshakeComboBox"), TEXT("ShaftOnlyComboBox"),
    TEXT("SyncShortVideosToBeatComboBox"), TEXT("TaskModifiersToggleComboBox"),
    TEXT("TipOnlyComboBox"), TEXT("VoicelinesComboBox"),
};
}

FString URecoveredVideoSettingsMenu::SettingNameForCombo(FName ComboName) {
    FString Name = ComboName.ToString();
    Name.RemoveFromEnd(TEXT("ComboBox"));
    return Name;
}

void URecoveredVideoSettingsMenu::BindControls(bool bBind) {
    for (const TCHAR* ComboPtr : GVideoCombos) {
        auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(ComboPtr));
        if (!Combo) continue;
        if (bBind) {
            Combo->OnSelectionChanged.AddUniqueDynamic(this, &URecoveredVideoSettingsMenu::OnComboSelectionChanged);
        } else {
            Combo->OnSelectionChanged.RemoveAll(this);
        }
    }
    if (auto* Button = Cast<UButton>(GetWidgetFromName(TEXT("ClearFavoritesButton")))) {
        if (bBind) Button->OnClicked.AddUniqueDynamic(this, &URecoveredVideoSettingsMenu::OnClearFavoritesClicked);
        else Button->OnClicked.RemoveDynamic(this, &URecoveredVideoSettingsMenu::OnClearFavoritesClicked);
    }
}

void URecoveredVideoSettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    PopulateComboDefaults();
    for (const TCHAR* Name : GVideoCombos) {
        if (auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(Name))) LastSelections.Add(FName(Name), Combo->GetSelectedOption());
    }
    BindControls(true);
}

void URecoveredVideoSettingsMenu::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredVideoSettingsMenu::CommitComboValue(FName ComboName, const FString& SelectedItem) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetStringSetting(SettingNameForCombo(ComboName), SelectedItem)) {
        Instance->SaveRecoveredState();
    }
}

void URecoveredVideoSettingsMenu::PopulateComboDefaults() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    for (const TCHAR* ComboPtr : GVideoCombos) {
        auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(ComboPtr));
        if (!Combo) continue;
        const FString Saved = Instance->CurrentSave->GetStringSetting(SettingNameForCombo(FName(ComboPtr)), Combo->GetSelectedOption());
        Combo->SetSelectedOption(Saved);
    }
}

void URecoveredVideoSettingsMenu::OnClearFavoritesClicked() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetStringArraySetting(TEXT("FavoriteMedia"), TArray<FString>())) {
        Instance->SaveRecoveredState();
    }
}

void URecoveredVideoSettingsMenu::OnComboSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType) {
    if (SelectionType == ESelectInfo::Direct) return;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    bool bChanged = false;
    for (const TCHAR* Name : GVideoCombos) {
        if (auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(Name))) {
            const FString Key = SettingNameForCombo(FName(Name));
            const FString Value = Combo->GetSelectedOption();
            if (LastSelections.FindRef(FName(Name)) != Value) {
                bChanged |= Instance->CurrentSave->SetStringSetting(Key, Value);
                LastSelections.Add(FName(Name), Value);
            }
        }
    }
    if (bChanged) Instance->SaveRecoveredState();
}
