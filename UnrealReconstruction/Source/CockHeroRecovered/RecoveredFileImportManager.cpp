#include "RecoveredFileImportManager.h"

#include "RecoveredRules.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

#if PLATFORM_WINDOWS
#include "Windows/WindowsHWrapper.h"
#include <commdlg.h>
#include <ShlObj.h>
#endif

namespace {
constexpr const TCHAR* ImportStateKey = TEXT("RecoveryFileImportStateV2");
constexpr const TCHAR* LegacyImportedFilesKey = TEXT("RecoveryImportedFiles");
constexpr const TCHAR* LegacyDirectoriesKey = TEXT("RecoveryImportDirectories");
constexpr const TCHAR* LegacyPresetNamesKey = TEXT("RecoveryImportPresetNames");
constexpr const TCHAR* LegacyPresetFilesPrefix = TEXT("RecoveryImportPresetFiles_");
constexpr const TCHAR* LegacyPresetDirectoriesPrefix = TEXT("RecoveryImportPresetDirectories_");
constexpr int32 ImportStateVersion = 2;

bool ReadFileRecord(const TSharedPtr<FJsonObject>& Object, FRecoveredImportedFile& OutRecord) {
    if (!Object.IsValid() || !Object->TryGetStringField(TEXT("path"), OutRecord.FilePath) || OutRecord.FilePath.IsEmpty()) return false;
    Object->TryGetBoolField(TEXT("enabled"), OutRecord.bEnabled);
    return URecoveredFileImportManager::IsSupportedMediaFile(OutRecord.FilePath);
}

TSharedPtr<FJsonObject> WriteFileRecord(const FRecoveredImportedFile& Record) {
    const TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
    Object->SetStringField(TEXT("path"), Record.FilePath);
    Object->SetBoolField(TEXT("enabled"), Record.bEnabled);
    return Object;
}

void ReadDirectories(const TArray<TSharedPtr<FJsonValue>>* Values, TArray<FString>& OutDirectories) {
    if (!Values) return;
    for (const TSharedPtr<FJsonValue>& Value : *Values) {
        FString Directory;
        if (Value.IsValid() && Value->TryGetString(Directory) && !Directory.IsEmpty()) {
            OutDirectories.AddUnique(FPaths::ConvertRelativePathToFull(Directory));
        }
    }
}

TArray<TSharedPtr<FJsonValue>> WriteDirectories(const TArray<FString>& Directories) {
    TArray<TSharedPtr<FJsonValue>> Result;
    Result.Reserve(Directories.Num());
    for (const FString& Directory : Directories) Result.Add(MakeShared<FJsonValueString>(Directory));
    return Result;
}

void ReadFiles(const TArray<TSharedPtr<FJsonValue>>* Values, TArray<FRecoveredImportedFile>& OutFiles) {
    if (!Values) return;
    for (const TSharedPtr<FJsonValue>& Value : *Values) {
        FRecoveredImportedFile Record;
        if (Value.IsValid() && ReadFileRecord(Value->AsObject(), Record) &&
            !OutFiles.ContainsByPredicate([&Record](const FRecoveredImportedFile& Existing) { return Existing.FilePath == Record.FilePath; })) {
            OutFiles.Add(MoveTemp(Record));
        }
    }
}

TArray<TSharedPtr<FJsonValue>> WriteFiles(const TArray<FRecoveredImportedFile>& Files) {
    TArray<TSharedPtr<FJsonValue>> Result;
    Result.Reserve(Files.Num());
    for (const FRecoveredImportedFile& File : Files) Result.Add(MakeShared<FJsonValueObject>(WriteFileRecord(File)));
    return Result;
}
}

bool URecoveredFileImportManager::IsImageFile(const FString& FilePath) {
    static const TSet<FString> ImageExtensions = {
        TEXT("png"), TEXT("jpg"), TEXT("jpeg"), TEXT("bmp"), TEXT("gif"), TEXT("webp")
    };
    return ImageExtensions.Contains(FPaths::GetExtension(FilePath, false).ToLower());
}

bool URecoveredFileImportManager::IsVideoFile(const FString& FilePath) {
    static const TSet<FString> VideoExtensions = { TEXT("mp4"), TEXT("webm"), TEXT("mov") };
    return VideoExtensions.Contains(FPaths::GetExtension(FilePath, false).ToLower());
}

bool URecoveredFileImportManager::IsSupportedMediaFile(const FString& FilePath) {
    return !FilePath.IsEmpty() && (IsImageFile(FilePath) || IsVideoFile(FilePath));
}

FString URecoveredFileImportManager::NormalizePath(const FString& FilePath) {
    return FPaths::ConvertRelativePathToFull(FilePath);
}

bool URecoveredFileImportManager::IsValidPresetName(const FString& PresetName) {
    return PresetName.Len() > 1;
}

