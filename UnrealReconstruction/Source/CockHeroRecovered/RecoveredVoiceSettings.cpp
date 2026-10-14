#include "RecoveredMenu.h"

#include "Components/AudioComponent.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Dom/JsonObject.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "RecoveredRules.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundBase.h"

namespace {

constexpr TCHAR VoicePackCatalogRelativePath[] = TEXT("Recovery/Definitions/voice-pack-catalog.json");
constexpr TCHAR VoicePackEvidenceCatalogRelativePath[] = TEXT("RecoveryEvidence/voice-pack-catalog.json");
constexpr TCHAR VoicePackEntryClassPath[] = TEXT("/Game/Recovery/UI/VoicePackEntryWidget.VoicePackEntryWidget_C");
constexpr TCHAR SelectedVoicePackKey[] = TEXT("SelectedVoicePack");
constexpr TCHAR SmallPenisHumiliationKey[] = TEXT("SPHEnabled?");

bool ReadVoiceString(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,FString& Out) {
    return Object.IsValid() && Object->TryGetStringField(Name,Out);
}

bool ReadVoiceInteger(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,int32& Out) {
    if (!Object.IsValid() || !Object->HasTypedField<EJson::Number>(Name)) return false;
    Out=static_cast<int32>(Object->GetNumberField(Name));
    return true;
}

bool ReadVoiceTags(const TSharedPtr<FJsonObject>& Object,TArray<FText>& Out) {
    const TArray<TSharedPtr<FJsonValue>>* Values=nullptr;
    if (!Object.IsValid() || !Object->TryGetArrayField(TEXT("tags"),Values) || !Values || Values->Num()!=4) return false;
    Out.Reset();
    Out.Reserve(Values->Num());
    for (const TSharedPtr<FJsonValue>& Value:*Values) {
        FString Text;
        if (!Value.IsValid() || !Value->TryGetString(Text) || Text.IsEmpty()) return false;
        Out.Add(FText::FromString(Text));
    }
    return true;
}

USoundBase* LoadVoiceSound(const FString& AssetPath) {
    return AssetPath.IsEmpty() ? nullptr : LoadObject<USoundBase>(nullptr,*AssetPath);
}

bool SamePackText(const FText& Left,const FText& Right) {
    return Left.ToString().Equals(Right.ToString(),ESearchCase::IgnoreCase);
}

FText EquippedLabel() {
    return FText::FromString(TEXT("Equipped"));
}

FText EquipLabel() {
    return FText::FromString(TEXT("Equip"));
}

}

void URecoveredVoicePackEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindSourceTree();
    BindSourceEvents(true);
    ApplyPresentation();
}

void URecoveredVoicePackEntryWidget::NativeDestruct() {
    BindSourceEvents(false);
    Super::NativeDestruct();
}

void URecoveredVoicePackEntryWidget::BindSourceTree() {
    if (!SourceClickPackButton) SourceClickPackButton=Cast<UButton>(GetWidgetFromName(TEXT("ClickPackButton")));
    if (!SourceDisplayName) SourceDisplayName=Cast<UTextBlock>(GetWidgetFromName(TEXT("DisplayName")));
}

void URecoveredVoicePackEntryWidget::BindSourceEvents(bool bBind) {
    BindSourceTree();
    if (!SourceClickPackButton) return;
    if (bBind) {
        SourceClickPackButton->OnClicked.AddUniqueDynamic(this,&URecoveredVoicePackEntryWidget::HandleClicked);
        SourceClickPackButton->OnHovered.AddUniqueDynamic(this,&URecoveredVoicePackEntryWidget::HandleHovered);
        SourceClickPackButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredVoicePackEntryWidget::HandleUnhovered);
    } else {
        SourceClickPackButton->OnClicked.RemoveDynamic(this,&URecoveredVoicePackEntryWidget::HandleClicked);
        SourceClickPackButton->OnHovered.RemoveDynamic(this,&URecoveredVoicePackEntryWidget::HandleHovered);
        SourceClickPackButton->OnUnhovered.RemoveDynamic(this,&URecoveredVoicePackEntryWidget::HandleUnhovered);
    }
}

void URecoveredVoicePackEntryWidget::ApplyPresentation() {
    BindSourceTree();
    if (SourceDisplayName) SourceDisplayName->SetText(DisplayNameID);
}

