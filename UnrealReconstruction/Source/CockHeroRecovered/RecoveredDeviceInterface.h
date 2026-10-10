#pragma once

#include "CoreMinimal.h"
#include "HttpFwd.h"
#include "RecoveredGameplay.h"
#include "TimerManager.h"
#include "RecoveredDeviceInterface.generated.h"

class URecoveredSaveGame;
class IWebSocket;
struct FRecoveredBeatEvent;
#if WITH_DEV_AUTOMATION_TESTS
class FRecoveredToySettingsParityTest;
#endif

UENUM(BlueprintType)
enum class ERecoveredDeviceKind : uint8 {
    None UMETA(DisplayName="None"),
    Handy UMETA(DisplayName="Handy"),
    Lovense UMETA(DisplayName="Lovense"),
    Intiface UMETA(DisplayName="Intiface"),
};

UENUM(BlueprintType)
enum class ERecoveredDeviceConnectionStatus : uint8 {
    Disconnected UMETA(DisplayName="Disconnected"),
    Connecting UMETA(DisplayName="Connecting"),
    Connected UMETA(DisplayName="Connected"),
    Error UMETA(DisplayName="Error"),
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredDeviceConnection {
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite) ERecoveredDeviceKind DeviceType = ERecoveredDeviceKind::None;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) ERecoveredDeviceConnectionStatus Status = ERecoveredDeviceConnectionStatus::Disconnected;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bConnected = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DeviceID;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString Endpoint;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FString LastError;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) TArray<FString> DeviceNames;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) float CurrentSpeed = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasVibrators = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bHasStrokers = false;
};

struct FRecoveredLovenseHttpToy {
    FString Id;
    FString Name;
    FString NickName;
    int32 Battery = 0;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredDeviceConnectionChanged, ERecoveredDeviceKind, DeviceType, bool, bConnected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredDeviceConnectionUpdated, const FRecoveredDeviceConnection&, Connection);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredDeviceManager : public UObject {
    GENERATED_BODY()
public:
    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintCallable, Category="Recovered Devices") bool ConnectDevice(ERecoveredDeviceKind DeviceType, const FString& ConnectionInfo);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") bool RefreshDevice(ERecoveredDeviceKind DeviceType);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void DisconnectDevice(ERecoveredDeviceKind DeviceType);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") bool IsDeviceConnected(ERecoveredDeviceKind DeviceType) const;
    UFUNCTION(BlueprintPure, Category="Recovered Devices") ERecoveredDeviceConnectionStatus GetDeviceConnectionStatus(ERecoveredDeviceKind DeviceType) const;
    UFUNCTION(BlueprintPure, Category="Recovered Devices") FRecoveredDeviceConnection GetDeviceConnection(ERecoveredDeviceKind DeviceType) const;
    UFUNCTION(BlueprintPure, Category="Recovered Devices") TArray<FString> GetConnectedDeviceNames(ERecoveredDeviceKind DeviceType) const;
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetDeviceSpeed(ERecoveredDeviceKind DeviceType, float Speed);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void StopDevice(ERecoveredDeviceKind DeviceType);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SendTestCommand(ERecoveredDeviceKind DeviceType);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetStrokeRange(float MinPercent, float MaxPercent);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetVibratorIntensity(float Intensity);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetIntifaceVibratorPulseDuration(float DurationSeconds);
    UFUNCTION(BlueprintCallable, Category="Recovered Devices") void SetFullStrokePerBeat(bool bEnabled);
    UFUNCTION(BlueprintPure, Category="Recovered Devices") FRecoveredDeviceState GetGameplayDeviceState() const;
    UFUNCTION(BlueprintPure, Category="Recovered Devices") FString GetConnectionStatusLabel(ERecoveredDeviceKind DeviceType) const;
    UFUNCTION(BlueprintPure, Category="Recovered Devices") static FString BuildLovenseEndpoint(const FString& Host, int32 Port);
    UFUNCTION(BlueprintPure, Category="Recovered Devices") static FString NormalizeIntifaceEndpoint(const FString& Endpoint);

    void DispatchBeat(const FRecoveredBeatEvent& Event);
    void DispatchBeatHitCenter(const FRecoveredBeatEvent& Event);
    void SaveDeviceSettings(URecoveredSaveGame* Save);
    void LoadDeviceSettings(URecoveredSaveGame* Save);

    UPROPERTY(BlueprintAssignable, Category="Recovered Devices") FRecoveredDeviceConnectionChanged OnDeviceStateChanged;
    UPROPERTY(BlueprintAssignable, Category="Recovered Devices") FRecoveredDeviceConnectionUpdated OnDeviceConnectionUpdated;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") TMap<ERecoveredDeviceKind, FRecoveredDeviceConnection> DeviceStates;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") float StrokeRangeMin = 0.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") float StrokeRangeMax = 100.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") float MaximumVibratorIntensity = 1.0f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices", meta=(ClampMin="0.05", ClampMax="2.0")) float IntifaceVibratorPulseDuration = 0.25f;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") bool bFullStrokePerBeat = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices") bool bAutoReconnectIntiface = true;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices", meta=(ClampMin="0")) int32 MaxIntifaceReconnectAttempts = 5;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Devices", meta=(ClampMin="0.1")) float IntifaceReconnectBaseDelaySeconds = 2.0f;

