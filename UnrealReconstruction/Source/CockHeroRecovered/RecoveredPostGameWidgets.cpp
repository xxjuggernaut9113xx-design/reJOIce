#include "RecoveredPostGameWidgets.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "MovieScene.h"
#include "RecoveredGameplay.h"
#include "RecoveredRules.h"
#include "Sound/SoundBase.h"
#include "UObject/UnrealType.h"

namespace {
UWidgetAnimation* FindPostGameAnimation(const UUserWidget* Widget, FName Name) {
    if (!Widget) return nullptr;
    if (const FObjectPropertyBase* Property = FindFProperty<FObjectPropertyBase>(Widget->GetClass(), Name)) {
        if (UWidgetAnimation* Animation = Cast<UWidgetAnimation>(Property->GetObjectPropertyValue_InContainer(Widget))) return Animation;
    }
    const UWidgetBlueprintGeneratedClass* Generated = Cast<UWidgetBlueprintGeneratedClass>(Widget->GetClass());
    if (!Generated) return nullptr;
    const FName RuntimeName(*FString::Printf(TEXT("%s_INST"), *Name.ToString()));
    for (UWidgetAnimation* Animation : Generated->Animations) {
        if (!Animation) continue;
        const UMovieScene* Scene = Animation->GetMovieScene();
        if (
            Animation->GetFName() == Name ||
            Animation->GetFName() == RuntimeName ||
            (Scene && (Scene->GetFName() == Name || Scene->GetFName() == RuntimeName))
        ) return Animation;
    }
    return nullptr;
}

UTexture2D* LoadRecoveredPlayerCardTexture(const FString& OriginalPath) {
    if (OriginalPath.IsEmpty()) return nullptr;
    const auto LoadTexture = [](const FString& ObjectPath) -> UTexture2D* {
        int32 Dot = INDEX_NONE;
        if (!ObjectPath.FindLastChar(TEXT('.'), Dot) || Dot < 1 || !FPackageName::DoesPackageExist(ObjectPath.Left(Dot))) return nullptr;
        return LoadObject<UTexture2D>(nullptr, *ObjectPath);
    };
    if (UTexture2D* Texture = LoadTexture(OriginalPath)) return Texture;
    FString AssetName = OriginalPath;
    int32 Dot = INDEX_NONE;
    if (AssetName.FindLastChar(TEXT('.'), Dot)) AssetName = AssetName.Mid(Dot + 1);
    return LoadTexture(FString::Printf(TEXT("/Game/Recovery/Resources/PlayerCards/%s.%s"), *AssetName, *AssetName));
}

USoundBase* LoadRecoveredPostGameSound(const TCHAR* Name) {
    const FString ObjectPath = FString::Printf(TEXT("/Game/Recovery/Resources/PostGameSoundFX/%s.%s"), Name, Name);
    const int32 Dot = ObjectPath.Find(TEXT("."), ESearchCase::CaseSensitive, ESearchDir::FromEnd);
    return Dot > 0 && FPackageName::DoesPackageExist(ObjectPath.Left(Dot)) ? LoadObject<USoundBase>(nullptr, *ObjectPath) : nullptr;
}

void PlayRecoveredPostGameSound(const UObject* WorldContext, const TCHAR* Name, float Volume, float Pitch) {
    if (USoundBase* Sound = LoadRecoveredPostGameSound(Name)) UGameplayStatics::PlaySound2D(WorldContext, Sound, Volume, Pitch, 0.0f, nullptr, nullptr, true);
}

void SetPostGameText(UUserWidget* Widget, FName Name, const FText& Text) {
    if (UTextBlock* TextBlock = Cast<UTextBlock>(Widget ? Widget->GetWidgetFromName(Name) : nullptr)) TextBlock->SetText(Text);
}
}

void URecoveredXPBarWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (!RecoveredGameInstance) RecoveredGameInstance = Cast<URecoveredGameInstance>(GetGameInstance());
}

void URecoveredXPBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);
    AdvanceRecoveredXPAnimation(InDeltaTime);
}

void URecoveredXPBarWidget::SetRecoveredPostGameGameInstance(URecoveredGameInstance* Instance) {
    RecoveredGameInstance = Instance;
}

void URecoveredXPBarWidget::InitializeBar(int32 StartLevel, int32 StartXP, int32 XPToNext) {
    CurrentLevel = StartLevel;
    TargetLevel = URecoveredStateRuleLibrary::AddInt32Wrapping(StartLevel, 1);
    CurrentXP = StartXP;
    MaxXP = XPToNext;
    UpdateDisplay();
}

