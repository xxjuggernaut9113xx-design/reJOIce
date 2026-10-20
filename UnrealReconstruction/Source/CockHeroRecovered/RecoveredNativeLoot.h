#pragma once
#include "CoreMinimal.h"
#include "RecoveredNewerInventory.h"

struct FRecoveredNativeLootContext {
    bool bBurningProfits=false;
    bool bBiggerPockets=false;
    bool bPrizeMachine=false;
    bool bBadRNG=false;
    bool bDrySpell=false;
    bool bJackpotDrops=false;
    int32 CoinReward=10;
    float JackpotWeight=7.5f;
};

struct FRecoveredNativeLootReward {
    uint8 Type=0;
    ERecoveredShopItemType Item=ERecoveredShopItemType::None;
    int32 Amount=10;
};

namespace RecoveredNativeLoot {
COCKHERORECOVERED_API FRecoveredNativeLootReward Roll(const URecoveredNewerInventory& Inventory,const FRecoveredNativeLootContext& Context,float RollPercent);
COCKHERORECOVERED_API bool IsPanicBlocked(FName ItemID,double Heat,const TArray<FString>& Modifiers);
}
