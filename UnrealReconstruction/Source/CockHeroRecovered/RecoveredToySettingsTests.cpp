#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredDeviceInterface.h"
#include "RecoveredRules.h"
#include "RecoveredToySettings.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredToySettingsParityTest,"CockHero.Recovery.ToySettingsTransportParity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredToySettingsParityTest::RunTest(const FString& Parameters) {
    FString Text;
    TSharedPtr<FJsonObject> Evidence;
    const FString EvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/toy-settings-parity-recovery.json");
    if (!FFileHelper::LoadFileToString(Text,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) {
        AddError(TEXT("Missing toy-settings parity evidence"));
        return false;
    }

    TestEqual(TEXT("Source control inventory"),Evidence->GetArrayField(TEXT("controls")).Num(),27);
    TestEqual(TEXT("Source animation inventory"),Evidence->GetArrayField(TEXT("animations")).Num(),9);
    TestEqual(TEXT("Source transport call inventory"),Evidence->GetArrayField(TEXT("source_transport_calls")).Num(),17);
    TestEqual(TEXT("Source Handy default"),Evidence->GetObjectField(TEXT("defaults"))->GetNumberField(TEXT("HandyMaxStrokeLength")),1.0);
    TestEqual(TEXT("Source Intiface endpoint"),Evidence->GetObjectField(TEXT("defaults"))->GetStringField(TEXT("ButtplugURL")),FString(TEXT("ws://127.0.0.1:12345")));
    const TSharedPtr<FJsonObject> NativeDefaults=Evidence->GetObjectField(TEXT("native_transport_defaults"));
    TestTrue(TEXT("Original static source was not executed"),!Evidence->GetBoolField(TEXT("source_executed")));
    TestTrue(TEXT("Native static source was not executed"),!Evidence->GetObjectField(TEXT("native_static_provenance"))->GetBoolField(TEXT("source_executed")));
    TestTrue(TEXT("Source Intiface pulse duration"),FMath::IsNearlyEqual(static_cast<float>(NativeDefaults->GetNumberField(TEXT("ButtplugVibratorPulseDurationSeconds"))),0.25f));
    TestTrue(TEXT("Source Intiface reconnect delay"),FMath::IsNearlyEqual(static_cast<float>(NativeDefaults->GetNumberField(TEXT("ButtplugReconnectDelaySeconds"))),2.0f));
    TestEqual(TEXT("Source Intiface reconnect attempts"),static_cast<int32>(FMath::RoundToInt(NativeDefaults->GetNumberField(TEXT("ButtplugMaxReconnectAttempts")))),5);
    const TSharedPtr<FJsonObject> LovenseTiming=Evidence->GetObjectField(TEXT("native_timing"))->GetObjectField(TEXT("lovense_http"));
    TestEqual(TEXT("Source Lovense continuous threshold"),LovenseTiming->GetNumberField(TEXT("continuous_threshold_seconds")),0.5);
    TestEqual(TEXT("Source Lovense active status"),static_cast<int32>(FMath::RoundToInt(LovenseTiming->GetNumberField(TEXT("active_status")))),1);
    auto HasLiteral=[](const TArray<TSharedPtr<FJsonValue>>& Values,const FString& Expected) {
        return Values.ContainsByPredicate([&Expected](const TSharedPtr<FJsonValue>& Value) { return Value.IsValid() && Value->AsString()==Expected; });
    };
    TestTrue(TEXT("Source Lovense status format"),HasLiteral(Evidence->GetObjectField(TEXT("status_literals"))->GetArrayField(TEXT("lovense")),TEXT("Connection Status: {status}\r\n{devicecount} devices Connected")));

    URecoveredSaveGame* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Recovered defaults initialize"),Save->InitializeRecoveredDefaults())) return false;
    TestTrue(TEXT("Fixture Handy key writes"),Save->SetStringSetting(TEXT("HandyKey"),TEXT("fixture-connection-key")));
    TestTrue(TEXT("Fixture Lovense host writes"),Save->SetStringSetting(TEXT("LovenseIP"),TEXT("192.168.1.42")));
    TestTrue(TEXT("Fixture Lovense port writes"),Save->SetStringSetting(TEXT("LovensePort"),TEXT("30010")));
    TestTrue(TEXT("Fixture Intiface endpoint writes"),Save->SetStringSetting(TEXT("ButtplugURL"),TEXT("ws://127.0.0.1:12345")));
    TestTrue(TEXT("Fixture stroke range writes"),Save->SetNumberSetting(TEXT("HandyMaxStrokeLength"),0.63));
    TestTrue(TEXT("Fixture vibration range writes"),Save->SetNumberSetting(TEXT("MaxButtPlugVibratorIntensity"),0.42));
    TestTrue(TEXT("Fixture alternating mode writes"),Save->SetBoolSetting(TEXT("StrokeModeFull?"),false));

    URecoveredDeviceManager* Manager=NewObject<URecoveredDeviceManager>();
    TestTrue(TEXT("Source pulse duration default"),FMath::IsNearlyEqual(Manager->IntifaceVibratorPulseDuration,0.25f));
    TestTrue(TEXT("Source reconnect delay default"),FMath::IsNearlyEqual(Manager->IntifaceReconnectBaseDelaySeconds,2.0f));
    TestEqual(TEXT("Source reconnect attempt default"),Manager->MaxIntifaceReconnectAttempts,5);
    Manager->SetIntifaceVibratorPulseDuration(0.0f);
    TestTrue(TEXT("Source pulse duration lower clamp"),FMath::IsNearlyEqual(Manager->IntifaceVibratorPulseDuration,0.05f));
    Manager->SetIntifaceVibratorPulseDuration(4.0f);
    TestTrue(TEXT("Source pulse duration upper clamp"),FMath::IsNearlyEqual(Manager->IntifaceVibratorPulseDuration,2.0f));
    Manager->SetIntifaceVibratorPulseDuration(0.25f);
    Manager->LoadDeviceSettings(Save);
    TestTrue(TEXT("Source stroke range rehydrates"),FMath::IsNearlyEqual(Manager->StrokeRangeMax,63.0f));
    TestTrue(TEXT("Source vibration range rehydrates"),FMath::IsNearlyEqual(Manager->MaximumVibratorIntensity,0.42f));
    TestFalse(TEXT("Source alternating mode rehydrates"),Manager->bFullStrokePerBeat);
    TestEqual(TEXT("Lovense endpoint is reconstructed"),Manager->GetDeviceConnection(ERecoveredDeviceKind::Lovense).Endpoint,FString(TEXT("http://192.168.1.42:30010/command")));
    TestEqual(TEXT("Intiface endpoint is reconstructed"),Manager->GetDeviceConnection(ERecoveredDeviceKind::Intiface).Endpoint,FString(TEXT("ws://127.0.0.1:12345")));
    TestEqual(TEXT("Lovense endpoint builder"),URecoveredDeviceManager::BuildLovenseEndpoint(TEXT("192.168.1.42"),30010),FString(TEXT("http://192.168.1.42:30010/command")));
    TestEqual(TEXT("Lovense endpoint accepts scheme"),URecoveredDeviceManager::BuildLovenseEndpoint(TEXT("https://192.168.1.42"),30010),FString(TEXT("https://192.168.1.42:30010/command")));
    TestEqual(TEXT("Intiface endpoint normalizes scheme"),URecoveredDeviceManager::NormalizeIntifaceEndpoint(TEXT("127.0.0.1:12345/")),FString(TEXT("ws://127.0.0.1:12345")));
    TestFalse(TEXT("No transport is marked connected from settings alone"),Manager->GetGameplayDeviceState().bHandy||Manager->GetGameplayDeviceState().bLovense||Manager->GetGameplayDeviceState().bButtplugVibrators||Manager->GetGameplayDeviceState().bButtplugStrokers);
    TestFalse(TEXT("None cannot create a connection"),Manager->ConnectDevice(ERecoveredDeviceKind::None,TEXT("ignored")));
    TestFalse(TEXT("Empty Handy key is rejected"),Manager->ConnectDevice(ERecoveredDeviceKind::Handy,TEXT(" ")));
    TestEqual(TEXT("Invalid Handy state is explicit"),Manager->GetDeviceConnectionStatus(ERecoveredDeviceKind::Handy),ERecoveredDeviceConnectionStatus::Error);
    TestEqual(TEXT("Invalid Handy label is explicit"),Manager->GetConnectionStatusLabel(ERecoveredDeviceKind::Handy),FString(TEXT("Error")));
    TestFalse(TEXT("Malformed Lovense endpoint is rejected"),Manager->ConnectDevice(ERecoveredDeviceKind::Lovense,TEXT("not-a-url")));
    TestFalse(TEXT("Empty Intiface endpoint is rejected"),Manager->ConnectDevice(ERecoveredDeviceKind::Intiface,FString()));
    Manager->DisconnectDevice(ERecoveredDeviceKind::Handy);
    Manager->SaveDeviceSettings(Save);
    TestEqual(TEXT("Disconnect preserves Handy configuration"),Save->GetStringSetting(TEXT("HandyKey"),FString()),FString(TEXT("fixture-connection-key")));
    Manager->SetStrokeRange(0.0f,51.0f);
    Manager->SetVibratorIntensity(0.75f);
    Manager->SetFullStrokePerBeat(true);
    Manager->SaveDeviceSettings(Save);
    TestTrue(TEXT("Slider stroke range persists"),FMath::IsNearlyEqual(static_cast<float>(Save->GetNumberSetting(TEXT("HandyMaxStrokeLength"),0.0)),0.51f));
    TestTrue(TEXT("Slider vibration range persists"),FMath::IsNearlyEqual(static_cast<float>(Save->GetNumberSetting(TEXT("MaxButtPlugVibratorIntensity"),0.0)),0.75f));
    TestTrue(TEXT("Stroke mode persists"),Save->GetBoolSetting(TEXT("StrokeModeFull?"),false));

    TSharedPtr<FJsonObject> LovensePayload;
    const FString LovenseResponse=TEXT("{\"type\":\"OK\",\"data\":{\"toys\":{\"alpha\":{\"id\":\"toy-alpha\",\"name\":\"lush\",\"nickName\":\"Lush\",\"battery\":87,\"status\":1},\"beta\":{\"id\":\"toy-beta\",\"name\":\"solace\",\"nickName\":\"Solace\",\"battery\":72,\"status\":1},\"offline\":{\"id\":\"toy-offline\",\"name\":\"max\",\"nickName\":\"Offline\",\"battery\":10,\"status\":0}}}}");
    if (!TestTrue(TEXT("Lovense fixture deserializes"),FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(LovenseResponse),LovensePayload))) return false;
    TArray<FRecoveredLovenseHttpToy> ParsedToys;
    TestTrue(TEXT("Lovense source response parses"),URecoveredDeviceManager::ParseLovenseToysResponse(LovensePayload,ParsedToys));
    TestEqual(TEXT("Lovense source filters inactive toys"),ParsedToys.Num(),2);
    const FRecoveredLovenseHttpToy* LushToy=ParsedToys.FindByPredicate([](const FRecoveredLovenseHttpToy& Toy) { return Toy.Id==TEXT("toy-alpha"); });
    if (!TestNotNull(TEXT("Lovense vibrator record"),LushToy)) return false;
    TestEqual(TEXT("Lovense vibrator name"),LushToy->Name,FString(TEXT("lush")));
    TestEqual(TEXT("Lovense vibrator nickname"),LushToy->NickName,FString(TEXT("Lush")));
    TestEqual(TEXT("Lovense vibrator battery"),LushToy->Battery,87);
    TSharedPtr<FJsonObject> RejectedLovensePayload;
    if (!TestTrue(TEXT("Lovense rejected fixture deserializes"),FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(TEXT("{\"type\":\"ERROR\",\"data\":{\"toys\":{}}}")),RejectedLovensePayload))) return false;
    TestFalse(TEXT("Lovense rejects non-OK response"),URecoveredDeviceManager::ParseLovenseToysResponse(RejectedLovensePayload,ParsedToys));
    TestTrue(TEXT("Lovense vibrator classifier"),URecoveredDeviceManager::IsLovenseHttpVibrator(TEXT("lush")));
    TestFalse(TEXT("Lovense stroker is not a vibrator"),URecoveredDeviceManager::IsLovenseHttpVibrator(TEXT("solace")));
    TestTrue(TEXT("Lovense stroker classifier"),URecoveredDeviceManager::IsLovenseHttpStroker(TEXT("solace")));
    TestTrue(TEXT("Lovense thrust classifier"),URecoveredDeviceManager::IsLovenseHttpThrusting(TEXT("machine")));
    TestTrue(TEXT("Lovense thrust substring classifier"),URecoveredDeviceManager::IsLovenseHttpThrusting(TEXT("TurboThrust")));

    const TSharedRef<FJsonObject> LovenseBeatCommand=URecoveredDeviceManager::BuildLovenseFunctionCommand(TEXT("toy-alpha"),TEXT("Vibrate:15"),0.0f,true);
    TestEqual(TEXT("Lovense beat command"),LovenseBeatCommand->GetStringField(TEXT("command")),FString(TEXT("Function")));
    TestEqual(TEXT("Lovense beat action"),LovenseBeatCommand->GetStringField(TEXT("action")),FString(TEXT("Vibrate:15")));
    TestTrue(TEXT("Lovense beat duration"),FMath::IsNearlyEqual(static_cast<float>(LovenseBeatCommand->GetNumberField(TEXT("timeSec"))),0.0f));
    TestTrue(TEXT("Lovense beat stops previous command"),LovenseBeatCommand->GetBoolField(TEXT("stopPrevious")));
    TestEqual(TEXT("Lovense beat protocol version"),static_cast<int32>(FMath::RoundToInt(LovenseBeatCommand->GetNumberField(TEXT("apiVer")))),1);
    TestEqual(TEXT("Lovense beat target"),LovenseBeatCommand->GetStringField(TEXT("toy")),FString(TEXT("toy-alpha")));
    const TSharedRef<FJsonObject> LovenseStrokeCommand=URecoveredDeviceManager::BuildLovenseFunctionCommand(TEXT("toy-beta"),TEXT("Stroke:10,Thrusting:20"),0.3f,false);
    TestEqual(TEXT("Lovense test stroker action"),LovenseStrokeCommand->GetStringField(TEXT("action")),FString(TEXT("Stroke:10,Thrusting:20")));
    TestTrue(TEXT("Lovense test stroker duration"),FMath::IsNearlyEqual(static_cast<float>(LovenseStrokeCommand->GetNumberField(TEXT("timeSec"))),0.3f));
    TestFalse(TEXT("Lovense test commands omit beat stop flag"),LovenseStrokeCommand->HasField(TEXT("stopPrevious")));

    UClass* Class=LoadClass<URecoveredToySettingsMenu>(nullptr,TEXT("/Game/Recovery/UI/ToySettingsMenu.ToySettingsMenu_C"));
    if (!TestNotNull(TEXT("Recovered toy-settings class"),Class)) return false;
    if (!TestTrue(TEXT("Recovered toy-settings parent"),Class->IsChildOf(URecoveredToySettingsMenu::StaticClass()))) return false;
    URecoveredToySettingsMenu* Widget=NewObject<URecoveredToySettingsMenu>(GetTransientPackage(),Class);
    if (!TestTrue(TEXT("Recovered toy-settings widget initializes"),Widget->Initialize())) return false;
    Widget->TakeWidget();
    Widget->NativeConstruct();

    struct FButtonBinding { const TCHAR* Name; const TCHAR* Method; };
    const FButtonBinding ButtonBindings[]={
        {TEXT("ConnectLovenseToysButton"),TEXT("OnConnectLovenseClicked")},
        {TEXT("ConnectMobileLovenseToysButton"),TEXT("OnConnectMobileLovenseClicked")},
        {TEXT("DisconnectLovenseToysButton"),TEXT("OnDisconnectLovenseClicked")},
        {TEXT("HandyConnectButtonV2"),TEXT("OnHandyConnectClicked")},
        {TEXT("RefreshHandyConnectionButton"),TEXT("OnRefreshHandyClicked")},
        {TEXT("SendHandyTestStrokesButton"),TEXT("OnSendHandyTestClicked")},
        {TEXT("StopHandyStrokingButton"),TEXT("OnStopHandyClicked")},
        {TEXT("IntifaceConnectButton"),TEXT("OnIntifaceConnectClicked")},
        {TEXT("DisconnectIntiface"),TEXT("OnDisconnectIntifaceClicked")},
        {TEXT("SendTestIntifaceButton"),TEXT("OnSendIntifaceTestClicked")},
        {TEXT("RefreshIntifaceStatusButton"),TEXT("OnRefreshIntifaceClicked")},
        {TEXT("RefreshLovenseConnectionsButton"),TEXT("OnRefreshLovenseClicked")},
        {TEXT("TestLovenseDevicesButton"),TEXT("OnTestLovenseClicked")},
    };
    for (const FButtonBinding& Binding:ButtonBindings) {
        UButton* Button=Cast<UButton>(Widget->GetWidgetFromName(Binding.Name));
        if (TestNotNull(Binding.Name,Button)) TestTrue(*(FString(Binding.Name)+TEXT(" binds its recovered action")),Button->OnClicked.Contains(Widget,Binding.Method));
    }

    struct FSliderBinding { const TCHAR* Name; const TCHAR* Commit; const TCHAR* Changed; };
    const FSliderBinding SliderBindings[]={
        {TEXT("HandyStrokeRangeSlider"),TEXT("OnHandyStrokeRangeCommitted"),TEXT("OnHandyStrokeRangeChanged")},
        {TEXT("IntifaceStrokeRangeSlider"),TEXT("OnIntifaceStrokeRangeCommitted"),TEXT("OnIntifaceStrokeRangeChanged")},
        {TEXT("MaxVibrationIntensitySlider"),TEXT("OnMaxVibrationCommitted"),TEXT("OnMaxVibrationChanged")},
    };
    for (const FSliderBinding& Binding:SliderBindings) {
        USlider* Slider=Cast<USlider>(Widget->GetWidgetFromName(Binding.Name));
        if (TestNotNull(Binding.Name,Slider)) {
            TestTrue(*(FString(Binding.Name)+TEXT(" binds capture-end persistence")),Slider->OnMouseCaptureEnd.Contains(Widget,Binding.Commit));
            TestTrue(*(FString(Binding.Name)+TEXT(" binds live label update")),Slider->OnValueChanged.Contains(Widget,Binding.Changed));
        }
    }
    UComboBoxString* Mode=Cast<UComboBoxString>(Widget->GetWidgetFromName(TEXT("StrokeModeComboBox")));
    if (TestNotNull(TEXT("Source stroke mode selector"),Mode)) TestTrue(TEXT("Source stroke mode selector binds"),Mode->OnSelectionChanged.Contains(Widget,TEXT("OnStrokeModeSelectionChanged")));
    for (const TCHAR* Name:{TEXT("HandyKeyInputBox"),TEXT("LovenseMobileIPInputBox"),TEXT("LovenseMobilePortInputBox"),TEXT("IntifaceServerAddressInputBox")}) TestNotNull(Name,Cast<UEditableTextBox>(Widget->GetWidgetFromName(Name)));
    for (const TCHAR* Name:{TEXT("HandyConnectionStatus"),TEXT("TextBlock_277"),TEXT("IntifaceStatusText"),TEXT("DevicesConnectedCountIntiface")}) TestNotNull(Name,Cast<UTextBlock>(Widget->GetWidgetFromName(Name)));
    for (const TCHAR* Name:{TEXT("LovenseDevicesScrollbox"),TEXT("IntifaceDevicesScrollbox")}) TestNotNull(Name,Cast<UScrollBox>(Widget->GetWidgetFromName(Name)));
    Widget->NativeDestruct();
    return true;
}
#endif
