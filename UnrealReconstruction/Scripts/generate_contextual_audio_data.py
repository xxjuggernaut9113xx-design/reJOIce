from __future__ import annotations

import json
from pathlib import Path


PROJECT = Path(__file__).resolve().parents[1]
SOURCE = PROJECT / "RecoveryEvidence" / "contextual-audio-source.json"
OUTPUT = PROJECT / "Source" / "CockHeroRecovered" / "RecoveredContextualAudioData.inl"


def main() -> None:
    source = json.loads(SOURCE.read_text(encoding="utf-8"))
    lines: list[str] = []
    for tag, pool in source["pools"].items():
        folder = pool["folder"]
        names = pool["tracks"]
        symbol = f"GRecoveredContextual{folder}Sounds"
        lines.append(f"static const TCHAR* const {symbol}[] = {{")
        lines.extend(f'    TEXT("{name}"),' for name in names)
        lines.append("};")
        lines.append("")
    OUTPUT.write_text("\n".join(lines), encoding="utf-8")
    print(json.dumps({"output": str(OUTPUT), "pools": {tag: len(pool["tracks"]) for tag, pool in source["pools"].items()}}, indent=2))


if __name__ == "__main__":
    main()
