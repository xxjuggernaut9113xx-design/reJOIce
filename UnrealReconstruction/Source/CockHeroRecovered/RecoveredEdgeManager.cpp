#include "RecoveredEdgeManager.h"

#include "RecoveredMenu.h"
#include "RecoveredRules.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Image.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

ARecoveredEdgeManager::ARecoveredEdgeManager() {
    PrimaryActorTick.bCanEverTick=false;
}

void ARecoveredEdgeManager::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    ClearRecoveredEdgeHold();
    if (GetWorld()) GetWorldTimerManager().ClearTimer(EdgeResolutionTimerHandle);
    RemoveRecoveredEdgeHoldOverlay();
    Super::EndPlay(EndPlayReason);
}

void ARecoveredEdgeManager::SetRecoveredGlobalManager(ARecoveredGlobalManager* Manager) {
    GlobalManagerRef=Manager;
}

bool ARecoveredEdgeManager::TriggerRecoveredEdgeV2() {
    if (!IsValid(GlobalManagerRef)) return false;

    // Source entry L3675: record the edge before classifying its streak branch.
    URecoveredStateRuleLibrary::RecordSessionMetric(GlobalManagerRef->SessionStats,ERecoveredMetric::Edges,1);
    GlobalManagerRef->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::Edges,1);
    ClearRecoveredEdgeHold();
    bIsPerfectEdge=false;
    LastEdgeRatio=0.0;

    const bool bDealWithTheDevil=GlobalManagerRef->BeatContext.ActiveModifiers.ContainsByPredicate([](const FString& Modifier) {
        return Modifier.Equals(TEXT("Deal With The Devil"),ESearchCase::IgnoreCase);
    });
    if (!GlobalManagerRef->bPlayerEdgedLastDraw) {
        GlobalManagerRef->CreateRecoveredNotification(TEXT("EdgeItem"),TEXT("Edge Streak Started"),TEXT("Continue to Edge to Bank\r\nHigh Rewards."));
        GlobalManagerRef->LastEdgeStrokeCount=25;
        GiveRecoveredEdge();
        GlobalManagerRef->PlayerVariables.bCanUseItems=false;
        GlobalManagerRef->PlayerVariables.bCanDraw=false;
        GlobalManagerRef->EdgeStreak=URecoveredStateRuleLibrary::AddInt32Wrapping(GlobalManagerRef->EdgeStreak,1);
        GlobalManagerRef->PlayerVariables.EdgeStreak=GlobalManagerRef->EdgeStreak;
        URecoveredStateRuleLibrary::SetSessionMetric(GlobalManagerRef->SessionStats,ERecoveredMetric::EdgeStreak,GlobalManagerRef->EdgeStreak);
        GlobalManagerRef->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::EdgeStreak,GlobalManagerRef->EdgeStreak);
        GlobalManagerRef->SpawnRecoveredOverlay(TEXT("StartEdgeStreakOverlay_Widget"));
        GlobalManagerRef->PlayDialogueLine(TEXT("SpecialEvent_5"));
        GlobalManagerRef->EdgeBreakDurationScaled=GlobalManagerRef->MasterEdgeBreakDuration;
        CurrentEdgesUntillNextMercy=MasterEdgesUntilNextMercy;
        PostEdgeBreakDuration=1.75;
    } else {
        const int32 Remaining=GlobalManagerRef->BeatTimeline ? GlobalManagerRef->BeatTimeline->GetBeatsRemaining() : 0;
        GlobalManagerRef->LastEdgeStrokeCount=URecoveredStateRuleLibrary::AddInt32Wrapping(GlobalManagerRef->PlayerVariables.AssignedStrokeCount,-Remaining);
        if (GlobalManagerRef->PlayerVariables.AssignedStrokeCount>0) {
            LastEdgeRatio=static_cast<double>(GlobalManagerRef->LastEdgeStrokeCount)/static_cast<double>(GlobalManagerRef->PlayerVariables.AssignedStrokeCount);
        }
        GlobalManagerRef->PlayerVariables.bCanUseItems=false;
        GlobalManagerRef->PlayerVariables.bCanDraw=false;
        if (LastEdgeRatio>=0.85) {
            GlobalManagerRef->PlayDialogueLine(TEXT("SpecialEvent_9"));
            if (!bDealWithTheDevil) GlobalManagerRef->AddToCumMeter(0.08);
            GlobalManagerRef->CreateRecoveredNotification(TEXT("EdgeItem"),TEXT("Perfect Edge!"),TEXT("Good boy!\r\nIncreased Rewards."));
            bIsPerfectEdge=true;
            GiveRecoveredEdge();
            GlobalManagerRef->AddToEdgeBank(50);
            GlobalManagerRef->EdgeStreak=URecoveredStateRuleLibrary::AddInt32Wrapping(GlobalManagerRef->EdgeStreak,1);
            AdjustRecoveredBreakDuration();
            GlobalManagerRef->SpawnRecoveredOverlay(TEXT("PerfectEdgeOverlay_Widget"));
            URecoveredStateRuleLibrary::RecordSessionMetric(GlobalManagerRef->SessionStats,ERecoveredMetric::PerfectEdges,1);
            GlobalManagerRef->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::PerfectEdges,1);
        } else {
            GlobalManagerRef->PlayDialogueLine(TEXT("SpecialEvent_5"));
            if (!bDealWithTheDevil) GlobalManagerRef->AddToCumMeter(0.05);
            const int32 Threshold=FMath::TruncToInt((1.0-0.85)*100.0);
            GlobalManagerRef->CreateRecoveredNotification(TEXT("EdgeItem"),TEXT("Normal Edge"),FString::Printf(TEXT("Edge within last %d%% of strokes\r\nto gain bonus rewards."),Threshold));
            GiveRecoveredEdge();
            GlobalManagerRef->AddToEdgeBank(30);
            GlobalManagerRef->SpawnRecoveredOverlay(TEXT("NormalEdgeOverlay_Widget"));
            AdjustRecoveredBreakDuration();
            GlobalManagerRef->EdgeStreak=URecoveredStateRuleLibrary::AddInt32Wrapping(GlobalManagerRef->EdgeStreak,1);
        }
        GlobalManagerRef->PlayerVariables.EdgeStreak=GlobalManagerRef->EdgeStreak;
        URecoveredStateRuleLibrary::SetSessionMetric(GlobalManagerRef->SessionStats,ERecoveredMetric::EdgeStreak,GlobalManagerRef->EdgeStreak);
        GlobalManagerRef->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::EdgeStreak,GlobalManagerRef->EdgeStreak);
    }

    GlobalManagerRef->PlayerVariables.bHasEdged=true;
    GlobalManagerRef->bPlayerEdgedLastDraw=true;
    GlobalManagerRef->PlayerVariables.TotalEdgeCount=URecoveredStateRuleLibrary::AddInt32Wrapping(GlobalManagerRef->PlayerVariables.TotalEdgeCount,1);
    GlobalManagerRef->PlayerVariables.LastEdgeTime=static_cast<double>(GlobalManagerRef->PlayerVariables.SessionLength);
    GlobalManagerRef->PlayerVariables.PerPdgeStrokeCountArray.Add(GlobalManagerRef->PlayerVariables.CurrentComboCount);
    GlobalManagerRef->PlayerVariables.BrokenComboArray.Add(GlobalManagerRef->PlayerVariables.CurrentComboCount);
    if (URecoveredGameInstance* Instance=Cast<URecoveredGameInstance>(GlobalManagerRef->GetGameInstance())) Instance->SaveRecoveredState();
    if (auto* Menu=Cast<URecoveredMenuWidget>(GlobalManagerRef->SessionScreen)) Menu->PlayRecoveredAnimation(TEXT("EdgedAnimation"));
    GlobalManagerRef->SetEdgeStreakCounterVisible(true);
    GlobalManagerRef->UpdateEdgeStreakProgressBar();
    const double AdjustedPostEdgeBreakDuration=AdjustRecoveredPostEdgeBreakDelay();
    if (GlobalManagerRef->BeatTimeline) GlobalManagerRef->BeatTimeline->ApplyStrokeCountModifier(999);
    ScheduleRecoveredEdgeCompletion(bIsPerfectEdge,AdjustedPostEdgeBreakDuration);
    return true;
}

