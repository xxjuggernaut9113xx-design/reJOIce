#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoveredGameplay.h"
#include "RecoveredSuccuEconomy.generated.h"

class ARecoveredGlobalManager;

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredSuccuShopEntry {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) uint8 Modifier=0;
    UPROPERTY(BlueprintReadOnly) FString Title;
    UPROPERTY(BlueprintReadOnly) FString Description;
    UPROPERTY(BlueprintReadOnly) int32 Cost=0;
};

// RoundState.SuccuCoins and SuccuModifiers are run state, never profile currency.
UCLASS(ClassGroup=(Recovered),meta=(BlueprintSpawnableComponent))
class COCKHERORECOVERED_API URecoveredSuccuEconomy : public UActorComponent {
    GENERATED_BODY()
public:
    URecoveredSuccuEconomy();
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) int32 SuccuCoins=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) TSet<uint8> OwnedModifiers;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) FString LastError;
    int32 ShieldDraws=0;
    UFUNCTION(BlueprintCallable) void Initialize(ARecoveredGlobalManager* InManager);
    UFUNCTION(BlueprintCallable) void ResetRun();
    UFUNCTION(BlueprintCallable) bool Purchase(uint8 Modifier);
    UFUNCTION(BlueprintCallable) bool AddSuccuCoins(int32 Amount);
    UFUNCTION(BlueprintPure) bool HasModifier(uint8 Modifier) const;
    UFUNCTION(BlueprintPure) static TArray<FRecoveredSuccuShopEntry> GetCatalog();
    double AdjustHeatGain(double Amount) const;
    double GetHeatCap() const;
    double GetSuccubusStrokeMultiplier() const;
    int32 AdjustLootCoinReward(int32 Amount) const;
    int32 AdjustSuccubusCoinReward(int32 Amount);
    bool RollRecycler();
    bool RollBankingError();
    bool IsSuccubusOnCooldown() const;
    virtual void TickComponent(float DeltaTime,ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) override;
    virtual void EndPlay(const EEndPlayReason::Type Reason) override;
private:
    UPROPERTY() TObjectPtr<ARecoveredGlobalManager> Manager;
    FRandomStream Random;
    double TycoonElapsed=0;
    double ExorcistRemaining=0;
    int32 CoinverterStrokes=0;
    UFUNCTION() void HandleMetric(ERecoveredMetric Metric,int32 Amount);
    UFUNCTION() void HandleAction(FName Action);
};
