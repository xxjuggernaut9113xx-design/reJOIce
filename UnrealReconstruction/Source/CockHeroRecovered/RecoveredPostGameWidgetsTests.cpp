#include "RecoveredPostGameWidgets.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Engine/DataTable.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "RecoveredRules.h"
#include "Sound/SoundWave.h"

#if WITH_DEV_AUTOMATION_TESTS
namespace {
UWorld* CreatePostGameWidgetWorld(FWorldContext*& OutContext) {
    const auto Initialization = UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World = UWorld::CreateWorld(EWorldType::Game, false, NAME_None, nullptr, true, ERHIFeatureLevel::Num, &Initialization);
    OutContext = &GEngine->CreateNewWorldContext(EWorldType::Game);
    OutContext->SetCurrentWorld(World);
    return World;
}

FString GetAssetName(const FString& ObjectPath) {
    int32 Dot = INDEX_NONE;
    return ObjectPath.FindLastChar(TEXT('.'), Dot) ? ObjectPath.Mid(Dot + 1) : FString();
}

UTexture2D* GetImageTexture(UUserWidget* Widget, FName Name) {
    const UImage* Image = Cast<UImage>(Widget ? Widget->GetWidgetFromName(Name) : nullptr);
    return Image ? Cast<UTexture2D>(Image->GetBrush().GetResourceObject()) : nullptr;
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredPostGameWidgetsTest, "CockHero.Recovery.PostGameWidgetContracts", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredPostGameWidgetsTest::RunTest(const FString& Parameters) {
    UClass* XPBarClass = LoadClass<URecoveredXPBarWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_XPBar.WBP_XPBar_C"));
    UClass* XPSourceClass = LoadClass<URecoveredXPSourceTextWidget>(nullptr, TEXT("/Game/Recovery/UI/XBP_XPSourceText.XBP_XPSourceText_C"));
    UClass* XPScreenClass = LoadClass<URecoveredXPScreenWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_XPScreen.WBP_XPScreen_C"));
    UClass* UPRewardScreenClass = LoadClass<URecoveredUPRewardScreenWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_UPRewardScreen.WBP_UPRewardScreen_C"));
    UClass* UPSourceClass = LoadClass<URecoveredUPSourceTextWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_UPSourceText.WBP_UPSourceText_C"));
    UClass* PlayerCardClass = LoadClass<URecoveredPlayerCardWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_PlayerCard.WBP_PlayerCard_C"));
    UClass* LevelUpClass = LoadClass<URecoveredLevelUpScreenWidget>(nullptr, TEXT("/Game/Recovery/UI/WBP_LevelUpScreen.WBP_LevelUpScreen_C"));
    if (!TestNotNull(TEXT("Recovered XP bar class"), XPBarClass) || !TestNotNull(TEXT("Recovered XP source class"), XPSourceClass) ||
        !TestNotNull(TEXT("Recovered XP screen class"), XPScreenClass) || !TestNotNull(TEXT("Recovered UP reward screen class"), UPRewardScreenClass) ||
        !TestNotNull(TEXT("Recovered UP source class"), UPSourceClass) || !TestNotNull(TEXT("Recovered player-card class"), PlayerCardClass) ||
        !TestNotNull(TEXT("Recovered level-up class"), LevelUpClass)) return false;
    if (!TestTrue(TEXT("XP bar uses recovered native parent"), XPBarClass->IsChildOf(URecoveredXPBarWidget::StaticClass())) ||
        !TestTrue(TEXT("XP source uses recovered native parent"), XPSourceClass->IsChildOf(URecoveredXPSourceTextWidget::StaticClass())) ||
        !TestTrue(TEXT("XP screen uses recovered native parent"), XPScreenClass->IsChildOf(URecoveredXPScreenWidget::StaticClass())) ||
        !TestTrue(TEXT("UP reward screen uses recovered native parent"), UPRewardScreenClass->IsChildOf(URecoveredUPRewardScreenWidget::StaticClass())) ||
        !TestTrue(TEXT("UP source uses recovered native parent"), UPSourceClass->IsChildOf(URecoveredUPSourceTextWidget::StaticClass())) ||
        !TestTrue(TEXT("Player card uses recovered native parent"), PlayerCardClass->IsChildOf(URecoveredPlayerCardWidget::StaticClass())) ||
        !TestTrue(TEXT("Level-up screen uses recovered native parent"), LevelUpClass->IsChildOf(URecoveredLevelUpScreenWidget::StaticClass()))) return false;

    FWorldContext* Context = nullptr;
    UWorld* World = CreatePostGameWidgetWorld(Context);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance = NewObject<URecoveredGameInstance>();
    auto* Save = NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Post-game save initializes"), Save->InitializeRecoveredDefaults()) || !TestTrue(TEXT("Post-game player name writes"), Save->SetStringSetting(TEXT("Playercard_Name"), TEXT("Reyes")))) return false;
    Instance->CurrentSave = Save;
    Instance->ProgressionManager = NewObject<URecoveredProgressionManager>(Instance);
    URecoveredProgressionManager* Progression = Instance->ProgressionManager;
    Progression->LevelDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Recovery/Progression/DT_LevelData.DT_LevelData"));
    Progression->PlayerCardDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Recovery/Progression/DT_PlayerCards.DT_PlayerCards"));
    if (!TestNotNull(TEXT("Source level data table"), Progression->LevelDataTable.Get()) || !TestNotNull(TEXT("Source player-card data table"), Progression->PlayerCardDataTable.Get())) return false;
    TArray<FRecoveredPlayerCardRow> Cards;
    Progression->GetAllPlayerCardData(Cards);
    if (!TestTrue(TEXT("Source player-card rows available"), !Cards.IsEmpty())) return false;
    const FRecoveredPlayerCardRow& EquippedCard = Cards[0];
    Progression->EquippedPlayerCard = FName(*EquippedCard.CardID);
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    for (int32 Level = 1; Level <= 20; ++Level) {
        const FRecoveredLevelRow* SourceRow = nullptr;
        for (const TPair<FName, uint8*>& Pair : Progression->LevelDataTable->GetRowMap()) {
            const auto* Candidate = reinterpret_cast<const FRecoveredLevelRow*>(Pair.Value);
            if (Candidate && Candidate->Level == Level) {
                SourceRow = Candidate;
                break;
            }
        }
        if (!TestNotNull(FString::Printf(TEXT("Source rank row %d"), Level), SourceRow)) continue;
        UTexture2D* Icon = Progression->GetIconForLevel(Level);
        if (!TestNotNull(FString::Printf(TEXT("Recovered rank icon %d"), Level), Icon)) continue;
        TestEqual(FString::Printf(TEXT("Recovered rank icon name %d"), Level), Icon->GetName(), GetAssetName(SourceRow->LevelIcon));
        const FIntPoint Size = Icon->GetImportedSize();
        TestEqual(FString::Printf(TEXT("Recovered rank icon width %d"), Level), Size.X, 512);
        TestEqual(FString::Printf(TEXT("Recovered rank icon height %d"), Level), Size.Y, 512);
    }
    Progression->CurrentLevel = 19;
    TestEqual(TEXT("Next level icon resolves level twenty"), Progression->GetNextLevelIcon()->GetName(), FString(TEXT("Level_20_-_Cock_Legend")));
    Progression->CurrentLevel = 20;
    TestEqual(TEXT("Max-level next icon remains level twenty"), Progression->GetNextLevelIcon()->GetName(), FString(TEXT("Level_20_-_Cock_Legend")));
    TestNull(TEXT("Out-of-range level icon is absent"), Progression->GetIconForLevel(21));

    URecoveredXPBarWidget* XPBar = CreateWidget<URecoveredXPBarWidget>(World, XPBarClass);
    if (!TestNotNull(TEXT("Recovered XP bar instantiates"), XPBar)) return false;
    XPBar->TakeWidget();
    XPBar->SetRecoveredPostGameGameInstance(Instance);
    XPBar->InitializeBar(3, 41, 175);
    UTextBlock* CurrentLevelText = Cast<UTextBlock>(XPBar->GetWidgetFromName(TEXT("CurrentLevelText")));
    UTextBlock* NextLevelText = Cast<UTextBlock>(XPBar->GetWidgetFromName(TEXT("NextLevelNumber")));
    UTextBlock* XPText = Cast<UTextBlock>(XPBar->GetWidgetFromName(TEXT("XPText")));
    UProgressBar* XPProgress = Cast<UProgressBar>(XPBar->GetWidgetFromName(TEXT("XPProgressBar")));
    if (!TestNotNull(TEXT("Source current level text"), CurrentLevelText) || !TestNotNull(TEXT("Source next level text"), NextLevelText) || !TestNotNull(TEXT("Source XP text"), XPText) || !TestNotNull(TEXT("Source XP progress"), XPProgress)) return false;
    TestEqual(TEXT("Source current-level display"), CurrentLevelText->GetText().ToString(), FString(TEXT("3")));
    TestEqual(TEXT("Source next-level display"), NextLevelText->GetText().ToString(), FString(TEXT("4")));
    TestEqual(TEXT("Source XP display"), XPText->GetText().ToString(), FString(TEXT("41/175 XP")));
    TestEqual(TEXT("Source XP percent"), XPProgress->GetPercent(), 41.0f / 175.0f);
    UTexture2D* CurrentIcon = GetImageTexture(XPBar, TEXT("CurrentLevelEmblemIcon"));
    UTexture2D* NextIcon = GetImageTexture(XPBar, TEXT("NextLevelEmblem"));
    if (TestNotNull(TEXT("Source current rank image"), CurrentIcon)) TestEqual(TEXT("Source current rank image name"), CurrentIcon->GetName(), FString(TEXT("Level_3_-_Sophomore_Slapper")));
    if (TestNotNull(TEXT("Source next rank image"), NextIcon)) TestEqual(TEXT("Source next rank image name"), NextIcon->GetName(), FString(TEXT("Level_4_-_Shaft_Shaman")));
    XPBar->AddXPAnimated(200, 0.65f);
    XPBar->AdvanceRecoveredXPAnimation(0.325f);
    TestEqual(TEXT("Source XP animation interpolates with floor"), XPBar->CurrentXP, 141);
    XPBar->AdvanceRecoveredXPAnimation(1.0f);
    TestEqual(TEXT("Source XP animation clamps at level threshold"), XPBar->CurrentXP, 175);
    TestEqual(TEXT("Source XP animation retains overflow"), XPBar->GetOverflowXP(), 66);
    TestFalse(TEXT("Source XP animation stops after threshold"), XPBar->bIsAnimating);
    TestEqual(TEXT("Source full XP display"), XPText->GetText().ToString(), FString(TEXT("175/175 XP")));

    URecoveredPlayerCardWidget* PlayerCard = CreateWidget<URecoveredPlayerCardWidget>(World, PlayerCardClass);
    if (!TestNotNull(TEXT("Recovered player-card instantiates"), PlayerCard)) return false;
    PlayerCard->TakeWidget();
    PlayerCard->SetRecoveredPostGameGameInstance(Instance);
    PlayerCard->InitializePlayerCard();
    UTextBlock* PlayerName = Cast<UTextBlock>(PlayerCard->GetWidgetFromName(TEXT("PlayerNameText")));
    UTexture2D* PlayerTexture = GetImageTexture(PlayerCard, TEXT("SelectedPlayerCard"));
    if (TestNotNull(TEXT("Source player-card name field"), PlayerName)) TestEqual(TEXT("Source player-card name"), PlayerName->GetText().ToString(), FString(TEXT("Reyes")));
    if (TestNotNull(TEXT("Source player-card artwork"), PlayerTexture)) TestEqual(TEXT("Source player-card artwork name"), PlayerTexture->GetName(), GetAssetName(EquippedCard.CardImage));

    URecoveredLevelUpScreenWidget* LevelUp = CreateWidget<URecoveredLevelUpScreenWidget>(World, LevelUpClass);
    if (!TestNotNull(TEXT("Recovered level-up screen instantiates"), LevelUp)) return false;
    LevelUp->TakeWidget();
    LevelUp->SetRecoveredPostGameGameInstance(Instance);
    FRecoveredLevelUpEventData LevelData;
    LevelData.NewLevel = 10;
    LevelData.Title = TEXT("Stroke Sergeant");
    LevelData.UPReward = 3;
    LevelData.XPThresholdCrossed = 515;
    LevelUp->InitializeScreen(LevelData);
    UTextBlock* LevelText = Cast<UTextBlock>(LevelUp->GetWidgetFromName(TEXT("LevelText")));
    UTextBlock* RankTitle = Cast<UTextBlock>(LevelUp->GetWidgetFromName(TEXT("RankTitle")));
    if (TestNotNull(TEXT("Source level-up number"), LevelText)) TestEqual(TEXT("Source level-up number value"), LevelText->GetText().ToString(), FString(TEXT("10")));
    if (TestNotNull(TEXT("Source level-up title"), RankTitle)) TestEqual(TEXT("Source level-up title value"), RankTitle->GetText().ToString(), FString(TEXT("Stroke Sergeant")));
    UTexture2D* LevelUpIcon = GetImageTexture(LevelUp, TEXT("RankIcon"));
    if (TestNotNull(TEXT("Source level-up rank image"), LevelUpIcon)) TestEqual(TEXT("Source level-up rank image name"), LevelUpIcon->GetName(), FString(TEXT("Level_10_-_Stroke_Sergeant")));
    TestTrue(TEXT("Source level-up animation restored"), LevelUp->GetRecoveredLevelUpAnimationDuration() > 0.0f);

    URecoveredXPSourceTextWidget* XPSource = CreateWidget<URecoveredXPSourceTextWidget>(World, XPSourceClass);
    if (!TestNotNull(TEXT("Recovered XP source instantiates"), XPSource)) return false;
    XPSource->TakeWidget();
    FRecoveredXPSourceData XPSourceData;
    XPSourceData.XPAmount = 125;
    XPSourceData.DetailText = FText::FromString(TEXT("5 MIN"));
    XPSource->InitializeSource(XPSourceData);
    UTextBlock* XPAmountText = Cast<UTextBlock>(XPSource->GetWidgetFromName(TEXT("XPAmountText")));
    UTextBlock* XPDetailText = Cast<UTextBlock>(XPSource->GetWidgetFromName(TEXT("XPDetailText")));
    if (!TestNotNull(TEXT("Source XP source amount"), XPAmountText) || !TestNotNull(TEXT("Source XP source detail"), XPDetailText)) return false;
    TestEqual(TEXT("Source XP source text"), XPAmountText->GetText().ToString(), FString(TEXT("+125 XP")));
    TestEqual(TEXT("Source XP source detail text"), XPDetailText->GetText().ToString(), FString(TEXT("(5 MIN)")));
    TestEqual(TEXT("Source XP source data"), XPSource->XPSourceData.XPAmount, 125);
    TestTrue(TEXT("Source XP source animation restored"), XPSource->GetRecoveredSourceAnimationDuration() > 0.0f);

    URecoveredXPScreenWidget* XPScreen = CreateWidget<URecoveredXPScreenWidget>(World, XPScreenClass);
    if (!TestNotNull(TEXT("Recovered XP screen instantiates"), XPScreen)) return false;
    XPScreen->TakeWidget();
    XPScreen->InitializeRecoveredScreen(false);
    XPScreen->SequenceEvent__ENTRYPOINTWBP_XPScreen();
    TestTrue(TEXT("Source XP loss callback plays penalty"), XPScreen->bRecoveredPenaltyPlayed);
    XPScreen->InitializeRecoveredScreen(true);
    XPScreen->SequenceEvent__ENTRYPOINTWBP_XPScreen();
    TestFalse(TEXT("Source XP win callback skips penalty"), XPScreen->bRecoveredPenaltyPlayed);

    URecoveredUPRewardScreenWidget* UPRewardScreen = CreateWidget<URecoveredUPRewardScreenWidget>(World, UPRewardScreenClass);
    if (!TestNotNull(TEXT("Recovered UP reward screen instantiates"), UPRewardScreen)) return false;
    UPRewardScreen->TakeWidget();
    UWidget* UPPenaltyText = UPRewardScreen->GetWidgetFromName(TEXT("50PercentPenaltyText"));
    if (!TestNotNull(TEXT("Source UP penalty text"), UPPenaltyText)) return false;
    UPRewardScreen->InitializeRecoveredScreen(true);
    TestEqual(TEXT("Source UP penalty hides on win"), static_cast<uint8>(UPPenaltyText->GetVisibility()), static_cast<uint8>(ESlateVisibility::Collapsed));
    UPRewardScreen->InitializeRecoveredScreen(false);
    TestEqual(TEXT("Source UP penalty shows on loss"), static_cast<uint8>(UPPenaltyText->GetVisibility()), static_cast<uint8>(ESlateVisibility::Visible));
    TestFalse(TEXT("Source UP callback resets before source animation"), UPRewardScreen->bRecoveredSourceAnimationComplete);
    UPRewardScreen->OnSourceAnimationComplete();
    TestTrue(TEXT("Source UP callback completes after source animation"), UPRewardScreen->bRecoveredSourceAnimationComplete);

    URecoveredUPSourceTextWidget* UPSource = CreateWidget<URecoveredUPSourceTextWidget>(World, UPSourceClass);
    if (!TestNotNull(TEXT("Recovered UP source instantiates"), UPSource)) return false;
    UPSource->TakeWidget();
    FRecoveredUPSourceData UPSourceData;
    UPSourceData.UPAmount = 3;
    UPSourceData.DetailText = FText::FromString(TEXT("LVL 10"));
    UPSource->InitializeSource(UPSourceData);
    UTextBlock* UPAmountText = Cast<UTextBlock>(UPSource->GetWidgetFromName(TEXT("UPAmountText")));
    UTextBlock* UPDetailText = Cast<UTextBlock>(UPSource->GetWidgetFromName(TEXT("DetailText")));
    if (!TestNotNull(TEXT("Source UP source amount"), UPAmountText) || !TestNotNull(TEXT("Source UP source detail"), UPDetailText)) return false;
    TestEqual(TEXT("Source UP source text"), UPAmountText->GetText().ToString(), FString(TEXT("+3 UP")));
    TestEqual(TEXT("Source UP source detail text"), UPDetailText->GetText().ToString(), FString(TEXT("(LVL 10)")));
    TestEqual(TEXT("Source UP source data"), UPSource->UPData.UPAmount, 3);
    TestTrue(TEXT("Source UP source animation restored"), UPSource->GetRecoveredSourceAnimationDuration() > 0.0f);

    struct FSoundExpectation { const TCHAR* Path; int32 Frames; };
    const FSoundExpectation Sounds[] = {
        {TEXT("/Game/Recovery/Resources/PostGameSoundFX/whoosh-cinematic-161021_sfx.whoosh-cinematic-161021_sfx"), 133632},
        {TEXT("/Game/Recovery/Resources/PostGameSoundFX/drop-coin-384921.drop-coin-384921"), 48384},
        {TEXT("/Game/Recovery/Resources/PostGameSoundFX/Juice_SFX__11_.Juice_SFX__11_"), 304128},
        {TEXT("/Game/Recovery/Resources/PostGameSoundFX/Juice_SFX__9_.Juice_SFX__9_"), 86400},
        {TEXT("/Game/Recovery/Resources/PostGameSoundFX/Juice_SFX__5_.Juice_SFX__5_"), 19052},
    };
    for (const FSoundExpectation& Expected : Sounds) {
        USoundWave* Sound = LoadObject<USoundWave>(nullptr, Expected.Path);
        if (!TestNotNull(FString(TEXT("Recovered post-game sound ")) + Expected.Path, Sound)) continue;
        TArray<uint8> PCM;
        uint32 SampleRate = 0;
        uint16 ChannelCount = 0;
        TestTrue(FString(TEXT("Recovered post-game PCM ")) + Expected.Path, Sound->GetImportedSoundWaveData(PCM, SampleRate, ChannelCount));
        TestEqual(FString(TEXT("Recovered post-game sample rate ")) + Expected.Path, static_cast<int32>(SampleRate), 44100);
        TestEqual(FString(TEXT("Recovered post-game channel count ")) + Expected.Path, static_cast<int32>(ChannelCount), 2);
        TestEqual(FString(TEXT("Recovered post-game PCM frames ")) + Expected.Path, PCM.Num() / (2 * 2), Expected.Frames);
    }
    return true;
}
#endif
