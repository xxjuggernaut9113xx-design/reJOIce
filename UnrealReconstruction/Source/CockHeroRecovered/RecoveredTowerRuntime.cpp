#include "RecoveredTowerRuntime.h"
#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "RecoveredRules.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredSuccuEconomy.h"

namespace {
const TCHAR* ObjectiveNames[] = {TEXT("FillCumMeter"), TEXT("TimerBased"), TEXT("Strokes"), TEXT("Edges"), TEXT("CoinFlip"), TEXT("Ruiner"), TEXT("Prejac"), TEXT("Tribute"), TEXT("SuccuSlayer")};
bool ModifierFitsObjective(const FString& Modifier, uint8 Objective) {
    if (Modifier.Equals(TEXT("Mr. Money Bandz"), ESearchCase::IgnoreCase)) return Objective == 0;
    if (Modifier.Equals(TEXT("Hungry Succubi"), ESearchCase::IgnoreCase)) return Objective == 0 || Objective == 2;
    if (Modifier.Equals(TEXT("Succufrenzy"), ESearchCase::IgnoreCase)) return Objective != 3 && Objective != 6 && Objective != 7;
    if (Modifier.Equals(TEXT("Slow and Steady"), ESearchCase::IgnoreCase)) return Objective <= 8 && ((0x1a8u >> Objective) & 1) != 0;
    if (Modifier.Equals(TEXT("Sacrificial"), ESearchCase::IgnoreCase) || Modifier.Equals(TEXT("Demon Proof"), ESearchCase::IgnoreCase)) return Objective == 8;
    if (Modifier.Equals(TEXT("Deal With The Devil"), ESearchCase::IgnoreCase)) return Objective <= 8 && ((0x1aau >> Objective) & 1) != 0;
    if (Modifier.Equals(TEXT("Double Time"), ESearchCase::IgnoreCase)) return Objective == 3;
    return true;
}
const TCHAR* SuccuModifierNames[]={TEXT("PotLid"),TEXT("GoldenShower"),TEXT("Lube"),TEXT("DevilCoin"),TEXT("HeatSpell"),TEXT("BurningProfits"),TEXT("Molasses"),TEXT("InfernalClause"),TEXT("HellMagnet"),TEXT("Accelerant"),TEXT("Exorcist"),TEXT("BankingError"),TEXT("StockholmCuffs"),TEXT("BiggerPockets"),TEXT("EnhancedPlating"),TEXT("Firemouth"),TEXT("PassiveCooling"),TEXT("Recycler"),TEXT("SpoilsOfSin"),TEXT("GoonTycoon"),TEXT("Coinverter"),TEXT("FlameHarness")};
}
bool URecoveredTowerRuntime::LoadSourceCatalog(FString& Error) {
    FString Json;
    const FString Path = FPaths::ProjectContentDir() / TEXT("Recovery/Definitions/newer-20261017-mode-data.json");
    if (!FFileHelper::LoadFileToString(Json, *Path)) { Error = TEXT("Cannot read Tower mode data: ") + Path; return false; }
    TSharedPtr<FJsonObject> Parsed;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json), Parsed) || !Parsed.IsValid()) { Error = TEXT("Tower mode data is invalid JSON"); return false; }
    const TArray<TSharedPtr<FJsonValue>>* Tiers = nullptr; const TArray<TSharedPtr<FJsonValue>>* Objectives = nullptr;
    if (!Parsed->TryGetArrayField(TEXT("tiers"), Tiers) || Tiers->Num() != 6 || !Parsed->TryGetArrayField(TEXT("objectives"), Objectives) || Objectives->Num() != 42) { Error = TEXT("Tower mode data is missing the six tiers or 42 objective parameter rows"); return false; }
    SourceCatalog = MoveTemp(Parsed); Error.Reset(); return true;
}
float URecoveredTowerRuntime::GetDifficultyProgress(int32 Round) const {
    if (bEndlessMode) return FMath::Clamp(FMath::Max(Round - 1, 0) * .06f, 0.f, .9f);
    return TotalRounds < 2 ? 0.f : FMath::Clamp(static_cast<float>(Round - 1) / (TotalRounds - 1), 0.f, 1.f);
}
float URecoveredTowerRuntime::CalculateAdaptivePressure() const {
    if (RoundHistory.IsEmpty()) return 0;
    const float Progress = 1 - FMath::Pow(1 - GetDifficultyProgress(CurrentRound), .6f);
    const float TargetEdges = FMath::Lerp(.5f, 2.5f, Progress), TargetDefense = FMath::Lerp(0.f, 1.5f, Progress);
    const float TargetOffense = Progress, TargetTaunts = Progress, TargetTemptations = Progress;
    const float RecentWeights[] = {.6f, .3f, .1f};
    float Pressure = 0, Total = 0;
    for (int32 I = 0; I < FMath::Min(RoundHistory.Num(), 3); ++I) {
        const auto& Stats = RoundHistory[RoundHistory.Num() - 1 - I];
        const float PerMinute = 1.f / FMath::Max(Stats.SessionDuration / 60.f, .1f);
        const float EdgeWeight = Stats.Edges > 0 ? .4f : 0.f;
        const float Scale = 1.2f / (.8f + EdgeWeight);
        const float Edges = Stats.Edges > 0 ? (Stats.Edges * PerMinute - TargetEdges) / 3 : 0;
        const float Defense = (Stats.DefensiveItemsUsed * PerMinute - TargetDefense) / 2;
        const float Offense = (TargetOffense - Stats.OffensiveItemsUsed * PerMinute) / 2;
        const float Taunts = (TargetTaunts - Stats.TimesTaunted * PerMinute) / 2;
        const float Temptations = (TargetTemptations - Stats.AcceptedTemptation * PerMinute) / 2;
        Pressure += (.15f * Temptations + .15f * Taunts + .2f * Offense + .3f * Defense + EdgeWeight * Edges) * Scale * RecentWeights[I];
        Total += RecentWeights[I];
    }
    return Total > 0 ? Pressure / Total : 0;
}
int32 URecoveredTowerRuntime::RollAdaptiveTier() {
    if (!bEndlessMode && TotalRounds < 2) return 1;
    const float Pressure = CalculateAdaptivePressure();
    const float Progress = FMath::Clamp(GetDifficultyProgress(CurrentRound + 1) - (Pressure > 0 ? .2f : .1f) * Pressure, 0.f, 1.f);
    float Weights[5], Total = 0;
    for (int32 I = 0; I < 5; ++I) { const float Shape = FMath::Max(1 - FMath::Abs(Progress - I * .25f) * 2.5f, 0.f); Weights[I] = Shape * Shape + .1f; Total += Weights[I]; }
    float Roll = Random.FRand() * Total;
    for (int32 I = 0; I < 5; ++I) { Roll -= Weights[I]; if (Roll <= 0) return I + 1; }
    return 5;
}

