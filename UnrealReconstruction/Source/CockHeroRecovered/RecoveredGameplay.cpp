#include "RecoveredGameplay.h"
#include "Kismet/KismetMathLibrary.h"

int32 URecoveredStateRuleLibrary::AddInt32Wrapping(int32 A, int32 B) {
    const uint32 Bits = static_cast<uint32>(A) + static_cast<uint32>(B);
    int32 Result;
    FMemory::Memcpy(&Result, &Bits, sizeof(Result));
    return Result;
}

double URecoveredStateRuleLibrary::GetPreferenceMultiplier(uint8 Index, double Previous) {
    // SetEdgingPaceModifier and SetUserStrokeMultiplier retain the old value on an unknown index.
    switch (Index) {
    case 0: return 1.0;
    case 1: return 2.0;
    case 2: return 3.0;
    case 3: return 4.0;
    case 4: return 8.0;
    default: return Previous;
    }
}

uint8 URecoveredStateRuleLibrary::DetermineComboTier(int32 ComboCount, uint8 PreviousTier) {
    // Original ranges include their lower boundary and exclude their upper boundary.
    // The final failed range jumps to the tier-5 assignment, including out-of-range counts.
    const int32 Boundaries[] = {0, 100, 250, 500, 750, 1250, 2000};
    for (uint8 Tier = 0; Tier < 6; ++Tier) {
        if (ComboCount >= Boundaries[Tier] && ComboCount < Boundaries[Tier + 1]) return Tier;
    }
    return 5;
}

double URecoveredStateRuleLibrary::GetMinimumBeatInterval(uint8 Difficulty, const FRecoveredDeviceState& Devices, double Previous) {
    // Call arguments are authoritative: original debug messages contain different numbers.
    if (Devices.bLovense) return 0.42;
    if (Devices.bHandy) return 0.24;
    if (Difficulty > 2) return Previous;
    if (Devices.bButtplugVibrators) return Difficulty == 0 ? 0.28 : 0.25;
    if (Devices.bButtplugStrokers && Devices.bFullStrokePerBeat) return Difficulty == 0 ? 0.28 : 0.20;
    switch (Difficulty) {
    case 0: return 0.28;
    case 1: return 0.18;
    case 2: return 0.14;
    default: return Previous;
    }
}

FRecoveredPitchPair URecoveredStateRuleLibrary::CalculateBeatPitch(int32 TotalBeats, int32 RemainingBeats) {
    FRecoveredPitchPair Result;
    const double BeatProgress = 1.0 - UKismetMathLibrary::Divide_DoubleDouble(static_cast<double>(RemainingBeats), static_cast<double>(TotalBeats));
    const double MoanProgress = 1.0 - UKismetMathLibrary::Divide_DoubleDouble(static_cast<double>(RemainingBeats), static_cast<double>(TotalBeats));
    Result.BeatPitch = 1.0 + FMath::Clamp((BeatProgress - 0.6) / 0.4, 0.0, 1.0) * 0.5;
    Result.MoanPitch = 1.0 + FMath::Clamp((MoanProgress - 0.6) / 0.4, 0.0, 1.0) * 0.4;
    return Result;
}

int32 URecoveredStateRuleLibrary::AddCoinsToState(FRecoveredPlayerVariables& Player, int32 Coins) {
    // AddCoins uses the player struct multiplier, not the separate difficulty field.
    const int32 Earned = UKismetMathLibrary::FTrunc(static_cast<double>(Coins) * Player.CoinEarnMultiplier);
    Player.PlayerCoins = AddInt32Wrapping(Player.PlayerCoins, Earned);
    return Earned;
}

double URecoveredStateRuleLibrary::AddToCumMeter(double Current, double Amount) { return Current + Amount; }
double URecoveredStateRuleLibrary::AddToLootBar(double Current, double Amount, double Multiplier) { return Current + Amount * Multiplier; }

