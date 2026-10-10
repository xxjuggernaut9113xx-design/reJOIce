#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "RecoveredEditUsernameOverlay.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRecoveredUsernameOverlayClosed);

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredEditUsernameOverlay : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintAssignable,Category="Recovered Username") FRecoveredUsernameOverlayClosed OnClosed;
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Recovered Username") bool bLastSaveSucceeded=false;

    UFUNCTION(BlueprintCallable,Category="Recovered Username") void InitializeUsernameEditor();
    UFUNCTION(BlueprintCallable,Category="Recovered Username") void CancelUsernameEdit();
    UFUNCTION(BlueprintCallable,Category="Recovered Username") void SubmitUsernameEdit();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void ClampUsernameText(const FText& Value);
    void BindControls(bool bBind);
};
