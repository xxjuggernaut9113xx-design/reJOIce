#include "RecoveredRules.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
#include "UObject/Package.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBrainMelterTest,"CockHero.Recovery.BrainMelterMediaSwap",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredBrainMelterTest::RunTest(const FString& Parameters) {
    FRecoveredMediaEntry Slow;
    Slow.File=TEXT("slow.mp4");
    Slow.Type=TEXT("video");
    Slow.FullPath=TEXT("C:/Recovery/slow.mp4");
    FRecoveredMediaEntry Fast;
    Fast.File=TEXT("fast.mp4");
    Fast.Type=TEXT("video");
    Fast.FullPath=TEXT("C:/Recovery/fast.mp4");
    FRecoveredMediaEntry Cum;
    Cum.File=TEXT("cum.mp4");
    Cum.Type=TEXT("video");
    Cum.FullPath=TEXT("C:/Recovery/cum.mp4");

    auto* Decks=NewObject<URecoveredDeckState>(GetTransientPackage());
    Decks->Master.Slow={Slow};
    Decks->Master.Fast={Fast};
    Decks->Master.Cum={Cum};
    Decks->SetChildDecks();

    auto* Manager=NewObject<ARecoveredGlobalManager>(GetTransientPackage());
    Manager->MediaDeckState=Decks;
    Manager->bBrainMelterEnabled=true;
    Manager->MasterBrainMelterSwapInterval=2;
    Manager->CurrentBrainMelterSwapInterval=2;
    Manager->BeatTimeline->TotalStrokes=2;
    Manager->BeatTimeline->CompletedBeats=0;
    Manager->BeatContext.CardType=0;

    Manager->TriggerBrainMelter();
    TestEqual(TEXT("Non-final beat leaves the source interval unchanged"),Manager->CurrentBrainMelterSwapInterval,2);
    TestFalse(TEXT("Non-final beat cannot swap media"),Manager->bLastBrainMelterSwapSucceeded);

    Manager->BeatTimeline->CompletedBeats=1;
    Manager->TriggerBrainMelter();
    TestEqual(TEXT("First final beat decrements the source interval"),Manager->CurrentBrainMelterSwapInterval,1);
    TestFalse(TEXT("Interval has not elapsed on its first final beat"),Manager->bLastBrainMelterSwapSucceeded);

    Manager->TriggerBrainMelter();
    TestEqual(TEXT("Elapsed interval resets from its source master value"),Manager->CurrentBrainMelterSwapInterval,2);
    TestTrue(TEXT("Elapsed interval swaps the active media"),Manager->bLastBrainMelterSwapSucceeded);
    TestEqual(TEXT("Slow card type routes to the slow media deck"),Manager->LastBrainMelterSwapDeck,0);
    TestEqual(TEXT("Slow swap selects source media"),Manager->SelectedRandomCard.FullPath,Slow.FullPath);
    TestEqual(TEXT("One-item slow deck refills after source removal"),Decks->Child.Slow.Num(),1);

    Manager->MasterBrainMelterSwapInterval=1;
    Manager->CurrentBrainMelterSwapInterval=1;
    Manager->BeatContext.CardType=5;
    Manager->TriggerBrainMelter();
    TestTrue(TEXT("Fast variant swaps media"),Manager->bLastBrainMelterSwapSucceeded);
    TestEqual(TEXT("Card type five shares the fast deck"),Manager->LastBrainMelterSwapDeck,2);
    TestEqual(TEXT("Fast variant selects fast media"),Manager->SelectedRandomCard.FullPath,Fast.FullPath);

    Manager->BeatContext.CardType=6;
    Manager->TriggerBrainMelter();
    TestEqual(TEXT("Cum card routes to the cum deck"),Manager->LastBrainMelterSwapDeck,4);
    TestEqual(TEXT("Cum card selects source media"),Manager->SelectedRandomCard.FullPath,Cum.FullPath);

    Manager->MasterBrainMelterSwapInterval=3;
    Manager->CurrentBrainMelterSwapInterval=1;
    Manager->BeatContext.CardType=4;
    Manager->TriggerBrainMelter();
    TestEqual(TEXT("Unsupported card type still resets the elapsed source counter"),Manager->CurrentBrainMelterSwapInterval,3);
    TestFalse(TEXT("Unsupported card type does not swap media"),Manager->bLastBrainMelterSwapSucceeded);
    TestEqual(TEXT("Unsupported card type records no swap deck"),Manager->LastBrainMelterSwapDeck,INDEX_NONE);

    Manager->bBrainMelterEnabled=false;
    Manager->CurrentBrainMelterSwapInterval=2;
    Manager->BeatContext.CardType=0;
    Manager->TriggerBrainMelter();
    TestEqual(TEXT("Disabled Brain Melter leaves the source interval intact"),Manager->CurrentBrainMelterSwapInterval,2);
    return true;
}
#endif
