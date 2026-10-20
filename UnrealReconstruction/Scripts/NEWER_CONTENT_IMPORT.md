# Versioned newer progression import

The retained `Analysis/ReferenceBuilds/newer-20261017` table evidence supplies all
70 challenge rows, 48 card rows, 20 unchanged level rows, 28 modifier rows and four
heat-category rows. All 14 decoded source tables and their 329 rows are retained
in the staged JSON definition. The importer verifies
the original byte-identical roundtrip flags, unique row names and identifiers,
card-to-challenge references, and every required native metric name. The generated
JSON definition retains source SHA-256 values and per-table payload provenance.

1. Run `python Scripts/newer_content_contract.py` and
   `python Scripts/test_newer_content_contract.py` from the project directory.
2. Convert the newer source **Paks directory**, including its global container,
   using `retoc to-legacy <Paks> Saved/NewerArtworkLegacy --filter
   CockHero/Content/ChallengeIcons --no-shaders --version UE5_3`. Repeat for
   `CockHero/Content/PlayerCards` and `CockHero/Content/UI/ModifierIcons`. A single game `.utoc` does not contain the
   required global ScriptObjects chunk.
3. After building the current editor module, run `export_newer_artwork.py` in
   Unreal's Python commandlet. This loads converted texture packages, exports
   their top mip, and records component and payload SHA-256 values. It never
   launches the source executable.
4. Run `python Scripts/decode_newer_artwork.py` outside Unreal. This uses the
   existing Pillow DDS decoder to retain decoded PNG source assets and hashes.
5. Run `import_newer_progression.py` in Unreal. All table fields are compared
   against re-exported editable tables before saving. All texture dimensions
   are checked. The runtime enum must expose every source requirement metric.
6. Convert `CockHero/Content/Audio/Voicelines/` to `Saved/NewerVoiceLegacy`
   with the same retoc version and source Paks directory. Run
   `python Scripts/prepare_newer_voices.py`; it retains seven source catalog
   rows and reconstructs all 28 exact referenced sample/selection Bink streams.
   Run `import_newer_voices.py` in Unreal to decode and import them, validating
   sample rate, channel count and frame count. The existing baseline catalog
   and sounds remain independent. `import_all_newer_content.py` combines both
   progression and voice imports into one commandlet session.
7. Run `CockHero.Recovery.NewerProgressionContent` in editor automation. This
   checks asset counts, retained baseline challenges, metric reflection, all
   unlock references, all 118 challenge/card textures, all 28 bound modifier
   textures, all seven voice catalogs and their 28 imported sample/selection
   sounds. It also checks baseline four-pack catalog compatibility.

The assets live below `/Game/Recovery/Newer20261017/`. Baseline progression and
artwork assets are preserved. Version selection belongs to the runtime loader;
it must select these tables only when the newer event producers are enabled and
the recovery profile has passed its existing verified backup gate. Layer
`Content/Recovery/Definitions/newer-20261017-resource-aliases.json` over baseline
resource aliases for that selected version. The unchanged level artwork keeps
using baseline aliases. Importing assets does not itself activate a profile or
mark the game's runtime reconstruction complete.
