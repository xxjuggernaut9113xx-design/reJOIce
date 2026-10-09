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
static const TArray<FRecoveredMediaEntry>* SelectDeck(const FRecoveredMediaDecks& Decks,uint8 Deck) {
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
static bool EntriesMatch(const FRecoveredMediaEntry& Left,const FRecoveredMediaEntry& Right) {
    return FRecoveredMediaEntry::StaticStruct()->CompareScriptStruct(&Left,&Right,0);
}
void URecoveredDeckState::SetChildDecks() { Child=Master; }
void URecoveredDeckState::ReplaceEmptyDecks() {
    for(uint8 Deck=0;Deck<7;++Deck) {
        auto* Target=SelectDeck(Child,Deck);
        if(Target->IsEmpty() && IsDeckRepeating(Deck)) *Target=*SelectDeck(Master,Deck);
    }
    for(uint8 Deck=0;Deck<5;++Deck) {
        auto* Target=SelectDeck(ChildFavorites,Deck);
        if(Target->IsEmpty() && IsDeckRepeating(Deck)) *Target=*SelectDeck(MasterFavorites,Deck);
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

void URecoveredDeckState::ShuffleDeck(uint8 Deck) {
    // Shuffle applies to the master deck entries.
    // Uses the same 0..6 deck indices as Draw; invalid indices do nothing.
    auto ShuffleArray = [](TArray<FRecoveredMediaEntry>& Arr) {
        for (int32 i = Arr.Num() - 1; i > 0; --i) {
            const int32 j = FMath::RandRange(0, i);
            Arr.Swap(i, j);
        }
    };
    if (auto* Entries=SelectDeck(Master,Deck)) ShuffleArray(*Entries);
    if (auto* Entries=SelectDeck(Child,Deck)) ShuffleArray(*Entries);
}

void URecoveredDeckState::SetDeckRepeat(uint8 Deck, bool bRepeat) {
    DeckRepeat.Add(Deck, bRepeat);
}

bool URecoveredDeckState::IsDeckRepeating(uint8 Deck) const {
    const bool* bRepeat = DeckRepeat.Find(Deck);
    return bRepeat ? *bRepeat : true; // Preserve original automatic refill unless explicitly disabled.
}

int32 URecoveredDeckState::FavoriteDeckForCardType(uint8 CardType) {
    switch (CardType) {
        case 0:return 0;
        case 1:return 1;
        case 2:
        case 4:
        case 5:
        case 7:
        case 8:return 2;
        case 3:return 3;
        case 6:return 4;
        default:return INDEX_NONE;
    }
}

FString URecoveredDeckState::FavoriteSaveKey(uint8 Deck) {
    switch (Deck) {
        case 0:return TEXT("RecoveryFavoriteMediaSlow");
        case 1:return TEXT("RecoveryFavoriteMediaMedium");
        case 2:return TEXT("RecoveryFavoriteMediaFast");
        case 3:return TEXT("RecoveryFavoriteMediaSuccubus");
        case 4:return TEXT("RecoveryFavoriteMediaCum");
        default:return FString();
    }
}

bool URecoveredDeckState::ToggleFavorite(uint8 Deck,const FRecoveredMediaEntry& Entry,bool& bNowFavorite) {
    bNowFavorite=false;
    if (Entry.FullPath.IsEmpty()) return false;
    TArray<FRecoveredMediaEntry>* MasterDeck=SelectDeck(MasterFavorites,Deck);
    TArray<FRecoveredMediaEntry>* ChildDeck=SelectDeck(ChildFavorites,Deck);
    if (!MasterDeck || !ChildDeck) return false;
    const bool bWasFavorite=MasterDeck->ContainsByPredicate([&Entry](const FRecoveredMediaEntry& Candidate) { return EntriesMatch(Candidate,Entry); });
    if (bWasFavorite) {
        MasterDeck->RemoveAll([&Entry](const FRecoveredMediaEntry& Candidate) { return EntriesMatch(Candidate,Entry); });
        ChildDeck->RemoveAll([&Entry](const FRecoveredMediaEntry& Candidate) { return EntriesMatch(Candidate,Entry); });
        return true;
    }
    MasterDeck->Add(Entry);
    ChildDeck->Add(Entry);
    bNowFavorite=true;
    return true;
}

void URecoveredDeckState::RestoreFavoritePaths(uint8 Deck,const TArray<FString>& Paths) {
    TArray<FRecoveredMediaEntry>* MasterDeck=SelectDeck(MasterFavorites,Deck);
    TArray<FRecoveredMediaEntry>* ChildDeck=SelectDeck(ChildFavorites,Deck);
    const TArray<FRecoveredMediaEntry>* SourceDeck=SelectDeck(Master,Deck);
    if (!MasterDeck || !ChildDeck || !SourceDeck) return;
    MasterDeck->Reset();
    ChildDeck->Reset();
    for (const FRecoveredMediaEntry& Entry : *SourceDeck) {
        if (Paths.Contains(Entry.FullPath)) {
            MasterDeck->Add(Entry);
            ChildDeck->Add(Entry);
        }
    }
}

TArray<FString> URecoveredDeckState::GetFavoritePaths(uint8 Deck) const {
    TArray<FString> Paths;
    const TArray<FRecoveredMediaEntry>* FavoriteDeck=SelectDeck(MasterFavorites,Deck);
    if (!FavoriteDeck) return Paths;
    for (const FRecoveredMediaEntry& Entry : *FavoriteDeck) {
        if (!Entry.FullPath.IsEmpty()) Paths.AddUnique(Entry.FullPath);
    }
    return Paths;
}

bool URecoveredDeckState::ChooseRandom(uint8 Deck,bool bFavorite,FRecoveredMediaEntry& Entry,bool bShuffle) {
    TArray<FRecoveredMediaEntry>* Target=SelectDeck(bFavorite ? ChildFavorites : Child,Deck);
    if (!Target || Target->IsEmpty()) { Entry=FRecoveredMediaEntry();return false; }
    if (bShuffle) {
        for (int32 Index=0;Index<Target->Num();++Index) Target->Swap(Index,FMath::RandRange(Index,Target->Num()-1));
    }
    Entry=(*Target)[FMath::RandRange(0,Target->Num()-1)];
    return true;
}
