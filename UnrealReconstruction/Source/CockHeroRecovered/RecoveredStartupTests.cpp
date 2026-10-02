#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredMenu.h"
#include "WidgetBlueprint.h"
#include "Components/Button.h"
#include "RecoveredSessionWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredDifficultyBindingTest,"CockHero.Recovery.DifficultyNavigationBindings",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredDifficultyBindingTest::RunTest(const FString& Parameters) {
    auto* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/DifficultySelectScreen_Widget.DifficultySelectScreen_Widget"));
    if (!TestNotNull(TEXT("Recovered difficulty screen"),Blueprint)) return false;
    if (!TestTrue(TEXT("Difficulty handlers are installed"),Blueprint->GeneratedClass->IsChildOf(URecoveredDifficultyMenu::StaticClass()))) return false;
    auto* Menu=NewObject<URecoveredDifficultyMenu>(GetTransientPackage(),Blueprint->GeneratedClass);
    if (!TestTrue(TEXT("Generated difficulty screen initializes"),Menu->Initialize())) return false;
    auto SlateWidget=Menu->TakeWidget();
    const TCHAR* Buttons[]={TEXT("EasyDifficultyButton"),TEXT("NormalDifficultyButton"),TEXT("InsaneDifficultyButton"),TEXT("BackButton")};
    const TCHAR* Methods[]={TEXT("SelectEasy"),TEXT("SelectNormal"),TEXT("SelectInsane"),TEXT("CloseDifficulty")};
    for (int32 I=0;I<4;++I) {
        auto* Button=Cast<UButton>(Menu->GetWidgetFromName(Buttons[I]));
        if (TestNotNull(Buttons[I],Button)) TestTrue(Methods[I],Button->OnClicked.Contains(Menu,FName(Methods[I])));
    }
    Menu->SelectNormal();
    TestEqual(TEXT("Selection without game mode reports failure safely"),Menu->LastStartError,FString(TEXT("Difficulty selection requires the recovered game mode")));
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSessionWidgetTest,"CockHero.Recovery.SessionMediaPresentationBindings",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSessionWidgetTest::RunTest(const FString& Parameters) {
    auto* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/UI_Manager.UI_Manager"));
    if (!TestNotNull(TEXT("Recovered gameplay screen"),Blueprint)) return false;
    if (!TestTrue(TEXT("Media consumer is installed"),Blueprint->GeneratedClass->IsChildOf(URecoveredSessionWidget::StaticClass()))) return false;
    auto* Screen=NewObject<URecoveredSessionWidget>(GetTransientPackage(),Blueprint->GeneratedClass);
    if (!TestTrue(TEXT("Gameplay screen initializes"),Screen->Initialize())) return false;
    auto SlateWidget=Screen->TakeWidget();
    auto* Image=Cast<UImage>(Screen->GetWidgetFromName(TEXT("MainImage")));
    if (!TestNotNull(TEXT("Actual gameplay image target"),Image)) return false;
    auto* Still=NewObject<UTexture2D>();
    Screen->DisplayMedia(Still);
    TestTrue(TEXT("Still media reaches the image brush"),Image->GetBrush().GetResourceObject()==Still);
    Screen->DisplayMedia(nullptr);
    TestTrue(TEXT("Missing media preserves the displayed image"),Image->GetBrush().GetResourceObject()==Still);
    const TCHAR* Buttons[]={TEXT("ResumeButton"),TEXT("SettingsMenuButton"),TEXT("DrawButtonTextButton")};
    const TCHAR* Methods[]={TEXT("ResumeSession"),TEXT("OpenSessionSettings"),TEXT("DrawCard")};
    for (int32 I=0;I<3;++I) {
        auto* Button=Cast<UButton>(Screen->GetWidgetFromName(Buttons[I]));
        if (TestNotNull(Buttons[I],Button)) TestTrue(Methods[I],Button->OnClicked.Contains(Screen,FName(Methods[I])));
    }
    return true;
}
#endif
