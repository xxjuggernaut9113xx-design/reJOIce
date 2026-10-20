#include "RecoveredStoreItem.h"
#include "RecoveredRules.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Blueprint/WidgetTree.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

namespace {
struct FRecoveredStorePricing {
    int32 PurchaseCost;
    int32 UpgradeCost;
};

const FRecoveredStorePricing& GetRecoveredStorePricing(FName ItemID,int32 Level) {
    static constexpr FRecoveredStorePricing CumChance[]={{250,300},{300,350},{400,500},{500,999},{750,0}};
    static constexpr FRecoveredStorePricing BonerPill[]={{100,150},{125,300},{150,450},{175,999},{200,0}};
    static constexpr FRecoveredStorePricing Break[]={{150,200},{200,350},{300,500},{400,999},{600,0}};
    static constexpr FRecoveredStorePricing DecreaseHeat[]={{150,100},{175,300},{175,500},{200,999},{350,0}};
    static constexpr FRecoveredStorePricing Edge[]={{350,150},{200,300},{150,450},{125,750},{75,0}};
    static constexpr FRecoveredStorePricing Slowdown[]={{100,150},{150,300},{150,500},{175,750},{175,0}};
    static constexpr FRecoveredStorePricing SuccuShield[]={{75,100},{125,200},{175,350},{300,600},{400,0}};
    static constexpr FRecoveredStorePricing Resupply={350,20};
    static constexpr FRecoveredStorePricing Fallback={0,0};
    const int32 Index=FMath::Clamp(Level,0,4);
    if (ItemID==TEXT("XCumChance")) return CumChance[Index];
    if (ItemID==TEXT("BonerPill")) return BonerPill[Index];
    if (ItemID==TEXT("Break")) return Break[Index];
    if (ItemID==TEXT("DecreaseHeat")) return DecreaseHeat[Index];
    if (ItemID==TEXT("Edge")) return Edge[Index];
    if (ItemID==TEXT("Resupply")) return Resupply;
    if (ItemID==TEXT("Slowdown")) return Slowdown[Index];
    if (ItemID==TEXT("SuccuShield")) return SuccuShield[Index];
    return Fallback;
}

ARecoveredGlobalManager* GetRecoveredStoreManager(const UUserWidget* Widget) {
    if (!Widget || !Widget->GetWorld()) return nullptr;
    if (auto* Manager=Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(Widget))) return Manager;
    for (TActorIterator<ARecoveredGlobalManager> It(Widget->GetWorld());It;++It) return *It;
    return nullptr;
}
}

void URecoveredStoreItemWidget::BindControls(bool bBind) {
#define BIND_CLICK(Name, Method) \
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredStoreItemWidget::Method); \
        else Button->OnClicked.RemoveDynamic(this,&URecoveredStoreItemWidget::Method); \
    }
#define BIND_HOVER(Name, Method, Delegate) \
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->Delegate.AddUniqueDynamic(this,&URecoveredStoreItemWidget::Method); \
        else Button->Delegate.RemoveDynamic(this,&URecoveredStoreItemWidget::Method); \
    }
    BIND_CLICK("BuyButton",OnBuyClicked)
    BIND_CLICK("UpgradeButton",OnUpgradeClicked)
    BIND_CLICK("UseButton",OnUseClicked)
    BIND_CLICK("EquipButton",OnEquipClicked)
    BIND_HOVER("BuyButton",OnBuyHovered,OnHovered)
    BIND_HOVER("BuyButton",OnBuyUnhovered,OnUnhovered)
    BIND_HOVER("UpgradeButton",OnUpgradeHovered,OnHovered)
    BIND_HOVER("UpgradeButton",OnUpgradeUnhovered,OnUnhovered)
#undef BIND_HOVER
#undef BIND_CLICK
}

