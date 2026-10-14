"""Recover the complete Unlock Store pack catalog and byte-identical preview sources."""
from __future__ import annotations

import hashlib
import json
import shutil
import sys
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
EVIDENCE = PROJECT / "RecoveryEvidence"
SOURCE_ROOT = Path(r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\Extracted")
OUTPUT_DIRECTORY = EVIDENCE / "TextureSource" / "UnlockStorePackPreviews"
CATALOG_PATH = EVIDENCE / "pack-store-catalog.json"
COOKED_CATALOG_PATH = PROJECT / "Content" / "Recovery" / "Definitions" / "pack-store-catalog.json"
REPORT_PATH = EVIDENCE / "unlock-store-recovery.json"
WIDGET_EVIDENCE = EVIDENCE / "widget-functions"
ANIMATION_CATALOG = EVIDENCE / "animation-source-catalog.json"
PILLOW_TOOLS = Path(r"C:\Users\webma\analysis\cockhero-v004\tools\pillow")
if str(PILLOW_TOOLS) not in sys.path:
    sys.path.insert(0, str(PILLOW_TOOLS))
from PIL import Image


# Folder spelling is the shipping layout. Pack IDs are the lower-cased values
# exposed by the original CHPack Manager and challenge reward table.
PACKS = (
    ("Anal_Vol._1", "Anal_Vol._1", "anal_vol"),
    ("Base_Game_CG", "Base_Game_CG", "base_game_cg"),
    ("Cum_Covered_Succubi_Vol._1", "Cum_Covered_Succubi_Vol._1", "cum_covered_succubi_vol"),
    ("Elves_Vol._1", "Elves_Vol._1", "elves_vol"),
    ("Footjobs_Vol._1", "Footjobs_Vol._1", "footjobs_vol"),
    ("Leggings_Remake", "Leggings_Remake", "leggings_remake"),
    ("Remedy_Vol._1", "Remedy_Vol._1", "remedy_vol"),
    ("Shopkeeper_Vol._1", "Shopkeeper_Vol._1", "shopkeeper_vol"),
    ("Skunk_Vol._1", "Skunk_Vol._1", "skunk_vol"),
    ("Upskirts_Remake", "Upskirts_Remake", "upskirts_remake"),
    ("Vaelith_Vol._1", "Vaelith_Vol._1", "vaelith_vol"),
    ("Vera_Vol._1", "Vera_Vol._1", "vera_vol_1"),
    ("Vera_Vol._2", "Vera_Vol._2", "vera_vol"),
    ("Winter_Wonderland_Vol._1", "Winter_Wonderland_Vol._1", "winter_wonderland_vol"),
)

SOCIAL_LINK_FIELDS = (
    "onlyfans",
    "fansly",
    "twitter",
    "linktree",
    "manyvids",
    "redgifs",
    "discord",
    "patreon",
    "subscribestar",
    "kofi",
)

SOCIAL_ICON_ORDER = (
    ("fansly", 1),
    ("twitter", 2),
    ("linktree", 3),
    ("manyvids", 4),
    ("redgifs", 5),
    ("discord", 6),
    ("patreon", 7),
    ("subscribestar", 8),
    ("kofi", 9),
    ("onlyfans", 0),
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


def recovered_challenge_names() -> dict[str, str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    names: dict[str, str] = {}
    for row in rules["progression"]["DT_Challenges"]:
        for reward in row.get("Rewards", []):
            if reward.get("RewardType") == "ECHRewardType::UnlockPack":
                names[reward["ItemIdentifier"]] = row["DisplayName"]
    return names


def entrypoint(asset: str, function: str) -> int:
    payload = json.loads((WIDGET_EVIDENCE / asset / f"{function}.json").read_text(encoding="utf-8"))
    statements = payload.get("statements", [])
    entrypoints = []
    for statement in statements:
        if statement.get("op") != "EX_LocalFinalFunction":
            continue
        if statement.get("StackNode") != f"ExecuteUbergraph_{asset}":
            continue
        parameters = statement.get("Parameters", [])
        if parameters and isinstance(parameters[0].get("Value"), int):
            entrypoints.append(parameters[0]["Value"])
    require(len(entrypoints) == 1, f"Invalid source entrypoint: {asset}/{function}")
    return entrypoints[0]


def widget_component_count(asset: str) -> int:
    layout = json.loads((EVIDENCE / "ui-layout-values.json").read_text(encoding="utf-8"))
    return sum(1 for record in layout["widgets"] if record["asset"] == asset)


def main() -> None:
    require(SOURCE_ROOT.is_dir(), f"Original extracted pack root is unavailable: {SOURCE_ROOT}")
    expected_folders = {folder for _, folder, _ in PACKS}
    actual_folders = {folder.name for folder in SOURCE_ROOT.iterdir() if folder.is_dir() and (folder / "manifest.json").is_file()}
    require(actual_folders == expected_folders, "Shipping pack directory set differs from the recovered store catalog")
    challenge_names = recovered_challenge_names()
    challenge_pack_ids = set(challenge_names)
    configured_ids = {pack_id.lower() for pack_id, _, _ in PACKS}
    require(challenge_pack_ids <= configured_ids, "Challenge rewards reference a pack outside the shipping catalog")
    require(len(PACKS) == 14, "Recovered store catalog count changed")
    OUTPUT_DIRECTORY.mkdir(parents=True, exist_ok=True)

    packs = []
    preview_report = []
    for pack_id, folder_name, asset_name in PACKS:
        folder = SOURCE_ROOT / folder_name
        manifest_path = folder / "manifest.json"
        require(manifest_path.is_file(), f"Source pack manifest is unavailable: {manifest_path}")
        manifest = parse_manifest(manifest_path)
        preview_name = manifest.get("preview")
        require(isinstance(preview_name, str) and preview_name, f"Source preview name is invalid: {manifest_path}")
        source_preview = folder / preview_name
        require(source_preview.is_file(), f"Source preview is unavailable: {source_preview}")
        with Image.open(source_preview) as image:
            width, height = image.size
            image_format = image.format
        require(image_format == "PNG", f"Source preview format changed: {source_preview}")
        destination = OUTPUT_DIRECTORY / f"{asset_name}.png"
        shutil.copy2(source_preview, destination)
        require(sha256(destination) == sha256(source_preview), f"Preview copy differs from source: {pack_id}")
        media = manifest.get("media", [])
        require(isinstance(media, list), f"Source media list is invalid: {manifest_path}")
        source_links = manifest.get("social_links")
        require(isinstance(source_links, dict), f"Source social links are invalid: {manifest_path}")
        social_links = {}
        for field in SOCIAL_LINK_FIELDS:
            value = source_links.get(field)
            require(isinstance(value, str), f"Source social link is invalid: {manifest_path}/{field}")
            social_links[field] = value
        images = sum(1 for item in media if isinstance(item, dict) and item.get("type") == "image")
        videos = sum(1 for item in media if isinstance(item, dict) and item.get("type") == "video")
        packs.append(
            {
                "pack_id": pack_id,
                "source_folder": folder_name,
                "asset_name": asset_name,
                "asset_path": f"/Game/Recovery/Resources/Packs/{asset_name}.{asset_name}",
                "name": manifest["name"],
                "author": manifest["author"],
                "description": manifest["description"],
                "unlock_cost": int(manifest["unlock_cost"]),
                "patreon_exclusive": bool(manifest["patreon_exclusive"]),
                "required_challenge": str(manifest.get("required_challenge", "")),
                "challenge_name": challenge_names.get(pack_id.lower(), ""),
                "social_links": social_links,
                "total_media_count": len(media),
                "image_count": images,
                "video_count": videos,
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
            }
        )
        preview_report.append({key: packs[-1][key] for key in (
            "pack_id", "source_folder", "asset_name", "asset_path", "source_manifest", "source_manifest_sha256",
            "source_preview", "source_preview_sha256", "source_preview_bytes", "preview_filename",
            "recovered_source", "recovered_source_sha256", "width", "height", "format",
        )})

    require(len(packs) == 14, "Recovered store catalog is incomplete")
    require(sum(pack["pack_id"] == "Base_Game_CG" for pack in packs) == 1, "Base game catalog record is missing")
    require(sum(bool(pack["challenge_name"]) for pack in packs) == len(challenge_pack_ids), "Challenge name mapping is incomplete")
    catalog_payload = {
        "catalog_version": 1,
        "source_root": str(SOURCE_ROOT),
        "pack_count": len(packs),
        "source_order": [pack["pack_id"] for pack in packs],
        "packs": packs,
    }
    catalog_text = json.dumps(catalog_payload, ensure_ascii=False, indent=2) + "\n"
    CATALOG_PATH.write_text(catalog_text, encoding="utf-8")
    COOKED_CATALOG_PATH.parent.mkdir(parents=True, exist_ok=True)
    COOKED_CATALOG_PATH.write_text(catalog_text, encoding="utf-8")
    animations = json.loads(ANIMATION_CATALOG.read_text(encoding="utf-8"))
    source_entrypoints = {
        "Construct": entrypoint("UnlockStoreWidget", "Construct"),
        "BackButtonClicked": entrypoint("UnlockStoreWidget", "BndEvt__UnlockStoreWidget_BackButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature"),
        "OnEntryClicked": entrypoint("UnlockStoreWidget", "OnEntryClicked"),
        "OnEntryHovered": entrypoint("UnlockStoreWidget", "OnEntryHovered"),
        "OnEntryUnhovered": entrypoint("UnlockStoreWidget", "OnEntryUnhovered"),
        "InteractionButtonClicked": entrypoint("UnlockStoreWidget", "BndEvt__UnlockStoreWidget_InteractionButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature"),
        "EnableDisableButtonA": entrypoint("UnlockStoreWidget", "BndEvt__UnlockStoreWidget_DisablePacksButton_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature"),
        "EnableDisableButtonB": entrypoint("UnlockStoreWidget", "BndEvt__UnlockStoreWidget_DisablePacksButton_1_K2Node_ComponentBoundEvent_7_OnButtonClickedEvent__DelegateSignature"),
        "ClearRefreshPacks": entrypoint("UnlockStoreWidget", "Clear_RefreshPacks"),
        "CreatePackBatch": entrypoint("UnlockStoreWidget", "CreatePackBatch"),
    }
    REPORT_PATH.write_text(json.dumps({
        "recovery": "unlock-store",
        "source_executed": False,
        "source_kind": "shipping extracted pack manifests and PNG preview payloads",
        "source_root": str(SOURCE_ROOT),
        "catalog": str(CATALOG_PATH),
        "cooked_catalog": str(COOKED_CATALOG_PATH),
        "pack_count": len(packs),
        "source_entrypoints": source_entrypoints,
        "source_widget_components": {
            "UnlockStoreWidget": widget_component_count("UnlockStoreWidget"),
            "CHPackEntryWidget": widget_component_count("CHPackEntryWidget"),
            "UnlockStoreSocialIconBaseButton": widget_component_count("UnlockStoreSocialIconBaseButton"),
        },
        "source_animation_contract": {
            "UnlockStoreWidget": animations["UnlockStoreWidget"]["animations"],
            "CHPackEntryWidget": animations["CHPackEntryWidget"]["animations"],
            "UnlockStoreSocialIconBaseButton": animations["UnlockStoreSocialIconBaseButton"]["animations"],
        },
        "social_icon_contract": {
            "widget": "UnlockStoreSocialIconBaseButton",
            "source_entrypoints": {
                "Construct": entrypoint("UnlockStoreSocialIconBaseButton", "Construct"),
                "Hover": entrypoint("UnlockStoreSocialIconBaseButton", "BndEvt__UnlockStoreSocialIconBaseButton_SocialButton_K2Node_ComponentBoundEvent_0_OnButtonHoverEvent__DelegateSignature"),
                "Unhover": entrypoint("UnlockStoreSocialIconBaseButton", "BndEvt__UnlockStoreSocialIconBaseButton_SocialButton_K2Node_ComponentBoundEvent_1_OnButtonHoverEvent__DelegateSignature"),
                "Click": entrypoint("UnlockStoreSocialIconBaseButton", "BndEvt__UnlockStoreSocialIconBaseButton_SocialButton_K2Node_ComponentBoundEvent_2_OnButtonClickedEvent__DelegateSignature"),
            },
            "max_buttons": 4,
            "button_size": [56, 56],
            "icon_size": [32, 32],
            "padding": [16, 0, 16, 0],
            "platform_order": [{"name": name, "value": value} for name, value in SOCIAL_ICON_ORDER],
        },
        "grid_columns": 4,
        "packs_per_frame": 2,
        "challenge_reward_pack_count": len(challenge_pack_ids),
        "patreon_exclusive_pack_count": sum(pack["patreon_exclusive"] for pack in packs),
        "copied_previews": len(preview_report),
        "output_directory": str(OUTPUT_DIRECTORY),
        "previews": preview_report,
    }, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"recovered": len(packs), "catalog": str(CATALOG_PATH), "report": str(REPORT_PATH)}, indent=2))


if __name__ == "__main__":
    main()