void URecoveredVoicePackEntryWidget::PopulateVoicePackEntry(
    const FText& InDisplayName,
    const FText& InDescription,
    USoundBase* InSample1,
    USoundBase* InSample2,
    USoundBase* InSample3,
    const TArray<FText>& InTags,
    uint8 InVoicePackEnum,
    USoundBase* InSelectionLine) {
    DisplayNameID=InDisplayName;
    SampleLine1=InSample1;
    SampleLine2=InSample2;
    SampleLine3=InSample3;
    Tags=InTags;
    Description=InDescription;
    VoicePackEnum=InVoicePackEnum;
    SelectionLine=InSelectionLine;
    ApplyPresentation();
}

void URecoveredVoicePackEntryWidget::HandleClicked() {
    OnClicked.Broadcast(DisplayNameID,this);
}

void URecoveredVoicePackEntryWidget::HandleHovered() {
    PlayRecoveredAnimation(TEXT("OnHover"));
}

void URecoveredVoicePackEntryWidget::HandleUnhovered() {
    PlayRecoveredAnimation(TEXT("Unhover"));
}

void URecoveredVoiceSettings::NativeConstruct() {
    Super::NativeConstruct();
    BindSourceTree();
    BindSourceEvents(true);
    InitDefaultsFromSaveGame();
    bVoicelinesAllowedToTrigger=true;
    PopulateVoicepacks();
    SelectEquippedPack();
}

void URecoveredVoiceSettings::NativeDestruct() {
    StopAudioComponent();
    BindSourceEvents(false);
    for (URecoveredVoicePackEntryWidget* Entry:PackEntries) {
        if (Entry) Entry->OnClicked.RemoveDynamic(this,&URecoveredVoiceSettings::HandleVoicePackClicked);
    }
    PackEntries.Reset();
    Super::NativeDestruct();
}

void URecoveredVoiceSettings::BindSourceTree() {
    if (!SourcePacksScrollbox) SourcePacksScrollbox=Cast<UScrollBox>(GetWidgetFromName(TEXT("PacksScrollbox")));
    if (!SourceEquipButton) SourceEquipButton=Cast<UButton>(GetWidgetFromName(TEXT("EquipButton")));
    if (!SourceSample1Button) SourceSample1Button=Cast<UButton>(GetWidgetFromName(TEXT("Sample1Button")));
    if (!SourceSample2Button) SourceSample2Button=Cast<UButton>(GetWidgetFromName(TEXT("Sample2Button")));
    if (!SourceSample3Button) SourceSample3Button=Cast<UButton>(GetWidgetFromName(TEXT("Sample3Button")));
    if (!SourceHealthBarAndTextComboBox) SourceHealthBarAndTextComboBox=Cast<UComboBoxString>(GetWidgetFromName(TEXT("HealthBarAndTextComboBox")));
    if (!SourceEquipButtonText) SourceEquipButtonText=Cast<UTextBlock>(GetWidgetFromName(TEXT("EquipButtonText")));
    if (!SourcePackTitle) SourcePackTitle=Cast<UTextBlock>(GetWidgetFromName(TEXT("PackTitle")));
    if (!SourcePackDescription) SourcePackDescription=Cast<UTextBlock>(GetWidgetFromName(TEXT("PackDescription")));
    if (!SourceTag1) SourceTag1=Cast<UTextBlock>(GetWidgetFromName(TEXT("Tag1")));
    if (!SourceTag2) SourceTag2=Cast<UTextBlock>(GetWidgetFromName(TEXT("Tag2")));
    if (!SourceTag3) SourceTag3=Cast<UTextBlock>(GetWidgetFromName(TEXT("Tag3")));
    if (!SourceTag4) SourceTag4=Cast<UTextBlock>(GetWidgetFromName(TEXT("Tag4")));
}

