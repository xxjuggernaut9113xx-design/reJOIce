# Final supplied gap-fill patch: integration and limits

Input: `ghidra-gap-fill-final.patch` supplied by the user on 2026-10-04. Integrated over `a684caf74da3eb301e00a8d4d452cf2cbd4990c2`; the input repeated parts of the earlier patch. Earlier tag delegate lifetime and checked-state fixes were retained. Source files were merged, not regenerated. Original game files, saves, and reconstructed assets were preserved.

## Repairs made during review

- Removed the store-completion callback recursion and synchronous media-failure redraw recursion.
- Made the unimplemented device transport report failure, rather than a successful connection.
- Isolated named save operations under `CockHeroRecovered_Named_`, rejected path-like names and existing-slot overwrite, and initialized new snapshot defaults. The later named-profile continuation adds recovery-owned listing, switching, and rehydration while original save loading remains disabled.
- Removed duplicate challenge reward grants and duplicate XP text; the existing challenge tracker already grants rewards. Removed replay of per-event cumulative metrics at settlement and the second win-counter increment. Win state now comes from the recorded outcome rather than absence of a loss.
- Recorded regular coin awards in session earnings, connected active modifiers to XP, validated lifetime-load values before casting, and report failure from the final progression save. Settlement still needs transaction/retry work.
- Recovered all 27 preference widget names, actual save keys, and bool/string/enum/count conversions from the original `VideoSettingsMenu/InitDefaultsFromSaveGame` instructions. Fixed Borderless mapping; graphics setters apply resolution, screen mode and FPS. Removed the incorrect interpretation of stroke multiplier as a visibility setting.
- Connected the existing calibration button to `WBP_CalibrationUI`; load the saved calibration profile at ordinary game-instance startup. Added audio slider controller-commit callbacks.
- Read tags from the unfiltered manifest before a session, included all seven decks in fallback discovery, used three columns and the real `CheckBox`/`TagString` controls, retaining delegate objects safely.
- Added failed-session-start cleanup, sequence delegate teardown and inventory/notification reset. Fixed Escape/P pause consistency and removed the patch's incorrect Q-to-quit mapping. Remaining shortcuts are not certified as original mappings.
- Corrected animation object lookup and selected names, checked optional overlay packages before loading, guarded the meter threshold and disabled-state media effect, removed duplicate loot presentation notification, and made the defensive overlay dismissal callback weak.
- Made shuffle actually shuffle the selected deck, honored explicit repeat-disable while preserving default refill, connected video-loop state to current/future media players, and avoided duplicate file-import counts.
- Preserved immediate item use on existing assets without a separate use button, so new inventory scaffolding does not strand purchased items.

## 2026-10-06 recovery wiring

- Reparented the existing `ImportMenuWidget`, `ChallengesTabWidget`, and `ModifiersTabWidget` assets to their recovered native classes. A fresh commandlet readback resolved all 15 expected widget parents, including the prior settings/store widgets.
- Rebuilt import around the actual controls recovered from `ImportMenuWidget`: `AddButton`, `AddDirectoryButton`, `ScanButton`, `ClearButton`, `EntryScrollBox`, `PresetsComboBox`, and `PresetSaveNameTextBox`. The Windows recovery build now opens native file/directory pickers, retains watched directories, saves recovery-owned presets, creates a recovery-owned absolute-path manifest, and reloads the media deck without copying original media.
- Extended `ReadPackManifest` to accept absolute paths only for recovery-generated manifests; original relative manifests retain their `manifest-directory/media` resolution.
- Rebuilt the challenge tab against `ChallengesVerticalBox`, `InteractionButton`, and the recovered detail fields. It combines session/lifetime progress, persists tracker-backed tracking, presents requirements/rewards, and claims a completed reward once.
- Rebuilt modifiers against `UniformGridPanel_94` and `ModifierCardEntryWidget`. It uses real data-table row names, preserves unlock state, removes reconstructed conflicts before enabling a modifier, persists enabled values, and synchronizes session modifier IDs for XP/session consumers.
- Repaired the post-game handoff. It now writes the recovered XP, unlock-point, level-up, and session-summary fields to nested child widgets, suppresses the duplicate standalone level-up overlay during finalization, binds the nested return button, and lands the master switcher on its usable summary page.

## 2026-10-07 named profile recovery

