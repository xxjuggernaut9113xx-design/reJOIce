#pragma once
#include "CoreMinimal.h"
#include "RecoveredDeviceInterface.generated.h"

class URecoveredSaveGame;

// Device interface: abstracts Handy/Lovense/Intiface hardware.
// Implementations stub the transport; hardware behavior needs real devices.
UENUM(BlueprintType)
enum class ERecoveredDeviceKind : uint8 {
    None UMETA(DisplayName="None"),
    Handy UMETA(DisplayName="Handy"),
    Lovense UMETA(DisplayName="Lovense"),
    Intiface UMETA(DisplayName="Intiface"),
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredDeviceConnection {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ERecoveredDeviceKind DeviceType = ERecoveredDeviceKind::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bConnected = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DeviceID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrentSpeed = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredDeviceConnectionChanged, ERecoveredDeviceKind, DeviceType, bool, bConnected);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredDeviceManager : public UObject {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") bool ConnectDevice(ERecoveredDeviceKind DeviceType, const FString& ConnectionInfo);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void DisconnectDevice(ERecoveredDeviceKind DeviceType);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") bool IsDeviceConnected(ERecoveredDeviceKind DeviceType) const;
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetDeviceSpeed(ERecoveredDeviceKind DeviceType, float Speed);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void StopDevice(ERecoveredDeviceKind DeviceType);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetStrokeRange(float MinPercent, float MaxPercent);
    // Persist device settings to/from the save game.
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SaveDeviceSettings(URecoveredSaveGame* Save);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void LoadDeviceSettings(URecoveredSaveGame* Save);
    UPROPERTY(BlueprintAssignable, Category="Recovered Devices") FRecoveredDeviceConnectionChanged OnDeviceStateChanged;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") TMap<ERecoveredDeviceKind, FRecoveredDeviceConnection> DeviceStates;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") float StrokeRangeMin = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") float StrokeRangeMax = 100.0f;
};
