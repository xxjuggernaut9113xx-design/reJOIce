#include "RecoveredTextureRecovery.h"
#include "Engine/Texture2D.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/UObjectGlobals.h"
#include "PixelFormat.h"
#include "Engine/Font.h"
#include "Engine/FontFace.h"
#include "UObject/SavePackage.h"

FString URecoveredTextureRecovery::ExportCookedMip(const FString& ContentDirectory,const FString& RelativeAssetPath) {
    auto Result=MakeShared<FJsonObject>();
    Result->SetBoolField(TEXT("success"),false);
#if WITH_EDITOR
    if(RelativeAssetPath.Contains(TEXT("..")) || RelativeAssetPath.Contains(TEXT(":")) || RelativeAssetPath.StartsWith(TEXT("/"))) {
        Result->SetStringField(TEXT("error"),TEXT("Expected a relative recovered asset path"));
    } else {
        const FString Mount=TEXT("/RecoveryCooked/");
        FString Directory=FPaths::ConvertRelativePathToFull(ContentDirectory); FPaths::NormalizeDirectoryName(Directory); Directory+=TEXT("/");
        FPackageName::RegisterMountPoint(Mount,Directory);
        TGuardValue<int32> CookedGuard(GAllowCookedDataInEditorBuilds,1);
        TGuardValue<int32> UnversionedGuard(GAllowUnversionedContentInEditor,1);
        FString PackagePath=RelativeAssetPath; PackagePath.RemoveFromEnd(TEXT(".uasset"));
        const FString Name=FPaths::GetBaseFilename(PackagePath);
        const FString ObjectPath=Mount+PackagePath+TEXT(".")+Name;
        UTexture2D* Texture=LoadObject<UTexture2D>(nullptr,*ObjectPath,nullptr,LOAD_NoWarn);
        FTexturePlatformData* Platform=Texture ? Texture->GetPlatformData() : nullptr;
        if(!Platform || Platform->Mips.IsEmpty()) Result->SetStringField(TEXT("error"),TEXT("No cooked texture mip data"));
        else {
            FTexture2DMipMap& Mip=Platform->Mips[0]; const int64 Size=Mip.BulkData.GetBulkDataSize();
            if(Size<=0 || Size>256*1024*1024) Result->SetStringField(TEXT("error"),TEXT("Unsupported mip data size"));
            else {
                void* Bytes=nullptr; Mip.BulkData.GetCopy(&Bytes,false);
                const FString Output=FPaths::ProjectSavedDir()/TEXT("TextureRecovery")/(Name+TEXT(".bin"));
                IFileManager::Get().MakeDirectory(*FPaths::GetPath(Output),true);
                const bool Saved=Bytes && FFileHelper::SaveArrayToFile(TArrayView<const uint8>(static_cast<const uint8*>(Bytes),int32(Size)),*Output);
                FMemory::Free(Bytes);
                Result->SetBoolField(TEXT("success"),Saved);
                Result->SetStringField(TEXT("file"),Output);
                Result->SetStringField(TEXT("format"),GPixelFormats[Platform->PixelFormat].Name);
                Result->SetNumberField(TEXT("width"),Mip.SizeX); Result->SetNumberField(TEXT("height"),Mip.SizeY);
                Result->SetBoolField(TEXT("srgb"),Texture->SRGB);
                Result->SetNumberField(TEXT("bytes"),Size);
            }
        }
        FPackageName::UnRegisterMountPoint(Mount,Directory);
    }
#else
    Result->SetStringField(TEXT("error"),TEXT("Texture recovery requires the editor"));
#endif
    FString Text; FJsonSerializer::Serialize(Result,TJsonWriterFactory<>::Create(&Text));return Text;
}

