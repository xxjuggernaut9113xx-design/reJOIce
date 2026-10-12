#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredChallengeEntryWidget.generated.h"

class URecoveredChallengeEntryWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredChallengeEntryClicked,FName,ChallengeID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredChallengeEntryTrackClicked,FName,ChallengeID,URecoveredChallengeEntryWidget*,ChallengeEntryWidget);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredChallengeEntryWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable,Category="Recovered Challenge") FRecoveredChallengeEntryClicked OnChallengeClicked;
    UPROPERTY(BlueprintAssignable,Category="Recovered Challenge") FRecoveredChallengeEntryTrackClicked OnTrackButtonClicked;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Challenge") FName ChallengeID=NAME_None;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Challenge") bool bChallengeComplete=false;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Challenge") bool bChallengeTracked=false;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Challenge") bool bRewardsClaimed=false;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Challenge") int32 TrackedChallengesLength=0;

    UFUNCTION(BlueprintCallable,Category="Recovered Challenge") void PopulateChallengeEntry(
        FName InChallengeID,
        const FText& InChallengeTitle,
        class UTexture2D* InChallengeIcon,
        bool bInChallengeComplete,
        const TArray<FRecoveredReward>& InRewards,
        bool bInChallengeTracked,
        int32 InTrackedChallengesLength,
        bool bInRewardsClaimed);
    UFUNCTION(BlueprintCallable,Category="Recovered Challenge") void SetTrackButtonText(const FText& InText);

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void HandleEntryHovered();
    UFUNCTION() void HandleEntryUnhovered();
    UFUNCTION() void HandleEntryClicked();
    UFUNCTION() void HandleTrackClicked();

    void BindSourceTree();
    void BindSourceEvents();
    void ApplyPresentation();
    void PlaySourceAnimation(FName AnimationName);

    UPROPERTY(Transient) TObjectPtr<class UButton> SourceChallengeEntryButton;
    UPROPERTY(Transient) TObjectPtr<class UButton> SourceTrackButton;
    UPROPERTY(Transient) TObjectPtr<class UImage> SourceChallengeIcon;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceChallengeCompletionStatus;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceChallengeTitle;
    UPROPERTY(Transient) TObjectPtr<class UTextBlock> SourceTrackButtonText;
    UPROPERTY(Transient) TObjectPtr<class UTexture2D> SelectedChallengeIcon;
    UPROPERTY(Transient) TArray<FRecoveredReward> Rewards;
    FText ChallengeTitle;
};
