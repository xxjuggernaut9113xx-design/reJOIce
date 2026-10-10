import hashlib
import json
from pathlib import Path


analysis = Path(r"C:\Users\webma\analysis\cockhero-v004")
project = Path(__file__).resolve().parents[1]
widget_functions = analysis / "widget-functions" / "ToySettingsMenu"
decoded_package = analysis / "decoded-ui" / "CockHero" / "Content" / "Widgets" / "ToySettingsMenu.json"
native_decompile = analysis / "ghidra-native" / "integration-decompiled.c"
shipping_executable = Path(
    r"C:\Users\webma\Downloads\Cock_Hero_Shipping_Build_V0.04_-_Exclusive"
    r"\PrepV2\Windows\CockHero\Binaries\Win64\CockHero.exe"
)


def read_json(path: Path):
    return json.loads(path.read_text(encoding="utf-8"))


def sha256(path: Path):
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def string_literals(node):
    if isinstance(node, dict):
        if node.get("op") == "EX_StringConst":
            yield node["Value"]
        for value in node.values():
            yield from string_literals(value)
    elif isinstance(node, list):
        for value in node:
            yield from string_literals(value)


graph_path = widget_functions / "ExecuteUbergraph_ToySettingsMenu.json"
graph = read_json(graph_path)
package = read_json(decoded_package)
native_text = native_decompile.read_text(encoding="utf-8")
calls = set(graph["function"]["calls"])
fields = set(graph["function"]["fields"])
names = set(package["NameMap"])
names.update(export_item.get("ObjectName") for export_item in package["Exports"] if export_item.get("ObjectName"))

required_calls = {
    "ConnectToHandy",
    "ConnectToLovense",
    "ConnectToLovenseViaHTTP",
    "ConnectToButtplug",
    "DisconnectFromLovense",
    "DisconnectFromLovenseViaMobile",
    "DisconnectFromButtplug",
    "RefreshHandyStatus",
    "RefreshLovenseDevices",
    "RefreshButtplugDevices",
    "SetHandyPositionWithTime",
    "SetHandySlideSettings",
    "SetButtplugVibratorIntensity",
    "SetStrokeSlider",
    "SendTestVibration",
    "TestAllButtplugDevices",
    "StopHandyHAMP",
}
if required_calls - calls:
    raise RuntimeError(f"Source graph is missing toy transport calls: {sorted(required_calls - calls)}")

controls = [
    "ConnectLovenseToysButton",
    "ConnectMobileLovenseToysButton",
    "DisconnectLovenseToysButton",
    "HandyConnectButtonV2",
    "RefreshHandyConnectionButton",
    "SendHandyTestStrokesButton",
    "StopHandyStrokingButton",
    "IntifaceConnectButton",
    "DisconnectIntiface",
    "SendTestIntifaceButton",
    "RefreshIntifaceStatusButton",
    "RefreshLovenseConnectionsButton",
    "TestLovenseDevicesButton",
    "HandyKeyInputBox",
    "LovenseMobileIPInputBox",
    "LovenseMobilePortInputBox",
    "IntifaceServerAddressInputBox",
    "HandyStrokeRangeSlider",
    "IntifaceStrokeRangeSlider",
    "MaxVibrationIntensitySlider",
    "StrokeModeComboBox",
    "HandyConnectionStatus",
    "TextBlock_277",
    "IntifaceStatusText",
    "DevicesConnectedCountIntiface",
    "LovenseDevicesScrollbox",
    "IntifaceDevicesScrollbox",
]
if set(controls) - names:
    raise RuntimeError(f"Source widget is missing controls: {sorted(set(controls) - names)}")

animations = [
    "HandyConnectClick",
    "RefreshHandyClick",
    "HandyTestStrokesClick",
    "StopHandyStrokesClick",
    "ConnectLovenseViaPCClick",
    "ConnectMobileLovenseClick",
    "RefreshLovenseConnectionClick",
    "TestLovenseDevicesClick",
    "DisconnectLovenseToysClick",
]
if set(animations) - names:
    raise RuntimeError(f"Source widget is missing animations: {sorted(set(animations) - names)}")

