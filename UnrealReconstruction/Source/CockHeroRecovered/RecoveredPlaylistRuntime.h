#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecoveredBeatmap.h"
#include "RecoveredBeatTimeline.h"
#include "RecoveredPlaylistRuntime.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredBeatmapEventDelegate, const FRecoveredBeatmapEvent&, Event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredSongPathDelegate, const FString&, AudioPath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredPlaylistProgressDelegate, int32, CompletedRounds);

// Scheduling follows native-music-contract.md. A completed nonfinal track
// waits for progression selection before the next track starts.
UCLASS(ClassGroup=(Recovered), meta=(BlueprintSpawnableComponent))
class COCKHERORECOVERED_API URecoveredPlaylistRuntime : public UActorComponent {
    GENERATED_BODY()
public:
    int32 BreakRechargeStrokes = 0;
    int32 LastObservedStrokes = 0;
    bool bPreviousBreak = false;
    bool bBreakSectionDisabled = false;
    double BreakFilterOrigin = 0;
    float BreakFilterStart = 20000;
    float CurrentBreakFilter = 20000;
    bool bAwaitingNextTrack = false;
    bool ContinuePlaylist(FString& Error);
    URecoveredPlaylistRuntime();
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") FRecoveredBeatmapData CurrentSong;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") FString CurrentAudioPath;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") int32 CompletedRounds = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") bool bPlaying = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") bool bPaused = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") bool bOnBreak = false;
    UFUNCTION(BlueprintCallable, Category="Recovered|Playlist") bool BeginBreak();
    UFUNCTION(BlueprintCallable, Category="Recovered|Playlist") void EndBreak();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Playlist") bool bSuppressBreakControls = false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Playlist") TArray<FRecoveredBeatmapEvent> EventHistory;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Playlist") FRecoveredBeatEventDelegate OnBeatFired;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Playlist") FRecoveredBeatEventDelegate OnBeatHitCenter;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Playlist") FRecoveredBeatmapEventDelegate OnBeatmapEvent;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Playlist") FRecoveredSongPathDelegate OnSongStarted;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Playlist") FRecoveredPlaylistProgressDelegate OnSongComplete;
    UPROPERTY(BlueprintAssignable, Category="Recovered|Playlist") FRecoveredPlaylistProgressDelegate OnPlaylistComplete;
    UFUNCTION(BlueprintCallable, Category="Recovered|Playlist") bool StartPlaylist(const TArray<FString>& Paths, bool bLoop, double LeadIn, double Travel, double Adjustment, FString& Error);
    UFUNCTION(BlueprintCallable, Category="Recovered|Playlist") void PausePlayback();
    UFUNCTION(BlueprintCallable, Category="Recovered|Playlist") void ResumePlayback();
    UFUNCTION(BlueprintCallable, Category="Recovered|Playlist") void StopPlayback();
    UFUNCTION(BlueprintPure, Category="Recovered|Playlist") double GetAudioTime() const;
    // Deterministic entry point for tests and external audio clock adapters.
    void AdvanceTo(double AudioTime);
    bool StartSongData(const FRecoveredBeatmapData& Data, double LeadIn, double Travel, double Adjustment, FString& Error);
protected:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
    bool LoadTrack(int32 Index, FString& Error);
    TArray<FString> Playlist;
    TArray<FRecoveredBeatEvent> Scheduled;
    int32 TrackIndex = 0, NextBeat = 0, NextEvent = 0, NextFire = 0, NextHit = 0;
    int32 PendingTrackIndex = INDEX_NONE;
    bool bLoopPlaylist = false;
    double Origin = 0, FrozenTime = 0, PauseStarted = 0, PausedDuration = 0;
    double ConfiguredLeadIn = 0, TravelSeconds = 0, AdjustmentSeconds = 0;
    uint64 Generation = 0;
};
