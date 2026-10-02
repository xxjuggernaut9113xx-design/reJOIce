"""Refresh only recovered resources and widget layouts; original gameplay remains incomplete."""
from pathlib import Path
import runpy
import subprocess
import unreal

project=Path(unreal.Paths.project_dir())
scripts=project/'Scripts'
runpy.run_path(str(scripts/'export_ui_textures.py'))
subprocess.run([r'C:\Users\webma\scoop\apps\python\current\python.exe',str(project.parent/'scripts/decode_texture_mips.py')],check=True)
runpy.run_path(str(scripts/'import_ui_textures.py'))
runpy.run_path(str(scripts/'decode_ui_audio.py'))
runpy.run_path(str(scripts/'import_ui_audio.py'))
runpy.run_path(str(scripts/'recover_video_material.py'))
runpy.run_path(str(scripts/'recover_modifier_table.py'))
runpy.run_path(str(scripts/'build_widget_assets.py'))
unreal.log('RECOVERED_RESOURCE_REFRESH_COMPLETE: full game remains incomplete')
