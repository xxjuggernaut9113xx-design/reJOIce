#pragma once
#include "CoreMinimal.h"
#include "RecoveredMedia.h"
#include "RecoveredMediaPlayback.generated.h"
class UMediaPlayer;
class UMediaTexture;
class UTexture;
class UMaterialInstanceDynamic;
class UScaleBox;
UENUM(BlueprintType)
enum class ERecoveredCropMode : uint8 {
    Auto = 0,
    Fill = 1,
    Fit = 2,
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredMediaReady, UTexture*, Texture);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredMediaError, const FString&, Error);

// Editor/runtime adapter for existing files; original transition, audio, and sync logic remains separate.
UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredMediaPlayback : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UMediaPlayer> MediaPlayer;
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UMediaTexture> VideoTexture;
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UTexture> CurrentTexture;
    UPROPERTY(BlueprintReadOnly) TObjectPtr<UMaterialInstanceDynamic> VideoMaterial;
    UPROPERTY(BlueprintReadOnly) FRecoveredMediaEntry CurrentEntry;
    UPROPERTY(BlueprintAssignable) FRecoveredMediaReady OnMediaReady;
    UPROPERTY(BlueprintAssignable) FRecoveredMediaError OnMediaError;
    UPROPERTY(BlueprintReadWrite) bool bLooping = true;
    UPROPERTY(BlueprintReadOnly, Category="Recovered|Media") ERecoveredCropMode CropMode = ERecoveredCropMode::Auto;
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetLooping(bool bEnabled);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetScaleBoxReference(UScaleBox* InScaleBox);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetCropMode(ERecoveredCropMode InCropMode);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") bool OpenEntry(const FRecoveredMediaEntry& Entry);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void StopPlayback();
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") void SetPaused(bool bPaused);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") bool SetPlaybackRate(float Rate);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") UMaterialInstanceDynamic* GetVideoDisplayMaterial();
    virtual void BeginDestroy() override;
private:
    void ApplyCropMode();
    float GetContentAspectRatio() const;
    UFUNCTION() void HandleOpened(FString Url);
    UFUNCTION() void HandleFailed(FString Url);
    TWeakObjectPtr<UScaleBox> ScaleBox;
};
