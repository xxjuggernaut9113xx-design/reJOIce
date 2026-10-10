#include "RecoveredWidgetRecovery.h"
#include "RecoveredMenu.h"
#include "RecoveredSessionWidget.h"
#include "RecoveredTabbedInventoryWidget.h"
#include "RecoveredPG2TabbedInventoryWidget.h"
#include "RecoveredRestWidget.h"
#include "RecoveredEventWidgets.h"
#include "RecoveredPostCumContinueWidget.h"
#include "RecoveredStatsWidget.h"
#include "RecoveredChallengesMenu.h"
#include "RecoveredCalibrationWidget.h"
#include "RecoveredAudioSettings.h"
#include "RecoveredVideoSettings.h"
#include "RecoveredTagSettings.h"
#include "RecoveredToySettings.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/PackageName.h"
#include "UObject/UnrealType.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "Components/PanelWidget.h"
#include "Components/PanelSlot.h"
#include "Components/Border.h"
#if WITH_EDITOR
#include "WidgetBlueprint.h"
#include "WidgetBlueprintFactory.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "UObject/SavePackage.h"

namespace {
struct FLayoutReader {
    TMap<int32,UWidget*> Widgets;
    TSharedPtr<FJsonObject> Imports;
    TSharedPtr<FJsonObject> ResourceAliases;
    TArray<TSharedPtr<FJsonValue>> Warnings;
    void Warn(const FString& Message) { Warnings.Add(MakeShared<FJsonValueString>(Message)); }
    void Apply(UStruct* Type, void* Data, const TSharedPtr<FJsonObject>& Values, const FString& Context) {
        for (const auto& Pair : Values->Values) {
            if (Pair.Key==TEXT("Slots") || Pair.Key==TEXT("Slot") || Pair.Key==TEXT("Parent") || Pair.Key==TEXT("Content")) continue;
            FProperty* Property=FindFProperty<FProperty>(Type,*Pair.Key);
            if (!Property) { Warn(Context+TEXT(" missing property ")+Pair.Key); continue; }
            Set(Property,Property->ContainerPtrToValuePtr<void>(Data),Pair.Value,Context+TEXT(".")+Pair.Key);
        }
    }
    void Set(FProperty* Property,void* Address,const TSharedPtr<FJsonValue>& Value,const FString& Context) {
        if (auto* P=CastField<FTextProperty>(Property)) {
            FString Text;
            if (Value->Type==EJson::Object) Value->AsObject()->TryGetStringField(TEXT("text"),Text);
            else if(Value->Type==EJson::String) Text=Value->AsString();
            FText Result=FText::FromString(Text);
            if(Value->Type==EJson::Object) {
                FString Namespace,Key;
                if(Value->AsObject()->TryGetStringField(TEXT("namespace"),Namespace) && Value->AsObject()->TryGetStringField(TEXT("key"),Key))
                    Result=FText::ChangeKey(Namespace,Key,Result);
            }
            P->SetPropertyValue(Address,Result); return;
        }
        if(auto* P=CastField<FStrProperty>(Property)) { P->SetPropertyValue(Address,Value->IsNull() ? FString() : Value->AsString()); return; }
        if(auto* P=CastField<FNameProperty>(Property)) { P->SetPropertyValue(Address,Value->IsNull() ? NAME_None : FName(*Value->AsString())); return; }
        if(auto* P=CastField<FBoolProperty>(Property)) {
            P->SetPropertyValue(Address,Value->Type==EJson::Boolean ? Value->AsBool() : Value->AsNumber()!=0); return;
        }
        if(auto* P=CastField<FEnumProperty>(Property)) {
            double Number=Value->Type==EJson::Object ? Value->AsObject()->GetNumberField(TEXT("value")) : Value->AsNumber();
            P->GetUnderlyingProperty()->SetIntPropertyValue(Address,int64(Number)); return;
        }
        if(auto* P=CastField<FNumericProperty>(Property)) {
            const double Number=Value->Type==EJson::Object ? Value->AsObject()->GetNumberField(TEXT("value")) : Value->AsNumber();
            if(P->IsFloatingPoint()) P->SetFloatingPointPropertyValue(Address,Number);
            else P->SetIntPropertyValue(Address,int64(Number));
            return;
        }
        if(auto* P=CastField<FObjectPropertyBase>(Property)) {
            if(Value->IsNull()) { P->SetObjectPropertyValue(Address,nullptr); return; }
            const auto Object=Value->AsObject();
            const int32 Index=int32(Object->GetNumberField(TEXT("index")));
            UObject* Resource=nullptr;
            if(Index>0) Resource=Widgets.FindRef(Index);
            else {
                FString Path;
                if(Imports->TryGetStringField(FString::FromInt(Index),Path)) {
                    FString RecoveredPath;
                    if(ResourceAliases.IsValid() && ResourceAliases->TryGetStringField(Path,RecoveredPath)) Path=RecoveredPath;
                    Resource=StaticLoadObject(P->PropertyClass,nullptr,*Path,nullptr,LOAD_NoWarn);
                }
            }
            if(Resource) P->SetObjectPropertyValue(Address,Resource);
            else Warn(Context+TEXT(" unresolved resource ")+Object->GetStringField(TEXT("name")));
            return;
        }
        if(auto* P=CastField<FStructProperty>(Property)) {
            if(Value->Type!=EJson::Object) { Warn(Context+TEXT(" unsupported struct value")); return; }
            const auto Object=Value->AsObject();
            if(Object->HasField(TEXT("zero_initialized_struct"))) {
                if(P->Struct->GetFName()==TEXT("DeprecateSlateVector2D")) {
                    static_assert(sizeof(FVector2f)==8);
                    *static_cast<FVector2f*>(Address)=FVector2f::ZeroVector; return;
                }
                if(P->Struct->StructFlags & STRUCT_IsPlainOldData) FMemory::Memzero(Address,P->Struct->GetStructureSize());
                else Warn(Context+TEXT(" unsupported non-POD zero value"));
                return;
            }
            // Slate's legacy vector wrapper has native serialization and no reflected X/Y fields.
            if(P->Struct->GetFName()==TEXT("DeprecateSlateVector2D")) {
                static_assert(sizeof(FVector2f)==8);
                *static_cast<FVector2f*>(Address)=FVector2f(Object->GetNumberField(TEXT("X")),Object->GetNumberField(TEXT("Y"))); return;
            }
            Apply(P->Struct,Address,Object,Context); return;
        }
        if(auto* P=CastField<FArrayProperty>(Property)) {
            if(Value->Type!=EJson::Array) { Warn(Context+TEXT(" unsupported array value")); return; }
            FScriptArrayHelper Array(P,Address); Array.Resize(Value->AsArray().Num());
            for(int32 I=0;I<Array.Num();++I) Set(P->Inner,Array.GetRawPtr(I),Value->AsArray()[I],Context);
            return;
        }
        Warn(Context+TEXT(" unsupported ")+Property->GetClass()->GetName());
    }
};
int32 Ref(const TSharedPtr<FJsonObject>& Object,const TCHAR* Field) {
    const TSharedPtr<FJsonObject>* Value=nullptr;
    return Object->TryGetObjectField(Field,Value) ? int32((*Value)->GetNumberField(TEXT("index"))) : 0;
}
}
#endif

