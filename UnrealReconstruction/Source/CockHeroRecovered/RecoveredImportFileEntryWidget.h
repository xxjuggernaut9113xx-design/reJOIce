#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RecoveredImportFileEntryWidget.generated.h"

class URecoveredImportWidget;

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredImportFileEntryWidget : public UUserWidget {
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Recovered Import")
    void Configure(URecoveredImportWidget* InOwner, const FString& InFilePath, bool bInEnabled);

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    void BindControls(bool bBind);
    void ApplyRecord();
    void PlaySourceAnimation(FName Name);

    UFUNCTION()
    void OnRemoveClicked();

    UFUNCTION()
    void OnRemoveHovered();

    UFUNCTION()
    void OnRemoveUnhovered();

    UFUNCTION()
    void OnEnabledChanged(bool bIsChecked);

    UPROPERTY(Transient)
    TObjectPtr<URecoveredImportWidget> OwnerWidget;

    UPROPERTY(Transient)
    FString EntryFilePath;

    UPROPERTY(Transient)
    bool bEntryEnabled = true;
};
