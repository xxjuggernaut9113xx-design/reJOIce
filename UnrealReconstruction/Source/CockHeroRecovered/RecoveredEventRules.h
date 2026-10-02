#pragma once
#include "CoreMinimal.h"
#include "RecoveredRules.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredEventRules.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredEligibilityState {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 HeatCategory = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Combo = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Coins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bCanSuccubiSpawn = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bBrainMelterEnabled = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bStoreOnCooldown = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 Shields = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bShieldToggled = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> Modifiers;
    UPROPERTY(BlueprintReadOnly) int32 ShieldsConsumed = 0;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredEventRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    // Rule sets: F,D,C,B,A,S combo weights, then slow, medium, fast heat weights.
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static FRecoveredEventRecord AdjustEventWeight(const FRecoveredEventRecord& Event, uint8 RuleSet);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static int32 ChooseEventAtRoll(const TArray<FRecoveredEventRecord>& Events, double Roll);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static double GetTotalWeight(const TArray<FRecoveredEventRecord>& Events);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static uint8 RefreshHeatCategory(double Heat, uint8 Previous);
    UFUNCTION(BlueprintCallable, Category="Recovered|Events") static bool CheckSuccubusEligibility(UPARAM(ref) FRecoveredEligibilityState& State);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static bool CheckStoreEligibility(const FRecoveredEligibilityState& State);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static bool CheckBodyFrenzyEligibility(const FRecoveredEligibilityState& State);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static FName DetermineDispatchedEvent(uint8 Event, bool bSuccufrenzyActive, bool bSlowAndSteadyActive, bool bDoubleTimeActive, int32 RandomRoll, bool& bClearIdleTimer);
    UFUNCTION(BlueprintCallable, Category="Recovered|Events") static TArray<FRecoveredEventRecord> BuildEligibleEvents(const TArray<FRecoveredEventRecord>& Events, UPARAM(ref) FRecoveredEligibilityState& State);
    UFUNCTION(BlueprintPure, Category="Recovered|Events") static TArray<FRecoveredEventRecord> ApplyDrawEventWeights(const TArray<FRecoveredEventRecord>& EligibleEvents,uint8 HeatCategory,uint8 ComboTier);
};