TSharedRef<SWidget> URecoveredStoreItemWidget::RebuildWidget() {
    if (WidgetTree && !WidgetTree->RootWidget) {
        auto* Row=WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass());
        WidgetTree->RootWidget=Row;
        for (const TCHAR* Name:{TEXT("TextBlock_92"),TEXT("EffectDescription_1"),TEXT("EffectDescription")}) {
            auto* Label=WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(),FName(Name));
            Label->SetAutoWrapText(true);
            Row->AddChild(Label);
        }
        const TCHAR* Names[]={TEXT("BuyButton"),TEXT("UpgradeButton"),TEXT("UseButton"),TEXT("EquipButton")};
        const TCHAR* Labels[]={TEXT("Buy"),TEXT("Upgrade"),TEXT("Use"),TEXT("Equip")};
        for (int32 Index=0;Index<4;++Index) {
            auto* Button=WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(),FName(Names[Index]));
            auto* Text=WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(),Index==0 ? FName(TEXT("TextBlock_371")) : Index==1 ? FName(TEXT("TextBlock_506")) : NAME_None);
            Text->SetText(FText::FromString(Labels[Index]));
            Button->AddChild(Text);
            Row->AddChild(Button);
        }
    }
    return Super::RebuildWidget();
}

void URecoveredStoreItemWidget::NativeConstruct() {
    Super::NativeConstruct();
    EnsureItemID();
    BindControls(true);
    CurrentLevel=FMath::Clamp(ReadLevelFromSave(),0,MaxLevel);
    if (auto* Manager=GetRecoveredStoreManager(this)) Manager->SetRecoveredItemUpgradeLevel(ItemID,CurrentLevel);
    RefreshPrices();
}

void URecoveredStoreItemWidget::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

FString URecoveredStoreItemWidget::LevelSettingName() const {
    return TEXT("StoreItemLevel_")+ItemID.ToString();
}

int32 URecoveredStoreItemWidget::ReadLevelFromSave() const {
    if (const auto* Manager=GetRecoveredStoreManager(this)) {
        if (RecoveredNewerInventoryAdapter::GetInventory(*Manager)) return Manager->GetRecoveredItemUpgradeLevel(ItemID);
    }
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    return Instance && Instance->CurrentSave ? static_cast<int32>(Instance->CurrentSave->GetNumberSetting(LevelSettingName(),0)) : 0;
}

void URecoveredStoreItemWidget::WriteLevelToSave(int32 Level) const {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetNumberSetting(LevelSettingName(),Level)) Instance->SaveRecoveredState();
}

void URecoveredStoreItemWidget::EnsureItemID() {
    if (!ItemID.IsNone()) return;
    const FString ClassName=GetClass()->GetName();
    if (ClassName.Contains(TEXT("XCumChance"))) ItemID=TEXT("XCumChance");
    else if (ClassName.Contains(TEXT("BonerPill"))) ItemID=TEXT("BonerPill");
    else if (ClassName.Contains(TEXT("BreakStoreItem"))) ItemID=TEXT("Break");
    else if (ClassName.Contains(TEXT("DecreaseHeat"))) ItemID=TEXT("DecreaseHeat");
    else if (ClassName.Contains(TEXT("EdgeStoreItem"))) ItemID=TEXT("Edge");
    else if (ClassName.Contains(TEXT("Resupply"))) ItemID=TEXT("Resupply");
    else if (ClassName.Contains(TEXT("Slowdown"))) ItemID=TEXT("Slowdown");
    else if (ClassName.Contains(TEXT("SuccuShield"))) ItemID=TEXT("SuccuShield");
}

void URecoveredStoreItemWidget::SetSourceText(FName WidgetName,const FText& Value) const {
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(WidgetName))) Text->SetText(Value);
}

void URecoveredStoreItemWidget::PlaySourceAnimation(FName Name) {
    PlayRecoveredAnimation(Name);
}

int32 URecoveredStoreItemWidget::GetBuyAmount() const {
    if (const auto* Manager=GetRecoveredStoreManager(this)) {
        int32 Buy=0,Upgrade=0;
        if (RecoveredNewerInventoryAdapter::GetInventory(*Manager) && RecoveredNewerInventoryAdapter::GetPricing(ItemID,CurrentLevel,Buy,Upgrade)) return Buy;
    }
    return GetRecoveredStorePricing(ItemID,CurrentLevel).PurchaseCost;
}

int32 URecoveredStoreItemWidget::GetUpgradeAmount() const {
    if (const auto* Manager=GetRecoveredStoreManager(this)) {
        int32 Buy=0,Upgrade=0;
        if (RecoveredNewerInventoryAdapter::GetInventory(*Manager) && RecoveredNewerInventoryAdapter::GetPricing(ItemID,CurrentLevel,Buy,Upgrade)) return Upgrade;
    }
    return GetRecoveredStorePricing(ItemID,CurrentLevel).UpgradeCost;
}

