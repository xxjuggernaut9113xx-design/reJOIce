#include "RecoveredMenu.h"
#include "RecoveredRules.h"
#include "RecoveredStatsWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Widget.h"
#include "HAL/PlatformProcess.h"
#include "TimerManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/Texture2D.h"
#include "Engine/Engine.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "Misc/CommandLine.h"
#include "Misc/Parse.h"

namespace {
const TCHAR* const RecoveredPatreonCoverGirlPaths[] = {
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/14.14"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/15.15"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/16.16"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/17.17"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/18.18"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/19.19"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/20.20"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/21.21"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/23.23"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/29.29"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/30.30"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/31.31"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/32.32"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/33.33"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/34.34"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/35.35"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/36.36"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/37.37"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/38.38"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/39.39"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/40.40"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1.Covergirl1"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__10_.Covergirl1__10_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__11_.Covergirl1__11_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__12_.Covergirl1__12_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__13_.Covergirl1__13_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__2_.Covergirl1__2_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__3_.Covergirl1__3_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__4_.Covergirl1__4_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__5_.Covergirl1__5_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__6_.Covergirl1__6_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__7_.Covergirl1__7_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__8_.Covergirl1__8_"),
    TEXT("/Game/Recovery/Resources/CoverGirls/V004/Covergirl1__9_.Covergirl1__9_")
};
}

bool RecoveredMenu::NeedsInitialCalibration(const URecoveredSaveGame* Save) {
    if (!Save) return false;
    FRecoveredLatencyProfile Profile;
    return !Save->GetLatencyProfile(Profile) || !Profile.bIsCalibrated;
}

