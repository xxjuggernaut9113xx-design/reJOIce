#include "RecoveredCalibration.h"
#include "Engine/World.h"
#include "TimerManager.h"
bool URecoveredCalibrationManager::CalculatePerceptionOffset(const TArray<float>& Taps,const TArray<double>& Beats,int32 MinimumTaps,float& Offset) {
    if (Taps.Num()<MinimumTaps || Taps.IsEmpty() || Beats.IsEmpty()) return false;
    float Sum=0;
    for (float Tap:Taps) {
        if (!FMath::IsFinite(Tap)) return false;
        float Nearest=float(Beats[0]),Distance=FMath::Abs(Tap-Nearest);
        for (double Beat:Beats) { if (!FMath::IsFinite(Beat)) return false;const float Value=float(Beat),Delta=FMath::Abs(Tap-Value);if (Delta<Distance) { Nearest=Value;Distance=Delta; } }
        Sum+=(Tap-Nearest)*1000.0f;
    }
    const float Result=Sum/float(Taps.Num());if (!FMath::IsFinite(Result)) return false;Offset=Result;return true;
}
UWorld* URecoveredCalibrationManager::GetWorld() const { return !HasAnyFlags(RF_ClassDefaultObject) && GetOuter()?GetOuter()->GetWorld():nullptr; }
void URecoveredCalibrationManager::StartCalibration() {
    CancelCalibration();State=1;CurrentProfile.AudioLatencyMs=45;OnProgress.Broadcast(State,0);
    if (GetWorld()) GetWorld()->GetTimerManager().SetTimer(CalibrationTimer,this,&URecoveredCalibrationManager::StartManualCalibration,1.0f,false);
    else StartManualCalibration();
}
void URecoveredCalibrationManager::StartManualCalibration() {
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(CalibrationTimer);
    State=2;TapTimes.Empty();BeatTimes.Empty();BeatIndex=0;OnProgress.Broadcast(State,0);RunManualCalibrationStep();
}
void URecoveredCalibrationManager::RunManualCalibrationStep() {
    if (State!=2) return;
    if (BeatIndex>=MaximumBeats) { FinishCalibration();return; }
    const double Time=GetWorld()?GetWorld()->GetTimeSeconds():0;
    if (BeatTimes.IsValidIndex(BeatIndex)) BeatTimes[BeatIndex]=Time;else BeatTimes.Add(Time);
    ++BeatIndex;OnMetronome.Broadcast();
    if (GetWorld() && CalibrationBPM>0) GetWorld()->GetTimerManager().SetTimer(CalibrationTimer,this,&URecoveredCalibrationManager::RunManualCalibrationStep,60.0f/CalibrationBPM,false);
}
void URecoveredCalibrationManager::RegisterBeatTap(float TimeStamp) {
    if (State!=2 || !FMath::IsFinite(TimeStamp)) return;
    TapTimes.Add(TimeStamp);OnProgress.Broadcast(State,float(TapTimes.Num())/float(RequiredTaps));
    if (TapTimes.Num()>=RequiredTaps) FinishCalibration();
}
void URecoveredCalibrationManager::FinishCalibration() {
    CalculatePerceptionOffset(TapTimes,BeatTimes,RequiredTaps,CurrentProfile.UserPerceptionOffsetMs);
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(CalibrationTimer);
    State=4;CurrentProfile.bIsCalibrated=true;CurrentProfile.CreatedDate=FDateTime::Now();
    OnComplete.Broadcast(CurrentProfile);OnProgress.Broadcast(State,1);
}
void URecoveredCalibrationManager::CancelCalibration() { if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(CalibrationTimer);State=0; }
int32 URecoveredCalibrationManager::GetRequiredTapsRemaining() const { return State==2?FMath::Max(RequiredTaps-TapTimes.Num(),0):0; }
float URecoveredCalibrationManager::GetCalibrationProgress() const {
    switch(State) { case 1:return .25f;case 2:return RequiredTaps>0?float(TapTimes.Num())*.5f/float(RequiredTaps)+.25f:.25f;case 3:return .75f;case 4:return 1;default:return 0; }
}
void URecoveredCalibrationManager::BeginDestroy() { CancelCalibration();Super::BeginDestroy(); }
