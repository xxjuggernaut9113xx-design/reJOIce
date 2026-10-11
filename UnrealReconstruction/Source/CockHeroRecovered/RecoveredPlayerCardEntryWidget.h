#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredPlayerCardEntryWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredPlayerCardEntryClicked,FName,CardID);

UCLASS()
class COCKHERORECOVERED_API URecoveredPlayerCardEntryWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable,Category="Recovered Player Card") FRecoveredPlayerCardEntryClicked OnClicked;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Player Card") FName CardID=NAME_None;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Player Card") bool bUnlocked=false;

    void PopulatePlayerCard(
        FName InCardID,
        class UTexture2D* InCardImage,
        const FString& InRequiredChallengeID,
        int32 InRequiredLevel,
        bool bInUnlocked,
        const FText& InChallengeDescription,
        const FText& InChallengeTitle,
        const FText& InCardName,
        const FLinearColor& InCardTint);

protected:
    virtual TSharedRef<SWidget> RebuildWidget() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void HandleCardHovered();
    UFUNCTION() void HandleCardUnhovered();
    UFUNCTION() void HandleCardClicked();

    void BuildWidgetTree();
    void BindRecoveredWidgetTree();
    void BindSourceInteractions();
    void ApplyPresentation();
    void ApplySourceCardStyle();
    void ApplySourceTooltip();
    void PlaySourceAnimation(FName AnimationName);
    void PlaySourceSound(const TCHAR* AssetPath,float VolumeMultiplier,float PitchMultiplier) const;

    UPROPERTY(Transient) TObjectPtr<class USizeBox> RootSize;
    UPROPERTY(Transient) TObjectPtr<class UButton> SourceCardButton;
    UPROPERTY(Transient) TObjectPtr<class UOverlay> SourceLockOverlay;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> RequirementCaption;
    UPROPERTY(Transient) TObjectPtr<class UTexture2D> SourceTexture;
    UPROPERTY(Transient) TObjectPtr<class UTexture2D> LockedTexture;
    UPROPERTY(Transient) TObjectPtr<class URecoveredTooltip> CardTooltip;
    FString RequiredChallengeID;
    int32 RequiredLevel=0;
    FText ChallengeDescription;
    FText ChallengeTitle;
    FText CardName;
    FLinearColor CardTint=FLinearColor::White;
};
