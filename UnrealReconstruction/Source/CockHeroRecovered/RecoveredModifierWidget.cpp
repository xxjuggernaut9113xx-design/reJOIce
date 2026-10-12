#include "RecoveredModifierWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "RecoveredModifierCardEntryWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

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

void URecoveredModifierWidget::SetRecoveredModifierGameInstance(URecoveredGameInstance* Instance) {
    RecoveredInstanceOverride=Instance;
}

URecoveredGameInstance* URecoveredModifierWidget::GetRecoveredModifierGameInstance() const {
    if (RecoveredInstanceOverride) return RecoveredInstanceOverride;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    return GetWorld() ? Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
}

void URecoveredModifierWidget::RefreshModifierList() {
    auto* Container = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel_94")));
    if (!Container) return;
    Container->ClearChildren();
    ToggleForwarders.Reset();
    RecoveredModifierEntries.Reset();
    auto* Instance = GetRecoveredModifierGameInstance();
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
        UUserWidget* Entry = EntryClass ? CreateWidget<UUserWidget>(this, EntryClass) : nullptr;
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
        FRecoveredChallengeRow Challenge;
        const FName ChallengeID=Progression->GetChallengeForModifier(ModifierID);
        if (!ChallengeID.IsNone() && Progression->ChallengeDataTable && Progression->ChallengeDataTable->GetRowStruct()==FRecoveredChallengeRow::StaticStruct()) {
            for (const TPair<FName,uint8*>& Pair:Progression->ChallengeDataTable->GetRowMap()) {
                const auto* Candidate=reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
                if (Candidate && Candidate->ChallengeID==ChallengeID.ToString()) { Challenge=*Candidate; break; }
            }
        }
        if (auto* SourceEntry=Cast<URecoveredModifierCardEntryWidget>(Entry)) {
            SourceEntry->PopulateDetails(bUnlocked,bEnabled,Row.ModifierTitle,Row.ModifierIcon,Row.ModifierDescription,Challenge.DisplayName,Challenge.Description);
            RecoveredModifierEntries.Add(ModifierID,SourceEntry);
            auto* Forward=NewObject<URecoveredModifierToggleForward>(this);
            Forward->Owner=this;
            Forward->ModifierID=ModifierID;
            SourceEntry->OnCardClicked.AddUniqueDynamic(Forward,&URecoveredModifierToggleForward::ToggleSourceEntry);
            ToggleForwarders.Add(Forward);
        } else {
            SetEntryText(Entry, TEXT("ModifierTitle"), Row.ModifierTitle);
            SetEntryText(Entry, TEXT("ModifierDescription"), Row.ModifierDescription);
            SetEntryText(Entry, TEXT("ChallengeRequiredText"), bUnlocked ? FText::GetEmpty() : FText::FromString(TEXT("Complete the linked challenge to unlock")));
            SetEntryText(Entry, TEXT("ButtonText"), FText::FromString(bEnabled ? TEXT("Enabled") : TEXT("Disabled")));
            if (auto* Icon = Cast<UImage>(Entry->GetWidgetFromName(TEXT("ModifierIcon")))) Icon->SetBrushFromTexture(Row.ModifierIcon);
            if (auto* Lock = Entry->GetWidgetFromName(TEXT("LockOverlay"))) Lock->SetVisibility(bUnlocked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
            if (UButton* Button=FindEntryButton(Entry,TEXT("ToggleModifierButton"))) {
                Button->SetIsEnabled(bUnlocked);
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
    return ToggleModifierInternal(ModifierID,FindRecoveredModifierEntry(ModifierID));
}

void URecoveredModifierWidget::ToggleModifierFromSource(const FText& ModifierTitle,UUserWidget* Entry) {
    ToggleModifierInternal(FName(*ModifierTitle.ToString()),Cast<URecoveredModifierCardEntryWidget>(Entry));
}

URecoveredModifierCardEntryWidget* URecoveredModifierWidget::FindRecoveredModifierEntry(FName ModifierID) const {
    if (const TObjectPtr<URecoveredModifierCardEntryWidget>* Found=RecoveredModifierEntries.Find(ModifierID)) return Found->Get();
    return nullptr;
}

bool URecoveredModifierWidget::ToggleModifierInternal(FName ModifierID,URecoveredModifierCardEntryWidget* SourceEntry) {
    auto* Instance = GetRecoveredModifierGameInstance();
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression || HasPendingModifierConflicts()) return false;
    ModifierID = Progression->GetCanonicalModifierID(ModifierID);
    if (ModifierID.IsNone()) return false;
    if (Progression->EnabledModifiers.Contains(ModifierID)) {
        if (SourceEntry) SourceEntry->SetButtonToggleWithSound(false);
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
        if (SourceEntry) SourceEntry->SetButtonToggleWithSound(true);
        Progression->EnabledModifiers.Add(ModifierID);
    }
    PersistModifierState();
    return true;
}

bool URecoveredModifierWidget::ConfirmModifierConflicts() {
    auto* Instance = GetRecoveredModifierGameInstance();
    URecoveredProgressionManager* Progression = Instance ? Instance->ProgressionManager.Get() : nullptr;
    if (!Progression || PendingModifierID.IsNone()) return false;
    for (const FName Conflict : PendingConflictingModifiers) Progression->EnabledModifiers.Remove(Conflict);
    Progression->EnabledModifiers.Add(PendingModifierID);
    CloseModifierConflictOverlay();
    PendingModifierID = NAME_None;
    PendingConflictingModifiers.Reset();
    PersistAndRefreshModifierState();
    PlaySourceToggleSound();
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

void URecoveredModifierWidget::PersistModifierState() {
    auto* Instance = GetRecoveredModifierGameInstance();
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
}

void URecoveredModifierWidget::PersistAndRefreshModifierState() {
    PersistModifierState();
    RefreshModifierList();
}

void URecoveredModifierWidget::PlaySourceToggleSound() {
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/ontoggle2.ontoggle2"))) {
        if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,0.5f,1.5f,0.1f,nullptr,nullptr,true);
    }
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

void URecoveredModifierToggleForward::ToggleSourceEntry(const FText& ModifierTitle,UUserWidget* Entry) {
    if (Owner) Owner->ToggleModifierFromSource(ModifierTitle,Entry);
}

void URecoveredModifierConflictForward::Confirm() {
    if (Owner) Owner->ConfirmModifierConflicts();
}

void URecoveredModifierConflictForward::Cancel() {
    if (Owner) Owner->CancelModifierConflicts();
}
