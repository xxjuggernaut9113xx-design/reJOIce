#include "RecoveredRules.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Misc/PackageName.h"

UUserWidget* ARecoveredGlobalManager::SpawnRecoveredOverlay(FName ScreenName) {
    if (ScreenName.IsNone() || !GetWorld()) return nullptr;
    APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0);
    if (!Controller) return nullptr;
    const FString Name=ScreenName.ToString();
    const FString Path=TEXT("/Game/Recovery/UI/")+Name+TEXT(".")+Name+TEXT("_C");
    if (!FPackageName::DoesPackageExist(TEXT("/Game/Recovery/UI/")+Name)) { LastSessionError=TEXT("Overlay asset is unavailable: ")+Name; return nullptr; }
    UClass* Class=LoadClass<UUserWidget>(nullptr,*Path);
    if (!Class) return nullptr;
    auto* Widget=CreateWidget<UUserWidget>(Controller,Class);
    if (Widget) { Widget->AddToViewport(0);EventOverlays.Add(Widget); }
    return Widget;
}
bool ARecoveredGlobalManager::SpawnRecoveredStore() {
    if (BeatTimeline) BeatTimeline->PauseSequence();
    bStoreOnCooldown=true;
    auto* Store=SpawnRecoveredOverlay(TEXT("StoreWidget"));
    if (!Store) { LastSessionError=TEXT("Recovered store screen is unavailable");return false; }
    BeatContext.CardType=4;
    GetWorldTimerManager().SetTimer(StoreCooldownTimer,this,&ARecoveredGlobalManager::CompleteRecoveredStoreCooldown,180.0f,false);
    OnSessionAction.Broadcast(TEXT("StoreCardStarted"));
    return true;
}
void ARecoveredGlobalManager::CompleteRecoveredStoreCooldown() { bStoreOnCooldown=false; }
void ARecoveredGlobalManager::HandleRecoveredOutcome(const FRecoveredOutcomeEffects& Effects) {
    if (BeatTimeline) { BeatTimeline->ApplySpeedModifier(Effects.SpeedModifier);BeatTimeline->ApplyStrokeCountModifier(Effects.StrokeCountModifier); }
    FName Overlay;
    if (Effects.OutcomeOverlaySourceIndex==-4047) Overlay=TEXT("CummingOnTimeOverlay_Widget");
    else if (Effects.OutcomeOverlaySourceIndex==-4046) Overlay=TEXT("CummingEarlySuccubus_Overlay_Widget");
    else if (Effects.OutcomeOverlaySourceIndex==-4045) Overlay=TEXT("CummingEarlyOverlay_Widget");
    SpawnRecoveredOverlay(Overlay);
    if (UUserWidget* PostCum = SpawnRecoveredOverlay(TEXT("PostCumContinue_Widget"))) {
        BindPostGameResultsButton(PostCum);
    }
    if (Effects.bApplyIronManPenalty) ApplyRecoveredIronManStorePenalty();
    // Outcome stinger: success for on-time, fail for early.
    PlayRecoveredSessionSound(Effects.OutcomeOverlaySourceIndex == -4047 ? TEXT("Success") : TEXT("Fail"));
    if (Effects.bDelayedContinuationRequested && GetWorld()) {
        GetWorldTimerManager().SetTimer(OutcomeContinuationTimer,[this]() {
            if (BeatTimeline) BeatTimeline->ApplySpeedModifier(.7699999809265137f);
            GetWorldTimerManager().SetTimer(OutcomeContinuationTimer,[this]() {
                if (BeatTimeline) BeatTimeline->ApplySpeedModifier(.5f);
                bStopSequence=true;
            },5.0f,false);
        },Effects.ContinuationDelay,false);
    }
}

void ARecoveredGlobalManager::PresentRecoveredBeat(const FRecoveredBeatEvent& Event) {
    PlayRecoveredSessionSound(TEXT("BeatTick"));
    auto* Controller=UGameplayStatics::GetPlayerController(this,0);
    UClass* Class=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/UMG_BeatIcon.UMG_BeatIcon_C"));
    if (!Controller || !Class) return;
    auto* Widget=CreateWidget<UUserWidget>(Controller,Class);
    auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Class);
    if (!Widget || !Generated) return;
    UWidgetAnimation* Animation=nullptr;
    for (UWidgetAnimation* Candidate:Generated->Animations) if (Candidate && Candidate->GetName()==TEXT("SpawnBeatAnim_INST")) Animation=Candidate;
    if (!Animation) return;
    Widget->AddToViewport(0);
    const double TravelTime=Event.TargetHitTime-Event.AbsoluteFireTime;
    const float Duration=Animation->GetEndTime()-Animation->GetStartTime();
    Widget->PlayAnimation(Animation,0,1,EUMGSequencePlayMode::Forward,TravelTime>0?Duration/TravelTime:1,false);
}
