#pragma once

#include "CoreMinimal.h"
#include "RecoveredNewerInventory.h"

class ARecoveredGlobalManager;
class URecoveredSaveGame;

namespace RecoveredNewerInventoryAdapter {
COCKHERORECOVERED_API bool ResolveType(FName ItemID, ERecoveredShopItemType& Type);
COCKHERORECOVERED_API FName ResolveID(ERecoveredShopItemType Type);
COCKHERORECOVERED_API URecoveredNewerInventory* GetInventory(const ARecoveredGlobalManager& Manager);
COCKHERORECOVERED_API void SynchronizeConsumed(ARecoveredGlobalManager& Manager, FName ItemID);
COCKHERORECOVERED_API void Persist(ARecoveredGlobalManager& Manager);
COCKHERORECOVERED_API void Initialize(ARecoveredGlobalManager& Manager);
COCKHERORECOVERED_API bool GetPricing(FName ItemID,int32 Level,int32& Buy,int32& Upgrade);
COCKHERORECOVERED_API bool GetPresentation(FName ItemID,int32 Level,FString& Title,FString& Description);
COCKHERORECOVERED_API void ResetItemStates(URecoveredNewerInventory& Inventory);
COCKHERORECOVERED_API void PopulateOwnedItemsFromHotbar(URecoveredNewerInventory& Inventory);
COCKHERORECOVERED_API TMap<ERecoveredShopItemType,FRecoveredNewerItemState> MakeNativeTowerInventory(const URecoveredNewerInventory& Inventory);
COCKHERORECOVERED_API void ResetForFreshRun(ARecoveredGlobalManager& Manager);
COCKHERORECOVERED_API void SetupMusicHotbar(URecoveredNewerInventory& Inventory);
COCKHERORECOVERED_API void PrepareFreshLoadout(URecoveredNewerInventory& Inventory, uint8 Mode, FRandomStream& Random);
COCKHERORECOVERED_API void RestoreClassicHotbar(URecoveredNewerInventory& Inventory, const URecoveredSaveGame* Save);
COCKHERORECOVERED_API bool SaveClassicHotbar(const URecoveredNewerInventory& Inventory, URecoveredSaveGame* Save);
}
