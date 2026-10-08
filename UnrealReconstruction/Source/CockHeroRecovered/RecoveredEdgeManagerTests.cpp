#include "RecoveredEdgeManager.h"
#include "RecoveredRules.h"
#include "RecoveredTabbedInventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "Sound/SoundBase.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredEdgeHoldLifecycleTest,"CockHero.Recovery.EdgeHoldLifecycle",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredEdgeHoldLifecycleTest::RunTest(const FString& Parameters) {
    TestNotNull(TEXT("Recovered edge countdown sound"),LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/1sec_clocktick.1sec_clocktick")));
    TestNotNull(TEXT("Recovered edge hold icon"),LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/InventoryButtonPNGs/EdgeItem.EdgeItem")));
    for (int32 Second=1;Second<=8;++Second) {
        const FString Name=FString::Printf(TEXT("HoldIt_Edge_%dSeconds"),Second);
        const FString Path=FString::Printf(TEXT("/Game/Recovery/Resources/Widgets/SpecialEventWidgets/%s.%s"),*Name,*Name);
        TestNotNull(*FString::Printf(TEXT("Recovered source countdown image %d"),Second),LoadObject<UTexture2D>(nullptr,*Path));
    }
    TestNotNull(TEXT("Recovered edge hold overlay"),LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/EdgeHoldCountdown_Overlay_Widget.EdgeHoldCountdown_Overlay_Widget_C")));
    UClass* EdgeBlueprintClass=LoadClass<ARecoveredEdgeManager>(nullptr,TEXT("/Game/NewSetup/BP_EdgeManager.BP_EdgeManager_C"));
    if (!TestNotNull(TEXT("Recovered edge manager blueprint"),EdgeBlueprintClass)) return false;
    TestTrue(TEXT("Recovered edge manager blueprint uses native owner"),EdgeBlueprintClass->IsChildOf(ARecoveredEdgeManager::StaticClass()));
    UClass* InventoryBlueprintClass=LoadClass<URecoveredTabbedInventoryWidget>(nullptr,TEXT("/Game/Recovery/UI/PG1TabbedInventory_Widget.PG1TabbedInventory_Widget_C"));
    if (!TestNotNull(TEXT("Recovered PG1 inventory widget"),InventoryBlueprintClass)) return false;
    TestTrue(TEXT("Recovered PG1 inventory widget uses native owner"),InventoryBlueprintClass->IsChildOf(URecoveredTabbedInventoryWidget::StaticClass()));

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());
    auto* Inventory=CreateWidget<URecoveredTabbedInventoryWidget>(World,InventoryBlueprintClass);
    if (!TestNotNull(TEXT("Recovered PG1 widget instantiates"),Inventory)) return false;
    TestNotNull(TEXT("Recovered PG1 edge button survives reparenting"),Cast<UButton>(Inventory->GetWidgetFromName(TEXT("EdgeItemButton"))));
    UTextBlock* EdgeQuantity=Cast<UTextBlock>(Inventory->GetWidgetFromName(TEXT("QuantityAmount_2")));
    if (!EdgeQuantity) {
        if (auto* Item=Cast<UUserWidget>(Inventory->GetWidgetFromName(TEXT("ItemButton_2")))) EdgeQuantity=Cast<UTextBlock>(Item->GetWidgetFromName(TEXT("QuantityAmount")));
    }
    TestNotNull(TEXT("Recovered PG1 source edge count label survives reparenting"),EdgeQuantity);
    TestEqual(TEXT("Recovered PG1 source edge count format"),Inventory->GetEdgeAvailableText().ToString(),FString(TEXT("(0)")));
    ARecoveredGlobalManager* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    ARecoveredEdgeManager* Edge=World->SpawnActor<ARecoveredEdgeManager>();
    if (!TestNotNull(TEXT("Recovered global timer owner"),Manager) || !TestNotNull(TEXT("Recovered edge timer actor"),Edge)) return false;
    Manager->EdgingManager=Edge;
    Edge->SetRecoveredGlobalManager(Manager);

    Manager->BeatContext.CardType=5;
    Edge->BeginRecoveredEdgeHold(3.9);
    TestEqual(TEXT("Source hold duration truncates before presentation"),Edge->CurrentEdgeHoldDuration,3.0);
    TestTrue(TEXT("Source one-second hold timer starts"),Edge->IsRecoveredEdgeHoldActive());
    FRecoveredOutcomeEffects Early;
    Early.bClearEdgeHoldTimer=true;
    Manager->HandleRecoveredOutcome(Early);
    TestFalse(TEXT("Early outcome clears the source edge hold timer"),Edge->IsRecoveredEdgeHoldActive());

    Edge->BeginRecoveredEdgeHold(2.9);
    FRecoveredOutcomeEffects Successful;
    Successful.OutcomeOverlaySourceIndex=-4047;
    Manager->HandleRecoveredOutcome(Successful);
    TestTrue(TEXT("Successful outcome leaves the source edge hold timer active"),Edge->IsRecoveredEdgeHoldActive());
    Edge->ClearRecoveredEdgeHold();

    Edge->BeginRecoveredEdgeHold(3.0);
    Manager->BeatContext.CardType=6;
    Edge->CountdownEdgeHold();
    TestEqual(TEXT("Outcome-card guard preserves source hold duration"),Edge->CurrentEdgeHoldDuration,3.0);
    TestTrue(TEXT("Outcome-card guard leaves the source timer active"),Edge->IsRecoveredEdgeHoldActive());
    Edge->ClearRecoveredEdgeHold();

    Manager->BeatContext.CardType=5;
    Edge->CurrentEdgesUntillNextMercy=2;
    Edge->BeginRecoveredEdgeHold(1.0);
    Edge->CountdownEdgeHold();
    TestFalse(TEXT("Expiry clears source hold timer"),Edge->IsRecoveredEdgeHoldActive());
    TestEqual(TEXT("Non-mercy expiry decrements source edge count"),Edge->CurrentEdgesUntillNextMercy,1);

    Edge->CurrentEdgesUntillNextMercy=1;
    Edge->BeginRecoveredEdgeHold(1.0);
    Edge->CountdownEdgeHold();
    TestEqual(TEXT("Mercy expiry retains final source edge count"),Edge->CurrentEdgesUntillNextMercy,1);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->EdgeBank=0;
    Manager->CumMeterPercentage=0;
    Manager->EdgeStreak=0;
    Manager->bPlayerEdgedLastDraw=false;
    Manager->PlayerVariables.CurrentComboCount=12;
    Manager->PlayerVariables.SessionLength=43;
    Edge->PostEdgeBreakDuration=1.0;
    const int32 FirstEdgeInventory=Manager->GetOwnedItemCount(TEXT("Edge"));
    TestTrue(TEXT("First source edge starts the recovered edge streak"),Edge->TriggerRecoveredEdgeV2());
    TestEqual(TEXT("First source edge records its session metric"),Manager->SessionStats.Edges,1);
    TestEqual(TEXT("First source edge sets the streak"),Manager->EdgeStreak,1);
    TestEqual(TEXT("First source edge restores mercy count"),Edge->CurrentEdgesUntillNextMercy,Edge->MasterEdgesUntilNextMercy);
    TestEqual(TEXT("First source edge uses its 1.75-second break duration"),Edge->PostEdgeBreakDuration,1.75);
    TestTrue(TEXT("First source edge schedules its one-second handoff"),Edge->IsRecoveredEdgeResolutionPending());
    TestTrue(TEXT("First source edge grants its replacement inventory item"),Manager->GetOwnedItemCount(TEXT("Edge"))==FirstEdgeInventory+1);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->EdgeBank=0;
    Manager->CumMeterPercentage=0;
    Manager->EdgeStreak=0;
    Manager->bPlayerEdgedLastDraw=true;
    Manager->PlayerVariables.AssignedStrokeCount=100;
    Manager->BeatTimeline->TotalStrokes=100;
    Manager->BeatTimeline->CompletedBeats=50;
    Edge->PostEdgeBreakDuration=1.0;
    TestTrue(TEXT("Normal source edge triggers"),Edge->TriggerRecoveredEdgeV2());
    TestEqual(TEXT("Normal source edge retains its measured ratio"),Edge->LastEdgeRatio,0.5);
    TestFalse(TEXT("Normal source edge is not classified perfect"),Edge->bIsPerfectEdge);
    TestEqual(TEXT("Normal source edge grants the source bank amount"),Manager->EdgeBank,30);
    TestEqual(TEXT("Normal source edge adds the source meter amount"),Manager->CumMeterPercentage,0.05);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->EdgeBank=0;
    Manager->CumMeterPercentage=0;
    Manager->EdgeStreak=5;
    Manager->bPlayerEdgedLastDraw=true;
    Manager->PlayerVariables.AssignedStrokeCount=100;
    Manager->BeatTimeline->TotalStrokes=100;
    Manager->BeatTimeline->CompletedBeats=100;
    Edge->PostEdgeBreakDuration=2.0;
    TestTrue(TEXT("Perfect source edge triggers"),Edge->TriggerRecoveredEdgeV2());
    TestEqual(TEXT("Perfect source edge retains its measured ratio"),Edge->LastEdgeRatio,1.0);
    TestTrue(TEXT("Perfect source edge uses the 85-percent classification"),Edge->bIsPerfectEdge);
    TestEqual(TEXT("Perfect source edge grants the source bank amount"),Manager->EdgeBank,50);
    TestEqual(TEXT("Perfect source edge adds the source meter amount"),Manager->CumMeterPercentage,0.08);
    TestEqual(TEXT("Perfect source edge records the source metric"),Manager->SessionStats.PerfectEdges,1);
    TestEqual(TEXT("Perfect source edge stages its truncated post-edge duration"),Edge->MasterEdgeHoldDuration,3.0);
    TestTrue(TEXT("Perfect source edge schedules the source 0.9-second handoff"),Edge->IsRecoveredEdgeResolutionPending());

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->OwnedItemCounts.Empty();
    Manager->EdgeStreak=0;
    Manager->bPlayerEdgedLastDraw=false;
    Manager->BeatContext.CardType=0;
    Manager->PlayerVariables.bCanUseItems=false;
    Manager->OwnedItemCounts.Add(TEXT("Edge"),1);
    TestFalse(TEXT("Source edge inventory blocks when item use is disabled outside edge cards"),Manager->CanUseRecoveredEdgeItem());
    TestEqual(TEXT("Source disabled item gate does not consume an edge"),Manager->UseRecoveredEdgeItem(),ERecoveredEdgeItemUseResult::CannotUseItems);
    TestEqual(TEXT("Source disabled item gate retains the edge"),Manager->GetOwnedItemCount(TEXT("Edge")),1);

    Manager->BeatContext.CardType=5;
    TestTrue(TEXT("Source edge-card exception permits the edge item"),Manager->CanUseRecoveredEdgeItem());
    Manager->PlayerVariables.TotalTauntsUsed=5;
    TestEqual(TEXT("Source punishment risk rises by 20 after five taunts"),Manager->GetRecoveredPunishmentChance(),20.0);
    Manager->PlayerVariables.TotalTauntsUsed=25;
    TestEqual(TEXT("Source punishment risk reaches 100 after twenty-five taunts"),Manager->GetRecoveredPunishmentChance(),100.0);
    TestEqual(TEXT("Source punishment resolves before triggering or consuming the edge"),Manager->UseRecoveredEdgeItem(),ERecoveredEdgeItemUseResult::PunishmentTriggered);
    TestEqual(TEXT("Source punishment retains the edge"),Manager->GetOwnedItemCount(TEXT("Edge")),1);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->EdgeStreak=0;
    Manager->bPlayerEdgedLastDraw=false;
    Manager->BeatContext.CardType=0;
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Edge"),1);
    TestTrue(TEXT("Source edge commit triggers the native edge owner"),Manager->CommitRecoveredEdgeItemUse());
    TestEqual(TEXT("Source edge commit grants then spends one edge"),Manager->GetOwnedItemCount(TEXT("Edge")),1);
    TestEqual(TEXT("Source edge commit records the edge"),Manager->SessionStats.Edges,1);
    return true;
}
#endif
