#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredMenu.h"
#include "WidgetBlueprint.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSettingsTest,"CockHero.Recovery.SettingsNavigation",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSettingsTest::RunTest(const FString& Parameters) {
    FString Text;TSharedPtr<FJsonObject> Traces,Defaults;
    if (!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/settings-navigation-traces.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Traces)) { AddError(TEXT("Missing settings instruction traces"));return false; }
    if (!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/widget-class-defaults.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Defaults)) { AddError(TEXT("Missing widget defaults"));return false; }
    TestEqual(TEXT("All selected widget defaults verified"),Defaults->GetArrayField(TEXT("defaults")).Num(),107);
    TestEqual(TEXT("No decoding failures"),Defaults->GetArrayField(TEXT("failures")).Num(),0);
    auto* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/SettingsMenuWidget.SettingsMenuWidget"));
    if (!TestNotNull(TEXT("Settings blueprint"),Blueprint) || !TestTrue(TEXT("Native settings parent"),Blueprint->GeneratedClass->IsChildOf(URecoveredSettingsMenu::StaticClass()))) return false;
    auto* Menu=NewObject<URecoveredSettingsMenu>(GetTransientPackage(),Blueprint->GeneratedClass);
    if (!TestTrue(TEXT("Settings widget initializes"),Menu->Initialize())) return false;
    auto Slate=Menu->TakeWidget();
    auto* Switcher=Cast<UWidgetSwitcher>(Menu->GetWidgetFromName(TEXT("WidgetSwitcher")));
    if (!TestNotNull(TEXT("Original widget switcher"),Switcher)) return false;
    TestEqual(TEXT("All original settings pages attached"),Switcher->GetChildrenCount(),5);
    UWidget* Voice=Menu->GetWidgetFromName(TEXT("VoicelineSettingsMenu"));
    if(TestNotNull(TEXT("Voice preview child"),Voice)) TestTrue(TEXT("Voice preview child inherits recovered stop handler"),Voice->IsA<URecoveredVoiceSettings>());
    TSharedPtr<FJsonObject> SourceStyles;
    for (const auto& Value:Defaults->GetArrayField(TEXT("defaults"))) if(Value->AsObject()->GetStringField(TEXT("class"))==TEXT("SettingsMenuWidget_C")) SourceStyles=Value->AsObject()->GetObjectField(TEXT("values"));
    if (!TestTrue(TEXT("Verified source styles available"),SourceStyles.IsValid())) return false;
    const FButtonStyle* Styles[]={&Menu->ClickedStyle,&Menu->UnclickedStyle};
    const TCHAR* StyleNames[]={TEXT("Clicked Style"),TEXT("UnclickedStyle")};
    for (int32 I=0;I<2;++I) {
        const auto Brush=SourceStyles->GetObjectField(StyleNames[I])->GetObjectField(TEXT("Normal"));
        const auto Color=Brush->GetObjectField(TEXT("TintColor"))->GetObjectField(TEXT("SpecifiedColor"));
        const FLinearColor Expected(float(Color->GetNumberField(TEXT("R"))),float(Color->GetNumberField(TEXT("G"))),float(Color->GetNumberField(TEXT("B"))),float(Color->GetNumberField(TEXT("A"))));
        TestEqual(StyleNames[I],Styles[I]->Normal.TintColor.GetSpecifiedColor(),Expected);
        TestEqual(TEXT("Source brush draw mode"),int32(Styles[I]->Normal.DrawAs),int32(Brush->GetNumberField(TEXT("DrawAs"))));
        TestTrue(TEXT("Source null resource name restored as None"),Styles[I]->Normal.GetResourceName().IsNone());
        TestEqual(TEXT("Zero-masked disabled brush width"),Styles[I]->Disabled.ImageSize.X,0.0f);
        TestEqual(TEXT("Zero-masked disabled brush height"),Styles[I]->Disabled.ImageSize.Y,0.0f);
    }
    // Broadcast actual generated-widget button delegates; no browser, device or file write.
    for (int32 Repeat=0;Repeat<2;++Repeat) for (const auto& Value:Traces->GetArrayField(TEXT("routes"))) {
        const auto Route=Value->AsObject();const FString Name=Route->GetStringField(TEXT("button"));
        auto* Button=Cast<UButton>(Menu->GetWidgetFromName(FName(*Name)));
        if (!TestNotNull(*Name,Button)) continue;
        Button->OnClicked.Broadcast();
        TestEqual(*Name,Switcher->GetActiveWidgetIndex(),int32(Route->GetNumberField(TEXT("active_index"))));
        for (const auto& CallValue:Route->GetArrayField(TEXT("calls"))) {
            const auto Call=CallValue->AsObject(); if(Call->GetStringField(TEXT("name"))!=TEXT("SetStyle")) continue;
            auto* Styled=Cast<UButton>(Menu->GetWidgetFromName(FName(*Call->GetStringField(TEXT("receiver")))));
            if (!TestNotNull(TEXT("Source styled button"),Styled)) continue;
            const FButtonStyle& Expected=Call->GetStringField(TEXT("style"))==TEXT("Clicked Style") ? Menu->ClickedStyle : Menu->UnclickedStyle;
            TestEqual(TEXT("Applied selected/unselected source style"),Styled->GetStyle().Normal.TintColor.GetSpecifiedColor(),Expected.Normal.TintColor.GetSpecifiedColor());
        }
    }
    return true;
}
#endif
