"""Normalize newly recovered loadout assets without rewriting prior evidence."""
import ast
import json
import re
from pathlib import Path

analysis = Path(__file__).resolve().parents[1]
source = analysis / "scripts/summarize_newer_blueprints.py"
tree = ast.parse(source.read_text(encoding="utf-8"))
functions = [node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name in ("kind", "compact_asset")]
namespace = {}
exec(compile(ast.Module(body=functions, type_ignores=[]), str(source), "exec"), namespace)
root = analysis / "ReferenceBuilds/newer-20261017"
for name in ("LoadoutEquipScreen_Widget", "WBP_LoadoutSlot", "WBP_EquipItemIcon"):
    path = root / "decoded-blueprints" / (name + "-functions.json")
    if not path.exists():
        continue
    asset = json.loads(path.read_text(encoding="utf-8"))
    output = root / "functions" / name
    output.mkdir(parents=True, exist_ok=True)
    for function, statements in namespace["compact_asset"](asset).items():
        destination = output / (re.sub(r"[^A-Za-z0-9_.-]+", "_", function) + ".json")
        destination.write_text(json.dumps({"function": function, "statements": statements}, indent=2) + "\n", encoding="utf-8")
    print(name, len(namespace["compact_asset"](asset)))
