# Static-analysis materials and continuation

The shipping executable has not been executed. The editable reconstruction remains incomplete. Original files and saves are preserved. Tools are installed separately.

## Coverage

The targeted slice is complete: **712 matching PDB symbols, 390 eligible functions, 390 exported records**. Counts were checked against the existing project and exports; no exports were repeated. The completed slice maps selected code and read-only data, so external engine-call coverage is limited.

All three projects already uploaded under Analysis/ghidra-projects have their complete .rep contents, verified against the originals. Their zero-byte .gpr markers are normal. Actual Ghidra read-only opens passed. These are preloaded slice/rdata scratch projects with zero persisted functions: helper functions were created in read-only script sessions, with their pseudocode saved separately. The separately released CockHeroNativeSlice database contains 712 persisted functions and 113,908 instructions.

The earlier full-image database mapped the executable and applied its matching PDB. That run used 298.789 seconds in PDB Universal and exhausted its 300-second limit. The subsequent code-analysis run disabled repeated PDB application, used a 7200-second limit and the default 2 GB headless heap, and saved **573,011 functions and 43,658,219 instructions**. It also reported a Java heap-memory error and a timeout; Analyzed remains false. Analyzer timings total 8309 seconds and cumulative database analysis time is 8609.657 seconds. These reported analyzer times are distinct from the configured timeout. Historical complete-image pseudocode export coverage is 351 targeted records; no new whole-program pseudocode export is claimed.

The saved resumed project is now in `full-image-saved-analysis-20261003.zip`, documented by `transfer-manifest.json`. Use it for further work. The older `CockHeroV004` archive is retained as a baseline. See [the other-machine guide](../START_ON_OTHER_MACHINE.md) for restoration and a continuation command using an 8 GB heap.

Blueprint decoding covers 134 assets represented in the function-analysis reports and 1,225 UFunctions, with zero recorded raw bytecode fallbacks in that selected scope. This is not every package or recovered editor node layout. The original cooked containers and small mappings support further decoding. Reconstruction has a historical 37-passing-test checkpoint, not full-game parity.

## Private downloads and hash verification

~~~powershell
gh auth login --hostname github.com --git-protocol https --web
git clone https://github.com/xxjuggernaut9113xx-design/reJOIce.git
Set-Location reJOIce
New-Item -ItemType Directory -Path MaterialDownloads -Force | Out-Null
gh release download materials-v004 --repo xxjuggernaut9113xx-design/reJOIce --pattern '*.zip' --dir MaterialDownloads
python ./Materials/Scripts/verify_downloads.py ./MaterialDownloads --manifest ./Materials/materials-manifest.json
~~~

The manifest records paths, sizes and SHA-256 for every archive and entry, PDB GUID/age match, tool versions, project coverage and authenticated release links. GitHub access to this private repository is required. The verifier only reads files. Extract each verified project archive into a separate new directory; never overwrite an existing .rep database. Extract the native and cooked archives to a source-material directory. Keep all five cooked container files together. Runtime media is available in the latest transfer manifest; original saves are not included.

## Ghidra continuation

Use Ghidra 12.1.4 PUBLIC with JDK 24. The following commands use the installed Windows wrapper and separately extracted release databases. Use CockHeroFullImageResumed from the latest transfer for continuation; CockHeroV004 is the older baseline:

~~~powershell
$env:GHIDRA_HEADLESS_MAXMEM = '8G'
$ghidraHeadless = 'C:/Users/webma/Tools/ghidra/bin/ghidra-headless.cmd'
$scriptDirectory = Join-Path (Get-Location) 'Materials/Scripts'
& $ghidraHeadless 'D:/GhidraContinuation' CockHeroFullImageResumed -process CockHero.exe -readOnly -noanalysis -scriptPath $scriptDirectory -postScript ProbeMaterials.java 'D:/complete-image-readability.tsv'
& $ghidraHeadless 'D:/GhidraContinuation' CockHeroFullImageResumed -process CockHero.exe -analysisTimeoutPerFile 7200 -max-cpu 4 -scriptPath $scriptDirectory -preScript ResumeFullImage.java 'D:/analysis-phase.txt' -postScript ProbeMaterials.java 'D:/complete-image-coverage.tsv' -log 'D:/full-image-continuation.log'
& $ghidraHeadless 'D:/CompletedSlice' CockHeroNativeSlice -process native-slice.bin -readOnly -noanalysis -scriptPath $scriptDirectory -postScript ProbeMaterials.java 'D:/slice-readability.tsv'
~~~

ResumeFullImage.java disables repeated PDB application while retaining the existing symbols. Check analyzer times, timeout messages, save status, instruction counts and Analyzed metadata. A saved partial project is not automatically fully analyzed. A fresh import with PDB application needs a separate generous time allowance. Verify the completed slice without exporting it again. Read-only Ghidra opens can rotate index backup files; marker-file size is not a readability test.

## Blueprint continuation

Install retoc 0.1.5 from https://github.com/trumank/retoc/releases/tag/v0.1.5 and UAssetGUI 1.1.0 from https://github.com/atenfyr/UAssetGUI/releases/tag/v1.1.0. Supply compatible Oodle through the local Unreal installation; no tools or proprietary tool dependencies are bundled. Unreal source version is 5.3; reconstruction uses 5.3.2-29314046. Python used for verification is 3.14.

~~~powershell
$retoc = 'C:/Users/webma/analysis/cockhero-v004/tools/retoc/retoc.exe'
$uassetGUI = 'C:/Users/webma/analysis/cockhero-v004/tools/uassetgui/UAssetGUI.exe'
& $retoc to-legacy 'D:/OriginalCooked/CockHero/Content/Paks' 'D:/BlueprintContinuation/Legacy' --version UE5_3 --filter BP_GlobalManager
New-Item -ItemType Directory -Path "$env:LOCALAPPDATA/UAssetGUI/Mappings" -Force | Out-Null
Copy-Item ./Materials/Mappings/FunctionOnly.usmap "$env:LOCALAPPDATA/UAssetGUI/Mappings/FunctionOnly.usmap"
$asset = 'D:/BlueprintContinuation/Legacy/CockHero/Content/NewSetup/BP_GlobalManager.uasset'
$jsonOutput = 'D:/BlueprintContinuation/BP_GlobalManager-functions.json'
$process = Start-Process -FilePath $uassetGUI -ArgumentList @('tojson', $asset, $jsonOutput, 'VER_UE5_3', 'FunctionOnly') -WindowStyle Hidden -PassThru -Wait
if ($process.ExitCode -ne 0 -or -not (Test-Path -LiteralPath $jsonOutput)) { throw 'Blueprint decode failed' }
~~~

Choose another package filter to expand coverage. Preserve uasset/uexp/ubulk pairs. FunctionOnly and CockHeroProgression mappings are limited schemas, not full-game mappings. Derive and validate additional property schemas against native reflection. UAssetGUI is a GUI-subsystem executable: wait for it to finish before checking output. Inferred pseudocode and cooked bytecode are evidence, not original source.

## Saved continuation checkpoint

The long run has ended and saved its partial progress. Both database versions inside its .rep directory are included. Further analysis is needed after the timeout and heap-memory error. Preserve the checkpoint before another run and use a larger heap where RAM permits. The shipping executable was not executed. The latest transfer also includes the remaining helper projects, derived analysis files and reconstruction media; use the other-machine restore guide to place them correctly.
