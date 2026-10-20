#include "RecoveredSuccuEconomy.h"
#include "RecoveredRules.h"
#include "RecoveredNewerInventoryAdapter.h"

URecoveredSuccuEconomy::URecoveredSuccuEconomy() {
    PrimaryComponentTick.bCanEverTick=true;
    Random.Initialize(173203);
}

TArray<FRecoveredSuccuShopEntry> URecoveredSuccuEconomy::GetCatalog() {
    struct FSourceEntry { uint8 ID; const TCHAR* Title; const TCHAR* Description; int32 Cost; };
    static const FSourceEntry Source[]={
        {0,TEXT("Pot Lid"),TEXT("Caps max heat to 75%"),10},
        {1,TEXT("Golden Shower"),TEXT("Earn 5x coins from the Lootbar"),5},
        {2,TEXT("Lube"),TEXT("-50% Heat Gain"),12},
        {3,TEXT("Devil Coin"),TEXT("50% chance to earn double SuccuCoins from Succubi"),6},
        {4,TEXT("Heat Spell"),TEXT("Defensive items reduce heat by 10% on use."),8},
        {5,TEXT("Burning Profits"),TEXT("Double item drop chance from the Lootbar at max heat."),6},
        {6,TEXT("Mollasses"),TEXT("50% slower strokes"),20},
        {7,TEXT("Infernal Clause"),TEXT("Succubus Stroke Counts Halved"),12},
        {8,TEXT("Hell Magnet"),TEXT("Double Succubus Spawn Rate"),2},
        {9,TEXT("Accelerant"),TEXT("Double Lootbar Progress during Succubus encounters"),6},
        {10,TEXT("Exorcist"),TEXT("30 second cooldown between Succubus Encounters"),10},
        {11,TEXT("Banking Error"),TEXT("20% chance for strokes to give double coins"),4},
        {12,TEXT("Stockholm Cuffs"),TEXT("Harder Succubi, but 3x SuccuCoin Rewards"),6},
        {13,TEXT("Bigger Pockets"),TEXT("+1 Inventory Space for All Items"),8},
        {14,TEXT("Enhanced Plating"),TEXT("SuccuShields last for 2 draws instead of 1"),8},
        {16,TEXT("Passive Cooling"),TEXT("Filling the Lootbar reduces heat by 2%"),3},
        {17,TEXT("Recycler"),TEXT("Using an item has a 25% chance to not consume the charge"),6},
        {18,TEXT("Spoils of Sin"),TEXT("Succubi drop a random item charge on defeat"),10},
        {19,TEXT("Goon Tycoon"),TEXT("Earn 1 SuccuCoin every minute"),3},
        {20,TEXT("Coinverter"),TEXT("Every 300 strokes grants +1 SuccuCoin"),12},
        {21,TEXT("Flame Harness"),TEXT("Reduce heat by 0.25% for every stroke during a Succubus Encounter"),12}
    };
    TArray<FRecoveredSuccuShopEntry> Catalog;
    for (const auto& Entry:Source) {
        FRecoveredSuccuShopEntry Row;
        Row.Modifier=Entry.ID; Row.Title=Entry.Title; Row.Description=Entry.Description; Row.Cost=Entry.Cost;
        Catalog.Add(MoveTemp(Row));
    }
    return Catalog;
}

void URecoveredSuccuEconomy::Initialize(ARecoveredGlobalManager* InManager) {
    if (Manager) {
        Manager->OnMetricUpdateRequested.RemoveDynamic(this,&URecoveredSuccuEconomy::HandleMetric);
        Manager->OnSessionAction.RemoveDynamic(this,&URecoveredSuccuEconomy::HandleAction);
    }
    Manager=InManager;
    if (Manager) {
        Manager->OnMetricUpdateRequested.AddUniqueDynamic(this,&URecoveredSuccuEconomy::HandleMetric);
        Manager->OnSessionAction.AddUniqueDynamic(this,&URecoveredSuccuEconomy::HandleAction);
    }
}

void URecoveredSuccuEconomy::ResetRun() {
    SuccuCoins=0;
    OwnedModifiers.Empty();
    LastError.Empty();
    TycoonElapsed=ExorcistRemaining=0;
    CoinverterStrokes=0;
    ShieldDraws=0;
}

bool URecoveredSuccuEconomy::HasModifier(uint8 Modifier) const { return OwnedModifiers.Contains(Modifier); }

bool URecoveredSuccuEconomy::AddSuccuCoins(int32 Amount) {
    const int64 Updated=static_cast<int64>(SuccuCoins)+Amount;
    if (Amount<0 || Updated>MAX_int32) { LastError=TEXT("Invalid SuccuCoin reward."); return false; }
    SuccuCoins=static_cast<int32>(Updated);
    return true;
}

bool URecoveredSuccuEconomy::Purchase(uint8 Modifier) {
    LastError.Empty();
    const auto Catalog=GetCatalog();
    const auto* Entry=Catalog.FindByPredicate([Modifier](const auto& Row) { return Row.Modifier==Modifier; });
    if (!Entry) { LastError=TEXT("Unknown Succu shop modifier."); return false; }
    if (HasModifier(Modifier)) { LastError=TEXT("Modifier already owned for this run."); return false; }
    if (SuccuCoins<Entry->Cost) { LastError=TEXT("Insufficient SuccuCoins."); return false; }
    SuccuCoins-=Entry->Cost;
    OwnedModifiers.Add(Modifier);
    if (Manager) {
        URecoveredStateRuleLibrary::RecordSessionMetric(Manager->SessionStats,ERecoveredMetric::SuccuCoinsSpent,Entry->Cost);
        Manager->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::SuccuCoinsSpent,Entry->Cost);
        Manager->CreateRecoveredNotification(TEXT("SuccuShop"),Entry->Title,Entry->Description);
    }
    return true;
}

