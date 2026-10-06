#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredImportWidget.generated.h"

class URecoveredImportWidget;

/** Carries the source path for a dynamically created import-list remove button. */
UCLASS()
class COCKHERORECOVERED_API URecoveredImportRemoveForward : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredImportWidget> Owner;
    UPROPERTY() FString FilePath;
    UFUNCTION() void RemoveFile();
};

// Media import UI recovered from ImportMenuWidget.  The original widget exposes
// file/directory pickers, a watched-directory scan, a removable list, and named
// presets.  This adapter keeps the original tree and supplies the missing native
// import manager using recovery-owned state only.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredImportWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
    friend class FRecoveredImportFailureTest;
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Import") bool AddMediaFile(const FString& FilePath);
    UFUNCTION(BlueprintCallable, Category="Recovered Import") int32 ScanMediaDirectory(const FString& DirPath);
    UFUNCTION(BlueprintCallable, Category="Recovered Import") void ClearImportedMedia();
    UFUNCTION(BlueprintPure, Category="Recovered Import") int32 GetImportedCount() const;
    UFUNCTION(BlueprintCallable, Category="Recovered Import") bool RemoveMediaFile(const FString& FilePath);
    UFUNCTION(BlueprintPure, Category="Recovered Import") FString GetLastImportStatus() const;
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    void BindControls(bool bBind);
    void LoadPersistedImportState();
    void PersistImportState();
    void RefreshImportedFileList();
    void RefreshPresetDropdown();
    bool RebuildImportedMediaDeck();
    bool WriteImportedManifest(FString& OutManifestPath) const;
    static bool IsSupportedMediaFile(const FString& FilePath);
    void SetImportStatus(const FString& Status);
    UFUNCTION() void OnAddFileClicked();
    UFUNCTION() void OnAddDirectoryClicked();
    UFUNCTION() void OnScanClicked();
    UFUNCTION() void OnClearClicked();
    UFUNCTION() void OnSavePresetClicked();
    UFUNCTION() void OnDeletePresetClicked();
    UFUNCTION() void OnBackClicked();
    UFUNCTION() void OnPresetSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
    UPROPERTY() TArray<FString> ImportedFiles;
    UPROPERTY() TArray<FString> WatchedDirectories;
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredImportRemoveForward>> RemoveForwarders;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Import") FString LastImportStatus;
};
