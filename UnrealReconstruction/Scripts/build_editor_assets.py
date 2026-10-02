"""Run in UE5.3 via -run=pythonscript -script=... . Builds new editable assets."""
from pathlib import Path
import json
import re
import unreal

project = Path(unreal.Paths.project_dir())
evidence = project / 'RecoveryEvidence'
rules = json.loads((evidence / 'game-rules-draft.json').read_text(encoding='utf-8'))
fields = json.loads((evidence / 'blueprint-class-fields.json').read_text(encoding='utf-8'))
properties = {c['class']: c['properties'] for c in fields['classes']}
tools = unreal.AssetToolsHelpers.get_asset_tools()
assets = unreal.EditorAssetLibrary
report = {'full_game_complete': False, 'definitions': [], 'blueprints': [], 'tables': {}, 'errors': []}

def snake(name):
    name = name.replace('PlayerVariablesStruct.', '')
    return re.sub(r'(?<!^)(?=[A-Z])', '_', name).lower()

def assign(obj, values):
    for key, value in values.items():
        obj.set_editor_property(snake(key), value)
    return obj

def create(name, path, cls, factory):
    asset = assets.load_asset(path + '/' + name) if assets.does_asset_exist(path + '/' + name) else None
    if asset is None:
        asset = tools.create_asset(name, path, cls, factory)
    assert asset is not None, path + '/' + name
    return asset

def save(asset):
    assert assets.save_loaded_asset(asset, False), asset.get_path_name()

def new_data(name, cls):
    factory = unreal.DataAssetFactory()
    factory.set_editor_property('data_asset_class', cls)
    return create(name, '/Game/Recovery/Definitions', cls, factory)

definition_assets = {}
folders = {p.name: p for p in (evidence / 'blueprint-functions').iterdir() if p.is_dir()}
names = set(folders) | {c[:-2] if c.endswith('_C') else c for c in rules['serialized_class_defaults']}
function_count = 0
for name in sorted(names):
    cls = name + '_C'
    definition = new_data('DA_' + name, unreal.RecoveredDefinitionAsset)
    definition.set_editor_property('source_class', cls)
    definition.set_editor_property('serialized_defaults_json', json.dumps(rules['serialized_class_defaults'].get(cls, {}), ensure_ascii=False, indent=2))
    definition.set_editor_property('declared_properties_json', json.dumps(properties.get(cls, []), ensure_ascii=False, indent=2))
    functions = {}
    if name in folders:
        for path in sorted(folders[name].glob('*.json')):
            data = json.loads(path.read_text(encoding='utf-8'))
            functions[data['function']['name']] = json.dumps(data, ensure_ascii=False, indent=2)
    definition.set_editor_property('decoded_function_bodies', functions)
    function_count += len(functions)
    save(definition)
    definition_assets[cls] = definition
    report['definitions'].append({'class': cls, 'asset': definition.get_path_name(), 'function_count': len(functions)})

rule_asset = new_data('DA_GameRules', unreal.RecoveredRulesAsset)
profiles = []
for profile in rules['difficulty_configuration']:
    profiles.append(assign(unreal.RecoveredDifficultyConfig(), profile['assignments']))
rule_asset.set_editor_property('difficulty_profiles', profiles)
for name, patterns in rules['beat_pattern_banks'].items():
    rule_asset.set_editor_property(snake(name), [assign(unreal.RecoveredBeatPattern(), pattern) for pattern in patterns])
events = []
for event in rules['event_records']:
    item = dict(event)
    item['IsOnCooldown'] = bool(item['IsOnCooldown'])
    item['IsEligible'] = bool(item['IsEligible'])
    item['EventDescription'] = unreal.Text(item['EventDescription'].get('text', ''))
    events.append(assign(unreal.RecoveredEventRecord(), item))
rule_asset.set_editor_property('event_records', events)
entries = []
for entry in rules['event_entries']:
    entries.append(assign(unreal.RecoveredEventEntry(), {'Event': entry['event'], 'EntryOffset': entry['entry_offset'], 'EntryStatement': entry['entry_statement']}))
rule_asset.set_editor_property('event_entries', entries)
rule_asset.set_editor_property('blueprint_enums_json', json.dumps(rules['blueprint_enums'], ensure_ascii=False, indent=2))
assert rule_asset.get_editor_property('source_game_sha256') == rules['game_sha256']
save(rule_asset)

def normalize(value):
    if value is None:
        return ''
    if isinstance(value, list):
        return [normalize(v) for v in value]
    if isinstance(value, dict):
        return {k: normalize(v) for k, v in value.items()}
    return value

