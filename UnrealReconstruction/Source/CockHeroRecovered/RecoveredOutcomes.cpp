#include "RecoveredOutcomes.h"

FRecoveredOutcomeEffects URecoveredOutcomeLibrary::ApplyOutcome(FRecoveredPlayerVariables& Player,FRecoveredSessionStats& Stats,uint8& CardType,bool bSuccessful,bool bHasTaunted,bool bIronManActive) {
    FRecoveredOutcomeEffects Effects;
    const uint8 PreviousCard=CardType;
    if(bSuccessful) Effects.MetricRequests.Add(ERecoveredMetric::SessionsWon);
    else {
        Effects.MetricRequests.Add(ERecoveredMetric::TimesLost);
        Effects.MetricRequests.Add(ERecoveredMetric::EarlyClimax);
        if(bHasTaunted) Effects.MetricRequests.Add(ERecoveredMetric::CameDuringTaunt);
        if(PreviousCard==3) Effects.MetricRequests.Add(ERecoveredMetric::LostToSuccubus);
    }
    for(const auto Metric:Effects.MetricRequests) URecoveredStateRuleLibrary::RecordSessionMetric(Stats,Metric,1);
    Player.BrokenComboArray.Add(Player.CurrentComboCount);
    Player.EdgeStreak=0; Player.CurrentComboCount=0; Player.bHasCame=true; Player.bCanDraw=true; Player.bCanUseItems=false;
    CardType=6;
    Effects.bClearEdgeHoldTimer=!bSuccessful;
    Effects.BackgroundStyle=bSuccessful ? 5 : 4;
    Effects.OutcomeOverlaySourceIndex=bSuccessful ? -4047 : (PreviousCard==3 ? -4046 : -4045);
    Effects.DialogueType=bSuccessful ? 3 : (PreviousCard==3 ? 6 : (PreviousCard==5 ? 10 : 2));
    Effects.bPlaySpecialEventDialogue=!bSuccessful && PreviousCard==5;
    Effects.bApplyIronManPenalty=!bSuccessful && bIronManActive;
    Effects.bPlayEarlyOutcomeAnimation=!bSuccessful;
    Effects.bDelayedContinuationRequested=bSuccessful;
    Effects.ContinuationDelay=bSuccessful ? 10.0f : 0.0f;
    // bWon is filled by the later stats-building flow, not these source entry points.
    return Effects;
}
