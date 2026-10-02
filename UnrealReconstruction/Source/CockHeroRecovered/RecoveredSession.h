#pragma once
#include "CoreMinimal.h"
#include "RecoveredGameplay.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredSession.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatPattern {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString PatternName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<double> IntervalMultipliers;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FString> Tags;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString Notes;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatContext {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") uint8 CardType = 9;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") uint8 HeatCategory = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double HighHeatAdd = 0.25;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double MediumHeatAdd = 0.15;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double SlowHeatAdd = 0.2;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FString> ActiveModifiers;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredSessionRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Session") static int32 GetCoinAward(uint8 CardType);
    UFUNCTION(BlueprintPure, Category="Recovered|Session") static double GetHeatAward(const FRecoveredBeatContext& Context);
    UFUNCTION(BlueprintPure, Category="Recovered|Session") static double GetLootIncrement(uint8 CardType, bool bMoneyModifier);
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") static void AddBeatMeter(UPARAM(ref) FRecoveredPlayerVariables& Player, const FRecoveredBeatContext& Context, double Heat, UPARAM(ref) double& BaseGain, UPARAM(ref) double& Meter);
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") static void BreakCombo(UPARAM(ref) FRecoveredPlayerVariables& Player);
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") static void DetermineDrawMultipliers(uint8 ComboTier, double DifficultyCount, double DifficultySpeed, UPARAM(ref) double& StrokeCountMultiplier, UPARAM(ref) double& StrokeTimeMultiplier);
    UFUNCTION(BlueprintPure, Category="Recovered|Session") static FRecoveredBeatPattern CheckIntervalMultipliers(const FRecoveredBeatPattern& Pattern, float CurrentInterval);
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") static int32 UpdateRecentDrawCount(UPARAM(ref) TArray<int32>& Timestamps, int32 SessionLength);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredSessionAction, FName, Action);