FString URecoveredTextureRecovery::RecoverHorizonFont(const FString& EvidenceFile,const FString& PayloadFile) {
    auto Result=MakeShared<FJsonObject>(); Result->SetBoolField(TEXT("success"),false);
#if WITH_EDITOR
    TArray<uint8> Payload;
    if(!FFileHelper::LoadFileToArray(Payload,*PayloadFile) || Payload.Num()<12 || Payload.Num()>16*1024*1024) {
        Result->SetStringField(TEXT("error"),TEXT("Invalid recovered font payload"));
    } else {
        FString EvidenceText; TSharedPtr<FJsonObject> Evidence;
        const bool Valid=FFileHelper::LoadFileToString(EvidenceText,*EvidenceFile) && FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(EvidenceText),Evidence);
        if(!Valid || !Evidence->GetObjectField(TEXT("Font"))->GetBoolField(TEXT("byte_identical_roundtrip")) ||
            !Evidence->GetObjectField(TEXT("FontFace"))->GetBoolField(TEXT("byte_identical_roundtrip"))) {
            Result->SetStringField(TEXT("error"),TEXT("Missing byte-verified font evidence"));
        } else {
            const auto FontValues=Evidence->GetObjectField(TEXT("Font"))->GetObjectField(TEXT("values"));
            const auto& Typeface=FontValues->GetObjectField(TEXT("CompositeFont"))->GetObjectField(TEXT("DefaultTypeface"))->GetArrayField(TEXT("Fonts"));
            if(Typeface.Num()!=1 || FontValues->GetObjectField(TEXT("FontCacheType"))->GetNumberField(TEXT("value"))!=1) {
                Result->SetStringField(TEXT("error"),TEXT("Unexpected source horizon typeface"));
                FString Text; FJsonSerializer::Serialize(Result,TJsonWriterFactory<>::Create(&Text)); return Text;
            }
            const FString FacePath=TEXT("/Game/Recovery/Resources/Fonts/horizon");
            const FString FontPath=TEXT("/Game/Recovery/Resources/Fonts/horizon_Font");
            auto Package=[](const FString& Path) {
                if(FPackageName::DoesPackageExist(Path)) LoadPackage(nullptr,*Path,LOAD_None);
                UPackage* P=CreatePackage(*Path); P->FullyLoad(); return P;
            };
            UPackage* FacePackage=Package(FacePath); UPackage* FontPackage=Package(FontPath);
            auto* Face=FindObject<UFontFace>(FacePackage,TEXT("horizon"));
            if(!Face) Face=NewObject<UFontFace>(FacePackage,TEXT("horizon"),RF_Public|RF_Standalone);
            // The only serialized FontFace property is SourceFilename; retain UE5.3 constructor defaults.
            Face->SourceFilename=PayloadFile;
            Face->FontFaceData=FFontFaceData::MakeFontFaceData(MoveTemp(Payload));
            Face->CacheSubFaces();
            auto* Font=FindObject<UFont>(FontPackage,TEXT("horizon_Font"));
            if(!Font) Font=NewObject<UFont>(FontPackage,TEXT("horizon_Font"),RF_Public|RF_Standalone);
            Font->FontCacheType=EFontCacheType::Runtime;
            Font->CompositeFont=FCompositeFont();
            FTypefaceEntry Entry(FName(*Typeface[0]->AsObject()->GetStringField(TEXT("Name"))));
            Entry.Font=FFontData(Face,int32(Typeface[0]->AsObject()->GetObjectField(TEXT("Font"))->GetNumberField(TEXT("subface_index"))));
            Font->CompositeFont.DefaultTypeface.Fonts.Add(Entry);
            auto Save=[](UPackage* P,UObject* Asset,const FString& Path) {
                const FString Filename=FPackageName::LongPackageNameToFilename(Path,FPackageName::GetAssetPackageExtension());
                IFileManager::Get().MakeDirectory(*FPaths::GetPath(Filename),true);
                FSavePackageArgs Args; Args.TopLevelFlags=RF_Public|RF_Standalone; Args.SaveFlags=SAVE_NoError;
                return UPackage::SavePackage(P,Asset,*Filename,Args);
            };
            const bool Saved=Save(FacePackage,Face,FacePath) && Save(FontPackage,Font,FontPath);
            Result->SetBoolField(TEXT("success"),Saved);
            Result->SetStringField(TEXT("font"),FontPath+TEXT(".horizon_Font"));
            Result->SetStringField(TEXT("face"),FacePath+TEXT(".horizon"));
            Result->SetStringField(TEXT("typeface_name"),Font->CompositeFont.DefaultTypeface.Fonts[0].Name.ToString());
            Result->SetNumberField(TEXT("payload_bytes"),Face->FontFaceData->GetData().Num());
        }
    }
#else
    Result->SetStringField(TEXT("error"),TEXT("Font recovery requires the editor"));
#endif
    FString Text; FJsonSerializer::Serialize(Result,TJsonWriterFactory<>::Create(&Text)); return Text;
}
