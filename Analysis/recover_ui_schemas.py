"""Read original PDB/PE UMG reflection metadata for cooked widget decoding."""
from pathlib import Path
import re,json
root=Path(__file__).parent
ns={'__file__':str(root/'recover_native_schemas.py')}
exec((root/'recover_native_schemas.py').read_text().split('schemas={}')[0],ns)
public,pe,off,q,string=tuple(ns[k] for k in ['public','pe','off','q','string'])
byva=ns['byva']
headers=Path(r'D:\Program Files\Epic Games\UE_5.3\Engine\Source\Runtime\UMG\Public')
supers={}
for path in headers.rglob('*.h'):
    text=path.read_text(encoding='utf-8',errors='replace')
    for cls,parent in re.findall(r'class\s+(?:UMG_API\s+)?U(\w+)\s*:\s*public\s+U(\w+)',text):supers[cls]=parent
supers.update(UserWidget='Widget',Widget='Visual',PanelSlot='Visual',Visual=None)
wanted={'WidgetTree','UserWidget','Widget','Visual','PanelSlot','PanelWidget','ContentWidget','SlateWidgetStyle','SlateBrush','SlateColor','SlateFontInfo','Margin','AnchorData','Anchors','WidgetTransform','ButtonStyle','TextBlockStyle','ProgressBarStyle','SliderStyle'}
for asset_path in list((root/'decoded').glob('*-functions.json'))+list((root/'decoded-ui').rglob('*.json')):
    asset=json.loads(asset_path.read_text(encoding='utf-8'))
    if not any(i['ObjectName']=='WidgetTree' for i in asset.get('Imports',[])):continue
    for export in asset['Exports']:
        if export['ClassIndex']<0:
            cls=asset['Imports'][-export['ClassIndex']-1]['ObjectName']
            if cls in supers:wanted.add(cls)
allprops={}
for name,va in public.items():
    match=re.search(r'NewProp_(.+)@Z_Construct_U(?:ScriptStruct_F|Class_[UA])([^@]+)_Statics@@',name)
    if not match or not name.startswith('?NewProp_'):continue
    _,owner=match.groups();a=off(va)
    kind=pe[a+24]&63
    flags=ns['struct'].unpack_from('<Q',pe,a+16)[0]
    dim,offset=ns['struct'].unpack_from('<HH',pe,a+48)
    extra=ns['struct'].unpack_from('<Q',pe,a+56)[0] if kind in (0,25,30) else None
    try:propname=string(q(va))
    except (StopIteration,UnicodeDecodeError):continue
    allprops.setdefault(owner,[]).append({'symbol':name,'address':hex(va),'name':propname,'kind':kind,'flags':hex(flags),'dim':dim,'offset':offset,'extra_symbol':byva.get(extra),'extra_address':hex(extra) if extra else None})
while True:
    old=set(wanted)
    for owner in old:
        if supers.get(owner):wanted.add(supers[owner])
        for prop in allprops.get(owner,[]):
            match=re.search(r'Z_Construct_UScriptStruct_F([^@]+)',prop['extra_symbol'] or '')
            if match:wanted.add(match[1])
    if wanted==old:break
selected={owner:props for owner,props in allprops.items() if owner in wanted}
for owner,props in selected.items():
    pointer_symbol=next((k for k in public if any(k.startswith('?PropPointers@Z_Construct_U'+prefix+owner+'_Statics@@') for prefix in ('ScriptStruct_F','Class_U','Class_A'))),None)
    if pointer_symbol:
        addresses={int(p['address'],16):p for p in props};ptr=public[pointer_symbol];ordered=[]
        for index in range(len(props)):
            value=q(ptr+8*index)
            if value not in addresses:break
            ordered.append(addresses[value])
        assert len(ordered)==len(props),owner
        selected[owner]=ordered
result={'schemas':selected,'supers':{owner:supers.get(owner) for owner in wanted},'missing_metadata':sorted(wanted-set(selected)-{'Visual','SlateWidgetStyle'})}
(root/'ui-reflection-schemas.json').write_text(json.dumps(result,indent=2))
print('Recovered',len(selected),'UI schemas; missing metadata:',result['missing_metadata'])
