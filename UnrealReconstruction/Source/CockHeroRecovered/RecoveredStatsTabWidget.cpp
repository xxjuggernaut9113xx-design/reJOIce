#include "RecoveredStatsTabWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredEditUsernameOverlay.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"

namespace {

const URecoveredGameInstance* GetRecoveredStatisticsInstance(const UUserWidget* Widget) {
    if (const auto* Stats=Cast<URecoveredStatsTabWidget>(Widget)) {
        if (const auto* Instance=Stats->GetRecoveredStatsTabGameInstance()) return Instance;
    }
    if (auto* Instance=Cast<URecoveredGameInstance>(Widget->GetGameInstance())) return Instance;
    return Widget->GetWorld() ? Cast<URecoveredGameInstance>(Widget->GetWorld()->GetGameInstance()) : nullptr;
}

const URecoveredSaveGame* GetRecoveredStatisticsSave(const UUserWidget* Widget) {
    if (const URecoveredGameInstance* Instance=GetRecoveredStatisticsInstance(Widget)) return Instance->CurrentSave;
    return nullptr;
}

int32 ReadRecoveredCounter(const URecoveredSaveGame* Save,const TCHAR* Key) {
    if (!Save) return 0;
    const double Value=Save->GetNumberSetting(Key,0);
    return FMath::IsFinite(Value) && Value>=MIN_int32 && Value<=MAX_int32 && Value==FMath::FloorToDouble(Value)
        ? static_cast<int32>(Value)
        : 0;
}

int32 SumRecoveredValues(const TArray<int32>& Values) {
    int64 Sum=0;
    for (const int32 Value:Values) Sum+=Value;
    return static_cast<int32>(FMath::Clamp<int64>(Sum,static_cast<int64>(MIN_int32),static_cast<int64>(MAX_int32)));
}

int32 MaxRecoveredValues(const TArray<int32>& Values) {
    int32 Result=0;
    for (const int32 Value:Values) Result=FMath::Max(Result,Value);
    return Result;
}

int32 ReadOrSum(const URecoveredSaveGame* Save,const TCHAR* Key,const TArray<int32>& History) {
    return Save && Save->HasSetting(Key) ? ReadRecoveredCounter(Save,Key) : SumRecoveredValues(History);
}

int32 ReadOrMax(const URecoveredSaveGame* Save,const TCHAR* Key,const TArray<int32>& History) {
    return Save && Save->HasSetting(Key) ? ReadRecoveredCounter(Save,Key) : MaxRecoveredValues(History);
}

FString FormatLargeNumber(int32 Value) {
    const bool bNegative=Value<0;
    uint64 Magnitude=bNegative ? static_cast<uint64>(-static_cast<int64>(Value)) : static_cast<uint64>(Value);
    FString Digits=LexToString(Magnitude);
    for (int32 Position=Digits.Len()-3; Position>0; Position-=3) Digits.InsertAt(Position,TEXT(","));
    return bNegative ? TEXT("-")+Digits : Digits;
}

FString FormatPlayTime(int32 Seconds) {
    const int32 SafeSeconds=FMath::Max(0,Seconds);
    const int32 Days=SafeSeconds/86400;
    const int32 Hours=(SafeSeconds%86400)/3600;
    const int32 Minutes=(SafeSeconds%3600)/60;
    const int32 Remaining=SafeSeconds%60;
    if (Days>0) return FString::Printf(TEXT("%dd %dh %dm"),Days,Hours,Minutes);
    if (Hours>0) return FString::Printf(TEXT("%dh %dm %ds"),Hours,Minutes,Remaining);
    if (Minutes>0) return FString::Printf(TEXT("%dm %ds"),Minutes,Remaining);
    return FString::Printf(TEXT("%ds"),Remaining);
}

FString FormatAverageDuration(int32 Seconds) {
    const int32 SafeSeconds=FMath::Max(0,Seconds);
    return FString::Printf(TEXT("%02d:%02d:%02d"),SafeSeconds/3600,(SafeSeconds%3600)/60,SafeSeconds%60);
}

FString FormatHighscoreDuration(int32 Seconds) {
    const int32 SafeSeconds=FMath::Max(0,Seconds);
    const int32 Hours=SafeSeconds/3600;
    const int32 Minutes=(SafeSeconds%3600)/60;
    const int32 Remaining=SafeSeconds%60;
    return Hours>0
        ? FString::Printf(TEXT("%02d:%02d:%02d"),Hours,Minutes,Remaining)
        : FString::Printf(TEXT("%02d:%02d"),Minutes,Remaining);
}

int32 RoundRecoveredAverage(int32 Total,int32 Count) {
    if (Count<1) return 0;
    return FMath::RoundToInt(static_cast<double>(Total)/static_cast<double>(Count));
}

int32 GetRecoveredSessionCount(const URecoveredSaveGame* Save) {
    if (!Save) return 0;
    if (Save->HasSetting(TEXT("Lifetime_TotalSessionsCompleted"))) return ReadRecoveredCounter(Save,TEXT("Lifetime_TotalSessionsCompleted"));
    const int32 Counter=ReadRecoveredCounter(Save,TEXT("SessionsWon"))+ReadRecoveredCounter(Save,TEXT("SessionsLost"));
    return Counter>0 ? Counter : Save->GetIntArraySetting(TEXT("AllSessionTimes")).Num();
}

int32 GetRecoveredSessionsWon(const URecoveredSaveGame* Save) {
    if (!Save) return 0;
    return Save->HasSetting(TEXT("Lifetime_TotalSessionsWon"))
        ? ReadRecoveredCounter(Save,TEXT("Lifetime_TotalSessionsWon"))
        : ReadRecoveredCounter(Save,TEXT("SessionsWon"));
}

int32 GetRecoveredChallengeCount(const URecoveredGameInstance* Instance) {
    if (!Instance || !Instance->ChallengeTracker) return 0;
    return Instance->ChallengeTracker->GetCompletedChallengeCount();
}

int32 GetRecoveredTotalChallengeCount(const URecoveredGameInstance* Instance) {
    if (!Instance || !Instance->ChallengeTracker) return 0;
    return Instance->ChallengeTracker->GetTotalChallengeCount();
}

}

