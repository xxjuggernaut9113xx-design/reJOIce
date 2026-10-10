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
- Routed recovered store purchases into source-aligned owned inventory so every PG1 action consumes the acquired item through its original-use path.
- Made staged post-game and named-save widget helpers unique under Unreal's Unity build aggregation, preserving their existing behavior while restoring full editor build correctness.

## 2026-10-06 recovery wiring

- Reparented the existing `ImportMenuWidget`, `ChallengesTabWidget`, and `ModifiersTabWidget` assets to their recovered native classes. A fresh commandlet readback resolved all 15 expected widget parents, including the prior settings/store widgets.
- Rebuilt import around the actual controls recovered from `ImportMenuWidget`: `AddButton`, `AddDirectoryButton`, `ScanButton`, `ClearButton`, `EntryScrollBox`, `PresetsComboBox`, and `PresetSaveNameTextBox`. The Windows recovery build now opens native file/directory pickers, retains watched directories, saves recovery-owned presets, creates a recovery-owned absolute-path manifest, and reloads the media deck without copying original media.
- Extended `ReadPackManifest` to accept absolute paths only for recovery-generated manifests; original relative manifests retain their `manifest-directory/media` resolution.
- Rebuilt the challenge tab against `ChallengesVerticalBox`, `InteractionButton`, and the recovered detail fields. It combines session/lifetime progress, persists tracker-backed tracking, presents requirements/rewards, and claims a completed reward once.
- Rebuilt modifiers against `UniformGridPanel_94` and `ModifierCardEntryWidget`. It identifies modifiers by their source titles rather than serialized data-table row keys, preserves unlock state, confirms removal of active conflicts before enabling a modifier, persists enabled values, and synchronizes session modifier IDs for XP/session consumers.
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

The recovered outcome branch now creates the source-message boxes before its outcome overlay: `Perfect Finish` / `Full Rewards Unlocked — Victory Achieved` for success, `Early Climax` / `Post-Game Rewards Cut in Half` for early completion, and the original Iron Man penalty text after the store reset. The reparented `NotificationBoxWidget` applies its title, description, and icon fields; plays the original `/Engine/VREditor/Sounds/UI/Dockable_Window_Pick_Up` UI sound at unity volume and pitch; plays `FadeIn`; holds for four seconds; plays `FadeOut`; removes itself; and clears the global manager's lifecycle tracking entry. The recovered widget mounts through the original `UI_Manager.NotifVerticalBox` only when `AreNotificationBoxesEnabled?` permits it.

Focused `CockHero.Recovery.OutcomeNotifications` completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. It verifies native parenting, source text, panel mounting, and lifecycle tracking. The current full `CockHero.Recovery` run completed **49 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Outcome notification artwork recovery (2026-10-07)

Recovered the original `PrematureCumIcon` and `SuccessfulCumIcon` from their cooked `Widgets/NotificationBoxIcons` packages through the matching Unreal serializer. Both 256×256 DXT5 source mips were decoded to editable PNG assets, imported at `/Game/Recovery/Resources/Widgets/NotificationBoxIcons`, and mapped into the live early and successful outcome branches. The focused notification test verifies both mounted image brushes point to their recovered source assets and confirms the notification preference prevents panel insertion when disabled. The recovery record includes source-package and mip SHA-256 values in [outcome-notification-icon-recovery-report.json](RecoveryEvidence/outcome-notification-icon-recovery-report.json).

### Edge lifecycle and inventory action recovery (2026-10-08)

`/Game/NewSetup/BP_EdgeManager` now extends `ARecoveredEdgeManager`. The native owner restores the decoded `TriggerEdgeV2` flow: first, normal, and perfect edge branches; source meter increments and reward banks; break-duration adjustment; edge-streak state; persistence; the recovered `EdgedAnimation`; and the delayed rest-or-mercy handoff. Its one-second hold timer follows the original card-six guard, countdown truncation, cancellation, and `CurrentEdgesUntillNextMercy` behavior. The early-climax outcome clears that hold handle before it opens its notification.

