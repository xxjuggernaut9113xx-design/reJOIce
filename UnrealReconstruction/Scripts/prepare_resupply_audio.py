from pathlib import Path
import hashlib
import json
import struct

project=Path(__file__).resolve().parents[1]
source=Path(r'C:\Users\webma\analysis\cockhero-v004\cooked-animation-audio\CockHero\Content\SoundFX\872025\new-notification-020-352772.uexp')
bulk=source.with_suffix('.ubulk')
package=source.read_bytes()
payload=bulk.read_bytes()
header_offset=package.find(b'ABEU')
if header_offset<0:
    raise RuntimeError('Bink audio header was not found in new-notification-020-352772')
header=package[header_offset:header_offset+28]
fields=struct.unpack('<IBBHIIHHIHH',header)
if fields[1]!=1 or fields[-2]!=0:
    raise RuntimeError('Unexpected Bink audio header layout')
starts=[]
cursor=0
while True:
    cursor=payload.find(b'SEEK',cursor)
    if cursor<0:
        break
    starts.append(cursor)
    cursor+=4
if not starts or starts[0]!=0:
    raise RuntimeError('Bink stream chunks were not found at the source offset')
chunks=[]
seek_table_bytes=0
for index,start in enumerate(starts):
    if payload[start+4]!=0:
        raise RuntimeError('Unexpected Bink stream chunk flags')
    seek_count=struct.unpack_from('<i',payload,start+11)[0]
    if not 0<seek_count<100000:
        raise RuntimeError('Unexpected Bink seek-table count')
    content_start=start+15+2*seek_count
    end=starts[index+1] if index+1<len(starts) else len(payload)
    if content_start>=end or payload[content_start:content_start+2]!=b'\x99\x99':
        raise RuntimeError('Unexpected Bink stream packet boundary')
    chunks.append(payload[content_start:end])
    seek_table_bytes+=2*seek_count
encoded=header+b''.join(chunks)
if fields[8]!=len(encoded)+seek_table_bytes:
    raise RuntimeError('Bink audio reconstruction length mismatch')
encoded_path=project/'RecoveryEvidence'/'AudioEncoded'/'new-notification-020-352772.binka'
encoded_path.parent.mkdir(parents=True,exist_ok=True)
encoded_path.write_bytes(encoded)
report={
    'original':'/Game/SoundFX/872025/new-notification-020-352772.new-notification-020-352772',
    'name':'new-notification-020-352772',
    'source_package':str(source),
    'source_package_sha256':hashlib.sha256(package).hexdigest(),
    'source_bulk_sha256':hashlib.sha256(payload).hexdigest(),
    'encoded':str(encoded_path),
    'encoded_sha256':hashlib.sha256(encoded).hexdigest(),
    'sample_rate':fields[4],
    'channels':fields[2],
    'frames':fields[5],
    'stream_chunks':len(starts),
}
(project/'RecoveryEvidence'/'resupply-audio-recovery.json').write_text(json.dumps(report,indent=2),encoding='utf-8')
print(json.dumps(report,indent=2))
