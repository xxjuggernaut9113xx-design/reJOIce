#include "RecoveredBeatmap.h"
#include "RecoveredContentPaths.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Misc/Paths.h"

#if WITH_DEV_AUTOMATION_TESTS
namespace {
FString BeatmapFixture() {
    return TEXT(R"JSON({"meta":{"title":"Reader fixture","artist":"Fixture artist","author":"Test","audioFile":"song.wav","duration":20.25,"bpm":126.04,"offset":-0.013},"beats":[{"time":0.004,"type":"stroke"},{"time":2.146456718444824,"type":"stroke"},{"time":19.5,"type":"stroke"}],"events":[{"time":0,"type":"cycle_media","value":"true"},{"time":0,"type":"media_change","value":"slow"},{"time":0,"type":"background","value":"normalbeatbackground"},{"time":1,"type":"disable_break","value":"start"},{"time":2,"type":"disable_break","value":"end"},{"time":3,"type":"media_change","value":"medium"},{"time":4,"type":"media_change","value":"fast"},{"time":5,"type":"media_change","value":"succubus"},{"time":5,"type":"background","value":"succubusbackground"},{"time":6,"type":"background","value":"mercybackground"},{"time":7,"type":"background","value":"tauntbackground"},{"time":8,"type":"background","value":"temptationbackground"},{"time":9,"type":"cum_event","value":"start"},{"time":9,"type":"media_change","value":"cum"},{"time":9,"type":"background","value":"successfulcumbackground"},{"time":18,"type":"cum_event","value":"end"}]})JSON");
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBeatmapParserTest, "CockHero.Recovery.BeatmapReader", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredBeatmapParserTest::RunTest(const FString& Parameters) {
    FRecoveredBeatmapData Data;
    FString Error;
    if (!TestTrue(TEXT("Parse shipped record shapes"), URecoveredBeatmapLibrary::ParseBeatmapJson(BeatmapFixture(), Data, Error))) return false;
    TestEqual(TEXT("Preserve beats"), Data.Beats.Num(), 3);
    TestEqual(TEXT("Preserve events"), Data.Events.Num(), 16);
    TestEqual(TEXT("Metadata offset is not applied twice"), Data.Beats[0].Time, 0.004);
    TestEqual(TEXT("Offset remains metadata"), Data.Meta.Offset, -0.013);
    TestEqual(TEXT("Native equal-time priority category first"), Data.Events[0].Type, FString(TEXT("media_change")));
    TestEqual(TEXT("Native equal-time priority background second"), Data.Events[1].Type, FString(TEXT("background")));
    TestEqual(TEXT("Native equal-time priority cycle third"), Data.Events[2].Type, FString(TEXT("cycle_media")));
    const FString Native = TEXT(R"JSON({"meta":{"difficulty":"Hard","offset":0.016},"beats":[null,5,{"time":40,"type":"ACCENT","duration":0.5},{"time":"-2","type":"unknown"},{}],"events":[false,{},{"time":2,"type":"text","value":12},{"time":1,"type":"cycle_media","value":true},{"time":1.00005,"type":"background"},{"time":1.00009,"type":"MEDIA_SWITCH","value":"ass"},{"time":3,"type":"unknown","duration":4}]})JSON");
    TestTrue(TEXT("Native accepts optional fields and skips nonobjects"), URecoveredBeatmapLibrary::ParseBeatmapJson(Native, Data, Error));
    TestTrue(TEXT("Successful parse clears errors"), Error.IsEmpty());
    TestEqual(TEXT("Default BPM"), Data.Meta.Bpm, 120.0);
    TestEqual(TEXT("Default duration"), Data.Meta.Duration, 0.0);
    TestEqual(TEXT("Difficulty retained"), Data.Meta.Difficulty, FString(TEXT("Hard")));
    TestEqual(TEXT("Object beat count"), Data.Beats.Num(), 3);
    TestEqual(TEXT("Numeric-string and negative time retained and sorted"), Data.Beats[0].Time, -2.0);
    TestEqual(TEXT("Unknown beat defaults to Stroke"), Data.Beats[0].Type, FString(TEXT("stroke")));
    TestEqual(TEXT("Case-insensitive Accent survives"), Data.Beats[2].Type, FString(TEXT("accent")));
    TestEqual(TEXT("Per-beat duration survives"), Data.Beats[2].Duration, 0.5);
    TestEqual(TEXT("Missing event type defaults to Custom"), Data.Events[0].Type, FString(TEXT("custom")));
    TestEqual(TEXT("Native epsilon prioritizes category over slightly earlier events"), Data.Events[1].Time, 1.00009);
    TestEqual(TEXT("Media switch alias canonicalized"), Data.Events[1].Type, FString(TEXT("media_change")));
    TestEqual(TEXT("Unknown category payload remains available to its handler"), Data.Events[1].Value, FString(TEXT("ass")));
    TestEqual(TEXT("Boolean payload converts through native JSON helper"), Data.Events[3].Value, FString(TEXT("true")));
    TestEqual(TEXT("Numeric payload converts through native JSON helper"), Data.Events[4].Value, FString(TEXT("12")));
    TestEqual(TEXT("Unknown event maps to Custom"), Data.Events.Last().Type, FString(TEXT("custom")));
    TestEqual(TEXT("Per-event duration survives"), Data.Events.Last().Duration, 4.0);
    TestTrue(TEXT("Missing events accepted"), URecoveredBeatmapLibrary::ParseBeatmapJson(TEXT(R"JSON({"beats":[{}]})JSON"), Data, Error));
    TestTrue(TEXT("Missing events yield empty stream"), Data.Events.IsEmpty());
    TestEqual(TEXT("Missing beat time defaults to zero"), Data.Beats[0].Time, 0.0);
    const FString Rest = TEXT(R"JSON({"beats":[{"time":1,"type":"REST"},{"time":1,"type":"stroke"}]})JSON");
    TestTrue(TEXT("Rest and duplicate beat timestamps are native-compatible"), URecoveredBeatmapLibrary::ParseBeatmapJson(Rest, Data, Error));
    TestEqual(TEXT("Duplicate records retained"), Data.Beats.Num(), 2);
    TestTrue(TEXT("Rest not discarded by parser"), Data.Beats.ContainsByPredicate([](const FRecoveredBeatmapBeat& Beat) { return Beat.Type == TEXT("rest"); }));
    Data.Meta.Title = TEXT("Preserve on failure");
    for (const FString& Invalid : {FString(TEXT("{")), FString(TEXT("{}")), FString(TEXT(R"JSON({"beats":[]})JSON")), FString(TEXT(R"JSON({"beats":[null,3]})JSON"))}) {
        TestFalse(TEXT("Malformed JSON or no object beats fails"), URecoveredBeatmapLibrary::ParseBeatmapJson(Invalid, Data, Error));
        TestTrue(TEXT("Explicit parse failure"), !Error.IsEmpty());
        TestEqual(TEXT("Recovery API preserves output on failure"), Data.Meta.Title, FString(TEXT("Preserve on failure")));
    }
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBeatmapFileTest, "CockHero.Recovery.BeatmapFileLoading", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredBeatmapFileTest::RunTest(const FString& Parameters) {
    const FString Directory = FPaths::ProjectSavedDir() / TEXT("Automation/BeatmapReader") / FGuid::NewGuid().ToString(EGuidFormats::Digits);
    if (!TestTrue(TEXT("Create isolated file fixtures"), IFileManager::Get().MakeDirectory(*Directory, true))) return false;
    const FString JsonPath = Directory / TEXT("beatmap.json");
    const FString AudioPath = Directory / TEXT("song.wav");
    FRecoveredBeatmapData Data;
    Data.Meta.Title = TEXT("File sentinel");
    FString ResolvedAudio = TEXT("Path sentinel");
    FString Error;
    TestTrue(TEXT("Write UTF-8 fixture"), FFileHelper::SaveStringToFile(BeatmapFixture(), *JsonPath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM));
    TestFalse(TEXT("Loading detects missing audio"), URecoveredBeatmapLibrary::LoadBeatmapFile(JsonPath, Data, ResolvedAudio, Error));
    TestTrue(TEXT("Missing asset error is explicit"), Error.Contains(TEXT("audio file is missing")));
    TestEqual(TEXT("Failed loading preserves data"), Data.Meta.Title, FString(TEXT("File sentinel")));
    TestEqual(TEXT("Failed loading preserves audio output"), ResolvedAudio, FString(TEXT("Path sentinel")));
    // File existence is this reader's boundary; this deliberately is not a playable WAV.
    TArray<uint8> Placeholder;
    Placeholder.Add(0);
    TestTrue(TEXT("Write existence-only audio fixture"), FFileHelper::SaveArrayToFile(Placeholder, *AudioPath));
    TestTrue(TEXT("UTF-8 load resolves sibling audio"), URecoveredBeatmapLibrary::LoadBeatmapFile(JsonPath, Data, ResolvedAudio, Error));
    TestTrue(TEXT("Resolved audio points at expected sibling"), FPaths::IsSamePath(ResolvedAudio, FPaths::ConvertRelativePathToFull(AudioPath)));
    TestTrue(TEXT("Write UTF-16 fixture"), FFileHelper::SaveStringToFile(BeatmapFixture(), *JsonPath, FFileHelper::EEncodingOptions::ForceUnicode));
    TestTrue(TEXT("UE loader accepts UTF-16 JSON"), URecoveredBeatmapLibrary::LoadBeatmapFile(JsonPath, Data, ResolvedAudio, Error));
    const FString Traversal = BeatmapFixture().Replace(TEXT("song.wav"), TEXT("../song.wav"));
    TestTrue(TEXT("Write escaping audio fixture"), FFileHelper::SaveStringToFile(Traversal, *JsonPath));
    TestFalse(TEXT("Loader rejects audio outside beatmap folder"), URecoveredBeatmapLibrary::LoadBeatmapFile(JsonPath, Data, ResolvedAudio, Error));
    TestTrue(TEXT("Escaping path error is explicit"), Error.Contains(TEXT("inside the beatmap directory")));
    const FString Absolute = BeatmapFixture().Replace(TEXT("song.wav"), TEXT("C:/song.wav"));
    TestTrue(TEXT("Write absolute audio fixture"), FFileHelper::SaveStringToFile(Absolute, *JsonPath));
    TestFalse(TEXT("Loader rejects absolute audio paths"), URecoveredBeatmapLibrary::LoadBeatmapFile(JsonPath, Data, ResolvedAudio, Error));
    TestTrue(TEXT("Absolute path error is explicit"), Error.Contains(TEXT("relative to the beatmap directory")));
    TestFalse(TEXT("Missing JSON returns failure"), URecoveredBeatmapLibrary::LoadBeatmapFile(Directory / TEXT("missing.json"), Data, ResolvedAudio, Error));
    TestTrue(TEXT("Missing JSON error is explicit"), Error.Contains(TEXT("Cannot read beatmap file")));
    TestTrue(TEXT("Clean isolated fixture directory"), IFileManager::Get().DeleteDirectory(*Directory, false, true));
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredBeatmapCorpusTest, "CockHero.Recovery.ReferenceBeatmapCorpus", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredBeatmapCorpusTest::RunTest(const FString& Parameters) {
    const FString Root=FRecoveredContentPaths::GetBeatmapsDirectory();
    if (Root.IsEmpty() || !IFileManager::Get().DirectoryExists(*Root)) {
        AddInfo(TEXT("Supplied reference corpus unavailable; corpus validation not performed."));
        return true;
    }
    TArray<FString> Paths;
    IFileManager::Get().FindFilesRecursive(Paths,*Root,TEXT("beatmap.json"),true,false);
    int32 TotalBeats=0,TotalEvents=0;
    TestEqual(TEXT("All ten supplied beatmaps discovered"),Paths.Num(),10);
    for (const FString& Path:Paths) {
        FRecoveredBeatmapData Data;
        FString Audio,Error;
        if (!TestTrue(TEXT("Load supplied map: ")+Path,URecoveredBeatmapLibrary::LoadBeatmapFile(Path,Data,Audio,Error))) { AddInfo(Error);continue; }
        TestTrue(TEXT("Supplied audio exists"),IFileManager::Get().FileExists(*Audio));
        TotalBeats+=Data.Beats.Num();TotalEvents+=Data.Events.Num();
        for (int32 I=1;I<Data.Beats.Num();++I) TestTrue(TEXT("Native beat sort is nondecreasing"),Data.Beats[I-1].Time<=Data.Beats[I].Time);
    }
    TestEqual(TEXT("All supplied beat records loaded"),TotalBeats,5734);
    TestEqual(TEXT("All supplied control records loaded"),TotalEvents,3876);
    return true;
}
#endif
