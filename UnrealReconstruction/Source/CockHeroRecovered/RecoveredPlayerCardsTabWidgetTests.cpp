#include "RecoveredPlayerCardsTabWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Engine/DataTable.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "MovieScene.h"
#include "RecoveredPlayerCardEntryWidget.h"
#include "RecoveredMenu.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPlayerCardsTabWidgetTest,"CockHero.Recovery.PlayerCardsTabWidget",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPlayerCardsTabWidgetTest::RunTest(const FString& Parameters) {
    FString EvidenceText;
    TSharedPtr<FJsonObject> Evidence;
    const FString EvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/player-cards-tab-recovery.json");
    if (!FFileHelper::LoadFileToString(EvidenceText,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(EvidenceText),Evidence)) {
        AddError(TEXT("Missing player cards tab recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Original source execution remains unclaimed"),Evidence->GetBoolField(TEXT("source_executed")));
    const TSharedPtr<FJsonObject> Entrypoints=Evidence->GetObjectField(TEXT("source_entrypoints"));
    TestEqual(TEXT("Player cards source construct entrypoint"),Entrypoints->GetIntegerField(TEXT("Construct")),1705);
    TestEqual(TEXT("Player cards source population entrypoint"),Entrypoints->GetIntegerField(TEXT("PopulatePlayerCards")),2306);
    TestEqual(TEXT("Player cards source click entrypoint"),Entrypoints->GetIntegerField(TEXT("PlayerCardClick")),2436);
    TestEqual(TEXT("Player cards source selected-card entrypoint"),Entrypoints->GetIntegerField(TEXT("ChangeSelectedPlayerCardDisplay")),2654);
    TestEqual(TEXT("Player cards source level entrypoint"),Entrypoints->GetIntegerField(TEXT("UpdateLevelDisplay")),2863);
    TestEqual(TEXT("Player cards source username entrypoint"),Entrypoints->GetIntegerField(TEXT("OnEditBoxClosed")),3804);
    const TSharedPtr<FJsonObject> Population=Evidence->GetObjectField(TEXT("population_contract"));
    TestEqual(TEXT("Source player-card count"),Population->GetIntegerField(TEXT("source_card_count")),36);
    TestEqual(TEXT("Source player-card columns"),Population->GetIntegerField(TEXT("columns")),3);
    const TSharedPtr<FJsonObject> TextureRecovery=Evidence->GetObjectField(TEXT("texture_recovery"));
    TestEqual(TEXT("Source player-card artwork count"),TextureRecovery->GetIntegerField(TEXT("source_card_images")),36);
    TestEqual(TEXT("Recovered player-card artwork count"),TextureRecovery->GetIntegerField(TEXT("recovered_texture_assets")),37);
    TestTrue(TEXT("Source locked-card placeholder restored"),TextureRecovery->GetBoolField(TEXT("locked_placeholder_recovered")));

    FString EntryEvidenceText;
    TSharedPtr<FJsonObject> EntryEvidence;
    const FString EntryEvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/player-card-entry-widget-recovery.json");
    if (!FFileHelper::LoadFileToString(EntryEvidenceText,*EntryEvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(EntryEvidenceText),EntryEvidence)) {
        AddError(TEXT("Missing player-card entry recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Player-card entry source execution remains unclaimed"),EntryEvidence->GetBoolField(TEXT("source_executed")));
    const TSharedPtr<FJsonObject> EntryEntrypoints=EntryEvidence->GetObjectField(TEXT("source_entrypoints"));
    TestEqual(TEXT("Source entry hover entrypoint"),EntryEntrypoints->GetIntegerField(TEXT("Hover")),75);
    TestEqual(TEXT("Source entry unhover entrypoint"),EntryEntrypoints->GetIntegerField(TEXT("Unhover")),187);
    TestEqual(TEXT("Source entry click entrypoint"),EntryEntrypoints->GetIntegerField(TEXT("Click")),239);
    TestEqual(TEXT("Source entry function count"),EntryEvidence->GetArrayField(TEXT("functions")).Num(),7);
    const TSharedPtr<FJsonObject> EntryLayout=EntryEvidence->GetObjectField(TEXT("layout"));
    TestEqual(TEXT("Source entry layout component count"),EntryLayout->GetIntegerField(TEXT("components")),26);
    TestTrue(TEXT("Source entry payload layout round-trips"),EntryLayout->GetBoolField(TEXT("byte_identical_component_payloads")));
    const TSharedPtr<FJsonObject> EntryReconstruction=EntryEvidence->GetObjectField(TEXT("reconstruction"));
    TestTrue(TEXT("Source entry widget tree restored"),EntryReconstruction->GetBoolField(TEXT("widget_tree_restored")));
    TestTrue(TEXT("Source entry animations restored"),EntryReconstruction->GetBoolField(TEXT("animations_restored")));
    TestEqual(TEXT("Source entry animation count"),EntryReconstruction->GetObjectField(TEXT("animation_restore"))->GetIntegerField(TEXT("animation_count")),4);

    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Player card save initializes"),Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Player card display name initializes"),Save->SetStringSetting(TEXT("Playercard_Name"),TEXT("Reyes")))) return false;

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };

    auto* Instance=NewObject<URecoveredGameInstance>();
    Instance->CurrentSave=Save;
    Instance->ProgressionManager=NewObject<URecoveredProgressionManager>(Instance);
    URecoveredProgressionManager* Progression=Instance->ProgressionManager;
    Progression->PlayerCardDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_PlayerCards.DT_PlayerCards"));
    Progression->LevelDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_LevelData.DT_LevelData"));
    Progression->ChallengeDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    Progression->CurrentLevel=3;
    Progression->CurrentXP=72;
    if (!TestNotNull(TEXT("Player cards source data table"),Progression->PlayerCardDataTable.Get())) return false;
    if (!TestNotNull(TEXT("Player cards source level table"),Progression->LevelDataTable.Get())) return false;
    if (!TestNotNull(TEXT("Player cards source challenge table"),Progression->ChallengeDataTable.Get())) return false;

    TArray<FRecoveredPlayerCardRow> SourceCards;
    Progression->GetAllPlayerCardData(SourceCards);
    TestEqual(TEXT("Player-card table feeds every restored image"),SourceCards.Num(),36);
    for (const FRecoveredPlayerCardRow& Card:SourceCards) {
        FString AssetName=Card.CardImage;
        int32 Dot=INDEX_NONE;
        if (!AssetName.FindLastChar(TEXT('.'),Dot) || Dot==AssetName.Len()-1) {
            AddError(FString::Printf(TEXT("Invalid source player-card image path: %s"),*Card.CardImage));
            continue;
        }
        AssetName=AssetName.Mid(Dot+1);
        const FString RecoveredPath=FString::Printf(TEXT("/Game/Recovery/Resources/PlayerCards/%s.%s"),*AssetName,*AssetName);
        UTexture2D* Texture=LoadObject<UTexture2D>(nullptr,*RecoveredPath);
        if (TestNotNull(*FString::Printf(TEXT("Recovered artwork exists: %s"),*AssetName),Texture)) {
            const FIntPoint ImportedSize=Texture->GetImportedSize();
            TestEqual(*FString::Printf(TEXT("Recovered artwork width: %s"),*AssetName),ImportedSize.X,900);
            TestEqual(*FString::Printf(TEXT("Recovered artwork height: %s"),*AssetName),ImportedSize.Y,200);
        }
    }
    UTexture2D* LockedTexture=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/PlayerCards/LockedPlayerCard.LockedPlayerCard"));
    if (TestNotNull(TEXT("Recovered locked player-card placeholder exists"),LockedTexture)) {
        const FIntPoint ImportedSize=LockedTexture->GetImportedSize();
        TestEqual(TEXT("Recovered locked player-card placeholder width"),ImportedSize.X,512);
        TestEqual(TEXT("Recovered locked player-card placeholder height"),ImportedSize.Y,512);
    }
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    UClass* EntryClass=LoadClass<URecoveredPlayerCardEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/PlayerCardEntryWidget.PlayerCardEntryWidget_C"));
    if (!TestNotNull(TEXT("Player-card entry recovered class"),EntryClass)) return false;
    TestTrue(TEXT("Player-card entry uses its recovered native owner"),EntryClass->IsChildOf(URecoveredPlayerCardEntryWidget::StaticClass()));
    if (auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(EntryClass)) {
        TestEqual(TEXT("Source entry restored animation count"),Generated->Animations.Num(),4);
        const auto HasSourceAnimation=[Generated](FName ExpectedName) {
            for (const TObjectPtr<UWidgetAnimation>& Animation:Generated->Animations) {
                if (!Animation) continue;
                const UMovieScene* MovieScene=Animation->GetMovieScene();
                if (
                    Animation->GetFName()==ExpectedName ||
                    (MovieScene && MovieScene->GetFName()==ExpectedName) ||
                    Animation->GetDisplayLabel().Equals(ExpectedName.ToString(),ESearchCase::CaseSensitive)
                ) return true;
            }
            return false;
        };
        for (const TCHAR* Name:{TEXT("Hover"),TEXT("Unhover"),TEXT("Click"),TEXT("UnsuccessfulClick")} ) {
            TestTrue(*FString::Printf(TEXT("Source entry animation restored: %s"),Name),HasSourceAnimation(FName(Name)));
        }
    } else AddError(TEXT("Player-card entry class lacks a recovered widget animation container"));

    auto* SourceEntry=CreateWidget<URecoveredPlayerCardEntryWidget>(World,EntryClass);
    if (!TestNotNull(TEXT("Source player-card entry instantiates"),SourceEntry)) return false;
    SourceEntry->TakeWidget();
    UTexture2D* SourceCardTexture=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/PlayerCards/Hypno_Boobs_-_Vol__1.Hypno_Boobs_-_Vol__1"));
    if (!TestNotNull(TEXT("Source player-card entry artwork"),SourceCardTexture)) return false;
    SourceEntry->PopulatePlayerCard(
        FName(TEXT("source_card")),SourceCardTexture,TEXT("source_challenge"),1,false,
        FText::FromString(TEXT("Inspect {card name}")),FText::FromString(TEXT("Ignored Source Title")),
        FText::FromString(TEXT("Source Card")),FLinearColor::Red);
    auto* EntryRoot=Cast<USizeBox>(SourceEntry->GetWidgetFromName(TEXT("SizeBox_60")));
    auto* EntryButton=Cast<UButton>(SourceEntry->GetWidgetFromName(TEXT("PlayerCardButton")));
    auto* EntryLock=Cast<UOverlay>(SourceEntry->GetWidgetFromName(TEXT("LockOverlay")));
    auto* EntryRequirement=Cast<UTextBlock>(SourceEntry->GetWidgetFromName(TEXT("UnlockRequirementText")));
    if (!TestNotNull(TEXT("Source entry root"),EntryRoot) || !TestNotNull(TEXT("Source entry button"),EntryButton) || !TestNotNull(TEXT("Source entry lock overlay"),EntryLock) || !TestNotNull(TEXT("Source entry requirement label"),EntryRequirement)) return false;
    TestEqual(TEXT("Source entry width"),EntryRoot->GetWidthOverride(),613.0f);
    TestEqual(TEXT("Source entry height"),EntryRoot->GetHeightOverride(),136.0f);
    TestEqual(TEXT("Source entry normal card art"),EntryButton->GetStyle().Normal.GetResourceObject(),static_cast<UObject*>(SourceCardTexture));
    TestEqual(TEXT("Source entry hovered card art"),EntryButton->GetStyle().Hovered.GetResourceObject(),static_cast<UObject*>(SourceCardTexture));
    TestEqual(TEXT("Source entry pressed card art"),EntryButton->GetStyle().Pressed.GetResourceObject(),static_cast<UObject*>(SourceCardTexture));
    TestEqual(TEXT("Source entry brush draw mode"),int32(EntryButton->GetStyle().Normal.DrawAs),int32(ESlateBrushDrawType::Image));
    TestEqual(TEXT("Source entry lock is visible when locked"),uint8(EntryLock->GetVisibility()),uint8(ESlateVisibility::Visible));
    TestEqual(TEXT("Source entry requirement format"),EntryRequirement->GetText().ToString(),FString(TEXT("Complete Challenge: \r\n\"source challenge\"")));
    TestTrue(TEXT("Source entry hover binding"),EntryButton->OnHovered.IsBound());
    TestTrue(TEXT("Source entry unhover binding"),EntryButton->OnUnhovered.IsBound());
    TestTrue(TEXT("Source entry click binding"),EntryButton->OnClicked.IsBound());
    if (auto* Tooltip=Cast<URecoveredTooltip>(EntryButton->GetToolTip())) {
        TestEqual(TEXT("Source locked tooltip title"),Tooltip->TooltipTitle.ToString(),FString(TEXT("Source Card - locked")));
        TestEqual(TEXT("Source locked tooltip description"),Tooltip->TooltipDescription.ToString(),FString(TEXT("Inspect Source Card")));
    } else AddError(TEXT("Source locked tooltip is missing"));
    SourceEntry->PopulatePlayerCard(
        FName(TEXT("source_card")),SourceCardTexture,TEXT("source_challenge"),1,true,
        FText::FromString(TEXT("Inspect {card name}")),FText::FromString(TEXT("Ignored Source Title")),
        FText::FromString(TEXT("Source Card")),FLinearColor::Red);
    TestEqual(TEXT("Source entry lock collapses when unlocked"),uint8(EntryLock->GetVisibility()),uint8(ESlateVisibility::Collapsed));
    if (auto* Tooltip=Cast<URecoveredTooltip>(EntryButton->GetToolTip())) {
        TestEqual(TEXT("Source unlocked tooltip title"),Tooltip->TooltipTitle.ToString(),FString(TEXT("Source Card")));
        TestEqual(TEXT("Source unlocked tooltip description"),Tooltip->TooltipDescription.ToString(),FString(TEXT("Unlocked")));
    } else AddError(TEXT("Source unlocked tooltip is missing"));

    UClass* TabClass=LoadClass<URecoveredPlayerCardsTabWidget>(nullptr,TEXT("/Game/Recovery/UI/PlayerCardsTabWidget.PlayerCardsTabWidget_C"));
    if (!TestNotNull(TEXT("Player cards recovered class"),TabClass)) return false;
    if (!TestTrue(TEXT("Player cards uses its recovered native owner"),TabClass->IsChildOf(URecoveredPlayerCardsTabWidget::StaticClass()))) return false;
    auto* Tab=CreateWidget<URecoveredPlayerCardsTabWidget>(World,TabClass);
    if (!TestNotNull(TEXT("Player cards tab instantiates"),Tab)) return false;
    Tab->SetRecoveredPlayerCardsGameInstance(Instance);
    Tab->TakeWidget();
    Tab->InitializePlayerCards();

    auto* Grid=Cast<UUniformGridPanel>(Tab->GetWidgetFromName(TEXT("PlayerCardUniformGrid")));
    if (!TestNotNull(TEXT("Source player-card uniform grid"),Grid)) return false;
    TestEqual(TEXT("All source player cards populate"),Grid->GetChildrenCount(),36);
    TestEqual(TEXT("Recovered player-card entry ledger"),Tab->GetPlayerCardEntryCount(),36);
    const FMargin GridPadding=Grid->GetSlotPadding();
    TestEqual(TEXT("Source player-card grid left padding"),GridPadding.Left,8.0f);
    TestEqual(TEXT("Source player-card grid top padding"),GridPadding.Top,8.0f);
    if (Tab->RecoveredCardEntries.Num()>=4) {
        for (const TObjectPtr<URecoveredPlayerCardEntryWidget>& Entry:Tab->RecoveredCardEntries) {
            TestEqual(TEXT("Source tab instantiates the restored entry class"),Entry->GetClass(),EntryClass);
        }
        TestEqual(TEXT("Source first card stays first"),Tab->RecoveredCardEntries[0]->CardID,FName(TEXT("catgirl_booties_pc_1")));
        TestEqual(TEXT("Source fourth card stays fourth"),Tab->RecoveredCardEntries[3]->CardID,FName(TEXT("hypnoboobs_pc_1")));
        TestFalse(TEXT("Source challenge-gated card stays locked"),Tab->RecoveredCardEntries[0]->bUnlocked);
    } else {
        AddError(TEXT("Missing recovered player-card entries"));
    }
    if (auto* FirstSlot=Cast<UUniformGridSlot>(Grid->GetChildAt(0)->Slot)) {
        TestEqual(TEXT("Source first card row"),FirstSlot->GetRow(),0);
        TestEqual(TEXT("Source first card column"),FirstSlot->GetColumn(),0);
    } else AddError(TEXT("Missing source first player-card slot"));
    if (auto* FourthSlot=Cast<UUniformGridSlot>(Grid->GetChildAt(3)->Slot)) {
        TestEqual(TEXT("Source fourth card row"),FourthSlot->GetRow(),1);
        TestEqual(TEXT("Source fourth card column"),FourthSlot->GetColumn(),0);
    } else AddError(TEXT("Missing source fourth player-card slot"));

    const FName FreeCard(TEXT("cybergirls_pc_2"));
    const FName SelectableCard(TEXT("hypnoboobs_pc_1"));
    const FName LockedCard(TEXT("catgirl_booties_pc_1"));
    TestTrue(TEXT("Source no-gate card unlocks during population"),Progression->IsPlayerCardUnlocked(FreeCard));
    TestEqual(TEXT("Source initializes the first unlocked player card"),Progression->GetEquippedPlayerCard(),FreeCard);
    TestTrue(TEXT("Source selectable card unlocks for selection test"),Progression->UnlockPlayerCard(SelectableCard));
    Tab->PlayerCardClick(SelectableCard);
    TestEqual(TEXT("Source unlocked click equips selected card"),Progression->GetEquippedPlayerCard(),SelectableCard);
    auto* SelectedImage=Cast<UImage>(Tab->GetWidgetFromName(TEXT("SelectedPlayerCard")));
    if (TestNotNull(TEXT("Source selected player-card image"),SelectedImage)) {
        UTexture2D* HypnoTexture=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/PlayerCards/Hypno_Boobs_-_Vol__1.Hypno_Boobs_-_Vol__1"));
        TestEqual(TEXT("Source selected player-card brush"),SelectedImage->GetBrush().GetResourceObject(),static_cast<UObject*>(HypnoTexture));
    }
    Tab->PlayerCardClick(LockedCard);
    TestEqual(TEXT("Source locked click leaves equipped card unchanged"),Progression->GetEquippedPlayerCard(),SelectableCard);

    if (auto* LevelText=Cast<UTextBlock>(Tab->GetWidgetFromName(TEXT("TitleLevelText")))) {
        TestEqual(TEXT("Source player-card level text"),LevelText->GetText().ToString(),FString(TEXT("Level: 3 - Sophomore Slapper")));
    } else AddError(TEXT("Missing source player-card level text"));
    if (auto* LevelMeter=Cast<UProgressBar>(Tab->GetWidgetFromName(TEXT("LevelMeter")))) {
        TestEqual(TEXT("Source player-card level progress"),LevelMeter->GetPercent(),72.0f/145.0f);
    } else AddError(TEXT("Missing source player-card level meter"));
    if (auto* PlayerName=Cast<UTextBlock>(Tab->GetWidgetFromName(TEXT("PlayerCardName")))) {
        TestEqual(TEXT("Source player-card username"),PlayerName->GetText().ToString(),FString(TEXT("Reyes")));
    } else AddError(TEXT("Missing source player-card username"));
    if (auto* EditButton=Cast<UButton>(Tab->GetWidgetFromName(TEXT("EditPlayerCardButton")))) {
        TestTrue(TEXT("Source username edit binding"),EditButton->OnClicked.IsBound());
    } else AddError(TEXT("Missing source player-card edit button"));

    Save->SetStringSetting(TEXT("Playercard_Name"),TEXT("Diaz"));
    if (UFunction* Closed=Tab->FindFunction(TEXT("OnEditBoxClosed"))) Tab->ProcessEvent(Closed,nullptr);
    else AddError(TEXT("Missing source player-card edit-close path"));
    if (auto* PlayerName=Cast<UTextBlock>(Tab->GetWidgetFromName(TEXT("PlayerCardName")))) {
        TestEqual(TEXT("Source close refreshes player-card username"),PlayerName->GetText().ToString(),FString(TEXT("Diaz")));
    }

    const FString State=Progression->ExportRecoveryState();
    auto* RoundTrip=NewObject<URecoveredProgressionManager>();
    RoundTrip->PlayerCardDataTable=Progression->PlayerCardDataTable;
    TestTrue(TEXT("Player-card selection serializes"),RoundTrip->ImportRecoveryState(State));
    TestEqual(TEXT("Player-card selection restores"),RoundTrip->GetEquippedPlayerCard(),SelectableCard);
    return true;
}
#endif
