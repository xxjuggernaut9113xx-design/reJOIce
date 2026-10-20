"""Fail-closed preflight for packaging the selected reconstructed runtime."""
import argparse
import hashlib
import json
from pathlib import Path
from newer_content_contract import PROJECT, COUNTS, DEFINITION, require, load_source


def read_json(path):
    raw = Path(path).read_bytes()
    return json.loads(raw.decode("utf-16" if raw.startswith((b"\xff\xfe", b"\xfe\xff")) else "utf-8-sig"))


def preflight(source_root):
    source_root = Path(source_root).resolve()
    require(source_root.is_dir(), f"Selected source Windows root is unavailable: {source_root}")
    extracted = source_root / "CockHero/Extracted"
    require((extracted / "Base_Game_CG/manifest.json").is_file(), "Selected newer root lacks its base manifest")
    manifests = sorted(extracted.rglob("manifest.json"))
    require(bool(manifests), "Selected newer root has no manifests")
    for manifest in manifests:
        require(isinstance(read_json(manifest), (dict, list)), f"Invalid manifest structure: {manifest}")
    require((source_root / "CockHero/Content/Movies").is_dir(), "Selected newer root lacks background movies")
    beatmaps = list((source_root / "CockHero/beatmaps").rglob("*.json"))
    require(bool(beatmaps), "Selected newer root lacks beatmap files")
    require(read_json(DEFINITION) == load_source(), "Versioned progression definition changed from retained source")
    report = read_json(PROJECT / "RecoveryEvidence/newer-20261017-progression-import.json")
    expected_tables = {**COUNTS, "DT_Modifiers": 28, "DT_HeatCategories": 4}
    for name, count in expected_tables.items():
        require(report["tables"][name]["rows"] == count and report["tables"][name]["all_fields_match"], f"Unverified imported table: {name}")
        require((PROJECT / f"Content/Recovery/Newer20261017/Progression/{name}.uasset").is_file(), f"Missing imported table asset: {name}")
    aliases = read_json(PROJECT / "Content/Recovery/Definitions/newer-20261017-resource-aliases.json")
    require(len(aliases) == 146, "Newer runtime artwork alias coverage is incomplete")
    for target in aliases.values():
        require(target.startswith("/Game/Recovery/Newer20261017/Resources/"), f"Artwork target escapes versioned content: {target}")
        require((PROJECT / "Content" / (target.split(".")[0].removeprefix("/Game/") + ".uasset")).is_file(), f"Missing runtime texture asset: {target}")
    require((PROJECT / "Content/Recovery/Definitions/newer-20261017-mode-data.json").is_file(), "Newer mode/item runtime data is absent")
    voices = read_json(PROJECT / "Content/Recovery/Definitions/newer-20261017-voice-pack-catalog.json")
    require(len(voices["packs"]) == 7 and not voices["unavailable_source_references"], "Newer voice catalog coverage is incomplete")
    voice_import = read_json(PROJECT / "RecoveryEvidence/newer-20261017-voice-import.json")
    require(len(voice_import["sounds"]) == 28 and all(row.get("imported") for row in voice_import["sounds"]), "Newer voice sample imports are incomplete")
    dialogue_path = PROJECT / "Content/Recovery/Definitions/newer-20261017-dialogue-catalog.json"
    dialogue = read_json(dialogue_path)
    dialogue_validation = read_json(PROJECT / "RecoveryEvidence/newer-20261017-dialogue-validation.json")
    require(dialogue_validation["all_staged_source_checksums_verified"] and
            dialogue_validation["catalog_sha256"] == hashlib.sha256(dialogue_path.read_bytes()).hexdigest(), "Dialogue source verification is stale")
    require(len(dialogue["packs"]) == 7 and len(dialogue["audio_streams"]) == 8350, "Full voice routing catalog is incomplete")
    require(all((PROJECT / "Content" / relative).is_file() for relative in dialogue["audio_streams"]), "A staged dialogue stream is missing")
    config = (PROJECT / "Config/DefaultGame.ini").read_text(encoding="utf-8")
    require('DirectoriesToAlwaysStageAsUFS=(Path="Recovery/Definitions")' in config, "Runtime JSON definitions are not staged")
    require('DirectoriesToAlwaysCook=(Path="/Game/Recovery/Newer20261017")' in config, "Versioned runtime assets are not included in cooking")
    require("UseNewerProgression=True" in config or "UseNewerProgression=true" in config, "Newer progression is not explicitly enabled")
    return {"packaging_preflight": "PASS", "source_root": str(source_root), "source_manifests": len(manifests),
            "source_beatmaps": len(beatmaps), "versioned_tables": expected_tables, "runtime_artwork": len(aliases),
            "voice_packs": 7, "voice_samples": 28,
            "source_dialogue_streams": len(dialogue["audio_streams"]), "source_dialogue_rows": sum(len(r) for r in dialogue["packs"].values()),
            "source_executed": False, "packaged_runtime_executed": False,
            "definition_sha256": hashlib.sha256(DEFINITION.read_bytes()).hexdigest()}


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--source-root", required=True)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    result = preflight(args.source_root)
    text = json.dumps(result, indent=2) + "\n"
    if args.report:
        args.report.parent.mkdir(parents=True, exist_ok=True)
        args.report.write_text(text, encoding="utf-8")
    print(text)
