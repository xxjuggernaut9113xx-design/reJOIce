#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredMedia.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredMediaEntry {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString File;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> Tags;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString FullPath;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredMediaDecks {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Slow;
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Medium;
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Fast;
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Cum;
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Succubus;
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Ass;
    UPROPERTY(BlueprintReadOnly) TArray<FRecoveredMediaEntry> Boobs;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredMediaLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Media") static TArray<FString> ParseFilenameTags(const FString& Filename);
    UFUNCTION(BlueprintPure, Category="Recovered|Media") static FRecoveredMediaDecks FilterMedia(const TArray<FRecoveredMediaEntry>& Entries, const TArray<FString>& ExcludedTags, bool bAssPreference, bool bBoobsPreference, bool bFeetPreference);
    UFUNCTION(BlueprintCallable, Category="Recovered|Media") static bool ReadPackManifest(const FString& ManifestPath, TArray<FRecoveredMediaEntry>& Entries, FString& Error);
};
