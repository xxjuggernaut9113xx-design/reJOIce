#include "RecoveredOutcomes.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredOutcomeTest,"CockHero.Recovery.OutcomeInstructionFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredOutcomeTest::RunTest(const FString& Parameters) {
    FString Text; TSharedPtr<FJsonObject> Root;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/outcome-traces.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject(); const auto Trace=Fixture->GetObjectField(TEXT("trace")); const auto Input=Trace->GetObjectField(TEXT("inputs")); const auto Writes=Trace->GetObjectField(TEXT("writes"));
        FRecoveredPlayerVariables Player; FRecoveredSessionStats Stats;
        Player.CurrentComboCount=Input->GetNumberField(TEXT("PlayerVariablesStruct.CurrentComboCount")); Player.EdgeStreak=Input->GetNumberField(TEXT("PlayerVariablesStruct.EdgeStreak"));
        Player.bCanDraw=Input->GetBoolField(TEXT("PlayerVariablesStruct.CanDraw?")); Player.bHasCame=Input->GetBoolField(TEXT("PlayerVariablesStruct.HasCame?")); Player.bCanUseItems=Input->GetBoolField(TEXT("PlayerVariablesStruct.CanUseItems?"));
        for(const auto& Item:Input->GetArrayField(TEXT("PlayerVariablesStruct.BrokenComboArray"))) Player.BrokenComboArray.Add(int32(Item->AsNumber()));
        uint8 CardType=Input->GetNumberField(TEXT("CurrentCardTypeEnum"));
        const auto Effects=URecoveredOutcomeLibrary::ApplyOutcome(Player,Stats,CardType,Fixture->GetStringField(TEXT("event"))==TEXT("SuccessfulCum"),Input->GetBoolField(TEXT("HasTaunted?")),Input->GetBoolField(TEXT("modifier:Iron Man")));
        TestEqual(TEXT("Source outcome card type"),CardType,uint8(Writes->GetNumberField(TEXT("CurrentCardTypeEnum"))));
        TestEqual(TEXT("Source outcome combo reset"),Player.CurrentComboCount,int32(Writes->GetNumberField(TEXT("PlayerVariablesStruct.CurrentComboCount"))));
        TestEqual(TEXT("Source outcome streak reset"),Player.EdgeStreak,int32(Writes->GetNumberField(TEXT("PlayerVariablesStruct.EdgeStreak"))));
        TestEqual(TEXT("Source outcome item gate"),Player.bCanUseItems,Writes->GetBoolField(TEXT("PlayerVariablesStruct.CanUseItems?")));
        TestEqual(TEXT("Source outcome draw gate"),Player.bCanDraw,Writes->GetBoolField(TEXT("PlayerVariablesStruct.CanDraw?")));
        TestEqual(TEXT("Source outcome completion flag"),Player.bHasCame,Writes->GetBoolField(TEXT("PlayerVariablesStruct.HasCame?")));
        const auto& History=Writes->GetArrayField(TEXT("PlayerVariablesStruct.BrokenComboArray"));
        TestEqual(TEXT("Source combo history count"),Player.BrokenComboArray.Num(),History.Num());
        for(int32 I=0;I<FMath::Min(Player.BrokenComboArray.Num(),History.Num());++I) TestEqual(TEXT("Source combo history values"),Player.BrokenComboArray[I],int32(History[I]->AsNumber()));
        TArray<ERecoveredMetric> ExpectedMetrics;
        bool Penalty=false,Clear=false,Delay=false; float DelaySeconds=0; int32 Overlay=0;
        for(const auto& CallValue:Trace->GetArrayField(TEXT("external_effects"))) {
            const auto Call=CallValue->AsObject(); const FString Name=Call->GetStringField(TEXT("call"));
            const TArray<TSharedPtr<FJsonValue>>* Args=nullptr; Call->TryGetArrayField(TEXT("arguments"),Args);
            if(Name==TEXT("UpdateMetric")) ExpectedMetrics.Add(ERecoveredMetric(uint8((*Args)[0]->AsNumber())));
            if(Name==TEXT("ApplyIronManPenalty")) Penalty=true;
            if(Name==TEXT("K2_ClearAndInvalidateTimerHandle")) Clear=true;
            if(Name==TEXT("Delay")) { Delay=true; DelaySeconds=(*Args)[1]->AsNumber(); }
            if(Name==TEXT("ApplySpeedModifier")) TestEqual(TEXT("Source outcome speed request"),Effects.SpeedModifier,float((*Args)[0]->AsNumber()));
            if(Name==TEXT("ApplyStrokeCountModifier")) TestEqual(TEXT("Source outcome stroke modifier request"),Effects.StrokeCountModifier,int32((*Args)[0]->AsNumber()));
            if(Name==TEXT("Change Beat Background")) TestEqual(TEXT("Source outcome background"),Effects.BackgroundStyle,int32((*Args)[0]->AsNumber()));
            if(Name==TEXT("Create") && Overlay==0) Overlay=(*Args)[1]->AsNumber();
        }
        TestTrue(TEXT("Source outcome metric requests preserve order"),Effects.MetricRequests==ExpectedMetrics);
        TestEqual(TEXT("Source outcome overlay request"),Effects.OutcomeOverlaySourceIndex,Overlay);
        TestEqual(TEXT("Source Iron Man penalty request"),Effects.bApplyIronManPenalty,Penalty);
        TestEqual(TEXT("Source edge timer clear request"),Effects.bClearEdgeHoldTimer,Clear);
        TestEqual(TEXT("Source delayed continuation request"),Effects.bDelayedContinuationRequested,Delay);
        TestEqual(TEXT("Source continuation delay"),Effects.ContinuationDelay,DelaySeconds);
        TestFalse(TEXT("Outcome entry does not construct final bWon session field"),Stats.bWon);
        ++Count;
    }
    TestEqual(TEXT("All outcome entry traces"),Count,40);
    return true;
}
#endif
