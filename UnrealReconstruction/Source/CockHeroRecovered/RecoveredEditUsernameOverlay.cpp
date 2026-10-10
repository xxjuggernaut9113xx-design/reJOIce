#include "RecoveredEditUsernameOverlay.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "RecoveredRules.h"
#include "Sound/SoundBase.h"

namespace {

URecoveredGameInstance* GetRecoveredUsernameGameInstance(const UUserWidget* Widget) {
    if (auto* Instance=Cast<URecoveredGameInstance>(Widget->GetGameInstance())) return Instance;
    return Widget->GetWorld() ? Cast<URecoveredGameInstance>(Widget->GetWorld()->GetGameInstance()) : nullptr;
}

}

void URecoveredEditUsernameOverlay::NativeConstruct() {
    Super::NativeConstruct();
    InitializeUsernameEditor();
}

void URecoveredEditUsernameOverlay::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredEditUsernameOverlay::InitializeUsernameEditor() {
    BindControls(true);
    if (auto* TextBox=Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_126")))) {
        const URecoveredGameInstance* Instance=GetRecoveredUsernameGameInstance(this);
        TextBox->SetText(Instance && Instance->CurrentSave
            ? Instance->CurrentSave->GetTextSetting(TEXT("Playercard_Name"),FText::GetEmpty())
            : FText::GetEmpty());
    }
}

void URecoveredEditUsernameOverlay::BindControls(bool bBind) {
    if (auto* TextBox=Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_126")))) {
        if (bBind) TextBox->OnTextChanged.AddUniqueDynamic(this,&URecoveredEditUsernameOverlay::ClampUsernameText);
        else TextBox->OnTextChanged.RemoveDynamic(this,&URecoveredEditUsernameOverlay::ClampUsernameText);
    }
    if (auto* Cancel=Cast<UButton>(GetWidgetFromName(TEXT("SubmitButton_1")))) {
        if (bBind) Cancel->OnClicked.AddUniqueDynamic(this,&URecoveredEditUsernameOverlay::CancelUsernameEdit);
        else Cancel->OnClicked.RemoveDynamic(this,&URecoveredEditUsernameOverlay::CancelUsernameEdit);
    }
    if (auto* Submit=Cast<UButton>(GetWidgetFromName(TEXT("SubmitButton")))) {
        if (bBind) Submit->OnClicked.AddUniqueDynamic(this,&URecoveredEditUsernameOverlay::SubmitUsernameEdit);
        else Submit->OnClicked.RemoveDynamic(this,&URecoveredEditUsernameOverlay::SubmitUsernameEdit);
    }
}

void URecoveredEditUsernameOverlay::ClampUsernameText(const FText& Value) {
    if (USoundBase* Keypress=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/keypress.keypress"))) {
        UGameplayStatics::PlaySound2D(this,Keypress,0.25f);
    }
    const FString Source=Value.ToString();
    if (Source.Len()<=14) return;
    if (auto* TextBox=Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_126")))) {
        TextBox->SetText(FText::FromString(Source.Left(14)));
    }
}

void URecoveredEditUsernameOverlay::CancelUsernameEdit() {
    RemoveFromParent();
}

void URecoveredEditUsernameOverlay::SubmitUsernameEdit() {
    bLastSaveSucceeded=false;
    if (auto* Instance=GetRecoveredUsernameGameInstance(this)) {
        if (Instance->CurrentSave) {
            FString Name;
            if (const auto* TextBox=Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_126")))) Name=TextBox->GetText().ToString().Left(14);
            bLastSaveSucceeded=Instance->CurrentSave->SetStringSetting(TEXT("Playercard_Name"),Name) && Instance->SaveRecoveredState();
        }
    }
    OnClosed.Broadcast();
    RemoveFromParent();
}
