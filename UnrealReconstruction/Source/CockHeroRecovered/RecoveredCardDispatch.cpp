#include "RecoveredRules.h"
#include "RecoveredEventRules.h"
#include "Kismet/KismetMathLibrary.h"

void ARecoveredGlobalManager::HandleRecoveredSessionAction(FName Action) {
    if (Action==TEXT("DetermineCardV2")) RequestNextRecoveredCard(true);
    else if (Action==TEXT("SuccubusCardStarted")) SpawnRecoveredOverlay(TEXT("SuccubusSpawnOverlay_Widget"));
    else if (Action==TEXT("PermissionCardStarted")) SpawnRecoveredOverlay(TEXT("PermissionToCumOverlay_Widget"));
    else if (Action==TEXT("FrenzyCardStarted")) SpawnRecoveredOverlay(BeatContext.CardType==7 ? TEXT("AssFrenzyWidget") : TEXT("BoobFrenzyWidget"));
}
bool ARecoveredGlobalManager::RequestNextRecoveredCard(bool bPlayMedia) {
    LastDispatchedEvent=NAME_None;
    if (!Rules || !MediaDeckState) { LastSessionError=TEXT("Recovered draw rules or media decks are unavailable"); return false; }
    if (PlayerVariables.bHasCame) {
        OnSessionAction.Broadcast(TEXT("ClearNotificationBoxes"));OnSessionAction.Broadcast(TEXT("HideEdgeStreakCounter"));
        LastDispatchedEvent=TEXT("CumOverride");return DrawRecoveredSpecialCard(LastDispatchedEvent,bPlayMedia);
    }
    if (!PrepareDrawState()) return false;
    if (PlayerVariables.bHasEdged || PlayerVariables.bIsAllowedToCum) {
        LastDispatchedEvent=PlayerVariables.bHasEdged ? TEXT("EdgingEventV2") : TEXT("CumEventOverride");
        return DrawRecoveredSpecialCard(LastDispatchedEvent,bPlayMedia);
    }
    FRecoveredEligibilityState State;
    State.HeatCategory=BeatContext.HeatCategory;
    State.Combo=PlayerVariables.CurrentComboCount;
    State.Coins=PlayerVariables.PlayerCoins;
    State.bCanSuccubiSpawn=PlayerVariables.bCanSuccubiSpawn;
    State.bBrainMelterEnabled=bBrainMelterEnabled;
    State.bStoreOnCooldown=bStoreOnCooldown;
    State.Shields=SuccubusShields; State.bShieldToggled=bShieldToggled;
    State.Modifiers=BeatContext.ActiveModifiers;
    const auto Eligible=URecoveredEventRuleLibrary::BuildEligibleEvents(Rules->EventRecords,State);
    SuccubusShields=State.Shields; bShieldToggled=State.bShieldToggled;
    const auto Weighted=URecoveredEventRuleLibrary::ApplyDrawEventWeights(Eligible,State.HeatCategory,CurrentComboTypeEnum);
    const double Total=URecoveredEventRuleLibrary::GetTotalWeight(Weighted);
    const int32 Index=URecoveredEventRuleLibrary::ChooseEventAtRoll(Weighted,UKismetMathLibrary::RandomFloatInRange(0,Total));
    // The source retains its instance FoundEvent when no weight exceeds the roll.
    if (Weighted.IsValidIndex(Index)) FoundEvent=Weighted[Index];
    bool bClearIdle=false;
    LastDispatchedEvent=URecoveredEventRuleLibrary::DetermineDispatchedEvent(static_cast<uint8>(FoundEvent.EventName),State.Modifiers.Contains(TEXT("Succufrenzy")),State.Modifiers.Contains(TEXT("Slow and Steady")),State.Modifiers.Contains(TEXT("Double Time")),UKismetMathLibrary::RandomIntegerInRange(0,1),bClearIdle);
    if (bClearIdle) OnSessionAction.Broadcast(TEXT("ClearIdleTimer"));
    if (LastDispatchedEvent==TEXT("SpawnStoreEvent")) return SpawnRecoveredStore();
    uint8 Pace=255;
    if (LastDispatchedEvent==TEXT("SlowStrokeEvent")) Pace=0;
    else if (LastDispatchedEvent==TEXT("MediumStrokeEvent")) Pace=1;
    else if (LastDispatchedEvent==TEXT("FastStrokeEvent")) Pace=2;
    if (Pace==255) {
        if (!DrawRecoveredSpecialCard(LastDispatchedEvent,bPlayMedia)) return false;
    } else if (!StartPaceCard(Pace,bPlayMedia,false)) return false;
    PlayerVariables.bCanDraw=true;
    OnSessionAction.Broadcast(TEXT("ToggleEdgeStreakCounterVisibilityFalse"));
    OnSessionAction.Broadcast(TEXT("DetermineAndSpawnTaskModifier"));
    return true;
}
