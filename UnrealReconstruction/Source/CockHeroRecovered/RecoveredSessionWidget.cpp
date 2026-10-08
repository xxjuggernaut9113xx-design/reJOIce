#include "RecoveredSessionWidget.h"
#include "RecoveredRules.h"
#include "RecoveredTabbedInventoryWidget.h"
#include "RecoveredPG2TabbedInventoryWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Engine/Texture2D.h"
#include "MediaTexture.h"
#include "Input/Reply.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

void URecoveredSessionWidget::BindSession(bool bBind) {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("DrawButtonTextButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::DrawCard);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::DrawCard);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResumeButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::ResumeSession);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::ResumeSession);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SettingsMenuButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::OpenSessionSettings);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::OpenSessionSettings);
    }
    // Pause-menu quit and return-to-menu buttons (audit items 126-127).
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("QuitSessionButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::QuitSession);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::QuitSession);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ReturnToMenuButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::QuitSession);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::QuitSession);
    }
    // Favorites toggle for the current media (audit item 94).
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("FavoriteButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::ToggleFavorite);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::ToggleFavorite);
    }
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager && Manager->MediaPlayback) {
        if(bBind) Manager->MediaPlayback->OnMediaReady.AddUniqueDynamic(this,&URecoveredSessionWidget::DisplayMedia);
        else Manager->MediaPlayback->OnMediaReady.RemoveDynamic(this,&URecoveredSessionWidget::DisplayMedia);
    }
}
void URecoveredSessionWidget::NativeConstruct() {
    Super::NativeConstruct(); SetIsFocusable(true); BindSession(true);
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager && Manager->MediaPlayback && Manager->MediaPlayback->CurrentTexture) DisplayMedia(Manager->MediaPlayback->CurrentTexture);
}
void URecoveredSessionWidget::NativeDestruct() { BindSession(false); Super::NativeDestruct(); }
void URecoveredSessionWidget::DisplayMedia(UTexture* Texture) {
    auto* Image=Cast<UImage>(GetWidgetFromName(TEXT("MainImage")));
    if (!Image || !Texture) return;
    if (auto* Still=Cast<UTexture2D>(Texture)) { Image->SetBrushFromTexture(Still,false); return; }
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Cast<UMediaTexture>(Texture) && Manager && Manager->MediaPlayback) {
        if (auto* Material=Manager->MediaPlayback->GetVideoDisplayMaterial()) Image->SetBrushFromMaterial(Material);
    }
}
void URecoveredSessionWidget::ResumeSession() {
    if (auto* Border=GetWidgetFromName(TEXT("PauseMenuMasterBorder"))) Border->SetVisibility(ESlateVisibility::Hidden);
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return;
    if (Manager->BeatTimeline) Manager->BeatTimeline->ResumeSequence();
    if (Manager->MediaPlayback) Manager->MediaPlayback->SetPaused(false);
    // Reset the idle timer on resume; clear any pause-state flags.
    Manager->ResetIdleTimer();
    Manager->OnSessionAction.Broadcast(TEXT("SessionResumed"));
}

void URecoveredSessionWidget::PauseSession() {
    if (auto* Border=Cast<UBorder>(GetWidgetFromName(TEXT("PauseMenuMasterBorder")))) {
        Border->SetVisibility(ESlateVisibility::Visible);
    }
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return;
    if (Manager->BeatTimeline) Manager->BeatTimeline->PauseSequence();
    if (Manager->MediaPlayback) Manager->MediaPlayback->SetPaused(true);
    Manager->ClearIdleTimer();
    Manager->OnSessionAction.Broadcast(TEXT("SessionPaused"));
}
void URecoveredSessionWidget::OpenSessionSettings() {
    if (!GetWorld()) return;
    UClass* Class=LoadClass<UUserWidget>(nullptr,TEXT("/Game/Recovery/UI/SettingsMenuWidget.SettingsMenuWidget_C"));
    if (Class) if (auto* Settings=CreateWidget<UUserWidget>(GetWorld(),Class)) Settings->AddToViewport(0);
}
void URecoveredSessionWidget::DrawCard() {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    // Original handler blocks skipping a succubus before testing CanDraw.
    if (!Manager || Manager->BeatContext.CardType==3 || !Manager->PlayerVariables.bCanDraw) return;
    Manager->RequestNextRecoveredCard(true);
}

