#include "RecoveredSession.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSessionTraceTest, "CockHero.Recovery.SessionTraceFixtures", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredSessionTraceTest::RunTest(const FString& Parameters) {
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *(FPaths::ProjectDir() / TEXT("RecoveryEvidence/session-rule-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root)) return false;
    int32 Count = 0;
    for (const auto& Item : Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture = Item->AsObject();
        const auto Inputs = Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes = Fixture->GetObjectField(TEXT("writes"));
        const FString Function = Fixture->GetStringField(TEXT("function"));
        const FString Label = FString::Printf(TEXT("Session fixture %d %s"), Count, *Function);
        auto Input = [&](const TCHAR* Key) { return Inputs->GetNumberField(Key); };
        auto Expected = [&](const TCHAR* Key, double Previous) { double Result = Previous; Writes->TryGetNumberField(Key, Result); return Result; };
        if (Function == TEXT("AddtoCumMeteronBeatComplete")) {
            FRecoveredPlayerVariables Player;
            Player.bHasCame = Inputs->GetBoolField(TEXT("PlayerVariablesStruct.HasCame?"));
            Player.CumMeterMultiplier = Input(TEXT("PlayerVariablesStruct.CumMeterMultiplier"));
            Player.ConsecutiveHighHeatDraws = Input(TEXT("PlayerVariablesStruct.ConsecutiveHighHeatDraws"));
            Player.TotalEdgeCount = Input(TEXT("PlayerVariablesStruct.TotalEdgeCount"));
            Player.CurrentComboCount = Input(TEXT("PlayerVariablesStruct.CurrentComboCount"));
            Player.SessionLength = Input(TEXT("PlayerVariablesStruct.SessionLength"));
            FRecoveredBeatContext Context;
            Context.CardType = Input(TEXT("CurrentCardTypeEnum"));
            for (const auto& Pair : Inputs->Values) {
                if (Pair.Key.StartsWith(TEXT("modifier:")) && Pair.Value->AsBool()) Context.ActiveModifiers.Add(Pair.Key.Mid(9));
            }
            double Base = Input(TEXT("BaseCumGain"));
            double Meter = Input(TEXT("CumMeterPercentage"));
            URecoveredSessionRuleLibrary::AddBeatMeter(Player, Context, Input(TEXT("Heat Level")), Base, Meter);
            TestEqual(Label + TEXT(" meter"), Meter, Expected(TEXT("CumMeterPercentage"), Input(TEXT("CumMeterPercentage"))));
            TestEqual(Label + TEXT(" base"), Base, Expected(TEXT("BaseCumGain"), Input(TEXT("BaseCumGain"))));
        } else if (Function == TEXT("Determine&CoinAdd")) {
            const auto& Effects = Fixture->GetArrayField(TEXT("external_effects"));
            const int32 Award = Effects.Num() ? Effects[0]->AsObject()->GetArrayField(TEXT("arguments"))[0]->AsNumber() : 0;
            TestEqual(Label, URecoveredSessionRuleLibrary::GetCoinAward(Input(TEXT("CurrentCardTypeEnum"))), Award);
        } else if (Function == TEXT("Determine&HeatAdd")) {
            FRecoveredBeatContext Context;
            Context.HeatCategory = Input(TEXT("HeatCategory"));
            Context.HighHeatAdd = Input(TEXT("HighCategory_HeatAdd"));
            Context.MediumHeatAdd = Input(TEXT("MedCategory_HeatAdd"));
            Context.SlowHeatAdd = Input(TEXT("SlowCategory_HeatAdd"));
            const auto& Effects = Fixture->GetArrayField(TEXT("external_effects"));
            const double Award = Effects.Num() ? Effects[0]->AsObject()->GetArrayField(TEXT("arguments"))[0]->AsNumber() : 0;
            TestEqual(Label, URecoveredSessionRuleLibrary::GetHeatAward(Context), Award);
        } else if (Function == TEXT("BreakCombo")) {
            FRecoveredPlayerVariables Player;
            Player.CurrentComboCount = Input(TEXT("PlayerVariablesStruct.CurrentComboCount"));
            Player.BrokenComboArray = {10,20};
            URecoveredSessionRuleLibrary::BreakCombo(Player);
            TestEqual(Label + TEXT(" count"), Player.CurrentComboCount, static_cast<int32>(Expected(TEXT("PlayerVariablesStruct.CurrentComboCount"), -1)));
            const auto& Array = Writes->GetArrayField(TEXT("PlayerVariablesStruct.BrokenComboArray"));
            TestEqual(Label + TEXT(" size"), Player.BrokenComboArray.Num(), Array.Num());
            for (int32 Index = 0; Index < Array.Num(); ++Index) TestEqual(Label + TEXT(" history"), Player.BrokenComboArray[Index], static_cast<int32>(Array[Index]->AsNumber()));
        } else AddError(TEXT("Unsupported session fixture"));
        ++Count;
    }
    TestEqual(TEXT("All session source cases tested"), Count, 146);
    return true;
}
#endif
