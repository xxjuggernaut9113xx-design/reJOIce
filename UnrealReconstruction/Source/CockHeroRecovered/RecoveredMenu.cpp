#include "RecoveredMenu.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "HAL/PlatformProcess.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Texture2D.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"

void URecoveredTooltip::SetTitleAndDescription(const FText& Title,const FText& Description) {
    TooltipTitle=Title;TooltipDescription=Description;
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")))) Label->SetText(Title);
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")))) Label->SetText(Description);
}
void URecoveredTooltip::NativeConstruct() { Super::NativeConstruct(); SetTitleAndDescription(TooltipTitle,TooltipDescription); }
void URecoveredMenuWidget::NativeConstruct() { Super::NativeConstruct(); AttachRecoveredTooltips(); }
void URecoveredMenuWidget::AttachRecoveredTooltips() {
    if (StaticTooltips.IsEmpty() || !GetWorld()) return;
    UClass* TooltipClass=LoadClass<URecoveredTooltip>(nullptr,TEXT("/Game/Recovery/UI/CustomToolTip_Widget.CustomToolTip_Widget_C"));
    if (!TooltipClass) return;
    for (const auto& Pair:StaticTooltips) {
        UWidget* Target=GetWidgetFromName(Pair.Key);
        if (!Target) continue;
        // Retain the tooltip instance across repeated construct/attach calls.
        auto* Tooltip=Cast<URecoveredTooltip>(Target->GetToolTip());
        if (!Tooltip) Tooltip=CreateWidget<URecoveredTooltip>(GetWorld(),TooltipClass);
        if (!Tooltip) continue;
        Tooltip->SetTitleAndDescription(Pair.Value.Title,Pair.Value.Description);
        Target->SetToolTip(Tooltip);
    }
}

void URecoveredMainMenu::BindNavigation(bool bBind) {
    // MainMenu's component-bound events name these widgets explicitly.
#define BIND_ROUTE(Name, Method) \
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredMainMenu::Method); \
        else Button->OnClicked.RemoveDynamic(this,&URecoveredMainMenu::Method); \
    }
    BIND_ROUTE("StartGameButton",OpenDifficulty)
    BIND_ROUTE("StatsButton",OpenChallenges)
    BIND_ROUTE("Settings",OpenSettings)
    BIND_ROUTE("UnlockStoreButton",OpenUnlockStore)
    BIND_ROUTE("AdultContentWarningSplashButton",CloseAdultWarning)
    BIND_ROUTE("TutorialSplashButton",CloseTutorialSplash)
    BIND_ROUTE("NewUpdateSplashButton",CloseUpdateSplash)
    BIND_ROUTE("Quit",QuitFromMenu)
