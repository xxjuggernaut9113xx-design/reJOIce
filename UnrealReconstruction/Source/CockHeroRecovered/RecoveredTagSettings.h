#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredTagSettings.generated.h"

class URecoveredTagSettingsMenu;

// Forwarder: UCheckBox dynamic delegates don't pass the sender, so each
// checkbox gets one of these holding its tag.
UCLASS()
class COCKHERORECOVERED_API URecoveredTagToggleForward : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredTagSettingsMenu> Owner;
    UPROPERTY() FString Tag;
    UPROPERTY(Transient) TObjectPtr<class UCheckBox> Check;
    UFUNCTION() void ForwardToggle(bool bChecked);
};

// Native TagSettingsMenu: the excluded-tags filter list. Tags are toggled via
// TagFilterEntry widgets; the exclusion list persists as the "ExcludedTags"
// string array the session media loader already reads.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredTagSettingsMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Tags") void InitDefaultsFromSaveGame();
    UFUNCTION(BlueprintCallable, Category="Recovered Tags") void SetTagExcluded(const FString& Tag, bool bExcluded);
    UFUNCTION(BlueprintPure, Category="Recovered Tags") bool IsTagExcluded(const FString& Tag) const;
    UFUNCTION(BlueprintCallable, Category="Recovered Tags") void ClearExcludedTags();
    // Builds tag entry widgets dynamically from the loaded media decks.
    // Entries are created under TagListContainer and wired to SetTagExcluded.
    UFUNCTION(BlueprintCallable, Category="Recovered Tags") void BuildTagEntries();
    UFUNCTION(BlueprintCallable, Category="Recovered Tags") TArray<FString> CollectAvailableTags() const;
protected:
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredTagToggleForward>> TagToggleForwarders;
    virtual void NativeConstruct() override;
};