void URecoveredSessionWidget::SwitchInventoryTabs() {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return;
    if (Manager->CurrentInventoryTab==0) {
        Manager->CurrentInventoryTab=1;
        if (auto* Page=Cast<URecoveredMenuWidget>(GetWidgetFromName(TEXT("PG2TabbedInventory_Widget")))) Page->PlayRecoveredAnimation(TEXT("SwitchInventoryTabAnimation"));
    } else if (Manager->CurrentInventoryTab==1) {
        Manager->CurrentInventoryTab=0;
        if (auto* Page=Cast<URecoveredMenuWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Page->PlayRecoveredAnimation(TEXT("SwitchInventoryTabAnimation"));
    }
}
void URecoveredSessionWidget::NativeTick(const FGeometry& Geometry,float DeltaSeconds) {
    Super::NativeTick(Geometry,DeltaSeconds);
    RefreshSessionDisplays(GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr);
}
void URecoveredSessionWidget::RefreshSessionDisplays(ARecoveredGlobalManager* Manager) {
    if (!Manager) return;
    auto Text=[this](FName Name,const FText& Value) { if (auto* Widget=Cast<UTextBlock>(GetWidgetFromName(Name))) Widget->SetText(Value); };
    auto Percent=[this](FName Name,double Value) { if (auto* Widget=Cast<UProgressBar>(GetWidgetFromName(Name))) Widget->SetPercent(static_cast<float>(Value)); };
    FNumberFormattingOptions IntegerFormat;
    IntegerFormat.UseGrouping=true;IntegerFormat.MinimumIntegralDigits=1;IntegerFormat.MaximumIntegralDigits=324;
    Text(TEXT("StrokeCounter"),FText::AsNumber(FMath::Clamp(Manager->BeatTimeline ? Manager->BeatTimeline->GetBeatsRemaining() : 0,0,999),&IntegerFormat));
    Text(TEXT("CoinCounterText"),FText::AsNumber(Manager->PlayerVariables.PlayerCoins,&IntegerFormat));
    Text(TEXT("ComboText"),FText::FromString(FString::FromInt(Manager->PlayerVariables.CurrentComboCount)+TEXT("X COMBO")));
    Text(TEXT("TextBlock_1"),FText::FromString(FString::Printf(TEXT("AutoDraw(%s)"),Manager->IsAutoDrawEnabled ? TEXT("True") : TEXT("False"))));
    const int32 Seconds=Manager->PlayerVariables.SessionLength;
    FNumberFormattingOptions TimeFormat=IntegerFormat;TimeFormat.MinimumIntegralDigits=2;TimeFormat.MaximumIntegralDigits=2;
    const FString Duration=FText::AsNumber(Seconds/3600,&TimeFormat).ToString()+TEXT(":")+FText::AsNumber((Seconds%3600)/60,&TimeFormat).ToString()+TEXT(":")+FText::AsNumber(Seconds%60,&TimeFormat).ToString();
    Text(TEXT("SessionDurationText"),FText::FromString(Duration));
    Percent(TEXT("HeatMeterBar"),Manager->HeatLevel/100.0);
    Percent(TEXT("CumMeterProgressBar"),Manager->CumMeterPercentage);
    Percent(TEXT("LootMeterProgressBar"),Manager->LootBarPercentage);
}

FReply URecoveredSessionWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) {
    const FKey Key = InKeyEvent.GetKey();
    if (Key == EKeys::Escape) {
        // Toggle pause menu.
        if (auto* Border = Cast<UBorder>(GetWidgetFromName(TEXT("PauseMenuMasterBorder")))) {
            const bool bHidden = Border->GetVisibility() == ESlateVisibility::Hidden;
            if (bHidden) PauseSession(); else ResumeSession();
            return FReply::Handled();
        }
    } else if (Key == EKeys::SpaceBar) {
        DrawCard();
        return FReply::Handled();
    } else if (Key == EKeys::Tab || Key == EKeys::Q) {
        SwitchInventoryTabs();
        return FReply::Handled();
    } else if (Key == EKeys::Three) {
        auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
        if (Manager && Manager->CurrentInventoryTab==0) {
            if (auto* Inventory=Cast<URecoveredTabbedInventoryWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Inventory->TabbedInventoryEdgeTrigger();
        } else if (Manager && Manager->CurrentInventoryTab==1) {
            if (auto* Inventory=Cast<URecoveredPG2TabbedInventoryWidget>(GetWidgetFromName(TEXT("PG2TabbedInventory_Widget")))) Inventory->TabbedInventoryResupplyTrigger();
            Manager->PlayDialogueLine(TEXT("SpecialEvent_12"));
        }
        return FReply::Handled();
    } else if (Key == EKeys::F) {
        ToggleFavorite();
        return FReply::Handled();
    } else if (Key == EKeys::P) {
        if (auto* Border=GetWidgetFromName(TEXT("PauseMenuMasterBorder"))) {
            if (Border->IsVisible()) ResumeSession(); else PauseSession();
            return FReply::Handled();
        }
    }

    return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void URecoveredSessionWidget::QuitSession() {
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager) Manager->ReturnToMainMenu();
}

void URecoveredSessionWidget::ToggleFavorite() {
    auto* Manager = GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Manager || !Instance || !Instance->CurrentSave) return;
    // Toggle the current media path in the favorites list.
    const FString CurrentMedia = Manager->SelectedRandomCard.FullPath;
    if (CurrentMedia.IsEmpty()) return;
    TArray<FString> Favorites = Instance->CurrentSave->GetStringArraySetting(TEXT("FavoriteMedia"));
    if (Favorites.Contains(CurrentMedia)) Favorites.Remove(CurrentMedia);
    else Favorites.Add(CurrentMedia);
    if (Instance->CurrentSave->SetStringArraySetting(TEXT("FavoriteMedia"), Favorites)) {
        Instance->SaveRecoveredState();
    }
}
