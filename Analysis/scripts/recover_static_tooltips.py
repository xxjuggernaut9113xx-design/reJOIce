"""Accept only literal, branch-free tooltip getters with the exact source call shape."""
from pathlib import Path
import hashlib
import json

root=Path(__file__).resolve().parents[1]
evidence=root/'UnrealReconstruction/RecoveryEvidence'
classes=json.loads((evidence/'widget-class-defaults.json').read_text(encoding='utf8'))
assert not classes['failures']
functions={}
for folder in ('widget-functions','blueprint-functions'):
    for path in (root/folder).glob('*/*.json'):
        function=json.loads(path.read_text(encoding='utf8'))
        functions[(path.parent.name,function['function']['name'])]=(function,path)

def text(value):
    assert value['op']=='EX_TextConst'
    literal=value['Value'];kind=literal['TextLiteralType']
    if kind=='LocalizedText':
        for key in ('LocalizedSource','LocalizedKey','LocalizedNamespace'):
            assert literal[key]['op'] in ('EX_StringConst','EX_UnicodeStringConst')
        return {'text':literal['LocalizedSource']['Value'],'key':literal['LocalizedKey']['Value'],'namespace':literal['LocalizedNamespace']['Value']}
    if kind=='InvariantText':
        assert literal['InvariantLiteralString']['op'] in ('EX_StringConst','EX_UnicodeStringConst')
        return {'text':literal['InvariantLiteralString']['Value'],'invariant':True}
    raise ValueError(kind)

records=[];skipped=[]
for cls in classes['classes']:
    screen=cls['class'].removesuffix('_C')
    raw_path=next((p for p in [root/'decoded'/(screen+'-functions.json'),root/'decoded-widget-functions'/(screen+'-functions.json')] if p.exists()),None)
    raw=json.loads(raw_path.read_text(encoding='utf8')) if raw_path else None
    for binding in cls['metadata'].get('Bindings',[]):
        if binding['PropertyName']!='ToolTipWidget':continue
        name=binding['FunctionName']
        try:
            function,path=functions[(screen,name)]
            code=function['statements'];assert len(code)==5
            assert code[0]['op']=='EX_LetObj' and code[1]['op']=='EX_Context' and code[2]['op']=='EX_LetObj' and code[3]['op']=='EX_Return' and code[4]['op']=='EX_EndOfScript'
            create=code[0]['AssignmentExpression']['ContextExpression'];assert create['StackNode']=='Create'
            assert create['Parameters'][0]['op']=='EX_Self' and create['Parameters'][2]['op']=='EX_NoObject'
            index=create['Parameters'][1]['Value'];assert index<0
            assert raw['Imports'][-index-1]['ObjectName']=='CustomToolTip_Widget_C'
            created=code[0]['VariableExpression'];assert created==code[1]['ObjectExpression']==code[2]['AssignmentExpression']
            assert code[2]['VariableExpression']==code[3]['ReturnExpression']
            call=code[1]['ContextExpression'];assert call['VirtualFunctionName']=='Set Title & Description' and len(call['Parameters'])==2
            assert binding['Kind']['value']==0
            records.append({'asset':screen,'widget':binding['ObjectName'],'function':name,'title':text(call['Parameters'][0]),'description':text(call['Parameters'][1]),'function_sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
        except (AssertionError,KeyError,TypeError,ValueError) as error:
            skipped.append({'asset':screen,'widget':binding['ObjectName'],'function':name,'reason':type(error).__name__})
report={'original_executed':False,'animations_restored':False,'records':records,'unsupported_getters':skipped}
(evidence/'static-tooltip-values.json').write_text(json.dumps(report,indent=2,ensure_ascii=False),encoding='utf8')
print('Verified static tooltip bindings',len(records),'unsupported',len(skipped))
