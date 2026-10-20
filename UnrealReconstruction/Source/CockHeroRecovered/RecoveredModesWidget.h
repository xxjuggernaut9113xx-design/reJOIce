#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "RecoveredModesWidget.generated.h"

UCLASS()
class COCKHERORECOVERED_API URecoveredModesWidget : public UUserWidget {
    GENERATED_BODY()
protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeTick(const FGeometry& Geometry, float DeltaTime) override;
private:
    UFUNCTION() void StartTower();
    UFUNCTION() void StartClassic();
    UFUNCTION() void ClassicObjectiveChanged(FString Selection,ESelectInfo::Type SelectionType);
    UFUNCTION() void StartPlaylist();
    UFUNCTION() void ConfirmLoadout();
    void ShowLoadout(uint8 Mode);
    uint8 LoadoutMode = 0;
    UPROPERTY(Transient) TObjectPtr<class URecoveredNewerInventory> LoadoutInventory;
    UPROPERTY(Transient) TObjectPtr<class UVerticalBox> LoadoutPanel;
    UPROPERTY(Transient) TArray<TObjectPtr<UComboBoxString>> LoadoutSlots;
    UFUNCTION() void PickFirst();
    UFUNCTION() void PickSecond();
    UFUNCTION() void PickThird();
    UFUNCTION() void ContinueRound();
    UFUNCTION() void TogglePause();
    UFUNCTION() void UpgradeDuration();
    UFUNCTION() void UpgradeCharges();
    UFUNCTION() void UpgradeRecharge();
    void ChooseMusicUpgrade(uint8 Type);
    UFUNCTION() void ClosePanel();
    void Pick(int32 Index);
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> Status;
    UPROPERTY(Transient) TObjectPtr<class UEditableTextBox> PlaylistFolder;
    UPROPERTY(Transient) TObjectPtr<class UButton> TowerButton;
    UPROPERTY(Transient) TObjectPtr<class UButton> PlaylistButton;
    UPROPERTY(Transient) TObjectPtr<class UButton> ContinueButton;
    UPROPERTY(Transient) TObjectPtr<class UButton> PauseButton;
    UPROPERTY(Transient) TArray<TObjectPtr<class UButton>> OptionButtons;
};
