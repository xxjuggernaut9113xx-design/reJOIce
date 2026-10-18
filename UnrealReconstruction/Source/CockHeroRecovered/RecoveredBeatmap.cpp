#include "RecoveredBeatmap.h"
#include "Dom/JsonObject.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
// Native GetNumberField returns zero for missing/unconvertible values and logs.
// Preserve its value semantics without turning tolerated input into automation errors.
double ReadNativeNumber(const TSharedPtr<FJsonObject>& Object, const TCHAR* Name) {
    double Number = 0;
    Object->TryGetNumberField(Name, Number);
    return Number;
}

void ReadOptionalNativeNumber(const TSharedPtr<FJsonObject>& Object, const TCHAR* Name, double& Out) {
    if (Object->HasField(Name)) Out = ReadNativeNumber(Object, Name);
}

FString NormalizeBeatType(const FString& Type) {
    if (Type.Equals(TEXT("rest"), ESearchCase::IgnoreCase)) return TEXT("rest");
    if (Type.Equals(TEXT("accent"), ESearchCase::IgnoreCase)) return TEXT("accent");
    return TEXT("stroke");
}

FString NormalizeEventType(const FString& Type) {
    if (Type.Equals(TEXT("media_change"), ESearchCase::IgnoreCase) || Type.Equals(TEXT("media_switch"), ESearchCase::IgnoreCase)) return TEXT("media_change");
    for (const TCHAR* Known : {TEXT("dialogue"), TEXT("edge"), TEXT("cum_event"), TEXT("speed_change"), TEXT("cycle_media"), TEXT("background"), TEXT("text"), TEXT("disable_break"), TEXT("grant_break"), TEXT("restore_break")}) {
        if (Type.Equals(Known, ESearchCase::IgnoreCase)) return Known;
    }
    return TEXT("custom");
}

int32 BeatmapEventPriority(const FString& Type) {
    if (Type == TEXT("media_change")) return 0;
    if (Type == TEXT("background")) return 1;
    if (Type == TEXT("cycle_media")) return 2;
    return 3;
}
}

