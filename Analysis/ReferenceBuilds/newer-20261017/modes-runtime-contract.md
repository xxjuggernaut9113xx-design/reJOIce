# Reconstructed modes: source evidence and boundaries

Static evidence from the matched newer PE/PDB and retained decoded Blueprint
functions. This record does not claim observation of the original application.

## Tower

`native-round-runtime` contains the recovered StartRoundSession, SelectRoundOption,
CompleteRound, AdvanceRound, and EndRoundSession bodies. Sessions begin at round
zero. Selecting increments the round. CompletedRounds is the largest completed
round number, including failed rounds. FailedRounds is separate; a finite final
success with no failures is a session win. The final round uses tier six.

`native-round-constructor/0x1482cf740.c` establishes opening calibration tiers
2,3,4; difficulty progress defaults; adaptive target rates, normalizers and
weights; and primary reward weights. `native-round-adaptive` retains all five
adaptive helper bodies. The implementation uses the latest three round records
with weights .6/.3/.1, the source progress curve exponent .6, pressure easing
.2 and ramp .1, and tier weights `max(1-abs(progress-i*.25)*2.5,0)^2+.1`.
Ordinary draft lanes derive relief/base/risk tiers and shuffle tier/lane pairs.
The exact .75/.2/.8 draft thresholds were read from the PE; constants and bit
patterns are preserved in `native-round-adaptive-constants.json`.

`native-round-filters/0x1482fcc80.c` is a local helper without a matched public
PDB name. Its initial caller-supplied label says "incompatible", but the caller
at `GenerateModifiersForRound` removes entries when it returns **false**: it is
a compatibility predicate. `native-round-filter-strings.json` binds every
literal operand to the PE bytes. Mr. Money Bandz fits objective0, Hungry Succubi
fits0/2, Sacrificial and Demon Proof fit8, Double Time fits3, and the source
bitmasks govern Slow and Steady / Deal With The Devil. The implementation also
retains three recent objectives (`TrackRecentObjective`0x148316d30), avoiding
them when at least three eligible fresh choices remain.

`GameModeCustomizationScreen_WIDGET/Update_Objective_Index` has seven cases,
calling SetCurrentSessionObjective at offsets583,1064,2051,3046,4044,5021,6000
with values0,1,2,3,6,7,8. CoinFlip4 and Ruiner5 remain in native enums and the
schema but are not offered by the reconstructed production chooser. Their enum
membership and Ruiner parameter rows do not establish current selectable flows.
Native GenerateRoundOptions excludes Prejac6 and Tribute7 before the final
round and filters Edges3 until prior round statistics contain edges or
defensive item usage. The runtime follows those filters.

Objective parameters are rolled from the exact source objective/tier rows in
`newer-20261017-mode-data.json`; unsupported numeric difficulty remapping into
the older three-difficulty gameplay configuration is not silently asserted.

Final ordinary objectives grant a 60-second confirmation window rather than
completing the round automatically. Start-window metric19 is emitted at the
source start-window site49122. Source expiry resets meter0, always extends timer1
and edges3, and extends strokes2 / succubi8 when
`DoesNotCummingInWindowResetObjective?` is true (the newer CDO default is1).
The implementation extends per-round baselines by the original target, which
is algebraically equivalent to extending the source cumulative requirement.
For an explicit false setting on2/8 it uses the source EndSession successful
completion path; it does not misclassify expiry as an early-climax input.
Tribute7 retains its direct completion branch at79493→79223. Prejac6 expires
as a failure and accepts confirmation before its authored deadline.

## Playlist, breaks and progression

`native-music-constructor/0x1482ce640.c` establishes intro lead-in2 seconds,
lookahead4 seconds, break resume safety2 seconds, lowpass300 Hz and ramp1 second.
`native-music-break` establishes that a break suppresses beat spawning while the
song clock and control events continue. It is distinct from PausePlayback.
EndBreak discards beats through current audio time plus the two-second safety
window. Native completion/stop are separate operations.

`BP_GlobalManager/ExecuteUbergraph_BP_GlobalManager` offsets94854..95025 caches
the next beatmap, checks AreAllUpgradesMaxed and opens progression selection
when upgrades remain. The runtime now waits between tracks for one selection;
maxed upgrades continue directly. Upgrade values come from all three recovered
MusicModeProgressionUpgrade rows: duration5/8/12/15/18, max charges1/2/3/4/5,
recharge strokes500/400/300/250/180. Recharge consumes actual stroke deltas and
grants charges only below the resolved maximum. Recovery-owned profile keys
`Recovery.MusicUpgradeLevel.0..2` store the independent levels; this is not
original-save compatibility. Fresh Playlist entry resets these levels to1,
matching the fresh UMusicModeManager spawned at BP_GlobalManager26719 and its
constructor. Initial recharge progress250 follows BP_GlobalManager28053.
GrantBreak event9 (dispatch95345) grants one charge; this is not an initial
charge producer. Lowpass uses a dedicated MediaSound component.

Actual track audio is opened through a dedicated asynchronous MediaPlayer;
opening failures return to the menu with a visible error. Presentation time is
the recovered monotonic clock with explicit pause exclusion. Initial audio seek
aligns a delayed asynchronous open to that clock. This adapter is not a claim
of sample-exact Quartz reconstruction or independently measured audio drift.

Beatmap card categories6/7/8 map to the older recovery media deck indices4/5/6
for Cum/Ass/Boobs. The native card category remains unchanged for gameplay.
This adapter is exercised through live multicast event delivery with distinct
deck fixtures in `PlaylistMediaCategoryAdapters`.

Tower rewards are implemented separately by RecoveredTowerRewards and should
be reviewed against its focused native helper evidence. Headless component
tests do not independently establish audiovisual or packaged-runtime parity.

Classic customization now exposes the exact seven objective indices from
GameModeCustomizationScreen_WIDGET.Update_Objective_Index:0,1,2,3,6,7,8.
The source LastObjectiveIndex_Classic and LastObjective_* keys persist selection
and targets. The recovery chooser uses a validated integer input instead of
reconstructing the original slider layout. Classic and Tower share objective
thresholds and the source60-second release-window/reset transitions. Meter
completion emits CumEventOverride, repairing the earlier unmatched MeterOverride
event. Prejac accepts actual confirmation through its deadline; Tribute uses
the actual MilkingEvent producer. Classic threshold, meter/window, Prejac and
Tribute regressions exercise these routes.
Missing target keys use the exact newer SaveGame CDO values (timer300,
strokes1000, edges2, Prejac60, Tribute2, SuccuSlayer5), verified by the full
byte-identical CDO roundtrip in save-class-defaults.json. Classic index is
declared but omitted from the cooked payload and therefore defaults to0.

Fresh loadout presentation is recovery-owned. Its available pool and empty
five-slot baseline come from LoadoutEquipScreen_Widget: Classic unlocks all11
authored items; Tower selects one shuffled defensive and one offensive item,
excluding Resupply. Selected states are transferred as a pending serialized
snapshot after the fresh-session reset, not persisted as permanent upgrades.
