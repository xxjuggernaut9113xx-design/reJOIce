#include "RecoveredProgression.h"
#include "RecoveredRules.h"

int32 URecoveredProgressionLibrary::CalculateSessionXP(const FRecoveredSessionStats& Stats,const FRecoveredXPSettings& Settings) {
    // Separate float operations preserve the recovered SSE arithmetic order.
    volatile float StrokeXP=static_cast<float>(Stats.Strokes)*Settings.XPPerStroke;
    volatile float Minutes=static_cast<float>(Stats.SessionDuration)*(1.0f/60.0f);
    volatile float DurationXP=Minutes*Settings.XPPerMinute;
    const int32 StrokePoints=FMath::Min(FMath::FloorToInt(static_cast<float>(StrokeXP)),Settings.StrokeXPCap);
    const int32 Enemies=URecoveredStateRuleLibrary::AddInt32Wrapping(Stats.EnemiesDefeated,Stats.SuccubiDefeated);
    const int32 EnemyPoints=FMath::Min(Enemies,Settings.EnemyXPCap);
    int32 Points=URecoveredStateRuleLibrary::AddInt32Wrapping(URecoveredStateRuleLibrary::AddInt32Wrapping(FMath::FloorToInt(static_cast<float>(DurationXP)),StrokePoints),EnemyPoints);
    volatile float EdgeXP=static_cast<float>(Stats.Edges)*Settings.XPPerEdge;
    volatile float WithEdges=static_cast<float>(Points)+EdgeXP;
    Points=FMath::TruncToInt(static_cast<float>(WithEdges));
    if(Stats.bWon) {
        volatile float WithWin=static_cast<float>(Points)+Settings.WinBonus;
        Points=FMath::TruncToInt(static_cast<float>(WithWin));
    }
    float Multiplier=1.0f;
    if(Stats.ActiveModifiers.ContainsByPredicate([](const FString& Tag){return Tag.Equals(TEXT("ironman"),ESearchCase::IgnoreCase);})) Multiplier=1.2f;
    if(Stats.ActiveModifiers.ContainsByPredicate([](const FString& Tag){return Tag.Equals(TEXT("hardcore"),ESearchCase::IgnoreCase);})) Multiplier+=0.15f;
    volatile float FinalXP=static_cast<float>(Points)*Multiplier;
    return FMath::FloorToInt(static_cast<float>(FinalXP));
}

int32 URecoveredProgressionLibrary::GetXPForNextLevel(int32 CurrentLevel) {
    // Original .rdata at 0x14cf77870; this function does not read the level data table.
    static constexpr int32 Requirements[]={100,120,145,175,210,250,300,360,430,515,620,750,910,1100,1330,1600,1920,2300,2750,3300};
    return CurrentLevel>0 && CurrentLevel<=20 ? Requirements[CurrentLevel-1] : 999999;
}

void URecoveredProgressionManager::AddUnlockPoints(int32 Amount) {
    UnlockPoints=URecoveredStateRuleLibrary::AddInt32Wrapping(UnlockPoints,Amount);
}

float URecoveredProgressionLibrary::CalculateLevelProgress(int32 CurrentXP,int32 CurrentLevel) {
    const int32 Required=GetXPForNextLevel(CurrentLevel);
    return Required>0 ? FMath::Clamp(float(CurrentXP)/float(Required),0.0f,1.0f) : 1.0f;
}

void URecoveredProgressionManager::AddXP(int32 Amount,const FString& Source) {
    if(Amount<=0) return;
    CurrentXP=URecoveredStateRuleLibrary::AddInt32Wrapping(CurrentXP,Amount);
    TotalXPEarned=URecoveredStateRuleLibrary::AddInt32Wrapping(TotalXPEarned,Amount);
    OnXPGained.Broadcast(Amount,Source);
    CheckLevelUp();
    OnMetricUpdateRequested.Broadcast(ERecoveredMetric::TotalXPEarned,Amount);
}

void URecoveredProgressionManager::CheckLevelUp() {
    if(CurrentLevel>=20) return;
    int32 Required=URecoveredProgressionLibrary::GetXPForNextLevel(CurrentLevel);
    while(CurrentXP>=Required && CurrentLevel<20) {
        CurrentXP=URecoveredStateRuleLibrary::AddInt32Wrapping(CurrentXP,-Required);
        CurrentLevel=URecoveredStateRuleLibrary::AddInt32Wrapping(CurrentLevel,1);
        if(LevelDataTable && LevelDataTable->GetRowStruct()==FRecoveredLevelRow::StaticStruct()) {
            const FName Name(*FString::Printf(TEXT("Level_%d"),CurrentLevel));
            if(const auto* Row=LevelDataTable->FindRow<FRecoveredLevelRow>(Name,TEXT("Recovered native level reward"),false)) {
                AddUnlockPoints(Row->UnlockPointsReward);
                OnLevelUp.Broadcast(CurrentLevel,Row->UnlockPointsReward,Row->ContentUnlocks);
            }
        }
        Required=URecoveredProgressionLibrary::GetXPForNextLevel(CurrentLevel);
    }
    OnProgressUpdate.Broadcast(URecoveredProgressionLibrary::CalculateLevelProgress(CurrentXP,CurrentLevel));
}
