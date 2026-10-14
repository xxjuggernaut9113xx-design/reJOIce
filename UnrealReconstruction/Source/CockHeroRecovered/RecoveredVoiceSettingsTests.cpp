#include "RecoveredMenu.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Dom/JsonObject.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "MovieScene.h"
#include "RecoveredRules.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Widgets/SWidget.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
namespace {

bool LoadVoiceJson(const TCHAR* RelativePath,TSharedPtr<FJsonObject>& OutObject) {
    FString Text;
    return FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/RelativePath))
        && FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),OutObject)
        && OutObject.IsValid();
}

bool HasVoiceSourceAnimation(const UWidgetBlueprintGeneratedClass* Generated,FName Name) {
    if (!Generated) return false;
    const FName InstanceName(*FString::Printf(TEXT("%s_INST"),*Name.ToString()));
    for (const TObjectPtr<UWidgetAnimation>& Animation:Generated->Animations) {
        if (!Animation) continue;
        const UMovieScene* Scene=Animation->GetMovieScene();
        if (
            Animation->GetFName()==Name || Animation->GetFName()==InstanceName
            || Animation->GetDisplayLabel().Equals(Name.ToString(),ESearchCase::CaseSensitive)
            || Animation->GetDisplayLabel().Equals(InstanceName.ToString(),ESearchCase::CaseSensitive)
            || (Scene && (Scene->GetFName()==Name || Scene->GetFName()==InstanceName))
        ) return true;
    }
    return false;
}

