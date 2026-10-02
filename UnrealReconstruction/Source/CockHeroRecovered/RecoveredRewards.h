#pragma once
#include "CoreMinimal.h"
#include "RecoveredRules.h"
#include "RecoveredRewards.generated.h"

UCLASS()
class COCKHERORECOVERED_API URecoveredRewardLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    // Native XP, unlock points and player cards. Pack requests need a store consumer.
    // Pack-store effects still require the store consumer.
    UFUNCTION(BlueprintCallable,Category="Recovered Rewards") static void GrantRecoveredRewards(URecoveredProgressionManager* Manager,const TArray<FRecoveredReward>& Rewards);
};
