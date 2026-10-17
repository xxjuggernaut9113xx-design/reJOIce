from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
ANIMATION_AUDIO = ANALYSIS / "cooked-animation-audio" / "CockHero" / "Content" / "SoundFX"
UI_AUDIO = ANALYSIS / "cooked-ui-audio" / "CockHero" / "Content" / "SoundFX"
DEFAULTS = ANALYSIS / "blueprint-default-values.json"
GLOBAL_MANAGER = ANALYSIS / "decoded" / "BP_GlobalManager.json"
SOURCE_FUNCTIONS = (
    ANALYSIS / "blueprint-functions" / "BP_GlobalManager" / "DetermineAndPlayBeatSFX.json",
    ANALYSIS / "blueprint-functions" / "BP_GlobalManager" / "DetermineAndPlayHeatSFX.json",
)
OUTPUT = PROJECT / "RecoveryEvidence" / "AudioEncoded" / "BeatAudio"
REPORT = PROJECT / "RecoveryEvidence" / "beat-audio-source.json"


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def reconstruct_bink_stream(package: bytes, bulk: bytes, name: str) -> tuple[bytes, tuple[int, ...], int]:
    header_offset = package.find(b"ABEU")
    if header_offset < 0:
        raise RuntimeError(f"{name}: Bink header was not found")
    header = package[header_offset : header_offset + 28]
    if len(header) != 28:
        raise RuntimeError(f"{name}: Bink header is truncated")
    fields = struct.unpack("<IBBHIIHHIHH", header)
    if fields[1] != 1 or fields[-2] != 0:
        raise RuntimeError(f"{name}: unexpected Bink header layout")

    offsets: list[int] = []
    cursor = 0
    while True:
        cursor = bulk.find(b"SEEK", cursor)
        if cursor < 0:
            break
        offsets.append(cursor)
        cursor += 4
    if not offsets or offsets[0] != 0:
        raise RuntimeError(f"{name}: Bink stream chunks were not found")

    chunks: list[bytes] = []
    seek_bytes = 0
    for index, offset in enumerate(offsets):
        if offset + 15 > len(bulk) or bulk[offset + 4] != 0:
            raise RuntimeError(f"{name}: invalid Bink SEEK record")
        seek_count = struct.unpack_from("<i", bulk, offset + 11)[0]
        if seek_count <= 0 or seek_count >= 100000:
            raise RuntimeError(f"{name}: invalid Bink seek-table count")
        content_offset = offset + 15 + 2 * seek_count
        end = offsets[index + 1] if index + 1 < len(offsets) else len(bulk)
        if content_offset >= end or bulk[content_offset : content_offset + 2] != b"\x99\x99":
            raise RuntimeError(f"{name}: invalid Bink packet boundary")
        chunks.append(bulk[content_offset:end])
        seek_bytes += 2 * seek_count

    encoded = header + b"".join(chunks)
    if fields[8] != len(encoded) + seek_bytes:
        raise RuntimeError(f"{name}: reconstructed Bink length differs from source metadata")
    return encoded, fields, len(offsets)


def global_manager_properties() -> dict:
    decoded = json.loads(DEFAULTS.read_text(encoding="utf-8"))
    for item in decoded["objects"]:
        if item.get("class") == "BP_GlobalManager_C":
            return item["serialized_properties"]
    raise RuntimeError("BP_GlobalManager source defaults are unavailable")


def source_package(index: int, imports: list[dict]) -> str:
    current = index
    while current < 0:
        record = imports[-current - 1]
        if record.get("ClassName") == "Package":
            package = record.get("ObjectName")
            if not isinstance(package, str) or not package.startswith("/Game/"):
                break
            return package
        current = record.get("OuterIndex") or 0
    raise RuntimeError(f"source package could not be resolved for import {index}")


def package_files(root: Path, relative_package: str, name: str) -> tuple[Path, Path, Path]:
    prefix = "/Game/SoundFX/"
    if not relative_package.startswith(prefix):
        raise RuntimeError(f"{name}: unsupported source package {relative_package}")
    path = root / relative_package.removeprefix(prefix)
    files = path.with_suffix(".uasset"), path.with_suffix(".uexp"), path.with_suffix(".ubulk")
    for file in files:
        if not file.is_file():
            raise RuntimeError(f"{name}: source component is missing: {file}")
    return files


