#include "RecoveredDecks.h"
#include "RecoveredMediaPlayback.h"
#include "RecoveredRules.h"
#include "RecoveredSessionWidget.h"
#include "Components/ScaleBox.h"
#include "Components/TextBlock.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSessionControlTest,"CockHero.Recovery.SessionControlHotkeys",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSessionControlTest::RunTest(const FString& Parameters) {
    FRecoveredMediaEntry Slow;
    Slow.File=TEXT("slow.mp4");
    Slow.Type=TEXT("video");
    Slow.FullPath=TEXT("C:/Recovery/slow.mp4");
    FRecoveredMediaEntry Cum;
    Cum.File=TEXT("cum.mp4");
    Cum.Type=TEXT("video");
    Cum.FullPath=TEXT("C:/Recovery/cum.mp4");

    auto* Decks=NewObject<URecoveredDeckState>(GetTransientPackage());
    Decks->Master.Slow={Slow};
    Decks->Master.Cum={Cum};
    Decks->SetChildDecks();
    bool bNowFavorite=false;
    TestTrue(TEXT("Source slow favorite can be added"),Decks->ToggleFavorite(0,Slow,bNowFavorite));
    TestTrue(TEXT("Source slow favorite state is added"),bNowFavorite);
    TestEqual(TEXT("Master favorite receives source entry"),Decks->MasterFavorites.Slow.Num(),1);
    TestEqual(TEXT("Child favorite receives source entry"),Decks->ChildFavorites.Slow.Num(),1);
    TestTrue(TEXT("Source slow favorite can be removed"),Decks->ToggleFavorite(0,Slow,bNowFavorite));
    TestFalse(TEXT("Source slow favorite state is removed"),bNowFavorite);
    TestEqual(TEXT("Master favorite removal uses array item semantics"),Decks->MasterFavorites.Slow.Num(),0);
    Decks->RestoreFavoritePaths(0,{Slow.FullPath});
    TestEqual(TEXT("Persisted source favorite restores by media path"),Decks->GetFavoritePaths(0),TArray<FString>{Slow.FullPath});
    const int32 CumBefore=Decks->Child.Cum.Num();
    FRecoveredMediaEntry Chosen;
    TestTrue(TEXT("Manual cum media chooses a card"),Decks->ChooseRandom(4,false,Chosen,true));
    TestEqual(TEXT("Manual cum media keeps source deck intact"),Decks->Child.Cum.Num(),CumBefore);
    TestEqual(TEXT("Manual cum media selects source entry"),Chosen.FullPath,Cum.FullPath);
    TestEqual(TEXT("Source favorites route slow cards"),URecoveredDeckState::FavoriteDeckForCardType(0),0);
    TestEqual(TEXT("Source favorites route medium cards"),URecoveredDeckState::FavoriteDeckForCardType(1),1);
    TestEqual(TEXT("Source favorites route fast variants"),URecoveredDeckState::FavoriteDeckForCardType(7),2);
    TestEqual(TEXT("Source favorites route succubus cards"),URecoveredDeckState::FavoriteDeckForCardType(3),3);
    TestEqual(TEXT("Source favorites route cum cards"),URecoveredDeckState::FavoriteDeckForCardType(6),4);

    auto* Playback=NewObject<URecoveredMediaPlayback>(GetTransientPackage());
    auto* ScaleBox=NewObject<UScaleBox>(GetTransientPackage());
    Playback->SetScaleBoxReference(ScaleBox);
    Playback->SetCropMode(ERecoveredCropMode::Fill);
    TestEqual(TEXT("Manual fill selects source stretch fill"),static_cast<int32>(ScaleBox->GetStretch()),static_cast<int32>(EStretch::Fill));
    Playback->SetCropMode(ERecoveredCropMode::Fit);
    TestEqual(TEXT("Manual fit selects source scale-to-fit"),static_cast<int32>(ScaleBox->GetStretch()),static_cast<int32>(EStretch::ScaleToFit));
    Playback->SetCropMode(ERecoveredCropMode::Auto);
    TestEqual(TEXT("Auto crop defaults to source sixteen-by-nine fill"),static_cast<int32>(ScaleBox->GetStretch()),static_cast<int32>(EStretch::Fill));

    auto* Manager=NewObject<ARecoveredGlobalManager>(GetTransientPackage());
    Manager->MediaDeckState=Decks;
    TestTrue(TEXT("Manual cum hotkey opens a selected entry without playback"),Manager->OpenRecoveredCumMedia(false));
    TestEqual(TEXT("Manual cum hotkey preserves deck size"),Decks->Child.Cum.Num(),CumBefore);
    TestEqual(TEXT("Manual cum hotkey writes selected media"),Manager->SelectedRandomCard.FullPath,Cum.FullPath);
    Manager->ToggleRecoveredBrainMelter();
    TestTrue(TEXT("Brain Melter hotkey enables source state"),Manager->bBrainMelterEnabled);
    TestTrue(TEXT("Brain Melter hotkey enables source override"),Manager->bBrainMelterOverrideEnabled);
    Manager->ToggleRecoveredBrainMelter();
    TestFalse(TEXT("Brain Melter hotkey disables source state"),Manager->bBrainMelterEnabled);
    TestFalse(TEXT("Brain Melter hotkey disables source override"),Manager->bBrainMelterOverrideEnabled);
    auto* Rules=NewObject<URecoveredRulesAsset>(GetTransientPackage());
    FRecoveredEventRecord SuccubusEvent;
    SuccubusEvent.EventName=8;
    SuccubusEvent.BaseWeight=20.0;
    Rules->EventRecords={SuccubusEvent};
    Manager->Rules=Rules;
    Manager->AddRecoveredPermanentSuccubusWeight();
    TestEqual(TEXT("Succubus taunt adds the decoded permanent weight"),Rules->EventRecords[0].BaseWeight,35.0);
    Manager->BeatContext.CardType=3;
    Manager->ExecuteTaunt();
    TestEqual(TEXT("Permanent succubus weight remains a UI-route action"),Rules->EventRecords[0].BaseWeight,35.0);
    TestTrue(TEXT("Succubus taunt rejoins the source taunt state"),Manager->bHasTaunted);
    TestTrue(TEXT("Source taunt starts its cooldown before media completion"),Manager->bIsTauntOnCooldown);
    for (int32 Tick=0;Tick<5;++Tick) Manager->OnTauntCooldownExpired();
    TestFalse(TEXT("Source five-second taunt cooldown clears on its fifth tick"),Manager->bIsTauntOnCooldown);
    TestEqual(TEXT("Source taunt cooldown clamps at zero"),Manager->TauntCooldownTimerDuration,0.0);

    UClass* ScreenClass=LoadClass<URecoveredSessionWidget>(nullptr,TEXT("/Game/Recovery/UI/UI_Manager.UI_Manager_C"));
    if (TestNotNull(TEXT("Recovered session screen class"),ScreenClass)) {
        auto* Screen=NewObject<URecoveredSessionWidget>(GetTransientPackage(),ScreenClass);
        Screen->Initialize();
        auto SlateWidget=Screen->TakeWidget();
        UTextBlock* CoinText=Cast<UTextBlock>(Screen->GetWidgetFromName(TEXT("CoinAddText")));
        if (TestNotNull(TEXT("Source C hotkey target exists"),CoinText)) {
            Screen->ToggleRecoveredUI();
            TestEqual(TEXT("Source C hotkey hides HUD target"),CoinText->GetVisibility(),ESlateVisibility::Hidden);
            Screen->ToggleRecoveredUI();
            TestEqual(TEXT("Source C hotkey restores HUD target"),CoinText->GetVisibility(),ESlateVisibility::Visible);
        }
    }
    return true;
}
#endif
