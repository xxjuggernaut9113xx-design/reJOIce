#include "RecoveredImportWidget.h"
#include "RecoveredMedia.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include <commdlg.h>
#include <ShlObj.h>
#endif

namespace {
constexpr const TCHAR* ImportedFilesKey = TEXT("RecoveryImportedFiles");
constexpr const TCHAR* WatchedDirectoriesKey = TEXT("RecoveryImportDirectories");
constexpr const TCHAR* PresetNamesKey = TEXT("RecoveryImportPresetNames");
constexpr const TCHAR* PresetFilesPrefix = TEXT("RecoveryImportPresetFiles_");
constexpr const TCHAR* PresetDirectoriesPrefix = TEXT("RecoveryImportPresetDirectories_");
constexpr const TCHAR* BaseManifestKey = TEXT("RecoveryImportBaseManifest");

FString PresetKey(const TCHAR* Prefix, const FString& PresetName) {
    return FString(Prefix) + PresetName;
}

#if PLATFORM_WINDOWS
bool BrowseForFiles(TArray<FString>& OutFiles) {
    OutFiles.Reset();
    TArray<wchar_t> Buffer;
    Buffer.SetNumZeroed(32768);
    OPENFILENAMEW Dialog{};
    Dialog.lStructSize = sizeof(Dialog);
    Dialog.lpstrFilter = L"Media Files\0*.mp4;*.webm;*.mkv;*.png;*.jpg;*.jpeg\0All Files\0*.*\0\0";
    Dialog.lpstrFile = Buffer.GetData();
    Dialog.nMaxFile = static_cast<DWORD>(Buffer.Num());
    Dialog.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (!GetOpenFileNameW(&Dialog)) return false;

    const wchar_t* First = Buffer.GetData();
    const wchar_t* Next = First + FCStringWide::Strlen(First) + 1;
    if (*Next == L'\0') {
        OutFiles.Add(FString(First));
        return true;
    }
    const FString Directory(First);
    while (*Next != L'\0') {
        OutFiles.Add(FPaths::Combine(Directory, FString(Next)));
        Next += FCStringWide::Strlen(Next) + 1;
    }
    return !OutFiles.IsEmpty();
}

bool BrowseForDirectory(FString& OutDirectory) {
    OutDirectory.Reset();
    BROWSEINFOW Dialog{};
    Dialog.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    Dialog.lpszTitle = L"Choose a media directory";
    PIDLIST_ABSOLUTE Item = SHBrowseForFolderW(&Dialog);
    if (!Item) return false;
    wchar_t Path[MAX_PATH]{};
    const bool bResolved = SHGetPathFromIDListW(Item, Path) != 0;
    CoTaskMemFree(Item);
    if (bResolved) OutDirectory = FString(Path);
    return bResolved;
}
#endif
}

void URecoveredImportWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
    LoadPersistedImportState();
    RefreshPresetDropdown();
    RefreshImportedFileList();
    if (!ImportedFiles.IsEmpty()) RebuildImportedMediaDeck();
}

void URecoveredImportWidget::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredImportWidget::BindControls(bool bBind) {
#define BIND(Name, Method) \
    if (auto* B = Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) B->OnClicked.AddUniqueDynamic(this, &URecoveredImportWidget::Method); \
        else B->OnClicked.RemoveDynamic(this, &URecoveredImportWidget::Method); \
    }
    BIND("AddButton", OnAddFileClicked)
    BIND("AddDirectoryButton", OnAddDirectoryClicked)
    BIND("ScanButton", OnScanClicked)
    BIND("ClearButton", OnClearClicked)
    BIND("SavePresetButton", OnSavePresetClicked)
    BIND("DeletePresetButton", OnDeletePresetClicked)
    BIND("BackButton", OnBackClicked)
#undef BIND
    if (auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")))) {
        if (bBind) Presets->OnSelectionChanged.AddUniqueDynamic(this, &URecoveredImportWidget::OnPresetSelectionChanged);
        else Presets->OnSelectionChanged.RemoveAll(this);
    }
}

bool URecoveredImportWidget::AddMediaFile(const FString& FilePath) {
    if (!IsSupportedMediaFile(FilePath)) return false;
    const FString Canonical = FPaths::ConvertRelativePathToFull(FilePath);
    if (ImportedFiles.ContainsByPredicate([&Canonical](const FString& Existing) { return Existing.Equals(Canonical, ESearchCase::IgnoreCase); })) return false;
    ImportedFiles.Add(Canonical);
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
    PersistImportState();
    RebuildImportedMediaDeck();
    RefreshImportedFileList();
}