bool URecoveredFileImportManager::ContainsFile(const TArray<FRecoveredImportedFile>& Files, const FString& FilePath) {
    return Files.ContainsByPredicate([&FilePath](const FRecoveredImportedFile& Existing) {
        return Existing.FilePath == FilePath;
    });
}

void URecoveredFileImportManager::AddFileIfMissing(const FString& FilePath) {
    if (!IsSupportedMediaFile(FilePath)) return;
    const FString Normalized = NormalizePath(FilePath);
    if (ContainsFile(ImportedFiles, Normalized)) return;
    FRecoveredImportedFile& Added = ImportedFiles.AddDefaulted_GetRef();
    Added.FilePath = Normalized;
    Added.bEnabled = true;
}

void URecoveredFileImportManager::AddFiles(const TArray<FString>& Files) {
    for (const FString& FilePath : Files) AddFileIfMissing(FilePath);
}

bool URecoveredFileImportManager::BrowseForDirectory(FString& OutDirectory) {
    OutDirectory.Reset();
#if PLATFORM_WINDOWS
    BROWSEINFOW Dialog{};
    Dialog.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
    Dialog.lpszTitle = L"Select Folder Containing Media";
    PIDLIST_ABSOLUTE Item = SHBrowseForFolderW(&Dialog);
    if (!Item) return false;

    wchar_t Path[MAX_PATH]{};
    const bool bResolved = SHGetPathFromIDListW(Item, Path) != 0;
    CoTaskMemFree(Item);
    if (!bResolved) return false;

    OutDirectory = NormalizePath(FString(Path));
    WatchedDirectories.AddUnique(OutDirectory);
    ScanCurrentPaths();
    return true;
#else
    return false;
#endif
}

bool URecoveredFileImportManager::BrowseForFiles(TArray<FString>& OutFiles) {
    OutFiles.Reset();
#if PLATFORM_WINDOWS
    TArray<wchar_t> Buffer;
    Buffer.SetNumZeroed(32768);

    OPENFILENAMEW Dialog{};
    Dialog.lStructSize = sizeof(Dialog);
    Dialog.lpstrFilter = L"Image and Video Files\0*.png;*.jpg;*.jpeg;*.bmp;*.gif;*.webp;*.mp4;*.webm;*.mov\0\0";
    Dialog.lpstrTitle = L"Select Media Files";
    Dialog.lpstrFile = Buffer.GetData();
    Dialog.nMaxFile = static_cast<DWORD>(Buffer.Num());
    Dialog.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if (!GetOpenFileNameW(&Dialog)) return false;

    const wchar_t* First = Buffer.GetData();
    const wchar_t* Next = First + FCStringWide::Strlen(First) + 1;
    if (*Next == L'\0') {
        OutFiles.Add(NormalizePath(FString(First)));
        return true;
    }

    const FString Directory(First);
    while (*Next != L'\0') {
        OutFiles.Add(NormalizePath(FPaths::Combine(Directory, FString(Next))));
        Next += FCStringWide::Strlen(Next) + 1;
    }
    return !OutFiles.IsEmpty();
#else
    return false;
#endif
}

void URecoveredFileImportManager::ClearAllData() {
    ImportedFiles.Reset();
    WatchedDirectories.Reset();
}

int32 URecoveredFileImportManager::GetImageCount() const {
    int32 Count = 0;
    for (const FRecoveredImportedFile& File : ImportedFiles) {
        if (File.bEnabled && IsImageFile(File.FilePath)) ++Count;
    }
    return Count;
}

int32 URecoveredFileImportManager::GetVideoCount() const {
    int32 Count = 0;
    for (const FRecoveredImportedFile& File : ImportedFiles) {
        if (File.bEnabled && IsVideoFile(File.FilePath)) ++Count;
    }
    return Count;
}

FString URecoveredFileImportManager::GetMediaCountText() const {
    return FString::Printf(TEXT("FOUND: %d IMAGES, %d VIDEOS"), GetImageCount(), GetVideoCount());
}

TArray<FRecoveredImportedFile> URecoveredFileImportManager::GetImportedFiles() const {
    return ImportedFiles;
}

TArray<FRecoveredMediaEntry> URecoveredFileImportManager::GetImportedMediaEntries() const {
    TArray<FRecoveredMediaEntry> Entries;
    Entries.Reserve(ImportedFiles.Num());
    for (const FRecoveredImportedFile& Record : ImportedFiles) {
        if (!Record.bEnabled) continue;
        FRecoveredMediaEntry& Entry = Entries.AddDefaulted_GetRef();
        Entry.File = Record.FilePath;
        Entry.FullPath = Record.FilePath;
        Entry.Type = IsVideoFile(Record.FilePath) ? TEXT("video") : TEXT("image");
        Entry.Tags = URecoveredMediaLibrary::ParseFilenameTags(Record.FilePath);
    }
    return Entries;
}

