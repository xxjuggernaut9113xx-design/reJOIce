#include "RecoveredDecks.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredCardTest,"CockHero.Recovery.CardTimingAndDeckRefill",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredCardTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/card-timing-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Inputs=Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes=Fixture->GetObjectField(TEXT("writes"));
        const auto Timing=URecoveredCardRuleLibrary::CalculateCardTiming(Inputs->GetNumberField(TEXT("call:RandomIntegerInRange")),Inputs->GetNumberField(TEXT("call:RandomFloatInRange")),Inputs->GetNumberField(TEXT("StrokeCountMultiplier")),Inputs->GetNumberField(TEXT("GlobalManager.UserStrokeCountMultiplier")),Inputs->GetNumberField(TEXT("TimeSpeedMultiplier")));
        TestEqual(FString::Printf(TEXT("Stroke trace %d"),Count),Timing.StrokeCount,static_cast<int32>(Writes->GetNumberField(TEXT("GlobalManager.PlayerVariablesStruct.CurrentStrokeCount"))));
        TestEqual(FString::Printf(TEXT("Interval trace %d"),Count),Timing.BeatInterval,Writes->GetNumberField(TEXT("GlobalManager.PlayerVariablesStruct.BeatSpawnInterval")));
        ++Count;
    }
    TestEqual(TEXT("All numeric card traces"),Count,128);
    auto* Decks=NewObject<URecoveredDeckState>();
    FRecoveredMediaEntry First,Second,Selected;
    First.File=TEXT("first");Second.File=TEXT("second");
    Decks->Master.Slow={First,Second,First};
    Decks->SetChildDecks();
    TestTrue(TEXT("Draw first entry"),URecoveredDeckState::DrawAtIndex(Decks->Child.Slow,0,Selected));
    TestEqual(TEXT("Native RemoveItem removes all duplicates"),Decks->Child.Slow.Num(),1);
    Decks->ReplaceEmptyDecks();
    TestEqual(TEXT("Nonempty deck is not reset"),Decks->Child.Slow.Num(),1);
    URecoveredDeckState::DrawAtIndex(Decks->Child.Slow,0,Selected);
    Decks->ReplaceEmptyDecks();
    TestEqual(TEXT("Exhausted deck refills"),Decks->Child.Slow.Num(),3);
    TestEqual(TEXT("Master remains intact"),Decks->Master.Slow.Num(),3);
    TestFalse(TEXT("Invalid selection guarded"),URecoveredDeckState::DrawAtIndex(Decks->Child.Slow,99,Selected));
    return true;
}
#endif
