#include "RecoveredRules.h"
#include "RecoveredChallengeTracker.h"
#include "Kismet/GameplayStatics.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
const FString RecoverySlot=TEXT("CockHeroRecovered_Standalone_v1");
const FString RecoverySlotIndex=TEXT("CockHeroRecovered_SaveSlotIndex_v1");
const FString NamedRecoverySlotPrefix=TEXT("CockHeroRecovered_Named_");
constexpr int32 MaxNamedSlots=128;
constexpr int32 MaxNamedSlotSuffixLength=64;

bool IsNamedRecoverySlot(const FString& SlotName) {
    if (!SlotName.StartsWith(NamedRecoverySlotPrefix,ESearchCase::CaseSensitive)) return false;
    const FString Suffix=SlotName.RightChop(NamedRecoverySlotPrefix.Len());
    if (Suffix.IsEmpty() || Suffix.Len()>MaxNamedSlotSuffixLength) return false;
    for (const TCHAR Character:Suffix) if (!FChar::IsAlnum(Character) && Character!=TEXT('_') && Character!=TEXT('-')) return false;
    return true;
}

bool ContainsSlot(const TArray<FString>& Slots,const FString& SlotName) {
    return Slots.ContainsByPredicate([&SlotName](const FString& Candidate) {
        return Candidate.Equals(SlotName,ESearchCase::IgnoreCase);
    });
}

bool IsValidSlotIndexPayload(const TArray<FString>& NamedSlots,const FString& ActiveSlot) {
    if (NamedSlots.Num()>MaxNamedSlots || !URecoveredGameInstance::IsRecoverySlotNameValid(ActiveSlot)) return false;
    TArray<FString> Seen;
    Seen.Reserve(NamedSlots.Num());
    for (const FString& SlotName:NamedSlots) {
        if (!IsNamedRecoverySlot(SlotName) || ContainsSlot(Seen,SlotName)) return false;
        Seen.Add(SlotName);
    }
    return ActiveSlot==RecoverySlot || ContainsSlot(NamedSlots,ActiveSlot);
}

bool BuildRecoveredRuntimeState(
    URecoveredGameInstance* Instance,
    URecoveredSaveGame* Save,
    URecoveredProgressionManager*& OutProgression,
    URecoveredChallengeTracker*& OutChallenges,
    URecoveredCalibrationManager*& OutCalibration,
    FString& OutError) {
    if (!Save || !Save->IsStateValid()) {
        OutError=TEXT("The selected recovery save is unreadable or has an unsupported format");
        return false;
    }

    auto* Progression=NewObject<URecoveredProgressionManager>(Instance);
    Progression->LevelDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_LevelData.DT_LevelData"));
    Progression->PlayerCardDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_PlayerCards.DT_PlayerCards"));
    Progression->ModifierDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Modifiers.DT_Modifiers"));
    Progression->ChallengeDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));

    const bool bHasProgressionState=Save->HasSetting(TEXT("RecoveryProgressionState"));
    const FString ProgressionState=Save->GetStringSetting(TEXT("RecoveryProgressionState"),TEXT(""));
    if (bHasProgressionState && (ProgressionState.IsEmpty() || !Progression->ImportRecoveryState(ProgressionState))) {
        OutError=TEXT("Recovery progression state is invalid; the active profile was left unchanged");
        return false;
    }
    if (!bHasProgressionState) {
        Progression->UnlockPoints=static_cast<int32>(FMath::Clamp(Save->GetNumberSetting(TEXT("UnlockPoints"),0),double(MIN_int32),double(MAX_int32)));
    }
    const TArray<FString> SavedModifiers=Save->HasSetting(TEXT("EnabledModifiers"))
        ? Save->GetStringArraySetting(TEXT("EnabledModifiers"))
        : Save->GetStringArraySetting(TEXT("ActiveModifiers"));
    for (const FString& ModifierName:SavedModifiers) {
        if (ModifierName.Len()>256) continue;
        const FName ModifierID=Progression->GetCanonicalModifierID(FName(*ModifierName));
        FRecoveredModifierRow Modifier;
        if (!ModifierID.IsNone() && Progression->IsModifierUnlocked(ModifierID) && Progression->GetModifierData(ModifierID,Modifier) && Progression->CanEnableModifier(ModifierID)) {
            Progression->EnabledModifiers.Add(ModifierID);
        }
    }

    auto* Challenges=NewObject<URecoveredChallengeTracker>(Instance);
    Challenges->RewardManager=Progression;
    Challenges->ChallengeTable=Progression->ChallengeDataTable;
    const bool bHasChallengeState=Save->HasSetting(TEXT("RecoveryChallengeState"));
    const FString ChallengeState=Save->GetStringSetting(TEXT("RecoveryChallengeState"),TEXT(""));
    if (bHasChallengeState && (ChallengeState.IsEmpty() || !Challenges->ImportRecoveryState(ChallengeState))) {
        OutError=TEXT("Recovery challenge state is invalid; the active profile was left unchanged");
        return false;
    }
    if (!Challenges->InitializeChallenges()) {
        OutError=TEXT("Recovered challenge definitions are unavailable");
        return false;
    }

    auto* Calibration=NewObject<URecoveredCalibrationManager>(Instance);
    if (Save->HasSetting(TEXT("LatencyProfile")) && !Save->GetLatencyProfile(Calibration->CurrentProfile)) {
        OutError=TEXT("Recovery calibration state is invalid; the active profile was left unchanged");
        return false;
    }

    OutProgression=Progression;
    OutChallenges=Challenges;
    OutCalibration=Calibration;
    return true;
}

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
bool URecoveredSaveGame::SetStringArraySetting(const FString& Name,const TArray<FString>& Values) {
    TArray<TSharedPtr<FJsonValue>> JsonValues;
    for (const FString& Value : Values) JsonValues.Add(MakeShared<FJsonValueString>(Value));
    return WriteSetting(StateJson,Name,MakeShared<FJsonValueArray>(JsonValues));
}

