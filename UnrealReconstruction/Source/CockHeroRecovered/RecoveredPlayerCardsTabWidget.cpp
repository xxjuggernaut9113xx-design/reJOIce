#include "RecoveredPlayerCardsTabWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Misc/PackageName.h"
#include "RecoveredEditUsernameOverlay.h"
#include "RecoveredPlayerCardEntryWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredProgressionResources.h"
#include "RecoveredRules.h"

namespace {

URecoveredGameInstance* GetRecoveredPlayerCardsInstance(const UUserWidget* Widget) {
    if (const auto* Tab=Cast<URecoveredPlayerCardsTabWidget>(Widget)) {
        if (auto* Instance=Tab->GetRecoveredPlayerCardsGameInstance()) return Instance;
    }
    if (auto* Instance=Cast<URecoveredGameInstance>(Widget->GetGameInstance())) return Instance;
    return Widget->GetWorld() ? Cast<URecoveredGameInstance>(Widget->GetWorld()->GetGameInstance()) : nullptr;
}

bool HasNoChallengeGate(const FRecoveredPlayerCardRow& Card) {
    return Card.RequiredChallengeID.IsEmpty() || Card.RequiredChallengeID.Equals(TEXT("none"),ESearchCase::IgnoreCase);
}

UTexture2D* LoadRecoveredCardTexture(const FString& OriginalPath) {
    if (OriginalPath.IsEmpty()) return nullptr;
    const auto LoadExistingTexture=[](const FString& ObjectPath) -> UTexture2D* {
        int32 Dot=INDEX_NONE;
        if (!ObjectPath.FindLastChar(TEXT('.'),Dot) || Dot<1) return nullptr;
        return FPackageName::DoesPackageExist(ObjectPath.Left(Dot)) ? LoadObject<UTexture2D>(nullptr,*ObjectPath) : nullptr;
    };
    const FString Resolved=ResolveRecoveredProgressionResource(OriginalPath);
    if (Resolved!=OriginalPath) return LoadExistingTexture(Resolved);
    if (UTexture2D* Texture=LoadExistingTexture(OriginalPath)) return Texture;
    FString AssetName=OriginalPath;
    int32 Dot=INDEX_NONE;
    if (AssetName.FindLastChar(TEXT('.'),Dot)) AssetName=AssetName.Mid(Dot+1);
    return LoadExistingTexture(FString::Printf(TEXT("/Game/Recovery/Resources/PlayerCards/%s.%s"),*AssetName,*AssetName));
}

bool GetRecoveredChallengeData(const URecoveredProgressionManager* Progression,const FString& ChallengeID,FRecoveredChallengeRow& OutData) {
    OutData=FRecoveredChallengeRow();
    if (!Progression || ChallengeID.IsEmpty() || !Progression->ChallengeDataTable || Progression->ChallengeDataTable->GetRowStruct()!=FRecoveredChallengeRow::StaticStruct()) return false;
    for (const TPair<FName,uint8*>& Pair:Progression->ChallengeDataTable->GetRowMap()) {
        const auto* Row=reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (Row && Row->ChallengeID.Equals(ChallengeID,ESearchCase::IgnoreCase)) {
            OutData=*Row;
            return true;
        }
    }
    return false;
}

}

void URecoveredPlayerCardsTabWidget::NativeConstruct() {
    Super::NativeConstruct();
    InitializePlayerCards();
}

void URecoveredPlayerCardsTabWidget::NativeDestruct() {
    BindControls(false);
    if (ActiveUsernameOverlay) ActiveUsernameOverlay->OnClosed.RemoveDynamic(this,&URecoveredPlayerCardsTabWidget::OnEditBoxClosed);
    ActiveUsernameOverlay=nullptr;
    Super::NativeDestruct();
}

void URecoveredPlayerCardsTabWidget::SetRecoveredPlayerCardsGameInstance(URecoveredGameInstance* Instance) {
    RecoveredInstanceOverride=Instance;
}

URecoveredGameInstance* URecoveredPlayerCardsTabWidget::GetRecoveredPlayerCardsGameInstance() const {
    if (RecoveredInstanceOverride) return RecoveredInstanceOverride;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    return GetWorld() ? Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
}

void URecoveredPlayerCardsTabWidget::BindControls(bool bBind) {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("EditPlayerCardButton")))) {
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredPlayerCardsTabWidget::OpenEditUsernameOverlay);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredPlayerCardsTabWidget::OpenEditUsernameOverlay);
    }
}

void URecoveredPlayerCardsTabWidget::InitializePlayerCards() {
    BindControls(true);
    PopulatePlayerCards();
    if (URecoveredGameInstance* Instance=GetRecoveredPlayerCardsInstance(this)) {
        if (URecoveredProgressionManager* Progression=Instance->ProgressionManager) {
            if (Progression->GetEquippedPlayerCard().IsNone()) {
                const TArray<FName> UnlockedCards=Progression->GetUnlockedPlayerCards();
                if (!UnlockedCards.IsEmpty()) Progression->EquipPlayerCard(UnlockedCards[0]);
            }
        }
    }
    ChangeSelectedPlayerCardDisplay();
    UpdateLevelDisplay();
    UpdatePlayerCardName();
}

