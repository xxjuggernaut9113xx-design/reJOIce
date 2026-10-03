#include "RecoveredBeatTimeline.h"

float URecoveredBeatTimeline::GetCurrentInterval() const { return BeatQueue.IsValidIndex(NextFire) ? static_cast<float>(BeatQueue[NextFire].Interval) : 0.0f; }
#include "HAL/PlatformTime.h"

URecoveredBeatTimeline::URecoveredBeatTimeline() {
    PrimaryComponentTick.bCanEverTick = true;
}
bool URecoveredBeatTimeline::BuildBeatQueue(const FRecoveredBeatPattern& Pattern, double BaseInterval, int32 StrokeCount, float SpeedModifier, double TravelTime, double MinimumInterval, TArray<FRecoveredBeatEvent>& Queue, FString& Error) {
    Queue.Reset();
    Error.Reset();
    if (StrokeCount <= 0 || Pattern.IntervalMultipliers.IsEmpty()) return true;
    // The original loops forever for an all-rest pattern. Reject that invalid input.
    bool bHasStroke = false;
    for (double Value : Pattern.IntervalMultipliers) {
        if (!FMath::IsFinite(Value)) { Error = TEXT("Pattern contains a non-finite interval"); return false; }
        bHasStroke |= Value >= 0;
    }
    if (!bHasStroke) { Error = TEXT("Pattern contains only rests"); return false; }
    if (!FMath::IsFinite(BaseInterval) || !FMath::IsFinite(SpeedModifier) || SpeedModifier <= 0 || !FMath::IsFinite(TravelTime) || !FMath::IsFinite(MinimumInterval) || MinimumInterval <= 0) {
        Error = TEXT("Invalid beat timing input"); return false;
    }
    double HitTime = TravelTime;
    int32 Strokes = 0;
    int32 PatternIndex = 0;
    while (Strokes < StrokeCount) {
        const float Multiplier = static_cast<float>(Pattern.IntervalMultipliers[PatternIndex]);
        const double Interval = FMath::Max((1.0 / static_cast<double>(SpeedModifier)) * (FMath::Abs(static_cast<double>(Multiplier)) * BaseInterval), MinimumInterval);
        FRecoveredBeatEvent Event;
        Event.AbsoluteFireTime = HitTime - TravelTime;
        Event.TargetHitTime = HitTime;
        Event.PatternIndex = PatternIndex;
        Event.Interval = Interval;
        Event.BeatNumber = Queue.Num() + 1;
        Event.CustomMultiplier = Multiplier;
        Queue.Add(Event);
        HitTime += Interval;
        if (Multiplier >= 0) ++Strokes;
        PatternIndex = (PatternIndex + 1) % Pattern.IntervalMultipliers.Num();
    }
    return true;
}
bool URecoveredBeatTimeline::StartPattern(const FRecoveredBeatPattern& Pattern, double BaseInterval, int32 StrokeCount, float SpeedModifier, double TravelTime) {
    TArray<FRecoveredBeatEvent> NewQueue;
    FString Error;
    if (!BuildBeatQueue(Pattern, BaseInterval, StrokeCount, SpeedModifier, TravelTime, MinimumBeatInterval, NewQueue, Error)) {
        UE_LOG(LogTemp, Warning, TEXT("Recovered beat queue rejected: %s"), *Error);
        return false;
    }
    ++Generation;
    CurrentPattern = Pattern;
    CurrentBaseInterval = BaseInterval;
    CurrentTravelTime = TravelTime;
    CurrentSpeedModifier = SpeedModifier;
    BeatQueue = MoveTemp(NewQueue);
    TotalStrokes = StrokeCount;
    CompletedBeats = 0;
    NextFire = NextHit = 0;
    TimelineOffset = 0;
    MasterTimeReference = FPlatformTime::Seconds();
    bIsRunning = !BeatQueue.IsEmpty();
    return true;
}
bool URecoveredBeatTimeline::RebuildFutureQueue(const FRecoveredBeatPattern& Pattern,double BaseInterval,float SpeedModifier,double TravelTime,double MinimumInterval,double CurrentTime,int32 FiredEntries,int32 FutureEntries,TArray<FRecoveredBeatEvent>& Queue) {
    // Original RebuildQueueFromCurrentState 0x1481d1c90: count is queue entries, including rests.
    // Non-finite timing and excessively large allocations are rejected by the reconstruction.
    if(Pattern.IntervalMultipliers.IsEmpty() || FiredEntries<0 || FiredEntries>Queue.Num() || FutureEntries<0 || FutureEntries>1000000 ||
        !FMath::IsFinite(SpeedModifier) || SpeedModifier<=0 || !FMath::IsFinite(BaseInterval) || !FMath::IsFinite(TravelTime) ||
        !FMath::IsFinite(CurrentTime) || !FMath::IsFinite(MinimumInterval) || MinimumInterval<=0) return false;
    for(double Value:Pattern.IntervalMultipliers) if(!FMath::IsFinite(Value)) return false;
    int32 PatternIndex=Queue.IsValidIndex(FiredEntries) ? Queue[FiredEntries].PatternIndex : 0;
    Queue.SetNum(FiredEntries);
    double FireTime=CurrentTime+0.1; // Original readonly double at 0x14bd774b8.
    const double InverseSpeed=1.0/static_cast<double>(SpeedModifier);
    for(int32 I=0;I<FutureEntries;++I) {
        if(!Pattern.IntervalMultipliers.IsValidIndex(PatternIndex)) PatternIndex=0;
        const float Multiplier=static_cast<float>(Pattern.IntervalMultipliers[PatternIndex]);
        double Interval=FMath::Abs(static_cast<double>(Multiplier))*BaseInterval*InverseSpeed;
        if(Interval<=MinimumInterval) Interval=MinimumInterval;
        FRecoveredBeatEvent Event;
        Event.AbsoluteFireTime=FireTime;
        Event.TargetHitTime=FireTime+TravelTime;
        Event.PatternIndex=PatternIndex;
        Event.Interval=Interval;
        Event.BeatNumber=FiredEntries+I+1;
        Event.CustomMultiplier=Multiplier;
        Queue.Add(Event);
        FireTime+=Interval;
        PatternIndex=(PatternIndex+1)%Pattern.IntervalMultipliers.Num();
    }
    return true;
}
bool URecoveredBeatTimeline::ApplySpeedModifier(float SpeedModifier) {
    if(!bIsRunning || BeatQueue.IsEmpty() || NextFire>=BeatQueue.Num()) return false;
    if(!RebuildFutureQueue(CurrentPattern,CurrentBaseInterval,SpeedModifier,CurrentTravelTime,MinimumBeatInterval,GetMasterTimelinePosition(),NextFire,BeatQueue.Num()-NextFire,BeatQueue)) return false;
    CurrentSpeedModifier=SpeedModifier;
    ++Generation;
    return true;
}
bool URecoveredBeatTimeline::ApplyStrokeCountModifier(int32 Factor) {
    if(!bIsRunning || Factor<=0 || BeatQueue.IsEmpty() || NextFire>=BeatQueue.Num()) return false;
    const int64 FutureCount=int64(BeatQueue.Num()-NextFire)*Factor;
    if(FutureCount>1000000 || FutureCount+NextFire>MAX_int32) return false;
    if(!RebuildFutureQueue(CurrentPattern,CurrentBaseInterval,CurrentSpeedModifier,CurrentTravelTime,MinimumBeatInterval,GetMasterTimelinePosition(),NextFire,int32(FutureCount),BeatQueue)) return false;
    // Native 0x1481cfbd4 counts rests in the revised total; retain that source behavior.
    TotalStrokes=NextFire+int32(FutureCount);
    ++Generation;
    return true;
}
void URecoveredBeatTimeline::PauseSequence() {
    if (!bIsRunning) return;
    // Fold only the uncalibrated position into the pause offset; the
    // calibration offset stays separate and keeps applying after resume.
    TimelineOffset = GetMasterTimelinePosition() - CalibrationOffset;
    MasterTimeReference = FPlatformTime::Seconds();
    bIsRunning = false;
    OnSequencePaused.Broadcast();
}
void URecoveredBeatTimeline::ResumeSequence() {
    if (bIsRunning || BeatQueue.IsEmpty() || CompletedBeats >= TotalStrokes) return;
    MasterTimeReference = FPlatformTime::Seconds();
    bIsRunning = true;
}
void URecoveredBeatTimeline::StopSequence() {
    ++Generation;
    bIsRunning = false;
    BeatQueue.Reset();
    NextFire = NextHit = 0;
    OnSequencePaused.Broadcast();
}
int32 URecoveredBeatTimeline::GetBeatsRemaining() const { return FMath::Max(TotalStrokes - CompletedBeats, 0); }
void URecoveredBeatTimeline::ApplyCalibrationOffset(double OffsetSeconds) {
    // Latency compensation is a small positive shift; clamp to a sane range so
    // a bad profile cannot throw the timeline off by seconds.
    CalibrationOffset = FMath::Clamp(OffsetSeconds, 0.0, 2.0);
}
double URecoveredBeatTimeline::GetMasterTimelinePosition() const {
    // The timeline runs ahead by the calibration offset so beats fire early
    // enough to land on the player's perception of the beat.
    return bIsRunning ? FPlatformTime::Seconds() - MasterTimeReference + TimelineOffset + CalibrationOffset : TimelineOffset + CalibrationOffset;
}
void URecoveredBeatTimeline::AdvanceTo(double TimelineTime) {
    if (!bIsRunning) return;
    const uint64 CurrentGeneration = Generation;
    while (NextFire < BeatQueue.Num() && BeatQueue[NextFire].AbsoluteFireTime <= TimelineTime) {
        const FRecoveredBeatEvent Event = BeatQueue[NextFire++];
        if (Event.CustomMultiplier >= 0) OnBeatFired.Broadcast(Event);
        if (Generation != CurrentGeneration || !bIsRunning) return;
    }
    while (NextHit < NextFire && BeatQueue[NextHit].TargetHitTime <= TimelineTime) {
        const FRecoveredBeatEvent Event = BeatQueue[NextHit++];
        if (Event.CustomMultiplier >= 0) {
            // Native OnBeatReachedCenter broadcasts before increasing CompletedBeats.
            OnBeatHitCenter.Broadcast(Event);
            if (Generation != CurrentGeneration) return;
            ++CompletedBeats;
        }
        if (!bIsRunning) return;
    }
    if (CompletedBeats >= TotalStrokes && NextHit >= BeatQueue.Num()) {
        bIsRunning = false;
        TimelineOffset = TimelineTime - CalibrationOffset;
        // Presentation/widget teardown and the original deferred end callback remain adapters.
        OnSequenceEnd.Broadcast();
    }
}
void URecoveredBeatTimeline::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AdvanceTo(GetMasterTimelinePosition());
}
