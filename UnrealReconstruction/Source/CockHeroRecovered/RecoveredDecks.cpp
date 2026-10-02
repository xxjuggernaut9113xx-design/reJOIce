#include "RecoveredDecks.h"

static TArray<FRecoveredMediaEntry>* SelectDeck(FRecoveredMediaDecks& Decks,uint8 Deck) {
    switch(Deck) {
        case 0:return &Decks.Slow;
        case 1:return &Decks.Medium;
        case 2:return &Decks.Fast;
        case 3:return &Decks.Succubus;
        case 4:return &Decks.Cum;
        case 5:return &Decks.Ass;
        case 6:return &Decks.Boobs;
        default:return nullptr;
    }
}
void URecoveredDeckState::SetChildDecks() { Child=Master; }
void URecoveredDeckState::ReplaceEmptyDecks() {
    for(uint8 Deck=0;Deck<7;++Deck) {
        auto* Target=SelectDeck(Child,Deck);
        if(Target->IsEmpty()) *Target=*SelectDeck(Master,Deck);
    }
    for(uint8 Deck=0;Deck<5;++Deck) {
        auto* Target=SelectDeck(ChildFavorites,Deck);
        if(Target->IsEmpty()) *Target=*SelectDeck(MasterFavorites,Deck);
    }
}
bool URecoveredDeckState::DrawAtIndex(TArray<FRecoveredMediaEntry>& Deck,int32 Index,FRecoveredMediaEntry& Entry) {
    if(!Deck.IsValidIndex(Index)) { Entry=FRecoveredMediaEntry();return false; }
    Entry=Deck[Index];
    // Kismet removes every identical struct, not just the selected index.
    Deck.RemoveAll([&Entry](const FRecoveredMediaEntry& Candidate) { return FRecoveredMediaEntry::StaticStruct()->CompareScriptStruct(&Candidate,&Entry,0); });
    return true;
}
bool URecoveredDeckState::Draw(uint8 Deck,bool bFavorite,FRecoveredMediaEntry& Entry) {
    auto* Target=SelectDeck(bFavorite ? ChildFavorites : Child,Deck);
    if(!Target || Target->IsEmpty()) { Entry=FRecoveredMediaEntry();return false; }
    // The original custom event receives an array value copy on its persistent frame.
    // Its shuffle changes RNG consumption, while removal affects the caller's reference.
    TArray<FRecoveredMediaEntry> Shuffled=*Target;
    for(int32 Index=0;Index<Shuffled.Num();++Index) Shuffled.Swap(Index,FMath::RandRange(Index,Shuffled.Num()-1));
    Entry=Shuffled[FMath::RandRange(0,Shuffled.Num()-1)];
    Target->RemoveAll([&Entry](const FRecoveredMediaEntry& Candidate) { return FRecoveredMediaEntry::StaticStruct()->CompareScriptStruct(&Candidate,&Entry,0); });
    return true;
}
FRecoveredCardTiming URecoveredCardRuleLibrary::CalculateCardTiming(int32 RolledStrokes,double RolledInterval,double CountMultiplier,double UserCountMultiplier,double TimeMultiplier) {
    FRecoveredCardTiming Result;
    Result.StrokeCount=FMath::TruncToInt(static_cast<double>(RolledStrokes)*(CountMultiplier*UserCountMultiplier));
    Result.BeatInterval=FMath::Clamp(RolledInterval*TimeMultiplier,0.28,5.0);
    return Result;
}
