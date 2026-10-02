"""Import decoded source pixels as fresh, editable texture assets."""
from pathlib import Path
import json
import unreal

project = Path(unreal.Paths.project_dir())
rows = json.loads((project/'RecoveryEvidence/texture-decoding-report.json').read_text(encoding='utf-8'))
alias_file = project/'RecoveryEvidence/resource-aliases.json'
aliases = json.loads(alias_file.read_text(encoding='utf-8')) if alias_file.exists() else {}
imported = 0
errors = []
for row in rows:
    if not row.get('decoded'):
        continue
    relative = row['original'].split('.', 1)[0][len('/Game/'):]
    folder = '/Game/Recovery/Resources/'+str(Path(relative).parent).replace('\\', '/')
    name = Path(relative).name
    task = unreal.AssetImportTask()
    task.filename = row['png']
    task.destination_path = folder
    task.destination_name = name
    task.automated = True
    task.replace_existing = True
    task.save = False
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks([task])
    path = folder+'/'+name+'.'+name
    texture = unreal.load_asset(path)
    if not isinstance(texture, unreal.Texture2D):
        errors.append(row['original'])
        continue
    texture.set_editor_property('srgb', row['srgb'])
    texture.set_editor_property('compression_settings', unreal.TextureCompressionSettings.TC_EDITOR_ICON)
    texture.set_editor_property('mip_gen_settings', unreal.TextureMipGenSettings.TMGS_NO_MIPMAPS)
    unreal.EditorAssetLibrary.save_loaded_asset(texture)
    aliases[row['original']] = path
    imported += 1
(project/'RecoveryEvidence/resource-aliases.json').write_text(json.dumps(aliases, indent=2), encoding='utf-8')
(project/'Saved/texture-import-report.json').write_text(json.dumps({'imported': imported, 'errors': errors}, indent=2), encoding='utf-8')
assert not errors, errors
unreal.log('RECOVERED_EDITABLE_TEXTURES '+str(imported))
