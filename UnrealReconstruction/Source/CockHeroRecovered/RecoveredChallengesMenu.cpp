#include "RecoveredChallengesMenu.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "RecoveredModifierWidget.h"
#include "RecoveredRules.h"
#include "Sound/SoundBase.h"

namespace {

FSlateBrush MakeSourceChallengesBrush(
    ESlateBrushDrawType::Type DrawAs,
    const FLinearColor& Tint,
    const FLinearColor& Outline,
    float OutlineWidth,
    const FVector4& CornerRadii,
    ESlateBrushRoundingType::Type RoundingType,
    bool bUseBrushTransparency) {
    FSlateBrush Brush;
    Brush.DrawAs=DrawAs;
    Brush.Tiling=ESlateBrushTileType::NoTile;
    Brush.Mirroring=ESlateBrushMirrorType::NoMirror;
    Brush.ImageType=ESlateBrushImageType::FullColor;
    Brush.ImageSize=FVector2D(32,32);
    Brush.Margin=FMargin(0);
    Brush.TintColor=FSlateColor(Tint);
    Brush.OutlineSettings.CornerRadii=CornerRadii;
    Brush.OutlineSettings.Color=FSlateColor(Outline);
    Brush.OutlineSettings.Width=OutlineWidth;
    Brush.OutlineSettings.RoundingType=RoundingType;
    Brush.OutlineSettings.bUseBrushTransparency=bUseBrushTransparency;
    return Brush;
}

FButtonStyle MakeSourceChallengesStyle(bool bClicked) {
    constexpr float UnclickedNormal=0.0f;
    constexpr float ClickedNormal=0.24620099365711212f;
    constexpr float Hovered=0.7230550050735474f;
    constexpr float Pressed=0.3842659890651703f;
    constexpr float NormalOutline=0.6951109766960144f;
    constexpr float InteractiveOutline=0.7242680191993713f;
    FButtonStyle Style;
    Style.Normal=MakeSourceChallengesBrush(
        ESlateBrushDrawType::Box,
        FLinearColor(bClicked ? ClickedNormal : UnclickedNormal,bClicked ? ClickedNormal : UnclickedNormal,bClicked ? ClickedNormal : UnclickedNormal,1),
        FLinearColor(NormalOutline,NormalOutline,NormalOutline,1),
        1,
        FVector4(4,4,4,4),
        ESlateBrushRoundingType::FixedRadius,
        true);
    Style.Hovered=MakeSourceChallengesBrush(
        ESlateBrushDrawType::RoundedBox,
        FLinearColor(Hovered,Hovered,Hovered,1),
        FLinearColor(InteractiveOutline,InteractiveOutline,InteractiveOutline,1),
        1,
        FVector4(4,4,4,4),
        ESlateBrushRoundingType::FixedRadius,
        true);
    Style.Pressed=MakeSourceChallengesBrush(
        ESlateBrushDrawType::RoundedBox,
        FLinearColor(Pressed,Pressed,Pressed,1),
        FLinearColor(InteractiveOutline,InteractiveOutline,InteractiveOutline,1),
        1,
        FVector4(4,4,4,4),
        ESlateBrushRoundingType::FixedRadius,
        true);
    Style.Disabled=MakeSourceChallengesBrush(
        ESlateBrushDrawType::NoDrawType,
        FLinearColor::White,
        FLinearColor::Transparent,
        0,
        FVector4(0,0,0,1),
        ESlateBrushRoundingType::HalfHeightRadius,
        false);
    Style.Disabled.ImageSize=FVector2D::ZeroVector;
    const FSlateColor Cyan=FSlateColor(FLinearColor(0,1,1,1));
    Style.NormalForeground=Cyan;
    Style.HoveredForeground=Cyan;
    Style.PressedForeground=Cyan;
    Style.DisabledForeground=FSlateColor(FLinearColor(0.527114987373352f,0.527114987373352f,0.527114987373352f,1));
    Style.NormalPadding=FMargin(12,1.5f,12,1.5f);
    Style.PressedPadding=FMargin(12,1.5f,12,1.5f);
    if (USoundBase* Click=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/click1_sfx.click1_sfx"))) Style.PressedSlateSound.SetResourceObject(Click);
    if (USoundBase* Hover=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/click4_sfx.click4_sfx"))) Style.HoveredSlateSound.SetResourceObject(Hover);
    return Style;
}

}

void URecoveredChallengesMenu::NativeConstruct() {
    Super::NativeConstruct();
    InitializeRecoveredChallengesMenu();
}

void URecoveredChallengesMenu::InitializeRecoveredChallengesMenu() {
    RestoreSourceStyles();
    BindNavigation(true);
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"),Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage"))));
    }
}

