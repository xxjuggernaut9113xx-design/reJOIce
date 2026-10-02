import pathlib,re,json
root=pathlib.Path(r'C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero')
out=pathlib.Path(__file__).parent
exe=(root/'Binaries/Win64/CockHero.exe').read_bytes()
names=[]
for m in re.finditer(rb'[\x20-\x7e]{4,}',exe):
    if 0xcf34000 <= m.start() <= 0xcf80000:
        names.append({'offset':hex(m.start()),'text':m.group().decode('ascii')})
(out/'game-reflection.json').write_text(json.dumps(names,indent=2),encoding='utf-8')
assets=[]
for p in list((root/'Content/Paks').glob('*.utoc'))+list((root/'Saved/SaveGames').glob('*.sav')):
    data=p.read_bytes()
    ss=[m.group().decode('ascii') for m in re.finditer(rb'[\x20-\x7e]{4,}',data)]
    assets.append({'path':str(p),'size':len(data),'strings':ss})
(out/'asset-save-inventory.json').write_text(json.dumps(assets,indent=2),encoding='utf-8')
pdb=(root/'Binaries/Win64/CockHero.pdb').read_bytes()
paths=sorted(set(m.group().decode('ascii') for m in re.finditer(rb'[\x20-\x7e]{8,}',pdb) if b'CockHero' in m.group() and (b'.cpp' in m.group() or b'.h' in m.group()) and b'Engine' not in m.group()))
(out/'project-source-symbols.txt').write_text('\n'.join(paths),encoding='utf-8')
print('reflection strings',len(names),'asset/save files',len(assets),'project source paths',len(paths))
