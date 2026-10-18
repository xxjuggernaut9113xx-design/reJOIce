# Newer native music contract

## Follow-up recovery

The five follow-up bodies are retained under `native-music-helpers`, array
postprocessors under `native-parser-array-helpers`, and event comparator under
`native-event-comparator`. Native JSON parsing accepts optional metadata/events,
defaults BPM to 120, skips nonobject records, defaults unknown beat types to
Stroke and unknown event types to Custom, and succeeds only when at least one
object beat remains. Rest/Accent, metadata Difficulty, and per-record Duration
are supported. It does not enforce positive duration/BPM, timestamp bounds, or
input ordering. It copies metadata Offset without modifying beat/event times.

Beat records sort by time. Event comparator `0x1482d2c40` first compares time;
within epsilon 0.0001 seconds it prioritizes MediaSwitch (0), Background (6),
CycleMedia (5), then all other types. The epsilon was read as a double directly
from newer PE virtual address `0x14bf8cef0` using the saved section mapping.
Both array helpers use unstable sorting, so equivalent-key source order is not
guaranteed. Tick's sequential dispatch therefore consumes the sorted array.

The reconstructed reader matches this recovered acceptance/sort policy while
retaining two recovery-owned safeguards: failed parsing leaves caller output
unchanged, and its file loader requires existing audio inside the selected
beatmap folder. Those safeguards are not claimed as native behavior. The
historical first-nine-export analysis and its then-unresolved items follow.

Static evidence inspected 2026-10-17. The supplied original game was not executed. Sources are the matched newer PE/PDB addresses in `native-music-symbol-addresses.json`, reflected field layouts in `native-reflection-schemas.json`, enum values in `native-reflection-enums.json`, and focused Ghidra pseudocode in `native-focused/`. These are local retained evidence, not REA runtime records. Pseudocode can misrepresent prototypes/register arguments; unresolved calls and types remain identified below.

## Address and layout normalization

`Tick` at `0x148315ac0` receives the **secondary tickable-base pointer**, 0x28 bytes after the UObject pointer. Its calls to `GetCurrentAudioTime`, warnings and completion explicitly pass `param_1 - 0x28`. Therefore add 0x28 to Tick's field offsets before comparing them with UObject/reflection offsets. For example Tick+0x540 is UObject+0x568 (`bIsPlaying`), Tick+0x488 is UObject+0x4b0 (`BeatSpawnerRef`), Tick+0x278 is UObject+0x2a0 (`LoadedBeatmap.Beats`), and Tick+0x260 is UObject+0x288 (`LoadedBeatmap.Meta.Duration`). This alignment is strongly corroborated by multiple independent reflected fields.

`BeatmapMeta` has Title0x00, Artist0x10, Author0x20, **Difficulty0x30**, AudioFile0x40, Duration0x50, BPM0x58, Offset0x60. `BeatmapBeat` has Time0x00, Type0x08, **Duration0x10**, size0x18. `BeatmapEvent` has Time0x00, Type0x08, Value0x10, **Duration0x20**, size0x28. These fields go beyond the ten supplied JSON examples and the first conservative reconstructed parser.

## Clock, lead-in and pause

Direct arithmetic from `GetCurrentAudioTime` (`0x1482e9b40`), with all offsets below relative to UObject:

- If `bIsPlaying` (+0x568) is false, return0. If paused (+0x569), return frozen snapshot+0x660.
- When clock-started flag+0x648 is true, return `monotonicNow - origin(+0x638) - accumulatedPause(+0x668) + correction(+0x678)`.
- Otherwise, if pending-lead-in flag+0x649 is true, return `monotonicNow - scheduledStart(+0x640)`. This is negative during pre-roll. Otherwise return0.
- `monotonicNow` is QueryPerformanceCounter converted by engine globals. It is not the sum of frame deltas and is not directly the audio playback-percent value.

