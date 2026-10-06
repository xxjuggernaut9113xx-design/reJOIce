#include "RecoveredMedia.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

TArray<FString> URecoveredMediaLibrary::ParseFilenameTags(const FString& Filename) {
    // Vocabulary and ordering recovered from native function 0x14818dbb0.
    static const TCHAR* Vocabulary[] = {TEXT("slow"),TEXT("fast"),TEXT("medium"),TEXT("anal"),TEXT("armpits"),TEXT("ass"),TEXT("assjob"),TEXT("bent_over"),TEXT("bikini"),TEXT("blowjob"),TEXT("boobs"),TEXT("bukkake"),TEXT("cameltoe"),TEXT("cowgirl"),TEXT("cum"),TEXT("cunnilingus"),TEXT("doggystyle"),TEXT("facesitting"),TEXT("feet"),TEXT("fingering"),TEXT("footjob"),TEXT("futa"),TEXT("gay"),TEXT("goth"),TEXT("group"),TEXT("handjob"),TEXT("latex"),TEXT("leggings"),TEXT("lingerie"),TEXT("nude"),TEXT("paizuri"),TEXT("pussy"),TEXT("sex"),TEXT("small_penis"),TEXT("spreading"),TEXT("succubus"),TEXT("thighjob"),TEXT("thighs"),TEXT("uniform"),TEXT("upskirt"),TEXT("vaginal")};
    // PDB resolves GetCleanFilename, GetBaseFilename, and FString::ToLower.
    const FString Name = FPaths::GetBaseFilename(Filename).ToLower();
    TArray<FString> Result;
    for (const TCHAR* Tag : Vocabulary) if (Name.Contains(Tag, ESearchCase::CaseSensitive)) Result.Add(Tag);
    return Result;
}

FRecoveredMediaDecks URecoveredMediaLibrary::FilterMedia(const TArray<FRecoveredMediaEntry>& Entries, const TArray<FString>& ExcludedTags, bool bAssPreference, bool bBoobsPreference, bool bFeetPreference) {
    FRecoveredMediaDecks Result;
    int32 Fallback = 0;
    for (const auto& Entry : Entries) {
        const auto Has = [&Entry](const TCHAR* Tag) { return Entry.Tags.ContainsByPredicate([Tag](const FString& Candidate) { return Candidate.Equals(Tag, ESearchCase::IgnoreCase); }); };
        if ((bAssPreference || bBoobsPreference || bFeetPreference) &&
            !((bAssPreference && (Has(TEXT("ass")) || Has(TEXT("assjob")))) ||
              (bBoobsPreference && (Has(TEXT("boobs")) || Has(TEXT("paizuri")))) ||
              (bFeetPreference && (Has(TEXT("feet")) || Has(TEXT("footjob")))))) continue;
        bool bExcluded = false;
        for (const FString& Tag : Entry.Tags) if (ExcludedTags.ContainsByPredicate([&Tag](const FString& Excluded) { return Excluded.Equals(Tag, ESearchCase::IgnoreCase); })) { bExcluded = true; break; }
        if (bExcluded) continue;
        const bool bCategorized = Has(TEXT("slow")) || Has(TEXT("medium")) || Has(TEXT("fast")) || Has(TEXT("cum")) || Has(TEXT("succubus")) || Has(TEXT("ass")) || Has(TEXT("boobs"));
        if (!bCategorized) {
            switch (Fallback++ % 5) {
                case 0: Result.Slow.Add(Entry); break;
                case 1: Result.Medium.Add(Entry); break;
                case 2: Result.Fast.Add(Entry); break;
                case 3: Result.Succubus.Add(Entry); break;
                case 4: Result.Cum.Add(Entry); break;
            }
        }
        // Native code adds once per matching tag, including repeated tags.
        for (const FString& Tag : Entry.Tags) {
            if (Tag.Equals(TEXT("slow"), ESearchCase::IgnoreCase)) Result.Slow.Add(Entry);
            else if (Tag.Equals(TEXT("medium"), ESearchCase::IgnoreCase)) Result.Medium.Add(Entry);
            else if (Tag.Equals(TEXT("fast"), ESearchCase::IgnoreCase)) Result.Fast.Add(Entry);
            else if (Tag.Equals(TEXT("cum"), ESearchCase::IgnoreCase)) Result.Cum.Add(Entry);
            else if (Tag.Equals(TEXT("succubus"), ESearchCase::IgnoreCase)) Result.Succubus.Add(Entry);
            else if (Tag.Equals(TEXT("ass"), ESearchCase::IgnoreCase)) Result.Ass.Add(Entry);
            else if (Tag.Equals(TEXT("boobs"), ESearchCase::IgnoreCase)) Result.Boobs.Add(Entry);
        }
    }
    return Result;
}

bool URecoveredMediaLibrary::ReadPackManifest(const FString& ManifestPath, TArray<FRecoveredMediaEntry>& Entries, FString& Error) {
    Entries.Reset(); Error.Reset();
    FString Text;
    if (!FFileHelper::LoadFileToString(Text, *ManifestPath)) { Error = TEXT("Cannot read pack manifest"); return false; }
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text), Root) || !Root.IsValid()) { Error = TEXT("Invalid manifest JSON"); return false; }
    const TArray<TSharedPtr<FJsonValue>>* Media = nullptr;
    if (!Root->TryGetArrayField(TEXT("media"), Media)) { Error = TEXT("Manifest has no media array"); return false; }
    const FString Directory = FPaths::GetPath(FPaths::ConvertRelativePathToFull(ManifestPath));
    for (const auto& Item : *Media) {
        const auto Object = Item->AsObject();
        FRecoveredMediaEntry Entry;
        if (!Object.IsValid() || !Object->TryGetStringField(TEXT("file"), Entry.File)) { Entries.Reset(); Error = TEXT("Media entry has no file"); return false; }
        Object->TryGetStringField(TEXT("type"), Entry.Type);
        Entry.FullPath = FPaths::IsRelative(Entry.File)
            ? FPaths::ConvertRelativePathToFull(Directory / TEXT("media"), Entry.File)
            : FPaths::ConvertRelativePathToFull(Entry.File);
        Entry.Tags = ParseFilenameTags(Entry.File);
        Entries.Add(MoveTemp(Entry));
    }
    return true;
}
