"""Fingerprint a reference build without executing it or replacing old evidence."""
import argparse
import hashlib
import json
import mmap
from pathlib import Path
import re
import struct


def digest(path):
    with path.open("rb") as handle:
        return hashlib.file_digest(handle, "sha256").hexdigest()


def write_json(path, value):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


def native_inventory(exe, pdb, baseline):
    u32 = lambda data, offset: struct.unpack_from("<I", data, offset)[0]
    with exe.open("rb") as pe_file, pdb.open("rb") as pdb_file:
        with mmap.mmap(pe_file.fileno(), 0, access=mmap.ACCESS_READ) as pe, \
                mmap.mmap(pdb_file.fileno(), 0, access=mmap.ACCESS_READ) as data:
            if not data[:32].startswith(b"Microsoft C/C++ MSF 7.00"):
                raise ValueError("Unsupported PDB format")
            block, _, _, directory_size, _, blockmap = struct.unpack_from("<6I", data, 32)
            count = (directory_size + block - 1) // block
            ids = struct.unpack_from("<" + "I" * count, data, blockmap * block)
            directory = b"".join(data[i * block:(i + 1) * block] for i in ids)[:directory_size]
            count = u32(directory, 0)
            sizes = struct.unpack_from("<" + "I" * count, directory, 4)
            pos, streams = 4 + 4 * count, []
            for size in sizes:
                nblocks = 0 if size == 0xffffffff else (size + block - 1) // block
                ids = struct.unpack_from("<" + "I" * nblocks, directory, pos)
                pos += 4 * nblocks
                streams.append((size, ids))

            def stream(index):
                size, ids = streams[index]
                return b"".join(data[i * block:(i + 1) * block] for i in ids)[:size]

            peoff = u32(pe, 0x3c)
            if pe[peoff:peoff + 4] != b"PE\0\0":
                raise ValueError("Invalid PE signature")
            optional = peoff + 24
            if struct.unpack_from("<H", pe, optional)[0] != 0x20b:
                raise ValueError("Expected PE32+ executable")
            imagebase = struct.unpack_from("<Q", pe, optional + 24)[0]
            section_start = optional + struct.unpack_from("<H", pe, peoff + 20)[0]
            sections = []
            for index in range(struct.unpack_from("<H", pe, peoff + 6)[0]):
                at = section_start + 40 * index
                sections.append(dict(name=pe[at:at + 8].rstrip(b"\0").decode(),
                                     rva=u32(pe, at + 12), rawsize=u32(pe, at + 16),
                                     raw=u32(pe, at + 20)))
            debug_rva, debug_size = struct.unpack_from("<II", pe, optional + 112 + 6 * 8)
            section = next(s for s in sections if s["rva"] <= debug_rva < s["rva"] + s["rawsize"])
            debug_at = section["raw"] + debug_rva - section["rva"]
            codeview = None
            for at in range(debug_at, debug_at + debug_size, 28):
                pointer = u32(pe, at + 24)
                if u32(pe, at + 12) == 2 and pe[pointer:pointer + 4] == b"RSDS":
                    codeview = pointer
                    break
            info = stream(1)
            match = codeview is not None and pe[codeview + 4:codeview + 20] == info[12:28] \
                and u32(pe, codeview + 20) == u32(info, 8)
            if not match:
                raise ValueError("Executable/PDB GUID and age do not match")

            old = json.loads(baseline.read_text(encoding="utf-8-sig"))
            # Match function owners, not UE types appearing in decorated arguments.
            classes = sorted(set(re.findall(r"^\?[^@]+@((?:U|A)[A-Za-z0-9_]+)@@", "\n".join(r["name"] for r in old), re.MULTILINE)))
            target = re.compile(r"@(?:" + "|".join(map(re.escape, classes)) + r")@@")
            dbi = stream(3)
            symbols = stream(struct.unpack_from("<H", dbi, 20)[0])
            at, hits = 0, []
            while at + 4 <= len(symbols):
                length, kind = struct.unpack_from("<HH", symbols, at)
                if length < 2 or at + length + 2 > len(symbols):
                    raise ValueError("Malformed PDB symbol record")
                if kind == 0x110e and length >= 12:
                    flags, offset, segment = struct.unpack_from("<IIH", symbols, at + 4)
                    name = symbols[at + 14:at + length + 2].split(b"\0")[0].decode("utf-8", errors="replace")
                    if flags & 2 and target.search(name) and 0 < segment <= len(sections):
                        section = sections[segment - 1]
                        hits.append(dict(name=name, address=hex(imagebase + section["rva"] + offset),
                                         file_offset=section["raw"] + offset, section=section["name"]))
                at += length + 2
            old_names, new_names = {r["name"] for r in old}, {r["name"] for r in hits}
            return dict(guid_and_age_match=match, pdb_guid_bytes=info[12:28].hex(),
                        pdb_age=u32(info, 8), classes=classes, symbol_count=len(hits),
                        baseline_symbol_count=len(old),
                        added_symbols=sorted(new_names - old_names),
                        absent_symbols=sorted(old_names - new_names),
                        retained_symbol_count=len(old_names & new_names)), sorted(hits, key=lambda r: int(r["address"], 16))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="Packaged Windows directory")
    parser.add_argument("output", type=Path, help="Separate evidence directory")
    parser.add_argument("--baseline-symbols", type=Path, default=Path(__file__).resolve().parents[1] / "native-symbol-addresses.json")
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if output == source or source in output.parents or output in source.parents:
        parser.error("Source and output must be separate directory trees")
    game = source / "CockHero"
    binaries = game / "Binaries/Win64"
    files = [source / "CockHero.exe", binaries / "CockHero.exe", binaries / "CockHero.pdb"]
    files += sorted((game / "Content/Paks").glob("*"))
    fingerprints = [dict(path=str(p.relative_to(source)), size=p.stat().st_size, sha256=digest(p)) for p in files if p.is_file()]
    native, symbols = native_inventory(binaries / "CockHero.exe", binaries / "CockHero.pdb", args.baseline_symbols)
    packs, errors = [], []
    for manifest in sorted((game / "Extracted").glob("*/manifest.json")):
        try:
            raw = manifest.read_bytes()
            encoding = "utf-16" if raw.startswith((b"\xff\xfe", b"\xfe\xff")) else "utf-8-sig"
            try:
                text = raw.decode(encoding)
            except UnicodeDecodeError:
                encoding = "cp1252"
                text = raw.decode(encoding)
            value = json.loads(text)
            packs.append(dict(directory=manifest.parent.name, sha256=digest(manifest),
                              encoding=encoding,
                              version=value.get("version"), media_count=len(value.get("media", [])),
                              fields=sorted(value.keys())))
        except (ValueError, OSError) as error:
            errors.append(dict(path=str(manifest), error=str(error)))
    beatmaps = []
    for path in sorted((game / "beatmaps").rglob("*.json")):
        value = json.loads(path.read_text(encoding="utf-8-sig"))
        beatmaps.append(dict(path=str(path.relative_to(game)), sha256=digest(path),
                             top_level_fields=sorted(value.keys()) if isinstance(value, dict) else None))
    write_json(output / "native-symbol-addresses.json", symbols)
    write_json(output / "reference-inventory.json", dict(source_root=str(source), original_game_executed=False,
               files=fingerprints, native=native, packs=packs, beatmaps=beatmaps, errors=errors,
               coverage="Native symbol comparison covers baseline classes only; not full feature parity."))
    print(json.dumps(dict(native_symbols=len(symbols), added_symbols=len(native["added_symbols"]),
                          absent_symbols=len(native["absent_symbols"]), packs=len(packs),
                          beatmaps=len(beatmaps), errors=len(errors))))


if __name__ == "__main__":
    main()
