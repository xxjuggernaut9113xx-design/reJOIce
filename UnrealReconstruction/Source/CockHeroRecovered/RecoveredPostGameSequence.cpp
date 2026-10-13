#include "RecoveredPostGameSequence.h"

#include "RecoveredPostGameWidgets.h"
#include "RecoveredRules.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"
#include "UObject/UnrealType.h"

namespace {
constexpr float SourceSettleDelay = 0.5f;
constexpr float XPAnimationDuration = 0.65f;
constexpr float UPSettleDelay = 0.35f;
constexpr float ScreenSwitchDelay = 1.0f;

UWidget* FindPostGameSequenceWidget(UUserWidget* Root, FName Name) {
    if (!Root) return nullptr;
    if (UWidget* Direct = Root->GetWidgetFromName(Name)) return Direct;
    if (!Root->WidgetTree) return nullptr;
    TArray<UWidget*> Widgets;
    Root->WidgetTree->GetAllWidgets(Widgets);
    for (UWidget* Widget : Widgets) {
        if (!Widget) continue;
        if (Widget->GetFName() == Name) return Widget;
        if (UUserWidget* Nested = Cast<UUserWidget>(Widget)) {
            if (UWidget* Found = FindPostGameSequenceWidget(Nested, Name)) return Found;
        }
    }
    return nullptr;
}

UUserWidget* FindNestedUserWidget(UUserWidget* Root, FName Name) {
    return Cast<UUserWidget>(FindPostGameSequenceWidget(Root, Name));
}

void BindPostGameWidgetInstance(ARecoveredGlobalManager* Manager, UUserWidget* Root) {
    URecoveredGameInstance* Instance = Manager ? Cast<URecoveredGameInstance>(Manager->GetGameInstance()) : nullptr;
    if (!Instance || !Root) return;
    if (URecoveredXPBarWidget* XPBar = Cast<URecoveredXPBarWidget>(FindNestedUserWidget(Root, TEXT("WBP_XPBar")))) {
        XPBar->SetRecoveredPostGameGameInstance(Instance);
    }
    if (URecoveredPlayerCardWidget* PlayerCard = Cast<URecoveredPlayerCardWidget>(FindNestedUserWidget(Root, TEXT("WBP_PlayerCard")))) {
        PlayerCard->SetRecoveredPostGameGameInstance(Instance);
    }
    if (URecoveredLevelUpScreenWidget* LevelUp = Cast<URecoveredLevelUpScreenWidget>(FindNestedUserWidget(Root, TEXT("WBP_LevelUpScreen")))) {
        LevelUp->SetRecoveredPostGameGameInstance(Instance);
    }
}

void InitializePostGamePlayerCard(ARecoveredGlobalManager* Manager, UUserWidget* Page) {
    if (!Page) return;
    if (URecoveredPlayerCardWidget* PlayerCard = Cast<URecoveredPlayerCardWidget>(FindNestedUserWidget(Page, TEXT("WBP_PlayerCard")))) {
        PlayerCard->SetRecoveredPostGameGameInstance(Manager ? Cast<URecoveredGameInstance>(Manager->GetGameInstance()) : nullptr);
        PlayerCard->InitializePlayerCard();
    }
}

USoundBase* LoadPostGameSequenceSound(const TCHAR* Name) {
    const FString ObjectPaths[] = {
        FString::Printf(TEXT("/Game/Recovery/Resources/PostGameSoundFX/%s.%s"), Name, Name),
        FString::Printf(TEXT("/Game/Recovery/Resources/Audio/%s.%s"), Name, Name),
    };
    for (const FString& ObjectPath : ObjectPaths) {
        const FString PackagePath = FPackageName::ObjectPathToPackageName(ObjectPath);
        if (!FPackageName::DoesPackageExist(PackagePath)) continue;
        if (USoundBase* Sound = LoadObject<USoundBase>(nullptr, *ObjectPath)) return Sound;
    }
    return nullptr;
}

void PlayPostGameSequenceSound(const UObject* WorldContext, const TCHAR* Name, float Volume, float Pitch) {
    if (USoundBase* Sound = LoadPostGameSequenceSound(Name)) UGameplayStatics::PlaySound2D(WorldContext, Sound, Volume, Pitch, 0.0f, nullptr, nullptr, true);
}

void PlayPostGameEngineSound(const UObject* WorldContext, const TCHAR* ObjectPath, float Volume, float Pitch) {
    const FString PackagePath = FPackageName::ObjectPathToPackageName(FString(ObjectPath));
    if (!FPackageName::DoesPackageExist(PackagePath)) return;
    if (USoundBase* Sound = LoadObject<USoundBase>(nullptr, ObjectPath)) UGameplayStatics::PlaySound2D(WorldContext, Sound, Volume, Pitch, 0.0f, nullptr, nullptr, true);
}

void SetPostGameSequenceText(UUserWidget* Root, const TCHAR* Name, const FText& Value) {
    if (UTextBlock* Text = Cast<UTextBlock>(FindPostGameSequenceWidget(Root, FName(Name)))) Text->SetText(Value);
}

void SetPostGameSequenceTextAny(UUserWidget* Root, std::initializer_list<const TCHAR*> Names, const FText& Value) {
    for (const TCHAR* Name : Names) SetPostGameSequenceText(Root, Name, Value);
}

void SetIntProperty(UObject* Object, FName Name, int32 Value) {
    if (!Object) return;
    if (FIntProperty* Property = FindFProperty<FIntProperty>(Object->GetClass(), Name)) Property->SetPropertyValue_InContainer(Object, Value);
}

void SetFloatProperty(UObject* Object, FName Name, float Value) {
    if (!Object) return;
    if (FFloatProperty* Property = FindFProperty<FFloatProperty>(Object->GetClass(), Name)) Property->SetPropertyValue_InContainer(Object, Value);
}

void SetBoolProperty(UObject* Object, FName Name, bool Value) {
    if (!Object) return;
    if (FBoolProperty* Property = FindFProperty<FBoolProperty>(Object->GetClass(), Name)) Property->SetPropertyValue_InContainer(Object, Value);
}

void CallNoArgFunction(UObject* Object, FName Name) {
    if (!Object) return;
    if (UFunction* Function = Object->FindFunction(Name)) Object->ProcessEvent(Function, nullptr);
}

float PlayNamedAnimation(UUserWidget* Widget, FName Name) {
    if (!Widget) return 0.0f;
    FObjectPropertyBase* Property = FindFProperty<FObjectPropertyBase>(Widget->GetClass(), Name);
    if (!Property) return 0.0f;
    UWidgetAnimation* Animation = Cast<UWidgetAnimation>(Property->GetObjectPropertyValue_InContainer(Widget));
    if (!Animation) return 0.0f;
    Widget->PlayAnimation(Animation);
    return Animation->GetEndTime();
}

void UpdateXPBar(UUserWidget* XPPage, int32 Level, int32 CurrentXP, int32 TargetXP, bool bAnimating) {
    UUserWidget* Bar = FindNestedUserWidget(XPPage, TEXT("WBP_XPBar"));
    if (!Bar) return;
    const int32 XPToNext = URecoveredProgressionLibrary::GetXPForNextLevel(Level);
    if (URecoveredXPBarWidget* RecoveredBar = Cast<URecoveredXPBarWidget>(Bar)) {
        RecoveredBar->InitializeBar(Level, CurrentXP, XPToNext);
        if (bAnimating) RecoveredBar->AddXPAnimated(URecoveredStateRuleLibrary::AddInt32Wrapping(TargetXP, -CurrentXP), XPAnimationDuration);
        return;
    }
    SetIntProperty(Bar, TEXT("CurrentLevel"), Level);
    SetIntProperty(Bar, TEXT("TargetLevel"), URecoveredStateRuleLibrary::AddInt32Wrapping(Level, 1));
    SetIntProperty(Bar, TEXT("CurrentXP"), CurrentXP);
    SetIntProperty(Bar, TEXT("MaxXP"), XPToNext);
    SetIntProperty(Bar, TEXT("AnimationStartXP"), CurrentXP);
    SetIntProperty(Bar, TEXT("AnimationTargetXP"), TargetXP);
    SetFloatProperty(Bar, TEXT("AnimationDuration"), XPAnimationDuration);
    SetFloatProperty(Bar, TEXT("AnimationElapsed"), 0.0f);
    SetBoolProperty(Bar, TEXT("bIsAnimating"), bAnimating);
    CallNoArgFunction(Bar, TEXT("UpdateDisplay"));
}

void UpdateUPTotal(UUserWidget* UPPage, int32 DisplayedUP) {
    if (!UPPage) return;
    SetIntProperty(UPPage, TEXT("DisplayedUP"), DisplayedUP);
    SetPostGameSequenceText(UPPage, TEXT("UPTotalText"), FText::AsNumber(DisplayedUP));
}
}

