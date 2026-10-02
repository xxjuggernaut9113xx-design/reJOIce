#include "RecoveredRewards.h"

bool URecoveredProgressionManager::UnlockPlayerCard(FName CardID) {
    if (CardID.IsNone() || UnlockedPlayerCards.Contains(CardID) || !PlayerCardDataTable || PlayerCardDataTable->GetRowStruct()!=FRecoveredPlayerCardRow::StaticStruct()) return false;
    // The native helper searches each row's CardID, rather than using row names.
    for (const auto& Pair:PlayerCardDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredPlayerCardRow*>(Pair.Value);
        if (FName(*Row->CardID)!=CardID) continue;
        UnlockedPlayerCards.Add(CardID);
        OnSaveRequested.Broadcast();
        return true;
    }
    return false;
}

bool URecoveredProgressionManager::UnlockModifier(FName ModifierID) {
    if (ModifierID.IsNone() || UnlockedModifiers.Contains(ModifierID) || !ModifierDataTable || ModifierDataTable->GetRowStruct()!=FRecoveredModifierRow::StaticStruct()) return false;
    const FString Requested=ModifierID.ToString();
    for (const auto& Pair:ModifierDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value);
        const FString Title=Row->ModifierTitle.ToString();
        if (Title.IsEmpty() || !Title.Equals(Requested,ESearchCase::IgnoreCase)) continue;
        UnlockedModifiers.Add(ModifierID);
        OnSaveRequested.Broadcast();
        return true;
    }
    return false;
}

void URecoveredRewardLibrary::GrantRecoveredRewards(URecoveredProgressionManager* Manager,const TArray<FRecoveredReward>& Rewards) {
    if (!Manager) return;
    for (const auto& Reward:Rewards) {
        FString Kind=Reward.RewardType;
        Kind.RemoveFromStart(TEXT("ECHRewardType::"));
        if (Kind==TEXT("XP")) Manager->AddXP(Reward.Value,TEXT("Challenge"));
        else if (Kind==TEXT("UnlockPoints")) {
            if (Reward.Value<=0) continue;
            Manager->AddUnlockPoints(Reward.Value);
            Manager->OnStorePointsRequested.Broadcast(Reward.Value);
        } else if (Kind==TEXT("UnlockPack")) {
            if (!FName(*Reward.ItemIdentifier).IsNone()) Manager->OnPackRewardRequested.Broadcast(Reward.ItemIdentifier);
        } else if (Kind==TEXT("PlayerCard")) Manager->UnlockPlayerCard(FName(*Reward.ItemIdentifier));
        else if (Kind==TEXT("UnlockModifier")) Manager->UnlockModifier(FName(*Reward.ItemIdentifier));
    }
}
