"""Cache ordered native reflection fields and inheritance from the original PDB/PE."""
from pathlib import Path
import hashlib
import json
import re

root=Path(__file__).resolve().parents[1]
namespace={'__file__':str(root/'recover_native_schemas.py')}
exec((root/'recover_native_schemas.py').read_text(encoding='utf8').split('schemas={}')[0],namespace)
public,pe,off,q,string,byva,struct=(namespace[k] for k in ('public','pe','off','q','string','byva','struct'))
schemas={};pointers={};supers={};inheritance=[];skipped=[];unsupported=set()
for name,va in public.items():
    match=re.match(r'\?PropPointers@Z_Construct_U(?:ScriptStruct_F|Class_[UA])([^@]+)_Statics@@',name)
    if match:pointers[match[1]]=va
    match=re.match(r'\?DependentSingletons@Z_Construct_UClass_[UA]([^@]+)_Statics@@',name)
    if match:
        owner=match[1];target=q(va);dependency=byva.get(target,'')
        parent=re.search(r'Z_Construct_UClass_[UA]([^@]+)',dependency)
        supers[owner]=parent[1] if parent else None
        inheritance.append({'owner':owner,'symbol':name,'address':hex(va),'dependency_address':hex(target),'dependency':dependency,'parent':supers[owner]})
    match=re.match(r'\?ReturnStructParams@Z_Construct_UScriptStruct_F([^@]+)_Statics@@',name)
    if match:
        owner=match[1];target=q(va+8);dependency=byva.get(target,'')
        parent=re.search(r'Z_Construct_UScriptStruct_F([^@]+)',dependency)
        supers[owner]=parent[1] if parent else None
        inheritance.append({'owner':owner,'symbol':name,'address':hex(va),'dependency_address':hex(target),'dependency':dependency,'parent':supers[owner]})
    match=re.match(r'\?NewProp_(.+)@Z_Construct_U(?:ScriptStruct_F|Class_[UA])([^@]+)_Statics@@',name)
    if not match:continue
    if match[1].endswith('_SetBit'):continue # Setter code symbols are not property descriptors.
    _,owner=match.groups();position=off(va)
    kind=pe[position+24]&63
    flags=struct.unpack_from('<Q',pe,position+16)[0]
    dimension,member_offset=struct.unpack_from('<HH',pe,position+48)
    extra=struct.unpack_from('<Q',pe,position+56)[0] if kind in (0,25,30) else None
    try:propname=string(q(va))
    except (StopIteration,UnicodeDecodeError) as error:
        skipped.append({'owner':owner,'symbol':name,'address':hex(va),'error':type(error).__name__});unsupported.add(owner);continue
    schemas.setdefault(owner,[]).append({'symbol':name,'address':hex(va),'name':propname,'kind':kind,'flags':hex(flags),'dim':dimension,'offset':member_offset,'extra_symbol':byva.get(extra),'extra_address':hex(extra) if extra else None})
for owner in unsupported:schemas.pop(owner,None)
for owner,fields in schemas.items():
    assert owner in pointers,owner
    addresses={int(field['address'],16):field for field in fields}
    ordered=[]
    for index in range(len(fields)):
        address=q(pointers[owner]+8*index)
        assert address in addresses,(owner,index,hex(address))
        ordered.append(addresses[address])
    assert len({field['address'] for field in ordered})==len(fields),owner
    schemas[owner]=ordered
for owner in supers:
    if owner not in unsupported:schemas.setdefault(owner,[])
report={'original_executed':False,'source_exe_sha256':hashlib.sha256(pe).hexdigest(),'schemas':schemas,'supers':supers,'inheritance_evidence':inheritance,'unsupported_owners':sorted(unsupported),'skipped_metadata':skipped}
(root/'native-reflection-catalog.json').write_text(json.dumps(report,indent=2),encoding='utf8')
print('Cached native schemas',len(schemas),'fields',sum(len(v) for v in schemas.values()),'inheritance records',len(inheritance))
print('Material parent:',supers.get('Material'),'interface parent:',supers.get('MaterialInterface'))
