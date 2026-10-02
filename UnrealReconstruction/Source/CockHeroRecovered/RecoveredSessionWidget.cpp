#include "RecoveredSessionWidget.h"
#include "RecoveredRules.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Engine/Texture2D.h"
#include "MediaTexture.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

void URecoveredSessionWidget::BindSession(bool bBind) {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("DrawButtonTextButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::DrawCard);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::DrawCard);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResumeButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::ResumeSession);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::ResumeSession);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SettingsMenuButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::OpenSessionSettings);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::OpenSessionSettings);
    }
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager && Manager->MediaPlayback) {
        if(bBind) Manager->MediaPlayback->OnMediaReady.AddUniqueDynamic(this,&URecoveredSessionWidget::DisplayMedia);
        else Manager->MediaPlayback->OnMediaReady.RemoveDynamic(this,&URecoveredSessionWidget::DisplayMedia);
    }
}
void URecoveredSessionWidget::NativeConstruct() {
    Super::NativeConstruct(); BindSession(true);
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager && Manager->MediaPlayback && Manager->MediaPlayback->CurrentTexture) DisplayMedia(Manager->MediaPlayback->CurrentTexture);
}
void URecoveredSessionWidget::NativeDestruct() { BindSession(false); Super::NativeDestruct(); }
void URecoveredSessionWidget::DisplayMedia(UTexture* Texture) {
    auto* Image=Cast<UImage>(GetWidgetFromName(TEXT("MainImage")));
    if (!Image || !Texture) return;
    if (auto* Still=Cast<UTexture2D>(Texture)) { Image->SetBrushFromTexture(Still,false); return; }
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Cast<UMediaTexture>(Texture) && Manager && Manager->MediaPlayback) {
        if (auto* Material=Manager->MediaPlayback->GetVideoDisplayMaterial()) Image->SetBrushFromMaterial(Material);
    }
}
void URecoveredSessionWidget::ResumeSession() {
    if (auto* Border=GetWidgetFromName(TEXT("PauseMenuMasterBorder"))) Border->SetVisibility(ESlateVisibility::Hidden);
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager && Manager->BeatTimeline) Manager->BeatTimeline->ResumeSequence();
    if (Manager && Manager->MediaPlayback) Manager->MediaPlayback->SetPaused(false);
}
void URecoveredSessionWidget::OpenSessionSettings() {
    if (!GetWorld()) return;
    UClass* Class=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/SettingsMenuWidget.SettingsMenuWidget_C"));
    if (Class) if (auto* Settings=CreateWidget<UUserWidget>(GetWorld(),Class)) Settings->AddToViewport(0);
}
void URecoveredSessionWidget::DrawCard() {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    // Original handler blocks skipping a succubus before testing CanDraw.
    if (!Manager || Manager->BeatContext.CardType==3 || !Manager->PlayerVariables.bCanDraw) return;
    Manager->RequestNextRecoveredCard(true);
}
void URecoveredSessionWidget::NativeTick(const FGeometry& Geometry,float DeltaSeconds) {
    Super::NativeTick(Geometry,DeltaSeconds);
    RefreshSessionDisplays(GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr);
}
void URecoveredSessionWidget::RefreshSessionDisplays(ARecoveredGlobalManager* Manager) {
    if (!Manager) return;
    auto Text=[this](FName Name,const FText& Value) { if (auto* Widget=Cast<UTextBlock>(GetWidgetFromName(Name))) Widget->SetText(Value); };
    auto Percent=[this](FName Name,double Value) { if (auto* Widget=Cast<UProgressBar>(GetWidgetFromName(Name))) Widget->SetPercent(static_cast<float>(Value)); };
    FNumberFormattingOptions IntegerFormat;
    IntegerFormat.UseGrouping=true;IntegerFormat.MinimumIntegralDigits=1;IntegerFormat.MaximumIntegralDigits=324;
    Text(TEXT("StrokeCounter"),FText::AsNumber(FMath::Clamp(Manager->BeatTimeline ? Manager->BeatTimeline->GetBeatsRemaining() : 0,0,999),&IntegerFormat));
    Text(TEXT("CoinCounterText"),FText::AsNumber(Manager->PlayerVariables.PlayerCoins,&IntegerFormat));
    Text(TEXT("ComboText"),FText::FromString(FString::FromInt(Manager->PlayerVariables.CurrentComboCount)+TEXT("X COMBO")));
    const int32 Seconds=Manager->PlayerVariables.SessionLength;
    FNumberFormattingOptions TimeFormat=IntegerFormat;TimeFormat.MinimumIntegralDigits=2;TimeFormat.MaximumIntegralDigits=2;
    const FString Duration=FText::AsNumber(Seconds/3600,&TimeFormat).ToString()+TEXT(":")+FText::AsNumber((Seconds%3600)/60,&TimeFormat).ToString()+TEXT(":")+FText::AsNumber(Seconds%60,&TimeFormat).ToString();
    Text(TEXT("SessionDurationText"),FText::FromString(Duration));
    Percent(TEXT("HeatMeterBar"),Manager->HeatLevel/100.0);
    Percent(TEXT("CumMeterProgressBar"),Manager->CumMeterPercentage);
    Percent(TEXT("LootMeterProgressBar"),Manager->LootBarPercentage);
}