def track_row(
    *,
    name: str,
    source_root: Path,
    source_package_path: str,
    original: str,
    destination: str,
    kind: str,
    pool: str | None = None,
    original_wave: str | None = None,
) -> dict:
    asset_path, package_path, bulk_path = package_files(source_root, source_package_path, name)
    package = package_path.read_bytes()
    bulk = bulk_path.read_bytes()
    encoded, fields, chunk_count = reconstruct_bink_stream(package, bulk, name)
    encoded_path = OUTPUT / (pool or "Core") / f"{name}.binka"
    encoded_path.parent.mkdir(parents=True, exist_ok=True)
    encoded_path.write_bytes(encoded)
    row = {
        "name": name,
        "kind": kind,
        "pool": pool,
        "original": original,
        "destination": destination,
        "source_asset": str(asset_path),
        "source_package": str(package_path),
        "source_bulk": str(bulk_path),
        "source_asset_sha256": file_sha256(asset_path),
        "source_package_sha256": sha256(package),
        "source_bulk_sha256": sha256(bulk),
        "encoded": str(encoded_path),
        "encoded_sha256": sha256(encoded),
        "sample_rate": fields[4],
        "channels": fields[2],
        "frames": fields[5],
        "stream_chunks": chunk_count,
        "source_executed": False,
    }
    if original_wave is not None:
        row["original_wave"] = original_wave
    return row


def main() -> None:
    for source in (*SOURCE_FUNCTIONS, DEFAULTS, GLOBAL_MANAGER):
        if not source.is_file():
            raise RuntimeError(f"Required source evidence is unavailable: {source}")

    OUTPUT.mkdir(parents=True, exist_ok=True)
    properties = global_manager_properties()
    global_manager = json.loads(GLOBAL_MANAGER.read_text(encoding="utf-8"))
    imports = global_manager["Imports"]
    tracks: list[dict] = []
    pools: dict[str, list[str]] = {}
    pool_definitions = (
        ("Slow", "Slow_MoanSFX_Array_MASTER"),
        ("Medium", "Medium_MoanSFX_Array_MASTER"),
        ("Fast", "Fast_MoanSFX_Array_MASTER"),
    )
    for pool, property_name in pool_definitions:
        entries = properties.get(property_name)
        if not isinstance(entries, list) or not entries:
            raise RuntimeError(f"{property_name}: source pool is unavailable")
        names: list[str] = []
        for entry in entries:
            cue_name = entry.get("name")
            cue_index = entry.get("index")
            if not isinstance(cue_name, str) or not isinstance(cue_index, int) or not cue_name.endswith("Cue"):
                raise RuntimeError(f"{property_name}: invalid source cue reference {entry!r}")
            wave_name = cue_name[:-4]
            cue_package = source_package(cue_index, imports)
            if not cue_package.endswith("_Cue"):
                raise RuntimeError(f"{cue_name}: source cue package does not have the expected suffix")
            wave_package = cue_package[:-4]
            tracks.append(
                track_row(
                    name=wave_name,
                    source_root=ANIMATION_AUDIO,
                    source_package_path=wave_package,
                    original=f"{cue_package}.{cue_name}",
                    original_wave=f"{wave_package}.{wave_name}",
                    destination=f"/Game/Recovery/Resources/BeatMoans/{pool}",
                    kind="moan",
                    pool=pool,
                )
            )
            names.append(wave_name)
        pools[pool] = names

    tracks.append(
        track_row(
            name="casual-click-pop-ui-10-262126",
            source_root=UI_AUDIO,
            source_package_path="/Game/SoundFX/casual-click-pop-ui-10-262126",
            original="/Game/SoundFX/casual-click-pop-ui-10-262126.casual-click-pop-ui-10-262126",
            destination="/Game/Recovery/Resources/BeatAudio",
            kind="metronome",
        )
    )
    tracks.append(
        track_row(
            name="heatfiresfx",
            source_root=ANIMATION_AUDIO,
            source_package_path="/Game/SoundFX/heatfiresfx",
            original="/Game/SoundFX/heatfiresfx.heatfiresfx",
            destination="/Game/Recovery/Resources/BeatAudio",
            kind="heat",
        )
    )

    if len(pools["Slow"]) != 47 or len(pools["Medium"]) != 61 or len(pools["Fast"]) != 72:
        raise RuntimeError(f"Unexpected source moan-pool counts: { {key: len(value) for key, value in pools.items()} }")

    REPORT.write_text(
        json.dumps(
            {
                "recovery": "beat-audio-streams",
                "source_executed": False,
                "source_functions": [
                    {"path": str(source), "sha256": file_sha256(source)} for source in SOURCE_FUNCTIONS
                ],
                "pools": pools,
                "tracks": tracks,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(json.dumps({"report": str(REPORT), "tracks": len(tracks), "pools": {key: len(value) for key, value in pools.items()}}, indent=2))


if __name__ == "__main__":
    main()
