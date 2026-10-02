#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredCalibration.h"
#include "RecoveredCalibrationWidget.generated.h"
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredCalibrationWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadOnly) TObjectPtr<URecoveredCalibrationManager> CalibrationManager;
    UFUNCTION() void StartSequence();
    UFUNCTION() void RegisterTap();
    UFUNCTION() void CloseCalibration();
    UFUNCTION() void ShowMetronome();
    UFUNCTION() void ShowProgress(uint8 State,float Progress);
    UFUNCTION() void CalibrationComplete(const FRecoveredLatencyProfile& Profile);
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void BindControls(bool Bind);
};
