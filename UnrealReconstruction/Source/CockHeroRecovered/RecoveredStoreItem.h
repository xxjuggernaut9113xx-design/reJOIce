#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredStoreItem.generated.h"

// Native event-graph reconstruction for the eight source StoreItems widgets.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredStoreItemWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") FName ItemID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 BasePurchaseCost = 50;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 BaseUpgradeCost = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 MaxLevel = 4;
    UPROPERTY(BlueprintReadOnly, Category="Recovered Store") int32 CurrentLevel = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 PurchaseCost = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 UpgradeCost = 0;

    UFUNCTION(BlueprintCallable, Category="Recovered Store") void RefreshPrices();
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetBuyAmount() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetUpgradeAmount() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetEffectDescription() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetUpgradeText() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetBuyText() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetLevelText() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FText GetTitleText() const;
    UFUNCTION(BlueprintCallable, Category="Recovered Store") bool TryBuy();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") bool TryUse();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") bool TryUpgrade();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void BindControls(bool bBind);
    UFUNCTION() void OnBuyClicked();
    UFUNCTION() void OnUpgradeClicked();
    UFUNCTION() void OnUseClicked();
    UFUNCTION() void OnBuyHovered();
    UFUNCTION() void OnBuyUnhovered();
    UFUNCTION() void OnUpgradeHovered();
    UFUNCTION() void OnUpgradeUnhovered();
    int32 ReadLevelFromSave() const;
    void WriteLevelToSave(int32 Level) const;
    FString LevelSettingName() const;
    void EnsureItemID();
    void SetSourceText(FName WidgetName, const FText& Value) const;
    void PlaySourceAnimation(FName Name);
};
