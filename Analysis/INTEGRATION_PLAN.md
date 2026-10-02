# CockHero V0.04 as an additional AvtoHmver playback mode

Prepared 2026-10-01. Target: the full game experience inside AvtoHmver, including media management and gameplay/session systems. This is a reverse-engineering assessment and implementation plan, not an implemented mode or a claim of complete game recovery.

## Recommendation

Build a distinct **CockHero** mode in AvtoHmver's existing native playback workspace, backed by a Rust game domain and the shared backend. Reuse AvtoHmver's library, player, music service, authentication, maintenance admission, and session ownership. Reimplement game behavior from a verified specification and load compatible content through a versioned game-content adapter.

The packaged Unreal executable is an application, not an integration SDK. Copying it into the installation does not expose the game as a Slint playback mode. Full fidelity requires recovering its Blueprint-driven behavior and game data as well as native functions. A separate-process/window embedding experiment could retain the original engine, but would add Windows window/input/focus/lifecycle work and would not provide native library/session integration. It is not the recommended architecture for the requested mode.

Full V0.04 parity is the final acceptance target. Interim milestones must identify missing systems rather than present a metronome or simplified playlist as the complete game.

## Evidence and confidence

Update: Unreal 5.3.2 build 29314046 is installed and its UnrealPak command-line tool is verified. Selected packages yield 479 decoded Blueprint function bodies with zero raw-bytecode fallbacks; all three progression tables are decoded (55 challenges, 20 levels, 36 player cards). Table `.uexp` payloads round-trip byte-identically; header differences are confined to regenerated name hashes. See [recovery status](RECOVERY_STATUS.md), [function index](blueprint-analysis-summary.json), and [normalized progression](progression-tables.json). Eight selected class-default payloads and twelve Blueprint enums now round-trip exactly. Five difficulty functions have validated static branch traces; the main event graph has 141 aligned direct branch/flow targets and 60 named entry points. The [rules draft](RULES_SPEC_DRAFT.md) captures this evidence, including difficulty initialization overrides. Startup/outcome semantics, remaining systems and runtime comparisons still block a complete gameplay specification.

The analyzed package is `C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows`.

- The top-level `CockHero.exe` is a 154,112-byte launcher. The real game executable is `CockHero\Binaries\Win64\CockHero.exe`, 259,111,424 bytes.
- The game SHA-256 is `c645757d1112491952b67bf29502b4721133ba6940a9cfb08358f0dde127560f`. The accompanying 310,423,552-byte PDB has a matching CodeView GUID and age, verified through the PE debug directory and PDB information stream. See [binary metadata](binary-metadata.json) and [PDB match](pdb-match.json).
- A saved game log identifies Unreal Engine **5.3.2**, build `29314046`. The filename's V0.04 label and the content manifest's `0.02a` version are different identifiers; they must not be conflated.
- The supplied PDB yields **712 public function symbols across ten targeted native classes**, including generated wrappers. The focused Ghidra pass exported **390 decompilation attempts**. This is not 390 independently verified source functions. See [symbol addresses](native-symbol-addresses.tsv), [Ghidra output](ghidra-native/integration-decompiled.c), and [analysis log](ghidra-native.log).
- The focused project maps a 712,704-byte native code slice at original addresses plus the original `.rdata`. Calls into omitted engine code remain unresolved, and Ghidra reports some incomplete control flow. Treat exact formulas, inferred types, and exceptional branches as provisional until checked against the complete image and behavior.
- The broader PE/PDB analysis reached its 300-second analysis limit, then exported **351 additional decompilation attempts** and saved the complete-image project. These overlap the focused pass and must not be added as unique functions. Its [partial output](ghidra/integration-decompiled.c) is supplementary; the focused project is the reproducible evidence source for this plan. A timeout is not complete analysis.
- The IoStore directory contains **7,734 `.uasset`/`.umap` leaf-name strings**, including engine assets. This is an inventory of names, not decoded Blueprint graphs or a count of unique gameplay systems. See [asset/save inventory](asset-save-inventory.json).
- **14 already extracted pack manifests** are available under `Windows\Extracted`. A sampled manifest uses `0.02a`, media entries with `file`/`type`, and `image_count`, `video_count`, `total_media` fields. These corroborate native parser evidence without executing the game.
- AvtoHmver was inspected at commit `addd9634946a76ae03b58fcee469ae6906e3637b`, with substantial uncommitted work. The plan reflects the current working files. No AvtoHmver application code was changed for this assessment.

Useful starting points in the recovered native layer:

