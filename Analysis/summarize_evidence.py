import pathlib,re,json,struct,collections
base=pathlib.Path(__file__).parent
pe=pathlib.Path(r'C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero\Binaries\Win64\CockHero.exe').read_bytes()
sections=json.loads((base/'pe-sections.json').read_text())
def read_va(va,n=400):
    rva=va-0x140000000
    for s in sections:
        if s['rva']<=rva<s['rva']+s['rawsize']:
            at=s['raw']+rva-s['rva']; return pe[at:at+n]
    return b''
def literal(va):
    b=read_va(va)
    if len(b)<4: return None
    if b[1]==0:
        end=0
        while end+1<len(b) and b[end:end+2]!=b'\0\0': end+=2
        try: s=b[:end].decode('utf-16le')
        except UnicodeDecodeError: return None
    else:
        try: s=b.split(b'\0')[0].decode('ascii')
        except UnicodeDecodeError: return None
    return s if len(s)>=3 and all(c.isprintable() or c in '\r\n\t' for c in s) else None
code=(base/'ghidra-native/integration-decompiled.c').read_text(encoding='utf-8')
blocks=re.split(r'(?=^/\* [0-9a-f]+ \?)',code,flags=re.M)
want=re.compile(r'\?(ParseManifestJson|ExtractChpackToFolder|GetPackExtractionPath|LoadManifestFromChpack|ValidateMediaEntries|FilterMediaIntoCategoriesAsync|CalculateSessionXP|PrepareSessionRewards|RecordSessionMetric|UpdateBeatInterval|UpdateSpeedItemMultiplier|StartPatternWithMediaSync|GetAllEnabledMedia|UnlockPack|IsPackLocked|AddFiles|GetImportedMediaEntries|UpdateHeat|SetBeatPattern|GetCompensatedBeatTime|GetProfileTotalLatency)@')
results=[]
for b in blocks:
    if not want.search(b[:500]):continue
    head=b.splitlines()[0]
    literals={}
    for addr in set(re.findall(r'(?:UNK|DAT)_([0-9a-f]{9,16})',b)):
        s=literal(int(addr,16))
        if s: literals[addr]=s
    results.append({'function':head,'lines':len(b.splitlines()),'referenced_strings':literals,'inline_strings':re.findall(r'"([^"\n]+)"',b)[:60]})
    name=want.search(b[:500]).group(1)
    (base/(name+'.c')).write_text(b+'\n/* Resolved referenced strings:\n'+json.dumps(literals,indent=2)+'\n*/\n',encoding='utf-8')
(base/'native-function-evidence.json').write_text(json.dumps(results,indent=2),encoding='utf-8')
symbols=json.loads((base/'native-symbol-addresses.json').read_text())
counts=collections.Counter(re.search(r'@([^@]+)@@',x['name']).group(1) for x in symbols if re.search(r'@([^@]+)@@',x['name']))
print(json.dumps(counts,indent=2)); print('targeted evidence functions',len(results))
for va in [0x14bcfdb1c,0x14bcfdb5c,0x14bd4dc7c]: print(hex(va),struct.unpack('<f',read_va(va,4))[0])
