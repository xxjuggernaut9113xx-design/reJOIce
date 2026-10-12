#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredSessionSummaryWidget.generated.h"

class ARecoveredGlobalManager;
class USoundBase;
class UWidgetAnimation;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredSessionSummaryWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void InitializeRecoveredSummary(const FRecoveredSessionRewardData& RewardData, bool bDidPlayerWin);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void PlayPostGameVoicelines();
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") USoundBase* SelectRecoveredPostGameVoiceline() const;
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") USoundBase* SelectRecoveredPostGameVoicelineFor(FName VoicePackID, bool bWon) const;
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void StartRecoveredBeginDisplayAnimation();
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") bool IsRecoveredAnimationPlaying(FName AnimationName) const;
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") bool DidRecoveredPlayerWin() const { return bRecoveredDidPlayerWin; }
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") static FString GetRecoveredSummarySocialURL(FName Destination);

protected:
    virtual void NativeOnInitialized() override;
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    void BindRecoveredControls(bool bBind);
    void ApplyRecoveredPresentation();
    void InitializeRecoveredNestedWidgets();
    void InitializeRecoveredXPBar(int32 Level, int32 XP, int32 XPToNextLevel) const;
    ARecoveredGlobalManager* ResolveRecoveredGlobalManager() const;
    UWidgetAnimation* FindRecoveredAnimation(FName Name) const;
    USoundBase* SelectRecoveredVoiceLine(FName PropertyName) const;
    UFUNCTION() void HandleRecoveredReturnToMenu();
    UFUNCTION() void HandleRecoveredPatreonClicked();
    UFUNCTION() void HandleRecoveredPatreonHovered();
    UFUNCTION() void HandleRecoveredPatreonUnhovered();
    UFUNCTION() void HandleRecoveredDiscordClicked();
    UFUNCTION() void HandleRecoveredDiscordHovered();
    UFUNCTION() void HandleRecoveredDiscordUnhovered();
    UFUNCTION() void HandleRecoveredTwitterClicked();
    UFUNCTION() void HandleRecoveredTwitterHovered();
    UFUNCTION() void HandleRecoveredTwitterUnhovered();

    UPROPERTY(Transient) FRecoveredSessionRewardData RecoveredRewardData;
    UPROPERTY(Transient) bool bRecoveredDidPlayerWin = false;
    UPROPERTY(Transient) bool bRecoveredSummaryInitialized = false;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> VillainessPostGameVictoryLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> VillainessPostGameDefeatLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> BratPostGameVictoryLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> BratPostGameDefeatLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> DommyMommyPostGameVictoryLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> DommyMommyPostGameDefeatLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> SweetheartPostGameVictoryLines;
    UPROPERTY(EditDefaultsOnly, Category="Recovered|PostGame|Voicelines") TArray<TObjectPtr<USoundBase>> SweetheartPostGameDefeatLines;
};
