#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Blueprint/WidgetTree.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredWidgetLayoutTest,"CockHero.Recovery.WidgetLayouts",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredWidgetLayoutTest::RunTest(const FString& Parameters) {
    FString Input; TSharedPtr<FJsonObject> Evidence;
    if(!FFileHelper::LoadFileToString(Input,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/ui-layout-values.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Input),Evidence)) {
        AddError(TEXT("Missing recovered widget evidence")); return false;
    }
    TestEqual(TEXT("All widget payloads decode and re-encode exactly"),Evidence->GetArrayField(TEXT("failures")).Num(),0);
    TMap<FString,UWidgetBlueprint*> Screens;
    int32 TextChecks=0,SlotChecks=0,ExpectedTexts=0,ExpectedSlots=0;
    for(const auto& Value:Evidence->GetArrayField(TEXT("widgets"))) {
        const auto Record=Value->AsObject(); const FString Screen=Record->GetStringField(TEXT("asset"));
        if(!Screens.Contains(Screen)) {
            const FString Path=TEXT("/Game/Recovery/UI/")+Screen+TEXT(".")+Screen;
            Screens.Add(Screen,LoadObject<UWidgetBlueprint>(nullptr,*Path));
            if(!TestNotNull(*Path,Screens[Screen])) return false;
            TestTrue(TEXT("Widget blueprint compiles"),Screens[Screen]->Status!=BS_Error);
            TestNotNull(TEXT("Widget tree root"),Screens[Screen]->WidgetTree->RootWidget.Get());
        }
        UWidgetTree* Tree=Screens[Screen]->WidgetTree;
        const FString Class=Record->GetStringField(TEXT("class"));
        const auto Values=Record->GetObjectField(TEXT("values"));
        const FString Name=Record->GetStringField(TEXT("name"));
        if(Class==TEXT("TextBlock") && Values->HasField(TEXT("Text"))) {
            ++ExpectedTexts;
            auto* Widget=Cast<UTextBlock>(Tree->FindWidget(FName(*Name)));
            if(!TestNotNull(*Name,Widget)) continue;
            const auto Text=Values->TryGetField(TEXT("Text"));
            const FString Expected=Text->Type==EJson::Object ? Text->AsObject()->GetStringField(TEXT("text")) : Text->AsString();
            TestEqual(*(Screen+TEXT(".")+Name+TEXT(" source text")),Widget->GetText().ToString(),Expected); ++TextChecks;
        }
        if(Class.EndsWith(TEXT("Slot"))) {
            const TSharedPtr<FJsonObject>* Content=nullptr; const TSharedPtr<FJsonObject>* Parent=nullptr;
            if(!Values->TryGetObjectField(TEXT("Content"),Content) || !Values->TryGetObjectField(TEXT("Parent"),Parent)) continue;
            ++ExpectedSlots;
            UWidget* Child=Tree->FindWidget(FName(*(*Content)->GetStringField(TEXT("name"))));
            UWidget* ExpectedParent=Tree->FindWidget(FName(*(*Parent)->GetStringField(TEXT("name"))));
            if(!TestNotNull(*(Screen+TEXT(".")+Name+TEXT(" child")),Child)) continue;
            TestTrue(*(Screen+TEXT(".")+Name+TEXT(" parent")),Child->GetParent()==ExpectedParent);
            TestNotNull(*(Name+TEXT(" slot")),Child->Slot.Get()); ++SlotChecks;
            if(Class==TEXT("CanvasPanelSlot")) {
                auto* Slot=Cast<UCanvasPanelSlot>(Child->Slot); if(!TestNotNull(*Name,Slot)) continue;
                const TSharedPtr<FJsonObject>* Layout=nullptr;
                if(Values->TryGetObjectField(TEXT("LayoutData"),Layout)) {
                    const TSharedPtr<FJsonObject>* Offsets=nullptr;
                    if((*Layout)->TryGetObjectField(TEXT("Offsets"),Offsets) && !(*Offsets)->HasField(TEXT("zero_initialized_struct"))) {
                        FMargin Actual=Slot->GetOffsets();
                        const TCHAR* Keys[]={TEXT("Left"),TEXT("Top"),TEXT("Right"),TEXT("Bottom")};
                        const float Numbers[]={Actual.Left,Actual.Top,Actual.Right,Actual.Bottom};
                        for(int32 I=0;I<4;++I) {
                            double Expected;
                            if((*Offsets)->TryGetNumberField(Keys[I],Expected)) TestEqual(*(Name+TEXT(" ")+Keys[I]),Numbers[I],float(Expected));
                        }
                    }
                }
            }
        }
    }
    TSet<FString> ExpectedScreens;
    for(const auto& Value:Evidence->GetArrayField(TEXT("widgets"))) ExpectedScreens.Add(Value->AsObject()->GetStringField(TEXT("asset")));
    TestEqual(TEXT("Every recovered screen checked"),Screens.Num(),ExpectedScreens.Num());
    TestEqual(TEXT("All serialized texts checked across screens"),TextChecks,ExpectedTexts);
    TestEqual(TEXT("All serialized parent links checked across screens"),SlotChecks,ExpectedSlots);
    TestTrue(TEXT("Nonempty text evidence"),ExpectedTexts>0);
    TestTrue(TEXT("Nonempty slot evidence"),ExpectedSlots>0);
    for(const auto& Value:Evidence->GetArrayField(TEXT("omitted_custom_widgets"))) {
        const auto Record=Value->AsObject(); const FString Screen=Record->GetStringField(TEXT("asset"));
        const FString Name=Record->GetStringField(TEXT("name"));
        auto* Widget=Screens[Screen]->WidgetTree->FindWidget(FName(*Name));
        if(TestNotNull(*Name,Widget)) TestEqual(*(Name+TEXT(" recovered nested class")),Widget->GetClass()->GetName(),Record->GetStringField(TEXT("class")));
    }
    return true;
}
#endif