double URecoveredSuccuEconomy::AdjustHeatGain(double Amount) const { return HasModifier(2) ? Amount*.5 : Amount; }
double URecoveredSuccuEconomy::GetHeatCap() const { return HasModifier(0) ? 75 : 100; }
double URecoveredSuccuEconomy::GetSuccubusStrokeMultiplier() const { return HasModifier(7) ? .5 : 1; }
int32 URecoveredSuccuEconomy::AdjustLootCoinReward(int32 Amount) const { return static_cast<int32>(FMath::Min<int64>(MAX_int32,static_cast<int64>(Amount)*(HasModifier(1) ? 5 : 1))); }
int32 URecoveredSuccuEconomy::AdjustSuccubusCoinReward(int32 Amount) {
    int64 Result=Amount;
    if (HasModifier(3) && Random.FRand()<.5f) Result*=2;
    if (HasModifier(12)) Result*=3;
    return static_cast<int32>(FMath::Clamp<int64>(Result,0,MAX_int32));
}
bool URecoveredSuccuEconomy::RollRecycler() { return HasModifier(17) && Random.FRand()<.25f; }
bool URecoveredSuccuEconomy::RollBankingError() { return HasModifier(11) && Random.FRand()<.2f; }
bool URecoveredSuccuEconomy::IsSuccubusOnCooldown() const { return HasModifier(10) && ExorcistRemaining>0; }

void URecoveredSuccuEconomy::HandleMetric(ERecoveredMetric Metric,int32 Amount) {
    if (!Manager || Amount<=0) return;
    if (Metric==ERecoveredMetric::Strokes) {
        if (HasModifier(20)) {
            const int64 Total=static_cast<int64>(CoinverterStrokes)+Amount;
            AddSuccuCoins(static_cast<int32>(Total/300));
            CoinverterStrokes=static_cast<int32>(Total%300);
        }
        if (HasModifier(21) && Manager->BeatContext.CardType==3) Manager->AddHeat(-.25*Amount);
    } else if (Metric==ERecoveredMetric::DefensiveItemsUsed && HasModifier(4)) Manager->HeatLevel=FMath::Clamp(Manager->HeatLevel-10,0.0,100.0);
    else if (Metric==ERecoveredMetric::SuccubiDefeated) {
        AddSuccuCoins(AdjustSuccubusCoinReward(Amount));
        if (HasModifier(10)) ExorcistRemaining=30;
        if (HasModifier(18)) {
            if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
                TArray<ERecoveredShopItemType> Eligible;
                static constexpr int32 TableCaps[]={0,3,0,3,2,5,15,1,0,3,1,2,2,2};
                for (const auto Type:Inventory->HotbarItems) {
                    const int32 Index=static_cast<uint8>(Type);
                    if (Index<UE_ARRAY_COUNT(TableCaps) && TableCaps[Index]>0 && Inventory->GetItemState(Type).Charges<TableCaps[Index]+(HasModifier(13) ? 1 : 0)) Eligible.Add(Type);
                }
                if (!Eligible.IsEmpty()) Manager->AcquireStoreItem(RecoveredNewerInventoryAdapter::ResolveID(Eligible[Random.RandRange(0,Eligible.Num()-1)]));
                else {
                    Manager->PlayerVariables.PlayerCoins=URecoveredStateRuleLibrary::AddInt32Wrapping(Manager->PlayerVariables.PlayerCoins,75);
                    Manager->OnCoinsAdded.Broadcast(75,Manager->PlayerVariables.PlayerCoins);
                }
            }
        }
    }
}

void URecoveredSuccuEconomy::HandleAction(FName Action) {
    if (Manager && Action==TEXT("CreateLootRewardWidget") && HasModifier(16)) Manager->HeatLevel=FMath::Clamp(Manager->HeatLevel-2,0.0,GetHeatCap());
    if (!Manager) return;
    if (Action.ToString().StartsWith(TEXT("InventoryUsed_")) && Action!=TEXT("InventoryUsed_DecreaseHeat") && Manager->BeatContext.ActiveModifiers.Contains(TEXT("Hot Hands"))) Manager->HeatLevel=FMath::Clamp(Manager->HeatLevel+10,0.0,GetHeatCap());
    if (Action==TEXT("SuccubusCardStarted") && Manager->BeatContext.ActiveModifiers.Contains(TEXT("Those Are Mine"))) {
        if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
            for (const auto Type:Inventory->HotbarItems) {
                if (auto* State=Inventory->OwnedItems.Find(Type)) {
                    State->Charges=0;
                    Manager->OwnedItemCounts.Remove(RecoveredNewerInventoryAdapter::ResolveID(Type));
                }
            }
            RecoveredNewerInventoryAdapter::Persist(*Manager);
        }
    }
}

void URecoveredSuccuEconomy::TickComponent(float DeltaTime,ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction) {
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);
    if (!Manager || !FMath::IsFinite(DeltaTime) || DeltaTime<=0) return;
    ExorcistRemaining=FMath::Max(0.0,ExorcistRemaining-DeltaTime);
    if (HasModifier(19)) {
        TycoonElapsed+=DeltaTime;
        const int32 Reward=static_cast<int32>(TycoonElapsed/60);
        if (Reward>0) { AddSuccuCoins(Reward); TycoonElapsed-=60.0*Reward; }
    }
}

void URecoveredSuccuEconomy::EndPlay(const EEndPlayReason::Type Reason) {
    Initialize(nullptr);
    Super::EndPlay(Reason);
}