void ARecoveredEdgeManager::BeginRecoveredEdgeHold(double AdjustedPostEdgeBreakDuration) {
    ClearRecoveredEdgeHold();
    RemoveRecoveredEdgeHoldOverlay();
    MasterEdgeHoldDuration=static_cast<double>(FMath::TruncToInt(AdjustedPostEdgeBreakDuration));
    CurrentEdgeHoldDuration=MasterEdgeHoldDuration;
    if (!IsValid(GlobalManagerRef) || CurrentEdgeHoldDuration<=0.0 || !GetWorld()) return;
    const int32 HoldSeconds=FMath::TruncToInt(CurrentEdgeHoldDuration);
    GlobalManagerRef->CreateRecoveredNotification(TEXT("EdgeItem"),TEXT("Hold It!"),FString::Printf(TEXT("Keep Stroking for %d\r\nSeconds. "),HoldSeconds));
    GetWorldTimerManager().SetTimer(EdgeHoldTimerHandle,this,&ARecoveredEdgeManager::CountdownEdgeHold,1.0f,true,0.0f);
    CreateRecoveredEdgeHoldOverlay();
}

void ARecoveredEdgeManager::CountdownEdgeHold() {
    if (IsValid(GlobalManagerRef) && GlobalManagerRef->BeatContext.CardType==6) return;
    CurrentEdgeHoldDuration-=1.0;
    if (CurrentEdgeHoldDuration<=0.0) {
        ClearRecoveredEdgeHold();
        RemoveRecoveredEdgeHoldOverlay();
        CompleteRecoveredEdgeBreak();
        return;
    }
    UpdateRecoveredEdgeHoldOverlay(FMath::TruncToInt(CurrentEdgeHoldDuration));
}

