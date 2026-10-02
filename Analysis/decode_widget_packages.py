"""Convert recovered widget packages to raw JSON using the installed asset reader."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import subprocess,json
root=Path(__file__).parent
source=root/'cooked-ui'
reader=root/'tools/uassetgui/UAssetGUI.exe'
packages=[p for p in source.rglob('*.uasset') if b'WidgetTree' in p.read_bytes()]
def convert(path):
    target=(root/'decoded-ui'/path.relative_to(source)).with_suffix('.json');target.parent.mkdir(parents=True,exist_ok=True)
    result=subprocess.run([str(reader),'tojson',str(path),str(target),'VER_UE5_3'],cwd=root,capture_output=True,text=True)
    if not target.exists():return {'source':str(path.relative_to(source)),'error':result.stderr[-500:],'exit_code':result.returncode}
    data=json.loads(target.read_text(encoding='utf-8'))
    return {'source':str(path.relative_to(source)),'json':str(target.relative_to(root)),'exports':len(data.get('Exports',[])),'exit_code':result.returncode}
with ThreadPoolExecutor(max_workers=4) as pool:results=list(pool.map(convert,packages))
(root/'widget-package-decode-report.json').write_text(json.dumps({'packages':results,'original_game_executed':False},indent=2))
print('Converted',len(results),'widget packages; failures',sum('error' in r for r in results))
