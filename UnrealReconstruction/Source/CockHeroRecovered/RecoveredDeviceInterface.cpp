#include "RecoveredDeviceInterface.h"

#include "RecoveredBeatTimeline.h"
#include "RecoveredRules.h"
#include "Dom/JsonObject.h"
#include "Engine/World.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "IWebSocket.h"
#include "Modules/ModuleManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "WebSocketsModule.h"

namespace {
const FString HandyBaseUrl = TEXT("https://www.handyfeeling.com/api/handy/v2/");
const FString LovenseGetToysCommand = TEXT("GetToys");
const FString LovenseFunctionCommand = TEXT("Function");

bool IsSuccessfulResponse(const FHttpResponsePtr& Response, bool bSucceeded) {
    return bSucceeded && Response.IsValid() && EHttpResponseCodes::IsOk(Response->GetResponseCode());
}

void AddUniqueName(TArray<FString>& Names, const FString& Name) {
    const FString Trimmed = Name.TrimStartAndEnd();
    if (!Trimmed.IsEmpty()) Names.AddUnique(Trimmed);
}

TArray<int32> GetIntifaceFeatureIndices(const TSharedPtr<FJsonObject>& DeviceMessages, const TCHAR* CommandName, bool bRequireVibrate) {
    TArray<int32> Indices;
    if (!DeviceMessages.IsValid()) return Indices;

    const TArray<TSharedPtr<FJsonValue>>* Features = nullptr;
    if (DeviceMessages->TryGetArrayField(CommandName, Features) && Features) {
        for (int32 ArrayIndex = 0; ArrayIndex < Features->Num(); ++ArrayIndex) {
            const TSharedPtr<FJsonValue>& Value = (*Features)[ArrayIndex];
            const TSharedPtr<FJsonObject>* FeaturePtr = nullptr;
            if (!Value.IsValid() || !Value->TryGetObject(FeaturePtr) || !FeaturePtr || !FeaturePtr->IsValid()) continue;
            const TSharedPtr<FJsonObject>& Feature = *FeaturePtr;
            FString ActuatorType;
            Feature->TryGetStringField(TEXT("ActuatorType"), ActuatorType);
            if (bRequireVibrate && !ActuatorType.Equals(TEXT("Vibrate"), ESearchCase::IgnoreCase)) continue;
            double FeatureIndex = ArrayIndex;
            Feature->TryGetNumberField(TEXT("Index"), FeatureIndex);
            const int32 ParsedIndex = FMath::RoundToInt(FeatureIndex);
            if (ParsedIndex >= 0) Indices.AddUnique(ParsedIndex);
        }
        return Indices;
    }

    const TSharedPtr<FJsonObject>* Capability = nullptr;
    if (!DeviceMessages->TryGetObjectField(CommandName, Capability) || !Capability || !Capability->IsValid()) return Indices;
    FString ActuatorType;
    (*Capability)->TryGetStringField(TEXT("ActuatorType"), ActuatorType);
    if (bRequireVibrate && !ActuatorType.Equals(TEXT("Vibrate"), ESearchCase::IgnoreCase)) return Indices;
    double FeatureCount = 0;
    if ((*Capability)->TryGetNumberField(TEXT("FeatureCount"), FeatureCount)) {
        for (int32 FeatureIndex = 0; FeatureIndex < FMath::Max(FMath::RoundToInt(FeatureCount), 0); ++FeatureIndex) Indices.Add(FeatureIndex);
        return Indices;
    }
    double FeatureIndex = 0;
    (*Capability)->TryGetNumberField(TEXT("Index"), FeatureIndex);
    if (FeatureIndex >= 0) Indices.Add(FMath::RoundToInt(FeatureIndex));
    return Indices;
}

FString GetJsonString(const TSharedPtr<FJsonObject>& Object, const TCHAR* Field, const FString& Fallback = FString()) {
    FString Result;
    return Object.IsValid() && Object->TryGetStringField(Field, Result) ? Result : Fallback;
}

bool JsonObjectHasCommand(const TSharedPtr<FJsonObject>& Object, const TCHAR* CommandName, const TSharedPtr<FJsonObject>*& OutPayload) {
    OutPayload = nullptr;
    return Object.IsValid() && Object->TryGetObjectField(CommandName, OutPayload) && OutPayload && OutPayload->IsValid();
}

void ExtractLovenseHostAndPort(const FString& Endpoint, FString& OutHost, int32& OutPort) {
    OutHost.Reset();
    OutPort = 0;
    FString Authority = Endpoint.TrimStartAndEnd();
    Authority.RemoveFromStart(TEXT("http://"), ESearchCase::IgnoreCase);
    Authority.RemoveFromStart(TEXT("https://"), ESearchCase::IgnoreCase);
    int32 SlashIndex = INDEX_NONE;
    if (Authority.FindChar(TEXT('/'), SlashIndex)) Authority = Authority.Left(SlashIndex);
    int32 ColonIndex = INDEX_NONE;
    if (Authority.FindLastChar(TEXT(':'), ColonIndex)) {
        const FString PortText = Authority.Mid(ColonIndex + 1);
        if (LexTryParseString(OutPort, *PortText)) {
            OutHost = Authority.Left(ColonIndex);
            return;
        }
    }
    OutHost = Authority;
}
}

void URecoveredDeviceManager::BeginDestroy() {
    bIntifaceReconnectWanted = false;
    if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(IntifaceReconnectTimer);
    ClearIntifaceSocket(true);
    Super::BeginDestroy();
}

FRecoveredDeviceConnection& URecoveredDeviceManager::GetOrCreateConnection(ERecoveredDeviceKind DeviceType) {
    FRecoveredDeviceConnection& Connection = DeviceStates.FindOrAdd(DeviceType);
    Connection.DeviceType = DeviceType;
    return Connection;
}

const FRecoveredDeviceConnection* URecoveredDeviceManager::FindConnection(ERecoveredDeviceKind DeviceType) const {
    return DeviceStates.Find(DeviceType);
}

void URecoveredDeviceManager::ClearIntifaceSocket(bool bCloseSocket) {
    if (!IntifaceSocket.IsValid()) return;
    const TSharedPtr<IWebSocket> Socket = IntifaceSocket;
    Socket->OnConnected().RemoveAll(this);
    Socket->OnConnectionError().RemoveAll(this);
    Socket->OnClosed().RemoveAll(this);
    Socket->OnMessage().RemoveAll(this);
    IntifaceSocket.Reset();
    if (bCloseSocket) Socket->Close();
}

void URecoveredDeviceManager::ResetIntifaceRuntimeState() {
    IntifaceDevices.Reset();
    IntifaceVibratorFeatures.Reset();
    IntifaceStrokerFeatures.Reset();
    PendingBeatDirections.Reset();
    NextIntifaceMessageId = 1;
}

void URecoveredDeviceManager::ScheduleIntifaceReconnect() {
    if (!bAutoReconnectIntiface || !bIntifaceReconnectWanted || MaxIntifaceReconnectAttempts <= 0 || IntifaceReconnectAttempts >= MaxIntifaceReconnectAttempts) return;
    const FRecoveredDeviceConnection* Connection = FindConnection(ERecoveredDeviceKind::Intiface);
    if (!Connection || Connection->Endpoint.IsEmpty()) return;
    UWorld* World = GetWorld();
    if (!World) return;
    FTimerManager& Timers = World->GetTimerManager();
    if (Timers.IsTimerActive(IntifaceReconnectTimer)) return;
    ++IntifaceReconnectAttempts;
    const float Delay = FMath::Max(IntifaceReconnectBaseDelaySeconds * static_cast<float>(IntifaceReconnectAttempts), 0.1f);
    Timers.SetTimer(IntifaceReconnectTimer, this, &URecoveredDeviceManager::ReconnectIntiface, Delay, false);
}