The hold overlay uses the recovered source icon, source countdown images, and `/Game/Recovery/Resources/Audio/1sec_clocktick`. The original Bink payload was reconstructed from its cooked bulk data, imported into the live recovery asset, and recorded with source and output hashes in [edge-hold-audio-recovery.json](RecoveryEvidence/edge-hold-audio-recovery.json).

`/Game/Recovery/UI/PG1TabbedInventory_Widget` now extends `URecoveredTabbedInventoryWidget`. The restored PG1 Edge action preserves its original sequence: source availability gate including card type 5, taunt-based punishment roll, `EdgeItemKeyPress`, edge-owner trigger, one-item spend, count refresh, and last-item visual. It also restores `ReceiveEdgeItem`, `CantUseEdgeItem`, `UsedLastEdgeItem`, and `GetEdgeAvailableText` against the original `EdgeItemButton`/`QuantityAmount_2` control tree. `UI_Manager` key `3` enters the PG1 edge route on inventory tab zero; `Q` and `Tab` switch the recovered tab state and play the matching PG1/PG2 tab animation.

Focused `CockHero.Recovery.EdgeHoldLifecycle` automation completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **50 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### PG2 resupply recovery (2026-10-08)

`/Game/Recovery/UI/PG2TabbedInventory_Widget` now extends `URecoveredPG2TabbedInventoryWidget`. The owner restores the decoded resupply route: it blocks unavailable item use, records `ItemsUsed` before the punishment roll, preserves the item on punishment, applies `All or Nothing` to coins and the cum meter, plays `ResupplyKeyPress`, presents the source overlay and `Resupply Used` / `Store Will Open Shortly` notification, then waits two seconds before opening the store and spending one resupply. A final source item schedules `UsedLastStoreItem` after 0.3 seconds. The original key-three path now invokes this route on tab one and follows it with special-event dialogue.

The original `/Game/SoundFX/872025/new-notification-020-352772` Bink payload was reconstructed from its cooked package and imported at `/Game/Recovery/Resources/Audio/new-notification-020-352772`. The evidence record includes source, bulk, encoded hashes, a verified 48 kHz stereo decode, and the recovered resource alias in [resupply-audio-recovery.json](RecoveryEvidence/resupply-audio-recovery.json).

Focused `CockHero.Recovery.PG2Resupply` automation completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **50 succeeded**, **1 succeeded with warnings**, **0 failed**, and **0 not run**. Its one warning is the pre-existing external-sampler mismatch in `Background_Video_Texture_Mat`; the PG2 test had zero warnings.

### PG1 defensive item recovery (2026-10-08)

`/Game/Recovery/UI/PG1TabbedInventory_Widget` now binds the original `DecreaseHeatButton`, `10SecBreakButton`, `SlowdownItemButton`, and `CumChanceIncreaseButton` controls through `URecoveredTabbedInventoryWidget`. The recovered paths preserve the source availability checks, `All or Nothing` and taunt punishment order, item-usage metrics, source count limits, source animation events, delayed final-item presentation, and source upgrade values: heat reductions of 15/25/35/45/60, cum-meter gains of .05/.08/.12/.18/.35, and slowdown multipliers of x2 through x6. Heat, break, slowdown, and cum-chance inputs are routed from the original inventory key paths; break enters the recovered RestWidget lifecycle, and slowdown maintains the source task-level gate and elapsed-defense timer.

The source control-name recovery is recorded in [pg1-defensive-items-recovery.json](RecoveryEvidence/pg1-defensive-items-recovery.json). Focused `CockHero.Recovery.PG1DefensiveItems` automation completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **52 succeeded**, **0 failures**, and **0 not run**.

### RestWidget break lifecycle recovery (2026-10-08)

`/Game/Recovery/UI/RestWidget` now extends `URecoveredRestWidget`. Its recovered construct path pauses the beat sequence, disables drawing and item use, loads `backgroundmenuloop` into `BackgroundImage`, reads the source master duration, and advances `ProgressBar_0` from unpaused elapsed time at the original 10 ms interval. Completion clears the timer, invokes the recovered `DetermineCardV2` equivalent, and removes the widget. `G` and `CancelBreakButton` take the same one-shot cancel route. Break upgrades now drive the original 5/10/15/25/50-second duration ladder through `MasterBreakDuration`.

