#include "RecoveredChallengeWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "MovieScene.h"
#include "RecoveredChallengeEntryWidget.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "Sound/SoundBase.h"

namespace {

const FLinearColor CompletedColor(0.0f,0.5209959745407104f,0.12477199733257294f,1.0f);
const FLinearColor IncompleteColor(1.0f,0.015208999626338482f,0.01298299990594387f,1.0f);
constexpr TCHAR ChallengeClaimSoundPath[]=TEXT("/Game/Recovery/Resources/Audio/Juice_SFX__16_.Juice_SFX__16_");
constexpr TCHAR CameraShutterSoundPath[]=TEXT("/Engine/VREditor/Sounds/UI/Camera_Shutter.Camera_Shutter");
constexpr TCHAR XPRewardIconPath[]=TEXT("/Game/Recovery/Resources/UI/Rewards/XPRewardIcon.XPRewardIcon");
constexpr TCHAR UnlockPointsRewardIconPath[]=TEXT("/Game/Recovery/Resources/UI/Rewards/UnlockPointsRewardIcon.UnlockPointsRewardIcon");
constexpr TCHAR PackRewardFallbackIconPath[]=TEXT("/Game/Recovery/Resources/UI/OverlayAssets/PackUnlockBackground.PackUnlockBackground");

struct FRecoveredPackPreview {
    const TCHAR* ID;
    const TCHAR* AssetName;
    const TCHAR* DisplayName;
};

const FRecoveredPackPreview* FindRecoveredPackPreview(const FString& PackID) {
    static const FRecoveredPackPreview Previews[]={
        {TEXT("anal_vol._1"),TEXT("anal_vol"),TEXT("Anal Vol. 1")},
        {TEXT("cum_covered_succubi_vol._1"),TEXT("cum_covered_succubi_vol"),TEXT("Cum Covered Succubi Vol. 1")},
        {TEXT("elves_vol._1"),TEXT("elves_vol"),TEXT("Elves Vol. 1")},
        {TEXT("footjobs_vol._1"),TEXT("footjobs_vol"),TEXT("Footjobs Vol. 1")},
        {TEXT("leggings_remake"),TEXT("leggings_remake"),TEXT("Leggings Remake")},
        {TEXT("shopkeeper_vol._1"),TEXT("shopkeeper_vol"),TEXT("Shopkeeper Vol. 1")},
        {TEXT("upskirts_remake"),TEXT("upskirts_remake"),TEXT("Upskirts Remake")},
        {TEXT("vera_vol._2"),TEXT("vera_vol"),TEXT("Vera Vol. 2")},
        {TEXT("winter_wonderland_vol._1"),TEXT("winter_wonderland_vol"),TEXT("Winter Wonderland Vol. 1")},
    };
    for (const FRecoveredPackPreview& Preview:Previews) if (PackID.Equals(Preview.ID,ESearchCase::IgnoreCase)) return &Preview;
    return nullptr;
}

URecoveredGameInstance* GetRecoveredChallengeInstance(const UUserWidget* Widget) {
    if (!Widget) return nullptr;
    if (const auto* Tab=Cast<URecoveredChallengeWidget>(Widget)) return Tab->GetRecoveredChallengeGameInstance();
    if (auto* Instance=Cast<URecoveredGameInstance>(Widget->GetGameInstance())) return Instance;
    return Widget->GetWorld() ? Cast<URecoveredGameInstance>(Widget->GetWorld()->GetGameInstance()) : nullptr;
}

URecoveredChallengeTracker* GetChallengeTracker(const UUserWidget* Widget) {
    if (auto* Instance=GetRecoveredChallengeInstance(Widget)) return Instance->ChallengeTracker.Get();
    return nullptr;
}

URecoveredProgressionManager* GetProgressionManager(const UUserWidget* Widget) {
    if (auto* Instance=GetRecoveredChallengeInstance(Widget)) return Instance->ProgressionManager.Get();
    return nullptr;
}

const FRecoveredChallengeProgress* FindProgress(const URecoveredChallengeTracker* Tracker,FName ChallengeID) {
    if (!Tracker) return nullptr;
    if (const auto* Progress=Tracker->SessionProgress.Find(ChallengeID)) return Progress;
    return Tracker->LifetimeProgress.Find(ChallengeID);
}

const FRecoveredChallengeRow* FindDefinition(const URecoveredChallengeTracker* Tracker,FName ChallengeID) {
    if (!Tracker || !Tracker->ChallengeTable || Tracker->ChallengeTable->GetRowStruct()!=FRecoveredChallengeRow::StaticStruct()) return nullptr;
    if (const auto* ByRowName=Tracker->ChallengeTable->FindRow<FRecoveredChallengeRow>(ChallengeID,TEXT("Recovered challenge UI"))) return ByRowName;
    for (const auto& Pair:Tracker->ChallengeTable->GetRowMap()) {
        const auto* Candidate=reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (Candidate && Candidate->ChallengeID==ChallengeID.ToString()) return Candidate;
    }
    return nullptr;
}

const TArray<FName>& SourceChallengeOrder() {
    static const TArray<FName> Order={
        FName(TEXT("rookie_edger")),FName(TEXT("intermediate_edger")),FName(TEXT("master_edger")),FName(TEXT("quickshot")),FName(TEXT("master_of_control")),
        FName(TEXT("succubus_lunch")),FName(TEXT("oops")),FName(TEXT("the_cockfather")),FName(TEXT("like_a_rabbit")),FName(TEXT("demon_proof")),
        FName(TEXT("succubus_initiative")),FName(TEXT("goonlight_sonata")),FName(TEXT("goon_ronin")),FName(TEXT("carpet_burn")),FName(TEXT("clit_eastwood")),
        FName(TEXT("customer_loyalty")),FName(TEXT("crankin_my_hog")),FName(TEXT("chicken_dinner")),FName(TEXT("the_names_danger")),FName(TEXT("trash_talker")),
        FName(TEXT("skill_issue")),FName(TEXT("edgewalker")),FName(TEXT("my_arm_hurts")),FName(TEXT("meter_maid")),FName(TEXT("its_called_motion")),
        FName(TEXT("good_boy")),FName(TEXT("succubus_buffet")),FName(TEXT("bricked_up")),FName(TEXT("goon_gambit")),FName(TEXT("the_price_of_hubris")),
        FName(TEXT("provoker")),FName(TEXT("nice")),FName(TEXT("i_see_god")),FName(TEXT("obedient")),FName(TEXT("easily_tempted")),
        FName(TEXT("master_of_restraint")),FName(TEXT("built_different")),FName(TEXT("strokeaholic")),FName(TEXT("bag_of_tricks")),FName(TEXT("monk_of_lust")),
        FName(TEXT("speed_freak")),FName(TEXT("tony_stank")),FName(TEXT("swarm_protocol")),FName(TEXT("overclocked")),FName(TEXT("gambler")),
        FName(TEXT("the_lamb")),FName(TEXT("feeding_hour")),FName(TEXT("masochist")),FName(TEXT("devils_toll")),FName(TEXT("cock_hero")),
        FName(TEXT("death_spiral")),FName(TEXT("reach_level_5")),FName(TEXT("reach_level_10")),FName(TEXT("reach_level_15")),FName(TEXT("reach_level_20"))
    };
    return Order;
}

TArray<FName> OrderedChallengeIDs(const URecoveredChallengeTracker* Tracker) {
    TSet<FName> Available;
    if (Tracker) {
        for (const auto& Pair:Tracker->SessionProgress) Available.Add(Pair.Key);
        for (const auto& Pair:Tracker->LifetimeProgress) Available.Add(Pair.Key);
    }
    TArray<FName> Ordered;
    for (const FName ID:SourceChallengeOrder()) if (Available.Remove(ID)>0) Ordered.Add(ID);
    TArray<FName> Remaining=Available.Array();
    Remaining.Sort([](const FName& A,const FName& B) { return A.LexicalLess(B); });
    Ordered.Append(Remaining);
    return Ordered;
}

UTexture2D* LoadExistingTexture(const FString& ObjectPath) {
    int32 DotIndex=INDEX_NONE;
    if (ObjectPath.IsEmpty() || !ObjectPath.FindLastChar(TEXT('.'),DotIndex) || DotIndex<1) return nullptr;
    return FPackageName::DoesPackageExist(ObjectPath.Left(DotIndex)) ? LoadObject<UTexture2D>(nullptr,*ObjectPath) : nullptr;
}

UTexture2D* LoadRecoveredChallengeIcon(const FString& SourcePath) {
    static const FString Prefix(TEXT("/Game/ChallengeIcons/"));
    if (!SourcePath.StartsWith(Prefix)) return LoadExistingTexture(SourcePath);
    int32 DotIndex=INDEX_NONE;
    if (!SourcePath.FindLastChar(TEXT('.'),DotIndex) || DotIndex==SourcePath.Len()-1) return nullptr;
    const FString AssetName=SourcePath.Mid(DotIndex+1);
    return LoadExistingTexture(FString::Printf(TEXT("/Game/Recovery/Resources/ChallengeIcons/%s.%s"),*AssetName,*AssetName));
}

UTexture2D* LoadRecoveredPlayerCardTexture(const FString& SourcePath) {
    if (UTexture2D* Texture=LoadExistingTexture(SourcePath)) return Texture;
    FString AssetName=SourcePath;
    int32 DotIndex=INDEX_NONE;
    if (AssetName.FindLastChar(TEXT('.'),DotIndex)) AssetName=AssetName.Mid(DotIndex+1);
    return LoadExistingTexture(FString::Printf(TEXT("/Game/Recovery/Resources/PlayerCards/%s.%s"),*AssetName,*AssetName));
}

UTexture2D* LoadRecoveredPackTexture(const FString& PackID) {
    if (const FRecoveredPackPreview* Preview=FindRecoveredPackPreview(PackID)) {
        if (UTexture2D* Texture=LoadExistingTexture(FString::Printf(TEXT("/Game/Recovery/Resources/Packs/%s.%s"),Preview->AssetName,Preview->AssetName))) return Texture;
    }
    const FString AssetName=PackID.Contains(TEXT(".")) ? PackID.Left(PackID.Find(TEXT("."))) : PackID;
    for (const TCHAR* Folder:{TEXT("Packs"),TEXT("PackPreviews"),TEXT("UI/Packs")}) {
        if (UTexture2D* Texture=LoadExistingTexture(FString::Printf(TEXT("/Game/Recovery/Resources/%s/%s.%s"),Folder,*AssetName,*AssetName))) return Texture;
    }
    return LoadObject<UTexture2D>(nullptr,PackRewardFallbackIconPath);
}

FText GetRecoveredPackDisplayName(const FString& PackID) {
    if (const FRecoveredPackPreview* Preview=FindRecoveredPackPreview(PackID)) return FText::FromString(Preview->DisplayName);
    return FText::FromString(PackID.Replace(TEXT("_"),TEXT(" ")));
}

FString RewardKind(const FRecoveredReward& Reward) {
    FString Kind=Reward.RewardType;
    Kind.RemoveFromStart(TEXT("ECHRewardType::"));
    return Kind;
}

bool ContainsRewardKind(const TArray<FRecoveredReward>& Rewards,const TCHAR* Kind) {
    return Rewards.ContainsByPredicate([Kind](const FRecoveredReward& Reward) { return RewardKind(Reward)==Kind; });
}

FText GetRewardPlayerCardName(const URecoveredProgressionManager* Progression,const FString& CardID) {
    FRecoveredPlayerCardRow Card;
    if (Progression && Progression->GetPlayerCardData(FName(*CardID),Card)) return Card.CardName;
    return FText::FromString(CardID);
}

FText GetRewardModifierName(const URecoveredProgressionManager* Progression,const FString& ModifierID) {
    FRecoveredModifierRow Modifier;
    if (Progression && Progression->GetModifierData(FName(*ModifierID),Modifier)) return Modifier.ModifierTitle;
    return FText::FromString(ModifierID);
}

UTexture2D* GetRewardModifierIcon(const URecoveredProgressionManager* Progression,const FString& ModifierID) {
    FRecoveredModifierRow Modifier;
    return Progression && Progression->GetModifierData(FName(*ModifierID),Modifier) ? Modifier.ModifierIcon.Get() : nullptr;
}

FString DescribeReward(const FRecoveredReward& Reward,const URecoveredProgressionManager* Progression) {
    const FString Kind=RewardKind(Reward);
    if (Kind==TEXT("XP")) return FString::Printf(TEXT("+ %d XP\r\n"),Reward.Value);
    if (Kind==TEXT("UnlockPoints")) return FString::Printf(TEXT("+ %d UP\r\n"),Reward.Value);
    if (Kind==TEXT("UnlockPack")) return FString::Printf(TEXT("+ %s pack\r\n"),*Reward.ItemIdentifier.Replace(TEXT("_"),TEXT(" ")));
    if (Kind==TEXT("PlayerCard")) return FString::Printf(TEXT("+ %s player card\r\n"),*GetRewardPlayerCardName(Progression,Reward.ItemIdentifier).ToString());
    if (Kind==TEXT("UnlockModifier")) return FString::Printf(TEXT("+ %s Modifier\r\n"),*Reward.ItemIdentifier);
    return FString();
}

FString DescribeRewards(const FRecoveredChallengeRow* Definition,const URecoveredProgressionManager* Progression) {
    if (!Definition) return FString();
    FString Result;
    for (const FRecoveredReward& Reward:Definition->Rewards) Result+=DescribeReward(Reward,Progression);
    if (Definition->Rewards.IsEmpty()) {
        if (Definition->XPReward>0) {
            FRecoveredReward Reward;
            Reward.RewardType=TEXT("XP");
            Reward.Value=Definition->XPReward;
            Result+=DescribeReward(Reward,Progression);
        }
        if (Definition->UnlockPointsReward>0) {
            FRecoveredReward Reward;
            Reward.RewardType=TEXT("UnlockPoints");
            Reward.Value=Definition->UnlockPointsReward;
            Result+=DescribeReward(Reward,Progression);
        }
    }
    return Result;
}

bool HasClaimableRewards(const FRecoveredChallengeRow* Definition) {
    return Definition && (!Definition->Rewards.IsEmpty() || Definition->XPReward>0 || Definition->UnlockPointsReward>0);
}

FString FormatSourceSeconds(int32 Seconds) {
    const int32 SafeSeconds=FMath::Max(0,Seconds);
    const int32 Hours=SafeSeconds/3600;
    const int32 Minutes=(SafeSeconds%3600)/60;
    const int32 Remaining=SafeSeconds%60;
    if (Hours>0) return FString::Printf(TEXT("%02d:%02d:%02d"),Hours,Minutes,Remaining);
    return FString::Printf(TEXT("%02d:%02d"),Minutes,Remaining);
}

FString DescribeMetricProgress(const FString& Metric,int32 CurrentValue,int32 TargetValue) {
    if (Metric==TEXT("Strokes")) return FString::Printf(TEXT("%d/%d strokes"),CurrentValue,TargetValue);
    if (Metric==TEXT("Edges")) return FString::Printf(TEXT("%d/%d edges"),CurrentValue,TargetValue);
    if (Metric==TEXT("SuccubiDefeated")) return FString::Printf(TEXT("%d/%d succubi"),CurrentValue,TargetValue);
    if (Metric==TEXT("EnemiesDefeated")) return FString::Printf(TEXT("%d/%d enemies"),CurrentValue,TargetValue);
    if (Metric==TEXT("MaxCombo")) return FString::Printf(TEXT("%d/%d combo"),CurrentValue,TargetValue);
    if (Metric==TEXT("StrokeCombo")) return FString::Printf(TEXT("%d/%d stroke combo"),CurrentValue,TargetValue);
    if (Metric==TEXT("MissedCumWindows")) return FString::Printf(TEXT("%d/%d missed cum windows"),CurrentValue,TargetValue);
    if (Metric==TEXT("TimesTaunted")) return FString::Printf(TEXT("%d/%d taunts"),CurrentValue,TargetValue);
    if (Metric==TEXT("ItemsUsed")) return FString::Printf(TEXT("%d/%d items used"),CurrentValue,TargetValue);
    if (Metric==TEXT("AvgStrokesPerEdge")) return FString::Printf(TEXT("%d/%d avg strokes/edge"),CurrentValue,TargetValue);
    if (Metric==TEXT("DrawsAtMaxHeat")) return FString::Printf(TEXT("%d/%d max heat draws"),CurrentValue,TargetValue);
    if (Metric==TEXT("EarlyClimax")) return FString::Printf(TEXT("%d/%d early climax"),CurrentValue,TargetValue);
    if (Metric==TEXT("SessionDuration")) return FString::Printf(TEXT("%s/%s duration"),*FormatSourceSeconds(CurrentValue),*FormatSourceSeconds(TargetValue));
    if (Metric==TEXT("SessionsCompleted")) return FString::Printf(TEXT("%d/%d sessions"),CurrentValue,TargetValue);
    if (Metric==TEXT("SessionsWon")) return FString::Printf(TEXT("%d/%d wins"),CurrentValue,TargetValue);
    if (Metric==TEXT("TotalXPEarned")) return FString::Printf(TEXT("%d/%d XP earned"),CurrentValue,TargetValue);
    if (Metric==TEXT("MoneySpent")) return FString::Printf(TEXT("%d/%d money spent"),CurrentValue,TargetValue);
    if (Metric==TEXT("EdgeStreak")) return FString::Printf(TEXT("%d/%d edge streak"),CurrentValue,TargetValue);
    if (Metric==TEXT("ConsecutiveSuccubiSurvived")) return FString::Printf(TEXT("%d/%d succubi in a row"),CurrentValue,TargetValue);
    if (Metric==TEXT("CumWindowsHit")) return FString::Printf(TEXT("%d/%d cum windows hit"),CurrentValue,TargetValue);
    if (Metric==TEXT("PerfectRounds")) return FString::Printf(TEXT("%d/%d perfect rounds"),CurrentValue,TargetValue);
    if (Metric==TEXT("TimesLost")) return FString::Printf(TEXT("%d/%d losses"),CurrentValue,TargetValue);
    if (Metric==TEXT("LostToSuccubus")) return FString::Printf(TEXT("%d/%d lost to succubus"),CurrentValue,TargetValue);
    if (Metric==TEXT("TimeAtHighHeat")) return FString::Printf(TEXT("%s/%s high heat"),*FormatSourceSeconds(CurrentValue),*FormatSourceSeconds(TargetValue));
    if (Metric==TEXT("PercentAtHighHeat")) return FString::Printf(TEXT("%d/%d%% at high heat"),CurrentValue,TargetValue);
    if (Metric==TEXT("GamesWithSexToy")) return FString::Printf(TEXT("%d/%d games with toy"),CurrentValue,TargetValue);
    if (Metric==TEXT("PerfectEdges")) return FString::Printf(TEXT("%d/%d perfect edges"),CurrentValue,TargetValue);
    if (Metric==TEXT("BonerPillsUsed")) return FString::Printf(TEXT("%d/%d boner pills"),CurrentValue,TargetValue);
    if (Metric==TEXT("AcceptedTemptation")) return FString::Printf(TEXT("%d/%d temptations"),CurrentValue,TargetValue);
    if (Metric==TEXT("CameDuringTaunt")) return FString::Printf(TEXT("%d/%d came during taunt"),CurrentValue,TargetValue);
    return TEXT("INCOMPLETE");
}

FString DescribeChallengeProgress(const FRecoveredChallengeProgress& Progress) {
    if (Progress.Requirements.IsEmpty()) return TEXT("INCOMPLETE");
    if (Progress.bCompleted) return Progress.bRewardsClaimed ? TEXT("COMPLETED") : TEXT("CLAIM REWARDS");
    const FRecoveredRequirement& Requirement=Progress.Requirements[0];
    int32 CurrentValue=Requirement.CurrentValue;
    if (Progress.BestValues.IsValidIndex(0)) CurrentValue=FMath::Max(CurrentValue,Progress.BestValues[0]);
    FString Metric=Requirement.MetricType;
    Metric.RemoveFromStart(TEXT("EMetricType::"));
    Metric.RemoveFromStart(TEXT("ERecoveredMetric::"));
    return DescribeMetricProgress(Metric,CurrentValue,Requirement.TargetValue);
}

UWidgetAnimation* FindSourceAnimation(const UUserWidget* Widget,FName AnimationName) {
    const auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Widget ? Widget->GetClass() : nullptr);
    if (!Generated) return nullptr;
    const FName RuntimeName(*FString::Printf(TEXT("%s_INST"),*AnimationName.ToString()));
    for (UWidgetAnimation* Animation:Generated->Animations) {
        if (!Animation) continue;
        const UMovieScene* Scene=Animation->GetMovieScene();
        if (Animation->GetFName()==AnimationName || Animation->GetFName()==RuntimeName || (Scene && (Scene->GetFName()==AnimationName || Scene->GetFName()==RuntimeName))) return Animation;
    }
    return nullptr;
}

