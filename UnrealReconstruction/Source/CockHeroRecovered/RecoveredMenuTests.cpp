#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredMenu.h"
#include "WidgetBlueprint.h"
#include "Components/Button.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/Texture2D.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredMenuBindingTest,"CockHero.Recovery.MenuNavigationBindings",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredMenuBindingTest::RunTest(const FString& Parameters) {
    auto* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/MainMenu.MainMenu"));
    if (!TestNotNull(TEXT("Main menu blueprint"),Blueprint)) return false;
    if (!TestTrue(TEXT("Main menu inherits reconstructed navigation"),Blueprint->GeneratedClass->IsChildOf(URecoveredMainMenu::StaticClass()))) return false;
    auto* Menu=NewObject<URecoveredMainMenu>(GetTransientPackage(),Blueprint->GeneratedClass);
    if (!TestTrue(TEXT("Generated menu initializes"),Menu->Initialize())) return false;
    auto SlateWidget=Menu->TakeWidget();
    TestEqual(TEXT("Verified cover array restored"),Menu->PatreonCoverGirlArray.Num(),34);
    auto* Cover=Cast<UButton>(Menu->GetWidgetFromName(TEXT("CoverGirlButton")));
    if (TestNotNull(TEXT("Cover button"),Cover)) {
        TestTrue(TEXT("Construct selects a recovered cover"),Menu->PatreonCoverGirlArray.Contains(Cast<UTexture2D>(Cover->GetStyle().Normal.GetResourceObject())));
        TestEqual(TEXT("Cover draw mode follows source"),int32(Cover->GetStyle().Normal.DrawAs),3);
        TestEqual(TEXT("Cover image width follows source"),float(Cover->GetStyle().Normal.ImageSize.X),32.0f);
    }
    const TCHAR* Buttons[]={TEXT("StartGameButton"),TEXT("StatsButton"),TEXT("Settings"),TEXT("UnlockStoreButton")};
    const TCHAR* Methods[]={TEXT("OpenDifficulty"),TEXT("OpenChallenges"),TEXT("OpenSettings"),TEXT("OpenUnlockStore")};
    for (int32 I=0;I<4;++I) {
        auto* Button=Cast<UButton>(Menu->GetWidgetFromName(Buttons[I]));
        if (TestNotNull(Buttons[I],Button)) TestTrue(Methods[I],Button->OnClicked.Contains(Menu,FName(Methods[I])));
    }
    // Creating the Slate tree must not navigate or start a session.
    TestNull(TEXT("No screen opened during construction"),Menu->LastOpenedScreen.Get());
    const TCHAR* Screens[]={TEXT("DifficultySelectScreen_Widget"),TEXT("ChallengesMenuWidget"),TEXT("SettingsMenuWidget"),TEXT("UnlockStoreWidget")};
    for (const TCHAR* Name:Screens) {
        const FString Path=FString::Printf(TEXT("/Game/Recovery/UI/%s.%s_C"),Name,Name);
        TestNotNull(*Path,LoadClass<UUserWidget>(nullptr,*Path));
    }
    return true;
}
#endif
