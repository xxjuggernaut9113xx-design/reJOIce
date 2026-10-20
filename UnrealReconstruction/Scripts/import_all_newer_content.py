"""Run validated newer progression, modifier artwork and voice imports together."""
import runpy
from pathlib import Path
import unreal

scripts = Path(unreal.Paths.project_dir()).resolve() / "Scripts"
runpy.run_path(str(scripts / "import_newer_progression.py"), run_name="__main__")
runpy.run_path(str(scripts / "import_newer_voices.py"), run_name="__main__")
unreal.log("NEWER_CONTENT_IMPORT_COMPLETE")
