#include "RecoveredEdgeManager.h"
#include "RecoveredPG2TabbedInventoryWidget.h"
#include "Sound/SoundBase.h"
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPG2ResupplyTest,"CockHero.Recovery.PG2Resupply",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPG2ResupplyTest::RunTest(const FString& Parameters) {
    UClass* InventoryBlueprintClass=LoadClass<URecoveredPG2TabbedInventoryWidget>(nullptr,TEXT("/Game/Recovery/UI/PG2TabbedInventory_Widget.PG2TabbedInventory_Widget_C"));
    if (!TestNotNull(TEXT("Recovered PG2 inventory widget"),InventoryBlueprintClass)) return false;
    TestTrue(TEXT("Recovered PG2 inventory widget uses native owner"),InventoryBlueprintClass->IsChildOf(URecoveredPG2TabbedInventoryWidget::StaticClass()));
    TestNotNull(TEXT("Recovered PG2 source notification cue"),LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/new-notification-020-352772.new-notification-020-352772")));

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());

    auto* Inventory=CreateWidget<URecoveredPG2TabbedInventoryWidget>(World,InventoryBlueprintClass);
    if (!TestNotNull(TEXT("Recovered PG2 widget instantiates"),Inventory)) return false;
    TestNotNull(TEXT("Recovered PG2 resupply button survives reparenting"),Cast<UButton>(Inventory->GetWidgetFromName(TEXT("ResupplyButton"))));
    UTextBlock* ResupplyQuantity=Cast<UTextBlock>(Inventory->GetWidgetFromName(TEXT("QuantityAmount")));
    if (!ResupplyQuantity) {
        if (auto* Item=Cast<UUserWidget>(Inventory->GetWidgetFromName(TEXT("ItemButton")))) ResupplyQuantity=Cast<UTextBlock>(Item->GetWidgetFromName(TEXT("QuantityAmount")));
    }
    TestNotNull(TEXT("Recovered PG2 source resupply count label survives reparenting"),ResupplyQuantity);
    TestEqual(TEXT("Recovered PG2 source resupply count format"),Inventory->GetResupplyCount().ToString(),FString(TEXT("(0)")));

    ARecoveredGlobalManager* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Recovered PG2 global manager"),Manager)) return false;
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->PlayerVariables.bCanUseItems=false;
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Resupply"),1);
    TestFalse(TEXT("Source resupply blocks when item use is disabled"),Manager->CanUseRecoveredResupplyItem());
    TestEqual(TEXT("Source resupply disabled gate returns its original result"),Manager->UseRecoveredResupplyItem(),ERecoveredResupplyItemUseResult::CannotUseItems);
    TestEqual(TEXT("Source resupply disabled gate does not record item use"),Manager->SessionStats.ItemsUsed,0);
    TestEqual(TEXT("Source resupply disabled gate retains the item"),Manager->GetOwnedItemCount(TEXT("Resupply")),1);

    Manager->PlayerVariables.bCanUseItems=true;
    Manager->OwnedItemCounts.Empty();
    TestEqual(TEXT("Source resupply empty gate returns its original result"),Manager->UseRecoveredResupplyItem(),ERecoveredResupplyItemUseResult::NoResupplyAvailable);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->PlayerVariables.bCanUseItems=true;
    Manager->PlayerVariables.TotalTauntsUsed=25;
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Resupply"),1);
    TestEqual(TEXT("Source resupply punishment resolves before presentation or spend"),Manager->UseRecoveredResupplyItem(),ERecoveredResupplyItemUseResult::PunishmentTriggered);
    TestEqual(TEXT("Source resupply records item use before punishment"),Manager->SessionStats.ItemsUsed,1);
    TestEqual(TEXT("Source resupply punishment retains the item"),Manager->GetOwnedItemCount(TEXT("Resupply")),1);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->PlayerVariables.bCanUseItems=true;
    Manager->PlayerVariables.PlayerCoins=250;
    Manager->CumMeterPercentage=0.75;
    Manager->BeatContext.ActiveModifiers.Reset();
    Manager->BeatContext.ActiveModifiers.Add(TEXT("All or Nothing"));
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Resupply"),1);
    TestEqual(TEXT("Source resupply starts its two-second store continuation"),Manager->UseRecoveredResupplyItem(),ERecoveredResupplyItemUseResult::Triggered);
    TestEqual(TEXT("Source resupply records the source item metric"),Manager->SessionStats.ItemsUsed,1);
    TestEqual(TEXT("All or Nothing clears source coins before presentation"),Manager->PlayerVariables.PlayerCoins,0);
    TestEqual(TEXT("All or Nothing clears the source cum meter before presentation"),Manager->CumMeterPercentage,0.0);
    TestEqual(TEXT("Source resupply retains inventory until the delayed store handoff"),Manager->GetOwnedItemCount(TEXT("Resupply")),1);
    TestTrue(TEXT("Source resupply schedules its two-second store handoff"),Manager->IsRecoveredResupplyPending());
    Manager->CompleteRecoveredResupplyItemUse();
    TestFalse(TEXT("Source resupply clears its store handoff after completion"),Manager->IsRecoveredResupplyPending());
    TestEqual(TEXT("Source resupply spends only after the store handoff"),Manager->GetOwnedItemCount(TEXT("Resupply")),0);

    Manager->SessionStats=FRecoveredSessionStats();
    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->PlayerVariables.bCanUseItems=true;
    Manager->BeatContext.ActiveModifiers.Reset();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Resupply"),1);
    TestTrue(TEXT("Generic recovered inventory dispatches resupply to its source action"),Manager->UseOwnedItem(TEXT("Resupply"),0));
    TestEqual(TEXT("Generic resupply dispatch keeps the item during its source delay"),Manager->GetOwnedItemCount(TEXT("Resupply")),1);
    Manager->CompleteRecoveredResupplyItemUse();
    TestEqual(TEXT("Generic resupply dispatch completes the delayed source spend"),Manager->GetOwnedItemCount(TEXT("Resupply")),0);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPG1DefensiveItemsTest,"CockHero.Recovery.PG1DefensiveItems",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPG1DefensiveItemsTest::RunTest(const FString& Parameters) {
    UClass* InventoryBlueprintClass=LoadClass<URecoveredTabbedInventoryWidget>(nullptr,TEXT("/Game/Recovery/UI/PG1TabbedInventory_Widget.PG1TabbedInventory_Widget_C"));
    if (!TestNotNull(TEXT("Recovered PG1 defensive inventory widget"),InventoryBlueprintClass)) return false;
    TestTrue(TEXT("Recovered PG1 defensive inventory uses its native owner"),InventoryBlueprintClass->IsChildOf(URecoveredTabbedInventoryWidget::StaticClass()));
    TestNotNull(TEXT("Recovered heat notification icon"),LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/InventoryButtonPNGs/DecreaseHealthBarItem.DecreaseHealthBarItem")));
    TestNotNull(TEXT("Recovered cum chance notification icon"),LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/InventoryButtonPNGs/CumChangeItem.CumChangeItem")));
    TestNotNull(TEXT("Recovered slowdown notification icon"),LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/InventoryButtonPNGs/SlowdownItem.SlowdownItem")));
    TestNotNull(TEXT("Recovered heat item overlay"),LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/UseDecreaseHeatOverlay_Widget.UseDecreaseHeatOverlay_Widget_C")));
    TestNotNull(TEXT("Recovered slowdown item overlay"),LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/SlowdownItemUseOverlay_Widget.SlowdownItemUseOverlay_Widget_C")));
    TestNotNull(TEXT("Recovered cum chance item overlay"),LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/PlusCumChanceOverlay_Widget.PlusCumChanceOverlay_Widget_C")));
    TestNotNull(TEXT("Recovered source break rest widget"),LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/RestWidget.RestWidget_C")));

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());

    auto* Inventory=CreateWidget<URecoveredTabbedInventoryWidget>(World,InventoryBlueprintClass);
    if (!TestNotNull(TEXT("Recovered PG1 defensive widget instantiates"),Inventory)) return false;
    TestNotNull(TEXT("Recovered PG1 heat button survives reparenting"),Cast<UButton>(Inventory->GetWidgetFromName(TEXT("DecreaseHeatButton"))));
    TestNotNull(TEXT("Recovered PG1 break button survives reparenting"),Cast<UButton>(Inventory->GetWidgetFromName(TEXT("10SecBreakButton"))));
    TestNotNull(TEXT("Recovered PG1 slowdown button survives reparenting"),Cast<UButton>(Inventory->GetWidgetFromName(TEXT("SlowdownItemButton"))));
    TestNotNull(TEXT("Recovered PG1 cum chance button survives reparenting"),Cast<UButton>(Inventory->GetWidgetFromName(TEXT("CumChanceIncreaseButton"))));
    TestNotNull(TEXT("Recovered PG1 heat count label survives reparenting"),Cast<UTextBlock>(Inventory->GetWidgetFromName(TEXT("QuantityAmount"))));
    TestNotNull(TEXT("Recovered PG1 break count label survives reparenting"),Cast<UTextBlock>(Inventory->GetWidgetFromName(TEXT("QuantityAmount_1"))));
    TestNotNull(TEXT("Recovered PG1 slowdown count label survives reparenting"),Cast<UTextBlock>(Inventory->GetWidgetFromName(TEXT("QuantityAmount_3"))));
    TestNotNull(TEXT("Recovered PG1 cum chance count label survives reparenting"),Cast<UTextBlock>(Inventory->GetWidgetFromName(TEXT("QuantityAmount_4"))));

    ARecoveredGlobalManager* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Recovered PG1 defensive manager"),Manager)) return false;

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("DecreaseHeat"),1);
    Manager->PlayerVariables.bCanUseItems=false;
    TestEqual(TEXT("Source heat gate rejects disabled item use"),Manager->UseRecoveredDecreaseHeatItem(),ERecoveredDefensiveItemUseResult::CannotUseItems);
    TestEqual(TEXT("Source heat disabled gate retains inventory"),Manager->GetOwnedItemCount(TEXT("DecreaseHeat")),1);
    TestEqual(TEXT("Source heat disabled gate does not record item use"),Manager->SessionStats.ItemsUsed,0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("DecreaseHeat"),1);
    Manager->HeatLevel=80;
    Manager->CumMeterPercentage=0;
    Manager->SetRecoveredItemUpgradeLevel(TEXT("DecreaseHeat"),0);
    TestEqual(TEXT("Source heat item triggers"),Manager->UseRecoveredDecreaseHeatItem(),ERecoveredDefensiveItemUseResult::Triggered);
    TestEqual(TEXT("Source heat level zero reduces heat by fifteen"),Manager->HeatLevel,65.0);
    TestEqual(TEXT("Source heat action adds the source meter amount"),Manager->CumMeterPercentage,0.01);
    TestEqual(TEXT("Source heat action records item use"),Manager->SessionStats.ItemsUsed,1);
    TestEqual(TEXT("Source heat action spends one item"),Manager->GetOwnedItemCount(TEXT("DecreaseHeat")),0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("DecreaseHeat"),1);
    Manager->PlayerVariables.TotalTauntsUsed=25;
    Manager->HeatLevel=20;
    TestEqual(TEXT("Source heat punishment resolves after accounting"),Manager->UseRecoveredDecreaseHeatItem(),ERecoveredDefensiveItemUseResult::PunishmentTriggered);
    TestEqual(TEXT("Source heat punishment retains inventory"),Manager->GetOwnedItemCount(TEXT("DecreaseHeat")),1);
    TestEqual(TEXT("Source heat punishment records the source item metric"),Manager->SessionStats.ItemsUsed,1);
    TestEqual(TEXT("Source heat punishment applies its heat penalty"),Manager->HeatLevel,35.0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("XCumChance"),1);
    Manager->PlayerVariables.SessionLength=42;
    Manager->CumMeterPercentage=0;
    Manager->SetRecoveredItemUpgradeLevel(TEXT("XCumChance"),4);
    TestEqual(TEXT("Source cum chance item triggers"),Manager->UseRecoveredCumChanceItem(),ERecoveredDefensiveItemUseResult::Triggered);
    TestEqual(TEXT("Source cum chance level four adds thirty-five percent"),Manager->CumMeterPercentage,0.35);
    TestEqual(TEXT("Source cum chance increments defensive item count"),Manager->PlayerVariables.TotalDefenseItemUses,1);
    TestEqual(TEXT("Source cum chance records its session time"),Manager->PlayerVariables.LastDefensiveItemUsageTime,42.0);
    TestEqual(TEXT("Source cum chance records item use"),Manager->SessionStats.ItemsUsed,1);
    TestEqual(TEXT("Source cum chance spends one item"),Manager->GetOwnedItemCount(TEXT("XCumChance")),0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Break"),1);
    Manager->PlayerVariables.CurrentComboCount=13;
    Manager->CumMeterPercentage=0;
    Manager->bStopSequence=false;
    TestEqual(TEXT("Source break item triggers"),Manager->UseRecoveredBreakItem(),ERecoveredDefensiveItemUseResult::Triggered);
    TestEqual(TEXT("Source break action adds the source meter amount"),Manager->CumMeterPercentage,0.01);
    TestTrue(TEXT("Source break stops the active sequence"),Manager->bStopSequence);
    TestEqual(TEXT("Source break resets the combo"),Manager->PlayerVariables.CurrentComboCount,0);
    TestTrue(TEXT("Source break stores the broken combo"),Manager->PlayerVariables.BrokenComboArray.Contains(13));
    TestEqual(TEXT("Source break spends one item"),Manager->GetOwnedItemCount(TEXT("Break")),0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Slowdown"),1);
    Manager->PlayerVariables.BeatSpawnInterval=1;
    Manager->PlayerVariables.SessionLength=53;
    Manager->CumMeterPercentage=0;
    Manager->bCanUseSlowdown=true;
    Manager->bCanUseBonerPill=true;
    Manager->SetRecoveredItemUpgradeLevel(TEXT("Slowdown"),2);
    TestEqual(TEXT("Source slowdown item triggers"),Manager->UseRecoveredSlowdownItem(),ERecoveredDefensiveItemUseResult::Triggered);
    TestEqual(TEXT("Source slowdown level two uses the x4 multiplier"),Manager->PlayerVariables.BeatSpawnInterval,4.0);
    TestEqual(TEXT("Source slowdown action adds the source meter amount"),Manager->CumMeterPercentage,0.01);
    TestFalse(TEXT("Source slowdown locks the item for the task"),Manager->bCanUseSlowdown);
    TestTrue(TEXT("Source slowdown leaves boner pill availability unchanged"),Manager->bCanUseBonerPill);
    TestEqual(TEXT("Source slowdown records its session time"),Manager->PlayerVariables.LastDefensiveItemUsageTime,53.0);
    TestEqual(TEXT("Source slowdown spends one item"),Manager->GetOwnedItemCount(TEXT("Slowdown")),0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->SessionStats=FRecoveredSessionStats();
    Manager->OwnedItemCounts.Empty();
    Manager->OwnedItemCounts.Add(TEXT("Slowdown"),1);
    Manager->bCanUseSlowdown=false;
    TestEqual(TEXT("Source slowdown cooldown blocks a second item"),Manager->UseRecoveredSlowdownItem(),ERecoveredDefensiveItemUseResult::CooldownActive);
    TestEqual(TEXT("Source slowdown cooldown retains inventory"),Manager->GetOwnedItemCount(TEXT("Slowdown")),1);
    TestEqual(TEXT("Source slowdown cooldown does not record item use"),Manager->SessionStats.ItemsUsed,0);

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->OwnedItemCounts.Empty();
    for (int32 Index=0;Index<4;++Index) Manager->AcquireStoreItem(TEXT("DecreaseHeat"));
    TestEqual(TEXT("Source heat inventory caps at three items"),Manager->GetOwnedItemCount(TEXT("DecreaseHeat")),3);
    return true;
}
#endif
