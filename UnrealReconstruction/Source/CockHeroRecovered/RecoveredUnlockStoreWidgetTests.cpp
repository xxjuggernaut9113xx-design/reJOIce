#include "RecoveredUnlockStoreWidget.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Dom/JsonObject.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "MovieScene.h"
#include "RecoveredRules.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "WidgetBlueprint.h"
#include "Widgets/SWidget.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
namespace {

bool LoadRecoveryJson(const TCHAR* RelativePath,TSharedPtr<FJsonObject>& OutObject) {
    FString Text;
    return FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/RelativePath))
        && FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),OutObject)
        && OutObject.IsValid();
}

bool HasSourceAnimation(const UWidgetBlueprintGeneratedClass* Generated,FName Name) {
    if (!Generated) return false;
    const FName InstanceName(*FString::Printf(TEXT("%s_INST"),*Name.ToString()));
    for (const TObjectPtr<UWidgetAnimation>& Animation:Generated->Animations) {
        if (!Animation) continue;
        const UMovieScene* Scene=Animation->GetMovieScene();
        if (
            Animation->GetFName()==Name ||
            Animation->GetFName()==InstanceName ||
            Animation->GetDisplayLabel().Equals(Name.ToString(),ESearchCase::CaseSensitive) ||
            Animation->GetDisplayLabel().Equals(InstanceName.ToString(),ESearchCase::CaseSensitive) ||
            (Scene && (Scene->GetFName()==Name || Scene->GetFName()==InstanceName))
        ) return true;
    }
    return false;
}

URecoveredPackEntryWidget* FindPackEntry(UUniformGridPanel* Grid,const FString& PackID) {
    if (!Grid) return nullptr;
    for (int32 Index=0;Index<Grid->GetChildrenCount();++Index) {
        auto* Entry=Cast<URecoveredPackEntryWidget>(Grid->GetChildAt(Index));
        if (Entry && Entry->PackID.Equals(PackID,ESearchCase::IgnoreCase)) return Entry;
    }
    return nullptr;
}

