#pragma once
#include "CoreMinimal.h"

// Recovery-owned file locations, independent of the original game's saves.
struct COCKHERORECOVERED_API FRecoveredContentPaths {
    static FString GetSourceWindowsRoot();
    static FString GetBaseManifestPath();
    static FString GetMoviesDirectory();
    static FString GetBeatmapsDirectory();
    // Both shipped layouts exist in the supplied reference builds.
    static FString FindBaseManifest(const FString& WindowsRoot);
};
