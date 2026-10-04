#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredChallengeWidget.generated.h"

// Challenge list UI: populates from the tracker, supports tracking selection,
// progress display, and reward claims.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredChallengeWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") void RefreshChallengeList();
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") void SetChallengeTracked(FName ChallengeID, bool bTracked);
    UFUNCTION(BlueprintPure, Category="Recovered Challenges") bool IsChallengeTracked(FName ChallengeID) const;
    UFUNCTION(BlueprintCallable, Category="Recovered Challenges") bool ClaimChallengeRewards(FName ChallengeID);
    UFUNCTION(BlueprintPure, Category="Recovered Challenges") TArray<FName> GetTrackedChallenges() const;
protected:
    virtual void NativeConstruct() override;
    UPROPERTY() TSet<FName> TrackedChallenges;
    UFUNCTION() void OnChallengeProgressNotification(FName ChallengeID);
};