bool ContainsPack(const TArray<FString>& Values,const FString& Expected) {
    return Values.ContainsByPredicate([&Expected](const FString& Value) { return Value.Equals(Expected,ESearchCase::IgnoreCase); });
}

}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredUnlockStoreWidgetTest,"CockHero.Recovery.UnlockStoreWidget",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredUnlockStoreWidgetTest::RunTest(const FString& Parameters) {
    TSharedPtr<FJsonObject> Evidence;
    if (!LoadRecoveryJson(TEXT("RecoveryEvidence/unlock-store-recovery.json"),Evidence)) {
        AddError(TEXT("Missing unlock-store recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Unlock-store original source execution remains unclaimed"),Evidence->GetBoolField(TEXT("source_executed")));
    TestEqual(TEXT("Recovered shipping pack count"),int32(Evidence->GetIntegerField(TEXT("pack_count"))),14);
    const TSharedPtr<FJsonObject> Entrypoints=Evidence->GetObjectField(TEXT("source_entrypoints"));
    TestEqual(TEXT("Source store construct entrypoint"),Entrypoints->GetIntegerField(TEXT("Construct")),7238);
    TestEqual(TEXT("Source store back entrypoint"),Entrypoints->GetIntegerField(TEXT("BackButtonClicked")),7562);
    TestEqual(TEXT("Source store entry-click entrypoint"),Entrypoints->GetIntegerField(TEXT("OnEntryClicked")),7614);
    TestEqual(TEXT("Source store entry-hover entrypoint"),Entrypoints->GetIntegerField(TEXT("OnEntryHovered")),8509);
    TestEqual(TEXT("Source store entry-unhover entrypoint"),Entrypoints->GetIntegerField(TEXT("OnEntryUnhovered")),7613);
    TestEqual(TEXT("Source store interaction entrypoint"),Entrypoints->GetIntegerField(TEXT("InteractionButtonClicked")),8606);
    TestEqual(TEXT("Source store refresh entrypoint"),Entrypoints->GetIntegerField(TEXT("ClearRefreshPacks")),12680);
    TestEqual(TEXT("Source store batch entrypoint"),Entrypoints->GetIntegerField(TEXT("CreatePackBatch")),12951);
    TestEqual(TEXT("Source grid columns"),int32(Evidence->GetIntegerField(TEXT("grid_columns"))),4);
    TestEqual(TEXT("Source packs per frame"),int32(Evidence->GetIntegerField(TEXT("packs_per_frame"))),2);
    TestEqual(TEXT("Source challenge pack count"),int32(Evidence->GetIntegerField(TEXT("challenge_reward_pack_count"))),9);
    TestEqual(TEXT("Source patron pack count"),int32(Evidence->GetIntegerField(TEXT("patreon_exclusive_pack_count"))),4);

    const TSharedPtr<FJsonObject> SourceComponents=Evidence->GetObjectField(TEXT("source_widget_components"));
    TestEqual(TEXT("Store source component record count"),int32(SourceComponents->GetIntegerField(TEXT("UnlockStoreWidget"))),78);
    TestEqual(TEXT("Pack entry source component record count"),int32(SourceComponents->GetIntegerField(TEXT("CHPackEntryWidget"))),12);
    TestEqual(TEXT("Social entry source component record count"),int32(SourceComponents->GetIntegerField(TEXT("UnlockStoreSocialIconBaseButton"))),4);
    const TSharedPtr<FJsonObject> SocialContract=Evidence->GetObjectField(TEXT("social_icon_contract"));
    TestEqual(TEXT("Source social-button cap"),int32(SocialContract->GetIntegerField(TEXT("max_buttons"))),4);
    TestEqual(TEXT("Source social-link order count"),SocialContract->GetArrayField(TEXT("platform_order")).Num(),10);
    const TSharedPtr<FJsonObject> SocialEntrypoints=SocialContract->GetObjectField(TEXT("source_entrypoints"));
    TestEqual(TEXT("Source social construct entrypoint"),SocialEntrypoints->GetIntegerField(TEXT("Construct")),34);
    TestEqual(TEXT("Source social hover entrypoint"),SocialEntrypoints->GetIntegerField(TEXT("Hover")),39);
    TestEqual(TEXT("Source social unhover entrypoint"),SocialEntrypoints->GetIntegerField(TEXT("Unhover")),91);
    TestEqual(TEXT("Source social click entrypoint"),SocialEntrypoints->GetIntegerField(TEXT("Click")),143);

    TSharedPtr<FJsonObject> Catalog;
    if (!LoadRecoveryJson(TEXT("RecoveryEvidence/pack-store-catalog.json"),Catalog)) {
        AddError(TEXT("Missing recovered pack catalog"));
        return false;
    }
    const TArray<TSharedPtr<FJsonValue>>& CatalogPacks=Catalog->GetArrayField(TEXT("packs"));
    TestEqual(TEXT("Catalog preserves all shipping manifests"),CatalogPacks.Num(),14);
    TestEqual(TEXT("Catalog source order count"),Catalog->GetArrayField(TEXT("source_order")).Num(),14);
    int32 CatalogChallengePacks=0;
    int32 CatalogPatronPacks=0;
    for (const TSharedPtr<FJsonValue>& Value:CatalogPacks) {
        const TSharedPtr<FJsonObject> Pack=Value.IsValid() ? Value->AsObject() : nullptr;
        if (!TestNotNull(TEXT("Catalog pack record"),Pack.Get())) continue;
        TestEqual(TEXT("Catalog preview width"),int32(Pack->GetIntegerField(TEXT("width"))),512);
        TestEqual(TEXT("Catalog preview height"),int32(Pack->GetIntegerField(TEXT("height"))),512);
        TestEqual(TEXT("Catalog preview format"),Pack->GetStringField(TEXT("format")),FString(TEXT("PNG")));
        const TSharedPtr<FJsonObject> Links=Pack->GetObjectField(TEXT("social_links"));
        TestEqual(TEXT("Catalog social-link field count"),Links->Values.Num(),10);
        CatalogChallengePacks+=Pack->GetStringField(TEXT("challenge_name")).IsEmpty() ? 0 : 1;
        CatalogPatronPacks+=Pack->GetBoolField(TEXT("patreon_exclusive")) ? 1 : 0;
        UTexture2D* Preview=LoadObject<UTexture2D>(nullptr,*Pack->GetStringField(TEXT("asset_path")));
        if (TestNotNull(*FString::Printf(TEXT("Catalog preview texture: %s"),*Pack->GetStringField(TEXT("pack_id"))),Preview)) {
            TestEqual(TEXT("Catalog preview imported width"),Preview->GetImportedSize().X,512);
            TestEqual(TEXT("Catalog preview imported height"),Preview->GetImportedSize().Y,512);
        }
    }
    TestEqual(TEXT("Catalog challenge mapping count"),CatalogChallengePacks,9);
    TestEqual(TEXT("Catalog patron mapping count"),CatalogPatronPacks,4);

    UWidgetBlueprint* StoreBlueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/UnlockStoreWidget.UnlockStoreWidget"));
    UWidgetBlueprint* EntryBlueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/CHPackEntryWidget.CHPackEntryWidget"));
    UWidgetBlueprint* SocialBlueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/UnlockStoreSocialIconBaseButton.UnlockStoreSocialIconBaseButton"));
    if (!TestNotNull(TEXT("Recovered unlock-store blueprint"),StoreBlueprint)
        || !TestNotNull(TEXT("Recovered pack-entry blueprint"),EntryBlueprint)
        || !TestNotNull(TEXT("Recovered social-entry blueprint"),SocialBlueprint)) return false;
    TestTrue(TEXT("Unlock-store native owner restored"),StoreBlueprint->GeneratedClass->IsChildOf(URecoveredUnlockStoreWidget::StaticClass()));
    TestTrue(TEXT("Pack-entry native owner restored"),EntryBlueprint->GeneratedClass->IsChildOf(URecoveredPackEntryWidget::StaticClass()));
    TestTrue(TEXT("Social-entry native owner restored"),SocialBlueprint->GeneratedClass->IsChildOf(URecoveredUnlockStoreSocialIconWidget::StaticClass()));
    const UWidgetBlueprintGeneratedClass* StoreGenerated=Cast<UWidgetBlueprintGeneratedClass>(StoreBlueprint->GeneratedClass);
    const UWidgetBlueprintGeneratedClass* EntryGenerated=Cast<UWidgetBlueprintGeneratedClass>(EntryBlueprint->GeneratedClass);
    const UWidgetBlueprintGeneratedClass* SocialGenerated=Cast<UWidgetBlueprintGeneratedClass>(SocialBlueprint->GeneratedClass);
    if (!TestNotNull(TEXT("Unlock-store generated class"),StoreGenerated)
        || !TestNotNull(TEXT("Pack-entry generated class"),EntryGenerated)
        || !TestNotNull(TEXT("Social-entry generated class"),SocialGenerated)) return false;
    TestEqual(TEXT("Store authored animation count"),StoreBlueprint->Animations.Num(),9);
    TestEqual(TEXT("Store runtime animation count"),StoreGenerated->Animations.Num(),9);
    for (const TCHAR* Name:{TEXT("BackButtonHover"),TEXT("BackButtonUnhover"),TEXT("BuyPackFailed"),TEXT("BuyPackSuccess"),TEXT("DisablePackAnim"),TEXT("EnablePackAnim"),TEXT("OnInteractionButtonHover"),TEXT("OnInteractionButtonUnhover"),TEXT("OnUpdateInfo")}) {
        TestTrue(*FString::Printf(TEXT("Store source animation: %s"),Name),HasSourceAnimation(StoreGenerated,FName(Name)));
    }
    TestEqual(TEXT("Pack-entry authored animation count"),EntryBlueprint->Animations.Num(),3);
    TestEqual(TEXT("Pack-entry runtime animation count"),EntryGenerated->Animations.Num(),3);
    for (const TCHAR* Name:{TEXT("Click"),TEXT("OnHoverAnim"),TEXT("OnUnHoverAnim")}) {
        TestTrue(*FString::Printf(TEXT("Pack-entry source animation: %s"),Name),HasSourceAnimation(EntryGenerated,FName(Name)));
    }
    TestEqual(TEXT("Social-entry authored animation count"),SocialBlueprint->Animations.Num(),2);
    TestEqual(TEXT("Social-entry runtime animation count"),SocialGenerated->Animations.Num(),2);
    for (const TCHAR* Name:{TEXT("HoverSocial"),TEXT("UnHoverSocial")}) {
        TestTrue(*FString::Printf(TEXT("Social-entry source animation: %s"),Name),HasSourceAnimation(SocialGenerated,FName(Name)));
    }

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };

    auto* Instance=NewObject<URecoveredGameInstance>(World);
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Unlock-store test save initializes"),Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Unlock-store test starts as public build"),Save->SetBoolSetting(TEXT("IsPatron?"),false))) return false;
    const FString TestSlot=URecoveredGameInstance::GetNamedRecoverySlotPrefix()+TEXT("UnlockStoreWidgetAutomation");
    UGameplayStatics::DeleteGameInSlot(TestSlot,0);
    ON_SCOPE_EXIT { UGameplayStatics::DeleteGameInSlot(TestSlot,0); };
    Instance->CurrentSave=Save;
    Instance->ActiveRecoverySlot=TestSlot;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    UClass* StoreClass=LoadClass<URecoveredUnlockStoreWidget>(nullptr,TEXT("/Game/Recovery/UI/UnlockStoreWidget.UnlockStoreWidget_C"));
    UClass* EntryClass=LoadClass<URecoveredPackEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/CHPackEntryWidget.CHPackEntryWidget_C"));
    UClass* SocialClass=LoadClass<URecoveredUnlockStoreSocialIconWidget>(nullptr,TEXT("/Game/Recovery/UI/UnlockStoreSocialIconBaseButton.UnlockStoreSocialIconBaseButton_C"));
    if (!TestNotNull(TEXT("Recovered unlock-store class"),StoreClass)
        || !TestNotNull(TEXT("Recovered pack-entry class"),EntryClass)
        || !TestNotNull(TEXT("Recovered social-entry class"),SocialClass)) return false;
    auto* Store=CreateWidget<URecoveredUnlockStoreWidget>(World,StoreClass);
    if (!TestNotNull(TEXT("Recovered unlock-store instantiates"),Store)) return false;
    TSharedRef<SWidget> StoreSlateWidget=Store->TakeWidget();

    auto* BackButton=Cast<UButton>(Store->GetWidgetFromName(TEXT("BackButton")));
    auto* EnableButton=Cast<UButton>(Store->GetWidgetFromName(TEXT("EnablePacksButton")));
    auto* DisableButton=Cast<UButton>(Store->GetWidgetFromName(TEXT("DisablePacksButton_1")));
    auto* InteractionButton=Cast<UButton>(Store->GetWidgetFromName(TEXT("InteractionButton")));
    auto* PackGrid=Cast<UUniformGridPanel>(Store->GetWidgetFromName(TEXT("PackUniformGrid")));
    auto* EnableDisablePacksBox=Cast<UVerticalBox>(Store->GetWidgetFromName(TEXT("EnableDisablePacksButton")));
    auto* SocialBox=Cast<UHorizontalBox>(Store->GetWidgetFromName(TEXT("SocialIconsHoriBox")));
    auto* PackName=Cast<UTextBlock>(Store->GetWidgetFromName(TEXT("PackNameText")));
    auto* AuthorName=Cast<UTextBlock>(Store->GetWidgetFromName(TEXT("AuthorNameText")));
    auto* TotalCards=Cast<UTextBlock>(Store->GetWidgetFromName(TEXT("TotalCardsText")));
    auto* UnlockPoints=Cast<UTextBlock>(Store->GetWidgetFromName(TEXT("TextBlock_393")));
    if (!TestNotNull(TEXT("Source back button"),BackButton)
        || !TestNotNull(TEXT("Source enable button"),EnableButton)
        || !TestNotNull(TEXT("Source disable button"),DisableButton)
        || !TestNotNull(TEXT("Source interaction button"),InteractionButton)
        || !TestNotNull(TEXT("Source pack uniform grid"),PackGrid)
        || !TestNotNull(TEXT("Source bulk-pack control box"),EnableDisablePacksBox)
        || !TestNotNull(TEXT("Source social icon row"),SocialBox)
        || !TestNotNull(TEXT("Source pack title"),PackName)
        || !TestNotNull(TEXT("Source author label"),AuthorName)
        || !TestNotNull(TEXT("Source total-cards label"),TotalCards)
        || !TestNotNull(TEXT("Source unlock-point label"),UnlockPoints)) return false;
    TestTrue(TEXT("Source back click binding"),BackButton->OnClicked.IsBound());
    TestTrue(TEXT("Source back hover binding"),BackButton->OnHovered.IsBound());
    TestTrue(TEXT("Source back unhover binding"),BackButton->OnUnhovered.IsBound());
    TestTrue(TEXT("Source enable-all binding"),EnableButton->OnClicked.IsBound());
    TestTrue(TEXT("Source disable-all binding"),DisableButton->OnClicked.IsBound());
    TestTrue(TEXT("Source interaction binding"),InteractionButton->OnClicked.IsBound());
    TestTrue(TEXT("Source interaction hover binding"),InteractionButton->OnHovered.IsBound());
    TestTrue(TEXT("Source interaction unhover binding"),InteractionButton->OnUnhovered.IsBound());
    TestEqual(TEXT("Non-patron source bulk controls collapse"),EnableDisablePacksBox->GetVisibility(),ESlateVisibility::Collapsed);
    TestEqual(TEXT("Store loads every catalog pack"),Store->AvailablePacks.Num(),14);
    TestEqual(TEXT("Store stages source grid before its timer fires"),Store->GetCreatedPackEntryCount(),0);
    TestEqual(TEXT("Store stages source grid panel before its timer fires"),PackGrid->GetChildrenCount(),0);
    TestTrue(TEXT("Store remains in source initialization during staged population"),Store->IsInit);
    Store->CreatePackBatch();
    TestEqual(TEXT("Store initializes first source batch"),Store->GetCreatedPackEntryCount(),2);
    TestEqual(TEXT("Store initializes first source grid batch"),PackGrid->GetChildrenCount(),2);
    TestEqual(TEXT("Store selects base pack"),Store->SelectedPackInfo.PackID,FString(TEXT("Base_Game_CG")));
    TestTrue(TEXT("Base pack initializes unlocked"),Store->IsPackUnlocked(TEXT("Base_Game_CG")));
    TestTrue(TEXT("Base pack initializes enabled"),Store->IsPackEnabled(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Base pack interaction label"),Store->GetInteractionLabel(),FString(TEXT("Pack Enabled")));
    TestEqual(TEXT("Base pack source title"),PackName->GetText().ToString(),FString(TEXT("Base Game CG")));
    TestEqual(TEXT("Base pack source author"),AuthorName->GetText().ToString(),FString(TEXT("Author: Official")));
    TestEqual(TEXT("Base pack source total cards"),TotalCards->GetText().ToString(),FString(TEXT("Total Cards: 487")));
    TestEqual(TEXT("Base pack source social-icon count"),Store->GetCreatedSocialIconCount(),3);
    TestEqual(TEXT("Base pack source social row count"),SocialBox->GetChildrenCount(),3);
    Store->OnEntryHovered(TEXT("Remedy_Vol._1"));
    TestEqual(TEXT("Source entry hover preserves selection"),Store->SelectedPackInfo.PackID,FString(TEXT("Base_Game_CG")));
    TestEqual(TEXT("Source entry hover preserves detail title"),PackName->GetText().ToString(),FString(TEXT("Base Game CG")));
    Store->OnEntryUnhovered();
    TestEqual(TEXT("Source entry unhover preserves selection"),Store->SelectedPackInfo.PackID,FString(TEXT("Base_Game_CG")));
    const TArray<uint8> ExpectedSocialPlatforms={2,6,7};
    const TArray<FString> ExpectedSocialURLs={TEXT("https://x.com/CockHeroGame"),TEXT("https://discord.com/invite/dQXRpF6Uhf"),TEXT("https://www.patreon.com/CockHeroGame")};
    for (int32 Index=0;Index<ExpectedSocialPlatforms.Num();++Index) {
        auto* Social=Cast<URecoveredUnlockStoreSocialIconWidget>(SocialBox->GetChildAt(Index));
        if (!TestNotNull(*FString::Printf(TEXT("Source social icon %d"),Index),Social)) continue;
        TestEqual(TEXT("Source social class"),Social->GetClass(),SocialClass);
        TestEqual(TEXT("Source social platform order"),Social->GetSocialPlatform(),ExpectedSocialPlatforms[Index]);
        TestEqual(TEXT("Source social URL"),Social->GetCreatorURL(),ExpectedSocialURLs[Index]);
        auto* SocialButton=Cast<UButton>(Social->GetWidgetFromName(TEXT("SocialButton")));
        if (TestNotNull(TEXT("Source social button"),SocialButton)) {
            TestTrue(TEXT("Source social click binding"),SocialButton->OnClicked.IsBound());
            TestTrue(TEXT("Source social hover binding"),SocialButton->OnHovered.IsBound());
            TestTrue(TEXT("Source social unhover binding"),SocialButton->OnUnhovered.IsBound());
            TestEqual(TEXT("Source social icon image width"),SocialButton->GetStyle().Normal.ImageSize.X,32.0f);
            TestEqual(TEXT("Source social icon image height"),SocialButton->GetStyle().Normal.ImageSize.Y,32.0f);
        }
        if (auto* Slot=Cast<UHorizontalBoxSlot>(Social->Slot)) TestEqual(TEXT("Source social icon padding"),Slot->GetPadding(),FMargin(16.0f,0.0f,16.0f,0.0f));
        else AddError(TEXT("Source social icon lacks horizontal slot"));
    }
    UTexture2D* TwitterIcon=LoadObject<UTexture2D>(nullptr,TEXT("/Game/Recovery/Resources/UI/SocialIcons/twittericon.twittericon"));
    if (TestNotNull(TEXT("Recovered Twitter social artwork"),TwitterIcon)) {
        auto* Twitter=Cast<URecoveredUnlockStoreSocialIconWidget>(SocialBox->GetChildAt(0));
        auto* TwitterButton=Twitter ? Cast<UButton>(Twitter->GetWidgetFromName(TEXT("SocialButton"))) : nullptr;
        if (TestNotNull(TEXT("Source Twitter social button"),TwitterButton)) TestEqual(TEXT("Source Twitter social artwork assigned"),TwitterButton->GetStyle().Normal.GetResourceObject(),static_cast<UObject*>(TwitterIcon));
    }

    for (int32 BatchAttempt=0;BatchAttempt<Store->AvailablePacks.Num() && Store->GetCreatedPackEntryCount()<Store->AvailablePacks.Num();++BatchAttempt) Store->CreatePackBatch();
    TestEqual(TEXT("Store completes source batch population"),Store->GetCreatedPackEntryCount(),14);
    TestEqual(TEXT("Store completes source grid population"),PackGrid->GetChildrenCount(),14);
    const TArray<FString> ExpectedPackOrder={
        TEXT("Anal_Vol._1"),TEXT("Base_Game_CG"),TEXT("Cum_Covered_Succubi_Vol._1"),TEXT("Elves_Vol._1"),
        TEXT("Footjobs_Vol._1"),TEXT("Leggings_Remake"),TEXT("Remedy_Vol._1"),TEXT("Shopkeeper_Vol._1"),
        TEXT("Skunk_Vol._1"),TEXT("Upskirts_Remake"),TEXT("Vaelith_Vol._1"),TEXT("Vera_Vol._1"),
        TEXT("Vera_Vol._2"),TEXT("Winter_Wonderland_Vol._1")
    };
    for (int32 Index=0;Index<ExpectedPackOrder.Num();++Index) {
        auto* Entry=Cast<URecoveredPackEntryWidget>(PackGrid->GetChildAt(Index));
        if (!TestNotNull(*FString::Printf(TEXT("Source pack entry %d"),Index),Entry)) continue;
        TestEqual(TEXT("Source pack-entry class"),Entry->GetClass(),EntryClass);
        TestEqual(TEXT("Source pack order"),Entry->PackID,ExpectedPackOrder[Index]);
        auto* Slot=Cast<UUniformGridSlot>(Entry->Slot);
        if (TestNotNull(TEXT("Source pack grid slot"),Slot)) {
            TestEqual(TEXT("Source pack grid row"),Slot->GetRow(),Index/4);
            TestEqual(TEXT("Source pack grid column"),Slot->GetColumn(),Index%4);
        }
    }
    auto* BaseEntry=FindPackEntry(PackGrid,TEXT("Base_Game_CG"));
    auto* RemedyEntry=FindPackEntry(PackGrid,TEXT("Remedy_Vol._1"));
    if (!TestNotNull(TEXT("Source base pack entry"),BaseEntry) || !TestNotNull(TEXT("Source patron pack entry"),RemedyEntry)) return false;
    auto* BaseButton=Cast<UButton>(BaseEntry->GetWidgetFromName(TEXT("Button")));
    auto* BaseLock=Cast<UImage>(BaseEntry->GetWidgetFromName(TEXT("LockIcon")));
    auto* RemedyLock=Cast<UImage>(RemedyEntry->GetWidgetFromName(TEXT("LockIcon")));
    auto* RemedyPatreonLock=Cast<UImage>(RemedyEntry->GetWidgetFromName(TEXT("PatreonLockIcon")));
    if (!TestNotNull(TEXT("Source base pack button"),BaseButton)
        || !TestNotNull(TEXT("Source base lock icon"),BaseLock)
        || !TestNotNull(TEXT("Source patron normal lock icon"),RemedyLock)
        || !TestNotNull(TEXT("Source patron lock icon"),RemedyPatreonLock)) return false;
    TestTrue(TEXT("Source pack click binding"),BaseButton->OnClicked.IsBound());
    TestTrue(TEXT("Source pack hover binding"),BaseButton->OnHovered.IsBound());
    TestTrue(TEXT("Source pack unhover binding"),BaseButton->OnUnhovered.IsBound());
    TestEqual(TEXT("Unlocked source normal lock collapses"),BaseEntry->GetLockIconVisibility(),ESlateVisibility::Collapsed);
    TestEqual(TEXT("Unlocked source normal lock widget collapses"),BaseLock->GetVisibility(),ESlateVisibility::Collapsed);
    TestEqual(TEXT("Locked patron source normal lock collapses"),RemedyEntry->GetLockIconVisibility(),ESlateVisibility::Collapsed);
    TestEqual(TEXT("Locked patron source Patreon lock shows"),RemedyEntry->GetPatreonLockIconVisibility(),ESlateVisibility::Visible);
    TestEqual(TEXT("Locked patron source normal lock widget collapses"),RemedyLock->GetVisibility(),ESlateVisibility::Collapsed);
    TestEqual(TEXT("Locked patron source Patreon lock widget shows"),RemedyPatreonLock->GetVisibility(),ESlateVisibility::Visible);

    Store->OnEntryClicked(TEXT("Anal_Vol._1"));
    TestEqual(TEXT("Source challenge-gated pack label"),Store->GetInteractionLabel(),FString(TEXT("Unlock Via Challenge:\r\n\"Cock Hero\"")));
    InteractionButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source challenge-gated interaction action"),Store->LastStoreAction,FString(TEXT("Challenge reward required")));
    TestFalse(TEXT("Source challenge-gated pack remains locked"),Store->IsPackUnlocked(TEXT("Anal_Vol._1")));

    Store->OnEntryClicked(TEXT("Remedy_Vol._1"));
    TestEqual(TEXT("Source non-patron label"),Store->GetInteractionLabel(),FString(TEXT("Become a Patron")));
    TestFalse(TEXT("Source patron-only pack remains locked without patron access"),Store->IsPackUnlocked(TEXT("Remedy_Vol._1")));
    TestTrue(TEXT("Source patron setting persists"),Save->SetBoolSetting(TEXT("IsPatron?"),true));
    TestTrue(TEXT("Source unlock points test balance persists"),Save->SetNumberSetting(TEXT("UnlockPoints"),20));
    Store->ClearAndRefreshPacks();
    TestEqual(TEXT("Source refresh recreates every pack synchronously"),Store->GetCreatedPackEntryCount(),14);
    TestEqual(TEXT("Source refresh recreates every source grid slot"),PackGrid->GetChildrenCount(),14);
    TestEqual(TEXT("Source refresh preserves current pack selection"),Store->SelectedPackInfo.PackID,FString(TEXT("Remedy_Vol._1")));
    Store->OnEntryClicked(TEXT("Remedy_Vol._1"));
    TestEqual(TEXT("Source patron unlock label"),Store->GetInteractionLabel(),FString(TEXT("Unlock: (16 UP)")));
    InteractionButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source patron unlock action"),Store->LastStoreAction,FString(TEXT("Pack unlocked")));
    TestTrue(TEXT("Source patron pack unlocks"),Store->IsPackUnlocked(TEXT("Remedy_Vol._1")));
    TestTrue(TEXT("Source patron pack enables on unlock"),Store->IsPackEnabled(TEXT("Remedy_Vol._1")));
    TestEqual(TEXT("Source patron unlock point deduction"),Store->GetUnlockPoints(),4);
    TestEqual(TEXT("Source post-unlock label"),Store->GetInteractionLabel(),FString(TEXT("Pack Enabled")));
    TestTrue(TEXT("Source patron unlock persists"),ContainsPack(Save->GetStringArraySetting(TEXT("UnlockedPacks")),TEXT("Remedy_Vol._1")));
    TestTrue(TEXT("Source patron enable persists"),ContainsPack(Save->GetStringArraySetting(TEXT("EnabledPacks")),TEXT("Remedy_Vol._1")));
    TestTrue(TEXT("Source patron unlock save writes to isolated slot"),UGameplayStatics::DoesSaveGameExist(TestSlot,0));
    TestEqual(TEXT("Source purchase refresh rebuilds the full grid"),Store->GetCreatedPackEntryCount(),14);
    TestEqual(TEXT("Source purchase refresh preserves patron pack selection"),Store->SelectedPackInfo.PackID,FString(TEXT("Remedy_Vol._1")));

    DisableButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source disable-all action"),Store->LastStoreAction,FString(TEXT("All unlocked packs disabled")));
    TestFalse(TEXT("Source disable-all disables base"),Store->IsPackEnabled(TEXT("Base_Game_CG")));
    TestFalse(TEXT("Source disable-all disables purchased pack"),Store->IsPackEnabled(TEXT("Remedy_Vol._1")));
    EnableButton->OnClicked.Broadcast();
    TestEqual(TEXT("Source enable-all action"),Store->LastStoreAction,FString(TEXT("All unlocked packs enabled")));
    TestTrue(TEXT("Source enable-all enables base"),Store->IsPackEnabled(TEXT("Base_Game_CG")));
    TestTrue(TEXT("Source enable-all enables purchased pack"),Store->IsPackEnabled(TEXT("Remedy_Vol._1")));
    TestEqual(TEXT("Source unlock-point text"),UnlockPoints->GetText().ToString(),FString(TEXT("UP: 4")));
    return true;
}
#endif
