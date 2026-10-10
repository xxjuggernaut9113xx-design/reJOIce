#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredPlayerCardsTabWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredPlayerCardsTabWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Player Cards") TObjectPtr<class URecoveredEditUsernameOverlay> ActiveUsernameOverlay;
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Player Cards") TObjectPtr<class URecoveredGameInstance> RecoveredInstanceOverride;
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Player Cards") TArray<TObjectPtr<class URecoveredPlayerCardEntryWidget>> RecoveredCardEntries;
    UPROPERTY(Transient,meta=(BindWidgetAnim),BlueprintReadOnly,Category="Recovered Player Cards") TObjectPtr<class UWidgetAnimation> UpdateEquippedCard;

    UFUNCTION(BlueprintCallable,Category="Recovered Player Cards") void SetRecoveredPlayerCardsGameInstance(class URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintCallable,Category="Recovered Player Cards") void InitializePlayerCards();
    UFUNCTION(BlueprintCallable,Category="Recovered Player Cards") void PopulatePlayerCards();
    UFUNCTION(BlueprintCallable,Category="Recovered Player Cards") void PlayerCardClick(FName CardID);
    UFUNCTION(BlueprintCallable,Category="Recovered Player Cards") void ChangeSelectedPlayerCardDisplay();
    UFUNCTION(BlueprintCallable,Category="Recovered Player Cards") void UpdateLevelDisplay();
    UFUNCTION(BlueprintPure,Category="Recovered Player Cards") int32 GetPlayerCardEntryCount() const;
    class URecoveredGameInstance* GetRecoveredPlayerCardsGameInstance() const;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void OpenEditUsernameOverlay();
    UFUNCTION() void OnEditBoxClosed();
    void BindControls(bool bBind);
    void UpdatePlayerCardName();
};
