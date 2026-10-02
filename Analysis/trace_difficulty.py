"""Resolve selected bytecode jumps and evaluate constant difficulty assignments.
Static evaluation only. Does not run the original game or simulate its engine.
Instruction sizes follow matching UAssetAPI 8b8687a Visit implementations.
"""
import pathlib,json
base=pathlib.Path(__file__).parent
def size(n):
 op=n['op'];fixed={'EX_ByteConst':2,'EX_DoubleConst':9,'EX_FloatConst':5,'EX_Int64Const':9,'EX_NameConst':13,'EX_ObjectConst':9,'EX_Jump':5,'EX_InstanceVariable':9,'EX_LocalVariable':9,'EX_LocalOutVariable':9,'EX_EndOfScript':1,'EX_Nothing':1,'EX_Self':1,'EX_True':1,'EX_False':1,'EX_NoObject':1,'EX_PopExecutionFlow':1,'EX_IntConst':5,'EX_SkipOffsetConst':5,'EX_PushExecutionFlow':5,'EX_VectorConst':25,'EX_RotationConst':25,'EX_TransformConst':81}
 if op in fixed:return fixed[op]
 if op=='EX_BitFieldConst':return 10 # opcode, in-memory FProperty pointer, byte value (UE5.3 ScriptSerialization.h).
 if op=='EX_StringConst':return 2+len(n['Value'].encode('utf-16le'))//2
 if op=='EX_UnicodeStringConst':return 3+len(n['Value'].encode('utf-16le'))
 if op in ('EX_CallMath','EX_FinalFunction','EX_LocalFinalFunction'):return 10+sum(size(p) for p in n['Parameters'])
 if op in ('EX_VirtualFunction','EX_LocalVirtualFunction'):return 14+sum(size(p) for p in n['Parameters'])
 if op=='EX_CallMulticastDelegate':return 10+size(n['Delegate'])+sum(size(p) for p in n['Parameters'])
 if op=='EX_LetValueOnPersistentFrame':return 9+size(n['AssignmentExpression'])
 if op=='EX_InterfaceContext':return 1+size(n['InterfaceValue'])
 if op=='EX_JumpIfNot':return 5+size(n['BooleanExpression'])
 if op=='EX_Let':return 9+size(n['Variable'])+size(n['Expression'])
 if op in ('EX_LetBool','EX_LetObj'):return 1+size(n['VariableExpression'])+size(n['AssignmentExpression'])
 if op=='EX_Return':return 1+size(n['ReturnExpression'])
 if op=='EX_SetArray':return 2+size(n['AssigningProperty'])+sum(size(e) for e in n['Elements'])
 if op=='EX_StructConst':return 14+sum(size(v) for v in n['Value'])
 if op=='EX_StructMemberContext':return 9+size(n['StructExpression'])
 if op=='EX_Context':return 13+size(n['ObjectExpression'])+size(n['ContextExpression'])
 if op=='EX_DynamicCast':return 9+size(n['Target'])
 if op=='EX_PrimitiveCast':return 2+(8 if n['ConversionType']=='ObjectToInterface' else 0)+size(n['Target'])
 if op=='EX_AddMulticastDelegate':return 1+size(n['Delegate'])+size(n['DelegateToAdd'])
 if op=='EX_BindDelegate':return 13+size(n['Delegate'])+size(n['ObjectTerm'])
 if op=='EX_ClearMulticastDelegate':return 1+size(n['DelegateToClear'])
 if op=='EX_ComputedJump':return 1+size(n['CodeOffsetExpression'])
 if op=='EX_PopExecutionFlowIfNot':return 1+size(n['BooleanExpression'])
 if op=='EX_TextConst':
  v=n['Value'];kind=v['TextLiteralType'];keys={'Empty':[],'LocalizedText':['LocalizedSource','LocalizedKey','LocalizedNamespace'],'InvariantText':['InvariantLiteralString'],'LiteralString':['LiteralString'],'StringTableEntry':['StringTableId','StringTableKey']}[kind]
  return 2+(8 if kind=='StringTableEntry' else 0)+sum(size(v[k]) for k in keys)
 raise ValueError(('Unsupported size',op))
