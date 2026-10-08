#include "RecoveredNotificationWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"

UWidgetAnimation* URecoveredNotificationWidget::FindAnimation(FName Name) const {
    const auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(GetClass());
    if (!Generated) return nullptr;
    for (UWidgetAnimation* Animation:Generated->Animations) if (Animation && Animation->GetFName()==Name) return Animation;
    return nullptr;
}

void URecoveredNotificationWidget::ApplyParams() {
    if (auto* Title=Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")))) Title->SetText(FText::FromString(NotificationTitle));
    if (auto* Description=Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")))) Description->SetText(FText::FromString(NotificationDescription));
    if (auto* Icon=Cast<UImage>(GetWidgetFromName(TEXT("NotificationIcon")))) Icon->SetBrushFromTexture(IconTexture,false);
}

void URecoveredNotificationWidget::NativeConstruct() {
    Super::NativeConstruct();
    ApplyParams();
}

void URecoveredNotificationWidget::NativeDestruct() {
    if (UWorld* World=GetWorld()) {
        World->GetTimerManager().ClearTimer(DespawnTimer);
        World->GetTimerManager().ClearTimer(RemovalTimer);
    }
    Super::NativeDestruct();
}

void URecoveredNotificationWidget::SetNotifBoxParams(UTexture2D* Icon,const FString& InTitle,const FString& InDescription) {
    IconTexture=Icon;
    NotificationTitle=InTitle;
    NotificationDescription=InDescription;
    ApplyParams();
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,TEXT("/Engine/VREditor/Sounds/UI/Dockable_Window_Pick_Up.Dockable_Window_Pick_Up"))) {
        if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,1.0f,1.0f,0.0f,nullptr,nullptr,true);
    }
    if (UWidgetAnimation* FadeIn=FindAnimation(TEXT("FadeIn"))) PlayAnimation(FadeIn);
    if (UWorld* World=GetWorld()) World->GetTimerManager().SetTimer(DespawnTimer,this,&URecoveredNotificationWidget::BeginFadeOut,4.0f,false);
}

void URecoveredNotificationWidget::BeginFadeOut() {
    UWidgetAnimation* FadeOut=FindAnimation(TEXT("FadeOut"));
    if (!FadeOut) {
        Expire();
        return;
    }
    PlayAnimation(FadeOut);
    const float Duration=FMath::Max(FadeOut->GetEndTime()-FadeOut->GetStartTime(),KINDA_SMALL_NUMBER);
    if (UWorld* World=GetWorld()) World->GetTimerManager().SetTimer(RemovalTimer,this,&URecoveredNotificationWidget::Expire,Duration,false);
    else Expire();
}

void URecoveredNotificationWidget::Expire() {
    OnNotificationExpired.Broadcast(this);
    RemoveFromParent();
}
