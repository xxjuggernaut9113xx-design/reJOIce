#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredUnlockStoreWidget.generated.h"

class UButton;
class UHorizontalBox;
class UImage;
class UTextBlock;
class UTexture2D;
class UUniformGridPanel;
class UVerticalBox;

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPackSocialLinks {
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString OnlyFans;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Fansly;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Twitter;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Linktree;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString ManyVids;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Redgifs;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Discord;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Patreon;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString SubscribeStar;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Kofi;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPackInfo {
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString PackID;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString DisplayName;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString Author;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store", meta=(MultiLine="true")) FString Description;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString PreviewAssetPath;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString ChallengeName;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 UnlockCost=0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 TotalMediaCount=0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 ImageCount=0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 VideoCount=0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FRecoveredPackSocialLinks SocialLinks;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bPatreonExclusive=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bUnlocked=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bEnabled=false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecoveredPackEntryClicked, const FString&, PackID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredPackEntryUnhovered);

/** Native interaction recovery for the cooked CHPackEntryWidget tree. */
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredPackEntryWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable, Category="Recovered Store") FRecoveredPackEntryClicked OnPackClicked;
    UPROPERTY(BlueprintAssignable, Category="Recovered Store") FRecoveredPackEntryClicked OnPackHovered;
    UPROPERTY(BlueprintAssignable, Category="Recovered Store") FRecoveredPackEntryUnhovered OnPackUnhovered;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString PackID;
    // This source field is named bIsLocked even though the original caller assigns PackInfo.bUnlocked to it.
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bIsLocked=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bIsPatreonExclusive=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bIsPatron=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool bPackEnabled=false;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") TObjectPtr<UTexture2D> PreviewTexture;

    UFUNCTION(BlueprintCallable, Category="Recovered Store") void ConfigureEntry(
        const FString& InPackID,
        UTexture2D* InPreviewTexture,
        bool bInUnlocked,
        bool bInPatreonExclusive,
        bool bInPatron,
        bool bInEnabled);
    UFUNCTION(BlueprintPure, Category="Recovered Store") ESlateVisibility GetLockIconVisibility() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") ESlateVisibility GetPatreonLockIconVisibility() const;

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
    void ApplyTooltip();
    void PlaySourceSound(const TCHAR* AssetPath,float Volume=1.0f,float Pitch=1.0f) const;

    UPROPERTY(Transient) TObjectPtr<UButton> SourceButton;
    UPROPERTY(Transient) TObjectPtr<UImage> SourceLockIcon;
    UPROPERTY(Transient) TObjectPtr<UImage> SourcePatreonLockIcon;
    UPROPERTY(Transient) TObjectPtr<UImage> SourcePreviewImage;
    UPROPERTY(Transient) TObjectPtr<URecoveredTooltip> EntryTooltip;
};

/** Native interaction recovery for the cooked creator-link button tree. */
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredUnlockStoreSocialIconWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString ButtonURL;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") uint8 Platform=0;

    UFUNCTION(BlueprintCallable, Category="Recovered Store") void SetURLAndIcon(const FString& InURL,uint8 InPlatform);
    UFUNCTION(BlueprintPure, Category="Recovered Store") FString GetCreatorURL() const { return ButtonURL; }
    UFUNCTION(BlueprintPure, Category="Recovered Store") uint8 GetSocialPlatform() const { return Platform; }

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void HandleClicked();
    UFUNCTION() void HandleHovered();
    UFUNCTION() void HandleUnhovered();
    void BindSourceTree();
    void BindSourceEvents(bool bBind);
    void ApplySourceStyle();
    void ApplyTooltip();

    UPROPERTY(Transient) TObjectPtr<UButton> SourceSocialButton;
    UPROPERTY(Transient) TObjectPtr<URecoveredTooltip> SocialTooltip;
};

