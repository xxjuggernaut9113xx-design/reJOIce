#include "RecoveredSessionWidget.h"
#include "RecoveredRules.h"
#include "RecoveredEdgeManager.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredTabbedInventoryWidget.h"
#include "RecoveredPG2TabbedInventoryWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
#include "Components/ScaleBox.h"
#include "Engine/Texture2D.h"
#include "MediaTexture.h"
#include "Input/Reply.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Sound/SoundBase.h"
#include "GameFramework/PlayerController.h"

namespace {
USoundBase* GetRecoveredInventorySwitchSound() {
    static TWeakObjectPtr<USoundBase> Sound;
    if (!Sound.IsValid()) Sound=LoadObject<USoundBase>(nullptr,TEXT("/Game/Recovery/Resources/Audio/swapitem.swapitem"));
    return Sound.Get();
}

void PlayRecoveredInventorySwitchSound(UObject* WorldContextObject) {
    if (!WorldContextObject || !WorldContextObject->GetWorld()) return;
    if (USoundBase* Sound=GetRecoveredInventorySwitchSound()) UGameplayStatics::PlaySound2D(WorldContextObject,Sound,0.25f,0.7f,0.0f,nullptr,nullptr,true);
}

USoundBase* GetRecoveredSettingsMenuSound() {
    static TWeakObjectPtr<USoundBase> Sound;
    if (!Sound.IsValid()) Sound=LoadObject<USoundBase>(nullptr,TEXT("/Engine/VREditor/Sounds/VR_ungrab.VR_ungrab"));
    return Sound.Get();
}

void PlayRecoveredSettingsMenuSound(UObject* WorldContextObject,float Pitch) {
    if (!WorldContextObject || !WorldContextObject->GetWorld()) return;
    if (USoundBase* Sound=GetRecoveredSettingsMenuSound()) UGameplayStatics::PlaySound2D(WorldContextObject,Sound,0.2f,Pitch,0.0f,nullptr,nullptr,true);
}
}

void URecoveredSessionWidget::BindSession(bool bBind) {
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("DrawButtonTextButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::DrawCard);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::DrawCard);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("ResumeButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::ToggleRecoveredSettingsMenu);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::ToggleRecoveredSettingsMenu);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("SettingsMenuButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::ToggleRecoveredSettingsMenu);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::ToggleRecoveredSettingsMenu);
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
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("CumTextButton_1")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::RequestRecoveredCumMediaFromButton);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::RequestRecoveredCumMediaFromButton);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("TauntButton")))) {
        if(bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredSessionWidget::RequestRecoveredTaunt);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredSessionWidget::RequestRecoveredTaunt);
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
    if (Manager && Manager->MediaPlayback) Manager->MediaPlayback->SetScaleBoxReference(Cast<UScaleBox>(GetWidgetFromName(TEXT("ScaleBox_416"))));
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
    SetRecoveredSettingsMenuVisible(false);
    PlayRecoveredSettingsMenuSound(this,1.0f);
    ShowRecoveredSettingsCursor();
}

void URecoveredSessionWidget::PauseSession() {
    SetRecoveredSettingsMenuVisible(true);
    PlayRecoveredSettingsMenuSound(this,4.0f);
    ShowRecoveredSettingsCursor();
}

void URecoveredSessionWidget::ToggleRecoveredSettingsMenu() {
    const auto* Border=Cast<UBorder>(GetWidgetFromName(TEXT("PauseMenuMasterBorder")));
    if (Border && Border->GetVisibility()==ESlateVisibility::Visible) ResumeSession();
    else PauseSession();
}

void URecoveredSessionWidget::SetRecoveredSettingsMenuVisible(bool bVisible) {
    if (auto* Border=Cast<UBorder>(GetWidgetFromName(TEXT("PauseMenuMasterBorder")))) {
        const ESlateVisibility TargetVisibility=bVisible ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
        Border->SetVisibility(TargetVisibility);
        if (UWidget* Content=Border->GetContent()) Content->SetVisibility(TargetVisibility);
    }
}

