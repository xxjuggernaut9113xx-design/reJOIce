#include "RecoveredModifierCardEntryWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Kismet/GameplayStatics.h"
#include "MovieScene.h"
#include "RecoveredMenu.h"
#include "Sound/SoundBase.h"

namespace {
constexpr TCHAR ModifierTooltipClassPath[]=TEXT("/Game/Recovery/UI/CustomToolTip_Widget.CustomToolTip_Widget_C");
constexpr TCHAR OnSoundPath[]=TEXT("/Game/Recovery/Resources/Audio/ontoggle2.ontoggle2");
constexpr TCHAR OffSoundPath[]=TEXT("/Game/Recovery/Resources/Audio/offtoggle.offtoggle");
UWidgetAnimation* FindAnimation(const UUserWidget* Widget,FName Name) {
    const auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Widget->GetClass());
    if (!Generated) return nullptr;
    const FName Instance(*FString::Printf(TEXT("%s_INST"),*Name.ToString()));
    for (UWidgetAnimation* Animation:Generated->Animations) {
        if (!Animation) continue;
        const UMovieScene* Scene=Animation->GetMovieScene();
        if (Animation->GetFName()==Name || Animation->GetFName()==Instance || (Scene && (Scene->GetFName()==Name || Scene->GetFName()==Instance))) return Animation;
    }
    return nullptr;
}
}

