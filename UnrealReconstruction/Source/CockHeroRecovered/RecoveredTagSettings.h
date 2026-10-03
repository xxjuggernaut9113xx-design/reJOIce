#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredTagSettings.generated.h"

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
protected:
    virtual void NativeConstruct() override;
};