private:
#if WITH_DEV_AUTOMATION_TESTS
    friend class FRecoveredToySettingsParityTest;
#endif
    FRecoveredDeviceConnection& GetOrCreateConnection(ERecoveredDeviceKind DeviceType);
    const FRecoveredDeviceConnection* FindConnection(ERecoveredDeviceKind DeviceType) const;
    void SetConnectionState(ERecoveredDeviceKind DeviceType, ERecoveredDeviceConnectionStatus Status, const FString& Error = FString());
    bool ConnectHandy(const FString& ConnectionKey);
    bool ConnectLovenseHttp(const FString& Endpoint);
    bool ConnectIntiface(const FString& Endpoint, bool bResetReconnectAttempts = true);
    void ClearIntifaceSocket(bool bCloseSocket);
    void ResetIntifaceRuntimeState();
    void ScheduleIntifaceReconnect();
    void ReconnectIntiface();
    void QueueIntifaceFullStrokeReturn(int32 DurationMs);
    void ScheduleIntifaceVibrationStop();
    void ScheduleIntifaceScanRestart();
    void QueueLovensePulseAfterContinuousStop();
    bool SendHandyRequest(const FString& Route, const FString& Verb, const FString& Payload, bool bConnectionCheck);
    bool SendLovenseCommand(const FString& Payload, bool bConnectionCheck, bool bParseToysResponse = false);
    void SendIntifaceHandshake();
    void SendIntifaceDeviceListRequest();
    void SendIntifaceStartScanning();
    void SendIntifaceStopScanning();
    void SendIntifaceScalar(float Intensity);
    void SendIntifaceLinear(float Position, int32 DurationMs);
    void SendIntifaceStop();
    void SendIntifaceJson(const TSharedRef<class FJsonObject>& Envelope);
    void HandleHandyResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded, bool bConnectionCheck);
    void HandleLovenseResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded, bool bConnectionCheck, bool bParseToysResponse);
    void HandleIntifaceConnected();
    void HandleIntifaceConnectionError(const FString& Error);
    void HandleIntifaceClosed(int32 StatusCode, const FString& Reason, bool bWasClean);
    void HandleIntifaceMessage(const FString& Message);
    void UpdateIntifaceDevices(const TSharedPtr<class FJsonObject>& Payload);
    void UpdateIntifaceDeviceCapabilities(int32 DeviceIndex, const TSharedPtr<class FJsonObject>& DeviceMessages);
    void RefreshIntifaceConnection();
    void SendHandyStroke(bool bForward, int32 DurationMs);
    void SendLovensePulse(float Intensity, float DurationSeconds);
    void SendLovenseBeatPulses();
    void StartLovenseContinuousVibration(float IntervalSeconds);
    void StopLovenseContinuousVibration();
    void SendLovenseTestCommands();
    bool SendLovenseFunctionCommand(const FString& ToyId, const FString& Action, float DurationSeconds, bool bStopPrevious);
    static TSharedRef<class FJsonObject> BuildLovenseFunctionCommand(const FString& ToyId, const FString& Action, float DurationSeconds, bool bStopPrevious);
    static bool ParseLovenseToysResponse(const TSharedPtr<class FJsonObject>& Payload, TArray<FRecoveredLovenseHttpToy>& OutToys);
    static bool IsLovenseHttpVibrator(const FString& Name);
    static bool IsLovenseHttpStroker(const FString& Name);
    static bool IsLovenseHttpThrusting(const FString& Name);
    FString GetHandyUrl(const FString& Route) const;
    FString GetLovenseEndpoint() const;
    static FString SerializeJsonObject(const TSharedRef<class FJsonObject>& Object);
    static bool DeserializeJsonObject(const FString& Text, TSharedPtr<class FJsonObject>& OutObject);
    static FString GetHttpError(FHttpResponsePtr Response, bool bSucceeded);

    FString HandyConnectionKey;
    FString LovenseHttpEndpoint;
    FString LovenseHost;
    int32 LovensePort = 0;
    TArray<FRecoveredLovenseHttpToy> LovenseHttpToys;
    TSharedPtr<IWebSocket> IntifaceSocket;
    TMap<int32, FString> IntifaceDevices;
    TMap<int32, TArray<int32>> IntifaceVibratorFeatures;
    TMap<int32, TArray<int32>> IntifaceStrokerFeatures;
    TMap<int32, bool> PendingBeatDirections;
    FTimerHandle IntifaceReconnectTimer;
    int32 NextIntifaceMessageId = 1;
    int32 IntifaceReconnectAttempts = 0;
    bool bIntifaceReconnectWanted = false;
    bool bLovenseContinuousVibration = false;
    bool bNextStrokeForward = true;
};