void ARecoveredEdgeManager::ClearRecoveredEdgeHold() {
    if (GetWorld()) GetWorldTimerManager().ClearTimer(EdgeHoldTimerHandle);
    EdgeHoldTimerHandle.Invalidate();
}

bool ARecoveredEdgeManager::IsRecoveredEdgeHoldActive() const {
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(EdgeHoldTimerHandle);
}

bool ARecoveredEdgeManager::IsRecoveredEdgeResolutionPending() const {
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(EdgeResolutionTimerHandle);
}

bool ARecoveredEdgeManager::CheckRecoveredEdgesUntilMercy() {
    if (CurrentEdgesUntillNextMercy<=1) return true;
    --CurrentEdgesUntillNextMercy;
    return false;
}

void ARecoveredEdgeManager::AdjustRecoveredBreakDuration() {
    if (!IsValid(GlobalManagerRef)) return;
    const double Percent=FMath::FRandRange(0.05,0.10);
    GlobalManagerRef->EdgeBreakDurationScaled=FMath::Clamp(GlobalManagerRef->EdgeBreakDurationScaled-(GlobalManagerRef->EdgeBreakDurationScaled*Percent),1.0,30.0);
}

double ARecoveredEdgeManager::AdjustRecoveredPostEdgeBreakDelay() {
    if (!IsValid(GlobalManagerRef)) return PostEdgeBreakDuration;
    PostEdgeBreakDuration=FMath::Clamp(PostEdgeBreakDuration+static_cast<double>(GlobalManagerRef->EdgeStreak/5),1.0,8.0);
    return PostEdgeBreakDuration;
}

void ARecoveredEdgeManager::GiveRecoveredEdge() {
    if (IsValid(GlobalManagerRef)) GlobalManagerRef->AcquireStoreItem(TEXT("Edge"));
}

