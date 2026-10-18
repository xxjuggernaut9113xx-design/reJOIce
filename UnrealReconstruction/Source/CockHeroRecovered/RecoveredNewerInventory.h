#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RecoveredNewerInventory.generated.h"

// Values from newer-20261017/native-reflection-enums.json: EShopItemType.
UENUM(BlueprintType)
enum class ERecoveredShopItemType : uint8 {
    IncreaseCumMeter = 0,
    DecreaseHeat = 1,
    Edge = 2,
    Slowdown = 3,
    Break = 4,
    BonerPill = 5,
    SuccuShield = 6,
    Resupply = 7,
    None = 8,
    ApexLure = 9,
    EscapeRope = 10,
    LootRush = 11,
    Bounty = 12,
    ComboCruncher = 13
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredNewerItemState {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") bool bIsUnlocked = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") int32 Level = 1;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") int32 Charges = 0;
};

// External results required by BP_CHGameInstance.GetMaxCharges. No manager/world dependency.
USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredNewerChargeContext {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") uint8 GameModeSelection = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") bool bGlobalManagerValid = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") int32 EffectiveMaxBreakCharges = 0;
    // ESuccuShopModifier::BiggerPockets = 13.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") bool bBiggerPockets = false;
};

// Source: newer-20261017/functions/BP_CHGameInstance. Pure domain transitions only:
// no saves, old inventory adapters, currency, item effects or widget/animation calls.
UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredNewerInventory : public UObject {
    GENERATED_BODY()
public:
    FString ExportRecoveryState() const;
    bool ImportRecoveryState(const FString& Json);
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") TMap<ERecoveredShopItemType, FRecoveredNewerItemState> OwnedItems;
    // Initial loadout size/defaults belong to the integration layer, not these functions.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered|Newer Inventory") TArray<ERecoveredShopItemType> HotbarItems;

    UFUNCTION(BlueprintPure, Category="Recovered|Newer Inventory") FRecoveredNewerItemState GetItemState(ERecoveredShopItemType ItemType) const;
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") bool UnlockItem(ERecoveredShopItemType ItemType);
    // Return reports mutation. SourceSuccess preserves the Blueprint output, which is
    // NOT assigned on successful mutation when its hotbar widget is invalid (offset658).
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") bool UpgradeItem(ERecoveredShopItemType ItemType, bool bHotbarWidgetValid, UPARAM(ref) bool& SourceSuccess);
    // Returns whether MaxCount was written. Edge/None/unknown values and mode2 Break
    // without a valid global manager leave the caller's previous output untouched.
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") static bool GetMaxCharges(ERecoveredShopItemType ItemType, const FRecoveredNewerChargeContext& Context, UPARAM(ref) int32& MaxCount);
    // Source checks the previous count only: no clamp and no positive-count guard.
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") bool GrantItem(ERecoveredShopItemType ItemType, int32 Count, const FRecoveredNewerChargeContext& Context);
    // Returns whether the destination was written. Source clears duplicates before
    // Array_Set validates SlotIndex; even a negative index can therefore clear them.
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") bool EquipToSlot(ERecoveredShopItemType ItemType, int32 SlotIndex);
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") bool UnEquipSlot(int32 SlotIndex);
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") void ResetHotbar();
    UFUNCTION(BlueprintCallable, Category="Recovered|Newer Inventory") void SetRhythmModeHotbar();
};
