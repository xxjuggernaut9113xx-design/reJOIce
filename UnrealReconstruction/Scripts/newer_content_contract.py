"""Versioned, source-bound progression contract. Runs without Unreal."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

PROJECT = Path(__file__).resolve().parents[1]
SOURCE = PROJECT.parent / "Analysis/ReferenceBuilds/newer-20261017"
DEFINITION = PROJECT / "Content/Recovery/Definitions/newer-20261017-progression.json"
DESTINATION = "/Game/Recovery/Newer20261017"
COUNTS = {"DT_Challenges": 70, "DT_PlayerCards": 48, "DT_LevelData": 20}
KEYS = {"DT_Challenges": "ChallengeID", "DT_PlayerCards": "CardID", "DT_LevelData": "Level"}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def validate(catalog, raw):
    require(not raw["failures"], "Newer table source contains decoding failures")
    proofs = {table["table"]: table for table in raw["tables"]}
    enums = catalog["native_enums"]
    for name, count in COUNTS.items():
        require(name in proofs and proofs[name].get("byte_identical_roundtrip") is True,
                f"Missing byte-identical source proof: {name}")
        rows = catalog["tables"][name]
        require(len(rows) == count, f"Unexpected {name} row count")
        require(len({r["row"] for r in rows}) == count, f"Duplicate {name} row names")
        require(len({r[KEYS[name]] for r in rows}) == count, f"Duplicate {name} identifiers")
    challenge_ids = {r["ChallengeID"] for r in catalog["tables"]["DT_Challenges"]}
    valid_metrics = {r["name"] for r in enums["EMetricType"] if not r["name"].endswith("::MAX")}
    for row in catalog["tables"]["DT_Challenges"]:
        for requirement in row["Requirements"]:
            require(requirement["MetricType"] in valid_metrics, f"Unknown metric: {requirement['MetricType']}")
    for row in catalog["tables"]["DT_PlayerCards"]:
        require(not row["RequiredChallengeID"] or row["RequiredChallengeID"] in challenge_ids,
                f"Unknown card challenge: {row['CardID']}")
    return {name: catalog["tables"][name] for name in COUNTS}


def load_source():
    catalog = json.loads((SOURCE / "normalized-content-catalog.json").read_text(encoding="utf-8"))
    raw = json.loads((SOURCE / "table-values.json").read_text(encoding="utf-8"))
    tables = validate(catalog, raw)
    for proof in raw["tables"]:
        require(proof.get("byte_identical_roundtrip") is True, f"Unverified supplemental source: {proof['table']}")
        require(len(proof["rows"]) == len(catalog["tables"][proof["table"]]), f"Supplemental source row count differs: {proof['table']}")
    return {"version": "newer-20261017", "source_executed": False,
            "sources": {name: digest(SOURCE / name) for name in ("normalized-content-catalog.json", "table-values.json")},
            "source_tables": {t["table"]: {k: t[k] for k in ("payload_sha256", "byte_identical_roundtrip", "source")}
                              for t in raw["tables"]},
            "native_enums": catalog["native_enums"], "tables": tables,
            "supplemental_tables": {k: v for k, v in catalog["tables"].items() if k not in COUNTS}}


def required_artwork(contract):
    return sorted({r[field] for table, field in (("DT_Challenges", "Icon"), ("DT_PlayerCards", "CardImage"))
                   for r in contract["tables"][table]})


def all_artwork(contract):
    return sorted(set(required_artwork(contract)) | {r["ModifierIcon"] for r in contract["supplemental_tables"]["ModifierInfoDataTable"]})


def canonical(value):
    if value is None:
        return ""
    if isinstance(value, list):
        return [canonical(v) for v in value]
    if isinstance(value, dict):
        return {k.lower().replace(" ", ""): canonical(v) for k, v in value.items()}
    return value


def table_rows(rows):
    def normalize(value):
        if value is None:
            return ""
        if isinstance(value, dict):
            return {k: normalize(v) for k, v in value.items()}
        if isinstance(value, list):
            return [normalize(v) for v in value]
        return value
    return [{"Name": r["row"], **normalize({k: v for k, v in r.items() if k != "row"})} for r in rows]


if __name__ == "__main__":
    contract = load_source()
    DEFINITION.parent.mkdir(parents=True, exist_ok=True)
    DEFINITION.write_text(json.dumps(contract, ensure_ascii=False, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"definition": str(DEFINITION), "rows": COUNTS, "artwork": len(required_artwork(contract))}))
