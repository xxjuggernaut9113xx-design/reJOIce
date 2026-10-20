"""Retain deduplicated source dialogue streams for bounded runtime decoding."""
import hashlib
import json
from pathlib import Path
from newer_content_contract import PROJECT, require
from prepare_voice_pack_audio import reconstruct_bink_stream

catalog_path = PROJECT / "Content/Recovery/Definitions/newer-20261017-dialogue-catalog.json"
catalog = json.loads(catalog_path.read_text(encoding="utf-8"))
source = Path("E:/reJOIceRecoveryCache/NewerVoiceLegacy/CockHero/Content/Audio/Voicelines")
require(source.is_dir(), "Retained converted voice source is unavailable")
files = {str(p.relative_to(source)).replace("\\", "/").lower(): p for p in source.rglob("*.uasset")}
output = PROJECT / "Content/Recovery/Definitions/NewerDialogueAudio"
output.mkdir(parents=True, exist_ok=True)
streams, missing = {}, []
for pack, rows in catalog["packs"].items():
    for row in rows:
        filename = row["VoiceFile"].replace(".wav", "")
        relative = f"{pack}/{row['Category']}/{filename}.uasset"
        require(".." not in relative and ":" not in relative, f"Invalid source dialogue path: {relative}")
        asset = files.get(relative.lower())
        if not asset:
            missing.append({"pack": pack, "row": row["row"], "source": relative})
            row["AudioStream"] = ""
            continue
        key = str(asset.relative_to(source)).replace("\\", "/")
        if key not in streams:
            package, bulk = asset.with_suffix(".uexp"), asset.with_suffix(".ubulk")
            require(package.is_file() and bulk.is_file(), f"Missing dialogue source components: {relative}")
            encoded, header, chunks = reconstruct_bink_stream(package.read_bytes(), bulk.read_bytes(), relative)
            sha256 = hashlib.sha256(encoded).hexdigest()
            path = output / (sha256 + ".binka")
            if not path.is_file():
                path.write_bytes(encoded)
            streams[key] = {"path": str(path.relative_to(PROJECT / "Content")).replace("\\", "/"),
                            "sha256": sha256, "sha1": hashlib.sha1(encoded).hexdigest(), "bytes": len(encoded),
                            "sample_rate": header[4], "channels": header[2], "frames": header[5],
                            "source_sha256": {p.suffix: hashlib.sha256(p.read_bytes()).hexdigest() for p in (asset, package, bulk)}}
        row["AudioStream"] = streams[key]["path"]
catalog["audio_streams"] = {row["path"]: row for row in streams.values()}
catalog["missing_source_audio"] = missing
catalog_path.write_text(json.dumps(catalog, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
(PROJECT / "RecoveryEvidence/newer-20261017-dialogue-audio.json").write_text(json.dumps({"source_executed": False,
    "source_root": str(source), "source_streams": streams, "missing_source_audio": missing}, indent=2) + "\n", encoding="utf-8")
print(json.dumps({"unique_source_streams": len(streams), "retained_bytes": sum(r["bytes"] for r in catalog["audio_streams"].values()), "missing_source_audio": len(missing)}))
