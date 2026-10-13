#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredPostGameWidgets.generated.h"

class URecoveredGameInstance;
class URecoveredProgressionManager;
class UTexture2D;
class UWidgetAnimation;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredXPBarFilled);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredLevelUpScreenComplete);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredXPBarWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void SetRecoveredPostGameGameInstance(URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void InitializeBar(int32 StartLevel, int32 StartXP, int32 XPToNext);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void AddXPAnimated(int32 XPAmount, float Duration);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void UpdateDisplay();
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") int32 GetOverflowXP() const { return OverflowXP; }
    void AdvanceRecoveredXPAnimation(float InDeltaTime);

    UPROPERTY(BlueprintAssignable, Category="Recovered|PostGame") FRecoveredXPBarFilled OnBarFilled;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 CurrentLevel = 1;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 TargetLevel = 2;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 CurrentXP = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 MaxXP = 100;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 OverflowXP = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 AnimationStartXP = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") int32 AnimationTargetXP = 0;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") float AnimationDuration = 0.0f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") float AnimationElapsed = 0.0f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Recovered|PostGame") bool bIsAnimating = false;

protected:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
    URecoveredProgressionManager* ResolveRecoveredProgressionManager() const;
    UWidgetAnimation* FindRecoveredAnimation(FName Name) const;
    UPROPERTY(Transient) TObjectPtr<URecoveredGameInstance> RecoveredGameInstance;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredPlayerCardWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void SetRecoveredPostGameGameInstance(URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void InitializePlayerCard();

protected:
    virtual void NativeConstruct() override;

private:
    URecoveredGameInstance* ResolveRecoveredGameInstance() const;
    UPROPERTY(Transient) TObjectPtr<URecoveredGameInstance> RecoveredGameInstance;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredLevelUpScreenWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void SetRecoveredPostGameGameInstance(URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void InitializeScreen(const FRecoveredLevelUpEventData& InData);
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void PlaySoundFX();
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void SequenceEvent();
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void SequenceEvent__ENTRYPOINTWBP_LevelUpScreen();
    UFUNCTION(BlueprintCallable, Category="Recovered|PostGame") void SequenceEvent__ENTRYPOINTWBP_LevelUpScreen_0();
    UFUNCTION(BlueprintPure, Category="Recovered|PostGame") float GetRecoveredLevelUpAnimationDuration() const;

    UPROPERTY(BlueprintAssignable, Category="Recovered|PostGame") FRecoveredLevelUpScreenComplete OnScreenComplete;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered|PostGame") FRecoveredLevelUpEventData LevelUpData;

protected:
    virtual void NativeConstruct() override;

private:
    URecoveredGameInstance* ResolveRecoveredGameInstance() const;
    URecoveredProgressionManager* ResolveRecoveredProgressionManager() const;
    UWidgetAnimation* FindRecoveredAnimation(FName Name) const;
    UPROPERTY(Transient) TObjectPtr<URecoveredGameInstance> RecoveredGameInstance;
};
