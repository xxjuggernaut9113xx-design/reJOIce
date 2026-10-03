#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredToySettings.generated.h"

// Native ToySettingsMenu: device connect/disconnect plus stroke-range and
// vibration-intensity sliders. Connection state persists to the recovered save;
// the live device managers consume FRecoveredDeviceState separately.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredToySettingsMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Toys") void RefreshConnectionStates();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void BindControls(bool bBind);
    UFUNCTION() void OnConnectLovenseClicked();
    UFUNCTION() void OnConnectMobileLovenseClicked();
    UFUNCTION() void OnDisconnectLovenseClicked();
    UFUNCTION() void OnHandyConnectClicked();
    UFUNCTION() void OnRefreshHandyClicked();
    UFUNCTION() void OnIntifaceConnectClicked();
    UFUNCTION() void OnDisconnectIntifaceClicked();
    UFUNCTION() void OnHandyStrokeRangeCommitted();
    UFUNCTION() void OnIntifaceStrokeRangeCommitted();
    UFUNCTION() void OnMaxVibrationCommitted();
    void SetDeviceConnected(const FString& SettingName, bool bConnected);
    bool IsDeviceConnected(const FString& SettingName) const;
    void UpdateConnectionLabel(FName LabelName, bool bConnected);
};
