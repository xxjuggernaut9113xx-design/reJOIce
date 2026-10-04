#include "RecoveredTagSettings.h"
#include "RecoveredRules.h"
#include "RecoveredMedia.h"
#include "RecoveredDecks.h"
#include "Components/CheckBox.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void URecoveredTagSettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    BuildTagEntries();
    InitDefaultsFromSaveGame();
}

void URecoveredTagSettingsMenu::InitDefaultsFromSaveGame() {
    for (URecoveredTagToggleForward* Forward : TagToggleForwarders) {
        if (!Forward) continue;
        if (UCheckBox* Check = Forward->Check) {
            Check->SetIsChecked(!IsTagExcluded(Forward->Tag));
        }
    }
}

bool URecoveredTagSettingsMenu::IsTagExcluded(const FString& Tag) const {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    return Instance && Instance->CurrentSave && Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags")).Contains(Tag);
}

void URecoveredTagSettingsMenu::SetTagExcluded(const FString& Tag, bool bExcluded) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave || Tag.IsEmpty()) return;
    TArray<FString> Excluded = Instance->CurrentSave->GetStringArraySetting(TEXT("ExcludedTags"));
    if (bExcluded) Excluded.AddUnique(Tag);
    else Excluded.Remove(Tag);
    if (Instance->CurrentSave->SetStringArraySetting(TEXT("ExcludedTags"), Excluded)) {
        Instance->SaveRecoveredState();
    }
}

void URecoveredTagSettingsMenu::ClearExcludedTags() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetStringArraySetting(TEXT("ExcludedTags"), TArray<FString>())) {
        Instance->SaveRecoveredState();
        InitDefaultsFromSaveGame();
    }
}

TArray<FString> URecoveredTagSettingsMenu::CollectAvailableTags() const {
    TSet<FString> Unique;
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager && Manager->MediaDeckState) {
        const FRecoveredMediaDecks& Decks = Manager->MediaDeckState->Master;
        const TArray<FRecoveredMediaEntry>* All[] = { &Decks.Slow, &Decks.Medium, &Decks.Fast, &Decks.Cum, &Decks.Succubus, &Decks.Ass };
        for (const auto* Deck : All) {
            for (const FRecoveredMediaEntry& Entry : *Deck) {
                for (const FString& Tag : Entry.Tags) {
                    if (!Tag.IsEmpty()) Unique.Add(Tag);
                }
            }
        }
    }
    TArray<FString> Out = Unique.Array();
    Out.Sort();
    return Out;
}

void URecoveredTagSettingsMenu::BuildTagEntries() {
    auto* Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("VertiBox1")));
    if (!Container) return;
    Container->ClearChildren();
    TagToggleForwarders.Reset();
    // Load the native tag entry widget class; fall back to a checkbox+label row.
    const TArray<FString> Tags = CollectAvailableTags();
    for (const FString& Tag : Tags) {
        auto* Row = NewObject<UHorizontalBox>(this);
        auto* Check = NewObject<UCheckBox>(this);
        auto* Label = NewObject<UTextBlock>(this);
        Label->SetText(FText::FromString(Tag));
        Row->AddChildToHorizontalBox(Check);
        Row->AddChildToHorizontalBox(Label);
        Container->AddChild(Row);
        if (Check) {
            Check->SetCheckedState(IsTagExcluded(Tag) ? ECheckBoxState::Unchecked : ECheckBoxState::Checked);
            // Dynamic delegates don't pass the sender, so each checkbox gets a
            // forwarder holding its tag.
            auto* Forward = NewObject<URecoveredTagToggleForward>(this);
            Forward->Owner = this;
            Forward->Tag = Tag;
            Forward->Check = Check;
            TagToggleForwarders.Add(Forward);
            Check->OnCheckStateChanged.AddUniqueDynamic(Forward, &URecoveredTagToggleForward::ForwardToggle);
        }
    }
}

void URecoveredTagToggleForward::ForwardToggle(bool bChecked) {
    if (Owner) Owner->SetTagExcluded(Tag, !bChecked);
}
