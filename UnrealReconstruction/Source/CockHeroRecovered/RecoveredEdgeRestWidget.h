#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "RecoveredMenu.h"
#include "RecoveredEdgeRestWidget.generated.h"

class ARecoveredGlobalManager;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredEdgeRestWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    URecoveredEdgeRestWidget();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Edge Rest") double BreakDuration=1.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Edge Rest") double CurrentProgress=0.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Edge Rest") double StartTime=0.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Edge Rest") bool bIsButtonInputAllowed=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Edge Rest") int32 EdgesLeft=0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Edge Rest") TArray<FText> LoadScreenTipsArray;

    UFUNCTION(BlueprintCallable, Category="Recovered Edge Rest") void BeginRecoveredEdgeRest(ARecoveredGlobalManager* Manager,int32 InEdgesLeft);
    UFUNCTION(BlueprintCallable, Category="Recovered Edge Rest") void UpdateProgress();
    UFUNCTION(BlueprintCallable, Category="Recovered Edge Rest") void UpdateEdgesLeftUntilMercy(int32 InEdgesLeft);
    UFUNCTION(BlueprintCallable, Category="Recovered Edge Rest") void CancelRecoveredEdgeRest();
    UFUNCTION(BlueprintPure, Category="Recovered Edge Rest") bool IsRecoveredEdgeRestActive() const;
protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) override;
private:
    UFUNCTION() void HandleCancelBreakClicked();
    ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void CompleteRecoveredEdgeRest();
    void StopRecoveredDevices(ARecoveredGlobalManager* Manager) const;
    void UpdateRecoveredTip();

    FTimerHandle UpdateProgressTimerHandle;
    TWeakObjectPtr<ARecoveredGlobalManager> ActiveManager;
    bool bBreakActive=false;
    bool bBreakFinished=false;
};