void URecoveredXPBarWidget::AddXPAnimated(int32 XPAmount, float Duration) {
    AnimationStartXP = CurrentXP;
    AnimationTargetXP = URecoveredStateRuleLibrary::AddInt32Wrapping(CurrentXP, XPAmount);
    AnimationDuration = Duration;
    AnimationElapsed = 0.0f;
    bIsAnimating = true;
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("ReceiveXP"))) {
        const float PlaybackSpeed = 0.25f / FMath::Max(Duration, KINDA_SMALL_NUMBER);
        PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, PlaybackSpeed, false);
    }
    PlayRecoveredPostGameSound(this, TEXT("whoosh-cinematic-161021_sfx"), 0.5f, 10.0f);
    PlayRecoveredPostGameSound(this, TEXT("drop-coin-384921"), 0.9f, 1.0f);
}

void URecoveredXPBarWidget::AdvanceRecoveredXPAnimation(float InDeltaTime) {
    if (!bIsAnimating) return;
    AnimationElapsed += InDeltaTime;
    const double Alpha = AnimationDuration > 0.0f
        ? FMath::Clamp(static_cast<double>(AnimationElapsed) / static_cast<double>(AnimationDuration), 0.0, 1.0)
        : 1.0;
    CurrentXP = FMath::FloorToInt(FMath::Lerp(static_cast<double>(AnimationStartXP), static_cast<double>(AnimationTargetXP), Alpha));
    UpdateDisplay();
    if (CurrentXP >= MaxXP) {
        OverflowXP = URecoveredStateRuleLibrary::AddInt32Wrapping(AnimationTargetXP, -MaxXP);
        CurrentXP = MaxXP;
        bIsAnimating = false;
        UpdateDisplay();
        OnBarFilled.Broadcast();
        return;
    }
    if (Alpha >= 1.0) bIsAnimating = false;
}

void URecoveredXPBarWidget::UpdateDisplay() {
    SetPostGameText(this, TEXT("CurrentLevelText"), FText::AsNumber(CurrentLevel));
    SetPostGameText(this, TEXT("NextLevelNumber"), FText::AsNumber(TargetLevel));
    FFormatNamedArguments Arguments;
    Arguments.Add(TEXT("maxxp"), FText::AsNumber(MaxXP));
    Arguments.Add(TEXT("currentxp"), FText::AsNumber(CurrentXP));
    SetPostGameText(this, TEXT("XPText"), FText::Format(FText::FromString(TEXT("{currentxp}/{maxxp} XP")), Arguments));
    if (UProgressBar* Bar = Cast<UProgressBar>(GetWidgetFromName(TEXT("XPProgressBar")))) {
        Bar->SetPercent(MaxXP != 0 ? static_cast<float>(CurrentXP) / static_cast<float>(MaxXP) : 0.0f);
    }
    URecoveredProgressionManager* Progression = ResolveRecoveredProgressionManager();
    if (UImage* Image = Cast<UImage>(GetWidgetFromName(TEXT("CurrentLevelEmblemIcon")))) Image->SetBrushFromTexture(Progression ? Progression->GetIconForLevel(CurrentLevel) : nullptr, false);
    if (UImage* Image = Cast<UImage>(GetWidgetFromName(TEXT("NextLevelEmblem")))) Image->SetBrushFromTexture(Progression ? Progression->GetIconForLevel(TargetLevel) : nullptr, false);
}

URecoveredProgressionManager* URecoveredXPBarWidget::ResolveRecoveredProgressionManager() const {
    URecoveredGameInstance* Instance = RecoveredGameInstance.Get();
    if (!Instance) Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance && GetWorld()) Instance = Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance());
    return Instance ? Instance->ProgressionManager.Get() : nullptr;
}

UWidgetAnimation* URecoveredXPBarWidget::FindRecoveredAnimation(FName Name) const {
    return FindPostGameAnimation(this, Name);
}

void URecoveredPlayerCardWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (!RecoveredGameInstance) RecoveredGameInstance = Cast<URecoveredGameInstance>(GetGameInstance());
}

void URecoveredPlayerCardWidget::SetRecoveredPostGameGameInstance(URecoveredGameInstance* Instance) {
    RecoveredGameInstance = Instance;
}

