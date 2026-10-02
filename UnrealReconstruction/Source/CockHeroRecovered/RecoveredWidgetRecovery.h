#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredWidgetRecovery.generated.h"

/** Editor reconstruction of verified cooked widget trees; does not restore event graphs. */
UCLASS()
class COCKHERORECOVERED_API URecoveredWidgetRecovery : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovery")
    static FString BuildWidgetAssets(const FString& EvidencePath);
    UFUNCTION(BlueprintCallable,Category="Recovery") static FString ProbeAnimationData(const FString& DecodedAssetPath);
    UFUNCTION(BlueprintCallable,Category="Recovery") static FString RestoreAnimationData(const FString& DecodedAssetPath,const FString& BlueprintPath);
};