FText URecoveredStoreItemWidget::GetBuyText() const {
    return FText::FromString(FString::Printf(TEXT("Buy: %d"),GetBuyAmount()));
}

FText URecoveredStoreItemWidget::GetUpgradeText() const {
    if (ItemID!=TEXT("Resupply") && CurrentLevel>=MaxLevel) return FText::FromString(TEXT("Max Level"));
    return FText::FromString(FString::Printf(TEXT("Upgrade: %d"),GetUpgradeAmount()));
}

FText URecoveredStoreItemWidget::GetLevelText() const {
    int32 Level=CurrentLevel;
    const auto* SourceManager=GetRecoveredStoreManager(this);
    if (ItemID==TEXT("Resupply") && (!SourceManager || !RecoveredNewerInventoryAdapter::GetInventory(*SourceManager))) {
        if (const auto* Manager=GetRecoveredStoreManager(this)) Level=Manager->GetRecoveredItemUpgradeLevel(TEXT("BonerPill"));
    }
    return FText::FromString(FString::Printf(TEXT("Level %d"),FMath::Clamp(Level,0,4)+1));
}

FText URecoveredStoreItemWidget::GetTitleText() const {
    if (const auto* Manager=GetRecoveredStoreManager(this)) if (RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
        FString Title,Description;
        if (RecoveredNewerInventoryAdapter::GetPresentation(ItemID,CurrentLevel,Title,Description)) return FText::FromString(Title);
    }
    const int32 Level=FMath::Clamp(CurrentLevel,0,4);
    if (ItemID==TEXT("XCumChance")) {
        static constexpr int32 Amounts[]={5,8,12,18,35};
        return FText::FromString(FString::Printf(TEXT("+%d%% Cum Meter"),Amounts[Level]));
    }
    if (ItemID==TEXT("SuccuShield")) {
        static constexpr int32 Amounts[]={1,4,7,10,15};
        return FText::FromString(FString::Printf(TEXT("+%d Succushield%s"),Amounts[Level],Amounts[Level]==1?TEXT(""):TEXT("s")));
    }
    if (ItemID==TEXT("BonerPill")) return FText::FromString(TEXT("boner pill"));
    if (ItemID==TEXT("Break")) return FText::FromString(TEXT("break"));
    if (ItemID==TEXT("DecreaseHeat")) return FText::FromString(TEXT("Decrease Heat"));
    if (ItemID==TEXT("Edge")) return FText::FromString(TEXT("Edge"));
    if (ItemID==TEXT("Resupply")) return FText::FromString(TEXT("resupply"));
    if (ItemID==TEXT("Slowdown")) return FText::FromString(TEXT("Slowdown"));
    if (ItemID==TEXT("ApexLure")) return FText::FromString(TEXT("Apex Lure"));
    if (ItemID==TEXT("LootRush")) return FText::FromString(TEXT("Loot Rush"));
    if (ItemID==TEXT("Bounty")) return FText::FromString(TEXT("Bounty"));
    if (ItemID==TEXT("EscapeRope")) return FText::FromString(TEXT("Escape Rope"));
    if (ItemID==TEXT("ComboCruncher")) return FText::FromString(TEXT("Combo Cruncher"));
    return FText::GetEmpty();
}

