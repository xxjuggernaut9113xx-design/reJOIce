# Supplied patch integration — 2026-10-03

This is an incomplete reconstruction. The Linux-authored patch supplied by the user
was applied to repository base `431bfbe` and repaired against the installed Unreal
Engine 5.3.2 headers. Its original claim that all handoff work was complete was not
supported by a build or runtime test.

## Integrated changes

- Replaced unsupported dynamic-delegate lambdas and variable-name slider bindings
  with reflected callbacks. Corrected the `FText::AsPercent` call and tag widget API usage.
- Corrected audio controls against `RecoveryEvidence/ui-layout-values.json`,
  including `MetronomeVolSlider` and `VoicelinesVolDisplay_1`.
- Preserved the existing verified native XP calculation instead of the patch's
  replacement formula. Removed unsupported reward bonuses. Session XP uses the
  `Session Complete` source; repeated finalization cannot award twice.
- Retained the supplied calibration offset handling and menu teardown, with a
  regression test for pause/resume offset and duplicate finalization.
- Reparented four settings widgets and eight store widgets through
  `Scripts/integrate_supplied_patch.py`, assigning the supplied store item IDs.
  Widget trees and animations are retained. Future full widget rebuilds must rerun
  this integration script to retain store parents and defaults.
- Settings selection callbacks save only controls that changed; constructing the
  settings screen does not overwrite all preferences.
- The animation reload test now uses a checked-in 72-screen / 357-animation
  expectation fixture derived from `Verification/animation-restore-report.json`,
  instead of an ignored `Saved` report. Store previews handle a missing world.
- Missing sound aliases are checked before loading. Saved device preferences are
  not reported as real hardware connections.

## Remaining reconstruction work

- Full end-to-end session and post-game presentation is not validated. The
  2026-10-03 gap-fill patch adds lifetime-stat save/load and results-text
  adapters, but the recovered results master screen has no direct text blocks,
  so visible binding still needs verification. Additional rewards and complete
  return-to-menu UI routing still need work. The duplicate-finalization regression does not establish full native parity.
- Store effects, pricing, timing and several text bindings in the supplied patch
  remain approximations. Reparenting does not verify these mechanics against native code.
- Tag exclusion storage is present, but dynamic tag-entry creation and user toggle
  wiring are incomplete. The recovered screen has no `TagListContainer` from the patch.
- Several video preferences still need explicit source-backed save-key mappings
  and runtime consumers. Persisting a selection does not implement its effect.
- No device transport is implemented. Device status stays unavailable; preference
  callbacks do not establish a connection.
- Beat/outcome sound aliases supplied by the patch are missing; those calls skip
  unavailable assets. The recovered click sound is present. No replacement audio
  was invented.
- Original Blueprint editor graphs are unavailable. Shipping game execution has
  not been used for validation. Original files and original save slots are preserved.

## Validation and continuation

Final Windows build passed. All 39 recovery tests passed with zero warnings,
failures or skipped tests. A separate fresh editor process verified all 12 saved
widget parents and the eight store item IDs.

See `RecoveryEvidence/patch-integration-verification.json` for the final build/test
result and supplied patch hash. The regression suite is headless and does not
replace an editor playtest.

PowerShell, from the repository root (adjust the Engine location):

```powershell
$engine = 'D:\Program Files\Epic Games\UE_5.3'
$project = (Resolve-Path '.\UnrealReconstruction\CockHeroRecovered.uproject').Path
& "$engine\Engine\Build\BatchFiles\Build.bat" CockHeroRecoveredEditor Win64 Development "-Project=$project" -WaitMutex -NoHotReloadFromIDE -NoUBTMakefiles -MaxParallelActions=2
$script = (Resolve-Path '.\UnrealReconstruction\Scripts\integrate_supplied_patch.py').Path
& "$engine\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $project -unattended -nop4 -nosplash -nosound -NullRHI -NoLiveCoding -run=pythonscript "-script=$script"
& "$engine\Engine\Binaries\Win64\UnrealEditor-Cmd.exe" $project -unattended -nop4 -nosplash -nosound -NullRHI -NoLiveCoding '-ExecCmds=Automation RunTests CockHero.Recovery' '-TestExit=Automation Test Queue Empty' '-ReportExportPath=Saved/AutomationPatch'
```

The existing materials manifests and Ghidra coverage remain unchanged:
712 matching PDB symbols, 390 eligible functions, 390 completed slice exports;
full-image analysis is a saved partial checkpoint, not complete analysis.

## Later gap-fill patch

`ghidra-gap-fill.patch` was applied after the first 39-test run. It adds
progression text helpers, modifier lookup stubs, lifetime-stat save/load,
results text binding, tag list construction, and platform-specific compiler
flags. The tag list now targets the recovered `VertiBox1` container; callback
objects are retained and checked means shown. Tags are sourced from loaded media
decks, so a menu opened before media initialization can still show an empty list.
Modifier conflict and challenge
linkage still return empty results. The text builders and results binding are
approximations until tested against native evidence and live widget trees.

See `RecoveryEvidence/ghidra-gap-fill-verification.json` for the build/test
result for this patch. The earlier 39-test report applies to the previous commit.
