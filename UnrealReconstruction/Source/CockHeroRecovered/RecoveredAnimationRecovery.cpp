#include "RecoveredWidgetRecovery.h"
#include "RecoveredEventWidgets.h"
#include "Misc/FileHelper.h"
#include "Misc/Base64.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/MemoryReader.h"
#include "Serialization/CustomVersion.h"
#include "UObject/ObjectVersion.h"
#include "Serialization/ArchiveUObject.h"
#include "Modules/ModuleManager.h"
#include "Animation/WidgetAnimation.h"
#include "MovieScene.h"
#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Misc/PackageName.h"
#include "UObject/SavePackage.h"
#endif

#if WITH_EDITOR
namespace {
class FRecoveredAnimationReader : public FMemoryReader {
public:
    FRecoveredAnimationReader(const TArray<uint8>& Bytes,const TArray<FString>& InNames,const TArray<UObject*>& InObjects,const TArray<UObject*>& InImports,TSet<int32>& InMissing)
        :FMemoryReader(Bytes,true),Names(InNames),Objects(InObjects),Imports(InImports),Missing(InMissing) {
        SetUseUnversionedPropertySerialization(true);ArIsFilterEditorOnly=true;
        SetUEVer(FPackageFileVersion(VER_UE4_CORRECT_LICENSEE_FLAG,EUnrealEngineObjectUE5Version::DATA_RESOURCES));SetCustomVersions(FCurrentCustomVersions::GetAll());
    }
    virtual FArchive& operator<<(FName& Name) override {
        int32 Index=0,Number=0;Serialize(&Index,4);Serialize(&Number,4);
        if (!Names.IsValidIndex(Index) || Number<0) { SetError();Name=NAME_None; }
        else Name=FName(*Names[Index],Number);
        return *this;
    }
    virtual FArchive& operator<<(UObject*& Object) override {
        int32 Index=0;Serialize(&Index,4);
        if (Index<0) { Object=Imports.IsValidIndex(-Index-1)?Imports[-Index-1]:nullptr;if (!Object) Missing.Add(Index); }
        else if (Index==0) Object=nullptr;
        else if (Objects.IsValidIndex(Index)) { Object=Objects[Index];if (!Object) Missing.Add(Index); }
        else { Object=nullptr;SetError(); }
        return *this;
    }
    virtual FArchive& operator<<(FObjectPtr& Value) override { return FArchiveUObject::SerializeObjectPtr(*this,Value); }
    virtual FArchive& operator<<(FWeakObjectPtr& Value) override { return FArchiveUObject::SerializeWeakObjectPtr(*this,Value); }
    virtual FArchive& operator<<(FLazyObjectPtr& Value) override { return FArchiveUObject::SerializeLazyObjectPtr(*this,Value); }
    virtual FArchive& operator<<(FSoftObjectPtr& Value) override { return FArchiveUObject::SerializeSoftObjectPtr(*this,Value); }
    virtual FArchive& operator<<(FSoftObjectPath& Value) override { return FArchiveUObject::SerializeSoftObjectPath(*this,Value); }
private:
    const TArray<FString>& Names;
    const TArray<UObject*>& Objects;
    const TArray<UObject*>& Imports;
    TSet<int32>& Missing;
};
}
#endif

