from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import json
import subprocess

root = Path(__file__).resolve().parents[1]
source = root/'cooked-ui/CockHero/Content'
evidence = json.loads((root/'ui-layout-values.json').read_text(encoding='utf-8'))
references = {p for imports in evidence['imports'].values() for p in imports.values()
              if p.startswith('/Game/') and '.' in p and ':' not in p}
modifier_path=root/'UnrealReconstruction/RecoveryEvidence/modifier-table-values.json'
if modifier_path.exists():
    modifier=json.loads(modifier_path.read_text(encoding='utf8'))
    references.update(p for p in modifier['imports'].values() if p.startswith('/Game/') and '.' in p and ':' not in p)
references=sorted(references)
def inspect(original):
    relative = original.split('.', 1)[0][len('/Game/'):]
    package = source/(relative+'.uasset')
    if original.rsplit('.', 1)[1] != Path(relative).name or not package.exists():
        return None
    if b'Texture2D' not in package.read_bytes():
        return None
    target = (root/'decoded-textures'/relative).with_suffix('.json')
    target.parent.mkdir(parents=True, exist_ok=True)
    if not target.exists():
        subprocess.run([str(root/'tools/uassetgui/UAssetGUI.exe'), 'tojson', str(package), str(target), 'VER_UE5_3'], capture_output=True, check=True)
    data = json.loads(target.read_text(encoding='utf-8'))
    for export in data.get('Exports', []):
        index = export.get('ClassIndex', 0)
        if index < 0 and data['Imports'][-index-1]['ObjectName'] == 'Texture2D':
            return original
    return None
with ThreadPoolExecutor(max_workers=4) as pool:
    textures = [p for p in pool.map(inspect, references) if p]
(root/'UnrealReconstruction/RecoveryEvidence/texture-catalog.json').write_text(json.dumps(textures, indent=2), encoding='utf-8')
print('Verified Texture2D packages:', len(textures))
