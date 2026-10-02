"""Minimal known-empty UObject schema for UFunction metadata decoding only.
Not game property mappings and not suitable for class defaults/table rows.
"""
import pathlib, struct
names = ["Function"]
body = struct.pack('<I', len(names))
for name in names:
    encoded = name.encode('ascii')
    body += struct.pack('<B', len(encoded)) + encoded
body += struct.pack('<II', 0, 1)  # enum count, schema count
body += struct.pack('<iiHH', 0, -1, 0, 0)
data = struct.pack('<HBBII', 0x30c4, 0, 0, len(body), len(body)) + body
target = pathlib.Path.home() / 'AppData/Local/UAssetGUI/Mappings/FunctionOnly.usmap'
target.parent.mkdir(parents=True, exist_ok=True)
target.write_bytes(data)
print(target)
