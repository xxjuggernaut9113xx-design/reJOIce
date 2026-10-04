#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "RecoveredGameplay.h"

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

FText URecoveredProgressionLibrary::GetLifetimeStatsText(const FRecoveredLifetimeStats& Stats) {
    // Mirrors native UProgressionManager::GetLifetimeStatsText: multi-line
    // summary of accumulated lifetime counters and peaks for the results screen.
    return FText::FromString(FString::Printf(
        TEXT("Sessions: %d (Won: %d)\nStrokes: %d | Edges: %d\nSuccubi: %d | Enemies: %d\nXP Earned: %d | Coins: %d\nBest Combo: %d | Best Edge Streak: %d\nLongest Session: %ds | Most Strokes: %d"),
        Stats.TotalSessionsCompleted, Stats.TotalSessionsWon,
        Stats.TotalStrokes, Stats.TotalEdges,
        Stats.TotalSuccubiDefeated, Stats.TotalEnemiesDefeated,
        Stats.TotalXPEarned, Stats.TotalCoinsEarned,
        Stats.BestCombo, Stats.BestEdgeStreak,
        Stats.LongestSessionSeconds, Stats.MostStrokesInSession));
}

FText URecoveredProgressionLibrary::GetRewardsText(const TArray<FRecoveredReward>& Rewards) {
    // Mirrors native UProgressionManager::GetRewardsText: lists granted rewards.
    if (Rewards.Num() == 0) return FText::FromString(TEXT("No rewards earned."));
    FString Out;
    for (const FRecoveredReward& R : Rewards) {
        if (!Out.IsEmpty()) Out += TEXT("\n");
        if (R.RewardType == TEXT("XP")) Out += FString::Printf(TEXT("+%d XP"), R.Value);
        else if (R.RewardType == TEXT("Coins")) Out += FString::Printf(TEXT("+%d Coins"), R.Value);
        else if (!R.ItemIdentifier.IsEmpty()) Out += FString::Printf(TEXT("%s x%d"), *R.ItemIdentifier, R.Value);
        else Out += FString::Printf(TEXT("%s: %d"), *R.RewardType, R.Value);
    }
    return FText::FromString(Out);
}

FText URecoveredProgressionLibrary::GetStatValueText(const FString& StatName, int32 SessionValue, int32 LifetimeValue, bool bUseLifetime) {
    // Mirrors native UProgressionManager::GetStatValueText: single stat line,
    // lifetime or session value based on the toggle.
    const int32 Value = bUseLifetime ? LifetimeValue : SessionValue;
    return FText::FromString(FString::Printf(TEXT("%s: %d"), *StatName, Value));
}

TArray<FRecoveredModifierRow> URecoveredProgressionManager::GetAllModifierData() const {
    TArray<FRecoveredModifierRow> Out;
    if (!ModifierDataTable) return Out;
    for (const auto& Pair : ModifierDataTable->GetRowMap()) {
        if (const FRecoveredModifierRow* Row = reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value)) {
            Out.Add(*Row);
        }
    }
    return Out;
}

bool URecoveredProgressionManager::GetModifierData(FName ModifierID, FRecoveredModifierRow& OutData) const {
    if (!ModifierDataTable) return false;
    if (const FRecoveredModifierRow* Row = ModifierDataTable->FindRow<FRecoveredModifierRow>(ModifierID, TEXT("GetModifierData"))) {
        OutData = *Row;
        return true;
    }
    return false;
}

bool URecoveredProgressionManager::IsModifierUnlocked(FName ModifierID) const {
    return UnlockedModifiers.Contains(ModifierID);
}

bool URecoveredProgressionManager::CanEnableModifier(FName ModifierID) const {
    // Native checks unlock state and conflicts; conflict data is not in the
    // recovered modifier table schema, so only the unlock gate is enforced here.
    return IsModifierUnlocked(ModifierID);
}

TArray<FName> URecoveredProgressionManager::GetUnlockedModifiers() const {
    return UnlockedModifiers.Array();
}

TArray<FName> URecoveredProgressionManager::GetConflictingModifiers(FName ModifierID) const {
    // Conflict pairs are not present in the recovered modifier table schema
    // (Title/Description/Icon only); returning empty until native data is available.
    return TArray<FName>();
}

FName URecoveredProgressionManager::GetChallengeForModifier(FName ModifierID) const {
    // Challenge linkage is not present in the recovered modifier table schema;
    // returning NAME_None until native data is available.
    return NAME_None;
}
