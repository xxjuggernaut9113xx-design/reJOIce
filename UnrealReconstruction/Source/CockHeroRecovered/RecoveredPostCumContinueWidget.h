#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredPostCumContinueWidget.generated.h"

class UWidgetAnimation;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredPostCumContinueWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void StartRecoveredIdleAnimation();
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") bool IsRecoveredIdleAnimationPlaying() const;
protected:
    virtual void NativeConstruct() override;
private:
    UWidgetAnimation* FindRecoveredAnimation(FName Name) const;
};
