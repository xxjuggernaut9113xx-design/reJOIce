#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredSessionWidget.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredSessionWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable,Category="Recovered Media") void DisplayMedia(class UTexture* Texture);
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void ResumeSession();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void PauseSession();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void OpenSessionSettings();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void DrawCard();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void SwitchInventoryTabs();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void RefreshSessionDisplays(class ARecoveredGlobalManager* Manager);
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void QuitSession();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void ToggleFavorite();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void ToggleRecoveredUI();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void ToggleRecoveredChallengeTracker();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void CycleRecoveredCropMode();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void RequestRecoveredCumMedia();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void RequestRecoveredTaunt();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    virtual void NativeTick(const FGeometry& Geometry,float DeltaSeconds) override;
private:
    void BindSession(bool bBind);
    UFUNCTION() void RequestRecoveredCumMediaFromButton();
    void RequestRecoveredCumMediaWithAnimation(FName AnimationName);
    bool bUIHidden=false;
    uint8 CurrentContentStretchState=0;
};
