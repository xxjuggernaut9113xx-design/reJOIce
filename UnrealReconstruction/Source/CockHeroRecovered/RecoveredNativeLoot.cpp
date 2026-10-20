#include "RecoveredNativeLoot.h"

bool RecoveredNativeLoot::IsPanicBlocked(FName ItemID,double Heat,const TArray<FString>& Modifiers) {
    if (Heat>75 || !Modifiers.Contains(TEXT("Panic Button"))) return false;
    return ItemID==TEXT("DecreaseHeat") || ItemID==TEXT("Slowdown") || ItemID==TEXT("Break") || ItemID==TEXT("SuccuShield") || ItemID==TEXT("Resupply") || ItemID==TEXT("EscapeRope") || ItemID==TEXT("ComboCruncher");
}

FRecoveredNativeLootReward RecoveredNativeLoot::Roll(const URecoveredNewerInventory& Inventory,const FRecoveredNativeLootContext& Context,float RollPercent) {
    FRecoveredNativeLootReward Result;
    Result.Amount=Context.CoinReward;
    if (Context.bDrySpell || !FMath::IsFinite(RollPercent)) return Result;
    struct FInfo { ERecoveredShopItemType Type; int32 Cap; float Weight; };
    static constexpr FInfo Rows[]={
        {ERecoveredShopItemType::DecreaseHeat,3,15},{ERecoveredShopItemType::Slowdown,3,10},
        {ERecoveredShopItemType::Break,2,6},{ERecoveredShopItemType::BonerPill,5,10},
        {ERecoveredShopItemType::SuccuShield,15,25},{ERecoveredShopItemType::Resupply,1,1},
        {ERecoveredShopItemType::ApexLure,3,20},{ERecoveredShopItemType::LootRush,2,10},
        {ERecoveredShopItemType::Bounty,2,10},{ERecoveredShopItemType::ComboCruncher,2,5},
        {ERecoveredShopItemType::EscapeRope,1,.5f}
    };
    TArray<FInfo> Eligible;
    float Total=0;
    for (const auto Item:Inventory.HotbarItems) {
        for (const auto& Row:Rows) if (Row.Type==Item) {
            const auto* State=Inventory.OwnedItems.Find(Item);
            if (State && State->Charges>=Row.Cap+(Context.bBiggerPockets ? 1 : 0)) break;
            Eligible.Add(Row);
            Total+=Row.Weight;
            break;
        }
    }
    if (Eligible.IsEmpty()) return Result;
    auto Scale=[&](float NewTotal) {
        const float Factor=Total>0 ? FMath::Max(0.f,NewTotal)/Total : 0;
        for (auto& Row:Eligible) Row.Weight*=Factor;
        Total=FMath::Max(0.f,NewTotal);
    };
    const float Multiplier=Context.bPrizeMachine ? (Context.bBurningProfits ? 6.f : 4.f) : (Context.bBurningProfits ? 2.f : 1.f);
    if (!FMath::IsNearlyEqual(Multiplier,1.f,1.e-8f)) Scale(Total*Multiplier);
    if (Context.bBadRNG) Scale(Total-50.f);
    if (Total>100.f) Scale(100.f);
    float Jackpot=0;
    if (Context.bJackpotDrops && Total>0) { Jackpot=FMath::Min(Total,FMath::Clamp(Context.JackpotWeight,0.f,100.f)); Scale(0); }
    float Accumulated=0;
    for (const auto& Row:Eligible) {
        Accumulated+=Row.Weight;
        if (Row.Weight>0 && RollPercent<=Accumulated) { Result.Type=4; Result.Item=Row.Type; Result.Amount=1; return Result; }
    }
    if (Jackpot>0 && RollPercent<=Accumulated+Jackpot) { Result.Type=6; Result.Amount=1; }
    return Result;
}