void URecoveredChallengesMenu::NativeDestruct() {
    BindNavigation(false);
    Super::NativeDestruct();
}

void URecoveredChallengesMenu::BindNavigation(bool bBind) {
#define BIND_CHALLENGES(Name, Method) \
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredChallengesMenu::Method); \
        else Button->OnClicked.RemoveDynamic(this,&URecoveredChallengesMenu::Method); \
    }
    BIND_CHALLENGES("ChallengesButton",OpenChallengesTab)
    BIND_CHALLENGES("PlayerCardButton",OpenPlayerCardsTab)
    BIND_CHALLENGES("StatsButton",OpenStatsTab)
    BIND_CHALLENGES("ModifiersButton",OpenModifiersTab)
    BIND_CHALLENGES("BackButton",CloseChallengesMenu)
#undef BIND_CHALLENGES
    if (auto* BackButton=Cast<UButton>(GetWidgetFromName(TEXT("BackButton")))) {
        if (bBind) {
            BackButton->OnHovered.AddUniqueDynamic(this,&URecoveredChallengesMenu::PlayBackButtonHover);
            BackButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredChallengesMenu::PlayBackButtonUnhover);
        } else {
            BackButton->OnHovered.RemoveDynamic(this,&URecoveredChallengesMenu::PlayBackButtonHover);
            BackButton->OnUnhovered.RemoveDynamic(this,&URecoveredChallengesMenu::PlayBackButtonUnhover);
        }
    }
}

void URecoveredChallengesMenu::RestoreSourceStyles() {
    UnclickedStyle=MakeSourceChallengesStyle(false);
    ClickedStyle=MakeSourceChallengesStyle(true);
}

void URecoveredChallengesMenu::SelectTab(int32 Index,const TCHAR* ActiveButton) {
    if (auto* Switcher=Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher")))) Switcher->SetActiveWidgetIndex(Index);
    const TCHAR* Names[]={TEXT("ChallengesButton"),TEXT("PlayerCardButton"),TEXT("StatsButton"),TEXT("ModifiersButton")};
    for (const TCHAR* Name:Names) {
        if (auto* Button=Cast<UButton>(GetWidgetFromName(Name))) Button->SetStyle(FCString::Strcmp(Name,ActiveButton)==0 ? ClickedStyle : UnclickedStyle);
    }
}

void URecoveredChallengesMenu::OpenChallengesTab() {
    SelectTab(0,TEXT("ChallengesButton"));
}

void URecoveredChallengesMenu::OpenPlayerCardsTab() {
    SelectTab(1,TEXT("PlayerCardButton"));
}

void URecoveredChallengesMenu::OpenStatsTab() {
    SelectTab(2,TEXT("StatsButton"));
}

void URecoveredChallengesMenu::OpenModifiersTab() {
    SelectTab(3,TEXT("ModifiersButton"));
    if (auto* Modifiers=Cast<URecoveredModifierWidget>(GetWidgetFromName(TEXT("ModifiersTabWidget")))) Modifiers->RefreshModifierList();
}

void URecoveredChallengesMenu::CloseChallengesMenu() {
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) Instance->RefreshRecoveredMainMenuBackground();
    RemoveFromParent();
}

void URecoveredChallengesMenu::PlayBackButtonHover() {
    PlayRecoveredAnimation(TEXT("HoverBackButton"));
}

void URecoveredChallengesMenu::PlayBackButtonUnhover() {
    PlayRecoveredAnimation(TEXT("UnhoverBackButton"));
}
