# Final supplied gap-fill patch: integration and limits

Input: `ghidra-gap-fill-final.patch` supplied by the user on 2026-10-04. Integrated over `a684caf74da3eb301e00a8d4d452cf2cbd4990c2`; the input repeated parts of the earlier patch. Earlier tag delegate lifetime and checked-state fixes were retained. Source files were merged, not regenerated. Original game files, saves, and reconstructed assets were preserved.

## Repairs made during review

- Removed the store-completion callback recursion and synchronous media-failure redraw recursion.
- Made the unimplemented device transport report failure, rather than a successful connection.
- Isolated named save operations under `CockHeroRecovered_Named_`, rejected path-like names and existing-slot overwrite, initialized new snapshot defaults. Loading remains explicitly disabled until target switching and rehydration are implemented; listing is still a stub.
- Removed duplicate challenge reward grants and duplicate XP text; the existing challenge tracker already grants rewards. Removed replay of per-event cumulative metrics at settlement and the second win-counter increment. Win state now comes from the recorded outcome rather than absence of a loss.
- Recorded regular coin awards in session earnings, connected active modifiers to XP, validated lifetime-load values before casting, and report failure from the final progression save. Settlement still needs transaction/retry work.
- Recovered all 27 preference widget names, actual save keys, and bool/string/enum/count conversions from the original `VideoSettingsMenu/InitDefaultsFromSaveGame` instructions. Fixed Borderless mapping; graphics setters apply resolution, screen mode and FPS. Removed the incorrect interpretation of stroke multiplier as a visibility setting.
- Connected the existing calibration button to `WBP_CalibrationUI`; load the saved calibration profile at ordinary game-instance startup. Added audio slider controller-commit callbacks.
- Read tags from the unfiltered manifest before a session, included all seven decks in fallback discovery, used three columns and the real `CheckBox`/`TagString` controls, retaining delegate objects safely.
- Added failed-session-start cleanup, sequence delegate teardown and inventory/notification reset. Fixed Escape/P pause consistency and removed the patch's incorrect Q-to-quit mapping. Remaining shortcuts are not certified as original mappings.
- Corrected animation object lookup and selected names, checked optional overlay packages before loading, guarded the meter threshold and disabled-state media effect, removed duplicate loot presentation notification, and made the defensive overlay dismissal callback weak.
- Made shuffle actually shuffle the selected deck, honored explicit repeat-disable while preserving default refill, connected video-loop state to current/future media players, and avoided duplicate file-import counts.
- Preserved immediate item use on existing assets without a separate use button, so new inventory scaffolding does not strand purchased items.

## What this does not establish

The supplied patch contains approximations and scaffolding. New challenge, modifier, import, cheat, and save-slot classes are not automatically attached to existing assets. Candidate modifier-conflict pairs, reward rolls, event penalties/cooldowns, dialogue paths and most widget names still need evidence-driven reconstruction. A callable method, a saved setting, or a matching notification name is not proof that the full player flow works.

The results master still needs its child-screen lifecycle. Importing does not yet build playable packs. Auto-draw has no completion consumer. Hardware transports, original save compatibility, original editor graphs, complete native analysis, full GUI playtests and packaged/clean-machine validation remain outstanding. No full-game completion or original-runtime parity is claimed. The shipping game was not executed.

Build/test details and input hashes are recorded in [final-gap-patch-verification.json](RecoveryEvidence/final-gap-patch-verification.json). The comprehensive missing/partial-feature audit is updated separately after pushing this integration.