/** Native event-graph reconstruction for the cooked UnlockStoreWidget tree. */
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredUnlockStoreWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") TArray<FRecoveredPackInfo> AvailablePacks;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FRecoveredPackInfo SelectedPackInfo;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString LastClickedPack;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") double LastClickTime=-1.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") int32 CurrentPackIndex=0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Store") int32 PacksPerFrame=2;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") bool IsInit=true;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered Store") FString LastStoreAction;

    UFUNCTION(BlueprintCallable, Category="Recovered Store") void ClearAndRefreshPacks();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void CreatePackBatch();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void OnEntryClicked(const FString& PackID);
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void OnEntryHovered(const FString& PackID);
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void OnEntryUnhovered();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void UpdateButtonDisplay(const FString& PackID,bool bPatreonExclusive=false);
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void UpdateDetails(const FString& PackID);
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void UpdateInfoPanel(const FString& PackID);
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void EnableAllPacks();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void DisableAllPacks();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void HandleInteractionClicked();
    UFUNCTION(BlueprintCallable, Category="Recovered Store") void CloseUnlockStore();
    UFUNCTION(BlueprintPure, Category="Recovered Store") bool IsPackUnlocked(const FString& PackID) const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") bool IsPackEnabled(const FString& PackID) const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetUnlockPoints() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") FString GetInteractionLabel() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetCreatedPackEntryCount() const;
    UFUNCTION(BlueprintPure, Category="Recovered Store") int32 GetCreatedSocialIconCount() const;
    UFUNCTION(BlueprintCallable, Category="Recovered Store") bool LoadRecoveredPackCatalog();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void HandleBackClicked();
    UFUNCTION() void HandleBackHovered();
    UFUNCTION() void HandleBackUnhovered();
    UFUNCTION() void HandleInteractionHovered();
    UFUNCTION() void HandleInteractionUnhovered();
    void BindSourceTree();
    void BindSourceEvents(bool bBind);
    void StartPackBatchTimer();
    void StopPackBatchTimer();
    void CreatePackEntry(const FRecoveredPackInfo& Pack,int32 GridIndex,bool bAssignAccessState);
    void ApplyEntryStates();
    bool SelectPack(const FString& PackID);
    const FRecoveredPackInfo* FindPack(const FString& PackID) const;
    FRecoveredPackInfo* FindMutablePack(const FString& PackID);
    bool IsPatron() const;
    bool IsChallengeReward(const FRecoveredPackInfo& Pack) const;
    bool SetPackUnlocked(const FString& PackID,bool bUnlocked);
    bool SetPackEnabled(const FString& PackID,bool bEnabled);
    bool TryUnlockSelectedPack();
    void CreateSocialIcons(const FRecoveredPackSocialLinks& Links);
    void SetUnlockPoints(int32 Points);
    void UpdateUnlockPointsText();
    void PersistStoreState();
    void PlaySourceSound(const TCHAR* AssetPath,float Volume=1.0f,float Pitch=1.0f) const;

    UPROPERTY(Transient) TObjectPtr<UButton> SourceBackButton;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceEnablePacksButton;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceDisablePacksButton;
    UPROPERTY(Transient) TObjectPtr<UButton> SourceInteractionButton;
    UPROPERTY(Transient) TObjectPtr<UUniformGridPanel> SourcePackUniformGrid;
    UPROPERTY(Transient) TObjectPtr<UVerticalBox> SourceEnableDisablePacksBox;
    UPROPERTY(Transient) TObjectPtr<UHorizontalBox> SourceSocialIconsHoriBox;
    UPROPERTY(Transient) TObjectPtr<UImage> SourceBackgroundImage;
    UPROPERTY(Transient) TObjectPtr<UImage> SourceImagePreview;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourcePackNameText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceAuthorNameText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceDescriptionText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceTotalCardsText;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> SourceInteractionButtonTextBlock;
    UPROPERTY(Transient) TObjectPtr<UTextBlock> UnlockPointsText;
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredPackEntryWidget>> PackEntries;
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredUnlockStoreSocialIconWidget>> SocialIconEntries;
    FTimerHandle PackBatchTimerHandle;
};
