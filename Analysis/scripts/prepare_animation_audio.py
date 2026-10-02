from pathlib import Path
import json,struct,hashlib
r=Path(__file__).resolve().parents[1];p=r/'UnrealReconstruction'
refs=json.loads((p/'RecoveryEvidence/animation-sound-references.json').read_text());rows=[]
for ref in refs:
    if not ref.startswith('/Game/'): continue
    package=r/'cooked-animation-audio'/('CockHero/Content/'+ref.split('.')[0][6:]+'.uexp')
    data=package.read_bytes();i=data.find(b'ABEU');assert i>=0,ref
    header=data[i:i+28];fields=struct.unpack('<IBBHIIHHIHH',header);assert fields[1]==1 and fields[-2]==0,ref
    bulk=package.with_suffix('.ubulk').read_bytes();starts=[];cursor=0
    while True:
        cursor=bulk.find(b'SEEK',cursor)
        if cursor<0: break
        starts.append(cursor);cursor+=4
    assert starts and starts[0]==0,ref
    chunks=[];count_total=0
    for j,start in enumerate(starts):
        assert bulk[start+4]==0,ref
        count=struct.unpack_from('<i',bulk,start+11)[0];assert 0<count<100000,ref
        skip=15+2*count;end=starts[j+1] if j+1<len(starts) else len(bulk)
        assert start+skip<end and bulk[start+skip:start+skip+2]==b'\x99\x99',ref
        chunks.append(bulk[start+skip:end]);count_total+=count
    encoded=header+b''.join(chunks)
    assert fields[8]==len(encoded)+2*count_total,ref
    out=p/'RecoveryEvidence/AudioEncoded'/(package.stem+'.binka');out.write_bytes(encoded)
    rows.append(dict(original=ref,name=package.stem,encoded=str(out),sample_rate=fields[4],channels=fields[2],frames=fields[5],stream_chunks=len(starts),encoded_sha256=hashlib.sha256(encoded).hexdigest()))
(p/'RecoveryEvidence/animation-audio-stream-catalog.json').write_text(json.dumps(rows,indent=2))
print('Prepared',len(rows),'animation sound streams')