int32 URecoveredImportWidget::GetImportedCount() const {
    return ImportedFiles.Num();
}

bool URecoveredImportWidget::RemoveMediaFile(const FString& FilePath) {
    const int32 Removed = ImportedFiles.RemoveAll([&FilePath](const FString& Existing) { return Existing.Equals(FilePath, ESearchCase::IgnoreCase); });
    if (Removed == 0) return false;
    PersistImportState();
    RebuildImportedMediaDeck();
    RefreshImportedFileList();
    return true;
}

FString URecoveredImportWidget::GetLastImportStatus() const {
    return LastImportStatus;
}

bool URecoveredImportWidget::IsSupportedMediaFile(const FString& FilePath) {
    if (FilePath.IsEmpty() || !FPaths::FileExists(FilePath)) return false;
    static const TSet<FString> Valid = { TEXT("mp4"), TEXT("webm"), TEXT("mkv"), TEXT("png"), TEXT("jpg"), TEXT("jpeg") };
    return Valid.Contains(FPaths::GetExtension(FilePath).ToLower());
}

void URecoveredImportWidget::LoadPersistedImportState() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    ImportedFiles.Reset();
    for (const FString& Path : Instance->CurrentSave->GetStringArraySetting(ImportedFilesKey)) AddMediaFile(Path);
    WatchedDirectories.Reset();
    for (const FString& Directory : Instance->CurrentSave->GetStringArraySetting(WatchedDirectoriesKey)) {
        if (FPaths::DirectoryExists(Directory)) WatchedDirectories.AddUnique(FPaths::ConvertRelativePathToFull(Directory));
    }
}

void URecoveredImportWidget::PersistImportState() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    const bool bFilesSaved = Instance->CurrentSave->SetStringArraySetting(ImportedFilesKey, ImportedFiles);
    const bool bDirectoriesSaved = Instance->CurrentSave->SetStringArraySetting(WatchedDirectoriesKey, WatchedDirectories);
    if (bFilesSaved || bDirectoriesSaved) Instance->SaveRecoveredState();
}

void URecoveredImportWidget::SetImportStatus(const FString& Status) {
    LastImportStatus = Status;
    if (auto* Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("MediaFoundText")))) Count->SetText(FText::FromString(Status));
}

void URecoveredImportWidget::RefreshImportedFileList() {
    auto* Entries = Cast<UScrollBox>(GetWidgetFromName(TEXT("EntryScrollBox")));
    if (!Entries) return;
    Entries->ClearChildren();
    RemoveForwarders.Reset();
    for (const FString& FilePath : ImportedFiles) {
        auto* Row = NewObject<UHorizontalBox>(this);
        auto* Label = NewObject<UTextBlock>(this);
        Label->SetText(FText::FromString(FPaths::GetCleanFilename(FilePath)));
        Label->SetToolTipText(FText::FromString(FilePath));
        auto* Remove = NewObject<UButton>(this);
        auto* RemoveLabel = NewObject<UTextBlock>(this);
        RemoveLabel->SetText(FText::FromString(TEXT("Remove")));
        Remove->SetContent(RemoveLabel);
        auto* Forward = NewObject<URecoveredImportRemoveForward>(this);
        Forward->Owner = this;
        Forward->FilePath = FilePath;
        Remove->OnClicked.AddUniqueDynamic(Forward, &URecoveredImportRemoveForward::RemoveFile);
        RemoveForwarders.Add(Forward);
        Row->AddChildToHorizontalBox(Label);
        Row->AddChildToHorizontalBox(Remove);
        Entries->AddChild(Row);
    }
    if (LastImportStatus.IsEmpty()) SetImportStatus(FString::Printf(TEXT("%d media file%s found"), ImportedFiles.Num(), ImportedFiles.Num() == 1 ? TEXT("") : TEXT("s")));
}

void URecoveredImportWidget::RefreshPresetDropdown() {
    auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")));
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Presets || !Instance || !Instance->CurrentSave) return;
    const FString Selected = Presets->GetSelectedOption();
    Presets->ClearOptions();
    TArray<FString> Names = Instance->CurrentSave->GetStringArraySetting(PresetNamesKey);
    Names.Sort();
    for (const FString& Name : Names) if (!Name.TrimStartAndEnd().IsEmpty()) Presets->AddOption(Name);
    if (!Selected.IsEmpty() && Names.Contains(Selected)) Presets->SetSelectedOption(Selected);
}

