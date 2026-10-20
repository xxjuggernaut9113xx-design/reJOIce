#pragma once
#include "CoreMinimal.h"
#include "RecoveredNewerInventory.h"

class ARecoveredGlobalManager;
struct FRecoveredTowerReward {
    uint8 Type=0;
    ERecoveredShopItemType Item=ERecoveredShopItemType::None;
    uint8 Modifier=22;
    int32 Amount=1;
};
struct FRecoveredTowerRewardContext {
    int32 Tier=1;
    uint8 Lane=0;
    int32 BaseCoins=1;
    int32 BaseSuccuCoins=1;
    bool bFinalRound=false;
    TArray<uint8> UnlockableModifiers;
};
namespace RecoveredTowerRewards {
COCKHERORECOVERED_API TArray<FRecoveredTowerReward> Generate(const FRecoveredTowerRewardContext& Context,const URecoveredNewerInventory& Inventory,const TSet<uint8>& OwnedModifiers,FRandomStream& Random);
COCKHERORECOVERED_API void Apply(ARecoveredGlobalManager& Manager,const TArray<FRecoveredTowerReward>& Rewards);
}
