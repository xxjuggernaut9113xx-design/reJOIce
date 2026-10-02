#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RecoveredCalibration.generated.h"
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredLatencyProfile {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float VideoDecodeLatencyMs=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float AudioLatencyMs=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float UserPerceptionOffsetMs=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float ToyLatencyMs=0;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float SystemBufferMs=60;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FString ProfileName=TEXT("Default");
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FDateTime CreatedDate;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) bool bIsCalibrated=false;
    float TotalLatencyMs() const { return ((SystemBufferMs+ToyLatencyMs)+UserPerceptionOffsetMs)+(AudioLatencyMs+VideoDecodeLatencyMs); }
    bool IsValid() const { return bIsCalibrated && TotalLatencyMs()>0; }
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredCalibrationProgress,uint8,State,float,Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredCalibrationComplete,const FRecoveredLatencyProfile&,Profile);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredMetronome);
UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredCalibrationManager : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FRecoveredLatencyProfile CurrentProfile;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) float CalibrationBPM=120;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) int32 RequiredTaps=16;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) int32 MaximumBeats=32;
    UPROPERTY(BlueprintReadOnly) uint8 State=0;
    UPROPERTY(BlueprintReadOnly) TArray<float> TapTimes;
    UPROPERTY(BlueprintReadOnly) TArray<double> BeatTimes;
    UPROPERTY(BlueprintAssignable) FRecoveredCalibrationProgress OnProgress;
    UPROPERTY(BlueprintAssignable) FRecoveredCalibrationComplete OnComplete;
    UPROPERTY(BlueprintAssignable) FRecoveredMetronome OnMetronome;
    UFUNCTION(BlueprintCallable) void StartCalibration();
    UFUNCTION(BlueprintCallable) void StartManualCalibration();
    UFUNCTION(BlueprintCallable) void RegisterBeatTap(float TimeStamp);
    UFUNCTION(BlueprintCallable) void CancelCalibration();
    UFUNCTION(BlueprintPure) int32 GetRequiredTapsRemaining() const;
    UFUNCTION(BlueprintPure) float GetCalibrationProgress() const;
    UFUNCTION(BlueprintPure) double GetCompensatedTimelineOffset() const { return double(CurrentProfile.TotalLatencyMs())*.001; }
    static bool CalculatePerceptionOffset(const TArray<float>& Taps,const TArray<double>& Beats,int32 MinimumTaps,float& Offset);
    virtual UWorld* GetWorld() const override;
    virtual void BeginDestroy() override;
private:
    UFUNCTION() void RunManualCalibrationStep();
    void FinishCalibration();
    FTimerHandle CalibrationTimer;
    int32 BeatIndex=0;
};
