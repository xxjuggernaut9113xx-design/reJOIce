# Reconstruction packaging validation

First complete `NEWER_CONTENT_IMPORT.md` and the full editor recovery automation
suite. The selected configuration must explicitly set `UseNewerProgression=True`
under `[Recovery.Content]`, stage `Recovery/Definitions` as UFS, and always cook
`/Game/Recovery/Newer20261017`. Baseline assets remain independent.

Run the fail-closed preflight from the project directory:

```powershell
python Scripts/verify_packaging_readiness.py --source-root 'C:/Users/webma/Downloads/cock-hero-windows (1)/Windows' --report RecoveryEvidence/newer-packaging-preflight.json
```

This validates source manifests with UTF-16/BOM support, the selected base
manifest, movie and beatmap directories, verified imported tables, all 146
versioned texture files, runtime alias coverage, and required staging/cooking
configuration. A preflight pass does not establish packaged behavior.

Full seven-pack source dialogue is staged under `Recovery/Definitions` as 8,350
deduplicated Bink streams. Runtime playback verifies a stream checksum and its
dimensions before decoding bounded PCM into a transient procedural sound. All
8,398 source table rows are retained. The 48 unavailable original source paths
are listed in `newer-20261017-dialogue-source-inventory.json` and verified against
the full shipped IoStore directory; playback never substitutes another pack.
`newer-20261017-dialogue-validation.json` records the verified staged hashes and
catalog digest. The editor automation test `NewerSourceDialogueAudio` must decode
representative PCM for every pack before packaging results are accepted.

Build a separate Development package after the editor exits:

```powershell
& 'D:/Program Files/Epic Games/UE_5.3/Engine/Build/BatchFiles/RunUAT.bat' BuildCookRun -project='E:/reJOIce/UnrealReconstruction/CockHeroRecovered.uproject' -noP4 -unattended -utf8output -platform=Win64 -clientconfig=Development -build -cook -cookall -allmaps -stage -pak -archive -stagingdirectory='E:/reJOIceRecoveryPackage/Staging' -archivedirectory='E:/reJOIceRecoveryPackage/Archive' '-ubtargs=-MaxParallelActions=2 -NoPCH' -NoXGE
```

`-cookall` retains widgets, manager Blueprints and baseline resources loaded by
native string paths, which map dependency discovery alone cannot retain.
Retain the complete UAT log and exit code. Inspect the package log for failed
loads, missing packages, cook errors, and unresolved native classes. Verify that
`newer-20261017-mode-data.json`, progression definition and resource aliases are
staged in the package's UFS payload. Validate packaged asset registry coverage
for all five newer tables and all 146 referenced textures. Run the reconstructed
package with the explicit selected source root:

```powershell
& 'E:/reJOIceRecoveryPackage/Archive/Windows/CockHeroRecovered.exe' '-RecoveredSourceRoot=C:/Users/webma/Downloads/cock-hero-windows (1)/Windows' -log
```

Confirm main-menu routes, Classic/Tower/Playlist starts, source manifest import,
artwork, audio and movie display, newer inventory purchases and use, completion,
challenge updates, rewards, profile backup/save/reload, and return to menu. Keep
hardware testing of external devices explicit in the resulting evidence. The
source executable is never used as the reconstruction launch target.