`StartPlayback` (`0x148314390`) requires loaded state, a resolved world, and a non-null BeatSpawner. It stores spawner/latency/media/travel-time arguments, clears pause/correction/cursor state, loads audio, obtains a Quartz clock, creates an audio component, and binds `OnAudioPlaybackPercent` (`0x1483020e0`). It computes `leadIn=max(IntroLeadInSeconds,0)` (reflected property+0x40), writes both origin+0x638 and scheduled-start+0x640 to `monotonicNow+leadIn`, sets the pending flag iff leadIn>0, and stores remaining delay+0x650. It initializes spawner mode via `StartFromBeatmap` (`0x148321290`) or `StartFromBeatmapWithMediaSync` (`0x1483213f0`), marks playing/unpaused, then calls `ScheduleDeferredAudioStart` (`0x14830f660`). These setup calls are observed; their internal Quartz callback/audio scheduling implementation is not in the first nine exports.

The latency-manager branch copies a profile and multiplies its float at+0x328 by **0.001**, storing seconds at music UObject+0x6c8. This quantity is added to beat target times in Tick. It is a separate quantity from metadata Offset. The exact profile-field name and helper predicate `0x148283d80` were not recovered in this schema export; do not label it a particular named user calibration control without further evidence.

`PausePlayback` (`0x148303850`) no-ops when stopped/already paused; otherwise snapshots current audio time, marks paused, and records monotonic pause-start+0x670. During a future pending lead-in it replaces remaining delay with `max(scheduledStart-now,0)` and clears the deferred timer. Otherwise it calls audio helper `0x14670a680(component,1)` (consistent with pause; unresolved engine symbol). It invokes verified PDB `UBeatSpawnerManager::PauseSequence` (`0x148320060`).

`ResumePlayback` (`0x14830cbd0`) no-ops unless playing and paused. During pending lead-in it clears paused, sets origin and scheduled start to `now+remainingDelay`, and re-schedules deferred audio. Otherwise it clears paused, adds `now-pauseStart` to accumulatedPause, and invokes the same audio helper with0. It invokes verified `ResumeSequence` (`0x148320930`). Pausing pre-roll therefore preserves its remaining delay; ordinary playback excludes paused wall time.

## Tick ordering and beat/event timing

Observed order in `0x148315ac0`, after audio ramps: skip music progression when paused; if playing and spawner exists, sample audio time once, evaluate warnings, enqueue eligible beats, dispatch eligible events, update media plan, then check song completion. Source cursors advance through array order; Tick does not sort either input array.

- Beat enqueue eligibility is `beat.Time <= audioTime + LookaheadWindow` (reflected UObject+0x6b8). It uses authored Time before calibration adjustment.
- For each eligible beat, a separate look-ahead event cursor scans events with `event.Time <= beat.Time`. MediaSwitch enum0 updates predicted media category. CycleMedia enum5 sets the beat's cycle flag only if `abs(event.Time-beat.Time) < 0.02`. It prepares media before actual event dispatch. This is distinct from the ordinary event cursor.
- Rest enum1 advances the beat cursor without enqueueing a beat. Stroke enum0 and Accent enum2 enqueue; Accent receives CustomMultiplier1.5, ordinary beat1.0.
- Enqueued `FBeatEvent.TargetHitTime = beat.Time + profileAdjustmentSeconds`; `AbsoluteFireTime = TargetHitTime - suppliedTravelTime`. Negative fire times are not clamped in this routine. BeatNumber is source index+1 (rests count in numbering). PatternIndex is0.
- Interval comes from the next non-rest beat's authored time difference. When no later non-rest beat exists, the code uses60/BPM if BPM>0, otherwise0.5 seconds. It does not generate beat times from BPM.
- Event dispatch eligibility is `event.Time <= audioTime`, with no profile adjustment in this comparison. Due events execute sequentially in stored array order, after the complete due beat-enqueue pass. No global ordering of event types is imposed.
- Suppression flag UObject+0x56b causes DisableBreak enum8 and RestoreBreak enum11 to be consumed without event-history insertion or generic dispatch. Other event types continue normally.
- MediaSwitch enum0 updates current category, informs a present media controller, and calls the reflected OnMediaCategorySwitch delegate (+0x200). Dialogue enum1 calls OnDialogueTriggered (+0x218). CycleMedia enum5 resolves beat number/category, and conditionally invokes media helpers. Some other cases only log or update internal state before generic dispatch; their gameplay effects belong to OnBeatmapEvent subscribers.
- CumEvent enum3 is consumed without generic dispatch when a round-session is active, not endless, round number>=1, and current round is below total planned rounds. Final/inactive/endless branches reach generic dispatch. This condition is traced from the actual branches after offset normalization, not inferred from the enum label.
- For non-suppressed dispatched events, history stores authored timestamp, sampled audio time, type/value/duration and trims oldest entries when prior length>=15. The generic OnBeatmapEvent delegate (+0x158) receives the event after the case-specific action. The delegate call target itself remains an unresolved generated helper, but its destination offset matches native reflection.