void PlaySourceAnimation(UUserWidget* Widget,FName AnimationName) {
    if (Widget) if (UWidgetAnimation* Animation=FindSourceAnimation(Widget,AnimationName)) Widget->PlayAnimation(Animation,0.0f,1,EUMGSequencePlayMode::Forward,1.0f,false);
}

void PlaySourceSound(const UObject* WorldContext,const TCHAR* AssetPath,float Volume,float Pitch) {
    if (!WorldContext || !WorldContext->GetWorld()) return;
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,AssetPath)) UGameplayStatics::PlaySound2D(WorldContext,Sound,Volume,Pitch,0.0f,nullptr,nullptr,true);
}

void SetNamedText(UUserWidget* Widget,const TCHAR* Name,const FText& Value) {
    if (auto* Text=Widget ? Cast<UTextBlock>(Widget->GetWidgetFromName(Name)) : nullptr) Text->SetText(Value);
}

void SetNamedColor(UUserWidget* Widget,const TCHAR* Name,const FLinearColor& Color) {
    if (auto* Text=Widget ? Cast<UTextBlock>(Widget->GetWidgetFromName(Name)) : nullptr) Text->SetColorAndOpacity(FSlateColor(Color));
}

void PopulateRewardBox(UUserWidget* RewardBox,const FRecoveredReward& Reward,const URecoveredProgressionManager* Progression) {
    if (!RewardBox) return;
    const FString Kind=RewardKind(Reward);
    UTexture2D* Icon=nullptr;
    FText Label;
    FVector2D ImageSize=FVector2D::ZeroVector;
    if (Kind==TEXT("XP")) {
        Icon=LoadObject<UTexture2D>(nullptr,XPRewardIconPath);
        Label=FText::FromString(FString::Printf(TEXT("+ %d \r\nLevel XP"),Reward.Value));
    } else if (Kind==TEXT("UnlockPoints")) {
        Icon=LoadObject<UTexture2D>(nullptr,UnlockPointsRewardIconPath);
        Label=FText::FromString(FString::Printf(TEXT("+ %d\r\nUnlock Points"),Reward.Value));
    } else if (Kind==TEXT("UnlockPack")) {
        Icon=LoadRecoveredPackTexture(Reward.ItemIdentifier);
        Label=FText::FromString(FString::Printf(TEXT("%s Pack"),*GetRecoveredPackDisplayName(Reward.ItemIdentifier).ToString()));
    } else if (Kind==TEXT("UnlockModifier")) {
        Icon=GetRewardModifierIcon(Progression,Reward.ItemIdentifier);
        Label=FText::FromString(FString::Printf(TEXT("%s\r\nModifier"),*GetRewardModifierName(Progression,Reward.ItemIdentifier).ToString()));
        ImageSize=FVector2D(256.0f,256.0f);
    } else if (Kind==TEXT("PlayerCard")) {
        FRecoveredPlayerCardRow Card;
        if (Progression) Progression->GetPlayerCardData(FName(*Reward.ItemIdentifier),Card);
        Icon=LoadRecoveredPlayerCardTexture(Card.CardImage);
        Label=FText::FromString(FString::Printf(TEXT("%s \r\nPlayer Card"),*GetRewardPlayerCardName(Progression,Reward.ItemIdentifier).ToString()));
        ImageSize=FVector2D(420.0f,93.3f);
    }
    if (auto* Image=Cast<UImage>(RewardBox->GetWidgetFromName(TEXT("RewardImage")))) {
        Image->SetBrushFromTexture(Icon,false);
        if (!ImageSize.IsNearlyZero()) Image->SetDesiredSizeOverride(ImageSize);
    }
    if (auto* ImageSizeBox=Cast<USizeBox>(RewardBox->GetWidgetFromName(TEXT("ImageSizeBox")))) {
        if (!ImageSize.IsNearlyZero()) {
            ImageSizeBox->SetWidthOverride(ImageSize.X);
            ImageSizeBox->SetHeightOverride(ImageSize.Y);
        }
    }
    SetNamedText(RewardBox,TEXT("RewardTitle"),Label);
}

}

