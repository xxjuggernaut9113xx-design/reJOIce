#include "RecoveredRules.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPlaylistMediaRoutingTest, "CockHero.Recovery.PlaylistMediaCategoryAdapters", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredPlaylistMediaRoutingTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false);
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false, NAME_None, nullptr, true, ERHIFeatureLevel::Num, &Initialization);
    if (!TestNotNull(TEXT("Create isolated media-routing world"), World)) return false;
    FWorldContext& Context = GEngine->CreateNewWorldContext(EWorldType::Game); Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { GEngine->DestroyWorldContext(World); World->DestroyWorld(false); };
    World->InitializeActorsForPlay(FURL());
    auto* Manager = World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Spawn real playlist event consumer"), Manager)) return false;
    Manager->MediaDeckState = NewObject<URecoveredDeckState>(Manager);
    auto AddEntry = [](TArray<FRecoveredMediaEntry>& Deck, const TCHAR* File) { auto& Entry = Deck.AddDefaulted_GetRef(); Entry.File = File; Entry.FullPath = File; };
    AddEntry(Manager->MediaDeckState->Child.Cum, TEXT("cum-deck-fixture.png"));
    AddEntry(Manager->MediaDeckState->Child.Ass, TEXT("ass-deck-fixture.png"));
    AddEntry(Manager->MediaDeckState->Child.Boobs, TEXT("boobs-deck-fixture.png"));
    const TCHAR* Categories[] = {TEXT("cum"), TEXT("ass"), TEXT("boobs")};
    const TCHAR* ExpectedFiles[] = {TEXT("cum-deck-fixture.png"), TEXT("ass-deck-fixture.png"), TEXT("boobs-deck-fixture.png")};
    for (int32 I = 0; I < 3; ++I) {
        FRecoveredBeatmapEvent Event; Event.Type = TEXT("media_change"); Event.Value = Categories[I];
        Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Event);
        TestEqual(TEXT("Native card category remains six, seven or eight"), Manager->BeatContext.CardType, static_cast<uint8>(I + 6));
        TestEqual(TEXT("Media event selects corresponding physical deck four, five or six"), Manager->SelectedRandomCard.File, FString(ExpectedFiles[I]));
        Manager->SelectedRandomCard.File = TEXT("selection-reset-sentinel");
        Event.Type = TEXT("cycle_media"); Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Event);
        TestEqual(TEXT("Cycle event uses same category adapter"), Manager->SelectedRandomCard.File, FString(ExpectedFiles[I]));
    }
    TestEqual(TEXT("Category selection does not consume cum deck"), Manager->MediaDeckState->Child.Cum.Num(), 1);
    TestEqual(TEXT("Category selection does not consume ass deck"), Manager->MediaDeckState->Child.Ass.Num(), 1);
    TestEqual(TEXT("Category selection does not consume boobs deck"), Manager->MediaDeckState->Child.Boobs.Num(), 1);
    FRecoveredBeatmapEvent Disable; Disable.Type = TEXT("disable_break"); Disable.Value = TEXT("start");
    Manager->PlaylistRuntime->bOnBreak = true;
    Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Disable);
    TestTrue(TEXT("Break-disabled section is retained during active break"), Manager->PlaylistRuntime->bBreakSectionDisabled);
    TestFalse(TEXT("Disabled section prevents item use"), Manager->PlayerVariables.bCanUseItems);
    Disable.Value = TEXT("end"); Manager->PlaylistRuntime->OnBeatmapEvent.Broadcast(Disable);
    TestFalse(TEXT("Explicit section end clears disabled state"), Manager->PlaylistRuntime->bBreakSectionDisabled);
    TestFalse(TEXT("Section end cannot override an active break's item gate"), Manager->PlayerVariables.bCanUseItems);
    return true;
}
#endif
