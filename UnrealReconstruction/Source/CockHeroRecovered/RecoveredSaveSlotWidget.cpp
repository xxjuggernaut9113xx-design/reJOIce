#include "RecoveredSaveSlotWidget.h"
#include "RecoveredRules.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

namespace {
FString IsolatedSlot(const FString& Name) {
    if (Name.IsEmpty() || Name.Len()>64) return FString();
    for (TCHAR Ch : Name) if (!FChar::IsAlnum(Ch) && Ch!=TEXT('_') && Ch!=TEXT('-')) return FString();
    return TEXT("CockHeroRecovered_Named_") + Name;
}
}

void URecoveredSaveSlotWidget::NativeConstruct() {
    Super::NativeConstruct();
    RefreshSlotList();
}

TArray<FString> URecoveredSaveSlotWidget::GetSaveSlotNames() const {
    TArray<FString> Slots;
    // Save slots are stored as separate save game objects.
    // The reconstruction uses a single active slot; this lists named variants.
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
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance) return false;
    if (UGameplayStatics::DoesSaveGameExist(SafeSlot, 0)) return false;
    // Never overwrite an existing named reconstruction snapshot.
    if (auto* NewSave = Cast<URecoveredSaveGame>(UGameplayStatics::CreateSaveGameObject(URecoveredSaveGame::StaticClass()))) {
        if (!NewSave->InitializeRecoveredDefaults()) return false;
        if (UGameplayStatics::SaveGameToSlot(NewSave, SafeSlot, 0)) {
            RefreshSlotList();
            return true;
        }
    }
    return false;
}

bool URecoveredSaveSlotWidget::LoadSaveSlot(const FString& SlotName) {
    // Incomplete: loading must switch the active persistence target and rehydrate
    // progression, challenges and settings together. Do not replace CurrentSave
    // while saves still target the default slot.
    return false;
}

bool URecoveredSaveSlotWidget::DeleteSaveSlot(const FString& SlotName) {
    const FString SafeSlot=IsolatedSlot(SlotName);
    if (SafeSlot.IsEmpty()) return false;
    if (UGameplayStatics::DeleteGameInSlot(SafeSlot, 0)) {
        RefreshSlotList();
        return true;
    }
    return false;
}
