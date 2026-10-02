"""Create an editable video-display material; the cooked expression graph is unavailable."""
from pathlib import Path
import json
import unreal

project=Path(unreal.Paths.project_dir())
evidence=json.loads((project/'RecoveryEvidence/background-material-values.json').read_text(encoding='utf8'))
assert evidence['property_prefix_byte_identical_roundtrip']
assert evidence['values']['MaterialDomain']==5
tools=unreal.AssetToolsHelpers.get_asset_tools()
library=unreal.EditorAssetLibrary
path='/Game/Recovery/Resources/Video'

def create(name,cls,factory):
    asset=library.load_asset(path+'/'+name) if library.does_asset_exist(path+'/'+name) else None
    return asset or tools.create_asset(name,path,cls,factory)

texture=create('Background_Video_Texture',unreal.MediaTexture,unreal.MediaTextureFactoryNew())
assert texture is not None
material=create('Background_Video_Texture_Mat',unreal.Material,unreal.MaterialFactoryNew())
assert material is not None
material.set_editor_property('material_domain',unreal.MaterialDomain.MD_UI)
material.set_editor_property('blend_mode',unreal.BlendMode.BLEND_OPAQUE)
# This is a new one-node display graph, explicitly marked as a reconstruction.
unreal.MaterialEditingLibrary.delete_all_material_expressions(material)
sample=unreal.MaterialEditingLibrary.create_material_expression(material,unreal.MaterialExpressionTextureSampleParameter2D,-300,0)
assert sample is not None
sample.set_editor_property('parameter_name','BackgroundVideoTexture')
sample.set_editor_property('texture',texture)
sample.set_editor_property('sampler_type',unreal.MaterialSamplerType.SAMPLERTYPE_EXTERNAL)
sample.set_editor_property('desc','Reconstructed video display; original cooked expression graph unavailable')
assert unreal.MaterialEditingLibrary.connect_material_property(sample,'RGB',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
unreal.MaterialEditingLibrary.recompile_material(material)
library.set_metadata_tag(material,'Recovery.ExpressionGraph','Reconstructed; original graph stripped from cooked build')
assert library.save_loaded_asset(texture,False)
assert library.save_loaded_asset(material,False)
aliases_path=project/'RecoveryEvidence/resource-aliases.json'
aliases=json.loads(aliases_path.read_text(encoding='utf8'))
aliases['/Game/Background_Video_Texture_Mat.Background_Video_Texture_Mat']=material.get_path_name()
aliases['/Game/Background_Video_Texture.Background_Video_Texture']=texture.get_path_name()
aliases_path.write_text(json.dumps(aliases,indent=2),encoding='utf8')
report={'full_game_complete':False,'original_expression_graph_restored':False,'material_domain_verified':True,'source_property_prefix_bytes':evidence['property_prefix_bytes'],'material':material.get_path_name(),'texture':texture.get_path_name(),'texture_parameter':'BackgroundVideoTexture','editor_video_playback_validated':False}
(project/'Saved/video-material-recovery-report.json').write_text(json.dumps(report,indent=2),encoding='utf8')
unreal.log('RECOVERED_VIDEO_MATERIAL_CREATED')
