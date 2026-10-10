#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateTypes.h"
#include "RecoveredMenu.generated.h"

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredTooltipDefinition {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FText Title;
    UPROPERTY(EditAnywhere,BlueprintReadWrite) FText Description;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredTooltip : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Tooltip") FText TooltipTitle;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Tooltip") FText TooltipDescription;
    UFUNCTION(BlueprintCallable,Category="Recovered Tooltip") void SetTitleAndDescription(const FText& Title,const FText& Description);
protected:
    virtual void NativeConstruct() override;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredMenuWidget : public UUserWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Tooltips") TMap<FName,FRecoveredTooltipDefinition> StaticTooltips;
    UFUNCTION(BlueprintCallable,Category="Recovered Tooltips") void AttachRecoveredTooltips();
    UFUNCTION(BlueprintCallable,Category="Recovered Animation") class UUMGSequencePlayer* PlayRecoveredAnimation(FName Name,int32 Loops=1,float Speed=1);
protected:
    virtual void NativeConstruct() override;
};

// Replaces the four verified navigation handlers in MainMenu. Other handlers,
// bindings, animations, patron checks and session initialization remain separate.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredMainMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered Menu") TObjectPtr<UUserWidget> LastOpenedScreen;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Menu") TArray<TObjectPtr<class UTexture2D>> PatreonCoverGirlArray;
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void InitCoverGirl();
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered Menu") FString LastNavigationError;
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenDifficulty();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenChallenges();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenStatsDebug();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenSettings();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenUnlockStore();
    UFUNCTION() void CloseAdultWarning();
    UFUNCTION() void CloseTutorialSplash();
    UFUNCTION() void CloseUpdateSplash();
    UFUNCTION() void QuitFromMenu();
    UFUNCTION() void RefreshBackground();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void OpenScreen(const TCHAR* ScreenName);
    void BindNavigation(bool bBind);
    void OpenInitialCalibration();
    FTimerHandle WarningTimer;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredMenuRefreshRequest);
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredDifficultyMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Menu") FString LastStartError;
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void SelectEasy();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void SelectNormal();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void SelectInsane();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void CloseDifficulty();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void SelectDifficulty(uint8 Difficulty);
    void CompleteSelection();
    void BindNavigation(bool bBind);
    FTimerHandle SelectionTimer;
    bool bSelectionPending=false;
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredMenuBackgroundRequest,const FString&,MediaName,class UImage*,Image);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredVoiceSettings : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadWrite,Category="Recovered Audio") TObjectPtr<class UAudioComponent> AudioComponent;
    UFUNCTION(BlueprintCallable,Category="Recovered Audio") void StopAudioComponent();
};

// Recovered tab navigation; controls inside each tab are reconstructed separately.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredSettingsMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Styles") FButtonStyle ClickedStyle;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Styles") FButtonStyle UnclickedStyle;
    UPROPERTY(BlueprintAssignable,Category="Recovered Menu") FRecoveredMenuRefreshRequest OnMainMenuBackgroundRefreshRequested;
    UPROPERTY(BlueprintAssignable,Category="Recovered Menu") FRecoveredMenuBackgroundRequest OnBackgroundMediaRequested;
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void OpenVideoTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void OpenAudioTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void OpenTagsTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void OpenVoiceTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void OpenToysTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void CloseSettings();
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void ApplyPatronLocks();
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
private:
    void BindNavigation(bool bBind);
    void SelectTab(int32 Index,const TCHAR* ButtonName,bool bStopPreview);
    void StopVoicePreview();
    bool IsPatron() const;
};
