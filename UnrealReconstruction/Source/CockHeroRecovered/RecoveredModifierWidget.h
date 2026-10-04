#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredModifierWidget.generated.h"

// Modifier list UI: shows available modifiers, toggle enable/disable,
// persists selection.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredModifierWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") void RefreshModifierList();
    UFUNCTION(BlueprintCallable, Category="Recovered Modifiers") bool ToggleModifier(FName ModifierID);
protected:
    virtual void NativeConstruct() override;
};
