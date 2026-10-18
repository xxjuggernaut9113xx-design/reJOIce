# Newer reference beatmap contract

**Native follow-up:** `native-music-helpers/0x148302440.c` and the two
`native-parser-array-helpers` supersede the initial conservative reader policy.
Metadata/events are optional, missing BPM defaults to 120, object beats default
to Stroke, Rest/Accent are supported, unknown events become Custom, and at least
one object beat is required. Optional difficulty and beat/event duration fields
are retained. Metadata offset is not added to timestamps. Native parsing sorts
beats by time and events with comparator `0x1482d2c40`: when timestamps differ by
at most 0.0001 seconds, MediaSwitch precedes Background, then CycleMedia, then
other events. The sort is unstable; file tie order is not the runtime contract.
The JSON corpus observations below remain valid, but recommendations based only
on file order or the limited shipped vocabulary are superseded by this recovery.

Inspected 2026-10-17. Scope: all ten shipped `CockHero/beatmaps/*/beatmap.json` files and their WAV headers, plus reconstruction source. The original program was not launched. This report records direct JSON/source observations, not REA decompilation or runtime evidence; it has no REA Evidence IDs.

## Observations

**BM-01 — Container and fields.** Each song folder contains exactly `beatmap.json` and `song.wav`. Every JSON root has `meta`, `beats`, `events`; there is no `sections` member. Every metadata object contains string `title`, `artist`, `author`, `audioFile` and numeric `duration`, `bpm`, `offset`. Every beat contains numeric `time` and string `type`; all 5,734 supplied beats have type `stroke`. Every event contains numeric `time` and string `type`, `value`. In particular, `cycle_media` has the literal string `"true"`, not a JSON boolean.

**BM-02 — Audio and units.** All WAVs are RIFF/WAVE format 1 PCM, 44,100 Hz, 16-bit stereo, 176,400 bytes/second, block alignment 4. For every file, `meta.duration` exactly matches WAV `data` chunk size divided by byte rate. Thus metadata duration is seconds; beat/event times are strongly consistent with seconds on that duration scale. Do not interpret these large irregular time arrays as BPM ticks or regenerate them from metadata BPM.

**BM-03 — Order and coverage.** Every beat array is strictly increasing with no duplicate beat times. Every event array is nondecreasing and contains simultaneous events. All supplied beat/event times fall within [0,duration]. Beat arrays have intros and outros; final beat is before audio end in all maps. `Kinda_Quirky_Tho` ends its last event at 163.1085662841797 seconds but its last beat is 170.6594123840332 and audio lasts 172.51120181405895. Completion must not be inferred merely from event exhaustion.

**BM-04 — Event vocabulary.** Across all maps there are 3,876 events:

- `cycle_media`: 3,597, value `true`.
- `media_change`: 177, values `slow`, `medium`, `fast`, `cum`, `succubus`.
- `background`: 54, values `normalbeatbackground`, `mercybackground`, `successfulcumbackground`, `succubusbackground`, `tauntbackground`, `temptationbackground`.
- `cum_event`: 20, values `start`, `end`; one pair per song.
- `disable_break`: 28, values `start`, `end`; absent in three songs.

**BM-05 — Simultaneous ordering is not uniform.** Cake's first events at 0.12480722367763519 are `cycle_media`, `media_change(slow)`, `background(normalbeatbackground)`, before its first beat at 14.872380256652832. Instructions Unclear starts at 0.003999948501586914 with `media_change(slow)`, `cycle_media`, `background(normalbeatbackground)`. Preserve input event order and original indices when storing the data; do not impose a global type priority from one example.

**BM-06 — Offsets are real metadata.** Instructions Unclear has offset +0.004, Lil Brat -0.013, Pleasure Place +0.016; the others have 0. Instructions Unclear's first beat and first event already approximate +0.004. This observation alone does not establish whether offset has been baked into timestamps, is added at load, or is used only by the editor. Do not apply it twice based on naming.

## Complete file inventory

Paths below are relative to `C:/Users/webma/Downloads/cock-hero-windows (1)/Windows/CockHero/beatmaps/`. Hashes identify `beatmap.json`, SHA-256. Counts include all records, with no filtering.