void URecoveredDeviceManager::ReconnectIntiface() {
    if (!bIntifaceReconnectWanted) return;
    const FRecoveredDeviceConnection* Connection = FindConnection(ERecoveredDeviceKind::Intiface);
    if (!Connection || Connection->Endpoint.IsEmpty()) return;
    ConnectIntiface(Connection->Endpoint, false);
}

void URecoveredDeviceManager::QueueIntifaceFullStrokeReturn(int32 DurationMs) {
    UWorld* World = GetWorld();
    if (!World) return;
    FTimerDelegate ReturnStroke;
    ReturnStroke.BindUObject(this, &URecoveredDeviceManager::SendIntifaceLinear, StrokeRangeMax / 100.0f, DurationMs);
    FTimerHandle ReturnTimer;
    World->GetTimerManager().SetTimer(ReturnTimer, ReturnStroke, FMath::Max(static_cast<float>(DurationMs) / 1000.0f, 0.1f), false);
}

void URecoveredDeviceManager::ScheduleIntifaceVibrationStop() {
    UWorld* World = GetWorld();
    if (!World) return;
    FTimerDelegate StopDelegate;
    StopDelegate.BindUObject(this, &URecoveredDeviceManager::SendIntifaceStop);
    FTimerHandle StopTimer;
    World->GetTimerManager().SetTimer(StopTimer, StopDelegate, IntifaceVibratorPulseDuration, false);
}

void URecoveredDeviceManager::ScheduleIntifaceScanRestart() {
    UWorld* World = GetWorld();
    if (!World) return;
    FTimerDelegate RestartDelegate;
    RestartDelegate.BindUObject(this, &URecoveredDeviceManager::SendIntifaceStartScanning);
    FTimerHandle RestartTimer;
    World->GetTimerManager().SetTimer(RestartTimer, RestartDelegate, 0.1f, false);
}

void URecoveredDeviceManager::QueueLovensePulseAfterContinuousStop() {
    UWorld* World = GetWorld();
    if (!World) return;
    FTimerDelegate PulseDelegate;
    PulseDelegate.BindUObject(this, &URecoveredDeviceManager::SendLovenseBeatPulses);
    FTimerHandle PulseTimer;
    World->GetTimerManager().SetTimer(PulseTimer, PulseDelegate, 0.1f, false);
}

void URecoveredDeviceManager::SetConnectionState(ERecoveredDeviceKind DeviceType, ERecoveredDeviceConnectionStatus Status, const FString& Error) {
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(DeviceType);
    Connection.Status = Status;
    Connection.bConnected = Status == ERecoveredDeviceConnectionStatus::Connected;
    if (Status == ERecoveredDeviceConnectionStatus::Disconnected) {
        Connection.CurrentSpeed = 0.0f;
        Connection.DeviceNames.Reset();
        Connection.bHasVibrators = false;
        Connection.bHasStrokers = false;
        Connection.LastError.Reset();
    } else if (!Error.IsEmpty()) {
        Connection.LastError = Error;
    } else if (Status == ERecoveredDeviceConnectionStatus::Connecting || Status == ERecoveredDeviceConnectionStatus::Connected) {
        Connection.LastError.Reset();
    }
    OnDeviceStateChanged.Broadcast(DeviceType, Connection.bConnected);
    OnDeviceConnectionUpdated.Broadcast(Connection);
}

FString URecoveredDeviceManager::BuildLovenseEndpoint(const FString& Host, int32 Port) {
    FString Result = Host.TrimStartAndEnd();
    if (Result.IsEmpty() || Port < 1 || Port > 65535) return FString();
    if (!Result.StartsWith(TEXT("http://"), ESearchCase::IgnoreCase) && !Result.StartsWith(TEXT("https://"), ESearchCase::IgnoreCase)) {
        Result = TEXT("http://") + Result;
    }
    while (Result.EndsWith(TEXT("/"))) Result.LeftChopInline(1);
    if (Result.EndsWith(TEXT("/command"), ESearchCase::IgnoreCase)) return Result;

    FString Authority = Result;
    Authority.RemoveFromStart(TEXT("http://"), ESearchCase::IgnoreCase);
    Authority.RemoveFromStart(TEXT("https://"), ESearchCase::IgnoreCase);
    int32 SlashIndex = INDEX_NONE;
    if (Authority.FindChar(TEXT('/'), SlashIndex)) Authority = Authority.Left(SlashIndex);
    int32 ExistingPort = INDEX_NONE;
    if (Authority.FindLastChar(TEXT(':'), ExistingPort) && ExistingPort < Authority.Len() - 1) {
        int32 ParsedPort = 0;
        if (LexTryParseString(ParsedPort, *Authority.Mid(ExistingPort + 1)) && ParsedPort > 0) return Result + TEXT("/command");
    }
    return FString::Printf(TEXT("%s:%d/command"), *Result, Port);
}

FString URecoveredDeviceManager::NormalizeIntifaceEndpoint(const FString& Endpoint) {
    FString Result = Endpoint.TrimStartAndEnd();
    if (Result.IsEmpty()) return FString();
    if (!Result.StartsWith(TEXT("ws://"), ESearchCase::IgnoreCase) && !Result.StartsWith(TEXT("wss://"), ESearchCase::IgnoreCase)) {
        Result = TEXT("ws://") + Result;
    }
    while (Result.EndsWith(TEXT("/"))) Result.LeftChopInline(1);
    return Result;
}

bool URecoveredDeviceManager::ConnectDevice(ERecoveredDeviceKind DeviceType, const FString& ConnectionInfo) {
    if (DeviceType == ERecoveredDeviceKind::None) return false;
    switch (DeviceType) {
    case ERecoveredDeviceKind::Handy:
        return ConnectHandy(ConnectionInfo);
    case ERecoveredDeviceKind::Lovense:
        return ConnectLovenseHttp(ConnectionInfo);
    case ERecoveredDeviceKind::Intiface:
        return ConnectIntiface(ConnectionInfo);
    default:
        return false;
    }
}

bool URecoveredDeviceManager::RefreshDevice(ERecoveredDeviceKind DeviceType) {
    switch (DeviceType) {
    case ERecoveredDeviceKind::Handy:
        return IsDeviceConnected(ERecoveredDeviceKind::Handy) && SendHandyRequest(TEXT("status"), TEXT("GET"), FString(), true);
    case ERecoveredDeviceKind::Lovense: {
        if (!IsDeviceConnected(ERecoveredDeviceKind::Lovense)) return false;
        auto Payload = MakeShared<FJsonObject>();
        Payload->SetStringField(TEXT("command"), LovenseGetToysCommand);
        Payload->SetNumberField(TEXT("apiVer"), 1);
        return SendLovenseCommand(SerializeJsonObject(Payload), false, true);
    }
    case ERecoveredDeviceKind::Intiface: {
        const FRecoveredDeviceConnection* Connection = FindConnection(DeviceType);
        if (!Connection || !Connection->bConnected || !IntifaceSocket.IsValid() || !IntifaceSocket->IsConnected()) return false;
        SendIntifaceStopScanning();
        SendIntifaceDeviceListRequest();
        ScheduleIntifaceScanRestart();
        return true;
    }
    default:
        return false;
    }
}

