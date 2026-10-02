#include "RecoveredEventRules.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredEventFilterTest,"CockHero.Recovery.EventFilterInstructionFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredEventFilterTest::RunTest(const FString& Parameters) {
    FString Text; TSharedPtr<FJsonObject> Root;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/event-filter-traces.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    TArray<FRecoveredEventRecord> Events;
    for(const auto& Value:Root->GetArrayField(TEXT("source_records"))) {
        const auto Record=Value->AsObject(); FRecoveredEventRecord Event;
        Event.EventName=Record->GetNumberField(TEXT("EventName")); Event.BaseWeight=Record->GetNumberField(TEXT("BaseWeight"));
        Event.WeightMultiplier=Record->GetNumberField(TEXT("WeightMultiplier")); Event.IsEligible=Record->GetBoolField(TEXT("IsEligible")); Event.IsOnCooldown=Record->GetBoolField(TEXT("IsOnCooldown")); Events.Add(Event);
    }
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject(); const auto Checks=Fixture->GetObjectField(TEXT("checks"));
        FRecoveredEligibilityState State; State.HeatCategory=0; State.bBrainMelterEnabled=Checks->GetBoolField(TEXT("Body"));
        State.Modifiers.Add(Checks->GetBoolField(TEXT("Succubus")) ? TEXT("Succufrenzy") : TEXT("Demon Proof"));
        State.Coins=200; State.bStoreOnCooldown=!Checks->GetBoolField(TEXT("Store"));
        const auto Result=URecoveredEventRuleLibrary::BuildEligibleEvents(Events,State);
        const auto& Expected=Fixture->GetObjectField(TEXT("trace"))->GetObjectField(TEXT("writes"))->GetArrayField(TEXT("EligibleSpecialEvents"));
        TestEqual(TEXT("Source filtered event count"),Result.Num(),Expected.Num());
        for(int32 I=0;I<FMath::Min(Result.Num(),Expected.Num());++I) {
            const auto Record=Expected[I]->AsObject();
            TestEqual(TEXT("Source filter retains order and duplicates"),Result[I].EventName,int32(Record->GetNumberField(TEXT("EventName"))));
            TestEqual(TEXT("Source filter preserves weight"),Result[I].BaseWeight,Record->GetNumberField(TEXT("BaseWeight")));
            TestEqual(TEXT("Source ignores record eligibility flag"),Result[I].IsEligible,Record->GetBoolField(TEXT("IsEligible")));
            TestEqual(TEXT("Source ignores record cooldown flag"),Result[I].IsOnCooldown,Record->GetBoolField(TEXT("IsOnCooldown")));
        }
        ++Count;
    }
    TestEqual(TEXT("All event filter branches"),Count,32);
    FRecoveredEligibilityState ShieldState; ShieldState.Shields=1; ShieldState.bShieldToggled=true; ShieldState.HeatCategory=0;
    FRecoveredEventRecord Succubus; Succubus.EventName=8;
    auto ShieldResult=URecoveredEventRuleLibrary::BuildEligibleEvents({Succubus,Succubus},ShieldState);
    TestEqual(TEXT("Repeated eligibility calls consume last shield before next duplicate"),ShieldResult.Num(),1);
    TestEqual(TEXT("One shield consumed"),ShieldState.ShieldsConsumed,1);
    TestEqual(TEXT("Source input records unchanged"),Events.Num(),34);
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/weight-pipeline-traces.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 WeightCount=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject(); FRecoveredEventRecord Event;
        Event.EventName=Fixture->GetNumberField(TEXT("EventName")); Event.BaseWeight=Fixture->GetNumberField(TEXT("BaseWeight"));
        const auto Result=URecoveredEventRuleLibrary::ApplyDrawEventWeights({Event},uint8(Fixture->GetNumberField(TEXT("HeatCategory"))),uint8(Fixture->GetNumberField(TEXT("ComboTier"))));
        const auto& Expected=Fixture->GetArrayField(TEXT("expected"));
        TestEqual(TEXT("Source weight-stage result count"),Result.Num(),Expected.Num());
        if(Result.Num()==1 && Expected.Num()==1) {
            TestEqual(TEXT("Source heat-then-combo weight"),Result[0].BaseWeight,Expected[0]->AsObject()->GetNumberField(TEXT("BaseWeight")));
            TestEqual(TEXT("Source weight-stage identity"),Result[0].EventName,int32(Expected[0]->AsObject()->GetNumberField(TEXT("EventName"))));
        }
        ++WeightCount;
    }
    TestEqual(TEXT("All composed weight traces"),WeightCount,768);
    TestEqual(TEXT("Original tier 6 appends no events"),URecoveredEventRuleLibrary::ApplyDrawEventWeights(Events,0,6).Num(),0);
    TestEqual(TEXT("Original tier 7 appends no events"),URecoveredEventRuleLibrary::ApplyDrawEventWeights(Events,0,7).Num(),0);
    return true;
}
#endif
