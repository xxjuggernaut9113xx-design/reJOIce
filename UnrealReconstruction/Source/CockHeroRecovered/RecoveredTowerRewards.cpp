#include "RecoveredTowerRewards.h"
#include "RecoveredRules.h"
#include "RecoveredSuccuEconomy.h"
#include "RecoveredNewerInventoryAdapter.h"

TArray<FRecoveredTowerReward> RecoveredTowerRewards::Generate(const FRecoveredTowerRewardContext& Context,const URecoveredNewerInventory& Inventory,const TSet<uint8>& OwnedModifiers,FRandomStream& Random) {
    // CalculateRewardsForRound 0x1482d8190; ctor 0x1482cf740, category helpers
    // 0x1482d1660/1ac0/1490 and source table bIsUpgradeable flags.
    static constexpr float Primary[3][5]={{45,25,20,5,5},{22,35,28,12,10},{5,35,45,35,25}};
    static constexpr float Bonus[3][6][5]={
        {{35,45,15,5,3},{30,45,20,8,5},{25,45,24,10,8},{20,40,28,12,12},{16,38,32,15,15},{12,35,36,18,18}},
        {{25,40,22,8,5},{22,38,28,12,8},{18,36,34,15,12},{14,32,40,18,18},{10,30,45,22,22},{8,28,50,25,25}},
        {{8,32,40,30,15},{6,30,45,35,18},{5,28,50,40,22},{4,25,55,45,30},{3,22,60,50,40},{2,20,65,55,45}}
    };
    const uint8 Lane=FMath::Min<uint8>(Context.Lane,2);
    const int32 Tier=FMath::Clamp(Context.Tier,1,6);
    TArray<ERecoveredShopItemType> Unlocks,Upgrades;
    for (uint8 Value=1;Value<=13;++Value) {
        if (Value==2 || Value==8) continue;
        const auto Type=static_cast<ERecoveredShopItemType>(Value);
        const auto* State=Inventory.OwnedItems.Find(Type);
        if (!State || !State->bIsUnlocked) Unlocks.Add(Type);
        else if (State->Level<5 && Value!=7 && Value!=10) Upgrades.Add(Type);
    }
    TArray<uint8> Modifiers;
    for (const uint8 Modifier:Context.UnlockableModifiers) if (Modifier!=22 && !OwnedModifiers.Contains(Modifier)) Modifiers.AddUnique(Modifier);
    TArray<FRecoveredTowerReward> Rewards;
    auto HasType=[&](uint8 Type) { return Rewards.ContainsByPredicate([Type](const auto& Reward){ return Reward.Type==Type; }); };
    auto Available=[&](uint8 Category) {
        if (Category==1 || Category==2) return !HasType(Category-1);
        if (Category==3) return !HasType(3) && !Upgrades.IsEmpty();
        if (Category==4) return !HasType(2) && !Unlocks.IsEmpty();
        return Category==5 && !HasType(5) && !Modifiers.IsEmpty();
    };
    auto Add=[&](uint8 Category,bool bBonus) {
        if (!Available(Category)) return false;
        FRecoveredTowerReward Reward;
        if (Category==1) {
            const float Multiplier=Lane==0 ? (bBonus ? .4f : .75f) : Lane==1 ? (bBonus ? .75f : 1.f) : 2.f;
            Reward.Type=0; Reward.Amount=FMath::Max(1,FMath::RoundToInt(Context.BaseCoins*Multiplier));
        } else if (Category==2) { Reward.Type=1; Reward.Amount=FMath::Max(1,Context.BaseSuccuCoins); }
        else if (Category==3) {
            Reward.Type=3; Reward.Item=Upgrades[Random.RandRange(0,Upgrades.Num()-1)];
            Reward.Amount=Tier>=6 ? 3 : ((Lane==2 && Tier>=4) || (Lane==1 && Tier>=5)) ? 2 : 1;
        } else if (Category==4) { Reward.Type=2; Reward.Item=Unlocks[Random.RandRange(0,Unlocks.Num()-1)]; }
        else { Reward.Type=5; Reward.Modifier=Modifiers[Random.RandRange(0,Modifiers.Num()-1)]; }
        Rewards.Add(Reward);
        return true;
    };
    auto Pick=[&](const float* Weights,bool bBonus) {
        float Total=0;
        for (uint8 Category=1;Category<=5;++Category) if (Available(Category)) Total+=Weights[Category-1];
        float Roll=Random.FRand()*Total;
        if (Total>0) for (uint8 Category=1;Category<=5;++Category) if (Available(Category)) {
            Roll-=Weights[Category-1];
            if (Roll<=0) { Add(Category,bBonus); return; }
        }
        for (const uint8 Category:{uint8(5),uint8(3),uint8(4),uint8(2),uint8(1)}) if (Add(Category,bBonus)) return;
    };
    if (Context.bFinalRound && Lane==2) Add(4,false);
    if (Rewards.IsEmpty()) Pick(Primary[Lane],false);
    Pick(Bonus[Lane][Tier-1],true);
    if (Rewards.Num()<2) for (const uint8 Category:{uint8(5),uint8(3),uint8(4),uint8(2),uint8(1)}) {
        if (Add(Category,true) && Rewards.Num()>=2) break;
    }
    return Rewards;
}

void RecoveredTowerRewards::Apply(ARecoveredGlobalManager& Manager,const TArray<FRecoveredTowerReward>& Rewards) {
    auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(Manager);
    for (const auto& Reward:Rewards) {
        if (Reward.Type==0) {
            Manager.PlayerVariables.PlayerCoins=URecoveredStateRuleLibrary::AddInt32Wrapping(Manager.PlayerVariables.PlayerCoins,Reward.Amount);
            Manager.OnCoinsAdded.Broadcast(Reward.Amount,Manager.PlayerVariables.PlayerCoins);
        }
        else if (Reward.Type==1 && Manager.SuccuEconomy) Manager.SuccuEconomy->AddSuccuCoins(Reward.Amount);
        else if (Reward.Type==5 && Manager.SuccuEconomy) Manager.SuccuEconomy->OwnedModifiers.Add(Reward.Modifier);
        else if (Inventory && Reward.Type==2) Inventory->UnlockItem(Reward.Item);
        else if (Inventory && Reward.Type==3) {
            // BP_CHGameInstance.RedeemRewardsFromArray calls UpgradeItem once
            // for each entry; it does not iterate RewardEntry.Amount.
            bool SourceSuccess=false;
            Inventory->UpgradeItem(Reward.Item,false,SourceSuccess);
        }
    }
    RecoveredNewerInventoryAdapter::Persist(Manager);
}