- Added a versioned recovery-owned index for `CockHeroRecovered_Named_` profiles. It accepts only bounded alphanumeric, underscore, and hyphen identifiers; rejects path-like targets and case-insensitive duplicates; and never reads an original save slot.
- Completed named profile listing, creation, loading, and deletion. The active profile cannot be deleted. A profile is loaded and rehydrated before the index changes, so an unreadable progression, challenge, or calibration state leaves the active profile untouched.
- Routed ordinary persistence to the active recovery profile. Startup resolves the indexed active profile across restarts and falls back to the default recovery profile without overwriting a missing or malformed selected profile.
- Rehydrated progression, challenge tracking, calibration, lifetime counters, audio routing, modifier state, and metric forwarding for an active game manager after a profile switch. Modifier toggles now persist both the editor-facing enabled set and the session-facing active set.

## Verification

### Import failure handling follow-up (2026-10-06)

The importer now preserves load errors when refreshing its rows, leaves the active manifest path unchanged when loading fails, and explicitly reports when clearing the list cannot restore unavailable base media. Base-manifest detection uses normalized path comparison, and its restore path is saved after a successful import. Reopening the importer reapplies an existing persisted selection. Preset save/delete messages now include the actual disk-save result. Windows headers are guarded for other build targets.

`CockHero.Recovery.ImportFailureVisibility` checks unavailable-session errors, status preservation across list refresh, rejected empty input, and the empty-directory scan prerequisite using the recovered importer asset. This does not validate native dialogs, successful media playback, disk-failure injection, or packaged behavior. Full-game completion remains unverified.

Follow-up validation: editor build passed; **43 tests passed, zero warnings/failures/not-run**, including the new importer regression. See [import-failure-validation.json](RecoveryEvidence/import-failure-validation.json). The 42-test results below describe the preceding wiring checkpoint.

- Windows Unreal Editor build completed successfully with Unreal Engine 5.3.2.
- `CockHero.Recovery` automation: **42 succeeded, 0 warnings, 0 failures**. This includes `WidgetAttachments`, which initializes all three newly parented trees and verifies their actual recovered controls, and `PostGameHandoff`, which verifies finalized strokes reach `WBP_SessionSummaryWidget` and the master switcher selects page 3.
- Fresh editor commandlet parent readback: **15 expected widgets verified**.

The machine-readable record is [recovery-wiring-validation.json](RecoveryEvidence/recovery-wiring-validation.json). The shipping game was not executed.

### Named save profile recovery (2026-10-07)

The Windows Unreal Editor build passed. `CockHero.Recovery` completed **45 tests**: **44 succeeded**, **1 succeeded with warnings**, **0 failed**, and **0 were not run**. `NamedSaveSlotIndexRoundTrip` verifies registry validation and serialization. `NamedSaveProfileSwitch` creates an isolated randomized profile, restores progression/challenge/calibration state into a game instance, persists back to that profile, rejects an invalid target, and restores the pre-existing registry after the test.

The one warning-bearing test, `WidgetArtwork`, carried 13 blocked EOS SDK HTTP messages from the sandboxed network; it completed successfully and the new named-profile tests had zero warnings. The machine-readable record is [named-save-profile-validation.json](RecoveryEvidence/named-save-profile-validation.json).

## Remaining limits

- The original post-game animation/delegate sequence (XP animation, pause for level-up, unlock-point animation, then summary) is not reconstructed. The recovery master presents its populated summary directly because the original child delegates require unavailable runtime classes.
- Importer file/directory picker behavior is Windows-specific and was validated by build, widget initialization, manifest/deck code, and parent readback. It still needs an interactive GUI and packaged-build check with representative user media. Playback support is limited by the existing recovered media backend.
- Recovered challenge and modifier lists use the original container/card assets and the recovered state models, but do not restore every original entry Blueprint animation, icon rule, conflict pair, reward roll, or data-table mapping.
- Auto-draw still has no verified completion consumer. Hardware transports, original save compatibility, original editor graphs, complete native analysis, full GUI playtests, packaged validation, and clean-machine validation remain outstanding.
- The complete-image checkpoint is still partial, and the original runtime has not been used for behavioral comparison. No full-game completion or original-runtime parity is claimed.

Build/test details and input hashes are recorded in [final-gap-patch-verification.json](RecoveryEvidence/final-gap-patch-verification.json). The comprehensive missing/partial-feature audit is updated separately after pushing this integration.
