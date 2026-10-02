#include "RecoveredRules.h"
#include "RecoveredChallengeTracker.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
bool ReadInt(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,int32& Value) {
    double Number;
    if (!Object->TryGetNumberField(Name,Number) || !FMath::IsFinite(Number) || Number<MIN_int32 || Number>MAX_int32 || Number!=FMath::FloorToDouble(Number)) return false;
    Value=static_cast<int32>(Number); return true;
}
TArray<TSharedPtr<FJsonValue>> WriteNames(const TSet<FName>& Names) {
    TArray<FString> Sorted;
    for (const FName Name:Names) Sorted.Add(Name.ToString());
    Sorted.Sort();
    TArray<TSharedPtr<FJsonValue>> Values;
    for (const FString& Name:Sorted) Values.Add(MakeShared<FJsonValueString>(Name));
    return Values;
}
bool ReadNames(const TSharedPtr<FJsonObject>& Object,const TCHAR* Field,TSet<FName>& Names) {
    const TArray<TSharedPtr<FJsonValue>>* Values=nullptr;
    if (!Object->TryGetArrayField(Field,Values) || Values->Num()>10000) return false;
    for (const auto& Value:*Values) {
        FString Name;
        if (!Value || !Value->TryGetString(Name) || Name.Len()>256 || FName(*Name).IsNone()) return false;
        Names.Add(FName(*Name));
    }
    return true;
}
}
FString URecoveredProgressionManager::ExportRecoveryState() const {
    auto Object=MakeShared<FJsonObject>();
    Object->SetNumberField(TEXT("Version"),1);
    Object->SetNumberField(TEXT("CurrentXP"),CurrentXP);
    Object->SetNumberField(TEXT("CurrentLevel"),CurrentLevel);
    Object->SetNumberField(TEXT("TotalXPEarned"),TotalXPEarned);
    Object->SetNumberField(TEXT("UnlockPoints"),UnlockPoints);
    Object->SetArrayField(TEXT("UnlockedPlayerCards"),WriteNames(UnlockedPlayerCards));
    Object->SetArrayField(TEXT("UnlockedModifiers"),WriteNames(UnlockedModifiers));
    FString Json; FJsonSerializer::Serialize(Object,TJsonWriterFactory<>::Create(&Json)); return Json;
}
bool URecoveredProgressionManager::ImportRecoveryState(const FString& Json) {
    if (Json.Len()>16*1024*1024) return false;
    TSharedPtr<FJsonObject> Object;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json),Object) || !Object) return false;
    int32 Version,XP,Level,Total,Points;
    TSet<FName> Cards,Modifiers;
    if (!ReadInt(Object,TEXT("Version"),Version) || Version!=1 || !ReadInt(Object,TEXT("CurrentXP"),XP) || !ReadInt(Object,TEXT("CurrentLevel"),Level) || Level<1 || Level>20 || !ReadInt(Object,TEXT("TotalXPEarned"),Total) || !ReadInt(Object,TEXT("UnlockPoints"),Points) || !ReadNames(Object,TEXT("UnlockedPlayerCards"),Cards) || !ReadNames(Object,TEXT("UnlockedModifiers"),Modifiers)) return false;
    CurrentXP=XP; CurrentLevel=Level; TotalXPEarned=Total; UnlockPoints=Points;
    UnlockedPlayerCards=MoveTemp(Cards); UnlockedModifiers=MoveTemp(Modifiers);
    return true;
}
void URecoveredGameInstance::HandleProgressionSaveRequest() { PersistRecoveredProgression(); }
bool URecoveredGameInstance::PersistRecoveredProgression() {
    if (!bProgressionStateValid || !bChallengeStateValid || !CurrentSave || !ProgressionManager) { LastSaveError=TEXT("Cannot save invalid or unavailable recovery progression"); return false; }
    if (ChallengeTracker && !CurrentSave->SetStringSetting(TEXT("RecoveryChallengeState"),ChallengeTracker->ExportRecoveryState())) { LastSaveError=TEXT("Could not update recovery challenge state");return false; }
    if (!CurrentSave->SetStringSetting(TEXT("RecoveryProgressionState"),ProgressionManager->ExportRecoveryState())) { LastSaveError=TEXT("Could not update recovery progression state"); return false; }
    if (!CurrentSave->SetNumberSetting(TEXT("UnlockPoints"),ProgressionManager->UnlockPoints)) { LastSaveError=TEXT("Could not update the recovery unlock balance"); return false; }
    return SaveRecoveredState();
}
