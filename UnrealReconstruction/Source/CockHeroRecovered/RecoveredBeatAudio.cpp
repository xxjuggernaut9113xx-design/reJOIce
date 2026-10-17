#include "RecoveredRules.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/PackageName.h"
#include "Sound/SoundBase.h"

namespace {
static const TCHAR* const GRecoveredSlowMoanMaster[] = {
    TEXT("slow_beatmoansfx__10_"),
    TEXT("slow_beatmoansfx__11_"),
    TEXT("slow_beatmoansfx__12_"),
    TEXT("slow_beatmoansfx__13_"),
    TEXT("slow_beatmoansfx__14_"),
    TEXT("slow_beatmoansfx__15_"),
    TEXT("slow_beatmoansfx__16_"),
    TEXT("slow_beatmoansfx__17_"),
    TEXT("slow_beatmoansfx__18_"),
    TEXT("slow_beatmoansfx__19_"),
    TEXT("slow_beatmoansfx__1_"),
    TEXT("slow_beatmoansfx__20_"),
    TEXT("slow_beatmoansfx__21_"),
    TEXT("slow_beatmoansfx__22_"),
    TEXT("slow_beatmoansfx__23_"),
    TEXT("slow_beatmoansfx__24_"),
    TEXT("slow_beatmoansfx__25_"),
    TEXT("slow_beatmoansfx__26_"),
    TEXT("slow_beatmoansfx__27_"),
    TEXT("slow_beatmoansfx__28_"),
    TEXT("slow_beatmoansfx__29_"),
    TEXT("slow_beatmoansfx__2_"),
    TEXT("slow_beatmoansfx__30_"),
    TEXT("slow_beatmoansfx__31_"),
    TEXT("slow_beatmoansfx__32_"),
    TEXT("slow_beatmoansfx__33_"),
    TEXT("slow_beatmoansfx__34_"),
    TEXT("slow_beatmoansfx__35_"),
    TEXT("slow_beatmoansfx__36_"),
    TEXT("slow_beatmoansfx__37_"),
    TEXT("slow_beatmoansfx__38_"),
    TEXT("slow_beatmoansfx__39_"),
    TEXT("slow_beatmoansfx__3_"),
    TEXT("slow_beatmoansfx__40_"),
    TEXT("slow_beatmoansfx__41_"),
    TEXT("slow_beatmoansfx__42_"),
    TEXT("slow_beatmoansfx__43_"),
    TEXT("slow_beatmoansfx__44_"),
    TEXT("slow_beatmoansfx__45_"),
    TEXT("slow_beatmoansfx__46_"),
    TEXT("slow_beatmoansfx__47_"),
    TEXT("slow_beatmoansfx__4_"),
    TEXT("slow_beatmoansfx__5_"),
    TEXT("slow_beatmoansfx__6_"),
    TEXT("slow_beatmoansfx__7_"),
    TEXT("slow_beatmoansfx__8_"),
    TEXT("slow_beatmoansfx__9_")
};

static const TCHAR* const GRecoveredMediumMoanMaster[] = {
    TEXT("medium_beatmoansfx__10_"),
    TEXT("medium_beatmoansfx__11_"),
    TEXT("medium_beatmoansfx__12_"),
    TEXT("medium_beatmoansfx__13_"),
    TEXT("medium_beatmoansfx__14_"),
    TEXT("medium_beatmoansfx__15_"),
    TEXT("medium_beatmoansfx__16_"),
    TEXT("medium_beatmoansfx__17_"),
    TEXT("medium_beatmoansfx__18_"),
    TEXT("medium_beatmoansfx__19_"),
    TEXT("medium_beatmoansfx__1_"),
    TEXT("medium_beatmoansfx__20_"),
    TEXT("medium_beatmoansfx__21_"),
    TEXT("medium_beatmoansfx__22_"),
    TEXT("medium_beatmoansfx__23_"),
    TEXT("medium_beatmoansfx__24_"),
    TEXT("medium_beatmoansfx__25_"),
    TEXT("medium_beatmoansfx__26_"),
    TEXT("medium_beatmoansfx__27_"),
    TEXT("medium_beatmoansfx__28_"),
    TEXT("medium_beatmoansfx__29_"),
    TEXT("medium_beatmoansfx__2_"),
    TEXT("medium_beatmoansfx__30_"),
    TEXT("medium_beatmoansfx__31_"),
    TEXT("medium_beatmoansfx__32_"),
    TEXT("medium_beatmoansfx__33_"),
    TEXT("medium_beatmoansfx__34_"),
    TEXT("medium_beatmoansfx__35_"),
    TEXT("medium_beatmoansfx__36_"),
    TEXT("medium_beatmoansfx__37_"),
    TEXT("medium_beatmoansfx__38_"),
    TEXT("medium_beatmoansfx__39_"),
    TEXT("medium_beatmoansfx__3_"),
    TEXT("medium_beatmoansfx__40_"),
    TEXT("medium_beatmoansfx__41_"),
    TEXT("medium_beatmoansfx__42_"),
    TEXT("medium_beatmoansfx__43_"),
    TEXT("medium_beatmoansfx__44_"),
    TEXT("medium_beatmoansfx__45_"),
    TEXT("medium_beatmoansfx__46_"),
    TEXT("medium_beatmoansfx__47_"),
    TEXT("medium_beatmoansfx__48_"),
    TEXT("medium_beatmoansfx__49_"),
    TEXT("medium_beatmoansfx__4_"),
    TEXT("medium_beatmoansfx__50_"),
    TEXT("medium_beatmoansfx__51_"),
    TEXT("medium_beatmoansfx__52_"),
    TEXT("medium_beatmoansfx__53_"),
    TEXT("medium_beatmoansfx__54_"),
    TEXT("medium_beatmoansfx__55_"),
    TEXT("medium_beatmoansfx__56_"),
    TEXT("medium_beatmoansfx__57_"),
    TEXT("medium_beatmoansfx__58_"),
    TEXT("medium_beatmoansfx__59_"),
    TEXT("medium_beatmoansfx__5_"),
    TEXT("medium_beatmoansfx__60_"),
    TEXT("medium_beatmoansfx__61_"),
    TEXT("medium_beatmoansfx__6_"),
    TEXT("medium_beatmoansfx__7_"),
    TEXT("medium_beatmoansfx__8_"),
    TEXT("medium_beatmoansfx__9_")
};

static const TCHAR* const GRecoveredFastMoanMaster[] = {
    TEXT("fast_beatmoansfx__10_"),
    TEXT("fast_beatmoansfx__11_"),
    TEXT("fast_beatmoansfx__12_"),
    TEXT("fast_beatmoansfx__13_"),
    TEXT("fast_beatmoansfx__14_"),
    TEXT("fast_beatmoansfx__15_"),
    TEXT("fast_beatmoansfx__16_"),
    TEXT("fast_beatmoansfx__17_"),
    TEXT("fast_beatmoansfx__18_"),
    TEXT("fast_beatmoansfx__19_"),
    TEXT("fast_beatmoansfx__1_"),
    TEXT("fast_beatmoansfx__20_"),
    TEXT("fast_beatmoansfx__21_"),
    TEXT("fast_beatmoansfx__22_"),
    TEXT("fast_beatmoansfx__23_"),
    TEXT("fast_beatmoansfx__24_"),
    TEXT("fast_beatmoansfx__25_"),
    TEXT("fast_beatmoansfx__26_"),
    TEXT("fast_beatmoansfx__27_"),
    TEXT("fast_beatmoansfx__28_"),
    TEXT("fast_beatmoansfx__29_"),
    TEXT("fast_beatmoansfx__2_"),
    TEXT("fast_beatmoansfx__30_"),
    TEXT("fast_beatmoansfx__31_"),
    TEXT("fast_beatmoansfx__32_"),
    TEXT("fast_beatmoansfx__33_"),
    TEXT("fast_beatmoansfx__34_"),
    TEXT("fast_beatmoansfx__35_"),
    TEXT("fast_beatmoansfx__36_"),
    TEXT("fast_beatmoansfx__37_"),
    TEXT("fast_beatmoansfx__38_"),
    TEXT("fast_beatmoansfx__39_"),
    TEXT("fast_beatmoansfx__3_"),
    TEXT("fast_beatmoansfx__40_"),
    TEXT("fast_beatmoansfx__41_"),
    TEXT("fast_beatmoansfx__42_"),
    TEXT("fast_beatmoansfx__43_"),
    TEXT("fast_beatmoansfx__44_"),
    TEXT("fast_beatmoansfx__45_"),
    TEXT("fast_beatmoansfx__46_"),
    TEXT("fast_beatmoansfx__47_"),
    TEXT("fast_beatmoansfx__48_"),
    TEXT("fast_beatmoansfx__49_"),
    TEXT("fast_beatmoansfx__4_"),
    TEXT("fast_beatmoansfx__50_"),
    TEXT("fast_beatmoansfx__51_"),
    TEXT("fast_beatmoansfx__52_"),
    TEXT("fast_beatmoansfx__53_"),
    TEXT("fast_beatmoansfx__54_"),
    TEXT("fast_beatmoansfx__55_"),
    TEXT("fast_beatmoansfx__56_"),
    TEXT("fast_beatmoansfx__57_"),
    TEXT("fast_beatmoansfx__58_"),
    TEXT("fast_beatmoansfx__59_"),
    TEXT("fast_beatmoansfx__5_"),
    TEXT("fast_beatmoansfx__60_"),
    TEXT("fast_beatmoansfx__61_"),
    TEXT("fast_beatmoansfx__62_"),
    TEXT("fast_beatmoansfx__63_"),
    TEXT("fast_beatmoansfx__64_"),
    TEXT("fast_beatmoansfx__65_"),
    TEXT("fast_beatmoansfx__66_"),
    TEXT("fast_beatmoansfx__67_"),
    TEXT("fast_beatmoansfx__68_"),
    TEXT("fast_beatmoansfx__69_"),
    TEXT("fast_beatmoansfx__6_"),
    TEXT("fast_beatmoansfx__70_"),
    TEXT("fast_beatmoansfx__71_"),
    TEXT("fast_beatmoansfx__72_"),
    TEXT("fast_beatmoansfx__7_"),
    TEXT("fast_beatmoansfx__8_"),
    TEXT("fast_beatmoansfx__9_")
};

void ResetRecoveredMoanPool(TArray<FName>& Destination, const TCHAR* const* Source, int32 Count) {
    Destination.Reset(Count);
    for (int32 Index=0; Index<Count; ++Index) Destination.Add(FName(Source[Index]));
}

bool PlayRecoveredSourceSound(ARecoveredGlobalManager* Manager, const FString& ObjectPath, float Volume, float Pitch, float StartTime=0.0f) {
    if (!Manager || !Manager->GetWorld()) return false;
    if (!FPackageName::DoesPackageExist(FPackageName::ObjectPathToPackageName(ObjectPath))) return false;
    USoundBase* Sound=LoadObject<USoundBase>(nullptr,*ObjectPath);
    if (!Sound) return false;
    UGameplayStatics::PlaySound2D(Manager,Sound,Volume,Pitch,StartTime);
    return true;
}

bool AreRecoveredMoansEnabled(const ARecoveredGlobalManager& Manager) {
    const auto* Instance=Cast<URecoveredGameInstance>(Manager.GetGameInstance());
    return !Instance || !Instance->CurrentSave || Instance->CurrentSave->GetBoolSetting(TEXT("bMoanSFXEnabled?"),true);
}

bool ResolveRecoveredMoanRoute(ARecoveredGlobalManager& Manager, float& OutMetronomeThreshold, TArray<FName>*& OutPool, const TCHAR*& OutFolder, const TCHAR* const*& OutMaster, int32& OutMasterCount) {
    OutPool=nullptr;
    OutFolder=nullptr;
    OutMaster=nullptr;
    OutMasterCount=0;
    switch (Manager.BeatContext.CardType) {
    case 0:
        OutMetronomeThreshold=.8f;
        OutPool=&Manager.RecoveredSlowMoanPool;
        OutFolder=TEXT("Slow");
        OutMaster=GRecoveredSlowMoanMaster;
        OutMasterCount=UE_ARRAY_COUNT(GRecoveredSlowMoanMaster);
        return true;
    case 1:
        OutMetronomeThreshold=.8f;
        OutPool=&Manager.RecoveredMediumMoanPool;
        OutFolder=TEXT("Medium");
        OutMaster=GRecoveredMediumMoanMaster;
        OutMasterCount=UE_ARRAY_COUNT(GRecoveredMediumMoanMaster);
        return true;
    case 2:
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        OutMetronomeThreshold=.55f;
        OutPool=&Manager.RecoveredFastMoanPool;
        OutFolder=TEXT("Fast");
        OutMaster=GRecoveredFastMoanMaster;
        OutMasterCount=UE_ARRAY_COUNT(GRecoveredFastMoanMaster);
        return true;
    default:
        return false;
    }
}

FString RecoveredMoanObjectPath(const TCHAR* Folder, FName MoanName) {
    const FString Name=MoanName.ToString();
    return FString::Printf(TEXT("/Game/Recovery/Resources/BeatMoans/%s/%s.%s"),Folder,*Name,*Name);
}
}

