#include "RecoveredRules.h"
#include "Kismet/KismetMathLibrary.h"

bool ARecoveredGlobalManager::DrawRecoveredSpecialCard(FName Event,bool bPlayMedia) {
    LastSessionError.Reset();
    if (!Rules || !MediaDeckState || !BeatTimeline) { LastSessionError=TEXT("Special card requires recovered rules and media decks");return false; }
    uint8 Deck=255,CardType=255;
    int32 MinStrokes=0,MaxStrokes=0;
    double MinInterval=0,MaxInterval=0,CountMultiplier=StrokeCountMultiplier,TimeMultiplier=StrokeTimeMultiplier,Travel=BeatTravelTime;
    const TArray<FRecoveredBeatPattern>* Patterns=nullptr;
    if (Event==TEXT("SpawnSuccubus")) {
        Deck=3;CardType=3;MinStrokes=30;MaxStrokes=50;MinInterval=.15;MaxInterval=.33;TimeMultiplier=1;Travel=1.5;
        if (BeatContext.ActiveModifiers.Contains(TEXT("Hivemind"))) CountMultiplier+=.4*SessionStats.SuccubiDefeated;
        Patterns=&Rules->SuccubusBeatPatterns;
    } else if (Event==TEXT("AssFrenzyEvent") || Event==TEXT("BoobFrenzyEvent")) {
        const auto* Row=HeatCategoryDataTable ? HeatCategoryDataTable->FindRow<FRecoveredHeatCategoryRow>(TEXT("HighHeat"),TEXT("Recovered frenzy")) : nullptr;
        if (!Row) { LastSessionError=TEXT("Frenzy timing row is unavailable");return false; }
        Deck=Event==TEXT("AssFrenzyEvent") ? 5 : 6;CardType=Deck==5 ? 7 : 8;
        MinStrokes=Row->MinStrokeCount;MaxStrokes=Row->MaxStrokeCount;MinInterval=.15;MaxInterval=Row->MaxIntervalSeconds;
        Patterns=&Rules->FrenzyBeatPatterns;
    } else if (Event==TEXT("EdgingEventV2")) {
        PlayerVariables.bHasEdged=false;PlayerVariables.bCanUseItems=false;
        EdgeStrokeMultiplier+=UKismetMathLibrary::RandomFloatInRange(.1,.25);
        LastEdgeInterval=FMath::Clamp(LastEdgeInterval-UKismetMathLibrary::RandomFloatInRange(.01,.02)*EdgePacingMultiplier,.15,1.0);
        const double IntervalRoll=UKismetMathLibrary::RandomFloatInRange(.8,1.25);
        const double CountRoll=UKismetMathLibrary::RandomFloatInRange(.8,1.25);
        const int32 BaseCount=FMath::TruncToInt(LastEdgeStrokeCount*EdgeStrokeMultiplier);
        Deck=2;CardType=5;MaxStrokes=FMath::Clamp(BaseCount,15,60);MinStrokes=FMath::Clamp(FMath::TruncToInt(BaseCount*double(CountRoll)),15,60);
        MaxInterval=LastEdgeInterval;MinInterval=LastEdgeInterval*IntervalRoll;CountMultiplier=TimeMultiplier=1;
        Patterns=&Rules->MediumBeatPatterns;bPlayerEdgedLastDraw=true;
    } else if (Event==TEXT("CumEventOverride") || Event==TEXT("CumOverride")) {
        Deck=4;CardType=6;Travel=1.5;Patterns=&Rules->FastBeatPatterns;
        MinStrokes=Event==TEXT("CumEventOverride")?75:25;MaxStrokes=Event==TEXT("CumEventOverride")?100:50;
        MinInterval=.28;MaxInterval=Event==TEXT("CumEventOverride")?.35:.30;
    } else if (Event==TEXT("PostEdgeSlowEvent") || Event==TEXT("PostEdgeFastEvent")) {
        const bool Fast=Event==TEXT("PostEdgeFastEvent");
        const auto* Row=HeatCategoryDataTable?HeatCategoryDataTable->FindRow<FRecoveredHeatCategoryRow>(Fast?TEXT("HighHeat"):TEXT("SlowHeat"),TEXT("Recovered post-edge")):nullptr;
        if (!Row) { LastSessionError=TEXT("Post-edge timing row unavailable");return false; }
        Deck=Fast?2:0;CardType=4;MinStrokes=Row->MinStrokeCount;MaxStrokes=Row->MaxStrokeCount;MinInterval=Row->MinIntervalSeconds;MaxInterval=Row->MaxIntervalSeconds;
        TimeMultiplier=Fast?.75:1;CountMultiplier=Fast?1.5:StrokeCountMultiplier;
        Patterns=Fast?&Rules->FastBeatPatterns:&Rules->SlowBeatPatterns;bPlayerEdgedLastDraw=false;
    } else { LastSessionError=TEXT("Unknown recovered special card: ")+Event.ToString();return false; }
    if (!Patterns || Patterns->IsEmpty()) { LastSessionError=TEXT("Special card pattern bank is empty");return false; }
    MediaDeckState->ReplaceEmptyDecks();
    if (!MediaDeckState->Draw(Deck,false,SelectedRandomCard)) { LastSessionError=TEXT("Special card media deck is empty");return false; }
    if (bPlayMedia && MediaPlayback) MediaPlayback->OpenEntry(SelectedRandomCard);
    const auto Timing=URecoveredCardRuleLibrary::CalculateCardTiming(UKismetMathLibrary::RandomIntegerInRange(MinStrokes,MaxStrokes),UKismetMathLibrary::RandomFloatInRange(MinInterval,MaxInterval),CountMultiplier,UserStrokeCountMultiplier,TimeMultiplier);
    PlayerVariables.BeatSpawnInterval=Timing.BeatInterval;
    const auto Pattern=URecoveredSessionRuleLibrary::CheckIntervalMultipliers((*Patterns)[UKismetMathLibrary::RandomIntegerInRange(0,Patterns->Num()-1)],BeatTimeline->GetCurrentInterval());
    if (!StartRecoveredBeatSequence(Pattern,Timing.BeatInterval,Timing.StrokeCount,1.0f,Travel)) { LastSessionError=TEXT("Special card timing was rejected");return false; }
    BeatContext.CardType=CardType;
    if (CardType==3) PlayerVariables.bCanUseItems=false;
    if (CardType==3) OnSessionAction.Broadcast(TEXT("SuccubusCardStarted"));
    else if (CardType==7 || CardType==8) OnSessionAction.Broadcast(TEXT("FrenzyCardStarted"));
    else if (CardType==5) OnSessionAction.Broadcast(TEXT("EdgeCardStarted"));
    else if (CardType==6) OnSessionAction.Broadcast(Event==TEXT("CumEventOverride")?TEXT("PermissionCardStarted"):TEXT("OutcomeOverrideCardStarted"));
    else OnSessionAction.Broadcast(TEXT("PostEdgeCardStarted"));
    return true;
}