void URecoveredSessionWidget::ShowRecoveredSettingsCursor() {
    if (!GetWorld()) return;
    if (APlayerController* Controller=UGameplayStatics::GetPlayerController(this,0)) Controller->bShowMouseCursor=true;
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

int32 URecoveredSessionWidget::GetSwitchedInventoryTab(int32 CurrentInventoryTab) {
    if (CurrentInventoryTab==0) return 1;
    if (CurrentInventoryTab==1) return 0;
    return CurrentInventoryTab;
}

void URecoveredSessionWidget::SwitchInventoryTabs() {
    PlayRecoveredInventorySwitchSound(this);
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return;
    const int32 NextInventoryTab=GetSwitchedInventoryTab(Manager->CurrentInventoryTab);
    if (NextInventoryTab==Manager->CurrentInventoryTab) return;
    Manager->CurrentInventoryTab=NextInventoryTab;
    if (NextInventoryTab==1) {
        if (auto* Page=Cast<URecoveredPG2TabbedInventoryWidget>(GetWidgetFromName(TEXT("PG2TabbedInventory_Widget")))) Page->PlayRecoveredAnimation(TEXT("SwitchTabAnimation"));
    } else {
        if (auto* Page=Cast<URecoveredTabbedInventoryWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Page->PlayRecoveredAnimation(TEXT("SwitchInventoryTabAnimation"));
    }
    UWidgetBlueprintLibrary::SetFocusToGameViewport();
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
        ToggleRecoveredSettingsMenu();
        return FReply::Handled();
    } else if (Key == EKeys::SpaceBar) {
        PlayRecoveredAnimation(TEXT("DrawButtonKeyPress"));
        DrawCard();
        return FReply::Handled();
    } else if (Key == EKeys::Tab || Key == EKeys::Q) {
        SwitchInventoryTabs();
        return FReply::Handled();
    } else if (Key == EKeys::One) {
        auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
        if (Manager && Manager->CurrentInventoryTab==0) {
            if (auto* Inventory=Cast<URecoveredTabbedInventoryWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Inventory->UseCumChanceItem();
        } else if (Manager && Manager->CurrentInventoryTab==1) {
            if (auto* Inventory=Cast<URecoveredPG2TabbedInventoryWidget>(GetWidgetFromName(TEXT("PG2TabbedInventory_Widget")))) Inventory->UseBonerPillItem();
        }
        return FReply::Handled();
    } else if (Key == EKeys::Two) {
        auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
        if (Manager && Manager->CurrentInventoryTab==0) {
            if (auto* Inventory=Cast<URecoveredTabbedInventoryWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Inventory->UseReduceHeatItem();
        } else if (Manager && Manager->CurrentInventoryTab==1) {
            if (auto* Inventory=Cast<URecoveredPG2TabbedInventoryWidget>(GetWidgetFromName(TEXT("PG2TabbedInventory_Widget")))) Inventory->ToggleSuccuShields();
            Manager->PlayDialogueLine(TEXT("SpecialEvent_12"));
        }
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
    } else if (Key == EKeys::Four) {
        auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
        if (Manager && Manager->CurrentInventoryTab==0) {
            if (auto* Inventory=Cast<URecoveredTabbedInventoryWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Inventory->TabbedInventorySlowdownTrigger();
        }
        return FReply::Handled();
    } else if (Key == EKeys::Five) {
        auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
        if (Manager && Manager->CurrentInventoryTab==0) {
            if (auto* Inventory=Cast<URecoveredTabbedInventoryWidget>(GetWidgetFromName(TEXT("PG1TabbedInventory_Widget")))) Inventory->TabbedInventoryBreakTrigger();
        }
        return FReply::Handled();
    } else if (Key == EKeys::B) {
        ToggleFavorite();
        return FReply::Handled();
    } else if (Key == EKeys::C) {
        ToggleRecoveredUI();
        return FReply::Handled();
    } else if (Key == EKeys::E) {
        RequestRecoveredCumMedia();
        return FReply::Handled();
    } else if (Key == EKeys::V) {
        ToggleRecoveredChallengeTracker();
        return FReply::Handled();
    } else if (Key == EKeys::W) {
        RequestRecoveredTaunt();
        return FReply::Handled();
    } else if (Key == EKeys::X) {
        if (auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr) Manager->ToggleRecoveredBrainMelter();
        return FReply::Handled();
    } else if (Key == EKeys::Z) {
        CycleRecoveredCropMode();
        return FReply::Handled();
    } else if (Key == EKeys::Up) {
        if (auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr) {
            Manager->PlayerVariables.CurrentComboCount=URecoveredStateRuleLibrary::AddInt32Wrapping(Manager->PlayerVariables.CurrentComboCount,100);
            Manager->PlayerVariables.TotalStrokeCount=URecoveredStateRuleLibrary::AddInt32Wrapping(Manager->PlayerVariables.TotalStrokeCount,100);
            Manager->LootBarPercentage=1.0;
            Manager->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::Strokes,100);
            Manager->OnMetricUpdateRequested.Broadcast(ERecoveredMetric::MaxCombo,100);
        }
        return FReply::Handled();
    } else if (Key == EKeys::K) {
        if (auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr) {
            Manager->PlayerVariables.PlayerCoins=9999999;
            const FName Items[]={TEXT("XCumChance"),TEXT("DecreaseHeat"),TEXT("Edge"),TEXT("SuccuShield"),TEXT("Break"),TEXT("Slowdown"),TEXT("BonerPill"),TEXT("Resupply"),TEXT("SpawnSuccubus"),TEXT("MinusPercentHeatGain")};
            for (const FName Item : Items) Manager->OwnedItemCounts.Add(Item,99);
            const FName Upgrades[]={TEXT("XCumChance"),TEXT("DecreaseHeat"),TEXT("SuccuShield"),TEXT("Break"),TEXT("Slowdown"),TEXT("BonerPill"),TEXT("Resupply"),TEXT("SpawnSuccubus"),TEXT("MinusPercentHeatGain")};
            for (const FName Item : Upgrades) Manager->SetRecoveredItemUpgradeLevel(Item,4);
            Manager->SetRecoveredItemUpgradeLevel(TEXT("Edge"),3);
            Manager->SpawnRecoveredStore();
        }
        return FReply::Handled();
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
    if (!Manager || !Manager->MediaDeckState || !Instance || !Instance->CurrentSave) return;
    const int32 Deck=URecoveredDeckState::FavoriteDeckForCardType(Manager->BeatContext.CardType);
    if (Deck==INDEX_NONE || Manager->SelectedRandomCard.FullPath.IsEmpty()) return;
    bool bNowFavorite=false;
    if (!Manager->MediaDeckState->ToggleFavorite(static_cast<uint8>(Deck),Manager->SelectedRandomCard,bNowFavorite)) return;
    const FString Key=URecoveredDeckState::FavoriteSaveKey(static_cast<uint8>(Deck));
    bool bSaved=Instance->CurrentSave->SetStringArraySetting(Key,Manager->MediaDeckState->GetFavoritePaths(static_cast<uint8>(Deck)));
    TArray<FString> AllFavorites;
    for (uint8 FavoriteDeck=0;FavoriteDeck<5;++FavoriteDeck) AllFavorites.Append(Manager->MediaDeckState->GetFavoritePaths(FavoriteDeck));
    AllFavorites.Sort();
    for (int32 Index=AllFavorites.Num()-1;Index>0;--Index) if (AllFavorites[Index]==AllFavorites[Index-1]) AllFavorites.RemoveAt(Index);
    bSaved|=Instance->CurrentSave->SetStringArraySetting(TEXT("FavoriteMedia"),AllFavorites);
    if (bSaved) Instance->SaveRecoveredState();
    static const TCHAR* Categories[]={TEXT("Slow"),TEXT("Medium"),TEXT("Fast"),TEXT("Succubus"),TEXT("Cum")};
    const FString Description=FString(Categories[Deck])+TEXT(" Media ")+(bNowFavorite ? TEXT("added to your favorites.") : TEXT("removed from your favorites."));
    Manager->CreateRecoveredNotification(NAME_None,bNowFavorite ? TEXT("Media Favorited") : TEXT("Media Unfavorited"),Description);
}

void URecoveredSessionWidget::ToggleRecoveredUI() {
    static const FName Widgets[]={TEXT("CoinsStoreVertiBox"),TEXT("DealerText_UI"),TEXT("BeatBarBackground_UI"),TEXT("HeatMeterBar"),TEXT("ComboTextBoxInvalidation"),TEXT("TabbedInventorySizeBox"),TEXT("HealthMeter"),TEXT("CumMeterSplashBackground"),TEXT("TauntCumInvalidationBox"),TEXT("CumMeterHeader"),TEXT("CumMeterTop"),TEXT("CumMeterProgressBar"),TEXT("LootMeterProgressBar"),TEXT("NotificationInvalidationBox"),TEXT("CoinAddText"),TEXT("CoinIcon")};
    bUIHidden=!bUIHidden;
    for (const FName Name : Widgets) if (UWidget* Widget=GetWidgetFromName(Name)) Widget->SetVisibility(bUIHidden ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void URecoveredSessionWidget::ToggleRecoveredChallengeTracker() {
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->ChallengeTracker || Instance->ChallengeTracker->TrackedChallenges.IsEmpty()) return;
    UWidget* Container=GetWidgetFromName(TEXT("ChallengeTrackerContainer"));
    if (!Container) return;
    PlayRecoveredAnimation(Container->IsVisible() ? TEXT("HideChallengeTrackerUIAnim") : TEXT("UnHideChallengeTrackerUIAnim"));
}

void URecoveredSessionWidget::CycleRecoveredCropMode() {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager || !Manager->MediaPlayback) return;
    FName Title;
    FString Description;
    if (CurrentContentStretchState==0) {
        CurrentContentStretchState=1;
        Manager->MediaPlayback->SetCropMode(ERecoveredCropMode::Fill);
        Title=TEXT("Crop Mode: Fill");
        Description=TEXT("Stretches to cover the screen");
    } else if (CurrentContentStretchState==1) {
        CurrentContentStretchState=2;
        Manager->MediaPlayback->SetCropMode(ERecoveredCropMode::Fit);
        Title=TEXT("Crop Mode: Fit");
        Description=TEXT("Scales to fit inside the frame");
    } else {
        CurrentContentStretchState=0;
        Manager->MediaPlayback->SetCropMode(ERecoveredCropMode::Auto);
        Title=TEXT("Crop Mode: Auto");
        Description=TEXT("Chooses the best option automatically");
    }
    Manager->CreateRecoveredNotification(TEXT("CropIcon"),Title.ToString(),Description);
}

void URecoveredSessionWidget::RequestRecoveredCumMedia() {
    RequestRecoveredCumMediaWithAnimation(TEXT("CumButtonKeyPress"));
}

void URecoveredSessionWidget::RequestRecoveredCumMediaFromButton() {
    RequestRecoveredCumMediaWithAnimation(TEXT("CumButtonClick"));
}

void URecoveredSessionWidget::RequestRecoveredCumMediaWithAnimation(FName AnimationName) {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return;
    if (Manager->EdgingManager) Manager->EdgingManager->ClearRecoveredEdgeHold();
    PlayRecoveredAnimation(AnimationName);
    Manager->OpenRecoveredCumMedia();
}

void URecoveredSessionWidget::RequestRecoveredTaunt() {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (!Manager) return;
    if (Manager->BeatContext.CardType==6) {
        Manager->CreateRecoveredNotification(TEXT("TauntIcon"),TEXT("Cannot Taunt"),TEXT("Cannot taunt during cum events."));
        return;
    }
    if (Manager->BeatContext.CardType==5) {
        Manager->CreateRecoveredNotification(TEXT("TauntIcon"),TEXT("Cannot Taunt"),TEXT("Cannot taunt during edging events."));
        return;
    }
    if (Manager->bIsTauntOnCooldown) {
        Manager->CreateRecoveredNotification(TEXT("TauntIcon"),TEXT("Taunt on Cooldown"),FString::Printf(TEXT("Try again in %d seconds."),FMath::TruncToInt(Manager->TauntCooldownTimerDuration)));
        return;
    }
    if (Manager->bHasTaunted) {
        Manager->CreateRecoveredNotification(TEXT("TauntIcon"),TEXT("Already Taunted"),TEXT("Wait until the next task to taunt."));
        return;
    }
    PlayRecoveredAnimation(TEXT("TauntButtonKeyPress"));
    if (Manager->BeatContext.CardType==3) {
        Manager->CreateRecoveredNotification(TEXT("TauntIcon"),TEXT("Succubus Taunt!"),TEXT("Succubi Spawn Chance Permanently Increased. "));
        Manager->AddRecoveredPermanentSuccubusWeight();
        Manager->SpawnRecoveredOverlay(TEXT("UseSuccubusTauntOverlay_Widget"));
    } else {
        Manager->CreateRecoveredNotification(TEXT("TauntIcon"),TEXT("Taunt!"),TEXT("Increased Stroke Speed & Count"));
        Manager->SpawnRecoveredOverlay(TEXT("UseTauntOverlay_Widget"));
    }
    Manager->ExecuteTaunt();
}
