#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "Engine/Texture2D.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"
#include "Sound/SoundWave.h"
#include "WidgetBlueprint.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/UnrealType.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredTextureTest,"CockHero.Recovery.WidgetArtwork",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredTextureTest::RunTest(const FString& Parameters) {
    auto Read=[&](const FString& Name,TSharedPtr<FJsonObject>& Object) {
        FString Text;
        return FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence")/Name)) &&
            FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Object);
    };
    TSharedPtr<FJsonObject> Aliases,Evidence;
    if(!Read(TEXT("resource-aliases.json"),Aliases) || !Read(TEXT("ui-layout-values.json"),Evidence)) {
        AddError(TEXT("Missing artwork evidence")); return false;
    }
    TMap<FString,UTexture2D*> Textures;
    TMap<FString,UObject*> Resources;
    for(const auto& Pair:Aliases->Values) {
        if(Pair.Value->AsString().StartsWith(TEXT("/Game/Recovery/Resources/Fonts/")) || Pair.Value->AsString().StartsWith(TEXT("/Game/Recovery/Resources/Audio/")) || Pair.Value->AsString().StartsWith(TEXT("/Game/Recovery/Resources/Video/"))) {
            auto* Resource=LoadObject<UObject>(nullptr,*Pair.Value->AsString());
            if(TestNotNull(*Pair.Key,Resource)) Resources.Add(Pair.Key,Resource);
            continue;
        }
        auto* Texture=LoadObject<UTexture2D>(nullptr,*Pair.Value->AsString());
        if(TestNotNull(*Pair.Key,Texture)) {
            Textures.Add(Pair.Key,Texture);
            Resources.Add(Pair.Key,Texture);
            TestTrue(*(Pair.Key+TEXT(" editable source pixels")),Texture->Source.IsValid());
            TestTrue(*(Pair.Key+TEXT(" source dimensions")),Texture->Source.GetSizeX()>0 && Texture->Source.GetSizeY()>0);
        }
    }
    FString AudioText; TArray<TSharedPtr<FJsonValue>> AudioRows;
    if(FFileHelper::LoadFileToString(AudioText,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/audio-decoding-report.json"))) &&
        FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(AudioText),AudioRows)) {
        for(const auto& Value:AudioRows) {
            const auto Row=Value->AsObject();
            auto* Sound=Cast<USoundWave>(Resources.FindRef(Row->GetStringField(TEXT("original"))));
            if(!TestNotNull(TEXT("Restored editable click sound"),Sound)) continue;
            TArray<uint8> PCM,Wave; uint32 Rate=0; uint16 Channels=0;
            TestTrue(TEXT("Imported audio source available"),Sound->GetImportedSoundWaveData(PCM,Rate,Channels));
            TestEqual(TEXT("Source sample rate"),Rate,uint32(Row->GetNumberField(TEXT("sample_rate"))));
            TestEqual(TEXT("Source channels"),Channels,uint16(Row->GetNumberField(TEXT("channels"))));
            TestEqual(TEXT("Exact source frame count"),PCM.Num(),int32(Row->GetNumberField(TEXT("frames")))*Channels*2);
            const FString File=FPaths::ProjectDir()/TEXT("RecoveryEvidence/AudioSource")/(Row->GetStringField(TEXT("name"))+TEXT(".wav"));
            if(TestTrue(TEXT("Decoded waveform available"),FFileHelper::LoadFileToArray(Wave,*File))) {
                TestEqual(TEXT("Decoded WAV size"),Wave.Num(),PCM.Num()+44);
                if(Wave.Num()==PCM.Num()+44) TestTrue(TEXT("Audio source preserved byte for byte"),FMemory::Memcmp(PCM.GetData(),Wave.GetData()+44,PCM.Num())==0);
            }
        }
    }
    auto* Font=Cast<UFont>(Resources.FindRef(TEXT("/Engine/EngineFonts/horizon_Font.horizon_Font")));
    auto* Face=Cast<UFontFace>(Resources.FindRef(TEXT("/Engine/EngineFonts/horizon.horizon")));
    if(TestNotNull(TEXT("Recovered composite font"),Font) && TestNotNull(TEXT("Recovered font face"),Face)) {
        TestTrue(TEXT("Runtime font cache preserved"),Font->FontCacheType==EFontCacheType::Runtime);
        TestEqual(TEXT("Original single typeface"),Font->CompositeFont.DefaultTypeface.Fonts.Num(),1);
        if(Font->CompositeFont.DefaultTypeface.Fonts.Num()==1) {
            TestEqual(TEXT("Original typeface name"),Font->CompositeFont.DefaultTypeface.Fonts[0].Name,FName(TEXT("Default")));
            TestTrue(TEXT("Typeface uses restored payload"),Font->CompositeFont.DefaultTypeface.Fonts[0].Font.GetFontFaceAsset()==Face);
        }
        TArray<uint8> Original;
        TestTrue(TEXT("Original font source available"),FFileHelper::LoadFileToArray(Original,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/FontSource/horizon.otf"))));
        TestTrue(TEXT("Font payload preserved byte for byte"),Face->FontFaceData->GetData()==Original);
    }
    FString ReportText; TArray<TSharedPtr<FJsonValue>> Reports;
    if(!FFileHelper::LoadFileToString(ReportText,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/texture-decoding-report.json"))) ||
        !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(ReportText),Reports)) {
        AddError(TEXT("Missing texture dimensions evidence")); return false;
    }
    for(const auto& Value:Reports) {
        const auto Row=Value->AsObject();
        if(!Row->GetBoolField(TEXT("success"))) continue;
        auto* Texture=Textures.FindRef(Row->GetStringField(TEXT("original")));
        if(!TestNotNull(TEXT("Every exported texture imported"),Texture)) continue;
        TestEqual(TEXT("Source width"),Texture->Source.GetSizeX(),int64(Row->GetNumberField(TEXT("width"))));
        TestEqual(TEXT("Source height"),Texture->Source.GetSizeY(),int64(Row->GetNumberField(TEXT("height"))));
        TestEqual(TEXT("Source color space"),bool(Texture->SRGB),Row->GetBoolField(TEXT("srgb")));
    }
    int32 Checked=0;
    TFunction<void(UStruct*,void*,const TSharedPtr<FJsonObject>&,const TSharedPtr<FJsonObject>&)> Verify;
    Verify=[&](UStruct* Type,void* Data,const TSharedPtr<FJsonObject>& Values,const TSharedPtr<FJsonObject>& Imports) {
        for(const auto& Pair:Values->Values) {
            auto* Property=FindFProperty<FProperty>(Type,*Pair.Key);
            if(!Property || Pair.Value->Type!=EJson::Object) continue;
            void* Address=Property->ContainerPtrToValuePtr<void>(Data);
            const auto Value=Pair.Value->AsObject();
            if(auto* Object=CastField<FObjectPropertyBase>(Property)) {
                double Index; FString Original;
                if(Value->TryGetNumberField(TEXT("index"),Index) && Index<0 && Imports->TryGetStringField(FString::FromInt(int32(Index)),Original) && Resources.Contains(Original)) {
                    TestTrue(*(Original+TEXT(" widget reference restored")),Object->GetObjectPropertyValue(Address)==Resources[Original]); ++Checked;
                }
            } else if(auto* Struct=CastField<FStructProperty>(Property)) Verify(Struct->Struct,Address,Value,Imports);
        }
    };
    TMap<FString,UWidgetBlueprint*> Screens;
    for(const auto& Value:Evidence->GetArrayField(TEXT("widgets"))) {
        const auto Row=Value->AsObject(); const FString Screen=Row->GetStringField(TEXT("asset"));
        if(!Screens.Contains(Screen)) Screens.Add(Screen,LoadObject<UWidgetBlueprint>(nullptr,*(TEXT("/Game/Recovery/UI/")+Screen+TEXT(".")+Screen)));
        auto* Blueprint=Screens[Screen]; if(!Blueprint) { AddError(Screen+TEXT(" missing widget")); continue; }
        if(auto* Widget=Blueprint->WidgetTree->FindWidget(FName(*Row->GetStringField(TEXT("name")))))
            Verify(Widget->GetClass(),Widget,Row->GetObjectField(TEXT("values")),Evidence->GetObjectField(TEXT("imports"))->GetObjectField(Screen));
    }
    TestTrue(TEXT("Recovered textures connected to widget properties"),Checked>0);
    AddInfo(FString::Printf(TEXT("Verified %d editable textures and %d widget artwork references"),Textures.Num(),Checked));
    return true;
}
#endif