void URecoveredStatsTabWidget::NativeConstruct() {
    Super::NativeConstruct();
    InitializeStats();
}

void URecoveredStatsTabWidget::NativeDestruct() {
    BindControls(false);
    if (ActiveUsernameOverlay) ActiveUsernameOverlay->OnClosed.RemoveDynamic(this,&URecoveredStatsTabWidget::HandleEditBoxClosed);
    ActiveUsernameOverlay=nullptr;
    Super::NativeDestruct();
}

void URecoveredStatsTabWidget::BindControls(bool bBind) {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("EditPlayerCardButton")))) {
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredStatsTabWidget::OpenEditUsernameOverlay);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredStatsTabWidget::OpenEditUsernameOverlay);
    }
}

void URecoveredStatsTabWidget::SetRecoveredStatsTabGameInstance(URecoveredGameInstance* Instance) {
    RecoveredInstanceOverride=Instance;
}

URecoveredGameInstance* URecoveredStatsTabWidget::GetRecoveredStatsTabGameInstance() const {
    if (RecoveredInstanceOverride) return RecoveredInstanceOverride;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    return GetWorld() ? Cast<URecoveredGameInstance>(GetWorld()->GetGameInstance()) : nullptr;
}

void URecoveredStatsTabWidget::InitializeStats() {
    BindControls(true);
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("LifetimeStatsText")))) Text->SetText(FText::FromString(GetRecoveredLifetimeStatsText()));
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("HighscoresText")))) Text->SetText(FText::FromString(GetRecoveredHighscoresText()));
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("AvgDurationText")))) Text->SetText(FText::FromString(GetRecoveredAverageDurationText()));
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("AvgEdgesText")))) Text->SetText(FText::FromString(GetRecoveredAverageEdgesText()));
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("AvgStrokesPerMinText")))) Text->SetText(FText::FromString(GetRecoveredAverageStrokesPerMinuteText()));
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("AvgStrokesText")))) Text->SetText(FText::FromString(GetRecoveredAverageStrokesText()));

    if (const URecoveredGameInstance* Instance=GetRecoveredStatisticsInstance(this)) {
        if (const URecoveredProgressionManager* Progression=Instance->ProgressionManager) {
            FRecoveredPlayerCardRow Card;
            if (Progression->GetPlayerCardData(Progression->GetEquippedPlayerCard(),Card)) {
                if (auto* Image=Cast<UImage>(GetWidgetFromName(TEXT("SelectedPlayerCard")))) {
                    Image->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr,*Card.CardImage),false);
                }
            }
            if (auto* Level=Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelText")))) {
                Level->SetText(FText::FromString(FString::Printf(TEXT("Level %d (%dXP/%dXP)"),Progression->CurrentLevel,Progression->CurrentXP,URecoveredProgressionLibrary::GetXPForNextLevel(Progression->CurrentLevel))));
            }
            if (auto* Bar=Cast<UProgressBar>(GetWidgetFromName(TEXT("LevelProgressBar")))) {
                Bar->SetPercent(URecoveredProgressionLibrary::CalculateLevelProgress(Progression->CurrentXP,Progression->CurrentLevel));
            }
        }
        if (auto* Title=Cast<UTextBlock>(GetWidgetFromName(TEXT("PlayerCardTitle")))) {
            Title->SetText(Instance->CurrentSave ? Instance->CurrentSave->GetTextSetting(TEXT("Playercard_Name"),FText::GetEmpty()) : FText::GetEmpty());
        }
    }
}

