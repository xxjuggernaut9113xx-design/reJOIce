#include "RecoveredToySettings.h"

#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

namespace {
const FString AlternatingStrokeMode = TEXT("Alternating (Up/Down Each Beat)");
const FString FullCycleStrokeMode = TEXT("Full Cycle (Complete Stroke Per Beat)");

float ReadSliderValue(UUserWidget* Widget, FName Name) {
    if (const USlider* Slider = Cast<USlider>(Widget->GetWidgetFromName(Name))) return Slider->GetValue();
    return 0.0f;
}

FString ReadEditableText(UUserWidget* Widget, FName Name) {
    if (const UEditableTextBox* Input = Cast<UEditableTextBox>(Widget->GetWidgetFromName(Name))) return Input->GetText().ToString().TrimStartAndEnd();
    return FString();
}
}

void URecoveredToySettingsMenu::BindControls(bool bBind) {
#define BIND_BUTTON(Name, Method) \
    if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this, &URecoveredToySettingsMenu::Method); \
        else Button->OnClicked.RemoveDynamic(this, &URecoveredToySettingsMenu::Method); \
    }
    BIND_BUTTON("ConnectLovenseToysButton", OnConnectLovenseClicked)
    BIND_BUTTON("ConnectMobileLovenseToysButton", OnConnectMobileLovenseClicked)
    BIND_BUTTON("DisconnectLovenseToysButton", OnDisconnectLovenseClicked)
    BIND_BUTTON("HandyConnectButtonV2", OnHandyConnectClicked)
    BIND_BUTTON("RefreshHandyConnectionButton", OnRefreshHandyClicked)
    BIND_BUTTON("SendHandyTestStrokesButton", OnSendHandyTestClicked)
    BIND_BUTTON("StopHandyStrokingButton", OnStopHandyClicked)
    BIND_BUTTON("IntifaceConnectButton", OnIntifaceConnectClicked)
    BIND_BUTTON("DisconnectIntiface", OnDisconnectIntifaceClicked)
    BIND_BUTTON("SendTestIntifaceButton", OnSendIntifaceTestClicked)
    BIND_BUTTON("RefreshIntifaceStatusButton", OnRefreshIntifaceClicked)
    BIND_BUTTON("RefreshLovenseConnectionsButton", OnRefreshLovenseClicked)
    BIND_BUTTON("TestLovenseDevicesButton", OnTestLovenseClicked)
#undef BIND_BUTTON

#define BIND_SLIDER(Name, Committed, Changed) \
    if (USlider* Slider = Cast<USlider>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) { \
            Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredToySettingsMenu::Committed); \
            Slider->OnValueChanged.AddUniqueDynamic(this, &URecoveredToySettingsMenu::Changed); \
        } else { \
            Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredToySettingsMenu::Committed); \
            Slider->OnValueChanged.RemoveDynamic(this, &URecoveredToySettingsMenu::Changed); \
        } \
    }
    BIND_SLIDER("HandyStrokeRangeSlider", OnHandyStrokeRangeCommitted, OnHandyStrokeRangeChanged)
    BIND_SLIDER("IntifaceStrokeRangeSlider", OnIntifaceStrokeRangeCommitted, OnIntifaceStrokeRangeChanged)
    BIND_SLIDER("MaxVibrationIntensitySlider", OnMaxVibrationCommitted, OnMaxVibrationChanged)
#undef BIND_SLIDER

    if (UComboBoxString* Combo = Cast<UComboBoxString>(GetWidgetFromName(TEXT("StrokeModeComboBox")))) {
        if (bBind) Combo->OnSelectionChanged.AddUniqueDynamic(this, &URecoveredToySettingsMenu::OnStrokeModeSelectionChanged);
        else Combo->OnSelectionChanged.RemoveDynamic(this, &URecoveredToySettingsMenu::OnStrokeModeSelectionChanged);
    }
}

URecoveredGameInstance* URecoveredToySettingsMenu::GetRecoveredInstance() const {
    return Cast<URecoveredGameInstance>(GetGameInstance());
}

