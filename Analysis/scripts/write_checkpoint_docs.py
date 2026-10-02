from pathlib import Path

root=Path(__file__).resolve().parents[1]
readme='''# CockHero recovered Unreal project

This is a separate, editable **partial reconstruction** for Unreal Engine 5.3.2. The active task is an Unreal C++/Blueprint recreation. Rust and AvtoHmver integration were cancelled. Full-game completion and parity are not claimed.

## Verified checkpoint — 2026-10-02

The editor module builds with UE5.3.2-29314046. All **27 CockHero.Recovery automation tests pass**, with zero failures or unexpected test warnings. The saved report is `Saved/Automation/index.json`; process exit status alone is insufficient validation.

Asset validation checks **115 table rows** (55 challenges, 20 levels, 36 player cards, four heat-category rows), 39 player defaults and eight rebuilt Blueprint classes. Eight selected gameplay default objects and all 107 widget default objects decode and re-encode byte for byte. Widget class metadata includes 153 original property bindings; most dynamic bindings remain unimplemented. The workspace map is an inspection scene, not the original game map.

There are **107 editable widget Blueprints**, containing 1,597 widgets and 1,490 reconstructed child links. Their layouts derive from 3,135 byte-verified serialized UI object payloads. The original font, **170 textures** and **seven sounds** are recreated as editable assets. Tests verify source dimensions/color space, exact font/audio payloads and **858 widget resource references**. The widget recovery report has **zero unresolved resource references**. The video brush uses a new editable display material with the verified original UI domain; its original expression graph was stripped and visual equivalence remains unverified. Four main-menu routes, settings tab switching with original styles, and voice-preview stopping are reconstructed in C++. Twenty-seven constant tooltip bindings attach and display the exact source text in tests. Settings background refresh/playback currently emits requests whose media consumers are unfinished. Full original widget event graphs, property bindings and animations remain unfinished; compiling a widget does not establish functional screen parity.

The media adapter exposes a dynamic video-display material and its texture binding is tested without decoding a video. Rule tests cover **14,076 static cases** derived from decoded bytecode or native instruction models. These include state changes, session accounting, event weights/filtering/dispatch, card timing and decks, pattern adjustment, XP/levels, outcome entry points, recent-draw tracking and beat queues. They are not observations of the original executable running. Outcome tests exclude delayed continuations and complete postgame behavior.

The native beat adapter supports signed rest entries, pause/resume, center callbacks, speed changes and future-entry count multiplication. Source quirks are retained, including counting rest entries in totals after count modification. Invalid timing and excessive allocations are rejected explicitly. XP thresholds come from native constants. Original level table names do not match native `Level_N` lookups; the source reward-lookup behavior is preserved rather than silently corrected.

## Content and evidence

`Content/Recovery` contains editable definitions, progression tables, UI and resources. `Content/NewSetup` contains rebuilt manager Blueprint shells backed by new C++ parents. `RecoveryEvidence` contains decoded values, selected function bodies, native pseudocode/instructions, exact round-trip results and static fixtures. The original Blueprint node layouts cannot be recovered from this cooked build; replacement event graphs and C++ behavior must be reconstructed.

The media adapter reads the original 487-entry pack manifest and resolves existing files without copying or changing them. Media filtering and deck behavior are tested. GUI playback, audio/video synchronization and complete session presentation have not been validated. Device state is modeled; hardware adapters are not connected.

## Remaining work

Startup/settings/menu handlers; complete draw and event/card bodies; challenge and reward execution; outcome continuation/postgame flow; full progression/challenge persistence and original-save compatibility; full media/audio/timing integration; animations and remaining resources; device adapters; end-to-end playable-session and editor validation.

The original shipping executable has not been executed. A separate recovery save adapter initializes from verified source defaults and passes an in-memory Unreal save/load round trip, retaining nested fields. Its only runtime slot is `CockHeroRecovered_Standalone_v1` under this project's Saved/SaveGames directory. Full progression/challenge consumers and original-save compatibility are unfinished. Original game files, saves and AvtoHmver are unchanged. Keep Unreal Editor closed during module builds and asset regeneration; reopen after the reconstruction is ready for final review. The user requested opening Unreal once complete.

MSVC14.44 compatibility is confined to the project's forced-include header. The engine installation is unchanged. Build with `-NoUBTMakefiles` and the Windows SDK bin directory on PATH; older cached makefiles captured a missing `mt.exe` environment.

Resource recovery scripts are in `Scripts/`; external static decoders are in the parent analysis directory. They write to this isolated recovery workspace. Older generator scripts may overwrite newer documentation/code and must not be run blindly. Historical early status text is preserved in `RecoveryEvidence/README_early_recovery_history.md`.
'''
status='''# Recovery status — 2026-10-02

The active target is a full Unreal C++/Blueprint recreation, followed by opening it in Unreal. Rust and AvtoHmver integration were cancelled. **The full game is not complete.** The separate project is `UnrealReconstruction/CockHeroRecovered.uproject`; Unreal Engine 5.3.2-29314046 is installed on D:.

The latest compiled editor module and saved assets pass **27 automation tests**, with zero failed tests or unexpected test warnings. Asset refresh verifies 115 table rows, 39 player defaults and eight manager Blueprint shells. Exact default-object round trips cover eight gameplay objects and all 107 widget objects; 153 original property bindings are decoded. Selected bytecode recovery now covers 1,225 UFunctions across the earlier gameplay set and newly decoded widgets; this is not all game functions. Four main-menu routes, settings tab switching/styles and 27 constant tooltips are reconstructed and pass generated-widget tests. Settings background-media consumers and controls inside the tabs remain unfinished.

UI recovery now contains 107 editable widget Blueprints, 1,597 widgets and 1,490 child links derived from 3,135 byte-verified UI payloads. Native resources have been recreated as 170 editable textures, the original horizon font and seven decoded sounds. Tests validate 858 resource references, source dimensions/color space and exact saved font/audio payloads. There are zero unresolved resource references. The background-video material is an editable replacement with the verified original UI domain; the original stripped expression graph and visual equivalence are not claimed. Original graphs, animation timelines and complete UI interactions are unfinished.

Static rule fixtures cover 14,076 cases, including native future-beat rebuilding, XP/level rules and synchronous outcome entry points. These fixtures model decoded instructions; the original executable has not run. A separate save adapter passes a memory-only serialization round trip; full startup/session execution, challenge/reward persistence, media synchronization, presentation and hardware devices still require reconstruction and end-to-end validation.

The editor GUI is closed so recovered assets and native modules can be refreshed without locks. Reopen when final reconstruction is ready, as requested. The original game, original saves and AvtoHmver remain untouched.

See `UnrealReconstruction/README.md` for current scope and gaps, `UnrealReconstruction/Saved/Automation/index.json` for test results, `UnrealReconstruction/Saved/reconstruction-validation.json` for table/default validation and `UnrealReconstruction/Saved/widget-recovery-report.json` for resource gaps. Earlier historical extraction/install details are preserved in `RECOVERY_STATUS_2026-10-01_HISTORY.md`.
'''
(root/'UnrealReconstruction/README.md').write_text(readme,encoding='utf-8')
(root/'RECOVERY_STATUS.md').write_text(status,encoding='utf-8')
print('Updated checkpoint documentation')