bool URecoveredImportWidget::WriteImportedManifest(FString& OutManifestPath) const {
    OutManifestPath.Reset();
    const FString Directory = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("RecoveryImports"));
    if (!IFileManager::Get().MakeDirectory(*Directory, true)) return false;
    TArray<TSharedPtr<FJsonValue>> Media;
    for (const FString& FilePath : ImportedFiles) {
        if (!IsSupportedMediaFile(FilePath)) continue;
        const TSharedRef<FJsonObject> Entry = MakeShared<FJsonObject>();
        Entry->SetStringField(TEXT("file"), FPaths::ConvertRelativePathToFull(FilePath));
        Entry->SetStringField(TEXT("type"), FPaths::GetExtension(FilePath).ToLower());
        Media.Add(MakeShared<FJsonValueObject>(Entry));
    }
    if (Media.IsEmpty()) return false;
    const TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetArrayField(TEXT("media"), Media);
    FString Json;
    const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Json);
    if (!FJsonSerializer::Serialize(Root, Writer) || !FFileHelper::SaveStringToFile(Json, *FPaths::Combine(Directory, TEXT("imported-media-manifest.json")))) return false;
    OutManifestPath = FPaths::Combine(Directory, TEXT("imported-media-manifest.json"));
    return true;
}

bool URecoveredImportWidget::RebuildImportedMediaDeck() {
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Manager || !Instance || !Instance->CurrentSave) {
        SetImportStatus(TEXT("Media import is unavailable until the recovery session is initialized"));
        return false;
    }
    if (ImportedFiles.IsEmpty()) {
        const FString BaseManifest = Instance->CurrentSave->GetStringSetting(BaseManifestKey, TEXT(""));
        if (BaseManifest.IsEmpty() || !FPaths::FileExists(BaseManifest)) {
            SetImportStatus(TEXT("Import list cleared, but base media is unavailable; current media remains loaded"));
            return false;
        }
        const bool bLoaded = Manager->LoadMediaPack(BaseManifest, Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags")));
        if (bLoaded) Manager->MediaManifestPath = BaseManifest;
        SetImportStatus(bLoaded ? TEXT("Import list cleared; base media restored") : Manager->LastSessionError);
        return bLoaded;
    }
    FString ManifestPath;
    if (!WriteImportedManifest(ManifestPath)) {
        SetImportStatus(TEXT("Unable to create recovered import manifest"));
        return false;
    }
    const FString PreviousManifest = Manager->MediaManifestPath;
    const bool bLoaded = Manager->LoadMediaPack(ManifestPath, Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags")));
    if (bLoaded) {
        Manager->MediaManifestPath = ManifestPath;
        if (!PreviousManifest.IsEmpty() && !FPaths::IsSamePath(PreviousManifest, ManifestPath)) {
            Instance->CurrentSave->SetStringSetting(BaseManifestKey, PreviousManifest);
            if (!Instance->SaveRecoveredState()) {
                SetImportStatus(TEXT("Imported media loaded, but the base-media restore path could not be saved"));
                return false;
            }
        }
    }
    SetImportStatus(bLoaded ? FString::Printf(TEXT("%d imported media file%s ready"), ImportedFiles.Num(), ImportedFiles.Num() == 1 ? TEXT("") : TEXT("s")) : Manager->LastSessionError);
    return bLoaded;
}

void URecoveredImportWidget::OnAddFileClicked() {
    TArray<FString> Selected;
#if PLATFORM_WINDOWS
    if (!BrowseForFiles(Selected)) return;
#else
    SetImportStatus(TEXT("Native file picking is only available in the Windows recovery build"));
    return;
#endif
    int32 Added = 0;
    for (const FString& FilePath : Selected) Added += AddMediaFile(FilePath) ? 1 : 0;
    PersistImportState();
    const bool bLoaded = RebuildImportedMediaDeck();
    RefreshImportedFileList();
    if (bLoaded && Added == 0) SetImportStatus(TEXT("No new supported media files were selected"));
}

void URecoveredImportWidget::OnAddDirectoryClicked() {
    FString Directory;
#if PLATFORM_WINDOWS
    if (!BrowseForDirectory(Directory)) return;
#else
    SetImportStatus(TEXT("Native directory picking is only available in the Windows recovery build"));
    return;
#endif
    Directory = FPaths::ConvertRelativePathToFull(Directory);
    WatchedDirectories.AddUnique(Directory);
    const int32 Added = ScanMediaDirectory(Directory);
    PersistImportState();
    const bool bLoaded = RebuildImportedMediaDeck();
    RefreshImportedFileList();
    if (bLoaded && Added == 0) SetImportStatus(TEXT("No supported media files found in selected directory"));
}

void URecoveredImportWidget::OnScanClicked() {
    if (WatchedDirectories.IsEmpty()) {
        SetImportStatus(TEXT("Add a media directory before scanning"));
        return;
    }
    int32 Added = 0;
    for (const FString& Directory : WatchedDirectories) Added += ScanMediaDirectory(Directory);
    PersistImportState();
    const bool bLoaded = RebuildImportedMediaDeck();
    RefreshImportedFileList();
    if (bLoaded && Added == 0) SetImportStatus(TEXT("Scan completed with no new supported media files"));
}

void URecoveredImportWidget::OnClearClicked() {
    ClearImportedMedia();
}

void URecoveredImportWidget::OnSavePresetClicked() {
    auto* NameBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("PresetSaveNameTextBox")));
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!NameBox || !Instance || !Instance->CurrentSave) return;
    const FString Name = NameBox->GetText().ToString().TrimStartAndEnd();
    if (Name.IsEmpty()) {
        SetImportStatus(TEXT("Enter a preset name before saving"));
        return;
    }
    TArray<FString> Names = Instance->CurrentSave->GetStringArraySetting(PresetNamesKey);
    Names.AddUnique(Name);
    bool bSaved = Instance->CurrentSave->SetStringArraySetting(PresetNamesKey, Names)
        && Instance->CurrentSave->SetStringArraySetting(PresetKey(PresetFilesPrefix, Name), ImportedFiles)
        && Instance->CurrentSave->SetStringArraySetting(PresetKey(PresetDirectoriesPrefix, Name), WatchedDirectories);
    if (bSaved) bSaved = Instance->SaveRecoveredState();
    RefreshPresetDropdown();
    if (auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")))) Presets->SetSelectedOption(Name);
    SetImportStatus(bSaved ? TEXT("Import preset saved") : TEXT("Failed to save import preset"));
}

