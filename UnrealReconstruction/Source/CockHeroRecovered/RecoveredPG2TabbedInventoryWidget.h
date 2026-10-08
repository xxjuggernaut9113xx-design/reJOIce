#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredPG2TabbedInventoryWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredPG2TabbedInventoryWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool TabbedInventoryResupplyTrigger();
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ReceiveStoreItem();
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") FText GetResupplyCount() const;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    UFUNCTION() void HandleResupplyClicked();
    UFUNCTION() void HandleRecoveredSessionAction(FName Action);
    class ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void RefreshRecoveredResupplyInventory();
};