void URecoveredChallengeWidget::NativeOnInitialized() {
    Super::NativeOnInitialized();
    if (URecoveredChallengeTracker* Tracker=GetChallengeTracker(this)) Tracker->OnChallengeProgress.AddUniqueDynamic(this,&URecoveredChallengeWidget::OnChallengeProgressNotification);
    RefreshChallengeList();
}

void URecoveredChallengeWidget::NativeConstruct() {
    Super::NativeConstruct();
    if (URecoveredChallengeTracker* Tracker=GetChallengeTracker(this)) Tracker->OnChallengeProgress.AddUniqueDynamic(this,&URecoveredChallengeWidget::OnChallengeProgressNotification);
    RefreshChallengeList();
}

void URecoveredChallengeWidget::NativeDestruct() {
    if (URecoveredChallengeTracker* Tracker=GetChallengeTracker(this)) Tracker->OnChallengeProgress.RemoveDynamic(this,&URecoveredChallengeWidget::OnChallengeProgressNotification);
    HandleRewardOverlayClose();
    Super::NativeDestruct();
}

void URecoveredChallengeWidget::SetRecoveredChallengeGameInstance(URecoveredGameInstance* Instance) {
    RecoveredInstanceOverride=Instance;
}

URecoveredGameInstance* URecoveredChallengeWidget::GetRecoveredChallengeGameInstance() const {
    if (RecoveredInstanceOverride) return RecoveredInstanceOverride;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    return GetWorld() ? Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
}

