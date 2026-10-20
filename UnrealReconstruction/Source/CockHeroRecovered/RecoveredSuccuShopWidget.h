#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredSuccuShopWidget.generated.h"

class URecoveredSuccuEconomy;
class UTextBlock;
class UButton;

UCLASS()
class COCKHERORECOVERED_API URecoveredSuccuShopRow : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredSuccuEconomy> Economy;
    UPROPERTY() uint8 Modifier=0;
    void Refresh();
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeConstruct() override;
private:
    UPROPERTY() TObjectPtr<UTextBlock> Label;
    UPROPERTY() TObjectPtr<UButton> BuyButton;
    UFUNCTION() void Buy();
};

UCLASS()
class COCKHERORECOVERED_API URecoveredSuccuShopWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredSuccuEconomy> Economy;
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& Geometry,float DeltaTime) override;
private:
    UPROPERTY() TObjectPtr<UTextBlock> Balance;
    UPROPERTY() TArray<TObjectPtr<URecoveredSuccuShopRow>> Rows;
};
