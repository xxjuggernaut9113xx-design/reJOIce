#include "RecoveredModifierWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"

namespace {
void SetEntryText(UUserWidget* Entry, const TCHAR* Name, const FText& Value) {
    if (auto* Text = Entry ? Cast<UTextBlock>(Entry->GetWidgetFromName(Name)) : nullptr) Text->SetText(Value);
}

UButton* FindEntryButton(UUserWidget* Entry, const TCHAR* Name) {
    return Entry ? Cast<UButton>(Entry->GetWidgetFromName(Name)) : nullptr;
}
}

void URecoveredModifierWidget::NativeConstruct() {
    Super::NativeConstruct();
    RefreshModifierList();
}

void URecoveredModifierWidget::RefreshModifierList() {
    auto* Container = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel_94")));
    if (!Container) return;
    Container->ClearChildren();
    ToggleForwarders.Reset();
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression || !Progression->ModifierDataTable || Progression->ModifierDataTable->GetRowStruct() != FRecoveredModifierRow::StaticStruct()) return;
    UClass* EntryClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Recovery/UI/ModifierCardEntryWidget.ModifierCardEntryWidget_C"));
    TArray<FName> IDs;
    Progression->ModifierDataTable->GetRowMap().GetKeys(IDs);
    IDs.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });
    int32 Index = 0;
    for (const FName ModifierID : IDs) {
        FRecoveredModifierRow Row;
        if (!Progression->GetModifierData(ModifierID, Row)) continue;
        UUserWidget* Entry = EntryClass && GetWorld() ? CreateWidget<UUserWidget>(GetWorld(), EntryClass) : nullptr;
        if (!Entry) {
            auto* Fallback = NewObject<UHorizontalBox>(this);
            auto* Title = NewObject<UTextBlock>(this);
            auto* Toggle = NewObject<UButton>(this);
            auto* ToggleText = NewObject<UTextBlock>(this);
            Title->SetText(Row.ModifierTitle);
            Toggle->SetContent(ToggleText);
            Fallback->AddChildToHorizontalBox(Title);
            Fallback->AddChildToHorizontalBox(Toggle);
            Container->AddChildToUniformGrid(Fallback, Index / 2, Index % 2);
            ++Index;
            continue;
        }
        const bool bEnabled = Progression->EnabledModifiers.Contains(ModifierID);
        const bool bUnlocked = Progression->IsModifierUnlocked(ModifierID);
        const bool bCanEnable = Progression->CanEnableModifier(ModifierID);
        SetEntryText(Entry, TEXT("ModifierTitle"), Row.ModifierTitle);
        SetEntryText(Entry, TEXT("ModifierDescription"), Row.ModifierDescription);
        SetEntryText(Entry, TEXT("ChallengeRequiredText"), bUnlocked ? FText::GetEmpty() : FText::FromString(TEXT("Complete the linked challenge to unlock")));
        SetEntryText(Entry, TEXT("ButtonText"), FText::FromString(bEnabled ? TEXT("Enabled") : bUnlocked ? TEXT("Enable") : TEXT("Locked")));
        if (auto* Icon = Cast<UImage>(Entry->GetWidgetFromName(TEXT("ModifierIcon")))) Icon->SetBrushFromTexture(Row.ModifierIcon);
        if (auto* Lock = Entry->GetWidgetFromName(TEXT("LockOverlay"))) Lock->SetVisibility(bUnlocked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
        for (const TCHAR* ButtonName : {TEXT("ToggleModifierButton"), TEXT("BackgroundButton")}) {
            if (UButton* Button = FindEntryButton(Entry, ButtonName)) {
                Button->SetIsEnabled(bEnabled || (bUnlocked && bCanEnable));
                auto* Forward = NewObject<URecoveredModifierToggleForward>(this);
                Forward->Owner = this;
                Forward->ModifierID = ModifierID;
                Button->OnClicked.AddUniqueDynamic(Forward, &URecoveredModifierToggleForward::Toggle);
                ToggleForwarders.Add(Forward);
            }
        }
        Container->AddChildToUniformGrid(Entry, Index / 2, Index % 2);
        ++Index;
    }
}

bool URecoveredModifierWidget::ToggleModifier(FName ModifierID) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression) return false;
    if (Progression->EnabledModifiers.Contains(ModifierID)) {
        Progression->EnabledModifiers.Remove(ModifierID);
    } else {
        if (!Progression->CanEnableModifier(ModifierID)) return false;
        // The original tab queries conflicts before enabling a modifier.  The
        // reconstructed manager supplies the same explicit conflict list.
        for (const FName Conflict : Progression->GetConflictingModifiers(ModifierID)) Progression->EnabledModifiers.Remove(Conflict);
        Progression->EnabledModifiers.Add(ModifierID);
    }
    // Persist the enabled set.
    if (Instance->CurrentSave) {
        TArray<FString> Enabled;
        for (FName M : Progression->EnabledModifiers) Enabled.Add(M.ToString());
        if (Instance->CurrentSave->SetStringArraySetting(TEXT("EnabledModifiers"), Enabled)
            && Instance->CurrentSave->SetStringArraySetting(TEXT("ActiveModifiers"), Enabled)) {
            Instance->SaveRecoveredState();
        }
    }
    if (auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr) {
        Manager->BeatContext.ActiveModifiers.Reset();
        for (const FName Enabled : Progression->EnabledModifiers) Manager->BeatContext.ActiveModifiers.Add(Enabled.ToString());
    }
    RefreshModifierList();
    return true;
}

void URecoveredModifierToggleForward::Toggle() {
    if (Owner) Owner->ToggleModifier(ModifierID);
}