save_keys = [
    "HandyKey",
    "LovenseIP",
    "LovensePort",
    "ButtplugURL",
    "HandyMaxStrokeLength",
    "MaxButtPlugVibratorIntensity",
    "StrokeModeFull?",
]
if set(save_keys) - fields:
    raise RuntimeError(f"Source graph is missing save fields: {sorted(set(save_keys) - fields)}")

status_functions = {
    "handy": read_json(widget_functions / "GetText.json"),
    "lovense": read_json(widget_functions / "GetText_0.json"),
    "intiface": read_json(widget_functions / "Get_IntifaceStatusText_Text.json"),
}
status_literals = {name: sorted(set(string_literals(payload))) for name, payload in status_functions.items()}
expected_status_literals = {
    "handy": {"Status: "},
    "lovense": {"Connected", "Disconnected", "Connection Status: {status}\r\n{devicecount} devices Connected"},
    "intiface": {"Status: Connected", "Status: Disconnected"},
}
for name, expected in expected_status_literals.items():
    if not expected.issubset(status_literals[name]):
        raise RuntimeError(f"Source {name} status text changed: {status_literals[name]}")

event_handlers = [
    "BndEvt__ToySettingsMenu_ConnectLovenseToysButton_K2Node_ComponentBoundEvent_12_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_ConnectMobileLovenseToysButton_K2Node_ComponentBoundEvent_0_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_DisconnectLovenseToysButton_K2Node_ComponentBoundEvent_15_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_HandyConnectButtonV2_K2Node_ComponentBoundEvent_8_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_RefreshHandyConnectionButton_K2Node_ComponentBoundEvent_9_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_SendHandyTestStrokesButton_K2Node_ComponentBoundEvent_10_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_StopHandyStrokingButton_K2Node_ComponentBoundEvent_11_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_IntifaceConnectButton_K2Node_ComponentBoundEvent_3_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_DisconnectIntiface_K2Node_ComponentBoundEvent_4_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_SendTestIntifaceButton_K2Node_ComponentBoundEvent_5_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_RefreshIntifaceStatusButton_K2Node_ComponentBoundEvent_18_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_RefreshLovenseConnectionsButton_K2Node_ComponentBoundEvent_13_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_TestLovenseDevicesButton_K2Node_ComponentBoundEvent_14_OnButtonClickedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_HandyStrokeRangeSlider_K2Node_ComponentBoundEvent_1_OnMouseCaptureEndEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_HandyStrokeRangeSlider_K2Node_ComponentBoundEvent_2_OnFloatValueChangedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_IntifaceStrokeRangeSlider_K2Node_ComponentBoundEvent_16_OnMouseCaptureEndEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_IntifaceStrokeRangeSlider_K2Node_ComponentBoundEvent_17_OnFloatValueChangedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_MaxVibrationIntensitySlider_K2Node_ComponentBoundEvent_6_OnMouseCaptureEndEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_MaxVibrationIntensitySlider_K2Node_ComponentBoundEvent_7_OnFloatValueChangedEvent__DelegateSignature.json",
    "BndEvt__ToySettingsMenu_StrokeModeComboBox_K2Node_ComponentBoundEvent_19_OnSelectionChangedEvent__DelegateSignature.json",
]
missing_handlers = [name for name in event_handlers if not (widget_functions / name).is_file()]
if missing_handlers:
    raise RuntimeError(f"Source widget event handlers are missing: {missing_handlers}")

native_contract_markers = {
    "lovense_beat_dispatch": "ExecuteLovenseHTTPBeatCommand",
    "lovense_per_beat_pulse": "SendLovensePulseForBeat",
    "lovense_inventory_parser": "ParseHTTPToysResponse",
    "lovense_test_dispatch": "SendTestVibration",
    "intiface_refresh": "RefreshButtplugDevices",
    "intiface_stop_all": 'L"StopAllDevices"',
    "intiface_pulse_clamp": "SetButtplugVibratorPulseDuration",
}
missing_native_markers = {
    name: marker
    for name, marker in native_contract_markers.items()
    if marker not in native_text
}
if missing_native_markers:
    raise RuntimeError(f"Native recovery markers are missing: {missing_native_markers}")