void URecoveredFileImportManager::RemoveFile(const FString& FilePath) {
    ImportedFiles.RemoveAll([&FilePath](const FRecoveredImportedFile& Record) {
        return Record.FilePath == FilePath;
    });
}

void URecoveredFileImportManager::ScanCurrentPaths() {
    TArray<FString> Found;
    for (const FString& Directory : WatchedDirectories) {
        if (!FPaths::DirectoryExists(Directory)) continue;
        Found.Reset();
        IFileManager::Get().FindFilesRecursive(Found, *Directory, TEXT("*.*"), true, false);
        AddFiles(Found);
    }
}

void URecoveredFileImportManager::SetFileEnabled(const FString& FilePath, bool bEnabled) {
    for (FRecoveredImportedFile& Record : ImportedFiles) {
        if (Record.FilePath == FilePath) {
            Record.bEnabled = bEnabled;
            return;
        }
    }
}

bool URecoveredFileImportManager::VerifyFileExists(const FString& FilePath) const {
    return FPaths::FileExists(FilePath);
}

bool URecoveredFileImportManager::EnsureSaveLoaded(URecoveredSaveGame* SaveGame) {
    if (!SaveGame) return false;
    return LoadedSave.Get() == SaveGame || LoadFromSave(SaveGame);
}

bool URecoveredFileImportManager::SavePresetToSaveGame(const FString& PresetName, URecoveredSaveGame* SaveGame) {
    if (!IsValidPresetName(PresetName) || !SaveGame) return false;
    if (LoadedSave.IsValid() && LoadedSave.Get() != SaveGame && !LoadFromSave(SaveGame)) return false;
    if (!LoadedSave.IsValid()) LoadedSave = SaveGame;

    const FString CanonicalName = PresetName;
    FRecoveredFileImportPreset Preset;
    Preset.PresetName = CanonicalName;
    Preset.WatchedDirectories = WatchedDirectories;
    Preset.ImportedFiles = ImportedFiles;

    const int32 ExistingIndex = Presets.IndexOfByPredicate([&CanonicalName](const FRecoveredFileImportPreset& Existing) {
        return Existing.PresetName == CanonicalName;
    });
    if (ExistingIndex == INDEX_NONE) Presets.Add(MoveTemp(Preset));
    else Presets[ExistingIndex] = MoveTemp(Preset);
    return SaveToSave(SaveGame);
}

bool URecoveredFileImportManager::LoadPresetFromSaveGame(const FString& PresetName, URecoveredSaveGame* SaveGame) {
    if (!IsValidPresetName(PresetName) || !EnsureSaveLoaded(SaveGame)) return false;

    const FString CanonicalName = PresetName;
    const FRecoveredFileImportPreset* Preset = Presets.FindByPredicate([&CanonicalName](const FRecoveredFileImportPreset& Existing) {
        return Existing.PresetName == CanonicalName;
    });
    if (!Preset) return false;

    const TArray<FString> RestoredDirectories = Preset->WatchedDirectories;
    const TArray<FRecoveredImportedFile> RestoredFiles = Preset->ImportedFiles;
    ClearAllData();
    WatchedDirectories = RestoredDirectories;
    for (const FRecoveredImportedFile& Record : RestoredFiles) {
        if (!VerifyFileExists(Record.FilePath)) continue;
        AddFileIfMissing(Record.FilePath);
        SetFileEnabled(NormalizePath(Record.FilePath), Record.bEnabled);
    }
    return true;
}

bool URecoveredFileImportManager::DeletePresetFromSaveGame(const FString& PresetName, URecoveredSaveGame* SaveGame) {
    if (!IsValidPresetName(PresetName) || !EnsureSaveLoaded(SaveGame)) return false;

    const FString CanonicalName = PresetName;
    const int32 Removed = Presets.RemoveAll([&CanonicalName](const FRecoveredFileImportPreset& Existing) {
        return Existing.PresetName == CanonicalName;
    });
    return Removed > 0 && SaveToSave(SaveGame);
}

TArray<FString> URecoveredFileImportManager::GetAllPresetNamesFromSaveGame(URecoveredSaveGame* SaveGame) const {
    auto* MutableThis = const_cast<URecoveredFileImportManager*>(this);
    if (!MutableThis->EnsureSaveLoaded(SaveGame)) return {};
    TArray<FString> Names;
    Names.Reserve(Presets.Num());
    for (const FRecoveredFileImportPreset& Preset : Presets) Names.Add(Preset.PresetName);
    return Names;
}

