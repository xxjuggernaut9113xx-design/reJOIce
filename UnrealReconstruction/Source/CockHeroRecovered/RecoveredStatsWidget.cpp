#include "RecoveredStatsWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/World.h"
#include "RecoveredRules.h"

namespace {

int32 ReadRecoveredInt(const URecoveredSaveGame* Save,const TCHAR* Key) {
    if (!Save) return 0;
    const double Value=Save->GetNumberSetting(Key,0);
    return FMath::IsFinite(Value) && Value>=MIN_int32 && Value<=MAX_int32 && Value==FMath::FloorToDouble(Value)
        ? static_cast<int32>(Value)
        : 0;
}

double CalculateRecoveredAverage(const TArray<int32>& Values) {
    int32 TotalSum=0;
    int32 Count=0;
    for (int32 Value:Values) {
        TotalSum=URecoveredStateRuleLibrary::AddInt32Wrapping(TotalSum,Value);
        Count=URecoveredStateRuleLibrary::AddInt32Wrapping(Count,1);
    }
    return Count>0 ? static_cast<double>(TotalSum)/static_cast<double>(Count) : 0.0;
}

FString FormatRecoveredTwoDigits(int32 Value) {
    return FString::Printf(TEXT("%02d"),Value);
}

}

void URecoveredStatsScreenWidget::SetRecoveredStatisticsGameInstance(URecoveredGameInstance* Instance) {
    RecoveredInstanceOverride=Instance;
}

void URecoveredStatsScreenWidget::NativeConstruct() {
    Super::NativeConstruct();
    InitializeRecoveredStatsScreen();
}

void URecoveredStatsScreenWidget::InitializeRecoveredStatsScreen() {
    BindRecoveredNavigation(true);
    CalculateHighScores();
    CalculateLifetimeAverages();
    if (auto* Instance=GetRecoveredInstance()) {
        Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"),Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage"))));
    }
    ApplyRecoveredTextBindings();
}

void URecoveredStatsScreenWidget::NativeDestruct() {
    BindRecoveredNavigation(false);
    Super::NativeDestruct();
}

void URecoveredStatsScreenWidget::BindRecoveredNavigation(bool bBind) {
    if (auto* BackButton=Cast<UButton>(GetWidgetFromName(TEXT("BackButton")))) {
        if (bBind) {
            BackButton->OnClicked.AddUniqueDynamic(this,&URecoveredStatsScreenWidget::CloseRecoveredStats);
            BackButton->OnHovered.AddUniqueDynamic(this,&URecoveredStatsScreenWidget::PlayBackButtonHover);
            BackButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredStatsScreenWidget::PlayBackButtonUnhover);
        } else {
            BackButton->OnClicked.RemoveDynamic(this,&URecoveredStatsScreenWidget::CloseRecoveredStats);
            BackButton->OnHovered.RemoveDynamic(this,&URecoveredStatsScreenWidget::PlayBackButtonHover);
            BackButton->OnUnhovered.RemoveDynamic(this,&URecoveredStatsScreenWidget::PlayBackButtonUnhover);
        }
    }
}

void URecoveredStatsScreenWidget::PlayBackButtonHover() {
    PlayRecoveredAnimation(TEXT("ButtonHover"));
}

void URecoveredStatsScreenWidget::PlayBackButtonUnhover() {
    PlayRecoveredAnimation(TEXT("ButtonUnHover"));
}

void URecoveredStatsScreenWidget::RefreshRecoveredStats() {
    CalculateHighScores();
    CalculateLifetimeAverages();
    ApplyRecoveredTextBindings();
}

void URecoveredStatsScreenWidget::CalculateHighScores() {
    URecoveredSaveGame* Save=GetRecoveredSave();
    if (!Save) return;
    for (int32 Value:Save->GetIntArraySetting(TEXT("AllSessionCombos"))) HighestCombo=FMath::Max(HighestCombo,Value);
    for (int32 Value:Save->GetIntArraySetting(TEXT("AllSessionTimes"))) HighestSessionTime=FMath::Max(HighestSessionTime,Value);
    for (int32 Value:Save->GetIntArraySetting(TEXT("AllSessionEdges"))) HighestEdges=FMath::Max(HighestEdges,Value);
    for (int32 Value:Save->GetIntArraySetting(TEXT("AllSessionStrokeCounts"))) HighestStrokeCount=FMath::Max(HighestStrokeCount,Value);
}

void URecoveredStatsScreenWidget::CalculateLifetimeAverages() {
    URecoveredSaveGame* Save=GetRecoveredSave();
    if (!Save) return;
    AvgSessionEdges=FMath::TruncToInt(CalculateRecoveredAverage(Save->GetIntArraySetting(TEXT("AllSessionEdges"))));
    AvgStrokesPerEdge=FMath::TruncToInt(CalculateRecoveredAverage(Save->GetIntArraySetting(TEXT("AllStrokesPerEdge"))));
    AvgStrokeCount=FMath::TruncToInt(CalculateRecoveredAverage(Save->GetIntArraySetting(TEXT("AllSessionStrokeCounts"))));
    AvgCombo=FMath::TruncToInt(CalculateRecoveredAverage(Save->GetIntArraySetting(TEXT("AllSessionCombos"))));
    AvgTime=FMath::TruncToInt(CalculateRecoveredAverage(Save->GetIntArraySetting(TEXT("AllSessionTimes"))));
}

