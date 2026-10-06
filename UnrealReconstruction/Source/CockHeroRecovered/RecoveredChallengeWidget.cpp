#include "RecoveredChallengeWidget.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredRules.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

namespace {
URecoveredChallengeTracker* GetChallengeTracker(const UUserWidget* Widget) {
    const auto* Instance = Widget ? Cast<URecoveredGameInstance>(Widget->GetGameInstance()) : nullptr;
    return Instance ? Instance->ChallengeTracker.Get() : nullptr;
}

const FRecoveredChallengeProgress* FindProgress(const URecoveredChallengeTracker* Tracker, FName ChallengeID) {
    if (!Tracker) return nullptr;
    if (const auto* Progress = Tracker->SessionProgress.Find(ChallengeID)) return Progress;
    return Tracker->LifetimeProgress.Find(ChallengeID);
}

const FRecoveredChallengeRow* FindDefinition(const URecoveredChallengeTracker* Tracker, FName ChallengeID) {
    if (!Tracker || !Tracker->ChallengeTable || Tracker->ChallengeTable->GetRowStruct() != FRecoveredChallengeRow::StaticStruct()) return nullptr;
    if (const auto* ByRowName = Tracker->ChallengeTable->FindRow<FRecoveredChallengeRow>(ChallengeID, TEXT("Recovered challenge UI"))) return ByRowName;
    for (const auto& Pair : Tracker->ChallengeTable->GetRowMap()) {
        const auto* Candidate = reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (Candidate && Candidate->ChallengeID == ChallengeID.ToString()) return Candidate;
    }
    return nullptr;
}

FString DescribeRequirements(const FRecoveredChallengeProgress& Progress) {
    TArray<FString> Lines;
    for (const FRecoveredRequirement& Requirement : Progress.Requirements) {
        Lines.Add(FString::Printf(TEXT("%s: %d / %d"), *Requirement.MetricType, Requirement.CurrentValue, Requirement.TargetValue));
    }
    return Lines.IsEmpty() ? TEXT("No recovered requirements") : FString::Join(Lines, TEXT("\n"));
}

FString DescribeRewards(const FRecoveredChallengeRow* Definition) {
    if (!Definition) return TEXT("No recovered reward data");
    TArray<FString> Lines;
    for (const FRecoveredReward& Reward : Definition->Rewards) Lines.Add(FString::Printf(TEXT("+%d %s"), Reward.Value, *Reward.RewardType));
    if (Definition->XPReward > 0) Lines.Add(FString::Printf(TEXT("+%d XP"), Definition->XPReward));
    if (Definition->UnlockPointsReward > 0) Lines.Add(FString::Printf(TEXT("+%d Unlock Points"), Definition->UnlockPointsReward));
    return Lines.IsEmpty() ? TEXT("No reward") : FString::Join(Lines, TEXT("\n"));
}

void SetNamedText(UUserWidget* Widget, const TCHAR* Name, const FText& Value) {
    if (auto* Text = Widget ? Cast<UTextBlock>(Widget->GetWidgetFromName(Name)) : nullptr) Text->SetText(Value);
}
}

void URecoveredChallengeWidget::NativeConstruct() {
    Super::NativeConstruct();
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->ChallengeTracker) {
        Instance->ChallengeTracker->OnChallengeProgress.AddUniqueDynamic(this, &URecoveredChallengeWidget::OnChallengeProgressNotification);
    }
    RefreshChallengeList();
}

void URecoveredChallengeWidget::RefreshChallengeList() {
    auto* Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("ChallengesVerticalBox")));
    if (!Container) Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("ChallengeListScrollbox")));
    if (!Container) return;
    Container->ClearChildren();
    ActionForwarders.Reset();
    URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    if (!Tracker) return;

    TSet<FName> IDs;
    for (const auto& Pair : Tracker->SessionProgress) IDs.Add(Pair.Key);
    for (const auto& Pair : Tracker->LifetimeProgress) IDs.Add(Pair.Key);
    TArray<FName> SortedIDs = IDs.Array();
    SortedIDs.Sort([](const FName& A, const FName& B) { return A.LexicalLess(B); });
    if (!SelectedChallengeID.IsNone() && !IDs.Contains(SelectedChallengeID)) SelectedChallengeID = NAME_None;
    if (SelectedChallengeID.IsNone() && !SortedIDs.IsEmpty()) SelectedChallengeID = SortedIDs[0];

    for (const FName ChallengeID : SortedIDs) {
        const FRecoveredChallengeProgress* Progress = FindProgress(Tracker, ChallengeID);
        if (!Progress) continue;
        const FRecoveredChallengeRow* Definition = FindDefinition(Tracker, ChallengeID);
        auto* Row = NewObject<UHorizontalBox>(this);
        auto* Select = NewObject<UButton>(this);
        auto* SelectText = NewObject<UTextBlock>(this);
        const FString Title = Definition ? Definition->DisplayName.ToString() : ChallengeID.ToString();
        FString Status = Progress->bCompleted ? TEXT("Complete") : TEXT("In Progress");
        if (Progress->bRewardsClaimed) Status += TEXT(" (Claimed)");
        SelectText->SetText(FText::FromString(Title + TEXT(" — ") + Status));
        Select->SetContent(SelectText);
        auto* SelectForward = NewObject<URecoveredChallengeActionForward>(this);
        SelectForward->Owner = this;
        SelectForward->ChallengeID = ChallengeID;
        SelectForward->bPrimaryAction = false;
        Select->OnClicked.AddUniqueDynamic(SelectForward, &URecoveredChallengeActionForward::Execute);
        ActionForwarders.Add(SelectForward);

        auto* Action = NewObject<UButton>(this);
        auto* ActionText = NewObject<UTextBlock>(this);
        const bool bCanClaim = Progress->bCompleted && !Progress->bRewardsClaimed;
        ActionText->SetText(FText::FromString(bCanClaim ? TEXT("Claim") : IsChallengeTracked(ChallengeID) ? TEXT("Untrack") : TEXT("Track")));
        Action->SetIsEnabled(!Progress->bRewardsClaimed);
        Action->SetContent(ActionText);
        auto* ActionForward = NewObject<URecoveredChallengeActionForward>(this);
        ActionForward->Owner = this;
        ActionForward->ChallengeID = ChallengeID;
        ActionForward->bPrimaryAction = true;
        Action->OnClicked.AddUniqueDynamic(ActionForward, &URecoveredChallengeActionForward::Execute);
        ActionForwarders.Add(ActionForward);

        Row->AddChildToHorizontalBox(Select);
        Row->AddChildToHorizontalBox(Action);
        Container->AddChild(Row);
    }
    RefreshDetailsPanel();
}