FString URecoveredWidgetRecovery::BuildWidgetAssets(const FString& EvidencePath) {
    auto Report=MakeShared<FJsonObject>();
    Report->SetBoolField(TEXT("full_game_complete"),false);
    Report->SetBoolField(TEXT("original_graphs_restored"),false);
    Report->SetBoolField(TEXT("animations_restored"),false);
    TArray<TSharedPtr<FJsonValue>> Reports,Errors;
#if WITH_EDITOR
    FString Input; TSharedPtr<FJsonObject> Evidence;
    if(!FFileHelper::LoadFileToString(Input,*EvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Input),Evidence)) {
        Errors.Add(MakeShared<FJsonValueString>(TEXT("Could not read widget evidence")));
    } else if(Evidence->GetArrayField(TEXT("failures")).Num()!=0) {
        Errors.Add(MakeShared<FJsonValueString>(TEXT("Widget evidence contains decoding failures")));
    } else {
        FString AliasText; TSharedPtr<FJsonObject> ResourceAliases;
        if(FFileHelper::LoadFileToString(AliasText,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/resource-aliases.json"))))
            FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(AliasText),ResourceAliases);
        FString TooltipText; TSharedPtr<FJsonObject> TooltipEvidence;
        if(!FFileHelper::LoadFileToString(TooltipText,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/static-tooltip-values.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(TooltipText),TooltipEvidence))
            Errors.Add(MakeShared<FJsonValueString>(TEXT("Missing verified tooltip evidence")));
        TMap<FString,TArray<TSharedPtr<FJsonObject>>> Screens;
        for(const auto& Value:Evidence->GetArrayField(TEXT("widgets"))) Screens.FindOrAdd(Value->AsObject()->GetStringField(TEXT("asset"))).Add(Value->AsObject());
        TArray<FString> Order;
        TSet<FString> Visiting,Visited;
        TFunction<void(const FString&)> Visit=[&](const FString& Name) {
            if(Visited.Contains(Name) || Visiting.Contains(Name)) return;
            Visiting.Add(Name);
            for(const auto& Value:Evidence->GetArrayField(TEXT("omitted_custom_widgets"))) {
                const auto Record=Value->AsObject();
                if(Record->GetStringField(TEXT("asset"))!=Name) continue;
                FString Dependency=Record->GetStringField(TEXT("class")); Dependency.RemoveFromEnd(TEXT("_C"));
                if(Screens.Contains(Dependency)) Visit(Dependency);
            }
            Visiting.Remove(Name); Visited.Add(Name); Order.Add(Name);
        };
        TArray<FString> Names; Screens.GetKeys(Names); Names.Sort();
        for(const auto& Name:Names) Visit(Name);
        for(const auto& ScreenName:Order) {
            const TPair<FString,TArray<TSharedPtr<FJsonObject>>> Screen(ScreenName,Screens[ScreenName]);
            FLayoutReader Reader; Reader.Imports=Evidence->GetObjectField(TEXT("imports"))->GetObjectField(Screen.Key);
            Reader.ResourceAliases=ResourceAliases;
            FString PackageName=TEXT("/Game/Recovery/UI/")+Screen.Key;
            UWidgetBlueprint* Existing=nullptr;
            if(FPackageName::DoesPackageExist(PackageName)) Existing=LoadObject<UWidgetBlueprint>(nullptr,*(PackageName+TEXT(".")+Screen.Key));
            UPackage* Package=CreatePackage(*PackageName);
            Package->FullyLoad();
            UWidgetBlueprint* Blueprint=Existing ? Existing : FindObject<UWidgetBlueprint>(Package,*Screen.Key);
            UClass* ParentClass=URecoveredMenuWidget::StaticClass();
            if(Screen.Key==TEXT("CustomToolTip_Widget")) ParentClass=URecoveredTooltip::StaticClass();
            if(Screen.Key==TEXT("MainMenu")) ParentClass=URecoveredMainMenu::StaticClass();
            if(Screen.Key==TEXT("UI_Manager")) ParentClass=URecoveredSessionWidget::StaticClass();
            if(Screen.Key==TEXT("PG1TabbedInventory_Widget")) ParentClass=URecoveredTabbedInventoryWidget::StaticClass();
            if(Screen.Key==TEXT("PG2TabbedInventory_Widget")) ParentClass=URecoveredPG2TabbedInventoryWidget::StaticClass();
            if(Screen.Key==TEXT("RestWidget")) ParentClass=URecoveredRestWidget::StaticClass();
            if(Screen.Key==TEXT("PostCumContinue_Widget")) ParentClass=URecoveredPostCumContinueWidget::StaticClass();
            if(Screen.Key==TEXT("StatsScreenWidget")) ParentClass=URecoveredStatsScreenWidget::StaticClass();
            if(Screen.Key==TEXT("ChallengesMenuWidget")) ParentClass=URecoveredChallengesMenu::StaticClass();
            if(URecoveredAnimatedOverlay::SupportsAsset(FName(*Screen.Key))) ParentClass=URecoveredAnimatedOverlay::StaticClass();
            if(Screen.Key==TEXT("UMG_BeatIcon")) ParentClass=URecoveredBeatWidget::StaticClass();
            if(Screen.Key==TEXT("WBP_CalibrationUI")) ParentClass=URecoveredCalibrationWidget::StaticClass();
            if(Screen.Key==TEXT("StoreWidget")) ParentClass=URecoveredStoreWidget::StaticClass();
            if(Screen.Key==TEXT("DifficultySelectScreen_Widget")) ParentClass=URecoveredDifficultyMenu::StaticClass();
            if(Screen.Key==TEXT("SettingsMenuWidget")) ParentClass=URecoveredSettingsMenu::StaticClass();
            if(Screen.Key==TEXT("VoicelineSettingsMenu")) ParentClass=URecoveredVoiceSettings::StaticClass();
            if(Screen.Key==TEXT("AudioSettingsMenu")) ParentClass=URecoveredAudioSettingsMenu::StaticClass();
            if(Screen.Key==TEXT("VideoSettingsMenu")) ParentClass=URecoveredVideoSettingsMenu::StaticClass();
            if(Screen.Key==TEXT("TagSettingsMenu")) ParentClass=URecoveredTagSettingsMenu::StaticClass();
            if(Screen.Key==TEXT("ToySettingsMenu")) ParentClass=URecoveredToySettingsMenu::StaticClass();

            if(!Blueprint) {
                auto* Factory=NewObject<UWidgetBlueprintFactory>(); Factory->ParentClass=ParentClass;
                Blueprint=Cast<UWidgetBlueprint>(Factory->FactoryCreateNew(UWidgetBlueprint::StaticClass(),Package,FName(*Screen.Key),RF_Public|RF_Standalone,nullptr,GWarn));
            }
            if(!Blueprint) { Errors.Add(MakeShared<FJsonValueString>(Screen.Key+TEXT(" could not create blueprint"))); continue; }
            if(Blueprint->ParentClass!=ParentClass) {
                Blueprint->ParentClass=ParentClass;
                FBlueprintEditorUtils::RefreshAllNodes(Blueprint);
                FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
            }
            if(Blueprint->WidgetTree) Blueprint->WidgetTree->Rename(nullptr,GetTransientPackage(),REN_DontCreateRedirectors|REN_NonTransactional);
            Blueprint->WidgetTree=NewObject<UWidgetTree>(Blueprint,TEXT("WidgetTree"),RF_Transactional);
            TMap<int32,TSharedPtr<FJsonObject>> Records;
            int32 Root=0,Linked=0;
            for(const auto& Record:Screen.Value) {
                int32 Index=int32(Record->GetNumberField(TEXT("export_index"))); Records.Add(Index,Record);
                const FString ClassName=Record->GetStringField(TEXT("class"));
                if(ClassName==TEXT("WidgetTree")) { Root=Ref(Record->GetObjectField(TEXT("values")),TEXT("RootWidget")); continue; }
                UClass* Class=LoadObject<UClass>(nullptr,*(TEXT("/Script/UMG.")+ClassName));
                if(Class && Class->IsChildOf(UWidget::StaticClass()) && !Class->HasAnyClassFlags(CLASS_Abstract))
                    Reader.Widgets.Add(Index,Blueprint->WidgetTree->ConstructWidget<UWidget>(Class,FName(*Record->GetStringField(TEXT("name")))));
            }
            for(const auto& Value:Evidence->GetArrayField(TEXT("omitted_custom_widgets"))) {
                auto Record=Value->AsObject(); if(Record->GetStringField(TEXT("asset"))!=Screen.Key) continue;
                const int32 Index=int32(Record->GetNumberField(TEXT("export_index")));
                const FString ClassName=Record->GetStringField(TEXT("class"));
                FString AssetName=ClassName; AssetName.RemoveFromEnd(TEXT("_C"));
                UClass* ChildClass=Screens.Contains(AssetName) ? LoadObject<UClass>(nullptr,*(TEXT("/Game/Recovery/UI/")+AssetName+TEXT(".")+ClassName)) : nullptr;
                if(ChildClass && ChildClass->IsChildOf(UUserWidget::StaticClass()))
                    Reader.Widgets.Add(Index,Blueprint->WidgetTree->ConstructWidget<UWidget>(ChildClass,FName(*Record->GetStringField(TEXT("name")))));
                else {
                    Reader.Widgets.Add(Index,Blueprint->WidgetTree->ConstructWidget<UBorder>(UBorder::StaticClass(),FName(*Record->GetStringField(TEXT("name")))));
                    Reader.Warn(TEXT("Custom widget placeholder: ")+Record->GetStringField(TEXT("name"))+TEXT(" (")+ClassName+TEXT(")"));
                }
            }
            for(const auto& Pair:Reader.Widgets) if(const auto* Record=Records.Find(Pair.Key)) Reader.Apply(Pair.Value->GetClass(),Pair.Value,(*Record)->GetObjectField(TEXT("values")),Pair.Value->GetName());
            for(const auto& Pair:Reader.Widgets) {
                UPanelWidget* Panel=Cast<UPanelWidget>(Pair.Value); const auto* Record=Records.Find(Pair.Key);
                if(!Panel || !Record) continue;
                const TArray<TSharedPtr<FJsonValue>>* Slots=nullptr;
                if(!(*Record)->GetObjectField(TEXT("values"))->TryGetArrayField(TEXT("Slots"),Slots)) continue;
                for(const auto& Value:*Slots) {
                    const auto* SlotRecord=Records.Find(int32(Value->AsObject()->GetNumberField(TEXT("index"))));
                    if(!SlotRecord) { Reader.Warn(Panel->GetName()+TEXT(" missing slot record")); continue; }
                    auto SlotValues=(*SlotRecord)->GetObjectField(TEXT("values"));
                    UWidget* Child=Reader.Widgets.FindRef(Ref(SlotValues,TEXT("Content")));
                    if(!Child) { Reader.Warn(Panel->GetName()+TEXT(" missing child")); continue; }
                    UPanelSlot* Slot=Panel->AddChild(Child);
                    if(!Slot) { Reader.Warn(Panel->GetName()+TEXT(" could not attach child")); continue; }
                    Reader.Apply(Slot->GetClass(),Slot,SlotValues,(*SlotRecord)->GetStringField(TEXT("name"))); ++Linked;
                }
            }
            Blueprint->WidgetTree->RootWidget=Reader.Widgets.FindRef(Root);
            if(!Blueprint->WidgetTree->RootWidget) Errors.Add(MakeShared<FJsonValueString>(Screen.Key+TEXT(" missing root")));
            FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
            FKismetEditorUtilities::CompileBlueprint(Blueprint);
            if(Blueprint->Status==BS_Error) Errors.Add(MakeShared<FJsonValueString>(Screen.Key+TEXT(" compile failed")));
            if(auto* MenuDefaults=Cast<URecoveredMenuWidget>(Blueprint->GeneratedClass->GetDefaultObject())) {
                MenuDefaults->StaticTooltips.Reset();
                if(TooltipEvidence.IsValid()) for(const auto& Value:TooltipEvidence->GetArrayField(TEXT("records"))) {
                    const auto Record=Value->AsObject();
                    if(Record->GetStringField(TEXT("asset"))!=Screen.Key) continue;
                    const FString WidgetName=Record->GetStringField(TEXT("widget"));
                    if(!Blueprint->WidgetTree->FindWidget(FName(*WidgetName))) { Errors.Add(MakeShared<FJsonValueString>(Screen.Key+TEXT(" missing tooltip target ")+WidgetName)); continue; }
                    const auto MakeText=[](const TSharedPtr<FJsonObject>& Text) {
                        if(Text->HasField(TEXT("invariant"))) return FText::AsCultureInvariant(Text->GetStringField(TEXT("text")));
                        return FText::ChangeKey(Text->GetStringField(TEXT("namespace")),Text->GetStringField(TEXT("key")),FText::FromString(Text->GetStringField(TEXT("text"))));
                    };
                    FRecoveredTooltipDefinition Definition;
                    Definition.Title=MakeText(Record->GetObjectField(TEXT("title"))); Definition.Description=MakeText(Record->GetObjectField(TEXT("description")));
                    MenuDefaults->StaticTooltips.Add(FName(*WidgetName),Definition);
                }
            }
            if(Screen.Key==TEXT("SettingsMenuWidget") || Screen.Key==TEXT("MainMenu")) {
                FString DefaultsText; TSharedPtr<FJsonObject> Defaults;
                if(!FFileHelper::LoadFileToString(DefaultsText,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/widget-class-defaults.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(DefaultsText),Defaults)) {
                    Errors.Add(MakeShared<FJsonValueString>(TEXT("Missing verified widget defaults")));
                } else {
                    bool Found=false;
                    for(const auto& Default:Defaults->GetArrayField(TEXT("defaults"))) {
                        const auto Record=Default->AsObject();
                        if(Record->GetStringField(TEXT("class"))!=Screen.Key+TEXT("_C")) continue;
                        Found=true;
                        if(!Record->GetBoolField(TEXT("byte_identical_roundtrip"))) { Errors.Add(MakeShared<FJsonValueString>(TEXT("Unverified settings defaults"))); break; }
                        auto Values=MakeShared<FJsonObject>(); const auto Original=Record->GetObjectField(TEXT("values"));
                        if(Screen.Key==TEXT("MainMenu")) Values->SetField(TEXT("PatreonCoverGirlArray"),Original->TryGetField(TEXT("PatreonCoverGirlArray")));
                        else {
                            Values->SetField(TEXT("ClickedStyle"),Original->TryGetField(TEXT("Clicked Style")));
                            Values->SetField(TEXT("UnclickedStyle"),Original->TryGetField(TEXT("UnclickedStyle")));
                        }
                        UObject* CDO=Blueprint->GeneratedClass->GetDefaultObject();
                        Reader.Apply(CDO->GetClass(),CDO,Values,TEXT("SettingsMenuWidget_C defaults"));
                    }
                    if(!Found) Errors.Add(MakeShared<FJsonValueString>(TEXT("No verified settings defaults")));
                }
            }
            FSavePackageArgs Save; Save.TopLevelFlags=RF_Public|RF_Standalone; Save.SaveFlags=SAVE_NoError;
            const FString Filename=FPackageName::LongPackageNameToFilename(PackageName,FPackageName::GetAssetPackageExtension());
            if(!UPackage::SavePackage(Package,Blueprint,*Filename,Save)) Errors.Add(MakeShared<FJsonValueString>(Screen.Key+TEXT(" save failed")));
            auto Entry=MakeShared<FJsonObject>(); Entry->SetStringField(TEXT("asset"),PackageName); Entry->SetNumberField(TEXT("widgets"),Reader.Widgets.Num()); Entry->SetNumberField(TEXT("linked_slots"),Linked); Entry->SetArrayField(TEXT("warnings"),Reader.Warnings); Reports.Add(MakeShared<FJsonValueObject>(Entry));
        }
    }
#else
    Errors.Add(MakeShared<FJsonValueString>(TEXT("Widget reconstruction requires the editor")));
#endif
    Report->SetArrayField(TEXT("assets"),Reports); Report->SetArrayField(TEXT("errors"),Errors);
    FString Output; FJsonSerializer::Serialize(Report,TJsonWriterFactory<>::Create(&Output)); return Output;
}