void URecoveredVoiceSettings::BindSourceEvents(bool bBind) {
    BindSourceTree();
#define BIND_VOICE_BUTTON(Button,Clicked,Hovered,Unhovered) \
    if (Button) { \
        if (bBind) { \
            Button->OnClicked.AddUniqueDynamic(this,&URecoveredVoiceSettings::Clicked); \
            Button->OnHovered.AddUniqueDynamic(this,&URecoveredVoiceSettings::Hovered); \
            Button->OnUnhovered.AddUniqueDynamic(this,&URecoveredVoiceSettings::Unhovered); \
        } else { \
            Button->OnClicked.RemoveDynamic(this,&URecoveredVoiceSettings::Clicked); \
            Button->OnHovered.RemoveDynamic(this,&URecoveredVoiceSettings::Hovered); \
            Button->OnUnhovered.RemoveDynamic(this,&URecoveredVoiceSettings::Unhovered); \
        } \
    }
    BIND_VOICE_BUTTON(SourceEquipButton,HandleEquipClicked,HandleEquipHovered,HandleEquipUnhovered)
    BIND_VOICE_BUTTON(SourceSample1Button,HandleSample1Clicked,HandleSample1Hovered,HandleSample1Unhovered)
    BIND_VOICE_BUTTON(SourceSample2Button,HandleSample2Clicked,HandleSample2Hovered,HandleSample2Unhovered)
    BIND_VOICE_BUTTON(SourceSample3Button,HandleSample3Clicked,HandleSample3Hovered,HandleSample3Unhovered)
#undef BIND_VOICE_BUTTON
    if (SourceHealthBarAndTextComboBox) {
        if (bBind) SourceHealthBarAndTextComboBox->OnSelectionChanged.AddUniqueDynamic(this,&URecoveredVoiceSettings::HandleSPHSelection);
        else SourceHealthBarAndTextComboBox->OnSelectionChanged.RemoveDynamic(this,&URecoveredVoiceSettings::HandleSPHSelection);
    }
}

bool URecoveredVoiceSettings::LoadRecoveredVoicePackCatalog() {
    FString Json;
    const FString ContentCatalog=FPaths::ProjectContentDir()/VoicePackCatalogRelativePath;
    const FString EvidenceCatalog=FPaths::ProjectDir()/VoicePackEvidenceCatalogRelativePath;
    if (!FFileHelper::LoadFileToString(Json,*ContentCatalog) && !FFileHelper::LoadFileToString(Json,*EvidenceCatalog)) {
        LastVoiceError=TEXT("Voice-pack catalog unavailable");
        return false;
    }
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json),Root) || !Root.IsValid()) {
        LastVoiceError=TEXT("Voice-pack catalog invalid");
        return false;
    }
    const TArray<TSharedPtr<FJsonValue>>* Records=nullptr;
    if (!Root->TryGetArrayField(TEXT("packs"),Records) || !Records || Records->Num()!=4) {
        LastVoiceError=TEXT("Voice-pack catalog incomplete");
        return false;
    }
    TArray<FRecoveredVoicePackDefinition> Parsed;
    Parsed.Reserve(Records->Num());
    for (const TSharedPtr<FJsonValue>& Value:*Records) {
        const TSharedPtr<FJsonObject> Record=Value.IsValid() ? Value->AsObject() : nullptr;
        FString DisplayName,Description,Sample1Path,Sample2Path,Sample3Path,SelectionLinePath;
        int32 VoicePackValue=0;
        FRecoveredVoicePackDefinition Definition;
        if (!ReadVoiceString(Record,TEXT("display_name"),DisplayName)
            || !ReadVoiceString(Record,TEXT("description"),Description)
            || !ReadVoiceTags(Record,Definition.Tags)
            || !ReadVoiceInteger(Record,TEXT("voice_pack_enum"),VoicePackValue)
            || !ReadVoiceString(Record,TEXT("sample_1_asset_path"),Sample1Path)
            || !ReadVoiceString(Record,TEXT("sample_2_asset_path"),Sample2Path)
            || !ReadVoiceString(Record,TEXT("sample_3_asset_path"),Sample3Path)
            || !ReadVoiceString(Record,TEXT("selection_line_asset_path"),SelectionLinePath)
            || VoicePackValue<0 || VoicePackValue>3) {
            LastVoiceError=TEXT("Voice-pack catalog record invalid");
            return false;
        }
        Definition.DisplayName=FText::FromString(DisplayName);
        Definition.Description=FText::FromString(Description);
        Definition.VoicePackEnum=static_cast<uint8>(VoicePackValue);
        Definition.Sample1AssetPath=Sample1Path;
        Definition.Sample2AssetPath=Sample2Path;
        Definition.Sample3AssetPath=Sample3Path;
        Definition.SelectionLineAssetPath=SelectionLinePath;
        Definition.Sample1=LoadVoiceSound(Definition.Sample1AssetPath);
        Definition.Sample2=LoadVoiceSound(Definition.Sample2AssetPath);
        Definition.Sample3=LoadVoiceSound(Definition.Sample3AssetPath);
        Definition.SelectionLine=LoadVoiceSound(Definition.SelectionLineAssetPath);
        Parsed.Add(MoveTemp(Definition));
    }
    static const TCHAR* const SourceOrder[]={TEXT("Villainess"),TEXT("Teasing Brat"),TEXT("Dommy Mommy"),TEXT("Sweetheart")};
    for (int32 Index=0;Index<UE_ARRAY_COUNT(SourceOrder);++Index) {
        if (Parsed[Index].DisplayName.ToString()!=SourceOrder[Index] || Parsed[Index].VoicePackEnum!=Index) {
            LastVoiceError=TEXT("Voice-pack source order invalid");
            return false;
        }
    }
    VoicePacks=MoveTemp(Parsed);
    LastVoiceError.Reset();
    return true;
}