void URecoveredPostGameSequence::Begin(ARecoveredGlobalManager* InManager, UUserWidget* InRoot, const FRecoveredSessionRewardData& InRewardData) {
    Stop();
    Manager = InManager;
    Root = InRoot;
    RewardData = InRewardData;
    if (!Manager || !Root) return;
    BindPostGameWidgetInstance(Manager, Root);

    CurrentXPSourceIndex = 0;
    CurrentUPSourceIndex = 0;
    CurrentLevelEventIndex = 0;
    PendingXPAmount = 0;
    PendingOverflowXP = 0;
    DisplayedXP = RewardData.StartingXP;
    DisplayedLevel = RewardData.StartingLevel;
    DisplayedUP = RewardData.StartingUP;
    Stage = ERecoveredPostGameStage::XP;
    SetPage(0);
    if (UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"))) {
        SetBoolProperty(XPPage, TEXT("bWaitingForLevelUp"), false);
        SetBoolProperty(XPPage, TEXT("DidPlayerWin?"), RewardData.bWon);
        SetIntProperty(XPPage, TEXT("CurrentSourceIndex"), 0);
        SetIntProperty(XPPage, TEXT("CurrentLevelUpIndex"), 0);
        UpdateXPBar(XPPage, DisplayedLevel, DisplayedXP, DisplayedXP, false);
        InitializePostGamePlayerCard(Manager, XPPage);
        if (URecoveredXPScreenWidget* RecoveredXPPage = Cast<URecoveredXPScreenWidget>(XPPage)) {
            RecoveredXPPage->InitializeRecoveredScreen(RewardData.bWon);
        } else {
            PlayNamedAnimation(XPPage, TEXT("FadeIn"));
            PlayPostGameSequenceSound(XPPage, TEXT("Juice_SFX__12_"), 1.0f, 1.0f);
            if (!RewardData.bWon) PlayNamedAnimation(XPPage, TEXT("Play50PercentPenalty"));
        }
    }
    ShowNextXPSource();
}

