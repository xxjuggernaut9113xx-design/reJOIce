from __future__ import annotations

import hashlib
import json
import shutil
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
EVIDENCE = PROJECT / "RecoveryEvidence"
SOURCE_CONTENT = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-ui\CockHero\Content")
SOURCE_DIRECTORY = SOURCE_CONTENT / "ChallengeIcons"
PAYLOAD_DIRECTORY = PROJECT / "Saved" / "TextureRecovery" / "ChallengeIcons"
REPORT_PATH = EVIDENCE / "challenge-icon-recovery.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def required_assets() -> list[str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    rows = rules["progression"]["DT_Challenges"]
    assets = [row["Icon"] for row in rows]
    require(len(rows) == 55, "DT_Challenges no longer contains 55 rows")
    require(len(assets) == 55 and len(set(assets)) == 55, "DT_Challenges no longer has 55 unique icon references")
    for asset in assets:
        package, separator, object_name = asset.partition(".")
        relative = package.removeprefix("/Game/")
        require(separator == "." and package.startswith("/Game/ChallengeIcons/"), f"Invalid challenge icon reference: {asset}")
        require(Path(relative).name == object_name, f"Challenge icon object/package mismatch: {asset}")
    return assets


def source_payload_path(result: dict, name: str) -> Path:
    reported = Path(str(result.get("file", "")))
    candidates = [
        reported,
        PROJECT / reported,
        PROJECT / "Saved" / "TextureRecovery" / f"{name}.bin",
    ]
    for candidate in candidates:
        if candidate.is_file():
            return candidate.resolve()
    raise RuntimeError(f"Texture recovery did not create payload for {name}: {result.get('file', '<missing>')}")


def main() -> None:
    require(SOURCE_CONTENT.is_dir(), f"Cooked source content directory is unavailable: {SOURCE_CONTENT}")
    require(SOURCE_DIRECTORY.is_dir(), f"Cooked challenge icon directory is unavailable: {SOURCE_DIRECTORY}")
    PAYLOAD_DIRECTORY.mkdir(parents=True, exist_ok=True)

    rows = []
    source_assets = required_assets()
    for original in source_assets:
        package = original.split(".", 1)[0]
        relative = package.removeprefix("/Game/")
        name = Path(relative).name
        uasset = SOURCE_CONTENT / f"{relative}.uasset"
        uexp = SOURCE_CONTENT / f"{relative}.uexp"
        ubulk = SOURCE_CONTENT / f"{relative}.ubulk"
        for component in (uasset, uexp, ubulk):
            require(component.is_file(), f"Missing cooked challenge icon component: {component}")

        result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(SOURCE_CONTENT), relative))
        require(result.get("success", False), f"Could not export {original}: {result.get('error', result)}")
        exported = source_payload_path(result, name)
        payload = PAYLOAD_DIRECTORY / f"{name}.bin"
        shutil.copy2(exported, payload)
        require(payload.is_file(), f"Payload copy failed for {original}")
        require(payload.stat().st_size == int(result["bytes"]), f"Payload byte count changed for {original}")

        rows.append(
            {
                "original": original,
                "relative_package": relative,
                "source": {
                    "uasset": str(uasset),
                    "uexp": str(uexp),
                    "ubulk": str(ubulk),
                    "uasset_sha256": sha256(uasset),
                    "uexp_sha256": sha256(uexp),
                    "ubulk_sha256": sha256(ubulk),
                    "uasset_bytes": uasset.stat().st_size,
                    "uexp_bytes": uexp.stat().st_size,
                    "ubulk_bytes": ubulk.stat().st_size,
                },
                "payload": str(payload),
                "payload_sha256": sha256(payload),
                "format": str(result["format"]),
                "width": int(result["width"]),
                "height": int(result["height"]),
                "srgb": bool(result["srgb"]),
                "bytes": int(result["bytes"]),
                "exported": True,
            }
        )

    require(len(rows) == 55, "Challenge icon export is incomplete")
    require(len({row["original"] for row in rows}) == 55, "Challenge icon export has duplicate source paths")
    REPORT_PATH.write_text(
        json.dumps(
            {
                "recovery": "challenge-icons",
                "source_executed": False,
                "source_kind": "cooked UE5.3 texture packages",
                "source_content": str(SOURCE_CONTENT),
                "source_package_directory": str(SOURCE_DIRECTORY),
                "expected_icons": 55,
                "exported_icons": len(rows),
                "payload_directory": str(PAYLOAD_DIRECTORY),
                "textures": rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("CHALLENGE_ICON_TEXTURES_EXPORTED " + json.dumps({"count": len(rows), "report": str(REPORT_PATH)}))


if __name__ == "__main__":
    main()
