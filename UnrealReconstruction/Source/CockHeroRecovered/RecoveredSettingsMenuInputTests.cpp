#include "RecoveredSessionWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Dom/JsonObject.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundBase.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSettingsMenuInputTest,"CockHero.Recovery.SettingsMenuInputParity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSettingsMenuInputTest::RunTest(const FString& Parameters) {
    FString Input;
    TSharedPtr<FJsonObject> Evidence;
    const FString EvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/settings-menu-input-recovery.json");
    if (!FFileHelper::LoadFileToString(Input,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Input),Evidence)) {
        AddError(TEXT("Missing settings menu input evidence"));
        return false;
    }
    TestEqual(TEXT("Escape enters the decoded source toggle"),Evidence->GetObjectField(TEXT("entrypoints"))->GetIntegerField(TEXT("Escape")),13976);
    TestEqual(TEXT("Settings button enters the decoded source toggle"),Evidence->GetObjectField(TEXT("entrypoints"))->GetIntegerField(TEXT("SettingsMenuButton")),12730);
    TestEqual(TEXT("All source routes converge at the decoded toggle"),Evidence->GetIntegerField(TEXT("shared_toggle_entry")),2414);
    TestEqual(TEXT("Source settings-menu sound"),Evidence->GetObjectField(TEXT("open"))->GetStringField(TEXT("sound")),FString(TEXT("/Engine/VREditor/Sounds/VR_ungrab.VR_ungrab")));
    TestNotNull(TEXT("Source settings-menu sound loads"),LoadObject<USoundBase>(nullptr,TEXT("/Engine/VREditor/Sounds/VR_ungrab.VR_ungrab")));

    UClass* Class=LoadClass<URecoveredSessionWidget>(nullptr,TEXT("/Game/Recovery/UI/UI_Manager.UI_Manager_C"));
    if (!TestNotNull(TEXT("Recovered session screen class"),Class)) return false;
    auto* Screen=NewObject<URecoveredSessionWidget>(GetTransientPackage(),Class);
    if (!TestTrue(TEXT("Recovered session screen initializes"),Screen->Initialize())) return false;
    auto SlateWidget=Screen->TakeWidget();
    auto* Border=Cast<UBorder>(Screen->GetWidgetFromName(TEXT("PauseMenuMasterBorder")));
    if (!TestNotNull(TEXT("Source settings-menu border"),Border)) return false;
    if (!TestNotNull(TEXT("Source settings-menu direct child"),Border->GetContent())) return false;
    for (const TCHAR* Name : {TEXT("ResumeButton"),TEXT("SettingsMenuButton")}) {
        auto* Button=Cast<UButton>(Screen->GetWidgetFromName(Name));
        if (TestNotNull(Name,Button)) TestTrue(*(FString(Name)+TEXT(" binds the source toggle")),Button->OnClicked.Contains(Screen,TEXT("ToggleRecoveredSettingsMenu")));
    }
    Screen->PauseSession();
    TestEqual(TEXT("Source open makes the border visible"),Border->GetVisibility(),ESlateVisibility::Visible);
    TestEqual(TEXT("Source open makes its direct child visible"),Border->GetContent()->GetVisibility(),ESlateVisibility::Visible);
    Screen->ResumeSession();
    TestEqual(TEXT("Source close collapses the border"),Border->GetVisibility(),ESlateVisibility::Collapsed);
    TestEqual(TEXT("Source close collapses its direct child"),Border->GetContent()->GetVisibility(),ESlateVisibility::Collapsed);
    Screen->ToggleRecoveredSettingsMenu();
    TestEqual(TEXT("Source toggle reopens the menu"),Border->GetVisibility(),ESlateVisibility::Visible);
    Screen->ToggleRecoveredSettingsMenu();
    TestEqual(TEXT("Source toggle recloses the menu"),Border->GetVisibility(),ESlateVisibility::Collapsed);
    return true;
}
#endif
