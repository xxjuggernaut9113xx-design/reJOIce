import pathlib,json,base64,hashlib
from decode_defaults import Reader,Writer,schemas
base=pathlib.Path(__file__).parent
schemas['UserDefinedEnum']=[{'name':'DisplayNameMap','type':'MapProperty','key':{'type':'NameProperty'},'value':{'type':'TextProperty'}}]
results=[];failures=[]
for path in sorted((base/'decoded').glob('*-functions.json')):
 a=json.loads(path.read_text(encoding='utf8'))
 for e in a['Exports']:
  if e['ClassIndex']>=0 or a['Imports'][-e['ClassIndex']-1]['ObjectName']!='UserDefinedEnum':continue
  r=Reader(base64.b64decode(e['Data']),a)
  try:
   props=r.properties('UserDefinedEnum');assert r.num('I')==0
   count=r.num('i');assert 0<=count<10000
   entries=[{'name':r.name(),'value':r.num('q')} for _ in range(count)]
   cppform=r.num('B');assert r.pos==len(r.data),(r.pos,len(r.data))
   display={k:v['text'] for k,v in props['DisplayNameMap']['entries']}
   for entry in entries:entry['display']=display.get(entry['name'].split('::')[-1])
   w=Writer(r);w.properties('UserDefinedEnum',props);w.num('I',0);w.num('i',count)
   for entry in entries:w.name(entry['name']);w.num('q',entry['value'])
   w.num('B',cppform);assert w.data==r.data
   results.append({'enum':e['ObjectName'],'entries':entries,'bytes':len(r.data),'roundtrip_identical':True,'sha256':hashlib.sha256(r.data).hexdigest()})
  except Exception as ex:failures.append({'enum':e['ObjectName'],'offset':r.pos,'error':repr(ex)})
(base/'blueprint-enums.json').write_text(json.dumps({'enums':results,'failures':failures},indent=2),encoding='utf8')
print('Enums',len(results),'failures',failures)
print(next((e for e in results if e['enum']=='DifficultySelections_ENUM'),None))