static FString RecoverAnimationData(const FString& DecodedAssetPath,const FString& BlueprintPath) {
    auto Report=MakeShared<FJsonObject>();Report->SetBoolField(TEXT("saved_assets"),false);
    TArray<TSharedPtr<FJsonValue>> Results;
#if WITH_EDITOR
    FString Text;TSharedPtr<FJsonObject> Asset;
    if (!FFileHelper::LoadFileToString(Text,*DecodedAssetPath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Asset) || !Asset) { Report->SetStringField(TEXT("error"),TEXT("Could not read decoded asset")); }
    else {
        UWidgetBlueprint* Blueprint=BlueprintPath.IsEmpty()?nullptr:LoadObject<UWidgetBlueprint>(nullptr,*BlueprintPath);
        if (!BlueprintPath.IsEmpty() && !Blueprint) return TEXT("{\"error\":\"Blueprint not found\"}");
        if (Blueprint && URecoveredAnimatedOverlay::SupportsAsset(Blueprint->GetFName())) Blueprint->ParentClass=URecoveredAnimatedOverlay::StaticClass();
        if (Blueprint && Blueprint->GetName()==TEXT("UMG_BeatIcon")) { Blueprint->ParentClass=URecoveredBeatWidget::StaticClass(); }
        FModuleManager::Get().LoadModule(TEXT("MovieScene"));FModuleManager::Get().LoadModule(TEXT("MovieSceneTracks"));
        const auto& Exports=Asset->GetArrayField(TEXT("Exports"));const auto& Imports=Asset->GetArrayField(TEXT("Imports"));
        TArray<FString> Names;for (const auto& Value:Asset->GetArrayField(TEXT("NameMap"))) Names.Add(Value->AsString());
        TArray<UObject*> Objects;Objects.SetNumZeroed(Exports.Num()+1);
        TArray<UClass*> Classes;Classes.SetNumZeroed(Exports.Num()+1);
        TArray<int32> Parents;Parents.SetNumZeroed(Exports.Num()+1);
        TArray<TArray<uint8>> Payloads;Payloads.SetNum(Exports.Num()+1);
        TFunction<FString(int32)> ImportPath=[&](int32 Index)->FString {
            if (Index>=0 || !Imports.IsValidIndex(-Index-1)) return TEXT("");
            const auto Object=Imports[-Index-1]->AsObject();const FString Name=Object->GetStringField(TEXT("ObjectName"));
            const int32 Outer=Object->GetIntegerField(TEXT("OuterIndex"));
            return Outer<0 ? ImportPath(Outer)+TEXT(".")+Name : Name;
        };
        TArray<UObject*> ImportObjects;ImportObjects.SetNumZeroed(Imports.Num());
        TSharedPtr<FJsonObject> Aliases;FString AliasText;
        if (FFileHelper::LoadFileToString(AliasText,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/resource-aliases.json")))) FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(AliasText),Aliases);
        for (int32 I=0;I<Imports.Num();++I) {
            FString Path=ImportPath(-I-1),Alias;
            if (Aliases && Aliases->TryGetStringField(Path,Alias)) Path=Alias;
            if (Path.StartsWith(TEXT("/Script/"))) ImportObjects[I]=StaticLoadObject(UObject::StaticClass(),nullptr,*Path,nullptr,LOAD_NoWarn|LOAD_Quiet);
            else if (Path.StartsWith(TEXT("/Engine/"))) ImportObjects[I]=StaticLoadObject(UObject::StaticClass(),nullptr,*Path,nullptr,LOAD_NoWarn|LOAD_Quiet);
            else if (Aliases && !Alias.IsEmpty()) ImportObjects[I]=LoadObject<UObject>(nullptr,*Path);
        }
        for (int32 I=0;I<Exports.Num();++I) {
            const auto Export=Exports[I]->AsObject();const int32 ClassIndex=Export->GetIntegerField(TEXT("ClassIndex"));
            if (ClassIndex>=0 || !Imports.IsValidIndex(-ClassIndex-1)) continue;
            const FString Name=Imports[-ClassIndex-1]->AsObject()->GetStringField(TEXT("ObjectName"));
            if (Name!=TEXT("WidgetAnimation") && !Name.StartsWith(TEXT("MovieScene"))) continue;
            FString Data;if (!Export->TryGetStringField(TEXT("Data"),Data) || !FBase64::Decode(Data,Payloads[I+1])) continue;
            Classes[I+1]=LoadObject<UClass>(nullptr,*ImportPath(ClassIndex));Parents[I+1]=Export->GetIntegerField(TEXT("OuterIndex"));
        }
        TFunction<UObject*(int32)> Create=[&](int32 Index)->UObject* {
            if (!Classes.IsValidIndex(Index) || !Classes[Index]) return GetTransientPackage();
            if (Objects[Index]) return Objects[Index];
            UObject* Outer=Parents[Index]>0 && Classes.IsValidIndex(Parents[Index]) && Classes[Parents[Index]] ? Create(Parents[Index]) : GetTransientPackage();
            const FString Name=Exports[Index-1]->AsObject()->GetStringField(TEXT("ObjectName"));
            Objects[Index]=NewObject<UObject>(Outer,Classes[Index],MakeUniqueObjectName(Outer,Classes[Index],FName(*Name)),RF_Transient);
            return Objects[Index];
        };
        for (int32 I=1;I<Classes.Num();++I) if (Classes[I]) Create(I);
        if (Blueprint) for (int32 I=0;I<Exports.Num();++I) {
            const auto Export=Exports[I]->AsObject();
            if (!Objects[I+1]) Objects[I+1]=Blueprint->ParentClass->FindFunctionByName(FName(*Export->GetStringField(TEXT("ObjectName"))));
        }
        TGuardValue<int32> UnversionedGuard(GAllowUnversionedContentInEditor,1);
        for (int32 I=1;I<Objects.Num();++I) if (Objects[I] && Classes[I]) {
            TSet<int32> Missing;
            FRecoveredAnimationReader Reader(Payloads[I],Names,Objects,ImportObjects,Missing);
            for (const auto& Version:Asset->GetArrayField(TEXT("CustomVersionContainer"))) {
                const auto Record=Version->AsObject();FGuid Guid;
                if (FGuid::Parse(Record->GetStringField(TEXT("Key")),Guid)) Reader.SetCustomVersion(Guid,Record->GetIntegerField(TEXT("Version")),NAME_None);
            }
            Objects[I]->Serialize(Reader);
            auto Result=MakeShared<FJsonObject>();Result->SetNumberField(TEXT("export_index"),I);
            Result->SetStringField(TEXT("name"),Exports[I-1]->AsObject()->GetStringField(TEXT("ObjectName")));
            Result->SetStringField(TEXT("class"),Classes[I]->GetName());Result->SetNumberField(TEXT("bytes"),Payloads[I].Num());Result->SetNumberField(TEXT("consumed"),Reader.Tell());
            Result->SetBoolField(TEXT("decoded"),!Reader.IsError() && Reader.Tell()==Payloads[I].Num());TArray<TSharedPtr<FJsonValue>> MissingValues;for (int32 Index:Missing) MissingValues.Add(MakeShared<FJsonValueNumber>(Index));Result->SetArrayField(TEXT("unresolved_references"),MissingValues);Results.Add(MakeShared<FJsonValueObject>(Result));
        }
        if (Blueprint) {
            bool Valid=true;for (const auto& Result:Results) { Valid &= Result->AsObject()->GetBoolField(TEXT("decoded"));Valid &= Result->AsObject()->GetArrayField(TEXT("unresolved_references")).IsEmpty(); }
            Report->SetBoolField(TEXT("complete_references"),Valid);
            if (Valid) {
                Blueprint->Modify();Blueprint->Animations.Empty();
                for (int32 Index=1;Index<Objects.Num();++Index) if (auto* Animation=Cast<UWidgetAnimation>(Objects[Index])) {
                    FString Name=Exports[Index-1]->AsObject()->GetStringField(TEXT("ObjectName"));Name.RemoveFromEnd(TEXT("_INST"));
                    if (UObject* Existing=FindObject<UObject>(Blueprint,*Name)) Existing->Rename(nullptr,GetTransientPackage(),REN_DontCreateRedirectors|REN_NonTransactional);
                    Animation->Rename(*Name,Blueprint,REN_DontCreateRedirectors|REN_NonTransactional);
                    TArray<UObject*> Children;GetObjectsWithOuter(Animation,Children,true);Animation->ClearFlags(RF_Transient);Animation->SetFlags(RF_Transactional);
                    for (UObject* Child:Children) { Child->ClearFlags(RF_Transient);Child->SetFlags(RF_Transactional); }
                    Blueprint->Animations.Add(Animation);
                }
                FKismetEditorUtilities::CompileBlueprint(Blueprint);
                if (Blueprint->Status!=BS_Error) {
                    UPackage* Package=Blueprint->GetOutermost();Package->MarkPackageDirty();FSavePackageArgs Args;Args.TopLevelFlags=RF_Public|RF_Standalone;Args.SaveFlags=SAVE_NoError;
                    Report->SetBoolField(TEXT("saved_assets"),UPackage::SavePackage(Package,Blueprint,*FPackageName::LongPackageNameToFilename(Package->GetName(),FPackageName::GetAssetPackageExtension()),Args));
                }
                Report->SetNumberField(TEXT("animation_count"),Blueprint->Animations.Num());
            }
        }
    }
#endif
    Report->SetArrayField(TEXT("objects"),Results);FString Json;FJsonSerializer::Serialize(Report,TJsonWriterFactory<>::Create(&Json));return Json;
}

FString URecoveredWidgetRecovery::ProbeAnimationData(const FString& Path) { return RecoverAnimationData(Path,TEXT("")); }
FString URecoveredWidgetRecovery::RestoreAnimationData(const FString& Path,const FString& BlueprintPath) { return RecoverAnimationData(Path,BlueprintPath); }
