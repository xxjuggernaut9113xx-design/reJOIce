#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredAudioSettings.generated.h"

// Native AudioSettingsMenu: six volume sliders (music, SFX, moans, voicelines,
// contextual beat SFX, metronome). Each slider commits on mouse capture end and
// persists to the recovered save; PopulateSliderDefaults restores saved values.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredAudioSettingsMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Audio") void PopulateSliderDefaults();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void BindControls(bool bBind);
    void CommitSliderValue(FName SliderName, const FString& SettingName);
    UFUNCTION() void OnMusicSliderCommitted();
    UFUNCTION() void OnSFXSliderCommitted();
    UFUNCTION() void OnMoansSliderCommitted();
    UFUNCTION() void OnVoicelinesSliderCommitted();
    UFUNCTION() void OnBeatSFXSliderCommitted();
    UFUNCTION() void OnMetronomeSliderCommitted();
    void SetSliderFromSetting(FName SliderName, const FString& SettingName, float Fallback);
    void SetDisplayText(FName TextName, const FString& SettingName, float Fallback);
    float ReadSlider(FName SliderName) const;
};
