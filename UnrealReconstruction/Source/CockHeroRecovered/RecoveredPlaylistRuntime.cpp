#include "RecoveredPlaylistRuntime.h"
#include "HAL/PlatformTime.h"

URecoveredPlaylistRuntime::URecoveredPlaylistRuntime() { PrimaryComponentTick.bCanEverTick = true; }

bool URecoveredPlaylistRuntime::StartSongData(const FRecoveredBeatmapData& Data, double LeadIn, double Travel, double Adjustment, FString& Error) {
    Error.Reset();
    if (Data.Beats.IsEmpty() || !FMath::IsFinite(Data.Meta.Duration) || Data.Meta.Duration <= 0 || !FMath::IsFinite(LeadIn) || !FMath::IsFinite(Travel) || Travel < 0 || !FMath::IsFinite(Adjustment)) {
        Error = TEXT("Playback requires beats, positive finite duration, and finite timing parameters"); return false;
    }
    for (const auto& Beat : Data.Beats) if (!FMath::IsFinite(Beat.Time)) { Error = TEXT("Playback beat timestamp is not finite"); return false; }
    for (const auto& Event : Data.Events) if (!FMath::IsFinite(Event.Time)) { Error = TEXT("Playback event timestamp is not finite"); return false; }
    ++Generation;
    CurrentSong = Data;
    ConfiguredLeadIn = FMath::Max(LeadIn, 0.0); TravelSeconds = Travel; AdjustmentSeconds = Adjustment;
    Origin = FPlatformTime::Seconds() + ConfiguredLeadIn;
    FrozenTime = -ConfiguredLeadIn; PausedDuration = 0;
    NextBeat = NextEvent = NextFire = NextHit = 0;
    Scheduled.Reset(); EventHistory.Reset();
    bPlaying = true; bPaused = false; bOnBreak = false; bBreakSectionDisabled = false;
    return true;
}

bool URecoveredPlaylistRuntime::LoadTrack(int32 Index, FString& Error) {
    FRecoveredBeatmapData Data; FString Audio;
    if (!Playlist.IsValidIndex(Index) || !URecoveredBeatmapLibrary::LoadBeatmapFile(Playlist[Index], Data, Audio, Error)) return false;
    if (!StartSongData(Data, ConfiguredLeadIn, TravelSeconds, AdjustmentSeconds, Error)) return false;
    TrackIndex = Index; CurrentAudioPath = MoveTemp(Audio);
    bAwaitingNextTrack = false; PendingTrackIndex = INDEX_NONE;
    OnSongStarted.Broadcast(CurrentAudioPath);
    return true;
}

bool URecoveredPlaylistRuntime::StartPlaylist(const TArray<FString>& Paths, bool bLoop, double LeadIn, double Travel, double Adjustment, FString& Error) {
    Error.Reset();
    if (Paths.IsEmpty()) { Error = TEXT("Playlist contains no tracks"); return false; }
    // Preflight every file before replacing an active session.
    for (const FString& Path : Paths) {
        FRecoveredBeatmapData Data; FString Audio;
        if (!URecoveredBeatmapLibrary::LoadBeatmapFile(Path, Data, Audio, Error)) return false;
        if (!FMath::IsFinite(Data.Meta.Duration) || Data.Meta.Duration <= 0) { Error = TEXT("Playlist track has no positive finite duration: ") + Path; return false; }
    }
    if (!FMath::IsFinite(LeadIn) || !FMath::IsFinite(Travel) || Travel < 0 || !FMath::IsFinite(Adjustment)) { Error = TEXT("Playlist timing parameters are invalid"); return false; }
    StopPlayback(); Playlist = Paths; bLoopPlaylist = bLoop; CompletedRounds = 0;
    ConfiguredLeadIn = FMath::Max(LeadIn, 0.0); TravelSeconds = Travel; AdjustmentSeconds = Adjustment;
    return LoadTrack(0, Error);
}