bool URecoveredDeviceManager::ConnectHandy(const FString& ConnectionKey) {
    const FString Key = ConnectionKey.TrimStartAndEnd();
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(ERecoveredDeviceKind::Handy);
    Connection.Endpoint = HandyBaseUrl;
    Connection.DeviceID = TEXT("Handy");
    if (Key.Len() < 2) {
        SetConnectionState(ERecoveredDeviceKind::Handy, ERecoveredDeviceConnectionStatus::Error, TEXT("Connection key is empty"));
        return false;
    }
    HandyConnectionKey = Key;
    SetConnectionState(ERecoveredDeviceKind::Handy, ERecoveredDeviceConnectionStatus::Connecting);
    if (SendHandyRequest(TEXT("info"), TEXT("GET"), FString(), true)) return true;
    SetConnectionState(ERecoveredDeviceKind::Handy, ERecoveredDeviceConnectionStatus::Error, TEXT("Unable to dispatch Handy connection request"));
    return false;
}

bool URecoveredDeviceManager::ConnectLovenseHttp(const FString& Endpoint) {
    const FString Normalized = Endpoint.TrimStartAndEnd();
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(ERecoveredDeviceKind::Lovense);
    Connection.Endpoint = Normalized;
    if (!Normalized.StartsWith(TEXT("http://"), ESearchCase::IgnoreCase) && !Normalized.StartsWith(TEXT("https://"), ESearchCase::IgnoreCase)) {
        SetConnectionState(ERecoveredDeviceKind::Lovense, ERecoveredDeviceConnectionStatus::Error, TEXT("Lovense requires a valid HTTP LAN endpoint"));
        return false;
    }
    LovenseHttpEndpoint = Normalized;
    ExtractLovenseHostAndPort(Normalized, LovenseHost, LovensePort);
    LovenseHttpToys.Reset();
    bLovenseContinuousVibration = false;
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetStringField(TEXT("command"), LovenseGetToysCommand);
    Payload->SetNumberField(TEXT("apiVer"), 1);
    SetConnectionState(ERecoveredDeviceKind::Lovense, ERecoveredDeviceConnectionStatus::Connecting);
    if (SendLovenseCommand(SerializeJsonObject(Payload), true, true)) return true;
    SetConnectionState(ERecoveredDeviceKind::Lovense, ERecoveredDeviceConnectionStatus::Error, TEXT("Unable to dispatch Lovense connection request"));
    return false;
}

bool URecoveredDeviceManager::ConnectIntiface(const FString& Endpoint, bool bResetReconnectAttempts) {
    const FString Normalized = NormalizeIntifaceEndpoint(Endpoint);
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(ERecoveredDeviceKind::Intiface);
    Connection.Endpoint = Normalized;
    if (Normalized.IsEmpty()) {
        bIntifaceReconnectWanted = false;
        IntifaceReconnectAttempts = 0;
        if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(IntifaceReconnectTimer);
        SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, TEXT("Intiface server address is empty"));
        return false;
    }
#if WITH_WEBSOCKETS
    bIntifaceReconnectWanted = true;
    if (bResetReconnectAttempts) {
        IntifaceReconnectAttempts = 0;
        if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(IntifaceReconnectTimer);
    }
    ClearIntifaceSocket(true);
    ResetIntifaceRuntimeState();
    SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Connecting);
    FWebSocketsModule& WebSockets = FModuleManager::LoadModuleChecked<FWebSocketsModule>(TEXT("WebSockets"));
    IntifaceSocket = WebSockets.CreateWebSocket(Normalized);
    IntifaceSocket->OnConnected().AddUObject(this, &URecoveredDeviceManager::HandleIntifaceConnected);
    IntifaceSocket->OnConnectionError().AddUObject(this, &URecoveredDeviceManager::HandleIntifaceConnectionError);
    IntifaceSocket->OnClosed().AddUObject(this, &URecoveredDeviceManager::HandleIntifaceClosed);
    IntifaceSocket->OnMessage().AddUObject(this, &URecoveredDeviceManager::HandleIntifaceMessage);
    IntifaceSocket->Connect();
    return true;
#else
    SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, TEXT("WebSocket transport is unavailable in this build"));
    return false;
#endif
}

void URecoveredDeviceManager::DisconnectDevice(ERecoveredDeviceKind DeviceType) {
    if (DeviceType == ERecoveredDeviceKind::None) return;
    if (DeviceType == ERecoveredDeviceKind::Lovense) {
        if (IsDeviceConnected(ERecoveredDeviceKind::Lovense)) StopLovenseContinuousVibration();
        LovenseHttpToys.Reset();
        bLovenseContinuousVibration = false;
    }
    if (DeviceType == ERecoveredDeviceKind::Intiface) {
        bIntifaceReconnectWanted = false;
        IntifaceReconnectAttempts = 0;
        if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(IntifaceReconnectTimer);
        ClearIntifaceSocket(true);
        ResetIntifaceRuntimeState();
    }
    SetConnectionState(DeviceType, ERecoveredDeviceConnectionStatus::Disconnected);
}

bool URecoveredDeviceManager::IsDeviceConnected(ERecoveredDeviceKind DeviceType) const {
    const FRecoveredDeviceConnection* Connection = FindConnection(DeviceType);
    return Connection && Connection->bConnected;
}

ERecoveredDeviceConnectionStatus URecoveredDeviceManager::GetDeviceConnectionStatus(ERecoveredDeviceKind DeviceType) const {
    const FRecoveredDeviceConnection* Connection = FindConnection(DeviceType);
    return Connection ? Connection->Status : ERecoveredDeviceConnectionStatus::Disconnected;
}

FRecoveredDeviceConnection URecoveredDeviceManager::GetDeviceConnection(ERecoveredDeviceKind DeviceType) const {
    const FRecoveredDeviceConnection* Connection = FindConnection(DeviceType);
    return Connection ? *Connection : FRecoveredDeviceConnection();
}

TArray<FString> URecoveredDeviceManager::GetConnectedDeviceNames(ERecoveredDeviceKind DeviceType) const {
    const FRecoveredDeviceConnection* Connection = FindConnection(DeviceType);
    return Connection ? Connection->DeviceNames : TArray<FString>();
}

FString URecoveredDeviceManager::GetConnectionStatusLabel(ERecoveredDeviceKind DeviceType) const {
    switch (GetDeviceConnectionStatus(DeviceType)) {
    case ERecoveredDeviceConnectionStatus::Connecting:
        return TEXT("Connecting");
    case ERecoveredDeviceConnectionStatus::Connected:
        return TEXT("Connected");
    case ERecoveredDeviceConnectionStatus::Error:
        return TEXT("Error");
    default:
        return TEXT("Disconnected");
    }
}

