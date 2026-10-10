#pragma once

#include "CoreMinimal.h"
#include "RecoveredMenu.h"
#include "Styling/SlateTypes.h"
#include "RecoveredChallengesMenu.generated.h"

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredChallengesMenu : public URecoveredMenuWidget {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Styles") FButtonStyle ClickedStyle;
    UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Recovered Styles") FButtonStyle UnclickedStyle;

    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void InitializeRecoveredChallengesMenu();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void OpenChallengesTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void OpenPlayerCardsTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void OpenStatsTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void OpenModifiersTab();
    UFUNCTION(BlueprintCallable,Category="Recovered Challenges") void CloseChallengesMenu();

protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;

private:
    UFUNCTION() void PlayBackButtonHover();
    UFUNCTION() void PlayBackButtonUnhover();
    void BindNavigation(bool bBind);
    void RestoreSourceStyles();
    void SelectTab(int32 Index,const TCHAR* ActiveButton);
};