- `Cake`: beats 379, events 215; duration 156.28045351473924; BPM 129; offset 0; first/last beat 14.872380256652832 / 141.37469482421875; hash `EC8BAA533B33CDB65D11523B11AB1ECBD8A0A4360F155716E05FC20825882B76`.
- `Fantasy`: beats 570, events 423; duration 237.79997732426304; BPM 147.15; offset 0; first/last beat 2.3713378608226776 / 229.59890747070312; hash `0C06304A81C0D00AD9D414CC182E4CEF0655ADA34B75A454D61D7F2AA6EE8474`.
- `I_Am_Just_a_Slut`: beats 745, events 454; duration 264.799977324263; BPM 178.21; offset 0; first/last beat 3.0185940265655518 / 258.6935119628906; hash `CC74F6EF9C4AB20DFAE7036684379DCBD47BABDB614B55D9D59C45FE91DF7652`.
- `In_Your_Head`: beats 704, events 495; duration 274.919977324263; BPM 148.61; offset 0; first/last beat 8.56816291809082 / 273.8213195800781; hash `75CA7A3FBEC394379D69A1818ED7C6EC935282BE23E2E1E7EE98500ECA88B402`.
- `Instructions_Unclear`: beats 353, events 271; duration 188.99736961451248; BPM 126.94; offset +0.004; first/last beat 0.003999948501586914 / 173.37582397460938; hash `D19232E8FC9FC5549104E58E671EFD0C4E7D6C7FE0597368997CDEA04FE3B9E1`.
- `Kinda_Quirky_Tho`: beats 436, events 299; duration 172.51120181405895; BPM 128.09; offset 0; first/last beat 0.4527890980243683 / 170.6594123840332; hash `BF26779EC006FEEE56F1B7B30AB731BD94A7566572CD80851881F10847AC7102`.
- `Lil_Brat`: beats 525, events 403; duration 245.39997732426303; BPM 126.04; offset -0.013; first/last beat 2.146456718444824 / 240.2089385986328; hash `6B8E306870421CCE9C477B0EE98C36360104B62507E3A995AC6811CAE0257409`.
- `Pleasure_Place`: beats 674, events 363; duration 254.83997732426303; BPM 142.6; offset +0.016; first/last beat 6.796225547790527 / 251.8597412109375; hash `4BE75EC48FFC375B7484D23AB9D9E5D52671B4E41A14F96AB8817CF5644B27CE`.
- `Say_I_m_Yours`: beats 627, events 527; duration 251.87997732426305; BPM 161.51; offset 0; first/last beat 3.0185940265655518 / 249.0107879638672; hash `49CE293FAF2830A493625D3D094A855FCFFE94AB92E7638134F4A35044D8D437`.
- `YOLO`: beats 721, events 426; duration 232.71997732426303; BPM 166.47; offset 0; first/last beat 9.729161262512207 / 230.13296508789062; hash `09B788DCA908B0B45161119A24229B8870F716DBE721F9F39D801DCD0DA243CA`.

Artist strings are preserved data: In Your Head uses `ME 2 PLEASE`, whereas other ME2PLEASE songs use `ME2PLEASE`. Every author is `Official`, every audioFile is `song.wav`.

## Inferences and unresolved runtime semantics

- A section is likely represented by state-changing events rather than a separate sections array. `cum_event` and `disable_break` start/end values likely establish time windows. State transitions, permissions and gameplay consequences require code evidence.
- `media_change` likely selects a content category, and `cycle_media` likely advances the chosen media. Equal-time ordering and whether a category change itself cycles content are unverified.
- Background names closely match existing reconstruction background resources after appending `loop`. Existing style mapping is normal=3, mercy=2, successfulcum=5, succubus=6, taunt=8, temptation=9. This is a reusable adapter candidate, not proof of newer dispatch logic.
- Beat time likely represents the audio-aligned target hit time, with visual travel scheduled earlier. Confirm with newer `StartFromBeatmap` / queue-building implementations before integrating. Near-zero first beats require explicit pre-roll/clipping policy; the data does not answer it.
- Unknown: offset sign/application, playback clock authority, calibration interaction, pause/break/seek behavior, tie ordering between beats and events, empty maps, accepted optional fields/types, error tolerance, completion timing/rewards, allowed beatmap paths/audio formats, and whether all events alter persistent state.
- Newer `native-symbol-addresses.json` contains named entry points `UBeatSpawnerManager::StartFromBeatmap` at `0x148321290` and `StartFromBeatmapWithMediaSync` at `0x1483213f0`. These addresses are pointers for follow-up analysis only; this report did not decompile them and does not treat names as execution evidence. The symbol inventory's coverage of MusicModeManager is not established.