void URecoveredDeviceManager::SetDeviceSpeed(ERecoveredDeviceKind DeviceType, float Speed) {
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(DeviceType);
    Connection.CurrentSpeed = FMath::Clamp(Speed, 0.0f, 1.0f);
    OnDeviceConnectionUpdated.Broadcast(Connection);
    if (!Connection.bConnected) return;
    switch (DeviceType) {
    case ERecoveredDeviceKind::Handy: {
        auto Payload = MakeShared<FJsonObject>();
        Payload->SetNumberField(TEXT("velocity"), FMath::RoundToInt(Connection.CurrentSpeed * 100.0f));
        SendHandyRequest(TEXT("hamp/velocity"), TEXT("PUT"), SerializeJsonObject(Payload), false);
        break;
    }
    case ERecoveredDeviceKind::Lovense:
        SendLovensePulse(Connection.CurrentSpeed, 0.25f);
        break;
    case ERecoveredDeviceKind::Intiface:
        SendIntifaceScalar(Connection.CurrentSpeed * MaximumVibratorIntensity);
        break;
    default:
        break;
    }
}

void URecoveredDeviceManager::StopDevice(ERecoveredDeviceKind DeviceType) {
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(DeviceType);
    Connection.CurrentSpeed = 0.0f;
    OnDeviceConnectionUpdated.Broadcast(Connection);
    if (!Connection.bConnected) return;
    switch (DeviceType) {
    case ERecoveredDeviceKind::Handy:
        SendHandyRequest(TEXT("hamp/stop"), TEXT("PUT"), TEXT("{}"), false);
        break;
    case ERecoveredDeviceKind::Lovense:
        StopLovenseContinuousVibration();
        bLovenseContinuousVibration = false;
        break;
    case ERecoveredDeviceKind::Intiface:
        SendIntifaceStop();
        break;
    default:
        break;
    }
}

void URecoveredDeviceManager::SendTestCommand(ERecoveredDeviceKind DeviceType) {
    switch (DeviceType) {
    case ERecoveredDeviceKind::Handy: {
        if (!IsDeviceConnected(DeviceType)) return;
        auto Payload = MakeShared<FJsonObject>();
        Payload->SetNumberField(TEXT("position"), FMath::RoundToInt(StrokeRangeMax));
        Payload->SetNumberField(TEXT("duration"), 500);
        SendHandyRequest(TEXT("hdsp/xpt"), TEXT("PUT"), SerializeJsonObject(Payload), false);
        break;
    }
    case ERecoveredDeviceKind::Lovense:
        SendLovenseTestCommands();
        break;
    case ERecoveredDeviceKind::Intiface:
        if (const FRecoveredDeviceConnection* Connection = FindConnection(ERecoveredDeviceKind::Intiface)) {
            if (Connection->bConnected && Connection->bHasStrokers) {
                SendIntifaceLinear(StrokeRangeMin / 100.0f, 500);
                QueueIntifaceFullStrokeReturn(500);
            }
            if (Connection->bConnected && Connection->bHasVibrators) {
                SendIntifaceScalar(MaximumVibratorIntensity);
                ScheduleIntifaceVibrationStop();
            }
        }
        break;
    default:
        break;
    }
}

void URecoveredDeviceManager::SetStrokeRange(float MinPercent, float MaxPercent) {
    StrokeRangeMin = FMath::Clamp(MinPercent, 0.0f, 100.0f);
    StrokeRangeMax = FMath::Clamp(MaxPercent, StrokeRangeMin, 100.0f);
    if (FRecoveredDeviceConnection* Connection = DeviceStates.Find(ERecoveredDeviceKind::Intiface)) {
        OnDeviceConnectionUpdated.Broadcast(*Connection);
    }
}

void URecoveredDeviceManager::SetVibratorIntensity(float Intensity) {
    MaximumVibratorIntensity = FMath::Clamp(Intensity, 0.0f, 1.0f);
    if (FRecoveredDeviceConnection* Connection = DeviceStates.Find(ERecoveredDeviceKind::Intiface)) {
        OnDeviceConnectionUpdated.Broadcast(*Connection);
    }
}

void URecoveredDeviceManager::SetIntifaceVibratorPulseDuration(float DurationSeconds) {
    IntifaceVibratorPulseDuration = FMath::Clamp(DurationSeconds, 0.05f, 2.0f);
}

void URecoveredDeviceManager::SetFullStrokePerBeat(bool bEnabled) {
    bFullStrokePerBeat = bEnabled;
}

FRecoveredDeviceState URecoveredDeviceManager::GetGameplayDeviceState() const {
    FRecoveredDeviceState State;
    State.bHandy = IsDeviceConnected(ERecoveredDeviceKind::Handy);
    State.bLovense = IsDeviceConnected(ERecoveredDeviceKind::Lovense);
    if (const FRecoveredDeviceConnection* Intiface = FindConnection(ERecoveredDeviceKind::Intiface)) {
        State.bButtplugVibrators = Intiface->bConnected && Intiface->bHasVibrators;
        State.bButtplugStrokers = Intiface->bConnected && Intiface->bHasStrokers;
    }
    State.bFullStrokePerBeat = bFullStrokePerBeat;
    return State;
}

FString URecoveredDeviceManager::GetHandyUrl(const FString& Route) const {
    FString RelativeRoute = Route.TrimStartAndEnd();
    RelativeRoute.RemoveFromStart(TEXT("/"));
    return HandyBaseUrl + RelativeRoute;
}

FString URecoveredDeviceManager::GetLovenseEndpoint() const {
    return LovenseHttpEndpoint;
}

bool URecoveredDeviceManager::SendHandyRequest(const FString& Route, const FString& Verb, const FString& Payload, bool bConnectionCheck) {
    if (HandyConnectionKey.Len() < 2) return false;
    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(GetHandyUrl(Route));
    Request->SetVerb(Verb);
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetHeader(TEXT("X-Connection-Key"), HandyConnectionKey);
    if (!Payload.IsEmpty()) Request->SetContentAsString(Payload);
    Request->OnProcessRequestComplete().BindUObject(this, &URecoveredDeviceManager::HandleHandyResponse, bConnectionCheck);
    return Request->ProcessRequest();
}

bool URecoveredDeviceManager::SendLovenseCommand(const FString& Payload, bool bConnectionCheck, bool bParseToysResponse) {
    const FString Endpoint = GetLovenseEndpoint();
    if (Endpoint.IsEmpty()) return false;
    FHttpRequestPtr Request = FHttpModule::Get().CreateRequest();
    Request->SetURL(Endpoint);
    Request->SetVerb(TEXT("POST"));
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
    Request->SetContentAsString(Payload);
    Request->OnProcessRequestComplete().BindUObject(this, &URecoveredDeviceManager::HandleLovenseResponse, bConnectionCheck, bParseToysResponse);
    return Request->ProcessRequest();
}

FString URecoveredDeviceManager::GetHttpError(FHttpResponsePtr Response, bool bSucceeded) {
    if (!bSucceeded || !Response.IsValid()) return TEXT("Transport request failed");
    return FString::Printf(TEXT("HTTP %d"), Response->GetResponseCode());
}

void URecoveredDeviceManager::HandleHandyResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded, bool bConnectionCheck) {
    if (!IsValid(this) || !bConnectionCheck) return;
    if (!IsSuccessfulResponse(Response, bSucceeded)) {
        SetConnectionState(ERecoveredDeviceKind::Handy, ERecoveredDeviceConnectionStatus::Error, GetHttpError(Response, bSucceeded));
        return;
    }
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(ERecoveredDeviceKind::Handy);
    TSharedPtr<FJsonObject> Payload;
    if (Response.IsValid() && DeserializeJsonObject(Response->GetContentAsString(), Payload)) {
        FString DeviceName = GetJsonString(Payload, TEXT("name"));
        if (DeviceName.IsEmpty()) {
            const TSharedPtr<FJsonObject>* Info = nullptr;
            if (Payload->TryGetObjectField(TEXT("info"), Info) && Info && Info->IsValid()) {
                DeviceName = GetJsonString(*Info, TEXT("name"));
                if (DeviceName.IsEmpty()) DeviceName = GetJsonString(*Info, TEXT("model"));
            }
        }
        if (!DeviceName.IsEmpty()) Connection.DeviceID = DeviceName;
    }
    SetConnectionState(ERecoveredDeviceKind::Handy, ERecoveredDeviceConnectionStatus::Connected);
}

