#include "RecoveredPlayerCardEntryWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

namespace {

UTexture2D* GetLockedCardTexture() {
    return LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/PlayerCards/LockedPlayerCard.LockedPlayerCard"));
}

FText GetRequirementText(const FString& RequiredChallengeID,int32 RequiredLevel,const FText& ChallengeTitle) {
    if (!RequiredChallengeID.IsEmpty() && !RequiredChallengeID.Equals(TEXT("none"),ESearchCase::IgnoreCase)) {
        if (!ChallengeTitle.IsEmpty()) return FText::FromString(FString::Printf(TEXT("Locked: %s"),*ChallengeTitle.ToString()));
        return FText::FromString(FString::Printf(TEXT("Locked: %s"),*RequiredChallengeID));
    }
    if (RequiredLevel>0) return FText::FromString(FString::Printf(TEXT("Locked: Level %d"),RequiredLevel));
    return FText::FromString(TEXT("Locked"));
}

}

void URecoveredPlayerCardEntryWidget::PopulatePlayerCard(
    FName InCardID,
    UTexture2D* InCardImage,
    const FString& InRequiredChallengeID,
    int32 InRequiredLevel,
    bool bInUnlocked,
    const FText& InChallengeDescription,
    const FText& InChallengeTitle,
    const FText& InCardName,
    const FLinearColor& InCardTint) {
    CardID=InCardID;
    SourceTexture=InCardImage;
    RequiredChallengeID=InRequiredChallengeID;
    RequiredLevel=InRequiredLevel;
    bUnlocked=bInUnlocked;
    ChallengeDescription=InChallengeDescription;
    ChallengeTitle=InChallengeTitle;
    CardName=InCardName;
    CardTint=InCardTint;
    ApplyPresentation();
}

TSharedRef<SWidget> URecoveredPlayerCardEntryWidget::RebuildWidget() {
    BuildWidgetTree();
    return Super::RebuildWidget();
}

void URecoveredPlayerCardEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
    ApplyPresentation();
}

void URecoveredPlayerCardEntryWidget::BuildWidgetTree() {
    if (!WidgetTree) WidgetTree=NewObject<UWidgetTree>(this,TEXT("WidgetTree"));
    if (WidgetTree->RootWidget) return;

    RootSize=WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(),TEXT("PlayerCardSize"));
    RootSize->SetWidthOverride(200.0f);
    RootSize->SetHeightOverride(44.444f);
    CardButton=WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(),TEXT("PlayerCardButton"));
    auto* Overlay=WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(),TEXT("PlayerCardOverlay"));
    CardImage=WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),TEXT("CardImage"));
    CardCaption=WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(),TEXT("CardCaption"));
    RequirementCaption=WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(),TEXT("RequirementCaption"));

    Overlay->AddChildToOverlay(CardImage);
    if (auto* OverlaySlot=Overlay->AddChildToOverlay(CardCaption)) {
        OverlaySlot->SetHorizontalAlignment(HAlign_Center);
        OverlaySlot->SetVerticalAlignment(VAlign_Bottom);
        OverlaySlot->SetPadding(FMargin(3.0f,0.0f));
    }
    if (auto* OverlaySlot=Overlay->AddChildToOverlay(RequirementCaption)) {
        OverlaySlot->SetHorizontalAlignment(HAlign_Center);
        OverlaySlot->SetVerticalAlignment(VAlign_Center);
        OverlaySlot->SetPadding(FMargin(3.0f,0.0f));
    }

    CardButton->SetContent(Overlay);
    CardButton->OnClicked.AddUniqueDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardClicked);
    RootSize->SetContent(CardButton);
    WidgetTree->RootWidget=RootSize;
}

void URecoveredPlayerCardEntryWidget::ApplyPresentation() {
    if (!CardImage || !CardCaption || !RequirementCaption) return;
    if (!LockedTexture) LockedTexture=GetLockedCardTexture();
    CardImage->SetBrushFromTexture(bUnlocked ? SourceTexture.Get() : LockedTexture.Get(),false);
    CardImage->SetColorAndOpacity(bUnlocked ? CardTint : FLinearColor(0.45f,0.45f,0.45f,1.0f));
    CardCaption->SetText(CardName);
    CardCaption->SetColorAndOpacity(FSlateColor::UseForeground());
    RequirementCaption->SetText(bUnlocked ? FText::GetEmpty() : GetRequirementText(RequiredChallengeID,RequiredLevel,ChallengeTitle));
    RequirementCaption->SetColorAndOpacity(FSlateColor(FLinearColor::White));
}

void URecoveredPlayerCardEntryWidget::HandleCardClicked() {
    OnClicked.Broadcast(CardID);
}
