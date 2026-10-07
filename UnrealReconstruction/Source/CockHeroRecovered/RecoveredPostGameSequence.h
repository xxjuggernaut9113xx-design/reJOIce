#pragma once

#include "CoreMinimal.h"
#include "RecoveredProgression.h"
#include "UObject/Object.h"
#include "RecoveredPostGameSequence.generated.h"

class ARecoveredGlobalManager;
class UUserWidget;

UENUM()
enum class ERecoveredPostGameStage : uint8 {
    Idle,
    XP,
    LevelUp,
    UnlockPoints,
    Summary
};

enum class ERecoveredPostGameAdvance : uint8 {
    None,
    XPSourceAnimation,
    XPBarAnimation,
    XPInterSourceDelay,
    LevelUpAnimation,
    XPOverflowAnimation,
    UnlockPointSourceAnimation,
    UnlockPointInterSourceDelay,
    BeginUnlockPoints,
    ShowSummary
};

UCLASS()
class COCKHERORECOVERED_API URecoveredPostGameSequence final : public UObject {
    GENERATED_BODY()
public:
    void Begin(ARecoveredGlobalManager* InManager, UUserWidget* InRoot, const FRecoveredSessionRewardData& InRewardData);
    void Stop();
    void AdvanceForTesting();
    ERecoveredPostGameStage GetStage() const { return Stage; }
    int32 GetDisplayedXP() const { return DisplayedXP; }
    int32 GetDisplayedUP() const { return DisplayedUP; }

private:
    UFUNCTION() void Advance();
    void ScheduleAdvance(float Delay, ERecoveredPostGameAdvance NextAdvance);
    void ShowNextXPSource();
    void StartXPBarAnimation();
    void CompleteXPSource();
    void ApplyXPAmount(int32 Amount);
    void PresentLevelUp();
    void CompleteLevelUp();
    void ShowXPOverflow();
    void ScheduleNextXPSource();
    void BeginUnlockPointStage();
    void ShowNextUPSource();
    void CompleteUPSource();
    void ShowSummary();
    void SetPage(int32 Index) const;
    int32 GetCurrentXPThreshold() const;

    UPROPERTY(Transient) TObjectPtr<ARecoveredGlobalManager> Manager;
    UPROPERTY(Transient) TObjectPtr<UUserWidget> Root;
    UPROPERTY(Transient) FRecoveredSessionRewardData RewardData;
    UPROPERTY(Transient) ERecoveredPostGameStage Stage = ERecoveredPostGameStage::Idle;
    FTimerHandle AdvanceTimer;
    ERecoveredPostGameAdvance PendingAdvance = ERecoveredPostGameAdvance::None;
    int32 CurrentXPSourceIndex = 0;
    int32 CurrentUPSourceIndex = 0;
    int32 CurrentLevelEventIndex = 0;
    int32 PendingXPAmount = 0;
    int32 PendingOverflowXP = 0;
    int32 DisplayedXP = 0;
    int32 DisplayedLevel = 1;
    int32 DisplayedUP = 0;
};
