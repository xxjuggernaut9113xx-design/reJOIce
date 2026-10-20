#include "RecoveredDialogueAudio.h"
#include "Audio.h"
#include "BinkAudioInfo.h"
#include "Dom/JsonObject.h"
#include "Interfaces/IAudioFormat.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/SecureHash.h"
#include "Modules/ModuleManager.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundWaveProcedural.h"
#include "UObject/Package.h"

namespace {
FString NormalizeDialogueKey(FString Value)
{
    Value.TrimStartAndEndInline();
    Value.ToLowerInline();
    Value.ReplaceInline(TEXT("_"),TEXT(""));
    Value.ReplaceInline(TEXT(" "),TEXT(""));
    Value.ReplaceInline(TEXT("-"),TEXT(""));
    return Value;
}
TSharedPtr<FJsonObject> GetDialogueCatalog()
{
    static const TSharedPtr<FJsonObject> Catalog=[]()
    {
        FString Text;
        TSharedPtr<FJsonObject> Result;
        const FString Path=FPaths::ProjectContentDir()/TEXT("Recovery/Definitions/newer-20261017-dialogue-catalog.json");
        if (!FFileHelper::LoadFileToString(Text,*Path)||!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Result)||!Result.IsValid())
        {
            UE_LOG(LogTemp,Error,TEXT("Source dialogue catalog is unavailable: %s"),*Path);
            return TSharedPtr<FJsonObject>();
        }
        return Result;
    }();
    return Catalog;
}
FString ResolveCategory(FString Request)
{
    if (Request.StartsWith(TEXT("SpecialEvent_")))
    {
        const FString Index=Request.Mid(13);
        const auto Catalog=GetDialogueCatalog();
        const TSharedPtr<FJsonObject>* Categories=nullptr;
        FString Category;
        if (Catalog.IsValid()&&Catalog->TryGetObjectField(TEXT("event_categories"),Categories)&&(*Categories)->TryGetStringField(Index,Category)) return Category;
        return FString();
    }
    Request.RemoveFromStart(TEXT("Generic_"));
    Request.RemoveFromEnd(TEXT("_DLS"));
    Request.RemoveFromEnd(TEXT("_DDT"));
    if (Request.Equals(TEXT("DefensiveItemUse"),ESearchCase::IgnoreCase)) return TEXT("defensiveitemusage");
    return Request;
}
bool CategoryMatches(const FString& Category,const FString& Request)
{
    const FString Key=NormalizeDialogueKey(Category);
    const FString Wanted=NormalizeDialogueKey(Request);
    if (Key==Wanted) return true;
    if (Wanted==TEXT("postgamewin")) return Key==TEXT("postgamevictory");
    if (Wanted==TEXT("postgameloss")) return Key==TEXT("postgamedefeat");
    return false;
}
USoundBase* DecodeSourceStream(const FString& Relative,const TSharedPtr<FJsonObject>& Record)
{
    if (!Relative.StartsWith(TEXT("Recovery/Definitions/NewerDialogueAudio/"))||Relative.Contains(TEXT(".."))||Relative.Contains(TEXT(":"))) return nullptr;
    TArray<uint8> Encoded;
    const FString Filename=FPaths::ProjectContentDir()/Relative;
    FString ExpectedSHA;
    if (!Record.IsValid()||!Record->TryGetStringField(TEXT("sha1"),ExpectedSHA)||!FFileHelper::LoadFileToArray(Encoded,*Filename)||Encoded.Num()<28||Encoded.Num()>64*1024*1024||FMemory::Memcmp(Encoded.GetData(),"ABEU",4)!=0) return nullptr;
    uint8 Hash[FSHA1::DigestSize];
    FSHA1::HashBuffer(Encoded.GetData(),Encoded.Num(),Hash);
    if (!BytesToHex(Hash,UE_ARRAY_COUNT(Hash)).Equals(ExpectedSHA,ESearchCase::IgnoreCase)) return nullptr;
    uint32 Frames=0,Rate=0;
    FMemory::Memcpy(&Rate,Encoded.GetData()+8,4);
    FMemory::Memcpy(&Frames,Encoded.GetData()+12,4);
    const uint8 Channels=Encoded[5];
    const uint64 PCMBytes=uint64(Frames)*Channels*2;
    if (Encoded[4]!=1||Channels<1||Channels>2||Rate<8000||Rate>192000||PCMBytes==0||PCMBytes>256*1024*1024) return nullptr;
    if (!FModuleManager::Get().LoadModulePtr<IModuleInterface>(TEXT("BinkAudioDecoder"))) return nullptr;
    TUniquePtr<ICompressedAudioInfo> Decoder(IAudioInfoFactoryRegistry::Get().Create(TEXT("BINKA")));
    FSoundQualityInfo Quality{};
    if (!Decoder||!Decoder->ReadCompressedInfo(Encoded.GetData(),Encoded.Num(),&Quality)||Quality.NumChannels!=Channels||Quality.SampleRate!=Rate||Quality.SampleDataSize!=PCMBytes) return nullptr;
    TArray<uint8> PCM;
    PCM.SetNumUninitialized(int32(Quality.SampleDataSize));
    Decoder->ExpandFile(PCM.GetData(),&Quality);
    if (Decoder->HasError()) return nullptr;
    auto* Wave=NewObject<USoundWaveProcedural>(GetTransientPackage());
    Wave->SetSampleRate(Quality.SampleRate);
    Wave->NumChannels=Quality.NumChannels;
    Wave->Duration=float(Frames)/Rate;
    Wave->SoundGroup=SOUNDGROUP_Voice;
    Wave->bLooping=false;
    Wave->QueueAudio(PCM.GetData(),PCM.Num());
    return Wave;
}
}