## Reconstruction gap and safe first implementation slice

Inspected `RecoveredBeatTimeline.h/.cpp`, `RecoveredSession.h`, `RecoveredBeatTests.cpp`, `RecoveredDynamicMusicTests.cpp`, `RecoveredPostGame.cpp`, and `RecoveredCardDispatch.cpp`. Source searches for beatmap/song.wav/MusicMode found no corresponding importer or mode. This is bounded to the current `UnrealReconstruction/Source/CockHeroRecovered` tree.

The existing timeline builds a repeating `FRecoveredBeatPattern.IntervalMultipliers` sequence from base interval, speed and stroke count. It supports rests, generated fire/hit events, pause/resume, calibration and modifier rebuilding; its completion means generated strokes are consumed. `PlayRecoveredMusic` switches among four imported background loops by card type. Neither interface represents a song's authored absolute times, metadata, control event stream or external WAV lifetime. Applying the old queue generator or speed/stroke rebuilding to these files would discard authored timing and control events.

Implemented first slice: a non-playing beatmap reader, leaving all existing gameplay paths intact. Interfaces in `UnrealReconstruction/Source/CockHeroRecovered/RecoveredBeatmap.h/.cpp` are reconstruction design, not claimed recovered ABI:

- `FRecoveredBeatmapMetadata`: Title/Artist/Author/AudioFile strings, Duration/Bpm/Offset doubles.
- `FRecoveredBeatmapBeat`: Time double, Type string; array position retains source index.
- `FRecoveredBeatmapEvent`: Time double, Type/Value strings; array position retains source index.
- `FRecoveredBeatmapData`: Metadata, Beats, Events arrays.
- `URecoveredBeatmapLibrary::ParseBeatmapJson(Json, OutData, OutError)` and `LoadBeatmapFile(JsonPath, OutData, OutAudioPath, OutError)`. They return raw values, original array order and metadata offset without scheduling or applying timing transforms. Discovery/catalog UI remains future work.

Reader policy: require correctly typed nonempty fields present in this corpus, finite numeric values, positive duration/BPM, ordered in-range timestamps (strict for beats, nondecreasing for events), and the recovered beat/event vocabulary. In addition to the five `media_change` values directly observed in the ten files, the parent investigation recovered `ass` and `boobs` in the newer Blueprint `HandleCategorySwitch`; both are accepted and covered by synthetic fixture variants. They are not claimed as present in the shipped beatmap corpus. Unknown types/values fail with a located error instead of silently dropping events or inventing behavior. These strict reader policies are conservative reconstruction choices; the original program's acceptance behavior remains unknown. Empty arrays can be inspected, without declaring them playable. Failures leave prior outputs unchanged. The parser does not sort, clamp, synthesize, discard records, derive a BPM grid, or access audio. File loading uses UE encoding-aware utilities, resolves `audioFile` lexically within the selected song folder and requires that file to exist; it neither decodes nor validates audio contents. Original inputs remain unmodified.

Verification added in `RecoveredBeatmapTests.cpp`: a small synthetic fixture covers all observed event values and raw timing/offset/order, invalid/missing/wrong-type/nonfinite fields, unknown types/values, timestamp bounds/order, null items, empty arrays, UTF-8/UTF-16 loading, missing audio/JSON and escaping/absolute audio paths. Tests create an isolated Saved/Automation folder and remove their fixtures; they have no download-path or song dependency. Existing card timeline and four-loop dynamic music tests are unchanged. Build/test execution is delegated to the parent agent's shared build, not performed by this recovery worker. The direct corpus inspection above confirmed schema/counts; the C++ parser still requires execution against the originals to confirm its corpus acceptance of all ten files.

Before any playback implementation, recover native loader/event dispatch/clock behavior and confirm any differences from these conservative reader policies. Parser completion alone must not be labelled Music Mode reconstruction.
