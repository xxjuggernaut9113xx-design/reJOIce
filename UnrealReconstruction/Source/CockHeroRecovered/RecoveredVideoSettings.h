#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredVideoSettings.generated.h"

// Native VideoSettingsMenu: content/preference combo boxes plus the clear
// favorites button. Each combo commits its selection to the recovered save on
// change; the setting name is derived from the widget name.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredVideoSettingsMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Video") void PopulateComboDefaults();
    static bool WritePreference(class URecoveredSaveGame* Save,FName Name,const FString& Value);
    static FString ReadPreference(class URecoveredSaveGame* Save,FName Name,const FString& Fallback);
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    TMap<FName, FString> LastSelections;
    void BindControls(bool bBind);
    UFUNCTION() void OpenCalibration();
    UFUNCTION() void OnComboSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
    void ApplyGraphicsSetting(const FString& Key, const FString& Value);
    UFUNCTION() void OnClearFavoritesClicked();
    void CommitComboValue(FName ComboName, const FString& SelectedItem);
    static FString SettingNameForCombo(FName ComboName);
};