double URecoveredPlaylistRuntime::GetAudioTime() const { return !bPlaying ? 0 : bPaused ? FrozenTime : FPlatformTime::Seconds() - Origin - PausedDuration; }
void URecoveredPlaylistRuntime::PausePlayback() {
    if (!bPlaying || bPaused) return;
    FrozenTime = GetAudioTime(); PauseStarted = FPlatformTime::Seconds(); bPaused = true;
}
void URecoveredPlaylistRuntime::ResumePlayback() {
    if (!bPlaying || !bPaused) return;
    PausedDuration += FPlatformTime::Seconds() - PauseStarted; bPaused = false;
}
void URecoveredPlaylistRuntime::StopPlayback() {
    ++Generation; bPlaying = bPaused = bOnBreak = false;
    Playlist.Reset(); Scheduled.Reset(); EventHistory.Reset();
    NextBeat = NextEvent = NextFire = NextHit = 0;
    bAwaitingNextTrack = false; PendingTrackIndex = INDEX_NONE;
}
bool URecoveredPlaylistRuntime::ContinuePlaylist(FString& Error) {
    if (!bAwaitingNextTrack || PendingTrackIndex == INDEX_NONE) { Error = TEXT("Playlist is not waiting for a next track"); return false; }
    return LoadTrack(PendingTrackIndex, Error);
}
bool URecoveredPlaylistRuntime::BeginBreak() {
    if (!bPlaying || bPaused || bOnBreak) return false;
    bOnBreak = true;
    Scheduled.Reset(); NextFire = NextHit = 0;
    return true;
}
void URecoveredPlaylistRuntime::EndBreak() {
    if (!bOnBreak) return;
    bOnBreak = false;
    // Native EndBreak discards beats through audio time plus the ctor's
    // two-second resume safety window.
    const double ResumeAt = GetAudioTime() + 2.0;
    while (CurrentSong.Beats.IsValidIndex(NextBeat) && CurrentSong.Beats[NextBeat].Time <= ResumeAt) ++NextBeat;
}

void URecoveredPlaylistRuntime::AdvanceTo(double AudioTime) {
    if (!bPlaying || bPaused || !FMath::IsFinite(AudioTime)) return;
    const uint64 CurrentGeneration = Generation;
    while (!bOnBreak && CurrentSong.Beats.IsValidIndex(NextBeat) && CurrentSong.Beats[NextBeat].Time <= AudioTime + 4.0) {
        const int32 Index = NextBeat++;
        const auto& Beat = CurrentSong.Beats[Index];
        if (Beat.Type == TEXT("rest")) continue;
        FRecoveredBeatEvent ScheduledBeat;
        ScheduledBeat.TargetHitTime = Beat.Time + AdjustmentSeconds;
        ScheduledBeat.AbsoluteFireTime = ScheduledBeat.TargetHitTime - TravelSeconds;
        ScheduledBeat.BeatNumber = Index + 1;
        ScheduledBeat.CustomMultiplier = Beat.Type == TEXT("accent") ? 1.5f : 1.f;
        ScheduledBeat.Interval = CurrentSong.Meta.Bpm > 0 ? 60.0 / CurrentSong.Meta.Bpm : 0.5;
        for (int32 I = Index + 1; I < CurrentSong.Beats.Num(); ++I) if (CurrentSong.Beats[I].Type != TEXT("rest")) { ScheduledBeat.Interval = CurrentSong.Beats[I].Time - Beat.Time; break; }
        Scheduled.Add(ScheduledBeat);
    }
    // Native enqueue pass precedes generic event dispatch. Presentation follows
    // the authored absolute fire/hit clocks and can dispatch several beats/frame.
    while (Scheduled.IsValidIndex(NextFire) && Scheduled[NextFire].AbsoluteFireTime <= AudioTime) {
        const auto Beat = Scheduled[NextFire++]; OnBeatFired.Broadcast(Beat);
        if (Generation != CurrentGeneration || !bPlaying || bPaused) return;
    }
    while (NextHit < NextFire && Scheduled[NextHit].TargetHitTime <= AudioTime) {
        const auto Beat = Scheduled[NextHit++]; OnBeatHitCenter.Broadcast(Beat);
        if (Generation != CurrentGeneration || !bPlaying || bPaused) return;
    }
    while (CurrentSong.Events.IsValidIndex(NextEvent) && CurrentSong.Events[NextEvent].Time <= AudioTime) {
        const auto Event = CurrentSong.Events[NextEvent++];
        if (bSuppressBreakControls && (Event.Type == TEXT("disable_break") || Event.Type == TEXT("restore_break"))) continue;
        const bool bMoreTracks = !bLoopPlaylist && Playlist.IsValidIndex(TrackIndex + 1);
        if (Event.Type == TEXT("cum_event") && bMoreTracks) continue;
        if (EventHistory.Num() >= 15) EventHistory.RemoveAt(0);
        EventHistory.Add(Event); OnBeatmapEvent.Broadcast(Event);
        if (Generation != CurrentGeneration || !bPlaying || bPaused) return;
    }
    if (AudioTime < CurrentSong.Meta.Duration) return;
    ++CompletedRounds; bPlaying = false;
    PendingTrackIndex = Playlist.IsValidIndex(TrackIndex + 1) ? TrackIndex + 1 : bLoopPlaylist ? 0 : INDEX_NONE;
    bAwaitingNextTrack = PendingTrackIndex != INDEX_NONE;
    OnSongComplete.Broadcast(CompletedRounds);
    if (Generation != CurrentGeneration) return;
    if (bAwaitingNextTrack) return;
    OnPlaylistComplete.Broadcast(CompletedRounds);
}
void URecoveredPlaylistRuntime::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction); AdvanceTo(GetAudioTime());
}
