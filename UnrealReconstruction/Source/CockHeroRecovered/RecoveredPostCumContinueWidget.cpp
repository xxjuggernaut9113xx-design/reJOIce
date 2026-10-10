#include "RecoveredPostCumContinueWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"

UWidgetAnimation* URecoveredPostCumContinueWidget::FindRecoveredAnimation(FName Name) const {
    const auto* GeneratedClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
    if (!GeneratedClass) return nullptr;
    for (UWidgetAnimation* Animation : GeneratedClass->Animations) {
        if (Animation && Animation->GetFName() == Name) return Animation;
    }
    return nullptr;
}

void URecoveredPostCumContinueWidget::NativeConstruct() {
    Super::NativeConstruct();
    StartRecoveredIdleAnimation();
}

void URecoveredPostCumContinueWidget::StartRecoveredIdleAnimation() {
    UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("IdleButton_INST"));
    if (!Animation || IsAnimationPlaying(Animation)) return;
    PlayAnimation(Animation, 0.0f, 0, EUMGSequencePlayMode::Forward, 1.0f, false);
}

bool URecoveredPostCumContinueWidget::IsRecoveredIdleAnimationPlaying() const {
    const UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("IdleButton_INST"));
    return Animation && IsAnimationPlaying(Animation);
}
