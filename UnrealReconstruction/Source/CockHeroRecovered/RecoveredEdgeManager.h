#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "RecoveredEdgeManager.generated.h"

class ARecoveredGlobalManager;
class UUserWidget;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API ARecoveredEdgeManager : public AActor {
    GENERATED_BODY()
public:
    ARecoveredEdgeManager();
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Edge") TObjectPtr<ARecoveredGlobalManager> GlobalManagerRef;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Edge") FTimerHandle EdgeHoldTimerHandle;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Edge") double MasterEdgeHoldDuration=0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Edge") double CurrentEdgeHoldDuration=0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Edge") int32 MasterEdgesUntilNextMercy=5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Edge") int32 CurrentEdgesUntillNextMercy=5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Edge") double PostEdgeBreakDuration=1.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Edge") bool bIsPerfectEdge=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Edge") double LastEdgeRatio=0.0;
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered|Edge") TObjectPtr<UUserWidget> EdgeHoldCountdownOverlay;

    UFUNCTION(BlueprintCallable, Category="Recovered|Edge") void SetRecoveredGlobalManager(ARecoveredGlobalManager* Manager);
    UFUNCTION(BlueprintCallable, Category="Recovered|Edge") bool TriggerRecoveredEdgeV2();
    UFUNCTION(BlueprintCallable, Category="Recovered|Edge") void BeginRecoveredEdgeHold(double AdjustedPostEdgeBreakDuration);
    UFUNCTION(BlueprintCallable, Category="Recovered|Edge") void CountdownEdgeHold();
    UFUNCTION(BlueprintCallable, Category="Recovered|Edge") void ClearRecoveredEdgeHold();
    UFUNCTION(BlueprintPure, Category="Recovered|Edge") bool IsRecoveredEdgeHoldActive() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Edge") bool IsRecoveredEdgeResolutionPending() const;
    UFUNCTION(BlueprintCallable, Category="Recovered|Edge") bool CheckRecoveredEdgesUntilMercy();

private:
    void AdjustRecoveredBreakDuration();
    double AdjustRecoveredPostEdgeBreakDelay();
    void GiveRecoveredEdge();
    void CompleteRecoveredEdgeBreak();
    void ScheduleRecoveredEdgeCompletion(bool bPerfect,double AdjustedPostEdgeBreakDuration);
    void CreateRecoveredEdgeHoldOverlay();
    void UpdateRecoveredEdgeHoldOverlay(int32 SecondsLeft);
    void RemoveRecoveredEdgeHoldOverlay();
    FTimerHandle EdgeResolutionTimerHandle;
};
