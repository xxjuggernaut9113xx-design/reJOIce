# Continue on another Windows machine

This transfers the saved analysis and editable reconstruction. The latest full-image Ghidra checkpoint has **573,011 functions and 43,658,219 instructions**. It saved successfully after a timeout and a Java heap-memory error. Further analysis and game reconstruction remain unfinished.

## Download and restore

Install Git, GitHub CLI and Python 3.11 or newer. Sign in to the GitHub account with access to this private repository:

```powershell
gh auth login
git clone https://github.com/xxjuggernaut9113xx-design/reJOIce.git
Set-Location reJOIce
New-Item -ItemType Directory -Path MaterialDownloads -Force | Out-Null
gh release download materials-v004 --repo xxjuggernaut9113xx-design/reJOIce --pattern '*.zip' --dir MaterialDownloads --skip-existing
python ./Materials/Scripts/restore_workspace.py ./MaterialDownloads
```

If you already have the clone, run `git pull --ff-only` inside it instead of cloning again. Existing downloads are skipped and still checked by the verifier.

Allow at least 20 GB of free space for downloads, restored databases and source materials, plus separate space for Unreal and builds. The restore script verifies every archive and file against SHA-256 before restoring. It preserves differing existing files instead of overwriting them.

After restoration:

- `UnrealReconstruction/` contains the editable project, source, assets and scripts from Git.
- `Ghidra/CockHeroFullImageResumed.gpr` opens the latest saved full-image analysis. Keep its entire adjacent `.rep` directory.
- `Ghidra/CockHeroNativeSlice.gpr` is the completed targeted slice: 712 matching PDB symbols, 390 eligible functions, 390 saved exports. Do not repeat that work.
- `Ghidra/CockHeroV004.gpr` is the earlier PDB-applied full-image snapshot.
- `Analysis/` contains saved pseudocode, decoded Blueprint evidence, derived package/texture data and the remaining helper projects.
- `OriginalWindows/` contains the source executable/PDB, original cooked containers, media manifest, media files and background images needed by the existing reconstruction.

Tools, build caches and original saves are excluded. The shipping executable is provided for static analysis and has not been executed by this work.

## Open the reconstruction

Install Unreal Engine **5.3.2**, Visual Studio 2022 C++ build tools and Windows SDK 10.0.26100. Open `UnrealReconstruction/CockHeroRecovered.uproject` and rebuild its native module for this machine.

The existing source still contains the original machine's absolute media paths. Before building, replace the old Windows root with the absolute path to the restored `OriginalWindows` directory in:

- `RecoveredRules.h` (`MediaManifestPath`).
- `RecoveredBackground.cpp` (background image directory).
- `RecoveredFlowTests.cpp` and `RecoveredMediaTests.cpp` (test fixtures).

These files are under `UnrealReconstruction/Source/CockHeroRecovered`. Keep the remainder of each path, including `Extracted/Base_Game_CG/manifest.json` or `CockHero/Content/Movies`. Historical analysis and editor scripts may also need their local tool/workspace paths adjusted.

Build from PowerShell after choosing your Unreal installation:

```powershell
$unrealRoot = 'D:/Program Files/Epic Games/UE_5.3'
$project = (Resolve-Path './UnrealReconstruction/CockHeroRecovered.uproject').Path
$env:Path += ';C:/Program Files (x86)/Windows Kits/10/bin/10.0.26100.0/x64'
& "$unrealRoot/Engine/Build/BatchFiles/Build.bat" CockHeroRecoveredEditor Win64 Development "-Project=$project" -WaitMutex -NoHotReloadFromIDE -NoUBTMakefiles -MaxParallelActions=2
```

See `UnrealReconstruction/HANDOFF.md` for remaining implementation work. The existing 37-test report is a historical checkpoint; run the tests again after rebuilding or changing paths.

## Continue static analysis

Install Ghidra **12.1.4 PUBLIC** and JDK **24**. Open the latest project first to inspect its saved progress. The previous run used the headless default 2 GB heap and encountered an out-of-memory error. On a machine with sufficient RAM, use an 8 GB heap for continuation:

```powershell
$env:JAVA_HOME = 'C:/Program Files/Java/jdk-24'
$env:GHIDRA_HEADLESS_MAXMEM = '8G'
$headless = 'C:/Tools/ghidra_12.1.4_PUBLIC/support/analyzeHeadless.bat'
$projects = (Resolve-Path './Ghidra').Path
$scripts = (Resolve-Path './Materials/Scripts').Path
& $headless $projects CockHeroFullImageResumed -process CockHero.exe -analysisTimeoutPerFile 7200 -max-cpu 4 -scriptPath $scripts -preScript ResumeFullImage.java './analysis-phase.txt' -postScript ProbeMaterials.java './analysis-coverage.tsv' -log './analysis-continuation.log'
```

Close the project in the Ghidra GUI before running headless analysis. Work on a copy if you want to retain this exact checkpoint. PDB application is retained and disabled during continuation; code analysis and later pseudocode export are separate phases. A successful save does not mean every analyzer completed.

For Blueprint decoding, use retoc 0.1.5 and UAssetGUI 1.1.0 with the supplied mappings and instructions in `Materials/CONTINUATION.md`. The source containers and prior decoded data are available after restoration.
