"""Recover seven shipped dialogue tables with byte-identical decode/write checks."""
import base64
import hashlib
import json
from pathlib import Path
import re
import subprocess
from newer_content_contract import PROJECT, SOURCE, require

ANALYSIS = PROJECT.parent / "Analysis"
LEGACY = Path("E:/reJOIceRecoveryCache/NewerDialogueLegacy")
CONTENT = LEGACY / "CockHero/Content/DialogueDTs"
DECODED = SOURCE / "decoded-dialogue"
DECODED.mkdir(parents=True, exist_ok=True)
PACKS = {"Default": "VillainessVoiceLines_DT", "Brat": "TeasingBratVoiceLines_DT",
         "DommyMommy": "DommyMommyVoicelines_DT", "Sweetheart": "SweetheartVoicelines_DT",
         "Yandere": "Yandere_DT", "Chariot": "Chariot_MiniPack_Dialogue_DT", "Pepper": "Pepper_MiniPack_Dialogue_DT"}
for name in [*PACKS.values(), "DialogueBucket"]:
    subprocess.run(["C:/Users/webma/analysis/cockhero-v004/tools/uassetgui/UAssetGUI.exe", "tojson", str(CONTENT / (name + ".uasset")),
                    str(DECODED / (name + "-raw.json")), "VER_UE5_3", "FunctionOnly"], check=True, creationflags=subprocess.CREATE_NO_WINDOW)

decoder = ANALYSIS / "scripts/recover_newer_table_values.py"
scope = {"__file__": str(decoder)}
exec(decoder.read_text(encoding="utf-8").split("classes=[];failures=[];tables=[]")[0], scope)
reader_scope = scope["scope"]
for cls in json.loads((SOURCE / "table-values.json").read_text(encoding="utf-8"))["recovered_struct_schemas"]:
    reader_scope["schemas"][cls["class"]] = cls["properties"]
    reader_scope["supers"][cls["class"]] = cls["super"]
for path in DECODED.glob("*-raw.json"):
    for cls in scope["reflection"]["read_asset"](path):
        reader_scope["schemas"][cls["class"]] = cls["properties"]
        reader_scope["supers"][cls["class"]] = cls["super"]


def normalize(value, asset):
    if isinstance(value, list):
        return [normalize(v, asset) for v in value]
    if not isinstance(value, dict):
        return value
    if "index" in value and "name" in value:
        def reference(index):
            if index == 0:
                return None
            entry = (asset["Exports"] if index > 0 else asset["Imports"])[index - 1 if index > 0 else -index - 1]
            outer = reference(entry.get("OuterIndex", 0))
            return (outer + "." if outer else "") + entry["ObjectName"]
        return reference(value["index"])
    if "text" in value:
        return value["text"]
    return {re.sub(r"_\d+_[A-Fa-f0-9]{32}$", "", k): normalize(v, asset) for k, v in value.items()}


packs, proof = {}, {}
for pack, table in PACKS.items():
    path = DECODED / (table + "-raw.json")
    asset = json.loads(path.read_text(encoding="utf-8"))
    export = next(e for e in asset["Exports"] if e["ObjectName"] == table)
    raw = base64.b64decode(export["Data"])
    reader = reader_scope["Reader"](raw, asset)
    properties = reader.properties("DataTable")
    require(reader.num("I") == 0, f"Unexpected table GUID: {table}")
    count = reader.num("i")
    require(0 < count < 10000, f"Invalid dialogue row count: {table}")
    row_class = properties["RowStruct"]["name"]
    rows = [{"row": reader.name(), "values": reader.properties(row_class)} for _ in range(count)]
    require(reader.pos == len(raw), f"Unconsumed dialogue source bytes: {table}")
    writer = reader_scope["Writer"](reader)
    writer.properties("DataTable", properties)
    writer.num("I", 0)
    writer.num("i", count)
    for row in rows:
        writer.name(row["row"])
        writer.properties(row_class, row["values"])
    require(bytes(writer.data) == raw, f"Dialogue payload differs on roundtrip: {table}")
    packs[pack] = [{"row": row["row"], **normalize(row["values"], asset)} for row in rows]
    proof[pack] = {"table": table, "row_class": row_class, "rows": count,
                   "payload_sha256": hashlib.sha256(raw).hexdigest(), "byte_identical_roundtrip": True,
                   "decoded_source": str(path.relative_to(PROJECT.parent))}
result = {"source_executed": False, "packs": packs, "proof": proof}
(PROJECT / "Content/Recovery/Definitions/newer-20261017-dialogue-catalog.json").write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({pack: len(rows) for pack, rows in packs.items()}))
