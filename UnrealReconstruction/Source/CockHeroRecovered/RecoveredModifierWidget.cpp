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
    int32 Index = 0;
    for (const FName RowID : IDs) {
        const auto* SourceRow = reinterpret_cast<const FRecoveredModifierRow*>(Progression->ModifierDataTable->GetRowMap().FindRef(RowID));
        if (!SourceRow) continue;
        const FName ModifierID = Progression->GetCanonicalModifierID(FName(*SourceRow->ModifierTitle.ToString()));
        if (ModifierID.IsNone()) continue;
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
            Container->AddChildToUniformGrid(Fallback, Index / 4, Index % 4);
            ++Index;
            continue;
        }
        const bool bEnabled = Progression->EnabledModifiers.Contains(ModifierID);
        const bool bUnlocked = Progression->IsModifierUnlocked(ModifierID);
        SetEntryText(Entry, TEXT("ModifierTitle"), Row.ModifierTitle);
        SetEntryText(Entry, TEXT("ModifierDescription"), Row.ModifierDescription);
        SetEntryText(Entry, TEXT("ChallengeRequiredText"), bUnlocked ? FText::GetEmpty() : FText::FromString(TEXT("Complete the linked challenge to unlock")));
        SetEntryText(Entry, TEXT("ButtonText"), FText::FromString(bEnabled ? TEXT("Enabled") : TEXT("Disabled")));
        if (auto* Icon = Cast<UImage>(Entry->GetWidgetFromName(TEXT("ModifierIcon")))) Icon->SetBrushFromTexture(Row.ModifierIcon);
        if (auto* Lock = Entry->GetWidgetFromName(TEXT("LockOverlay"))) Lock->SetVisibility(bUnlocked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
        for (const TCHAR* ButtonName : {TEXT("ToggleModifierButton"), TEXT("BackgroundButton")}) {
            if (UButton* Button = FindEntryButton(Entry, ButtonName)) {
                Button->SetIsEnabled(bEnabled || bUnlocked);
                auto* Forward = NewObject<URecoveredModifierToggleForward>(this);
                Forward->Owner = this;
                Forward->ModifierID = ModifierID;
                Button->OnClicked.AddUniqueDynamic(Forward, &URecoveredModifierToggleForward::Toggle);
                ToggleForwarders.Add(Forward);
            }
        }
        Container->AddChildToUniformGrid(Entry, Index / 4, Index % 4);
        ++Index;
    }
}

bool URecoveredModifierWidget::ToggleModifier(FName ModifierID) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression || HasPendingModifierConflicts()) return false;
    ModifierID = Progression->GetCanonicalModifierID(ModifierID);
    if (ModifierID.IsNone() || !Progression->IsModifierUnlocked(ModifierID)) return false;
    if (Progression->EnabledModifiers.Contains(ModifierID)) {
        Progression->EnabledModifiers.Remove(ModifierID);
    } else {
        const TArray<FName> Conflicts = Progression->GetConflictingModifiers(ModifierID);
        if (!Conflicts.IsEmpty()) {
            FRecoveredModifierRow Modifier;
            if (Progression->GetModifierData(ModifierID, Modifier)) ShowModifierConflictOverlay(Modifier, Conflicts);
            PendingModifierID = ModifierID;
            PendingConflictingModifiers = Conflicts;
            return false;
        }
        Progression->EnabledModifiers.Add(ModifierID);
    }
    PersistAndRefreshModifierState();
    return true;
}

bool URecoveredModifierWidget::ConfirmModifierConflicts() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression || PendingModifierID.IsNone()) return false;
    for (const FName Conflict : PendingConflictingModifiers) Progression->EnabledModifiers.Remove(Conflict);
    Progression->EnabledModifiers.Add(PendingModifierID);
    CloseModifierConflictOverlay();
    PendingModifierID = NAME_None;
    PendingConflictingModifiers.Reset();
    PersistAndRefreshModifierState();
    return true;
}

void URecoveredModifierWidget::CancelModifierConflicts() {
    CloseModifierConflictOverlay();
    PendingModifierID = NAME_None;
    PendingConflictingModifiers.Reset();
}

bool URecoveredModifierWidget::HasPendingModifierConflicts() const {
    return !PendingModifierID.IsNone();
}

void URecoveredModifierWidget::PersistAndRefreshModifierState() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression) return;
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
}

void URecoveredModifierWidget::ShowModifierConflictOverlay(const FRecoveredModifierRow& Modifier, const TArray<FName>& Conflicts) {
    CloseModifierConflictOverlay();
    UClass* OverlayClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Recovery/UI/ConflictingWidgetOverlayWidget.ConflictingWidgetOverlayWidget_C"));
    if (!OverlayClass || !GetWorld()) return;
    ConflictOverlay = CreateWidget<UUserWidget>(GetWorld(), OverlayClass);
    if (!ConflictOverlay) return;
    if (auto* Title = Cast<UTextBlock>(ConflictOverlay->GetWidgetFromName(TEXT("ConflictTitle")))) {
        Title->SetText(FText::FromString(FString::Printf(TEXT("\"%s\" Conflicts With:"), *Modifier.ModifierTitle.ToString())));
    }
    if (auto* Icon = Cast<UImage>(ConflictOverlay->GetWidgetFromName(TEXT("ModifierIcon")))) Icon->SetBrushFromTexture(Modifier.ModifierIcon);
    FString ConflictText;
    for (const FName Conflict : Conflicts) ConflictText += FString::Printf(TEXT("\"%s\"\r\n"), *Conflict.ToString());
    if (auto* Text = Cast<UTextBlock>(ConflictOverlay->GetWidgetFromName(TEXT("ConflictingModifiersText")))) Text->SetText(FText::FromString(ConflictText));
    ConflictForwarder = NewObject<URecoveredModifierConflictForward>(this);
    ConflictForwarder->Owner = this;
    if (auto* Confirm = FindEntryButton(ConflictOverlay, TEXT("RemoveConflictsButton"))) Confirm->OnClicked.AddUniqueDynamic(ConflictForwarder, &URecoveredModifierConflictForward::Confirm);
    if (auto* Cancel = FindEntryButton(ConflictOverlay, TEXT("CancelButton"))) Cancel->OnClicked.AddUniqueDynamic(ConflictForwarder, &URecoveredModifierConflictForward::Cancel);
    ConflictOverlay->AddToViewport(0);
}

void URecoveredModifierWidget::CloseModifierConflictOverlay() {
    if (ConflictOverlay) ConflictOverlay->RemoveFromParent();
    ConflictOverlay = nullptr;
    ConflictForwarder = nullptr;
}

void URecoveredModifierToggleForward::Toggle() {
    if (Owner) Owner->ToggleModifier(ModifierID);
}

void URecoveredModifierConflictForward::Confirm() {
    if (Owner) Owner->ConfirmModifierConflicts();
}

void URecoveredModifierConflictForward::Cancel() {
    if (Owner) Owner->CancelModifierConflicts();
}
