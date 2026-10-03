#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredGameplay.generated.h"

UENUM(BlueprintType)
enum class ERecoveredMetric : uint8 {
    Strokes = 0,
    Edges = 1,
    SuccubiDefeated = 2,
    EnemiesDefeated = 3,
    MaxCombo = 4,
    StrokeCombo = 5,
    MissedCumWindows = 6,
    TimesTaunted = 7,
    ItemsUsed = 8,
    AvgStrokesPerEdge = 9,
    DrawsAtMaxHeat = 10,
    EarlyClimax = 11,
    SessionDuration = 12,
    SessionsCompleted = 13,
    SessionsWon = 14,
    TotalXPEarned = 15,
    MoneySpent = 16,
    EdgeStreak = 17,
    ConsecutiveSuccubiSurvived = 18,
    CumWindowsHit = 19,
    PerfectRounds = 20,
    TimesLost = 21,
    LostToSuccubus = 22,
    TimeAtHighHeat = 23,
    PercentAtHighHeat = 24,
    GamesWithSexToy = 25,
    PerfectEdges = 26,
    BonerPillsUsed = 27,
    AcceptedTemptation = 28,
    CameDuringTaunt = 29,
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPlayerVariables {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TotalStrokeCount")) int32 TotalStrokeCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TotalDrawCount")) int32 TotalDrawCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="DrawsLast5Sec")) int32 DrawsLast5Sec = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="SessionLength")) int32 SessionLength = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TotalEdgeCount")) int32 TotalEdgeCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="EdgeStreak")) int32 EdgeStreak = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="LastEdgeTime")) double LastEdgeTime = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TimeSinceLastEdge")) double TimeSinceLastEdge = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="AvgStrokesPerEdge")) int32 AvgStrokesPerEdge = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="AvgTimePerEdge")) double AvgTimePerEdge = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="UsedDefensiveItemsInLast2Minutes")) int32 UsedDefensiveItemsInLast2Minutes = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TotalDefenseItemUses")) int32 TotalDefenseItemUses = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="LastDefensiveItemUsageTime")) double LastDefensiveItemUsageTime = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TimeSinceLastDefensiveItem")) double TimeSinceLastDefensiveItem = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="ConsecutiveHighHeatDraws")) int32 ConsecutiveHighHeatDraws = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="TotalTauntsUsed")) int32 TotalTauntsUsed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="BeatSpawnInterval")) double BeatSpawnInterval = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CurrentStrokeCount")) int32 CurrentStrokeCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CurrentComboCount")) int32 CurrentComboCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="PlayerCoins")) int32 PlayerCoins = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="EdgeRecoveryLength")) double EdgeRecoveryLength = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="HasEdged?")) bool bHasEdged = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="IsAllowedToCum?")) bool bIsAllowedToCum = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CanUseItems?")) bool bCanUseItems = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="AssignedStrokeCount")) int32 AssignedStrokeCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="HasUsedDefensiveItems")) bool bHasUsedDefensiveItems = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="HasItems?")) bool bHasItems = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="DidPlayerSurviveTaunt?")) bool bDidPlayerSurviveTaunt = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="IsPlayerEdgeable?")) bool bIsPlayerEdgeable = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CurrentStrokeCountForNextEdge")) int32 CurrentStrokeCountForNextEdge = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="SessionDrawsAtMaxHeat")) int32 SessionDrawsAtMaxHeat = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="HasCame?")) bool bHasCame = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="MissedCumWindows")) int32 MissedCumWindows = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="BrokenComboArray")) TArray<int32> BrokenComboArray;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="PerPdgeStrokeCountArray")) TArray<int32> PerPdgeStrokeCountArray;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CumMeterMultiplier")) double CumMeterMultiplier = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CoinEarnMultiplier")) double CoinEarnMultiplier = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CanSuccubiSpawn?")) bool bCanSuccubiSpawn = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="CanDraw?")) bool bCanDraw = false;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredSessionStats {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 Strokes = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 Edges = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 SuccubiDefeated = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 EnemiesDefeated = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 MaxCombo = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 MissedCumWindows = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 TimesTaunted = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 ItemsUsed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 DrawsAtMaxHeat = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 EarlyClimax = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 SessionDuration = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bWon = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bLostToSuccubus = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 SessionsWon = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 SessionsCompleted = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 TimesLostToSuccubus = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") TArray<FString> ActiveModifiers;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 EdgeStreak = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 ConsecutiveSuccubiSurvived = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 TimeAtHighHeat = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 PercentTimeAtHighHeat = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 CumWindowsHit = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 MoneySpent = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 GamesWithSexToy = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 PerfectEdges = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 BonerPillsUsed = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 AcceptedTemptation = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 CameDuringTaunt = 0;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredLifetimeStats {
    GENERATED_BODY()
    // Accumulated across all finalized sessions.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalSessionsCompleted = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalSessionsWon = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalStrokes = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalEdges = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalSuccubiDefeated = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalEnemiesDefeated = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalXPEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 TotalCoinsEarned = 0;
    // Peak values: kept as the maximum ever observed, mirroring the native
    // RecordSessionMetric lifetime-best behavior.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 BestCombo = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 BestEdgeStreak = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 LongestSessionSeconds = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Lifetime") int32 MostStrokesInSession = 0;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredDeviceState {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bLovense = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bHandy = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bButtplugVibrators = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bButtplugStrokers = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bFullStrokePerBeat = false;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPitchPair {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pitch") double BeatPitch = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pitch") double MoanPitch = 0;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredStateRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Preferences") static double GetPreferenceMultiplier(uint8 Index, double Previous);
    UFUNCTION(BlueprintPure, Category="Recovered|Combo") static uint8 DetermineComboTier(int32 ComboCount, uint8 PreviousTier);
    UFUNCTION(BlueprintPure, Category="Recovered|Timing") static double GetMinimumBeatInterval(uint8 Difficulty, const FRecoveredDeviceState& Devices, double Previous);
    UFUNCTION(BlueprintPure, Category="Recovered|Audio") static FRecoveredPitchPair CalculateBeatPitch(int32 TotalBeats, int32 RemainingBeats);
    UFUNCTION(BlueprintCallable, Category="Recovered|Resources") static int32 AddCoinsToState(UPARAM(ref) FRecoveredPlayerVariables& Player, int32 Coins);
    UFUNCTION(BlueprintPure, Category="Recovered|Resources") static double AddToCumMeter(double Current, double Amount);
    UFUNCTION(BlueprintPure, Category="Recovered|Resources") static double AddToLootBar(double Current, double Amount, double Multiplier);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void RecordSessionMetric(UPARAM(ref) FRecoveredSessionStats& Stats, ERecoveredMetric Metric, int32 Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void SetSessionMetric(UPARAM(ref) FRecoveredSessionStats& Stats, ERecoveredMetric Metric, int32 Value);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void SetMaximumCombo(UPARAM(ref) FRecoveredSessionStats& Stats, int32 Combo);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void AdvanceSessionDuration(UPARAM(ref) FRecoveredPlayerVariables& Player, UPARAM(ref) FRecoveredSessionStats& Stats, double Heat);
    UFUNCTION(BlueprintPure, Category="Recovered|Arithmetic") static int32 AddInt32Wrapping(int32 A, int32 B);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredMetricUpdateRequested, ERecoveredMetric, Metric, int32, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredCoinsAdded, int32, Earned, int32, Total);