bool URecoveredDeviceManager::IsLovenseHttpVibrator(const FString& Name) {
    static const TCHAR* const VibratorNames[] = {
        TEXT("lush"), TEXT("lush2"), TEXT("lush3"), TEXT("max"), TEXT("max2"), TEXT("max3"),
        TEXT("gush"), TEXT("domi"), TEXT("domi2"), TEXT("nora"), TEXT("hush"), TEXT("hush2"),
        TEXT("ambi"), TEXT("ferri"), TEXT("dolce"), TEXT("osci"), TEXT("edge"), TEXT("edge2"),
        TEXT("osci2"),
    };
    for (const TCHAR* VibratorName : VibratorNames) {
        if (Name == VibratorName) return true;
    }
    return false;
}

bool URecoveredDeviceManager::IsLovenseHttpStroker(const FString& Name) {
    return Name == TEXT("solace") || Name == TEXT("calor");
}

bool URecoveredDeviceManager::IsLovenseHttpThrusting(const FString& Name) {
    return Name == TEXT("machine") || Name.Contains(TEXT("thrust"), ESearchCase::IgnoreCase) || Name.Contains(TEXT("fuck"), ESearchCase::IgnoreCase);
}

bool URecoveredDeviceManager::ParseLovenseToysResponse(const TSharedPtr<FJsonObject>& Payload, TArray<FRecoveredLovenseHttpToy>& OutToys) {
    OutToys.Reset();
    if (!Payload.IsValid() || GetJsonString(Payload, TEXT("type")) != TEXT("OK")) return false;

    const TSharedPtr<FJsonObject>* Data = nullptr;
    if (!Payload->TryGetObjectField(TEXT("data"), Data) || !Data || !Data->IsValid()) return false;
    const TSharedPtr<FJsonObject>* Toys = nullptr;
    if (!(*Data)->TryGetObjectField(TEXT("toys"), Toys) || !Toys || !Toys->IsValid()) return false;

    for (const TPair<FString, TSharedPtr<FJsonValue>>& Pair : (*Toys)->Values) {
        const TSharedPtr<FJsonObject>* ToyObject = nullptr;
        if (!Pair.Value.IsValid() || !Pair.Value->TryGetObject(ToyObject) || !ToyObject || !ToyObject->IsValid()) continue;
        double Status = 0.0;
        if (!(*ToyObject)->TryGetNumberField(TEXT("status"), Status) || FMath::TruncToInt(Status) != 1) continue;

        FRecoveredLovenseHttpToy Toy;
        Toy.Id = GetJsonString(*ToyObject, TEXT("id"));
        Toy.Name = GetJsonString(*ToyObject, TEXT("name"));
        Toy.NickName = GetJsonString(*ToyObject, TEXT("nickName"));
        double Battery = 0.0;
        (*ToyObject)->TryGetNumberField(TEXT("battery"), Battery);
        Toy.Battery = FMath::TruncToInt(Battery);
        if (!Toy.Id.IsEmpty() && !Toy.Name.IsEmpty()) OutToys.Add(MoveTemp(Toy));
    }
    return OutToys.Num() > 0;
}

void URecoveredDeviceManager::HandleLovenseResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSucceeded, bool bConnectionCheck, bool bParseToysResponse) {
    if (!IsValid(this)) return;
    if (!IsSuccessfulResponse(Response, bSucceeded)) {
        if (bConnectionCheck) {
            LovenseHttpToys.Reset();
            bLovenseContinuousVibration = false;
            if (FRecoveredDeviceConnection* Connection = DeviceStates.Find(ERecoveredDeviceKind::Lovense)) {
                Connection->DeviceNames.Reset();
                Connection->bHasVibrators = false;
                Connection->bHasStrokers = false;
            }
            SetConnectionState(ERecoveredDeviceKind::Lovense, ERecoveredDeviceConnectionStatus::Error, GetHttpError(Response, bSucceeded));
        } else if (FRecoveredDeviceConnection* Connection = DeviceStates.Find(ERecoveredDeviceKind::Lovense)) {
            Connection->LastError = GetHttpError(Response, bSucceeded);
            OnDeviceConnectionUpdated.Broadcast(*Connection);
        }
        return;
    }

    if (!bParseToysResponse) return;

    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(ERecoveredDeviceKind::Lovense);
    TSharedPtr<FJsonObject> Payload;
    TArray<FRecoveredLovenseHttpToy> ParsedToys;
    if (!Response.IsValid() || !DeserializeJsonObject(Response->GetContentAsString(), Payload) || !ParseLovenseToysResponse(Payload, ParsedToys)) {
        LovenseHttpToys.Reset();
        bLovenseContinuousVibration = false;
        Connection.DeviceNames.Reset();
        Connection.bHasVibrators = false;
        Connection.bHasStrokers = false;
        SetConnectionState(ERecoveredDeviceKind::Lovense, ERecoveredDeviceConnectionStatus::Error, TEXT("No toys found via HTTP"));
        return;
    }

    LovenseHttpToys = MoveTemp(ParsedToys);
    Connection.DeviceNames.Reset();
    Connection.bHasVibrators = false;
    Connection.bHasStrokers = false;
    for (const FRecoveredLovenseHttpToy& Toy : LovenseHttpToys) {
        Connection.DeviceNames.Add(FString::Printf(TEXT("\U0001F4F3 %s (%s) - %d%%"), *Toy.Name, *Toy.NickName, Toy.Battery));
        Connection.bHasVibrators |= IsLovenseHttpVibrator(Toy.Name);
        Connection.bHasStrokers |= IsLovenseHttpStroker(Toy.Name) || IsLovenseHttpThrusting(Toy.Name);
    }
    SetConnectionState(ERecoveredDeviceKind::Lovense, ERecoveredDeviceConnectionStatus::Connected);
}

FString URecoveredDeviceManager::SerializeJsonObject(const TSharedRef<FJsonObject>& Object) {
    FString Serialized;
    FJsonSerializer::Serialize(Object, TJsonWriterFactory<>::Create(&Serialized));
    return Serialized;
}

bool URecoveredDeviceManager::DeserializeJsonObject(const FString& Text, TSharedPtr<FJsonObject>& OutObject) {
    OutObject.Reset();
    return FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), OutObject) && OutObject.IsValid();
}

void URecoveredDeviceManager::HandleIntifaceConnected() {
    if (!IsValid(this)) return;
    SendIntifaceHandshake();
}

void URecoveredDeviceManager::HandleIntifaceConnectionError(const FString& Error) {
    if (!IsValid(this)) return;
    ClearIntifaceSocket(false);
    ResetIntifaceRuntimeState();
    SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, Error.IsEmpty() ? TEXT("Intiface connection failed") : Error);
    ScheduleIntifaceReconnect();
}

