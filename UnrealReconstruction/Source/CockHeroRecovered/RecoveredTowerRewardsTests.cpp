#include "RecoveredTowerRewards.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTowerRewardsTest,"CockHero.Recovery.NewerInventory.TowerRewardCategories",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredTowerRewardsTest::RunTest(const FString& Parameters) {
    auto* Inventory=NewObject<URecoveredNewerInventory>();
    FRandomStream Random(173203);
    FRecoveredTowerRewardContext Context;
    Context.Tier=6; Context.Lane=2; Context.BaseCoins=100; Context.BaseSuccuCoins=9;
    Context.bFinalRound=true; Context.UnlockableModifiers={0,1,2};
    const TSet<uint8> Owned;
    for (int32 Iteration=0;Iteration<50;++Iteration) {
        const auto Rewards=RecoveredTowerRewards::Generate(Context,*Inventory,Owned,Random);
        TestEqual(TEXT("Native two reward entries"),Rewards.Num(),2);
        if (Rewards.Num()!=2) return false;
        TestEqual(TEXT("Final hard lane forces item unlock"),Rewards[0].Type,uint8(2));
        TestTrue(TEXT("Reward categories cannot duplicate"),Rewards[0].Type!=Rewards[1].Type);
        TestTrue(TEXT("Unlocked item belongs to source information table"),Rewards[0].Item!=ERecoveredShopItemType::IncreaseCumMeter && Rewards[0].Item!=ERecoveredShopItemType::Edge && Rewards[0].Item!=ERecoveredShopItemType::None);
    }
    for (uint8 Item=1;Item<=13;++Item) if (Item!=2 && Item!=8) {
        Inventory->UnlockItem(static_cast<ERecoveredShopItemType>(Item));
        Inventory->OwnedItems[static_cast<ERecoveredShopItemType>(Item)].Level=5;
    }
    const TSet<uint8> AllModifiers={0,1,2};
    Context.BaseCoins=100; Context.BaseSuccuCoins=9;
    const auto Saturated=RecoveredTowerRewards::Generate(Context,*Inventory,AllModifiers,Random);
    TestEqual(TEXT("Fully owned state still yields two currencies"),Saturated.Num(),2);
    bool bCoins=false,bSuccu=false;
    for (const auto& Reward:Saturated) { bCoins|=Reward.Type==0; bSuccu|=Reward.Type==1; }
    TestTrue(TEXT("Currency fallback contains coins and SuccuCoins"),bCoins && bSuccu);
    return true;
}
#endif
