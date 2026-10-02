import pathlib,json,hashlib,base64,struct
base=pathlib.Path(__file__).parent
records={};checks=[]
for p in sorted((base/'decoded').glob('*-progression.json')):
 a=json.loads(p.read_text(encoding='utf8'));e=a['Exports'][0]
 def ref(i):
  if i==0:return None
  pool=a['Exports'] if i>0 else a['Imports'];n=pool[i-1 if i>0 else -i-1]
  outer=n.get('OuterIndex',0)
  return (ref(outer)+'.' if outer else '')+n['ObjectName']
 def value(prop):
  kind=prop.get('$type','')
  v=prop.get('Value')
  if 'TextPropertyData' in kind:return prop.get('CultureInvariantString')
  if 'ObjectPropertyData' in kind:return ref(v)
  if 'StructPropertyData' in kind:
   if len(v)==1 and 'LinearColorPropertyData' in v[0].get('$type',''):return {k:x for k,x in v[0]['Value'].items() if k!='$type'}
   return {x['Name']:value(x) for x in v}
  if 'ArrayPropertyData' in kind:return [value(x) for x in v]
  return v
 rows=[{'row':r['Name'],**value(r)} for r in e['Table']['Data']]
 records[e['ObjectName']]=rows
 for ext in ('.uasset','.uexp'):
  original=base/'cooked-gameplay/CockHero/Content/Data/Progression'/(e['ObjectName']+ext)
  rebuilt=base/'roundtrip'/(e['ObjectName']+ext)
  old=hashlib.sha256(original.read_bytes()).hexdigest();new=hashlib.sha256(rebuilt.read_bytes()).hexdigest()
  left=original.read_bytes();right=rebuilt.read_bytes();namehash_only=False
  if ext=='.uasset':
   first=a['NameMap'][0].encode('utf8')+b'\0'
   pos=left.index(struct.pack('<i',len(first))+first);namehash_positions=set()
   for name in a['NameMap']:
    length=struct.unpack_from('<i',left,pos)[0]
    pos+=4+(length if length>=0 else -2*length)
    namehash_positions.update(range(pos,pos+4));pos+=4
   diffs={i for i,(x,y) in enumerate(zip(left,right)) if x!=y}
   namehash_only=len(left)==len(right) and not (diffs-namehash_positions)
  checks.append({'file':original.name,'original_sha256':old,'roundtrip_sha256':new,'identical':old==new,'differences_only_name_hashes':namehash_only,'payload_verified':old==new or namehash_only})
 assert not base64.b64decode(e.get('Extras') or ''),p
(base/'progression-tables.json').write_text(json.dumps(records,indent=2,ensure_ascii=False),encoding='utf8')
(base/'progression-roundtrip-check.json').write_text(json.dumps(checks,indent=2),encoding='utf8')
print('Rows',{k:len(v) for k,v in records.items()})
print('Roundtrip files',len(checks),'identical',sum(c['identical'] for c in checks))
print('Payload verified',sum(c['payload_verified'] for c in checks))
print('Level XP',[r['XPRequired'] for r in records['DT_LevelData']])
