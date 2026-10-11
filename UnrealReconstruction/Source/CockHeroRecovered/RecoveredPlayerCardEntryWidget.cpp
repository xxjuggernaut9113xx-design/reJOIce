#include "RecoveredPlayerCardEntryWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Components/ScaleBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Engine/Font.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "MovieScene.h"
#include "RecoveredMenu.h"
#include "Sound/SoundBase.h"
#include "Styling/SlateTypes.h"

namespace {

constexpr TCHAR LockedTexturePath[]=TEXT("/Game/Recovery/Resources/PlayerCards/LockedPlayerCard.LockedPlayerCard");
constexpr TCHAR TooltipClassPath[]=TEXT("/Game/Recovery/UI/CustomToolTip_Widget.CustomToolTip_Widget_C");
constexpr TCHAR HorizonFontPath[]=TEXT("/Game/Recovery/Resources/Fonts/horizon_Font.horizon_Font");
constexpr TCHAR HoverSoundPath[]=TEXT("/Game/Recovery/Resources/Audio/click4_sfx.click4_sfx");
constexpr TCHAR ClickSoundPath[]=TEXT("/Game/Recovery/Resources/Audio/Juice_SFX__12_.Juice_SFX__12_");
constexpr TCHAR RejectedClickSoundPath[]=TEXT("/Game/Recovery/Resources/Audio/anime-46068.anime-46068");

UTexture2D* GetLockedCardTexture() {
    return LoadObject<UTexture2D>(nullptr,LockedTexturePath);
}

FText GetRequirementText(const FString& RequiredChallengeID) {
    const FString Challenge=RequiredChallengeID.Replace(TEXT("_"),TEXT(" "));
    return FText::FromString(FString::Printf(TEXT("Complete Challenge: \r\n\"%s\""),*Challenge));
}

FText GetLockedTooltipTitle(const FText& CardName) {
    return FText::FromString(CardName.ToString()+TEXT(" - locked"));
}

FText GetLockedTooltipDescription(const FText& ChallengeDescription,const FText& CardName) {
    FFormatNamedArguments Arguments;
    Arguments.Add(TEXT("card name"),CardName);
    return FText::Format(ChallengeDescription,Arguments);
}

FButtonStyle MakeSourceCardStyle(UTexture2D* Texture) {
    FSlateBrush Brush;
    Brush.SetResourceObject(Texture);
    Brush.DrawAs=ESlateBrushDrawType::Image;
    Brush.Tiling=ESlateBrushTileType::NoTile;
    Brush.Mirroring=ESlateBrushMirrorType::NoMirror;
    Brush.ImageSize=FVector2D(32.0f,32.0f);
    Brush.Margin=FMargin(0.0f);
    Brush.TintColor=FSlateColor(FLinearColor::White);
    Brush.OutlineSettings.CornerRadii=FVector4(0.0,0.0,0.0,1.0);
    Brush.OutlineSettings.Color=FSlateColor(FLinearColor::Transparent);
    Brush.OutlineSettings.Width=0.0f;
    Brush.OutlineSettings.RoundingType=ESlateBrushRoundingType::HalfHeightRadius;
    Brush.OutlineSettings.bUseBrushTransparency=false;

    FButtonStyle Style;
    Style.Normal=Brush;
    Style.Hovered=Brush;
    Style.Pressed=Brush;
    Style.Disabled=FSlateBrush();
    const FSlateColor Foreground=FSlateColor::UseForeground();
    Style.NormalForeground=Foreground;
    Style.HoveredForeground=Foreground;
    Style.PressedForeground=Foreground;
    Style.DisabledForeground=Foreground;
    Style.NormalPadding=FMargin(0.0f);
    Style.PressedPadding=FMargin(0.0f);
    Style.PressedSlateSound=FSlateSound();
    Style.HoveredSlateSound=FSlateSound();
    return Style;
}

UWidgetAnimation* FindSourceAnimation(const UUserWidget* Widget,FName AnimationName) {
    const auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Widget->GetClass());
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
    BindSourceInteractions();
    ApplyPresentation();
}

