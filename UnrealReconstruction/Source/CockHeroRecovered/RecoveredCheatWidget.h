#pragma once
#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredCheatWidget.generated.h"

// Cheat code entry: validates codes and applies effects.
UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredCheatWidget : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Recovered Cheats") bool SubmitCheatCode(const FString& Code);
protected:
    virtual void NativeConstruct() override;
    void BindControls(bool bBind);
    UFUNCTION() void OnSubmitClicked();
};
