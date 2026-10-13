from __future__ import annotations

import hashlib
import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
RULES_PATH = EVIDENCE / "game-rules-draft.json"
REPORT_PATH = EVIDENCE / "level-icon-recovery.json"
ALIASES_PATH = EVIDENCE / "resource-aliases.json"
OUTPUT_PATH = EVIDENCE / "level-icon-contract-recovery.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    rules = json.loads(RULES_PATH.read_text(encoding="utf-8"))
    source_rows = rules["progression"]["DT_LevelData"]
    require(len(source_rows) == 20 and [int(row["Level"]) for row in source_rows] == list(range(1, 21)), "DT_LevelData source contract changed")
    expected = [str(row["LevelIcon"]) for row in source_rows]
    require(len(set(expected)) == 20, "DT_LevelData has duplicate level-icon paths")

    report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    rows = report.get("textures", [])
    require(report.get("expected_icons") == 20 and report.get("exported_icons") == 20 and report.get("decoded_icons") == 20 and report.get("imported_icons") == 20, "Level-icon recovery count is incomplete")
    require([row["original"] for row in rows] == expected, "Recovered level-icon order differs from source levels")
    aliases = json.loads(ALIASES_PATH.read_text(encoding="utf-8"))

    recovered_assets = []
    for row in rows:
        require(row.get("exported") and row.get("decoded") and row.get("imported"), f"Incomplete level icon: {row['original']}")
        source = row["source"]
        for key in ("uasset", "uexp", "ubulk"):
            path = Path(source[key])
            require(path.is_file() and sha256(path) == source[f"{key}_sha256"], f"Source {key} changed: {row['original']}")
        payload = Path(row["payload"])
        png = Path(row["png"])
        require(payload.is_file() and sha256(payload) == row["payload_sha256"], f"Recovered payload changed: {row['original']}")
        require(png.is_file() and sha256(png) == row["png_sha256"], f"Decoded PNG changed: {row['original']}")
        asset_path = str(row["recovered_asset"])
        require(aliases.get(row["original"]) == asset_path, f"Missing recovered level-icon alias: {row['original']}")
        package, _, name = asset_path.partition(".")
        disk_asset = PROJECT / "Content" / package.removeprefix("/Game/").replace("/", "\\")
        require(disk_asset.with_suffix(".uasset").is_file(), f"Missing imported level icon: {asset_path}")
        recovered_assets.append(asset_path)

    scripts = [
        PROJECT / "Scripts" / "export_level_icons.py",
        PROJECT / "Scripts" / "decode_level_icons.py",
        PROJECT / "Scripts" / "import_level_icons.py",
        PROJECT / "Scripts" / "recover_level_icon_contract.py",
    ]
    report_data = {
        "recovery": "post-game-level-icon-contract",
        "source_executed": False,
        "source_levels": [{"level": int(row["Level"]), "icon": row["LevelIcon"], "title": row["TitleUnlock"]} for row in source_rows],
        "verified": {
            "source_level_order_exact": True,
            "twenty_source_icons_exported": len(rows) == 20,
            "source_components_hash_verified": True,
            "twenty_icons_decoded": all(row.get("decoded") for row in rows),
            "twenty_icons_imported": all(row.get("imported") for row in rows),
            "aliases_complete": all(aliases.get(row["original"]) == row["recovered_asset"] for row in rows),
            "recovered_asset_files_complete": len(recovered_assets) == 20,
            "all_verified": True,
        },
        "recovered_assets": recovered_assets,
        "source_sha256": {str(path): sha256(path) for path in (RULES_PATH, REPORT_PATH, ALIASES_PATH)},
        "reconstruction_sha256": {str(path.relative_to(PROJECT)): sha256(path) for path in scripts},
    }
    OUTPUT_PATH.write_text(json.dumps(report_data, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"icons": len(rows), "report": str(OUTPUT_PATH), "verified": report_data["verified"]}, indent=2))


if __name__ == "__main__":
    main()
