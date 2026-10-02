#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredAudioRecovery.generated.h"
UCLASS()
class COCKHERORECOVERED_API URecoveredAudioRecovery : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable,Category="Recovery") static FString DecodeBinkAudio(const FString& EncodedFile,const FString& AssetName);
};