void URecoveredDeviceManager::HandleIntifaceClosed(int32 StatusCode, const FString& Reason, bool bWasClean) {
    if (!IsValid(this)) return;
    ClearIntifaceSocket(false);
    ResetIntifaceRuntimeState();
    if (bWasClean) {
        SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Disconnected);
        return;
    }
    const FString Detail = Reason.IsEmpty() ? FString::Printf(TEXT("Intiface closed with status %d"), StatusCode) : Reason;
    SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, Detail);
    ScheduleIntifaceReconnect();
}

void URecoveredDeviceManager::SendIntifaceHandshake() {
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
    Payload->SetStringField(TEXT("ClientName"), TEXT("Cock Hero"));
    Payload->SetNumberField(TEXT("MessageVersion"), 3);
    auto Envelope = MakeShared<FJsonObject>();
    Envelope->SetObjectField(TEXT("RequestServerInfo"), Payload);
    SendIntifaceJson(Envelope);
}

void URecoveredDeviceManager::SendIntifaceDeviceListRequest() {
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
    auto Envelope = MakeShared<FJsonObject>();
    Envelope->SetObjectField(TEXT("RequestDeviceList"), Payload);
    SendIntifaceJson(Envelope);
}

void URecoveredDeviceManager::SendIntifaceStartScanning() {
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
    auto Envelope = MakeShared<FJsonObject>();
    Envelope->SetObjectField(TEXT("StartScanning"), Payload);
    SendIntifaceJson(Envelope);
}

void URecoveredDeviceManager::SendIntifaceStopScanning() {
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
    auto Envelope = MakeShared<FJsonObject>();
    Envelope->SetObjectField(TEXT("StopScanning"), Payload);
    SendIntifaceJson(Envelope);
}

void URecoveredDeviceManager::SendIntifaceJson(const TSharedRef<FJsonObject>& Envelope) {
    if (!IntifaceSocket.IsValid() || !IntifaceSocket->IsConnected()) return;
    IntifaceSocket->Send(SerializeJsonObject(Envelope));
}

void URecoveredDeviceManager::HandleIntifaceMessage(const FString& Message) {
    if (!IsValid(this)) return;
    TSharedPtr<FJsonObject> Root;
    if (!DeserializeJsonObject(Message, Root)) {
        SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, TEXT("Intiface returned malformed JSON"));
        return;
    }

    const TSharedPtr<FJsonObject>* Payload = nullptr;
    if (JsonObjectHasCommand(Root, TEXT("Error"), Payload)) {
        FString Error = GetJsonString(*Payload, TEXT("ErrorMessage"));
        if (Error.IsEmpty()) Error = GetJsonString(*Payload, TEXT("Message"), TEXT("Intiface rejected the request"));
        SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, Error);
        return;
    }
    if (JsonObjectHasCommand(Root, TEXT("ServerInfo"), Payload)) {
        double Version = 3;
        (*Payload)->TryGetNumberField(TEXT("MessageVersion"), Version);
        if (FMath::RoundToInt(Version) != 3) {
            SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Error, TEXT("Intiface protocol version is not supported"));
            return;
        }
        IntifaceReconnectAttempts = 0;
        if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(IntifaceReconnectTimer);
        SetConnectionState(ERecoveredDeviceKind::Intiface, ERecoveredDeviceConnectionStatus::Connected);
        SendIntifaceDeviceListRequest();
        SendIntifaceStartScanning();
        return;
    }
    if (JsonObjectHasCommand(Root, TEXT("DeviceList"), Payload)) {
        UpdateIntifaceDevices(*Payload);
        return;
    }
    if (JsonObjectHasCommand(Root, TEXT("DeviceAdded"), Payload)) {
        UpdateIntifaceDevices(*Payload);
        return;
    }
    if (JsonObjectHasCommand(Root, TEXT("DeviceRemoved"), Payload)) {
        double Index = -1;
        if ((*Payload)->TryGetNumberField(TEXT("DeviceIndex"), Index)) {
            const int32 DeviceIndex = FMath::RoundToInt(Index);
            IntifaceDevices.Remove(DeviceIndex);
            IntifaceVibratorFeatures.Remove(DeviceIndex);
            IntifaceStrokerFeatures.Remove(DeviceIndex);
        }
        RefreshIntifaceConnection();
    }
}

void URecoveredDeviceManager::UpdateIntifaceDevices(const TSharedPtr<FJsonObject>& Payload) {
    if (!Payload.IsValid()) return;
    const TArray<TSharedPtr<FJsonValue>>* Devices = nullptr;
    if (Payload->TryGetArrayField(TEXT("Devices"), Devices) && Devices) {
        IntifaceDevices.Reset();
        IntifaceVibratorFeatures.Reset();
        IntifaceStrokerFeatures.Reset();
        for (const TSharedPtr<FJsonValue>& Value : *Devices) {
            const TSharedPtr<FJsonObject>* DevicePtr = nullptr;
            if (!Value.IsValid() || !Value->TryGetObject(DevicePtr) || !DevicePtr || !DevicePtr->IsValid()) continue;
            const TSharedPtr<FJsonObject>& Device = *DevicePtr;
            double DeviceIndex = -1;
            Device->TryGetNumberField(TEXT("DeviceIndex"), DeviceIndex);
            if (DeviceIndex < 0) continue;
            const int32 ParsedIndex = FMath::RoundToInt(DeviceIndex);
            FString Name = GetJsonString(Device, TEXT("DeviceName"));
            if (Name.IsEmpty()) Name = FString::Printf(TEXT("Device %d"), ParsedIndex);
            IntifaceDevices.Add(ParsedIndex, Name);
            const TSharedPtr<FJsonObject>* Messages = nullptr;
            TSharedPtr<FJsonObject> DeviceMessages;
            if (Device->TryGetObjectField(TEXT("DeviceMessages"), Messages) && Messages && Messages->IsValid()) DeviceMessages = *Messages;
            UpdateIntifaceDeviceCapabilities(ParsedIndex, DeviceMessages);
        }
    } else {
        double DeviceIndex = -1;
        Payload->TryGetNumberField(TEXT("DeviceIndex"), DeviceIndex);
        FString Name = GetJsonString(Payload, TEXT("DeviceName"));
        if (DeviceIndex >= 0) {
            const int32 ParsedIndex = FMath::RoundToInt(DeviceIndex);
            IntifaceDevices.Add(ParsedIndex, Name.IsEmpty() ? FString::Printf(TEXT("Device %d"), ParsedIndex) : Name);
            const TSharedPtr<FJsonObject>* Messages = nullptr;
            TSharedPtr<FJsonObject> DeviceMessages;
            if (Payload->TryGetObjectField(TEXT("DeviceMessages"), Messages) && Messages && Messages->IsValid()) DeviceMessages = *Messages;
            UpdateIntifaceDeviceCapabilities(ParsedIndex, DeviceMessages);
        }
    }
    RefreshIntifaceConnection();
}

void URecoveredDeviceManager::UpdateIntifaceDeviceCapabilities(int32 DeviceIndex, const TSharedPtr<FJsonObject>& DeviceMessages) {
    TArray<int32> VibratorIndices = GetIntifaceFeatureIndices(DeviceMessages, TEXT("ScalarCmd"), true);
    TArray<int32> StrokerIndices = GetIntifaceFeatureIndices(DeviceMessages, TEXT("LinearCmd"), false);
    if (VibratorIndices.IsEmpty()) IntifaceVibratorFeatures.Remove(DeviceIndex);
    else IntifaceVibratorFeatures.Add(DeviceIndex, MoveTemp(VibratorIndices));
    if (StrokerIndices.IsEmpty()) IntifaceStrokerFeatures.Remove(DeviceIndex);
    else IntifaceStrokerFeatures.Add(DeviceIndex, MoveTemp(StrokerIndices));
}

