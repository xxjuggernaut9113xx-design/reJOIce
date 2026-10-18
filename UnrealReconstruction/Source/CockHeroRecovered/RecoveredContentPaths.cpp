#include "RecoveredContentPaths.h"
#include "HAL/FileManager.h"
#include "Misc/CommandLine.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/Parse.h"
#include "Misc/Paths.h"

FString FRecoveredContentPaths::GetSourceWindowsRoot() {
    FString Root;
    if (!FParse::Value(FCommandLine::Get(), TEXT("RecoveredSourceRoot="), Root) && GConfig) {
        GConfig->GetString(TEXT("Recovery.Content"), TEXT("SourceWindowsRoot"), Root, GGameIni);
    }
    Root.TrimStartAndEndInline();
    if (Root.IsEmpty()) {
        const FString RestoredRoot = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("../OriginalWindows"));
        if (!IFileManager::Get().DirectoryExists(*RestoredRoot)) return FString();
        Root = RestoredRoot;
    } else if (FPaths::IsRelative(Root)) {
        Root = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir(), Root);
    }
    FPaths::NormalizeDirectoryName(Root);
    return Root;
}

FString FRecoveredContentPaths::FindBaseManifest(const FString& WindowsRoot) {
    if (WindowsRoot.IsEmpty()) return FString();
    const FString NewLayout = WindowsRoot / TEXT("CockHero/Extracted/Base_Game_CG/manifest.json");
    const FString LegacyLayout = WindowsRoot / TEXT("Extracted/Base_Game_CG/manifest.json");
    if (IFileManager::Get().FileExists(*NewLayout)) return NewLayout;
    if (IFileManager::Get().FileExists(*LegacyLayout)) return LegacyLayout;
    // Keep the requested root on failure so the importer reports it, rather than
    // silently reading an unrelated build's content.
    return NewLayout;
}

FString FRecoveredContentPaths::GetBaseManifestPath() {
    return FindBaseManifest(GetSourceWindowsRoot());
}

FString FRecoveredContentPaths::GetMoviesDirectory() {
    const FString Root = GetSourceWindowsRoot();
    return Root.IsEmpty() ? FString() : Root / TEXT("CockHero/Content/Movies");
}

FString FRecoveredContentPaths::GetBeatmapsDirectory() {
    const FString Root = GetSourceWindowsRoot();
    return Root.IsEmpty() ? FString() : Root / TEXT("CockHero/beatmaps");
}
