#include "RecoveredImportWidget.h"

#include "RecoveredImportFileEntryWidget.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "Misc/Paths.h"
#include "TimerManager.h"

void URecoveredImportWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (UWorld* World = GetWorld()) World->GetTimerManager().ClearAllTimersForObject(this);
    BindControls(true);
    RefreshImportedFileList();
    RefreshPresetDropdown();
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) {
        Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"), Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage"))));
    }
}

void URecoveredImportWidget::NativeDestruct() {
    if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(BatchHandle);
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredImportWidget::BindControls(bool bBind) {
#define BIND(Name, Method) \
    if (auto* Button = Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) { Button->OnClicked.RemoveAll(this); Button->OnClicked.AddUniqueDynamic(this, &URecoveredImportWidget::Method); } \
        else Button->OnClicked.RemoveDynamic(this, &URecoveredImportWidget::Method); \
    }
    BIND("AddButton", OnAddFileClicked)
    BIND("AddDirectoryButton", OnAddDirectoryClicked)
    BIND("ScanButton", OnScanClicked)
    BIND("ClearButton", OnClearClicked)
    BIND("SavePresetButton", OnSavePresetClicked)
    BIND("DeletePresetButton", OnDeletePresetClicked)
    BIND("BackButton", OnBackClicked)
#undef BIND

    if (auto* Back = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")))) {
        if (bBind) {
            Back->OnHovered.RemoveAll(this);
            Back->OnUnhovered.RemoveAll(this);
            Back->OnHovered.AddUniqueDynamic(this, &URecoveredImportWidget::OnBackHovered);
            Back->OnUnhovered.AddUniqueDynamic(this, &URecoveredImportWidget::OnBackUnhovered);
        } else {
            Back->OnHovered.RemoveDynamic(this, &URecoveredImportWidget::OnBackHovered);
            Back->OnUnhovered.RemoveDynamic(this, &URecoveredImportWidget::OnBackUnhovered);
        }
    }

    if (auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")))) {
        if (bBind) {
            Presets->OnSelectionChanged.RemoveAll(this);
            Presets->OnSelectionChanged.AddUniqueDynamic(this, &URecoveredImportWidget::OnPresetSelectionChanged);
        } else {
            Presets->OnSelectionChanged.RemoveDynamic(this, &URecoveredImportWidget::OnPresetSelectionChanged);
        }
    }
}

URecoveredFileImportManager* URecoveredImportWidget::GetImportManager() const {
    if (const auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) return Instance->FileImportManager;
    return nullptr;
}

bool URecoveredImportWidget::AddMediaFile(const FString& FilePath) {
    auto* ImportManager = GetImportManager();
    if (!ImportManager) return false;
    const int32 Before = ImportManager->ImportedFiles.Num();
    ImportManager->AddFiles({FilePath});
    if (ImportManager->ImportedFiles.Num() == Before) return false;
    RefreshImportedFileList();
    return true;
}

int32 URecoveredImportWidget::ScanMediaDirectory(const FString& DirPath) {
    auto* ImportManager = GetImportManager();
    if (!ImportManager || !FPaths::DirectoryExists(DirPath)) return 0;
    const int32 Before = ImportManager->ImportedFiles.Num();
    ImportManager->WatchedDirectories.Add(FPaths::ConvertRelativePathToFull(DirPath));
    ImportManager->ScanCurrentPaths();
    RefreshImportedFileList();
    return ImportManager->ImportedFiles.Num() - Before;
}

void URecoveredImportWidget::ClearImportedMedia() {
    if (auto* ImportManager = GetImportManager()) {
        ImportManager->ImportedFiles.Reset();
        RefreshImportedFileList();
    }
}

int32 URecoveredImportWidget::GetImportedCount() const {
    const auto* ImportManager = GetImportManager();
    return ImportManager ? ImportManager->ImportedFiles.Num() : 0;
}

bool URecoveredImportWidget::RemoveMediaFile(const FString& FilePath) {
    auto* ImportManager = GetImportManager();
    if (!ImportManager || !ImportManager->ImportedFiles.ContainsByPredicate([&FilePath](const FRecoveredImportedFile& Record) {
        return Record.FilePath == FilePath;
    })) return false;
    ImportManager->RemoveFile(FilePath);
    RefreshImportedFileList();
    return true;
}

bool URecoveredImportWidget::SetMediaFileEnabled(const FString& FilePath, bool bEnabled) {
    auto* ImportManager = GetImportManager();
    const FRecoveredImportedFile* Existing = ImportManager ? ImportManager->ImportedFiles.FindByPredicate([&FilePath](const FRecoveredImportedFile& Record) {
        return Record.FilePath == FilePath;
    }) : nullptr;
    if (!Existing) return false;
    ImportManager->SetFileEnabled(FilePath, bEnabled);
    return true;
}

TArray<FRecoveredImportedFile> URecoveredImportWidget::GetImportedFileRecords() const {
    const auto* ImportManager = GetImportManager();
    return ImportManager ? ImportManager->GetImportedFiles() : TArray<FRecoveredImportedFile>();
}

FString URecoveredImportWidget::GetMediaCountText() const {
    const auto* ImportManager = GetImportManager();
    return ImportManager ? ImportManager->GetMediaCountText() : TEXT("FOUND: 0 IMAGES, 0 VIDEOS");
}

FString URecoveredImportWidget::GetLastImportStatus() const {
    return LastImportStatus;
}

