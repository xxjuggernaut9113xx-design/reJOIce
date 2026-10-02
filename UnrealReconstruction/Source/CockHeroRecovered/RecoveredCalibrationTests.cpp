#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredRules.h"
#include "RecoveredCalibrationWidget.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredCalibrationTest,"CockHero.Recovery.NativeCalibrationAndSaveRoundTrip",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredCalibrationTest::RunTest(const FString& Parameters) {
    FString Text;TSharedPtr<FJsonObject> Evidence;
    if (!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/native-calibration-traces.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) { AddError(TEXT("Missing calibration traces"));return false; }
    for (const auto& Item:Evidence->GetArrayField(TEXT("cases"))) {
        auto Row=Item->AsObject();TArray<float> Taps;TArray<double> Beats;
        for (const auto& Value:Row->GetArrayField(TEXT("taps"))) Taps.Add(float(Value->AsNumber()));
        for (const auto& Value:Row->GetArrayField(TEXT("beats"))) Beats.Add(Value->AsNumber());
        float Offset=999;
        TestTrue(TEXT("Native nearest-beat analysis succeeds"),URecoveredCalibrationManager::CalculatePerceptionOffset(Taps,Beats,16,Offset));
        TestEqual(TEXT("Native float instruction result"),Offset,float(Row->GetNumberField(TEXT("offset"))));
    }
    float Offset=9;
    TestFalse(TEXT("Too few taps preserve prior result"),URecoveredCalibrationManager::CalculatePerceptionOffset({1},{1},16,Offset));TestEqual(TEXT("Prior offset retained"),Offset,9.0f);
    TestFalse(TEXT("No beat timestamps rejected safely"),URecoveredCalibrationManager::CalculatePerceptionOffset({1},{},1,Offset));
    auto* Manager=NewObject<URecoveredCalibrationManager>();
    TestEqual(TEXT("Native calibration tempo"),Manager->CalibrationBPM,120.0f);TestEqual(TEXT("Native required taps"),Manager->RequiredTaps,16);TestEqual(TEXT("Native beat cap"),Manager->MaximumBeats,32);
    Manager->StartManualCalibration();TestEqual(TEXT("First beat fires immediately"),Manager->BeatTimes.Num(),1);
    for (int32 I=0;I<16;++I) Manager->RegisterBeatTap(.05f);
    TestEqual(TEXT("Native signed mean"),Manager->CurrentProfile.UserPerceptionOffsetMs,50.0f);TestEqual(TEXT("Calibration completes at 16 taps"),int32(Manager->State),4);
    TestTrue(TEXT("Profile marks calibrated"),Manager->CurrentProfile.bIsCalibrated);TestEqual(TEXT("Native complete progress"),Manager->GetCalibrationProgress(),1.0f);
    TestEqual(TEXT("Native profile offset in seconds"),Manager->GetCompensatedTimelineOffset(),.11);
    const int32 Before=Manager->TapTimes.Num();Manager->RegisterBeatTap(.2f);TestEqual(TEXT("Completed state ignores new taps"),Manager->TapTimes.Num(),Before);
    auto* Save=NewObject<URecoveredSaveGame>();if (!TestTrue(TEXT("Source default save initializes"),Save->InitializeRecoveredDefaults())) return false;
    FRecoveredLatencyProfile Default;
    if (TestTrue(TEXT("Source latency structure reads"),Save->GetLatencyProfile(Default))) { TestEqual(TEXT("Source system buffer"),Default.SystemBufferMs,60.0f);TestFalse(TEXT("Source default uncalibrated"),Default.bIsCalibrated); }
    TestEqual(TEXT("Localized source menu title"),Save->GetTextSetting(TEXT("SelectedTitleText"),FText::GetEmpty()).ToString(),FString(TEXT("cock hero")));
    Manager->CurrentProfile.CreatedDate=FDateTime(638893482732250001ll);
    TestTrue(TEXT("Updated profile writes to recovery state"),Save->SetLatencyProfile(Manager->CurrentProfile));
    TArray<uint8> Bytes;if (!TestTrue(TEXT("Recovery save serializes to memory"),UGameplayStatics::SaveGameToMemory(Save,Bytes))) return false;
    auto* Loaded=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromMemory(Bytes));FRecoveredLatencyProfile Restored;
    if (TestNotNull(TEXT("Saved profile reloads"),Loaded) && TestTrue(TEXT("Saved latency fields read"),Loaded->GetLatencyProfile(Restored))) {
        TestEqual(TEXT("User timing survives save"),Restored.UserPerceptionOffsetMs,50.0f);TestEqual(TEXT("Exact timestamp ticks survive recovery save"),Restored.CreatedDate.GetTicks(),638893482732250001ll);TestTrue(TEXT("Completed profile survives save"),Restored.IsValid());
    }
    UClass* Class=LoadClass<URecoveredCalibrationWidget>(nullptr,TEXT("/Game/Recovery/UI/WBP_CalibrationUI.WBP_CalibrationUI_C"));
    if (!TestNotNull(TEXT("Editable calibration screen"),Class)) return false;
    auto* Widget=NewObject<URecoveredCalibrationWidget>(GetTransientPackage(),Class);if (!TestTrue(TEXT("Calibration tree initializes"),Widget->Initialize())) return false;auto Slate=Widget->TakeWidget();
    const TCHAR* Names[]={TEXT("Exit"),TEXT("IconClicker"),TEXT("StartSequenceButton")};const TCHAR* Methods[]={TEXT("CloseCalibration"),TEXT("RegisterTap"),TEXT("StartSequence")};
    for (int32 I=0;I<3;++I) if (auto* Button=Cast<UButton>(Widget->GetWidgetFromName(Names[I]))) TestTrue(TEXT("Source calibration control binds"),Button->OnClicked.Contains(Widget,Methods[I]));else AddError(FString(TEXT("Missing button "))+Names[I]);
    return true;
}
#endif
