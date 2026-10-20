#include "RecoveredMusicUpgrades.h"
#include "RecoveredRules.h"
#include "Dom/JsonObject.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
const TCHAR* Types[] = {TEXT("IncreaseBreakDuration"), TEXT("IncreaseTotalBreaks"), TEXT("DecreaseStrokesToGrantBreak")};
FString UpgradeKey(uint8 Type) { return FString::Printf(TEXT("Recovery.MusicUpgradeLevel.%d"), Type); }
}
int32 RecoveredMusicUpgrades::GetLevel(const URecoveredSaveGame* Save, uint8 Type) {
    if (Type > 2 || !Save) return 1;
    const double Value = Save->GetNumberSetting(UpgradeKey(Type), 1);
    return FMath::IsFinite(Value) ? FMath::Clamp(FMath::RoundToInt(Value), 1, 5) : 1;
}
double RecoveredMusicUpgrades::GetValue(const URecoveredSaveGame* Save, uint8 Type) {
    if (Type > 2) return 0;
    const int32 Level = GetLevel(Save, Type);
    static const double SourceValues[3][5] = {{5,8,12,15,18}, {1,2,3,4,5}, {500,400,300,250,180}};
    FString Json; TSharedPtr<FJsonObject> Root;
    if (FFileHelper::LoadFileToString(Json, *(FPaths::ProjectContentDir() / TEXT("Recovery/Definitions/newer-20261017-mode-data.json"))) &&
        FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json), Root) && Root.IsValid()) {
        const TArray<TSharedPtr<FJsonValue>>* Rows = nullptr;
        if (Root->TryGetArrayField(TEXT("music_upgrades"), Rows)) for (const auto& Value : *Rows) {
            const auto Row = Value->AsObject();
            if (!Row.IsValid() || Row->GetStringField(TEXT("UpgradeType")) != FString(TEXT("EMusicModeProgressionUpgrade::")) + Types[Type]) continue;
            double Result = 0;
            if (Row->TryGetNumberField(FString::Printf(TEXT("Value_L%d"), Level), Result) && FMath::IsFinite(Result) && Result > 0) return Result;
        }
    }
    return SourceValues[Type][Level - 1];
}
bool RecoveredMusicUpgrades::SetLevel(URecoveredSaveGame* Save, uint8 Type, int32 Level) {
    return Save && Type <= 2 && Level >= 1 && Level <= 5 && Save->SetNumberSetting(UpgradeKey(Type), Level);
}
