#include "RecoveredProgressionResources.h"
#include "Dom/JsonObject.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

bool IsRecoveredNewerProgressionEnabled()
{
    bool bEnabled=false;
    if (GConfig) GConfig->GetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),bEnabled,GGameIni);
    return bEnabled;
}

FString ResolveRecoveredProgressionResource(const FString& Path)
{
    if (!IsRecoveredNewerProgressionEnabled()||Path.IsEmpty()) return Path;
    static const TMap<FString,FString> Aliases=[]()
    {
        TMap<FString,FString> Result;
        FString Text;
        TSharedPtr<FJsonObject> Root;
        const FString Filename=FPaths::ProjectContentDir()/TEXT("Recovery/Definitions/newer-20261017-resource-aliases.json");
        if (!FFileHelper::LoadFileToString(Text,*Filename)||!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Root)||!Root.IsValid())
        {
            UE_LOG(LogTemp,Error,TEXT("Newer progression artwork aliases are unavailable: %s"),*Filename);
            return Result;
        }
        for (const auto& Entry:Root->Values)
        {
            FString Target;
            if (Entry.Value.IsValid()&&Entry.Value->TryGetString(Target)&&Entry.Key.StartsWith(TEXT("/Game/"))&&Target.StartsWith(TEXT("/Game/Recovery/Newer20261017/Resources/")))
                Result.Add(Entry.Key,MoveTemp(Target));
        }
        return Result;
    }();
    if (const FString* Resolved=Aliases.Find(Path)) return *Resolved;
    return Path;
}