URecoveredVoicePackEntryWidget* FindVoiceEntry(UScrollBox* Scrollbox,const TCHAR* DisplayName) {
    if (!Scrollbox) return nullptr;
    for (int32 Index=0;Index<Scrollbox->GetChildrenCount();++Index) {
        auto* Entry=Cast<URecoveredVoicePackEntryWidget>(Scrollbox->GetChildAt(Index));
        if (Entry && Entry->DisplayNameID.ToString()==DisplayName) return Entry;
    }
    return nullptr;
}

}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredVoiceSettingsTest,"CockHero.Recovery.VoicelineSettings",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredVoiceSettingsTest::RunTest(const FString& Parameters) {
    TSharedPtr<FJsonObject> Evidence,Catalog;
    if (!LoadVoiceJson(TEXT("RecoveryEvidence/voice-pack-recovery.json"),Evidence)
        || !LoadVoiceJson(TEXT("RecoveryEvidence/voice-pack-catalog.json"),Catalog)) {
        AddError(TEXT("Missing voice-pack recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Voice-pack original source execution remains unclaimed"),Evidence->GetBoolField(TEXT("source_executed")));
    TestEqual(TEXT("Shipping voice-pack row count"),int32(Evidence->GetIntegerField(TEXT("row_count"))),4);
    TestEqual(TEXT("Shipping voice-pack reference count"),int32(Evidence->GetIntegerField(TEXT("sound_reference_count"))),16);
    TestEqual(TEXT("Available shipping voice payload count"),int32(Evidence->GetIntegerField(TEXT("available_sound_payload_count"))),16);
    TestEqual(TEXT("Unavailable shipping voice payload count"),Evidence->GetArrayField(TEXT("unavailable_sound_payloads")).Num(),0);
    TestEqual(TEXT("Source table row count"),Catalog->GetArrayField(TEXT("packs")).Num(),4);
    const TArray<TSharedPtr<FJsonValue>>& SourceOrder=Catalog->GetArrayField(TEXT("source_row_order"));
    const TCHAR* ExpectedOrder[]={TEXT("Villainess"),TEXT("Teasing Brat"),TEXT("Dommy Mommy"),TEXT("Sweetheart")};
    for (int32 Index=0;Index<UE_ARRAY_COUNT(ExpectedOrder);++Index) {
        TestEqual(TEXT("Shipping voice-pack order"),SourceOrder[Index]->AsString(),FString(ExpectedOrder[Index]));
        const TSharedPtr<FJsonObject> Pack=Catalog->GetArrayField(TEXT("packs"))[Index]->AsObject();
        TestEqual(TEXT("Shipping voice enum value"),int32(Pack->GetIntegerField(TEXT("voice_pack_enum"))),Index);
        TestEqual(TEXT("Shipping voice tag count"),Pack->GetArrayField(TEXT("tags")).Num(),4);
        TestEqual(TEXT("Shipping voice source import count"),Pack->GetArrayField(TEXT("source_import_refs")).Num(),4);
    }

    UClass* VoiceClass=LoadClass<URecoveredVoiceSettings>(nullptr,TEXT("/Game/Recovery/UI/VoicelineSettingsMenu.VoicelineSettingsMenu_C"));
    UClass* EntryClass=LoadClass<URecoveredVoicePackEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/VoicePackEntryWidget.VoicePackEntryWidget_C"));
    if (!TestNotNull(TEXT("Recovered voice settings class"),VoiceClass)
        || !TestNotNull(TEXT("Recovered voice entry class"),EntryClass)) return false;
    TestTrue(TEXT("Voice settings class uses recovered native graph"),VoiceClass->IsChildOf(URecoveredVoiceSettings::StaticClass()));
    TestTrue(TEXT("Voice entry class uses recovered native graph"),EntryClass->IsChildOf(URecoveredVoicePackEntryWidget::StaticClass()));
    auto* VoiceGenerated=Cast<UWidgetBlueprintGeneratedClass>(VoiceClass);
    auto* EntryGenerated=Cast<UWidgetBlueprintGeneratedClass>(EntryClass);
    for (const TCHAR* Animation:{TEXT("EquipButtonClick"),TEXT("EquipButtonHover"),TEXT("EquipButtonUnhover"),TEXT("Sample1ButtonClick"),TEXT("Sample1ButtonHover"),TEXT("Sample1ButtonUnhover"),TEXT("Sample2ButtonClick"),TEXT("Sample2ButtonHover"),TEXT("Sample2ButtonUnhover"),TEXT("Sample3ButtonClick"),TEXT("Sample3ButtonHover"),TEXT("Sample3ButtonUnhover"),TEXT("SelectPackAnim")}) {
        TestTrue(*FString::Printf(TEXT("Voice source animation %s"),Animation),HasVoiceSourceAnimation(VoiceGenerated,FName(Animation)));
    }
    TestTrue(TEXT("Voice entry hover animation"),HasVoiceSourceAnimation(EntryGenerated,TEXT("OnHover")));
    TestTrue(TEXT("Voice entry unhover animation"),HasVoiceSourceAnimation(EntryGenerated,TEXT("Unhover")));

    FWorldInitializationValues Initialization;
    Initialization.AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>(World);
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Voice test save initializes"),Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Voice selected pack test value persists"),Save->SetNumberSetting(TEXT("SelectedVoicePack"),2))) return false;
    if (!TestTrue(TEXT("Voice SPH test value persists"),Save->SetBoolSetting(TEXT("SPHEnabled?"),false))) return false;
    const FString TestSlot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("VoiceSettingsAutomation");
    UGameplayStatics::DeleteGameInSlot(TestSlot,0);
    ON_SCOPE_EXIT { UGameplayStatics::DeleteGameInSlot(TestSlot,0); };
    Instance->CurrentSave=Save;
    Instance->ActiveRecoverySlot=TestSlot;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    auto* Menu=CreateWidget<URecoveredVoiceSettings>(World,VoiceClass);
    if (!TestNotNull(TEXT("Recovered voice settings instantiates"),Menu)) return false;
    TSharedRef<SWidget> SlateWidget=Menu->TakeWidget();
    auto* Scrollbox=Cast<UScrollBox>(Menu->GetWidgetFromName(TEXT("PacksScrollbox")));
    auto* EquipButton=Cast<UButton>(Menu->GetWidgetFromName(TEXT("EquipButton")));
    auto* Sample1Button=Cast<UButton>(Menu->GetWidgetFromName(TEXT("Sample1Button")));
    auto* Sample2Button=Cast<UButton>(Menu->GetWidgetFromName(TEXT("Sample2Button")));
    auto* Sample3Button=Cast<UButton>(Menu->GetWidgetFromName(TEXT("Sample3Button")));
    auto* Combo=Cast<UComboBoxString>(Menu->GetWidgetFromName(TEXT("HealthBarAndTextComboBox")));
    auto* EquipText=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("EquipButtonText")));
    auto* PackTitle=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("PackTitle")));
    auto* PackDescription=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("PackDescription")));
    auto* Tag1=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("Tag1")));
    auto* Tag2=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("Tag2")));
    auto* Tag3=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("Tag3")));
    auto* Tag4=Cast<UTextBlock>(Menu->GetWidgetFromName(TEXT("Tag4")));
    if (!TestNotNull(TEXT("Source voice scrollbox"),Scrollbox)
        || !TestNotNull(TEXT("Source equip button"),EquipButton)
        || !TestNotNull(TEXT("Source sample 1 button"),Sample1Button)
        || !TestNotNull(TEXT("Source sample 2 button"),Sample2Button)
        || !TestNotNull(TEXT("Source sample 3 button"),Sample3Button)
        || !TestNotNull(TEXT("Source SPH combo"),Combo)
        || !TestNotNull(TEXT("Source equip text"),EquipText)
        || !TestNotNull(TEXT("Source pack title"),PackTitle)
        || !TestNotNull(TEXT("Source pack description"),PackDescription)
        || !TestNotNull(TEXT("Source tag 1"),Tag1)
        || !TestNotNull(TEXT("Source tag 2"),Tag2)
        || !TestNotNull(TEXT("Source tag 3"),Tag3)
        || !TestNotNull(TEXT("Source tag 4"),Tag4)) return false;
    TestTrue(TEXT("Voice settings marks source voicelines triggerable"),Menu->bVoicelinesAllowedToTrigger);
    TestTrue(TEXT("Voice settings clears catalog error"),Menu->LastVoiceError.IsEmpty());
    TestEqual(TEXT("Voice settings loads all source rows"),Menu->VoicePacks.Num(),4);
    TestEqual(TEXT("Voice settings creates all source entries"),Menu->GetVoicePackEntryCount(),4);
    TestEqual(TEXT("Voice settings attaches entries to source scrollbox"),Scrollbox->GetChildrenCount(),4);
    TestEqual(TEXT("Saved source enum selects Dommy Mommy"),Menu->EquippedPack.ToString(),FString(TEXT("Dommy Mommy")));
    TestEqual(TEXT("Construct selects saved source pack"),Menu->SelectedPack.ToString(),FString(TEXT("Dommy Mommy")));
    TestEqual(TEXT("Construct source label marks saved pack equipped"),EquipText->GetText().ToString(),FString(TEXT("Equipped")));
    TestEqual(TEXT("Construct source title"),PackTitle->GetText().ToString(),FString(TEXT("Dommy Mommy")));
    TestEqual(TEXT("Construct source tag 1"),Tag1->GetText().ToString(),FString(TEXT("praise")));
    TestEqual(TEXT("Construct source tag 2"),Tag2->GetText().ToString(),FString(TEXT("dominant")));
    TestEqual(TEXT("Construct source tag 3"),Tag3->GetText().ToString(),FString(TEXT("soft")));
    TestEqual(TEXT("Construct source tag 4"),Tag4->GetText().ToString(),FString(TEXT("caring")));
    TestEqual(TEXT("Construct source description"),PackDescription->GetText().ToString(),FString(TEXT("A warm, dominant presence who knows how to make you behave. She rewards good boys, corrects bad ones, and keeps you right where she wants you — needy and obedient.")));
    TestTrue(TEXT("Source equip binding"),EquipButton->OnClicked.IsBound());
    TestTrue(TEXT("Source equip hover binding"),EquipButton->OnHovered.IsBound());
    TestTrue(TEXT("Source equip unhover binding"),EquipButton->OnUnhovered.IsBound());
    TestTrue(TEXT("Source sample 1 binding"),Sample1Button->OnClicked.IsBound());
    TestTrue(TEXT("Source sample 2 binding"),Sample2Button->OnClicked.IsBound());
    TestTrue(TEXT("Source sample 3 binding"),Sample3Button->OnClicked.IsBound());
    TestTrue(TEXT("Source SPH selection binding"),Combo->OnSelectionChanged.IsBound());

    auto* CheatCodeRedeemText=NewObject<UTextBlock>(Menu);
    CheatCodeRedeemText->SetVisibility(ESlateVisibility::Visible);
    Menu->ChangeCheatCodeRedeemVisibility(CheatCodeRedeemText);
    TestEqual(TEXT("Source cheat-code redeem helper collapses target"),CheatCodeRedeemText->GetVisibility(),ESlateVisibility::Collapsed);

    auto* Villainess=FindVoiceEntry(Scrollbox,TEXT("Villainess"));
    auto* Brat=FindVoiceEntry(Scrollbox,TEXT("Teasing Brat"));
    auto* Dommy=FindVoiceEntry(Scrollbox,TEXT("Dommy Mommy"));
    auto* Sweetheart=FindVoiceEntry(Scrollbox,TEXT("Sweetheart"));
    if (!TestNotNull(TEXT("Villainess source entry"),Villainess)
        || !TestNotNull(TEXT("Teasing Brat source entry"),Brat)
        || !TestNotNull(TEXT("Dommy Mommy source entry"),Dommy)
        || !TestNotNull(TEXT("Sweetheart source entry"),Sweetheart)) return false;
    TestEqual(TEXT("Source entry enum Villainess"),Villainess->VoicePackEnum,uint8(0));
    TestEqual(TEXT("Source entry enum Brat"),Brat->VoicePackEnum,uint8(1));
    TestEqual(TEXT("Source entry enum Dommy"),Dommy->VoicePackEnum,uint8(2));
    TestEqual(TEXT("Source entry enum Sweetheart"),Sweetheart->VoicePackEnum,uint8(3));
    TestNotNull(TEXT("Villainess source sample one imported"),Villainess->SampleLine1.Get());
    TestNotNull(TEXT("Villainess source sample two imported"),Villainess->SampleLine2.Get());
    TestNotNull(TEXT("Villainess source sample three imported"),Villainess->SampleLine3.Get());
    TestNotNull(TEXT("Villainess source selection imported"),Villainess->SelectionLine.Get());
    TestNotNull(TEXT("Brat source sample one imported"),Brat->SampleLine1.Get());
    TestNotNull(TEXT("Brat source sample two imported"),Brat->SampleLine2.Get());
    TestNotNull(TEXT("Brat source sample three imported"),Brat->SampleLine3.Get());
    TestNotNull(TEXT("Brat source selection imported"),Brat->SelectionLine.Get());
    for (URecoveredVoicePackEntryWidget* Entry:{Villainess,Brat,Dommy,Sweetheart}) {
        auto* Button=Cast<UButton>(Entry->GetWidgetFromName(TEXT("ClickPackButton")));
        if (!TestNotNull(TEXT("Source voice entry button"),Button)) continue;
        TestTrue(TEXT("Source voice entry click binding"),Button->OnClicked.IsBound());
        TestTrue(TEXT("Source voice entry hover binding"),Button->OnHovered.IsBound());
        TestTrue(TEXT("Source voice entry unhover binding"),Button->OnUnhovered.IsBound());
    }

    auto* SweetheartButton=Cast<UButton>(Sweetheart->GetWidgetFromName(TEXT("ClickPackButton")));
    if (!TestNotNull(TEXT("Sweetheart source click button"),SweetheartButton)) return false;
    SweetheartButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source entry click selects Sweetheart"),Menu->SelectedPack.ToString(),FString(TEXT("Sweetheart")));
    TestEqual(TEXT("Source entry click copies enum"),Menu->VoicePackEnum,uint8(3));
    TestEqual(TEXT("Source entry click updates title"),PackTitle->GetText().ToString(),FString(TEXT("Sweetheart")));
    TestEqual(TEXT("Source entry click updates description"),PackDescription->GetText().ToString(),FString(TEXT("A tender, affectionate lover who adores you. She guides softly, praises freely, and pulls you close with warm, romantic sweetness.")));
    TestEqual(TEXT("Source entry click enables equip label"),EquipText->GetText().ToString(),FString(TEXT("Equip")));
    EquipButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source equip updates equipped pack"),Menu->EquippedPack.ToString(),FString(TEXT("Sweetheart")));
    TestEqual(TEXT("Source equip updates save enum"),int32(Save->GetNumberSetting(TEXT("SelectedVoicePack"))),3);
    TestEqual(TEXT("Source equip label"),EquipText->GetText().ToString(),FString(TEXT("Equipped")));
    TestTrue(TEXT("Source equip writes isolated save"),UGameplayStatics::DoesSaveGameExist(TestSlot,0));
    Menu->PackClicked(FText::FromString(TEXT("sweetheart")),Sweetheart);
    EquipButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source case-insensitive duplicate equip preserves enum"),int32(Save->GetNumberSetting(TEXT("SelectedVoicePack"))),3);

    Combo->OnSelectionChanged.Broadcast(TEXT("on"),ESelectInfo::Direct);
    TestTrue(TEXT("Source SPH on persists"),Save->GetBoolSetting(TEXT("SPHEnabled?")));
    Combo->OnSelectionChanged.Broadcast(TEXT("off"),ESelectInfo::Direct);
    TestFalse(TEXT("Source SPH off persists"),Save->GetBoolSetting(TEXT("SPHEnabled?")));
    Combo->OnSelectionChanged.Broadcast(TEXT("invalid"),ESelectInfo::Direct);
    TestFalse(TEXT("Source unsupported SPH choice preserves save"),Save->GetBoolSetting(TEXT("SPHEnabled?")));
    Sample1Button->OnClicked.Broadcast();
    Sample2Button->OnClicked.Broadcast();
    Sample3Button->OnClicked.Broadcast();
    TestEqual(TEXT("Source preview clicks preserve selected pack"),Menu->SelectedPack.ToString(),FString(TEXT("sweetheart")));
    return true;
}
#endif
