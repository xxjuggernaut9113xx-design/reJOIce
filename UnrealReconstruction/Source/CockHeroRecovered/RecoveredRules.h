#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredGameplay.h"
#include "RecoveredDeviceInterface.h"
#include "RecoveredSession.h"
#include "RecoveredBeatTimeline.h"
#include "RecoveredCalibration.h"
#include "RecoveredDecks.h"
#include "RecoveredMediaPlayback.h"
#include "RecoveredProgression.h"
#include "RecoveredOutcomes.h"
#include "RecoveredRules.generated.h"

UENUM(BlueprintType)
enum class ERecoveredDifficulty : uint8 { EasyMode = 0, NormalMode = 1, InsaneMode = 2 };
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredHeatCategoryRow : public FTableRowBase {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MinStrokeCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 MaxStrokeCount = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double MinIntervalSeconds = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) double MaxIntervalSeconds = 0;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredDifficultyConfig {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double DifficultyHeatGainMultiplier = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double DifficultyCoinEarnMultiplier = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double DifficultyStrokeCounterMultiplier = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double DifficultyStrokeSpeedMultiplier = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double CumMeterMultiplier = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double CumIncreaseItemSpawnChance = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double DecreaseHeatItemSpawnChance = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double EdgeItemSpawnChance = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double BreakItemSpawnChance = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double SlowdownItemSpawnChance = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double BonerPillSpawnChance = 0.0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double SuccuShieldSpawnChance = 0.0;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredEventRecord {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 EventName = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double BaseWeight = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double WeightMultiplier = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") bool IsEligible = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double CooldownDuration = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") bool IsOnCooldown = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText EventDescription;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredEventEntry {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString Event;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 EntryOffset = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 EntryStatement = 0;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredRequirement {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString MetricType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 TargetValue = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString ComparisonType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 CurrentValue = 0;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredCondition {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString ConditionType;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString ConditionValue;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredChallengeRow : public FTableRowBase {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString ChallengeID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText DisplayName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText Description;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString Icon;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FLinearColor IconTint = FLinearColor::White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredRequirement> Requirements;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString Scope;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredCondition> Conditions;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FRecoveredReward> Rewards;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 XPReward = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 UnlockPointsReward = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") bool bHidden = false;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredLevelRow : public FTableRowBase {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 Level = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 XPRequired = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 UnlockPointsReward = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TArray<FString> ContentUnlocks;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText TitleUnlock;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString LevelIcon;
};
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPlayerCardRow : public FTableRowBase {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString CardID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FText CardName;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString CardImage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FString RequiredChallengeID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") int32 RequiredLevel = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") FLinearColor CardColor = FLinearColor::White;
};

UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredDefinitionAsset : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered") FString SourceClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered", meta=(MultiLine="true")) FString SerializedDefaultsJson;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered", meta=(MultiLine="true")) FString DeclaredPropertiesJson;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered") TMap<FString, FString> DecodedFunctionBodies;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evidence") bool bFullGameplayParityVerified = false;
};

UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredRulesAsset : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered") TArray<FRecoveredDifficultyConfig> DifficultyProfiles;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> BeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> SlowBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> MediumBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> FastBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> CumBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> SuccubusBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> FrenzyBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> EdgingBeatPatterns;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events") TArray<FRecoveredEventRecord> EventRecords;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events") TArray<FRecoveredEventEntry> EventEntries;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Evidence", meta=(MultiLine="true")) FString BlueprintEnumsJson;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evidence") FString SourceGameSHA256 = TEXT("c645757d1112491952b67bf29502b4721133ba6940a9cfb08358f0dde127560f");
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evidence") bool bFullGameplayParityVerified = false;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Difficulty") static FRecoveredDifficultyConfig GetDifficultyConfig(ERecoveredDifficulty Difficulty);
    UFUNCTION(BlueprintPure, Category="Recovered|Heat") static double CalculateHeat(double Heat, double HeatAdd, double HeatGainMultiplier);
    UFUNCTION(BlueprintPure, Category="Recovered|Draw") static bool EvaluateChance(double Roll, double Chance);
    UFUNCTION(BlueprintPure, Category="Recovered|Timing") static float ClampBeatInterval(float Interval);
    UFUNCTION(BlueprintPure, Category="Recovered|Timing") static float ClampSpeedItemMultiplier(float Multiplier);
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetChallengeRowStruct();
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetModifierRowStruct();
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetLevelRowStruct();
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetPlayerCardRowStruct();
    UFUNCTION(BlueprintPure, Category="Recovered|Session") static UScriptStruct* GetHeatCategoryRowStruct();
    UFUNCTION(BlueprintCallable, Category="Recovered|Progression") static FString ExportTableJson(UDataTable* Table);
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API ARecoveredManager : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API ARecoveredGlobalManager : public AGameModeBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredRulesAsset> Rules;
    ARecoveredGlobalManager();
    virtual void BeginPlay() override;
    UFUNCTION(BlueprintCallable, Category="Recovered Save") void ReloadRecoveredProfile();
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered Menu") TObjectPtr<class UUserWidget> MainMenu;
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered Menu") FString StartupError;
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") bool CreateMainMenuUI();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") bool ReturnToMainMenu();
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered Session") TObjectPtr<class UUserWidget> SessionScreen;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Media") FString MediaManifestPath=TEXT("C:/Users/webma/Downloads/Cock_Hero_Shipping_Build_V0.04_-_Exclusive/PrepV2/Windows/Extracted/Base_Game_CG/manifest.json");
    UFUNCTION(BlueprintCallable, Category="Recovered Session") bool InitializeRecoveredSession();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") ERecoveredDifficulty CurrentDifficulty = ERecoveredDifficulty::NormalMode;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double HeatLevel = 10.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") FRecoveredDifficultyConfig ActiveDifficulty;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") FRecoveredPlayerVariables PlayerVariables;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") FRecoveredSessionStats SessionStats;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") FRecoveredLifetimeStats LifetimeStats;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") double CumMeterPercentage = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") double LootBarPercentage = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") double LootBarMultiplier = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") int32 EdgeBank = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") int32 PointsSpent = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") double EdgePacingMultiplier = 0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered State") double EdgeStrokeMultiplier=1.1;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered State") double LastEdgeInterval=1.0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered State") int32 LastEdgeStrokeCount=25;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered State") bool bPlayerEdgedLastDraw=false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") double UserStrokeCountMultiplier = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") uint8 CurrentComboTypeEnum = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") double MinimumBeatInterval = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered State") FRecoveredPitchPair CurrentPitch;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") FRecoveredBeatContext BeatContext;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") double BaseMeterGain = 0.00025;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bLootBarEnabled = false;
    UPROPERTY(BlueprintAssignable, Category="Recovered Events") FRecoveredSessionAction OnSessionAction;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Session") TObjectPtr<URecoveredBeatTimeline> BeatTimeline;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool IsAutoDrawEnabled = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bStopSequence = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bCanUseSlowdown = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bCanUseBonerPill = true;
    // Selected beat sound bank and voice pack IDs.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Audio") FName BeatSoundBank = TEXT("Default");
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Audio") FName VoicePack = TEXT("Default");
    // Media pack states: pack ID -> enabled; pack ID -> priority (lower draws first).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Media") TMap<FString, bool> MediaPackEnabled;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Media") TMap<FString, int32> MediaPackPriority;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Media") bool bVideoLoopEnabled = true;
    // Pending notification queue.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Notifications") TArray<FString> PendingNotifications;
    // Owned consumable inventory: item ID -> count. Purchases add to inventory;
    // use is a separate step from acquisition.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Inventory") TMap<FName, int32> OwnedItemCounts;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") int32 ConsecutiveSuccubiSurvived = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") TObjectPtr<UDataTable> HeatCategoryDataTable;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Media") TObjectPtr<URecoveredDeckState> MediaDeckState;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Media") TObjectPtr<URecoveredMediaPlayback> MediaPlayback;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Media") FRecoveredMediaEntry SelectedRandomCard;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") double StrokeCountMultiplier = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") double StrokeTimeMultiplier = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") double BeatTravelTime = 1.75;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Session") FString LastSessionError;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") bool bHasTaunted = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Session") TArray<int32> RecentDrawTimestamps;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Session") int32 SessionDrawsAtMaxHeat = 0;
    UPROPERTY(BlueprintAssignable, Category="Recovered Events") FRecoveredCoinsAdded OnCoinsAdded;
    UPROPERTY(BlueprintAssignable, Category="Recovered Events") FRecoveredCoinsAdded OnEdgeBankAdded;
    // Challenge evaluation and original widget/audio consumers remain to be reconstructed.
    UPROPERTY(BlueprintAssignable, Category="Recovered Events") FRecoveredMetricUpdateRequested OnMetricUpdateRequested;
    UFUNCTION(BlueprintCallable, Category="Recovered") void ApplyDifficulty(ERecoveredDifficulty Difficulty);
    UFUNCTION(BlueprintCallable, Category="Recovered") void InitializeDifficultyVariables(uint8 SavedEdgePacingIndex, uint8 SavedStrokeMultiplierIndex);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddHeat(double HeatAdd);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddCoins(int32 Coins);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddToCumMeter(double Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddToLootBar(double Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddToEdgeBank(int32 Coins);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddToPointsSpent(int32 Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered") void DetermineComboType();
    UFUNCTION(BlueprintCallable, Category="Recovered") void UpdateMinimumBeatInterval(const FRecoveredDeviceState& Devices);
    UFUNCTION(BlueprintCallable, Category="Recovered") void CalculateBeatPitch(int32 TotalBeats, int32 RemainingBeats);
    UFUNCTION(BlueprintCallable, Category="Recovered") void UpdateBeatCompleteMetrics();
    UFUNCTION(BlueprintCallable, Category="Recovered") void SetSessionDuration();
    UFUNCTION(BlueprintCallable, Category="Recovered") void BeatComplete();
    UFUNCTION(BlueprintCallable, Category="Recovered") void BreakCombo();
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddBeatLootReward();
    UFUNCTION(BlueprintCallable, Category="Recovered") void CompleteBeatSequence();
    UFUNCTION(BlueprintCallable, Category="Recovered") bool StartRecoveredBeatSequence(const FRecoveredBeatPattern& Pattern, double BaseInterval, int32 StrokeCount, float SpeedModifier, double TravelTime);
    UFUNCTION() void PresentRecoveredBeat(const FRecoveredBeatEvent& Event);
    UFUNCTION() void HandleBeatHitCenter(const FRecoveredBeatEvent& Event);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") bool LoadMediaPack(const FString& ManifestPath, const TArray<FString>& ExcludedTags);
    // Media pack management: enable/disable packs and control their draw priority.
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetMediaPackEnabled(const FString& PackID, bool bEnabled);
    UFUNCTION(BlueprintPure, Category="Recovered|Media") bool IsMediaPackEnabled(const FString& PackID) const;
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetMediaPackPriority(const FString& PackID, int32 Priority);
    UFUNCTION(BlueprintPure, Category="Recovered|Media") TArray<FString> GetEnabledMediaPacks() const;
    // Direct pace entry point; full DetermineCardV2 dispatch and UI state machine remain separate.
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") bool DrawPaceCard(uint8 Pace, bool bPlayMedia = true);
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") bool PrepareDrawState();
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Events") bool bBrainMelterEnabled=false;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Events") bool bStoreOnCooldown=false;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Events") int32 SuccubusShields=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Events") bool bShieldToggled=false;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Events") FName LastDispatchedEvent;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Events") FRecoveredEventRecord FoundEvent;
    UFUNCTION(BlueprintCallable,Category="Recovered Events") bool RequestNextRecoveredCard(bool bPlayMedia=true);
    UFUNCTION() void HandleRecoveredSessionAction(FName Action);
    // Beat-presentation notification handlers (audit section 4).
    UFUNCTION() void PlayMainImageBeatComplete();
    UFUNCTION() void PlayComboTypeBeatComplete();
    UFUNCTION() void PlayHeatGainBeatComplete();
    UFUNCTION() void PlayBeatCompleteSFX();
    UFUNCTION() void TriggerClothesBreaker();
    UFUNCTION() void TriggerBrainMelter();
    UFUNCTION() void SpawnTaskModifier();
    UFUNCTION() void TriggerMeterOverride();
    UFUNCTION() void ClearNotificationBoxes();
    UFUNCTION() void RemoveAllActiveBeatWidgets();
    UFUNCTION() void SpawnOnomatopoeia();
    UFUNCTION() void PlayDrawButtonAnimation();
    UFUNCTION() void CreateLootRewardWidget();
    UFUNCTION() void RollAndGiveLootDrops();
    UFUNCTION() void SetEdgeStreakCounterVisible(bool bVisible);
    UFUNCTION() void UpdateEdgeStreakProgressBar();
    UFUNCTION() void ClearIdleTimer();
    UFUNCTION() void ResetIdleTimer();
    UFUNCTION() void OnIdleTimeout();
    UFUNCTION() void SyncVideoLoopToBeat();
    UFUNCTION() void HandleMediaPlaybackError(const FString& ErrorMessage);
    // Notification queue: enqueue, dequeue, and clear pending notifications.
    UFUNCTION(BlueprintCallable, Category="Recovered|Notifications") void EnqueueNotification(const FString& NotificationText);
    UFUNCTION(BlueprintCallable, Category="Recovered|Notifications") bool DequeueNotification(FString& OutText);
    UFUNCTION(BlueprintPure, Category="Recovered|Notifications") int32 GetPendingNotificationCount() const;
    // Exports session-end statistics as a JSON string for external tools.
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") FString ExportSessionStatsJson() const;
    // Video-loop toggle: enables/disables automatic video looping.
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetVideoLoopEnabled(bool bEnabled);
    UFUNCTION(BlueprintPure, Category="Recovered|Media") bool IsVideoLoopEnabled() const;
    UFUNCTION() void AddLifetimeDrawAndSave();
    UFUNCTION() void AddOneToLifetimeStrokesSave();
    UFUNCTION() void OnSessionFinalizedBroadcast();
    // Event family handlers (audit section 3).
    UFUNCTION() void StartMercyEvent();
    UFUNCTION() void AcceptMercy();
    UFUNCTION() void DeclineMercy();
    UFUNCTION() void StartTemptationEvent();
    UFUNCTION() void AcceptTemptation();
    UFUNCTION() void DeclineTemptation();
    UFUNCTION() void StartPunishmentEvent();
    UFUNCTION() void ExecuteTaunt();
    UFUNCTION() void OnMercyCooldownExpired();
    UFUNCTION() void OnTauntCooldownExpired();
    // Grants coins and tracks session earnings separately from the spendable balance.
    UFUNCTION(BlueprintCallable, Category="Recovered|Session") void GrantPlayerCoins(int32 Amount);
    // Inventory: acquire without immediate use, use from inventory, query counts.
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void AcquireStoreItem(FName ItemID);
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") bool UseOwnedItem(FName ItemID, int32 Level);
    UFUNCTION(BlueprintPure, Category="Recovered|Inventory") int32 GetOwnedItemCount(FName ItemID) const;
    // Shows the defensive item use overlay with the item name and remaining count.
    UFUNCTION(BlueprintCallable, Category="Recovered|Inventory") void ShowDefensiveItemOverlay(FName ItemID);
    // Dismisses all active event overlays.
    UFUNCTION(BlueprintCallable, Category="Recovered|Overlays") void DismissAllOverlays();
    UFUNCTION(BlueprintCallable, Category="Recovered|Overlays") void DismissOverlay(UUserWidget* Overlay);
    UFUNCTION() void HandleRecoveredMetric(ERecoveredMetric Metric,int32 Amount);
    UFUNCTION(BlueprintCallable,Category="Recovered Events") class UUserWidget* SpawnRecoveredOverlay(FName ScreenName);
    UFUNCTION(BlueprintCallable,Category="Recovered Events") bool SpawnRecoveredStore();
    UFUNCTION() void CompleteRecoveredStoreCooldown();
    UFUNCTION() void HandleRecoveredOutcome(const FRecoveredOutcomeEffects& Effects);
    // Post-game: session finalization, lifetime accounting, reward granting,
    // and presentation of the recovered post-game master screen. The original
    // ViewResultsButton routes through ExecuteUbergraph entry 67; the native
    // binding below reproduces that routing.
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void FinalizeRecoveredSession();
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void OpenPostGameResults();
    UFUNCTION() void BindPostGameResultsData(UUserWidget* Results);
    UFUNCTION() void HandleReturnToMenuClicked();
    UFUNCTION() void HandleRecoveredLevelUp(int32 Level, int32 UnlockPoints, const TArray<FString>& ContentUnlocks);
    UFUNCTION() void HandleSaveFailure(const FString& Context);
    UFUNCTION() void HandleProgressionMetric(ERecoveredMetric Metric, int32 Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") int32 CalculateRecoveredSessionXP() const;
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") FRecoveredSessionRewardData BuildRecoveredSessionRewardData(int32 SessionXP) const;
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") TArray<FRecoveredReward> PrepareRecoveredSessionRewards(int32 SessionXP) const;
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void ApplyRecoveredPostGameStorePoints(int32 Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") bool ApplyRecoveredIronManStorePenalty();
    UFUNCTION() void BindPostGameResultsButton(UUserWidget* PostCumWidget);
    UFUNCTION() void UpdateRecoveredLifetimeStats(int32 SessionXP);
    UFUNCTION() void SaveLifetimeStats();
    UFUNCTION() void LoadLifetimeStats();
    // Reads the saved calibration profile (if any) and applies its compensated
    // offset to the beat timeline. Called at session start and at every beat
    // sequence start so recalibration takes effect without restarting.
    UFUNCTION(BlueprintCallable, Category="Recovered|Calibration") void ApplySavedCalibrationToTimeline();
    // Launches the calibration flow UI.
    UFUNCTION(BlueprintCallable, Category="Recovered|Calibration") void LaunchCalibrationFlow();
    // Applies a purchased store item's effect to the live session. Called by
    // URecoveredStoreItemWidget after the coin deduction succeeds.
    UFUNCTION(BlueprintCallable, Category="Recovered|Store") bool ApplyStoreItemEffect(FName ItemID, int32 Level);
    // Audio presentation: plays session sounds (beat SFX with contextual pitch,
    // outcome stingers) as 2D sounds scaled by the saved volume settings.
    UFUNCTION(BlueprintCallable, Category="Recovered|Audio") void PlayRecoveredSessionSound(FName SoundID);
    // Dialogue/voiceline playback with voice-pack routing.
    UFUNCTION(BlueprintCallable, Category="Recovered|Audio") void PlayDialogueLine(FName LineID);
    // Beat sound bank selection: switches the tick sound variant.
    UFUNCTION(BlueprintCallable, Category="Recovered|Audio") void SetBeatSoundBank(FName BankID);
    UFUNCTION(BlueprintPure, Category="Recovered|Audio") FName GetBeatSoundBank() const;
    // Voice pack selection: switches the dialogue voice set.
    UFUNCTION(BlueprintCallable, Category="Recovered|Audio") void SetVoicePack(FName PackID);
    UFUNCTION(BlueprintPure, Category="Recovered|Audio") FName GetVoicePack() const;
    UFUNCTION(BlueprintCallable, Category="Recovered|Audio") float GetRecoveredVolume(const FString& SettingName, float Fallback) const;
    UPROPERTY(Transient) TArray<TObjectPtr<class UUserWidget>> EventOverlays;
    // During session finalization a level-up is presented by the post-game
    // master instead of spawning an unconnected duplicate overlay.
    UPROPERTY(Transient) int32 PendingPostGameLevel = INDEX_NONE;
    UPROPERTY(Transient) int32 PendingPostGameUnlockPoints = 0;
    UPROPERTY(Transient) TArray<FString> PendingPostGameContentUnlocks;
    UPROPERTY(Transient) FRecoveredSessionRewardData PendingPostGameRewardData;
    UPROPERTY(Transient) TObjectPtr<class URecoveredPostGameSequence> PostGameSequence;
    FTimerHandle StoreCooldownTimer;
    FTimerHandle OutcomeContinuationTimer;
    FTimerHandle IdleTimer;
    FTimerHandle MercyCooldownTimer;
    FTimerHandle TauntCooldownTimer;
    bool StartPaceCard(uint8 Pace,bool bPlayMedia,bool bPrepare);
    UFUNCTION(BlueprintCallable,Category="Recovered|Session") bool DrawRecoveredSpecialCard(FName Event,bool bPlayMedia=true);
    FTimerHandle SessionDurationTimer;
    bool bRecoveredSessionFinalized = false;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Outcomes") FRecoveredOutcomeEffects LastOutcomeEffects;
    UPROPERTY(BlueprintAssignable,Category="Recovered Outcomes") FRecoveredOutcomeRequested OnOutcomeRequested;
    UFUNCTION(BlueprintCallable,Category="Recovered Outcomes") void SuccessfulCum();
    UFUNCTION(BlueprintCallable,Category="Recovered Outcomes") void PrematureCum();
    // The original startup/session/outcome graph is not reconstructed here.
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredGameInstance : public UGameInstance {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Progression") TObjectPtr<URecoveredProgressionManager> ProgressionManager;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Progression") TObjectPtr<class URecoveredChallengeTracker> ChallengeTracker;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Devices") TObjectPtr<class URecoveredDeviceManager> DeviceManager;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") TObjectPtr<class URecoveredSaveGame> CurrentSave;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") FString ActiveRecoverySlot;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") FString LastSaveError;
    UPROPERTY(Transient,BlueprintReadOnly) bool bHasGameOpenedInSession=false;
    UPROPERTY(Transient,BlueprintReadOnly) TObjectPtr<URecoveredCalibrationManager> CalibrationManager;
    UPROPERTY(Transient) TObjectPtr<URecoveredMediaPlayback> BackgroundMediaPlayback;
    UPROPERTY(Transient) TObjectPtr<class UImage> BackgroundImageTarget;
    UFUNCTION() void PlayRecoveredBackgroundMedia(const FString& MediaName,class UImage* Image);
    UFUNCTION() void DisplayRecoveredBackgroundMedia(class UTexture* Texture);
    UFUNCTION() void RefreshRecoveredMainMenuBackground();
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") bool bProgressionStateValid=true;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") bool bChallengeStateValid=true;
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool PersistRecoveredProgression();
    UFUNCTION() void HandleProgressionSaveRequest();
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool LoadRecoveredSave();
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool LoadRecoveredSaveSlot(const FString& SlotName);
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool SaveRecoveredState();
    UFUNCTION(BlueprintPure,Category="Recovered Save") FString GetActiveRecoverySlot() const { return ActiveRecoverySlot; }
    static FString GetDefaultRecoverySlotName();
    static FString GetRecoverySlotIndexName();
    static FString GetNamedRecoverySlotPrefix();
    static bool IsRecoverySlotNameValid(const FString& SlotName);
    static bool ReadRecoverySlotIndex(TArray<FString>& OutNamedSlots,FString& OutActiveSlot,const FString& IndexSlotName);
    static bool WriteRecoverySlotIndex(const TArray<FString>& NamedSlots,const FString& ActiveSlot,const FString& IndexSlotName);
    virtual void Init() override;