FText URecoveredStoreItemWidget::GetEffectDescription() const {
    if (const auto* Manager=GetRecoveredStoreManager(this)) if (RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
        FString Title,Description;
        if (RecoveredNewerInventoryAdapter::GetPresentation(ItemID,CurrentLevel,Title,Description)) return FText::FromString(Description);
    }
    const int32 Level=FMath::Clamp(CurrentLevel,0,4);
    if (ItemID==TEXT("XCumChance")) {
        static constexpr int32 Amounts[]={5,8,12,18,35};
        return FText::FromString(FString::Printf(TEXT("Increases Cum Meter by %d%%\r\nUse When Ready to Cum"),Amounts[Level]));
    }
    if (ItemID==TEXT("BonerPill")) {
        static const TCHAR* Descriptions[]={
            TEXT("x2.0 Stroking | x2.0 Speed | \r\nx2.0 Coins | Use to Boost Rewards"),
            TEXT("x2.0 Stroking | x2.0 Speed | \r\nx2.0 Coins | Use to Boost Rewards"),
            TEXT("x3.0 Stroking | x3.0 Speed | \r\nx2.0 Coins | Use to Boost Rewards"),
            TEXT("x4.0 Stroking | x5.0 Speed | \r\nx3.0 Coins | Use to Boost Rewards"),
            TEXT("x6.0 Stroking | x6.0 Speed | \r\nx3.0 Coins | Use to Boost Rewards")
        };
        return FText::FromString(Descriptions[Level]);
    }
    if (ItemID==TEXT("Break")) {
        static constexpr int32 Durations[]={5,10,15,25,50};
        return FText::FromString(FString::Printf(TEXT("grants a %d second break\r\nstops stroking"),Durations[Level]));
    }
    if (ItemID==TEXT("DecreaseHeat")) {
        static constexpr int32 Amounts[]={15,25,35,45,60};
        return FText::FromString(FString::Printf(TEXT("Decreases heat by %d%%\r\nUse to manage difficulty"),Amounts[Level]));
    }
    if (ItemID==TEXT("Edge")) return FText::FromString(TEXT("INCREASES PERFECT EDGE \r\nWindow = LAST 15% OF TASK"));
    if (ItemID==TEXT("Resupply")) return FText::FromString(TEXT("SPAWNS A STORE EVENT\r\nCHOOSE FROM POWERFUL ITEMS"));
    if (ItemID==TEXT("Slowdown")) return FText::FromString(FString::Printf(TEXT("Slows down stroking by x%d\r\n(Affects Remaining Strokes)"),Level+2));
    if (ItemID==TEXT("SuccuShield")) return FText::FromString(TEXT("prevents succubi from \r\nspawning (toggle on/off)"));
    return FText::GetEmpty();
}

void URecoveredStoreItemWidget::RefreshPrices() {
    EnsureItemID();
    if (const auto* Manager=GetRecoveredStoreManager(this)) CurrentLevel=Manager->GetRecoveredItemUpgradeLevel(ItemID);
    CurrentLevel=FMath::Clamp(CurrentLevel,0,MaxLevel);
    const FRecoveredStorePricing& Pricing=GetRecoveredStorePricing(ItemID,CurrentLevel);
    PurchaseCost=Pricing.PurchaseCost;
    UpgradeCost=Pricing.UpgradeCost;
    if (const auto* Manager=GetRecoveredStoreManager(this)) {
        if (RecoveredNewerInventoryAdapter::GetInventory(*Manager)) RecoveredNewerInventoryAdapter::GetPricing(ItemID,CurrentLevel,PurchaseCost,UpgradeCost);
    }
    SetSourceText(TEXT("TextBlock_371"),GetBuyText());
    SetSourceText(TEXT("TextBlock_506"),GetUpgradeText());
    SetSourceText(TEXT("EffectDescription"),GetEffectDescription());
    SetSourceText(TEXT("EffectDescription_1"),GetLevelText());
    SetSourceText(TEXT("TextBlock_92"),GetTitleText());
}

bool URecoveredStoreItemWidget::TryBuy() {
    EnsureItemID();
    RefreshPrices();
    auto* Manager=GetRecoveredStoreManager(this);
    if (Manager) {
        if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
            ERecoveredShopItemType Type;
            if (!RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) {
                PlaySourceAnimation(TEXT("BuyClickFailure"));
                return false;
            }
        }
    }
    const bool bAtMaximum=Manager && Manager->GetRecoveredItemMaximum(ItemID)>0 && Manager->GetOwnedItemCount(ItemID)>=Manager->GetRecoveredItemMaximum(ItemID);
    int32 VerifiedBuy=0,VerifiedUpgrade=0;
    const bool bVerifiedFreePurchase=Manager && RecoveredNewerInventoryAdapter::GetInventory(*Manager) && RecoveredNewerInventoryAdapter::GetPricing(ItemID,CurrentLevel,VerifiedBuy,VerifiedUpgrade) && VerifiedBuy==0;
    if (!Manager || bAtMaximum || PurchaseCost<0 || (PurchaseCost==0 && !bVerifiedFreePurchase) || Manager->PlayerVariables.PlayerCoins<PurchaseCost) {
        PlaySourceAnimation(TEXT("BuyClickFailure"));
        return false;
    }
    Manager->PlayerVariables.PlayerCoins-=PurchaseCost;
    Manager->AddToPointsSpent(PurchaseCost);
    if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
        ERecoveredShopItemType Type;
        if (RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type)) {
            const auto* State=Inventory->OwnedItems.Find(Type);
            if (!State || !State->bIsUnlocked) Inventory->UnlockItem(Type);
        }
    }
    Manager->AcquireStoreItem(ItemID);
    RecoveredNewerInventoryAdapter::Persist(*Manager);
    RefreshPrices();
    PlaySourceAnimation(TEXT("BuyClickSuccessful"));
    return true;
}