void URecoveredVoiceSettings::InitDefaultsFromSaveGame() {
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const int32 SavedVoicePack=Instance && Instance->CurrentSave
        ? FMath::Clamp(FMath::RoundToInt(Instance->CurrentSave->GetNumberSetting(SelectedVoicePackKey,0)),0,3)
        : 0;
    static const TCHAR* const PackNames[]={TEXT("Villainess"),TEXT("Teasing Brat"),TEXT("Dommy Mommy"),TEXT("Sweetheart")};
    EquippedPack=FText::FromString(PackNames[SavedVoicePack]);
}

void URecoveredVoiceSettings::PopulateVoicepacks() {
    BindSourceTree();
    if (!LoadRecoveredVoicePackCatalog()) return;
    for (URecoveredVoicePackEntryWidget* Entry:PackEntries) {
        if (Entry) Entry->OnClicked.RemoveDynamic(this,&URecoveredVoiceSettings::HandleVoicePackClicked);
    }
    PackEntries.Reset();
    if (SourcePacksScrollbox) SourcePacksScrollbox->ClearChildren();
    UClass* EntryClass=LoadClass<URecoveredVoicePackEntryWidget>(nullptr,VoicePackEntryClassPath);
    for (const FRecoveredVoicePackDefinition& Definition:VoicePacks) {
        URecoveredVoicePackEntryWidget* Entry=EntryClass
            ? CreateWidget<URecoveredVoicePackEntryWidget>(this,EntryClass)
            : CreateWidget<URecoveredVoicePackEntryWidget>(this,URecoveredVoicePackEntryWidget::StaticClass());
        if (!Entry) {
            LastVoiceError=TEXT("Voice-pack entry creation failed");
            continue;
        }
        Entry->PopulateVoicePackEntry(
            Definition.DisplayName,
            Definition.Description,
            Definition.Sample1,
            Definition.Sample2,
            Definition.Sample3,
            Definition.Tags,
            Definition.VoicePackEnum,
            Definition.SelectionLine);
        Entry->OnClicked.AddUniqueDynamic(this,&URecoveredVoiceSettings::HandleVoicePackClicked);
        if (SourcePacksScrollbox) SourcePacksScrollbox->AddChild(Entry);
        PackEntries.Add(Entry);
    }
}

void URecoveredVoiceSettings::SelectEquippedPack() {
    for (URecoveredVoicePackEntryWidget* Entry:PackEntries) {
        if (Entry && Entry->DisplayNameID.EqualTo(EquippedPack)) PackClicked(EquippedPack,Entry);
    }
}

void URecoveredVoiceSettings::PackClicked(const FText& DisplayName,URecoveredVoicePackEntryWidget* Widget) {
    PlayRecoveredAnimation(TEXT("SelectPackAnim"));
    if (!Widget) return;
    SelectedEntryWidget=Widget;
    VoicePackEnum=Widget->VoicePackEnum;
    SelectedPack=DisplayName;
    Sample1=Widget->SampleLine1;
    Sample2=Widget->SampleLine2;
    Sample3=Widget->SampleLine3;
    ApplySelectedPackPresentation();
}

void URecoveredVoiceSettings::ApplySelectedPackPresentation() {
    if (!SelectedEntryWidget) return;
    if (SourcePackTitle) SourcePackTitle->SetText(SelectedEntryWidget->DisplayNameID);
    if (SourcePackDescription) SourcePackDescription->SetText(SelectedEntryWidget->Description);
    UTextBlock* const TagBlocks[]={SourceTag1,SourceTag2,SourceTag3,SourceTag4};
    for (int32 Index=0;Index<UE_ARRAY_COUNT(TagBlocks);++Index) {
        if (TagBlocks[Index]) TagBlocks[Index]->SetText(SelectedEntryWidget->Tags.IsValidIndex(Index) ? SelectedEntryWidget->Tags[Index] : FText::GetEmpty());
    }
    if (SourceEquipButtonText) SourceEquipButtonText->SetText(SamePackText(SelectedPack,EquippedPack) ? EquippedLabel() : EquipLabel());
}