URecoveredDeviceManager* URecoveredToySettingsMenu::GetDeviceManager() const {
    if (URecoveredGameInstance* Instance = GetRecoveredInstance()) return Instance->DeviceManager;
    return nullptr;
}

void URecoveredToySettingsMenu::BindDeviceManager(bool bBind) {
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) {
        if (bBind) {
            Manager->OnDeviceStateChanged.AddUniqueDynamic(this, &URecoveredToySettingsMenu::OnDeviceStateChanged);
            Manager->OnDeviceConnectionUpdated.AddUniqueDynamic(this, &URecoveredToySettingsMenu::OnDeviceConnectionUpdated);
        } else {
            Manager->OnDeviceStateChanged.RemoveDynamic(this, &URecoveredToySettingsMenu::OnDeviceStateChanged);
            Manager->OnDeviceConnectionUpdated.RemoveDynamic(this, &URecoveredToySettingsMenu::OnDeviceConnectionUpdated);
        }
    }
}

void URecoveredToySettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    LoadSourceSettings();
    BindControls(true);
    BindDeviceManager(true);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::NativeDestruct() {
    BindDeviceManager(false);
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredToySettingsMenu::LoadSourceSettings() {
    URecoveredGameInstance* Instance = GetRecoveredInstance();
    if (!Instance || !Instance->CurrentSave) return;
    URecoveredSaveGame* Save = Instance->CurrentSave;
    if (URecoveredDeviceManager* Manager = Instance->DeviceManager) Manager->LoadDeviceSettings(Save);

    const FString HandyKey = Save->GetStringSetting(TEXT("HandyKey"), FString());
    if (!HandyKey.IsEmpty()) {
        if (UEditableTextBox* Input = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("HandyKeyInputBox")))) Input->SetText(FText::FromString(HandyKey));
    }
    const FString LovenseIP = Save->GetStringSetting(TEXT("LovenseIP"), FString());
    if (!LovenseIP.IsEmpty()) {
        if (UEditableTextBox* Input = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("LovenseMobileIPInputBox")))) Input->SetText(FText::FromString(LovenseIP));
    }
    const FString LovensePort = Save->GetStringSetting(TEXT("LovensePort"), FString());
    if (!LovensePort.IsEmpty()) {
        if (UEditableTextBox* Input = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("LovenseMobilePortInputBox")))) Input->SetText(FText::FromString(LovensePort));
    }
    const FString IntifaceUrl = Save->GetStringSetting(TEXT("ButtplugURL"), TEXT("ws://127.0.0.1:12345"));
    if (!IntifaceUrl.IsEmpty()) {
        if (UEditableTextBox* Input = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("IntifaceServerAddressInputBox")))) Input->SetText(FText::FromString(IntifaceUrl));
    }

    const float StrokeLength = FMath::Clamp(static_cast<float>(Save->GetNumberSetting(TEXT("HandyMaxStrokeLength"), 1.0)), 0.0f, 1.0f);
    if (USlider* Slider = Cast<USlider>(GetWidgetFromName(TEXT("HandyStrokeRangeSlider")))) Slider->SetValue(StrokeLength);
    if (USlider* Slider = Cast<USlider>(GetWidgetFromName(TEXT("IntifaceStrokeRangeSlider")))) Slider->SetValue(StrokeLength);
    const float Vibration = FMath::Clamp(static_cast<float>(Save->GetNumberSetting(TEXT("MaxButtPlugVibratorIntensity"), 1.0)), 0.0f, 1.0f);
    if (USlider* Slider = Cast<USlider>(GetWidgetFromName(TEXT("MaxVibrationIntensitySlider")))) Slider->SetValue(Vibration);

    if (UComboBoxString* Combo = Cast<UComboBoxString>(GetWidgetFromName(TEXT("StrokeModeComboBox")))) {
        if (Combo->FindOptionIndex(AlternatingStrokeMode) == INDEX_NONE) Combo->AddOption(AlternatingStrokeMode);
        if (Combo->FindOptionIndex(FullCycleStrokeMode) == INDEX_NONE) Combo->AddOption(FullCycleStrokeMode);
        Combo->SetSelectedOption(Save->GetBoolSetting(TEXT("StrokeModeFull?"), true) ? FullCycleStrokeMode : AlternatingStrokeMode);
    }
    OnHandyStrokeRangeChanged(StrokeLength);
    OnIntifaceStrokeRangeChanged(StrokeLength);
    OnMaxVibrationChanged(Vibration);
}

