"""Import and validate all preview textures used by UnlockStoreWidget."""
from __future__ import annotations

import json
import os
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
EVIDENCE = PROJECT / "RecoveryEvidence"
CATALOG_PATH = EVIDENCE / "pack-store-catalog.json"
REPORT_PATH = EVIDENCE / "unlock-store-recovery.json"
DESTINATION = "/Game/Recovery/Resources/Packs"
VALIDATE_ONLY = os.environ.get("RECOVERY_VALIDATE_ONLY") == "1"


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    catalog = json.loads(CATALOG_PATH.read_text(encoding="utf-8"))
    packs = catalog.get("packs", [])
    require(catalog.get("pack_count") == 14 and len(packs) == 14, "Unlock Store catalog is incomplete")
    require(len({pack["pack_id"] for pack in packs}) == 14, "Unlock Store catalog pack IDs are not unique")
    require(sum(pack["pack_id"] == "Base_Game_CG" for pack in packs) == 1, "Base game store pack is missing")

    imported = []
    for pack in packs:
        source = Path(pack["recovered_source"])
        require(source.is_file(), f"Recovered pack preview source is unavailable: {source}")
        if not VALIDATE_ONLY:
            task = unreal.AssetImportTask()
            task.filename = str(source)
            task.destination_path = DESTINATION
            task.automated = True
            task.replace_existing = True
            task.save = False
            unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
        asset_path = pack["asset_path"]
        texture = unreal.load_asset(asset_path)
        require(isinstance(texture, unreal.Texture2D), f"Unlock Store preview import failed: {pack['pack_id']}")
        require(texture.blueprint_get_size_x() == int(pack["width"]), f"Unlock Store preview width changed: {pack['pack_id']}")
        require(texture.blueprint_get_size_y() == int(pack["height"]), f"Unlock Store preview height changed: {pack['pack_id']}")
        if not VALIDATE_ONLY:
            texture.set_editor_property("compression_settings", unreal.TextureCompressionSettings.TC_EDITOR_ICON)
            texture.set_editor_property("mip_gen_settings", unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
            texture.set_editor_property("srgb", True)
            require(unreal.EditorAssetLibrary.save_loaded_asset(texture, only_if_is_dirty=False), f"Could not save Unlock Store preview: {pack['pack_id']}")
        require(bool(texture.get_editor_property("srgb")), f"Unlock Store preview color space changed: {pack['pack_id']}")
        require(texture.get_editor_property("compression_settings") == unreal.TextureCompressionSettings.TC_EDITOR_ICON, f"Unlock Store preview compression changed: {pack['pack_id']}")
        require(texture.get_editor_property("mip_gen_settings") == unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS, f"Unlock Store preview mip configuration changed: {pack['pack_id']}")
        imported.append(asset_path)

    report = json.loads(REPORT_PATH.read_text(encoding="utf-8"))
    report.update({
        "destination": DESTINATION,
        "imported_previews": len(imported),
        "asset_properties_verified": True,
        "asset_validation_mode": "validation-only" if VALIDATE_ONLY else "import-and-validate",
        "imported_assets": imported,
    })
    REPORT_PATH.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    (PROJECT / "Saved" / "unlock-store-preview-import-report.json").write_text(
        json.dumps({"imported": len(imported), "destination": DESTINATION, "assets": imported}, indent=2) + "\n",
        encoding="utf-8",
    )
    unreal.log("UNLOCK_STORE_PACK_PREVIEWS_IMPORTED " + json.dumps({"count": len(imported), "destination": DESTINATION}))


if __name__ == "__main__":
    main()
