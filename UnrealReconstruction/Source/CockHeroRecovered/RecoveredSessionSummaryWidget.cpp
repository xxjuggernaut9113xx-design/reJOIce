#include "RecoveredSessionSummaryWidget.h"

#include "RecoveredRules.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundBase.h"
#include "UObject/UnrealType.h"

namespace {
constexpr FLinearColor RecoveredVictoryColor(0.0f, 0.5209959745407104f, 0.12477199733257294f, 1.0f);
constexpr FLinearColor RecoveredDefeatColor(0.838798999786377f, 0.0f, 0.0006070000235922635f, 1.0f);

void SetRecoveredSummaryText(UUserWidget* Widget, FName Name, const FText& Text) {
    if (UTextBlock* Block = Cast<UTextBlock>(Widget ? Widget->GetWidgetFromName(Name) : nullptr)) Block->SetText(Text);
}

void CallRecoveredNoArg(UUserWidget* Widget, FName FunctionName) {
    if (!Widget) return;
    if (UFunction* Function = Widget->FindFunction(FunctionName)) Widget->ProcessEvent(Function, nullptr);
}

void SetRecoveredIntProperty(UObject* Object, FName PropertyName, int32 Value) {
    if (!Object) return;
    if (FIntProperty* Property = FindFProperty<FIntProperty>(Object->GetClass(), PropertyName)) Property->SetPropertyValue_InContainer(Object, Value);
}
}

void URecoveredSessionSummaryWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    BindRecoveredControls(true);
}

void URecoveredSessionSummaryWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindRecoveredControls(true);
    InitializeRecoveredNestedWidgets();
    if (bRecoveredSummaryInitialized) ApplyRecoveredPresentation();
    StartRecoveredBeginDisplayAnimation();
}

void URecoveredSessionSummaryWidget::NativeDestruct() {
    BindRecoveredControls(false);
    Super::NativeDestruct();
}

void URecoveredSessionSummaryWidget::InitializeRecoveredSummary(const FRecoveredSessionRewardData& RewardData, bool bDidPlayerWin) {
    BindRecoveredControls(true);
    RecoveredRewardData = RewardData;
    bRecoveredDidPlayerWin = bDidPlayerWin;
    bRecoveredSummaryInitialized = true;
    ApplyRecoveredPresentation();
}

void URecoveredSessionSummaryWidget::ApplyRecoveredPresentation() {
    const FRecoveredSessionStats& Stats = RecoveredRewardData.SessionStats;
    SetRecoveredSummaryText(this, TEXT("DetailedStatsString"), URecoveredProgressionLibrary::GetDetailedStatsText(Stats));
    SetRecoveredSummaryText(this, TEXT("RewardsString"), URecoveredProgressionLibrary::GetRewardsText(RecoveredRewardData));
    SetRecoveredSummaryText(this, TEXT("DurationText"), URecoveredProgressionLibrary::GetDurationText(Stats));
    SetRecoveredSummaryText(this, TEXT("EdgeAmountText"), URecoveredProgressionLibrary::GetEdgesText(Stats));
    SetRecoveredSummaryText(this, TEXT("HighestComboText"), URecoveredProgressionLibrary::GetComboText(Stats));
    SetRecoveredSummaryText(this, TEXT("TotalStrokesText"), URecoveredProgressionLibrary::GetStrokesText(Stats));
    if (UTextBlock* Result = Cast<UTextBlock>(GetWidgetFromName(TEXT("VictoryText")))) {
        Result->SetColorAndOpacity(FSlateColor(bRecoveredDidPlayerWin ? RecoveredVictoryColor : RecoveredDefeatColor));
        Result->SetText(FText::FromString(bRecoveredDidPlayerWin ? TEXT("Victory") : TEXT("Defeat (-50% Rewards)")));
    }
    InitializeRecoveredXPBar(RecoveredRewardData.EndingLevel, RecoveredRewardData.EndingXP,
        URecoveredProgressionLibrary::GetXPForNextLevel(RecoveredRewardData.EndingLevel));
}

