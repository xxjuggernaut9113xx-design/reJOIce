#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "RecoveredMenu.h"
#include "RecoveredMercyRestWidget.generated.h"

class ARecoveredGlobalManager;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredMercyRestWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Mercy Rest") double BreakDuration=60.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Mercy Rest") double CurrentProgress=0.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Mercy Rest") double StartTime=0.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Mercy Rest") bool bIsButtonInputAllowed=false;

    UFUNCTION(BlueprintCallable, Category="Recovered Mercy Rest") void BeginRecoveredMercyRest(ARecoveredGlobalManager* Manager);
    UFUNCTION(BlueprintCallable, Category="Recovered Mercy Rest") void UpdateProgress();
    UFUNCTION(BlueprintCallable, Category="Recovered Mercy Rest") void CancelRecoveredMercyRest();
    UFUNCTION(BlueprintPure, Category="Recovered Mercy Rest") bool IsRecoveredMercyRestActive() const;

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) override;

private:
    UFUNCTION() void HandleCancelBreakClicked();
    ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void CompleteRecoveredMercyRest();
    void StopRecoveredDevices(ARecoveredGlobalManager* Manager) const;

    FTimerHandle UpdateProgressTimerHandle;
    TWeakObjectPtr<ARecoveredGlobalManager> ActiveManager;
    bool bBreakActive=false;
    bool bBreakFinished=false;
};
