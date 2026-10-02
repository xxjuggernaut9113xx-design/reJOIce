#pragma once
#include "CoreMinimal.h"
#include "RecoveredGameplay.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredOutcomes.generated.h"

/** Requests from the synchronous outcome entry point; external consumers are not simulated. */
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredOutcomeEffects {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) TArray<ERecoveredMetric> MetricRequests;
    UPROPERTY(BlueprintReadOnly) bool bClearEdgeHoldTimer=false;
    UPROPERTY(BlueprintReadOnly) int32 BackgroundStyle=0;
    UPROPERTY(BlueprintReadOnly) int32 OutcomeOverlaySourceIndex=0;
    UPROPERTY(BlueprintReadOnly) uint8 DialogueType=0;
    UPROPERTY(BlueprintReadOnly) bool bPlaySpecialEventDialogue=false;
    UPROPERTY(BlueprintReadOnly) float SpeedModifier=5;
    UPROPERTY(BlueprintReadOnly) int32 StrokeCountModifier=10;
    UPROPERTY(BlueprintReadOnly) bool bApplyIronManPenalty=false;
    UPROPERTY(BlueprintReadOnly) bool bPlayEarlyOutcomeAnimation=false;
    UPROPERTY(BlueprintReadOnly) bool bDelayedContinuationRequested=false;
    UPROPERTY(BlueprintReadOnly) float ContinuationDelay=0;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredOutcomeRequested,const FRecoveredOutcomeEffects&,Effects);

UCLASS()
class COCKHERORECOVERED_API URecoveredOutcomeLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable,Category="Recovered|Outcomes")
    static FRecoveredOutcomeEffects ApplyOutcome(UPARAM(ref) FRecoveredPlayerVariables& Player,UPARAM(ref) FRecoveredSessionStats& Stats,UPARAM(ref) uint8& CardType,bool bSuccessful,bool bHasTaunted,bool bIronManActive);
};
