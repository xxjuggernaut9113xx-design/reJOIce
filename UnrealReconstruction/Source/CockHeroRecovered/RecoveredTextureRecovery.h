#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredTextureRecovery.generated.h"
UCLASS()
class COCKHERORECOVERED_API URecoveredTextureRecovery : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    /** Read a recovered cooked texture through UE's matching serializer; export its top mip only. */
    UFUNCTION(BlueprintCallable,Category="Recovery") static FString ExportCookedMip(const FString& ContentDirectory,const FString& RelativeAssetPath);
    UFUNCTION(BlueprintCallable,Category="Recovery") static FString RecoverHorizonFont(const FString& EvidenceFile,const FString& PayloadFile);
};
