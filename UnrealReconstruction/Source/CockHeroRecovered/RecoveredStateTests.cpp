#include "RecoveredGameplay.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredStateFixtureTest, "CockHero.Recovery.StateTraceFixtures", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredStateFixtureTest::RunTest(const FString& Parameters) {
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *(FPaths::ProjectDir() / TEXT("RecoveryEvidence/state-rule-traces.json")))) {
        AddError(TEXT("Missing independently evaluated bytecode fixtures"));
        return false;
    }
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root)) return false;
    int32 Count = 0;
    for (const TSharedPtr<FJsonValue>& Entry : Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture = Entry->AsObject();
        const auto Inputs = Fixture->GetObjectField(TEXT("inputs"));
        const auto Writes = Fixture->GetObjectField(TEXT("writes"));
        const FString Function = Fixture->GetStringField(TEXT("function"));
        auto Input = [&](const TCHAR* Key) { return Inputs->GetNumberField(Key); };
        auto Expected = [&](const TCHAR* Key, double Previous) {
            double Value = Previous;
            Writes->TryGetNumberField(Key, Value);
            return Value;
        };
        const FString Label = FString::Printf(TEXT("Fixture %d %s"), Count, *Function);
        if (Function == TEXT("SetEdgingPaceModifier") || Function == TEXT("SetUserStrokeMultiplier")) {
            const bool Edge = Function == TEXT("SetEdgingPaceModifier");
            const TCHAR* Key = Edge ? TEXT("EdgePacingMultiplier") : TEXT("UserStrokeCountMultiplier");
            const uint8 Index = static_cast<uint8>(Input(Edge ? TEXT("GameInstance.CurrentSave.EdgePacingMultiplierEnum") : TEXT("GameInstance.CurrentSave.StrokeMultiplierEnum")));
            TestEqual(Label, URecoveredStateRuleLibrary::GetPreferenceMultiplier(Index, Input(Key)), Expected(Key, Input(Key)));
        } else if (Function == TEXT("DetermineComboType")) {
            const uint8 Previous = static_cast<uint8>(Input(TEXT("CurrentComboTypeEnum")));
            TestEqual(Label, URecoveredStateRuleLibrary::DetermineComboTier(static_cast<int32>(Input(TEXT("PlayerVariablesStruct.CurrentComboCount"))), Previous), static_cast<uint8>(Expected(TEXT("CurrentComboTypeEnum"), Previous)));
        } else if (Function == TEXT("SetMinimumBeatSpawnerInterval")) {
            FRecoveredDeviceState Devices;
            Devices.bLovense = Inputs->GetBoolField(TEXT("call:HasConnectedLovenseDevices"));
            Devices.bHandy = Inputs->GetBoolField(TEXT("call:IsHandyConnected"));
            Devices.bButtplugVibrators = Inputs->GetBoolField(TEXT("call:HasConnectedButtplugVibrators"));
            Devices.bButtplugStrokers = Inputs->GetBoolField(TEXT("call:HasConnectedButtplugStrokers"));
            Devices.bFullStrokePerBeat = Inputs->GetBoolField(TEXT("GameInstance.AdultToyManager.bButtplugFullStrokePerBeat"));
            double ExpectedInterval = 17.0;
            for (const auto& Effect : Fixture->GetArrayField(TEXT("external_effects"))) {
                const auto Object = Effect->AsObject();
                if (Object->GetStringField(TEXT("call")) == TEXT("SetMinimumBeatInterval")) ExpectedInterval = Object->GetArrayField(TEXT("arguments"))[0]->AsNumber();
            }
            TestEqual(Label, URecoveredStateRuleLibrary::GetMinimumBeatInterval(static_cast<uint8>(Input(TEXT("CurrentDifficulty"))), Devices, 17), ExpectedInterval);
        } else if (Function == TEXT("CalculateBeatPitch")) {
            const int32 Total = static_cast<int32>(Input(TEXT("call:GetTotalBeatsInQueue")));
            if (Total == 0) AddExpectedError(TEXT("Divide by zero: Divide_DoubleDouble"), EAutomationExpectedErrorFlags::Contains, 2);
            const auto Pitch = URecoveredStateRuleLibrary::CalculateBeatPitch(Total, static_cast<int32>(Input(TEXT("call:GetBeatsRemaining"))));
            TestEqual(Label + TEXT(" beat"), Pitch.BeatPitch, Expected(TEXT("BeatPitch"), 0));
            TestEqual(Label + TEXT(" voice"), Pitch.MoanPitch, Expected(TEXT("MoanPitch"), 0));
        } else if (Function == TEXT("AddCoins")) {
            FRecoveredPlayerVariables Player;
            Player.PlayerCoins = static_cast<int32>(Input(TEXT("PlayerVariablesStruct.PlayerCoins")));
            Player.CoinEarnMultiplier = Input(TEXT("PlayerVariablesStruct.CoinEarnMultiplier"));
            URecoveredStateRuleLibrary::AddCoinsToState(Player, static_cast<int32>(Input(TEXT("CoinAdd"))));
            TestEqual(Label, Player.PlayerCoins, static_cast<int32>(Expected(TEXT("PlayerVariablesStruct.PlayerCoins"), 0)));
        } else if (Function == TEXT("AddToCumMeter")) {
            TestEqual(Label, URecoveredStateRuleLibrary::AddToCumMeter(Input(TEXT("CumMeterPercentage")), Input(TEXT("Percentage (0-1.0)"))), Expected(TEXT("CumMeterPercentage"), 0));
        } else if (Function == TEXT("AddToLootBar")) {
            TestEqual(Label, URecoveredStateRuleLibrary::AddToLootBar(Input(TEXT("LootBarPercentage")), Input(TEXT("Add (0.0-1.0)")), Input(TEXT("LootBarMultiplier"))), Expected(TEXT("LootBarPercentage"), 0));
        } else {
            AddError(TEXT("Unsupported recovered fixture: ") + Function);
        }
        ++Count;
    }
    TestEqual(TEXT("All source cases covered"), Count, 170);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredMetricOrderTest, "CockHero.Recovery.MetricOrdering", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredMetricOrderTest::RunTest(const FString& Parameters) {
    FRecoveredPlayerVariables Player;
    FRecoveredSessionStats Stats;
    URecoveredStateRuleLibrary::AdvanceSessionDuration(Player, Stats, 70.0);
    TestEqual(TEXT("First high-heat tick is excluded from its precomputed percentage"), Stats.PercentTimeAtHighHeat, 0);
    TestEqual(TEXT("High heat threshold includes 70"), Stats.TimeAtHighHeat, 1);
    URecoveredStateRuleLibrary::AdvanceSessionDuration(Player, Stats, 70.0);
    TestEqual(TEXT("Second tick uses previous high-heat time"), Stats.PercentTimeAtHighHeat, 50);
    URecoveredStateRuleLibrary::AdvanceSessionDuration(Player, Stats, 69.99);
    TestEqual(TEXT("Percent truncates"), Stats.PercentTimeAtHighHeat, 66);
    TestEqual(TEXT("Below-threshold tick adds no high-heat time"), Stats.TimeAtHighHeat, 2);
    TestEqual(TEXT("Player duration is separate from native stats duration"), Stats.SessionDuration, 0);
    URecoveredStateRuleLibrary::RecordSessionMetric(Stats, ERecoveredMetric::MaxCombo, 100);
    URecoveredStateRuleLibrary::RecordSessionMetric(Stats, ERecoveredMetric::MaxCombo, 50);
    TestEqual(TEXT("Maximum metric never decreases"), Stats.MaxCombo, 100);
    URecoveredStateRuleLibrary::RecordSessionMetric(Stats, ERecoveredMetric::PercentAtHighHeat, 10);
    URecoveredStateRuleLibrary::RecordSessionMetric(Stats, ERecoveredMetric::PercentAtHighHeat, 20);
    TestEqual(TEXT("Percentage recording replaces instead of adding"), Stats.PercentTimeAtHighHeat, 20);
    Stats.Strokes = MAX_int32;
    URecoveredStateRuleLibrary::RecordSessionMetric(Stats, ERecoveredMetric::Strokes, 1);
    TestEqual(TEXT("Int32 arithmetic follows the Windows binary's wrap"), Stats.Strokes, MIN_int32);
    URecoveredStateRuleLibrary::SetSessionMetric(Stats, ERecoveredMetric::EdgeStreak, 20);
    URecoveredStateRuleLibrary::SetSessionMetric(Stats, ERecoveredMetric::EdgeStreak, 10);
    TestEqual(TEXT("Set maximum metric is also monotonic"), Stats.EdgeStreak, 20);
    return true;
}
#endif
