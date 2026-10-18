"""Normalize independently round-tripped table values for reconstruction consumers."""
from pathlib import Path
import json,re
root=Path(__file__).resolve().parents[1];dest=root/'ReferenceBuilds/newer-20261017'
source=json.loads((dest/'table-values.json').read_text(encoding='utf8'))
assert not source['failures']
enums=json.loads((dest/'native-reflection-enums.json').read_text(encoding='utf8'))
def normalize(value,asset):
    if isinstance(value,list):return [normalize(v,asset) for v in value]
    if not isinstance(value,dict):return value
    if 'enum' in value and 'value' in value:
        return next((e['name'] for e in enums.get(value['enum'],[]) if e['value']==value['value']),value)
    if 'text' in value:return value['text']
    if 'index' in value and 'name' in value:
        def ref(index):
            if index==0:return None
            e=(asset['Exports'] if index>0 else asset['Imports'])[index-1 if index>0 else -index-1]
            outer=ref(e.get('OuterIndex',0));return (outer+'.' if outer else '')+e['ObjectName']
        return ref(value['index'])
    if 'package' in value and 'asset' in value:return value['package']+'.'+value['asset']+(':'+value['subpath'] if value.get('subpath') else '')
    return {re.sub(r'_\d+_[A-Fa-f0-9]{32}$','',k):normalize(v,asset) for k,v in value.items()}
tables={}
for table in source['tables']:
    asset=json.loads((dest/table['source']).read_text(encoding='utf8'))
    tables[table['table']]=[{'row':row['row'],**normalize(row['values'],asset)} for row in table['rows']]
result={'original_game_executed':False,'source':'table-values.json; every table payload byte-identical roundtrip','native_enums':enums,'tables':tables}
(dest/'normalized-content-catalog.json').write_text(json.dumps(result,indent=2,ensure_ascii=False),encoding='utf8')
old=json.loads((root/'progression-tables.json').read_text(encoding='utf8'))
diff=[]
for table,key in [('DT_Challenges','ChallengeID'),('DT_PlayerCards','CardID'),('DT_LevelData','Level')]:
    before={r[key]:r for r in old[table]};after={r[key]:r for r in tables[table]}
    changes=[]
    for ident in set(before)&set(after):
        fields={k:{'baseline':before[ident][k],'reference':v} for k,v in after[ident].items() if k!='row' and k in before[ident] and before[ident][k]!=v}
        if fields:changes.append({'id':ident,'fields':fields})
    diff.append({'table':table,'baseline_rows':len(before),'reference_rows':len(after),'added_ids':sorted(set(after)-set(before)),'absent_ids':sorted(set(before)-set(after)),'changed':changes})
(dest/'progression-table-delta.json').write_text(json.dumps(diff,indent=2,ensure_ascii=False),encoding='utf8')
print('Catalog tables:',{name:len(rows) for name,rows in tables.items()})
for t in diff:print(t['table'],'added',len(t['added_ids']),'absent',len(t['absent_ids']),'changed',len(t['changed']))