void URecoveredPostGameSequence::Stop() {
    if (Manager) {
        if (UWorld* World = Manager->GetWorld()) World->GetTimerManager().ClearTimer(AdvanceTimer);
    }
    PendingAdvance = ERecoveredPostGameAdvance::None;
    Stage = ERecoveredPostGameStage::Idle;
}

void URecoveredPostGameSequence::AdvanceForTesting() {
    if (Manager) {
        if (UWorld* World = Manager->GetWorld()) World->GetTimerManager().ClearTimer(AdvanceTimer);
    }
    Advance();
}

void URecoveredPostGameSequence::ScheduleAdvance(float Delay, ERecoveredPostGameAdvance NextAdvance) {
    PendingAdvance = NextAdvance;
    if (!Manager) return;
    UWorld* World = Manager->GetWorld();
    if (!World) return;
    World->GetTimerManager().ClearTimer(AdvanceTimer);
    World->GetTimerManager().SetTimer(AdvanceTimer, this, &URecoveredPostGameSequence::Advance, FMath::Max(Delay, KINDA_SMALL_NUMBER), false);
}

void URecoveredPostGameSequence::Advance() {
    const ERecoveredPostGameAdvance CurrentAdvance = PendingAdvance;
    PendingAdvance = ERecoveredPostGameAdvance::None;
    switch (CurrentAdvance) {
        case ERecoveredPostGameAdvance::XPSourceAnimation:
            StartXPBarAnimation();
            break;
        case ERecoveredPostGameAdvance::XPBarAnimation:
            CompleteXPSource();
            break;
        case ERecoveredPostGameAdvance::XPInterSourceDelay:
            ShowNextXPSource();
            break;
        case ERecoveredPostGameAdvance::LevelUpAnimation:
            CompleteLevelUp();
            break;
        case ERecoveredPostGameAdvance::XPOverflowAnimation:
            ScheduleNextXPSource();
            break;
        case ERecoveredPostGameAdvance::UnlockPointSourceAnimation:
            CompleteUPSource();
            break;
        case ERecoveredPostGameAdvance::UnlockPointInterSourceDelay:
            ShowNextUPSource();
            break;
        case ERecoveredPostGameAdvance::BeginUnlockPoints:
            BeginUnlockPointStage();
            break;
        case ERecoveredPostGameAdvance::ShowSummary:
            ShowSummary();
            break;
        default:
            break;
    }
}