- `UCHPackManager::ExtractChpackToFolder`, **0x14818cfa0**: searches for `7za.exe`, invokes extraction, and checks `manifest.json`. Archive support comes through 7-Zip; it is not evidence that `.chpack` must be 7z-only.
- `UCHPackManager::ParseManifestJson`, **0x1481924d0**: reads version, name, author, description, preview, cost/challenge metadata, counts, exclusivity, social links, and media. See [parser pseudocode](ParseManifestJson.c).
- `UFileImportManager::AddFiles`, **0x1481971f0**: native comparisons include png/jpg/jpeg/bmp/gif/webp and mp4/mov/webm. This does not prove every codec/container combination plays successfully. See [import pseudocode](AddFiles.c).
- `UMediaPlaybackController::SetBeatPattern`, **0x1481ae230**, and `UBeatSpawnerManager::StartPatternWithMediaSync`, **0x1481d25e0**: beat patterns and media changes are coordinated; this is more than a fixed BPM overlay.
- `UMediaPlaybackController::UpdateBeatInterval`, **0x1481af4c0**: lower bound is approximately **0.01 seconds**. `UpdateSpeedItemMultiplier`, **0x1481af4e0**, clamps to approximately **0.1–5.0**. These are implementation limits, not recommended playback defaults.
- `UProgressionManager::CalculateSessionXP`, **0x1481b49f0**, `PrepareSessionRewards`, **0x1481c6a00**, and `RecordSessionMetric`, **0x1481c8fd0**: there is a separate progression/reward domain. Calculation code refers to modifier names and capped components; exact balancing still needs decoded types/data tables.
- `UCHPackStoreController::GetAllEnabledMedia`, **0x1481d4820**, and `UnlockPack`, **0x1481d6810**: enabled content and unlock state are separate concerns.

## What “full game” includes

The parity ledger must cover all of the following. Presence is confirmed by native symbols, reflected names, save fields, or asset names; runtime semantics are not all recovered yet.

1. **Game shell:** menu/setup, difficulty, settings, content selection, gameplay HUD, pause, completion/failure, and post-game flow. Assets include `DifficultySelectScreen_Widget`, `SettingsMenuWidget`, `WBP_PostGameFlow_Master`, and `WBP_SessionSummaryWidget`.
2. **Media/content:** pack catalog, previews, enabled/disabled packs, local imports, filename tags, filtering, categories, missing-file handling, and asynchronous preparation. Native classes include `UCHPackManager`, `UFileImportManager`, and `UCHPackStoreController`.
3. **Session gameplay:** draw/card rules, events, modifiers, resource meters, choices, win/loss transitions, and configurable pacing. Asset names include `BP_GlobalManager`, `BP_DrawManager`, `BP_CardManager`, and another dedicated gameplay manager. Their transitions and balancing require Blueprint decoding.
4. **Timing/rendering:** beat queue, travel time, pattern progression, media synchronization, latency offsets, pause/resume, and decoder error behavior. Native symbols and calibration widgets establish these systems' presence.
5. **Progression:** XP, levels, unlock points, rewards, player-card/modifier unlocks, lifetime/session metrics, challenges, tracked challenges, and statistics. Data tables include `DT_Challenges`, `DT_LevelData`, and `DT_PlayerCards`.
6. **Audio/presentation:** music, metronome, dialogue, voice packs, cues, overlays, and independent mixing. Assets include `BP_DialogueManager`, voice-pack UI, and many sound/cue assets. Recover selection/interruption rules before implementing them.
7. **Persistence:** settings, game/session save state, progression, enabled content, imported-media presets, and calibration profiles. Supplied files include `BP_CHSaveGame.sav`, `PlayerSave.sav`, and `ProgressionSave.sav`; the latter contains challenge/reward/progression fields.
8. **Peripheral integration:** device discovery/configuration, connection lifecycle, timing compensation, and output handling. PDB/source names and the saved log identify several adapters. Match each adapter's supported behavior through separate tests; symbol presence does not establish compatibility.

Network patron/store behavior, built-in content, device integration, and original asset presentation all need explicit entries in the ledger. Preserve existing entitlement decisions; a local port must not silently mark restricted content unlocked. Use user-provided game assets locally or separately authorized distributable assets, and track which build supplies them.

## AvtoHmver reuse and missing work

`src/session.rs` already has a versioned `GameConfig`, phases/events, tempo curves, seeded state, active-time accounting, and `SessionEffect` outputs. `src/services/session.rs` and `src/routes/session.rs` share command/state authority. Reuse those lifecycle boundaries, but do not force the entire card/progression game into the existing phase/event configuration.