FString URecoveredStatsTabWidget::GetRecoveredAverageDurationText() const {
    const URecoveredSaveGame* Save=GetRecoveredStatisticsSave(this);
    const int32 Count=GetRecoveredSessionCount(Save);
    if (Count<1) return TEXT("00:00:00");
    return FormatAverageDuration(RoundRecoveredAverage(SumRecoveredValues(Save->GetIntArraySetting(TEXT("AllSessionTimes"))),Count));
}

FString URecoveredStatsTabWidget::GetRecoveredAverageEdgesText() const {
    const URecoveredSaveGame* Save=GetRecoveredStatisticsSave(this);
    const int32 Count=GetRecoveredSessionCount(Save);
    return FString::FromInt(RoundRecoveredAverage(ReadOrSum(Save,TEXT("Lifetime_TotalEdges"),Save ? Save->GetIntArraySetting(TEXT("AllSessionEdges")) : TArray<int32>()),Count));
}

FString URecoveredStatsTabWidget::GetRecoveredAverageStrokesPerMinuteText() const {
    const URecoveredSaveGame* Save=GetRecoveredStatisticsSave(this);
    const int32 Seconds=Save ? SumRecoveredValues(Save->GetIntArraySetting(TEXT("AllSessionTimes"))) : 0;
    const int32 Strokes=ReadOrSum(Save,TEXT("Lifetime_TotalStrokes"),Save ? Save->GetIntArraySetting(TEXT("AllSessionStrokeCounts")) : TArray<int32>());
    if (Seconds<1) return TEXT("0");
    return FString::FromInt(FMath::RoundToInt((static_cast<double>(Strokes)/static_cast<double>(Seconds))*60.0));
}

FString URecoveredStatsTabWidget::GetRecoveredAverageStrokesText() const {
    const URecoveredSaveGame* Save=GetRecoveredStatisticsSave(this);
    return FString::FromInt(RoundRecoveredAverage(ReadOrSum(Save,TEXT("Lifetime_TotalStrokes"),Save ? Save->GetIntArraySetting(TEXT("AllSessionStrokeCounts")) : TArray<int32>()),GetRecoveredSessionCount(Save)));
}

FString URecoveredStatsTabWidget::GetRecoveredLifetimeStatsText() const {
    const URecoveredSaveGame* Save=GetRecoveredStatisticsSave(this);
    if (!Save) return FString();
    const int32 Sessions=GetRecoveredSessionCount(Save);
    const int32 Wins=GetRecoveredSessionsWon(Save);
    const int32 PlayTime=SumRecoveredValues(Save->GetIntArraySetting(TEXT("AllSessionTimes")));
    const int32 Edges=ReadOrSum(Save,TEXT("Lifetime_TotalEdges"),Save->GetIntArraySetting(TEXT("AllSessionEdges")));
    const int32 Strokes=ReadOrSum(Save,TEXT("Lifetime_TotalStrokes"),Save->GetIntArraySetting(TEXT("AllSessionStrokeCounts")));
    const int32 Enemies=Save->HasSetting(TEXT("Lifetime_TotalEnemiesDefeated")) ? ReadRecoveredCounter(Save,TEXT("Lifetime_TotalEnemiesDefeated")) : ReadRecoveredCounter(Save,TEXT("TotalEnemiesDefeated"));
    const int32 Succubi=Save->HasSetting(TEXT("Lifetime_TotalSuccubiDefeated")) ? ReadRecoveredCounter(Save,TEXT("Lifetime_TotalSuccubiDefeated")) : ReadRecoveredCounter(Save,TEXT("TotalSuccubiDefeated"));
    const int32 Money=ReadRecoveredCounter(Save,TEXT("Lifetime_TotalMoneySpent"));
    const int32 Items=Save->HasSetting(TEXT("Lifetime_TotalItemUses")) ? ReadRecoveredCounter(Save,TEXT("Lifetime_TotalItemUses")) : ReadRecoveredCounter(Save,TEXT("TotalLifetimeItemUses"));
    const int32 CumWindows=Save->HasSetting(TEXT("Lifetime_TotalCumWindowsHit")) ? ReadRecoveredCounter(Save,TEXT("Lifetime_TotalCumWindowsHit")) : ReadRecoveredCounter(Save,TEXT("TotalDrawCount"));
    const URecoveredGameInstance* Instance=GetRecoveredStatisticsInstance(this);
    const int32 Completed=GetRecoveredChallengeCount(Instance);
    const int32 TotalChallenges=GetRecoveredTotalChallengeCount(Instance);
    const FString WinRate=Sessions<1 ? TEXT("0%") : FString::Printf(TEXT("%.0f%%"),(static_cast<double>(Wins)/static_cast<double>(Sessions))*100.0);
    return FString::Printf(
        TEXT("Play Time: %s\nSessions Played: %d\nWin Rate: %s\nTotal Edges: %s\nTotal Strokes: %s\nEnemies Defeated: %s\nSuccubi Defeated: %s\nMoney Spent: %s\nChallenges Completed: %d/%d\nItems Used: %d\nCum Windows Hit: %d\n"),
        *FormatPlayTime(PlayTime),Sessions,*WinRate,*FormatLargeNumber(Edges),*FormatLargeNumber(Strokes),*FormatLargeNumber(Enemies),*FormatLargeNumber(Succubi),*FormatLargeNumber(Money),Completed,TotalChallenges,Items,CumWindows);
}