The graph inputs and validation result are recorded in [rest-widget-lifecycle-recovery.json](RecoveryEvidence/rest-widget-lifecycle-recovery.json). Focused `CockHero.Recovery.RestWidgetLifecycle` automation completed **1 succeeded**, **0 failures**, and **0 not run**. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **53 succeeded**, **0 failures**, and **0 not run**.

### PG2 Boner Pill and SuccuShield recovery (2026-10-09)

`/Game/Recovery/UI/PG2TabbedInventory_Widget` now binds the original `BonerPillItemButton` and `SuccubusShieldButton` routes through `URecoveredPG2TabbedInventoryWidget`, along with the recovered hover and unhover animation paths for every native PG2 control. The count labels now follow the source tree: Boner Pill at `QuantityAmount`, SuccuShield at `_1`, resupply at `_2`, slowdown at `_3`, and break at `_4`.

The Boner Pill path preserves its source gates, metrics 8 and 27, all-or-nothing adjustment, five gameplay-level multiplier rows, card type 2, special dialogue 13, temptation background style 9, source overlay/sound/notification, one-per-task gate, and the separate sixty-second temptation cooldown. The SuccuShield path preserves its original toggle semantics: a toggle checks availability and punishment but does not spend inventory; the source eligibility path consumes a shield, records the item metric, clears protection on the final shield, and presents the source overlays and notifications. Store acquisition uses the recovered shield quantities of 1/4/7/10/15 by upgrade level. The exact source tooltip is `Toggle to stop succubi from spawning`.

The source graph and validation record are in [pg2-defensive-items-recovery.json](RecoveryEvidence/pg2-defensive-items-recovery.json). The Windows Unreal Editor build passed. Focused `CockHero.Recovery.PG2` automation passed. The full `CockHero.Recovery` run completed **54 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Inventory keyboard recovery (2026-10-09)

The decoded `UI_Manager` input entries recover a three-key dispatch matrix that switches on `CurrentInventoryTab`. Key `One` calls PG1 Cum Chance on tab zero and PG2 Boner Pill on tab one. Key `Two` calls PG1 Heat Reduction on tab zero and PG2 SuccuShield on tab one, followed by source special-event dialogue 12. Key `Three` retains its existing PG1 Edge and PG2 Resupply routes; its tab-one route also plays source dialogue 12. The recovered branch order is recorded with the original entrypoint offsets and statement indices in [inventory-hotkey-recovery.json](RecoveryEvidence/inventory-hotkey-recovery.json).

The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **54 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Session-control keyboard recovery (2026-10-09)

The decoded `UI_Manager` control surface now routes `B`, `C`, `E`, `V`, `W`, `X`, `Z`, `Up`, and `K` through recovered native equivalents. `B` restores card-type-specific favorites and persistence; `E` selects a cum media entry without incorrectly invoking an outcome; the keyboard route plays `CumButtonKeyPress` while `CumTextButton_1` preserves the source mouse-click `CumButtonClick` animation; `C` restores all sixteen source HUD visibility targets; `V` preserves the tracked-challenge gate; and `Z` drives `ScaleBox_416` through the source Auto/Fill/Fit cycle. The media controller now implements manual `EStretch::Fill` and `EStretch::ScaleToFit`, with native-derived automatic aspect handling.

`W` restores the decoded taunt gates and messages before its source keypress animation. The card-three route applies its permanent succubus weight increase of 15 and rejoins the common taunt chain, including the decoded active-timeline 4x stroke and 5x speed modifiers. Every accepted route retains the 25 heat, two-times stroke count, 0.75 timing multiplier, 0.01 cum-meter increase, dialogue/background, and five-tick cooldown. `X` synchronizes the Brain Melter override and invokes the imported `PlayBMToggleAnim` Blueprint function. The original graph contains neither the prior reconstructed `F` favorite binding nor the prior reconstructed `P` pause binding, so both were removed. `Up` and `K` retain their source development-only routes.

