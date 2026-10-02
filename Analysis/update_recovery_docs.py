from pathlib import Path

root = Path(__file__).parent
p = root / 'RECOVERY_STATUS.md'
s = p.read_text(encoding='utf-8')
s = s.replace('A minimal Function schema permits UFunction decoding; it does **not** decode class defaults. Cooked class/default-object exports still need complete mappings.', 'The initial minimal Function schema decodes UFunctions only. Expanded reflection mappings and an independent UE5.3 reader now recover eight selected class default objects; all eight serialized payloads rebuild byte-for-byte. These are serialized defaults, not a complete account of native constructor or initialization behavior.')
s = s[:s.index('These are cooked runtime packages.')] + '''## Default objects and control flow

Recovered 528 declared properties across 19 selected classes/structs. Eight selected manager/save default objects have exact payload round trips; see [defaults](blueprint-default-values.json) and [checks](default-roundtrip-check.json). Twelve selected Blueprint enums also round-trip exactly, including EasyMode, NormalMode and InsaneMode.

Five difficulty functions have validated instruction sizes and jump targets, with three static branch traces apiece. Initialization overwrites several item probabilities: NormalMode sets break/slowdown/boner-pill rates to 15/15/50, compared with serialized defaults 5/10/35. The named speed multiplier is recovered as a field assignment; its effect on perceived speed still requires tracing its consumers. See [difficulty traces](difficulty-branch-traces.json).

The main event graph contains 1,173 statements and 43,645 in-memory bytecode bytes. All 141 direct branch/flow targets and 60 named wrapper event entry points align with statement boundaries. This establishes structural consistency, not full runtime semantics. See [event graph](main-event-graph.json).

The [rules draft](RULES_SPEC_DRAFT.md) and [machine-readable rules](game-rules-draft.json) collect three difficulty configurations, eight serialized default objects, 62 pattern slots, 31 event records and 111 progression rows. Pattern slots are not a unique-pattern count; event records include entries whose runtime eligibility remains unresolved. Full parity remains unverified.

These are cooked runtime packages. Original editable Blueprint graphs and the original Unreal project have not been recovered. Next: trace startup, event eligibility, session outcomes, native progression and timing consumers; recover remaining settings/audio/save/device behavior; then compare controlled runtime observations. The original game has not been executed and AvtoHmver application files have not been modified.
'''
p.write_text(s, encoding='utf-8')
p = root / 'INTEGRATION_PLAN.md'
s = p.read_text(encoding='utf-8')
s = s.replace('Class defaults, complete event-flow interpretation, and behavioral checks remain necessary; the full gameplay specification is not complete.', 'Eight selected class-default payloads and twelve Blueprint enums now round-trip exactly. Five difficulty functions have validated static branch traces; the main event graph has 141 aligned direct branch/flow targets and 60 named entry points. The [rules draft](RULES_SPEC_DRAFT.md) captures this evidence, including difficulty initialization overrides. Startup/outcome semantics, remaining systems and runtime comparisons still block a complete gameplay specification.')
s = s.replace('The principal dependency is decoding the Blueprint/data-table layer. Asset names show its scope but do not reveal full transitions, probabilities, default values, resource formulas, or UI interactions.', 'The principal dependency is completing the behavioral interpretation of the decoded Blueprint/native layer. Selected defaults, difficulty assignments, beat patterns and progression tables are recovered, but startup sequencing, event eligibility, outcomes and UI interactions are not fully verified.')
s = s.replace('The next implementation-ready deliverable is the **versioned game rules and parity ledger**, produced from the complete-image native analysis, Blueprint/data-table decoding, and isolated behavior traces.', 'An initial versioned [machine-readable rules draft](game-rules-draft.json) is available. The next deliverable is a complete **game rules specification and parity ledger**, extending this draft with native call interpretation, startup/outcome traces and isolated behavior comparisons. Explicitly apply difficulty initialization: copying serialized defaults alone reproduces incorrect item probabilities.')
p.write_text(s, encoding='utf-8')
p = Path(r'C:\Users\webma\.cursor\projects\empty-window\canvases\cockhero-AvtoHmver-integration.canvas.tsx')
s = p.read_text(encoding='utf-8')
s = s.replace('Map class defaults, trace branches; add card, modifier and resource domain', 'Trace startup/outcomes and eligibility; add card, modifier and resource domain')
s = s.replace("['14 manifests','Already extracted local content packs']", "['8 default objects','Exact serialized payload round trips']")
s = s.replace('Zero raw-bytecode fallbacks; class/default-object mappings and branch interpretation remain incomplete', 'Zero raw-bytecode fallbacks in initial selection; full semantic coverage remains incomplete')
s = s.replace("['Unreal Engine 5.3.2 build 29314046 installed'", "['8 default objects and 12 Blueprint enums','All selected serialized payloads rebuild byte-for-byte'],\n        ['5 difficulty functions; main event graph mapped','Three static cases per function; 141 aligned targets and 60 named entry points; runtime parity unverified'],\n        ['62 beat-pattern slots and 31 event records','Rules draft preserves data; unique patterns and event eligibility require interpretation'],\n        ['Unreal Engine 5.3.2 build 29314046 installed'")
s = s.replace('Complete class-default mappings and trace event-graph branches, then correlate decoded Blueprint calls and progression rows with native functions and original-game behavior.', 'Trace startup, outcomes, event eligibility and timing consumers; correlate decoded calls and progression rows with native functions and original-game behavior. Difficulty initialization overwrites several serialized item rates and must be reproduced.')
p.write_text(s, encoding='utf-8')
