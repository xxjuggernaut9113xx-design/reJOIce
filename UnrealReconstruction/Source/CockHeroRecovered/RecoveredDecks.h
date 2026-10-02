#pragma once
#include "CoreMinimal.h"
#include "RecoveredMedia.h"
#include "RecoveredDecks.generated.h"

UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredDeckState : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FRecoveredMediaDecks Master;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FRecoveredMediaDecks Child;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FRecoveredMediaDecks MasterFavorites;
    UPROPERTY(EditAnywhere, BlueprintReadWrite) FRecoveredMediaDecks ChildFavorites;
    UFUNCTION(BlueprintCallable, Category="Recovered|Decks") void SetChildDecks();
    UFUNCTION(BlueprintCallable, Category="Recovered|Decks") void ReplaceEmptyDecks();
    UFUNCTION(BlueprintCallable, Category="Recovered|Decks") bool Draw(uint8 Deck, bool bFavorite, FRecoveredMediaEntry& Entry);
    // Deterministic selection hook for validating native Array_RemoveItem semantics.
    static bool DrawAtIndex(TArray<FRecoveredMediaEntry>& Deck, int32 Index, FRecoveredMediaEntry& Entry);
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredCardTiming {
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly) int32 StrokeCount=0;
    UPROPERTY(BlueprintReadOnly) double BeatInterval=0;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredCardRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Cards") static FRecoveredCardTiming CalculateCardTiming(int32 RolledStrokes, double RolledInterval, double CountMultiplier, double UserCountMultiplier, double TimeMultiplier);
};