The source entrypoints, implementation mapping, and validation are recorded in [session-control-hotkeys-recovery.json](RecoveryEvidence/session-control-hotkeys-recovery.json). `CockHero.Recovery.SessionControlHotkeys` passed. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **55 succeeded**, **0 failures**, and **0 not run**.

### Inventory tab input parity recovery (2026-10-09)

The decoded `UI_Manager` routes both `Q` and `Tab` through entry offsets 13672 and 13677 into the same tab-switch tail at 12986. That tail plays `/Game/SoundFX/swapitem.swapitem` as a UI sound at 0.25 volume and 0.7 pitch, switches only tab zero to one or tab one to zero, invokes the target page's `TriggerInventorySwitchAnimation`, then returns focus to the game viewport. The recovered session widget now follows that order and leaves unsupported tab values unchanged.

The two page widgets use different source animation names. PG1 uses `SwitchInventoryTabAnimation`; PG2 uses `SwitchTabAnimation`. The former reconstructed PG2 route requested the PG1 animation name and therefore could not find the PG2 runtime sequence. The recovered `swapitem` Bink stream was rebuilt from its cooked package and bulk payload, verified at 44.1 kHz stereo with 24,192 frames, imported as `/Game/Recovery/Resources/Audio/swapitem`, and registered in the resource alias ledger.

The source entrypoints, call offsets, page-specific animation names, decoded audio hashes, and runtime mapping are recorded in [input-control-parity-recovery.json](RecoveryEvidence/input-control-parity-recovery.json). `CockHero.Recovery.InventoryTabInputParity` passed. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **57 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Settings-menu input parity recovery (2026-10-09)

The decoded `UI_Manager` routes `Escape`, `ToggleSettingsMenu`, and the `SettingsMenuButton` through entries 13976, 13981, and 12730 into the shared toggle at offset 2414. `ResumeButton` enters the same path through `ToggleSettingsMenu`. Opening sets `PauseMenuMasterBorder` and its direct child visible, plays `/Engine/VREditor/Sounds/VR_ungrab.VR_ungrab` as a UI sound at 0.2 volume and 4.0 pitch, and shows the mouse cursor. Closing collapses both widgets, retains the cursor, and plays the same cue at 0.2 volume and 1.0 pitch.

The source route does not pause the beat timeline or media player. The recovered session widget now uses the source visibility state rather than treating a hidden state as the only closed state, binds both source buttons to the shared toggle, and leaves session transport untouched.

The source offsets, visibility states, sound parameters, and runtime mapping are recorded in [settings-menu-input-recovery.json](RecoveryEvidence/settings-menu-input-recovery.json). `CockHero.Recovery.SettingsMenuInputParity` passed. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **58 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Modifier conflict and challenge-link recovery (2026-10-09)

`DT_Modifiers` serializes generic row keys, while the native manager looks up modifier records by `ModifierTitle`. The recovered manager now uses that title identity for lookup, unlocks, active-set persistence, and session-facing modifier IDs. The complete native conflict registry from `InitializeModifierConflicts` is restored. `GetAllConflictsForModifier` returns its registered targets; `GetConflictingModifiers` filters those targets against the active set; and `CanEnableModifier` follows the native conflict-only predicate.

The modifier tab now retains the source four-column layout and opens the imported `ConflictingWidgetOverlayWidget` when an unlocked selection conflicts with active modifiers. Confirm removes exactly the displayed active conflicts, enables the selected modifier, persists the result, and refreshes the list. Cancel leaves state unchanged. `GetChallengeForModifier` now scans source challenge conditions for the exact `modifier` condition type and returns the matching challenge's `ChallengeID` instead of synthesizing a row-name convention.

The recovered native addresses, full registry, and validation evidence are recorded in [modifier-conflict-and-challenge-link-recovery.json](RecoveryEvidence/modifier-conflict-and-challenge-link-recovery.json). `CockHero.Recovery.ModifierConflictAndChallengeLinks` passed. The Windows Unreal Editor build passed. The full `CockHero.Recovery` run completed **56 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Toy transport and settings recovery (2026-10-10)

