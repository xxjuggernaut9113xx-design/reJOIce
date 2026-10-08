from pathlib import Path
import hashlib
import json

import unreal

project = Path(unreal.Paths.project_dir())
source = Path(r"C:\Users\webma\analysis\cockhero-v004\cooked-ui\CockHero\Content")
icons = ("PrematureCumIcon", "SuccessfulCumIcon")
rows = []


for name in icons:
    relative = "Widgets/NotificationBoxIcons/" + name
    package = source / (relative + ".uasset")
    if not package.exists():
        raise RuntimeError("Missing cooked source package " + str(package))
    result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(source), relative))
    original = "/Game/Widgets/NotificationBoxIcons/{0}.{0}".format(name)
    result["original"] = original
    result["source_package_sha256"] = hashlib.sha256(package.read_bytes()).hexdigest()
    if not result.get("success"):
        raise RuntimeError("Cooked mip export failed for " + name + ": " + result.get("error", "unknown error"))
    raw = Path(result["file"]).read_bytes()
    result["mip_sha256"] = hashlib.sha256(raw).hexdigest()
    rows.append(result)

report = project / "Saved" / "outcome-notification-icon-recovery-report.json"
report.write_text(json.dumps(rows, indent=2), encoding="utf-8")
unreal.log("OUTCOME_NOTIFICATION_MIPS_EXPORTED " + str(len(rows)))
