from __future__ import annotations

import hashlib
import json
import shutil
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir())
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
SOURCE_UTOC = Path(r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero\Content\Paks\CockHero-Windows.utoc")
LEGACY_CONTENT = ANALYSIS / "player-cards-legacy-v2" / "CockHero" / "Content"
RAW_CONTENT = ANALYSIS / "player-cards-extract" / "CockHero" / "Content"
EVIDENCE = PROJECT / "RecoveryEvidence"
PAYLOAD_DIRECTORY = PROJECT / "Saved" / "TextureRecovery" / "PlayerCards"
REPORT_PATH = EVIDENCE / "player-card-texture-recovery.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def required_assets() -> list[str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    assets = [row["CardImage"] for row in rules["progression"]["DT_PlayerCards"]]
    if len(assets) != 36 or len(set(assets)) != 36:
        raise RuntimeError("DT_PlayerCards no longer has 36 unique source image references")
    return [*assets, "/Game/PlayerCards/LockedPlayerCard.LockedPlayerCard"]


if not SOURCE_UTOC.is_file() or not LEGACY_CONTENT.is_dir() or not RAW_CONTENT.is_dir():
    raise RuntimeError("Recovered PlayerCards package directories are unavailable")

PAYLOAD_DIRECTORY.mkdir(parents=True, exist_ok=True)
rows = []
for original in required_assets():
    relative = original.split(".", 1)[0][len("/Game/"):]
    name = Path(relative).name
    legacy_package = LEGACY_CONTENT / f"{relative}.uasset"
    legacy_exports = LEGACY_CONTENT / f"{relative}.uexp"
    raw_header = RAW_CONTENT / f"{relative}.uheader"
    raw_exports = RAW_CONTENT / f"{relative}.uexp"
    for path in (legacy_package, legacy_exports, raw_header, raw_exports):
        if not path.is_file():
            raise RuntimeError(f"Missing recovered PlayerCards package component: {path}")

    result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(LEGACY_CONTENT), relative))
    if not result.get("success"):
        raise RuntimeError(f"Could not export {original}: {result.get('error', result)}")
    exported = Path(result["file"])
    if not exported.is_file():
        raise RuntimeError(f"Texture recovery did not create payload for {original}")
    payload = PAYLOAD_DIRECTORY / f"{name}.bin"
    shutil.copy2(exported, payload)
    if not payload.is_file() or payload.stat().st_size != int(result["bytes"]):
        raise RuntimeError(f"Payload copy verification failed for {original}")

    rows.append(
        {
            "original": original,
            "relative_package": relative,
            "source": {
                "raw_uheader_sha256": sha256(raw_header),
                "raw_uexp_sha256": sha256(raw_exports),
                "legacy_uasset_sha256": sha256(legacy_package),
                "legacy_uexp_sha256": sha256(legacy_exports),
            },
            "payload": str(payload),
            "payload_sha256": sha256(payload),
            "format": result["format"],
            "width": int(result["width"]),
            "height": int(result["height"]),
            "srgb": bool(result["srgb"]),
            "bytes": int(result["bytes"]),
        }
    )

report = {
    "recovery": "player-card-textures",
    "source_executed": False,
    "source_container": {
        "utoc": str(SOURCE_UTOC),
        "utoc_sha256": sha256(SOURCE_UTOC),
        "conversion": "retoc to-legacy --filter CockHero/Content/PlayerCards --no-shaders --version UE5_3",
    },
    "expected_card_images": 36,
    "exported_images": len(rows),
    "textures": rows,
}
REPORT_PATH.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
unreal.log("PLAYER_CARD_TEXTURES_EXPORTED " + json.dumps({"count": len(rows), "report": str(REPORT_PATH)}))
