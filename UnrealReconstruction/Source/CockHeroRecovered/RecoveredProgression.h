#pragma once
#include "CoreMinimal.h"
#include "RecoveredGameplay.h"
#include "Engine/DataTable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredProgression.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredModifierRow : public FTableRowBase {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FText ModifierTitle;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FText ModifierDescription;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) TObjectPtr<class UTexture2D> ModifierIcon;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredReward {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString RewardType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 Value = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString ItemIdentifier;
};

// Mirrors native FXPSourceData.  The post-game XP screen presents these in
// order before moving on to the level-up and unlock-point stages.
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredXPSourceData {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText Label;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 XPAmount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText DetailText;
};

// Mirrors native FUPSourceData.  Level-up points are already committed by
// progression; the remaining sources are committed as the post-game flow
// presents them, matching the original screen sequence.
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredUPSourceData {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText Label;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 UPAmount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText DetailText;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") bool bFromLevelUp = false;
};

// Mirrors native FLevelUpEventData.  Native evidence establishes the exact
// fields consumed by WBP_XPScreen and WBP_LevelUpScreen.
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredLevelUpEventData {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 NewLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FName Title;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 UPReward = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 XPThresholdCrossed = 100;
};

// Mirrors native FSessionRewardData: the bundle PrepareSessionRewards builds.
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredSessionRewardData {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 StartingXP = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 StartingLevel = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 XPToNextLevel = 100;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredXPSourceData> XPSources;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 TotalXPEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredUPSourceData> UPSources;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 StartingUP = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 TotalUPEarned = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredLevelUpEventData> LevelUpEvents;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FRecoveredSessionStats SessionStats;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") bool bWon = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 EndingXP = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 EndingLevel = 1;
    // Retained for existing recovered callers that render the compact reward
    // summary instead of the staged post-game flow.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 XPGranted = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredReward> Rewards;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredXPSettings {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float XPPerMinute=10.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float XPPerStroke=0.18f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float XPPerEdge=15.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float WinBonus=60.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 StrokeXPCap=360;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 EnemyXPCap=60;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredProgressionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static int32 CalculateSessionXP(const FRecoveredSessionStats& Stats, const FRecoveredXPSettings& Settings);
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static int32 GetXPForNextLevel(int32 CurrentLevel);
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static float CalculateLevelProgress(int32 CurrentXP,int32 CurrentLevel);
    // Native text builders confirmed by Ghidra analysis (UProgressionManager::GetLifetimeStatsText
    // at 0x1481c0730, GetRewardsText at 0x1481c26e0 taking FSessionRewardData,
    // GetStatValueText at 0x1481c2b60 taking an enum metric).
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static FText GetLifetimeStatsText(const FRecoveredLifetimeStats& Stats);
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static FText GetRewardsText(const FRecoveredSessionRewardData& RewardData);
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static FText GetStatValueText(ERecoveredMetric Metric, const FRecoveredSessionStats& SessionStats, const FRecoveredLifetimeStats& LifetimeStats, bool bUseLifetime);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredXPGained,int32,Amount,const FString&,Source);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRecoveredLevelUp,int32,Level,int32,UnlockPoints,const TArray<FString>&,ContentUnlocks);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredContentUnlocked,FName,ContentID,const FString&,ContentName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredProgressUpdated,float,Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredProgressionSaveRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredPackRewardRequest,const FString&,PackID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredStorePointsRequest,int32,Amount);

/** Native XP/level state. Challenge execution and persistence are separate unfinished consumers. */
UCLASS(BlueprintType,Blueprintable)
class COCKHERORECOVERED_API URecoveredProgressionManager : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") int32 CurrentXP=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") int32 CurrentLevel=1;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") int32 TotalXPEarned=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") int32 UnlockPoints=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TObjectPtr<class UDataTable> LevelDataTable;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TObjectPtr<class UDataTable> PlayerCardDataTable;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TSet<FName> UnlockedPlayerCards;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TObjectPtr<class UDataTable> ModifierDataTable;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TObjectPtr<class UDataTable> ChallengeDataTable;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TSet<FName> UnlockedModifiers;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TSet<FName> EnabledModifiers;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredProgressionSaveRequest OnSaveRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredPackRewardRequest OnPackRewardRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredStorePointsRequest OnStorePointsRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredXPGained OnXPGained;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredLevelUp OnLevelUp;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredContentUnlocked OnContentUnlocked;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredProgressUpdated OnProgressUpdate;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredMetricUpdateRequested OnMetricUpdateRequested;
    UFUNCTION(BlueprintCallable,Category="Recovered") void AddXP(int32 Amount,const FString& Source);
    UFUNCTION(BlueprintCallable,Category="Recovered") void AddUnlockPoints(int32 Amount);
    UFUNCTION(BlueprintCallable,Category="Recovered") void CheckLevelUp();
    UFUNCTION(BlueprintCallable,Category="Recovered") bool UnlockPlayerCard(FName CardID);
    UFUNCTION(BlueprintCallable,Category="Recovered") bool UnlockModifier(FName ModifierID);
    // Native modifier data interface confirmed by Ghidra (UProgressionManager::GetAllModifierData,
    // GetModifierData, CanEnableModifier, IsModifierUnlocked, GetUnlockedModifiers,
    // GetAllConflictsForModifier, GetConflictingModifiers, GetChallengeForModifier).
    UFUNCTION(BlueprintPure,Category="Recovered") TArray<FRecoveredModifierRow> GetAllModifierData() const;
    UFUNCTION(BlueprintPure,Category="Recovered") bool GetModifierData(FName ModifierID, FRecoveredModifierRow& OutData) const;
    UFUNCTION(BlueprintPure,Category="Recovered") bool CanEnableModifier(FName ModifierID) const;
    UFUNCTION(BlueprintPure,Category="Recovered") bool IsModifierUnlocked(FName ModifierID) const;
    UFUNCTION(BlueprintPure,Category="Recovered") TArray<FName> GetUnlockedModifiers() const;
    UFUNCTION(BlueprintPure,Category="Recovered") TArray<FName> GetAllConflictsForModifier(FName ModifierID) const;
    UFUNCTION(BlueprintPure,Category="Recovered") TArray<FName> GetConflictingModifiers(FName ModifierID) const;
    UFUNCTION(BlueprintPure,Category="Recovered") FName GetChallengeForModifier(FName ModifierID) const;
    FName GetCanonicalModifierID(FName ModifierID) const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") FString ExportRecoveryState() const;
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool ImportRecoveryState(const FString& Json);
};
