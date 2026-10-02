#include "RecoveredRules.h"
#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredRulesTest, "CockHero.Recovery.VerifiedRules", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredRulesTest::RunTest(const FString& Parameters) {
    const auto EasyMode = URecoveredRuleLibrary::GetDifficultyConfig(ERecoveredDifficulty::EasyMode);
    TestEqual(TEXT("EasyMode: DifficultyHeatGainMultiplier"), EasyMode.DifficultyHeatGainMultiplier, 0.5);
    TestEqual(TEXT("EasyMode: DifficultyCoinEarnMultiplier"), EasyMode.DifficultyCoinEarnMultiplier, 2.0);
    TestEqual(TEXT("EasyMode: DifficultyStrokeCounterMultiplier"), EasyMode.DifficultyStrokeCounterMultiplier, 0.5);
    TestEqual(TEXT("EasyMode: DifficultyStrokeSpeedMultiplier"), EasyMode.DifficultyStrokeSpeedMultiplier, 1.85);
    TestEqual(TEXT("EasyMode: PlayerVariablesStruct.CumMeterMultiplier"), EasyMode.CumMeterMultiplier, 8.0);
    TestEqual(TEXT("EasyMode: CumIncreaseItemSpawnChance"), EasyMode.CumIncreaseItemSpawnChance, 20.0);
    TestEqual(TEXT("EasyMode: DecreaseHeatItemSpawnChance"), EasyMode.DecreaseHeatItemSpawnChance, 40.0);
    TestEqual(TEXT("EasyMode: EdgeItemSpawnChance"), EasyMode.EdgeItemSpawnChance, 45.0);
    TestEqual(TEXT("EasyMode: BreakItemSpawnChance"), EasyMode.BreakItemSpawnChance, 35.0);
    TestEqual(TEXT("EasyMode: SlowdownItemSpawnChance"), EasyMode.SlowdownItemSpawnChance, 40.0);
    TestEqual(TEXT("EasyMode: BonerPillSpawnChance"), EasyMode.BonerPillSpawnChance, 75.0);
    TestEqual(TEXT("EasyMode: SuccuShieldSpawnChance"), EasyMode.SuccuShieldSpawnChance, 20.0);
    const auto NormalMode = URecoveredRuleLibrary::GetDifficultyConfig(ERecoveredDifficulty::NormalMode);
    TestEqual(TEXT("NormalMode: DifficultyHeatGainMultiplier"), NormalMode.DifficultyHeatGainMultiplier, 1.0);
    TestEqual(TEXT("NormalMode: DifficultyCoinEarnMultiplier"), NormalMode.DifficultyCoinEarnMultiplier, 1.0);
    TestEqual(TEXT("NormalMode: DifficultyStrokeCounterMultiplier"), NormalMode.DifficultyStrokeCounterMultiplier, 1.0);
    TestEqual(TEXT("NormalMode: DifficultyStrokeSpeedMultiplier"), NormalMode.DifficultyStrokeSpeedMultiplier, 1.0);
    TestEqual(TEXT("NormalMode: PlayerVariablesStruct.CumMeterMultiplier"), NormalMode.CumMeterMultiplier, 1.0);
    TestEqual(TEXT("NormalMode: CumIncreaseItemSpawnChance"), NormalMode.CumIncreaseItemSpawnChance, 8.0);
    TestEqual(TEXT("NormalMode: DecreaseHeatItemSpawnChance"), NormalMode.DecreaseHeatItemSpawnChance, 25.0);
    TestEqual(TEXT("NormalMode: EdgeItemSpawnChance"), NormalMode.EdgeItemSpawnChance, 15.0);
    TestEqual(TEXT("NormalMode: BreakItemSpawnChance"), NormalMode.BreakItemSpawnChance, 15.0);
    TestEqual(TEXT("NormalMode: SlowdownItemSpawnChance"), NormalMode.SlowdownItemSpawnChance, 15.0);
    TestEqual(TEXT("NormalMode: BonerPillSpawnChance"), NormalMode.BonerPillSpawnChance, 50.0);
    TestEqual(TEXT("NormalMode: SuccuShieldSpawnChance"), NormalMode.SuccuShieldSpawnChance, 10.0);
    const auto InsaneMode = URecoveredRuleLibrary::GetDifficultyConfig(ERecoveredDifficulty::InsaneMode);
    TestEqual(TEXT("InsaneMode: DifficultyHeatGainMultiplier"), InsaneMode.DifficultyHeatGainMultiplier, 3.0);
    TestEqual(TEXT("InsaneMode: DifficultyCoinEarnMultiplier"), InsaneMode.DifficultyCoinEarnMultiplier, 0.5);
    TestEqual(TEXT("InsaneMode: DifficultyStrokeCounterMultiplier"), InsaneMode.DifficultyStrokeCounterMultiplier, 2.0);
    TestEqual(TEXT("InsaneMode: DifficultyStrokeSpeedMultiplier"), InsaneMode.DifficultyStrokeSpeedMultiplier, 0.6);
    TestEqual(TEXT("InsaneMode: PlayerVariablesStruct.CumMeterMultiplier"), InsaneMode.CumMeterMultiplier, 0.5);
    TestEqual(TEXT("InsaneMode: CumIncreaseItemSpawnChance"), InsaneMode.CumIncreaseItemSpawnChance, 3.0);
    TestEqual(TEXT("InsaneMode: DecreaseHeatItemSpawnChance"), InsaneMode.DecreaseHeatItemSpawnChance, 10.0);
    TestEqual(TEXT("InsaneMode: EdgeItemSpawnChance"), InsaneMode.EdgeItemSpawnChance, 5.0);
    TestEqual(TEXT("InsaneMode: BreakItemSpawnChance"), InsaneMode.BreakItemSpawnChance, 5.0);
    TestEqual(TEXT("InsaneMode: SlowdownItemSpawnChance"), InsaneMode.SlowdownItemSpawnChance, 10.0);
    TestEqual(TEXT("InsaneMode: BonerPillSpawnChance"), InsaneMode.BonerPillSpawnChance, 35.0);
    TestEqual(TEXT("InsaneMode: SuccuShieldSpawnChance"), InsaneMode.SuccuShieldSpawnChance, 5.0);
    TestEqual(TEXT("Heat gain uses difficulty"), URecoveredRuleLibrary::CalculateHeat(10, 2, 3), 16.0);
    TestEqual(TEXT("Heat caps at 100"), URecoveredRuleLibrary::CalculateHeat(99, 2, 3), 100.0);
    TestEqual(TEXT("Heat floors at 0"), URecoveredRuleLibrary::CalculateHeat(1, -2, 3), 0.0);
    TestTrue(TEXT("Chance equality is inclusive"), URecoveredRuleLibrary::EvaluateChance(25, 25));
    TestFalse(TEXT("Chance rejects higher roll"), URecoveredRuleLibrary::EvaluateChance(25.01, 25));
    TestEqual(TEXT("Beat interval minimum"), URecoveredRuleLibrary::ClampBeatInterval(-1), 0.01f);
    TestEqual(TEXT("Beat interval preserved"), URecoveredRuleLibrary::ClampBeatInterval(0.5f), 0.5f);
    TestEqual(TEXT("Speed floor"), URecoveredRuleLibrary::ClampSpeedItemMultiplier(-1), 0.1f);
    TestEqual(TEXT("Speed ceiling"), URecoveredRuleLibrary::ClampSpeedItemMultiplier(10), 5.0f);
    return true;
}
#endif
