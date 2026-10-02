#include "RecoveredChallengeTracker.h"
#include "JsonObjectConverter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
bool ValidProgress(const TMap<FName,FRecoveredChallengeProgress>& Map) {
    if (Map.Num()>10000) return false;
    for (const auto& Pair:Map) {
        const auto& Progress=Pair.Value;
        if (Pair.Key.IsNone() || Pair.Key.ToString().Len()>256 || !FMath::IsFinite(Progress.CompletionTime) || Progress.Requirements.Num()>100 || Progress.BestValues.Num()!=Progress.Requirements.Num()) return false;
        for (const auto& Requirement:Progress.Requirements) if (Requirement.MetricType.Len()>256 || Requirement.ComparisonType.Len()>256) return false;
    }
    return true;
}
bool ValidNumericFields(const TSharedPtr<FJsonValue>& Value,const FString& Key) {
    if (!Value) return false;
    if (Value->Type==EJson::Number) {
        const double Number=Value->AsNumber();
        if (!FMath::IsFinite(Number)) return false;
        if (Key==TEXT("completionTime")) return FMath::Abs(Number)<=MAX_flt;
        return Number>=MIN_int32 && Number<=MAX_int32 && Number==FMath::FloorToDouble(Number);
    }
    if (Value->Type==EJson::Array) { for (const auto& Child:Value->AsArray()) if (!ValidNumericFields(Child,Key)) return false; }
    if (Value->Type==EJson::Object) { for (const auto& Pair:Value->AsObject()->Values) if (!ValidNumericFields(Pair.Value,Pair.Key)) return false; }
    return true;
}
bool HasFields(const TSharedPtr<FJsonObject>& Object,std::initializer_list<const TCHAR*> Fields) {
    if (!Object) return false;
    for (const TCHAR* Field:Fields) if (!Object->HasField(Field)) return false;
    return true;
}
bool ValidMapShape(const TSharedPtr<FJsonObject>& Object,const TCHAR* Field) {
    const TSharedPtr<FJsonObject>* Map=nullptr;
    if (!Object->TryGetObjectField(Field,Map) || !Map || !*Map || (*Map)->Values.Num()>10000) return false;
    for (const auto& Pair:(*Map)->Values) {
        if (!Pair.Value || Pair.Value->Type!=EJson::Object) return false;
        const auto Progress=Pair.Value->AsObject();
        if (!HasFields(Progress,{TEXT("requirements"),TEXT("bestValues"),TEXT("bCompleted"),TEXT("bRewardsClaimed"),TEXT("completionTime")})) return false;
        const TArray<TSharedPtr<FJsonValue>>* Requirements=nullptr;
        if (!Progress->TryGetArrayField(TEXT("requirements"),Requirements) || Requirements->Num()>100) return false;
        for (const auto& Requirement:*Requirements) {
            if (!Requirement || Requirement->Type!=EJson::Object || !HasFields(Requirement->AsObject(),{TEXT("metricType"),TEXT("targetValue"),TEXT("comparisonType"),TEXT("currentValue")})) return false;
        }
    }
    return true;
}
}
FString URecoveredChallengeTracker::ExportRecoveryState() const {
    FRecoveredChallengeSaveState State;State.SessionProgress=SessionProgress;State.LifetimeProgress=LifetimeProgress;State.CompletedChallenges=CompletedChallenges;State.TrackedChallenges=TrackedChallenges;
    FString Json;FJsonObjectConverter::UStructToJsonObjectString(State,Json);return Json;
}
bool URecoveredChallengeTracker::ImportRecoveryState(const FString& Json) {
    if (Json.Len()>16*1024*1024) return false;
    TSharedPtr<FJsonObject> Object;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json),Object) || !Object) return false;
    // The engine converter can stop after the last provided key even in strict mode.
    // Check the required shape first so a truncated prefix cannot clear live state.
    if (!HasFields(Object,{TEXT("version"),TEXT("sessionProgress"),TEXT("lifetimeProgress"),TEXT("completedChallenges"),TEXT("trackedChallenges")}) || !ValidMapShape(Object,TEXT("sessionProgress")) || !ValidMapShape(Object,TEXT("lifetimeProgress"))) return false;
    for (const auto& Pair:Object->Values) if (!ValidNumericFields(Pair.Value,Pair.Key)) return false;
    FRecoveredChallengeSaveState State;
    if (!FJsonObjectConverter::JsonObjectToUStruct(Object.ToSharedRef(),&State,0,0,true) || State.Version!=1 || !ValidProgress(State.SessionProgress) || !ValidProgress(State.LifetimeProgress) || State.CompletedChallenges.Num()>10000 || State.TrackedChallenges.Num()>10000) return false;
    for (FName ID:State.CompletedChallenges) if (ID.IsNone() || ID.ToString().Len()>256) return false;
    for (FName ID:State.TrackedChallenges) if (ID.IsNone() || ID.ToString().Len()>256) return false;
    SessionProgress=MoveTemp(State.SessionProgress);LifetimeProgress=MoveTemp(State.LifetimeProgress);CompletedChallenges=MoveTemp(State.CompletedChallenges);TrackedChallenges=MoveTemp(State.TrackedChallenges);
    return true;
}