void URecoveredSessionSummaryWidget::InitializeRecoveredNestedWidgets() {
    CallRecoveredNoArg(Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_PlayerCard"))), TEXT("InitializePlayerCard"));
    if (!bRecoveredSummaryInitialized) {
        if (ARecoveredGlobalManager* Manager = ResolveRecoveredGlobalManager()) {
            const int32 Level = RecoveredRewardData.EndingLevel > 0 ? RecoveredRewardData.EndingLevel : 1;
            InitializeRecoveredXPBar(Level, RecoveredRewardData.EndingXP, URecoveredProgressionLibrary::GetXPForNextLevel(Level));
            if (Manager->SessionStats.bWon) bRecoveredDidPlayerWin = true;
        }
    }
}

void URecoveredSessionSummaryWidget::InitializeRecoveredXPBar(int32 Level, int32 XP, int32 XPToNextLevel) const {
    UUserWidget* XPBar = Cast<UUserWidget>(GetWidgetFromName(TEXT("WBP_XPBar")));
    if (!XPBar) return;
    SetRecoveredIntProperty(XPBar, TEXT("CurrentLevel"), Level);
    SetRecoveredIntProperty(XPBar, TEXT("CurrentXP"), XP);
    SetRecoveredIntProperty(XPBar, TEXT("AnimationStartXP"), XP);
    SetRecoveredIntProperty(XPBar, TEXT("AnimationTargetXP"), XP);
    if (UFunction* Function = XPBar->FindFunction(TEXT("InitializeBar"))) {
        TArray<uint8> Parameters;
        Parameters.SetNumZeroed(Function->ParmsSize);
        const int32 Values[] = {Level, XP, XPToNextLevel};
        int32 ValueIndex = 0;
        for (TFieldIterator<FProperty> It(Function); It; ++It) {
            FProperty* Property = *It;
            if (!Property->HasAnyPropertyFlags(CPF_Parm) || Property->HasAnyPropertyFlags(CPF_ReturnParm | CPF_OutParm)) continue;
            if (FNumericProperty* Numeric = CastField<FNumericProperty>(Property)) {
                void* Address = Property->ContainerPtrToValuePtr<void>(Parameters.GetData());
                const int32 Value = Values[FMath::Min<int32>(ValueIndex++, static_cast<int32>(UE_ARRAY_COUNT(Values) - 1))];
                if (Numeric->IsInteger()) Numeric->SetIntPropertyValue(Address, static_cast<int64>(Value));
                else Numeric->SetFloatingPointPropertyValue(Address, Value);
            }
        }
        XPBar->ProcessEvent(Function, Parameters.GetData());
    }
    CallRecoveredNoArg(XPBar, TEXT("UpdateDisplay"));
}

void URecoveredSessionSummaryWidget::BindRecoveredControls(bool bBind) {
#define BIND_RECOVERED_SUMMARY_BUTTON(WidgetName, Clicked, Hovered, Unhovered) \
    if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT(WidgetName)))) { \
        if (bBind) { \
            Button->OnClicked.AddUniqueDynamic(this, &URecoveredSessionSummaryWidget::Clicked); \
            Button->OnHovered.AddUniqueDynamic(this, &URecoveredSessionSummaryWidget::Hovered); \
            Button->OnUnhovered.AddUniqueDynamic(this, &URecoveredSessionSummaryWidget::Unhovered); \
        } else { \
            Button->OnClicked.RemoveDynamic(this, &URecoveredSessionSummaryWidget::Clicked); \
            Button->OnHovered.RemoveDynamic(this, &URecoveredSessionSummaryWidget::Hovered); \
            Button->OnUnhovered.RemoveDynamic(this, &URecoveredSessionSummaryWidget::Unhovered); \
        } \
    }
    if (UButton* Button = Cast<UButton>(GetWidgetFromName(TEXT("ReturnToMenu")))) {
        if (bBind) Button->OnClicked.AddUniqueDynamic(this, &URecoveredSessionSummaryWidget::HandleRecoveredReturnToMenu);
        else Button->OnClicked.RemoveDynamic(this, &URecoveredSessionSummaryWidget::HandleRecoveredReturnToMenu);
    }
    BIND_RECOVERED_SUMMARY_BUTTON("PatreonButton", HandleRecoveredPatreonClicked, HandleRecoveredPatreonHovered, HandleRecoveredPatreonUnhovered)
    BIND_RECOVERED_SUMMARY_BUTTON("DiscordInvButton", HandleRecoveredDiscordClicked, HandleRecoveredDiscordHovered, HandleRecoveredDiscordUnhovered)
    BIND_RECOVERED_SUMMARY_BUTTON("TwitterButton", HandleRecoveredTwitterClicked, HandleRecoveredTwitterHovered, HandleRecoveredTwitterUnhovered)
#undef BIND_RECOVERED_SUMMARY_BUTTON
}

ARecoveredGlobalManager* URecoveredSessionSummaryWidget::ResolveRecoveredGlobalManager() const {
    return GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
}

UWidgetAnimation* URecoveredSessionSummaryWidget::FindRecoveredAnimation(FName Name) const {
    const UWidgetBlueprintGeneratedClass* GeneratedClass = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
    if (!GeneratedClass) return nullptr;
    const FName InstanceName(*FString::Printf(TEXT("%s_INST"), *Name.ToString()));
    for (UWidgetAnimation* Animation : GeneratedClass->Animations) {
        if (Animation && (Animation->GetFName() == Name || Animation->GetFName() == InstanceName)) return Animation;
    }
    return nullptr;
}

void URecoveredSessionSummaryWidget::StartRecoveredBeginDisplayAnimation() {
    UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("BeginDisplay"));
    if (Animation && !IsAnimationPlaying(Animation)) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

bool URecoveredSessionSummaryWidget::IsRecoveredAnimationPlaying(FName AnimationName) const {
    const UWidgetAnimation* Animation = FindRecoveredAnimation(AnimationName);
    return Animation && IsAnimationPlaying(Animation);
}

