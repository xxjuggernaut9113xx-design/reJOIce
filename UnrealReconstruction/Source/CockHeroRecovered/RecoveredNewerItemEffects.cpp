#include "RecoveredNewerItemEffects.h"

void URecoveredNewerItemEffects::StartLootRush(int32 Level) {
    static constexpr double Durations[]={15,20,30,40,50};
    static constexpr double Bonuses[]={.5,.75,1,1.25,1.5};
    const int32 Index=FMath::Clamp(Level-1,0,4);
    LootRushRemaining=Durations[Index];
    LootRushBonus=Bonuses[Index];
}

void URecoveredNewerItemEffects::StartBounty(int32 Level,int32 CurrentStrokes,FRandomStream& Random) {
    static constexpr int32 StrokeMin[]={38,38,36,34,32};
    static constexpr int32 StrokeMax[]={48,48,46,44,42};
    static constexpr int32 DurationMin[]={14,17,20,23,26};
    static constexpr int32 DurationMax[]={17,20,23,26,30};
    BountyLevel=FMath::Clamp(Level,1,5);
    const int32 Index=BountyLevel-1;
    BountyStartStrokes=CurrentStrokes;
    BountyRequiredStrokes=Random.RandRange(StrokeMin[Index],StrokeMax[Index]);
    BountyRemaining=Random.RandRange(DurationMin[Index],DurationMax[Index]);
}

bool URecoveredNewerItemEffects::AdvanceLootRush(double Seconds) {
    if (LootRushRemaining<=0 || !FMath::IsFinite(Seconds) || Seconds<=0) return false;
    LootRushRemaining=FMath::Max(0.0,LootRushRemaining-Seconds);
    if (LootRushRemaining>0) return false;
    LootRushBonus=0;
    return true;
}

int32 URecoveredNewerItemEffects::AdvanceBounty(double Seconds,int32 CurrentStrokes) {
    if (BountyRemaining<=0 || !FMath::IsFinite(Seconds) || Seconds<0) return 0;
    if (static_cast<int64>(CurrentStrokes)-BountyStartStrokes>=BountyRequiredStrokes) {
        BountyRemaining=0;
        return 1;
    }
    BountyRemaining=FMath::Max(0.0,BountyRemaining-Seconds);
    return BountyRemaining>0 ? 0 : -1;
}
