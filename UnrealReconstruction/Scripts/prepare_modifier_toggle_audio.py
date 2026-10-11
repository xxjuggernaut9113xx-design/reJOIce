from pathlib import Path
import hashlib,json,struct

PROJECT=Path(__file__).resolve().parents[1]
SOURCE_ROOT=Path(r'C:\Users\webma\analysis\cockhero-v004\cooked-animation-audio\CockHero\Content\SoundFX\Toggles')
SOUNDS=[('ontoggle2','/Game/SoundFX/Toggles/ontoggle2.ontoggle2'),('offtoggle','/Game/SoundFX/Toggles/offtoggle.offtoggle')]
rows=[]
for name,original in SOUNDS:
    package_path=SOURCE_ROOT/(name+'.uexp'); bulk_path=SOURCE_ROOT/(name+'.ubulk')
    package=package_path.read_bytes(); bulk=bulk_path.read_bytes(); start=package.find(b'ABEU')
    if start<0: raise RuntimeError(f'{name}: Bink header not found')
    header=package[start:start+28]; fields=struct.unpack('<IBBHIIHHIHH',header)
    offsets=[]; cursor=0
    while True:
        cursor=bulk.find(b'SEEK',cursor)
        if cursor<0: break
        offsets.append(cursor); cursor+=4
    if not offsets or offsets[0]!=0: raise RuntimeError(f'{name}: invalid stream chunks')
    chunks=[]; seek_bytes=0
    for index,offset in enumerate(offsets):
        if bulk[offset+4]!=0: raise RuntimeError(f'{name}: invalid stream flags')
        count=struct.unpack_from('<i',bulk,offset+11)[0]
        content=offset+15+2*count; end=offsets[index+1] if index+1<len(offsets) else len(bulk)
        if content>=end or bulk[content:content+2]!=b'\x99\x99': raise RuntimeError(f'{name}: invalid packet')
        chunks.append(bulk[content:end]); seek_bytes+=2*count
    encoded=header+b''.join(chunks)
    if fields[8]!=len(encoded)+seek_bytes: raise RuntimeError(f'{name}: length mismatch')
    target=PROJECT/'RecoveryEvidence'/'AudioEncoded'/(name+'.binka'); target.parent.mkdir(parents=True,exist_ok=True); target.write_bytes(encoded)
    rows.append({'original':original,'name':name,'source_package':str(package_path),'source_package_sha256':hashlib.sha256(package).hexdigest(),'source_bulk_sha256':hashlib.sha256(bulk).hexdigest(),'encoded':str(target),'encoded_sha256':hashlib.sha256(encoded).hexdigest(),'sample_rate':fields[4],'channels':fields[2],'frames':fields[5],'stream_chunks':len(offsets),'source_executed':False})
report={'recovery':'modifier-toggle-audio','sounds':rows}
(PROJECT/'RecoveryEvidence'/'modifier-toggle-audio-recovery.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report,indent=2))