void URecoveredModifierCardEntryWidget::NativeOnInitialized() { Super::NativeOnInitialized(); ApplyPresentation(); }
void URecoveredModifierCardEntryWidget::NativeConstruct() { Super::NativeConstruct(); ApplyPresentation(); }
void URecoveredModifierCardEntryWidget::NativeDestruct() {
    if (SourceBackgroundButton) { SourceBackgroundButton->OnHovered.RemoveDynamic(this,&URecoveredModifierCardEntryWidget::HandleBackgroundHover); SourceBackgroundButton->OnUnhovered.RemoveDynamic(this,&URecoveredModifierCardEntryWidget::HandleBackgroundUnhover); }
    if (SourceToggleButton) { SourceToggleButton->OnHovered.RemoveDynamic(this,&URecoveredModifierCardEntryWidget::HandleToggleHover); SourceToggleButton->OnUnhovered.RemoveDynamic(this,&URecoveredModifierCardEntryWidget::HandleToggleUnhover); SourceToggleButton->OnClicked.RemoveDynamic(this,&URecoveredModifierCardEntryWidget::HandleToggleClick); }
    Tooltips.Reset(); TooltipTargets.Reset(); Super::NativeDestruct();
}
void URecoveredModifierCardEntryWidget::BindSourceTree() {
    if (!SourceBackgroundButton) SourceBackgroundButton=Cast<UButton>(GetWidgetFromName(TEXT("BackgroundButton")));
    if (!SourceToggleButton) SourceToggleButton=Cast<UButton>(GetWidgetFromName(TEXT("ToggleModifierButton")));
    if (!SourceLockOverlay) SourceLockOverlay=Cast<UBorder>(GetWidgetFromName(TEXT("LockOverlay")));
    if (!SourceModifierIcon) SourceModifierIcon=Cast<UImage>(GetWidgetFromName(TEXT("ModifierIcon")));
    if (!SourceModifierTitle) SourceModifierTitle=Cast<UTextBlock>(GetWidgetFromName(TEXT("ModifierTitle")));
    if (!SourceModifierDescription) SourceModifierDescription=Cast<UTextBlock>(GetWidgetFromName(TEXT("ModifierDescription")));
    if (!SourceChallengeRequirement) SourceChallengeRequirement=Cast<UTextBlock>(GetWidgetFromName(TEXT("ChallengeRequiredText")));
    if (!SourceButtonText) SourceButtonText=Cast<UTextBlock>(GetWidgetFromName(TEXT("ButtonText")));
    for (const TCHAR* Name : { TEXT("SizeBox_15"), TEXT("VerticalBox_149"), TEXT("LockOverlay"), TEXT("Overlay_388") }) {
        if (UWidget* Target=GetWidgetFromName(Name)) TooltipTargets.AddUnique(Target);
    }
}
void URecoveredModifierCardEntryWidget::BindSourceEvents() {
    BindSourceTree();
    if (SourceBackgroundButton) { SourceBackgroundButton->OnHovered.AddUniqueDynamic(this,&URecoveredModifierCardEntryWidget::HandleBackgroundHover); SourceBackgroundButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredModifierCardEntryWidget::HandleBackgroundUnhover); }
    if (SourceToggleButton) { SourceToggleButton->OnHovered.AddUniqueDynamic(this,&URecoveredModifierCardEntryWidget::HandleToggleHover); SourceToggleButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredModifierCardEntryWidget::HandleToggleUnhover); SourceToggleButton->OnClicked.AddUniqueDynamic(this,&URecoveredModifierCardEntryWidget::HandleToggleClick); }
}
void URecoveredModifierCardEntryWidget::PopulateDetails(bool bInUnlocked,bool bInEnabled,const FText& InTitle,UTexture2D* InIcon,const FText& InDescription,const FText& InChallengeTitle,const FText& InChallengeDescription) {
    bUnlocked=bInUnlocked; bEnabled=bInEnabled; StoredTitle=InTitle; SourceModifierTexture=InIcon; StoredDescription=InDescription; StoredChallengeTitle=InChallengeTitle; StoredChallengeDescription=InChallengeDescription;
    ApplyPresentation();
}
void URecoveredModifierCardEntryWidget::ApplyPresentation() {
    BindSourceEvents();
    if (SourceModifierTitle) SourceModifierTitle->SetText(StoredTitle);
    if (SourceModifierIcon) SourceModifierIcon->SetBrushFromTexture(SourceModifierTexture.Get(),false);
    if (SourceModifierDescription) SourceModifierDescription->SetText(StoredDescription);
    if (SourceChallengeRequirement) SourceChallengeRequirement->SetText(FText::FromString(FString::Printf(TEXT("Complete:\r\n\"%s\"\r\nChallenge"),*StoredChallengeTitle.ToString())));
    if (SourceLockOverlay) SourceLockOverlay->SetVisibility(bUnlocked ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    SetButtonToggle(bEnabled); ApplyTooltip();
}
void URecoveredModifierCardEntryWidget::SetButtonToggle(bool bInEnabled) { bEnabled=bInEnabled; if (!SourceButtonText) { BindSourceTree(); if (!SourceButtonText) return; } SourceButtonText->SetText(FText::FromString(bEnabled?TEXT("Enabled"):TEXT("Disabled"))); SourceButtonText->SetColorAndOpacity(bEnabled?FLinearColor(0.0f,0.52099597f,0.12477199f,1.0f):FLinearColor(1.0f,0.015209f,0.012983f,1.0f)); }
void URecoveredModifierCardEntryWidget::SetButtonToggleWithSound(bool bInEnabled) { SetButtonToggle(bInEnabled); PlaySourceSound(bInEnabled?OnSoundPath:OffSoundPath,0.5f,bInEnabled?1.5f:0.85f,bInEnabled?0.1f:0.0f); }
void URecoveredModifierCardEntryWidget::ApplyTooltip() {
    if (TooltipTargets.IsEmpty()) BindSourceTree();
    if (TooltipTargets.IsEmpty()) return;
    UClass* Class=LoadClass<URecoveredTooltip>(nullptr,ModifierTooltipClassPath);
    if (!Class) return;
    Tooltips.SetNum(TooltipTargets.Num());
    const FText Title=FText::FromString(StoredTitle.ToString()+(bUnlocked?TEXT(" - Unlocked"):TEXT(" - Locked")));
    const FText Description=bUnlocked?StoredDescription:StoredChallengeDescription;
    for (int32 Index=0;Index<TooltipTargets.Num();++Index) {
        UWidget* Target=TooltipTargets[Index].Get();
        if (!Target) continue;
        URecoveredTooltip* Tooltip=Tooltips[Index].Get();
        if (!Tooltip || !Tooltip->IsA(Class)) Tooltip=Cast<URecoveredTooltip>(UUserWidget::CreateWidgetInstance(*Target,Class,NAME_None));
        if (!Tooltip) continue;
        Tooltip->SetTitleAndDescription(Title,Description);
        Target->SetToolTip(Tooltip);
        Tooltips[Index]=Tooltip;
    }
}
void URecoveredModifierCardEntryWidget::PlaySourceAnimation(FName Name) { if (UWidgetAnimation* Animation=FindAnimation(this,Name)) PlayAnimation(Animation,0.0f,1,EUMGSequencePlayMode::Forward,1.0f,false); }
void URecoveredModifierCardEntryWidget::PlaySourceSound(const TCHAR* Path,float Volume,float Pitch,float StartTime) const { if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,Path)) if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,Volume,Pitch,StartTime,nullptr,nullptr,true); }
void URecoveredModifierCardEntryWidget::HandleBackgroundHover() { PlaySourceAnimation(TEXT("HoverModifier")); }
void URecoveredModifierCardEntryWidget::HandleBackgroundUnhover() { PlaySourceAnimation(TEXT("UnHoverModifier")); }
void URecoveredModifierCardEntryWidget::HandleToggleHover() { PlaySourceAnimation(TEXT("HoverButton")); }
void URecoveredModifierCardEntryWidget::HandleToggleUnhover() { PlaySourceAnimation(TEXT("UnHoverButton")); }
void URecoveredModifierCardEntryWidget::HandleToggleClick() { PlaySourceAnimation(TEXT("ClickButton")); OnCardClicked.Broadcast(StoredTitle,this); }
