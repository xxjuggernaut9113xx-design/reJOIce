from __future__ import annotations

import hashlib
import json
import shutil
from pathlib import Path

import unreal


PROJECT = Path(unreal.Paths.project_dir()).resolve()
SOURCE_CONTENT = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-ui\CockHero\Content")
RELATIVE_PACKAGE = "Widgets/NotificationBoxIcons/CoinRewardIcon"
ORIGINAL_OBJECT = "/Game/Widgets/NotificationBoxIcons/CoinRewardIcon.CoinRewardIcon"
PAYLOAD = PROJECT / "RecoveryEvidence" / "TextureSource" / "Widgets" / "NotificationBoxIcons" / "CoinRewardIcon.bin"
REPORT = PROJECT / "RecoveryEvidence" / "loot-notification-icon-recovery-report.json"


def sha256(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def require(condition: bool, message: str) -> None:
    if not condition:
        raise RuntimeError(message)


def main() -> None:
    package_base = SOURCE_CONTENT / RELATIVE_PACKAGE
    components = {suffix: package_base.with_suffix(suffix) for suffix in (".uasset", ".uexp", ".ubulk")}
    for component in components.values():
        require(component.is_file(), f"Missing cooked CoinRewardIcon component: {component}")

    result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(SOURCE_CONTENT), RELATIVE_PACKAGE))
    require(result.get("success", False), f"Could not export {ORIGINAL_OBJECT}: {result.get('error', result)}")
    exported = Path(str(result["file"]))
    require(exported.is_file(), f"Cooked mip export is missing: {exported}")

    PAYLOAD.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(exported, PAYLOAD)
    require(PAYLOAD.is_file(), f"Recovered payload copy failed: {PAYLOAD}")
    require(PAYLOAD.stat().st_size == int(result["bytes"]), "Recovered payload byte count changed during copy")

    row = {
        "recovery": "loot-notification-icon",
        "original": ORIGINAL_OBJECT,
        "relative_package": RELATIVE_PACKAGE,
        "source": {
            name.removeprefix("."): {
                "path": str(path),
                "sha256": sha256(path),
                "bytes": path.stat().st_size,
            }
            for name, path in components.items()
        },
        "payload": str(PAYLOAD),
        "payload_sha256": sha256(PAYLOAD),
        "bytes": int(result["bytes"]),
        "width": int(result["width"]),
        "height": int(result["height"]),
        "format": str(result["format"]),
        "srgb": bool(result["srgb"]),
        "exported": True,
    }
    REPORT.write_text(json.dumps(row, indent=2) + "\n", encoding="utf-8")
    unreal.log("LOOT_NOTIFICATION_ICON_EXPORTED " + json.dumps({"report": str(REPORT), "bytes": row["bytes"]}))


main()
