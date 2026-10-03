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
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    TMap<FName, FString> LastSelections;
    void BindControls(bool bBind);
    UFUNCTION() void OnComboSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
    UFUNCTION() void OnClearFavoritesClicked();
    void CommitComboValue(FName ComboName, const FString& SelectedItem);
    static FString SettingNameForCombo(FName ComboName);
};
