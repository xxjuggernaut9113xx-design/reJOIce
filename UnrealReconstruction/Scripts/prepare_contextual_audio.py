from __future__ import annotations

import hashlib
import json
from pathlib import Path
import struct


PROJECT = Path(__file__).resolve().parents[1]
ANALYSIS = Path(r"C:\Users\webma\analysis\cockhero-v004")
SOURCE_ROOT = ANALYSIS / "cooked-animation-audio" / "CockHero" / "Content"
DEFAULTS = ANALYSIS / "blueprint-default-values.json"
GLOBAL_MANAGER = ANALYSIS / "decoded" / "BP_GlobalManager.json"
SOURCE_FUNCTION = ANALYSIS / "blueprint-functions" / "BP_GlobalManager" / "PlayTagContextualBeatCompleteSFX.json"
OUTPUT = PROJECT / "RecoveryEvidence" / "AudioEncoded" / "ContextualAudio"
REPORT = PROJECT / "RecoveryEvidence" / "contextual-audio-source.json"

CATEGORIES = (
    ("assjob", "Assjob", "AssjobSoundsArray", 138),
    ("blowjob", "Blowjob", "BlowjobSoundsArray", 211),
    ("cowgirl", "Cowgirl", "CowgirlSoundsArray", 19),
    ("cum", "Cum", "CumSoundsArray", 247),
    ("handjob", "Handjob", "HandjobSoundsArray", 208),
    ("paizuri", "Paizuri", "PaizuriSoundsArray", 269),
    ("sex", "Sex", "SexSoundsArray", 199),
    ("succubus", "Succubus", "SuccubusSoundsArray", 30),
)


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
            if isinstance(package, str) and package.startswith("/Game/ContextualSoundFX/"):
                return package
            break
        current = record.get("OuterIndex") or 0
    raise RuntimeError(f"Contextual source package could not be resolved for import {index}")


def package_files(package_path: str, name: str) -> tuple[Path, Path, Path]:
    relative = package_path.removeprefix("/Game/")
    if relative == package_path or ".." in Path(relative).parts:
        raise RuntimeError(f"{name}: invalid source package {package_path}")
    base = SOURCE_ROOT / relative
    paths = base.with_suffix(".uasset"), base.with_suffix(".uexp"), base.with_suffix(".ubulk")
    for path in paths:
        if not path.is_file():
            raise RuntimeError(f"{name}: source component is missing: {path}")
    return paths


def main() -> None:
    for path in (DEFAULTS, GLOBAL_MANAGER, SOURCE_FUNCTION):
        if not path.is_file():
            raise RuntimeError(f"Required contextual audio evidence is unavailable: {path}")
    OUTPUT.mkdir(parents=True, exist_ok=True)
    properties = global_manager_properties()
    imports = json.loads(GLOBAL_MANAGER.read_text(encoding="utf-8"))["Imports"]
    tracks: list[dict] = []
    pools: dict[str, dict] = {}
    names: set[str] = set()

    for tag, folder, property_name, expected_count in CATEGORIES:
        entries = properties.get(property_name)
        if not isinstance(entries, list) or len(entries) != expected_count:
            raise RuntimeError(f"{property_name}: expected {expected_count} source entries")
        pool: list[str] = []
        for entry in entries:
            cue_name = entry.get("name")
            cue_index = entry.get("index")
            if not isinstance(cue_name, str) or not isinstance(cue_index, int) or not cue_name.endswith("Cue"):
                raise RuntimeError(f"{property_name}: invalid source cue reference {entry!r}")
            wave_name = cue_name[:-4]
            if wave_name in names:
                raise RuntimeError(f"Duplicate contextual wave name: {wave_name}")
            names.add(wave_name)
            cue_package = source_package(cue_index, imports)
            if not cue_package.endswith("_Cue"):
                raise RuntimeError(f"{cue_name}: source cue package does not have the expected suffix")
            wave_package = cue_package[:-4]
            asset_path, package_path, bulk_path = package_files(wave_package, wave_name)
            package = package_path.read_bytes()
            bulk = bulk_path.read_bytes()
            encoded, fields, chunk_count = reconstruct_bink_stream(package, bulk, wave_name)
            encoded_path = OUTPUT / folder / f"{wave_name}.binka"
            encoded_path.parent.mkdir(parents=True, exist_ok=True)
            encoded_path.write_bytes(encoded)
            tracks.append(
                {
                    "name": wave_name,
                    "tag": tag,
                    "folder": folder,
                    "original": f"{cue_package}.{cue_name}",
                    "original_wave": f"{wave_package}.{wave_name}",
                    "destination": f"/Game/Recovery/Resources/ContextualAudio/{folder}",
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
            )
            pool.append(wave_name)
        pools[tag] = {"folder": folder, "source_property": property_name, "tracks": pool}

    REPORT.write_text(
        json.dumps(
            {
                "recovery": "contextual-audio-streams",
                "source_executed": False,
                "source_function": {"path": str(SOURCE_FUNCTION), "sha256": file_sha256(SOURCE_FUNCTION)},
                "pools": pools,
                "tracks": tracks,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(json.dumps({"report": str(REPORT), "tracks": len(tracks), "pools": {tag: len(data["tracks"]) for tag, data in pools.items()}}, indent=2))


if __name__ == "__main__":
    main()
