#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredSaveSlotWidget.generated.h"

// Save slot management: list slots, create, load, delete.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredSaveSlotWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Save") void RefreshSlotList();
    UFUNCTION(BlueprintCallable, Category="Recovered Save") bool CreateSaveSlot(const FString& SlotName);
    UFUNCTION(BlueprintCallable, Category="Recovered Save") bool LoadSaveSlot(const FString& SlotName);
    UFUNCTION(BlueprintCallable, Category="Recovered Save") bool DeleteSaveSlot(const FString& SlotName);
    UFUNCTION(BlueprintPure, Category="Recovered Save") TArray<FString> GetSaveSlotNames() const;
protected:
    virtual void NativeConstruct() override;
};
