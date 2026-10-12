from __future__ import annotations

import hashlib
import json
import shutil
import sys
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
SOURCE_ROOT = Path(r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\Extracted")
OUTPUT_DIRECTORY = EVIDENCE / "TextureSource" / "ChallengePackPreviews"
REPORT_PATH = EVIDENCE / "challenge-pack-preview-recovery.json"
PILLOW_TOOLS = Path(r"C:\Users\webma\analysis\cockhero-v004\tools\pillow")
if str(PILLOW_TOOLS) not in sys.path:
    sys.path.insert(0, str(PILLOW_TOOLS))
from PIL import Image


PACKS = (
    ("anal_vol._1", "Anal_Vol._1", "anal_vol"),
    ("cum_covered_succubi_vol._1", "Cum_Covered_Succubi_Vol._1", "cum_covered_succubi_vol"),
    ("elves_vol._1", "Elves_Vol._1", "elves_vol"),
    ("footjobs_vol._1", "Footjobs_Vol._1", "footjobs_vol"),
    ("leggings_remake", "Leggings_Remake", "leggings_remake"),
    ("shopkeeper_vol._1", "Shopkeeper_Vol._1", "shopkeeper_vol"),
    ("upskirts_remake", "Upskirts_Remake", "upskirts_remake"),
    ("vera_vol._2", "Vera_Vol._2", "vera_vol"),
    ("winter_wonderland_vol._1", "Winter_Wonderland_Vol._1", "winter_wonderland_vol"),
)


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def parse_manifest(path: Path) -> dict:
    payload = path.read_bytes()
    for encoding in ("utf-8-sig", "utf-16", "utf-16-le", "utf-16-be"):
        try:
            decoded = json.loads(payload.decode(encoding))
        except (UnicodeDecodeError, json.JSONDecodeError):
            continue
        if isinstance(decoded, dict):
            return decoded
    raise RuntimeError(f"Could not decode source pack manifest: {path}")


def expected_reward_ids() -> set[str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    rows = rules["progression"]["DT_Challenges"]
    rewards = {
        reward["ItemIdentifier"]
        for row in rows
        for reward in row.get("Rewards", [])
        if reward.get("RewardType") == "ECHRewardType::UnlockPack"
    }
    require(len(rewards) == len(PACKS), "Recovered challenge reward pack count changed")
    return rewards


def main() -> None:
    require(SOURCE_ROOT.is_dir(), f"Original extracted pack root is unavailable: {SOURCE_ROOT}")
    expected = expected_reward_ids()
    configured = {pack_id for pack_id, _, _ in PACKS}
    require(expected == configured, "Recovered challenge pack mapping differs from DT_Challenges")
    OUTPUT_DIRECTORY.mkdir(parents=True, exist_ok=True)

    rows = []
    for pack_id, folder_name, asset_name in PACKS:
        folder = SOURCE_ROOT / folder_name
        manifest_path = folder / "manifest.json"
        require(manifest_path.is_file(), f"Source pack manifest is unavailable: {manifest_path}")
        manifest = parse_manifest(manifest_path)
        preview_name = manifest.get("preview")
        display_name = manifest.get("name")
        require(isinstance(preview_name, str) and preview_name, f"Source preview name is invalid: {manifest_path}")
        require(isinstance(display_name, str) and display_name, f"Source pack name is invalid: {manifest_path}")
        source_preview = folder / preview_name
        require(source_preview.is_file(), f"Source preview is unavailable: {source_preview}")
        with Image.open(source_preview) as image:
            width, height = image.size
            image_format = image.format
        require(image_format == "PNG", f"Source preview format changed: {source_preview}")
        destination = OUTPUT_DIRECTORY / f"{asset_name}.png"
        shutil.copy2(source_preview, destination)
        require(destination.is_file(), f"Preview copy failed: {destination}")
        require(sha256(destination) == sha256(source_preview), f"Preview copy differs from source: {pack_id}")
        rows.append(
            {
                "pack_id": pack_id,
                "pack_name": display_name,
                "source_folder": folder_name,
                "asset_name": asset_name,
                "source_manifest": str(manifest_path),
                "source_manifest_sha256": sha256(manifest_path),
                "source_preview": str(source_preview),
                "source_preview_sha256": sha256(source_preview),
                "source_preview_bytes": source_preview.stat().st_size,
                "preview_filename": preview_name,
                "recovered_source": str(destination),
                "recovered_source_sha256": sha256(destination),
                "width": width,
                "height": height,
                "format": image_format,
                "copied": True,
            }
        )

    require(len(rows) == len(PACKS), "Challenge pack preview recovery is incomplete")
    REPORT_PATH.write_text(
        json.dumps(
            {
                "recovery": "challenge-pack-previews",
                "source_executed": False,
                "source_kind": "shipping extracted pack preview JPEGs",
                "source_root": str(SOURCE_ROOT),
                "expected_pack_rewards": len(PACKS),
                "copied_previews": len(rows),
                "output_directory": str(OUTPUT_DIRECTORY),
                "previews": rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(json.dumps({"recovered": len(rows), "report": str(REPORT_PATH)}, indent=2))


if __name__ == "__main__":
    main()