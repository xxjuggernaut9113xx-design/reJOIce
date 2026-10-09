#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredPG2TabbedInventoryWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredPG2TabbedInventoryWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventoryResupplyTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool UseBonerPillItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool ToggleSuccuShields();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventoryBreakTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventorySlowdownTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveStoreItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveBonerPillItem();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveSuccuShieldItems();
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetResupplyCount() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetBonerPillCount() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetSuccuShieldAvailableText() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetBreakAmountText() const;
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetSlowdownQuantityText() const;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    UFUNCTION() void HandleResupplyClicked();
    UFUNCTION() void HandleBonerPillClicked();
    UFUNCTION() void HandleSuccuShieldClicked();
    UFUNCTION() void HandleBreakClicked();
    UFUNCTION() void HandleSlowdownClicked();
    UFUNCTION() void HandleBonerPillHovered();
    UFUNCTION() void HandleBonerPillUnhovered();
    UFUNCTION() void HandleSuccuShieldHovered();
    UFUNCTION() void HandleSuccuShieldUnhovered();
    UFUNCTION() void HandleResupplyHovered();
    UFUNCTION() void HandleResupplyUnhovered();
    UFUNCTION() void HandleBreakHovered();
    UFUNCTION() void HandleBreakUnhovered();
    UFUNCTION() void HandleSlowdownHovered();
    UFUNCTION() void HandleSlowdownUnhovered();
    UFUNCTION() void HandleRecoveredSessionAction(FName Action);
    class ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void RefreshRecoveredPG2Inventory();
};
