#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredDecisionWidgets.generated.h"

class ARecoveredGlobalManager;
class UWidgetAnimation;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredMercyEventWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Mercy") bool bButtonPressEnabled=false;

    UFUNCTION(BlueprintCallable, Category="Recovered Mercy") void SelectRecoveredMercyYes();
    UFUNCTION(BlueprintCallable, Category="Recovered Mercy") void SelectRecoveredMercyNo();
    UFUNCTION(BlueprintCallable, Category="Recovered Mercy") void CloseRecoveredMercyEvent();

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UFUNCTION() void HandleYesClicked();
    UFUNCTION() void HandleNoClicked();
    ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void RemoveRecoveredOverlay(ARecoveredGlobalManager* Manager);

    TWeakObjectPtr<ARecoveredGlobalManager> ActiveManager;
    bool bCloseAfterNoSelection=false;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredTemptationEventWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Temptation") bool bButtonPressEnabled=false;

    UFUNCTION(BlueprintCallable, Category="Recovered Temptation") void SelectRecoveredTemptationYes();
    UFUNCTION(BlueprintCallable, Category="Recovered Temptation") void SelectRecoveredTemptationNo();

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    virtual FReply NativeOnKeyDown(const FGeometry& InGeometry,const FKeyEvent& InKeyEvent) override;

private:
    UFUNCTION() void HandleYesClicked();
    UFUNCTION() void HandleNoClicked();
    ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    void RemoveRecoveredOverlay(ARecoveredGlobalManager* Manager);

    TWeakObjectPtr<ARecoveredGlobalManager> ActiveManager;
};
