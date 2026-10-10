#pragma once

#include "CoreMinimal.h"
#include "Components/ComboBoxString.h"
#include "RecoveredDeviceInterface.h"
#include "RecoveredMenu.h"
#include "RecoveredToySettings.generated.h"

class URecoveredDeviceManager;
class URecoveredGameInstance;
#if WITH_DEV_AUTOMATION_TESTS
class FRecoveredToySettingsParityTest;
#endif

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredToySettingsMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Toys") void RefreshConnectionStates();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
#if WITH_DEV_AUTOMATION_TESTS
    friend class FRecoveredToySettingsParityTest;
#endif
    void BindControls(bool bBind);
    void BindDeviceManager(bool bBind);
    void LoadSourceSettings();
    void PopulateDeviceList(FName ScrollBoxName, const TArray<FString>& Names);
    void UpdateConnectionLabel(FName LabelName, const FString& Label);
    void UpdateSliderText(FName LabelName, const FString& Prefix, float Value, bool bIncludePercent);
    bool PersistString(const FString& SettingName, const FString& Value);
    bool PersistNumber(const FString& SettingName, double Value);
    bool PersistBool(const FString& SettingName, bool Value);
    URecoveredGameInstance* GetRecoveredInstance() const;
    URecoveredDeviceManager* GetDeviceManager() const;
    void PlaySourceAnimation(FName AnimationName);

    UFUNCTION() void OnConnectLovenseClicked();
    UFUNCTION() void OnConnectMobileLovenseClicked();
    UFUNCTION() void OnDisconnectLovenseClicked();
    UFUNCTION() void OnHandyConnectClicked();
    UFUNCTION() void OnRefreshHandyClicked();
    UFUNCTION() void OnSendHandyTestClicked();
    UFUNCTION() void OnStopHandyClicked();
    UFUNCTION() void OnIntifaceConnectClicked();
    UFUNCTION() void OnDisconnectIntifaceClicked();
    UFUNCTION() void OnSendIntifaceTestClicked();
    UFUNCTION() void OnRefreshIntifaceClicked();
    UFUNCTION() void OnRefreshLovenseClicked();
    UFUNCTION() void OnTestLovenseClicked();
    UFUNCTION() void OnHandyStrokeRangeCommitted();
    UFUNCTION() void OnIntifaceStrokeRangeCommitted();
    UFUNCTION() void OnMaxVibrationCommitted();
    UFUNCTION() void OnHandyStrokeRangeChanged(float Value);
    UFUNCTION() void OnIntifaceStrokeRangeChanged(float Value);
    UFUNCTION() void OnMaxVibrationChanged(float Value);
    UFUNCTION() void OnStrokeModeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
    UFUNCTION() void OnDeviceStateChanged(ERecoveredDeviceKind DeviceType, bool bConnected);
    UFUNCTION() void OnDeviceConnectionUpdated(const FRecoveredDeviceConnection& Connection);

    bool bSynchronizingStrokeSliders = false;
};