void URecoveredChallengeWidget::RefreshChallengeList() {
    auto* Container=Cast<UVerticalBox>(GetWidgetFromName(TEXT("ChallengesVerticalBox")));
    if (!Container) return;
    Container->ClearChildren();
    RecoveredChallengeEntries.Reset();

    URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    if (!Tracker) return;
    const TArray<FName> ChallengeIDs=OrderedChallengeIDs(Tracker);
    SelectedChallengeID=ChallengeIDs.IsEmpty() ? NAME_None : ChallengeIDs[0];

    UClass* EntryClass=LoadClass<URecoveredChallengeEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/ChallengeEntryWidget.ChallengeEntryWidget_C"));
    if (!EntryClass) return;
    const int32 TrackedLength=Tracker->TrackedChallenges.Num();
    for (const FName ChallengeID:ChallengeIDs) {
        const FRecoveredChallengeProgress* Progress=FindProgress(Tracker,ChallengeID);
        const FRecoveredChallengeRow* Definition=FindDefinition(Tracker,ChallengeID);
        if (!Progress || !Definition) continue;
        URecoveredChallengeEntryWidget* Entry=CreateWidget<URecoveredChallengeEntryWidget>(this,EntryClass);
        if (!Entry) continue;
        Entry->PopulateChallengeEntry(
            ChallengeID,
            Definition->DisplayName,
            LoadRecoveredChallengeIcon(Definition->Icon),
            Progress->bCompleted,
            Definition->Rewards,
            IsChallengeTracked(ChallengeID),
            TrackedLength,
            Progress->bRewardsClaimed);
        Entry->OnChallengeClicked.AddUniqueDynamic(this,&URecoveredChallengeWidget::HandleChallengeEntrySelected);
        Entry->OnTrackButtonClicked.AddUniqueDynamic(this,&URecoveredChallengeWidget::HandleChallengeEntryTrackAction);
        Container->AddChildToVerticalBox(Entry);
        RecoveredChallengeEntries.Add(Entry);
    }
    RefreshDetailsPanel();
}

