"""Export referenced textures from isolated recovered packages, never the shipping executable."""
from pathlib import Path
import hashlib
import json
import unreal

project = Path(unreal.Paths.project_dir())
root = project.parent
evidence = json.loads((root/'ui-layout-values.json').read_text(encoding='utf-8'))
source = root/'cooked-ui/CockHero/Content'
references = json.loads((project/'RecoveryEvidence/texture-catalog.json').read_text(encoding='utf-8'))
results = []
previous_file=project/'Saved/texture-export-report.json'
previous={row['original']:row for row in json.loads(previous_file.read_text(encoding='utf-8'))} if previous_file.exists() else {}
for original in references:
    relative = original.split('.', 1)[0][len('/Game/'):]
    package = source/(relative+'.uasset')
    if not package.exists() or b'Texture2D' not in package.read_bytes():
        continue
    # Widget packages import textures too; only packages with a matching exported name qualify.
    if original.rsplit('.', 1)[1] != Path(relative).name:
        continue
    digest=hashlib.sha256(package.read_bytes()).hexdigest()
    cached=previous.get(original)
    if cached and cached['success'] and cached['source_package_sha256']==digest and Path(cached['file']).exists() and hashlib.sha256(Path(cached['file']).read_bytes()).hexdigest()==cached['mip_sha256']:
        results.append(cached)
        continue
    result = json.loads(unreal.RecoveredTextureRecovery.export_cooked_mip(str(source), relative))
    result['original'] = original
    result['source_package_sha256'] = digest
    if result['success']:
        raw = Path(result['file'])
        unique = raw.parent/(hashlib.sha256(original.encode()).hexdigest()[:16]+'.bin')
        raw.replace(unique)
        result['file'] = str(unique)
        result['mip_sha256'] = hashlib.sha256(unique.read_bytes()).hexdigest()
    results.append(result)
    unreal.log('TEXTURE_RECOVERY '+original+' '+str(result['success']))
output = project/'Saved/texture-export-report.json'
output.write_text(json.dumps(results, indent=2), encoding='utf-8')
unreal.log('TEXTURE_RECOVERY_EXPORTED '+str(sum(r['success'] for r in results)))
