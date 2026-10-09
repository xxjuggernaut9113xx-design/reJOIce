#include "RecoveredSessionWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Dom/JsonObject.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundBase.h"
#include "WidgetBlueprint.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
namespace {
bool HasRecoveredAnimation(const UWidgetBlueprint* Blueprint,FName Name) {
    const auto* Generated=Blueprint ? Cast<UWidgetBlueprintGeneratedClass>(Blueprint->GeneratedClass) : nullptr;
    if (!Generated) return false;
    for (const TObjectPtr<UWidgetAnimation>& Animation : Generated->Animations) if (Animation && Animation->GetFName()==Name) return true;
    return false;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredInventoryTabInputParityTest,"CockHero.Recovery.InventoryTabInputParity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredInventoryTabInputParityTest::RunTest(const FString& Parameters) {
    FString Input;
    TSharedPtr<FJsonObject> Evidence;
    const FString EvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/input-control-parity-recovery.json");
    if (!FFileHelper::LoadFileToString(Input,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Input),Evidence)) {
        AddError(TEXT("Missing inventory input parity evidence"));
        return false;
    }

    const TSharedPtr<FJsonObject> TabSwitch=Evidence->GetObjectField(TEXT("tab_switch"));
    TestEqual(TEXT("Q and Tab share the decoded source route"),TabSwitch->GetIntegerField(TEXT("shared_route_offset")),12986);
    const TSharedPtr<FJsonObject> Sound=TabSwitch->GetObjectField(TEXT("sound"));
    TestEqual(TEXT("Source tab switch sound"),Sound->GetStringField(TEXT("source")),FString(TEXT("/Game/SoundFX/swapitem.swapitem")));
    TestEqual(TEXT("Source tab switch volume"),Sound->GetNumberField(TEXT("volume_multiplier")),0.25);
    TestEqual(TEXT("Source tab switch pitch"),Sound->GetNumberField(TEXT("pitch_multiplier")),0.7);
    TestTrue(TEXT("Source tab switch uses the UI sound path"),Sound->GetBoolField(TEXT("ui_sound")));
    TestEqual(TEXT("Source closes input focus after a valid switch"),TabSwitch->GetStringField(TEXT("focus")),FString(TEXT("SetFocusToGameViewport")));

    TestEqual(TEXT("Source tab zero advances to tab one"),URecoveredSessionWidget::GetSwitchedInventoryTab(0),1);
    TestEqual(TEXT("Source tab one advances to tab zero"),URecoveredSessionWidget::GetSwitchedInventoryTab(1),0);
    TestEqual(TEXT("Invalid source tab state remains unchanged"),URecoveredSessionWidget::GetSwitchedInventoryTab(2),2);

    auto* SwitchSound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/swapitem.swapitem"));
    TestNotNull(TEXT("Recovered source tab switch sound loads"),SwitchSound);

    auto* PG1=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/PG1TabbedInventory_Widget.PG1TabbedInventory_Widget"));
    auto* PG2=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/PG2TabbedInventory_Widget.PG2TabbedInventory_Widget"));
    TestNotNull(TEXT("Recovered PG1 inventory blueprint"),PG1);
    TestNotNull(TEXT("Recovered PG2 inventory blueprint"),PG2);
    TestTrue(TEXT("PG1 retains its decoded tab switch animation"),HasRecoveredAnimation(PG1,TEXT("SwitchInventoryTabAnimation_INST")));
    TestTrue(TEXT("PG2 retains its distinct decoded tab switch animation"),HasRecoveredAnimation(PG2,TEXT("SwitchTabAnimation_INST")));
    return true;
}
#endif
