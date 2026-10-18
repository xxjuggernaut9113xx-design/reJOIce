#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredBeatmap.generated.h"

// Newer native ParseBeatmapJson contract (0x148302440), reflected schemas and
// shipped JSON. Times remain authored seconds; metadata Offset is not applied.
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatmapMetadata {
    GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Title;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Artist;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Author;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Difficulty;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString AudioFile;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Duration = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Bpm = 120;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Offset = 0;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatmapBeat {
    GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Time = 0;
    // Canonical native type: stroke/rest/accent. Unknown/missing types become stroke.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Type = TEXT("stroke");
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Duration = 0;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatmapEvent {
    GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Time = 0;
    // Canonical native type; unknown/missing types become custom, media_switch aliases media_change.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Type = TEXT("custom");
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FString Value;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") double Duration = 0;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredBeatmapData {
    GENERATED_BODY()
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") FRecoveredBeatmapMetadata Meta;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") TArray<FRecoveredBeatmapBeat> Beats;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|Beatmap") TArray<FRecoveredBeatmapEvent> Events;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredBeatmapLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    // Failure leaves OutData unchanged. Pure parsing never accesses audio files.
    UFUNCTION(BlueprintCallable, Category="Recovered|Beatmap") static bool ParseBeatmapJson(const FString& Json, FRecoveredBeatmapData& OutData, FString& OutError);
    // Resolves an existing audio file inside the selected beatmap's directory.
    // Does not decode, play, or modify either file. Failure leaves both outputs unchanged.
    UFUNCTION(BlueprintCallable, Category="Recovered|Beatmap") static bool LoadBeatmapFile(const FString& JsonPath, FRecoveredBeatmapData& OutData, FString& OutAudioPath, FString& OutError);
};
