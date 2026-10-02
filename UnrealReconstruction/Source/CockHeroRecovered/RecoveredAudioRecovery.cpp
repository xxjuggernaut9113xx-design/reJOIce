#include "RecoveredAudioRecovery.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
#if WITH_EDITOR
#include "Audio.h"
#include "Interfaces/IAudioFormat.h"
#include "BinkAudioInfo.h"
#include "Modules/ModuleManager.h"
#endif

FString URecoveredAudioRecovery::DecodeBinkAudio(const FString& EncodedFile,const FString& AssetName) {
    auto Result=MakeShared<FJsonObject>(); Result->SetBoolField(TEXT("success"),false);
#if WITH_EDITOR
    TArray<uint8> Encoded;
    if(AssetName.IsEmpty() || AssetName.Contains(TEXT("..")) || AssetName.Contains(TEXT("/")) || AssetName.Contains(TEXT("\\")) || AssetName.Contains(TEXT(":")) ||
        !FFileHelper::LoadFileToArray(Encoded,*EncodedFile) || Encoded.Num()<28 || Encoded.Num()>64*1024*1024 || FMemory::Memcmp(Encoded.GetData(),"ABEU",4)!=0) {
        Result->SetStringField(TEXT("error"),TEXT("Invalid reconstructed Bink audio input"));
    } else {
        uint32 Samples=0,Rate=0; FMemory::Memcpy(&Rate,Encoded.GetData()+8,4); FMemory::Memcpy(&Samples,Encoded.GetData()+12,4);
        const uint8 Channels=Encoded[5];
        if(Encoded[4]!=1 || Channels<1 || Channels>16 || Rate==0 || uint64(Samples)*Channels*2>256*1024*1024) {
            Result->SetStringField(TEXT("error"),TEXT("Unsupported Bink audio dimensions"));
        } else {
            FModuleManager::Get().LoadModuleChecked<IModuleInterface>(TEXT("BinkAudioDecoder"));
            TUniquePtr<ICompressedAudioInfo> Decoder(IAudioInfoFactoryRegistry::Get().Create(TEXT("BINKA"))); FSoundQualityInfo Quality{};
            if(!Decoder || !Decoder->ReadCompressedInfo(Encoded.GetData(),Encoded.Num(),&Quality)) Result->SetStringField(TEXT("error"),TEXT("Bink decoder rejected source stream"));
            else {
                TArray<uint8> PCM; PCM.SetNumZeroed(Quality.SampleDataSize);
                Decoder->ExpandFile(PCM.GetData(),&Quality);
                if(Decoder->HasError()) Result->SetStringField(TEXT("error"),TEXT("Bink decoder reported a payload error"));
                else {
                    TArray<uint8> Wave;
                    auto Tag=[&](const ANSICHAR* Value){ Wave.Append(reinterpret_cast<const uint8*>(Value),4); };
                    auto U32=[&](uint32 Value){ Wave.Append(reinterpret_cast<const uint8*>(&Value),4); };
                    auto U16=[&](uint16 Value){ Wave.Append(reinterpret_cast<const uint8*>(&Value),2); };
                    Tag("RIFF"); U32(36+PCM.Num()); Tag("WAVE"); Tag("fmt "); U32(16); U16(1); U16(Quality.NumChannels);
                    U32(Quality.SampleRate); U32(Quality.SampleRate*Quality.NumChannels*2); U16(Quality.NumChannels*2); U16(16);
                    Tag("data"); U32(PCM.Num()); Wave.Append(PCM);
                    const FString Output=FPaths::ProjectDir()/TEXT("RecoveryEvidence/AudioSource")/(AssetName+TEXT(".wav"));
                    IFileManager::Get().MakeDirectory(*FPaths::GetPath(Output),true);
                    Result->SetBoolField(TEXT("success"),FFileHelper::SaveArrayToFile(Wave,*Output));
                    Result->SetStringField(TEXT("file"),Output);
                    Result->SetNumberField(TEXT("sample_rate"),Quality.SampleRate); Result->SetNumberField(TEXT("channels"),Quality.NumChannels);
                    Result->SetNumberField(TEXT("frames"),Samples); Result->SetNumberField(TEXT("pcm_bytes"),PCM.Num());
                }
            }
        }
    }
#else
    Result->SetStringField(TEXT("error"),TEXT("Audio recovery requires the editor"));
#endif
    FString Text; FJsonSerializer::Serialize(Result,TJsonWriterFactory<>::Create(&Text)); return Text;
}
