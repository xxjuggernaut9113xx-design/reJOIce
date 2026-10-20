"""Decode the newer SaveGame CDO without opening any user save slot."""
import base64
import hashlib
import json
from pathlib import Path
from newer_content_contract import PROJECT, SOURCE, require

analysis = PROJECT.parent / "Analysis"
decoder = analysis / "scripts/recover_newer_blueprint_defaults.py"
scope = {"__file__": str(decoder)}
exec(decoder.read_text(encoding="utf-8").split("classes=[];failures=[];defaults=[]")[0], scope)
reader_scope = scope["scope"]
baseline_scope = {"__file__": str(analysis / "decode_defaults.py")}
exec((analysis / "decode_defaults.py").read_text(encoding="utf-8").split("results=[];failures=[];checks=[]")[0], baseline_scope)
latency_schema = SOURCE / "save-latency-native-schema.json"
require(json.loads(latency_schema.read_text(encoding="utf-8"))["matches_baseline_layout"], "Newer LatencyProfile schema has not been verified")
reader_scope["schemas"]["LatencyProfile"] = baseline_scope["schemas"]["LatencyProfile"]
path = SOURCE / "decoded-blueprints/BP_CHSaveGame-functions.json"
asset = json.loads(path.read_text(encoding="utf-8"))
classes = scope["reflection"]["read_asset"](path)
for cls in classes:
    reader_scope["schemas"][cls["class"]] = cls["properties"]
    reader_scope["supers"][cls["class"]] = cls["super"]
export = next(e for e in asset["Exports"] if e["ObjectName"] == "Default__BP_CHSaveGame_C")
raw = base64.b64decode(export["Data"])
reader = reader_scope["Reader"](raw, asset)
values = reader.properties("BP_CHSaveGame_C")
guid = reader.num("I")
require(guid == 0 and reader.pos == len(raw), "SaveGame CDO parse did not consume its exact payload")
writer = reader_scope["Writer"](reader)
writer.properties("BP_CHSaveGame_C", values)
writer.num("I", guid)
require(bytes(writer.data) == raw, "SaveGame CDO payload changed on roundtrip")
result = {"source_executed": False, "user_save_opened": False, "class": "BP_CHSaveGame_C",
          "byte_identical_roundtrip": True, "payload_sha256": hashlib.sha256(raw).hexdigest(),
          "decoded_source_sha256": hashlib.sha256(path.read_bytes()).hexdigest(), "values": values,
          "properties": classes[0]["properties"],
          "latency_schema_evidence_sha256": hashlib.sha256(latency_schema.read_bytes()).hexdigest(),
          "omitted_zero_defaults": {name: 0 for name in ("LastObjectiveIndex_Classic", "PlayerPronounSelection")
                                    if name not in values and any(p["name"] == name for p in classes[0]["properties"])}}
target = SOURCE / "save-class-defaults.json"
target.write_text(json.dumps(result, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
print(json.dumps({k: v for k, v in values.items() if "LastObjective" in k or "Slider" in k or "Pronoun" in k or "SPH" in k or "VoiceLinesEnabled" in k}))
