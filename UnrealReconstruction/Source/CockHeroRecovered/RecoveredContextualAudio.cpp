#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "Sound/SoundBase.h"

namespace {
#include "RecoveredContextualAudioData.inl"

struct FRecoveredContextualPool {
    const TCHAR* Tag;
    const TCHAR* Folder;
    const TCHAR* const* Sounds;
    int32 Count;
};

static const FRecoveredContextualPool GRecoveredContextualPools[] = {
    { TEXT("assjob"), TEXT("Assjob"), GRecoveredContextualAssjobSounds, UE_ARRAY_COUNT(GRecoveredContextualAssjobSounds) },
    { TEXT("blowjob"), TEXT("Blowjob"), GRecoveredContextualBlowjobSounds, UE_ARRAY_COUNT(GRecoveredContextualBlowjobSounds) },
    { TEXT("cowgirl"), TEXT("Cowgirl"), GRecoveredContextualCowgirlSounds, UE_ARRAY_COUNT(GRecoveredContextualCowgirlSounds) },
    { TEXT("cum"), TEXT("Cum"), GRecoveredContextualCumSounds, UE_ARRAY_COUNT(GRecoveredContextualCumSounds) },
    { TEXT("handjob"), TEXT("Handjob"), GRecoveredContextualHandjobSounds, UE_ARRAY_COUNT(GRecoveredContextualHandjobSounds) },
    { TEXT("paizuri"), TEXT("Paizuri"), GRecoveredContextualPaizuriSounds, UE_ARRAY_COUNT(GRecoveredContextualPaizuriSounds) },
    { TEXT("sex"), TEXT("Sex"), GRecoveredContextualSexSounds, UE_ARRAY_COUNT(GRecoveredContextualSexSounds) },
    { TEXT("succubus"), TEXT("Succubus"), GRecoveredContextualSuccubusSounds, UE_ARRAY_COUNT(GRecoveredContextualSuccubusSounds) },
};

bool AreRecoveredContextualSFXEnabled(const ARecoveredGlobalManager& Manager) {
    const auto* Instance=Cast<URecoveredGameInstance>(Manager.GetGameInstance());
    return !Instance || !Instance->CurrentSave || Instance->CurrentSave->GetBoolSetting(TEXT("AreContextualBeatSFXEnabled?"),true);
}

void PlayRecoveredContextualSourceSound(ARecoveredGlobalManager* Manager, const FString& ObjectPath, float Volume, float Pitch, float StartTime) {
    if (!Manager || !Manager->GetWorld()) return;
    if (!FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(ObjectPath))) return;
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,*ObjectPath)) {
        UGameplayStatics::PlaySound2D(Manager,Sound,Volume,Pitch,StartTime);
    }
}
}

void ARecoveredGlobalManager::PlayRecoveredTagContextualBeatCompleteSFX() {
    LastRecoveredContextualSound=NAME_None;
    LastRecoveredContextualVolume=0.0f;
    LastRecoveredContextualPitch=0.0f;
    LastRecoveredContextualStartTime=0.0f;
    if (!AreRecoveredContextualSFXEnabled(*this)) return;

    RecoveredEligibleContextualSounds.Reset();
    TMap<FName,FString> Folders;
    for (const FString& Tag:SelectedRandomCard.Tags) {
        for (const FRecoveredContextualPool& Pool:GRecoveredContextualPools) {
            if (Tag != Pool.Tag || Pool.Count==0) continue;
            const FName Candidate(Pool.Sounds[FMath::RandRange(0,Pool.Count-1)]);
            RecoveredEligibleContextualSounds.Add(Candidate);
            Folders.Add(Candidate,FString(Pool.Folder));
            break;
        }
    }
    if (RecoveredEligibleContextualSounds.IsEmpty()) return;

    LastRecoveredContextualSound=RecoveredEligibleContextualSounds[FMath::RandRange(0,RecoveredEligibleContextualSounds.Num()-1)];
    LastRecoveredContextualVolume=2.0f*GetRecoveredVolume(TEXT("ContextBeatSFXVolume"),1.0f);
    LastRecoveredContextualPitch=1.5f;
    LastRecoveredContextualStartTime=-.28f;
    ++RecoveredContextualPlayCount;
    const FString* Folder=Folders.Find(LastRecoveredContextualSound);
    if (!Folder) return;
    const FString Name=LastRecoveredContextualSound.ToString();
    const FString ObjectPath=FString::Printf(TEXT("/Game/Recovery/Resources/ContextualAudio/%s/%s.%s"),**Folder,*Name,*Name);
    PlayRecoveredContextualSourceSound(this,ObjectPath,LastRecoveredContextualVolume,LastRecoveredContextualPitch,LastRecoveredContextualStartTime);
}
