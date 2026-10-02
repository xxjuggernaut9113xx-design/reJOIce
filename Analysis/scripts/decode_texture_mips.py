"""Decode recovered cooked top mips into editable PNG source artwork."""
from pathlib import Path
import io
import json
import struct
import sys

root = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(root/'tools/pillow'))
from PIL import Image

project = root/'UnrealReconstruction'
report_path = project/'Saved/texture-export-report.json'
if not report_path.exists():
    rows = [json.loads((project/'Saved/texture-probe.json').read_text())]
    rows[0]['original'] = '/Game/UI/SettingsIcon.SettingsIcon'
else:
    rows = json.loads(report_path.read_text())
output = project/'RecoveryEvidence/TextureSource'
output.mkdir(parents=True, exist_ok=True)
for row in rows:
    if not row['success']:
        continue
    try:
        raw = Path(row['file']).read_bytes()
        width, height, fmt = row['width'], row['height'], row['format']
        if fmt in ('DXT1', 'DXT3', 'DXT5', 'BC4', 'BC5', 'BC7'):
            fourcc = {'BC4': 'ATI1', 'BC5': 'ATI2', 'BC7': 'DX10'}.get(fmt, fmt)
            header = struct.pack('<7I', 124, 0x81007, height, width, len(raw), 0, 1)
            header += bytes(44)
            header += struct.pack('<II4s5I', 32, 4, fourcc.encode('ascii'), 0, 0, 0, 0, 0)
            header += struct.pack('<5I', 0x1000, 0, 0, 0, 0)
            extension = struct.pack('<5I', 99 if row['srgb'] else 98, 3, 0, 1, 0) if fmt == 'BC7' else b''
            image = Image.open(io.BytesIO(b'DDS '+header+extension+raw)).convert('RGBA')
        elif fmt in ('B8G8R8A8', 'R8G8B8A8'):
            image = Image.frombytes('RGBA', (width, height), raw, 'raw', 'BGRA' if fmt == 'B8G8R8A8' else 'RGBA')
        elif fmt == 'G8':
            image = Image.frombytes('L', (width, height), raw)
        else:
            raise ValueError('Unsupported pixel format '+fmt)
        assert image.size == (width, height)
        destination = output/(row['original'].split('.', 1)[0][len('/Game/'):]+'.png')
        destination.parent.mkdir(parents=True, exist_ok=True)
        image.save(destination)
        row['png'] = str(destination)
        row['decoded'] = True
    except Exception as exc:
        row['decoded'] = False
        row['decode_error'] = str(exc)
(project/'RecoveryEvidence/texture-decoding-report.json').write_text(json.dumps(rows, indent=2), encoding='utf-8')
print(json.dumps({'exported': sum(r['success'] for r in rows), 'decoded': sum(r.get('decoded', False) for r in rows), 'errors': [r for r in rows if r['success'] and not r.get('decoded')]}))
