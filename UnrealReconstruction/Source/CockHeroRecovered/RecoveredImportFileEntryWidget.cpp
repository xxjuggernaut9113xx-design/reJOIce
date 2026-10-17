#include "RecoveredImportFileEntryWidget.h"

#include "RecoveredImportWidget.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"

void URecoveredImportFileEntryWidget::Configure(URecoveredImportWidget* InOwner, const FString& InFilePath, bool bInEnabled) {
    OwnerWidget = InOwner;
    EntryFilePath = InFilePath;
    bEntryEnabled = bInEnabled;
    BindControls(true);
    ApplyRecord();
}

void URecoveredImportFileEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindControls(true);
    ApplyRecord();
}

void URecoveredImportFileEntryWidget::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredImportFileEntryWidget::BindControls(bool bBind) {
    if (auto* Remove = Cast<UButton>(GetWidgetFromName(TEXT("RemoveButton")))) {
        if (bBind) {
            Remove->OnClicked.RemoveAll(this);
            Remove->OnHovered.RemoveAll(this);
            Remove->OnUnhovered.RemoveAll(this);
            Remove->OnClicked.AddUniqueDynamic(this, &URecoveredImportFileEntryWidget::OnRemoveClicked);
            Remove->OnHovered.AddUniqueDynamic(this, &URecoveredImportFileEntryWidget::OnRemoveHovered);
            Remove->OnUnhovered.AddUniqueDynamic(this, &URecoveredImportFileEntryWidget::OnRemoveUnhovered);
        } else {
            Remove->OnClicked.RemoveDynamic(this, &URecoveredImportFileEntryWidget::OnRemoveClicked);
            Remove->OnHovered.RemoveDynamic(this, &URecoveredImportFileEntryWidget::OnRemoveHovered);
            Remove->OnUnhovered.RemoveDynamic(this, &URecoveredImportFileEntryWidget::OnRemoveUnhovered);
        }
    }
    if (auto* Enabled = Cast<UCheckBox>(GetWidgetFromName(TEXT("EnableCheckBox")))) {
        if (bBind) {
            Enabled->OnCheckStateChanged.RemoveAll(this);
            Enabled->OnCheckStateChanged.AddUniqueDynamic(this, &URecoveredImportFileEntryWidget::OnEnabledChanged);
        } else {
            Enabled->OnCheckStateChanged.RemoveDynamic(this, &URecoveredImportFileEntryWidget::OnEnabledChanged);
        }
    }
}

void URecoveredImportFileEntryWidget::ApplyRecord() {
    if (auto* Path = Cast<UTextBlock>(GetWidgetFromName(TEXT("FilePathTextUMG")))) {
        Path->SetText(FText::FromString(EntryFilePath));
        Path->SetToolTipText(FText::FromString(EntryFilePath));
    }
    if (auto* Enabled = Cast<UCheckBox>(GetWidgetFromName(TEXT("EnableCheckBox")))) Enabled->SetIsChecked(bEntryEnabled);
}

void URecoveredImportFileEntryWidget::OnRemoveClicked() {
    if (OwnerWidget) OwnerWidget->RemoveMediaFile(EntryFilePath);
}

void URecoveredImportFileEntryWidget::OnRemoveHovered() {
    PlaySourceAnimation(TEXT("HoverRemove"));
}

void URecoveredImportFileEntryWidget::OnRemoveUnhovered() {
    PlaySourceAnimation(TEXT("UnHoverRemove"));
}

void URecoveredImportFileEntryWidget::OnEnabledChanged(bool bIsChecked) {
    bEntryEnabled = bIsChecked;
    if (OwnerWidget) OwnerWidget->SetMediaFileEnabled(EntryFilePath, bIsChecked);
}

void URecoveredImportFileEntryWidget::PlaySourceAnimation(FName Name) {
    const auto* Class = Cast<UWidgetBlueprintGeneratedClass>(GetClass());
    if (!Class) return;
    const FString RuntimeName = Name.ToString() + TEXT("_INST");
    for (UWidgetAnimation* Animation : Class->Animations) {
        if (Animation && Animation->GetName() == RuntimeName) {
            PlayAnimation(Animation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
            return;
        }
    }
}
