#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "RecoveredMenu.h"
#include "RecoveredRestWidget.generated.h"

class ARecoveredGlobalManager;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredRestWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Break") double BreakDuration=5.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Break") double CurrentProgress=0.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Break") double StartTime=0.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Break") bool bIsButtonInputAllowed=false;
    UFUNCTION(BlueprintCallable, Category="Recovered Break") void BeginRecoveredBreak(ARecoveredGlobalManager* Manager);
    UFUNCTION(BlueprintCallable, Category="Recovered Break") void UpdateProgress();
    UFUNCTION(BlueprintCallable, Category="Recovered Break") void CancelRecoveredBreak();
    UFUNCTION(BlueprintPure, Category="Recovered Break") bool IsRecoveredBreakActive() const;
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
private:
    UFUNCTION() void HandleCancelBreakClicked();
    ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void CompleteRecoveredBreak();
    FTimerHandle UpdateProgressTimerHandle;
    TWeakObjectPtr<ARecoveredGlobalManager> ActiveManager;
    bool bBreakActive=false;
    bool bBreakFinished=false;
};
