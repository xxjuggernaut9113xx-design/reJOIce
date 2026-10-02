#include "RecoveredBeatTimeline.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBeatModifierTest,"CockHero.Recovery.NativeBeatModifierFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredBeatModifierTest::RunTest(const FString& Parameters) {
    FString Text; TSharedPtr<FJsonObject> Evidence;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/beat-modifier-traces.json"))) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) { AddError(TEXT("Missing beat modifier evidence")); return false; }
    int32 Count=0;
    auto Entry=[](const TSharedPtr<FJsonObject>& Value) {
        FRecoveredBeatEvent Beat;
        Beat.AbsoluteFireTime=Value->GetNumberField(TEXT("AbsoluteFireTime"));
        Beat.TargetHitTime=Value->GetNumberField(TEXT("TargetHitTime"));
        Beat.PatternIndex=int32(Value->GetNumberField(TEXT("PatternIndex")));
        Beat.Interval=Value->GetNumberField(TEXT("Interval"));
        Beat.BeatNumber=int32(Value->GetNumberField(TEXT("BeatNumber")));
        Beat.CustomMultiplier=float(Value->GetNumberField(TEXT("CustomMultiplier")));
        return Beat;
    };
    for(const auto& Item:Evidence->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Item->AsObject(); FRecoveredBeatPattern Pattern;
        for(const auto& Value:Fixture->GetArrayField(TEXT("multipliers"))) Pattern.IntervalMultipliers.Add(Value->AsNumber());
        TArray<FRecoveredBeatEvent> Queue;
        for(const auto& Value:Fixture->GetArrayField(TEXT("input_queue"))) Queue.Add(Entry(Value->AsObject()));
        TestTrue(TEXT("Rebuild native future entries"),URecoveredBeatTimeline::RebuildFutureQueue(Pattern,Fixture->GetNumberField(TEXT("base_interval")),float(Fixture->GetNumberField(TEXT("speed"))),
            Fixture->GetNumberField(TEXT("travel_time")),Fixture->GetNumberField(TEXT("minimum_interval")),Fixture->GetNumberField(TEXT("current_time")),
            int32(Fixture->GetNumberField(TEXT("fired_entries"))),int32(Fixture->GetNumberField(TEXT("future_entries"))),Queue));
        const auto& Expected=Fixture->GetArrayField(TEXT("queue"));
        TestEqual(TEXT("Future entry count includes rests"),Queue.Num(),Expected.Num());
        for(int32 I=0;I<FMath::Min(Queue.Num(),Expected.Num());++I) {
            auto Beat=Entry(Expected[I]->AsObject()); const auto& Actual=Queue[I];
            TestEqual(TEXT("Fire time"),Actual.AbsoluteFireTime,Beat.AbsoluteFireTime);
            TestEqual(TEXT("Target time"),Actual.TargetHitTime,Beat.TargetHitTime);
            TestEqual(TEXT("Interval"),Actual.Interval,Beat.Interval);
            TestEqual(TEXT("Pattern index"),Actual.PatternIndex,Beat.PatternIndex);
            TestEqual(TEXT("Beat number"),Actual.BeatNumber,Beat.BeatNumber);
            TestEqual(TEXT("Signed multiplier"),Actual.CustomMultiplier,Beat.CustomMultiplier);
        }
        ++Count;
    }
    TestEqual(TEXT("All source pattern rebuilds covered"),Count,1674);
    FRecoveredBeatPattern Pattern; Pattern.IntervalMultipliers={-1,1};
    auto* Timeline=NewObject<URecoveredBeatTimeline>();
    TestTrue(TEXT("Begin modifier timeline"),Timeline->StartPattern(Pattern,0.25,2,1,2));
    Timeline->AdvanceTo(0); // First entry is a rest; next fire advances without completing a stroke.
    TestTrue(TEXT("Speed change preserves future count"),Timeline->ApplySpeedModifier(5));
    TestEqual(TEXT("Speed retains original total strokes"),Timeline->TotalStrokes,2);
    TestTrue(TEXT("Stroke modifier multiplies entries"),Timeline->ApplyStrokeCountModifier(10));
    TestEqual(TEXT("Native revised total includes rests"),Timeline->TotalStrokes,31);
    Timeline->PauseSequence();
    TestFalse(TEXT("Paused speed changes ignored"),Timeline->ApplySpeedModifier(2));
    TestFalse(TEXT("Paused count changes ignored"),Timeline->ApplyStrokeCountModifier(2));
    return true;
}
#endif
