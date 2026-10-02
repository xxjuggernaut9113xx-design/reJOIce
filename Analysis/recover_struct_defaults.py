"""Read and independently re-encode cooked UUserDefinedStruct defaults."""
from pathlib import Path
import base64
import json
import hashlib
import re

root = Path(__file__).parent
namespace = {'__file__':str(root/'decode_defaults.py')}
source = (root/'decode_defaults.py').read_text()
exec(compile(source.split('results=[];failures=[];checks=[]')[0], 'default_decoder_types', 'exec'), namespace)
Reader, Writer = namespace['Reader'], namespace['Writer']
classes = json.loads((root/'blueprint-class-fields.json').read_text())['classes']
results = {}
for cls in classes:
    path = root/'decoded'/ (cls['class']+'-functions.json')
    if not path.exists():
        continue
    asset = json.loads(path.read_text())
    export = next((e for e in asset['Exports'] if e['ObjectName']==cls['class']), None)
    if not export or export['ClassIndex'] >= 0:
        continue
    if asset['Imports'][-export['ClassIndex']-1]['ObjectName'] != 'UserDefinedStruct':
        continue
    raw = base64.b64decode(export['Data'])
    offset = cls['class_tail_offset'] + 4  # UScriptStruct::Serialize writes StructFlags.
    reader = Reader(raw[offset:], asset)
    values = reader.properties(cls['class'])
    assert reader.pos == len(reader.data), (cls['class'], reader.pos, len(reader.data))
    writer = Writer(reader)
    writer.properties(cls['class'], values)
    assert writer.data == reader.data, cls['class']
    clean = {re.sub(r'_\d+_[A-Fa-f0-9]{32}$','',k):v for k,v in values.items()}
    results[cls['class']] = {'defaults':clean,'default_payload_bytes':len(reader.data),
                            'byte_identical_roundtrip':True,'sha256':hashlib.sha256(reader.data).hexdigest()}
(root/'struct-default-values.json').write_text(json.dumps(results,indent=2),encoding='utf-8')
print('Recovered',len(results),'struct defaults with byte-identical round trips')
