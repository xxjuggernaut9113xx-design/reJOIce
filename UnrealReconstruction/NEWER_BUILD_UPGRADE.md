# Newer Cock Hero reconstruction upgrade

Started 2026-10-17. Work is in progress; the newer game is not fully reconstructed.
The existing editable project is the starting point. Existing features and original
files are preserved. Newer verified behavior takes precedence over older behavior.

## Reference and evidence

- Source Windows directory: `C:/Users/webma/Downloads/cock-hero-windows (1)/Windows`.
- Shipping executable SHA-256: `a8f46896593d8724cefb9a232db5772df48ae5731da78cfacbec82e98d040c10`.
- Executable/PDB GUID and age match. Engine logs identify UE 5.3.2, build 29314046.
- Version-specific evidence is in `../Analysis/ReferenceBuilds/newer-20261017/`;
  older V0.04 evidence has not been replaced.
- Container comparison: 16,417 unchanged, 92 changed, 6,895 added, and 2,588 absent
  game chunks. These are chunk counts, not semantic feature counts. Absence in
  the newer container does not authorize deleting an older recovered feature.
- All 117 extracted pack manifests read successfully, including 43 UTF-16 files.
- Recovered 14 tables / 329 rows and six selected manager defaults with exact
  payload round trips. Native reflection provides 157 schemas and newer enums.
- The newer tables have 70 challenges and 48 player cards. No old challenge or
  player-card IDs were removed. The 20 level rows are unchanged.
- Decoded selected Blueprint contracts establish Classic, Tower, and Playlist
  modes; the newer owned-item/hotbar system; and additional gameplay modifiers.
  Their presence in evidence does not mean their complete runtime is connected.

Detailed contracts and compatibility gaps are recorded in
`BLUEPRINT_BEHAVIOR_CONTRACTS.md`, `native-music-contract.md`,
`PROGRESSION_RUNTIME_COMPATIBILITY.md`, and `beatmap-contract.md` in that directory.

## Implementation in progress

- Added a beatmap data reader and file loader. Native parser recovery is being
  used to extend the initial shipped-example contract before Playlist playback
  is wired. Metadata offset must not be guessed or applied twice.
- Added the newer owned-item/hotbar state model with source-aligned levels,
  grants, charge limits, and slot behavior. Versioned recovery-profile persistence
  now retains its full ownership and hotbar state. Existing store consumers,
  effects, and new widgets still require integration.
- Added configurable content roots for the selected source build, supporting both
  old and newer extracted-pack layouts. Backgrounds use the same selected root.
- Challenge definition migration is required before activating newer tables:
  existing requirements must refresh while completed/claimed flags survive scope
  changes. Definition reconciliation and older-save readability now have passing
  regression tests. Missing newer metrics and their producers must still be
  implemented before newer tables go live. Existing recovery profiles now receive
  byte-verified, content-addressed disk snapshots before runtime reconciliation.

## Recovery profile safeguards

Existing profiles are copied through Unreal's save backend before definitions are
reconciled. Snapshot names are `<profile>_Backup_<SHA1-of-original-bytes>`, stored
beside the source profile in `Saved/SaveGames`. Repeated identical profiles reuse
the same snapshot. Existing snapshots are read back and compared byte for byte;
a damaged snapshot blocks profile loading rather than being overwritten. Original
game slots are rejected by the backup API. Snapshots are not profile-index entries.
To recover a snapshot, close the game, retain the current `.sav`, and copy the
selected backup `.sav` to its original profile filename. The backup test reloads
the saved object and checks its pre-migration value independently.

Newer inventory uses the `RecoveryNewerInventoryState` setting, with its own
version-one JSON payload. Profile loading creates a separate inventory object and
validates the complete payload before replacing active state. Unknown source enum
bytes and signed or over-cap charge values are preserved, matching the recovered
domain transitions. Malformed numbers, duplicate owned-item entries, unsupported
versions, and oversized arrays are rejected. Older profiles without this setting
remain readable and start with an empty newer inventory; baseline inventory is
not relabeled or converted into unverified newer ownership.

## Source content configuration

`Config/DefaultGame.ini`, section `[Recovery.Content]`, contains the selected
`SourceWindowsRoot`. It can be overridden with:

```text
-RecoveredSourceRoot="D:/CockHeroReference/Windows"
```

Relative configured paths resolve from the project directory. With no configured
root, a restored `../OriginalWindows` directory is used when present. An explicitly
selected root with missing content does not silently select another source build.
Original saves are not used by this configuration.

## Tools and verification status

The 2026-10-18 continuation passed a fresh editor build and **92 recovery tests**,
with zero warnings, failures, or skipped tests. The queue completed and the editor
exited with status zero. This includes backup restoration/corruption checks,
inventory serialization failure isolation, and named-profile inventory persistence.
See [continuation validation](RecoveryEvidence/continuation-20261018-validation.json).
The 90-test record below applies to the earlier foundation checkpoint.

REA 6.5.0 is installed and registered for Codex, with the matching workflow skill,
Ghidra 12.1.4 and JDK 24. Its setup doctor reported healthy. The first native MCP
decompilation request timed out after 300 seconds; the cause is not established.
Selected native routines were subsequently exported with local Ghidra from a
fresh full-image project without whole-engine autoanalysis. A workspace executable
copy has the same verified hash as the source and avoids the batch launcher's
failure on the original folder's parentheses.

The first cached-header build stalled without completing a compile action. A
`-NoPCH -MaxParallelActions=1` retry progressed and exposed missing direct includes
in older code. Those includes have been repaired. This workaround does not prove
the underlying cause was a corrupt or locked header.

The Windows editor build passed. The fresh full `CockHero.Recovery` run completed
**90 succeeded, 0 warnings, 0 failures, 0 not run**, including nine new tests for
the native-compatible reader, all ten supplied maps, item/hotbar state, source
layouts, definition reconciliation, and older version-one recovery saves.
The engine completed its queue and exited with status zero. The machine record
and source/artifact hashes are in
[newer-build-upgrade-validation.json](RecoveryEvidence/newer-build-upgrade-validation.json).
The report was created at 2026-10-17 23:29:22 in the user's local timezone.

Use the tested build command from `HANDOFF.md` with `-NoPCH` and
`-MaxParallelActions=1` for continuation. No engine files were patched.

Do not activate new table defaults until the runtime compatibility report is
resolved. Full-session GUI verification, packaged Windows validation, device
validation, and original-runtime comparisons remain outstanding. The original
shipping executable has not been launched by this upgrade work.