#undef BIND_ROUTE
}
void URecoveredMainMenu::NativeConstruct() {
    Super::NativeConstruct();BindNavigation(true);InitCoverGirl();
    if (GetWorld()) { PlayRecoveredAnimation(TEXT("MainTextIdle"),0);PlayRecoveredAnimation(TEXT("CoverGirlIdle"),0); }
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance) {
        if (Instance->bHasGameOpenedInSession) {
            for (FName Name:{FName(TEXT("AdultContentWarningSplashButton")),FName(TEXT("TutorialSplashButton")),FName(TEXT("NewUpdateSplashButton"))}) if (auto* Widget=GetWidgetFromName(Name)) Widget->SetVisibility(ESlateVisibility::Hidden);
        } else Instance->bHasGameOpenedInSession=true;
        if (Instance->CurrentSave && Instance->CurrentSave->GetBoolSetting(TEXT("HasSeenSplashes?"))) {
            CloseTutorialSplash();if (auto* Widget=GetWidgetFromName(TEXT("NewUpdateSplashButton"))) Widget->RemoveFromParent();
        }
        if (Instance->CurrentSave) if (auto* Title=Cast<UTextBlock>(GetWidgetFromName(TEXT("MainMenuTitleText")))) Title->SetText(Instance->CurrentSave->GetTextSetting(TEXT("SelectedTitleText"),FText::GetEmpty()));
        RefreshBackground();
    }
}
void URecoveredMainMenu::InitCoverGirl() {
    auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CoverGirlButton")));
    if (!Button || PatreonCoverGirlArray.IsEmpty()) return;
    // Values from the original branch-free InitCoverGirl Blueprint bytecode.
    FSlateBrush Brush;
    Brush.SetResourceObject(PatreonCoverGirlArray[FMath::RandRange(0,PatreonCoverGirlArray.Num()-1)]);
    Brush.DrawAs=ESlateBrushDrawType::Image;
    Brush.Tiling=ESlateBrushTileType::NoTile;
    Brush.Mirroring=ESlateBrushMirrorType::NoMirror;
    Brush.ImageSize=FVector2D(32,32);
    Brush.Margin=FMargin(0);
    Brush.TintColor=FSlateColor(FLinearColor::White);
    Brush.OutlineSettings.CornerRadii=FVector4(0,0,0,1);
    Brush.OutlineSettings.Color=FSlateColor(FLinearColor::Transparent);
    Brush.OutlineSettings.Width=0;
    Brush.OutlineSettings.RoundingType=ESlateBrushRoundingType::HalfHeightRadius;
    Brush.OutlineSettings.bUseBrushTransparency=false;
    FButtonStyle Style;
    Style.Normal=Brush; Style.Hovered=Brush; Style.Pressed=Brush; Style.Disabled=Brush;
    const FSlateColor Foreground=FSlateColor::UseForeground();
    Style.NormalForeground=Foreground; Style.HoveredForeground=Foreground;
    Style.PressedForeground=Foreground; Style.DisabledForeground=Foreground;
    Style.NormalPadding=FMargin(0); Style.PressedPadding=FMargin(0);
    Style.PressedSlateSound=FSlateSound(); Style.HoveredSlateSound=FSlateSound();
    Button->SetStyle(Style);
}
void URecoveredMainMenu::NativeDestruct() { if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(WarningTimer);BindNavigation(false); Super::NativeDestruct(); }
void URecoveredMainMenu::OpenScreen(const TCHAR* ScreenName) {
    LastNavigationError.Reset();
    const FString Path=FString::Printf(TEXT("/Game/Recovery/UI/%s.%s_C"),ScreenName,ScreenName);
    UClass* ScreenClass=LoadClass<UUserWidget>(nullptr,*Path);
    if (!ScreenClass || !GetWorld()) { LastNavigationError=TEXT("Recovered screen or world unavailable: ")+Path; return; }
    UUserWidget* Screen=CreateWidget<UUserWidget>(GetWorld(),ScreenClass);
    if (!Screen) { LastNavigationError=TEXT("Could not create recovered screen: ")+Path; return; }
    LastOpenedScreen=Screen;
    Screen->AddToViewport(0);
    // Source handlers keep the main menu behind the new screen.
}
void URecoveredMainMenu::OpenDifficulty() {
    // The original Start handler first casts GetGameMode to BP_GlobalManager.
    if (!Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this))) {
        LastNavigationError=TEXT("Start requires the recovered global game mode"); return;
    }
    OpenScreen(TEXT("DifficultySelectScreen_Widget"));
}
void URecoveredMainMenu::OpenChallenges() { OpenScreen(TEXT("ChallengesMenuWidget")); }
void URecoveredMainMenu::OpenSettings() { OpenScreen(TEXT("SettingsMenuWidget")); }
void URecoveredMainMenu::OpenUnlockStore() { OpenScreen(TEXT("UnlockStoreWidget")); }

void URecoveredDifficultyMenu::BindNavigation(bool bBind) {
#define BIND_DIFFICULTY(Name, Method) \
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredDifficultyMenu::Method); \
        else Button->OnClicked.RemoveDynamic(this,&URecoveredDifficultyMenu::Method); \
    }
    BIND_DIFFICULTY("EasyDifficultyButton",SelectEasy)
    BIND_DIFFICULTY("NormalDifficultyButton",SelectNormal)
    BIND_DIFFICULTY("InsaneDifficultyButton",SelectInsane)
    BIND_DIFFICULTY("BackButton",CloseDifficulty)
