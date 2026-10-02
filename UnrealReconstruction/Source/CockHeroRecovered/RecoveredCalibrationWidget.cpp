#include "RecoveredCalibrationWidget.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
void URecoveredCalibrationWidget::BindControls(bool Bind) {
#define BIND_CONTROL(Name,Method) if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT(Name)))) { if(Bind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredCalibrationWidget::Method);else Button->OnClicked.RemoveDynamic(this,&URecoveredCalibrationWidget::Method); }
    BIND_CONTROL("Exit",CloseCalibration)
    BIND_CONTROL("IconClicker",RegisterTap)
    BIND_CONTROL("StartSequenceButton",StartSequence)
#undef BIND_CONTROL
}
void URecoveredCalibrationWidget::NativeConstruct() {
    Super::NativeConstruct();BindControls(true);
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (!Instance->CalibrationManager) {
            Instance->CalibrationManager=NewObject<URecoveredCalibrationManager>(Instance);
            if (Instance->CurrentSave) Instance->CurrentSave->GetLatencyProfile(Instance->CalibrationManager->CurrentProfile);
        }
        CalibrationManager=Instance->CalibrationManager;
        CalibrationManager->OnProgress.AddUniqueDynamic(this,&URecoveredCalibrationWidget::ShowProgress);
        CalibrationManager->OnComplete.AddUniqueDynamic(this,&URecoveredCalibrationWidget::CalibrationComplete);
        CalibrationManager->OnMetronome.AddUniqueDynamic(this,&URecoveredCalibrationWidget::ShowMetronome);
        ShowProgress(CalibrationManager->State,CalibrationManager->GetCalibrationProgress());
    }
}
void URecoveredCalibrationWidget::NativeDestruct() {
    BindControls(false);
    if (CalibrationManager) {
        CalibrationManager->OnProgress.RemoveDynamic(this,&URecoveredCalibrationWidget::ShowProgress);
        CalibrationManager->OnComplete.RemoveDynamic(this,&URecoveredCalibrationWidget::CalibrationComplete);
        CalibrationManager->OnMetronome.RemoveDynamic(this,&URecoveredCalibrationWidget::ShowMetronome);
        CalibrationManager->CancelCalibration();
    }
    Super::NativeDestruct();
}
void URecoveredCalibrationWidget::StartSequence() { if (CalibrationManager) CalibrationManager->StartCalibration(); }
void URecoveredCalibrationWidget::RegisterTap() { if (CalibrationManager && GetWorld()) CalibrationManager->RegisterBeatTap(GetWorld()->GetTimeSeconds()); }
void URecoveredCalibrationWidget::CloseCalibration() { RemoveFromParent(); }
void URecoveredCalibrationWidget::ShowMetronome() {
    auto* Sound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/click3_sfx.click3_sfx"));
    if (Sound && GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,1,1,0,nullptr,nullptr,true);
    PlayRecoveredAnimation(TEXT("MetronomePulse"));
}
void URecoveredCalibrationWidget::ShowProgress(uint8 State,float Progress) {
    auto Text=[this](const TCHAR* Name,const FText& Value) { if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(Name))) Label->SetText(Value); };
    if (State==0 || State==2) {
        Text(TEXT("StepText"),FText::FromString(TEXT("Tap Calibration")));
        Text(TEXT("InstructionText"),FText::FromString(TEXT("Click the heart when you hear the beat!")));
        const int32 Count=CalibrationManager?16-CalibrationManager->GetRequiredTapsRemaining():0;
        Text(TEXT("TapCounter"),FText::FromString(FString::Printf(TEXT("Taps:  %d/16"),State==0?0:Count)));
    } else if (State==4) Text(TEXT("StepText"),FText::FromString(TEXT("Complete")));
    if (auto* Bar=Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar")))) Bar->SetPercent(Progress);
}
void URecoveredCalibrationWidget::CalibrationComplete(const FRecoveredLatencyProfile& Profile) {
    if (auto* Label=Cast<UTextBlock>(GetWidgetFromName(TEXT("InstructionText")))) Label->SetText(FText::FromString(FString::Printf(TEXT("Calibration Finished!\r\nLatency: %gms"),Profile.UserPerceptionOffsetMs)));
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) if (Instance->CurrentSave && Instance->CurrentSave->SetLatencyProfile(Profile)) Instance->SaveRecoveredState();
    if (auto* Sound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/click4_sfx.click4_sfx"))) if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,1,1,0,nullptr,nullptr,true);
}
