#include "RecoveredAudioSettings.h"
#include "RecoveredRules.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"

namespace {
struct FAudioSliderDef { const TCHAR* Slider; const TCHAR* Setting; const TCHAR* Display; float Fallback; };
// Slider widget name, save setting name, display text widget, default volume.
const FAudioSliderDef GAudioSliders[] = {
    { TEXT("BackgroundMusicVolSlider"), TEXT("MusicVolume"), TEXT("BackgroundMusicVolDisplay"), 0.7f },
    { TEXT("SFXVolSlider"), TEXT("SFXVolume"), TEXT("SFXVolDisplay"), 0.8f },
    { TEXT("MoansVolSlider"), TEXT("MoansVolume"), TEXT("MoansVolDisplay"), 0.8f },
    { TEXT("VoicelinesVolSlider"), TEXT("VoicelinesVolume"), TEXT("VoicelinesVolDisplay"), 0.8f },
    { TEXT("ContextBeatSFXVolSlider"), TEXT("BeatSFXVolume"), TEXT("VoicelinesVolDisplay_1"), 0.8f },
    { TEXT("MetronomeVolSlider"), TEXT("MetronomeVolume"), TEXT("MetronomeVolDisplay"), 0.5f },
};
}

void URecoveredAudioSettingsMenu::BindControls(bool bBind) {
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("BackgroundMusicVolSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredAudioSettingsMenu::OnMusicSliderCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredAudioSettingsMenu::OnMusicSliderCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("SFXVolSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredAudioSettingsMenu::OnSFXSliderCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredAudioSettingsMenu::OnSFXSliderCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("MoansVolSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredAudioSettingsMenu::OnMoansSliderCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredAudioSettingsMenu::OnMoansSliderCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("VoicelinesVolSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredAudioSettingsMenu::OnVoicelinesSliderCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredAudioSettingsMenu::OnVoicelinesSliderCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("ContextBeatSFXVolSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredAudioSettingsMenu::OnBeatSFXSliderCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredAudioSettingsMenu::OnBeatSFXSliderCommitted);
    }
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(TEXT("MetronomeVolSlider")))) {
        if (bBind) Slider->OnMouseCaptureEnd.AddUniqueDynamic(this, &URecoveredAudioSettingsMenu::OnMetronomeSliderCommitted);
        else Slider->OnMouseCaptureEnd.RemoveDynamic(this, &URecoveredAudioSettingsMenu::OnMetronomeSliderCommitted);
    }
}

void URecoveredAudioSettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
    PopulateSliderDefaults();
}

void URecoveredAudioSettingsMenu::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

float URecoveredAudioSettingsMenu::ReadSlider(FName SliderName) const {
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(SliderName))) return Slider->GetValue();
    return 0;
}

void URecoveredAudioSettingsMenu::CommitSliderValue(FName SliderName, const FString& SettingName) {
    const float Value = ReadSlider(SliderName);
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(SettingName, Value)) {
        Instance->SaveRecoveredState();
    }
    for (const auto& Def : GAudioSliders) {
        if (SliderName == FName(Def.Slider)) SetDisplayText(Def.Display, SettingName, Value);
    }
}

void URecoveredAudioSettingsMenu::OnMusicSliderCommitted() { CommitSliderValue(TEXT("BackgroundMusicVolSlider"), TEXT("MusicVolume")); }
void URecoveredAudioSettingsMenu::OnSFXSliderCommitted() { CommitSliderValue(TEXT("SFXVolSlider"), TEXT("SFXVolume")); }
void URecoveredAudioSettingsMenu::OnMoansSliderCommitted() { CommitSliderValue(TEXT("MoansVolSlider"), TEXT("MoansVolume")); }
void URecoveredAudioSettingsMenu::OnVoicelinesSliderCommitted() { CommitSliderValue(TEXT("VoicelinesVolSlider"), TEXT("VoicelinesVolume")); }
void URecoveredAudioSettingsMenu::OnBeatSFXSliderCommitted() { CommitSliderValue(TEXT("ContextBeatSFXVolSlider"), TEXT("BeatSFXVolume")); }
void URecoveredAudioSettingsMenu::OnMetronomeSliderCommitted() { CommitSliderValue(TEXT("MetronomeVolSlider"), TEXT("MetronomeVolume")); }

void URecoveredAudioSettingsMenu::SetSliderFromSetting(FName SliderName, const FString& SettingName, float Fallback) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    const float Value = Instance && Instance->CurrentSave
        ? static_cast<float>(Instance->CurrentSave->GetNumberSetting(SettingName, Fallback))
        : Fallback;
    if (auto* Slider = Cast<USlider>(GetWidgetFromName(SliderName))) Slider->SetValue(Value);
}

void URecoveredAudioSettingsMenu::SetDisplayText(FName TextName, const FString& SettingName, float Fallback) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    const float Value = Instance && Instance->CurrentSave
        ? static_cast<float>(Instance->CurrentSave->GetNumberSetting(SettingName, Fallback))
        : Fallback;
    if (auto* Text = Cast<UTextBlock>(GetWidgetFromName(TextName))) {
        Text->SetText(FText::AsPercent(Value));
    }
}

void URecoveredAudioSettingsMenu::PopulateSliderDefaults() {
    for (const auto& Def : GAudioSliders) {
        SetSliderFromSetting(Def.Slider, Def.Setting, Def.Fallback);
        SetDisplayText(Def.Display, Def.Setting, Def.Fallback);
    }
}