void URecoveredPostGameSequence::ShowNextXPSource() {
    if (CurrentXPSourceIndex >= RewardData.XPSources.Num()) {
        PendingXPAmount = 0;
        ScheduleAdvance(ScreenSwitchDelay, ERecoveredPostGameAdvance::BeginUnlockPoints);
        return;
    }

    const FRecoveredXPSourceData& Source = RewardData.XPSources[CurrentXPSourceIndex++];
    PendingXPAmount = Source.XPAmount;
    UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"));
    UUserWidget* SourceWidget = FindNestedUserWidget(XPPage, TEXT("XBP_XPSourceText"));
    SetIntProperty(XPPage, TEXT("CurrentSourceIndex"), CurrentXPSourceIndex - 1);
    if (SourceWidget) SourceWidget->SetVisibility(ESlateVisibility::Visible);
    const float SourceDuration = [&]() {
        if (URecoveredXPSourceTextWidget* RecoveredSource = Cast<URecoveredXPSourceTextWidget>(SourceWidget)) {
            RecoveredSource->InitializeSource(Source);
            return RecoveredSource->GetRecoveredSourceAnimationDuration();
        }
        SetPostGameSequenceTextAny(SourceWidget, { TEXT("XPAmountText") }, FText::FromString(FString::Printf(TEXT("+%d XP"), Source.XPAmount)));
        SetPostGameSequenceTextAny(SourceWidget, { TEXT("XPDetailText") }, FText::FromString(FString::Printf(TEXT("(%s)"), *Source.DetailText.ToString())));
        return PlayNamedAnimation(SourceWidget, TEXT("SpawnAndSlam"));
    }();
    ScheduleAdvance(FMath::Max(SourceDuration, KINDA_SMALL_NUMBER), ERecoveredPostGameAdvance::XPSourceAnimation);
}

void URecoveredPostGameSequence::StartXPBarAnimation() {
    UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"));
    const int32 Threshold = GetCurrentXPThreshold();
    const int32 TargetXP = Threshold > 0 ? FMath::Min(DisplayedXP + PendingXPAmount, Threshold) : DisplayedXP + PendingXPAmount;
    UUserWidget* Bar = FindNestedUserWidget(XPPage, TEXT("WBP_XPBar"));
    UpdateXPBar(XPPage, DisplayedLevel, DisplayedXP, TargetXP, true);
    if (!Cast<URecoveredXPBarWidget>(Bar)) PlayNamedAnimation(Bar, TEXT("ReceiveXP"));
    ScheduleAdvance(XPAnimationDuration, ERecoveredPostGameAdvance::XPBarAnimation);
}

void URecoveredPostGameSequence::CompleteXPSource() {
    const int32 Amount = PendingXPAmount;
    PendingXPAmount = 0;
    ApplyXPAmount(Amount);
}

