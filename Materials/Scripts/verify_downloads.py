"""Verify private release archives and entries without executing binaries."""
from pathlib import Path
import argparse,hashlib,json,zipfile
p=argparse.ArgumentParser()
p.add_argument('directory',type=Path)
p.add_argument('--manifest',type=Path,default=Path(__file__).resolve().parents[1]/'materials-manifest.json')
p.add_argument('--report',type=Path)
a=p.parse_args()
manifest=json.loads(a.manifest.read_text(encoding='utf-8-sig'))
def digest(stream):
    h=hashlib.sha256()
    for chunk in iter(lambda:stream.read(8*1024*1024),b''):h.update(chunk)
    return h.hexdigest()
verified=[]
for asset in manifest['assets']:
    path=a.directory/asset['name']
    assert path.stat().st_size==asset['size'],f'Size mismatch: {path}'
    with path.open('rb') as stream:assert digest(stream)==asset['sha256'],f'Hash mismatch: {path}'
    with zipfile.ZipFile(path) as archive:
        assert set(archive.namelist())=={e['path'] for e in asset['entries']}
        for entry in asset['entries']:
            assert archive.getinfo(entry['path']).file_size==entry['size']
            with archive.open(entry['path']) as stream:assert digest(stream)==entry['sha256'],f'Entry mismatch: {entry["path"]}'
    verified.append({'name':asset['name'],'sha256':asset['sha256'],'entries_verified':len(asset['entries'])})
report={'all_archives_and_entries_match':True,'verified':verified,'shipping_executable_executed':False}
if a.report:a.report.write_text(json.dumps(report,indent=2),encoding='utf8')
print(json.dumps(report,indent=2))
