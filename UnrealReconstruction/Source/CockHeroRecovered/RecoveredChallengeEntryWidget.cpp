#include "RecoveredChallengeEntryWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "MovieScene.h"
#include "RecoveredProgression.h"

namespace {

const FLinearColor CompletedColor(0.0f,0.5209959745407104f,0.12477199733257294f,1.0f);
const FLinearColor IncompleteColor(1.0f,0.015208999626338482f,0.01298299990594387f,1.0f);

UWidgetAnimation* FindSourceAnimation(const UUserWidget* Widget,FName AnimationName) {
    const auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Widget ? Widget->GetClass() : nullptr);
    if (!Generated) return nullptr;
    const FName RuntimeName(*FString::Printf(TEXT("%s_INST"),*AnimationName.ToString()));
    for (UWidgetAnimation* Animation:Generated->Animations) {
        if (!Animation) continue;
        const UMovieScene* MovieScene=Animation->GetMovieScene();
        if (
            Animation->GetFName()==AnimationName ||
            Animation->GetFName()==RuntimeName ||
            (MovieScene && (MovieScene->GetFName()==AnimationName || MovieScene->GetFName()==RuntimeName))
        ) return Animation;
    }
    return nullptr;
}

}

void URecoveredChallengeEntryWidget::PopulateChallengeEntry(
    FName InChallengeID,
    const FText& InChallengeTitle,
    UTexture2D* InChallengeIcon,
    bool bInChallengeComplete,
    const TArray<FRecoveredReward>& InRewards,
    bool bInChallengeTracked,
    int32 InTrackedChallengesLength,
    bool bInRewardsClaimed) {
    BindSourceEvents();
    ChallengeID=InChallengeID;
    ChallengeTitle=InChallengeTitle;
    SelectedChallengeIcon=InChallengeIcon;
    bChallengeComplete=bInChallengeComplete;
    Rewards=InRewards;
    bChallengeTracked=bInChallengeTracked;
    TrackedChallengesLength=InTrackedChallengesLength;
    bRewardsClaimed=bInRewardsClaimed;
    ApplyPresentation();
}

void URecoveredChallengeEntryWidget::SetTrackButtonText(const FText& InText) {
    BindSourceTree();
    if (SourceTrackButtonText) SourceTrackButtonText->SetText(InText);
}

void URecoveredChallengeEntryWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    BindSourceEvents();
    ApplyPresentation();
}

void URecoveredChallengeEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindSourceEvents();
    ApplyPresentation();
}

void URecoveredChallengeEntryWidget::NativeDestruct() {
    if (SourceChallengeEntryButton) {
        SourceChallengeEntryButton->OnHovered.RemoveDynamic(this,&URecoveredChallengeEntryWidget::HandleEntryHovered);
        SourceChallengeEntryButton->OnUnhovered.RemoveDynamic(this,&URecoveredChallengeEntryWidget::HandleEntryUnhovered);
        SourceChallengeEntryButton->OnClicked.RemoveDynamic(this,&URecoveredChallengeEntryWidget::HandleEntryClicked);
    }
    if (SourceTrackButton) SourceTrackButton->OnClicked.RemoveDynamic(this,&URecoveredChallengeEntryWidget::HandleTrackClicked);
    Super::NativeDestruct();
}

void URecoveredChallengeEntryWidget::BindSourceTree() {
    if (!SourceChallengeEntryButton) SourceChallengeEntryButton=Cast<UButton>(GetWidgetFromName(TEXT("ChallengeEntryButton")));
    if (!SourceTrackButton) SourceTrackButton=Cast<UButton>(GetWidgetFromName(TEXT("TrackButton")));
    if (!SourceChallengeIcon) SourceChallengeIcon=Cast<UImage>(GetWidgetFromName(TEXT("ChallengeIcon")));
    if (!SourceChallengeCompletionStatus) SourceChallengeCompletionStatus=Cast<UTextBlock>(GetWidgetFromName(TEXT("ChallengeCompletionStatus")));
    if (!SourceChallengeTitle) SourceChallengeTitle=Cast<UTextBlock>(GetWidgetFromName(TEXT("ChallengeTitle")));
    if (!SourceTrackButtonText) SourceTrackButtonText=Cast<UTextBlock>(GetWidgetFromName(TEXT("TrackButtonText")));
}

void URecoveredChallengeEntryWidget::BindSourceEvents() {
    BindSourceTree();
    if (SourceChallengeEntryButton) {
        SourceChallengeEntryButton->OnHovered.AddUniqueDynamic(this,&URecoveredChallengeEntryWidget::HandleEntryHovered);
        SourceChallengeEntryButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredChallengeEntryWidget::HandleEntryUnhovered);
        SourceChallengeEntryButton->OnClicked.AddUniqueDynamic(this,&URecoveredChallengeEntryWidget::HandleEntryClicked);
    }
    if (SourceTrackButton) SourceTrackButton->OnClicked.AddUniqueDynamic(this,&URecoveredChallengeEntryWidget::HandleTrackClicked);
}

void URecoveredChallengeEntryWidget::ApplyPresentation() {
    BindSourceTree();
    if (SourceChallengeTitle) SourceChallengeTitle->SetText(ChallengeTitle);
    if (SourceChallengeIcon) SourceChallengeIcon->SetBrushFromTexture(SelectedChallengeIcon,false);
    if (!SourceChallengeCompletionStatus) return;

    if (bChallengeComplete) {
        SourceChallengeCompletionStatus->SetColorAndOpacity(FSlateColor(CompletedColor));
        SourceChallengeCompletionStatus->SetText(FText::FromString(bRewardsClaimed ? TEXT("Completed") : TEXT("Claim Rewards")));
        if (bRewardsClaimed) SetTrackButtonText(FText::FromString(TEXT("Done")));
        return;
    }

    SourceChallengeCompletionStatus->SetColorAndOpacity(FSlateColor(IncompleteColor));
    SourceChallengeCompletionStatus->SetText(FText::FromString(TEXT("Incomplete")));
    if (bChallengeTracked) SetTrackButtonText(FText::FromString(FString::Printf(TEXT("Untrack %d/2"),TrackedChallengesLength)));
    else SetTrackButtonText(FText::FromString(FString::Printf(TEXT("Track %d/2"),TrackedChallengesLength)));
}

void URecoveredChallengeEntryWidget::PlaySourceAnimation(FName AnimationName) {
    if (UWidgetAnimation* Animation=FindSourceAnimation(this,AnimationName)) {
        PlayAnimation(Animation,0.0f,1,EUMGSequencePlayMode::Forward,1.0f,false);
    }
}

void URecoveredChallengeEntryWidget::HandleEntryHovered() {
    PlaySourceAnimation(TEXT("ButtonHover"));
}

void URecoveredChallengeEntryWidget::HandleEntryUnhovered() {
    PlaySourceAnimation(TEXT("ButtonUnhover"));
}

void URecoveredChallengeEntryWidget::HandleEntryClicked() {
    OnChallengeClicked.Broadcast(ChallengeID);
}

void URecoveredChallengeEntryWidget::HandleTrackClicked() {
    OnTrackButtonClicked.Broadcast(ChallengeID,this);
}