void URecoveredPlayerCardsTabWidget::PopulatePlayerCards() {
    RecoveredCardEntries.Reset();
    auto* Grid=Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("PlayerCardUniformGrid")));
    if (!Grid) return;
    Grid->ClearChildren();

    URecoveredGameInstance* Instance=GetRecoveredPlayerCardsInstance(this);
    URecoveredProgressionManager* Progression=Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression) return;

    TArray<FRecoveredPlayerCardRow> Cards;
    Progression->GetAllPlayerCardData(Cards);
    UClass* EntryClass=LoadClass<URecoveredPlayerCardEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/PlayerCardEntryWidget.PlayerCardEntryWidget_C"));
    if (!EntryClass) EntryClass=URecoveredPlayerCardEntryWidget::StaticClass();
    for (int32 Index=0;Index<Cards.Num();++Index) {
        const FRecoveredPlayerCardRow& Card=Cards[Index];
        const FName CardID(*Card.CardID);
        if (CardID.IsNone()) continue;
        if (HasNoChallengeGate(Card)) Progression->UnlockPlayerCard(CardID);

        FRecoveredChallengeRow Challenge;
        GetRecoveredChallengeData(Progression,Card.RequiredChallengeID,Challenge);
        auto* Entry=CreateWidget<URecoveredPlayerCardEntryWidget>(this,EntryClass);
        if (!Entry) continue;
        Entry->PopulatePlayerCard(
            CardID,
            LoadRecoveredCardTexture(Card.CardImage),
            Card.RequiredChallengeID,
            Card.RequiredLevel,
            Progression->IsPlayerCardUnlocked(CardID),
            Challenge.Description,
            Challenge.DisplayName,
            Card.CardName,
            Card.CardColor);
        Entry->OnClicked.AddUniqueDynamic(this,&URecoveredPlayerCardsTabWidget::PlayerCardClick);
        Grid->AddChildToUniformGrid(Entry,Index/3,Index%3);
        RecoveredCardEntries.Add(Entry);
    }
}

void URecoveredPlayerCardsTabWidget::PlayerCardClick(FName CardID) {
    URecoveredGameInstance* Instance=GetRecoveredPlayerCardsInstance(this);
    URecoveredProgressionManager* Progression=Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression || !Progression->IsPlayerCardUnlocked(CardID) || !Progression->EquipPlayerCard(CardID)) return;
    ChangeSelectedPlayerCardDisplay();
    if (UpdateEquippedCard) PlayAnimation(UpdateEquippedCard,0.0f,1,EUMGSequencePlayMode::Forward,1.0f,false);
}

void URecoveredPlayerCardsTabWidget::ChangeSelectedPlayerCardDisplay() {
    URecoveredGameInstance* Instance=GetRecoveredPlayerCardsInstance(this);
    URecoveredProgressionManager* Progression=Instance ? Instance->ProgressionManager.Get() : nullptr;
    auto* Image=Cast<UImage>(GetWidgetFromName(TEXT("SelectedPlayerCard")));
    if (!Image || !Progression) return;
    FRecoveredPlayerCardRow Card;
    if (Progression->GetPlayerCardData(Progression->GetEquippedPlayerCard(),Card)) Image->SetBrushFromTexture(LoadRecoveredCardTexture(Card.CardImage),false);
    else Image->SetBrushFromTexture(nullptr,false);
}

void URecoveredPlayerCardsTabWidget::UpdateLevelDisplay() {
    URecoveredGameInstance* Instance=GetRecoveredPlayerCardsInstance(this);
    URecoveredProgressionManager* Progression=Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression) return;
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TitleLevelText")))) {
        Text->SetText(FText::FromString(FString::Printf(TEXT("Level: %d - %s"),Progression->CurrentLevel,*Progression->GetCurrentPlayerTitle().ToString())));
    }
    if (auto* Meter=Cast<UProgressBar>(GetWidgetFromName(TEXT("LevelMeter")))) {
        Meter->SetPercent(URecoveredProgressionLibrary::CalculateLevelProgress(Progression->CurrentXP,Progression->CurrentLevel));
    }
}

void URecoveredPlayerCardsTabWidget::UpdatePlayerCardName() {
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerCardName")))) {
        URecoveredGameInstance* Instance=GetRecoveredPlayerCardsInstance(this);
        Text->SetText(Instance && Instance->CurrentSave ? Instance->CurrentSave->GetTextSetting(TEXT("Playercard_Name"),FText::GetEmpty()) : FText::GetEmpty());
    }
}

void URecoveredPlayerCardsTabWidget::OpenEditUsernameOverlay() {
    if (ActiveUsernameOverlay) return;
    UClass* OverlayClass=LoadClass<URecoveredEditUsernameOverlay>(nullptr,TEXT("/Game/Recovery/UI/EditUsernameOverlay.EditUsernameOverlay_C"));
    if (!OverlayClass) return;
    ActiveUsernameOverlay=CreateWidget<URecoveredEditUsernameOverlay>(GetWorld(),OverlayClass);
    if (!ActiveUsernameOverlay) return;
    ActiveUsernameOverlay->OnClosed.AddUniqueDynamic(this,&URecoveredPlayerCardsTabWidget::OnEditBoxClosed);
    ActiveUsernameOverlay->AddToViewport(0);
}

void URecoveredPlayerCardsTabWidget::OnEditBoxClosed() {
    UpdatePlayerCardName();
    ActiveUsernameOverlay=nullptr;
}

int32 URecoveredPlayerCardsTabWidget::GetPlayerCardEntryCount() const {
    return RecoveredCardEntries.Num();
}
