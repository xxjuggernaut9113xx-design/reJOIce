#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredStoreItem.generated.h"

// Native store item widget (Slowdown, BonerPill, Break, DecreaseHeat, Edge,
// Resupply, SuccuShield, XCumChance). Buy/upgrade buttons deduct player coins
// and apply the item effect to the live session through the global manager.
// Prices scale with level; RefreshPrices updates the displayed amounts.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredStoreItemWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") FName ItemID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 BasePurchaseCost = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 BaseUpgradeCost = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 MaxLevel = 3;
    UPROPERTY(BlueprintReadOnly, Category="Recovered Store") int32 CurrentLevel = 0;

    UFUNCTION(BlueprintCallable, Category="Recovered Store") void RefreshPrices();
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetBuyAmount() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetUpgradeAmount() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetEffectDescription() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetUpgradeText() const;
    UFUNCTION(BlueprintCallable, Category="Recovered Store") bool TryBuy();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") bool TryUpgrade();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void BindControls(bool bBind);
    UFUNCTION() void OnBuyClicked();
    UFUNCTION() void OnUpgradeClicked();
    int32 ReadLevelFromSave() const;
    void WriteLevelToSave(int32 Level) const;
    FString LevelSettingName() const;
};
