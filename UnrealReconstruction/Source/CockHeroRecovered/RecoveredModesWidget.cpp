#include "RecoveredModesWidget.h"
#include "RecoveredRules.h"
#include "RecoveredMenu.h"
#include "RecoveredSuccuShopWidget.h"
#include "RecoveredMusicUpgrades.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredSuccuEconomy.h"
#include "RecoveredContentPaths.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/VerticalBox.h"
#include "Components/VerticalBoxSlot.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "HAL/FileManager.h"
#include "Kismet/GameplayStatics.h"

namespace {
ARecoveredGlobalManager* ModeManager(UUserWidget* Widget) { return Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(Widget)); }
UButton* ModeButton(UWidgetTree* Tree, UVerticalBox* Box, const TCHAR* Name, const FString& Label) {
    auto* Button = Tree->ConstructWidget<UButton>(UButton::StaticClass(), FName(Name));
    auto* Text = Tree->ConstructWidget<UTextBlock>(); Text->SetText(FText::FromString(Label)); Text->SetAutoWrapText(true);
    Button->AddChild(Text);
    if (auto* ContentSlot=Cast<UButtonSlot>(Text->Slot)) ContentSlot->SetHorizontalAlignment(HAlign_Fill);
    Box->AddChildToVerticalBox(Button)->SetPadding(FMargin(8)); return Button;
}
}
TSharedRef<SWidget> URecoveredModesWidget::RebuildWidget() {
    if (!WidgetTree) WidgetTree = NewObject<UWidgetTree>(this, TEXT("WidgetTree"));
    if (WidgetTree->RootWidget) return Super::RebuildWidget();
    auto* Border = WidgetTree->ConstructWidget<UBorder>(); Border->SetPadding(FMargin(24)); Border->SetBrushColor(FLinearColor(.025f, .03f, .05f, .96f));
    auto* Box = WidgetTree->ConstructWidget<UVerticalBox>(); Border->SetContent(Box); WidgetTree->RootWidget = Border;
    Status = WidgetTree->ConstructWidget<UTextBlock>(); Status->SetAutoWrapText(true); Box->AddChildToVerticalBox(Status);
    LoadoutPanel=WidgetTree->ConstructWidget<UVerticalBox>();Box->AddChildToVerticalBox(LoadoutPanel);
    for (int32 SlotIndex=0;SlotIndex<5;++SlotIndex) {
        auto* Choice=WidgetTree->ConstructWidget<UComboBoxString>();LoadoutPanel->AddChildToVerticalBox(Choice);LoadoutSlots.Add(Choice);
    }
    ModeButton(WidgetTree,LoadoutPanel,TEXT("ConfirmLoadout"),TEXT("Confirm loadout"))->OnClicked.AddDynamic(this,&URecoveredModesWidget::ConfirmLoadout);
    LoadoutPanel->SetVisibility(ESlateVisibility::Collapsed);
    const auto* GameInstance = Cast<URecoveredGameInstance>(GetGameInstance());
    const URecoveredSaveGame* Profile = GameInstance ? GameInstance->CurrentSave.Get() : nullptr;
    auto* ClassicObjectives = WidgetTree->ConstructWidget<UComboBoxString>(UComboBoxString::StaticClass(),TEXT("ClassicObjective"));
    for (const auto& Spec : RecoveredObjectives::GetSpecs()) ClassicObjectives->AddOption(Spec.Title);
    const int32 ClassicIndex=RecoveredObjectives::GetSelectedIndex(Profile);
    ClassicObjectives->SetSelectedIndex(ClassicIndex);Box->AddChildToVerticalBox(ClassicObjectives);
    auto* ClassicTarget=WidgetTree->ConstructWidget<UEditableTextBox>(UEditableTextBox::StaticClass(),TEXT("ClassicTarget"));
    ClassicTarget->SetHintText(FText::FromString(TEXT("Objective target")));ClassicTarget->SetText(FText::AsNumber(RecoveredObjectives::GetSavedTarget(Profile,ClassicIndex)));
    ClassicTarget->SetVisibility(ClassicIndex==0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);Box->AddChildToVerticalBox(ClassicTarget);
    ClassicObjectives->OnSelectionChanged.AddDynamic(this,&URecoveredModesWidget::ClassicObjectiveChanged);
    ModeButton(WidgetTree, Box, TEXT("StartClassic"), TEXT("Classic: choose difficulty"))->OnClicked.AddDynamic(this, &URecoveredModesWidget::StartClassic);
    TowerButton = ModeButton(WidgetTree, Box, TEXT("StartTower"), TEXT("Tower: five rounds")); TowerButton->OnClicked.AddDynamic(this, &URecoveredModesWidget::StartTower);
    PlaylistFolder = WidgetTree->ConstructWidget<UEditableTextBox>(); PlaylistFolder->SetText(FText::FromString(FRecoveredContentPaths::GetBeatmapsDirectory())); PlaylistFolder->SetHintText(FText::FromString(TEXT("Beatmap folder"))); Box->AddChildToVerticalBox(PlaylistFolder);
    PlaylistButton = ModeButton(WidgetTree, Box, TEXT("StartPlaylist"), TEXT("Playlist: play beatmaps in folder")); PlaylistButton->OnClicked.AddDynamic(this, &URecoveredModesWidget::StartPlaylist);
    for (int32 I = 0; I < 3; ++I) OptionButtons.Add(ModeButton(WidgetTree, Box, *FString::Printf(TEXT("Draft%d"), I), TEXT("Round option")));
    OptionButtons[0]->OnClicked.AddDynamic(this, &URecoveredModesWidget::PickFirst);
    OptionButtons[1]->OnClicked.AddDynamic(this, &URecoveredModesWidget::PickSecond);
    OptionButtons[2]->OnClicked.AddDynamic(this, &URecoveredModesWidget::PickThird);
    ContinueButton = ModeButton(WidgetTree, Box, TEXT("ContinueRound"), TEXT("Continue")); ContinueButton->OnClicked.AddDynamic(this, &URecoveredModesWidget::ContinueRound);
    PauseButton = ModeButton(WidgetTree, Box, TEXT("PausePlaylist"), TEXT("Pause / resume playlist")); PauseButton->OnClicked.AddDynamic(this, &URecoveredModesWidget::TogglePause);
    ModeButton(WidgetTree, Box, TEXT("MusicDuration"), TEXT("Upgrade break duration and continue"))->OnClicked.AddDynamic(this, &URecoveredModesWidget::UpgradeDuration);
    ModeButton(WidgetTree, Box, TEXT("MusicCharges"), TEXT("Upgrade maximum break charges and continue"))->OnClicked.AddDynamic(this, &URecoveredModesWidget::UpgradeCharges);
    ModeButton(WidgetTree, Box, TEXT("MusicRecharge"), TEXT("Upgrade break recharge strokes and continue"))->OnClicked.AddDynamic(this, &URecoveredModesWidget::UpgradeRecharge);
    auto* ShopHeight = WidgetTree->ConstructWidget<USizeBox>(USizeBox::StaticClass(), TEXT("TowerShopHeight")); ShopHeight->SetHeightOverride(300);
    auto* ShopScroll = WidgetTree->ConstructWidget<UScrollBox>(); ShopHeight->AddChild(ShopScroll);
    if (auto* Manager = ModeManager(this)) {
        auto* Shop = CreateWidget<URecoveredSuccuShopWidget>(GetOwningPlayer(), URecoveredSuccuShopWidget::StaticClass());
        if (Shop) { Shop->Economy = Manager->SuccuEconomy; ShopScroll->AddChild(Shop); }
    }
    Box->AddChildToVerticalBox(ShopHeight);
    ModeButton(WidgetTree, Box, TEXT("CloseModes"), TEXT("Close"))->OnClicked.AddDynamic(this, &URecoveredModesWidget::ClosePanel);
    return Super::RebuildWidget();
}
void URecoveredModesWidget::NativeTick(const FGeometry& Geometry, float DeltaTime) {
    Super::NativeTick(Geometry, DeltaTime); auto* Manager = ModeManager(this); if (!Manager || !Status) return;
    if (LoadoutInventory) {
        Status->SetText(FText::FromString(Manager->LastSessionError.IsEmpty() ? TEXT("Choose up to five items. Empty slots are allowed.") : Manager->LastSessionError));
        if (auto* Root=Cast<UVerticalBox>(LoadoutPanel->GetParent())) for (auto* Child:Root->GetAllChildren()) Child->SetVisibility(Child==LoadoutPanel || Child==Status || Child==GetWidgetFromName(TEXT("CloseModes")) ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        return;
    }
    const bool Active = Manager->ActiveRecoveredMode != 0;
    if (auto* Classic = GetWidgetFromName(TEXT("StartClassic"))) Classic->SetVisibility(Active ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    if (auto* Objectives=Cast<UComboBoxString>(GetWidgetFromName(TEXT("ClassicObjective")))) {
        Objectives->SetVisibility(Active ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
        if (auto* Target=GetWidgetFromName(TEXT("ClassicTarget"))) Target->SetVisibility(Active || Objectives->GetSelectedIndex()==0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    }
    TowerButton->SetVisibility(Active ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    PlaylistButton->SetVisibility(Active ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    PlaylistFolder->SetVisibility(Active ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
    const auto* Tower = Manager->TowerRuntime.Get();
    const bool Selecting = Manager->ActiveRecoveredMode == 1 && Tower && Tower->Phase == ERecoveredRoundPhase::RoundSelection;
    for (int32 I = 0; I < OptionButtons.Num(); ++I) {
        OptionButtons[I]->SetVisibility(Selecting ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
        if (Selecting && Tower->CurrentOptions.IsValidIndex(I)) {
            const auto& Option = Tower->CurrentOptions[I];
            const TCHAR* Names[] = {TEXT("Fill meter"), TEXT("Seconds"), TEXT("Strokes"), TEXT("Edges"), TEXT("Coin flip"), TEXT("Ruins"), TEXT("Finish within seconds"), TEXT("Tributes"), TEXT("Succubi")};
            TArray<FString> Rewards;
            for (const auto& Reward : Option.NativeRewards) {
                if (Reward.Type == 0) Rewards.Add(FString::Printf(TEXT("%d coins"), Reward.Amount));
                else if (Reward.Type == 1) Rewards.Add(FString::Printf(TEXT("%d SuccuCoins"), Reward.Amount));
                else if (Reward.Type == 2) Rewards.Add(TEXT("Unlock ") + RecoveredNewerInventoryAdapter::ResolveID(Reward.Item).ToString());
                else if (Reward.Type == 3) Rewards.Add(FString::Printf(TEXT("Upgrade %s +%d"), *RecoveredNewerInventoryAdapter::ResolveID(Reward.Item).ToString(), Reward.Amount));
                else if (Reward.Type == 5) for (const auto& Entry : URecoveredSuccuEconomy::GetCatalog()) if (Entry.Modifier == Reward.Modifier) { Rewards.Add(TEXT("Modifier: ") + Entry.Title); break; }
            }
            if (Rewards.IsEmpty()) Rewards.Add(FString::Printf(TEXT("%d coins, %d SuccuCoins"), Option.RewardCoins, Option.RewardSuccuCoins));
            const FString ObjectiveText=Option.Objective==0 ? TEXT("Fill meter to 100%") : FString::Printf(TEXT("%s %.0f"),Names[Option.Objective],Option.ObjectiveParam);
            if (auto* Label = Cast<UTextBlock>(OptionButtons[I]->GetContent())) Label->SetText(FText::FromString(FString::Printf(TEXT("Tier %d. %s: %s. Rewards: %s"), Option.DifficultyTier, Option.DraftLane == 0 ? TEXT("Relief") : Option.DraftLane == 1 ? TEXT("Steady") : TEXT("Risk"), *ObjectiveText, *FString::Join(Rewards, TEXT(", ")))));
        }
    }
    const bool Between = Manager->ActiveRecoveredMode == 1 && Tower && (Tower->Phase == ERecoveredRoundPhase::RoundComplete || Tower->Phase == ERecoveredRoundPhase::Shop);
    ContinueButton->SetVisibility(Between ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    if (auto* Shop = GetWidgetFromName(TEXT("TowerShopHeight"))) Shop->SetVisibility(Manager->ActiveRecoveredMode == 1 && Tower && Tower->Phase == ERecoveredRoundPhase::Shop ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    PauseButton->SetVisibility(Manager->ActiveRecoveredMode == 2 && Manager->PlaylistRuntime->bPlaying ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    const auto* Instance = Cast<URecoveredGameInstance>(Manager->GetGameInstance());
    const URecoveredSaveGame* Save = Instance ? Instance->CurrentSave.Get() : nullptr;
    const TCHAR* UpgradeButtons[] = {TEXT("MusicDuration"), TEXT("MusicCharges"), TEXT("MusicRecharge")};
    for (uint8 Type = 0; Type < 3; ++Type) if (auto* Button = GetWidgetFromName(UpgradeButtons[Type])) Button->SetVisibility(Manager->ActiveRecoveredMode == 2 && Manager->PlaylistRuntime->bAwaitingNextTrack && RecoveredMusicUpgrades::GetLevel(Save, Type) < 5 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    FString Description = TEXT("Choose a game mode.");
    if (Manager->ActiveRecoveredMode == 1 && Tower) Description = FString::Printf(TEXT("Tower. Round %d/%d. Completed %d. Failed %d."), Tower->CurrentRound, Tower->TotalRounds, Tower->CompletedRounds, Tower->FailedRounds);
    if (Manager->ActiveRecoveredMode == 2 && Manager->PlaylistRuntime) Description = FString::Printf(TEXT("Playlist. %s. Completed %d. %.1fs."), *Manager->PlaylistRuntime->CurrentSong.Meta.Title, Manager->PlaylistRuntime->CompletedRounds, Manager->PlaylistRuntime->GetAudioTime());
    if (!Manager->LastSessionError.IsEmpty()) Description += TEXT("\n") + Manager->LastSessionError;
    Status->SetText(FText::FromString(Description));
}
void URecoveredModesWidget::StartTower() { ShowLoadout(1); }
void URecoveredModesWidget::StartClassic() {
    if (auto* Manager = ModeManager(this)) {
        if (Manager->ActiveRecoveredMode != 0) return;
        auto* Objectives=Cast<UComboBoxString>(GetWidgetFromName(TEXT("ClassicObjective")));
        auto* Target=Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ClassicTarget")));
        int32 Value=1;
        if (!Objectives || !Target || (Objectives->GetSelectedIndex()!=0 && !LexTryParseString(Value,*Target->GetText().ToString().Replace(TEXT(","),TEXT(""))))) { Manager->LastSessionError=TEXT("Objective target must be a positive integer");return; }
        if (!Manager->ConfigureRecoveredClassicObjective(Objectives->GetSelectedIndex(),Value,Manager->LastSessionError)) return;
        ShowLoadout(0);
    }
}
void URecoveredModesWidget::ShowLoadout(uint8 Mode) {
    if (auto* Manager=ModeManager(this)) Manager->PendingRecoveredLoadoutJson.Reset();
    LoadoutMode=Mode;LoadoutInventory=NewObject<URecoveredNewerInventory>(this);
    FRandomStream Random(FMath::Rand());
    RecoveredNewerInventoryAdapter::PrepareFreshLoadout(*LoadoutInventory,Mode,Random);
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Mode==0) RecoveredNewerInventoryAdapter::RestoreClassicHotbar(*LoadoutInventory,Instance ? Instance->CurrentSave.Get() : nullptr);
    for (int32 SlotIndex=0;SlotIndex<LoadoutSlots.Num();++SlotIndex) {
        auto* Choice=LoadoutSlots[SlotIndex].Get();
        Choice->ClearOptions();Choice->AddOption(TEXT("None"));
        for (const auto& Pair:LoadoutInventory->OwnedItems) if (Pair.Value.bIsUnlocked) Choice->AddOption(RecoveredNewerInventoryAdapter::ResolveID(Pair.Key).ToString());
        Choice->SetSelectedOption(LoadoutInventory->HotbarItems.IsValidIndex(SlotIndex) && LoadoutInventory->HotbarItems[SlotIndex]!=ERecoveredShopItemType::None ? RecoveredNewerInventoryAdapter::ResolveID(LoadoutInventory->HotbarItems[SlotIndex]).ToString() : TEXT("None"));
    }
    LoadoutPanel->SetVisibility(ESlateVisibility::Visible);
}
void URecoveredModesWidget::ConfirmLoadout() {
    auto* Manager=ModeManager(this);if (!Manager || !LoadoutInventory) return;
    TSet<FString> Selected;
    for (const auto& Choice:LoadoutSlots) {
        const FString Item=Choice->GetSelectedOption();
        if (Item==TEXT("None")) continue;
        if (Selected.Contains(Item)) { Manager->LastSessionError=TEXT("Each item can occupy only one loadout slot");return; }
        Selected.Add(Item);
    }
    LoadoutInventory->ResetHotbar();
    for (int32 SlotIndex=0;SlotIndex<LoadoutSlots.Num();++SlotIndex) {
        ERecoveredShopItemType Type;
        if (RecoveredNewerInventoryAdapter::ResolveType(FName(*LoadoutSlots[SlotIndex]->GetSelectedOption()),Type)) LoadoutInventory->EquipToSlot(Type,SlotIndex);
    }
    if (LoadoutMode==0) {
        auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
        if (!Instance || !Instance->CurrentSave) return;
        const FString Before=Instance->CurrentSave->StateJson;
        if (!RecoveredNewerInventoryAdapter::SaveClassicHotbar(*LoadoutInventory,Instance->CurrentSave.Get()) || !Instance->SaveRecoveredState()) {
            Instance->CurrentSave->StateJson=Before;Manager->LastSessionError=TEXT("Classic loadout could not be saved");
            return;
        }
    }
    Manager->PendingRecoveredLoadoutJson=LoadoutInventory->ExportRecoveryState();
    LoadoutInventory=nullptr;LoadoutPanel->SetVisibility(ESlateVisibility::Collapsed);
    if (auto* Root=Cast<UVerticalBox>(LoadoutPanel->GetParent())) for (auto* Child:Root->GetAllChildren()) if (Child!=LoadoutPanel) Child->SetVisibility(ESlateVisibility::Visible);
    if (LoadoutMode==1) Manager->StartTowerSession();
    else if (auto* Menu=Cast<URecoveredMainMenu>(Manager->MainMenu)) { RemoveFromParent();Menu->OpenDifficulty(); }
}
void URecoveredModesWidget::ClassicObjectiveChanged(FString Selection,ESelectInfo::Type SelectionType) {
    auto* Objectives=Cast<UComboBoxString>(GetWidgetFromName(TEXT("ClassicObjective")));
    auto* Target=Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ClassicTarget")));
    if (!Objectives || !Target) return;
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const int32 Index=Objectives->GetSelectedIndex();
    Target->SetText(FText::AsNumber(RecoveredObjectives::GetSavedTarget(Instance ? Instance->CurrentSave.Get() : nullptr,Index)));
    Target->SetVisibility(Index==0 ? ESlateVisibility::Collapsed : ESlateVisibility::Visible);
}
void URecoveredModesWidget::StartPlaylist() {
    if (auto* Manager = ModeManager(this)) {
        Manager->PendingRecoveredLoadoutJson.Reset();
        TArray<FString> Paths; IFileManager::Get().FindFilesRecursive(Paths, *PlaylistFolder->GetText().ToString(), TEXT("beatmap.json"), true, false); Paths.Sort();
        Manager->StartPlaylistSession(Paths);
    }
}
void URecoveredModesWidget::Pick(int32 Index) { if (auto* Manager = ModeManager(this)) if (Manager->TowerRuntime && Manager->TowerRuntime->SelectOption(Index)) RemoveFromParent(); }
void URecoveredModesWidget::PickFirst() { Pick(0); }
void URecoveredModesWidget::PickSecond() { Pick(1); }
void URecoveredModesWidget::PickThird() { Pick(2); }
void URecoveredModesWidget::ContinueRound() {
    if (auto* Manager = ModeManager(this)) if (auto* Tower = Manager->TowerRuntime.Get()) {
        if (Tower->Phase == ERecoveredRoundPhase::Shop) {
            for (auto& Overlay : Manager->EventOverlays) if (Overlay && Overlay != this) Overlay->RemoveFromParent();
            Manager->EventOverlays.Reset();
            Tower->LeaveShop();
        } else {
            Tower->ContinueAfterRound();
            if (Tower->Phase == ERecoveredRoundPhase::Shop) Manager->SpawnRecoveredStore();
        }
    }
}
void URecoveredModesWidget::TogglePause() { if (auto* Manager = ModeManager(this)) if (auto* Playlist = Manager->PlaylistRuntime.Get()) { if (Playlist->bPaused) Playlist->ResumePlayback(); else Playlist->PausePlayback(); } }
void URecoveredModesWidget::UpgradeDuration() { ChooseMusicUpgrade(0); }
void URecoveredModesWidget::UpgradeCharges() { ChooseMusicUpgrade(1); }
void URecoveredModesWidget::UpgradeRecharge() { ChooseMusicUpgrade(2); }
void URecoveredModesWidget::ChooseMusicUpgrade(uint8 Type) {
    auto* Manager = ModeManager(this); if (!Manager || Manager->ActiveRecoveredMode != 2 || !Manager->PlaylistRuntime->bAwaitingNextTrack) return;
    auto* Instance = Cast<URecoveredGameInstance>(Manager->GetGameInstance()); if (!Instance || !Instance->CurrentSave) return;
    const int32 Level = RecoveredMusicUpgrades::GetLevel(Instance->CurrentSave, Type);
    if (Level >= 5 || !RecoveredMusicUpgrades::SetLevel(Instance->CurrentSave, Type, Level + 1)) return;
    Instance->SaveRecoveredState();
    if (!Manager->PlaylistRuntime->ContinuePlaylist(Manager->LastSessionError)) { Manager->HandlePlaylistAudioFailed(Manager->LastSessionError); return; }
    RemoveFromParent();
}
void URecoveredModesWidget::ClosePanel() {
    LoadoutInventory=nullptr;
    if (LoadoutPanel) {
        LoadoutPanel->SetVisibility(ESlateVisibility::Collapsed);
        if (auto* Root=Cast<UVerticalBox>(LoadoutPanel->GetParent())) for (auto* Child:Root->GetAllChildren()) if (Child!=LoadoutPanel) Child->SetVisibility(ESlateVisibility::Visible);
    }
    if (auto* Manager=ModeManager(this)) Manager->PendingRecoveredLoadoutJson.Reset();
    if (auto* Manager = ModeManager(this)) if (Manager->ActiveRecoveredMode == 2 && Manager->PlaylistRuntime->bAwaitingNextTrack) { Manager->ReturnToMainMenu(); return; }
    if (auto* Manager = ModeManager(this)) if (Manager->ActiveRecoveredMode == 1 && Manager->TowerRuntime && Manager->TowerRuntime->Phase != ERecoveredRoundPhase::Playing && Manager->TowerRuntime->Phase != ERecoveredRoundPhase::BossRound) { Manager->ReturnToMainMenu(); return; }
    RemoveFromParent();
}