The native shell currently polls session snapshots at 250 ms locally and one second remotely. Those snapshots are suitable for status display, **not beat-accurate cue scheduling**. Native code also notes that metronome/speech cues remain browser-only. A reliable effect consumer, media selector, native audio mixer, checkpoint writer, and presentation clock are required to turn domain effects into full gameplay. Do not assume an effect enum means its side effects are implemented.

The old native Cock Hero compatibility code exists, but the parity ledger records removal of its Slint panel. The requested mode needs a new intentional shell/workspace entry and complete controls; resurrecting a dormant callback is insufficient.

Reuse `desktop/src/player.rs` for media decoding/presentation, `src/native.rs` for Host/Viewer adapters, `src/services/music.rs` for managed tracks, `src/services/playback.rs` for presentation presets, and `src/local_import.rs` for managed-library ingestion. Current local folder import copies content into the library. A game-install reference mode, if desired, needs a distinct media source/identity contract rather than assuming folder import avoids copying.

`src/chpack.rs` already exports a ZIP-based `0.02a` manifest, media entries, and rating-to-speed filename tags. The native parser and extracted manifests substantiate this basic format. Counts and additional game metadata need typed optional support. This is an **exporter**, not a pack importer, catalog, entitlement service, or full gameplay engine. `src/linked_packages.rs` creates managed hard-link staging plus portable archives; it does not make the game a native mode.

## Proposed architecture

Add a `CockHero` playback driver and a game-mode service beneath the existing application boundary. The game domain emits typed effects; player/audio/HUD/device adapters perform them. One authoritative session owns the clock and run ID. Library browsing and editing retain their existing services.

Proposed modules, subject to repository conventions:

- `src/game/mod.rs`, `config.rs`, `state.rs`, `commands.rs`, `effects.rs`: versioned mode configuration, deterministic state machine, commands, and effects.
- `src/game/rules.rs`, `cards.rs`, `events.rs`, `progression.rs`: decoded rule definitions, deterministic draws/modifiers, metrics, challenges, and transactional rewards.
- `src/game/content.rs` and `src/services/game_content.rs`: typed manifests, pack identity, content indices, library-media resolution, tag/category mapping, asset provenance, and enabled/unlocked state.
- `src/services/game.rs`: lifecycle, authorization, maintenance admission, effect delivery, checkpoints, and application integration. HTTP adapters remain thin; the native Host calls services directly.
- `desktop/src/game.rs`, `game_audio.rs`, and a dedicated Slint game stage: renderer/HUD, input, media handoff, mixer, scheduling, calibration, and mode transitions.
- `src/game/save_import.rs`: optional read-only Unreal save parsing and migration preview. Writes go to new AvtoHmver game tables, never back to the supplied saves.
- Device adapters consume abstract timed output effects through an optional feature boundary. Keep credentials in established local configuration, out of media manifests and game exports.

Persist independent tables for game profiles, rule/data versions, content packs, enabled/unlocked state, cards/modifiers, challenges, progression, runs, events, calibration, and checkpoints. Use stable definition IDs and a configuration/content hash in checkpoints. Reward settlement must be idempotent per run and reward ID.

Add a reliable ordered effect channel with sequence numbers, run IDs, and restart/reconnect rules. Keep lossy status snapshots separate. The renderer schedules cues against a monotonic presentation/audio clock; it must not fire beats from a 250-ms UI poll. Preserve media generation IDs so late decoder completions cannot update a stopped/replaced run. At mode exit, stop scheduled cues, audio, and peripheral output before returning player ownership.

## Implementation sequence and gates

### 0. Finish the behavioral specification

Recover native type layouts and remaining important functions from the complete image. Decode UE 5.3.2 IoStore packages and Blueprint bytecode/data tables using a compatible reader. Inventory every screen, card, modifier, resource, event, outcome, audio rule, challenge, and save field. Create a provenance-linked parity ledger with evidence levels: observed, decompiled, asset-only, inferred, and verified.

Capture behavior from the original game in a copied profile with controlled media and isolated device outputs. Record choices, timestamps, rules/settings, transitions, and final stats. RNG replay cannot be assumed identical merely because AvtoHmver already accepts a seed; recover the source RNG/selection behavior or use controlled traces.

**Gate:** every shipped feature has an identified source and acceptance scenario; unknown values are explicit. Freeze a versioned rules/content specification before claiming full parity. Source project access, if available, would reduce uncertainty substantially.

### 1. Establish the additional playback mode

