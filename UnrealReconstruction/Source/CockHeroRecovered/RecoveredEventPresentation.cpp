#include "RecoveredRules.h"
#include "RecoveredNotificationWidget.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Misc/PackageName.h"
#include "RecoveredEdgeManager.h"

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
bool ARecoveredGlobalManager::CreateRecoveredNotification(FName IconName,const FString& Title,const FString& Description) {
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!IsValid(SessionScreen) || !Instance || !Instance->CurrentSave || !Instance->CurrentSave->GetBoolSetting(TEXT("AreNotificationBoxesEnabled?"),true)) return false;
    auto* Panel=Cast<UVerticalBox>(SessionScreen->GetWidgetFromName(TEXT("NotifVerticalBox")));
    UClass* Class=LoadClass<URecoveredNotificationWidget>(nullptr,TEXT("/Game/Recovery/UI/NotificationBoxWidget.NotificationBoxWidget_C"));
    if (!Panel || !GetWorld() || !Class) return false;
    auto* Notification=CreateWidget<URecoveredNotificationWidget>(GetWorld(),Class);
    if (!Notification) return false;
    UTexture2D* Icon=nullptr;
    if (IconName==TEXT("PunishmentIcon")) Icon=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/NotifBoxIcons/PunishmentIcon.PunishmentIcon"));
    else if (IconName==TEXT("EdgeItem")) Icon=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/InventoryButtonPNGs/EdgeItem.EdgeItem"));
    else if (IconName==TEXT("PrematureCumIcon") || IconName==TEXT("SuccessfulCumIcon")) {
        const FString Name=IconName.ToString();
        Icon=LoadObject<UTexture2D>(nullptr,*FString::Printf(TEXT("/Game/Recovery/Resources/Widgets/NotificationBoxIcons/%s.%s"),*Name,*Name));
    }
    Panel->AddChildToVerticalBox(Notification);
    Notification->OnNotificationExpired.AddUniqueDynamic(this,&ARecoveredGlobalManager::HandleRecoveredNotificationExpired);
    Notification->SetNotifBoxParams(Icon,Title,Description);
    EventOverlays.Add(Notification);
    return true;
}
UUserWidget* ARecoveredGlobalManager::SpawnRecoveredEdgeBreak(int32 EdgesUntilNextMercy) {
    if (BeatTimeline) BeatTimeline->PauseSequence();
    UUserWidget* Widget=SpawnRecoveredOverlay(TEXT("EdgeRestWidget"));
    if (UTextBlock* EdgesLeft=Widget ? Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("EdgesLeftText"))) : nullptr) {
        EdgesLeft->SetText(FText::FromString(EdgesUntilNextMercy==1 ? TEXT("1 Edge Left Until Mercy") : FString::Printf(TEXT("%d Edges Left Until Mercy"),EdgesUntilNextMercy)));
    }
    return Widget;
}
void ARecoveredGlobalManager::HandleRecoveredNotificationExpired(URecoveredNotificationWidget* Notification) {
    EventOverlays.Remove(Notification);
}
void ARecoveredGlobalManager::HandleRecoveredOutcome(const FRecoveredOutcomeEffects& Effects) {
    if (Effects.bClearEdgeHoldTimer && IsValid(EdgingManager)) EdgingManager->ClearRecoveredEdgeHold();
    const bool bSuccessful=Effects.OutcomeOverlaySourceIndex==-4047;
    CreateRecoveredNotification(bSuccessful ? TEXT("SuccessfulCumIcon") : TEXT("PrematureCumIcon"),bSuccessful ? TEXT("Perfect Finish") : TEXT("Early Climax"),bSuccessful ? TEXT("Full Rewards Unlocked — Victory Achieved") : TEXT("Post-Game Rewards Cut in Half"));
    FName Overlay;
    if (Effects.OutcomeOverlaySourceIndex==-4047) Overlay=TEXT("CummingOnTimeOverlay_Widget");
    else if (Effects.OutcomeOverlaySourceIndex==-4046) Overlay=TEXT("CummingEarlySuccubus_Overlay_Widget");
    else if (Effects.OutcomeOverlaySourceIndex==-4045) Overlay=TEXT("CummingEarlyOverlay_Widget");
    SpawnRecoveredOverlay(Overlay);
    if (BeatTimeline) { BeatTimeline->ApplySpeedModifier(Effects.SpeedModifier);BeatTimeline->ApplyStrokeCountModifier(Effects.StrokeCountModifier); }
    if (UUserWidget* PostCum = SpawnRecoveredOverlay(TEXT("PostCumContinue_Widget"))) {
        BindPostGameResultsButton(PostCum);
    }
    if (Effects.bApplyIronManPenalty) {
        ApplyRecoveredIronManStorePenalty();
        CreateRecoveredNotification(TEXT("PunishmentIcon"),TEXT("Iron Man Penalty"),TEXT("All packs locked. Unlock Points reset to 0."));
    }
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
