#include "RecoveredToySettings.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

void URecoveredToySettingsMenu::BindControls(bool bBind) {
#define BIND_BUTTON(Name, Method) \
    if (auto* Button_##Method = Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button_##Method->OnClicked.AddUniqueDynamic(this, &URecoveredToySettingsMenu::Method); \
        else Button_##Method->OnClicked.RemoveDynamic(this, &URecoveredToySettingsMenu::Method); \
    }
    BIND_BUTTON("ConnectLovenseToysButton", OnConnectLovenseClicked)
    BIND_BUTTON("ConnectMobileLovenseToysButton", OnConnectMobileLovenseClicked)
    BIND_BUTTON("DisconnectLovenseToysButton", OnDisconnectLovenseClicked)
    BIND_BUTTON("HandyConnectButtonV2", OnHandyConnectClicked)
    BIND_BUTTON("RefreshHandyConnectionButton", OnRefreshHandyClicked)
    BIND_BUTTON("IntifaceConnectButton", OnIntifaceConnectClicked)
    BIND_BUTTON("DisconnectIntiface", OnDisconnectIntifaceClicked)
#undef BIND_BUTTON
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("HandyStrokeRangeSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredToySettingsMenu::OnHandyStrokeRangeCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredToySettingsMenu::OnHandyStrokeRangeCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("IntifaceStrokeRangeSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredToySettingsMenu::OnIntifaceStrokeRangeCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredToySettingsMenu::OnIntifaceStrokeRangeCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("MaxVibrationIntensitySlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredToySettingsMenu::OnMaxVibrationCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredToySettingsMenu::OnMaxVibrationCommitted);
    }
}

void URecoveredToySettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

bool URecoveredToySettingsMenu::IsDeviceConnected(const FString& SettingName) const {
    // Saved preferences cannot establish a live hardware connection.
    return false;
}

void URecoveredToySettingsMenu::SetDeviceConnected(const FString& SettingName, bool bConnected) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetBoolSetting(SettingName, bConnected)) {
        Instance->SaveRecoveredState();
    }
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::UpdateConnectionLabel(FName LabelName, bool bConnected) {
    if (auto* Label = Cast<UTextBlock>(GetWidgetFromName(LabelName))) {
        Label->SetText(FText::FromString(TEXT("Device connection unavailable")));
    }
}

void URecoveredToySettingsMenu::RefreshConnectionStates() {
    const bool bLovense = IsDeviceConnected(TEXT("ToyLovenseConnected"));
    const bool bHandy = IsDeviceConnected(TEXT("ToyHandyConnected"));
    const bool bIntiface = IsDeviceConnected(TEXT("ToyIntifaceConnected"));
    UpdateConnectionLabel(TEXT("LovenseStatusText"), bLovense);
    UpdateConnectionLabel(TEXT("HandyStatusText"), bHandy);
    UpdateConnectionLabel(TEXT("IntifaceStatusText"), bIntiface);
    // Show connect buttons only when disconnected, disconnect only when connected.
    auto SetVisible = [this](const TCHAR* Name, bool bVisible) {
        if (auto* W = GetWidgetFromName(Name)) W->SetVisibility(bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    };
    SetVisible(TEXT("ConnectLovenseToysButton"), !bLovense);
    SetVisible(TEXT("DisconnectLovenseToysButton"), bLovense);
    SetVisible(TEXT("HandyConnectButtonV2"), !bHandy);
    SetVisible(TEXT("IntifaceConnectButton"), !bIntiface);
    SetVisible(TEXT("DisconnectIntiface"), bIntiface);
}

void URecoveredToySettingsMenu::OnConnectLovenseClicked() { SetDeviceConnected(TEXT("ToyLovenseConnected"), true); }
void URecoveredToySettingsMenu::OnConnectMobileLovenseClicked() { SetDeviceConnected(TEXT("ToyLovenseConnected"), true); }
void URecoveredToySettingsMenu::OnDisconnectLovenseClicked() { SetDeviceConnected(TEXT("ToyLovenseConnected"), false); }
void URecoveredToySettingsMenu::OnHandyConnectClicked() { SetDeviceConnected(TEXT("ToyHandyConnected"), true); }
void URecoveredToySettingsMenu::OnRefreshHandyClicked() { RefreshConnectionStates(); }
void URecoveredToySettingsMenu::OnIntifaceConnectClicked() { SetDeviceConnected(TEXT("ToyIntifaceConnected"), true); }
void URecoveredToySettingsMenu::OnDisconnectIntifaceClicked() { SetDeviceConnected(TEXT("ToyIntifaceConnected"), false); }

void URecoveredToySettingsMenu::OnHandyStrokeRangeCommitted() {
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("HandyStrokeRangeSlider")))) {
        auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
        if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(TEXT("HandyStrokeRange"), Slider->GetValue())) Instance->SaveRecoveredState();
    }
}
void URecoveredToySettingsMenu::OnIntifaceStrokeRangeCommitted() {
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("IntifaceStrokeRangeSlider")))) {
        auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
        if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(TEXT("IntifaceStrokeRange"), Slider->GetValue())) Instance->SaveRecoveredState();
    }
}
void URecoveredToySettingsMenu::OnMaxVibrationCommitted() {
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("MaxVibrationIntensitySlider")))) {
        auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
        if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(TEXT("MaxVibrationIntensity"), Slider->GetValue())) Instance->SaveRecoveredState();
    }
}
