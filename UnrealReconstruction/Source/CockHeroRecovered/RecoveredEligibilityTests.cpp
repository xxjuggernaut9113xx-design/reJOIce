#include "RecoveredEventRules.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredEligibilityTest,"CockHero.Recovery.EligibilityTraceFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredEligibilityTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/eligibility-rule-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Inputs=Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes=Fixture->GetObjectField(TEXT("writes"));
        const FString Name=Fixture->GetStringField(TEXT("function"));
        FRecoveredEligibilityState State;
        bool Actual=false,Expected=false;
        if(Name==TEXT("StoreEventCheck")) {
            State.bStoreOnCooldown=Inputs->GetBoolField(TEXT("IsStoreOnCooldown"));
            State.Coins=Inputs->GetNumberField(TEXT("PlayerVariablesStruct.PlayerCoins"));
            Actual=URecoveredEventRuleLibrary::CheckStoreEligibility(State);
            Expected=Writes->GetBoolField(TEXT("StoreEligibilityReturn"));
        } else if(Name==TEXT("SuccubusEligibilityCheck")) {
            State.bCanSuccubiSpawn=Inputs->GetBoolField(TEXT("PlayerVariablesStruct.CanSuccubiSpawn?"));
            State.Combo=Inputs->GetNumberField(TEXT("PlayerVariablesStruct.CurrentComboCount"));
            State.HeatCategory=Inputs->GetNumberField(TEXT("HeatCategory"));
            if(Inputs->GetBoolField(TEXT("modifier:Demon Proof"))) State.Modifiers.Add(TEXT("Demon Proof"));
            if(Inputs->GetBoolField(TEXT("modifier:Succufrenzy"))) State.Modifiers.Add(TEXT("Succufrenzy"));
            Actual=URecoveredEventRuleLibrary::CheckSuccubusEligibility(State);
            Expected=Writes->GetBoolField(TEXT("IsEligibleReturn"));
        } else {
            State.bBrainMelterEnabled=Inputs->GetBoolField(TEXT("IsBrainMelterEnabled?"));
            State.HeatCategory=Inputs->GetNumberField(TEXT("HeatCategory"));
            Actual=URecoveredEventRuleLibrary::CheckBodyFrenzyEligibility(State);
            Expected=Writes->GetBoolField(TEXT("IsEligibleReturn"));
        }
        TestEqual(FString::Printf(TEXT("Eligibility source trace %d %s"),Count,*Name),Actual,Expected);
        ++Count;
    }
    TestEqual(TEXT("All source traces"),Count,74);
    return true;
}
#endif
