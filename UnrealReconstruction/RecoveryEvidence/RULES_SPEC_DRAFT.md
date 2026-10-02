# CockHero V0.04 rules specification — recovery draft 1

The current target is an editable Unreal C++/Blueprint reconstruction. The user cancelled the AvtoHmver integration and Rust work. This document records recovered data and checked static behavior; it does not claim complete game reconstruction or verified runtime parity.

## Verified recovery

All eight gameplay/save class default objects decode without unread bytes and rebuild byte-for-byte: beat manager, card manager, game instance, save class, dialogue manager, draw manager, edge manager, and global manager. The largest payload is the global manager's 18,607 bytes, containing 132 serialized properties. The default reader uses UE5.3 property serialization layouts, generated native reflection metadata from the matching PDB, and recovered cooked Blueprint field definitions. See [default values](blueprint-default-values.json), [payload checks](default-roundtrip-check.json), and [field definitions](blueprint-class-fields.json).

Twelve Blueprint enums also decode and round-trip byte-identically. The difficulty enum establishes the actual labels and numeric values: 0 = EasyMode, 1 = NormalMode, 2 = InsaneMode. See [enum definitions](blueprint-enums.json).

Five difficulty functions have independently calculated in-memory instruction sizes matching their declared sizes, with every direct jump targeting a valid instruction boundary. Static branch evaluation recovers all three cases. See [difficulty traces](difficulty-branch-traces.json). Debug formatting is skipped during this evaluation; the recorded gameplay assignments are constant writes recovered from the bytecode, not observed runs.

The main event graph contains 43,645 in-memory bytecode bytes and 1,173 statements. Its 141 direct branch/flow targets and 60 event-wrapper entry points resolve to valid statement boundaries. Named entries include startup, initialization, song synchronization, media switching, input actions, cooldowns, save operations, and outcomes. This establishes structure, not complete semantics of dynamic flow stacks, asynchronous engine callbacks, or every conditional path. See [event graph](main-event-graph.json).

## Difficulty behavior

The recovered heat-gain multipliers are 0.5 / 1 / 3 for EasyMode / NormalMode / InsaneMode. Coin multipliers are 2 / 1 / 0.5. The fields named `DifficultyStrokeCounterMultiplier` receive 0.5 / 1 / 2; `DifficultyStrokeSpeedMultiplier` receives 1.85 / 1 / 0.6. The latter's actual effect on interval scheduling still needs correlation with its consumers; its name alone does not establish perceived speed.

Difficulty initialization also writes the resource-meter multiplier and seven item-rate fields. Keep these writes separate from constructor defaults. For example, the global class serializes `BreakItemSpawnChance = 5`, while the NormalMode initialization branch assigns 15; its slowdown-item field similarly changes from 10 to 15. A recreation that only loads serialized defaults will have incorrect balance. Full values and source function names are in [the machine-readable rules draft](game-rules-draft.json).

The decoded `AddHeat` function performs:

```text
heat = clamp(heat + HeatAdd * DifficultyHeatGainMultiplier, 0, 100)
```

The draw manager's chance helper calls `RandomFloatInRange(0, 100)` and returns `roll <= Chance`. Preserve the comparator when reproducing boundary behavior; do not assume a replacement RNG reproduces Unreal's random sequence or call ordering.

## Pattern and event data

The global default object contains eight pattern arrays with 62 total slots: general 4, slow 8, medium 9, fast 14, outcome 5, enemy 10, frenzy 3, and edging 9. These are array slots, not 62 unique patterns. Each recovered native pattern includes its name, interval multipliers, tags, and notes. Selection, eligibility and transitions still require branch interpretation.

There are 31 serialized special-event records, with enum identity, base weight, multiplier, eligibility, cooldown duration/state, and description fields. A record count is not a count of playable events: zero-weight and sentinel/fallback entries must be interpreted from their consumers. Do not normalize all records into one unconditional probability distribution.

Progression data remains fully recovered: 55 challenge rows, 20 level rows, and 36 player-card rows. Their requirements, scope/comparison enums, reward records, XP values and unlock references are included in the rules draft. Table payload round trips are documented separately in [progression checks](progression-roundtrip-check.json).

## Reconstruction implications and remaining work

The reconstructed Unreal gameplay classes should use the recovered configuration and explicit difficulty initialization. Serialized constructor values alone do not reproduce initialized gameplay. Beat-pattern scheduling, media/audio timing and output ordering still need correlation with their original consumers before runtime parity can be claimed.

Next, interpret startup and start-session paths, trace pattern/event eligibility and weighted selection, resolve each outcome and postgame settlement path, and correlate native progression calculations with their recovered struct fields. Then complete the full feature ledger and compare behavior using controlled original-game traces. Ghidra native pseudocode, table values, decoded bytecode, and original-game observations must remain separately attributed.

Unserialized native constructor defaults, native/Blueprint interaction, voice arbitration, save migration, device timing, and complete UI behavior are still unresolved. AvtoHmver application files and original game/save files have not been modified by this recovery work.
