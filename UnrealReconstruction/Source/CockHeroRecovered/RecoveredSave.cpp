#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
const FString RecoverySlot=TEXT("CockHeroRecovered_Standalone_v1");
bool ReadState(const FString& Text,TSharedPtr<FJsonObject>& Object) {
    return Text.Len()<=16*1024*1024 && FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Object) && Object.IsValid();
}
bool WriteSetting(FString& Text,const FString& Name,const TSharedPtr<FJsonValue>& Value) {
    if (Name.IsEmpty() || Name.Len()>256) return false;
    TSharedPtr<FJsonObject> Object;
    if (!ReadState(Text,Object)) return false;
    Object->SetField(Name,Value);
    FString Updated;
    if (!FJsonSerializer::Serialize(Object.ToSharedRef(),TJsonWriterFactory<>::Create(&Updated))) return false;
    Text=MoveTemp(Updated); return true;
}
}
bool URecoveredSaveGame::InitializeRecoveredDefaults() {
    if (!RecoveredDefinition) RecoveredDefinition=LoadObject<URecoveredDefinitionAsset>(nullptr,TEXT("/Game/Recovery/Definitions/DA_BP_CHSaveGame.DA_BP_CHSaveGame"));
    if (!RecoveredDefinition || RecoveredDefinition->SourceClass!=TEXT("BP_CHSaveGame_C")) return false;
    TSharedPtr<FJsonObject> Object;
    if (!ReadState(RecoveredDefinition->SerializedDefaultsJson,Object)) return false;
    StateJson=RecoveredDefinition->SerializedDefaultsJson; RecoveryFormatVersion=1; return true;
}
bool URecoveredSaveGame::IsStateValid() const {
    TSharedPtr<FJsonObject> Object; return RecoveryFormatVersion==1 && ReadState(StateJson,Object);
}
bool URecoveredSaveGame::HasSetting(const FString& Name) const {
    TSharedPtr<FJsonObject> Object;
    return ReadState(StateJson,Object) && Object->HasField(Name);
}
TArray<FString> URecoveredSaveGame::GetStringArraySetting(const FString& Name) const {
    TArray<FString> Result;
    TSharedPtr<FJsonObject> Object;
    if (!ReadState(StateJson,Object)) return Result;
    const TArray<TSharedPtr<FJsonValue>>* Values=nullptr;
    if (!Object->TryGetArrayField(Name,Values)) return Result;
    for (const auto& Value:*Values) { FString Item; if (Value && Value->TryGetString(Item)) Result.Add(Item); }
    return Result;
}
bool URecoveredSaveGame::GetBoolSetting(const FString& Name,bool Fallback) const {
    TSharedPtr<FJsonObject> Object;
    if (!ReadState(StateJson,Object)) return Fallback;
    const auto Value=Object->TryGetField(Name);
    if (!Value) return Fallback;
    if (Value->Type==EJson::Boolean) return Value->AsBool();
    if (Value->Type==EJson::Number) return Value->AsNumber()!=0; // Cooked bool defaults are serialized as 0/1.
    return Fallback;
}
double URecoveredSaveGame::GetNumberSetting(const FString& Name,double Fallback) const {
    TSharedPtr<FJsonObject> Object; double Result;
    return ReadState(StateJson,Object) && Object->TryGetNumberField(Name,Result) ? Result : Fallback;
}
FString URecoveredSaveGame::GetStringSetting(const FString& Name,const FString& Fallback) const {
    TSharedPtr<FJsonObject> Object; FString Result;
    return ReadState(StateJson,Object) && Object->TryGetStringField(Name,Result) ? Result : Fallback;
}
bool URecoveredSaveGame::SetBoolSetting(const FString& Name,bool Value) { return WriteSetting(StateJson,Name,MakeShared<FJsonValueBoolean>(Value)); }
bool URecoveredSaveGame::SetNumberSetting(const FString& Name,double Value) { return FMath::IsFinite(Value) && WriteSetting(StateJson,Name,MakeShared<FJsonValueNumber>(Value)); }
bool URecoveredSaveGame::SetStringSetting(const FString& Name,const FString& Value) { return WriteSetting(StateJson,Name,MakeShared<FJsonValueString>(Value)); }

bool URecoveredGameInstance::LoadRecoveredSave() {
    LastSaveError.Reset();
    URecoveredSaveGame* Loaded=nullptr;
    if (UGameplayStatics::DoesSaveGameExist(RecoverySlot,0)) {
        Loaded=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(RecoverySlot,0));
        if (!Loaded || !Loaded->IsStateValid()) { LastSaveError=TEXT("The separate recovery save is unreadable or has an unsupported format"); return false; }
    } else {
        Loaded=NewObject<URecoveredSaveGame>(this);
        if (!Loaded->InitializeRecoveredDefaults()) { LastSaveError=TEXT("Verified source save defaults are unavailable"); return false; }
    }
    CurrentSave=Loaded;
    return true; // Loading does not write a file.
}
bool URecoveredGameInstance::SaveRecoveredState() {
    if (!CurrentSave || !CurrentSave->IsStateValid()) { LastSaveError=TEXT("No valid recovery state to save"); return false; }
    if (!UGameplayStatics::SaveGameToSlot(CurrentSave,RecoverySlot,0)) { LastSaveError=TEXT("Could not write the separate recovery save"); return false; }
    LastSaveError.Reset(); return true;
}

