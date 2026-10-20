"""Recover missing newer calibration schema directly from its executable/PDB."""
import json
from pathlib import Path
from newer_content_contract import PROJECT, SOURCE, require

analysis = PROJECT.parent / "Analysis"
temporary = Path("E:/reJOIceRecoveryCache/NewerSaveReflection")
temporary.mkdir(parents=True, exist_ok=True)
wrapper = analysis / "scripts/recover_newer_native_reflection.py"
text = wrapper.read_text(encoding="utf-8").split("exec(compile(source,str(root/'recover_native_schemas.py')")[0]
text = text.replace("dest=root/'ReferenceBuilds/newer-20261017'", "dest=Path(r'" + str(temporary) + "')")
scope = {"__file__": str(wrapper)}
exec(text, scope)
source = "\n".join(" if owner != 'LatencyProfile':continue" if line.startswith(" if not re.search(") else line for line in scope["source"].splitlines())
exec(compile(source, str(analysis / "recover_native_schemas.py"), "exec"), {"__file__": str(temporary / "recover_native_schemas.py")})
schema = json.loads((temporary / "native-reflection-schemas.json").read_text(encoding="utf-8"))["LatencyProfile"]
baseline = json.loads((analysis / "native-reflection-schemas.json").read_text(encoding="utf-8"))["LatencyProfile"]
fields = ("name", "kind", "flags", "dim", "offset", "extra_symbol")
match = [{k: p[k] for k in fields} for p in schema] == [{k: p[k] for k in fields} for p in baseline]
require(match, "LatencyProfile schema changed; baseline decoder is not valid")
(SOURCE / "save-latency-native-schema.json").write_text(json.dumps({"source_executed": False, "native_source": "newer executable/PDB", "matches_baseline_layout": match, "properties": schema}, indent=2) + "\n", encoding="utf-8")
print("NEWER_LATENCY_SCHEMA_VERIFIED " + str(len(schema)))