asset=json.loads((base/'decoded/BP_GlobalManager-functions.json').read_text())
exports={e['ObjectName']:e for e in asset['Exports']}
names=['SetHeatGainDifficultyModifier','SetCoinMultiplierBasedOnDifficulty','SetStrokeCountAndSpeedDifficultyModifiers','SetCumMeterDifficultyModifier','SetItemSpawnRatesBasedOnDifficulty']
enum_data=json.loads((base/'blueprint-enums.json').read_text())['enums']
difficulty_labels={entry['value']:entry['display'] for enum in enum_data if enum['enum']=='DifficultySelections_ENUM' for entry in enum['entries']}
result=[]
for name in names:
 p=json.loads((base/'blueprint-functions/BP_GlobalManager'/(name+'.json')).read_text());code=p['statements'];offsets=[];offset=0
 for n in code:offsets.append(offset);offset+=size(n)
 assert offset==exports[name]['ScriptBytecodeSize'],(name,offset,exports[name]['ScriptBytecodeSize'])
 byoffset={v:i for i,v in enumerate(offsets)}
 jumps=[{'statement':i,'offset':offsets[i],'target':n['CodeOffset'],'target_statement':byoffset[n['CodeOffset']]} for i,n in enumerate(code) if n['op'] in ('EX_Jump','EX_JumpIfNot')]
 cases=[]
 for difficulty in range(3):
  state={'CurrentDifficulty':difficulty};visited=[];assignments={};i=0
  def val(n):
   op=n['op']
   if op in ('EX_LocalVariable','EX_InstanceVariable'):return state.get(n['Variable']['field'])
   if op=='EX_True':return True
   if op in ('EX_DoubleConst','EX_FloatConst','EX_ByteConst','EX_Int64Const'):return 0 if n['Value']=='+0' else n['Value']
   if op=='EX_CallMath' and n['StackNode']=='NotEqual_ByteByte':return val(n['Parameters'][0])!=val(n['Parameters'][1])
   if op in ('EX_StringConst','EX_NameConst'):return n['Value']
   return None
  for _ in range(1000):
   n=code[i];visited.append(i);op=n['op']
   if op=='EX_Jump':i=byoffset[n['CodeOffset']];continue
   if op=='EX_JumpIfNot' and not val(n['BooleanExpression']):i=byoffset[n['CodeOffset']];continue
   if op in ('EX_Let','EX_LetBool'):
    variable=n['Variable'] if op=='EX_Let' else n['VariableExpression']
    expr=n['Expression'] if op=='EX_Let' else n['AssignmentExpression']
    if variable['op'] in ('EX_InstanceVariable','EX_LocalVariable'):
     field=variable['Variable']['field'];v=val(expr);state[field]=v
     if variable['op']=='EX_InstanceVariable':
      assert v is not None,('Cannot evaluate gameplay assignment',name,field,expr)
      assignments[field]=v
    elif variable['op']=='EX_StructMemberContext' and variable['StructExpression']['op']=='EX_InstanceVariable':
     parent=variable['StructExpression']['Variable']['field'];field=variable['StructMemberExpression']['field'];v=val(expr)
     assert v is not None,('Cannot evaluate gameplay struct assignment',name,field,expr)
     assignments[parent+'.'+field]=v
   if op in ('EX_Return','EX_EndOfScript'):break
   i+=1
  else:raise ValueError(('Evaluation exceeded step limit',name,difficulty))
  cases.append({'enumerator_index':difficulty,'display_label':difficulty_labels[difficulty],'assignments':assignments,'visited_statements':visited})
 result.append({'function':name,'memory_bytes':offset,'matches_declared_size':True,'jump_targets':jumps,'cases':cases})
(base/'difficulty-branch-traces.json').write_text(json.dumps(result,indent=2),encoding='utf8')
for rule in result:print(rule['function'],[(c['enumerator_index'],c['assignments']) for c in rule['cases']])
