# Current handoff — 2026-10-18

Latest continuation: editor build passed and **92 recovery tests passed**, with
zero warnings, failures, or skipped tests. Report created locally at
`2026.10.18-00.02.42`; the queue completed and the editor exited with status zero.
See [continuation validation](RecoveryEvidence/continuation-20261018-validation.json).
The 90-test foundation record below is retained as the earlier checkpoint.

Continuation is active. This is an editable, incomplete
reconstruction, not a finished game. This section supersedes all paths, test
totals, and next-step claims in the historical handoff retained below.

## Project and verified checkpoint

- Repository: `D:\reJOIce`.
- Project: `D:\reJOIce\UnrealReconstruction\CockHeroRecovered.uproject`.
- Engine: UE 5.3.2 (29314046), `D:\Program Files\Epic Games\UE_5.3`.
- Startup map: `/Game/Recovery/RecoveryWorkspace`.
- Windows editor build passed with `-NoPCH -MaxParallelActions=1`.
- Full recovery suite: **90 passed, 0 warnings, 0 failures, 0 not run**, in
  74.21 seconds. Report timestamp: `2026.10.17-23.29.22`, America/Havana local
  time. The log uses UTC and shows October 18. The queue completed and the engine
  exited with status zero.
- These completed results were rechecked from disk for this handoff; no new
  build or test run was performed during this documentation update.
- No upgraded packaged Windows build or full-session GUI validation is
  established by this checkpoint. The editor DLL is not a packaged deliverable.

Read [NEWER_BUILD_UPGRADE.md](NEWER_BUILD_UPGRADE.md) and the
[machine-readable checkpoint](RecoveryEvidence/newer-build-upgrade-validation.json)
for changes, hashes, and limitations. Local verification files are
`Saved/Automation/NewerUpgrade20261017/index.json` and
`Saved/newer-upgrade-tests.log`.

The continuation commits the implementation and versioned reference evidence.
Build
outputs, reports, reference binaries, and analysis caches may be ignored by Git
and need separate backup when transferring machines.

## Implementation present

- `RecoveredBeatmap.*` and tests: native-compatible JSON reader and relative
  audio-file resolution, tested against all ten supplied maps.
- `RecoveredNewerInventory.*`, `RecoveredNewerInventoryPersistence.cpp`, and
  tests: ownership/hotbar state model with recovery-profile persistence;
  existing store and effect consumers are not fully integrated.
- `RecoveredSave.cpp`: content-addressed, byte-verified profile snapshots before
  runtime reconciliation; backup failure leaves the active profile unchanged.
- `RecoveredContentPaths.*` and tests: configurable roots for both extracted-pack
  layouts, used by startup and backgrounds.
- `RecoveredChallengeTracker.*` and `RecoveredChallengeMigrationTests.cpp`:
  definition reconciliation, scope/requirement changes, archived definitions,
  claimed-state preservation, and older recovery-save readability.
- Direct-include fixes required by the no-PCH build. No installed engine files
  were patched; existing reconstruction assets were retained.

Code is in `Source/CockHeroRecovered`; editable assets are in `Content/Recovery`
and `Content/NewSetup`. New reference evidence is isolated in
`../Analysis/ReferenceBuilds/newer-20261017/`; older evidence is preserved.
Recovered data and passing component tests do not establish complete runtime
integration or full parity.

## Content and saves

Selected reference: `C:\Users\webma\Downloads\cock-hero-windows (1)\Windows`.
Configure `[Recovery.Content] SourceWindowsRoot` in `Config/DefaultGame.ini`, or
override with `-RecoveredSourceRoot="D:/CockHeroReference/Windows"`.
Relative paths resolve from the project directory. With no configured root,
`../OriginalWindows` is used when present. An explicitly selected missing root
does not silently switch builds. External media is not made portable merely by
moving the project.

Original files and saves are untouched. Recovery-owned slots are
`CockHeroRecovered_Standalone_v1` and `CockHeroRecovered_Named_...`.
Original-save loading is not implemented. The original shipping executable has
not been run for this upgrade; static recovery and reconstruction tests are not
original-runtime observations.

## Remaining engineering and release checks

- Disk backups now precede profile reconciliation. Newer defaults remain gated
  by missing runtime metric producers and content integration.
- New data/state models still need persistence and UI consumer integration.
  Retain baseline assets until compatibility is verified. Existing upgrade
  notes and checkpoint JSON record the outstanding scope.
- Verify full-session navigation, audiovisual behavior, profile reopening, and
  visible UI behavior end to end. Headless tests do not cover these adequately.
- Device preferences are not proof of working transport or hardware validation.
- Produce and independently validate a packaged Windows build before calling
  the release runnable or complete.

## Current build and test commands

Close the editor before rebuilding. From PowerShell:

```powershell
$recoveryProject = 'D:\reJOIce\UnrealReconstruction'
$unrealRoot = 'D:\Program Files\Epic Games\UE_5.3'
$env:Path += ';C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64'
& "$unrealRoot\Engine\Build\BatchFiles\Build.bat" CockHeroRecoveredEditor Win64 Development "-Project=$recoveryProject\CockHeroRecovered.uproject" -WaitMutex -NoHotReloadFromIDE -NoUBTMakefiles -MaxParallelActions=1 -NoPCH
if ($LASTEXITCODE -ne 0) { throw 'Editor build failed; an older DLL is not a fresh build.' }
$verificationRun = Get-Date -Format 'yyyyMMdd-HHmmss'
& "$unrealRoot\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" "$recoveryProject\CockHeroRecovered.uproject" -unattended -nop4 -nosplash -nosound -NullRHI -NoLiveCoding '-ExecCmds=Automation RunTests CockHero.Recovery' '-TestExit=Automation Test Queue Empty' "-ReportExportPath=$recoveryProject\Saved\Automation\Handoff-$verificationRun" "-abslog=$recoveryProject\Saved\handoff-$verificationRun.log"
if ($LASTEXITCODE -ne 0) { throw 'Automation failed; inspect the new report and log.' }
```

Inspect the new report's timestamp, counters, and queue-completion log marker;
exit code alone is insufficient. Timestamped continuation runs keep the original
90-test checkpoint separate. GUI and packaged-runtime verification remain required.

## Known hiccups and preservation notes

REA 6.5.0 setup doctor reported healthy with Ghidra 12.1.4 and JDK 24. The first
native MCP decompilation timed out after 300 seconds; cause not established.
Focused local Ghidra exports succeeded. Parentheses in the reference directory
broke a batch launcher; a hash-verified workspace executable copy was used for
static analysis only.

The initial cached-header build stalled. A no-PCH, single-action retry succeeded
after direct-include repairs; this does not establish the stall's root cause.
Parallel workers reached a usage limit; the primary agent completed and verified
the pending foundation changes. None of these facts establishes full completion.

Do not bulk-run historical asset generators: they can overwrite current native
parents, animations, or reports. Inspect scripts first. Keep ignored Ghidra and
extraction caches for resumption, with separate backups if transferring machines.

Historical records: [October 3 integration](RECONSTRUCTION_COMPLETION_HANDOFF.md),
[later gap patch](FINAL_GAP_PATCH_HANDOFF.md), and
[transfer instructions](../START_ON_OTHER_MACHINE.md). Their older paths and
test totals are historical, not current verification.

---

# Historical handoff — superseded

The following text is retained as history only. Its project paths, 37-test total,
and proposed next steps must not override the current checkpoint above.

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