void URecoveredTooltip::SetTitleAndDescription(const FText& Title,const FText& Description) {
    TooltipTitle=Title;TooltipDescription=Description;
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("Title")))) Label->SetText(Title);
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("Description")))) Label->SetText(Description);
}
void URecoveredTooltip::NativeConstruct() { Super::NativeConstruct(); SetTitleAndDescription(TooltipTitle,TooltipDescription); }
void URecoveredMenuWidget::NativeConstruct() { Super::NativeConstruct(); AttachRecoveredTooltips(); }
void URecoveredMenuWidget::ChangeCheatCodeRedeemVisibility(UWidget* CheatCodeTextRedeemText) {
    if (IsValid(CheatCodeTextRedeemText)) CheatCodeTextRedeemText->SetVisibility(ESlateVisibility::Collapsed);
}
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
    BIND_ROUTE("StartGameButton",OpenModes)
    BIND_ROUTE("StatsButton",OpenChallenges)
    BIND_ROUTE("StatsDebugButton",OpenStatsDebug)
    BIND_ROUTE("Settings",OpenSettings)
    BIND_ROUTE("UnlockStoreButton",OpenUnlockStore)
    BIND_ROUTE("ImportButton",OpenImport)
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
        ApplyPatronLocks();
        RefreshBackground();
    }
}
void URecoveredMainMenu::InitCoverGirl() {
    auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CoverGirlButton")));
    if (!Button) return;
    TArray<UTexture2D*> ResolvedCoverGirls;
    ResolvedCoverGirls.Reserve(UE_ARRAY_COUNT(RecoveredPatreonCoverGirlPaths));
    for (const TCHAR* Path:RecoveredPatreonCoverGirlPaths) if (auto* CoverGirl=LoadObject<UTexture2D>(nullptr,Path)) ResolvedCoverGirls.Add(CoverGirl);
    for (UTexture2D* CoverGirl:PatreonCoverGirlArray) if (IsValid(CoverGirl) && !ResolvedCoverGirls.Contains(CoverGirl)) ResolvedCoverGirls.Add(CoverGirl);
    if (ResolvedCoverGirls.IsEmpty()) {
        if (auto* Fallback=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/CoverGirls/40.40"))) ResolvedCoverGirls.Add(Fallback);
    }
    if (ResolvedCoverGirls.IsEmpty()) return;
    // Values from the original branch-free InitCoverGirl Blueprint bytecode.
    UTexture2D* SelectedCover=nullptr;
#if WITH_DEV_AUTOMATION_TESTS
    FString RequestedCover;
    if (FParse::Value(FCommandLine::Get(),TEXT("RecoveredCoverGirl="),RequestedCover)) {
        for (UTexture2D* CoverGirl:ResolvedCoverGirls) if (CoverGirl && CoverGirl->GetName().Equals(RequestedCover,ESearchCase::IgnoreCase)) { SelectedCover=CoverGirl;break; }
    }
#endif
    if (!SelectedCover) SelectedCover=ResolvedCoverGirls[FMath::RandRange(0,ResolvedCoverGirls.Num()-1)];
    FSlateBrush Brush;
    Brush.SetResourceObject(SelectedCover);
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
void URecoveredMainMenu::ApplyPatronLocks() {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const bool bIsPatron=Instance && Instance->CurrentSave && Instance->CurrentSave->GetBoolSetting(TEXT("IsPatron?"));
    auto* Version=Cast<UTextBlock>(GetWidgetFromName(TEXT("VersionInfoMainMenuText")));
    auto* Support=Cast<UTextBlock>(GetWidgetFromName(TEXT("PatreonSupportText")));
    if (bIsPatron) {
        if (Version) Version->SetText(FText::FromString(TEXT("V0.04 Patreon Build")));
        if (Support) Support->SetText(FText::FromString(TEXT("vote on weekly content packs \r\nvia patreon")));
        return;
    }
    if (auto* Import=Cast<UTextBlock>(GetWidgetFromName(TEXT("ImportText")))) Import->SetOpacity(0.5f);
    if (auto* Lock=GetWidgetFromName(TEXT("PatronLockImportSizebox"))) Lock->SetVisibility(ESlateVisibility::Visible);
    if (Version) Version->SetText(FText::FromString(TEXT("V0.04 Public Build")));
    if (Support) Support->SetText(FText::FromString(TEXT("Join now for complete access and fresh content drops every Friday.")));
}
void URecoveredMainMenu::NativeDestruct() { BindNavigation(false); Super::NativeDestruct(); }
void URecoveredMainMenu::OpenScreen(const TCHAR* ScreenName) {
    LastNavigationError.Reset();
    const FString Path=FString::Printf(TEXT("/Game/Recovery/UI/%s.%s_C"),ScreenName,ScreenName);
    UClass* ScreenClass=LoadClass<UUserWidget>(nullptr,*Path);
    if (!ScreenClass || !GetWorld()) { LastNavigationError=TEXT("Recovered screen or world unavailable: ")+Path; return; }
    UUserWidget* Screen=CreateWidget<UUserWidget>(GetWorld(),ScreenClass);
    if (!Screen) { LastNavigationError=TEXT("Could not create recovered screen: ")+Path; return; }
    if (auto* StatsScreen=Cast<URecoveredStatsScreenWidget>(Screen)) {
        StatsScreen->SetRecoveredStatisticsGameInstance(Cast<URecoveredGameInstance>(GetGameInstance()));
    }
    LastOpenedScreen=Screen;
    if (GEngine && GEngine->GameViewport) Screen->AddToViewport(0);
    // Source handlers keep the main menu behind the new screen.
}
void URecoveredMainMenu::OpenDifficulty() {
    // The original Start handler first casts GetGameMode to BP_GlobalManager.
    if (!Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this))) {
        LastNavigationError=TEXT("Start requires the recovered global game mode"); return;
    }
    PlayRecoveredAnimation(TEXT("StartGameClick"));
    OpenScreen(TEXT("DifficultySelectScreen_Widget"));
}
void URecoveredMainMenu::OpenModes() {
    if (auto* Manager = Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this))) Manager->OpenRecoveredModes();
}
void URecoveredMainMenu::OpenChallenges() {
    PlayRecoveredAnimation(TEXT("StatsClick"));
    OpenScreen(TEXT("ChallengesMenuWidget"));
}
void URecoveredMainMenu::OpenStatsDebug() { OpenScreen(TEXT("StatsScreenWidget")); }
void URecoveredMainMenu::OpenSettings() {
    PlayRecoveredAnimation(TEXT("SettingsClick"));
    OpenScreen(TEXT("SettingsMenuWidget"));
}
void URecoveredMainMenu::OpenUnlockStore() {
    PlayRecoveredAnimation(TEXT("UnlocksClick"));
    OpenScreen(TEXT("UnlockStoreWidget"));
}
void URecoveredMainMenu::OpenImport() {
    PlayRecoveredAnimation(TEXT("ImportClick"));
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->GetBoolSetting(TEXT("IsPatron?"))) {
        OpenScreen(TEXT("ImportMenuWidget"));
        return;
    }
    FPlatformProcess::LaunchURL(TEXT("https://www.patreon.com/CockHeroGame"),nullptr,nullptr);
}

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
    OpenInitialCalibration();
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
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && RecoveredMenu::NeedsInitialCalibration(Instance->CurrentSave)) OpenScreen(TEXT("WBP_CalibrationUI"));
}