bool URecoveredBeatmapLibrary::ParseBeatmapJson(const FString& Json, FRecoveredBeatmapData& OutData, FString& OutError) {
    OutError.Reset();
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Json);
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(Reader, Root) || !Root.IsValid()) {
        OutError = TEXT("Invalid beatmap JSON object: ") + Reader->GetErrorMessage();
        return false;
    }
    const TSharedPtr<FJsonObject>* Meta = nullptr;
    const TArray<TSharedPtr<FJsonValue>>* Beats = nullptr;
    const TArray<TSharedPtr<FJsonValue>>* Events = nullptr;
    FRecoveredBeatmapData Parsed;
    if (Root->TryGetObjectField(TEXT("meta"), Meta)) {
        (*Meta)->TryGetStringField(TEXT("title"), Parsed.Meta.Title);
        (*Meta)->TryGetStringField(TEXT("artist"), Parsed.Meta.Artist);
        (*Meta)->TryGetStringField(TEXT("author"), Parsed.Meta.Author);
        if (!(*Meta)->TryGetStringField(TEXT("difficulty"), Parsed.Meta.Difficulty)) {
            double Difficulty = 0;
            if ((*Meta)->TryGetNumberField(TEXT("difficulty"), Difficulty)) Parsed.Meta.Difficulty = FString::Printf(TEXT("%.1f"), Difficulty);
        }
        (*Meta)->TryGetStringField(TEXT("audioFile"), Parsed.Meta.AudioFile);
        ReadOptionalNativeNumber(*Meta, TEXT("duration"), Parsed.Meta.Duration);
        ReadOptionalNativeNumber(*Meta, TEXT("bpm"), Parsed.Meta.Bpm);
        ReadOptionalNativeNumber(*Meta, TEXT("offset"), Parsed.Meta.Offset);
    }
    if (Root->TryGetArrayField(TEXT("beats"), Beats)) {
        for (const auto& Entry : *Beats) {
            if (!Entry.IsValid() || Entry->Type != EJson::Object) continue;
            const auto Object = Entry->AsObject();
            FRecoveredBeatmapBeat Beat;
            Beat.Time = ReadNativeNumber(Object, TEXT("time"));
            FString Type;
            Object->TryGetStringField(TEXT("type"), Type);
            Beat.Type = NormalizeBeatType(Type);
            ReadOptionalNativeNumber(Object, TEXT("duration"), Beat.Duration);
            Parsed.Beats.Add(MoveTemp(Beat));
        }
    }
    if (Root->TryGetArrayField(TEXT("events"), Events)) {
        for (const auto& Entry : *Events) {
            if (!Entry.IsValid() || Entry->Type != EJson::Object) continue;
            const auto Object = Entry->AsObject();
            FRecoveredBeatmapEvent Event;
            Event.Time = ReadNativeNumber(Object, TEXT("time"));
            FString Type;
            Object->TryGetStringField(TEXT("type"), Type);
            Event.Type = NormalizeEventType(Type);
            Object->TryGetStringField(TEXT("value"), Event.Value);
            ReadOptionalNativeNumber(Object, TEXT("duration"), Event.Duration);
            Parsed.Events.Add(MoveTemp(Event));
        }
    }
    // Native comparator 0x1482d2c40 treats times within .0001 seconds as equal.
    // Ties do not preserve file order: category, background, cycle, then others.
    Parsed.Beats.Sort([](const FRecoveredBeatmapBeat& A, const FRecoveredBeatmapBeat& B) { return A.Time < B.Time; });
    Parsed.Events.Sort([](const FRecoveredBeatmapEvent& A, const FRecoveredBeatmapEvent& B) {
        if (FMath::Abs(A.Time - B.Time) > 0.0001) return A.Time < B.Time;
        return BeatmapEventPriority(A.Type) < BeatmapEventPriority(B.Type);
    });
    if (Parsed.Beats.IsEmpty()) { OutError = TEXT("beats must contain at least one object"); return false; }
    OutData = MoveTemp(Parsed);
    return true;
}

bool URecoveredBeatmapLibrary::LoadBeatmapFile(const FString& JsonPath, FRecoveredBeatmapData& OutData, FString& OutAudioPath, FString& OutError) {
    OutError.Reset();
    FString Json;
    if (!IFileManager::Get().FileExists(*JsonPath) || !FFileHelper::LoadFileToString(Json, *JsonPath)) { OutError = TEXT("Cannot read beatmap file: ") + JsonPath; return false; }
    FRecoveredBeatmapData Parsed;
    if (!ParseBeatmapJson(Json, Parsed, OutError)) return false;
    FString RelativeAudio = Parsed.Meta.AudioFile;
    if (RelativeAudio.IsEmpty()) { OutError = TEXT("meta.audioFile is missing or empty"); return false; }
    FPaths::NormalizeFilename(RelativeAudio);
    if (!FPaths::IsRelative(RelativeAudio) || RelativeAudio.Contains(TEXT(":"))) {
        OutError = TEXT("meta.audioFile must be relative to the beatmap directory");
        return false;
    }
    FString Directory = FPaths::ConvertRelativePathToFull(FPaths::GetPath(JsonPath));
    FPaths::NormalizeDirectoryName(Directory);
    FString AudioPath = FPaths::ConvertRelativePathToFull(Directory / RelativeAudio);
    FPaths::NormalizeFilename(AudioPath);
    const FString DirectoryPrefix = Directory.EndsWith(TEXT("/")) ? Directory : Directory + TEXT("/");
    if (!AudioPath.StartsWith(DirectoryPrefix, ESearchCase::IgnoreCase)) {
        OutError = TEXT("meta.audioFile must stay inside the beatmap directory");
        return false;
    }
    if (!IFileManager::Get().FileExists(*AudioPath)) { OutError = TEXT("Beatmap audio file is missing: ") + AudioPath; return false; }
    OutData = MoveTemp(Parsed);
    OutAudioPath = MoveTemp(AudioPath);
    return true;
}
