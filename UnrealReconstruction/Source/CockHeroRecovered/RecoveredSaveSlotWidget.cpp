#include "RecoveredSaveSlotWidget.h"
#include "RecoveredRules.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

namespace {
FString IsolatedSlot(const FString& Name) {
    const FString Slot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+Name;
    return URecoveredGameInstance::IsRecoverySlotNameValid(Slot) ? Slot : FString();
}

bool ContainsSlot(const TArray<FString>& Slots,const FString& SlotName) {
    return Slots.ContainsByPredicate([&SlotName](const FString& Candidate) {
        return Candidate.Equals(SlotName,ESearchCase::IgnoreCase);
    });
}

void RemoveUnavailableSlots(TArray<FString>& Slots) {
    Slots.RemoveAll([](const FString& SlotName) {
        return !UGameplayStatics::DoesSaveGameExist(SlotName,0);
    });
}
}

void URecoveredSaveSlotWidget::NativeConstruct() {
    Super::NativeConstruct();
    RefreshSlotList();
}

TArray<FString> URecoveredSaveSlotWidget::GetSaveSlotNames() const {
    TArray<FString> Slots;
    TArray<FString> StoredSlots;
    FString ActiveSlot;
    if (!URecoveredGameInstance::ReadRecoverySlotIndex(StoredSlots,ActiveSlot,URecoveredGameInstance::GetRecoverySlotIndexName())) return Slots;
    const FString Prefix=URecoveredGameInstance::GetNamedRecoverySlotPrefix();
    for (const FString& StoredSlot:StoredSlots) {
        if (!UGameplayStatics::DoesSaveGameExist(StoredSlot,0)) continue;
        Slots.Add(StoredSlot.RightChop(Prefix.Len()));
    }
    Slots.Sort();
    return Slots;
}

void URecoveredSaveSlotWidget::RefreshSlotList() {
    auto* Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("SaveSlotContainer")));
    if (!Container) return;
    Container->ClearChildren();
    for (const FString& SlotName : GetSaveSlotNames()) {
        auto* Row = NewObject<UHorizontalBox>(this);
        auto* Label = NewObject<UTextBlock>(this);
        Label->SetText(FText::FromString(SlotName));
        Row->AddChildToHorizontalBox(Label);
        Container->AddChild(Row);
    }
}

bool URecoveredSaveSlotWidget::CreateSaveSlot(const FString& SlotName) {
    const FString SafeSlot=IsolatedSlot(SlotName);
    if (SafeSlot.IsEmpty()) return false;
    TArray<FString> StoredSlots;
    FString ActiveSlot;
    if (!URecoveredGameInstance::ReadRecoverySlotIndex(StoredSlots,ActiveSlot,URecoveredGameInstance::GetRecoverySlotIndexName())) return false;
    RemoveUnavailableSlots(StoredSlots);
    if (ContainsSlot(StoredSlots,SafeSlot) || UGameplayStatics::DoesSaveGameExist(SafeSlot,0)) return false;
    if (auto* NewSave = Cast<URecoveredSaveGame>(UGameplayStatics::CreateSaveGameObject(URecoveredSaveGame::StaticClass()))) {
        if (!NewSave->InitializeRecoveredDefaults()) return false;
        if (UGameplayStatics::SaveGameToSlot(NewSave, SafeSlot, 0)) {
            StoredSlots.Add(SafeSlot);
            if (ActiveSlot!=URecoveredGameInstance::GetDefaultRecoverySlotName() && !UGameplayStatics::DoesSaveGameExist(ActiveSlot,0)) {
                ActiveSlot=URecoveredGameInstance::GetDefaultRecoverySlotName();
            }
            if (URecoveredGameInstance::WriteRecoverySlotIndex(StoredSlots,ActiveSlot,URecoveredGameInstance::GetRecoverySlotIndexName())) {
                RefreshSlotList();
                return true;
            }
            UGameplayStatics::DeleteGameInSlot(SafeSlot,0);
        }
    }
    return false;
}

bool URecoveredSaveSlotWidget::LoadSaveSlot(const FString& SlotName) {
    const FString SafeSlot=IsolatedSlot(SlotName);
    if (SafeSlot.IsEmpty()) return false;
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !UGameplayStatics::DoesSaveGameExist(SafeSlot,0)) return false;
    if (!Instance->LoadRecoveredSaveSlot(SafeSlot)) return false;
    RefreshSlotList();
    return true;
}

bool URecoveredSaveSlotWidget::DeleteSaveSlot(const FString& SlotName) {
    const FString SafeSlot=IsolatedSlot(SlotName);
    if (SafeSlot.IsEmpty()) return false;
    TArray<FString> StoredSlots;
    FString ActiveSlot;
    if (!URecoveredGameInstance::ReadRecoverySlotIndex(StoredSlots,ActiveSlot,URecoveredGameInstance::GetRecoverySlotIndexName())) return false;
    if (!ContainsSlot(StoredSlots,SafeSlot) || ActiveSlot.Equals(SafeSlot,ESearchCase::IgnoreCase)) return false;
    if (UGameplayStatics::DeleteGameInSlot(SafeSlot, 0)) {
        StoredSlots.RemoveAll([&SafeSlot](const FString& Candidate) {
            return Candidate.Equals(SafeSlot,ESearchCase::IgnoreCase);
        });
        URecoveredGameInstance::WriteRecoverySlotIndex(StoredSlots,ActiveSlot,URecoveredGameInstance::GetRecoverySlotIndexName());
        RefreshSlotList();
        return true;
    }
    return false;
}