void URecoveredChallengeWidget::SetChallengeTracked(FName ChallengeID,bool bTracked) {
    URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    const FRecoveredChallengeProgress* Progress=FindProgress(Tracker,ChallengeID);
    if (!Tracker || !Progress || Progress->bCompleted) return;
    if (bTracked) {
        if (!Tracker->TrackedChallenges.Contains(ChallengeID)) {
            if (Tracker->TrackedChallenges.Num()>=2) Tracker->TrackedChallenges.RemoveAt(0);
            Tracker->TrackedChallenges.Add(ChallengeID);
        }
    } else {
        Tracker->TrackedChallenges.Remove(ChallengeID);
    }
    if (auto* Instance=GetRecoveredChallengeInstance(this)) Instance->PersistRecoveredProgression();
    RefreshChallengeList();
}

bool URecoveredChallengeWidget::IsChallengeTracked(FName ChallengeID) const {
    const URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    return Tracker && Tracker->TrackedChallenges.Contains(ChallengeID);
}

TArray<FName> URecoveredChallengeWidget::GetTrackedChallenges() const {
    const URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    return Tracker ? Tracker->TrackedChallenges : TArray<FName>();
}

TArray<FRecoveredReward> URecoveredChallengeWidget::ClaimChallengeRewardsInternal(FName ChallengeID) {
    URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    if (!Tracker) return {};
    TArray<FRecoveredReward> Rewards=Tracker->ClaimChallengeRewards(ChallengeID);
    if (!Rewards.IsEmpty()) if (auto* Instance=GetRecoveredChallengeInstance(this)) Instance->PersistRecoveredProgression();
    return Rewards;
}

