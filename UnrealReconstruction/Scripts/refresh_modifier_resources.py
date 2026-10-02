from pathlib import Path
import runpy,subprocess
import unreal
project=Path(unreal.Paths.project_dir());scripts=project/'Scripts'
runpy.run_path(str(scripts/'export_ui_textures.py'))
subprocess.run([r'C:\Users\webma\scoop\apps\python\current\python.exe',str(project.parent/'scripts/decode_texture_mips.py')],check=True)
runpy.run_path(str(scripts/'import_ui_textures.py'))
runpy.run_path(str(scripts/'recover_modifier_table.py'))
