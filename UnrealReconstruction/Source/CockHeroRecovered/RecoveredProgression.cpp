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

FText URecoveredProgressionLibrary::GetRewardsText(const FRecoveredSessionRewardData& RewardData) {
    // Mirrors native UProgressionManager::GetRewardsText (0x1481c26e0): builds
    // the reward list text from the session reward bundle.
    FString Out;
    if (RewardData.XPGranted > 0) Out += FString::Printf(TEXT("+%d XP"), RewardData.XPGranted);
    for (const FRecoveredReward& R : RewardData.Rewards) {
        if (R.RewardType == TEXT("XP") && RewardData.XPGranted > 0) continue;
        if (!Out.IsEmpty()) Out += TEXT("\n");
        if (R.RewardType == TEXT("XP")) Out += FString::Printf(TEXT("+%d XP"), R.Value);
        else if (R.RewardType == TEXT("Coins")) Out += FString::Printf(TEXT("+%d Coins"), R.Value);
        else if (!R.ItemIdentifier.IsEmpty()) Out += FString::Printf(TEXT("%s x%d"), *R.ItemIdentifier, R.Value);
        else Out += FString::Printf(TEXT("%s: %d"), *R.RewardType, R.Value);
    }
    if (Out.IsEmpty()) return FText::FromString(TEXT("No rewards earned."));
    return FText::FromString(Out);
}

static int32 GetMetricSessionValue(ERecoveredMetric Metric, const FRecoveredSessionStats& S) {
    switch (Metric) {
        case ERecoveredMetric::Strokes: return S.Strokes;
        case ERecoveredMetric::Edges: return S.Edges;
        case ERecoveredMetric::SuccubiDefeated: return S.SuccubiDefeated;
        case ERecoveredMetric::EnemiesDefeated: return S.EnemiesDefeated;
        case ERecoveredMetric::MaxCombo: return S.MaxCombo;
        case ERecoveredMetric::MissedCumWindows: return S.MissedCumWindows;
        case ERecoveredMetric::TimesTaunted: return S.TimesTaunted;
        case ERecoveredMetric::ItemsUsed: return S.ItemsUsed;
        case ERecoveredMetric::DrawsAtMaxHeat: return S.DrawsAtMaxHeat;
        case ERecoveredMetric::EarlyClimax: return S.EarlyClimax;
        case ERecoveredMetric::SessionDuration: return S.SessionDuration;
        case ERecoveredMetric::SessionsCompleted: return S.SessionsCompleted;
        case ERecoveredMetric::SessionsWon: return S.SessionsWon;
        case ERecoveredMetric::EdgeStreak: return S.EdgeStreak;
        default: return 0;
    }
}

static int32 GetMetricLifetimeValue(ERecoveredMetric Metric, const FRecoveredLifetimeStats& L) {
    switch (Metric) {
        case ERecoveredMetric::Strokes: return L.TotalStrokes;
        case ERecoveredMetric::Edges: return L.TotalEdges;
        case ERecoveredMetric::SuccubiDefeated: return L.TotalSuccubiDefeated;
        case ERecoveredMetric::EnemiesDefeated: return L.TotalEnemiesDefeated;
        case ERecoveredMetric::MaxCombo: return L.BestCombo;
        case ERecoveredMetric::SessionDuration: return L.LongestSessionSeconds;
        case ERecoveredMetric::SessionsCompleted: return L.TotalSessionsCompleted;
        case ERecoveredMetric::SessionsWon: return L.TotalSessionsWon;
        case ERecoveredMetric::TotalXPEarned: return L.TotalXPEarned;
        case ERecoveredMetric::EdgeStreak: return L.BestEdgeStreak;
        default: return 0;
    }
}

