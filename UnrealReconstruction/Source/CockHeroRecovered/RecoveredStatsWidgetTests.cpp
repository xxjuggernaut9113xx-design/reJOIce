#include "RecoveredStatsWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "RecoveredEdgeManager.h"
#include "RecoveredRules.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredStatisticsScreenTest,"CockHero.Recovery.StatisticsScreen",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredStatisticsScreenTest::RunTest(const FString& Parameters) {
    const FString Slot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("AutomationStats_")+FGuid::NewGuid().ToString(EGuidFormats::Digits);
    ON_SCOPE_EXIT { UGameplayStatics::DeleteGameInSlot(Slot,0); };

    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Statistics save initializes"),Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Statistics history initializes"),
        Save->SetIntArraySetting(TEXT("AllSessionCombos"),{2,10,4}) &&
        Save->SetIntArraySetting(TEXT("AllSessionTimes"),{60,3605,120}) &&
        Save->SetIntArraySetting(TEXT("AllSessionEdges"),{1,8,3}) &&
        Save->SetIntArraySetting(TEXT("AllSessionStrokeCounts"),{99,200,1}) &&
        Save->SetIntArraySetting(TEXT("AllStrokesPerEdge"),{7,8,9}))) return false;
    if (!TestTrue(TEXT("Statistics lifetime counters initialize"),
        Save->SetNumberSetting(TEXT("TotalLifetimeStrokes"),703) &&
        Save->SetNumberSetting(TEXT("TotalLifetimeEdges"),37) &&
        Save->SetNumberSetting(TEXT("TotalDrawCount"),40) &&
        Save->SetNumberSetting(TEXT("TotalEnemiesDefeated"),10) &&
        Save->SetNumberSetting(TEXT("TotalSuccubiDefeated"),9) &&
        Save->SetNumberSetting(TEXT("TotalLifetimeItemUses"),6) &&
        Save->SetNumberSetting(TEXT("SessionsWon"),5) &&
        Save->SetNumberSetting(TEXT("SessionsLost"),2) &&
        Save->SetNumberSetting(TEXT("TimesLostToSuccubus"),1) &&
        Save->SetNumberSetting(TEXT("LifetimeMaxHeatDraws"),4) &&
        Save->SetNumberSetting(TEXT("LifetimeTauntCount"),12))) return false;

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>();
    Instance->CurrentSave=Save;
    Instance->ActiveRecoverySlot=Slot;
    Instance->ProgressionManager=NewObject<URecoveredProgressionManager>(Instance);
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    UClass* StatsClass=LoadClass<URecoveredStatsScreenWidget>(nullptr,TEXT("/Game/Recovery/UI/StatsScreenWidget.StatsScreenWidget_C"));
    if (!TestNotNull(TEXT("Recovered statistics screen class"),StatsClass)) return false;
    TestTrue(TEXT("Recovered statistics screen uses its native owner"),StatsClass->IsChildOf(URecoveredStatsScreenWidget::StaticClass()));
    auto* Stats=CreateWidget<URecoveredStatsScreenWidget>(World,StatsClass);
    if (!TestNotNull(TEXT("Recovered statistics screen instantiates"),Stats)) return false;
    Stats->TakeWidget();
    TestTrue(TEXT("Statistics world retains the recovery instance"),World->GetGameInstance()==Instance);
    Stats->SetRecoveredStatisticsGameInstance(Instance);
    Stats->InitializeRecoveredStatsScreen();

    TestEqual(TEXT("Source highest combo"),Stats->HighestCombo,10);
    TestEqual(TEXT("Source longest session"),Stats->HighestSessionTime,3605);
    TestEqual(TEXT("Source highest edge count"),Stats->HighestEdges,8);
    TestEqual(TEXT("Source highest stroke count"),Stats->HighestStrokeCount,200);
    TestEqual(TEXT("Source average edge count"),Stats->AvgSessionEdges,4);
    TestEqual(TEXT("Source average strokes per edge"),Stats->AvgStrokesPerEdge,8);
    TestEqual(TEXT("Source average stroke count"),Stats->AvgStrokeCount,100);
    TestEqual(TEXT("Source average combo"),Stats->AvgCombo,5);
    TestEqual(TEXT("Source average session time"),Stats->AvgTime,1261);
    TestEqual(TEXT("Source time formatting"),Stats->FormatRecoveredTime(3605).ToString(),FString(TEXT("01:00:05")));
    TestEqual(TEXT("Source high-score text"),Stats->GetRecoveredHighScores().ToString(),FString(TEXT("Longest Session: 01:00:05\r\nHighest Combo: 10\r\nHighest Edges: 8\r\nHighest Stroke Count: 200")));
    TestEqual(TEXT("Source duration text"),Stats->GetRecoveredAvgSessionDurationText().ToString(),FString(TEXT("Avg Duration:\r\n00:21:01")));
    TestEqual(TEXT("Source lifetime text"),Stats->GetRecoveredLifetimeStatsDisplay().ToString(),FString(TEXT("Total Strokes: 703\r\nTotal Edges: 37\r\nTotal Draw Count: 40\r\nTotal Enemies Defeated: 10\r\nTotal Succubi Defeated: 9\r\nTotal Lifetime Item Uses: 6\r\nSessions Won: 5\r\nSessions Lost: 2\r\nTimes Lost to Succubus: 1\r\nLifetime Max Heat Draws: 4\r\nLifetime Taunts Used: 12")));
    if (auto* Text=Cast<UTextBlock>(Stats->GetWidgetFromName(TEXT("TextBlock_5")))) TestEqual(TEXT("Source lifetime binding updates its recovered text block"),Text->GetText().ToString(),Stats->GetRecoveredLifetimeStatsDisplay().ToString());
    else AddError(TEXT("Missing source lifetime statistics text block"));
    if (auto* Text=Cast<UTextBlock>(Stats->GetWidgetFromName(TEXT("TextBlock_7")))) TestEqual(TEXT("Source high-score binding updates its recovered text block"),Text->GetText().ToString(),Stats->GetRecoveredHighScores().ToString());
    else AddError(TEXT("Missing source high-score text block"));
    if (auto* BackButton=Cast<UButton>(Stats->GetWidgetFromName(TEXT("BackButton")))) {
        TestTrue(TEXT("Source statistics back click binding is installed"),BackButton->OnClicked.IsBound());
        TestTrue(TEXT("Source statistics hover binding is installed"),BackButton->OnHovered.IsBound());
        TestTrue(TEXT("Source statistics unhover binding is installed"),BackButton->OnUnhovered.IsBound());
    } else AddError(TEXT("Missing source statistics back button"));

    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    auto* Edge=World->SpawnActor<ARecoveredEdgeManager>();
    if (!TestNotNull(TEXT("Recovered statistics edge manager"),Manager) || !TestNotNull(TEXT("Recovered statistics edge owner"),Edge)) return false;
    Manager->EdgingManager=Edge;
    Edge->SetRecoveredGlobalManager(Manager);
    Manager->PlayerVariables.CurrentComboCount=12;
    Manager->PlayerVariables.SessionLength=41;
    Manager->bPlayerEdgedLastDraw=false;
    TestTrue(TEXT("Source edge event records a stroke-per-edge sample"),Edge->TriggerRecoveredEdgeV2());
    const TArray<int32> StrokeSamples=Save->GetIntArraySetting(TEXT("AllStrokesPerEdge"));
    TestEqual(TEXT("Source edge history appends one sample"),StrokeSamples.Num(),4);
    if (StrokeSamples.Num()==4) TestEqual(TEXT("Source edge history preserves the combo sample"),StrokeSamples.Last(),12);
    auto* Persisted=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot,0));
    if (!TestNotNull(TEXT("Source edge history reaches disk"),Persisted)) return false;
    TestEqual(TEXT("Source edge history survives a save round trip"),Persisted->GetIntArraySetting(TEXT("AllStrokesPerEdge")).Num(),4);
    Stats->RefreshRecoveredStats();
    TestEqual(TEXT("Statistics screen consumes the persisted edge history"),Stats->AvgStrokesPerEdge,9);
    return true;
}
#endif
