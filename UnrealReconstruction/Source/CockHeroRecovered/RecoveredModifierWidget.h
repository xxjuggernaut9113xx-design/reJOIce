#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredModifierWidget.generated.h"

class URecoveredModifierWidget;
struct FRecoveredModifierRow;

/** Carries the data-table row name for each generated modifier-card button. */
UCLASS()
class COCKHERORECOVERED_API URecoveredModifierToggleForward : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredModifierWidget> Owner;
    UPROPERTY() FName ModifierID;
    UFUNCTION() void Toggle();
    UFUNCTION() void ToggleSourceEntry(const FText& ModifierTitle,class UUserWidget* Entry);
};

/** Retains native conflict-overlay callbacks while its UMG instance is open. */
UCLASS()
class COCKHERORECOVERED_API URecoveredModifierConflictForward : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredModifierWidget> Owner;
    UFUNCTION() void Confirm();
    UFUNCTION() void Cancel();
};

// Modifier list UI: repopulates the recovered UniformGridPanel_94 with the
// original card asset, confirms explicit conflict removal, and persists the
// enabled set.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredModifierWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(Transient,BlueprintReadOnly,Category="Recovered Modifiers") TObjectPtr<class URecoveredGameInstance> RecoveredInstanceOverride;
    UFUNCTION(BlueprintCallable,Category="Recovered Modifiers") void SetRecoveredModifierGameInstance(class URecoveredGameInstance* Instance);
    UFUNCTION(BlueprintPure,Category="Recovered Modifiers") class URecoveredGameInstance* GetRecoveredModifierGameInstance() const;
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") void RefreshModifierList();
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") bool ToggleModifier(FName ModifierID);
    UFUNCTION() void ToggleModifierFromSource(const FText& ModifierTitle,class UUserWidget* Entry);
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") bool ConfirmModifierConflicts();
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") void CancelModifierConflicts();
    UFUNCTION(BlueprintPure, Category="Recovered Modifiers") bool HasPendingModifierConflicts() const;
protected:
    virtual void NativeConstruct() override;
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredModifierToggleForward>> ToggleForwarders;
    UPROPERTY(Transient) TMap<FName,TObjectPtr<class URecoveredModifierCardEntryWidget>> RecoveredModifierEntries;
    UPROPERTY(Transient) TObjectPtr<class UUserWidget> ConflictOverlay;
    UPROPERTY(Transient) TObjectPtr<URecoveredModifierConflictForward> ConflictForwarder;
    UPROPERTY(Transient) FName PendingModifierID;
    UPROPERTY(Transient) TArray<FName> PendingConflictingModifiers;
private:
    bool ToggleModifierInternal(FName ModifierID,class URecoveredModifierCardEntryWidget* SourceEntry);
    class URecoveredModifierCardEntryWidget* FindRecoveredModifierEntry(FName ModifierID) const;
    void PersistModifierState();
    void PersistAndRefreshModifierState();
    void PlaySourceToggleSound();
    void ShowModifierConflictOverlay(const FRecoveredModifierRow& Modifier, const TArray<FName>& Conflicts);
    void CloseModifierConflictOverlay();
};