Read directly from the newer PE `.rdata` using `pe-sections.json`: `0x14bf3cd30`=0.001, `0x14bf2ebf8`=0.02, `0x14bf2ec00`=0.5, `0x14bf56a40`=60.0, `0x14bf683b8`=-1.0, and `0x14bf56a90`=absolute-value sign mask0x7fffffffffffffff. This resolves numeric constants in the pseudocode without guessing them.

## Load, completion and stop

`LoadBeatmap` (`0x1482fdff0`) first reads the JSON file through an engine helper. On read success it immediately writes CurrentBeatmapJsonPath+0x2d0 and BeatmapFolderPath+0x2c0, initializing the library root when empty, **before JSON parsing succeeds**. It delegates actual parsing to `ParseBeatmapJson` (`0x148302440`). On parse success it copies metadata/beats/events into LoadedBeatmap, marks bBeatmapLoaded+0x2f0, refreshes preview/warnings and invokes OnBeatmapLoaded (+0x188). No load-time sorting or timestamp adjustment appears in this wrapper; such work could still occur inside the parser.

Tick completion is `audioTime >= LoadedBeatmap.Meta.Duration`, after due enqueue/event dispatch, calling `HandleSongComplete` (`0x1482f9c00`). It does not require event exhaustion, beat exhaustion, the final hit, or an audio-finished callback in the inspected Tick. The body of HandleSongComplete is needed to establish playback/round delegates, reward timing, playlist continuation and spawner cleanup. Do not replace it merely with StopPlayback.

`StopPlayback` (`0x148315400`) acts only while playing. It clears playing/paused/break/start/pending flags, clears deferred timer and media preloads, stops/releases audio and Quartz handles through engine helpers, calls PDB-verified `StopSequence` (`0x148321e70`), clears history/cursors/warnings/session reference pointers, and resets audio ramps. It does not itself call the reflected completion delegate in the inspected body. Stopping and completing are separate operations.

## Parser compatibility and remaining blockers

The first nine decompilations **do not include ParseBeatmapJson**. Therefore native acceptance of absent metadata, unknown event names/values, optional duration/difficulty, wrong types, empty arrays, timestamp disorder, negative/out-of-range times, and unknown root members remains unresolved. LoadBeatmap's wrapper cannot answer those questions. Its call target and exact PDB address are established; export `0x148302440` before claiming compatibility or tightening/loosening the current reader.

The first reconstructed parser's restrictions documented in `beatmap-contract.md` are deliberate conservative policies, not recovered native behavior. Reflection already establishes additional native metadata Difficulty and per-record Duration fields, so that restricted input vocabulary is not evidence of the native schema's full extent.

Metadata Offset is copied as metadata and is not read in the inspected StartPlayback, Tick or clock bodies. **Do not yet conclude that it is ignored globally**: the missing parser could bake it into record times. Likewise exact clock correction, Quartz start origin and delayed-start handling require `OnAudioPlaybackPercent` (`0x1483020e0`), `OnQuartzPlaybackStarted` (`0x148302240`) and `ScheduleDeferredAudioStart` (`0x14830f660`). Body-level follow-up is also needed for `HandleSongComplete`, cycle-media resolution and spawner clock consumption. This document establishes scheduling relationships from static evidence, not end-to-end runtime equivalence.
