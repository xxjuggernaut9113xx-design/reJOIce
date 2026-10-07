import unreal

path = "/Game/Recovery/UI/NotificationBoxWidget"
blueprint = unreal.load_asset(path)
if not blueprint:
    raise RuntimeError("Missing widget: " + path)
widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
if not widget_class:
    raise RuntimeError("Missing generated class: " + path)
if not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredNotificationWidget):
    unreal.BlueprintEditorLibrary.reparent_blueprint(blueprint, unreal.RecoveredNotificationWidget)
    unreal.BlueprintEditorLibrary.compile_blueprint(blueprint)
    widget_class = unreal.EditorAssetLibrary.load_blueprint_class(path)
    if not widget_class or not isinstance(unreal.get_default_object(widget_class), unreal.RecoveredNotificationWidget):
        raise RuntimeError("Notification widget reparent failed")
if not unreal.EditorAssetLibrary.save_loaded_asset(blueprint, only_if_is_dirty=False):
    raise RuntimeError("Notification widget save failed")
unreal.log("NOTIFICATION_WIDGET_REPARENTED")