void URecoveredPlayerCardEntryWidget::NativeDestruct() {
    if (SourceCardButton) {
        SourceCardButton->OnHovered.RemoveDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardHovered);
        SourceCardButton->OnUnhovered.RemoveDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardUnhovered);
        SourceCardButton->OnClicked.RemoveDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardClicked);
    }
    CardTooltip=nullptr;
    Super::NativeDestruct();
}

void URecoveredPlayerCardEntryWidget::BuildWidgetTree() {
    if (!WidgetTree) WidgetTree=NewObject<UWidgetTree>(this,TEXT("WidgetTree"));
    if (WidgetTree->RootWidget) {
        BindRecoveredWidgetTree();
        return;
    }

    RootSize=WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(),TEXT("SizeBox_60"));
    RootSize->SetWidthOverride(613.0f);
    RootSize->SetHeightOverride(136.0f);
    auto* CardBorder=WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(),TEXT("Border_0"));
    SourceCardButton=WidgetTree->ConstructWidget<UButton>(UButton::StaticClass(),TEXT("PlayerCardButton"));
    SourceLockOverlay=WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(),TEXT("LockOverlay"));
    auto* Darkening=WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(),TEXT("Border_122"));
    Darkening->SetPadding(FMargin(0.0f));
    Darkening->SetBrushColor(FLinearColor(0.0f,0.0f,0.0f,0.5f));
    auto* LockScale=WidgetTree->ConstructWidget<UScaleBox>(UScaleBox::StaticClass(),TEXT("ScaleBox_1"));
    auto* LockSize=WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(),TEXT("SizeBox_1"));
    LockSize->SetWidthOverride(600.0f);
    auto* LockRow=WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(),TEXT("HorizontalBox_76"));
    auto* LeftLock=WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),TEXT("Image_257"));
    auto* RightLock=WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),TEXT("Image_86"));
    auto* RequirementSize=WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(),TEXT("SizeBox_0"));
    RequirementSize->SetWidthOverride(586.0f);
    auto* RequirementScale=WidgetTree->ConstructWidget<UScaleBox>(UScaleBox::StaticClass(),TEXT("ScaleBox_0"));
    RequirementCaption=WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(),TEXT("UnlockRequirementText"));
    RequirementCaption->SetJustification(ETextJustify::Center);
    FSlateFontInfo Font;
    Font.FontObject=LoadObject<UObject>(nullptr,HorizonFontPath);
    Font.TypefaceFontName=TEXT("Default");
    Font.Size=16.5f;
    RequirementCaption->SetFont(Font);

    if (!LockedTexture) LockedTexture=GetLockedCardTexture();
    for (UImage* Lock:{LeftLock,RightLock}) {
        Lock->SetBrushFromTexture(LockedTexture.Get(),false);
        FWidgetTransform Transform;
        Transform.Scale=FVector2D(1.5f,1.5f);
        Lock->SetRenderTransform(Transform);
    }
    if (auto* ChildSlot=LockRow->AddChildToHorizontalBox(LeftLock)) ChildSlot->SetPadding(FMargin(32.0f,0.0f));
    if (auto* ChildSlot=LockRow->AddChildToHorizontalBox(RequirementSize)) ChildSlot->SetSize(FSlateChildSize(ESlateSizeRule::Fill));
    if (auto* ChildSlot=LockRow->AddChildToHorizontalBox(RightLock)) ChildSlot->SetPadding(FMargin(32.0f,0.0f));
    RequirementScale->SetContent(RequirementCaption);
    RequirementSize->SetContent(RequirementScale);
    LockSize->SetContent(LockRow);
    LockScale->SetContent(LockSize);
    if (auto* OverlayChildSlot=SourceLockOverlay->AddChildToOverlay(Darkening)) {
        OverlayChildSlot->SetHorizontalAlignment(HAlign_Fill);
        OverlayChildSlot->SetVerticalAlignment(VAlign_Fill);
    }
    if (auto* OverlayChildSlot=SourceLockOverlay->AddChildToOverlay(LockScale)) {
        OverlayChildSlot->SetHorizontalAlignment(HAlign_Center);
        OverlayChildSlot->SetVerticalAlignment(VAlign_Center);
    }
    SourceCardButton->SetContent(SourceLockOverlay);
    CardBorder->SetContent(SourceCardButton);
    RootSize->SetContent(CardBorder);
    WidgetTree->RootWidget=RootSize;
}