void URecoveredImportWidget::OnDeletePresetClicked() {
    auto* Presets = Cast<UComboBoxString>(GetWidgetFromName(TEXT("PresetsComboBox")));
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Presets || !Instance || !Instance->CurrentSave) return;
    const FString Name = Presets->GetSelectedOption();
    if (Name.IsEmpty()) {
        SetImportStatus(TEXT("Select an import preset before deleting"));
        return;
    }
    TArray<FString> Names = Instance->CurrentSave->GetStringArraySetting(PresetNamesKey);
    Names.Remove(Name);
    bool bSaved = Instance->CurrentSave->SetStringArraySetting(PresetNamesKey, Names)
        && Instance->CurrentSave->SetStringArraySetting(PresetKey(PresetFilesPrefix, Name), {})
        && Instance->CurrentSave->SetStringArraySetting(PresetKey(PresetDirectoriesPrefix, Name), {});
    if (bSaved) bSaved = Instance->SaveRecoveredState();
    RefreshPresetDropdown();
    SetImportStatus(bSaved ? TEXT("Import preset deleted") : TEXT("Failed to delete import preset"));
}

void URecoveredImportWidget::OnBackClicked() {
    RemoveFromParent();
}

void URecoveredImportWidget::OnPresetSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType) {
    if (SelectionType == ESelectInfo::Direct || SelectedItem.IsEmpty()) return;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    ImportedFiles.Reset();
    for (const FString& FilePath : Instance->CurrentSave->GetStringArraySetting(PresetKey(PresetFilesPrefix, SelectedItem))) AddMediaFile(FilePath);
    WatchedDirectories.Reset();
    for (const FString& Directory : Instance->CurrentSave->GetStringArraySetting(PresetKey(PresetDirectoriesPrefix, SelectedItem))) {
        if (FPaths::DirectoryExists(Directory)) WatchedDirectories.AddUnique(FPaths::ConvertRelativePathToFull(Directory));
    }
    PersistImportState();
    RebuildImportedMediaDeck();
    RefreshImportedFileList();
}

void URecoveredImportRemoveForward::RemoveFile() {
    if (Owner) Owner->RemoveMediaFile(FilePath);
}