static const TCHAR* GetMetricDisplayName(ERecoveredMetric Metric) {
    switch (Metric) {
        case ERecoveredMetric::Strokes: return TEXT("Strokes");
        case ERecoveredMetric::Edges: return TEXT("Edges");
        case ERecoveredMetric::SuccubiDefeated: return TEXT("Succubi Defeated");
        case ERecoveredMetric::EnemiesDefeated: return TEXT("Enemies Defeated");
        case ERecoveredMetric::MaxCombo: return TEXT("Best Combo");
        case ERecoveredMetric::MissedCumWindows: return TEXT("Missed Cum Windows");
        case ERecoveredMetric::TimesTaunted: return TEXT("Taunts");
        case ERecoveredMetric::ItemsUsed: return TEXT("Items Used");
        case ERecoveredMetric::DrawsAtMaxHeat: return TEXT("Draws at Max Heat");
        case ERecoveredMetric::EarlyClimax: return TEXT("Early Climaxes");
        case ERecoveredMetric::SessionDuration: return TEXT("Session Duration");
        case ERecoveredMetric::SessionsCompleted: return TEXT("Sessions Completed");
        case ERecoveredMetric::SessionsWon: return TEXT("Sessions Won");
        case ERecoveredMetric::TotalXPEarned: return TEXT("Total XP Earned");
        case ERecoveredMetric::MoneySpent: return TEXT("Coins Spent");
        case ERecoveredMetric::EdgeStreak: return TEXT("Edge Streak");
        default: return TEXT("Unknown");
    }
}

FText URecoveredProgressionLibrary::GetStatValueText(ERecoveredMetric Metric, const FRecoveredSessionStats& SessionStats, const FRecoveredLifetimeStats& LifetimeStats, bool bUseLifetime) {
    // Mirrors native UProgressionManager::GetStatValueText (0x1481c2b60): single
    // stat line addressed by metric enum, lifetime or session value by toggle.
    const int32 Value = bUseLifetime ? GetMetricLifetimeValue(Metric, LifetimeStats) : GetMetricSessionValue(Metric, SessionStats);
    return FText::FromString(FString::Printf(TEXT("%s: %d"), GetMetricDisplayName(Metric), Value));
}

namespace {
const FRecoveredModifierRow* FindModifierRowByTitle(const UDataTable* Table, FName ModifierID, FName* OutCanonicalID = nullptr) {
    if (!Table || ModifierID.IsNone() || Table->GetRowStruct() != FRecoveredModifierRow::StaticStruct()) return nullptr;
    for (const auto& Pair : Table->GetRowMap()) {
        const auto* Row = reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value);
        if (!Row) continue;
        const FString Title = Row->ModifierTitle.ToString();
        if (Title.IsEmpty() || FName(*Title) != ModifierID) continue;
        if (OutCanonicalID) *OutCanonicalID = FName(*Title);
        return Row;
    }
    return nullptr;
}

const TMap<FString, TArray<FString>>& GetRecoveredModifierConflicts() {
    // UProgressionManager::InitializeModifierConflicts at 0x1481c4c00.
    static const TMap<FString, TArray<FString>> Conflicts = {
        { TEXT("Pheromones"), { TEXT("Slow and Steady"), TEXT("Succufrenzy") } },
        { TEXT("Mr. Money Bandz"), { TEXT("Succufrenzy"), TEXT("Sacrificial") } },
        { TEXT("Ass Fanatic"), { TEXT("Boobs Fanatic"), TEXT("Feet Fanatic") } },
        { TEXT("Boobs Fanatic"), { TEXT("Ass Fanatic"), TEXT("Feet Fanatic") } },
        { TEXT("Hungry Succubi"), { TEXT("Succufrenzy"), TEXT("Slow and Steady"), TEXT("Demon Proof"), TEXT("Deal With The Devil") } },
        { TEXT("Succufrenzy"), { TEXT("Slow and Steady"), TEXT("Sacrificial"), TEXT("Hungry Succubi"), TEXT("Raw Dog"), TEXT("Demon Proof"), TEXT("All or Nothing"), TEXT("Double Time"), TEXT("Pheromones"), TEXT("Mr. Money Bandz"), TEXT("Deal With The Devil") } },
        { TEXT("Slow and Steady"), { TEXT("Hungry Succubi"), TEXT("Succufrenzy"), TEXT("Hivemind"), TEXT("Deal With The Devil"), TEXT("Double Time"), TEXT("Pheromones"), TEXT("Iron Man") } },
        { TEXT("Sacrificial"), { TEXT("Mr. Money Bandz"), TEXT("Deal With The Devil"), TEXT("Succufrenzy") } },
        { TEXT("Feet Fanatic"), { TEXT("Ass Fanatic"), TEXT("Boobs Fanatic") } },
        { TEXT("Iron Man"), { TEXT("Slow and Steady") } },
        { TEXT("Raw Dog"), { TEXT("Succufrenzy"), TEXT("All or Nothing") } },
        { TEXT("Demon Proof"), { TEXT("Deal With The Devil"), TEXT("Hivemind"), TEXT("Succufrenzy"), TEXT("Hungry Succubi") } },
        { TEXT("All or Nothing"), { TEXT("Succufrenzy"), TEXT("Raw Dog") } },
        { TEXT("Hivemind"), { TEXT("Demon Proof"), TEXT("Slow and Steady") } },
        { TEXT("Deal With The Devil"), { TEXT("Demon Proof"), TEXT("Hungry Succubi"), TEXT("Sacrificial"), TEXT("Slow and Steady"), TEXT("Succufrenzy") } },
        { TEXT("Double Time"), { TEXT("Succufrenzy"), TEXT("Slow and Steady") } },
    };
    return Conflicts;
}
}

