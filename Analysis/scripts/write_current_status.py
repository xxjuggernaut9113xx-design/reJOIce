"""Write an honest current checkpoint from saved verification reports."""
from pathlib import Path
import json
root=Path(__file__).resolve().parents[1]
project=root/'UnrealReconstruction'
tests=json.loads((project/'Saved/Automation/index.json').read_text(encoding='utf-8-sig'))
assert tests['failed']==0 and tests['notRun']==0, 'Do not document a passing checkpoint before checking failures'
count=tests['succeeded']+tests['succeededWithWarnings']
text=f'''# CockHero Unreal reconstruction — 2026-10-02

The project is being handed off for the user to complete. Rust and AvtoHmver integration were cancelled. **The full game is not complete.** This is an isolated, editable partial reconstruction for Unreal Engine 5.3.2-29314046.

The current saved automation report records **{count} passing tests**, {tests['succeededWithWarnings']} with warnings, zero failures and zero tests left unrun. The report is `Saved/Automation/index.json`. Static fixtures cover 14,076 rule cases and 400 additional calibration cases derived from decoded instructions; they are not observations of the original executable running. New integration checks are separate from that fixture count.

Recovered assets include 107 editable widget Blueprints, 1,597 widgets, 1,490 child links, 184 textures, 29 sounds and the original horizon font. UI layout recovery comes from 3,135 byte-verified payloads. Five progression tables contain 131 rows: 55 challenges, 20 levels, 36 player cards, four heat categories and 16 modifiers. Exact default-object round trips cover eight gameplay classes and 107 widget classes. Selected bytecode decoding covers 1,225 UFunctions; 153 original property bindings are retained as evidence, with only selected behavior rebuilt.

Rebuilt startup opens the main menu, routes difficulty selection into a session, initializes media decks, automatically dispatches the first card and displays the selected original PNG. Headless startup/media smoke checks pass. Main-menu routes, settings tab styles, voice-preview stopping, 27 static tooltips and gameplay image/button bindings have generated-widget checks. The live HUD updates strokes remaining, coins, combo, duration and heat/cum/loot meters from the reconstructed session.

Gameplay implements verified rule adapters for weights, eligibility, draw multipliers, base pace cards, succubus and body frenzy card timing/decks/patterns, beat accounting, future beat rebuilding, XP/levels and synchronous outcome entry points. The draw dispatcher selects the event record using the weighted array index, retains the source's previous FoundEvent on a selection miss, and prepares each card once. Beat completion can request the next card through the connected dispatcher. Unsupported event bodies still fail explicitly.

Challenge adapters reconstruct initialization, session/lifetime requirement updates, best values, completion, tracking removal and reward claims from native instruction evidence. Typed rewards take precedence over legacy XP/point fields; claimed flags prevent repeat grants when progress exists. Challenge state has its own validated recovery JSON adapter and live metric routing. Progression, unlocked cards/modifiers and challenges use the separate recovery save slot `CockHeroRecovered_Standalone_v1`; original saves are never loaded. Original save compatibility is not claimed.

The media adapter reads the original 487-entry image manifest and resolves existing PNGs without copying or modifying them. Video material binding is tested, but menu background and idle animations are connected, while complete audiovisual synchronization and GUI presentation are unfinished. Source quirks are retained, including the original native level lookup/table-name mismatch. Original Blueprint node layouts remain stripped. Serialized animation payloads are recoverable: 357 animations across 72 screens have been saved as editable tracks with resolved references; nine screens still need specialized callbacks. Beat animation playback passes a live reconstruction smoke test.

Remaining technical work includes postgame navigation and session finalization, lifetime accounting and reward consumers, controls inside settings tabs, inventory actions, complete audio presentation, nine specialized animation callbacks, calibration offset integration, hardware adapters, and end-to-end GUI verification. Calibration timing, its screen bindings and isolated profile persistence are implemented and covered by tests; actual GUI interaction remains unverified. Some game-specific event behavior is still incomplete. Compiling assets does not establish full-game parity.

Unreal Editor remains closed during builds. It has not been opened as a finished game. See HANDOFF.md for opening and verification commands. The original shipping executable has not been executed. Original game files, saves and AvtoHmver are unchanged. Recovery C++ is under `Source/CockHeroRecovered`; editable assets are under `Content/Recovery` and `Content/NewSetup`; decoded evidence is under `RecoveryEvidence` and the parent analysis directory.

Build with `-NoUBTMakefiles -MaxParallelActions=2` and the Windows SDK x64 bin directory on PATH. MSVC compatibility is confined to the project's forced-include header; the engine is unchanged. Resource refresh can emit known cooked-version/import naming warnings, which are separate from automation warnings. Older generator scripts may overwrite current code or reports and should not be run blindly.
'''
(project/'README.md').write_text(text,encoding='utf8')
(root/'RECOVERY_STATUS.md').write_text(text,encoding='utf8')
print(f'Current status written from {count} passing tests; full_game_complete=false')
