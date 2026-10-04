#include "RecoveredChallengeWidget.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredRules.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Kismet/GameplayStatics.h"

void URecoveredChallengeWidget::NativeConstruct() {
    Super::NativeConstruct();
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->ChallengeTracker) {
        Instance->ChallengeTracker->OnChallengeProgress.AddUniqueDynamic(this, &URecoveredChallengeWidget::OnChallengeProgressNotification);
    }
    RefreshChallengeList();
}

void URecoveredChallengeWidget::RefreshChallengeList() {
    auto* Container = Cast<UPanelWidget>(GetWidgetFromName(TEXT("ChallengeListContainer")));
    if (!Container) return;
    Container->ClearChildren();
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredChallengeTracker* Tracker = Instance ? Instance->ChallengeTracker.Get() : nullptr;
    if (!Tracker) return;
    // Populate from session progress map.
    for (const auto& Pair : Tracker->SessionProgress) {
        const FName ChallengeID = Pair.Key;
        const FRecoveredChallengeProgress& Progress = Pair.Value;
        auto* Row = NewObject<UHorizontalBox>(this);
        auto* NameText = NewObject<UTextBlock>(this);
        NameText->SetText(FText::FromString(ChallengeID.ToString()));
        auto* ProgressText = NewObject<UTextBlock>(this);
        FString ProgressStr = Progress.bCompleted ? TEXT("Complete") : TEXT("In Progress");
        if (Progress.bRewardsClaimed) ProgressStr += TEXT(" (Claimed)");
        ProgressText->SetText(FText::FromString(ProgressStr));
        auto* TrackCheck = NewObject<UCheckBox>(this);
        TrackCheck->SetCheckedState(IsChallengeTracked(ChallengeID) ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
        auto* ClaimButton = NewObject<UButton>(this);
        ClaimButton->SetIsEnabled(Progress.bCompleted && !Progress.bRewardsClaimed);
        Row->AddChildToHorizontalBox(NameText);
        Row->AddChildToHorizontalBox(ProgressText);
        Row->AddChildToHorizontalBox(TrackCheck);
        Row->AddChildToHorizontalBox(ClaimButton);
        Container->AddChild(Row);
    }
}

void URecoveredChallengeWidget::SetChallengeTracked(FName ChallengeID, bool bTracked) {
    if (bTracked) TrackedChallenges.Add(ChallengeID);
    else TrackedChallenges.Remove(ChallengeID);
}

bool URecoveredChallengeWidget::IsChallengeTracked(FName ChallengeID) const {
    return TrackedChallenges.Contains(ChallengeID);
}

TArray<FName> URecoveredChallengeWidget::GetTrackedChallenges() const {
    return TrackedChallenges.Array();
}

bool URecoveredChallengeWidget::ClaimChallengeRewards(FName ChallengeID) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    URecoveredChallengeTracker* Tracker = Instance ? Instance->ChallengeTracker.Get() : nullptr;
    if (!Tracker) return false;
    TArray<FRecoveredReward> Rewards = Tracker->ClaimChallengeRewards(ChallengeID);
    if (Rewards.Num() == 0) return false;
    // The tracker already grants all reward types through its reward manager.
    // Applying XP here again would double the reward.
    Instance->PersistRecoveredProgression();
    RefreshChallengeList();
    return true;
}

void URecoveredChallengeWidget::OnChallengeProgressNotification(FName ChallengeID) {
    // Refresh the list entry when progress updates.
    RefreshChallengeList();
}
