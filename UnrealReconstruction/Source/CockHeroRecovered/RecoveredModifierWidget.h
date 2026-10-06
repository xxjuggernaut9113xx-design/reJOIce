#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredModifierWidget.generated.h"

class URecoveredModifierWidget;

/** Carries the data-table row name for each generated modifier-card button. */
UCLASS()
class COCKHERORECOVERED_API URecoveredModifierToggleForward : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY() TObjectPtr<URecoveredModifierWidget> Owner;
    UPROPERTY() FName ModifierID;
    UFUNCTION() void Toggle();
};

// Modifier list UI: repopulates the recovered UniformGridPanel_94 with the
// original card asset, toggles selections, removes explicit conflicts, and
// persists the enabled set.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredModifierWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") void RefreshModifierList();
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") bool ToggleModifier(FName ModifierID);
protected:
    virtual void NativeConstruct() override;
    UPROPERTY(Transient) TArray<TObjectPtr<URecoveredModifierToggleForward>> ToggleForwarders;
};
