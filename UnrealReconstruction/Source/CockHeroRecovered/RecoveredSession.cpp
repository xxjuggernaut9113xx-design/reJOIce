#include "RecoveredSession.h"

int32 URecoveredSessionRuleLibrary::UpdateRecentDrawCount(TArray<int32>& Timestamps,int32 SessionLength) {
    for(int32 Index=0;Index<Timestamps.Num();++Index) {
        if(Timestamps[Index]==0) Timestamps.Remove(0);
        const int32 Value=Timestamps.IsValidIndex(Index) ? Timestamps[Index] : 0;
        if(URecoveredStateRuleLibrary::AddInt32Wrapping(SessionLength,static_cast<int32>(0u-static_cast<uint32>(Value)))>=5) Timestamps.Remove(Value);
    }
    return Timestamps.Num();
}

FRecoveredBeatPattern URecoveredSessionRuleLibrary::CheckIntervalMultipliers(const FRecoveredBeatPattern& Pattern,float CurrentInterval) {
    FRecoveredBeatPattern Result=Pattern;
    if(static_cast<double>(CurrentInterval)<=0.2) for(double& Multiplier:Result.IntervalMultipliers) if(static_cast<double>(static_cast<float>(Multiplier))>=2.0) Multiplier=2.5;
    return Result;
}

void URecoveredSessionRuleLibrary::DetermineDrawMultipliers(uint8 ComboTier, double DifficultyCount, double DifficultySpeed, double& StrokeCountMultiplier, double& StrokeTimeMultiplier) {
    static constexpr double Counts[]={0.8,0.8,1.0,1.25,1.5,1.75,2.25,3.0};
    static constexpr double Times[]={1.4,1.25,1.0,0.95,0.85,0.8,0.75,0.6};
    if(ComboTier>=UE_ARRAY_COUNT(Counts)) return;
    StrokeCountMultiplier=Counts[ComboTier]*DifficultyCount;
    // Tier A deliberately assigns a literal, bypassing the difficulty multiplier.
    StrokeTimeMultiplier=ComboTier==4 ? 0.85 : Times[ComboTier]*DifficultySpeed;
}

int32 URecoveredSessionRuleLibrary::GetCoinAward(uint8 CardType) {
    switch (CardType) {
    case 0: case 1: case 2: case 6: case 7: case 8: return 1;
    case 3: case 5: return 2;
    default: return 0;
    }
}
double URecoveredSessionRuleLibrary::GetHeatAward(const FRecoveredBeatContext& Context) {
    switch (Context.HeatCategory) {
    case 0: return Context.HighHeatAdd;
    case 1: return Context.MediumHeatAdd;
    case 2: return Context.SlowHeatAdd;
    default: return 0;
    }
}
double URecoveredSessionRuleLibrary::GetLootIncrement(uint8 CardType, bool bMoneyModifier) {
    switch (CardType) {
    case 0: return bMoneyModifier ? 0.1 : 0.05;
    case 1: return bMoneyModifier ? 0.07 : 0.035;
    case 2: case 7: case 8: return bMoneyModifier ? 0.06 : 0.03;
    case 3: case 5: case 6: return bMoneyModifier ? 0.1 : 0.05;
    default: return 0;
    }
}
void URecoveredSessionRuleLibrary::AddBeatMeter(FRecoveredPlayerVariables& Player, const FRecoveredBeatContext& Context, double Heat, double& BaseGain, double& Meter) {
    if (Player.bHasCame) return;
    if (Context.ActiveModifiers.Contains(TEXT("Hungry Succubi")) && Context.CardType == 3) {
        Meter = FMath::Clamp(Meter - 0.002, 0.0, 1.0);
        return;
    }
    if (Context.ActiveModifiers.Contains(TEXT("Sacrificial"))) return;
    if (Context.ActiveModifiers.Contains(TEXT("Mr. Money Bandz"))) BaseGain = 0.000125;
    if (Context.ActiveModifiers.Contains(TEXT("Deal With The Devil")) && Context.CardType != 3) return;
    Meter += BaseGain * Player.CumMeterMultiplier;
    if (Heat >= 80) Meter += 0.00025;
    if (Player.ConsecutiveHighHeatDraws >= 8) Meter += 0.00025;
    Meter += (static_cast<double>(Player.TotalEdgeCount) / 3.0) / 2000.0;
    if (Player.CurrentComboCount >= 1500) Meter += 0.00025;
    Meter += static_cast<double>(Player.SessionLength / 300) / 10000.0;
}
void URecoveredSessionRuleLibrary::BreakCombo(FRecoveredPlayerVariables& Player) {
    Player.BrokenComboArray.Add(Player.CurrentComboCount);
    Player.CurrentComboCount = 0;
}
