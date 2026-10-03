"""Restore verified release files beside a clone; never execute the shipping binary."""
from pathlib import Path
import argparse,hashlib,json,shutil,subprocess,sys,zipfile

parser=argparse.ArgumentParser()
parser.add_argument('downloads',type=Path)
parser.add_argument('--destination',type=Path,default=Path(__file__).resolve().parents[2])
args=parser.parse_args()
repo=Path(__file__).resolve().parents[2]
destination=args.destination.resolve()
destination.mkdir(parents=True,exist_ok=True)
manifests=[repo/'Materials/materials-manifest.json',repo/'Materials/transfer-manifest.json']
for manifest in manifests:
    subprocess.run([sys.executable,str(repo/'Materials/Scripts/verify_downloads.py'),str(args.downloads),'--manifest',str(manifest)],check=True)
restored=0
for manifest in manifests:
    for asset in json.loads(manifest.read_text(encoding='utf-8-sig'))['assets']:
        prefix=Path()
        if asset['name'] in {'shipping-native-v004.zip','original-cooked-packages-v004.zip'}:prefix=Path('OriginalWindows')
        elif asset['name'] in {'completed-native-slice-v004.zip','complete-image-pdb-project-v004.zip'}:prefix=Path('Ghidra')
        with zipfile.ZipFile(args.downloads/asset['name']) as archive:
            for entry in asset['entries']:
                target=(destination/prefix/entry['path']).resolve()
                if not target.is_relative_to(destination):raise RuntimeError('Unsafe archive path')
                if target.exists():
                    with target.open('rb') as stream:existing=hashlib.file_digest(stream,'sha256').hexdigest()
                    if existing!=entry['sha256']:raise RuntimeError('Preserving changed existing file: '+str(target))
                    continue
                target.parent.mkdir(parents=True,exist_ok=True)
                with archive.open(entry['path']) as stream,target.open('xb') as output:shutil.copyfileobj(stream,output,8*1024*1024)
                restored+=1
print(f'Restored {restored} files into {destination}. No executable was run.')
