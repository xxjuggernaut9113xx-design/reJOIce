#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredNotificationWidget.generated.h"

class UTexture2D;
class UWidgetAnimation;
class URecoveredNotificationWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredNotificationExpired,URecoveredNotificationWidget*,Notification);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredNotificationWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable,Category="Recovered Notification") FRecoveredNotificationExpired OnNotificationExpired;
    UFUNCTION(BlueprintCallable,Category="Recovered Notification") void SetNotifBoxParams(UTexture2D* Icon,const FString& InTitle,const FString& InDescription);
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    UWidgetAnimation* FindAnimation(FName Name) const;
    void ApplyParams();
    void BeginFadeOut();
    void Expire();
    FTimerHandle DespawnTimer;
    FTimerHandle RemovalTimer;
    TObjectPtr<UTexture2D> IconTexture;
    FString NotificationTitle;
    FString NotificationDescription;
};