URecoveredDeviceManager now follows the recovered hardware transport contracts behind the 27-control Toy Settings menu and its nine source animations. The manager persists the source save keys, routes Handy through HTTPS v2, discovers active Lovense HTTP toys from the recovered type=OK / data.toys response, and restricts Intiface commands to advertised Buttplug WebSocket v3 capabilities.

The native recovery restores the source timing and message shapes: Intiface uses a 0.25-second vibrator pulse, StopAllDevices, a 0.1-second scan restart, linear test return after the complete 500 ms move, and five reconnect attempts with a two-second step. Lovense beat dispatch sends a per-active-vibrator Function command with Vibrate:15, timeSec: 0, stopPrevious: true, and apiVer: 1; fast beats enter the recovered continuous mode below 0.5 seconds, then stop and defer the next discrete pulse by 0.1 seconds. Test actions restore the vibrator, stroker, thrusting, and fallback command forms from the native dispatcher.

[toy-settings-parity-recovery.json](RecoveryEvidence/toy-settings-parity-recovery.json) records the widget inventory, source save fields, static-native contract markers, and SHA-256 values for the decompile and shipping executable. The original executable was not run. CockHero.Recovery.ToySettingsTransportParity completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The Windows Unreal Editor build passed. The full CockHero.Recovery suite completed **59 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

### Post-cum results transition recovery (2026-10-10)

PostCumContinue_Widget.ViewResultsButton dispatches ExecuteUbergraph_PostCumContinue_Widget entry 67. That source branch pauses the beat sequence, creates and adds WBP_PostGameFlow_Master at viewport layer zero, appends the active combo to PlayerVariablesStruct.BrokenComboArray, then clears the player edge streak and current combo count.

OpenPostGameResults now preserves that ordering around the recovered session-finalization step. It pauses the timeline before constructing the results master, keeps the source continue overlay in the viewport stack, records the active combo after the results master is added, clears the player and native runtime edge-streak state, and leaves SessionStats.EdgeStreak intact for the completed-session result. Returning to the main menu stops and releases the staged post-game sequence so its timers cannot survive the next session.

[post-cum-transition-recovery.json](RecoveryEvidence/post-cum-transition-recovery.json) records the source button entrypoint, graph statement order, source hashes, shipping executable hash, and native mapping. The original executable was not run. CockHero.Recovery.PostCumResultsTransition completed **1 succeeded**, **0 warnings**, **0 failures**, and **0 not run**. The Windows Unreal Editor build passed. The full CockHero.Recovery suite completed **60 succeeded**, **0 warnings**, **0 failures**, and **0 not run**.

## Remaining limits

- The staged post-game controller follows recovered graph order and timings, but interactive side-by-side original-runtime comparison of every animation curve, sound cue, and transient visual state remains outstanding.
- Importer file/directory picker behavior is Windows-specific and was validated by build, widget initialization, manifest/deck code, and parent readback. It still needs an interactive GUI and packaged-build check with representative user media. Playback support is limited by the existing recovered media backend.
- Recovered challenge and modifier lists use the original container/card assets, title-based modifier identity, source conflict registry, challenge-condition mapping, and recovered state models. Original entry Blueprint animation, tooltip/icon rules, reward-roll presentation, and interactive original-runtime comparison remain incomplete.
- The current inventory recovery covers PG1's Edge action, tab switching, heat, break, slowdown, cum chance, PG2 resupply, Boner Pill, and SuccuShield. Interactive original-runtime timing and full-session behavior still need side-by-side recovery.
- Hardware transports, original save compatibility, original editor graphs, complete native analysis, full GUI playtests, packaged validation, and clean-machine validation remain outstanding.
- The recovered Lovense HTTP flow covers the mobile LAN contract. The original desktop SDK route remains represented by the local HTTP adapter until its proprietary runtime can be exercised against a compatible device.
- The complete-image checkpoint is still partial, and the original runtime has not been used for behavioral comparison. No full-game completion or original-runtime parity is claimed.

Build/test details and input hashes are recorded in [final-gap-patch-verification.json](RecoveryEvidence/final-gap-patch-verification.json). The comprehensive missing/partial-feature audit is updated separately after this integration.
