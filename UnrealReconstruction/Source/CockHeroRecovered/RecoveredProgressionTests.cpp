#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredXPTest,"CockHero.Recovery.NativeXPInstructionFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredXPTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/native-xp-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject();
        const auto Input=Fixture->GetObjectField(TEXT("stats"));
        FRecoveredSessionStats Stats;
        Stats.Strokes=Input->GetNumberField(TEXT("Strokes"));
        Stats.SessionDuration=Input->GetNumberField(TEXT("SessionDuration"));
        Stats.Edges=Input->GetNumberField(TEXT("Edges"));
        Stats.EnemiesDefeated=Input->GetNumberField(TEXT("EnemiesDefeated"));
        Stats.bWon=Input->GetBoolField(TEXT("bWon"));
        for(const auto& Tag:Input->GetArrayField(TEXT("ActiveModifiers"))) Stats.ActiveModifiers.Add(Tag->AsString());
        TestEqual(FString::Printf(TEXT("Native XP trace %d"),Count),URecoveredProgressionLibrary::CalculateSessionXP(Stats,FRecoveredXPSettings()),static_cast<int32>(Fixture->GetNumberField(TEXT("expected_xp"))));
        ++Count;
    }
    TestEqual(TEXT("All native XP cases"),Count,4200);
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredLevelTest,"CockHero.Recovery.NativeLevelInstructionFixtures",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredLevelTest::RunTest(const FString& Parameters) {
    FString Text;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/native-level-traces.json")))) return false;
    TSharedPtr<FJsonObject> Root;
    if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)) return false;
    auto* Table=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_LevelData.DT_LevelData"));
    if(!TestNotNull(TEXT("Source level data table"),Table)) return false;
    TestEqual(TEXT("Original level rows retained"),Table->GetRowNames().Num(),20);
    TestTrue(TEXT("Original table has no Level_2 reward row"),!Table->GetRowNames().Contains(TEXT("Level_2")));
    const auto& Requirements=Root->GetArrayField(TEXT("thresholds"));
    for(int32 Level=-1;Level<=21;++Level) {
        const int32 Expected=Level>0 && Level<=20 ? int32(Requirements[Level-1]->AsNumber()) : 999999;
        TestEqual(TEXT("Native threshold lookup"),URecoveredProgressionLibrary::GetXPForNextLevel(Level),Expected);
    }
    auto* Manager=NewObject<URecoveredProgressionManager>();
    int32 Count=0;
    for(const auto& Value:Root->GetArrayField(TEXT("fixtures"))) {
        const auto Fixture=Value->AsObject(); const auto Input=Fixture->GetObjectField(TEXT("input")); const auto Expected=Fixture->GetObjectField(TEXT("expected"));
        Manager->CurrentLevel=Input->GetNumberField(TEXT("CurrentLevel"));
        Manager->CurrentXP=Input->GetNumberField(TEXT("CurrentXP"));
        Manager->TotalXPEarned=Input->GetNumberField(TEXT("TotalXPEarned"));
        Manager->UnlockPoints=Input->GetNumberField(TEXT("UnlockPoints"));
        Manager->LevelDataTable=Input->GetBoolField(TEXT("TableEnabled")) ? Table : nullptr;
        Manager->AddXP(int32(Input->GetNumberField(TEXT("Amount"))),TEXT("Static native trace"));
        TestEqual(TEXT("Native level result"),Manager->CurrentLevel,int32(Expected->GetNumberField(TEXT("CurrentLevel"))));
        TestEqual(TEXT("Native XP remainder"),Manager->CurrentXP,int32(Expected->GetNumberField(TEXT("CurrentXP"))));
        TestEqual(TEXT("Native lifetime XP"),Manager->TotalXPEarned,int32(Expected->GetNumberField(TEXT("TotalXPEarned"))));
        TestEqual(TEXT("Native unlock points"),Manager->UnlockPoints,int32(Expected->GetNumberField(TEXT("UnlockPoints")))); ++Count;
        TestEqual(TEXT("Native single-precision level progress"),URecoveredProgressionLibrary::CalculateLevelProgress(Manager->CurrentXP,Manager->CurrentLevel),float(Expected->GetNumberField(TEXT("LevelProgress"))));
    }
    TestEqual(TEXT("All native level cases"),Count,2240);
    // A deliberately renamed editable row verifies reward lookup without silently renaming source rows.
    auto* NamedTable=NewObject<UDataTable>(); NamedTable->RowStruct=FRecoveredLevelRow::StaticStruct();
    FRecoveredLevelRow Reward; Reward.Level=2; Reward.XPRequired=9999; Reward.UnlockPointsReward=5;
    NamedTable->AddRow(TEXT("Level_2"),Reward);
    Manager->CurrentLevel=1; Manager->CurrentXP=0; Manager->TotalXPEarned=0; Manager->UnlockPoints=0; Manager->LevelDataTable=NamedTable;
    Manager->AddXP(100,TEXT("Renamed row test"));
    TestEqual(TEXT("Native thresholds ignore table XPRequired"),Manager->CurrentLevel,2);
    TestEqual(TEXT("Matching native reward name grants points"),Manager->UnlockPoints,5);
    Manager->UnlockPoints=MAX_int32; Manager->AddUnlockPoints(1);
    TestEqual(TEXT("Unlock point arithmetic wraps"),Manager->UnlockPoints,MIN_int32);
    return true;
}
#endif
