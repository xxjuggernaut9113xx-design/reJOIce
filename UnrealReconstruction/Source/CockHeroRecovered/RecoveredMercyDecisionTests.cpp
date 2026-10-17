#include "RecoveredDecisionWidgets.h"
#include "RecoveredEdgeManager.h"
#include "RecoveredMercyRestWidget.h"
#include "RecoveredRules.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredMercyTemptationDecisionTest,"CockHero.Recovery.MercyTemptationDecisionLifecycle",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredMercyTemptationDecisionTest::RunTest(const FString& Parameters) {
    UClass* MercyRestClass=LoadClass<URecoveredMercyRestWidget>(nullptr,TEXT("/Game/Recovery/UI/MercyRestWidget.MercyRestWidget_C"));
    UClass* MercyDecisionClass=LoadClass<URecoveredMercyEventWidget>(nullptr,TEXT("/Game/Recovery/UI/MercyEventWidget.MercyEventWidget_C"));
    UClass* TemptationDecisionClass=LoadClass<URecoveredTemptationEventWidget>(nullptr,TEXT("/Game/Recovery/UI/TemptationEventWidget.TemptationEventWidget_C"));
    if (!TestNotNull(TEXT("Recovered MercyRestWidget"),MercyRestClass) || !TestNotNull(TEXT("Recovered MercyEventWidget"),MercyDecisionClass) || !TestNotNull(TEXT("Recovered TemptationEventWidget"),TemptationDecisionClass)) return false;
    TestTrue(TEXT("Recovered MercyRestWidget uses native lifecycle owner"),MercyRestClass->IsChildOf(URecoveredMercyRestWidget::StaticClass()));
    TestTrue(TEXT("Recovered MercyEventWidget uses native decision owner"),MercyDecisionClass->IsChildOf(URecoveredMercyEventWidget::StaticClass()));
    TestTrue(TEXT("Recovered TemptationEventWidget uses native decision owner"),TemptationDecisionClass->IsChildOf(URecoveredTemptationEventWidget::StaticClass()));

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());

    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    auto* EdgeManager=World->SpawnActor<ARecoveredEdgeManager>();
    auto* MercyRest=CreateWidget<URecoveredMercyRestWidget>(World,MercyRestClass);
    auto* MercyDecision=CreateWidget<URecoveredMercyEventWidget>(World,MercyDecisionClass);
    auto* TemptationDecision=CreateWidget<URecoveredTemptationEventWidget>(World,TemptationDecisionClass);
    if (!TestNotNull(TEXT("Recovered decision manager"),Manager) || !TestNotNull(TEXT("Recovered decision edge manager"),EdgeManager) || !TestNotNull(TEXT("Recovered MercyRestWidget instantiates"),MercyRest) || !TestNotNull(TEXT("Recovered MercyEventWidget instantiates"),MercyDecision) || !TestNotNull(TEXT("Recovered TemptationEventWidget instantiates"),TemptationDecision)) return false;
    Manager->EdgingManager=EdgeManager;
    EdgeManager->SetRecoveredGlobalManager(Manager);

    TestNotNull(TEXT("Recovered MercyRestWidget preserves cancel control"),Cast<UButton>(MercyRest->GetWidgetFromName(TEXT("CancelBreakButton"))));
    auto* MercyProgress=Cast<UProgressBar>(MercyRest->GetWidgetFromName(TEXT("ProgressBar_0")));
    if (!TestNotNull(TEXT("Recovered MercyRestWidget preserves progress control"),MercyProgress)) return false;
    TestNotNull(TEXT("Recovered MercyEventWidget preserves yes control"),Cast<UButton>(MercyDecision->GetWidgetFromName(TEXT("YesButton"))));
    TestNotNull(TEXT("Recovered MercyEventWidget preserves no control"),Cast<UButton>(MercyDecision->GetWidgetFromName(TEXT("NoButton"))));
    TestNotNull(TEXT("Recovered TemptationEventWidget preserves yes control"),Cast<UButton>(TemptationDecision->GetWidgetFromName(TEXT("YesButton"))));
    TestNotNull(TEXT("Recovered TemptationEventWidget preserves no control"),Cast<UButton>(TemptationDecision->GetWidgetFromName(TEXT("NoButton"))));

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->PlayerVariables.bHasEdged=true;
    Manager->PlayerVariables.bCanUseItems=true;
    Manager->PlayerVariables.bCanDraw=true;
    Manager->bStopSequence=false;
    Manager->StartMercyEvent();
    TestFalse(TEXT("Mercy source event clears edged state"),Manager->PlayerVariables.bHasEdged);
    TestTrue(TEXT("Mercy source event stops the active sequence"),Manager->bStopSequence);
    TestEqual(TEXT("Mercy source event selects card type five"),Manager->BeatContext.CardType,uint8(5));
    TestEqual(TEXT("Mercy source cooldown duration is 120 seconds"),Manager->MercyCooldownDuration,120.0);
    TestEqual(TEXT("Mercy source rest meter add is one percent"),Manager->BreakCumMeterAddAmount,0.01);

    Manager->HeatLevel=82.0;
    Manager->EdgeBank=80;
    Manager->PlayerVariables.PlayerCoins=10;
    Manager->PlayerVariables.SessionCoinsEarned=0;
    Manager->PlayerVariables.CoinEarnMultiplier=1.0;
    Manager->AcceptMercy();
    TestEqual(TEXT("Mercy acceptance clears source heat"),Manager->HeatLevel,0.0);
    TestTrue(TEXT("Mercy acceptance starts source cooldown"),Manager->bIsMercyOnCooldown);
    TestTrue(TEXT("Mercy acceptance schedules its cooldown completion"),World->GetTimerManager().IsTimerActive(Manager->MercyCooldownTimer));
    TestEqual(TEXT("Mercy acceptance pays the complete edge bank"),Manager->PlayerVariables.PlayerCoins,90);
    TestEqual(TEXT("Mercy acceptance clears the edge bank"),Manager->EdgeBank,0);
    TestTrue(TEXT("Mercy acceptance applies the source break meter reward"),FMath::IsNearlyEqual(Manager->CumMeterPercentage,0.01));
    Manager->OnMercyCooldownExpired();
    TestFalse(TEXT("Mercy cooldown completion restores eligibility"),Manager->bIsMercyOnCooldown);

    Manager->PlayerVariables.bCanUseItems=true;
    Manager->PlayerVariables.bCanDraw=true;
    MercyRest->BeginRecoveredMercyRest(Manager);
    TestTrue(TEXT("Mercy rest accepts source cancel input"),MercyRest->bIsButtonInputAllowed);
    TestTrue(TEXT("Mercy rest starts source lifecycle"),MercyRest->IsRecoveredMercyRestActive());
    TestEqual(TEXT("Mercy rest is exactly sixty seconds"),MercyRest->BreakDuration,60.0);
    TestFalse(TEXT("Mercy rest disables item use"),Manager->PlayerVariables.bCanUseItems);
    TestFalse(TEXT("Mercy rest disables drawing"),Manager->PlayerVariables.bCanDraw);
    MercyRest->StartTime=World->GetUnpausedTimeSeconds()-30.0;
    MercyRest->UpdateProgress();
    TestTrue(TEXT("Mercy rest derives progress from unpaused time"),FMath::IsNearlyEqual(MercyRest->CurrentProgress,0.5,0.05));
    TestTrue(TEXT("Mercy rest writes progress to source control"),FMath::IsNearlyEqual(MercyProgress->GetPercent(),0.5f,0.05f));
    MercyRest->CancelRecoveredMercyRest();
    TestFalse(TEXT("Mercy rest cancels only once"),MercyRest->bIsButtonInputAllowed);

    EdgeManager->MasterEdgesUntilNextMercy=5;
    EdgeManager->CurrentEdgesUntillNextMercy=1;
    EdgeManager->UpdateRecoveredMasterEdgeCountAndSet();
    TestEqual(TEXT("Mercy decline increases source master edge count by 25 percent"),EdgeManager->MasterEdgesUntilNextMercy,6);
    TestEqual(TEXT("Mercy decline copies source master count to current count"),EdgeManager->CurrentEdgesUntillNextMercy,6);
    Manager->LastDispatchedEvent=NAME_None;
    Manager->DeclineMercy();
    TestEqual(TEXT("Mercy decline resumes the source edge-streak event directly"),Manager->LastDispatchedEvent,FName(TEXT("EdgingEventV2")));

    Manager->PlayerVariables=FRecoveredPlayerVariables();
    Manager->bStopSequence=false;
    Manager->bIsTemptationOnCooldown=false;
    Manager->StartTemptationEvent();
    TestTrue(TEXT("Temptation source event starts its cooldown"),Manager->bIsTemptationOnCooldown);
    TestTrue(TEXT("Temptation source event schedules its sixty-second cooldown"),World->GetTimerManager().IsTimerActive(Manager->TemptationCooldownTimer));
    TestTrue(TEXT("Temptation source event stops the active sequence"),Manager->bStopSequence);
    TestEqual(TEXT("Temptation source event selects card type four"),Manager->BeatContext.CardType,uint8(4));
    TestEqual(TEXT("Temptation source event selects its background"),Manager->CurrentBeatBackgroundStyle,9);
    Manager->CompleteRecoveredTemptationCooldown();
    TestFalse(TEXT("Temptation cooldown completion restores eligibility"),Manager->bIsTemptationOnCooldown);
    Manager->HeatLevel=18.0;
    Manager->SessionStats.AcceptedTemptation=0;
    Manager->AcceptTemptation();
    TestEqual(TEXT("Temptation acceptance sets heat to source maximum"),Manager->HeatLevel,100.0);
    TestEqual(TEXT("Temptation acceptance records source metric twenty-eight"),Manager->SessionStats.AcceptedTemptation,1);

    MercyDecision->bButtonPressEnabled=true;
    MercyDecision->SelectRecoveredMercyYes();
    TestFalse(TEXT("Mercy yes input consumes its source gate"),MercyDecision->bButtonPressEnabled);
    TemptationDecision->bButtonPressEnabled=true;
    TemptationDecision->SelectRecoveredTemptationNo();
    TestFalse(TEXT("Temptation no input consumes its source gate"),TemptationDecision->bButtonPressEnabled);
    return true;
}
#endif
