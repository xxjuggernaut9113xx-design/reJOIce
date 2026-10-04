#include "RecoveredCheatWidget.h"
#include "RecoveredRules.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void URecoveredCheatWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
}

void URecoveredCheatWidget::BindControls(bool bBind) {
    if (auto* B = Cast<UButton>(GetWidgetFromName(TEXT("SubmitCheatButton")))) {
        if (bBind) B->OnClicked.AddUniqueDynamic(this, &URecoveredCheatWidget::OnSubmitClicked);
        else B->OnClicked.RemoveDynamic(this, &URecoveredCheatWidget::OnSubmitClicked);
    }
}

bool URecoveredCheatWidget::SubmitCheatCode(const FString& Code) {
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return false;
    const FString Upper = Code.ToUpper().TrimStartAndEnd();
    bool bValid = false;
    if (Upper == TEXT("MORECOINS")) {
        Manager->GrantPlayerCoins(1000);
        bValid = true;
    } else if (Upper == TEXT("MAXHEAT")) {
        Manager->AddHeat(100.0);
        bValid = true;
    } else if (Upper == TEXT("NOHEAT")) {
        Manager->AddHeat(-100.0);
        bValid = true;
    } else if (Upper == TEXT("GODMODE")) {
        Manager->SuccubusShields = 99;
        bValid = true;
    }
    if (auto* Feedback = Cast<UTextBlock>(GetWidgetFromName(TEXT("CheatFeedbackText")))) {
        Feedback->SetText(FText::FromString(bValid ? TEXT("Cheat applied.") : TEXT("Invalid code.")));
    }
    return bValid;
}

void URecoveredCheatWidget::OnSubmitClicked() {
    if (auto* Box = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("CheatCodeBox")))) {
        SubmitCheatCode(Box->GetText().ToString());
    }
}
