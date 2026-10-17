#pragma once

#include "CoreMinimal.h"
#include "RecoveredFileImportManager.h"
#include "RecoveredMenu.h"
#include "TimerManager.h"
#include "RecoveredImportWidget.generated.h"

class URecoveredFileImportManager;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredImportWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool AddMediaFile(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    int32 ScanMediaDirectory(const FString& DirPath);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void ClearImportedMedia();

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    int32 GetImportedCount() const;

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool RemoveMediaFile(const FString& FilePath);

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    bool SetMediaFileEnabled(const FString& FilePath, bool bEnabled);

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    TArray<FRecoveredImportedFile> GetImportedFileRecords() const;

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    FString GetMediaCountText() const;

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    FString GetLastImportStatus() const;

    UFUNCTION(BlueprintPure, Category="Recovered Import")
    int32 GetFilesPerFrame() const { return FilesPerFrame; }

    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void CreateFileBatch();

    virtual void NativeConstruct() override;

protected:
    virtual void NativeDestruct() override;

    void BindControls(bool bBind);
    void RefreshImportedFileList();
    void RefreshPresetDropdown();
    URecoveredFileImportManager* GetImportManager() const;

    UFUNCTION() void OnAddFileClicked();
    UFUNCTION() void OnAddDirectoryClicked();
    UFUNCTION() void OnScanClicked();
    UFUNCTION() void OnClearClicked();
    UFUNCTION() void OnSavePresetClicked();
    UFUNCTION() void OnDeletePresetClicked();
    UFUNCTION() void OnBackClicked();
    UFUNCTION() void OnBackHovered();
    UFUNCTION() void OnBackUnhovered();
    UFUNCTION() void OnPresetSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Import")
    FString LastImportStatus;

    UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category="Recovered Import")
    int32 CurrentFileIndex = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Recovered Import")
    int32 FilesPerFrame = 10;

    FTimerHandle BatchHandle;
};
