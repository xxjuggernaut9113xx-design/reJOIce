"""Read matched newer PDB public addresses for focused Tower recovery."""
from pathlib import Path
import json
import math

root = Path(__file__).resolve().parents[1]
dest = root / 'ReferenceBuilds/newer-20261017'
source = (root / 'recover_native_schemas.py').read_text(encoding='utf8').split('schemas={}')[0]
source = source.replace("base=pathlib.Path(__file__).parent", "base=pathlib.Path(r'" + str(dest) + "')")
source = source.replace(r'C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive\PrepV2\Windows\CockHero\Binaries\Win64', r'C:\Users\webma\Downloads\cock-hero-windows (1)\Windows\CockHero\Binaries\Win64')
namespace = {}
exec(compile(source, str(root / 'recover_native_schemas.py'), 'exec'), namespace)
symbols = [{'address': hex(address), 'name': name} for name, address in namespace['public'].items() if ('@URoundManager@@' in name or name.startswith('??0URoundManager@@')) and name.startswith('?') and not name.startswith('?exec')]
symbols.sort(key=lambda symbol: int(symbol['address'], 16))
(dest / 'native-round-symbols.json').write_text(json.dumps(symbols, indent=2), encoding='utf8')
print(json.dumps(symbols, indent=2))
constants = {}
for address in (0x14c144af0, 0x14bfe47a8, 0x14bfe47ac, 0x14bf8cea0, 0x14bf8ce7c, 0x14bf3cd38, 0x14bf3cd58, 0x14bf2ebec, 0x14bf56a24, 0x14bf569c8, 0x14bf56a6c, 0x14bfb66c0, 0x14c291cb0, 0x14bf56a80, 0x14c4d1160, 0x14bf3cd20):
    value = namespace['struct'].unpack_from('<f', namespace['pe'], namespace['off'](address))[0]
    constants[hex(address)] = value if math.isfinite(value) else {'bits': hex(namespace['struct'].unpack_from('<I', namespace['pe'], namespace['off'](address))[0])}
(dest / 'native-round-adaptive-constants.json').write_text(json.dumps(constants, indent=2), encoding='utf8')
print('Adaptive constants', constants)
print('Constructors', [(name, hex(address)) for name, address in namespace['public'].items() if ('URoundManager' in name or 'UMusicModeManager' in name) and ('Constructor' in name or name.startswith('??0'))])
filter_strings = {}
for address in (0x14d2183d0, 0x14d218470, 0x14d218370, 0x14d218350, 0x14d218490, 0x14d218388, 0x14d218448, 0x14d2184d8):
    position = namespace['off'](address)
    end = position
    while namespace['pe'][end:end + 2] != b'\0\0':
        end += 2
    filter_strings[hex(address)] = namespace['pe'][position:end].decode('utf-16-le')
(dest / 'native-round-filter-strings.json').write_text(json.dumps(filter_strings, indent=2), encoding='utf8')
print('Filter strings', filter_strings)
print('Filter symbol', [(name, hex(address)) for name, address in namespace['public'].items() if address == 0x1482fcc80])
