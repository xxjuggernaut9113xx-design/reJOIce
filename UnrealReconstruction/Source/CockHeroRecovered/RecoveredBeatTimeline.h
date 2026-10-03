#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoveredSession.h"
#include "RecoveredBeatTimeline.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatEvent {
    GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") double AbsoluteFireTime = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") double TargetHitTime = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") int32 PatternIndex = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") double Interval = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") int32 BeatNumber = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") float CustomMultiplier = 0;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredBeatEventDelegate, const FRecoveredBeatEvent&, Beat);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredSequenceDelegate);

UCLASS(ClassGroup=(Recovered), meta=(BlueprintSpawnableComponent))
class COCKHERORECOVERED_API URecoveredBeatTimeline : public UActorComponent {
    GENERATED_BODY()
public:
    URecoveredBeatTimeline();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double MinimumBeatInterval = 0.01;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") TArray<FRecoveredBeatEvent> BeatQueue;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") int32 TotalStrokes = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") int32 CompletedBeats = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") bool bIsRunning = false;
    UPROPERTY(BlueprintAssignable, Category="Recovered") FRecoveredBeatEventDelegate OnBeatFired;
    UPROPERTY(BlueprintAssignable, Category="Recovered") FRecoveredBeatEventDelegate OnBeatHitCenter;
    UPROPERTY(BlueprintAssignable, Category="Recovered") FRecoveredSequenceDelegate OnSequenceEnd;
    UPROPERTY(BlueprintAssignable, Category="Recovered") FRecoveredSequenceDelegate OnSequencePaused;
    UFUNCTION(BlueprintCallable, Category="Recovered") bool StartPattern(const FRecoveredBeatPattern& Pattern, double BaseInterval, int32 StrokeCount, float SpeedModifier, double TravelTime);
    UFUNCTION(BlueprintCallable, Category="Recovered") void PauseSequence();
    UFUNCTION(BlueprintCallable, Category="Recovered") void ResumeSequence();
    UFUNCTION(BlueprintCallable, Category="Recovered") void StopSequence();
    UFUNCTION(BlueprintCallable, Category="Recovered") bool ApplySpeedModifier(float SpeedModifier);
    UFUNCTION(BlueprintCallable, Category="Recovered") bool ApplyStrokeCountModifier(int32 Factor);
    // Latency compensation from the calibration manager: the master timeline
    // runs ahead by this many seconds so beats fire early enough to be
    // perceived on time. Kept separate from TimelineOffset (pause bookkeeping).
    UFUNCTION(BlueprintCallable, Category="Recovered") void ApplyCalibrationOffset(double OffsetSeconds);
    UFUNCTION(BlueprintPure, Category="Recovered") double GetCalibrationOffset() const { return CalibrationOffset; }
    UFUNCTION(BlueprintPure, Category="Recovered") int32 GetBeatsRemaining() const;
    UFUNCTION(BlueprintPure, Category="Recovered") double GetMasterTimelinePosition() const;
    UFUNCTION(BlueprintPure, Category="Recovered") float GetCurrentInterval() const;
    static bool BuildBeatQueue(const FRecoveredBeatPattern& Pattern, double BaseInterval, int32 StrokeCount, float SpeedModifier, double TravelTime, double MinimumInterval, TArray<FRecoveredBeatEvent>& Queue, FString& Error);
    static bool RebuildFutureQueue(const FRecoveredBeatPattern& Pattern, double BaseInterval, float SpeedModifier, double TravelTime, double MinimumInterval, double CurrentTime, int32 FiredEntries, int32 FutureEntries, TArray<FRecoveredBeatEvent>& Queue);
    void AdvanceTo(double TimelineTime);
protected:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
    double MasterTimeReference = 0;
    double TimelineOffset = 0;
    double CalibrationOffset = 0;
    int32 NextFire = 0;
    int32 NextHit = 0;
    uint64 Generation = 0;
    FRecoveredBeatPattern CurrentPattern;
    double CurrentBaseInterval = 0;
    double CurrentTravelTime = 0;
    float CurrentSpeedModifier = 1;
};