void URecoveredPostGameSequence::ApplyXPAmount(int32 Amount) {
    const int32 Threshold = GetCurrentXPThreshold();
    if (Threshold > 0 && RewardData.LevelUpEvents.IsValidIndex(CurrentLevelEventIndex)) {
        const int32 ToThreshold = FMath::Max(0, Threshold - DisplayedXP);
        if (Amount >= ToThreshold) {
            DisplayedXP = Threshold;
            PendingOverflowXP = Amount - ToThreshold;
            if (UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"))) {
                UpdateXPBar(XPPage, DisplayedLevel, DisplayedXP, DisplayedXP, false);
                if (UWidget* SourceWidget = FindPostGameSequenceWidget(XPPage, TEXT("XBP_XPSourceText"))) SourceWidget->SetVisibility(ESlateVisibility::Hidden);
            }
            PresentLevelUp();
            return;
        }
    }

    DisplayedXP += Amount;
    if (UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"))) UpdateXPBar(XPPage, DisplayedLevel, DisplayedXP, DisplayedXP, false);
    ScheduleNextXPSource();
}

void URecoveredPostGameSequence::PresentLevelUp() {
    if (!RewardData.LevelUpEvents.IsValidIndex(CurrentLevelEventIndex)) {
        ScheduleNextXPSource();
        return;
    }
    Stage = ERecoveredPostGameStage::LevelUp;
    SetPage(1);
    const FRecoveredLevelUpEventData& Event = RewardData.LevelUpEvents[CurrentLevelEventIndex];
    UUserWidget* LevelPage = FindNestedUserWidget(Root, TEXT("WBP_LevelUpScreen"));
    if (UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"))) {
        SetBoolProperty(XPPage, TEXT("bWaitingForLevelUp"), true);
        SetIntProperty(XPPage, TEXT("CurrentLevelUpIndex"), CurrentLevelEventIndex + 1);
    }
    const float Duration = [&]() {
        if (URecoveredLevelUpScreenWidget* RecoveredLevelUp = Cast<URecoveredLevelUpScreenWidget>(LevelPage)) {
            RecoveredLevelUp->InitializeScreen(Event);
            return RecoveredLevelUp->GetRecoveredLevelUpAnimationDuration();
        }
        SetPostGameSequenceText(LevelPage, TEXT("LevelText"), FText::AsNumber(Event.NewLevel));
        SetPostGameSequenceText(LevelPage, TEXT("RankTitle"), FText::FromName(Event.Title));
        return PlayNamedAnimation(LevelPage, TEXT("Anim_LevelUp"));
    }();
    ScheduleAdvance(FMath::Max(Duration, KINDA_SMALL_NUMBER), ERecoveredPostGameAdvance::LevelUpAnimation);
}

void URecoveredPostGameSequence::CompleteLevelUp() {
    if (!RewardData.LevelUpEvents.IsValidIndex(CurrentLevelEventIndex)) {
        Stage = ERecoveredPostGameStage::XP;
        SetPage(0);
        ShowNextXPSource();
        return;
    }
    const FRecoveredLevelUpEventData& Event = RewardData.LevelUpEvents[CurrentLevelEventIndex++];
    DisplayedLevel = Event.NewLevel;
    DisplayedXP = 0;
    Stage = ERecoveredPostGameStage::XP;
    SetPage(0);
    if (UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"))) {
        SetBoolProperty(XPPage, TEXT("bWaitingForLevelUp"), false);
        UpdateXPBar(XPPage, DisplayedLevel, 0, 0, false);
    }
    if (PendingOverflowXP > 0) ShowXPOverflow();
    else ShowNextXPSource();
}

void URecoveredPostGameSequence::ShowXPOverflow() {
    PendingXPAmount = PendingOverflowXP;
    PendingOverflowXP = 0;
    UUserWidget* XPPage = FindNestedUserWidget(Root, TEXT("WBP_XPScreen"));
    const int32 Threshold = GetCurrentXPThreshold();
    const int32 TargetXP = Threshold > 0 ? FMath::Min(DisplayedXP + PendingXPAmount, Threshold) : DisplayedXP + PendingXPAmount;
    UUserWidget* Bar = FindNestedUserWidget(XPPage, TEXT("WBP_XPBar"));
    UpdateXPBar(XPPage, DisplayedLevel, DisplayedXP, TargetXP, true);
    if (!Cast<URecoveredXPBarWidget>(Bar)) PlayNamedAnimation(Bar, TEXT("ReceiveXP"));
    ScheduleAdvance(XPAnimationDuration, ERecoveredPostGameAdvance::XPOverflowAnimation);
}

void URecoveredPostGameSequence::ScheduleNextXPSource() {
    ScheduleAdvance(SourceSettleDelay, ERecoveredPostGameAdvance::XPInterSourceDelay);
}

void URecoveredPostGameSequence::BeginUnlockPointStage() {
    Stage = ERecoveredPostGameStage::UnlockPoints;
    SetPage(2);
    UUserWidget* UPPage = FindNestedUserWidget(Root, TEXT("WBP_UPRewardScreen"));
    SetIntProperty(UPPage, TEXT("CurrentSourceIndex"), 0);
    UpdateUPTotal(UPPage, DisplayedUP);
    InitializePostGamePlayerCard(Manager, UPPage);
    if (URecoveredUPRewardScreenWidget* RecoveredUPPage = Cast<URecoveredUPRewardScreenWidget>(UPPage)) {
        RecoveredUPPage->InitializeRecoveredScreen(RewardData.bWon);
    } else {
        SetBoolProperty(UPPage, TEXT("Did Player Win?"), RewardData.bWon);
        if (UWidget* Penalty = FindPostGameSequenceWidget(UPPage, TEXT("50PercentPenaltyText"))) {
            Penalty->SetVisibility(RewardData.bWon ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
        }
        PlayNamedAnimation(UPPage, TEXT("FadeIn"));
    }
    ShowNextUPSource();
}

void URecoveredPostGameSequence::ShowNextUPSource() {
    if (CurrentUPSourceIndex >= RewardData.UPSources.Num()) {
        ScheduleAdvance(ScreenSwitchDelay, ERecoveredPostGameAdvance::ShowSummary);
        return;
    }

    const FRecoveredUPSourceData& Source = RewardData.UPSources[CurrentUPSourceIndex];
    UUserWidget* UPPage = FindNestedUserWidget(Root, TEXT("WBP_UPRewardScreen"));
    UUserWidget* SourceWidget = FindNestedUserWidget(UPPage, TEXT("WBP_UPSourceText"));
    SetIntProperty(UPPage, TEXT("CurrentSourceIndex"), CurrentUPSourceIndex);
    if (SourceWidget) SourceWidget->SetVisibility(ESlateVisibility::Visible);
    const float SourceDuration = [&]() {
        if (URecoveredUPSourceTextWidget* RecoveredSource = Cast<URecoveredUPSourceTextWidget>(SourceWidget)) {
            RecoveredSource->InitializeSource(Source);
            return RecoveredSource->GetRecoveredSourceAnimationDuration();
        }
        SetPostGameSequenceText(SourceWidget, TEXT("UPAmountText"), FText::FromString(FString::Printf(TEXT("+%d UP"), Source.UPAmount)));
        SetPostGameSequenceText(SourceWidget, TEXT("DetailText"), FText::FromString(FString::Printf(TEXT("(%s)"), *Source.DetailText.ToString())));
        return PlayNamedAnimation(SourceWidget, TEXT("AnimSlam"));
    }();
    ScheduleAdvance(FMath::Max(SourceDuration, KINDA_SMALL_NUMBER), ERecoveredPostGameAdvance::UnlockPointSourceAnimation);
}

void URecoveredPostGameSequence::CompleteUPSource() {
    if (!RewardData.UPSources.IsValidIndex(CurrentUPSourceIndex)) {
        ShowSummary();
        return;
    }
    const FRecoveredUPSourceData& Source = RewardData.UPSources[CurrentUPSourceIndex++];
    if (Manager) Manager->ApplyRecoveredPostGameStorePoints(Source.UPAmount);
    DisplayedUP += Source.UPAmount;
    UUserWidget* UPPage = FindNestedUserWidget(Root, TEXT("WBP_UPRewardScreen"));
    UpdateUPTotal(UPPage, DisplayedUP);
    if (UWidget* SourceWidget = FindPostGameSequenceWidget(UPPage, TEXT("WBP_UPSourceText"))) SourceWidget->SetVisibility(ESlateVisibility::Collapsed);
    PlayNamedAnimation(UPPage, TEXT("ReceiveUP"));
    PlayPostGameEngineSound(UPPage, TEXT("/Engine/VREditor/Sounds/VR_teleport.VR_teleport"), 0.8f, 1.0f);
    PlayPostGameSequenceSound(UPPage, TEXT("Juice_SFX__16_"), 1.0f, 1.5f);
    ScheduleAdvance(UPSettleDelay, ERecoveredPostGameAdvance::UnlockPointInterSourceDelay);
}

void URecoveredPostGameSequence::ShowSummary() {
    Stage = ERecoveredPostGameStage::Summary;
    SetPage(3);
}

void URecoveredPostGameSequence::SetPage(int32 Index) const {
    if (UWidgetSwitcher* Switcher = Cast<UWidgetSwitcher>(FindPostGameSequenceWidget(Root, TEXT("WidgetSwitcher")))) Switcher->SetActiveWidgetIndex(Index);
}

int32 URecoveredPostGameSequence::GetCurrentXPThreshold() const {
    if (!RewardData.LevelUpEvents.IsValidIndex(CurrentLevelEventIndex)) return 0;
    const FRecoveredLevelUpEventData& Event = RewardData.LevelUpEvents[CurrentLevelEventIndex];
    if (Event.NewLevel != DisplayedLevel + 1) return 0;
    return Event.XPThresholdCrossed > 0 ? Event.XPThresholdCrossed : URecoveredProgressionLibrary::GetXPForNextLevel(DisplayedLevel);
}
