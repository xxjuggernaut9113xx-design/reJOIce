"""Create an editable modifier table from byte-verified cooked row data."""
from pathlib import Path
import json,re
import unreal
project=Path(unreal.Paths.project_dir())
evidence=json.loads((project/'RecoveryEvidence/modifier-table-values.json').read_text(encoding='utf8'))
assert evidence['byte_identical_roundtrip']
aliases=json.loads((project/'RecoveryEvidence/resource-aliases.json').read_text(encoding='utf8'))
rows=[]
for entry in evidence['rows']:
    row={'Name':entry['row']}
    for name,value in entry['values'].items():
        name=re.sub(r'_\d+_[A-Fa-f0-9]{32}$','',name)
        if name=='ModifierIcon':
            original=evidence['imports'][str(value['index'])]
            value=aliases[original]
        elif isinstance(value,dict) and 'text' in value:
            if 'namespace' in value and 'key' in value:
                value='NSLOCTEXT('+','.join(json.dumps(value[k],ensure_ascii=False) for k in ('namespace','key','text'))+')'
            else:value=value['text']
        row[name]=value
    rows.append(row)
path='/Game/Recovery/Progression/DT_Modifiers'
table=unreal.load_asset(path) if unreal.EditorAssetLibrary.does_asset_exist(path) else None
if not table:
    factory=unreal.DataTableFactory()
    factory.set_editor_property('struct',unreal.RecoveredRuleLibrary.get_modifier_row_struct())
    table=unreal.AssetToolsHelpers.get_asset_tools().create_asset('DT_Modifiers','/Game/Recovery/Progression',unreal.DataTable,factory)
assert table and unreal.DataTableFunctionLibrary.fill_data_table_from_json_string(table,json.dumps(rows))
assert unreal.EditorAssetLibrary.save_loaded_asset(table)
exported=json.loads(unreal.RecoveredRuleLibrary.export_table_json(table))
assert len(exported)==len(rows)
for original,recovered in zip(evidence['rows'],exported):
    title=next(v['text'] for k,v in original['values'].items() if k.startswith('ModifierTitle_'))
    assert recovered['ModifierTitle']==title,(title,recovered)
report={'rows':len(rows),'byte_identical_source_roundtrip':True,'original_executed':False,'full_game_complete':False}
(project/'Saved/modifier-table-recovery-report.json').write_text(json.dumps(report,indent=2),encoding='utf8')
unreal.log('RECOVERED_MODIFIER_TABLE_VERIFIED '+str(len(rows)))
