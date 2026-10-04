# reJOIce

Saved static analysis and an editable partial Unreal reconstruction of the supplied V0.04 build.

**To continue on another machine, follow [START_ON_OTHER_MACHINE.md](START_ON_OTHER_MACHINE.md).** It covers the private release downloads, SHA-256 verification, folder restoration, tool versions, media paths and build commands.

- **Targeted slice:** complete at 712 matching PDB symbols, 390 eligible functions and 390 exported records. This work has not been repeated.
- **Full-image checkpoint:** 573,011 functions and 43,658,219 instructions saved in `CockHeroFullImageResumed`. The run timed out and encountered a Java heap-memory error; code analysis is still incomplete. The database and logs are available for continuation with more memory.
- **Blueprint coverage:** 134 assets in the function-analysis reports, with 1,225 decoded UFunctions. Original cooked containers and derived decoding files are included.
- **Reconstruction:** editable Unreal 5.3.2 source and assets, plus the media files referenced by the current project. The repaired patch passed a fresh 39-test run on 2026-10-03 (zero warnings/failures); the earlier 37-test report is historical. The game remains unfinished; see [handoff](UnrealReconstruction/HANDOFF.md).

Large databases, source materials and media are [private release assets](https://github.com/xxjuggernaut9113xx-design/reJOIce/releases/tag/materials-v004). The [original materials manifest](Materials/materials-manifest.json) and [latest transfer manifest](Materials/transfer-manifest.json) record filenames, sizes and hashes. Downloaded archives are restored by `Materials/Scripts/restore_workspace.py`.

The original files, saves and editable project were preserved. The shipping game has not been executed by this work. Tools and build caches are installed or regenerated separately.

The 2026-10-03 supplied reconstruction patch has a separate [integration handoff](UnrealReconstruction/RECONSTRUCTION_COMPLETION_HANDOFF.md), which distinguishes compatibility repairs and verified checks from remaining placeholders.

The later [Ghidra gap-fill handoff](UnrealReconstruction/RECONSTRUCTION_COMPLETION_HANDOFF.md) records the 2026-10-03 patch, a fresh 39-test run, and remaining limitations.

The 2026-10-04 final supplied patch was reviewed and repaired. The Windows editor build and **40 regression tests** passed (zero test warnings/failures). See the [final patch handoff](UnrealReconstruction/FINAL_GAP_PATCH_HANDOFF.md) for fixes and remaining scaffolding.