bool URecoveredChallengeWidget::ClaimChallengeRewards(FName ChallengeID) {
    const TArray<FRecoveredReward> Rewards=ClaimChallengeRewardsInternal(ChallengeID);
    if (Rewards.IsEmpty()) return false;
    RefreshChallengeList();
    return true;
}

void URecoveredChallengeWidget::SelectChallenge(FName ChallengeID) {
    if (!FindProgress(GetChallengeTracker(this),ChallengeID)) return;
    SelectedChallengeID=ChallengeID;
    RefreshDetailsPanel();
}

void URecoveredChallengeWidget::RunChallengeAction(FName ChallengeID) {
    URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    const FRecoveredChallengeProgress* Progress=FindProgress(Tracker,ChallengeID);
    if (!Tracker || !Progress || Progress->bCompleted) return;
    SetChallengeTracked(ChallengeID,!Tracker->TrackedChallenges.Contains(ChallengeID));
}

int32 URecoveredChallengeWidget::GetChallengeEntryCount() const {
    return RecoveredChallengeEntries.Num();
}

UUserWidget* URecoveredChallengeWidget::GetActiveRewardOverlay() const {
    return ActiveRewardOverlay.Get();
}

void URecoveredChallengeWidget::RefreshDetailsPanel() {
    URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    const FRecoveredChallengeProgress* Progress=FindProgress(Tracker,SelectedChallengeID);
    const FRecoveredChallengeRow* Definition=FindDefinition(Tracker,SelectedChallengeID);
    if (!Progress || !Definition) return;

    SetNamedText(this,TEXT("ChallengeTitle"),Definition->DisplayName);
    SetNamedText(this,TEXT("RequirementDescription"),Definition->Description);
    SetNamedText(this,TEXT("RewardsBody"),FText::FromString(DescribeRewards(Definition,GetProgressionManager(this))));
    SetNamedText(this,TEXT("CompletionStatusText"),FText::FromString(Progress->bCompleted ? TEXT("Completed") : TEXT("Incomplete")));
    SetNamedColor(this,TEXT("CompletionStatusText"),Progress->bCompleted ? CompletedColor : IncompleteColor);
    if (auto* Icon=Cast<UImage>(GetWidgetFromName(TEXT("ChallengeIcon")))) Icon->SetBrushFromTexture(LoadRecoveredChallengeIcon(Definition->Icon),false);
    if (auto* Interaction=Cast<UButton>(GetWidgetFromName(TEXT("InteractionButton")))) {
        Interaction->SetIsEnabled(true);
        Interaction->OnClicked.RemoveAll(this);
        Interaction->OnClicked.AddUniqueDynamic(this,&URecoveredChallengeWidget::HandleInteractionClicked);
    }
    SetNamedText(this,TEXT("InteractionButtonText"),FText::FromString(DescribeChallengeProgress(*Progress)));
    PlayRecoveredAnimation(TEXT("UpdateDetailsPanelBounce"));
}

