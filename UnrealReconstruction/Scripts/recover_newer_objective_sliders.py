"""Recover serialized objective slider bounds with full payload roundtrip checks."""
import base64
import hashlib
import json
from newer_content_contract import PROJECT, SOURCE, require

analysis = PROJECT.parent / "Analysis"
scope = {"__file__": str(analysis / "decode_ui_layout.py")}
exec((analysis / "decode_ui_layout.py").read_text(encoding="utf-8").split("records=[];failures=[]")[0], scope)
runtime = scope["ns"]
BaseReader, BaseWriter = runtime["Reader"], runtime["Writer"]


class SliderReader(BaseReader):
    def value(self, prop, zero=False):
        if prop["type"] in ("MulticastInlineDelegateProperty", "MulticastDelegateProperty", "MulticastSparseDelegateProperty"):
            return [] if zero else [{"object": self.ref(), "function": self.name()} for _ in range(self.num("i"))]
        return super().value(prop, zero)


class SliderWriter(BaseWriter):
    def value(self, prop, value, zero=False):
        if prop["type"] in ("MulticastInlineDelegateProperty", "MulticastDelegateProperty", "MulticastSparseDelegateProperty"):
            if not zero:
                self.num("i", len(value))
                for item in value:
                    self.num("i", item["object"]["index"] if item["object"] else 0)
                    self.name(item["function"])
            return
        return super().value(prop, value, zero)


path = SOURCE / "decoded-blueprints/GameModeCustomizationScreen_WIDGET-functions.json"
asset = json.loads(path.read_text(encoding="utf-8"))
sliders = {}
for export in asset["Exports"]:
    if export["ClassIndex"] >= 0 or asset["Imports"][-export["ClassIndex"]-1]["ObjectName"] != "Slider":
        continue
    raw = base64.b64decode(export["Data"])
    reader = SliderReader(raw, asset)
    values = reader.properties("Slider")
    guid = reader.num("I")
    require(guid == 0 and reader.pos == len(raw), f"Slider payload not consumed: {export['ObjectName']}")
    writer = SliderWriter(reader)
    writer.properties("Slider", values)
    writer.num("I", guid)
    require(bytes(writer.data) == raw, f"Slider source payload differs: {export['ObjectName']}")
    sliders[export["ObjectName"]] = {"values": values, "byte_identical_roundtrip": True, "payload_sha256": hashlib.sha256(raw).hexdigest()}
result = {"source_executed": False, "source_sha256": hashlib.sha256(path.read_bytes()).hexdigest(), "sliders": sliders}
(SOURCE / "objective-slider-defaults.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
print(json.dumps({k: {p: v for p, v in r["values"].items() if p in ("MinValue", "MaxValue", "Value", "StepSize")} for k, r in sliders.items()}))
