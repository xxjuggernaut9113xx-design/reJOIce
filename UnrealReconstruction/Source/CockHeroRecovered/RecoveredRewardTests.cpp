#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredRewards.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredRewardTest,"CockHero.Recovery.NativeRewardAndCardBoundaries",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredRewardTest::RunTest(const FString& Parameters) {
    auto* Manager=NewObject<URecoveredProgressionManager>();
    auto* Table=NewObject<UDataTable>(); Table->RowStruct=FRecoveredPlayerCardRow::StaticStruct();
    FRecoveredPlayerCardRow Row; Row.CardID=TEXT("NativeCard"); Row.RequiredLevel=999;
    Table->AddRow(TEXT("UnrelatedRowName"),Row); Manager->PlayerCardDataTable=Table;
    TestFalse(TEXT("None card is rejected"),Manager->UnlockPlayerCard(NAME_None));
    TestFalse(TEXT("Unknown card is rejected"),Manager->UnlockPlayerCard(TEXT("Unknown")));
    TestTrue(TEXT("Lookup uses CardID and native FName case semantics"),Manager->UnlockPlayerCard(TEXT("nativecard")));
    TestFalse(TEXT("Already unlocked card is rejected"),Manager->UnlockPlayerCard(TEXT("NativeCard")));
    TestEqual(TEXT("Card added once"),Manager->UnlockedPlayerCards.Num(),1);
    TArray<FRecoveredReward> Rewards;
    for (const int32 Value:{-1,0,120}) {
        FRecoveredReward XP; XP.RewardType=TEXT("XP"); XP.Value=Value; Rewards.Add(XP);
        FRecoveredReward Points; Points.RewardType=TEXT("ECHRewardType::UnlockPoints"); Points.Value=Value; Rewards.Add(Points);
    }
    URecoveredRewardLibrary::GrantRecoveredRewards(Manager,Rewards);
    TestEqual(TEXT("Positive XP uses native level thresholds"),Manager->CurrentLevel,2);
    TestEqual(TEXT("Native XP remainder"),Manager->CurrentXP,20);
    TestEqual(TEXT("Nonpositive XP grants ignored"),Manager->TotalXPEarned,120);
    TestEqual(TEXT("Nonpositive point grants ignored"),Manager->UnlockPoints,120);
    auto* EmptyManager=NewObject<URecoveredProgressionManager>();
    TestFalse(TEXT("Missing card table is rejected"),EmptyManager->UnlockPlayerCard(TEXT("NativeCard")));
    Manager->ModifierDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Modifiers.DT_Modifiers"));
    if (TestNotNull(TEXT("Recovered modifier table"),Manager->ModifierDataTable.Get())) {
        TestEqual(TEXT("All byte-verified modifier rows restored"),Manager->ModifierDataTable->GetRowMap().Num(),16);
        TestTrue(TEXT("Modifier lookup compares the displayed title ignoring case"),Manager->UnlockModifier(TEXT("slow and steady")));
        TestFalse(TEXT("Already unlocked modifier is rejected"),Manager->UnlockModifier(TEXT("Slow and Steady")));
        TestFalse(TEXT("Spaces in modifier titles remain significant"),Manager->UnlockModifier(TEXT("SlowandSteady")));
        for (const auto& Pair:Manager->ModifierDataTable->GetRowMap()) {
            const auto* Modifier=reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value);
            TestNotNull(*Modifier->ModifierTitle.ToString(),Modifier->ModifierIcon.Get());
        }
    }
    URecoveredRewardLibrary::GrantRecoveredRewards(nullptr,Rewards);
    return true;
}
#endif
