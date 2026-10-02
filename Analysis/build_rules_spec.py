import pathlib,json,re
base=pathlib.Path(__file__).parent
defaults=json.loads((base/'blueprint-default-values.json').read_text())
branches=json.loads((base/'difficulty-branch-traces.json').read_text())
enums=json.loads((base/'blueprint-enums.json').read_text())
graph=json.loads((base/'main-event-graph.json').read_text())
def clean(value):
 if isinstance(value,dict):return {re.sub(r'_\d+_[A-F0-9]{32}$','',k):clean(v) for k,v in value.items()}
 if isinstance(value,list):return [clean(v) for v in value]
 return value
objects={o['class']:clean(o['serialized_properties']) for o in defaults['objects']}
g=objects['BP_GlobalManager_C']
patterns={k:v for k,v in g.items() if isinstance(v,list) and 'Pattern' in k}
config=[]
for i in range(3):
 row={'enumerator_index':i,'display_label':branches[0]['cases'][i]['display_label'],'assignments':{}}
 for rule in branches:row['assignments'].update(clean(rule['cases'][i]['assignments']))
 config.append(row)
spec={'schema_version':'cockhero-v004-rules-draft-1','game_sha256':'c645757d1112491952b67bf29502b4721133ba6940a9cfb08358f0dde127560f','engine':'5.3.2-29314046','full_parity_verified':False,'evidence':{'default_objects':8,'default_payload_roundtrips_identical':8,'difficulty_functions_with_validated_sizes_and_jumps':5,'main_graph_bytes':graph['memory_bytes'],'main_graph_statements':graph['statement_count'],'main_graph_aligned_branch_flow_targets':graph['aligned_jump_targets'],'main_graph_event_entries':len(graph['event_entries'])},'difficulty_configuration':config,'serialized_class_defaults':objects,'beat_pattern_banks':patterns,'event_records':g['AllSpecialEventsArray'],'blueprint_enums':enums['enums'],'event_entries':graph['event_entries'],'progression':json.loads((base/'progression-tables.json').read_text()),'verified_static_formulas':[{'source':'BP_GlobalManager.AddHeat','formula':'heat = clamp(heat + HeatAdd * DifficultyHeatGainMultiplier, 0, 100)'},{'source':'BP_DrawManager.RollChance','formula':'RollSuccessful = RandomFloatInRange(0, 100) <= Chance','rng_sequence_verified':False}],'limitations':['Serialized defaults are not final initialized gameplay values; difficulty functions overwrite some defaults.','Unserialized native constructor defaults and initialization callbacks require further correlation.','Main graph structure is checked; all conditional behavior, dynamic flow stacks, native calls and async callbacks are not yet interpreted.','No original-game behavioral traces or full parity acceptance runs have been performed.']}
(base/'game-rules-draft.json').write_text(json.dumps(spec,indent=2),encoding='utf8')
print('Rules draft: difficulty modes',len(config),'pattern slots',sum(len(v) for v in patterns.values()),'event records',len(spec['event_records']))
