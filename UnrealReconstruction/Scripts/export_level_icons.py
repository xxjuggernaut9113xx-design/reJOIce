from __future__ import annotations

import hashlib
import json
import shutil
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
EVIDENCE = PROJECT / "RecoveryEvidence"
SOURCE_CONTENT = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-ui\CockHero\Content")
SOURCE_DIRECTORY = SOURCE_CONTENT / "UI" / "PostGameFlow" / "LevelIcons"
PAYLOAD_DIRECTORY = PROJECT / "Saved" / "TextureRecovery" / "LevelIcons"
REPORT_PATH = EVIDENCE / "level-icon-recovery.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def source_icons() -> list[str]:
    rules = json.loads((EVIDENCE / "game-rules-draft.json").read_text(encoding="utf-8"))
    rows = rules["progression"]["DT_LevelData"]
    require(len(rows) == 20, "DT_LevelData no longer contains twenty levels")
    require([int(row["Level"]) for row in rows] == list(range(1, 21)), "DT_LevelData order is no longer source order")
    paths = [str(row["LevelIcon"]) for row in rows]
    require(len(set(paths)) == 20, "DT_LevelData level icons are not unique")
    for path in paths:
        package, separator, object_name = path.partition(".")
        relative = package.removeprefix("/Game/")
        require(separator == "." and package.startswith("/Game/UI/PostGameFlow/LevelIcons/"), f"Invalid level-icon path: {path}")
        require(Path(relative).name == object_name, f"Level-icon object/package mismatch: {path}")
    return paths


def exported_payload(result: dict, name: str) -> Path:
    candidates = [
        Path(str(result.get("file", ""))),
        PROJECT / str(result.get("file", "")),
        PROJECT / "Saved" / "TextureRecovery" / f"{name}.bin",
    ]
    for candidate in candidates:
        if candidate.is_file():
            return candidate.resolve()
    raise RuntimeError(f"Texture recovery did not create a payload for {name}: {result}")


def main() -> None:
    require(SOURCE_DIRECTORY.is_dir(), f"Missing cooked level-icon directory: {SOURCE_DIRECTORY}")
    PAYLOAD_DIRECTORY.mkdir(parents=True, exist_ok=True)

    rows = []
    for original in source_icons():
        package = original.split(".", 1)[0]
        relative = package.removeprefix("/Game/")
        name = Path(relative).name
        uasset = SOURCE_CONTENT / f"{relative}.uasset"
        uexp = SOURCE_CONTENT / f"{relative}.uexp"
        ubulk = SOURCE_CONTENT / f"{relative}.ubulk"
        for component in (uasset, uexp, ubulk):
            require(component.is_file(), f"Missing cooked level-icon component: {component}")

        result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(SOURCE_CONTENT), relative))
        require(result.get("success", False), f"Could not export {original}: {result.get('error', result)}")
        exported = exported_payload(result, name)
        payload = PAYLOAD_DIRECTORY / f"{name}.bin"
        shutil.copy2(exported, payload)
        require(payload.is_file() and payload.stat().st_size == int(result["bytes"]), f"Payload copy failed for {original}")

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

    require(len(rows) == 20 and len({row["original"] for row in rows}) == 20, "Level-icon export is incomplete")
    REPORT_PATH.write_text(
        json.dumps(
            {
                "recovery": "post-game-level-icons",
                "source_executed": False,
                "source_content": str(SOURCE_CONTENT),
                "expected_icons": 20,
                "exported_icons": len(rows),
                "textures": rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    unreal.log("POST_GAME_LEVEL_ICONS_EXPORTED " + json.dumps({"count": len(rows), "report": str(REPORT_PATH)}))


if __name__ == "__main__":
    main()
