#include "RecoveredStatsTabWidget.h"

#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredRules.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredStatsTabWidgetTest,"CockHero.Recovery.StatsTabWidget",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredStatsTabWidgetTest::RunTest(const FString& Parameters) {
    FString EvidenceText;
    TSharedPtr<FJsonObject> Evidence;
    const FString EvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/stats-tab-recovery.json");
    if (!FFileHelper::LoadFileToString(EvidenceText,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(EvidenceText),Evidence)) {
        AddError(TEXT("Missing stats tab recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Original source execution remains unclaimed"),Evidence->GetBoolField(TEXT("source_executed")));
    TestEqual(TEXT("Stats source construct entrypoint"),Evidence->GetObjectField(TEXT("source_entrypoints"))->GetIntegerField(TEXT("Construct")),286);
    TestEqual(TEXT("Stats source edit entrypoint"),Evidence->GetObjectField(TEXT("source_entrypoints"))->GetIntegerField(TEXT("EditPlayerCardButton")),291);

    auto* Save=NewObject<URecoveredSaveGame>();
    if (!TestTrue(TEXT("Stats tab save initializes"),Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Stats tab data initializes"),
        Save->SetIntArraySetting(TEXT("AllSessionTimes"),{61,60}) &&
        Save->SetIntArraySetting(TEXT("AllSessionEdges"),{1,4}) &&
        Save->SetIntArraySetting(TEXT("AllSessionStrokeCounts"),{80,45}) &&
        Save->SetIntArraySetting(TEXT("AllSessionCombos"),{5,17}) &&
        Save->SetNumberSetting(TEXT("SessionsWon"),1) &&
        Save->SetNumberSetting(TEXT("SessionsLost"),1) &&
        Save->SetNumberSetting(TEXT("TotalLifetimeStrokes"),125) &&
        Save->SetNumberSetting(TEXT("TotalLifetimeEdges"),5) &&
        Save->SetNumberSetting(TEXT("TotalEnemiesDefeated"),9) &&
        Save->SetNumberSetting(TEXT("TotalSuccubiDefeated"),4) &&
        Save->SetNumberSetting(TEXT("TotalLifetimeItemUses"),3) &&
        Save->SetNumberSetting(TEXT("TotalDrawCount"),6) &&
        Save->SetNumberSetting(TEXT("Lifetime_BestEdgeStreak"),12) &&
        Save->SetNumberSetting(TEXT("Lifetime_MostSuccubiInSession"),3) &&
        Save->SetNumberSetting(TEXT("Lifetime_MostXPEarnedInSession"),120) &&
        Save->SetNumberSetting(TEXT("Lifetime_MostPerfectEdgesInSession"),2) &&
        Save->SetNumberSetting(TEXT("Lifetime_MostCumWindowsHitInSession"),5) &&
        Save->SetNumberSetting(TEXT("Lifetime_MostItemsUsedInSession"),2) &&
        Save->SetNumberSetting(TEXT("Lifetime_MostMoneySpentInSession"),40))) return false;

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };

    auto* Instance=NewObject<URecoveredGameInstance>();
    Instance->CurrentSave=Save;
    Instance->ProgressionManager=NewObject<URecoveredProgressionManager>(Instance);
    Instance->ProgressionManager->CurrentLevel=3;
    Instance->ProgressionManager->CurrentXP=72;
    Instance->ChallengeTracker=NewObject<URecoveredChallengeTracker>(Instance);
    Instance->ChallengeTracker->ChallengeTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    if (!TestTrue(TEXT("Stats tab challenge ledger initializes"),Instance->ChallengeTracker->InitializeChallenges())) return false;
    Instance->ChallengeTracker->CompletedChallenges.Add(TEXT("quickshot"));
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    UClass* StatsClass=LoadClass<URecoveredStatsTabWidget>(nullptr,TEXT("/Game/Recovery/UI/StatsTabWidget.StatsTabWidget_C"));
    if (!TestNotNull(TEXT("Stats tab recovered class"),StatsClass)) return false;
    if (!TestTrue(TEXT("Stats tab uses its recovered native owner"),StatsClass->IsChildOf(URecoveredStatsTabWidget::StaticClass()))) return false;
    auto* Stats=CreateWidget<URecoveredStatsTabWidget>(World,StatsClass);
    if (!TestNotNull(TEXT("Stats tab instantiates"),Stats)) return false;
    Stats->SetRecoveredStatsTabGameInstance(Instance);
    Stats->TakeWidget();
    Stats->InitializeStats();

    TestEqual(TEXT("Source average duration rounds to seconds"),Stats->GetRecoveredAverageDurationText(),FString(TEXT("00:01:01")));
    TestEqual(TEXT("Source average edges rounds to nearest"),Stats->GetRecoveredAverageEdgesText(),FString(TEXT("3")));
    TestEqual(TEXT("Source average strokes per minute rounds to nearest"),Stats->GetRecoveredAverageStrokesPerMinuteText(),FString(TEXT("62")));
    TestEqual(TEXT("Source average strokes rounds to nearest"),Stats->GetRecoveredAverageStrokesText(),FString(TEXT("63")));
    TestEqual(TEXT("Source lifetime ledger"),
        Stats->GetRecoveredLifetimeStatsText(),
        FString(TEXT("Play Time: 2m 1s\nSessions Played: 2\nWin Rate: 50%\nTotal Edges: 5\nTotal Strokes: 125\nEnemies Defeated: 9\nSuccubi Defeated: 4\nMoney Spent: 0\nChallenges Completed: 1/"))+FString::FromInt(Instance->ChallengeTracker->GetTotalChallengeCount())+TEXT("\nItems Used: 3\nCum Windows Hit: 6\n"));
    TestEqual(TEXT("Source high-score ledger"),
        Stats->GetRecoveredHighscoresText(),
        FString(TEXT("Longest Edge Streak: 12\nHighest Combo: 17\nMost Edges: 4\nMost Strokes: 80\nLongest Session: 01:01\nMost Succubi: 3\nMost XP Earned: 120\nMost Perfect Edges: 2\nMost Cum Windows Hit: 5\nMost Items Used: 2\nMost Money Spent: 40\n")));

    if (auto* Text=Cast<UTextBlock>(Stats->GetWidgetFromName(TEXT("LifetimeStatsText")))) TestEqual(TEXT("Source lifetime widget binding"),Text->GetText().ToString(),Stats->GetRecoveredLifetimeStatsText());
    else AddError(TEXT("Missing source lifetime text widget"));
    if (auto* Text=Cast<UTextBlock>(Stats->GetWidgetFromName(TEXT("HighscoresText")))) TestEqual(TEXT("Source high-score widget binding"),Text->GetText().ToString(),Stats->GetRecoveredHighscoresText());
    else AddError(TEXT("Missing source high-score text widget"));
    if (auto* Text=Cast<UTextBlock>(Stats->GetWidgetFromName(TEXT("LevelText")))) TestEqual(TEXT("Source level format"),Text->GetText().ToString(),FString(TEXT("Level 3 (72XP/145XP)")));
    else AddError(TEXT("Missing source level text widget"));
    if (auto* Bar=Cast<UProgressBar>(Stats->GetWidgetFromName(TEXT("LevelProgressBar")))) TestEqual(TEXT("Source level progress"),Bar->GetPercent(),72.0f/145.0f);
    else AddError(TEXT("Missing source level progress widget"));
    if (auto* Button=Cast<UButton>(Stats->GetWidgetFromName(TEXT("EditPlayerCardButton")))) TestTrue(TEXT("Source username edit binding"),Button->OnClicked.IsBound());
    else AddError(TEXT("Missing source username edit button"));
    return true;
}
#endif