void URecoveredChallengeWidget::SetChallengeTracked(FName ChallengeID, bool bTracked) {
    URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    if (!Tracker || !FindProgress(Tracker, ChallengeID)) return;
    if (bTracked) Tracker->TrackedChallenges.AddUnique(ChallengeID);
    else Tracker->TrackedChallenges.Remove(ChallengeID);
    if (auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) Instance->PersistRecoveredProgression();
    RefreshChallengeList();
}

bool URecoveredChallengeWidget::IsChallengeTracked(FName ChallengeID) const {
    const URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    return Tracker && Tracker->TrackedChallenges.Contains(ChallengeID);
}

TArray<FName> URecoveredChallengeWidget::GetTrackedChallenges() const {
    const URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    return Tracker ? Tracker->TrackedChallenges : TArray<FName>();
}

bool URecoveredChallengeWidget::ClaimChallengeRewards(FName ChallengeID) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    if (!Tracker) return false;
    TArray<FRecoveredReward> Rewards = Tracker->ClaimChallengeRewards(ChallengeID);
    if (Rewards.Num() == 0) return false;
    // The tracker already grants all reward types through its reward manager.
    // Applying XP here again would double the reward.
    Instance->PersistRecoveredProgression();
    RefreshChallengeList();
    return true;
}

void URecoveredChallengeWidget::SelectChallenge(FName ChallengeID) {
    if (URecoveredChallengeTracker* Tracker = GetChallengeTracker(this)) {
        if (!FindProgress(Tracker, ChallengeID)) return;
        SelectedChallengeID = ChallengeID;
        RefreshDetailsPanel();
    }
}

void URecoveredChallengeWidget::RunChallengeAction(FName ChallengeID) {
    URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    const FRecoveredChallengeProgress* Progress = FindProgress(Tracker, ChallengeID);
    if (!Progress) return;
    SelectedChallengeID = ChallengeID;
    if (Progress->bCompleted) {
        if (!Progress->bRewardsClaimed) ClaimChallengeRewards(ChallengeID);
        return;
    }
    SetChallengeTracked(ChallengeID, !IsChallengeTracked(ChallengeID));
}

void URecoveredChallengeWidget::RefreshDetailsPanel() {
    URecoveredChallengeTracker* Tracker = GetChallengeTracker(this);
    const FRecoveredChallengeProgress* Progress = FindProgress(Tracker, SelectedChallengeID);
    if (!Progress) return;
    const FRecoveredChallengeRow* Definition = FindDefinition(Tracker, SelectedChallengeID);
    SetNamedText(this, TEXT("ChallengeTitle"), Definition ? Definition->DisplayName : FText::FromName(SelectedChallengeID));
    SetNamedText(this, TEXT("RequirementTitle"), FText::FromString(TEXT("Requirements")));
    SetNamedText(this, TEXT("RequirementDescription"), FText::FromString(DescribeRequirements(*Progress)));
    SetNamedText(this, TEXT("RewardsTitle"), FText::FromString(TEXT("Rewards")));
    SetNamedText(this, TEXT("RewardsBody"), FText::FromString(DescribeRewards(Definition)));
    const FString Completion = Progress->bRewardsClaimed ? TEXT("Rewards claimed") : Progress->bCompleted ? TEXT("Complete") : TEXT("In Progress");
    SetNamedText(this, TEXT("CompletionStatusText"), FText::FromString(Completion));
    if (auto* Interaction = Cast<UButton>(GetWidgetFromName(TEXT("InteractionButton")))) {
        const bool bCanClaim = Progress->bCompleted && !Progress->bRewardsClaimed;
        Interaction->SetIsEnabled(!Progress->bRewardsClaimed);
        if (auto* Label = Cast<UTextBlock>(GetWidgetFromName(TEXT("InteractionButtonText")))) {
            Label->SetText(FText::FromString(bCanClaim ? TEXT("Claim Rewards") : IsChallengeTracked(SelectedChallengeID) ? TEXT("Untrack Challenge") : TEXT("Track Challenge")));
        }
        Interaction->OnClicked.RemoveAll(this);
        Interaction->OnClicked.AddUniqueDynamic(this, &URecoveredChallengeWidget::HandleInteractionClicked);
    }
}

void URecoveredChallengeWidget::HandleInteractionClicked() {
    if (!SelectedChallengeID.IsNone()) RunChallengeAction(SelectedChallengeID);
}

void URecoveredChallengeWidget::OnChallengeProgressNotification(FName ChallengeID) {
    RefreshChallengeList();
}

void URecoveredChallengeActionForward::Execute() {
    if (!Owner) return;
    if (bPrimaryAction) Owner->RunChallengeAction(ChallengeID);
    else Owner->SelectChallenge(ChallengeID);
}
