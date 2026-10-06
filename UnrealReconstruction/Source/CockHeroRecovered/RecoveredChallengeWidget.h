#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredChallengeWidget.generated.h"

class URecoveredChallengeWidget;

/** Dynamic UMG buttons do not carry their row identity; this forwards it safely. */
UCLASS()
class COCKHERORECOVERED_API URecoveredChallengeActionForward : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredChallengeWidget> Owner;
    UPROPERTY() FName ChallengeID;
    UPROPERTY() bool bPrimaryAction = false;
    UFUNCTION() void Execute();
};

// Challenge list UI: populates the recovered ChallengesVerticalBox, supports
// selection, tracking, progress display, and one-time reward claims.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredChallengeWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") void RefreshChallengeList();
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") void SetChallengeTracked(FName ChallengeID, bool bTracked);
    UFUNCTION(BlueprintPure, Category="Recovered Challenges") bool IsChallengeTracked(FName ChallengeID) const;
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") bool ClaimChallengeRewards(FName ChallengeID);
    UFUNCTION(BlueprintPure, Category="Recovered Challenges") TArray<FName> GetTrackedChallenges() const;
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") void SelectChallenge(FName ChallengeID);
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") void RunChallengeAction(FName ChallengeID);
protected:
    virtual void NativeConstruct() override;
    void RefreshDetailsPanel();
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredChallengeActionForward>> ActionForwarders;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Challenges") FName SelectedChallengeID;
    UFUNCTION() void HandleInteractionClicked();
    UFUNCTION() void OnChallengeProgressNotification(FName ChallengeID);
};