bool URecoveredFileImportManager::LoadFromSave(URecoveredSaveGame* SaveGame) {
    ImportedFiles.Reset();
    WatchedDirectories.Reset();
    Presets.Reset();
    LoadedSave = SaveGame;
    if (!SaveGame) return false;

    const FString Serialized = SaveGame->GetStringSetting(ImportStateKey, TEXT(""));
    if (Serialized.IsEmpty()) {
        LoadLegacyState(SaveGame);
        return true;
    }

    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Serialized), Root) || !Root.IsValid()) {
        LoadLegacyState(SaveGame);
        return false;
    }

    const TArray<TSharedPtr<FJsonValue>>* PresetValues = nullptr;
    if (Root->TryGetArrayField(TEXT("presets"), PresetValues) && PresetValues) {
        for (const TSharedPtr<FJsonValue>& Value : *PresetValues) {
            const TSharedPtr<FJsonObject> Object = Value.IsValid() ? Value->AsObject() : nullptr;
            FRecoveredFileImportPreset Preset;
            if (!Object.IsValid() || !Object->TryGetStringField(TEXT("name"), Preset.PresetName) || !IsValidPresetName(Preset.PresetName)) continue;

            const TArray<TSharedPtr<FJsonValue>>* PresetDirectories = nullptr;
            Object->TryGetArrayField(TEXT("directories"), PresetDirectories);
            ReadDirectories(PresetDirectories, Preset.WatchedDirectories);

            const TArray<TSharedPtr<FJsonValue>>* PresetFiles = nullptr;
            Object->TryGetArrayField(TEXT("files"), PresetFiles);
            ReadFiles(PresetFiles, Preset.ImportedFiles);
            if (!Presets.ContainsByPredicate([&Preset](const FRecoveredFileImportPreset& Existing) {
                return Existing.PresetName == Preset.PresetName;
            })) {
                Presets.Add(MoveTemp(Preset));
            }
        }
    }
    return true;
}

void URecoveredFileImportManager::LoadLegacyState(URecoveredSaveGame* SaveGame) {
    if (!SaveGame) return;

    const TArray<FString> LegacyFiles = SaveGame->GetStringArraySetting(LegacyImportedFilesKey);
    AddFiles(LegacyFiles);

    for (const FString& Directory : SaveGame->GetStringArraySetting(LegacyDirectoriesKey)) {
        if (!Directory.IsEmpty()) WatchedDirectories.AddUnique(NormalizePath(Directory));
    }

    for (const FString& PresetName : SaveGame->GetStringArraySetting(LegacyPresetNamesKey)) {
        if (!IsValidPresetName(PresetName)) continue;
        FRecoveredFileImportPreset& Preset = Presets.AddDefaulted_GetRef();
        Preset.PresetName = PresetName;
        for (const FString& Directory : SaveGame->GetStringArraySetting(FString(LegacyPresetDirectoriesPrefix) + Preset.PresetName)) {
            if (!Directory.IsEmpty()) Preset.WatchedDirectories.AddUnique(NormalizePath(Directory));
        }
        for (const FString& FilePath : SaveGame->GetStringArraySetting(FString(LegacyPresetFilesPrefix) + Preset.PresetName)) {
            if (!IsSupportedMediaFile(FilePath)) continue;
            const FString Normalized = NormalizePath(FilePath);
            if (ContainsFile(Preset.ImportedFiles, Normalized)) continue;
            FRecoveredImportedFile& Record = Preset.ImportedFiles.AddDefaulted_GetRef();
            Record.FilePath = Normalized;
            Record.bEnabled = true;
        }
    }
}

bool URecoveredFileImportManager::SaveToSave(URecoveredSaveGame* SaveGame) const {
    if (!SaveGame) return false;

    const TSharedRef<FJsonObject> Root = MakeShared<FJsonObject>();
    Root->SetNumberField(TEXT("version"), ImportStateVersion);
    TArray<TSharedPtr<FJsonValue>> PresetValues;
    PresetValues.Reserve(Presets.Num());
    for (const FRecoveredFileImportPreset& Preset : Presets) {
        if (!IsValidPresetName(Preset.PresetName)) continue;
        const TSharedRef<FJsonObject> Object = MakeShared<FJsonObject>();
        Object->SetStringField(TEXT("name"), Preset.PresetName);
        Object->SetArrayField(TEXT("directories"), WriteDirectories(Preset.WatchedDirectories));
        Object->SetArrayField(TEXT("files"), WriteFiles(Preset.ImportedFiles));
        PresetValues.Add(MakeShared<FJsonValueObject>(Object));
    }
    Root->SetArrayField(TEXT("presets"), PresetValues);

    FString Serialized;
    const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&Serialized);
    return FJsonSerializer::Serialize(Root, Writer) && SaveGame->SetStringSetting(ImportStateKey, Serialized);
}
