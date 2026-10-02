#include "RecoveredRules.h"
#include "RecoveredMenu.h"
#include "Components/Image.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Engine/Texture2D.h"
#include "MediaTexture.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
void URecoveredGameInstance::PlayRecoveredBackgroundMedia(const FString& MediaName,UImage* Image) {
    if (!Image || MediaName.IsEmpty() || MediaName.Contains(TEXT("/")) || MediaName.Contains(TEXT("\\")) || MediaName.Contains(TEXT(".."))) return;
    const FString Root=TEXT("C:/Users/webma/Downloads/Cock_Hero_Shipping_Build_V0.04_-_Exclusive/PrepV2/Windows/CockHero/Content/Movies");
    FRecoveredMediaEntry Entry;
    for (const TCHAR* Extension:{TEXT(".jpg"),TEXT(".png"),TEXT(".mp4"),TEXT(".webm")}) {
        const FString Path=Root/(MediaName+Extension);
        if (IFileManager::Get().FileExists(*Path)) { Entry.FullPath=Path;Entry.Type=(FString(Extension)==TEXT(".jpg") || FString(Extension)==TEXT(".png"))?TEXT("image"):TEXT("video");break; }
    }
    if (Entry.FullPath.IsEmpty()) return;
    if (!BackgroundMediaPlayback) {
        BackgroundMediaPlayback=NewObject<URecoveredMediaPlayback>(this);
        BackgroundMediaPlayback->OnMediaReady.AddUniqueDynamic(this,&URecoveredGameInstance::DisplayRecoveredBackgroundMedia);
    }
    BackgroundImageTarget=Image;BackgroundMediaPlayback->OpenEntry(Entry);
}
void URecoveredGameInstance::DisplayRecoveredBackgroundMedia(UTexture* Texture) {
    if (!BackgroundImageTarget || !Texture) return;
    if (auto* Still=Cast<UTexture2D>(Texture)) BackgroundImageTarget->SetBrushFromTexture(Still,false);
    else if (Cast<UMediaTexture>(Texture) && BackgroundMediaPlayback) if (auto* Material=BackgroundMediaPlayback->GetVideoDisplayMaterial()) BackgroundImageTarget->SetBrushFromMaterial(Material);
}
void URecoveredGameInstance::RefreshRecoveredMainMenuBackground() {
    auto* Manager=Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this));
    if (Manager) if (auto* Menu=Cast<URecoveredMainMenu>(Manager->MainMenu)) Menu->RefreshBackground();
}
