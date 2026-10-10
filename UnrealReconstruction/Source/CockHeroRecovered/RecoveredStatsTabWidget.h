#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredStatsTabWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredStatsTabWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Statistics") TObjectPtr<class URecoveredEditUsernameOverlay> ActiveUsernameOverlay;
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Statistics") TObjectPtr<class URecoveredGameInstance> RecoveredInstanceOverride;

    UFUNCTION(BlueprintCallable,Category="Recovered Statistics") void SetRecoveredStatsTabGameInstance(class URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintCallable,Category="Recovered Statistics") void InitializeStats();
    UFUNCTION(BlueprintPure,Category="Recovered Statistics") FString GetRecoveredLifetimeStatsText() const;
    UFUNCTION(BlueprintPure,Category="Recovered Statistics") FString GetRecoveredHighscoresText() const;
    UFUNCTION(BlueprintPure,Category="Recovered Statistics") FString GetRecoveredAverageDurationText() const;
    UFUNCTION(BlueprintPure,Category="Recovered Statistics") FString GetRecoveredAverageEdgesText() const;
    UFUNCTION(BlueprintPure,Category="Recovered Statistics") FString GetRecoveredAverageStrokesPerMinuteText() const;
    UFUNCTION(BlueprintPure,Category="Recovered Statistics") FString GetRecoveredAverageStrokesText() const;
    class URecoveredGameInstance* GetRecoveredStatsTabGameInstance() const;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void OpenEditUsernameOverlay();
    UFUNCTION() void HandleEditBoxClosed();
    void BindControls(bool bBind);
};
