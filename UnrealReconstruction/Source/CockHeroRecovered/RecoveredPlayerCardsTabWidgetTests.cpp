#include "RecoveredPlayerCardsTabWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
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
#include "RecoveredPlayerCardEntryWidget.h"
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
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

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
