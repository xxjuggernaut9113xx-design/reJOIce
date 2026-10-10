#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredStatsWidget.generated.h"

class URecoveredSaveGame;
class URecoveredGameInstance;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredStatsScreenWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 HighestCombo=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 HighestSessionTime=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 HighestEdges=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 HighestStrokeCount=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 AvgSessionEdges=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 AvgStrokesPerEdge=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 AvgStrokeCount=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 AvgCombo=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered|Statistics") int32 AvgTime=0;

    void SetRecoveredStatisticsGameInstance(URecoveredGameInstance* Instance);
    void InitializeRecoveredStatsScreen();
    UFUNCTION(BlueprintCallable,Category="Recovered|Statistics") void RefreshRecoveredStats();
    UFUNCTION(BlueprintCallable,Category="Recovered|Statistics") void CalculateHighScores();
    UFUNCTION(BlueprintCallable,Category="Recovered|Statistics") void CalculateLifetimeAverages();
    UFUNCTION(BlueprintCallable,Category="Recovered|Statistics") void CloseRecoveredStats();
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText FormatRecoveredTime(int32 Time) const;
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText GetRecoveredLifetimeStatsDisplay() const;
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText GetRecoveredHighScores() const;
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText GetRecoveredAvgSessionDurationText() const;
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText GetRecoveredAvgEdgesText() const;
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText GetRecoveredAvgStrokesPerEdgeText() const;
    UFUNCTION(BlueprintPure,Category="Recovered|Statistics") FText GetRecoveredAvgStrokeCountText() const;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void PlayBackButtonHover();
    UFUNCTION() void PlayBackButtonUnhover();
    void BindRecoveredNavigation(bool bBind);
    void ApplyRecoveredTextBindings();
    URecoveredGameInstance* GetRecoveredInstance() const;
    URecoveredSaveGame* GetRecoveredSave() const;
    UPROPERTY(Transient) TObjectPtr<URecoveredGameInstance> RecoveredInstanceOverride;
};
