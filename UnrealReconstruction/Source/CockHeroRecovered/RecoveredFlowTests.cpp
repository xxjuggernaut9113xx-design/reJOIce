#include "RecoveredRules.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Misc/AutomationTest.h"
#include "RecoveredSessionWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPaceFlowTest,"CockHero.Recovery.PaceCardFlow",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredPaceFlowTest::RunTest(const FString& Parameters) {
    auto* Rules=LoadObject<URecoveredRulesAsset>(nullptr,TEXT("/Game/Recovery/Definitions/DA_GameRules.DA_GameRules"));
    auto* Table=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_HeatCategories.DT_HeatCategories"));
    if(!TestNotNull(TEXT("Recovered rules asset"),Rules) || !TestNotNull(TEXT("Recovered timing table"),Table)) return false;
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    GEngine->CreateNewWorldContext(EWorldType::Game).SetCurrentWorld(World);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if(!TestNotNull(TEXT("Spawn reconstruction manager"),Manager)) { World->DestroyWorld(false);GEngine->DestroyWorldContext(World);return false; }
    Manager->Rules=Rules;
    Manager->HeatCategoryDataTable=Table;
    Manager->InitializeDifficultyVariables(0,0);
    Manager->UpdateMinimumBeatInterval(FRecoveredDeviceState());
    TestTrue(TEXT("Load source media pack"),Manager->LoadMediaPack(TEXT("C:/Users/webma/Downloads/Cock_Hero_Shipping_Build_V0.04_-_Exclusive/PrepV2/Windows/Extracted/Base_Game_CG/manifest.json"),{}));
    for(uint8 Pace=0;Pace<3;++Pace) {
        Manager->PlayerVariables.CurrentComboCount=99;
        Manager->DetermineComboType();
        const int32 BeforeStrokes=Manager->PlayerVariables.TotalStrokeCount;
        const int32 BeforeCoins=Manager->PlayerVariables.PlayerCoins;
        const int32 BeforeMetrics=Manager->SessionStats.Strokes;
        TestTrue(TEXT("Draw source-backed pace card"),Manager->DrawPaceCard(Pace,false));
        const int32 Assigned=Manager->PlayerVariables.AssignedStrokeCount;
        TestTrue(TEXT("Card assigns strokes"),Assigned>0);
        TestTrue(TEXT("Card selects media path"),!Manager->SelectedRandomCard.FullPath.IsEmpty());
        if(Manager->BeatTimeline->BeatQueue.IsEmpty()) { AddError(Manager->LastSessionError);break; }
        Manager->BeatTimeline->AdvanceTo(Manager->BeatTimeline->BeatQueue.Last().TargetHitTime+1);
        TestEqual(TEXT("Complete all assigned strokes"),Manager->PlayerVariables.CurrentStrokeCount,0);
        TestEqual(TEXT("Beat callbacks update stroke total"),Manager->PlayerVariables.TotalStrokeCount,BeforeStrokes+Assigned);
        TestEqual(TEXT("Beat callbacks award coins"),Manager->PlayerVariables.PlayerCoins,BeforeCoins+Assigned);
        TestEqual(TEXT("Beat callbacks update session metric"),Manager->SessionStats.Strokes,BeforeMetrics+Assigned);
        TestEqual(TEXT("Combo tier advances through bound callbacks"),Manager->CurrentComboTypeEnum,static_cast<uint8>(1));
        TestFalse(TEXT("Timeline completes"),Manager->BeatTimeline->bIsRunning);
    }
    const FName SpecialEvents[]={TEXT("SpawnSuccubus"),TEXT("AssFrenzyEvent"),TEXT("BoobFrenzyEvent")};
    const uint8 ExpectedTypes[]={3,7,8};
    for (int32 I=0;I<3;++I) {
        Manager->StrokeCountMultiplier=1;Manager->StrokeTimeMultiplier=1;
        Manager->PlayerVariables.bCanUseItems=true;
        TestTrue(TEXT("Draw decoded special card"),Manager->DrawRecoveredSpecialCard(SpecialEvents[I],false));
        TestEqual(TEXT("Special card uses decoded type"),Manager->BeatContext.CardType,ExpectedTypes[I]);
        TestTrue(TEXT("Special media path selected"),!Manager->SelectedRandomCard.FullPath.IsEmpty());
        TestTrue(TEXT("Special pattern produces beat queue"),!Manager->BeatTimeline->BeatQueue.IsEmpty());
        if (I==0) {
            TestFalse(TEXT("Succubus disables items"),Manager->PlayerVariables.bCanUseItems);
            TestTrue(TEXT("Succubus source stroke bounds"),Manager->PlayerVariables.AssignedStrokeCount>=30 && Manager->PlayerVariables.AssignedStrokeCount<=50);
        }
        Manager->BeatTimeline->StopSequence();
    }
    Manager->BeatContext.ActiveModifiers={TEXT("Succufrenzy")};
    const int32 BeforeDraws=Manager->PlayerVariables.TotalDrawCount;
    TestTrue(TEXT("Modifier dispatch reaches actual special card"),Manager->RequestNextRecoveredCard(false));
    TestEqual(TEXT("One preparation per dispatched card"),Manager->PlayerVariables.TotalDrawCount,BeforeDraws+1);
    TestEqual(TEXT("Dispatch uses event identity rather than array index"),Manager->BeatContext.CardType,static_cast<uint8>(3));
    Manager->BeatTimeline->StopSequence();
    const FName OverrideEvents[]={TEXT("EdgingEventV2"),TEXT("CumEventOverride"),TEXT("CumOverride"),TEXT("PostEdgeSlowEvent"),TEXT("PostEdgeFastEvent")};
    const uint8 OverrideTypes[]={5,6,6,4,4};
    for (int32 I=0;I<5;++I) {
        Manager->StrokeCountMultiplier=Manager->StrokeTimeMultiplier=1;Manager->PlayerVariables.bHasEdged=true;Manager->PlayerVariables.bCanUseItems=true;
        TestTrue(TEXT("Recovered event override draws media and starts beats"),Manager->DrawRecoveredSpecialCard(OverrideEvents[I],false));
        TestEqual(TEXT("Override uses source card type"),Manager->BeatContext.CardType,OverrideTypes[I]);
        TestTrue(TEXT("Override builds a beat queue"),!Manager->BeatTimeline->BeatQueue.IsEmpty());
        TestTrue(TEXT("Override selects an original media file"),!Manager->SelectedRandomCard.FullPath.IsEmpty());
        if (I==0) {
            TestFalse(TEXT("Edge override clears draw trigger"),Manager->PlayerVariables.bHasEdged);TestFalse(TEXT("Edge override disables items"),Manager->PlayerVariables.bCanUseItems);
            TestTrue(TEXT("Edge multiplier advances within source range"),Manager->EdgeStrokeMultiplier>=1.2 && Manager->EdgeStrokeMultiplier<=1.35);
            TestTrue(TEXT("Edge interval remains in source clamp"),Manager->LastEdgeInterval>=.15 && Manager->LastEdgeInterval<=1);
        }
        Manager->BeatTimeline->StopSequence();
    }
    Manager->PlayerVariables.bHasEdged=false;Manager->PlayerVariables.bHasCame=true;
    TestTrue(TEXT("Outcome draw dispatches its override instead of stopping"),Manager->RequestNextRecoveredCard(false));
    TestEqual(TEXT("Outcome override wins dispatch precedence"),Manager->LastDispatchedEvent,FName(TEXT("CumOverride")));
    Manager->BeatTimeline->StopSequence();Manager->PlayerVariables.bHasCame=false;
    UClass* ScreenClass=LoadClass<URecoveredSessionWidget>(nullptr,TEXT("/Game/Recovery/UI/UI_Manager.UI_Manager_C"));
    if (TestNotNull(TEXT("Gameplay display class"),ScreenClass)) {
        auto* Screen=NewObject<URecoveredSessionWidget>(GetTransientPackage(),ScreenClass);
        Screen->Initialize();auto SlateWidget=Screen->TakeWidget();
        Manager->PlayerVariables.CurrentComboCount=42;Manager->PlayerVariables.PlayerCoins=123;
        Manager->PlayerVariables.SessionLength=3661;Manager->HeatLevel=25;Manager->CumMeterPercentage=.6;Manager->LootBarPercentage=.4;
        Screen->RefreshSessionDisplays(Manager);
        auto* Combo=Cast<UTextBlock>(Screen->GetWidgetFromName(TEXT("ComboText")));
        auto* Coins=Cast<UTextBlock>(Screen->GetWidgetFromName(TEXT("CoinCounterText")));
        auto* Duration=Cast<UTextBlock>(Screen->GetWidgetFromName(TEXT("SessionDurationText")));
        auto* Heat=Cast<UProgressBar>(Screen->GetWidgetFromName(TEXT("HeatMeterBar")));
        if (TestNotNull(TEXT("Live combo display"),Combo)) TestEqual(TEXT("Exact source combo suffix"),Combo->GetText().ToString(),FString(TEXT("42X COMBO")));
        if (TestNotNull(TEXT("Live coin display"),Coins)) TestEqual(TEXT("Current coins displayed"),Coins->GetText().ToString(),FString(TEXT("123")));
        if (TestNotNull(TEXT("Live duration display"),Duration)) TestEqual(TEXT("Source duration formatting"),Duration->GetText().ToString(),FString(TEXT("01:01:01")));
        if (TestNotNull(TEXT("Live heat meter"),Heat)) TestEqual(TEXT("Heat normalized to fraction"),Heat->GetPercent(),.25f);
    }
    World->DestroyWorld(false);
    GEngine->DestroyWorldContext(World);
    return true;
}
#endif
