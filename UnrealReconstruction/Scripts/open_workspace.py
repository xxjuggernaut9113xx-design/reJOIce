import unreal

rules = unreal.load_asset('/Game/Recovery/Definitions/DA_GameRules')
assert rules is not None
manager = unreal.load_asset('/Game/NewSetup/BP_GlobalManager')
assert manager is not None
assert unreal.get_editor_subsystem(unreal.AssetEditorSubsystem).open_editor_for_assets([rules, manager])
unreal.EditorAssetLibrary.sync_browser_to_objects([
    '/Game/Recovery/Definitions/DA_GameRules',
    '/Game/NewSetup/BP_GlobalManager',
    '/Game/Recovery/Progression/DT_Challenges',
    '/Game/Recovery/Progression/DT_LevelData',
    '/Game/Recovery/Progression/DT_PlayerCards'
])
unreal.log('RECOVERED_EDITOR_READY: partial editable reconstruction; full gameplay remains incomplete')
