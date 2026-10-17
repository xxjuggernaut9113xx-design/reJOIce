#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredMenu.h"
#include "RecoveredImportWidget.h"
#include "RecoveredRules.h"
#include "RecoveredCalibrationWidget.h"
#include "WidgetBlueprint.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Misc/ScopeExit.h"

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
        const TCHAR* const SourceCoverPaths[]={
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/14.14"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/15.15"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/16.16"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/17.17"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/18.18"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/19.19"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/20.20"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/21.21"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/23.23"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/29.29"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/30.30"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/31.31"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/32.32"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/33.33"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/34.34"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/35.35"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/36.36"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/37.37"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/38.38"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/39.39"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/40.40"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1.Covergirl1"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__10_.Covergirl1__10_"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__11_.Covergirl1__11_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__12_.Covergirl1__12_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__13_.Covergirl1__13_"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__2_.Covergirl1__2_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__3_.Covergirl1__3_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__4_.Covergirl1__4_"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__5_.Covergirl1__5_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__6_.Covergirl1__6_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__7_.Covergirl1__7_"),
            TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__8_.Covergirl1__8_"),TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__9_.Covergirl1__9_")
        };
        TArray<UTexture2D*> ResolvedCovers;
        ResolvedCovers.Reserve(UE_ARRAY_COUNT(SourceCoverPaths));
        for (const TCHAR* Path:SourceCoverPaths) {
            UTexture2D* Candidate=LoadObject<UTexture2D>(nullptr,Path);
            TestNotNull(*FString::Printf(TEXT("Recovered source cover resolves: %s"),Path),Candidate);
            if (Candidate) ResolvedCovers.Add(Candidate);
        }
        TestEqual(TEXT("All recovered source covers resolve"),ResolvedCovers.Num(),static_cast<int32>(UE_ARRAY_COUNT(SourceCoverPaths)));
        auto* SelectedCover=Cast<UTexture2D>(Cover->GetStyle().Normal.GetResourceObject());
        TestNotNull(TEXT("Construct selects a valid recovered cover"),SelectedCover);
        TestTrue(TEXT("Construct selects a recovered source cover"),ResolvedCovers.Contains(SelectedCover));
        TestEqual(TEXT("Cover draw mode follows source"),int32(Cover->GetStyle().Normal.DrawAs),3);
        TestEqual(TEXT("Cover image width follows source"),float(Cover->GetStyle().Normal.ImageSize.X),32.0f);
    }
    const TCHAR* Buttons[]={TEXT("StartGameButton"),TEXT("StatsButton"),TEXT("Settings"),TEXT("UnlockStoreButton"),TEXT("ImportButton")};
    const TCHAR* Methods[]={TEXT("OpenDifficulty"),TEXT("OpenChallenges"),TEXT("OpenSettings"),TEXT("OpenUnlockStore"),TEXT("OpenImport")};
    for (int32 I=0;I<UE_ARRAY_COUNT(Buttons);++I) {
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
    auto* FreshSave=NewObject<URecoveredSaveGame>(GetTransientPackage());
    TestTrue(TEXT("Fresh source-default latency profile launches calibration"),RecoveredMenu::NeedsInitialCalibration(FreshSave));
    FRecoveredLatencyProfile CalibratedProfile;CalibratedProfile.bIsCalibrated=true;
    TestTrue(TEXT("Calibrated source profile persists"),FreshSave->SetLatencyProfile(CalibratedProfile));
    TestFalse(TEXT("Calibrated latency profile skips calibration"),RecoveredMenu::NeedsInitialCalibration(FreshSave));

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>(World);
    auto* SourceSave=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Fresh source save initializes"),SourceSave->InitializeRecoveredDefaults())) return false;
    Instance->CurrentSave=SourceSave;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());
    UClass* LiveMenuClass=Blueprint->GeneratedClass.Get();
    auto* LiveMenu=CreateWidget<URecoveredMainMenu>(World,LiveMenuClass);
    if (!TestNotNull(TEXT("Live main menu instantiates"),LiveMenu)) return false;
    LiveMenu->TakeWidget();
    auto* Version=Cast<UTextBlock>(LiveMenu->GetWidgetFromName(TEXT("VersionInfoMainMenuText")));
    auto* Support=Cast<UTextBlock>(LiveMenu->GetWidgetFromName(TEXT("PatreonSupportText")));
    TestEqual(TEXT("Patron source version is restored"),Version ? Version->GetText().ToString() : FString(),FString(TEXT("V0.04 Patreon Build")));
    TestEqual(TEXT("Patron source support text is restored"),Support ? Support->GetText().ToString() : FString(),FString(TEXT("vote on weekly content packs \r\nvia patreon")));
    LiveMenu->OpenImport();
    TestNotNull(TEXT("Patron source route opens the import menu"),Cast<URecoveredImportWidget>(LiveMenu->LastOpenedScreen));
    if (LiveMenu->LastOpenedScreen) LiveMenu->LastOpenedScreen->RemoveFromParent();
    LiveMenu->LastOpenedScreen=nullptr;
    TestTrue(TEXT("Public source patron flag writes"),SourceSave->SetBoolSetting(TEXT("IsPatron?"),false));
    LiveMenu->ApplyPatronLocks();
    TestEqual(TEXT("Public source version is restored"),Version ? Version->GetText().ToString() : FString(),FString(TEXT("V0.04 Public Build")));
    TestEqual(TEXT("Public source support text is restored"),Support ? Support->GetText().ToString() : FString(),FString(TEXT("Join now for complete access and fresh content drops every Friday.")));
    auto* Import=Cast<UTextBlock>(LiveMenu->GetWidgetFromName(TEXT("ImportText")));
    TestEqual(TEXT("Public source import glyph opacity is restored"),Import ? Import->GetColorAndOpacity().GetSpecifiedColor().A : 0.0f,0.5f);
    if (auto* Lock=LiveMenu->GetWidgetFromName(TEXT("PatronLockImportSizebox"))) TestEqual(TEXT("Public source import lock is visible"),int32(Lock->GetVisibility()),int32(ESlateVisibility::Visible));
    LiveMenu->CloseAdultWarning();
    auto* Calibration=Cast<URecoveredCalibrationWidget>(LiveMenu->LastOpenedScreen);
    if (!TestNotNull(TEXT("Fresh profile routes through source calibration widget"),Calibration)) return false;
    Calibration->TakeWidget();
    auto* Header=Cast<UTextBlock>(Calibration->GetWidgetFromName(TEXT("Header")));
    auto* Instruction=Cast<UTextBlock>(Calibration->GetWidgetFromName(TEXT("InstructionText")));
    TestEqual(TEXT("Source calibration title is visible"),Header ? Header->GetText().ToString() : FString(),FString(TEXT("Timing Calibration")));
    TestEqual(TEXT("Source calibration instruction is visible"),Instruction ? Instruction->GetText().ToString() : FString(),FString(TEXT("Click the heart when you hear the beat!")));
    return true;
}
#endif
