#include "RecoveredImportWidget.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"

void URecoveredImportWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
}

void URecoveredImportWidget::BindControls(bool bBind) {
#define BIND(Name, Method) \
    if (auto* B = Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) B->OnClicked.AddUniqueDynamic(this, &URecoveredImportWidget::Method); \
        else B->OnClicked.RemoveDynamic(this, &URecoveredImportWidget::Method); \
    }
    BIND("AddFileButton", OnAddFileClicked)
    BIND("ScanButton", OnScanClicked)
    BIND("ClearButton", OnClearClicked)
#undef BIND
}

bool URecoveredImportWidget::AddMediaFile(const FString& FilePath) {
    if (FilePath.IsEmpty() || !FPaths::FileExists(FilePath)) return false;
    const FString Ext = FPaths::GetExtension(FilePath).ToLower();
    static const TSet<FString> Valid = { TEXT("mp4"), TEXT("webm"), TEXT("mkv"), TEXT("png"), TEXT("jpg"), TEXT("jpeg") };
    if (!Valid.Contains(Ext)) return false;
    if (ImportedFiles.Contains(FilePath)) return false;
    ImportedFiles.Add(FilePath);
    return true;
}

int32 URecoveredImportWidget::ScanMediaDirectory(const FString& DirPath) {
    if (!FPaths::DirectoryExists(DirPath)) return 0;
    TArray<FString> Found;
    IFileManager::Get().FindFilesRecursive(Found, *DirPath, TEXT("*.*"), true, false);
    int32 Added = 0;
    for (const FString& F : Found) {
        if (AddMediaFile(F)) Added++;
    }
    return Added;
}

void URecoveredImportWidget::ClearImportedMedia() {
    ImportedFiles.Reset();
}

int32 URecoveredImportWidget::GetImportedCount() const {
    return ImportedFiles.Num();
}

void URecoveredImportWidget::OnAddFileClicked() {
    if (auto* Box = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("FilePathBox")))) {
        AddMediaFile(Box->GetText().ToString());
    }
}

void URecoveredImportWidget::OnScanClicked() {
    if (auto* Box = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("DirPathBox")))) {
        ScanMediaDirectory(Box->GetText().ToString());
    }
}

void URecoveredImportWidget::OnClearClicked() {
    ClearImportedMedia();
}