FString URecoveredGameInstance::GetDefaultRecoverySlotName() { return RecoverySlot; }
FString URecoveredGameInstance::GetRecoverySlotIndexName() { return RecoverySlotIndex; }
FString URecoveredGameInstance::GetNamedRecoverySlotPrefix() { return NamedRecoverySlotPrefix; }
bool URecoveredGameInstance::IsRecoverySlotNameValid(const FString& SlotName) {
    return SlotName==RecoverySlot || IsNamedRecoverySlot(SlotName);
}

bool URecoveredGameInstance::ReadRecoverySlotIndex(TArray<FString>& OutNamedSlots,FString& OutActiveSlot,const FString& IndexSlotName) {
    OutNamedSlots.Reset();
    OutActiveSlot=RecoverySlot;
    const FString ResolvedIndexSlot=IndexSlotName.IsEmpty() ? RecoverySlotIndex : IndexSlotName;
    if (!UGameplayStatics::DoesSaveGameExist(ResolvedIndexSlot,0)) return true;
    const auto* Index=Cast<URecoveredSaveSlotIndex>(UGameplayStatics::LoadGameFromSlot(ResolvedIndexSlot,0));
    if (!Index || Index->RecoverySlotIndexVersion!=1) return false;
    const FString Active=Index->ActiveSlot.IsEmpty() ? RecoverySlot : Index->ActiveSlot;
    if (!IsValidSlotIndexPayload(Index->NamedSlots,Active)) return false;
    OutNamedSlots=Index->NamedSlots;
    OutNamedSlots.Sort();
    OutActiveSlot=Active;
    return true;
}

bool URecoveredGameInstance::WriteRecoverySlotIndex(const TArray<FString>& NamedSlots,const FString& ActiveSlot,const FString& IndexSlotName) {
    const FString ResolvedIndexSlot=IndexSlotName.IsEmpty() ? RecoverySlotIndex : IndexSlotName;
    if (!IsValidSlotIndexPayload(NamedSlots,ActiveSlot)) return false;
    auto* Index=NewObject<URecoveredSaveSlotIndex>();
    Index->RecoverySlotIndexVersion=1;
    Index->NamedSlots=NamedSlots;
    Index->NamedSlots.Sort();
    Index->ActiveSlot=ActiveSlot;
    return UGameplayStatics::SaveGameToSlot(Index,ResolvedIndexSlot,0);
}