void URecoveredDeviceManager::RefreshIntifaceConnection() {
    FRecoveredDeviceConnection& Connection = GetOrCreateConnection(ERecoveredDeviceKind::Intiface);
    Connection.DeviceNames.Reset();
    for (const TPair<int32, FString>& Pair : IntifaceDevices) AddUniqueName(Connection.DeviceNames, Pair.Value);
    Connection.DeviceNames.Sort();
    Connection.bHasVibrators = false;
    Connection.bHasStrokers = false;
    for (const TPair<int32, TArray<int32>>& Pair : IntifaceVibratorFeatures) {
        if (IntifaceDevices.Contains(Pair.Key) && !Pair.Value.IsEmpty()) {
            Connection.bHasVibrators = true;
            break;
        }
    }
    for (const TPair<int32, TArray<int32>>& Pair : IntifaceStrokerFeatures) {
        if (IntifaceDevices.Contains(Pair.Key) && !Pair.Value.IsEmpty()) {
            Connection.bHasStrokers = true;
            break;
        }
    }
    OnDeviceConnectionUpdated.Broadcast(Connection);
}

void URecoveredDeviceManager::SendIntifaceScalar(float Intensity) {
    const FRecoveredDeviceConnection* Connection = FindConnection(ERecoveredDeviceKind::Intiface);
    if (!Connection || !Connection->bConnected) return;
    for (const TPair<int32, FString>& Pair : IntifaceDevices) {
        const TArray<int32>* FeatureIndices = IntifaceVibratorFeatures.Find(Pair.Key);
        if (!FeatureIndices) continue;
        for (const int32 FeatureIndex : *FeatureIndices) {
            auto Scalar = MakeShared<FJsonObject>();
            Scalar->SetNumberField(TEXT("Index"), FeatureIndex);
            Scalar->SetNumberField(TEXT("Scalar"), FMath::Clamp(Intensity, 0.0f, 1.0f));
            Scalar->SetStringField(TEXT("ActuatorType"), TEXT("Vibrate"));
            TArray<TSharedPtr<FJsonValue>> Scalars;
            Scalars.Add(MakeShared<FJsonValueObject>(Scalar));
            auto Payload = MakeShared<FJsonObject>();
            Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
            Payload->SetNumberField(TEXT("DeviceIndex"), Pair.Key);
            Payload->SetArrayField(TEXT("Scalars"), Scalars);
            auto Envelope = MakeShared<FJsonObject>();
            Envelope->SetObjectField(TEXT("ScalarCmd"), Payload);
            SendIntifaceJson(Envelope);
        }
    }
}

void URecoveredDeviceManager::SendIntifaceLinear(float Position, int32 DurationMs) {
    const FRecoveredDeviceConnection* Connection = FindConnection(ERecoveredDeviceKind::Intiface);
    if (!Connection || !Connection->bConnected || !Connection->bHasStrokers) return;
    for (const TPair<int32, FString>& Pair : IntifaceDevices) {
        const TArray<int32>* FeatureIndices = IntifaceStrokerFeatures.Find(Pair.Key);
        if (!FeatureIndices) continue;
        for (const int32 FeatureIndex : *FeatureIndices) {
            auto Vector = MakeShared<FJsonObject>();
            Vector->SetNumberField(TEXT("Index"), FeatureIndex);
            Vector->SetNumberField(TEXT("Duration"), FMath::Max(DurationMs, 50));
            Vector->SetNumberField(TEXT("Position"), FMath::Clamp(Position, 0.0f, 1.0f));
            TArray<TSharedPtr<FJsonValue>> Vectors;
            Vectors.Add(MakeShared<FJsonValueObject>(Vector));
            auto Payload = MakeShared<FJsonObject>();
            Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
            Payload->SetNumberField(TEXT("DeviceIndex"), Pair.Key);
            Payload->SetArrayField(TEXT("Vectors"), Vectors);
            auto Envelope = MakeShared<FJsonObject>();
            Envelope->SetObjectField(TEXT("LinearCmd"), Payload);
            SendIntifaceJson(Envelope);
        }
    }
}

void URecoveredDeviceManager::SendIntifaceStop() {
    const FRecoveredDeviceConnection* Connection = FindConnection(ERecoveredDeviceKind::Intiface);
    if (!Connection || !Connection->bConnected) return;
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetNumberField(TEXT("Id"), NextIntifaceMessageId++);
    auto Envelope = MakeShared<FJsonObject>();
    Envelope->SetObjectField(TEXT("StopAllDevices"), Payload);
    SendIntifaceJson(Envelope);
}

void URecoveredDeviceManager::SendHandyStroke(bool bForward, int32 DurationMs) {
    if (!IsDeviceConnected(ERecoveredDeviceKind::Handy)) return;
    auto Payload = MakeShared<FJsonObject>();
    const float Position = bForward ? StrokeRangeMax : StrokeRangeMin;
    Payload->SetNumberField(TEXT("position"), FMath::RoundToInt(Position));
    Payload->SetNumberField(TEXT("duration"), FMath::Max(DurationMs, 50));
    SendHandyRequest(TEXT("hdsp/xpt"), TEXT("PUT"), SerializeJsonObject(Payload), false);
}

TSharedRef<FJsonObject> URecoveredDeviceManager::BuildLovenseFunctionCommand(const FString& ToyId, const FString& Action, float DurationSeconds, bool bStopPrevious) {
    auto Payload = MakeShared<FJsonObject>();
    Payload->SetStringField(TEXT("command"), LovenseFunctionCommand);
    Payload->SetStringField(TEXT("action"), Action);
    Payload->SetNumberField(TEXT("timeSec"), FMath::Max(DurationSeconds, 0.0f));
    if (bStopPrevious) Payload->SetBoolField(TEXT("stopPrevious"), true);
    Payload->SetNumberField(TEXT("apiVer"), 1);
    if (!ToyId.IsEmpty()) Payload->SetStringField(TEXT("toy"), ToyId);
    return Payload;
}

bool URecoveredDeviceManager::SendLovenseFunctionCommand(const FString& ToyId, const FString& Action, float DurationSeconds, bool bStopPrevious) {
    if (!IsDeviceConnected(ERecoveredDeviceKind::Lovense) || ToyId.IsEmpty()) return false;
    return SendLovenseCommand(SerializeJsonObject(BuildLovenseFunctionCommand(ToyId, Action, DurationSeconds, bStopPrevious)), false);
}

void URecoveredDeviceManager::SendLovensePulse(float Intensity, float DurationSeconds) {
    const FString Action = FString::Printf(TEXT("Vibrate:%d"), FMath::RoundToInt(FMath::Clamp(Intensity, 0.0f, 1.0f) * 20.0f));
    for (const FRecoveredLovenseHttpToy& Toy : LovenseHttpToys) {
        if (IsLovenseHttpVibrator(Toy.Name)) SendLovenseFunctionCommand(Toy.Id, Action, DurationSeconds, false);
    }
}