FText URecoveredSaveGame::GetTextSetting(const FString& Name,const FText& Fallback) const {
    TSharedPtr<FJsonObject> Object;if (!ReadState(StateJson,Object)) return Fallback;
    const auto Value=Object->TryGetField(Name);if (!Value) return Fallback;
    FString Text;if (Value->TryGetString(Text)) return FText::FromString(Text);
    const TSharedPtr<FJsonObject>* Fields=nullptr;
    if (!Value->TryGetObject(Fields) || !Fields || !(*Fields)->TryGetStringField(TEXT("text"),Text)) return Fallback;
    FString Namespace,Key;
    if ((*Fields)->TryGetStringField(TEXT("namespace"),Namespace) && (*Fields)->TryGetStringField(TEXT("key"),Key)) return FText::ChangeKey(Namespace,Key,FText::FromString(Text));
    return FText::FromString(Text);
}

bool URecoveredSaveGame::GetLatencyProfile(FRecoveredLatencyProfile& Profile) const {
    TSharedPtr<FJsonObject> Root;if (!ReadState(StateJson,Root)) return false;
    const TSharedPtr<FJsonObject>* Value=nullptr;if (!Root->TryGetObjectField(TEXT("LatencyProfile"),Value) || !Value) return false;
    FRecoveredLatencyProfile Parsed;const auto Object=*Value;
    auto Number=[&](const TCHAR* Name,float& Target) { double Number;if (!Object->TryGetNumberField(Name,Number) || !FMath::IsFinite(Number) || FMath::Abs(Number)>MAX_flt) return false;Target=float(Number);return true; };
    if (!Number(TEXT("VideoDecodeLatencyMs"),Parsed.VideoDecodeLatencyMs) || !Number(TEXT("AudioLatencyMs"),Parsed.AudioLatencyMs) || !Number(TEXT("UserPerceptionOffsetMs"),Parsed.UserPerceptionOffsetMs) || !Number(TEXT("ToyLatencyMs"),Parsed.ToyLatencyMs) || !Number(TEXT("SystemBufferMs"),Parsed.SystemBufferMs) || !Object->TryGetBoolField(TEXT("bIsCalibrated"),Parsed.bIsCalibrated) || !Object->TryGetStringField(TEXT("ProfileName"),Parsed.ProfileName) || Parsed.ProfileName.Len()>256) return false;
    const TSharedPtr<FJsonObject>* Date=nullptr;
    if (Object->TryGetObjectField(TEXT("CreatedDate"),Date) && Date) {
        FString Ticks;double Numeric=0;int64 ValueTicks=0;
        if ((*Date)->TryGetStringField(TEXT("ticks"),Ticks)) { if (!LexTryParseString(ValueTicks,*Ticks)) return false; }
        else if ((*Date)->TryGetNumberField(TEXT("ticks"),Numeric) && FMath::IsFinite(Numeric) && Numeric>=0 && Numeric<=double(FDateTime::MaxValue().GetTicks())) ValueTicks=int64(Numeric);
        else return false;
        if (ValueTicks<0 || ValueTicks>FDateTime::MaxValue().GetTicks()) return false;
        Parsed.CreatedDate=FDateTime(ValueTicks);
    }
    Profile=MoveTemp(Parsed);return true;
}
bool URecoveredSaveGame::SetLatencyProfile(const FRecoveredLatencyProfile& Profile) {
    if (!FMath::IsFinite(Profile.VideoDecodeLatencyMs) || !FMath::IsFinite(Profile.AudioLatencyMs) || !FMath::IsFinite(Profile.UserPerceptionOffsetMs) || !FMath::IsFinite(Profile.ToyLatencyMs) || !FMath::IsFinite(Profile.SystemBufferMs) || Profile.ProfileName.Len()>256 || Profile.CreatedDate.GetTicks()<0) return false;
    auto Object=MakeShared<FJsonObject>();
    Object->SetNumberField(TEXT("VideoDecodeLatencyMs"),Profile.VideoDecodeLatencyMs);Object->SetNumberField(TEXT("AudioLatencyMs"),Profile.AudioLatencyMs);Object->SetNumberField(TEXT("UserPerceptionOffsetMs"),Profile.UserPerceptionOffsetMs);Object->SetNumberField(TEXT("ToyLatencyMs"),Profile.ToyLatencyMs);Object->SetNumberField(TEXT("SystemBufferMs"),Profile.SystemBufferMs);
    Object->SetStringField(TEXT("ProfileName"),Profile.ProfileName);Object->SetBoolField(TEXT("bIsCalibrated"),Profile.bIsCalibrated);
    auto Date=MakeShared<FJsonObject>();Date->SetStringField(TEXT("ticks"),LexToString(Profile.CreatedDate.GetTicks()));Object->SetObjectField(TEXT("CreatedDate"),Date);
    return WriteSetting(StateJson,TEXT("LatencyProfile"),MakeShared<FJsonValueObject>(Object));
}
