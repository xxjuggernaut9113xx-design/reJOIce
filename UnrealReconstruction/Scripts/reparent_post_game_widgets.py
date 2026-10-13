from pathlib import Path
import json

import unreal


PROJECT = Path(unreal.Paths.project_dir())
TARGETS = (
    ("/Game/Recovery/UI/WBP_XPBar", unreal.RecoveredXPBarWidget),
    ("/Game/Recovery/UI/XBP_XPSourceText", unreal.RecoveredXPSourceTextWidget),
    ("/Game/Recovery/UI/WBP_XPScreen", unreal.RecoveredXPScreenWidget),
    ("/Game/Recovery/UI/WBP_UPRewardScreen", unreal.RecoveredUPRewardScreenWidget),
    ("/Game/Recovery/UI/WBP_UPSourceText", unreal.RecoveredUPSourceTextWidget),
    ("/Game/Recovery/UI/WBP_PlayerCard", unreal.RecoveredPlayerCardWidget),
    ("/Game/Recovery/UI/WBP_LevelUpScreen", unreal.RecoveredLevelUpScreenWidget),
)


def main() -> None:
    results = []
    for path, parent in TARGETS:
        blueprint = unreal.load_asset(path)
        if not blueprint:
            raise RuntimeError(f"Missing recovered post-game widget: {path}")
        widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
        if not widget_class:
            raise RuntimeError(f"Missing generated class: {path}")
        changed = False
        if not isinstance(unreal.get_default_object(widget_class), parent):
            unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, parent)
            changed = True
        unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
        widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
        if not widget_class or not isinstance(unreal.get_default_object(widget_class), parent):
            raise RuntimeError(f"Post-game widget reparent failed: {path}")
        if not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
            raise RuntimeError(f"Post-game widget save failed: {path}")
        results.append({"asset": path, "parent": parent.static_class().get_path_name(), "changed": changed})

    report = {"widgets": results}
    output = PROJECT / "Saved" / "post-game-widgets-reparent.json"
    output.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    unreal.log("POST_GAME_WIDGETS_REPARENTED " + json.dumps(report))


if __name__ == "__main__":
    main()
