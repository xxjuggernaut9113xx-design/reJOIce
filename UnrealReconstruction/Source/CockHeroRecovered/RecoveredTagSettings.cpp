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
    if (Manager) {
        TArray<FRecoveredMediaEntry> Entries;
        FString Error;
        if (URecoveredMediaLibrary::ReadPackManifest(Manager->MediaManifestPath,Entries,Error)) {
            for (const auto& Entry:Entries) for (const FString& Tag:Entry.Tags) if (!Tag.IsEmpty()) Unique.Add(Tag);
        } else if (Manager->MediaDeckState) {
            const auto& Decks=Manager->MediaDeckState->Master;
            const TArray<FRecoveredMediaEntry>* All[]={&Decks.Slow,&Decks.Medium,&Decks.Fast,&Decks.Cum,&Decks.Succubus,&Decks.Ass,&Decks.Boobs};
            for (const auto* Deck:All) for (const auto& Entry:*Deck) for (const auto& Tag:Entry.Tags) if (!Tag.IsEmpty()) Unique.Add(Tag);
        }
    }
    TArray<FString> Out = Unique.Array();
    Out.Sort();
    return Out;
}

void URecoveredTagSettingsMenu::BuildTagEntries() {
    TArray<UPanelWidget*> Columns;
    for (const TCHAR* Name : {TEXT("VertiBox1"), TEXT("VertiBox2"), TEXT("VertiBox3")}) {
        if (auto* Column=Cast<UPanelWidget>(GetWidgetFromName(Name))) { Column->ClearChildren(); Columns.Add(Column); }
    }
    if (Columns.IsEmpty()) return;
    int32 ColumnIndex=0;
    TagToggleForwarders.Reset();
    // Load the native tag entry widget class; fall back to a checkbox+label row.
    UClass* EntryClass=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/TagFilterEntry_WIDGET.TagFilterEntry_WIDGET_C"));
    const TArray<FString> Tags = CollectAvailableTags();
    for (const FString& Tag : Tags) {
        UUserWidget* Entry=EntryClass && GetWorld() ? CreateWidget<UUserWidget>(GetWorld(),EntryClass) : nullptr;
        UCheckBox* Check=Entry ? Cast<UCheckBox>(Entry->GetWidgetFromName(TEXT("CheckBox"))) : nullptr;
        UTextBlock* Label=Entry ? Cast<UTextBlock>(Entry->GetWidgetFromName(TEXT("TagString"))) : nullptr;
        UWidget* Row=Entry;
        if (!Check || !Label) {
            auto* Fallback=NewObject<UHorizontalBox>(this);
            Check=NewObject<UCheckBox>(this);Label=NewObject<UTextBlock>(this);
            Fallback->AddChildToHorizontalBox(Check);Fallback->AddChildToHorizontalBox(Label);Row=Fallback;
        }
        Label->SetText(FText::FromString(Tag));
        Columns[ColumnIndex++ % Columns.Num()]->AddChild(Row);
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

void URecoveredTagSettingsMenu::SelectAllTags() { ClearExcludedTags(); }
void URecoveredTagSettingsMenu::DeselectAllTags() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    if (Instance->CurrentSave->SetStringArraySetting(TEXT("ExcludedTags"), CollectAvailableTags())) Instance->SaveRecoveredState();
    InitDefaultsFromSaveGame();
}
