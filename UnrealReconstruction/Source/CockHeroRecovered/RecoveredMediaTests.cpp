#include "RecoveredMedia.h"
#include "Misc/AutomationTest.h"
#include "HAL/FileManager.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredMediaTest, "CockHero.Recovery.MediaFilterBoundaries", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredMediaTest::RunTest(const FString& Parameters) {
    TArray<FRecoveredMediaEntry> Entries;
    for (int32 Index=0; Index<6; ++Index) { FRecoveredMediaEntry Entry; Entry.File=FString::FromInt(Index); Entries.Add(Entry); }
    auto Decks=URecoveredMediaLibrary::FilterMedia(Entries,{},false,false,false);
    TestEqual(TEXT("Round robin wraps"),Decks.Slow.Num(),2);
    TestEqual(TEXT("Fourth fallback is succubus"),Decks.Succubus[0].File,FString(TEXT("3")));
    TestEqual(TEXT("Fifth fallback is cum"),Decks.Cum[0].File,FString(TEXT("4")));
    FRecoveredMediaEntry Multi; Multi.Tags={TEXT("slow"),TEXT("fast"),TEXT("slow"),TEXT("ass")};
    Decks=URecoveredMediaLibrary::FilterMedia({Multi},{},true,true,false);
    TestEqual(TEXT("Preferences use OR"),Decks.Ass.Num(),1);
    TestEqual(TEXT("Repeated tags preserved"),Decks.Slow.Num(),2);
    TestEqual(TEXT("Multiple categories retained"),Decks.Fast.Num(),1);
    Decks=URecoveredMediaLibrary::FilterMedia({Multi},{TEXT("fast")},false,false,false);
    TestEqual(TEXT("Exclusion removes entire entry"),Decks.Slow.Num(),0);
    Multi.Tags={TEXT("assjob")};
    Decks=URecoveredMediaLibrary::FilterMedia({Multi},{},true,false,false);
    TestEqual(TEXT("Preference alias enters fallback"),Decks.Slow.Num(),1);
    TestEqual(TEXT("Preference alias is not body category"),Decks.Ass.Num(),0);
    Multi.Tags={TEXT("ass")};
    Decks=URecoveredMediaLibrary::FilterMedia({Multi},{},false,false,false);
    TestEqual(TEXT("Body-only entry does not enter fallback"),Decks.Slow.Num(),0);
    TestEqual(TEXT("Body-only category retained"),Decks.Ass.Num(),1);
    Multi.Tags={TEXT("SLOW"),TEXT("Ass")};
    Decks=URecoveredMediaLibrary::FilterMedia({Multi},{TEXT("ass")},true,false,false);
    TestEqual(TEXT("Native exclusions ignore case"),Decks.Slow.Num(),0);
    Decks=URecoveredMediaLibrary::FilterMedia({Multi},{},true,false,false);
    TestEqual(TEXT("Native categories ignore case"),Decks.Slow.Num(),1);
    const auto Tags=URecoveredMediaLibrary::ParseFilenameTags(TEXT("100_BOOBS_SLOW.png"));
    TestEqual(TEXT("Vocabulary order"),Tags[0],FString(TEXT("slow")));
    TestEqual(TEXT("Case normalized"),Tags[1],FString(TEXT("boobs")));
    const FString Manifest=TEXT("C:/Users/webma/Downloads/Cock_Hero_Shipping_Build_V0.04_-_Exclusive/PrepV2/Windows/Extracted/Base_Game_CG/manifest.json");
    if (IFileManager::Get().FileExists(*Manifest)) {
        FString Error;
        TestTrue(TEXT("Real UTF-16 manifest loads"),URecoveredMediaLibrary::ReadPackManifest(Manifest,Entries,Error));
        TestEqual(TEXT("Real pack entry count"),Entries.Num(),487);
        for(const auto& Entry:Entries) TestTrue(TEXT("Manifest media exists: ")+Entry.File,IFileManager::Get().FileExists(*Entry.FullPath));
    }
    return true;
}
#endif
