# Newer progression import compatibility

Audited against the current `RecoveredGameplay`, `RecoveredRules`, `RecoveredProgression`, challenge tracker/rules/persistence, reward adapter, and save initialization source. Inputs are the independently round-tripped newer tables and native reflection. No editor was run and no existing asset was changed.

## Result: content schema fits; full runtime mapping is incomplete

All fields in70 challenge rows,48 player-card rows, and20 level rows fit the current recovered row structs. All newer used comparison operations, condition types, scope names, and reward kinds already have adapters. No player-card challenge reference is orphaned. The existing string metric representation permits loading unsupported metric names without an import error; this would conceal an execution gap.

Current `ERecoveredMetric` contains0..29. The newer native metric enum preserves every one of those names **and numeric values**, then appends17 entries30..46. This is an additive capability change, not a renumbering. Fourteen missing metric names are used by16 challenges, preventing ordinary tracker dispatch from ever updating those requirements. Thirteen player cards depend on those blocked challenges. The exact mappings and IDs are in `progression-runtime-compatibility.json`.

Missing metrics currently used by challenge rows:

- SessionsWonAtMaxDifficulty41: `built_different`, `speed_freak`.
- OffensiveItemsUsed31: `aggravator`; DeclinedTemptation32: `disciplined`.
- BountiesCollected33: `dead_or_alive`; BountyCollectionFailures46: `django_unclaimed`.
- LootRushesUsed34: `loot_goblin`; EscapeRopesUsed35: `im_outta_here`; ComboCrunchersUsed39: `pump_and_dump`.
- SuccuSlayerSessionsWon37: `public_safety`; SuccuCoinsSpent40: `ember's fave`, `budget_run`.
- BestMusicModeWinRounds42: `the_whole_record`; BestTowerWinRounds43: `test_your_might`.
- MusicBreaksUsed44: `not_quite_my_tempo`; DisabledBreakSectionFailures45: `aint_got_rhythm`.

Also added natively but not directly required by these70 rows: DefensiveItemsUsed30, MilkingCount36, EdgeSessionsWon38. All17 fields are present as int32 in newer native `SessionStats`; current `FRecoveredSessionStats` lacks all17. Current `MetricField`, session-specific tracker updates, presentation, event producers, and persistence need corresponding behavior before activating the full catalog. Simply appending enum names would allow generic incremental updates but would not establish best-round maxima, objective-specific wins, or event classification semantics.

## Existing semantic changes that require migration

`speed_freak` replaces SessionsWon>=5 plus condition modifier=insanemode with SessionsWonAtMaxDifficulty>=5 and no modifier condition. `built_different` replaces session SessionsWon>=1 plus insanemode with **lifetime** SessionsWonAtMaxDifficulty>=1 and no modifier condition. `cock_hero` description changes54 to69 other challenges; its recovered data does not establish whether native completion special-casing also changed. These changes are in `progression-table-delta.json`; all20 level rows and prior36 player-card rows compare unchanged.

`RecoveredSave.cpp` imports saved challenge state before `InitializeChallenges`. That initializer copies existing same-scope `Requirements` verbatim, even when definitions changed. A table-only update therefore leaves saved `speed_freak` using its old metric. The scope change for `built_different` looks in a different prior map and creates a fresh progress entry while retaining the separate `CompletedChallenges` set. This can separate previous completion/claim flags from the new entry; `ClaimChallengeRewards` consults that new entry's claim flag. Migration must preserve completion and reward-claim identity across scope changes to avoid losing progress or permitting duplicate rewards.

The content version must be stored with recovery state, definitions reconciled by challenge ID, and changed requirements deliberately replaced. Unchanged requirement counters may be carried across exact semantic matches; old generic wins cannot be relabeled as verified maximum-difficulty wins. Preserve prior earned completion/claim state without fabricating the new counters. Back up existing profiles before applying that migration.

## Resources and validation before activating versioned assets

New icon and card-image string paths can be preserved losslessly, but string preservation does not import their artwork. Current import scripts assert55 challenge icons and36 card-era content. Existing source icon/card adapters may map known old paths only; recover and bind the new resources before visual parity is claimed.

The existing reward adapter covers XP, UnlockPoints, UnlockPack, PlayerCard, and UnlockModifier, exactly matching the newer native reward enum. Conditions used by these rows remain within modifier/no_items/max_time. Current row fields retain all decoded primitive content; null FName references should use the existing empty-string normalization. The native-to-recovered FText conversion preserves displayed strings but not native localization namespace/key metadata; retain the raw evidence as already done for previous tables.

Required verification after implementing the missing runtime behavior:

- Initialize70 challenge definitions and48 cards from new assets; assert all requirement metrics resolve to a supported enum and all fields survive import/export.
- Drive each of the14 new used metrics through its real event producer; verify requirement progress and reward claiming, including maximum-round and maximum-difficulty semantics.
- Migrate old unfinished and completed/claimed states for `speed_freak` and `built_different`, retaining claims across scope changes and preventing duplicate rewards.
- Confirm unchanged55challenge content remains available for old mode/baseline validation, new table assets do not overwrite old assets, and old tests with explicit55counts are not silently repointed.
- Verify artwork bindings for15 added challenges and12 added cards.

Because the full mapping is incomplete, the conditional editor import script was **not created**. A versioned importer can be added once metrics/event adapters and migration are ready, targeting only `/Game/Recovery/Newer/Progression` and failing before asset creation for unsupported fields or metrics. Existing assets and runtime source remain untouched by this audit.
