import unreal
bp=unreal.load_asset('/Game/Recovery/UI/WBP_CalibrationUI')
unreal.BlueprintEditorLibrary.reparent_blueprint(bp,unreal.RecoveredCalibrationWidget)
unreal.BlueprintEditorLibrary.compile_blueprint(bp)
assert unreal.EditorAssetLibrary.save_loaded_asset(bp)
unreal.log('CALIBRATION_WIDGET_REPARENTED')
