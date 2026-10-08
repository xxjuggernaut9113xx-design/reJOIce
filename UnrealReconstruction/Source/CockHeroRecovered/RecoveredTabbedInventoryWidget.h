#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredTabbedInventoryWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredTabbedInventoryWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventoryEdgeTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveEdgeItem();
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetEdgeAvailableText() const;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    UFUNCTION() void HandleEdgeItemClicked();
    UFUNCTION() void HandleRecoveredSessionAction(FName Action);
    class ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void RefreshRecoveredEdgeInventory();
};