void URecoveredPlayerCardWidget::InitializePlayerCard() {
    URecoveredGameInstance* Instance = ResolveRecoveredGameInstance();
    if (!Instance) return;
    if (UImage* Image = Cast<UImage>(GetWidgetFromName(TEXT("SelectedPlayerCard")))) {
        FRecoveredPlayerCardRow Card;
        UTexture2D* Texture = Instance->ProgressionManager && Instance->ProgressionManager->GetPlayerCardData(Instance->ProgressionManager->GetEquippedPlayerCard(), Card)
            ? LoadRecoveredPlayerCardTexture(Card.CardImage)
            : nullptr;
        Image->SetBrushFromTexture(Texture, false);
    }
    if (UTextBlock* Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerNameText")))) {
        Text->SetText(Instance->CurrentSave ? Instance->CurrentSave->GetTextSetting(TEXT("Playercard_Name"), FText::GetEmpty()) : FText::GetEmpty());
    }
}

URecoveredGameInstance* URecoveredPlayerCardWidget::ResolveRecoveredGameInstance() const {
    if (RecoveredGameInstance) return RecoveredGameInstance;
    if (URecoveredGameInstance* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    return GetWorld() ? Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
}

void URecoveredLevelUpScreenWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (!RecoveredGameInstance) RecoveredGameInstance = Cast<URecoveredGameInstance>(GetGameInstance());
}

void URecoveredLevelUpScreenWidget::SetRecoveredPostGameGameInstance(URecoveredGameInstance* Instance) {
    RecoveredGameInstance = Instance;
}

void URecoveredLevelUpScreenWidget::InitializeScreen(const FRecoveredLevelUpEventData& InData) {
    LevelUpData = InData;
    SetPostGameText(this, TEXT("LevelText"), FText::AsNumber(LevelUpData.NewLevel));
    SetPostGameText(this, TEXT("RankTitle"), FText::FromName(LevelUpData.Title));
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("Anim_LevelUp"))) PlayAnimation(Animation);
    if (URecoveredPlayerCardWidget* PlayerCard = Cast<URecoveredPlayerCardWidget>(GetWidgetFromName(TEXT("WBP_PlayerCard")))) {
        PlayerCard->SetRecoveredPostGameGameInstance(ResolveRecoveredGameInstance());
        PlayerCard->InitializePlayerCard();
    }
    if (UImage* RankIcon = Cast<UImage>(GetWidgetFromName(TEXT("RankIcon")))) {
        URecoveredProgressionManager* Progression = ResolveRecoveredProgressionManager();
        RankIcon->SetBrushFromTexture(Progression ? Progression->GetIconForLevel(LevelUpData.NewLevel) : nullptr, false);
    }
}

void URecoveredLevelUpScreenWidget::PlaySoundFX() {
    PlayRecoveredPostGameSound(this, TEXT("Juice_SFX__11_"), 1.0f, 1.1f);
    PlayRecoveredPostGameSound(this, TEXT("Juice_SFX__9_"), 1.0f, 1.1f);
}

void URecoveredLevelUpScreenWidget::SequenceEvent() {
    OnScreenComplete.Broadcast();
}

void URecoveredLevelUpScreenWidget::SequenceEvent__ENTRYPOINTWBP_LevelUpScreen() {
    PlaySoundFX();
}

void URecoveredLevelUpScreenWidget::SequenceEvent__ENTRYPOINTWBP_LevelUpScreen_0() {
    SequenceEvent();
}

float URecoveredLevelUpScreenWidget::GetRecoveredLevelUpAnimationDuration() const {
    if (UWidgetAnimation* Animation = FindRecoveredAnimation(TEXT("Anim_LevelUp"))) return Animation->GetEndTime();
    return 0.0f;
}

URecoveredProgressionManager* URecoveredLevelUpScreenWidget::ResolveRecoveredProgressionManager() const {
    URecoveredGameInstance* Instance = ResolveRecoveredGameInstance();
    return Instance ? Instance->ProgressionManager.Get() : nullptr;
}

URecoveredGameInstance* URecoveredLevelUpScreenWidget::ResolveRecoveredGameInstance() const {
    if (RecoveredGameInstance) return RecoveredGameInstance;
    if (URecoveredGameInstance* Instance = Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    return GetWorld() ? Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
}

UWidgetAnimation* URecoveredLevelUpScreenWidget::FindRecoveredAnimation(FName Name) const {
    return FindPostGameAnimation(this, Name);
}
