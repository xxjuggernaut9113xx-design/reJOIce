#include "RecoveredRules.h"
#include "RecoveredGameplay.h"
#include "RecoveredMenu.h"
#include "RecoveredProgression.h"
#include "RecoveredProgressionResources.h"
#include "Engine/Texture2D.h"
#include "Misc/AutomationTest.h"
#include "Misc/ConfigCacheIni.h"
#include "Sound/SoundBase.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerContentTest,"CockHero.Recovery.NewerProgressionContent",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerContentTest::RunTest(const FString& Parameters)
{
    auto* Challenges=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Newer20261017/Progression/DT_Challenges.DT_Challenges"));
    auto* Cards=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Newer20261017/Progression/DT_PlayerCards.DT_PlayerCards"));
    auto* Levels=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Newer20261017/Progression/DT_LevelData.DT_LevelData"));
    if (!TestNotNull(TEXT("Versioned newer challenges"),Challenges)||!TestNotNull(TEXT("Versioned newer cards"),Cards)||!TestNotNull(TEXT("Versioned newer levels"),Levels)) return false;
    TestEqual(TEXT("Newer challenge count"),Challenges->GetRowNames().Num(),70);
    TestEqual(TEXT("Newer card count"),Cards->GetRowNames().Num(),48);
    TestEqual(TEXT("Unchanged level count"),Levels->GetRowNames().Num(),20);
    auto* Modifiers=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Newer20261017/Progression/DT_Modifiers.DT_Modifiers"));
    if (TestNotNull(TEXT("Versioned newer modifiers"),Modifiers))
    {
        TestEqual(TEXT("All newer modifier rows"),Modifiers->GetRowNames().Num(),28);
        if (TestTrue(TEXT("Newer modifier row schema"),Modifiers->GetRowStruct()==FRecoveredModifierRow::StaticStruct()))
        {
            for (const auto& Entry:Modifiers->GetRowMap())
                TestNotNull(TEXT("Newer modifier artwork binding"),reinterpret_cast<const FRecoveredModifierRow*>(Entry.Value)->ModifierIcon.Get());
        }
    }
    auto* Heat=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Newer20261017/Progression/DT_HeatCategories.DT_HeatCategories"));
    if (TestNotNull(TEXT("Versioned newer heat timing"),Heat)) TestEqual(TEXT("Source heat categories"),Heat->GetRowNames().Num(),4);
    auto* Baseline=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    if (TestNotNull(TEXT("Baseline retained independently"),Baseline)) TestEqual(TEXT("Baseline retains 55 challenges"),Baseline->GetRowNames().Num(),55);
    TSet<FString> IDs;
    TSet<FString> Artwork;
    const UEnum* Metrics=StaticEnum<ERecoveredMetric>();
    for (const auto& Entry:Challenges->GetRowMap())
    {
        const auto* Row=reinterpret_cast<const FRecoveredChallengeRow*>(Entry.Value);
        TestFalse(TEXT("Unique newer challenge identifier"),IDs.Contains(Row->ChallengeID));
        IDs.Add(Row->ChallengeID);
        Artwork.Add(Row->Icon);
        for (const auto& Requirement:Row->Requirements)
        {
            FString Metric=Requirement.MetricType;
            int32 Separator=INDEX_NONE;
            if (Metric.FindLastChar(TCHAR(':'),Separator)) Metric=Metric.Mid(Separator+1);
            TestTrue(*FString::Printf(TEXT("Reflected metric %s"),*Metric),Metrics->GetValueByNameString(Metric)!=INDEX_NONE);
        }
    }
    for (const auto& Entry:Cards->GetRowMap())
    {
        const auto* Row=reinterpret_cast<const FRecoveredPlayerCardRow*>(Entry.Value);
        TestTrue(TEXT("Card unlock challenge resolves"),Row->RequiredChallengeID.IsEmpty()||IDs.Contains(Row->RequiredChallengeID));
        Artwork.Add(Row->CardImage);
    }
    TestEqual(TEXT("Source references cover all newer artwork"),Artwork.Num(),118);
    bool bPrevious=false;
    const bool bHadSetting=GConfig->GetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),bPrevious,GGameIni);
    GConfig->SetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),true,GGameIni);
    auto* Voices=NewObject<URecoveredVoiceSettings>();
    if (TestTrue(TEXT("Selected newer voice catalog loads"),Voices->LoadRecoveredVoicePackCatalog()))
    {
        TestEqual(TEXT("All seven source voice packs"),Voices->VoicePacks.Num(),7);
        for (const auto& Pack:Voices->VoicePacks)
        {
            TestNotNull(TEXT("Newer sample one"),Pack.Sample1.Get());
            TestNotNull(TEXT("Newer sample two"),Pack.Sample2.Get());
            TestNotNull(TEXT("Newer sample three"),Pack.Sample3.Get());
            TestNotNull(TEXT("Newer selection preview"),Pack.SelectionLine.Get());
        }
    }
    for (const FString& Original:Artwork)
    {
        FString Relative=Original;
        Relative.RemoveFromStart(TEXT("/Game/"));
        const FString Path=TEXT("/Game/Recovery/Newer20261017/Resources/")+Relative;
        TestEqual(TEXT("Selected newer alias resolves exact asset"),ResolveRecoveredProgressionResource(Original),Path);
        auto* Texture=LoadObject<UTexture2D>(nullptr,*Path);
        if (TestNotNull(*FString::Printf(TEXT("Newer artwork %s"),*Original),Texture))
        {
#if WITH_EDITORONLY_DATA
            TestTrue(TEXT("Artwork retains nonempty imported source pixels"),Texture->Source.GetSizeX()>0&&Texture->Source.GetSizeY()>0);
#else
            TestTrue(TEXT("Artwork has nonempty pixel dimensions"),Texture->GetSizeX()>0&&Texture->GetSizeY()>0);
#endif
        }
    }
    GConfig->SetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),false,GGameIni);
    TestTrue(TEXT("Baseline voice catalog remains readable"),Voices->LoadRecoveredVoicePackCatalog());
    TestEqual(TEXT("Baseline voice packs remain four"),Voices->VoicePacks.Num(),4);
    TestEqual(TEXT("Disabled newer definitions retain baseline lookup"),ResolveRecoveredProgressionResource(TEXT("/Game/ChallengeIcons/QuickshotIcon.QuickshotIcon")),FString(TEXT("/Game/ChallengeIcons/QuickshotIcon.QuickshotIcon")));
    if (bHadSetting) GConfig->SetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),bPrevious,GGameIni);
    else GConfig->RemoveKey(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),GGameIni);
    return true;
}
#endif