void URecoveredDeviceManager::SendLovenseBeatPulses() {
    for (const FRecoveredLovenseHttpToy& Toy : LovenseHttpToys) {
        if (IsLovenseHttpVibrator(Toy.Name)) SendLovenseFunctionCommand(Toy.Id, TEXT("Vibrate:15"), 0.0f, true);
    }
}

void URecoveredDeviceManager::StartLovenseContinuousVibration(float IntervalSeconds) {
    int32 Intensity = 2;
    if (IntervalSeconds <= 0.42f) Intensity = 20;
    else if (IntervalSeconds <= 0.45f) Intensity = 15;
    else if (IntervalSeconds <= 0.5f) Intensity = 10;

    const FString Action = FString::Printf(TEXT("Vibrate:%d"), Intensity);
    for (const FRecoveredLovenseHttpToy& Toy : LovenseHttpToys) {
        if (IsLovenseHttpVibrator(Toy.Name)) SendLovenseFunctionCommand(Toy.Id, Action, 0.0f, true);
    }
}

void URecoveredDeviceManager::StopLovenseContinuousVibration() {
    for (const FRecoveredLovenseHttpToy& Toy : LovenseHttpToys) {
        SendLovenseFunctionCommand(Toy.Id, TEXT("Stop"), 0.0f, true);
    }
}

void URecoveredDeviceManager::SendLovenseTestCommands() {
    for (const FRecoveredLovenseHttpToy& Toy : LovenseHttpToys) {
        if (IsLovenseHttpVibrator(Toy.Name)) {
            SendLovenseFunctionCommand(Toy.Id, TEXT("Vibrate:15"), 3.0f, false);
        } else if (IsLovenseHttpStroker(Toy.Name)) {
            SendLovenseFunctionCommand(Toy.Id, TEXT("Stroke:10,Thrusting:20"), 0.3f, false);
        } else if (IsLovenseHttpThrusting(Toy.Name)) {
            SendLovenseFunctionCommand(Toy.Id, TEXT("Thrusting:15"), 3.0f, false);
        } else {
            SendLovenseFunctionCommand(Toy.Id, TEXT("Vibrate:10"), 3.0f, false);
        }
    }
}

void URecoveredDeviceManager::DispatchBeat(const FRecoveredBeatEvent& Event) {
    if (Event.CustomMultiplier < 0.0f) return;
    const bool bForward = bNextStrokeForward;
    bNextStrokeForward = !bNextStrokeForward;
    PendingBeatDirections.Add(Event.BeatNumber, bForward);
    SendHandyStroke(bForward, FMath::Max(FMath::RoundToInt(Event.Interval * 1000.0), 50));
}

void URecoveredDeviceManager::DispatchBeatHitCenter(const FRecoveredBeatEvent& Event) {
    if (Event.CustomMultiplier < 0.0f) return;
    bool bForward = bNextStrokeForward;
    if (!PendingBeatDirections.RemoveAndCopyValue(Event.BeatNumber, bForward)) {
        bNextStrokeForward = !bNextStrokeForward;
    }
    const int32 DurationMs = FMath::Max(FMath::RoundToInt(Event.Interval * 1000.0), 100);
    const float LovenseInterval = static_cast<float>(Event.Interval);
    if (LovenseInterval >= 0.5f) {
        if (bLovenseContinuousVibration) {
            StopLovenseContinuousVibration();
            bLovenseContinuousVibration = false;
            QueueLovensePulseAfterContinuousStop();
        } else {
            SendLovenseBeatPulses();
        }
    } else if (!bLovenseContinuousVibration) {
        StartLovenseContinuousVibration(LovenseInterval);
        bLovenseContinuousVibration = true;
    }
    if (const FRecoveredDeviceConnection* Intiface = FindConnection(ERecoveredDeviceKind::Intiface)) {
        if (Intiface->bConnected && Intiface->bHasVibrators) {
            SendIntifaceScalar(MaximumVibratorIntensity);
            ScheduleIntifaceVibrationStop();
        }
        if (Intiface->bConnected && Intiface->bHasStrokers) {
            if (bFullStrokePerBeat) {
                SendIntifaceLinear(StrokeRangeMin / 100.0f, DurationMs);
                QueueIntifaceFullStrokeReturn(DurationMs);
            } else {
                SendIntifaceLinear(bForward ? StrokeRangeMax / 100.0f : StrokeRangeMin / 100.0f, DurationMs);
            }
        }
    }
}

void URecoveredDeviceManager::SaveDeviceSettings(URecoveredSaveGame* Save) {
    if (!Save) return;
    Save->SetStringSetting(TEXT("HandyKey"), HandyConnectionKey);
    Save->SetStringSetting(TEXT("LovenseIP"), LovenseHost);
    Save->SetStringSetting(TEXT("LovensePort"), LovensePort > 0 ? LexToString(LovensePort) : FString());
    if (const FRecoveredDeviceConnection* Intiface = FindConnection(ERecoveredDeviceKind::Intiface)) {
        Save->SetStringSetting(TEXT("ButtplugURL"), Intiface->Endpoint);
    }
    Save->SetNumberSetting(TEXT("HandyMaxStrokeLength"), StrokeRangeMax / 100.0f);
    Save->SetNumberSetting(TEXT("MaxButtPlugVibratorIntensity"), MaximumVibratorIntensity);
    Save->SetBoolSetting(TEXT("StrokeModeFull?"), bFullStrokePerBeat);
}

void URecoveredDeviceManager::LoadDeviceSettings(URecoveredSaveGame* Save) {
    if (!Save) return;
    LovenseHttpToys.Reset();
    bLovenseContinuousVibration = false;
    HandyConnectionKey = Save->GetStringSetting(TEXT("HandyKey"), FString());
    LovenseHost = Save->GetStringSetting(TEXT("LovenseIP"), FString());
    LexTryParseString(LovensePort, *Save->GetStringSetting(TEXT("LovensePort"), FString()));
    LovenseHttpEndpoint = BuildLovenseEndpoint(LovenseHost, LovensePort);
    StrokeRangeMin = 0.0f;
    StrokeRangeMax = FMath::Clamp(static_cast<float>(Save->GetNumberSetting(TEXT("HandyMaxStrokeLength"), 1.0) * 100.0), 0.0f, 100.0f);
    MaximumVibratorIntensity = FMath::Clamp(static_cast<float>(Save->GetNumberSetting(TEXT("MaxButtPlugVibratorIntensity"), 1.0)), 0.0f, 1.0f);
    bFullStrokePerBeat = Save->GetBoolSetting(TEXT("StrokeModeFull?"), true);

    FRecoveredDeviceConnection& Handy = GetOrCreateConnection(ERecoveredDeviceKind::Handy);
    Handy.Endpoint = HandyBaseUrl;
    Handy.DeviceID = TEXT("Handy");
    FRecoveredDeviceConnection& Lovense = GetOrCreateConnection(ERecoveredDeviceKind::Lovense);
    Lovense.Endpoint = LovenseHttpEndpoint;
    FRecoveredDeviceConnection& Intiface = GetOrCreateConnection(ERecoveredDeviceKind::Intiface);
    Intiface.Endpoint = NormalizeIntifaceEndpoint(Save->GetStringSetting(TEXT("ButtplugURL"), TEXT("ws://127.0.0.1:12345")));
    OnDeviceConnectionUpdated.Broadcast(Handy);
    OnDeviceConnectionUpdated.Broadcast(Lovense);
    OnDeviceConnectionUpdated.Broadcast(Intiface);
}
