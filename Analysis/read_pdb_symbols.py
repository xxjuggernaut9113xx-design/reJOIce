import pathlib,struct,json,re
base=pathlib.Path(__file__).parent
game=pathlib.Path(r'C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero\Binaries\Win64')
data=(game/'CockHero.pdb').read_bytes()
u32=lambda b,o: struct.unpack_from('<I',b,o)[0]
block,_,_,directory_size,_,blockmap=struct.unpack_from('<6I',data,32)
nblocks=(directory_size+block-1)//block
blocks=struct.unpack_from('<'+'I'*nblocks,data,blockmap*block)
directory=b''.join(data[i*block:(i+1)*block] for i in blocks)[:directory_size]
n=u32(directory,0); sizes=struct.unpack_from('<'+'I'*n,directory,4); pos=4+4*n; streams=[]
for size in sizes:
    count=0 if size==0xffffffff else (size+block-1)//block
    ids=struct.unpack_from('<'+'I'*count,directory,pos) if count else []
    pos+=4*count
    streams.append((size,ids))
def stream(i):
    size,ids=streams[i]
    return b''.join(data[x*block:(x+1)*block] for x in ids)[:size]
dbi=stream(3); sym_index=struct.unpack_from('<H',dbi,20)[0]; symbols=stream(sym_index)
pe=(game/'CockHero.exe').read_bytes(); peoff=u32(pe,0x3c); count=struct.unpack_from('<H',pe,peoff+6)[0]; opts=struct.unpack_from('<H',pe,peoff+20)[0]; optional=peoff+24
imagebase=struct.unpack_from('<Q',pe,optional+24)[0]; sections=[]
for i in range(count):
    at=optional+opts+40*i
    sections.append({'name':pe[at:at+8].rstrip(b'\0').decode(),'vsize':u32(pe,at+8),'rva':u32(pe,at+12),'rawsize':u32(pe,at+16),'raw':u32(pe,at+20)})
target=re.compile(r'@(?:U)?(?:CHPackManager|FileImportManager|CHPackStoreController|MediaPlaybackController|ProgressionManager|PreciseBeatWidget|BeatSpawnerManager|LatencyCompensationManager|HandyManager|AdultToyManager|FFmpegManager)@@')
hits=[]; at=0
while at+4<=len(symbols):
    length,kind=struct.unpack_from('<HH',symbols,at)
    if length<2 or at+length+2>len(symbols): break
    rec=symbols[at:at+length+2]
    if kind==0x110e and len(rec)>=15:
        flags,offset,segment=struct.unpack_from('<IIH',rec,4)
        name=rec[14:].split(b'\0')[0].decode('utf-8',errors='replace')
        if flags&2 and target.search(name) and 0<segment<=len(sections):
            sec=sections[segment-1]; va=imagebase+sec['rva']+offset
            hits.append({'address':hex(va),'name':name,'file_offset':sec['raw']+offset,'section':sec['name']})
    at+=length+2
hits.sort(key=lambda x:int(x['address'],16))
(base/'native-symbol-addresses.json').write_text(json.dumps(hits,indent=2),encoding='utf-8')
(base/'native-symbol-addresses.tsv').write_text('\n'.join(x['address']+'\t'+x['name'] for x in hits),encoding='utf-8')
(base/'pe-sections.json').write_text(json.dumps(sections,indent=2),encoding='utf-8')
print('PDB public symbol stream',sym_index,'target functions',len(hits))
print('addresses',hits[0]['address'] if hits else None,hits[-1]['address'] if hits else None)
start=min(x['file_offset'] for x in hits)//4096*4096
end=(max(x['file_offset'] for x in hits)+65536+4095)//4096*4096
sec=next(s for s in sections if s['name']=='.text')
(base/'native-slice.bin').write_bytes(pe[start:end])
slice_va=imagebase+sec['rva']+(start-sec['raw'])
(base/'native-slice-address.txt').write_text(hex(slice_va),encoding='utf-8')
print('native slice',hex(slice_va),end-start,'bytes')
info=stream(1)
debug_rva=u32(pe,optional+112+6*8); debug_size=u32(pe,optional+112+6*8+4)
debug_sec=next(s for s in sections if s['rva']<=debug_rva<s['rva']+s['rawsize'])
debug_at=debug_sec['raw']+debug_rva-debug_sec['rva']; rsds=-1
for off in range(debug_at,debug_at+debug_size,28):
    if u32(pe,off+12)==2:
        ptr=u32(pe,off+24)
        if pe[ptr:ptr+4]==b'RSDS': rsds=ptr; break
match=rsds>=0 and pe[rsds+4:rsds+20]==info[12:28] and u32(pe,rsds+20)==u32(info,8)
(base/'pdb-match.json').write_text(json.dumps({'pdb_age':u32(info,8),'pdb_guid_bytes':info[12:28].hex(),'pe_codeview_offset':hex(rsds),'guid_and_age_match':match},indent=2),encoding='utf-8')
print('PDB GUID and age match:',match)
rd=next(s for s in sections if s['name']=='.rdata')
(base/'native-rdata.bin').write_bytes(pe[rd['raw']:rd['raw']+rd['rawsize']])
(base/'native-rdata-address.txt').write_text(hex(imagebase+rd['rva']),encoding='utf-8')
