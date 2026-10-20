#pragma once
#include "CoreMinimal.h"
class URecoveredSaveGame;

namespace RecoveredMusicUpgrades {
// Native music upgrade types0 duration,1 max charges,2 recharge strokes.
// Persistence keys belong to recovery profiles; original-save loading is separate.
COCKHERORECOVERED_API int32 GetLevel(const URecoveredSaveGame* Save, uint8 Type);
COCKHERORECOVERED_API double GetValue(const URecoveredSaveGame* Save, uint8 Type);
COCKHERORECOVERED_API bool SetLevel(URecoveredSaveGame* Save, uint8 Type, int32 Level);
}
