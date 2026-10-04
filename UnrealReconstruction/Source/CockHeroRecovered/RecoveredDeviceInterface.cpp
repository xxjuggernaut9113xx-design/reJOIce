#include "RecoveredDeviceInterface.h"
#include "RecoveredRules.h"

bool URecoveredDeviceManager::ConnectDevice(ERecoveredDeviceKind DeviceType, const FString& ConnectionInfo) {
    if (DeviceType == ERecoveredDeviceKind::None) return false;
    // Transport stub: records the connection intent. No transport is implemented.
    // Never report a successful handshake until an actual transport confirms it.
    FRecoveredDeviceConnection& State = DeviceStates.FindOrAdd(DeviceType);
    State.DeviceType = DeviceType;
    State.DeviceID = ConnectionInfo;
    State.bConnected = false;
    State.CurrentSpeed = 0.0f;
    OnDeviceStateChanged.Broadcast(DeviceType, false);
    return false;
}

void URecoveredDeviceManager::DisconnectDevice(ERecoveredDeviceKind DeviceType) {
    if (auto* State = DeviceStates.Find(DeviceType)) {
        State->bConnected = false;
        State->CurrentSpeed = 0.0f;
    }
    OnDeviceStateChanged.Broadcast(DeviceType, false);
}

bool URecoveredDeviceManager::IsDeviceConnected(ERecoveredDeviceKind DeviceType) const {
    const auto* State = DeviceStates.Find(DeviceType);
    return State && State->bConnected;
}

void URecoveredDeviceManager::SetDeviceSpeed(ERecoveredDeviceKind DeviceType, float Speed) {
    if (auto* State = DeviceStates.Find(DeviceType)) {
        if (!State->bConnected) return;
        State->CurrentSpeed = FMath::Clamp(Speed, 0.0f, 1.0f);
        // Hardware command dispatch is a stub; the speed is recorded for UI.
    }
}

void URecoveredDeviceManager::StopDevice(ERecoveredDeviceKind DeviceType) {
    SetDeviceSpeed(DeviceType, 0.0f);
}

void URecoveredDeviceManager::SetStrokeRange(float MinPercent, float MaxPercent) {
    StrokeRangeMin = FMath::Clamp(MinPercent, 0.0f, 100.0f);
    StrokeRangeMax = FMath::Clamp(MaxPercent, StrokeRangeMin, 100.0f);
}

void URecoveredDeviceManager::SaveDeviceSettings(URecoveredSaveGame* Save) {
    if (!Save) return;
    // Persist stroke range and last-connected device types.
    Save->SetNumberSetting(TEXT("Device_StrokeRangeMin"), StrokeRangeMin);
    Save->SetNumberSetting(TEXT("Device_StrokeRangeMax"), StrokeRangeMax);
    TArray<FString> Connected;
    for (const auto& Pair : DeviceStates) {
        if (Pair.Value.bConnected) {
            Connected.Add(FString::Printf(TEXT("%d:%s"), static_cast<int32>(Pair.Key), *Pair.Value.DeviceID));
        }
    }
    Save->SetStringArraySetting(TEXT("Device_Connected"), Connected);
}

void URecoveredDeviceManager::LoadDeviceSettings(URecoveredSaveGame* Save) {
    if (!Save) return;
    StrokeRangeMin = Save->GetNumberSetting(TEXT("Device_StrokeRangeMin"), 0.0);
    StrokeRangeMax = Save->GetNumberSetting(TEXT("Device_StrokeRangeMax"), 100.0);
}