bool URecoveredToySettingsMenu::PersistString(const FString& SettingName, const FString& Value) {
    URecoveredGameInstance* Instance = GetRecoveredInstance();
    return Instance && Instance->CurrentSave && Instance->CurrentSave->SetStringSetting(SettingName, Value) && Instance->SaveRecoveredState();
}

bool URecoveredToySettingsMenu::PersistNumber(const FString& SettingName, double Value) {
    URecoveredGameInstance* Instance = GetRecoveredInstance();
    return Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(SettingName, Value) && Instance->SaveRecoveredState();
}

bool URecoveredToySettingsMenu::PersistBool(const FString& SettingName, bool Value) {
    URecoveredGameInstance* Instance = GetRecoveredInstance();
    return Instance && Instance->CurrentSave && Instance->CurrentSave->SetBoolSetting(SettingName, Value) && Instance->SaveRecoveredState();
}

void URecoveredToySettingsMenu::PlaySourceAnimation(FName AnimationName) {
    PlayRecoveredAnimation(AnimationName);
}

void URecoveredToySettingsMenu::UpdateConnectionLabel(FName LabelName, const FString& Label) {
    if (UTextBlock* Text = Cast<UTextBlock>(GetWidgetFromName(LabelName))) Text->SetText(FText::FromString(Label));
}

void URecoveredToySettingsMenu::UpdateSliderText(FName LabelName, const FString& Prefix, float Value, bool bIncludePercent) {
    if (UTextBlock* Text = Cast<UTextBlock>(GetWidgetFromName(LabelName))) {
        const int32 Percent = FMath::TruncToInt(FMath::Clamp(Value, 0.0f, 1.0f) * 100.0f);
        Text->SetText(FText::FromString(bIncludePercent ? FString::Printf(TEXT("%s: %d%%"), *Prefix, Percent) : FString::Printf(TEXT("%s: %d"), *Prefix, Percent)));
    }
}

void URecoveredToySettingsMenu::PopulateDeviceList(FName ScrollBoxName, const TArray<FString>& Names) {
    UScrollBox* List = Cast<UScrollBox>(GetWidgetFromName(ScrollBoxName));
    if (!List) return;
    List->ClearChildren();
    for (const FString& Name : Names) {
        UTextBlock* Row = NewObject<UTextBlock>(List);
        Row->SetText(FText::FromString(Name));
        List->AddChild(Row);
    }
}

void URecoveredToySettingsMenu::RefreshConnectionStates() {
    URecoveredDeviceManager* Manager = GetDeviceManager();
    const bool bLovense = Manager && Manager->IsDeviceConnected(ERecoveredDeviceKind::Lovense);
    const bool bIntiface = Manager && Manager->IsDeviceConnected(ERecoveredDeviceKind::Intiface);
    const TArray<FString> LovenseDevices = Manager ? Manager->GetConnectedDeviceNames(ERecoveredDeviceKind::Lovense) : TArray<FString>();
    const TArray<FString> IntifaceDevices = Manager ? Manager->GetConnectedDeviceNames(ERecoveredDeviceKind::Intiface) : TArray<FString>();
    const FString HandyStatus = Manager ? Manager->GetConnectionStatusLabel(ERecoveredDeviceKind::Handy) : TEXT("Disconnected");

    UpdateConnectionLabel(TEXT("HandyConnectionStatus"), FString::Printf(TEXT("Status: %s"), *HandyStatus));
    UpdateConnectionLabel(TEXT("TextBlock_277"), FString::Printf(TEXT("Connection Status: %s\r\n%d devices Connected"), bLovense ? TEXT("Connected") : TEXT("Disconnected"), LovenseDevices.Num()));
    UpdateConnectionLabel(TEXT("IntifaceStatusText"), bIntiface ? TEXT("Status: Connected") : TEXT("Status: Disconnected"));
    UpdateConnectionLabel(TEXT("DevicesConnectedCountIntiface"), FString::Printf(TEXT("%d Devices Connected"), IntifaceDevices.Num()));
    PopulateDeviceList(TEXT("LovenseDevicesScrollbox"), LovenseDevices);
    PopulateDeviceList(TEXT("IntifaceDevicesScrollbox"), IntifaceDevices);
}