TArray<FRecoveredModifierRow> URecoveredProgressionManager::GetAllModifierData() const {
    TArray<FRecoveredModifierRow> Out;
    if (!ModifierDataTable || ModifierDataTable->GetRowStruct()!=FRecoveredModifierRow::StaticStruct()) return Out;
    for (const auto& Pair : ModifierDataTable->GetRowMap()) {
        if (const FRecoveredModifierRow* Row = reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value)) {
            Out.Add(*Row);
        }
    }
    return Out;
}

bool URecoveredProgressionManager::GetModifierData(FName ModifierID, FRecoveredModifierRow& OutData) const {
    if (const FRecoveredModifierRow* Row = FindModifierRowByTitle(ModifierDataTable, ModifierID)) {
        OutData = *Row;
        return true;
    }
    return false;
}

FName URecoveredProgressionManager::GetCanonicalModifierID(FName ModifierID) const {
    FName CanonicalID;
    FindModifierRowByTitle(ModifierDataTable, ModifierID, &CanonicalID);
    return CanonicalID.IsNone() ? ModifierID : CanonicalID;
}

bool URecoveredProgressionManager::IsModifierUnlocked(FName ModifierID) const {
    return UnlockedModifiers.Contains(ModifierID);
}

bool URecoveredProgressionManager::CanEnableModifier(FName ModifierID) const {
    // Native CanEnableModifier (0x1481b4d00) is a conflict-only predicate.
    return GetConflictingModifiers(ModifierID).IsEmpty();
}

TArray<FName> URecoveredProgressionManager::GetUnlockedModifiers() const {
    return UnlockedModifiers.Array();
}

TArray<FName> URecoveredProgressionManager::GetAllConflictsForModifier(FName ModifierID) const {
    TArray<FName> Out;
    const FString Key = GetCanonicalModifierID(ModifierID).ToString();
    if (const TArray<FString>* Found = GetRecoveredModifierConflicts().Find(Key)) {
        for (const FString& C : *Found) Out.Add(FName(*C));
    }
    return Out;
}

TArray<FName> URecoveredProgressionManager::GetConflictingModifiers(FName ModifierID) const {
    TArray<FName> Out;
    for (const FName Conflict : GetAllConflictsForModifier(ModifierID)) {
        if (EnabledModifiers.Contains(Conflict)) Out.Add(Conflict);
    }
    return Out;
}

FName URecoveredProgressionManager::GetChallengeForModifier(FName ModifierID) const {
    // Native GetChallengeForModifier (0x1481ba860) scans challenge conditions
    // for a type-4 modifier condition and returns the first matching challenge.
    if (!ChallengeDataTable || ChallengeDataTable->GetRowStruct() != FRecoveredChallengeRow::StaticStruct()) return NAME_None;
    const FString CanonicalModifier = GetCanonicalModifierID(ModifierID).ToString();
    if (CanonicalModifier.IsEmpty()) return NAME_None;
    for (const auto& Pair : ChallengeDataTable->GetRowMap()) {
        const auto* Challenge = reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (!Challenge) continue;
        for (const FRecoveredCondition& Condition : Challenge->Conditions) {
            if (Condition.ConditionType == TEXT("modifier") && Condition.ConditionValue == CanonicalModifier) {
                return FName(*Challenge->ChallengeID);
            }
        }
    }
    return NAME_None;
}
