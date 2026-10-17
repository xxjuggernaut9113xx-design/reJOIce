#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

#if WITH_DEV_AUTOMATION_TESTS
namespace {
int32 FindRecoveredLootSeed(int32 RequiredCashRoll,int32 RequiredRewardIndex=INDEX_NONE) {
    for (int32 Seed=1;Seed<100000;++Seed) {
        FMath::RandInit(Seed);
        if (UKismetMathLibrary::RandomIntegerInRange(0,5)!=RequiredCashRoll) continue;
        if (RequiredCashRoll==0 || UKismetMathLibrary::RandomIntegerInRange(0,6)==RequiredRewardIndex) return Seed;
    }
    return INDEX_NONE;
}

void RollRecoveredLootAtSeed(ARecoveredGlobalManager& Manager,int32 Seed) {
    FMath::RandInit(Seed);
    Manager.RollAndGiveLootDropsV2();
}

FRecoveredDifficultyConfig MakeGuaranteedLegacyLootConfig() {
    FRecoveredDifficultyConfig Config;
    Config.CumIncreaseItemSpawnChance=100.0;
    Config.DecreaseHeatItemSpawnChance=100.0;
    Config.EdgeItemSpawnChance=100.0;
    Config.BreakItemSpawnChance=100.0;
    Config.SlowdownItemSpawnChance=100.0;
    Config.BonerPillSpawnChance=100.0;
    Config.SuccuShieldSpawnChance=100.0;
    return Config;
}

void FillLegacyLootCaps(ARecoveredGlobalManager& Manager) {
    Manager.OwnedItemCounts.Reset();
    Manager.OwnedItemCounts.Add(TEXT("XCumChance"),1);
    Manager.OwnedItemCounts.Add(TEXT("DecreaseHeat"),3);
    Manager.OwnedItemCounts.Add(TEXT("Edge"),10);
    Manager.OwnedItemCounts.Add(TEXT("Slowdown"),3);
    Manager.OwnedItemCounts.Add(TEXT("Break"),2);
    Manager.OwnedItemCounts.Add(TEXT("BonerPill"),5);
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredLootDropParityTest,"CockHero.Recovery.LootDropParity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredLootDropParityTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Source loot manager"),Manager)) return false;
    Manager->PlayerVariables.CoinEarnMultiplier=1.0;

    const FName SourceItems[]={TEXT("DecreaseHeat"),TEXT("XCumChance"),TEXT("Edge"),TEXT("Break"),TEXT("BonerPill"),TEXT("Resupply"),TEXT("Slowdown")};
    const int32 SourceCaps[]={3,1,10,2,5,1,3};
    for (int32 Index=0;Index<UE_ARRAY_COUNT(SourceItems);++Index) {
        TestEqual(FString::Printf(TEXT("Source loot cap %s"),*SourceItems[Index].ToString()),Manager->GetRecoveredItemMaximum(SourceItems[Index]),SourceCaps[Index]);
        const int32 Seed=FindRecoveredLootSeed(1,Index);
        if (!TestTrue(FString::Printf(TEXT("Seed reaches source loot index %d"),Index),Seed!=INDEX_NONE)) continue;
        Manager->OwnedItemCounts.Reset();
        Manager->PlayerVariables.PlayerCoins=0;
        Manager->PlayerVariables.SessionCoinsEarned=0;
        Manager->PlayerVariables.bHasItems=false;
        RollRecoveredLootAtSeed(*Manager,Seed);
        TestEqual(FString::Printf(TEXT("Source item grant %s"),*SourceItems[Index].ToString()),Manager->GetOwnedItemCount(SourceItems[Index]),1);
        TestEqual(TEXT("Source item grant does not mint cash"),Manager->PlayerVariables.PlayerCoins,0);
        TestTrue(TEXT("Source item grant marks inventory available"),Manager->PlayerVariables.bHasItems);
    }

    const int32 CashSeed=FindRecoveredLootSeed(0);
    if (TestTrue(TEXT("Seed reaches source cash branch"),CashSeed!=INDEX_NONE)) {
        Manager->OwnedItemCounts.Reset();
        Manager->PlayerVariables.PlayerCoins=0;
        Manager->PlayerVariables.SessionCoinsEarned=0;
        RollRecoveredLootAtSeed(*Manager,CashSeed);
        TestEqual(TEXT("Source cash branch grants fifty coins"),Manager->PlayerVariables.PlayerCoins,50);
        TestEqual(TEXT("Source cash branch tracks session coins"),Manager->PlayerVariables.SessionCoinsEarned,50);
        TestEqual(TEXT("Source cash branch grants no item"),Manager->OwnedItemCounts.Num(),0);
    }

    const int32 ResupplySeed=FindRecoveredLootSeed(1,5);
    if (TestTrue(TEXT("Seed reaches source resupply branch"),ResupplySeed!=INDEX_NONE)) {
        Manager->OwnedItemCounts.Reset();
        Manager->OwnedItemCounts.Add(TEXT("Resupply"),1);
        Manager->PlayerVariables.PlayerCoins=0;
        Manager->PlayerVariables.SessionCoinsEarned=0;
        RollRecoveredLootAtSeed(*Manager,ResupplySeed);
        TestEqual(TEXT("Capped source resupply remains capped"),Manager->GetOwnedItemCount(TEXT("Resupply")),1);
        TestEqual(TEXT("Capped source resupply becomes cash"),Manager->PlayerVariables.PlayerCoins,50);
        TestEqual(TEXT("Capped source resupply tracks cash"),Manager->PlayerVariables.SessionCoinsEarned,50);
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredLegacyLootDropParityTest,"CockHero.Recovery.LegacyLootDropParity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredLegacyLootDropParityTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Legacy loot manager"),Manager)) return false;

    Manager->ActiveDifficulty=MakeGuaranteedLegacyLootConfig();
    Manager->OwnedItemCounts.Reset();
    Manager->ItemUpgradeLevels.Reset();
    Manager->PlayerVariables.bHasItems=false;
    FMath::RandInit(1776);
    Manager->RollAndGiveLootDrops();
    TestEqual(TEXT("Legacy cum chance roll grants one source item"),Manager->GetOwnedItemCount(TEXT("XCumChance")),1);
    TestEqual(TEXT("Legacy heat roll grants one source item"),Manager->GetOwnedItemCount(TEXT("DecreaseHeat")),1);
    TestEqual(TEXT("Legacy edge roll grants one source item"),Manager->GetOwnedItemCount(TEXT("Edge")),1);
    TestEqual(TEXT("Legacy swapped slowdown chance grants break"),Manager->GetOwnedItemCount(TEXT("Break")),1);
    TestEqual(TEXT("Legacy swapped break chance grants slowdown"),Manager->GetOwnedItemCount(TEXT("Slowdown")),1);
    TestEqual(TEXT("Legacy boner pill roll grants one source item"),Manager->GetOwnedItemCount(TEXT("BonerPill")),1);
    TestEqual(TEXT("Legacy level-zero shield roll grants ten source shields"),Manager->GetOwnedItemCount(TEXT("SuccuShield")),10);
    TestTrue(TEXT("Legacy source rolls mark inventory present"),Manager->PlayerVariables.bHasItems);

    Manager->OwnedItemCounts.Reset();
    Manager->OwnedItemCounts.Add(TEXT("Slowdown"),3);
    Manager->OwnedItemCounts.Add(TEXT("XCumChance"),1);
    Manager->OwnedItemCounts.Add(TEXT("DecreaseHeat"),3);
    Manager->OwnedItemCounts.Add(TEXT("Edge"),10);
    Manager->OwnedItemCounts.Add(TEXT("BonerPill"),5);
    Manager->ActiveDifficulty=MakeGuaranteedLegacyLootConfig();
    FMath::RandInit(1777);
    Manager->RollAndGiveLootDrops();
    TestEqual(TEXT("Capped legacy slowdown suppresses the break grant"),Manager->GetOwnedItemCount(TEXT("Break")),0);
    TestEqual(TEXT("Uncapped legacy break gate can exceed slowdown cap"),Manager->GetOwnedItemCount(TEXT("Slowdown")),4);

    const int32 SourceShieldAmounts[]={10,15,20,25,35};
    for (int32 Level=0;Level<UE_ARRAY_COUNT(SourceShieldAmounts);++Level) {
        FillLegacyLootCaps(*Manager);
        Manager->ItemUpgradeLevels.Reset();
        Manager->ItemUpgradeLevels.Add(TEXT("SuccuShield"),Level);
        Manager->ActiveDifficulty=FRecoveredDifficultyConfig();
        Manager->ActiveDifficulty.SuccuShieldSpawnChance=100.0;
        FMath::RandInit(1800+Level);
        Manager->RollAndGiveLootDrops();
        TestEqual(FString::Printf(TEXT("Legacy shield grant at source upgrade %d"),Level),Manager->GetOwnedItemCount(TEXT("SuccuShield")),SourceShieldAmounts[Level]);
    }

    Manager->OwnedItemCounts.Reset();
    Manager->ActiveDifficulty=FRecoveredDifficultyConfig();
    Manager->ActiveDifficulty.CumIncreaseItemSpawnChance=100.0;
    Manager->IsAutoDrawEnabled=true;
    Manager->bStopSequence=false;
    Manager->BeatContext.CardType=5;
    if (!TestNotNull(TEXT("Legacy completion has a recovered beat timeline"),Manager->BeatTimeline.Get())) return false;
    Manager->BeatTimeline->StopSequence();
    FMath::RandInit(2026);
    Manager->CompleteBeatSequence();
    TestEqual(TEXT("Legacy completion invokes the source roll route before its card-five stop"),Manager->GetOwnedItemCount(TEXT("XCumChance")),1);
    return true;
}
#endif
