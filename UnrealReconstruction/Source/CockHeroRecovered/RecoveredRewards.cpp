#include "RecoveredRewards.h"

bool URecoveredProgressionManager::UnlockPlayerCard(FName CardID) {
    if (CardID.IsNone() || UnlockedPlayerCards.Contains(CardID) || !PlayerCardDataTable || PlayerCardDataTable->GetRowStruct()!=FRecoveredPlayerCardRow::StaticStruct()) return false;
    // The native helper searches each row's CardID, rather than using row names.
    for (const auto& Pair:PlayerCardDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredPlayerCardRow*>(Pair.Value);
        if (FName(*Row->CardID)!=CardID) continue;
        UnlockedPlayerCards.Add(CardID);
        OnContentUnlocked.Broadcast(CardID, Row->CardID);
        OnSaveRequested.Broadcast();
        return true;
    }
    return false;
}

bool URecoveredProgressionManager::EquipPlayerCard(FName CardID) {
    if (CardID.IsNone()) {
        EquippedPlayerCard=NAME_None;
        OnSaveRequested.Broadcast();
        return true;
    }
    if (!IsPlayerCardUnlocked(CardID)) return false;
    EquippedPlayerCard=CardID;
    OnSaveRequested.Broadcast();
    return true;
}

FName URecoveredProgressionManager::GetEquippedPlayerCard() const {
    return EquippedPlayerCard;
}

bool URecoveredProgressionManager::IsPlayerCardUnlocked(FName CardID) const {
    return !CardID.IsNone() && UnlockedPlayerCards.Contains(CardID);
}

bool URecoveredProgressionManager::GetPlayerCardData(FName CardID,FRecoveredPlayerCardRow& OutData) const {
    OutData=FRecoveredPlayerCardRow();
    if (CardID.IsNone() || !PlayerCardDataTable || PlayerCardDataTable->GetRowStruct()!=FRecoveredPlayerCardRow::StaticStruct()) return false;
    for (const TPair<FName,uint8*>& Pair:PlayerCardDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredPlayerCardRow*>(Pair.Value);
        if (Row && FName(*Row->CardID)==CardID) {
            OutData=*Row;
            return true;
        }
    }
    return false;
}

TArray<FName> URecoveredProgressionManager::GetUnlockedPlayerCards() const {
    TArray<FName> Result;
    if (!PlayerCardDataTable || PlayerCardDataTable->GetRowStruct()!=FRecoveredPlayerCardRow::StaticStruct()) return Result;
    for (const TPair<FName,uint8*>& Pair:PlayerCardDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredPlayerCardRow*>(Pair.Value);
        if (Row && IsPlayerCardUnlocked(FName(*Row->CardID))) Result.Add(FName(*Row->CardID));
    }
    Result.Sort([](const FName& Left,const FName& Right) { return Left.LexicalLess(Right); });
    return Result;
}

bool URecoveredProgressionManager::UnlockModifier(FName ModifierID) {
    if (ModifierID.IsNone() || UnlockedModifiers.Contains(ModifierID) || !ModifierDataTable || ModifierDataTable->GetRowStruct()!=FRecoveredModifierRow::StaticStruct()) return false;
    for (const auto& Pair:ModifierDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value);
        const FString Title=Row->ModifierTitle.ToString();
        const FName CanonicalID(*Title);
        if (CanonicalID.IsNone() || CanonicalID!=ModifierID) continue;
        UnlockedModifiers.Add(CanonicalID);
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
