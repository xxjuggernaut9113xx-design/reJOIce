#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredStoreItem.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "Widgets/SWidget.h"

namespace CockHeroRecoveredStoreItemParity {
struct FSourceCase {
    const TCHAR* Asset;
    const TCHAR* ItemID;
    int32 Purchase[5];
    int32 Upgrade[5];
};

static const FSourceCase Cases[]={
    {TEXT("+XCumChance_StoreItem"),TEXT("XCumChance"),{250,300,400,500,750},{300,350,500,999,0}},
    {TEXT("BonerPillStoreItem"),TEXT("BonerPill"),{100,125,150,175,200},{150,300,450,999,0}},
    {TEXT("BreakStoreItem"),TEXT("Break"),{150,200,300,400,600},{200,350,500,999,0}},
    {TEXT("DecreaseHeatLevel_StoreItem"),TEXT("DecreaseHeat"),{150,175,175,200,350},{100,300,500,999,0}},
    {TEXT("EdgeStoreItem"),TEXT("Edge"),{350,200,150,125,75},{150,300,450,750,0}},
    {TEXT("ResupplyStoreItem"),TEXT("Resupply"),{350,350,350,350,350},{20,20,20,20,20}},
    {TEXT("SlowdownStoreItem"),TEXT("Slowdown"),{100,150,150,175,175},{150,300,500,750,0}},
    {TEXT("SuccuShieldStoreItem"),TEXT("SuccuShield"),{75,125,175,300,400},{100,200,350,600,0}}
};

FString ExpectedSourceEffect(FName ItemID,int32 Level) {
    Level=FMath::Clamp(Level,0,4);
    if (ItemID==TEXT("XCumChance")) {
        static constexpr int32 Values[]={5,8,12,18,35};
        return FString::Printf(TEXT("Increases Cum Meter by %d%%\r\nUse When Ready to Cum"),Values[Level]);
    }
    if (ItemID==TEXT("BonerPill")) {
        static const TCHAR* Values[]={
            TEXT("x2.0 Stroking | x2.0 Speed | \r\nx2.0 Coins | Use to Boost Rewards"),
            TEXT("x2.0 Stroking | x2.0 Speed | \r\nx2.0 Coins | Use to Boost Rewards"),
            TEXT("x3.0 Stroking | x3.0 Speed | \r\nx2.0 Coins | Use to Boost Rewards"),
            TEXT("x4.0 Stroking | x5.0 Speed | \r\nx3.0 Coins | Use to Boost Rewards"),
            TEXT("x6.0 Stroking | x6.0 Speed | \r\nx3.0 Coins | Use to Boost Rewards")
        };
        return Values[Level];
    }
    if (ItemID==TEXT("Break")) {
        static constexpr int32 Values[]={5,10,15,25,50};
        return FString::Printf(TEXT("grants a %d second break\r\nstops stroking"),Values[Level]);
    }
    if (ItemID==TEXT("DecreaseHeat")) {
        static constexpr int32 Values[]={15,25,35,45,60};
        return FString::Printf(TEXT("Decreases heat by %d%%\r\nUse to manage difficulty"),Values[Level]);
    }
    if (ItemID==TEXT("Edge")) return TEXT("INCREASES PERFECT EDGE \r\nWindow = LAST 15% OF TASK");
    if (ItemID==TEXT("Resupply")) return TEXT("SPAWNS A STORE EVENT\r\nCHOOSE FROM POWERFUL ITEMS");
    if (ItemID==TEXT("Slowdown")) return FString::Printf(TEXT("Slows down stroking by x%d\r\n(Affects Remaining Strokes)"),Level+2);
    if (ItemID==TEXT("SuccuShield")) return TEXT("prevents succubi from \r\nspawning (toggle on/off)");
    return FString();
}

FString ExpectedSourceTitle(FName ItemID,int32 Level) {
    Level=FMath::Clamp(Level,0,4);
    if (ItemID==TEXT("XCumChance")) {
        static constexpr int32 Values[]={5,8,12,18,35};
        return FString::Printf(TEXT("+%d%% Cum Meter"),Values[Level]);
    }
    if (ItemID==TEXT("SuccuShield")) {
        static constexpr int32 Values[]={1,4,7,10,15};
        return FString::Printf(TEXT("+%d Succushield%s"),Values[Level],Values[Level]==1?TEXT(""):TEXT("s"));
    }
    if (ItemID==TEXT("BonerPill")) return TEXT("boner pill");
    if (ItemID==TEXT("Break")) return TEXT("break");
    if (ItemID==TEXT("DecreaseHeat")) return TEXT("Decrease Heat");
    if (ItemID==TEXT("Edge")) return TEXT("Edge");
    if (ItemID==TEXT("Resupply")) return TEXT("resupply");
    if (ItemID==TEXT("Slowdown")) return TEXT("Slowdown");
    return FString();
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredStoreItemParityTest,"CockHero.Recovery.StoreItemParity",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredStoreItemParityTest::RunTest(const FString& Parameters) {
    using namespace CockHeroRecoveredStoreItemParity;
    for (const FSourceCase& Source:Cases) {
        const FString Path=FString::Printf(TEXT("/Game/Recovery/UI/%s.%s_C"),Source.Asset,Source.Asset);
        UClass* Class=LoadClass<URecoveredStoreItemWidget>(nullptr,*Path);
        if (!TestNotNull(*FString::Printf(TEXT("Source store class %s"),Source.Asset),Class)) continue;
        TestTrue(TEXT("Source store native owner"),Class->IsChildOf(URecoveredStoreItemWidget::StaticClass()));
        const auto* Defaults=Cast<URecoveredStoreItemWidget>(Class->GetDefaultObject());
        if (!TestNotNull(TEXT("Source store defaults"),Defaults)) continue;
        TestEqual(TEXT("Source item identifier"),Defaults->ItemID,FName(Source.ItemID));

        auto* Widget=NewObject<URecoveredStoreItemWidget>(GetTransientPackage(),Class);
        if (!TestTrue(TEXT("Source store widget initializes"),Widget->Initialize())) continue;
        TSharedRef<SWidget> Slate=Widget->TakeWidget();
        auto* Buy=Cast<UButton>(Widget->GetWidgetFromName(TEXT("BuyButton")));
        auto* Upgrade=Cast<UButton>(Widget->GetWidgetFromName(TEXT("UpgradeButton")));
        auto* BuyText=Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock_371")));
        auto* UpgradeText=Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock_506")));
        auto* Description=Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("EffectDescription")));
        auto* Level=Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("EffectDescription_1")));
        auto* Title=Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock_92")));
        if (!TestNotNull(TEXT("Source buy button"),Buy)
            || !TestNotNull(TEXT("Source upgrade button"),Upgrade)
            || !TestNotNull(TEXT("Source buy label"),BuyText)
            || !TestNotNull(TEXT("Source upgrade label"),UpgradeText)
            || !TestNotNull(TEXT("Source effect label"),Description)
            || !TestNotNull(TEXT("Source level label"),Level)
            || !TestNotNull(TEXT("Source title label"),Title)) continue;
        TestTrue(TEXT("Source buy click binding"),Buy->OnClicked.IsBound());
        TestTrue(TEXT("Source buy hover binding"),Buy->OnHovered.IsBound());
        TestTrue(TEXT("Source buy unhover binding"),Buy->OnUnhovered.IsBound());
        TestTrue(TEXT("Source upgrade click binding"),Upgrade->OnClicked.IsBound());
        TestTrue(TEXT("Source upgrade hover binding"),Upgrade->OnHovered.IsBound());
        TestTrue(TEXT("Source upgrade unhover binding"),Upgrade->OnUnhovered.IsBound());
        for (int32 Index=0;Index<5;++Index) {
            Widget->CurrentLevel=Index;
            Widget->RefreshPrices();
            TestEqual(TEXT("Source purchase ladder"),Widget->GetBuyAmount(),Source.Purchase[Index]);
            TestEqual(TEXT("Source upgrade ladder"),Widget->GetUpgradeAmount(),Source.Upgrade[Index]);
            TestEqual(TEXT("Source purchase state"),Widget->PurchaseCost,Source.Purchase[Index]);
            TestEqual(TEXT("Source upgrade state"),Widget->UpgradeCost,Source.Upgrade[Index]);
            TestEqual(TEXT("Source effect copy"),Widget->GetEffectDescription().ToString(),ExpectedSourceEffect(Defaults->ItemID,Index));
            TestEqual(TEXT("Source title copy"),Widget->GetTitleText().ToString(),ExpectedSourceTitle(Defaults->ItemID,Index));
            TestEqual(TEXT("Source level copy"),Widget->GetLevelText().ToString(),FString::Printf(TEXT("Level %d"),Index+1));
            const FString ExpectedUpgrade=(Defaults->ItemID!=TEXT("Resupply") && Index==4)
                ? TEXT("Max Level")
                : FString::Printf(TEXT("Upgrade: %d"),Source.Upgrade[Index]);
            TestEqual(TEXT("Source upgrade copy"),Widget->GetUpgradeText().ToString(),ExpectedUpgrade);
        }
        Widget->CurrentLevel=0;
        Widget->RefreshPrices();
        TestEqual(TEXT("Source buy text"),BuyText->GetText().ToString(),FString::Printf(TEXT("Buy: %d"),Source.Purchase[0]));
        TestEqual(TEXT("Source upgrade text"),UpgradeText->GetText().ToString(),FString::Printf(TEXT("Upgrade: %d"),Source.Upgrade[0]));
        TestFalse(TEXT("Source description is populated"),Description->GetText().IsEmpty());
        TestEqual(TEXT("Source first level text"),Level->GetText().ToString(),FString(TEXT("Level 1")));
        TestFalse(TEXT("Source title is populated"),Title->GetText().IsEmpty());
    }

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Source store interaction manager"),Manager)) return false;
    UClass* SlowdownClass=LoadClass<URecoveredStoreItemWidget>(nullptr,TEXT("/Game/Recovery/UI/SlowdownStoreItem.SlowdownStoreItem_C"));
    if (!TestNotNull(TEXT("Source slowdown class"),SlowdownClass)) return false;
    auto* Slowdown=CreateWidget<URecoveredStoreItemWidget>(World,SlowdownClass);
    if (!TestNotNull(TEXT("Source slowdown widget"),Slowdown)) return false;
    TSharedRef<SWidget> SlowdownSlate=Slowdown->TakeWidget();
    Manager->PlayerVariables.PlayerCoins=1000;
    Manager->SetRecoveredItemUpgradeLevel(TEXT("Slowdown"),0);
    Slowdown->RefreshPrices();
    TestTrue(TEXT("Source purchase accepts source price"),Slowdown->TryBuy());
    TestEqual(TEXT("Source purchase debits source price"),Manager->PlayerVariables.PlayerCoins,900);
    TestEqual(TEXT("Source purchase grants one item"),Manager->GetOwnedItemCount(TEXT("Slowdown")),1);
    TestEqual(TEXT("Source purchase records spent points"),Manager->PointsSpent,100);
    TestTrue(TEXT("Source upgrade accepts source price"),Slowdown->TryUpgrade());
    TestEqual(TEXT("Source upgrade debits source price"),Manager->PlayerVariables.PlayerCoins,750);
    TestEqual(TEXT("Source upgrade advances level"),Manager->GetRecoveredItemUpgradeLevel(TEXT("Slowdown")),1);
    TestEqual(TEXT("Source upgraded purchase price"),Slowdown->GetBuyAmount(),150);
    while (Manager->GetOwnedItemCount(TEXT("Slowdown"))<Manager->GetRecoveredItemMaximum(TEXT("Slowdown"))) Manager->AcquireStoreItem(TEXT("Slowdown"));
    const int32 CoinsBeforeCap=Manager->PlayerVariables.PlayerCoins;
    TestFalse(TEXT("Source cap blocks further purchase"),Slowdown->TryBuy());
    TestEqual(TEXT("Source cap preserves coins"),Manager->PlayerVariables.PlayerCoins,CoinsBeforeCap);
    return true;
}
#endif