private:
    bool LoadRecoveredSaveSlotInternal(const FString& SlotName,bool bPersistActiveSlot);
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredSaveGame : public USaveGame {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
    // Separate recovery format. Original slots and original GVAS data are never loaded.
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") int32 RecoveryFormatVersion=1;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Save") FString StateJson=TEXT("{}");
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool InitializeRecoveredDefaults();
    UFUNCTION(BlueprintPure,Category="Recovered Save") bool IsStateValid() const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") bool GetBoolSetting(const FString& Name,bool Fallback=false) const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") double GetNumberSetting(const FString& Name,double Fallback=0) const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") FString GetStringSetting(const FString& Name,const FString& Fallback) const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") TArray<FString> GetStringArraySetting(const FString& Name) const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") bool HasSetting(const FString& Name) const;
    UFUNCTION(BlueprintPure,Category="Recovered Save") FText GetTextSetting(const FString& Name,const FText& Fallback) const;
    UFUNCTION(BlueprintPure) bool GetLatencyProfile(FRecoveredLatencyProfile& Profile) const;
    UFUNCTION(BlueprintCallable) bool SetLatencyProfile(const FRecoveredLatencyProfile& Profile);
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool SetBoolSetting(const FString& Name,bool Value);
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool SetNumberSetting(const FString& Name,double Value);
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool SetStringSetting(const FString& Name,const FString& Value);
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool SetStringArraySetting(const FString& Name,const TArray<FString>& Values);
    // This does not implement original GVAS migration or restore original saves.
};

UCLASS()
class COCKHERORECOVERED_API URecoveredSaveSlotIndex : public USaveGame {
    GENERATED_BODY()
public:
    UPROPERTY() int32 RecoverySlotIndexVersion=1;
    UPROPERTY() TArray<FString> NamedSlots;
    UPROPERTY() FString ActiveSlot;
};
