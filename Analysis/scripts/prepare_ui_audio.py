"""Restore Bink stream framing from recovered chunks, using UE5.3 seek-table layout."""
from pathlib import Path
import json
import struct
import hashlib

root=Path(__file__).resolve().parents[1]
project=root/'UnrealReconstruction'
source=root/'cooked-ui-audio/CockHero/Content'
output=project/'RecoveryEvidence/AudioEncoded';output.mkdir(parents=True,exist_ok=True)
rows=[]
for package in sorted(source.rglob('*.uexp')):
    if package.stem not in {'click1_sfx','click2_sfx','click3_sfx','click4_sfx','click5_sfx','mouseclick1_sfx','Juice_SFX__12_'}:continue
    data=package.read_bytes(); header_offset=data.find(b'ABEU')
    assert header_offset>=0 and data.find(b'ABEU',header_offset+1)<0
    header=data[header_offset:header_offset+28]
    fields=struct.unpack('<IBBHIIHHIHH',header)
    assert fields[1]==1 and fields[-2]==0 # Version 1, original seek table removed by stream cook.
    bulk=package.with_suffix('.ubulk').read_bytes()
    assert bulk[:5]==b'SEEK\x00' # Constant-rate chunk seek table.
    count=struct.unpack_from('<i',bulk,11)[0]
    assert 0<count<100000
    skip=15+2*count
    assert bulk[skip:skip+2]==b'\x99\x99'
    encoded=header+bulk[skip:]
    # Cook preserves original output_file_size, including now-removed uint16 seek entries.
    assert fields[8]==len(encoded)+2*count
    destination=output/(package.stem+'.binka')
    destination.write_bytes(encoded)
    rows.append({'original':'/Game/'+package.relative_to(source).with_suffix('').as_posix()+'.'+package.stem,'name':package.stem,
                 'encoded':str(destination),'sample_rate':fields[4],'channels':fields[2],'frames':fields[5],
                 'source_uexp_sha256':hashlib.sha256(data).hexdigest(),'source_bulk_sha256':hashlib.sha256(bulk).hexdigest(),
                 'encoded_sha256':hashlib.sha256(encoded).hexdigest(),'source_executed':False})
(project/'RecoveryEvidence/audio-stream-catalog.json').write_text(json.dumps(rows,indent=2),encoding='utf-8')
print('Reconstructed Bink streams:',len(rows))