report = {
    "source_executed": False,
    "sources": {
        "widget_graph": str(graph_path),
        "widget_graph_sha256": sha256(graph_path),
        "widget_package": str(decoded_package),
        "widget_package_sha256": sha256(decoded_package),
    },
    "native_static_provenance": {
        "decompile": str(native_decompile),
        "decompile_sha256": sha256(native_decompile),
        "shipping_executable": str(shipping_executable),
        "shipping_executable_sha256": sha256(shipping_executable),
        "source_executed": False,
        "contract_markers": native_contract_markers,
    },
    "controls": controls,
    "animations": animations,
    "event_handlers": event_handlers,
    "save_keys": save_keys,
    "source_transport_calls": sorted(required_calls),
    "status_literals": status_literals,
    "defaults": {
        "HandyMaxStrokeLength": 1.0,
        "ButtplugURL": "ws://127.0.0.1:12345",
        "MaxButtPlugVibratorIntensity": 1.0,
        "StrokeModeFull?": True,
    },
    "native_transport_defaults": {
        "ButtplugVibratorIntensity": 1.0,
        "ButtplugVibratorPulseDurationSeconds": 0.25,
        "ButtplugReconnectDelaySeconds": 2.0,
        "ButtplugMaxReconnectAttempts": 5,
        "LovenseVibrationDurationSeconds": 0.25,
        "LovenseVibrationIntensity": 20,
    },
    "native_timing": {
        "buttplug_linear_min_duration_ms": 100,
        "full_cycle_return_delay": "duration_ms / 1000.0",
        "buttplug_vibration_stop_delay_seconds": 0.25,
        "refresh_scan_restart_delay_seconds": 0.1,
        "lovense_http": {
            "response_type": "OK",
            "active_status": 1,
            "vibrator_names": [
                "lush", "lush2", "lush3", "max", "max2", "max3", "gush",
                "domi", "domi2", "nora", "hush", "hush2", "ambi", "ferri",
                "dolce", "osci", "edge", "edge2", "osci2",
            ],
            "stroker_names": ["solace", "calor"],
            "thrusting_name_rules": ["machine", "contains:thrust", "contains:fuck"],
            "beat": {
                "command": "Function",
                "action": "Vibrate:15",
                "timeSec": 0,
                "stopPrevious": True,
                "apiVer": 1,
                "per_active_vibrator": True,
            },
            "continuous_threshold_seconds": 0.5,
            "continuous_post_stop_pulse_delay_seconds": 0.1,
            "test_actions": {
                "vibrator": {"action": "Vibrate:15", "timeSec": 3},
                "stroker": {"action": "Stroke:10,Thrusting:20", "timeSec": 0.3},
                "thrusting": {"action": "Thrusting:15", "timeSec": 3},
                "fallback": {"action": "Vibrate:10", "timeSec": 3},
            },
        },
    },
    "runtime_mapping": {
        "manager": "URecoveredDeviceManager",
        "widget": "URecoveredToySettingsMenu",
        "live_protocols": {
            "handy": "HTTPS Handy v2",
            "lovense_mobile": "HTTP /command",
            "intiface": "Buttplug WebSocket v3",
        },
        "beat_dispatch": "ARecoveredGlobalManager::HandleRecoveredDeviceBeat",
        "capability_routing": "ScalarCmd and LinearCmd are routed only to advertised Intiface devices",
        "lovense_http_inventory": "type=OK, data.toys object, status=1 records only",
        "lovense_http_beat": "per-vibrator Function/Vibrate:15, with recovered continuous-vibration threshold",
        "intiface_stop": "StopAllDevices envelope",
    },
}

destination = project / "RecoveryEvidence" / "toy-settings-parity-recovery.json"
destination.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
print(json.dumps(report, indent=2))