bool URecoveredGameInstance::LoadRecoveredSave() {
    TArray<FString> NamedSlots;
    FString IndexedActiveSlot=RecoverySlot;
    FString IndexError;
    if (!ReadRecoverySlotIndex(NamedSlots,IndexedActiveSlot,RecoverySlotIndex)) {
        IndexError=TEXT("Recovery profile index is unreadable; the default profile was loaded without replacing it");
    } else if (IndexedActiveSlot!=RecoverySlot) {
        if (ContainsSlot(NamedSlots,IndexedActiveSlot) && UGameplayStatics::DoesSaveGameExist(IndexedActiveSlot,0)) {
            if (LoadRecoveredSaveSlotInternal(IndexedActiveSlot,false)) return true;
            IndexError=TEXT("Selected recovery profile could not be restored: ")+LastSaveError;
        } else {
            IndexError=TEXT("Selected recovery profile is unavailable; the default profile was loaded without replacing it");
        }
    }
    const bool bLoaded=LoadRecoveredSaveSlotInternal(RecoverySlot,false);
    if (bLoaded && !IndexError.IsEmpty()) LastSaveError=IndexError;
    return bLoaded;
}

bool URecoveredGameInstance::LoadRecoveredSaveSlot(const FString& SlotName) {
    if (!IsRecoverySlotNameValid(SlotName)) {
        LastSaveError=TEXT("Recovery profile name is invalid");
        return false;
    }
    TArray<FString> NamedSlots;
    FString ActiveSlot;
    if (!ReadRecoverySlotIndex(NamedSlots,ActiveSlot,RecoverySlotIndex)) {
        LastSaveError=TEXT("Recovery profile index is unreadable");
        return false;
    }
    if (SlotName!=RecoverySlot && (!ContainsSlot(NamedSlots,SlotName) || !UGameplayStatics::DoesSaveGameExist(SlotName,0))) {
        LastSaveError=TEXT("Selected recovery profile is unavailable");
        return false;
    }
    return LoadRecoveredSaveSlotInternal(SlotName,true);
}

bool URecoveredGameInstance::LoadRecoveredSaveSlotInternal(const FString& SlotName,bool bPersistActiveSlot) {
    URecoveredSaveGame* Loaded=nullptr;
    if (UGameplayStatics::DoesSaveGameExist(SlotName,0)) {
        Loaded=Cast<URecoveredSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
        if (!Loaded || !Loaded->IsStateValid()) {
            LastSaveError=TEXT("The selected recovery save is unreadable or has an unsupported format");
            return false;
        }
    } else if (SlotName==RecoverySlot) {
        Loaded=NewObject<URecoveredSaveGame>(this);
        if (!Loaded->InitializeRecoveredDefaults()) {
            LastSaveError=TEXT("Verified source save defaults are unavailable");
            return false;
        }
    } else {
        LastSaveError=TEXT("Selected recovery profile is unavailable");
        return false;
    }

    URecoveredProgressionManager* NewProgression=nullptr;
    URecoveredChallengeTracker* NewChallenges=nullptr;
    URecoveredCalibrationManager* NewCalibration=nullptr;
    FString RehydrationError;
    if (!BuildRecoveredRuntimeState(this,Loaded,NewProgression,NewChallenges,NewCalibration,RehydrationError)) {
        LastSaveError=RehydrationError;
        return false;
    }

    if (bPersistActiveSlot) {
        TArray<FString> NamedSlots;
        FString IndexedActiveSlot;
        if (!ReadRecoverySlotIndex(NamedSlots,IndexedActiveSlot,RecoverySlotIndex) || !WriteRecoverySlotIndex(NamedSlots,SlotName,RecoverySlotIndex)) {
            LastSaveError=TEXT("Recovery profile index could not record the active profile");
            return false;
        }
    }

    CurrentSave=Loaded;
    if (DeviceManager) DeviceManager->LoadDeviceSettings(CurrentSave);
    ActiveRecoverySlot=SlotName;
    ProgressionManager=NewProgression;
    ChallengeTracker=NewChallenges;
    CalibrationManager=NewCalibration;
    bProgressionStateValid=true;
    bChallengeStateValid=true;
    ProgressionManager->OnSaveRequested.AddUniqueDynamic(this,&URecoveredGameInstance::HandleProgressionSaveRequest);
    if (UWorld* World=GetWorld()) {
        if (auto* Manager=Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(World))) Manager->ReloadRecoveredProfile();
    }
    LastSaveError.Reset();
    return true;
}

bool URecoveredGameInstance::SaveRecoveredState() {
    if (!CurrentSave || !CurrentSave->IsStateValid()) { LastSaveError=TEXT("No valid recovery state to save"); return false; }
    const FString TargetSlot=IsRecoverySlotNameValid(ActiveRecoverySlot) ? ActiveRecoverySlot : RecoverySlot;
    if (!UGameplayStatics::SaveGameToSlot(CurrentSave,TargetSlot,0)) { LastSaveError=TEXT("Could not write the active recovery save"); return false; }
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
