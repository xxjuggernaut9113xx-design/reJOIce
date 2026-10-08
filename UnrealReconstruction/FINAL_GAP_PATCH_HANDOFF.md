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
- Made staged post-game and named-save widget helpers unique under Unreal's Unity build aggregation, preserving their existing behavior while restoring full editor build correctness.

## 2026-10-06 recovery wiring

- Reparented the existing `ImportMenuWidget`, `ChallengesTabWidget`, and `ModifiersTabWidget` assets to their recovered native classes. A fresh commandlet readback resolved all 15 expected widget parents, including the prior settings/store widgets.
- Rebuilt import around the actual controls recovered from `ImportMenuWidget`: `AddButton`, `AddDirectoryButton`, `ScanButton`, `ClearButton`, `EntryScrollBox`, `PresetsComboBox`, and `PresetSaveNameTextBox`. The Windows recovery build now opens native file/directory pickers, retains watched directories, saves recovery-owned presets, creates a recovery-owned absolute-path manifest, and reloads the media deck without copying original media.
- Extended `ReadPackManifest` to accept absolute paths only for recovery-generated manifests; original relative manifests retain their `manifest-directory/media` resolution.
- Rebuilt the challenge tab against `ChallengesVerticalBox`, `InteractionButton`, and the recovered detail fields. It combines session/lifetime progress, persists tracker-backed tracking, presents requirements/rewards, and claims a completed reward once.
- Rebuilt modifiers against `UniformGridPanel_94` and `ModifierCardEntryWidget`. It uses real data-table row names, preserves unlock state, removes reconstructed conflicts before enabling a modifier, persists enabled values, and synchronizes session modifier IDs for XP/session consumers.
- Recovered the original four-stage post-game flow. It snapshots presentation data before `EndSession`, starts at XP, waits for each source slam before animating the bar, pauses at level boundaries and resumes overflow, awards every staged unlock-point source to the recovery-owned store ledger after its slam, then reaches the summary. It retains nested return binding and suppresses duplicate standalone level-up overlays during finalization.
- Recovered the native Iron Man loss penalty. The no-argument outcome entry now derives modifier state from the active session, reduces `UnlockedPacks` and `EnabledPacks` to `Base_Game_CG`, zeros the separate store `UnlockPoints` ledger, and persists the active recovery profile without altering progression-level points.
- Recovered the outcome-notification path. `NotificationBoxWidget` is parented to a native lifecycle controller, honors `AreNotificationBoxesEnabled?`, mounts in `NotifVerticalBox`, plays its recovered fade animations, and removes itself after the original four-second hold.

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

### Staged post-game recovery (2026-10-07)

The post-game master now follows the recovered source/delegate order: XP source slam, 0.65-second bar, level-boundary pause and overflow resume, 1.0-second page changes, unlock-point source slam, store-ledger award, 0.35-second next-source delay, then summary. Native `UProgressionManager` level points and the `CHPackStoreController` ledger are kept separate; progression persistence no longer overwrites the store balance.

The Windows Unreal Editor build passed. Focused `CockHero.Recovery.PostGame` automation completed **3 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The current full `CockHero.Recovery` run completed **49 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The source sequence test covers the XP source/bar handoff, threshold pause, overflow resume, unlock-point stage, and summary.

### Iron Man store-penalty recovery (2026-10-07)

The decoded premature-outcome branch invokes `UCHPackStoreController::ApplyIronManPenalty` only when the live `Iron Man` modifier is active. The reconstructed branch now follows that call: it preserves only `Base_Game_CG` in the unlocked and enabled pack ledgers, sets the controller-compatible `UnlockPoints` balance to zero, writes the active isolated profile, and leaves `UProgressionManager` level points separate.

Focused `CockHero.Recovery.IronManStorePenalty` automation completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The test reaches the native-shaped no-argument `PrematureCum` entry through active modifier state, validates the in-memory and persisted ledgers, and verifies progression-level points remain untouched.

### Outcome notification recovery (2026-10-07)

The recovered outcome branch now creates the source-message boxes before its outcome overlay: `Perfect Finish` / `Full Rewards Unlocked — Victory Achieved` for success, `Early Climax` / `Post-Game Rewards Cut in Half` for early completion, and the original Iron Man penalty text after the store reset. The reparented `NotificationBoxWidget` applies its title, description, and icon fields; plays `FadeIn`; holds for four seconds; plays `FadeOut`; removes itself; and clears the global manager's lifecycle tracking entry. The recovered widget mounts through the original `UI_Manager.NotifVerticalBox` only when `AreNotificationBoxesEnabled?` permits it.

Focused `CockHero.Recovery.OutcomeNotifications` completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. It verifies native parenting, source text, panel mounting, and lifecycle tracking. The current full `CockHero.Recovery` run completed **49 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Outcome notification artwork recovery (2026-10-07)

Recovered the original `PrematureCumIcon` and `SuccessfulCumIcon` from their cooked `Widgets/NotificationBoxIcons` packages through the matching Unreal serializer. Both 256×256 DXT5 source mips were decoded to editable PNG assets, imported at `/Game/Recovery/Resources/Widgets/NotificationBoxIcons`, and mapped into the live early and successful outcome branches. The focused notification test verifies both mounted image brushes point to their recovered source assets and confirms the notification preference prevents panel insertion when disabled. The recovery record includes source-package and mip SHA-256 values in [outcome-notification-icon-recovery-report.json](RecoveryEvidence/outcome-notification-icon-recovery-report.json).

## Remaining limits

- The staged post-game controller follows recovered graph order and timings, but interactive side-by-side original-runtime comparison of every animation curve, sound cue, and transient visual state remains outstanding.
- The notification path now has its source text, placement, animation names, hold timing, and original successful- and premature-outcome textures. The notification sound asset remains unrecovered, so that audio detail is not claimed exact.
- Importer file/directory picker behavior is Windows-specific and was validated by build, widget initialization, manifest/deck code, and parent readback. It still needs an interactive GUI and packaged-build check with representative user media. Playback support is limited by the existing recovered media backend.
- Recovered challenge and modifier lists use the original container/card assets and the recovered state models, but do not restore every original entry Blueprint animation, icon rule, conflict pair, reward roll, or data-table mapping.
- Auto-draw still has no verified completion consumer. Hardware transports, original save compatibility, original editor graphs, complete native analysis, full GUI playtests, packaged validation, and clean-machine validation remain outstanding.
- The complete-image checkpoint is still partial, and the original runtime has not been used for behavioral comparison. No full-game completion or original-runtime parity is claimed.

Build/test details and input hashes are recorded in [final-gap-patch-verification.json](RecoveryEvidence/final-gap-patch-verification.json). The comprehensive missing/partial-feature audit is updated separately after this integration.