FString GetRecoveredCanonicalVoicePack(const FString& VoicePack)
{
    const FString Key=NormalizeDialogueKey(VoicePack);
    if (Key==TEXT("default")||Key==TEXT("villainess")) return TEXT("Default");
    if (Key==TEXT("brat")||Key==TEXT("teasingbrat")) return TEXT("Brat");
    if (Key==TEXT("dommymommy")) return TEXT("DommyMommy");
    if (Key==TEXT("sweetheart")) return TEXT("Sweetheart");
    if (Key==TEXT("yandere")) return TEXT("Yandere");
    if (Key==TEXT("chariot")||Key==TEXT("chariot(mini)")) return TEXT("Chariot");
    if (Key==TEXT("pepper")||Key==TEXT("pepper(mini)")) return TEXT("Pepper");
    return FString();
}

FString GetRecoveredDialoguePronoun(int32 Selection)
{
    static const TCHAR* Pronouns[]={TEXT("Male"),TEXT("Female"),TEXT("Neutral")};
    return Pronouns[FMath::Clamp(Selection,0,2)];
}

USoundBase* SelectRecoveredSourceDialogue(const FString& VoicePack,const FString& Request,const FString& Pronoun,FString* SelectedRow)
{
    if (SelectedRow) SelectedRow->Reset();
    const auto Catalog=GetDialogueCatalog();
    const TSharedPtr<FJsonObject>* Packs=nullptr;
    const TSharedPtr<FJsonObject>* Streams=nullptr;
    const TArray<TSharedPtr<FJsonValue>>* Rows=nullptr;
    const FString Pack=GetRecoveredCanonicalVoicePack(VoicePack);
    const FString Category=ResolveCategory(Request);
    if (!Catalog.IsValid()||Pack.IsEmpty()||Category.IsEmpty()||!Catalog->TryGetObjectField(TEXT("packs"),Packs)||!Catalog->TryGetObjectField(TEXT("audio_streams"),Streams)||!(*Packs)->TryGetArrayField(Pack,Rows)) return nullptr;
    TArray<TSharedPtr<FJsonObject>> Candidates;
    for (const auto& Value:*Rows)
    {
        const auto Row=Value->AsObject();
        FString RowName,RowCategory,RowPronoun,Audio;
        if (!Row.IsValid()||!Row->TryGetStringField(TEXT("row"),RowName)||!Row->TryGetStringField(TEXT("Category"),RowCategory)||!Row->TryGetStringField(TEXT("Pronoun"),RowPronoun)||!Row->TryGetStringField(TEXT("AudioStream"),Audio)||Audio.IsEmpty()) continue;
        if (!(RowName.Equals(Request,ESearchCase::IgnoreCase)||CategoryMatches(RowCategory,Category))) continue;
        RowPronoun.TrimStartAndEndInline();
        if (!RowPronoun.IsEmpty()&&!RowPronoun.Equals(TEXT("neutral"),ESearchCase::IgnoreCase)&&!RowPronoun.Equals(Pronoun.TrimStartAndEnd(),ESearchCase::IgnoreCase)) continue;
        Candidates.Add(Row);
    }
    if (Candidates.IsEmpty()) return nullptr;
    const auto Selected=Candidates[FMath::RandRange(0,Candidates.Num()-1)];
    const FString Relative=Selected->GetStringField(TEXT("AudioStream"));
    const TSharedPtr<FJsonObject>* Stream=nullptr;
    if (!(*Streams)->TryGetObjectField(Relative,Stream)) return nullptr;
    USoundBase* Sound=DecodeSourceStream(Relative,*Stream);
    if (Sound&&SelectedRow) *SelectedRow=Selected->GetStringField(TEXT("row"));
    if (!Sound) UE_LOG(LogTemp,Error,TEXT("Source dialogue stream failed integrity/decoding validation: %s"),*Relative);
    return Sound;
}

