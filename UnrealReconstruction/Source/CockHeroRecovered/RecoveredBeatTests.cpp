#include "RecoveredBeatTimeline.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBeatQueueTest, "CockHero.Recovery.NativeBeatQueueFixtures", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredBeatQueueTest::RunTest(const FString& Parameters) {
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *(FPaths::ProjectDir() / TEXT("RecoveryEvidence/beat-queue-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root)) return false;
    int32 Count = 0;
    for (const auto& Item : Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture = Item->AsObject();
        FRecoveredBeatPattern Pattern;
        for (const auto& Multiplier : Fixture->GetArrayField(TEXT("multipliers"))) Pattern.IntervalMultipliers.Add(Multiplier->AsNumber());
        TArray<FRecoveredBeatEvent> Queue;
        FString Error;
        const FString Label = FString::Printf(TEXT("Queue %d"), Count);
        TestTrue(Label, URecoveredBeatTimeline::BuildBeatQueue(Pattern, Fixture->GetNumberField(TEXT("base_interval")), Fixture->GetNumberField(TEXT("stroke_count")), Fixture->GetNumberField(TEXT("speed")), Fixture->GetNumberField(TEXT("travel_time")), Fixture->GetNumberField(TEXT("minimum_interval")), Queue, Error));
        const auto& Expected = Fixture->GetArrayField(TEXT("queue"));
        TestEqual(Label + TEXT(" entries"), Queue.Num(), Expected.Num());
        for (int32 Index = 0; Index < FMath::Min(Queue.Num(), Expected.Num()); ++Index) {
            const auto Entry = Expected[Index]->AsObject();
            TestEqual(Label + TEXT(" fire"), Queue[Index].AbsoluteFireTime, Entry->GetNumberField(TEXT("AbsoluteFireTime")));
            TestEqual(Label + TEXT(" hit"), Queue[Index].TargetHitTime, Entry->GetNumberField(TEXT("TargetHitTime")));
            TestEqual(Label + TEXT(" interval"), Queue[Index].Interval, Entry->GetNumberField(TEXT("Interval")));
            TestEqual(Label + TEXT(" pattern"), Queue[Index].PatternIndex, static_cast<int32>(Entry->GetNumberField(TEXT("PatternIndex"))));
            TestEqual(Label + TEXT(" beat"), Queue[Index].BeatNumber, static_cast<int32>(Entry->GetNumberField(TEXT("BeatNumber"))));
            TestEqual(Label + TEXT(" multiplier"), Queue[Index].CustomMultiplier, static_cast<float>(Entry->GetNumberField(TEXT("CustomMultiplier"))));
        }
        ++Count;
    }
    TestEqual(TEXT("All recovered pattern queues covered"), Count, 186);
    FRecoveredBeatPattern Pattern;
    Pattern.IntervalMultipliers = {-1,1};
    auto* Timeline = NewObject<URecoveredBeatTimeline>();
    TestTrue(TEXT("Start timeline"), Timeline->StartPattern(Pattern, 0.25, 2, 1, 2));
    Timeline->AdvanceTo(2);
    TestEqual(TEXT("Rest does not complete a stroke"), Timeline->CompletedBeats, 0);
    Timeline->AdvanceTo(2.25);
    TestEqual(TEXT("Positive entry completes stroke"), Timeline->CompletedBeats, 1);
    TestEqual(TEXT("Remaining counts positive strokes"), Timeline->GetBeatsRemaining(), 1);
    Timeline->PauseSequence();
    Timeline->AdvanceTo(100);
    TestEqual(TEXT("Paused timeline does not dispatch"), Timeline->CompletedBeats, 1);
    Timeline->ResumeSequence();
    Timeline->AdvanceTo(2.75);
    TestEqual(TEXT("Resumed timeline completes"), Timeline->CompletedBeats, 2);
    TestFalse(TEXT("Completed timeline stops"), Timeline->bIsRunning);
    Pattern.IntervalMultipliers = {-1,-2};
    TArray<FRecoveredBeatEvent> Queue;
    FString Error;
    TestFalse(TEXT("Reject all-rest input instead of native infinite loop"), URecoveredBeatTimeline::BuildBeatQueue(Pattern,0.25,2,1,2,0.01,Queue,Error));
    return true;
}
#endif