#undef BIND_DIFFICULTY
}
void URecoveredDifficultyMenu::NativeConstruct() { Super::NativeConstruct(); BindNavigation(true); }
void URecoveredDifficultyMenu::NativeDestruct() {
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(SelectionTimer);
    bSelectionPending=false; BindNavigation(false); Super::NativeDestruct();
}
void URecoveredDifficultyMenu::SelectEasy() { SelectDifficulty(0); }
void URecoveredDifficultyMenu::SelectNormal() { SelectDifficulty(1); }
void URecoveredDifficultyMenu::SelectInsane() { SelectDifficulty(2); }
void URecoveredDifficultyMenu::CloseDifficulty() { RemoveFromParent(); }
void URecoveredDifficultyMenu::SelectDifficulty(uint8 Difficulty) {
    if (bSelectionPending) return;
    LastStartError.Reset();
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager || !GetWorld()) { LastStartError=TEXT("Difficulty selection requires the recovered game mode"); return; }
    Manager->CurrentDifficulty=static_cast<ERecoveredDifficulty>(Difficulty);
    bSelectionPending=true;
    GetWorld()->GetTimerManager().SetTimer(SelectionTimer,this,&URecoveredDifficultyMenu::CompleteSelection,0.20000000298023224f,false);
}
void URecoveredDifficultyMenu::CompleteSelection() {
    bSelectionPending=false;
    auto* Manager=Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this));
    if (!Manager) { LastStartError=TEXT("Recovered game mode became unavailable"); return; }
    if (!Manager->InitializeRecoveredSession()) { LastStartError=Manager->LastSessionError; return; }
    StopAllAnimations();
    if (Manager->MainMenu) Manager->MainMenu->RemoveFromParent();
    RemoveFromParent();
}

void URecoveredVoiceSettings::StopAudioComponent() { if (IsValid(AudioComponent)) AudioComponent->Stop(); }
void URecoveredSettingsMenu::BindNavigation(bool bBind) {
#define BIND_TAB(Name, Method) \
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSettingsMenu::Method); \
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSettingsMenu::Method); \
    }
    BIND_TAB("VideoSettingsButton",OpenVideoTab)
    BIND_TAB("AudioSettingsButton",OpenAudioTab)
    BIND_TAB("TagsSettingsButton",OpenTagsTab)
    BIND_TAB("VoiceSettingsButton",OpenVoiceTab)
    BIND_TAB("ToysSettingsButton",OpenToysTab)
    BIND_TAB("BackButton",CloseSettings)