void URecoveredChallengeWidget::HandleChallengeEntrySelected(FName ChallengeID) {
    SelectChallenge(ChallengeID);
}

void URecoveredChallengeWidget::HandleChallengeEntryTrackAction(FName ChallengeID,URecoveredChallengeEntryWidget* Entry) {
    const FRecoveredChallengeProgress* Progress=FindProgress(GetChallengeTracker(this),ChallengeID);
    if (!Progress) return;
    if (Progress->bCompleted) {
        if (Entry) Entry->SetTrackButtonText(FText::FromString(TEXT("Done")));
        return;
    }
    RunChallengeAction(ChallengeID);
}

void URecoveredChallengeWidget::ShowClaimRewardOverlay(const TArray<FRecoveredReward>& Rewards) {
    HandleRewardOverlayClose();
    UClass* OverlayClass=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/ChallengeRewardOverlayWidget.ChallengeRewardOverlayWidget_C"));
    UClass* RewardBoxClass=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/GeneralRewardBox.GeneralRewardBox_C"));
    if (!OverlayClass || !RewardBoxClass) return;
    UUserWidget* Overlay=CreateWidget<UUserWidget>(this,OverlayClass);
    if (!Overlay) return;
    ActiveRewardOverlay=Overlay;
    if (Overlay->GetWorld()) Overlay->AddToViewport(0);
    auto* RewardsBox=Cast<UHorizontalBox>(Overlay->GetWidgetFromName(TEXT("RewardsHorBox")));
    if (!RewardsBox) return;
    RewardsBox->ClearChildren();
    URecoveredProgressionManager* Progression=GetProgressionManager(this);
    for (const FRecoveredReward& Reward:Rewards) {
        UUserWidget* RewardBox=CreateWidget<UUserWidget>(Overlay,RewardBoxClass);
        if (!RewardBox) continue;
        RewardBox->TakeWidget();
        PopulateRewardBox(RewardBox,Reward,Progression);
        if (UHorizontalBoxSlot* RewardSlot=RewardsBox->AddChildToHorizontalBox(RewardBox)) RewardSlot->SetPadding(FMargin(8.0f,0.0f,8.0f,0.0f));
    }
    if (auto* CloseContainer=Cast<USizeBox>(Overlay->GetWidgetFromName(TEXT("SizeBox_1")))) CloseContainer->SetVisibility(ESlateVisibility::Visible);
    if (auto* CloseButton=Cast<UButton>(Overlay->GetWidgetFromName(TEXT("InteractionButton")))) CloseButton->OnClicked.AddUniqueDynamic(this,&URecoveredChallengeWidget::HandleRewardOverlayClose);
    PlaySourceAnimation(Overlay,TEXT("RevealCloseButton"));
}

