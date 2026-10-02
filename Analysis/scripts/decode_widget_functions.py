"""Decode all recovered UI function bodies without changing existing selected evidence."""
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
import json
import subprocess

root=Path(__file__).resolve().parents[1]
source=root/'cooked-ui'
selected=root/'decoded'
packages=[p for p in source.rglob('*.uasset') if b'WidgetTree' in p.read_bytes() and not (selected/(p.stem+'-functions.json')).exists()]
def decode(package):
    target=root/'decoded-widget-functions'/(package.stem+'-functions.json')
    target.parent.mkdir(parents=True,exist_ok=True)
    result=subprocess.run([str(root/'tools/uassetgui/UAssetGUI.exe'),'tojson',str(package),str(target),'VER_UE5_3','FunctionOnly'],cwd=root,capture_output=True,text=True)
    assert result.returncode==0 and target.exists(),(package,result.stderr)
    data=json.loads(target.read_text(encoding='utf-8'))
    exports=[e for e in data.get('Exports',[]) if 'FunctionExport' in e['$type']]
    fallbacks=[e['ObjectName'] for e in exports if e.get('ScriptBytecodeRaw')]
    assert not fallbacks,(package,fallbacks)
    return {'asset':package.stem,'functions':len(exports),'json':str(target),'raw_fallbacks':fallbacks}
with ThreadPoolExecutor(max_workers=4) as pool:
    rows=list(pool.map(decode,packages))
report={'original_game_executed':False,'assets':rows,'additional_functions':sum(r['functions'] for r in rows)}
(root/'widget-function-decode-report.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print('Additional UI assets:',len(rows),'functions:',report['additional_functions'])