void URecoveredPlayerCardEntryWidget::BindRecoveredWidgetTree() {
    if (!RootSize) RootSize=Cast<USizeBox>(GetWidgetFromName(TEXT("SizeBox_60")));
    if (!SourceCardButton) SourceCardButton=Cast<UButton>(GetWidgetFromName(TEXT("PlayerCardButton")));
    if (!SourceLockOverlay) SourceLockOverlay=Cast<UOverlay>(GetWidgetFromName(TEXT("LockOverlay")));
    if (!RequirementCaption) RequirementCaption=Cast<UTextBlock>(GetWidgetFromName(TEXT("UnlockRequirementText")));
}

void URecoveredPlayerCardEntryWidget::BindSourceInteractions() {
    BindRecoveredWidgetTree();
    if (!SourceCardButton) return;
    SourceCardButton->OnHovered.AddUniqueDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardHovered);
    SourceCardButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardUnhovered);
    SourceCardButton->OnClicked.AddUniqueDynamic(this,&URecoveredPlayerCardEntryWidget::HandleCardClicked);
}

void URecoveredPlayerCardEntryWidget::ApplySourceCardStyle() {
    if (SourceCardButton) SourceCardButton->SetStyle(MakeSourceCardStyle(SourceTexture.Get()));
}

void URecoveredPlayerCardEntryWidget::ApplySourceTooltip() {
    if (!SourceCardButton) return;
    UClass* TooltipClass=LoadClass<URecoveredTooltip>(nullptr,TooltipClassPath);
    if (!TooltipClass) return;
    if (!CardTooltip || !CardTooltip->IsA(TooltipClass)) {
        CardTooltip=Cast<URecoveredTooltip>(
            UUserWidget::CreateWidgetInstance(*SourceCardButton,TooltipClass,NAME_None));
    }
    if (!CardTooltip) return;
    CardTooltip->SetTitleAndDescription(
        bUnlocked ? CardName : GetLockedTooltipTitle(CardName),
        bUnlocked ? FText::FromString(TEXT("Unlocked")) : GetLockedTooltipDescription(ChallengeDescription,CardName));
    SourceCardButton->SetToolTip(CardTooltip);
}

void URecoveredPlayerCardEntryWidget::ApplyPresentation() {
    BindSourceInteractions();
    if (!SourceCardButton || !SourceLockOverlay || !RequirementCaption) return;
    ApplySourceCardStyle();
    SourceLockOverlay->SetVisibility(bUnlocked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    if (!bUnlocked) RequirementCaption->SetText(GetRequirementText(RequiredChallengeID));
    ApplySourceTooltip();
}

void URecoveredPlayerCardEntryWidget::PlaySourceAnimation(FName AnimationName) {
    if (UWidgetAnimation* Animation=FindSourceAnimation(this,AnimationName)) PlayAnimation(Animation,0.0f,1,EUMGSequencePlayMode::Forward,1.0f,false);
}

void URecoveredPlayerCardEntryWidget::PlaySourceSound(const TCHAR* AssetPath,float VolumeMultiplier,float PitchMultiplier) const {
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,AssetPath)) {
        if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,VolumeMultiplier,PitchMultiplier,0.0f,nullptr,nullptr,true);
    }
}

void URecoveredPlayerCardEntryWidget::HandleCardHovered() {
    PlaySourceAnimation(TEXT("Hover"));
    PlaySourceSound(HoverSoundPath,1.0f,1.0f);
}

void URecoveredPlayerCardEntryWidget::HandleCardUnhovered() {
    PlaySourceAnimation(TEXT("Unhover"));
}

void URecoveredPlayerCardEntryWidget::HandleCardClicked() {
    OnClicked.Broadcast(CardID);
    if (bUnlocked) {
        PlaySourceAnimation(TEXT("Click"));
        PlaySourceSound(ClickSoundPath,2.0f,1.3f);
    } else {
        PlaySourceAnimation(TEXT("UnsuccessfulClick"));
        PlaySourceSound(RejectedClickSoundPath,0.8f,0.9f);
    }
}