void URecoveredChallengeWidget::HandleRewardOverlayClose() {
    UUserWidget* Overlay=ActiveRewardOverlay.Get();
    if (!Overlay) return;
    if (auto* CloseButton=Cast<UButton>(Overlay->GetWidgetFromName(TEXT("InteractionButton")))) CloseButton->OnClicked.RemoveDynamic(this,&URecoveredChallengeWidget::HandleRewardOverlayClose);
    Overlay->RemoveFromParent();
    ActiveRewardOverlay=nullptr;
}

void URecoveredChallengeWidget::HandleInteractionClicked() {
    URecoveredChallengeTracker* Tracker=GetChallengeTracker(this);
    const FRecoveredChallengeProgress* Progress=FindProgress(Tracker,SelectedChallengeID);
    const FRecoveredChallengeRow* Definition=FindDefinition(Tracker,SelectedChallengeID);
    if (!Progress || !Definition) return;
    if (!Progress->bCompleted) {
        PlayRecoveredAnimation(TEXT("CompletedClick"));
        return;
    }
    if (Progress->bRewardsClaimed || !HasClaimableRewards(Definition)) {
        PlayRecoveredAnimation(TEXT("UnsuccessfulClickNotCompleted"));
        PlaySourceSound(this,CameraShutterSoundPath,1.0f,1.0f);
        return;
    }
    PlayRecoveredAnimation(TEXT("ButtonClick"));
    PlaySourceSound(this,ChallengeClaimSoundPath,1.0f,1.5f);
    const TArray<FRecoveredReward> Rewards=ClaimChallengeRewardsInternal(SelectedChallengeID);
    if (Rewards.IsEmpty()) {
        PlayRecoveredAnimation(TEXT("UnsuccessfulClickNotCompleted"));
        PlaySourceSound(this,CameraShutterSoundPath,1.0f,1.0f);
        return;
    }
    PlaySourceSound(this,CameraShutterSoundPath,1.0f,1.0f);
    ShowClaimRewardOverlay(Rewards);
    RefreshChallengeList();
}

void URecoveredChallengeWidget::OnChallengeProgressNotification(FName ChallengeID) {
    RefreshChallengeList();
}