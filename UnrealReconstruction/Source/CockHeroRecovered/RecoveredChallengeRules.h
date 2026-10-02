#pragma once
#include "CoreMinimal.h"
#include "RecoveredRules.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredChallengeRules.generated.h"

/** Reconstructed native requirement and condition predicates; tracking/rewards remain separate. */
UCLASS()
class COCKHERORECOVERED_API URecoveredChallengeRules : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure,Category="Recovered|Challenges") static bool AreAllRequirementsMet(const TArray<FRecoveredRequirement>& Requirements);
    UFUNCTION(BlueprintPure,Category="Recovered|Challenges") static bool CheckChallengeConditions(const TArray<FRecoveredCondition>& Conditions,const TArray<FString>& ActiveModifiers,int32 ItemsUsed,int32 SessionDuration);
    UFUNCTION(BlueprintPure,Category="Recovered|Challenges") static float GetRequirementProgressPercent(const FRecoveredRequirement& Requirement);
};
