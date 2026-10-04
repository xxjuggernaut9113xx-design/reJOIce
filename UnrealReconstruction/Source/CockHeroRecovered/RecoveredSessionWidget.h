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
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void RefreshSessionDisplays(class ARecoveredGlobalManager* Manager);
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void QuitSession();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void ToggleAutoDraw();
    UFUNCTION(BlueprintCallable,Category="Recovered Session") void ToggleFavorite();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
    UPROPERTY() bool bAutoDrawEnabled = false;
    virtual void NativeTick(const FGeometry& Geometry,float DeltaSeconds) override;
private:
    void BindSession(bool bBind);
};
