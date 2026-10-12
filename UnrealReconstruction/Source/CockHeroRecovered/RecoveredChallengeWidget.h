#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredProgression.h"
#include "RecoveredChallengeWidget.generated.h"

class URecoveredChallengeEntryWidget;
class UUserWidget;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredChallengeWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Challenges") TObjectPtr<class URecoveredGameInstance> RecoveredInstanceOverride;
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Challenges") TArray<TObjectPtr<URecoveredChallengeEntryWidget>> RecoveredChallengeEntries;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Challenges") FName SelectedChallengeID;

    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void SetRecoveredChallengeGameInstance(class URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintPure,Category="Recovered Challenges") class URecoveredGameInstance* GetRecoveredChallengeGameInstance() const;
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void RefreshChallengeList();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void SetChallengeTracked(FName ChallengeID,bool bTracked);
    UFUNCTION(BlueprintPure,Category="Recovered Challenges") bool IsChallengeTracked(FName ChallengeID) const;
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") bool ClaimChallengeRewards(FName ChallengeID);
    UFUNCTION(BlueprintPure,Category="Recovered Challenges") TArray<FName> GetTrackedChallenges() const;
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void SelectChallenge(FName ChallengeID);
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void RunChallengeAction(FName ChallengeID);
    UFUNCTION(BlueprintPure,Category="Recovered Challenges") int32 GetChallengeEntryCount() const;
    UFUNCTION(BlueprintPure,Category="Recovered Challenges") UUserWidget* GetActiveRewardOverlay() const;

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    void RefreshDetailsPanel();
    TArray<FRecoveredReward> ClaimChallengeRewardsInternal(FName ChallengeID);
    void ShowClaimRewardOverlay(const TArray<FRecoveredReward>& Rewards);
    UFUNCTION() void HandleChallengeEntrySelected(FName ChallengeID);
    UFUNCTION() void HandleChallengeEntryTrackAction(FName ChallengeID,URecoveredChallengeEntryWidget* Entry);
    UFUNCTION() void HandleInteractionClicked();
    UFUNCTION() void HandleRewardOverlayClose();
    UFUNCTION() void OnChallengeProgressNotification(FName ChallengeID);

    UPROPERTY(Transient) TObjectPtr<UUserWidget> ActiveRewardOverlay;
};