#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredModifierCardEntryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredModifierCardClicked,const FText&,SourceModifierTitle,UUserWidget*,Entry);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredModifierCardEntryWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable,Category="Recovered Modifier") FRecoveredModifierCardClicked OnCardClicked;
    UFUNCTION(BlueprintCallable,Category="Recovered Modifier") void PopulateDetails(bool bInUnlocked,bool bInEnabled,const FText& InTitle,class UTexture2D* InIcon,const FText& InDescription,const FText& InChallengeTitle,const FText& InChallengeDescription);
    UFUNCTION(BlueprintCallable,Category="Recovered Modifier") void SetButtonToggle(bool bEnabled);
    UFUNCTION(BlueprintCallable,Category="Recovered Modifier") void SetButtonToggleWithSound(bool bEnabled);
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    UFUNCTION() void HandleBackgroundHover();
    UFUNCTION() void HandleBackgroundUnhover();
    UFUNCTION() void HandleToggleHover();
    UFUNCTION() void HandleToggleUnhover();
    UFUNCTION() void HandleToggleClick();
    void BindSourceTree();
    void BindSourceEvents();
    void ApplyTooltip();
    void PlaySourceAnimation(FName Name);
    void PlaySourceSound(const TCHAR* Path,float Volume,float Pitch,float StartTime) const;
    UPROPERTY(Transient) TObjectPtr<class UButton> SourceBackgroundButton;
    UPROPERTY(Transient) TObjectPtr<class UButton> SourceToggleButton;
    UPROPERTY(Transient) TObjectPtr<class UBorder> SourceLockOverlay;
    UPROPERTY(Transient) TObjectPtr<class UImage> SourceModifierIcon;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceModifierTitle;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceModifierDescription;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceChallengeRequirement;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceButtonText;
    UPROPERTY(Transient) TObjectPtr<class URecoveredTooltip> Tooltip;
    bool bUnlocked=false;
    FText StoredTitle;
    FText StoredDescription;
    FText StoredChallengeTitle;
    FText StoredChallengeDescription;
};
