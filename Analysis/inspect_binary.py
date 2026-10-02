import pathlib, re, json, hashlib
root = pathlib.Path(r'C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows')
out = pathlib.Path(__file__).parent
pattern = re.compile(r'chpack|manifest\.json|FileImportManager|PackManager|ContentPack|ImportPack|ExtractPack|LoadPack|MediaTag|7za|/api/|localhost|127\.0\.0\.1|unlock_cost|required_challenge|patreon_exclusive|social_links|GameContent|CustomMedia', re.I)
files = [root/'CockHero.exe', root/'CockHero/Binaries/Win64/CockHero.exe', root/'CockHero/Binaries/Win64/CockHero.pdb']
meta=[]
for p in files:
    data=p.read_bytes()
    meta.append({'path':str(p),'size':len(data),'sha256':hashlib.sha256(data).hexdigest()})
    hits=[]
    for enc, regex in [('ascii',rb'[\x20-\x7e]{5,}'), ('utf16',rb'(?:[\x20-\x7e]\x00){5,}')]:
        for m in re.finditer(regex,data):
            s=m.group().decode('ascii' if enc=='ascii' else 'utf-16le')
            if pattern.search(s): hits.append({'offset':hex(m.start()),'encoding':enc,'text':s[:1500]})
    label='pdb' if p.suffix=='.pdb' else ('launcher' if p.parent==root else 'game')
    (out/(label+'-strings.json')).write_text(json.dumps(hits,indent=2),encoding='utf-8')
    print(label, 'size',len(data),'matched strings',len(hits))
(out/'binary-metadata.json').write_text(json.dumps(meta,indent=2),encoding='utf-8')
