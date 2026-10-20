#pragma once
#include "CoreMinimal.h"
#include "RecoveredGameplay.h"

class URecoveredSaveGame;
struct COCKHERORECOVERED_API FRecoveredObjectiveSpec {
    uint8 Objective;
    const TCHAR* Title;
    const TCHAR* SaveKey;
    int32 DefaultTarget;
    int32 SliderStep;
};
struct COCKHERORECOVERED_API FRecoveredObjectiveRuntime {
    bool bActive = false;
    uint8 Objective = 0;
    int32 Target = 1;
    int32 BaselineDuration = 0;
    int32 BaselineStrokes = 0;
    int32 BaselineEdges = 0;
    int32 BaselineSuccubi = 0;
    int32 BaselineMilking = 0;
};
namespace RecoveredObjectives {
COCKHERORECOVERED_API const TArray<FRecoveredObjectiveSpec>& GetSpecs();
COCKHERORECOVERED_API int32 GetSelectedIndex(const URecoveredSaveGame* Save);
COCKHERORECOVERED_API int32 GetSavedTarget(const URecoveredSaveGame* Save, int32 Index);
COCKHERORECOVERED_API bool IsComplete(const FRecoveredObjectiveRuntime& Runtime, const FRecoveredPlayerVariables& Player, const FRecoveredSessionStats& Stats, double Meter);
COCKHERORECOVERED_API bool IsPrejacExpired(const FRecoveredObjectiveRuntime& Runtime, const FRecoveredPlayerVariables& Player);
// True means the source objective resets and play continues; false reaches EndSession.
COCKHERORECOVERED_API bool ResetAfterMiss(FRecoveredObjectiveRuntime& Runtime, bool ResetSetting, double& Meter);
}