FString URecoveredStatsTabWidget::GetRecoveredHighscoresText() const {
    const URecoveredSaveGame* Save=GetRecoveredStatisticsSave(this);
    if (!Save) return FString();
    const int32 EdgeStreak=ReadRecoveredCounter(Save,TEXT("Lifetime_BestEdgeStreak"));
    const int32 Combo=ReadOrMax(Save,TEXT("Lifetime_BestCombo"),Save->GetIntArraySetting(TEXT("AllSessionCombos")));
    const int32 Edges=ReadOrMax(Save,TEXT("Lifetime_MostEdgesInSession"),Save->GetIntArraySetting(TEXT("AllSessionEdges")));
    const int32 Strokes=ReadOrMax(Save,TEXT("Lifetime_MostStrokesInSession"),Save->GetIntArraySetting(TEXT("AllSessionStrokeCounts")));
    const int32 Longest=ReadOrMax(Save,TEXT("Lifetime_LongestSessionSeconds"),Save->GetIntArraySetting(TEXT("AllSessionTimes")));
    return FString::Printf(
        TEXT("Longest Edge Streak: %d\nHighest Combo: %d\nMost Edges: %d\nMost Strokes: %d\nLongest Session: %s\nMost Succubi: %d\nMost XP Earned: %d\nMost Perfect Edges: %d\nMost Cum Windows Hit: %d\nMost Items Used: %d\nMost Money Spent: %d\n"),
        EdgeStreak,Combo,Edges,Strokes,*FormatHighscoreDuration(Longest),
        ReadRecoveredCounter(Save,TEXT("Lifetime_MostSuccubiInSession")),
        ReadRecoveredCounter(Save,TEXT("Lifetime_MostXPEarnedInSession")),
        ReadRecoveredCounter(Save,TEXT("Lifetime_MostPerfectEdgesInSession")),
        ReadRecoveredCounter(Save,TEXT("Lifetime_MostCumWindowsHitInSession")),
        ReadRecoveredCounter(Save,TEXT("Lifetime_MostItemsUsedInSession")),
        ReadRecoveredCounter(Save,TEXT("Lifetime_MostMoneySpentInSession")));
}

void URecoveredStatsTabWidget::OpenEditUsernameOverlay() {
    if (ActiveUsernameOverlay) return;
    UClass* OverlayClass=LoadClass<URecoveredEditUsernameOverlay>(nullptr,TEXT("/Game/Recovery/UI/EditUsernameOverlay.EditUsernameOverlay_C"));
    if (!OverlayClass) return;
    ActiveUsernameOverlay=CreateWidget<URecoveredEditUsernameOverlay>(GetWorld(),OverlayClass);
    if (!ActiveUsernameOverlay) return;
    ActiveUsernameOverlay->OnClosed.AddUniqueDynamic(this,&URecoveredStatsTabWidget::HandleEditBoxClosed);
    ActiveUsernameOverlay->AddToViewport(0);
}

void URecoveredStatsTabWidget::HandleEditBoxClosed() {
    InitializeStats();
    ActiveUsernameOverlay=nullptr;
}
