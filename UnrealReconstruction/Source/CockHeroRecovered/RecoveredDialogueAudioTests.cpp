#include "RecoveredDialogueAudio.h"
#include "Misc/AutomationTest.h"
#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundWaveProcedural.h"
#include "UObject/Package.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredSourceDialogueAudioTest,"CockHero.Recovery.NewerSourceDialogueAudio",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredSourceDialogueAudioTest::RunTest(const FString& Parameters)
{
    const TCHAR* Packs[]={TEXT("Default"),TEXT("Brat"),TEXT("DommyMommy"),TEXT("Sweetheart"),TEXT("Yandere"),TEXT("Chariot"),TEXT("Pepper")};
    for (const TCHAR* Pack:Packs)
    {
        FString Row;
        auto* Wave=Cast<USoundWaveProcedural>(SelectRecoveredSourceDialogue(Pack,TEXT("boobs"),TEXT("Neutral"),&Row));
        if (TestNotNull(*FString::Printf(TEXT("Source Bink decode for selected pack %s"),Pack),Wave))
        {
            TestTrue(TEXT("Decoded source has queued PCM"),Wave->GetAvailableAudioByteCount()>0);
            TestTrue(TEXT("Decoded source has valid channels"),Wave->NumChannels>=1&&Wave->NumChannels<=2);
            TestTrue(TEXT("Decoded source has finite positive duration"),FMath::IsFinite(Wave->Duration)&&Wave->Duration>0.0f);
            TestTrue(TEXT("Selected row matches requested context"),Row.StartsWith(TEXT("boobs_")));
            TestFalse(TEXT("Source dialogue does not loop"),Wave->bLooping);
        }
    }
    TestNull(TEXT("Unknown pack cannot fall back to another voice"),SelectRecoveredSourceDialogue(TEXT("UnknownPack"),TEXT("boobs")));
    TestNull(TEXT("Unknown source context fails closed"),SelectRecoveredSourceDialogue(TEXT("Yandere"),TEXT("no_such_source_category")));
    TestEqual(TEXT("Selected mini-pack display names use source folder"),GetRecoveredCanonicalVoicePack(TEXT("Chariot (Mini)")),FString(TEXT("Chariot")));
    TestEqual(TEXT("Selected brat display name uses source folder"),GetRecoveredCanonicalVoicePack(TEXT("Teasing Brat")),FString(TEXT("Brat")));
    FString Text;
    TSharedPtr<FJsonObject> Catalog;
    if (!TestTrue(TEXT("Source pronoun audit data loads"),FFileHelper::LoadFileToString(Text,*(FPaths::ProjectContentDir()/TEXT("Recovery/Definitions/newer-20261017-dialogue-catalog.json")))&&FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Catalog))) return false;
    const auto& DefaultRows=Catalog->GetObjectField(TEXT("packs"))->GetArrayField(TEXT("Default"));
    const TCHAR* Pronouns[]={TEXT("Male"),TEXT("Female"),TEXT("Neutral")};
    for (int32 Selection=0;Selection<3;++Selection)
    {
        const FString Pronoun=GetRecoveredDialoguePronoun(Selection);
        TestEqual(TEXT("Source numeric pronoun selection"),Pronoun,FString(Pronouns[Selection]));
        FString Selected;
        TestNotNull(TEXT("Tag candidates decode with selected pronoun"),SelectRecoveredPaceDialogue(TEXT("Default"),0,{TEXT("small_penis"),TEXT("boobs")},Pronoun,false,&Selected));
        TestTrue(TEXT("Disabled SPH candidate is excluded"),Selected.StartsWith(TEXT("boobs_")));
        for (const auto& Value:DefaultRows)
        {
            const auto Row=Value->AsObject();
            if (Row->GetStringField(TEXT("row"))==Selected) {
                const FString Actual=Row->GetStringField(TEXT("Pronoun"));
                TestTrue(TEXT("Selected source row passes pronoun filter"),Actual.IsEmpty()||Actual.Equals(TEXT("Neutral"),ESearchCase::IgnoreCase)||Actual.Equals(Pronoun,ESearchCase::IgnoreCase));
                break;
            }
        }
    }
    FString Fallback;
    TestNotNull(TEXT("No matching tag falls back to pace category"),SelectRecoveredPaceDialogue(TEXT("Default"),0,{TEXT("unknown_category")},TEXT("Male"),false,&Fallback));
    TestTrue(TEXT("Fallback stays in slow source category"),Fallback.StartsWith(TEXT("slow_")));
    return true;
}
#endif
