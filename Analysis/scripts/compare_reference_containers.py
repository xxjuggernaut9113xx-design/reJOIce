"""Compare cooked game chunks using retoc's hashes, without extracting assets."""
import argparse
from collections import Counter
import json
from pathlib import Path
import subprocess


def inventory(retoc, container):
    result = subprocess.run([str(retoc), "list", str(container), "--hash", "--size", "--path"],
                            capture_output=True, text=True, encoding="utf-8", check=True)
    records = {}
    for line in result.stdout.splitlines():
        parts = line.split(maxsplit=5)
        if len(parts) != 6:
            raise ValueError(f"Unexpected retoc record: {line[:160]}")
        _, chunk_id, chunk_hash, chunk_type, size, path = parts
        prefix = "../../../CockHero/Content/"
        if not path.startswith(prefix):
            continue
        path = path[len(prefix):]
        key = (path, chunk_type)
        if key in records:
            raise ValueError(f"Duplicate chunk identity: {key}")
        records[key] = dict(path=path, chunk_type=chunk_type, chunk_id=chunk_id,
                            hash=chunk_hash, size=int(size))
    if not records:
        raise ValueError(f"No game chunks found in {container}")
    return records


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("baseline", type=Path)
    parser.add_argument("reference", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument("--retoc", type=Path, required=True)
    args = parser.parse_args()
    old, new = inventory(args.retoc, args.baseline), inventory(args.retoc, args.reference)
    added = [new[key] for key in sorted(new.keys() - old.keys())]
    absent = [old[key] for key in sorted(old.keys() - new.keys())]
    changed = [dict(path=key[0], chunk_type=key[1], baseline=old[key], reference=new[key])
               for key in sorted(old.keys() & new.keys()) if old[key]["hash"] != new[key]["hash"]]
    unchanged = sum(old[key]["hash"] == new[key]["hash"] for key in old.keys() & new.keys())
    summary = dict(baseline_game_chunks=len(old), reference_game_chunks=len(new),
                   added=len(added), absent=len(absent), changed=len(changed), unchanged=unchanged)
    groups = Counter(r["path"].split("/")[0] for r in added)
    report = dict(baseline_container=str(args.baseline), reference_container=str(args.reference),
                  original_game_executed=False, summary=summary,
                  added_by_top_directory=dict(sorted(groups.items())),
                  added=added, absent=absent, changed=changed,
                  interpretation="Chunk hashes establish byte differences, not semantic feature changes.")
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    print(json.dumps(summary))


if __name__ == "__main__":
    main()
