#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredImportWidget.generated.h"

// Media import UI: add files, scan directories, clear imported media.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredImportWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Import") bool AddMediaFile(const FString& FilePath);
    UFUNCTION(BlueprintCallable, Category="Recovered Import") int32 ScanMediaDirectory(const FString& DirPath);
    UFUNCTION(BlueprintCallable, Category="Recovered Import") void ClearImportedMedia();
    UFUNCTION(BlueprintPure, Category="Recovered Import") int32 GetImportedCount() const;
protected:
    virtual void NativeConstruct() override;
    void BindControls(bool bBind);
    UFUNCTION() void OnAddFileClicked();
    UFUNCTION() void OnScanClicked();
    UFUNCTION() void OnClearClicked();
    UPROPERTY() TArray<FString> ImportedFiles;
};