bool URecoveredStoreItemWidget::TryUse() {
    auto* Manager=GetRecoveredStoreManager(this);
    if (!Manager || !Manager->UseOwnedItem(ItemID,CurrentLevel)) return false;
    RefreshPrices();
    return true;
}

bool URecoveredStoreItemWidget::TryUpgrade() {
    EnsureItemID();
    RefreshPrices();
    auto* Manager=GetRecoveredStoreManager(this);
    if (Manager) if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
        ERecoveredShopItemType Type;
        const bool Known=RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type);
        const auto* State=Known ? Inventory->OwnedItems.Find(Type) : nullptr;
        if (!State || !State->bIsUnlocked) {
            PlaySourceAnimation(TEXT("UpgradeClickFailure"));
            return false;
        }
    }
    if (!Manager || CurrentLevel>=MaxLevel || UpgradeCost<=0 || Manager->PlayerVariables.PlayerCoins<UpgradeCost) {
        PlaySourceAnimation(TEXT("UpgradeClickFailure"));
        return false;
    }
    Manager->PlayerVariables.PlayerCoins-=UpgradeCost;
    Manager->AddToPointsSpent(UpgradeCost);
    CurrentLevel=FMath::Clamp(CurrentLevel+1,0,MaxLevel);
    Manager->SetRecoveredItemUpgradeLevel(ItemID,CurrentLevel);
    WriteLevelToSave(CurrentLevel);
    RefreshPrices();
    PlaySourceAnimation(TEXT("UpgradeClickSuccessful"));
    return true;
}

void URecoveredStoreItemWidget::OnBuyClicked() { TryBuy(); }
void URecoveredStoreItemWidget::OnUpgradeClicked() { TryUpgrade(); }
void URecoveredStoreItemWidget::OnUseClicked() { TryUse(); }
bool URecoveredStoreItemWidget::TryEquip(int32 SlotIndex) {
    auto* Manager=GetRecoveredStoreManager(this);
    if (!Manager) return false;
    auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager);
    ERecoveredShopItemType Type;
    if (!Inventory || SlotIndex<0 || SlotIndex>=5 || !RecoveredNewerInventoryAdapter::ResolveType(ItemID,Type) || !Inventory->EquipToSlot(Type,SlotIndex)) return false;
    RecoveredNewerInventoryAdapter::Persist(*Manager);
    return true;
}
bool URecoveredStoreItemWidget::TryUnequip(int32 SlotIndex) {
    auto* Manager=GetRecoveredStoreManager(this);
    if (!Manager) return false;
    auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager);
    if (!Inventory || SlotIndex<0 || SlotIndex>=5 || !Inventory->UnEquipSlot(SlotIndex)) return false;
    RecoveredNewerInventoryAdapter::Persist(*Manager);
    return true;
}
void URecoveredStoreItemWidget::OnEquipClicked() {
    if (auto* Manager=GetRecoveredStoreManager(this)) {
        if (auto* Inventory=RecoveredNewerInventoryAdapter::GetInventory(*Manager)) {
            for (int32 Index=0;Index<Inventory->HotbarItems.Num();++Index) if (Inventory->HotbarItems[Index]==ERecoveredShopItemType::None) { TryEquip(Index); return; }
            TryEquip(0);
        }
    }
}
void URecoveredStoreItemWidget::OnBuyHovered() { PlaySourceAnimation(TEXT("BuyHover")); }
void URecoveredStoreItemWidget::OnBuyUnhovered() { PlaySourceAnimation(TEXT("BuyUnhover")); }
void URecoveredStoreItemWidget::OnUpgradeHovered() { PlaySourceAnimation(TEXT("UpgradeHover")); }
void URecoveredStoreItemWidget::OnUpgradeUnhovered() { PlaySourceAnimation(TEXT("UpgradeUnhover")); }
