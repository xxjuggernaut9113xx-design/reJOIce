#pragma once
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RecoveredNewerItemEffects.generated.h"

UCLASS()
class COCKHERORECOVERED_API URecoveredNewerItemEffects : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() double LootRushRemaining=0;
    UPROPERTY() double LootRushBonus=0;
    UPROPERTY() double BountyRemaining=0;
    UPROPERTY() int32 BountyRequiredStrokes=0;
    UPROPERTY() int32 BountyStartStrokes=0;
    UPROPERTY() int32 BountyLevel=1;
    void StartLootRush(int32 Level);
    void StartBounty(int32 Level,int32 CurrentStrokes,FRandomStream& Random);
    bool AdvanceLootRush(double Seconds);
    int32 AdvanceBounty(double Seconds,int32 CurrentStrokes);
};