Add the mode entry, setup view, HUD host, lifecycle service, state schema, and playback ownership. Start/pause/resume/end/restart must share the existing service boundary. Keep current playback modes usable and use the existing role/permission matrix.

**Gate:** start a minimal fixture session; media and audio stop on exit, panic, shutdown, or mode switch; viewer permissions and maintenance admission match Host/Server policy. No other mode's presets or history are overwritten.

### 2. Implement content and selection

Add manifest import and validation, managed staging, catalog/preview, enabled state, local imports, filename tag parsing, category mapping, and media identity. Support already extracted local packs first; add archive import with detected ZIP/7z formats and size/path limits. Extend export metadata only after reading the actual parser/specification. Provide selection by library scopes as well as game packs.

**Gate:** neutral image/video fixtures round-trip; tags/categories match specified behavior; corrupt/missing media produces actionable errors; pack enablement and content gates work; import is cancellable and preserves originals. Original proprietary media is not required for tests.

### 3. Implement the complete gameplay domain

Port the recovered draw/card/modifier/resource/event rules, difficulty, pacing, input actions, outcomes, and post-game sequence as deterministic transitions. Implement actual data-table values rather than guessed BPM schedules or hardcoded approximations. Keep authored content/data separate from code and version it.

**Gate:** controlled traces cover every rule branch and outcome, including conflict/priority rules, interruption, empty selections, and repeated inputs. Interim builds label unfinished systems. “Full game” remains unaccepted until all ledger entries pass.

### 4. Finish timing, audio, and presentation

Implement beat-pattern/media synchronization, animation travel time, native sound/voice mixing, queued cue cancellation, video completion/interruption rules, and saved latency profiles. Adapt decoded UI presentation to AvtoHmver while preserving gameplay information and inputs. Import local compatible assets or use authorized substitutes where original asset loading is unsupported.

**Gate:** instrumented traces demonstrate bounded audio/visual skew, no duplicate/missed cues, and correct phase/pattern/media alignment. Define measurable timing tolerances from original-game observations before acceptance. Pauses, hidden windows, CPU load, seek/decoder failures, and mode changes have explicit tests.

### 5. Implement progression and persistence

Port levels, XP, unlock points, challenges, card/modifier unlocks, statistics, and rewards from recovered types/rules/data. Add durable runs/checkpoints and save migration preview with backups. Reuse AvtoHmver database admission/backup facilities.

**Gate:** each completed run settles once; interruption/crash/restart cannot duplicate rewards; save import never changes original saves; version mismatches get migration/recovery behavior. Progress persists independently of media library rating edits.

### 6. Add full settings, calibration, peripherals, and remote behavior

Implement all mapped settings and device-adapter behavior. Native Host owns hardware connections; remote clients send authorized game commands and display authoritative state. Make peripheral parity a required tracked milestone for a claim of complete V0.04 compatibility, while retaining useful playback with no connected device.

**Gate:** mocked adapters verify output ordering and stop behavior; supported devices get real manual acceptance; disconnect/panic/shutdown stop output; Viewer has no direct access to local filesystem or device secrets. Document platform-specific gaps rather than hiding them.

### 7. Full-game acceptance and release

Run the entire parity ledger against V0.04: setup, all content paths, every card/modifier/event/challenge/outcome, presentation/audio, progression, save migration, settings, calibration, peripherals, and post-game flow. Test packaged Windows Host, Viewer/Server permissions, existing playback modes, and installer/upgrade behavior. Linux status is separately measured.

**Gate:** no unverified asset-only or inferred gameplay item remains in the claimed parity scope. Only then label the mode a complete recreation. Update the canonical parity ledger and release documentation with dated evidence.

## Remaining unknowns and next concrete work

The principal dependency is completing the behavioral interpretation of the decoded Blueprint/native layer. Selected defaults, difficulty assignments, beat patterns and progression tables are recovered, but startup sequencing, event eligibility, outcomes and UI interactions are not fully verified. Native pseudocode alone cannot produce a verified full-game specification. Audio arbitration, original save compatibility, store/network behavior, and device timing also remain to be validated.

An initial versioned [machine-readable rules draft](game-rules-draft.json) is available. The next deliverable is a complete **game rules specification and parity ledger**, extending this draft with native call interpretation, startup/outcome traces and isolated behavior comparisons. Explicitly apply difficulty initialization: copying serialized defaults alone reproduces incorrect item probabilities. Start the Rust mode skeleton once its lifecycle/content boundaries are settled; do not commit to a completion date before measuring that recovery work.

All analysis helpers and Ghidra projects are kept in this directory. The game was not executed during this assessment. AvtoHmver's existing working changes were preserved.