FString URecoveredSessionSummaryWidget::GetRecoveredSummarySocialURL(FName Destination) {
    if (Destination == TEXT("Patreon")) return TEXT("https://www.patreon.com/CockHeroGame");
    if (Destination == TEXT("Discord")) return TEXT("https://discord.gg/dQXRpF6Uhf");
    if (Destination == TEXT("Twitter")) return TEXT("https://x.com/CockHeroGame");
    return FString();
}

USoundBase* URecoveredSessionSummaryWidget::SelectRecoveredVoiceLine(FName PropertyName) const {
    FArrayProperty* Property = FindFProperty<FArrayProperty>(GetClass(), PropertyName);
    if (!Property) return nullptr;
    FObjectPropertyBase* Inner = CastField<FObjectPropertyBase>(Property->Inner);
    if (!Inner) return nullptr;
    FScriptArrayHelper Lines(Property, Property->ContainerPtrToValuePtr<void>(this));
    TArray<USoundBase*> ValidLines;
    for (int32 Index = 0; Index < Lines.Num(); ++Index) {
        if (USoundBase* Line = Cast<USoundBase>(Inner->GetObjectPropertyValue(Lines.GetRawPtr(Index)))) ValidLines.Add(Line);
    }
    return ValidLines.IsEmpty() ? nullptr : ValidLines[FMath::RandHelper(ValidLines.Num())];
}

USoundBase* URecoveredSessionSummaryWidget::SelectRecoveredPostGameVoiceline() const {
    const ARecoveredGlobalManager* Manager = ResolveRecoveredGlobalManager();
    const bool bWon = Manager ? Manager->PlayerVariables.bIsAllowedToCum : bRecoveredDidPlayerWin;
    return SelectRecoveredPostGameVoicelineFor(Manager ? Manager->GetVoicePack() : FName(TEXT("Default")), bWon);
}

USoundBase* URecoveredSessionSummaryWidget::SelectRecoveredPostGameVoicelineFor(FName VoicePackID, bool bWon) const {
    FString Pack = VoicePackID.ToString();
    Pack.ReplaceInline(TEXT(" "), TEXT(""));
    Pack.ReplaceInline(TEXT("_"), TEXT(""));
    Pack.ReplaceInline(TEXT("-"), TEXT(""));
    FString Prefix = TEXT("Villainess");
    if (Pack.Contains(TEXT("Brat"), ESearchCase::IgnoreCase)) Prefix = TEXT("Brat");
    else if (Pack.Contains(TEXT("Dommy"), ESearchCase::IgnoreCase)) Prefix = TEXT("DommyMommy");
    else if (Pack.Contains(TEXT("Sweetheart"), ESearchCase::IgnoreCase)) Prefix = TEXT("Sweetheart");
    FString Result = Prefix + (bWon ? TEXT(" Post Game Victory Lines") : TEXT(" Post Game Defeat Lines"));
    if (USoundBase* Line = SelectRecoveredVoiceLine(FName(*Result))) return Line;
    Result.ReplaceInline(TEXT(" "), TEXT(""));
    return SelectRecoveredVoiceLine(FName(*Result));
}

void URecoveredSessionSummaryWidget::PlayPostGameVoicelines() {
    if (USoundBase* Line = SelectRecoveredPostGameVoiceline()) {
        UGameplayStatics::PlaySound2D(this, Line, 1.0f, 1.0f, 0.0f, nullptr, nullptr, true);
    }
}

void URecoveredSessionSummaryWidget::HandleRecoveredReturnToMenu() {
    if (ARecoveredGlobalManager* Manager = ResolveRecoveredGlobalManager()) Manager->ReturnToMainMenu();
}

void URecoveredSessionSummaryWidget::HandleRecoveredPatreonClicked() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("PatreonClick"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
    UKismetSystemLibrary::LaunchURL(GetRecoveredSummarySocialURL(TEXT("Patreon")));
}

void URecoveredSessionSummaryWidget::HandleRecoveredPatreonHovered() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("PatreonHover"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void URecoveredSessionSummaryWidget::HandleRecoveredPatreonUnhovered() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("PatreonUnhover"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void URecoveredSessionSummaryWidget::HandleRecoveredDiscordClicked() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("DiscordClick"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
    UKismetSystemLibrary::LaunchURL(GetRecoveredSummarySocialURL(TEXT("Discord")));
}

void URecoveredSessionSummaryWidget::HandleRecoveredDiscordHovered() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("DiscordHover"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void URecoveredSessionSummaryWidget::HandleRecoveredDiscordUnhovered() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("DiscordUnhover"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void URecoveredSessionSummaryWidget::HandleRecoveredTwitterClicked() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("TwitterClick"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
    UKismetSystemLibrary::LaunchURL(GetRecoveredSummarySocialURL(TEXT("Twitter")));
}

void URecoveredSessionSummaryWidget::HandleRecoveredTwitterHovered() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("TwitterHover"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}

void URecoveredSessionSummaryWidget::HandleRecoveredTwitterUnhovered() {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("TwitterUnhover"))) PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
}
