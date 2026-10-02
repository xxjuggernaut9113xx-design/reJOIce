#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredEventWidgets.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredStoreWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite) double MaxTimeOpen=30;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) double RemainingTimeOpen=30;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) double TimeRatio=1;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly) bool bButtonPressEnabled=false;
    UFUNCTION(BlueprintCallable) void CloseStore();
    UFUNCTION(BlueprintCallable) void UpdateTimer();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    FTimerHandle MaxTimeHandler;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredBeatIconComplete);
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredBeatWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable) FRecoveredBeatIconComplete OnBeatIconAnimComplete;
    UFUNCTION() void SequenceEvent__ENTRYPOINTUMG_BeatIcon();
    UFUNCTION() void SequenceEvent__ENTRYPOINTUMG_BeatIcon_0();
    UFUNCTION() void SequenceEvent__ENTRYPOINTUMG_BeatIcon_1();
    UFUNCTION(BlueprintCallable) void BeatCompleteEvent();
protected:
    virtual void OnAnimationFinished_Implementation(const class UWidgetAnimation* Animation) override;
};

/** Animation callbacks recovered from source blocks containing only RemoveFromParent. */
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredAnimatedOverlay : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    static bool SupportsAsset(FName Name);
    UFUNCTION() void SequenceEvent__ENTRYPOINTAssFrenzyWidget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTBonerPillItemUseOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTBoobFrenzyWidget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTCumWindowClosedOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTCummingEarlyOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTCummingEarlySuccubus_Overlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTCummingOnTimeOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTDefeatEnemyOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTFillLootbarOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTNoShieldsLeft_OverlayWidget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTNormalEdgeOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTPerfectEdgeOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTPermissionToCumOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTPlusCumChanceOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTPunishmentSpawn_Overlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTResupplyItem_OverlayWidget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTShieldOff_OverlayWidget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTShieldOn_OverlayWidget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTSlowdownItemUseOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTStartEdgeStreakOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTSuccubusSpawnOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTTemptationAcceptOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTUnlockStorePackOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTUseDecreaseHeatOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTUseSuccubusTauntOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTUseTauntOverlay_Widget();
    UFUNCTION() void SequenceEvent__ENTRYPOINTonomatopoeia_Overlay_Widget();
protected:
    virtual void NativeConstruct() override;
};
