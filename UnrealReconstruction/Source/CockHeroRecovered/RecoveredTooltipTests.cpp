#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredMenu.h"
#include "Engine/World.h"
#include "Misc/ScopeExit.h"
#include "Components/TextBlock.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTooltipTest,"CockHero.Recovery.StaticTooltipBindings",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredTooltipTest::RunTest(const FString& Parameters) {
    FString Text;TSharedPtr<FJsonObject> Evidence;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/static-tooltip-values.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) { AddError(TEXT("Missing verified tooltip values")); return false; }
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,FName(TEXT("RecoveryTooltipTest")));
    if(!TestNotNull(TEXT("Isolated transient world"),World)) return false;
    ON_SCOPE_EXIT { World->DestroyWorld(false); };
    TMap<FString,URecoveredMenuWidget*> Screens;
    int32 Checked=0;
    for(const auto& Value:Evidence->GetArrayField(TEXT("records"))) {
        const auto Record=Value->AsObject(); const FString ScreenName=Record->GetStringField(TEXT("asset"));
        if(!Screens.Contains(ScreenName)) {
            UClass* Class=LoadClass<URecoveredMenuWidget>(nullptr,*FString::Printf(TEXT("/Game/Recovery/UI/%s.%s_C"),*ScreenName,*ScreenName));
            if(!TestNotNull(*ScreenName,Class)) continue;
            auto* Screen=CreateWidget<URecoveredMenuWidget>(World,Class);
            if(!TestNotNull(TEXT("Generated screen instance"),Screen)) continue;
            Screens.Add(ScreenName,Screen);
            Screen->AttachRecoveredTooltips();
        }
        URecoveredMenuWidget* Screen=Screens[ScreenName];
        UWidget* Target=Screen->GetWidgetFromName(FName(*Record->GetStringField(TEXT("widget"))));
        if(!TestNotNull(TEXT("Source tooltip target"),Target)) continue;
        auto* Tooltip=Cast<URecoveredTooltip>(Target->GetToolTip());
        if(!TestNotNull(TEXT("Recovered styled tooltip attached"),Tooltip)) continue;
        const FString Title=Record->GetObjectField(TEXT("title"))->GetStringField(TEXT("text"));
        const FString Description=Record->GetObjectField(TEXT("description"))->GetStringField(TEXT("text"));
        TestEqual(TEXT("Exact source title"),Tooltip->TooltipTitle.ToString(),Title);
        TestEqual(TEXT("Exact source description"),Tooltip->TooltipDescription.ToString(),Description);
        auto Slate=Tooltip->TakeWidget();
        auto* TitleBlock=Cast<UTextBlock>(Tooltip->GetWidgetFromName(TEXT("Title")));
        auto* DescriptionBlock=Cast<UTextBlock>(Tooltip->GetWidgetFromName(TEXT("Description")));
        if(TestNotNull(TEXT("Original title text block"),TitleBlock)) TestEqual(TEXT("Displayed source title"),TitleBlock->GetText().ToString(),Title);
        if(TestNotNull(TEXT("Original description text block"),DescriptionBlock)) TestEqual(TEXT("Displayed source description"),DescriptionBlock->GetText().ToString(),Description);
        Screen->AttachRecoveredTooltips();
        TestTrue(TEXT("Repeated construction retains tooltip"),Target->GetToolTip()==Tooltip);
        ++Checked;
    }
    TestEqual(TEXT("All accepted static tooltip bindings checked"),Checked,27);
    return true;
}
#endif
