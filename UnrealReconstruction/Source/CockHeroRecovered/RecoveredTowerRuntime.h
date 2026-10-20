#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoveredPlaylistRuntime.h"
#include "RecoveredTowerRewards.h"
#include "RecoveredTowerRuntime.generated.h"

UENUM(BlueprintType)
enum class ERecoveredRoundPhase : uint8 { Inactive, SessionSetup, RoundSelection, Playing, RoundComplete, Shop, BossRound, SessionComplete };

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredTowerOption {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Tower") FName PackName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Tower") uint8 Objective = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Tower") TArray<FName> Modifiers;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Tower") int32 DifficultyTier = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Tower") float ObjectiveParam = 100;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") uint8 DraftLane = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") int32 RewardCoins = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") int32 RewardSuccuCoins = 0;
    TArray<FRecoveredTowerReward> NativeRewards;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredTowerOptionDelegate, const FRecoveredTowerOption&, Option);

// Native lifecycle, calibration tiers, pressure and draft distribution are
// recovered from native-round-runtime/native-round-adaptive and ctor evidence.
UCLASS(ClassGroup=(Recovered), meta=(BlueprintSpawnableComponent))
class COCKHERORECOVERED_API URecoveredTowerRuntime : public UActorComponent {
    GENERATED_BODY()
public:
    int32 BaselineStrokes = 0, BaselineEdges = 0, BaselineDuration = 0, BaselineSuccubi = 0, BaselineMilking = 0, BaselineCoins = 0;
    bool LoadSourceCatalog(FString& Error);
    FRecoveredSessionStats BaselineStats;
    TArray<FRecoveredSessionStats> RoundHistory;
    TArray<uint8> RecentObjectives;
    float GetDifficultyProgress(int32 Round) const;
    float CalculateAdaptivePressure() const;
    int32 RollAdaptiveTier();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") ERecoveredRoundPhase Phase = ERecoveredRoundPhase::Inactive;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") int32 CurrentRound = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") int32 CompletedRounds = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") int32 FailedRounds = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") int32 TotalRounds = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") bool bEndlessMode = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") bool bLastRoundSucceeded = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") TArray<FRecoveredTowerOption> CurrentOptions;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Tower") FRecoveredTowerOption SelectedOption;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Tower") FRecoveredTowerOptionDelegate OnRoundStarted;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Tower") FRecoveredPlaylistProgressDelegate OnRoundCompleted;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Tower") FRecoveredPlaylistProgressDelegate OnSessionComplete;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Tower") FRecoveredSequenceDelegate OnShopOpened;
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") bool StartSession(int32 Rounds, bool Endless, int32 ShopEvery, const TArray<FRecoveredTowerOption>& Pool, int32 Seed, FString& Error);
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") bool GenerateOptions();
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") bool SelectOption(int32 Index);
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") bool CompleteRound(bool Success);
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") bool ContinueAfterRound();
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") bool LeaveShop();
    UFUNCTION(BlueprintCallable, Category="Recovered|Tower") void StopSession();
private:
    TArray<FRecoveredTowerOption> OptionPool;
    FRandomStream Random;
    int32 ShopInterval = 0;
    TSharedPtr<class FJsonObject> SourceCatalog;
};
