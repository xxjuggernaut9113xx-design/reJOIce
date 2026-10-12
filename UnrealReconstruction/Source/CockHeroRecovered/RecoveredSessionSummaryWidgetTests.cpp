#include "RecoveredSessionSummaryWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "Sound/SoundWave.h"
#include "UObject/UnrealType.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSessionSummaryWidgetContractTest, "CockHero.Recovery.SessionSummaryWidgetContract", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredSessionSummaryWidgetContractTest::RunTest(const FString& Parameters) {
    UClass* Class = LoadClass<URecoveredSessionSummaryWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_SessionSummaryWidget.WBP_SessionSummaryWidget_C"));
    if (!TestNotNull(TEXT("Session summary recovered class"), Class)) return false;
    if (!TestTrue(TEXT("Session summary uses native recovery parent"), Class->IsChildOf(URecoveredSessionSummaryWidget::StaticClass()))) return false;

    const auto Initialization = UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false, NAME_None, nullptr, true, ERHIFeatureLevel::Num, &Initialization);
    FWorldContext& Context = GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    World->InitializeActorsForPlay(FURL());

    URecoveredSessionSummaryWidget* Widget = CreateWidget<URecoveredSessionSummaryWidget>(World, Class);
    if (!TestNotNull(TEXT("Session summary instantiates"), Widget)) return false;
    Widget->TakeWidget();

    const TCHAR* AnimationNames[] = {
        TEXT("BeginDisplay"), TEXT("PatreonHover"), TEXT("PatreonUnhover"), TEXT("PatreonClick"),
        TEXT("DiscordHover"), TEXT("DiscordUnhover"), TEXT("DiscordClick"),
        TEXT("TwitterHover"), TEXT("TwitterUnhover"), TEXT("TwitterClick")
    };
    for (const TCHAR* AnimationName : AnimationNames) {
        TestNotNull(FString(TEXT("Source summary animation ")) + AnimationName, FindFProperty<FObjectPropertyBase>(Class, FName(AnimationName)));
    }

    struct FVoiceArrayExpectation {
        const TCHAR* PropertyName;
        const TCHAR* AssetPrefix;
        int32 Count;
    };
    const FVoiceArrayExpectation VoiceArrays[] = {
        {TEXT("VillainessPostGameVictoryLines"), TEXT("VillainessPostGameVictory"), 8},
        {TEXT("VillainessPostGameDefeatLines"), TEXT("VillainessPostGameDefeat"), 8},
        {TEXT("BratPostGameVictoryLines"), TEXT("BratPostGameVictory"), 7},
        {TEXT("BratPostGameDefeatLines"), TEXT("BratPostGameDefeat"), 8},
        {TEXT("DommyMommyPostGameVictoryLines"), TEXT("DommyMommyPostGameVictory"), 10},
        {TEXT("DommyMommyPostGameDefeatLines"), TEXT("DommyMommyPostGameDefeat"), 10},
        {TEXT("SweetheartPostGameVictoryLines"), TEXT("SweetheartPostGameVictory"), 10},
        {TEXT("SweetheartPostGameDefeatLines"), TEXT("SweetheartPostGameDefeat"), 9},
    };
    for (const FVoiceArrayExpectation& VoiceArray : VoiceArrays) {
        FArrayProperty* Property = FindFProperty<FArrayProperty>(Class, FName(VoiceArray.PropertyName));
        if (!TestNotNull(FString(TEXT("Source post-game voice route ")) + VoiceArray.PropertyName, Property)) continue;
        FObjectPropertyBase* Inner = CastField<FObjectPropertyBase>(Property->Inner);
        if (!TestNotNull(FString(TEXT("Source post-game voice object type ")) + VoiceArray.PropertyName, Inner)) continue;
        FScriptArrayHelper Lines(Property, Property->ContainerPtrToValuePtr<void>(Widget));
        TestEqual(FString(TEXT("Source post-game voice count ")) + VoiceArray.PropertyName, Lines.Num(), VoiceArray.Count);
        for (int32 Index = 0; Index < Lines.Num(); ++Index) {
            USoundWave* Sound = Cast<USoundWave>(Inner->GetObjectPropertyValue(Lines.GetRawPtr(Index)));
            if (!TestNotNull(FString::Printf(TEXT("Recovered source post-game voice %s %d"), VoiceArray.PropertyName, Index + 1), Sound)) continue;
            TestEqual(FString::Printf(TEXT("Recovered source post-game voice name %s %d"), VoiceArray.PropertyName, Index + 1), Sound->GetName(), FString::Printf(TEXT("%s%02d"), VoiceArray.AssetPrefix, Index + 1));
            TArray<uint8> PCM;
            uint32 SampleRate = 0;
            uint16 ChannelCount = 0;
            TestTrue(FString::Printf(TEXT("Recovered source post-game PCM %s %d"), VoiceArray.PropertyName, Index + 1), Sound->GetImportedSoundWaveData(PCM, SampleRate, ChannelCount));
            TestEqual(FString::Printf(TEXT("Recovered source post-game voice rate %s %d"), VoiceArray.PropertyName, Index + 1), static_cast<int32>(SampleRate), 44100);
            TestEqual(FString::Printf(TEXT("Recovered source post-game voice channels %s %d"), VoiceArray.PropertyName, Index + 1), static_cast<int32>(ChannelCount), 2);
            TestTrue(FString::Printf(TEXT("Recovered source post-game PCM bytes %s %d"), VoiceArray.PropertyName, Index + 1), PCM.Num() > 0);
        }
    }

    FRecoveredSessionRewardData BootstrapRewardData;
    Widget->InitializeRecoveredSummary(BootstrapRewardData, false);

    const TCHAR* Buttons[] = {TEXT("ReturnToMenu"), TEXT("PatreonButton"), TEXT("DiscordInvButton"), TEXT("TwitterButton")};
    for (const TCHAR* ButtonName : Buttons) {
        UButton* Button = Cast<UButton>(Widget->GetWidgetFromName(FName(ButtonName)));
        if (!TestNotNull(FString(TEXT("Source summary control ")) + ButtonName, Button)) continue;
        TestTrue(FString(ButtonName) + TEXT(" click binding"), Button->OnClicked.IsBound());
    }

    FRecoveredSessionRewardData RewardData;
    RewardData.bWon = true;
    RewardData.EndingLevel = 3;
    RewardData.EndingXP = 41;
    RewardData.XPGranted = 125;
    RewardData.SessionStats.Strokes = 42;
    RewardData.SessionStats.Edges = 7;
    RewardData.SessionStats.MaxCombo = 11;
    RewardData.SessionStats.EnemiesDefeated = 3;
    RewardData.SessionStats.SuccubiDefeated = 2;
    RewardData.SessionStats.SessionDuration = 125;
    RewardData.SessionStats.TimesTaunted = 4;
    RewardData.SessionStats.TimeAtHighHeat = 367;
    RewardData.SessionStats.DrawsAtMaxHeat = 3;
    RewardData.SessionStats.ItemsUsed = 5;
    RewardData.SessionStats.PerfectEdges = 6;
    RewardData.SessionStats.EdgeStreak = 9;
    Widget->InitializeRecoveredSummary(RewardData, true);

    UTextBlock* Victory = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("VictoryText")));
    UTextBlock* Strokes = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TotalStrokesText")));
    UTextBlock* Combo = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("HighestComboText")));
    UTextBlock* Edges = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("EdgeAmountText")));
    UTextBlock* Duration = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("DurationText")));
    UTextBlock* Details = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("DetailedStatsString")));
    if (!TestNotNull(TEXT("Source summary result field"), Victory) || !TestNotNull(TEXT("Source summary stroke field"), Strokes) ||
        !TestNotNull(TEXT("Source summary combo field"), Combo) || !TestNotNull(TEXT("Source summary edge field"), Edges) || !TestNotNull(TEXT("Source summary duration field"), Duration) ||
        !TestNotNull(TEXT("Source summary detail field"), Details)) return false;
    TestEqual(TEXT("Summary victory label"), Victory->GetText().ToString(), FString(TEXT("Victory")));
    TestTrue(TEXT("Summary victory source color"), Victory->GetColorAndOpacity().GetSpecifiedColor().Equals(FLinearColor(0.0f, 0.5209959745407104f, 0.12477199733257294f, 1.0f), KINDA_SMALL_NUMBER));
    TestEqual(TEXT("Summary source stroke notation"), Strokes->GetText().ToString(), FString(TEXT("42")));
    TestEqual(TEXT("Summary source combo notation"), Combo->GetText().ToString(), FString(TEXT("11")));
    TestEqual(TEXT("Summary source edge notation"), Edges->GetText().ToString(), FString(TEXT("7")));
    TestEqual(TEXT("Summary source duration"), Duration->GetText().ToString(), FString(TEXT("2:05")));
    TestEqual(TEXT("Summary source detail body"), Details->GetText().ToString(), FString(TEXT("SUCCUBI DEFEATED: 2\nENEMIES DEFEATED: 5\nTIMES TAUNTED: 4\nTIME AT HIGH HEAT: 6:07\nDRAWS AT MAX HEAT: 3\nITEMS USED: 5\nPERFECT EDGES: 6\nBEST EDGE STREAK: 9")));
    Widget->InitializeRecoveredSummary(RewardData, false);
    TestEqual(TEXT("Summary defeat label"), Victory->GetText().ToString(), FString(TEXT("Defeat (-50% Rewards)")));
    TestTrue(TEXT("Summary defeat source color"), Victory->GetColorAndOpacity().GetSpecifiedColor().Equals(FLinearColor(0.838798999786377f, 0.0f, 0.0006070000235922635f, 1.0f), KINDA_SMALL_NUMBER));
    Widget->InitializeRecoveredSummary(RewardData, true);
    TestEqual(TEXT("Patreon source URL"), URecoveredSessionSummaryWidget::GetRecoveredSummarySocialURL(TEXT("Patreon")), FString(TEXT("https://www.patreon.com/CockHeroGame")));
    TestEqual(TEXT("Discord source URL"), URecoveredSessionSummaryWidget::GetRecoveredSummarySocialURL(TEXT("Discord")), FString(TEXT("https://discord.gg/dQXRpF6Uhf")));
    TestEqual(TEXT("Twitter source URL"), URecoveredSessionSummaryWidget::GetRecoveredSummarySocialURL(TEXT("Twitter")), FString(TEXT("https://x.com/CockHeroGame")));
    struct FVoiceRouteExpectation {
        FName VoicePack;
        bool bWon;
        const TCHAR* AssetPrefix;
    };
    const FVoiceRouteExpectation VoiceRoutes[] = {
        {TEXT("Default"), true, TEXT("VillainessPostGameVictory")},
        {TEXT("Default"), false, TEXT("VillainessPostGameDefeat")},
        {TEXT("Brat"), true, TEXT("BratPostGameVictory")},
        {TEXT("Brat"), false, TEXT("BratPostGameDefeat")},
        {TEXT("Dommy Mommy"), true, TEXT("DommyMommyPostGameVictory")},
        {TEXT("Dommy Mommy"), false, TEXT("DommyMommyPostGameDefeat")},
        {TEXT("Sweetheart"), true, TEXT("SweetheartPostGameVictory")},
        {TEXT("Sweetheart"), false, TEXT("SweetheartPostGameDefeat")},
    };
    for (const FVoiceRouteExpectation& Route : VoiceRoutes) {
        USoundBase* Voice = Widget->SelectRecoveredPostGameVoicelineFor(Route.VoicePack, Route.bWon);
        if (!TestNotNull(FString::Printf(TEXT("Source post-game voice route %s %d"), *Route.VoicePack.ToString(), Route.bWon), Voice)) continue;
        TestTrue(FString::Printf(TEXT("Source post-game voice pack %s %d"), *Route.VoicePack.ToString(), Route.bWon), Voice->GetName().StartsWith(Route.AssetPrefix));
    }
    TestNotNull(TEXT("Source post-game fallback route selects recovered audio"), Widget->SelectRecoveredPostGameVoiceline());
    Widget->StartRecoveredBeginDisplayAnimation();
    TestTrue(TEXT("Summary construct starts source animation"), Widget->IsRecoveredAnimationPlaying(TEXT("BeginDisplay")));
    return true;
}
#endif
