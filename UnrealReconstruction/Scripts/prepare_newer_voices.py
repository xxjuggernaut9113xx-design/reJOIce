"""Retain all seven newer voice catalogs and rebuild their referenced Bink streams."""
import hashlib
import json
from pathlib import Path
from newer_content_contract import PROJECT, DEFINITION, require
from prepare_voice_pack_audio import reconstruct_bink_stream

contract = json.loads(DEFINITION.read_text(encoding="utf-8"))
rows = contract["supplemental_tables"]["VoicePackInfo_DataTable"]
require(len(rows) == 7, "Newer voice table must have seven packs")
source = PROJECT / "Saved/NewerVoiceLegacy/CockHero/Content"
files = {str(p.relative_to(source)).replace("\\", "/").lower(): p for p in source.rglob("*.uasset")}
output = PROJECT / "RecoveryEvidence/AudioEncoded/NewerVoice"
output.mkdir(parents=True, exist_ok=True)
packs, sounds, unavailable = [], [], []
for row in rows:
    pack = {"row_name": row["DisplayName"], "display_name": row["DisplayName"], "description": row["Description"],
            "tags": row["Tags"], "voice_pack_enum": row["SelectedVoicePack"]}
    for field, target in (("Sample1Wave", "sample_1_asset_path"), ("Sample2Wave", "sample_2_asset_path"),
                          ("Sample3Wave", "sample_3_asset_path"), ("SelectedVoiceLine", "selection_line_asset_path")):
        original = row[field]
        relative = original.split(".")[0].removeprefix("/Game/") + ".uasset"
        asset = files.get(relative.lower())
        if not asset:
            pack[target] = ""
            unavailable.append({"pack": row["DisplayName"], "field": field, "original": original})
            continue
        name = f"NewerVP_{row['SelectedVoicePack']}_{field}"
        package, bulk = asset.with_suffix(".uexp"), asset.with_suffix(".ubulk")
        require(package.is_file() and bulk.is_file(), f"Voice source components missing: {original}")
        encoded, header, chunks = reconstruct_bink_stream(package.read_bytes(), bulk.read_bytes(), name)
        encoded_path = output / (name + ".binka")
        encoded_path.write_bytes(encoded)
        path = f"/Game/Recovery/Newer20261017/Resources/VoicePreviews/{name}.{name}"
        pack[target] = path
        sounds.append({"asset_name": name, "asset_path": path, "original": original,
                       "encoded": str(encoded_path), "encoded_sha256": hashlib.sha256(encoded).hexdigest(),
                       "source_sha256": {str(p.relative_to(source)): hashlib.sha256(p.read_bytes()).hexdigest() for p in (asset, package, bulk)},
                       "sample_rate": header[4], "channels": header[2], "frames": header[5], "stream_chunks": chunks})
    packs.append(pack)
catalog = {"catalog_version": 2, "source_executed": False, "packs": packs, "unavailable_source_references": unavailable}
(PROJECT / "Content/Recovery/Definitions/newer-20261017-voice-pack-catalog.json").write_text(json.dumps(catalog, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
(PROJECT / "RecoveryEvidence/newer-20261017-voice-streams.json").write_text(json.dumps({"sounds": sounds, "unavailable_source_references": unavailable}, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"packs": len(packs), "streams": len(sounds), "unavailable": unavailable}))