void URecoveredVoiceSettings::HandleVoicePackClicked(const FText& DisplayName,URecoveredVoicePackEntryWidget* Widget) {
    PackClicked(DisplayName,Widget);
}

void URecoveredVoiceSettings::StopAudioComponent() {
    if (IsValid(AudioComponent)) AudioComponent->Stop();
}

void URecoveredVoiceSettings::PlayVoicePreview(USoundBase* Sound) {
    StopAudioComponent();
    AudioComponent=Sound && GetWorld()
        ? UGameplayStatics::SpawnSound2D(this,Sound,1.0f,1.0f,0.0f,nullptr,false,true)
        : nullptr;
}

void URecoveredVoiceSettings::PlaySample(USoundBase* Sound,FName AnimationName) {
    PlayRecoveredAnimation(AnimationName);
    PlayVoicePreview(Sound);
}

void URecoveredVoiceSettings::PlaySample1() {
    PlaySample(Sample1,TEXT("Sample1ButtonClick"));
}

void URecoveredVoiceSettings::PlaySample2() {
    PlaySample(Sample2,TEXT("Sample2ButtonClick"));
}

void URecoveredVoiceSettings::PlaySample3() {
    PlaySample(Sample3,TEXT("Sample3ButtonClick"));
}

void URecoveredVoiceSettings::EquipSelectedPack() {
    if (SamePackText(SelectedPack,EquippedPack)) return;
    PlayRecoveredAnimation(TEXT("EquipButtonClick"));
    PlayVoicePreview(SelectedEntryWidget ? SelectedEntryWidget->SelectionLine : nullptr);
    EquippedPack=SelectedPack;
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) {
            Instance->CurrentSave->SetNumberSetting(SelectedVoicePackKey,VoicePackEnum);
            Instance->SaveRecoveredState();
        }
    }
    if (SourceEquipButtonText) SourceEquipButtonText->SetText(EquippedLabel());
}

void URecoveredVoiceSettings::SetSmallPenisHumiliationEnabled(bool bEnabled) {
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) {
            Instance->CurrentSave->SetBoolSetting(SmallPenisHumiliationKey,bEnabled);
            Instance->SaveRecoveredState();
        }
    }
}

void URecoveredVoiceSettings::SetTextBlock(FName Name,const FText& Value) const {
    if (auto* Text=Cast<UTextBlock>(GetWidgetFromName(Name))) Text->SetText(Value);
}

void URecoveredVoiceSettings::HandleEquipClicked() { EquipSelectedPack(); }
void URecoveredVoiceSettings::HandleEquipHovered() { PlayRecoveredAnimation(TEXT("EquipButtonHover")); }
void URecoveredVoiceSettings::HandleEquipUnhovered() { PlayRecoveredAnimation(TEXT("EquipButtonUnhover")); }
void URecoveredVoiceSettings::HandleSample1Clicked() { PlaySample1(); }
void URecoveredVoiceSettings::HandleSample2Clicked() { PlaySample2(); }
void URecoveredVoiceSettings::HandleSample3Clicked() { PlaySample3(); }
void URecoveredVoiceSettings::HandleSample1Hovered() { PlayRecoveredAnimation(TEXT("Sample1ButtonHover")); }
void URecoveredVoiceSettings::HandleSample1Unhovered() { PlayRecoveredAnimation(TEXT("Sample1ButtonUnhover")); }
void URecoveredVoiceSettings::HandleSample2Hovered() { PlayRecoveredAnimation(TEXT("Sample2ButtonHover")); }
void URecoveredVoiceSettings::HandleSample2Unhovered() { PlayRecoveredAnimation(TEXT("Sample2ButtonUnhover")); }
void URecoveredVoiceSettings::HandleSample3Hovered() { PlayRecoveredAnimation(TEXT("Sample3ButtonHover")); }
void URecoveredVoiceSettings::HandleSample3Unhovered() { PlayRecoveredAnimation(TEXT("Sample3ButtonUnhover")); }

void URecoveredVoiceSettings::HandleSPHSelection(FString SelectedItem,ESelectInfo::Type SelectionType) {
    if (SelectedItem.Equals(TEXT("on"),ESearchCase::IgnoreCase)) SetSmallPenisHumiliationEnabled(true);
    else if (SelectedItem.Equals(TEXT("off"),ESearchCase::IgnoreCase)) SetSmallPenisHumiliationEnabled(false);
}
