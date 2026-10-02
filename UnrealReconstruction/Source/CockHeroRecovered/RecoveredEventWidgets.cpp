#include "RecoveredEventWidgets.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void URecoveredStoreWidget::NativeConstruct() {
    Super::NativeConstruct();bButtonPressEnabled=true;RemainingTimeOpen=MaxTimeOpen;
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("Close")))) Button->OnClicked.AddUniqueDynamic(this,&URecoveredStoreWidget::CloseStore);
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager) { Manager->bStopSequence=true;Manager->PlayerVariables.bHasItems=false;Manager->PlayerVariables.bCanDraw=false; }
    if (GetWorld()) GetWorld()->GetTimerManager().SetTimer(MaxTimeHandler,this,&URecoveredStoreWidget::UpdateTimer,.05f,true);
}
void URecoveredStoreWidget::NativeDestruct() {
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(MaxTimeHandler);
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("Close")))) Button->OnClicked.RemoveDynamic(this,&URecoveredStoreWidget::CloseStore);
    Super::NativeDestruct();
}
void URecoveredStoreWidget::CloseStore() {
    if (!bButtonPressEnabled) return;
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager) Manager->RequestNextRecoveredCard(true);
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(MaxTimeHandler);
    bButtonPressEnabled=false;RemoveFromParent();
}
void URecoveredStoreWidget::UpdateTimer() {
    if (RemainingTimeOpen<=0) { CloseStore();return; }
    RemainingTimeOpen-=.05;TimeRatio=MaxTimeOpen==0 ? 0 : RemainingTimeOpen/MaxTimeOpen;
    if (auto* Bar=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_168")))) Bar->SetPercent(static_cast<float>(TimeRatio));
}

void URecoveredBeatWidget::SequenceEvent__ENTRYPOINTUMG_BeatIcon() { BeatCompleteEvent(); }
void URecoveredBeatWidget::SequenceEvent__ENTRYPOINTUMG_BeatIcon_0() { BeatCompleteEvent(); }
void URecoveredBeatWidget::SequenceEvent__ENTRYPOINTUMG_BeatIcon_1() { BeatCompleteEvent(); }
void URecoveredBeatWidget::BeatCompleteEvent() { OnBeatIconAnimComplete.Broadcast(); }
void URecoveredBeatWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) {
    Super::OnAnimationFinished_Implementation(Animation);
    // Gameplay counting is owned by the native timeline's center-hit delegate.
    RemoveFromParent();
}

bool URecoveredAnimatedOverlay::SupportsAsset(FName Name) {
    static const TSet<FName> Names={TEXT("AssFrenzyWidget"),TEXT("BonerPillItemUseOverlay_Widget"),TEXT("BoobFrenzyWidget"),TEXT("CummingEarlyOverlay_Widget"),TEXT("CummingEarlySuccubus_Overlay_Widget"),TEXT("CummingOnTimeOverlay_Widget"),TEXT("CumWindowClosedOverlay_Widget"),TEXT("DefeatEnemyOverlay_Widget"),TEXT("FillLootbarOverlay_Widget"),TEXT("NormalEdgeOverlay_Widget"),TEXT("NoShieldsLeft_OverlayWidget"),TEXT("onomatopoeia_Overlay_Widget"),TEXT("PerfectEdgeOverlay_Widget"),TEXT("PermissionToCumOverlay_Widget"),TEXT("PlusCumChanceOverlay_Widget"),TEXT("PunishmentSpawn_Overlay_Widget"),TEXT("ResupplyItem_OverlayWidget"),TEXT("ShieldOff_OverlayWidget"),TEXT("ShieldOn_OverlayWidget"),TEXT("SlowdownItemUseOverlay_Widget"),TEXT("StartEdgeStreakOverlay_Widget"),TEXT("SuccubusSpawnOverlay_Widget"),TEXT("TemptationAcceptOverlay_Widget"),TEXT("UnlockStorePackOverlay_Widget"),TEXT("UseDecreaseHeatOverlay_Widget"),TEXT("UseSuccubusTauntOverlay_Widget"),TEXT("UseTauntOverlay_Widget")};return Names.Contains(Name);
}
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTAssFrenzyWidget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTBonerPillItemUseOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTBoobFrenzyWidget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTCumWindowClosedOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTCummingEarlyOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTCummingEarlySuccubus_Overlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTCummingOnTimeOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTDefeatEnemyOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTFillLootbarOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTNoShieldsLeft_OverlayWidget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTNormalEdgeOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTPerfectEdgeOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTPermissionToCumOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTPlusCumChanceOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTPunishmentSpawn_Overlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTResupplyItem_OverlayWidget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTShieldOff_OverlayWidget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTShieldOn_OverlayWidget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTSlowdownItemUseOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTStartEdgeStreakOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTSuccubusSpawnOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTTemptationAcceptOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTUnlockStorePackOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTUseDecreaseHeatOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTUseSuccubusTauntOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTUseTauntOverlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::SequenceEvent__ENTRYPOINTonomatopoeia_Overlay_Widget() { RemoveFromParent(); }
void URecoveredAnimatedOverlay::NativeConstruct() {
    Super::NativeConstruct();
    if (GetWorld()) PlayRecoveredAnimation(GetClass()->GetName()==TEXT("onomatopoeia_Overlay_Widget_C")?TEXT("Spawn"):TEXT("SpawnOverlay"));
}
