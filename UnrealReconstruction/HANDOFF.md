# Unreal reconstruction handoff

This is an editable partial reconstruction, not a complete game. The user will finish the remaining implementation. The last saved automation report (2026.10.02-17.37.27) contains 37 passed tests, zero warnings and zero failures. These results were verified from the existing report at handoff; no new test run was performed during handoff.

## Open the project

Use Unreal Engine 5.3.2 installed at `D:\Program Files\Epic Games\UE_5.3`. Open `CockHeroRecovered.uproject` in this directory. The configured startup map is `/Game/Recovery/RecoveryWorkspace`. The editor has been left closed; opening this partial project does not establish completion or original-game parity.

## Build and verify

Close the editor before rebuilding or refreshing recovered assets. From PowerShell:

```powershell
$recoveryProject = 'C:\Users\webma\analysis\cockhero-v004\UnrealReconstruction'
$unrealRoot = 'D:\Program Files\Epic Games\UE_5.3'
$env:Path += ';C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64'
& "$unrealRoot\Engine\Build\BatchFiles\Build.bat" CockHeroRecoveredEditor Win64 Development "-Project=$recoveryProject\CockHeroRecovered.uproject" -WaitMutex -NoHotReloadFromIDE -NoUBTMakefiles -MaxParallelActions=2
& "$unrealRoot\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "$recoveryProject\CockHeroRecovered.uproject" -unattended -nop4 -nosplash -nosound -NullRHI -NoLiveCoding '-ExecCmds=Automation RunTests CockHero.Recovery' '-TestExit=Automation Test Queue Empty' "-ReportExportPath=$recoveryProject\Saved\Automation" "-abslog=$recoveryProject\Saved\rules-tests.log"
```

Check the newly generated `Saved/Automation/index.json` timestamp and counters and the log's completion marker. A process exit code alone is insufficient: a crash can leave an older passing report in place. The report uses UTF-8 with a BOM.

## Where to work

- `Source/CockHeroRecovered`: native reconstruction and integration tests.
- `Content/Recovery` and `Content/NewSetup`: editable recovered assets and startup classes.
- `RecoveryEvidence`: decoded bytecode, defaults, layouts, aliases and static verification fixtures.
- `Scripts`: editor Python tools for selected asset restoration.
- `../Verification/animation-restore-report.json`: 72 restored screens, 357 animations; nine screens still need specialized callbacks.
- `README.md` and the parent `RECOVERY_STATUS.md`: current scope and limitations.

The original image manifest and image files remain external dependencies at the original Downloads location. The reconstruction uses the separate save slot `CockHeroRecovered_Standalone_v1`; original save compatibility is not implemented. Original files and saves have not been modified, and the original shipping executable has not been run.

## Next technical work

1. Connect the results button to the recovered postgame master screen. Its handler is currently unbound. Implement session finalization, lifetime accounting and reward consumers before presenting finalized results.
2. Complete return-to-menu cleanup. The existing main-menu creation guard can retain a removed widget; avoid duplicate timers, delegates and stale session state.
3. Connect the calibration offset to the playback timeline, then verify calibration and playback through actual GUI interaction.
4. Finish settings controls, inventory actions, remaining audio presentation and specialized animation callbacks.
5. Run fresh automation and runtime smoke checks, followed by GUI verification of navigation, playback, saves and reopening.

Native postgame lifecycle evidence is in the `../Analysis/ghidra-challenge-lifecycle/runtime-helpers.c`. Postgame widget functions are in the `../Analysis/blueprint-functions` and `../Analysis/widget-functions` directories. Static evidence is not an observation of the original executable running.

Asset generators can overwrite current native parents, animations or reports. Read a script before running it; do not bulk-run historical generators. Keep engine changes confined to this project: the installed engine has not been patched.

## Analysis materials

The targeted slice is complete (712 matching symbols, 390 eligible functions, 390 exports); do not repeat it. Complete-image analysis and Blueprint decoding have separate coverage limits. Matching executable/PDB, original cooked containers and Ghidra databases are private release assets. See [continuation instructions](../Materials/CONTINUATION.md) and [hash manifest](../Materials/materials-manifest.json). Zero-byte .gpr markers are normal; complete .rep databases were opened read-only. Material availability does not establish full-game completion.

## Transfer to another machine — October 3, 2026

[START_ON_OTHER_MACHINE.md](../START_ON_OTHER_MACHINE.md) provides the download and restore commands. The local reconstruction source and assets matched this repository at transfer time. The latest release assets add the saved full-image Ghidra checkpoint (573,011 functions; 43,658,219 instructions), remaining analysis files and project media. Analysis is partial because the run timed out and encountered a heap-memory error. Rebuild Unreal on the destination machine after adjusting the four documented absolute media paths. No game-completion claim is made.
