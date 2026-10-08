#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredTabbedInventoryWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredTabbedInventoryWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventoryEdgeTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool UseReduceHeatItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventoryBreakTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventorySlowdownTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool UseCumChanceItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveEdgeItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveHeatItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveBreakItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveSlowdownItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveCumChanceItem();
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetEdgeAvailableText() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetHeatDecreaseAvailableText() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetBreakAmountText() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetSlowdownQuantityText() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetCumChanceAvailableText() const;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    UFUNCTION() void HandleEdgeItemClicked();
    UFUNCTION() void HandleDecreaseHeatClicked();
    UFUNCTION() void HandleBreakClicked();
    UFUNCTION() void HandleSlowdownClicked();
    UFUNCTION() void HandleCumChanceClicked();
    UFUNCTION() void HandleRecoveredSessionAction(FName Action);
    class ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void RefreshRecoveredEdgeInventory();
    void RefreshRecoveredDefensiveInventory();
};