void URecoveredStatsScreenWidget::CloseRecoveredStats() {
    if (auto* Instance=GetRecoveredInstance()) Instance->RefreshRecoveredMainMenuBackground();
    RemoveFromParent();
}

FText URecoveredStatsScreenWidget::FormatRecoveredTime(int32 Time) const {
    const int32 RemainingAfterHours=Time%3600;
    const int32 Hours=Time/3600;
    const int32 Minutes=RemainingAfterHours/60;
    const int32 Seconds=Time%60;
    return FText::FromString(
        FormatRecoveredTwoDigits(Hours)+TEXT(":")+
        FormatRecoveredTwoDigits(Minutes)+TEXT(":")+
        FormatRecoveredTwoDigits(Seconds));
}

FText URecoveredStatsScreenWidget::GetRecoveredLifetimeStatsDisplay() const {
    const URecoveredSaveGame* Save=GetRecoveredSave();
    if (!Save) return FText::GetEmpty();
    return FText::FromString(
        FString::Printf(
            TEXT("Total Strokes: %d\r\nTotal Edges: %d\r\nTotal Draw Count: %d\r\nTotal Enemies Defeated: %d\r\nTotal Succubi Defeated: %d\r\nTotal Lifetime Item Uses: %d\r\nSessions Won: %d\r\nSessions Lost: %d\r\nTimes Lost to Succubus: %d\r\nLifetime Max Heat Draws: %d\r\nLifetime Taunts Used: %d"),
            ReadRecoveredInt(Save,TEXT("TotalLifetimeStrokes")),
            ReadRecoveredInt(Save,TEXT("TotalLifetimeEdges")),
            ReadRecoveredInt(Save,TEXT("TotalDrawCount")),
            ReadRecoveredInt(Save,TEXT("TotalEnemiesDefeated")),
            ReadRecoveredInt(Save,TEXT("TotalSuccubiDefeated")),
            ReadRecoveredInt(Save,TEXT("TotalLifetimeItemUses")),
            ReadRecoveredInt(Save,TEXT("SessionsWon")),
            ReadRecoveredInt(Save,TEXT("SessionsLost")),
            ReadRecoveredInt(Save,TEXT("TimesLostToSuccubus")),
            ReadRecoveredInt(Save,TEXT("LifetimeMaxHeatDraws")),
            ReadRecoveredInt(Save,TEXT("LifetimeTauntCount"))));
}

FText URecoveredStatsScreenWidget::GetRecoveredHighScores() const {
    return FText::FromString(FString::Printf(
        TEXT("Longest Session: %s\r\nHighest Combo: %d\r\nHighest Edges: %d\r\nHighest Stroke Count: %d"),
        *FormatRecoveredTime(HighestSessionTime).ToString(),
        HighestCombo,
        HighestEdges,
        HighestStrokeCount));
}

FText URecoveredStatsScreenWidget::GetRecoveredAvgSessionDurationText() const {
    return FText::FromString(FString::Printf(TEXT("Avg Duration:\r\n%s"),*FormatRecoveredTime(AvgTime).ToString()));
}

FText URecoveredStatsScreenWidget::GetRecoveredAvgEdgesText() const {
    return FText::FromString(FString::Printf(TEXT("Avg Edges: \r\n%d"),AvgSessionEdges));
}

FText URecoveredStatsScreenWidget::GetRecoveredAvgStrokesPerEdgeText() const {
    return FText::FromString(FString::Printf(TEXT("Avg Strokes/Edge:\r\n%d"),AvgStrokesPerEdge));
}

FText URecoveredStatsScreenWidget::GetRecoveredAvgStrokeCountText() const {
    return FText::FromString(FString::Printf(TEXT("Avg Strokes: \r\n%d"),AvgStrokeCount));
}

void URecoveredStatsScreenWidget::ApplyRecoveredTextBindings() {
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock")))) Text->SetText(GetRecoveredAvgSessionDurationText());
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_1")))) Text->SetText(GetRecoveredAvgEdgesText());
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_2")))) Text->SetText(GetRecoveredAvgStrokesPerEdgeText());
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_3")))) Text->SetText(GetRecoveredAvgStrokeCountText());
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_5")))) Text->SetText(GetRecoveredLifetimeStatsDisplay());
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_7")))) Text->SetText(GetRecoveredHighScores());
}

URecoveredGameInstance* URecoveredStatsScreenWidget::GetRecoveredInstance() const {
    if (RecoveredInstanceOverride) return RecoveredInstanceOverride;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) return Instance;
    if (const UWorld* World=GetWorld()) return Cast<URecoveredGameInstance>(World->GetGameInstance());
    return nullptr;
}

URecoveredSaveGame* URecoveredStatsScreenWidget::GetRecoveredSave() const {
    if (const auto* Instance=GetRecoveredInstance()) return Instance->CurrentSave;
    return nullptr;
}
