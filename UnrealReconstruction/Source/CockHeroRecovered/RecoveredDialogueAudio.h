#pragma once
#include "CoreMinimal.h"

class USoundBase;
COCKHERORECOVERED_API FString GetRecoveredCanonicalVoicePack(const FString& VoicePack);
COCKHERORECOVERED_API FString GetRecoveredDialoguePronoun(int32 Selection);
COCKHERORECOVERED_API USoundBase* SelectRecoveredSourceDialogue(const FString& VoicePack,const FString& Request,const FString& Pronoun=TEXT("Neutral"),FString* SelectedRow=nullptr);
COCKHERORECOVERED_API USoundBase* SelectRecoveredPaceDialogue(const FString& VoicePack,uint8 Pace,const TArray<FString>& Tags,const FString& Pronoun,bool bSPHEnabled,FString* SelectedRow=nullptr);