void ARecoveredEdgeManager::CompleteRecoveredEdgeBreak() {
    if (!IsValid(GlobalManagerRef)) return;
    if (CheckRecoveredEdgesUntilMercy()) GlobalManagerRef->StartMercyEvent();
    else GlobalManagerRef->SpawnRecoveredEdgeBreak(CurrentEdgesUntillNextMercy);
}

void ARecoveredEdgeManager::ScheduleRecoveredEdgeCompletion(bool bPerfect,double AdjustedPostEdgeBreakDuration) {
    if (!GetWorld()) return;
    if (AdjustedPostEdgeBreakDuration>=2.0) {
        MasterEdgeHoldDuration=static_cast<double>(FMath::TruncToInt(AdjustedPostEdgeBreakDuration));
        CurrentEdgeHoldDuration=MasterEdgeHoldDuration;
        GetWorldTimerManager().SetTimer(EdgeResolutionTimerHandle,FTimerDelegate::CreateWeakLambda(this,[this,bPerfect]() {
            if (!IsValid(this)) return;
            if (bPerfect) CompleteRecoveredEdgeBreak();
            else BeginRecoveredEdgeHold(MasterEdgeHoldDuration);
        }),0.9f,false);
    } else {
        GetWorldTimerManager().SetTimer(EdgeResolutionTimerHandle,FTimerDelegate::CreateWeakLambda(this,[this]() {
            if (IsValid(this)) CompleteRecoveredEdgeBreak();
        }),1.0f,false);
    }
}

void ARecoveredEdgeManager::CreateRecoveredEdgeHoldOverlay() {
    if (!GetWorld()) return;
    UClass* Class=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/EdgeHoldCountdown_Overlay_Widget.EdgeHoldCountdown_Overlay_Widget_C"));
    if (!Class) return;
    EdgeHoldCountdownOverlay=CreateWidget<UUserWidget>(GetWorld(),Class);
    if (!IsValid(EdgeHoldCountdownOverlay)) return;
    UpdateRecoveredEdgeHoldOverlay(FMath::TruncToInt(CurrentEdgeHoldDuration));
    if (GEngine && GEngine->GameViewport) EdgeHoldCountdownOverlay->AddToViewport(0);
}

void ARecoveredEdgeManager::UpdateRecoveredEdgeHoldOverlay(int32 SecondsLeft) {
    if (!IsValid(EdgeHoldCountdownOverlay)) return;
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/1sec_clocktick.1sec_clocktick"))) {
        UGameplayStatics::PlaySound2D(this,Sound,1.0f,1.0f,0.0f,nullptr,nullptr,true);
    }
    if (SecondsLeft<1 || SecondsLeft>8) return;
    UImage* Image=Cast<UImage>(EdgeHoldCountdownOverlay->GetWidgetFromName(TEXT("Text")));
    const FString TextureName=FString::Printf(TEXT("HoldIt_Edge_%dSeconds"),SecondsLeft);
    if (Image) {
        const FString TexturePath=FString::Printf(TEXT("/Game/Recovery/Resources/Widgets/SpecialEventWidgets/%s.%s"),*TextureName,*TextureName);
        Image->SetBrushFromTexture(LoadObject<UTexture2D>(nullptr,*TexturePath),false);
    }
    if (const UWidgetBlueprintGeneratedClass* Class=Cast<UWidgetBlueprintGeneratedClass>(EdgeHoldCountdownOverlay->GetClass())) {
        for (UWidgetAnimation* Animation:Class->Animations) {
            if (Animation && (Animation->GetName()==TEXT("PlaySecondInterval_INST") || Animation->GetName()==TEXT("PlaySecondInterval"))) {
                EdgeHoldCountdownOverlay->PlayAnimation(Animation,0.0f,1,EUMGSequencePlayMode::Forward,1.0f,false);
                break;
            }
        }
    }
}

void ARecoveredEdgeManager::RemoveRecoveredEdgeHoldOverlay() {
    if (IsValid(EdgeHoldCountdownOverlay)) EdgeHoldCountdownOverlay->RemoveFromParent();
    EdgeHoldCountdownOverlay=nullptr;
}