USoundBase* SelectRecoveredPaceDialogue(const FString& VoicePack,uint8 Pace,const TArray<FString>& Tags,const FString& Pronoun,bool bSPHEnabled,FString* SelectedRow)
{
    if (SelectedRow) SelectedRow->Reset();
    if (Pace>2) return nullptr;
    const auto Catalog=GetDialogueCatalog();
    const TSharedPtr<FJsonObject>* Packs=nullptr;
    const TSharedPtr<FJsonObject>* Streams=nullptr;
    const TArray<TSharedPtr<FJsonValue>>* Rows=nullptr;
    const FString Pack=GetRecoveredCanonicalVoicePack(VoicePack);
    if (!Catalog.IsValid()||Pack.IsEmpty()||!Catalog->TryGetObjectField(TEXT("packs"),Packs)||!Catalog->TryGetObjectField(TEXT("audio_streams"),Streams)||!(*Packs)->TryGetArrayField(Pack,Rows)) return nullptr;
    TArray<TSharedPtr<FJsonObject>> PerTagCandidates;
    for (FString Tag:Tags)
    {
        Tag.TrimStartAndEndInline();
        Tag.ToLowerInline();
        if (Tag==TEXT("small_penis")&&!bSPHEnabled) continue;
        TArray<TSharedPtr<FJsonObject>> Matching;
        for (const auto& Value:*Rows)
        {
            const auto Row=Value->AsObject();
            FString Category,RowPronoun,Audio;
            if (!Row.IsValid()||!Row->TryGetStringField(TEXT("Category"),Category)||!Row->TryGetStringField(TEXT("Pronoun"),RowPronoun)||!Row->TryGetStringField(TEXT("AudioStream"),Audio)||Audio.IsEmpty()) continue;
            Category.TrimStartAndEndInline();
            if (!Category.Equals(Tag,ESearchCase::IgnoreCase)) continue;
            RowPronoun.TrimStartAndEndInline();
            if (!RowPronoun.IsEmpty()&&!RowPronoun.Equals(TEXT("neutral"),ESearchCase::IgnoreCase)&&!RowPronoun.Equals(Pronoun.TrimStartAndEnd(),ESearchCase::IgnoreCase)) continue;
            Matching.Add(Row);
        }
        if (!Matching.IsEmpty()) PerTagCandidates.Add(Matching[FMath::RandRange(0,Matching.Num()-1)]);
    }
    if (PerTagCandidates.IsEmpty()) return SelectRecoveredSourceDialogue(Pack,Pace==0 ? TEXT("slow") : Pace==1 ? TEXT("medium") : TEXT("fast"),Pronoun,SelectedRow);
    const auto Selected=PerTagCandidates[FMath::RandRange(0,PerTagCandidates.Num()-1)];
    const FString Relative=Selected->GetStringField(TEXT("AudioStream"));
    const TSharedPtr<FJsonObject>* Stream=nullptr;
    if (!(*Streams)->TryGetObjectField(Relative,Stream)) return nullptr;
    USoundBase* Sound=DecodeSourceStream(Relative,*Stream);
    if (Sound&&SelectedRow) *SelectedRow=Selected->GetStringField(TEXT("row"));
    return Sound;
}