structs = {
    'DT_Challenges': unreal.RecoveredRuleLibrary.get_challenge_row_struct(),
    'DT_LevelData': unreal.RecoveredRuleLibrary.get_level_row_struct(),
    'DT_PlayerCards': unreal.RecoveredRuleLibrary.get_player_card_row_struct(),
    'DT_HeatCategories': unreal.RecoveredRuleLibrary.get_heat_category_row_struct()
}
heat_evidence = json.loads((evidence / 'heat-category-rows.json').read_text(encoding='utf-8'))
assert heat_evidence['byte_identical_roundtrip']
rules['progression']['DT_HeatCategories'] = [dict(row=row['row'], **{re.sub(r'_\d+_[A-Fa-f0-9]{32}$', '', key):value for key,value in row['values'].items()}) for row in heat_evidence['rows']]
for name, rows in rules['progression'].items():
    factory = unreal.DataTableFactory()
    factory.set_editor_property('struct', structs[name])
    table = create(name, '/Game/Recovery/Progression', unreal.DataTable, factory)
    source_rows = []
    for row in rows:
        row = normalize(row)
        row['Name'] = row.pop('row')
        source_rows.append(row)
    assert unreal.DataTableFunctionLibrary.fill_data_table_from_json_string(table, json.dumps(source_rows)), name
    save(table)
    exported = json.loads(unreal.RecoveredRuleLibrary.export_table_json(table))
    # Unreal exporters sanitize display-name field spacing; match keys case-insensitively.
    def canonical(value):
        if isinstance(value, list):
            return [canonical(v) for v in value]
        if isinstance(value, dict):
            return {k.lower().replace(' ', ''): canonical(v) for k, v in value.items()}
        return value
    expected = {row['Name']: canonical(row) for row in source_rows}
    actual = {row['Name']: canonical(row) for row in exported}
    assert actual == expected, name + ' imported values differ from recovered rows'
    report['tables'][name] = {'rows': len(exported), 'all_fields_match': True}

for cls in rules['serialized_class_defaults']:
    name = cls[:-2]
    parent = unreal.RecoveredManager
    if name == 'BP_GlobalManager':
        parent = unreal.RecoveredGlobalManager
    elif name == 'BP_CHGameInstance':
        parent = unreal.RecoveredGameInstance
    elif name == 'BP_CHSaveGame':
        parent = unreal.RecoveredSaveGame
    factory = unreal.BlueprintFactory()
    factory.set_editor_property('parent_class', parent)
    bp = create(name, '/Game/NewSetup', unreal.Blueprint, factory)
    unreal.BlueprintEditorLibrary.compile_blueprint(bp)
    generated = unreal.BlueprintEditorLibrary.generated_class(bp)
    assert generated is not None, name
    defaults = unreal.get_default_object(generated)
    defaults.set_editor_property('recovered_definition', definition_assets[cls])
    if name == 'BP_GlobalManager':
        defaults.set_editor_property('rules', rule_asset)
        defaults.set_editor_property('heat_category_data_table', assets.load_asset('/Game/Recovery/Progression/DT_HeatCategories'))
        player = defaults.get_editor_property('player_variables')
        player_fields = json.loads((evidence / 'player-field-map.json').read_text(encoding='utf-8'))
        expected = rules['serialized_class_defaults'][cls]['PlayerVariablesStruct']
        for original, reflected in player_fields.items():
            actual = player.get_editor_property(reflected)
            if isinstance(expected[original], list):
                actual = list(actual)
            assert actual == expected[original], (original, actual, expected[original])
        report['player_default_fields_verified'] = len(player_fields)
    save(bp)
    report['blueprints'].append({'asset': bp.get_path_name(), 'generated_class': generated.get_path_name(), 'original_graph_restored': False})

level_path = '/Game/Recovery/RecoveryWorkspace'
if not assets.does_asset_exist(level_path):
    assert unreal.EditorLevelLibrary.new_level(level_path)
else:
    assert unreal.EditorLevelLibrary.load_level(level_path)
world = unreal.EditorLevelLibrary.get_editor_world()
global_class = unreal.load_class(None, '/Game/NewSetup/BP_GlobalManager.BP_GlobalManager_C')
world.get_world_settings().set_editor_property('default_game_mode', global_class)
if not any(a.get_actor_label() == 'RecoveryStatus' for a in unreal.EditorLevelLibrary.get_all_level_actors()):
    label = unreal.EditorLevelLibrary.spawn_actor_from_class(unreal.TextRenderActor, unreal.Vector(0, 0, 150))
    label.set_actor_label('RecoveryStatus')
    text = label.get_component_by_class(unreal.TextRenderComponent)
    text.set_text('CockHero V0.04 recovered workspace\nEditable data and verified rules\nFull gameplay reconstruction incomplete')
    text.set_world_size(24)
    label.set_actor_rotation(unreal.Rotator(0, 180, 0), False)
assert unreal.EditorLoadingAndSavingUtils.save_map(world, level_path)

report.update({'decoded_function_bodies': function_count,
               'difficulty_profiles': len(profiles),
               'pattern_slots': sum(len(v) for v in rules['beat_pattern_banks'].values()),
               'event_records': len(events), 'event_entries': len(entries),
               'original_media_imported': False,
               'editable_original_blueprint_graphs_recovered': False,
               'validation_passed': True})
assert function_count == 479, 'Decoded function coverage changed; audit the recovery selection'
assert len(report['blueprints']) == 8
assert report['pattern_slots'] == 62 and len(events) == 31 and len(entries) == 60
output = project / 'Saved' / 'reconstruction-validation.json'
output.parent.mkdir(parents=True, exist_ok=True)
output.write_text(json.dumps(report, ensure_ascii=False, indent=2), encoding='utf-8')
unreal.log('RECOVERY_ASSETS_VALIDATED ' + str(output))
