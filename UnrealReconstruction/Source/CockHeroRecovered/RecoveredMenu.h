#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateTypes.h"
#include "RecoveredMenu.generated.h"

class URecoveredSaveGame;
class UAudioComponent;
class UButton;
class UComboBoxString;
class UScrollBox;
class USoundBase;
class UTextBlock;
class UWidget;

namespace RecoveredMenu {
COCKHERORECOVERED_API bool NeedsInitialCalibration(const URecoveredSaveGame* Save);
}

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
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void ChangeCheatCodeRedeemVisibility(UWidget* CheatCodeTextRedeemText);
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
    UFUNCTION(BlueprintCallable,Category="Recovered Menu") void ApplyPatronLocks();
    UPROPERTY(Transient, BlueprintReadOnly, Category="Recovered Menu") FString LastNavigationError;
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenDifficulty();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenChallenges();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenStatsDebug();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenSettings();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenUnlockStore();
    UFUNCTION(BlueprintCallable, Category="Recovered Menu") void OpenImport();
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

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredVoicePackDefinition {
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") FText DisplayName;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice", meta=(MultiLine="true")) FText Description;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TArray<FText> Tags;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") uint8 VoicePackEnum=0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") FString Sample1AssetPath;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") FString Sample2AssetPath;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") FString Sample3AssetPath;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") FString SelectionLineAssetPath;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> Sample1;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> Sample2;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> Sample3;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> SelectionLine;
};

class URecoveredVoicePackEntryWidget;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredVoicePackEntryClicked,const FText&,DisplayName,URecoveredVoicePackEntryWidget*,Widget);

/** Native event-graph reconstruction for the cooked VoicePackEntryWidget tree. */
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredVoicePackEntryWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Recovered Voice") FRecoveredVoicePackEntryClicked OnClicked;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") FText DisplayNameID;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice", meta=(MultiLine="true")) FText Description;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TArray<FText> Tags;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") uint8 VoicePackEnum=0;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> SampleLine1;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> SampleLine2;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> SampleLine3;
    UPROPERTY(Transient, VisibleAnywhere, BlueprintReadOnly, Category="Recovered Voice") TObjectPtr<USoundBase> SelectionLine;

    UFUNCTION(BlueprintCallable, Category="Recovered Voice") void PopulateVoicePackEntry(
        const FText& InDisplayName,
        const FText& InDescription,
        USoundBase* InSample1,
        USoundBase* InSample2,
        USoundBase* InSample3,
        const TArray<FText>& InTags,
        uint8 InVoicePackEnum,
        USoundBase* InSelectionLine);

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void HandleClicked();
    UFUNCTION() void HandleHovered();
    UFUNCTION() void HandleUnhovered();
    void BindSourceTree();
    void BindSourceEvents(bool bBind);
    void ApplyPresentation();

    UPROPERTY(Transient) TObjectPtr<UButton> SourceClickPackButton;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceDisplayName;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredVoiceSettings : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadWrite,Category="Recovered Audio") TObjectPtr<UAudioComponent> AudioComponent;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") FText EquippedPack;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") FText SelectedPack;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") uint8 VoicePackEnum=0;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") bool bVoicelinesAllowedToTrigger=false;
    UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") TObjectPtr<URecoveredVoicePackEntryWidget> SelectedEntryWidget;
    UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") TObjectPtr<USoundBase> Sample1;
    UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") TObjectPtr<USoundBase> Sample2;
    UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") TObjectPtr<USoundBase> Sample3;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") TArray<FRecoveredVoicePackDefinition> VoicePacks;
    UPROPERTY(Transient,VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") TArray<TObjectPtr<URecoveredVoicePackEntryWidget>> PackEntries;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Voice") FString LastVoiceError;

    UFUNCTION(BlueprintCallable,Category="Recovered Audio") void StopAudioComponent();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void InitDefaultsFromSaveGame();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void PopulateVoicepacks();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void PackClicked(const FText& DisplayName,URecoveredVoicePackEntryWidget* Widget);
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void EquipSelectedPack();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void PlaySample1();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void PlaySample2();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void PlaySample3();
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") void SetSmallPenisHumiliationEnabled(bool bEnabled);
    UFUNCTION(BlueprintCallable,Category="Recovered Voice") bool LoadRecoveredVoicePackCatalog();
    UFUNCTION(BlueprintPure,Category="Recovered Voice") int32 GetVoicePackEntryCount() const { return PackEntries.Num(); }

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void HandleVoicePackClicked(const FText& DisplayName,URecoveredVoicePackEntryWidget* Widget);
    UFUNCTION() void HandleEquipClicked();
    UFUNCTION() void HandleEquipHovered();
    UFUNCTION() void HandleEquipUnhovered();
    UFUNCTION() void HandleSample1Clicked();
    UFUNCTION() void HandleSample2Clicked();
    UFUNCTION() void HandleSample3Clicked();
    UFUNCTION() void HandleSample1Hovered();
    UFUNCTION() void HandleSample1Unhovered();
    UFUNCTION() void HandleSample2Hovered();
    UFUNCTION() void HandleSample2Unhovered();
    UFUNCTION() void HandleSample3Hovered();
    UFUNCTION() void HandleSample3Unhovered();
    UFUNCTION() void HandleSPHSelection(FString SelectedItem,ESelectInfo::Type SelectionType);
    void BindSourceTree();
    void BindSourceEvents(bool bBind);
    void SelectEquippedPack();
    void ApplySelectedPackPresentation();
    void PlaySample(USoundBase* Sound,FName AnimationName);
    void PlayVoicePreview(USoundBase* Sound);
    void SetTextBlock(FName Name,const FText& Value) const;

    UPROPERTY(Transient) TObjectPtr<UScrollBox> SourcePacksScrollbox;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceEquipButton;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceSample1Button;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceSample2Button;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceSample3Button;
    UPROPERTY(Transient) TObjectPtr<UComboBoxString> SourceHealthBarAndTextComboBox;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceEquipButtonText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourcePackTitle;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourcePackDescription;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceTag1;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceTag2;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceTag3;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceTag4;
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