void URecoveredImportWidget::RefreshImportedFileList() {
    if (auto* Entries = Cast<UScrollBox>(GetWidgetFromName(TEXT("EntryScrollBox")))) Entries->ClearChildren();
    CurrentFileIndex = 0;
    LastImportStatus = GetMediaCountText();
    if (auto* Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("MediaFoundText")))) Count->SetText(FText::FromString(LastImportStatus));

    if (UWorld* World = GetWorld()) {
        World->GetTimerManager().ClearTimer(BatchHandle);
        World->GetTimerManager().SetTimer(BatchHandle, this, &URecoveredImportWidget::CreateFileBatch, 0.016f, true);
    } else {
        CreateFileBatch();
    }
}

void URecoveredImportWidget::CreateFileBatch() {
    auto* Entries = Cast<UScrollBox>(GetWidgetFromName(TEXT("EntryScrollBox")));
    const TArray<FRecoveredImportedFile> Files = GetImportedFileRecords();
    const int32 LastFileIndex = FMath::Min(CurrentFileIndex + FilesPerFrame - 1, Files.Num() - 1);
    UClass* EntryClass = LoadClass<URecoveredImportFileEntryWidget>(nullptr, TEXT("/Game/Recovery/UI/FileEntry.FileEntry_C"));

    for (int32 Index = CurrentFileIndex; Entries && Index <= LastFileIndex; ++Index) {
        const FRecoveredImportedFile& File = Files[Index];
        URecoveredImportFileEntryWidget* Entry = EntryClass
            ? CreateWidget<URecoveredImportFileEntryWidget>(this, EntryClass)
            : CreateWidget<URecoveredImportFileEntryWidget>(this, URecoveredImportFileEntryWidget::StaticClass());
        if (!Entry) continue;
        Entry->TakeWidget();
        Entry->Configure(this, File.FilePath, File.bEnabled);
        Entries->AddChild(Entry);
    }

    CurrentFileIndex += FilesPerFrame;
    if (CurrentFileIndex >= Files.Num()) {
        if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(BatchHandle);
    }
}

void URecoveredImportWidget::RefreshPresetDropdown() {
    auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")));
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    auto* ImportManager = GetImportManager();
    if (!Presets || !Instance || !Instance->CurrentSave || !ImportManager) return;

    Presets->ClearOptions();
    for (const FString& Name : ImportManager->GetAllPresetNamesFromSaveGame(Instance->CurrentSave)) Presets->AddOption(Name);
}

void URecoveredImportWidget::OnAddFileClicked() {
    auto* ImportManager = GetImportManager();
    if (!ImportManager) return;
    TArray<FString> Selected;
    if (!ImportManager->BrowseForFiles(Selected)) return;
    ImportManager->AddFiles(Selected);
    RefreshImportedFileList();
}

void URecoveredImportWidget::OnAddDirectoryClicked() {
    auto* ImportManager = GetImportManager();
    if (!ImportManager) return;
    FString Directory;
    if (!ImportManager->BrowseForDirectory(Directory)) return;
    ImportManager->WatchedDirectories.Add(Directory);
    RefreshImportedFileList();
}

void URecoveredImportWidget::OnScanClicked() {
    if (auto* ImportManager = GetImportManager()) {
        ImportManager->ScanCurrentPaths();
        PlayRecoveredAnimation(TEXT("ScanFilesClick"));
        RefreshImportedFileList();
    }
}

void URecoveredImportWidget::OnClearClicked() {
    auto* ImportManager = GetImportManager();
    if (!ImportManager) return;
    ImportManager->ImportedFiles.Reset();
    PlayRecoveredAnimation(TEXT("ClearFilesClick"));
    RefreshImportedFileList();
    if (auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")))) Presets->ClearSelection();
}

void URecoveredImportWidget::OnSavePresetClicked() {
    PlayRecoveredAnimation(TEXT("SavePresetClick"));
    auto* NameBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PresetSaveNameTextBox")));
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    auto* ImportManager = GetImportManager();
    if (!NameBox || !Instance || !Instance->CurrentSave || !ImportManager || NameBox->GetText().IsEmpty()) return;

    ImportManager->SavePresetToSaveGame(NameBox->GetText().ToString(), Instance->CurrentSave);
    RefreshPresetDropdown();
    NameBox->SetText(FText::GetEmpty());
    Instance->SaveRecoveredState();
}

void URecoveredImportWidget::OnDeletePresetClicked() {
    PlayRecoveredAnimation(TEXT("DeletePresetClick"));
    auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")));
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    auto* ImportManager = GetImportManager();
    if (!Presets || !Instance || !Instance->CurrentSave || !ImportManager) return;

    const FString Name = Presets->GetSelectedOption();
    if (Name.IsEmpty()) return;
    ImportManager->DeletePresetFromSaveGame(Name, Instance->CurrentSave);
    RefreshPresetDropdown();
    RefreshImportedFileList();
}

void URecoveredImportWidget::OnBackClicked() {
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) Instance->RefreshRecoveredMainMenuBackground();
    RemoveFromParent();
}

void URecoveredImportWidget::OnBackHovered() {
    PlayRecoveredAnimation(TEXT("BackButtonHover"));
}

void URecoveredImportWidget::OnBackUnhovered() {
    PlayRecoveredAnimation(TEXT("BackButtonUnhover"));
}

void URecoveredImportWidget::OnPresetSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType) {
    (void)SelectionType;
    if (SelectedItem.IsEmpty()) return;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    auto* ImportManager = GetImportManager();
    if (!Instance || !Instance->CurrentSave || !ImportManager) return;
    ImportManager->LoadPresetFromSaveGame(SelectedItem, Instance->CurrentSave);
    RefreshImportedFileList();
}
