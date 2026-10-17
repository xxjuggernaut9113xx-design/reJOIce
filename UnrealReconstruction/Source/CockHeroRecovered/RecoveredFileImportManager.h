#pragma once

#include "CoreMinimal.h"
#include "RecoveredMedia.h"
#include "UObject/Object.h"
#include "RecoveredFileImportManager.generated.h"

class URecoveredSaveGame;

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredImportedFile {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Import")
    FString FilePath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Import")
    bool bEnabled = true;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredFileImportPreset {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Import")
    FString PresetName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Import")
    TArray<FString> WatchedDirectories;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Import")
    TArray<FRecoveredImportedFile> ImportedFiles;
};

/**
 * Native reconstruction of the source FileImportManager. The manager owns
 * import selection, enabled-state, watched directories, and saved presets.
 */
UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredFileImportManager : public UObject {
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Import")
    TArray<FRecoveredImportedFile> ImportedFiles;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Import")
    TArray<FString> WatchedDirectories;

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void AddFiles(const TArray<FString>& Files);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool BrowseForDirectory(FString& OutDirectory);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool BrowseForFiles(TArray<FString>& OutFiles);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void ClearAllData();

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    int32 GetImageCount() const;

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    int32 GetVideoCount() const;

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    FString GetMediaCountText() const;

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    TArray<FRecoveredImportedFile> GetImportedFiles() const;

    TArray<FRecoveredMediaEntry> GetImportedMediaEntries() const;

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void RemoveFile(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void ScanCurrentPaths();

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void SetFileEnabled(const FString& FilePath, bool bEnabled);

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    bool VerifyFileExists(const FString& FilePath) const;

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool SavePresetToSaveGame(const FString& PresetName, URecoveredSaveGame* SaveGame);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool LoadPresetFromSaveGame(const FString& PresetName, URecoveredSaveGame* SaveGame);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool DeletePresetFromSaveGame(const FString& PresetName, URecoveredSaveGame* SaveGame);

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    TArray<FString> GetAllPresetNamesFromSaveGame(URecoveredSaveGame* SaveGame) const;

    bool LoadFromSave(URecoveredSaveGame* SaveGame);
    bool SaveToSave(URecoveredSaveGame* SaveGame) const;

    static bool IsSupportedMediaFile(const FString& FilePath);
    static bool IsImageFile(const FString& FilePath);
    static bool IsVideoFile(const FString& FilePath);

private:
    UPROPERTY()
    TArray<FRecoveredFileImportPreset> Presets;

    TWeakObjectPtr<URecoveredSaveGame> LoadedSave;

    static FString NormalizePath(const FString& FilePath);
    static bool IsValidPresetName(const FString& PresetName);
    static bool ContainsFile(const TArray<FRecoveredImportedFile>& Files, const FString& FilePath);
    void AddFileIfMissing(const FString& FilePath);
    void LoadLegacyState(URecoveredSaveGame* SaveGame);
    bool EnsureSaveLoaded(URecoveredSaveGame* SaveGame);
};