void ARecoveredGlobalManager::PlayRecoveredBeatCompleteAudio() {
    LastRecoveredMetronome=NAME_None;
    LastRecoveredBeatMoan=NAME_None;
    LastRecoveredMetronomeVolume=0.0f;
    LastRecoveredMetronomePitch=0.0f;
    LastRecoveredMoanVolume=0.0f;
    LastRecoveredMoanPitch=0.0f;

    float MetronomeThreshold=0.0f;
    TArray<FName>* MoanPool=nullptr;
    const TCHAR* Folder=nullptr;
    const TCHAR* const* Master=nullptr;
    int32 MasterCount=0;
    if (ResolveRecoveredMoanRoute(*this,MetronomeThreshold,MoanPool,Folder,Master,MasterCount)) {
        FRecoveredPitchPair Pitch;
        Pitch.BeatPitch=1.0;
        Pitch.MoanPitch=1.0;
        if (BeatTimeline && BeatTimeline->TotalStrokes>0) {
            CalculateBeatPitch(BeatTimeline->TotalStrokes,BeatTimeline->GetBeatsRemaining());
            Pitch=CurrentPitch;
        } else {
            CurrentPitch=Pitch;
        }

        LastRecoveredMetronome=TEXT("casual-click-pop-ui-10-262126");
        LastRecoveredMetronomePitch=static_cast<float>(Pitch.BeatPitch);
        LastRecoveredMetronomeVolume=(LastRecoveredMetronomePitch-MetronomeThreshold)*GetRecoveredVolume(TEXT("MetronomeVolume"),1.0f);
        PlayRecoveredSourceSound(this,TEXT("/Game/Recovery/Resources/BeatAudio/casual-click-pop-ui-10-262126.casual-click-pop-ui-10-262126"),LastRecoveredMetronomeVolume,LastRecoveredMetronomePitch);

        if (AreRecoveredMoansEnabled(*this) && MoanPool && Master && MasterCount>0) {
            LastRecoveredMoanVolume=static_cast<float>(Pitch.MoanPitch)*GetRecoveredVolume(TEXT("MoansVolume"),1.0f);
            LastRecoveredMoanPitch=static_cast<float>(Pitch.MoanPitch);
            if (!MoanPool->IsEmpty()) {
                const FName PlayedMoan=(*MoanPool)[FMath::RandRange(0,MoanPool->Num()-1)];
                LastRecoveredBeatMoan=PlayedMoan;
                PlayRecoveredSourceSound(this,RecoveredMoanObjectPath(Folder,PlayedMoan),LastRecoveredMoanVolume,LastRecoveredMoanPitch);
            }
            const bool bSlowRoute=BeatContext.CardType==0;
            const bool bFastRoute=!bSlowRoute && BeatContext.CardType!=1;
            if (bSlowRoute) PlayRecoveredTagContextualBeatCompleteSFX();
            if (!MoanPool->IsEmpty()) {
                const FName RemovedMoan=(*MoanPool)[FMath::RandRange(0,MoanPool->Num()-1)];
                MoanPool->Remove(RemovedMoan);
            }
            if (!bSlowRoute) PlayRecoveredTagContextualBeatCompleteSFX();
            const bool bPoolReset=MoanPool->IsEmpty();
            if (bPoolReset) ResetRecoveredMoanPool(*MoanPool,Master,MasterCount);
            if (bFastRoute && bPoolReset) PlayRecoveredTagContextualBeatCompleteSFX();
        }
    }

    PlayRecoveredHeatSFX();
}

void ARecoveredGlobalManager::PlayRecoveredHeatSFX() {
    LastRecoveredHeatSound=NAME_None;
    LastRecoveredHeatVolume=0.0f;
    LastRecoveredHeatPitch=0.0f;

    float CategoryScalar=0.0f;
    switch (BeatContext.HeatCategory) {
    case 0: CategoryScalar=1.0f; break;
    case 1: CategoryScalar=.8f; break;
    case 2: CategoryScalar=.6f; break;
    default: return;
    }
    LastRecoveredHeatSound=TEXT("heatfiresfx");
    LastRecoveredHeatVolume=CategoryScalar*GetRecoveredVolume(TEXT("SFXVolume"),1.0f);
    LastRecoveredHeatPitch=CategoryScalar;
    PlayRecoveredSourceSound(this,TEXT("/Game/Recovery/Resources/BeatAudio/heatfiresfx.heatfiresfx"),LastRecoveredHeatVolume,LastRecoveredHeatPitch,.02f);
}