#undef BIND_TAB
}
bool URecoveredSettingsMenu::IsPatron() const {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    return Instance && Instance->CurrentSave && Instance->CurrentSave->GetBoolSetting(TEXT("IsPatron?"));
}
void URecoveredSettingsMenu::NativeConstruct() {
    Super::NativeConstruct(); BindNavigation(true);
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        OnBackgroundMediaRequested.AddUniqueDynamic(Instance,&URecoveredGameInstance::PlayRecoveredBackgroundMedia);
        OnMainMenuBackgroundRefreshRequested.AddUniqueDynamic(Instance,&URecoveredGameInstance::RefreshRecoveredMainMenuBackground);
        ApplyPatronLocks();
        OnBackgroundMediaRequested.Broadcast(TEXT("backgroundmenuloop"),Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage"))));
    }
}
void URecoveredSettingsMenu::NativeDestruct() { BindNavigation(false); Super::NativeDestruct(); }
void URecoveredSettingsMenu::ApplyPatronLocks() {
    // Original true branch does nothing; it does not reset prior lock visuals.
    if (IsPatron()) return;
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("ToysTextBlock")))) Text->SetOpacity(0.5f);
    if (UWidget* Lock=GetWidgetFromName(TEXT("PatreonLock"))) Lock->SetVisibility(ESlateVisibility::Visible);
}
void URecoveredSettingsMenu::StopVoicePreview() {
    if (auto* Voice=Cast<URecoveredVoiceSettings>(GetWidgetFromName(TEXT("VoicelineSettingsMenu")))) Voice->StopAudioComponent();
}
void URecoveredSettingsMenu::SelectTab(int32 Index,const TCHAR* ButtonName,bool bStopPreview) {
    if (auto* Switcher=Cast<UWidgetSwitcher>(GetWidgetFromName(TEXT("WidgetSwitcher")))) Switcher->SetActiveWidgetIndex(Index);
    if (bStopPreview) StopVoicePreview();
    const TCHAR* Names[]={TEXT("VideoSettingsButton"),TEXT("AudioSettingsButton"),TEXT("TagsSettingsButton"),TEXT("VoiceSettingsButton"),TEXT("ToysSettingsButton")};
    for (const TCHAR* Name:Names) if (auto* Button=Cast<UButton>(GetWidgetFromName(Name))) Button->SetStyle(FCString::Strcmp(Name,ButtonName)==0 ? ClickedStyle : UnclickedStyle);
}
void URecoveredSettingsMenu::OpenVideoTab() { SelectTab(0,TEXT("VideoSettingsButton"),true); }
void URecoveredSettingsMenu::OpenAudioTab() { SelectTab(4,TEXT("AudioSettingsButton"),true); }
void URecoveredSettingsMenu::OpenTagsTab() { SelectTab(2,TEXT("TagsSettingsButton"),true); }
void URecoveredSettingsMenu::OpenVoiceTab() { SelectTab(3,TEXT("VoiceSettingsButton"),false); }
void URecoveredSettingsMenu::OpenToysTab() {
    // Unlike other tabs, the source stops preview before checking access.
    StopVoicePreview();
    if (IsPatron()) SelectTab(1,TEXT("ToysSettingsButton"),false);
    else FPlatformProcess::LaunchURL(TEXT("https://www.patreon.com/CockHeroGame"),nullptr,nullptr);
}
void URecoveredSettingsMenu::CloseSettings() {
    OnMainMenuBackgroundRefreshRequested.Broadcast(); StopVoicePreview(); RemoveFromParent();
}

UUMGSequencePlayer* URecoveredMenuWidget::PlayRecoveredAnimation(FName Name,int32 Loops,float Speed) {
    auto* Class=Cast<UWidgetBlueprintGeneratedClass>(GetClass());
    if (!Class) return nullptr;
    const FString RuntimeName=Name.ToString()+TEXT("_INST");
    for (UWidgetAnimation* Animation:Class->Animations) if (Animation && Animation->GetName()==RuntimeName) return PlayAnimation(Animation,0,Loops,EUMGSequencePlayMode::Forward,Speed,false);
    return nullptr;
}

void URecoveredMainMenu::CloseAdultWarning() {
    if (auto* Widget=GetWidgetFromName(TEXT("AdultContentWarningSplashButton"))) { Widget->SetVisibility(ESlateVisibility::Hidden);Widget->RemoveFromParent(); }
    if (GetWorld()) GetWorld()->GetTimerManager().SetTimer(WarningTimer,this,&URecoveredMainMenu::OpenInitialCalibration,.25f,false);
}
void URecoveredMainMenu::CloseTutorialSplash() {
    if (auto* Widget=GetWidgetFromName(TEXT("TutorialSplashButton"))) { Widget->SetVisibility(ESlateVisibility::Hidden);Widget->RemoveFromParent(); }
}
void URecoveredMainMenu::CloseUpdateSplash() {
    if (auto* Widget=GetWidgetFromName(TEXT("NewUpdateSplashButton"))) Widget->RemoveFromParent();
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetBoolSetting(TEXT("HasSeenSplashes?"),true)) Instance->SaveRecoveredState();
}
void URecoveredMainMenu::QuitFromMenu() { if (GetWorld()) { PlayRecoveredAnimation(TEXT("QuitClick"));UKismetSystemLibrary::QuitGame(this,GetOwningPlayer(),EQuitPreference::Quit,false); } }
void URecoveredMainMenu::RefreshBackground() { if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"),Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage")))); }

void URecoveredMainMenu::OpenInitialCalibration() {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());FRecoveredLatencyProfile Profile;
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->GetLatencyProfile(Profile) && !Profile.bIsCalibrated) OpenScreen(TEXT("WBP_CalibrationUI"));
}
