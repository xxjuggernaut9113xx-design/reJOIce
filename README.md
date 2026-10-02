# reJOIce

Editable partial Unreal reconstruction and Ghidra analysis of the supplied shipping build.

- `Analysis/`: Ghidra decompilation outputs and databases, decoded evidence, verification fixtures and analysis scripts.
- `UnrealReconstruction/`: Unreal Engine 5.3.2 project, editable assets, C++ source and handoff notes.
- `Verification/automation-index.json`: saved report of 37 passing tests; no failures or warnings. This is a historical checkpoint, not a new CI run.

Start with `UnrealReconstruction/HANDOFF.md`. The reconstruction is incomplete. Original game media remains an external dependency. Build caches, compiled binaries, tools, duplicate cooked extractions and temporary projects are excluded. No original executable or original saves are included. No redistribution license is asserted for recovered third-party material.
