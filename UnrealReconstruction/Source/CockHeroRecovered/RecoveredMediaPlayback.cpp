#include "RecoveredMediaPlayback.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Components/ScaleBox.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "HAL/FileManager.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

bool URecoveredMediaPlayback::OpenEntry(const FRecoveredMediaEntry& Entry, double InitialSyncTime) {
    StopPlayback();
    CurrentEntry=Entry;
    if (!IFileManager::Get().FileExists(*Entry.FullPath)) { OnMediaError.Broadcast(TEXT("Media file does not exist: ")+Entry.FullPath); return false; }
    if (Entry.Type.Equals(TEXT("image"), ESearchCase::IgnoreCase)) {
        CurrentTexture=UKismetRenderingLibrary::ImportFileAsTexture2D(this,Entry.FullPath);
        if (!CurrentTexture) { OnMediaError.Broadcast(TEXT("Image decoder failed: ")+Entry.FullPath); return false; }
        ApplyCropMode();
        OnMediaReady.Broadcast(CurrentTexture);
        return true;
    }
    // PlayMediaEntry marks a video for its initial beat-travel alignment before
    // StartPatternWithMediaSync consumes that one-shot flag.
    bHasInitialSync=InitialSyncTime>=0.0;
    BeatTravelTimeOffset=bHasInitialSync ? InitialSyncTime : 0.0;
    if (!MediaPlayer) {
        MediaPlayer=NewObject<UMediaPlayer>(this);
        MediaPlayer->OnMediaOpened.AddDynamic(this,&URecoveredMediaPlayback::HandleOpened);
        MediaPlayer->OnMediaOpenFailed.AddDynamic(this,&URecoveredMediaPlayback::HandleFailed);
        VideoTexture=NewObject<UMediaTexture>(this);
        VideoTexture->SetMediaPlayer(MediaPlayer);
        VideoTexture->UpdateResource();
    }
    MediaPlayer->SetLooping(bLooping);
    if (!MediaPlayer->OpenFile(Entry.FullPath)) { OnMediaError.Broadcast(TEXT("Video open request failed: ")+Entry.FullPath); return false; }
    return true;
}
void URecoveredMediaPlayback::HandleOpened(FString Url) {
    CurrentTexture=VideoTexture;
    ApplyCropMode();
    MediaPlayer->Play();
    OnMediaReady.Broadcast(CurrentTexture);
}
void URecoveredMediaPlayback::HandleFailed(FString Url) { OnMediaError.Broadcast(TEXT("Video decoder failed: ")+Url); }
void URecoveredMediaPlayback::StopPlayback() {
    if(MediaPlayer) MediaPlayer->Close();
    CurrentTexture=nullptr;
    bHasInitialSync=false;
    bUseSyncStartTime=false;
    BeatTravelTimeOffset=0.0;
}
void URecoveredMediaPlayback::SetPaused(bool bPaused) { if(MediaPlayer) { if(bPaused) MediaPlayer->Pause(); else MediaPlayer->Play(); } }
bool URecoveredMediaPlayback::SetPlaybackRate(float Rate) { return MediaPlayer && MediaPlayer->SetRate(Rate); }
void URecoveredMediaPlayback::SetBeatInterval(double NewBeatInterval) {
    BeatInterval=FMath::Max(NewBeatInterval,0.01);
}
void URecoveredMediaPlayback::SetSyncStartTime(double InMasterTimeReference,double InTimelineOffset) {
    MasterTimeReference=InMasterTimeReference;
    TimelineOffset=InTimelineOffset;
    SyncStartTime=InMasterTimeReference;
    bUseSyncStartTime=true;
    BeatTravelTimeOffset=0.0;
}
void URecoveredMediaPlayback::SyncToBeat(double InBeatTime,double InMasterTime,double InOffset) {
    LastSyncBeatTime=InBeatTime;
    LastSyncTimelineTime=InMasterTime-InOffset;
}
void URecoveredMediaPlayback::BeginPatternSynchronization(double InMasterTimeReference,double InTimelineOffset,double InitialBeatTravelTime) {
    SetSyncStartTime(InMasterTimeReference,InTimelineOffset);
    if (!bHasInitialSync) {
        SyncToBeat(InitialBeatTravelTime,InMasterTimeReference,0.0);
        return;
    }
    BeatTravelTimeOffset=0.0;
    bHasInitialSync=false;
}
void URecoveredMediaPlayback::EnableBeatPatternSync(bool bEnabled) { bBeatSyncEnabled=bEnabled; }
UMaterialInstanceDynamic* URecoveredMediaPlayback::GetVideoDisplayMaterial() {
    if (!VideoTexture) return nullptr;
    if (!VideoMaterial) {
        auto* Material=LoadObject<UMaterialInterface>(nullptr,TEXT("/Game/Recovery/Resources/Video/Background_Video_Texture_Mat.Background_Video_Texture_Mat"));
        if (!Material) return nullptr;
        VideoMaterial=UMaterialInstanceDynamic::Create(Material,this);
    }
    if (VideoMaterial) VideoMaterial->SetTextureParameterValue(TEXT("BackgroundVideoTexture"),VideoTexture);
    return VideoMaterial;
}
void URecoveredMediaPlayback::BeginDestroy() { StopPlayback(); Super::BeginDestroy(); }

void URecoveredMediaPlayback::SetLooping(bool bEnabled) { bLooping=bEnabled; if (MediaPlayer) MediaPlayer->SetLooping(bEnabled); }

void URecoveredMediaPlayback::SetScaleBoxReference(UScaleBox* InScaleBox) {
    ScaleBox=InScaleBox;
    ApplyCropMode();
}

void URecoveredMediaPlayback::SetCropMode(ERecoveredCropMode InCropMode) {
    CropMode=InCropMode;
    ApplyCropMode();
}

float URecoveredMediaPlayback::GetContentAspectRatio() const {
    if (const UTexture2D* Still=Cast<UTexture2D>(CurrentTexture)) {
        const int32 Height=Still->GetSizeY();
        if (Height>0) return static_cast<float>(Still->GetSizeX())/static_cast<float>(Height);
    }
    if (MediaPlayer) {
        const float Aspect=MediaPlayer->GetVideoTrackAspectRatio(INDEX_NONE,INDEX_NONE);
        if (Aspect>0.0f) return Aspect;
    }
    return 16.0f/9.0f;
}

void URecoveredMediaPlayback::ApplyCropMode() {
    UScaleBox* Target=ScaleBox.Get();
    if (!Target) return;
    EStretch::Type Stretch=EStretch::ScaleToFill;
    if (CropMode==ERecoveredCropMode::Fill) {
        Stretch=EStretch::Fill;
    } else if (CropMode==ERecoveredCropMode::Fit) {
        Stretch=EStretch::ScaleToFit;
    } else {
        const float Aspect=GetContentAspectRatio();
        if (FMath::IsNearlyEqual(Aspect,16.0f/9.0f,0.01f)) Stretch=EStretch::Fill;
        else if (Aspect<=1.0f || FMath::IsNearlyEqual(Aspect,9.0f/16.0f,0.01f) || FMath::IsNearlyEqual(Aspect,3.0f/4.0f,0.01f)) Stretch=EStretch::ScaleToFit;
        else if (FMath::IsNearlyEqual(Aspect,4.0f/3.0f,0.01f)) Stretch=EStretch::ScaleToFitY;
        else if (Aspect>=2.0f) Stretch=EStretch::ScaleToFitX;
    }
    Target->SetStretch(Stretch);
}