void URecoveredToySettingsMenu::OnConnectLovenseClicked() {
    PlaySourceAnimation(TEXT("ConnectLovenseViaPCClick"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) {
        const FString DesktopEndpoint = URecoveredDeviceManager::BuildLovenseEndpoint(TEXT("127.0.0.1"), 30010);
        Manager->ConnectDevice(ERecoveredDeviceKind::Lovense, DesktopEndpoint);
    }
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnConnectMobileLovenseClicked() {
    PlaySourceAnimation(TEXT("ConnectMobileLovenseClick"));
    const FString Host = ReadEditableText(this, TEXT("LovenseMobileIPInputBox"));
    int32 Port = 0;
    LexTryParseString(Port, *ReadEditableText(this, TEXT("LovenseMobilePortInputBox")));
    PersistString(TEXT("LovenseIP"), Host);
    PersistString(TEXT("LovensePort"), Port > 0 ? LexToString(Port) : FString());
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->ConnectDevice(ERecoveredDeviceKind::Lovense, URecoveredDeviceManager::BuildLovenseEndpoint(Host, Port));
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnDisconnectLovenseClicked() {
    PlaySourceAnimation(TEXT("DisconnectLovenseToysClick"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->DisconnectDevice(ERecoveredDeviceKind::Lovense);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnHandyConnectClicked() {
    PlaySourceAnimation(TEXT("HandyConnectClick"));
    const FString Key = ReadEditableText(this, TEXT("HandyKeyInputBox"));
    PersistString(TEXT("HandyKey"), Key);
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->ConnectDevice(ERecoveredDeviceKind::Handy, Key);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnRefreshHandyClicked() {
    PlaySourceAnimation(TEXT("RefreshHandyClick"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->RefreshDevice(ERecoveredDeviceKind::Handy);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnSendHandyTestClicked() {
    PlaySourceAnimation(TEXT("HandyTestStrokesClick"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SendTestCommand(ERecoveredDeviceKind::Handy);
}

void URecoveredToySettingsMenu::OnStopHandyClicked() {
    PlaySourceAnimation(TEXT("StopHandyStrokesClick"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->StopDevice(ERecoveredDeviceKind::Handy);
}

void URecoveredToySettingsMenu::OnIntifaceConnectClicked() {
    const FString Endpoint = ReadEditableText(this, TEXT("IntifaceServerAddressInputBox"));
    PersistString(TEXT("ButtplugURL"), Endpoint);
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->ConnectDevice(ERecoveredDeviceKind::Intiface, Endpoint);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnDisconnectIntifaceClicked() {
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->DisconnectDevice(ERecoveredDeviceKind::Intiface);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnSendIntifaceTestClicked() {
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SendTestCommand(ERecoveredDeviceKind::Intiface);
}

void URecoveredToySettingsMenu::OnRefreshIntifaceClicked() {
    if (UScrollBox* Devices = Cast<UScrollBox>(GetWidgetFromName(TEXT("IntifaceDevicesScrollbox")))) Devices->ClearChildren();
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->RefreshDevice(ERecoveredDeviceKind::Intiface);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnRefreshLovenseClicked() {
    PlaySourceAnimation(TEXT("RefreshLovenseConnectionClick"));
    if (UScrollBox* Devices = Cast<UScrollBox>(GetWidgetFromName(TEXT("LovenseDevicesScrollbox")))) Devices->ClearChildren();
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->RefreshDevice(ERecoveredDeviceKind::Lovense);
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnTestLovenseClicked() {
    PlaySourceAnimation(TEXT("TestLovenseDevicesClick"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SendTestCommand(ERecoveredDeviceKind::Lovense);
}

void URecoveredToySettingsMenu::OnHandyStrokeRangeCommitted() {
    const float Value = ReadSliderValue(this, TEXT("HandyStrokeRangeSlider"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SetStrokeRange(0.0f, Value * 100.0f);
    PersistNumber(TEXT("HandyMaxStrokeLength"), Value);
    UpdateSliderText(TEXT("HandyStrokeLengthSliderText"), TEXT("Handy Max Stroke Height Set to"), Value, false);
}

void URecoveredToySettingsMenu::OnIntifaceStrokeRangeCommitted() {
    const float Value = ReadSliderValue(this, TEXT("IntifaceStrokeRangeSlider"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SetStrokeRange(0.0f, Value * 100.0f);
    PersistNumber(TEXT("HandyMaxStrokeLength"), Value);
    UpdateSliderText(TEXT("IntifaceStrokeLengthSlider"), TEXT("Intiface Max Stroke Height Set to"), Value, false);
}

void URecoveredToySettingsMenu::OnMaxVibrationCommitted() {
    const float Value = ReadSliderValue(this, TEXT("MaxVibrationIntensitySlider"));
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SetVibratorIntensity(Value);
    PersistNumber(TEXT("MaxButtPlugVibratorIntensity"), Value);
    UpdateSliderText(TEXT("MaxVibratorIntensityText"), TEXT("Max Vibration Intensity"), Value, true);
}

void URecoveredToySettingsMenu::OnHandyStrokeRangeChanged(float Value) {
    UpdateSliderText(TEXT("HandyStrokeLengthSliderText"), TEXT("Max Stroke Height"), Value, true);
    if (bSynchronizingStrokeSliders) return;
    TGuardValue<bool> SynchronizingGuard(bSynchronizingStrokeSliders, true);
    if (USlider* Intiface = Cast<USlider>(GetWidgetFromName(TEXT("IntifaceStrokeRangeSlider")))) {
        if (!FMath::IsNearlyEqual(Intiface->GetValue(), Value)) Intiface->SetValue(Value);
    }
}

void URecoveredToySettingsMenu::OnIntifaceStrokeRangeChanged(float Value) {
    UpdateSliderText(TEXT("IntifaceStrokeLengthSlider"), TEXT("Max Stroke Height"), Value, true);
    if (bSynchronizingStrokeSliders) return;
    TGuardValue<bool> SynchronizingGuard(bSynchronizingStrokeSliders, true);
    if (USlider* Handy = Cast<USlider>(GetWidgetFromName(TEXT("HandyStrokeRangeSlider")))) {
        if (!FMath::IsNearlyEqual(Handy->GetValue(), Value)) Handy->SetValue(Value);
    }
}

void URecoveredToySettingsMenu::OnMaxVibrationChanged(float Value) {
    UpdateSliderText(TEXT("MaxVibratorIntensityText"), TEXT("Max Vibrator Intensity"), Value, true);
}

void URecoveredToySettingsMenu::OnStrokeModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType) {
    if (SelectedItem != AlternatingStrokeMode && SelectedItem != FullCycleStrokeMode) return;
    const bool bFull = SelectedItem == FullCycleStrokeMode;
    if (URecoveredDeviceManager* Manager = GetDeviceManager()) Manager->SetFullStrokePerBeat(bFull);
    PersistBool(TEXT("StrokeModeFull?"), bFull);
}

void URecoveredToySettingsMenu::OnDeviceStateChanged(ERecoveredDeviceKind DeviceType, bool bConnected) {
    RefreshConnectionStates();
}

void URecoveredToySettingsMenu::OnDeviceConnectionUpdated(const FRecoveredDeviceConnection& Connection) {
    RefreshConnectionStates();
}
