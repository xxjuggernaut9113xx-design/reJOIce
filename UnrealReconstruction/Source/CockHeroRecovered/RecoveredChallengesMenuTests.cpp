#include "RecoveredChallengesMenu.h"

#include "WidgetBlueprint.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Dom/JsonObject.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredChallengesMenuTest,"CockHero.Recovery.ChallengesMenuNavigation",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredChallengesMenuTest::RunTest(const FString& Parameters) {
    FString Text;
    TSharedPtr<FJsonObject> Evidence;
    const FString EvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/challenges-menu-navigation-recovery.json");
    if (!FFileHelper::LoadFileToString(Text,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) {
        AddError(TEXT("Missing challenges-menu recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Original source execution remains unclaimed"),Evidence->GetBoolField(TEXT("source_executed")));
    TestEqual(TEXT("Source construct entrypoint"),Evidence->GetObjectField(TEXT("source_entrypoints"))->GetIntegerField(TEXT("Construct")),51);
    TestEqual(TEXT("Source back entrypoint"),Evidence->GetObjectField(TEXT("source_entrypoints"))->GetIntegerField(TEXT("BackButton")),344);
    TestEqual(TEXT("Source tab route count"),Evidence->GetArrayField(TEXT("routes")).Num(),4);

    UWidgetBlueprint* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/ChallengesMenuWidget.ChallengesMenuWidget"));
    if (!TestNotNull(TEXT("Challenges menu blueprint"),Blueprint)) return false;
    if (!TestTrue(TEXT("Challenges menu uses the recovered native owner"),Blueprint->GeneratedClass->IsChildOf(URecoveredChallengesMenu::StaticClass()))) return false;
    auto* Menu=NewObject<URecoveredChallengesMenu>(GetTransientPackage(),Blueprint->GeneratedClass);
    if (!TestTrue(TEXT("Challenges menu initializes"),Menu->Initialize())) return false;
    Menu->TakeWidget();
    Menu->InitializeRecoveredChallengesMenu();

    auto* Switcher=Cast<UWidgetSwitcher>(Menu->GetWidgetFromName(TEXT("WidgetSwitcher")));
    if (!TestNotNull(TEXT("Source widget switcher"),Switcher)) return false;
    const TArray<FString> ExpectedChildren={TEXT("ChallengesTabWidget"),TEXT("PlayerCardsTabWidget"),TEXT("StatsTabWidget"),TEXT("ModifiersTabWidget")};
    TestEqual(TEXT("All source tab widgets remain attached"),Switcher->GetChildrenCount(),ExpectedChildren.Num());
    for (int32 Index=0; Index<ExpectedChildren.Num(); ++Index) {
        UWidget* Child=Switcher->GetChildAt(Index);
        if (TestNotNull(TEXT("Source switcher child"),Child)) TestEqual(TEXT("Source switcher child order"),Child->GetName(),ExpectedChildren[Index]);
    }

    const FLinearColor Clicked=Menu->ClickedStyle.Normal.TintColor.GetSpecifiedColor();
    const FLinearColor Unclicked=Menu->UnclickedStyle.Normal.TintColor.GetSpecifiedColor();
    TestEqual(TEXT("Source clicked normal tint"),Clicked,FLinearColor(0.24620099365711212f,0.24620099365711212f,0.24620099365711212f,1));
    TestEqual(TEXT("Source unclicked normal tint"),Unclicked,FLinearColor(0,0,0,1));
    TestEqual(TEXT("Source normal button draw mode"),int32(Menu->ClickedStyle.Normal.DrawAs),int32(ESlateBrushDrawType::Box));
    TestEqual(TEXT("Source interactive button draw mode"),int32(Menu->ClickedStyle.Hovered.DrawAs),int32(ESlateBrushDrawType::RoundedBox));
    TestEqual(TEXT("Source button horizontal padding"),Menu->ClickedStyle.NormalPadding.Left,12.0f);
    TestEqual(TEXT("Source button vertical padding"),Menu->ClickedStyle.NormalPadding.Top,1.5f);
    TestEqual(TEXT("Recovered static tooltip bindings"),Menu->StaticTooltips.Num(),4);

    for (const auto& RouteValue:Evidence->GetArrayField(TEXT("routes"))) {
        const TSharedPtr<FJsonObject> Route=RouteValue->AsObject();
        const FString ButtonName=Route->GetStringField(TEXT("button"));
        UButton* Button=Cast<UButton>(Menu->GetWidgetFromName(FName(*ButtonName)));
        if (!TestNotNull(*ButtonName,Button)) continue;
        TestTrue(*(ButtonName+TEXT(" binds its recovered source route")),Button->OnClicked.IsBound());
        Button->OnClicked.Broadcast();
        const int32 ActiveIndex=Route->GetIntegerField(TEXT("active_widget_index"));
        TestEqual(*(ButtonName+TEXT(" selects the source index")),Switcher->GetActiveWidgetIndex(),ActiveIndex);
        for (const TCHAR* Name:{TEXT("ChallengesButton"),TEXT("PlayerCardButton"),TEXT("StatsButton"),TEXT("ModifiersButton")}) {
            UButton* Styled=Cast<UButton>(Menu->GetWidgetFromName(Name));
            if (!TestNotNull(TEXT("Source tab button"),Styled)) continue;
            const FLinearColor Expected=ButtonName==Name ? Clicked : Unclicked;
            TestEqual(TEXT("Source selected and unselected styles"),Styled->GetStyle().Normal.TintColor.GetSpecifiedColor(),Expected);
        }
    }

    UButton* Back=Cast<UButton>(Menu->GetWidgetFromName(TEXT("BackButton")));
    if (TestNotNull(TEXT("Source back button"),Back)) {
        TestTrue(TEXT("Source back click binding"),Back->OnClicked.IsBound());
        TestTrue(TEXT("Source back hover binding"),Back->OnHovered.IsBound());
        TestTrue(TEXT("Source back unhover binding"),Back->OnUnhovered.IsBound());
    }
    return true;
}
#endif
