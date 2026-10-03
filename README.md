# reJOIce

Static-analysis evidence, original continuation materials and an editable partial Unreal reconstruction of the supplied V0.04 build.

Start with [continuation instructions](Materials/CONTINUATION.md) and the [materials hash manifest](Materials/materials-manifest.json). Large files are private [release assets](https://github.com/xxjuggernaut9113xx-design/reJOIce/releases/tag/materials-v004); authentication is required.

- **Targeted slice:** complete at 712 matching PDB symbols, 390 eligible functions and 390 exported records. Verified without repeating exports.
- **Complete image:** readable full PE/PDB database; the earlier 300-second run was exhausted by PDB application. Analysis resumed on a preserved copy with a 7200-second limit. The released full-image database is the preserved pre-resumption snapshot. Final long-run coverage is still pending; see the manifest and verification checkpoint. Whole-program decompilation is not claimed.
- **Blueprint coverage:** 134 assets represented in the function-analysis reports and 1,225 decoded UFunctions. Cooked containers support further decoding; editor node layouts remain stripped.
- **Reconstruction:** editable Unreal 5.3.2 project with a historical 37-passing-test checkpoint. It remains incomplete; see [handoff](UnrealReconstruction/HANDOFF.md).

Analysis contains saved pseudocode, evidence, scripts and three complete helper .rep databases. Zero-byte .gpr markers are normal; each database was actually opened read-only. These helper databases are preloaded scratch projects; the completed slice database is separately downloadable.

Original files and saves are preserved. The shipping executable has not been run. Build caches, duplicate extractions, runtime media and bundled tools are excluded. No redistribution license is asserted for recovered third-party material.
