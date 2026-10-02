#include "RecoveredMediaPlayback.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "Engine/Texture2D.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "HAL/FileManager.h"
#include "Materials/MaterialInterface.h"
#include "Materials/MaterialInstanceDynamic.h"

bool URecoveredMediaPlayback::OpenEntry(const FRecoveredMediaEntry& Entry) {
    StopPlayback();
    CurrentEntry=Entry;
    if (!IFileManager::Get().FileExists(*Entry.FullPath)) { OnMediaError.Broadcast(TEXT("Media file does not exist: ")+Entry.FullPath); return false; }
    if (Entry.Type.Equals(TEXT("image"), ESearchCase::IgnoreCase)) {
        CurrentTexture=UKismetRenderingLibrary::ImportFileAsTexture2D(this,Entry.FullPath);
        if (!CurrentTexture) { OnMediaError.Broadcast(TEXT("Image decoder failed: ")+Entry.FullPath); return false; }
        OnMediaReady.Broadcast(CurrentTexture);
        return true;
    }
    if (!MediaPlayer) {
        MediaPlayer=NewObject<UMediaPlayer>(this);
        MediaPlayer->OnMediaOpened.AddDynamic(this,&URecoveredMediaPlayback::HandleOpened);
        MediaPlayer->OnMediaOpenFailed.AddDynamic(this,&URecoveredMediaPlayback::HandleFailed);
        VideoTexture=NewObject<UMediaTexture>(this);
        VideoTexture->SetMediaPlayer(MediaPlayer);
        VideoTexture->UpdateResource();
    }
    MediaPlayer->SetLooping(true);
    if (!MediaPlayer->OpenFile(Entry.FullPath)) { OnMediaError.Broadcast(TEXT("Video open request failed: ")+Entry.FullPath); return false; }
    return true;
}
void URecoveredMediaPlayback::HandleOpened(FString Url) {
    CurrentTexture=VideoTexture;
    MediaPlayer->Play();
    OnMediaReady.Broadcast(CurrentTexture);
}
void URecoveredMediaPlayback::HandleFailed(FString Url) { OnMediaError.Broadcast(TEXT("Video decoder failed: ")+Url); }
void URecoveredMediaPlayback::StopPlayback() { if(MediaPlayer) MediaPlayer->Close(); CurrentTexture=nullptr; }
void URecoveredMediaPlayback::SetPaused(bool bPaused) { if(MediaPlayer) { if(bPaused) MediaPlayer->Pause(); else MediaPlayer->Play(); } }
bool URecoveredMediaPlayback::SetPlaybackRate(float Rate) { return MediaPlayer && MediaPlayer->SetRate(Rate); }
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
