#pragma once
#include "CoreMinimal.h"
#include "RecoveredRules.h"
#include "RecoveredChallengeTracker.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredChallengeProgress {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere,BlueprintReadWrite) TArray<FRecoveredRequirement> Requirements;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) TArray<int32> BestValues;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) bool bCompleted=false;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) bool bRewardsClaimed=false;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float CompletionTime=0;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredChallengeNotification,FName,ChallengeID);

/** Native challenge map adapter; session metric routing and save integration are separate. */
UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredChallengeTracker : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite) TObjectPtr<UDataTable> ChallengeTable;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) TObjectPtr<URecoveredProgressionManager> RewardManager;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) TMap<FName,FRecoveredChallengeProgress> SessionProgress;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) TMap<FName,FRecoveredChallengeProgress> LifetimeProgress;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) TSet<FName> CompletedChallenges;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) TArray<FName> TrackedChallenges;
    UPROPERTY(BlueprintAssignable) FRecoveredChallengeNotification OnChallengeCompleted;
    UPROPERTY(BlueprintAssignable) FRecoveredChallengeNotification OnChallengeProgress;
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") bool InitializeChallenges();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void UpdateChallengeProgress(FName ChallengeID,ERecoveredMetric Metric,int32 Amount,const FRecoveredSessionStats& Stats,int32 ElapsedSeconds,float WorldSeconds);
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") bool CompleteChallenge(FName ChallengeID,float WorldSeconds);
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") TArray<FRecoveredReward> ClaimChallengeRewards(FName ChallengeID);
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void StartNewSession();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void UpdateMetricWithConditions(ERecoveredMetric Metric,int32 Amount,const FRecoveredSessionStats& Stats,const TArray<FString>& ActiveModifiers,int32 ElapsedSeconds,float WorldSeconds);
    UFUNCTION(BlueprintPure,Category="Recovered Save") FString ExportRecoveryState() const;
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool ImportRecoveryState(const FString& Json);
private:
    const FRecoveredChallengeRow* FindDefinition(FName ChallengeID) const;
};
USTRUCT()
struct FRecoveredChallengeSaveState {
    GENERATED_BODY()
    UPROPERTY() int32 Version=1;
    UPROPERTY() TMap<FName,FRecoveredChallengeProgress> SessionProgress;
    UPROPERTY() TMap<FName,FRecoveredChallengeProgress> LifetimeProgress;
    UPROPERTY() TSet<FName> CompletedChallenges;
    UPROPERTY() TArray<FName> TrackedChallenges;
};