namespace {
int32* MetricField(FRecoveredSessionStats& Stats, ERecoveredMetric Metric) {
    switch (Metric) {
    case ERecoveredMetric::Strokes: return &Stats.Strokes;
    case ERecoveredMetric::Edges: return &Stats.Edges;
    case ERecoveredMetric::SuccubiDefeated: return &Stats.SuccubiDefeated;
    case ERecoveredMetric::EnemiesDefeated: return &Stats.EnemiesDefeated;
    case ERecoveredMetric::MaxCombo: return &Stats.MaxCombo;
    case ERecoveredMetric::MissedCumWindows: return &Stats.MissedCumWindows;
    case ERecoveredMetric::TimesTaunted: return &Stats.TimesTaunted;
    case ERecoveredMetric::ItemsUsed: return &Stats.ItemsUsed;
    case ERecoveredMetric::DrawsAtMaxHeat: return &Stats.DrawsAtMaxHeat;
    case ERecoveredMetric::EarlyClimax: return &Stats.EarlyClimax;
    case ERecoveredMetric::SessionDuration: return &Stats.SessionDuration;
    case ERecoveredMetric::SessionsCompleted: return &Stats.SessionsCompleted;
    case ERecoveredMetric::SessionsWon: return &Stats.SessionsWon;
    case ERecoveredMetric::MoneySpent: return &Stats.MoneySpent;
    case ERecoveredMetric::EdgeStreak: return &Stats.EdgeStreak;
    case ERecoveredMetric::ConsecutiveSuccubiSurvived: return &Stats.ConsecutiveSuccubiSurvived;
    case ERecoveredMetric::CumWindowsHit: return &Stats.CumWindowsHit;
    case ERecoveredMetric::LostToSuccubus: return &Stats.TimesLostToSuccubus;
    case ERecoveredMetric::TimeAtHighHeat: return &Stats.TimeAtHighHeat;
    case ERecoveredMetric::PercentAtHighHeat: return &Stats.PercentTimeAtHighHeat;
    case ERecoveredMetric::GamesWithSexToy: return &Stats.GamesWithSexToy;
    case ERecoveredMetric::PerfectEdges: return &Stats.PerfectEdges;
    case ERecoveredMetric::BonerPillsUsed: return &Stats.BonerPillsUsed;
    case ERecoveredMetric::AcceptedTemptation: return &Stats.AcceptedTemptation;
    case ERecoveredMetric::CameDuringTaunt: return &Stats.CameDuringTaunt;
    default: return nullptr; // Matches native session switch; other metrics route through challenges.
    }
}
bool IsMaximumMetric(ERecoveredMetric Metric) {
    return Metric == ERecoveredMetric::MaxCombo || Metric == ERecoveredMetric::EdgeStreak || Metric == ERecoveredMetric::ConsecutiveSuccubiSurvived;
}
}

void URecoveredStateRuleLibrary::RecordSessionMetric(FRecoveredSessionStats& Stats, ERecoveredMetric Metric, int32 Amount) {
    if (int32* Field = MetricField(Stats, Metric)) {
        if (IsMaximumMetric(Metric)) *Field = FMath::Max(*Field, Amount);
        else if (Metric == ERecoveredMetric::PercentAtHighHeat) *Field = Amount;
        else *Field = AddInt32Wrapping(*Field, Amount);
    }
    // Native lifetime maximum persistence and challenge evaluation are separate, unrestored adapters.
}

void URecoveredStateRuleLibrary::SetSessionMetric(FRecoveredSessionStats& Stats, ERecoveredMetric Metric, int32 Value) {
    if (int32* Field = MetricField(Stats, Metric)) *Field = IsMaximumMetric(Metric) ? FMath::Max(*Field, Value) : Value;
}

void URecoveredStateRuleLibrary::SetMaximumCombo(FRecoveredSessionStats& Stats, int32 Combo) { Stats.MaxCombo = FMath::Max(Stats.MaxCombo, Combo); }

void URecoveredStateRuleLibrary::AdvanceSessionDuration(FRecoveredPlayerVariables& Player, FRecoveredSessionStats& Stats, double Heat) {
    Player.SessionLength = AddInt32Wrapping(Player.SessionLength, 1);
    // Original computes the percentage before adding this tick's high-heat time.
    Stats.PercentTimeAtHighHeat = UKismetMathLibrary::FTrunc(UKismetMathLibrary::Divide_DoubleDouble(static_cast<double>(Stats.TimeAtHighHeat), static_cast<double>(Player.SessionLength)) * 100.0);
    if (Heat >= 70.0) Stats.TimeAtHighHeat = AddInt32Wrapping(Stats.TimeAtHighHeat, 1);
}