bool URecoveredTowerRuntime::StartSession(int32 Rounds, bool Endless, int32 ShopEvery, const TArray<FRecoveredTowerOption>& Pool, int32 Seed, FString& Error) {
    Error.Reset();
    if ((!Endless && Rounds <= 0) || ShopEvery < 0 || Pool.IsEmpty()) { Error = TEXT("Tower requires a round count, nonnegative shop interval, and an option pool"); return false; }
    for (const auto& Option : Pool) if (Option.Objective > 8 || Option.DifficultyTier < 0 || Option.DifficultyTier > 6 || !FMath::IsFinite(Option.ObjectiveParam) || Option.ObjectiveParam <= 0) {
        Error = TEXT("Tower option contains an invalid objective, difficulty tier, or objective parameter"); return false;
    }
    StopSession(); OptionPool = Pool; TotalRounds = Rounds; bEndlessMode = Endless; ShopInterval = ShopEvery; Random.Initialize(Seed);
    CurrentRound = 0; Phase = ERecoveredRoundPhase::SessionSetup;
    return GenerateOptions();
}
bool URecoveredTowerRuntime::GenerateOptions() {
    if (OptionPool.IsEmpty() || (Phase != ERecoveredRoundPhase::SessionSetup && Phase != ERecoveredRoundPhase::RoundComplete && Phase != ERecoveredRoundPhase::Shop)) return false;
    CurrentOptions.Reset();
    TArray<int32> Candidates;
    const bool FinalRound = !bEndlessMode && CurrentRound + 1 >= TotalRounds;
    const bool HasEdgeHistory = RoundHistory.ContainsByPredicate([](const FRecoveredSessionStats& Stats) { return Stats.Edges > 0 || Stats.DefensiveItemsUsed > 0; });
    for (int32 I = 0; I < OptionPool.Num(); ++I) {
        if (!FinalRound && (OptionPool[I].Objective == 6 || OptionPool[I].Objective == 7)) continue;
        if (SourceCatalog.IsValid() && OptionPool[I].Objective == 3 && !HasEdgeHistory) continue;
        Candidates.Add(I);
    }
    if (Candidates.IsEmpty()) return false;
    if (SourceCatalog.IsValid()) {
        TArray<int32> Fresh;
        for (int32 Index : Candidates) if (!RecentObjectives.Contains(OptionPool[Index].Objective)) Fresh.Add(Index);
        if (Fresh.Num() >= 3) Candidates = MoveTemp(Fresh);
    }
    const TArray<int32> Eligible = Candidates;
    int32 Tiers[] = {2, 3, 4}; uint8 Lanes[] = {0, 1, 2};
    if (SourceCatalog.IsValid() && CurrentRound > 0 && !FinalRound) {
        const int32 Base = RollAdaptiveTier();
        Tiers[0] = FMath::Clamp(Base - (Random.FRand() >= .75f ? 2 : 1), 1, 5);
        const float MiddleRoll = Random.FRand(); Tiers[1] = FMath::Clamp(Base + (MiddleRoll < .2f ? -1 : MiddleRoll >= .8f ? 1 : 0), 1, 5);
        Tiers[2] = FMath::Clamp(Base + (Random.FRand() >= .75f ? 2 : 1), 1, 5);
    }
    if (SourceCatalog.IsValid() && !FinalRound) for (int32 I = 2; I > 0; --I) { const int32 J = Random.RandRange(0, I); Swap(Tiers[I], Tiers[J]); Swap(Lanes[I], Lanes[J]); }
    // Draw without replacement where possible; a single eligible objective
    // still offers the three declared lanes without inventing new objectives.
    for (uint8 Lane = 0; Lane < 3; ++Lane) {
        if (Candidates.IsEmpty()) Candidates = Eligible;
        const int32 Pick = Random.RandRange(0, Candidates.Num() - 1);
        FRecoveredTowerOption Option = OptionPool[Candidates[Pick]];
        Candidates.RemoveAt(Pick); Option.DraftLane = Lanes[Lane];
        if (SourceCatalog.IsValid()) {
            // Native GenerateRoundOptions assigns final rounds tier six. Its
            // opening calibration and adaptive helpers select ordinary tiers.
            Option.DifficultyTier = FinalRound ? 6 : Tiers[Lane];
            const auto& Objectives = SourceCatalog->GetArrayField(TEXT("objectives"));
            Option.ObjectiveParam = 0;
            for (const auto& Value : Objectives) {
                const auto Row = Value->AsObject();
                if (Row->GetIntegerField(TEXT("Tier")) != Option.DifficultyTier || Row->GetStringField(TEXT("Objective")) != FString(TEXT("ESessionObjective::")) + ObjectiveNames[Option.Objective]) continue;
                Option.ObjectiveParam = Random.RandRange(Row->GetIntegerField(TEXT("MinValue")), Row->GetIntegerField(TEXT("MaxValue"))); break;
            }
            for (const auto& Value : SourceCatalog->GetArrayField(TEXT("tiers"))) {
                const auto Row = Value->AsObject(); if (Row->GetIntegerField(TEXT("Tier")) != Option.DifficultyTier) continue;
                Option.RewardCoins = Random.RandRange(Row->GetIntegerField(TEXT("MinBaseCoins")), Row->GetIntegerField(TEXT("MaxBaseCoins")));
                Option.RewardSuccuCoins = FMath::Max(1, FMath::RoundToInt(Random.RandRange(Row->GetIntegerField(TEXT("MinBaseSuccuCoins")), Row->GetIntegerField(TEXT("MaxBaseSuccuCoins"))) * (Option.DraftLane == 0 ? 1.f : Option.DraftLane == 1 ? 1.75f : 3.f)));
                if (auto* Manager=Cast<ARecoveredGlobalManager>(GetOwner())) {
                    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
                        FRecoveredTowerRewardContext Context;
                        Context.Tier=Option.DifficultyTier; Context.Lane=Option.DraftLane;
                        Context.BaseCoins=Option.RewardCoins; Context.BaseSuccuCoins=Option.RewardSuccuCoins;
                        Context.bFinalRound=FinalRound;
                        const TArray<TSharedPtr<FJsonValue>>* Unlockable=nullptr;
                        if (Row->TryGetArrayField(TEXT("UnlockableSuccuModifiers"),Unlockable)) for (const auto& UnlockableValue:*Unlockable) {
                            const FString Name=UnlockableValue->AsString();
                            for (uint8 Modifier=0;Modifier<UE_ARRAY_COUNT(SuccuModifierNames);++Modifier) if (Name==FString(TEXT("ESuccuShopModifier::"))+SuccuModifierNames[Modifier]) Context.UnlockableModifiers.Add(Modifier);
                        }
                        const TSet<uint8> Empty;
                        Option.NativeRewards=RecoveredTowerRewards::Generate(Context,*Inventory,Manager->SuccuEconomy ? Manager->SuccuEconomy->OwnedModifiers : Empty,Random);
                        Option.RewardCoins=Option.RewardSuccuCoins=0;
                        for (const auto& Reward:Option.NativeRewards) {
                            if (Reward.Type==0) Option.RewardCoins+=Reward.Amount;
                            else if (Reward.Type==1) Option.RewardSuccuCoins+=Reward.Amount;
                        }
                    }
                }
                const int32 Minimum = Row->GetIntegerField(TEXT("MinModifiers")), Maximum = Row->GetIntegerField(TEXT("MaxModifiers"));
                TArray<FString> Modifiers;
                for (const auto& Modifier : Row->GetArrayField(TEXT("EligibleModifierTitles"))) if (ModifierFitsObjective(Modifier->AsString(), Option.Objective)) Modifiers.Add(Modifier->AsString());
                const int32 Count = FMath::Min(Random.RandRange(Minimum, Maximum), Modifiers.Num());
                for (int32 I = 0; I < Count; ++I) { const int32 Selected = Random.RandRange(0, Modifiers.Num() - 1); Option.Modifiers.Add(FName(*Modifiers[Selected])); Modifiers.RemoveAt(Selected); }
                break;
            }
        }
        CurrentOptions.Add(MoveTemp(Option));
    }
    Phase = ERecoveredRoundPhase::RoundSelection;
    return true;
}
bool URecoveredTowerRuntime::SelectOption(int32 Index) {
    if (Phase != ERecoveredRoundPhase::RoundSelection || !CurrentOptions.IsValidIndex(Index)) return false;
    SelectedOption = CurrentOptions[Index];
    RecentObjectives.Add(SelectedOption.Objective);
    while (RecentObjectives.Num() > 3) RecentObjectives.RemoveAt(0);
    ++CurrentRound;
    Phase = !bEndlessMode && CurrentRound>=TotalRounds ? ERecoveredRoundPhase::BossRound : ERecoveredRoundPhase::Playing;
    OnRoundStarted.Broadcast(SelectedOption); return true;
}
bool URecoveredTowerRuntime::CompleteRound(bool Success) {
    if (Phase != ERecoveredRoundPhase::Playing && Phase != ERecoveredRoundPhase::BossRound) return false;
    bLastRoundSucceeded = Success;
    CompletedRounds=FMath::Max(CompletedRounds,CurrentRound);
    if (!Success) ++FailedRounds;
    Phase = ERecoveredRoundPhase::RoundComplete;
    OnRoundCompleted.Broadcast(CompletedRounds); return true;
}
bool URecoveredTowerRuntime::ContinueAfterRound() {
    if (Phase != ERecoveredRoundPhase::RoundComplete) return false;
    if (!bEndlessMode && CurrentRound >= TotalRounds) {
        Phase = ERecoveredRoundPhase::SessionComplete; OnSessionComplete.Broadcast(CompletedRounds); return true;
    }
    if (ShopInterval > 0 && CurrentRound % ShopInterval == 0) { Phase = ERecoveredRoundPhase::Shop; OnShopOpened.Broadcast(); return true; }
    return GenerateOptions();
}
bool URecoveredTowerRuntime::LeaveShop() { return Phase == ERecoveredRoundPhase::Shop && GenerateOptions(); }
void URecoveredTowerRuntime::StopSession() {
    Phase = ERecoveredRoundPhase::Inactive; CurrentRound = CompletedRounds = FailedRounds = TotalRounds = 0;
    bLastRoundSucceeded = bEndlessMode = false; CurrentOptions.Reset(); OptionPool.Reset(); RoundHistory.Reset(); RecentObjectives.Reset(); SelectedOption = FRecoveredTowerOption();
}
