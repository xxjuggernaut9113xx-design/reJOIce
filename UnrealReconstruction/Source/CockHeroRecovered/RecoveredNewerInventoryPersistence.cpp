#include "RecoveredNewerInventory.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace {
bool ReadInteger(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,int32& Result) {
    double Number;
    if (!Object->TryGetNumberField(Name,Number) || !FMath::IsFinite(Number) || Number<MIN_int32 || Number>MAX_int32 || Number!=FMath::FloorToDouble(Number)) return false;
    Result=static_cast<int32>(Number);
    return true;
}
}

FString URecoveredNewerInventory::ExportRecoveryState() const {
    if (HotbarItems.Num()>4096) return FString();
    auto Root=MakeShared<FJsonObject>();
    Root->SetNumberField(TEXT("version"),1);
    TArray<ERecoveredShopItemType> Keys;
    OwnedItems.GetKeys(Keys);
    Keys.Sort([](ERecoveredShopItemType A,ERecoveredShopItemType B) { return static_cast<uint8>(A)<static_cast<uint8>(B); });
    TArray<TSharedPtr<FJsonValue>> Entries,Slots;
    for (const auto Key:Keys) {
        const auto& State=OwnedItems[Key];
        auto Entry=MakeShared<FJsonObject>();
        Entry->SetNumberField(TEXT("type"),static_cast<uint8>(Key));
        Entry->SetBoolField(TEXT("unlocked"),State.bIsUnlocked);
        Entry->SetNumberField(TEXT("level"),State.Level);
        Entry->SetNumberField(TEXT("charges"),State.Charges);
        Entries.Add(MakeShared<FJsonValueObject>(Entry));
    }
    for (const auto Item:HotbarItems) Slots.Add(MakeShared<FJsonValueNumber>(static_cast<uint8>(Item)));
    Root->SetArrayField(TEXT("ownedItems"),Entries);
    Root->SetArrayField(TEXT("hotbarItems"),Slots);
    FString Json;
    return FJsonSerializer::Serialize(Root,TJsonWriterFactory<>::Create(&Json)) ? Json : FString();
}

bool URecoveredNewerInventory::ImportRecoveryState(const FString& Json) {
    if (Json.Len()>1024*1024) return false;
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json),Root) || !Root) return false;
    int32 Version;
    const TArray<TSharedPtr<FJsonValue>>* Entries=nullptr;
    const TArray<TSharedPtr<FJsonValue>>* Slots=nullptr;
    if (!ReadInteger(Root,TEXT("version"),Version) || Version!=1 || !Root->TryGetArrayField(TEXT("ownedItems"),Entries) || Entries->Num()>256 || !Root->TryGetArrayField(TEXT("hotbarItems"),Slots) || Slots->Num()>4096) return false;
    TMap<ERecoveredShopItemType,FRecoveredNewerItemState> ParsedItems;
    TArray<ERecoveredShopItemType> ParsedSlots;
    for (const auto& Value:*Entries) {
        const TSharedPtr<FJsonObject>* Entry=nullptr;
        int32 Type=0;
        FRecoveredNewerItemState State;
        if (!Value || !Value->TryGetObject(Entry) || !Entry || !Entry->IsValid() || !ReadInteger(*Entry,TEXT("type"),Type) || Type<0 || Type>255 || !(*Entry)->TryGetBoolField(TEXT("unlocked"),State.bIsUnlocked) || !ReadInteger(*Entry,TEXT("level"),State.Level) || !ReadInteger(*Entry,TEXT("charges"),State.Charges)) return false;
        const auto Item=static_cast<ERecoveredShopItemType>(Type);
        if (ParsedItems.Contains(Item)) return false;
        ParsedItems.Add(Item,State);
    }
    for (const auto& Value:*Slots) {
        double Type=0;
        if (!Value || !Value->TryGetNumber(Type) || !FMath::IsFinite(Type) || Type<0 || Type>255 || Type!=FMath::FloorToDouble(Type)) return false;
        ParsedSlots.Add(static_cast<ERecoveredShopItemType>(static_cast<uint8>(Type)));
    }
    OwnedItems=MoveTemp(ParsedItems);
    HotbarItems=MoveTemp(ParsedSlots);
    return true;
}
