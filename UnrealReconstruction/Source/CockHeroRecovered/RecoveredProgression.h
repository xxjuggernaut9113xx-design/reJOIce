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
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredXPGained,int32,Amount,const FString&,Source);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRecoveredLevelUp,int32,Level,int32,UnlockPoints,const TArray<FString>&,ContentUnlocks);
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
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered") TSet<FName> UnlockedModifiers;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredProgressionSaveRequest OnSaveRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredPackRewardRequest OnPackRewardRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredStorePointsRequest OnStorePointsRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredXPGained OnXPGained;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredLevelUp OnLevelUp;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredProgressUpdated OnProgressUpdate;
    UPROPERTY(BlueprintAssignable,Category="Recovered") FRecoveredMetricUpdateRequested OnMetricUpdateRequested;
    UFUNCTION(BlueprintCallable,Category="Recovered") void AddXP(int32 Amount,const FString& Source);
    UFUNCTION(BlueprintCallable,Category="Recovered") void AddUnlockPoints(int32 Amount);
    UFUNCTION(BlueprintCallable,Category="Recovered") void CheckLevelUp();
    UFUNCTION(BlueprintCallable,Category="Recovered") bool UnlockPlayerCard(FName CardID);
    UFUNCTION(BlueprintCallable,Category="Recovered") bool UnlockModifier(FName ModifierID);
    UFUNCTION(BlueprintPure,Category="Recovered Save") FString ExportRecoveryState() const;
    UFUNCTION(BlueprintCallable,Category="Recovered Save") bool ImportRecoveryState(const FString& Json);
};
