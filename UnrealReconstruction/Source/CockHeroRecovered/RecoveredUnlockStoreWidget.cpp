#include "RecoveredUnlockStoreWidget.h"

#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/VerticalBox.h"
#include "Dom/JsonObject.h"
#include "Engine/Texture2D.h"
#include "HAL/PlatformProcess.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "RecoveredRules.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Sound/SoundBase.h"
#include "TimerManager.h"

namespace {

constexpr TCHAR StoreCatalogRelativePath[] = TEXT("Recovery/Definitions/pack-store-catalog.json");
constexpr TCHAR StoreEvidenceCatalogRelativePath[] = TEXT("RecoveryEvidence/pack-store-catalog.json");
constexpr TCHAR EntryClassPath[] = TEXT("/Game/Recovery/UI/CHPackEntryWidget.CHPackEntryWidget_C");
constexpr TCHAR SocialIconClassPath[] = TEXT("/Game/Recovery/UI/UnlockStoreSocialIconBaseButton.UnlockStoreSocialIconBaseButton_C");
constexpr TCHAR TooltipClassPath[] = TEXT("/Game/Recovery/UI/CustomToolTip_Widget.CustomToolTip_Widget_C");
constexpr TCHAR EntryClickSoundPath[] = TEXT("/Game/Recovery/Resources/Audio/click5_sfx.click5_sfx");
constexpr TCHAR EntryHoverSoundPath[] = TEXT("/Game/Recovery/Resources/Audio/click4_sfx.click4_sfx");
constexpr TCHAR StoreFailureSoundPath[] = TEXT("/Game/Recovery/Resources/Audio/anime-46068.anime-46068");
constexpr TCHAR StoreSuccessSoundPath[] = TEXT("/Game/Recovery/Resources/Audio/Juice_SFX__12_.Juice_SFX__12_");
constexpr TCHAR PatreonURL[] = TEXT("https://www.patreon.com/CockHeroGame");
constexpr TCHAR UnlockPointsKey[] = TEXT("UnlockPoints");
constexpr TCHAR UnlockedPacksKey[] = TEXT("UnlockedPacks");
constexpr TCHAR EnabledPacksKey[] = TEXT("EnabledPacks");
constexpr TCHAR PatronKey[] = TEXT("IsPatron?");
constexpr TCHAR BasePackID[] = TEXT("Base_Game_CG");
constexpr double DoubleClickWindowSeconds = 0.25;
constexpr int32 GridColumns = 4;

bool EquivalentPackID(const FString& Left,const FString& Right) {
    return Left.Equals(Right,ESearchCase::IgnoreCase);
}

int32 FindSavedPackIndex(const TArray<FString>& Values,const FString& PackID) {
    return Values.IndexOfByPredicate([&PackID](const FString& Value) { return EquivalentPackID(Value,PackID); });
}

bool SavedPackContains(const TArray<FString>& Values,const FString& PackID) {
    return FindSavedPackIndex(Values,PackID) != INDEX_NONE;
}

FString DisplayPackID(const FString& PackID) {
    return PackID.Replace(TEXT("_"),TEXT(" "));
}

bool ReadString(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,FString& Out) {
    return Object.IsValid() && Object->TryGetStringField(Name,Out);
}

bool ReadInteger(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,int32& Out) {
    if (!Object.IsValid() || !Object->HasTypedField<EJson::Number>(Name)) return false;
    Out=static_cast<int32>(Object->GetNumberField(Name));
    return true;
}

bool ReadBoolean(const TSharedPtr<FJsonObject>& Object,const TCHAR* Name,bool& Out) {
    return Object.IsValid() && Object->TryGetBoolField(Name,Out);
}

bool ReadSocialLinks(const TSharedPtr<FJsonObject>& Object,FRecoveredPackSocialLinks& Out) {
    const TSharedPtr<FJsonObject>* Links=nullptr;
    if (!Object.IsValid() || !Object->TryGetObjectField(TEXT("social_links"),Links) || !Links || !Links->IsValid()) return false;
    return ReadString(*Links,TEXT("onlyfans"),Out.OnlyFans)
        && ReadString(*Links,TEXT("fansly"),Out.Fansly)
        && ReadString(*Links,TEXT("twitter"),Out.Twitter)
        && ReadString(*Links,TEXT("linktree"),Out.Linktree)
        && ReadString(*Links,TEXT("manyvids"),Out.ManyVids)
        && ReadString(*Links,TEXT("redgifs"),Out.Redgifs)
        && ReadString(*Links,TEXT("discord"),Out.Discord)
        && ReadString(*Links,TEXT("patreon"),Out.Patreon)
        && ReadString(*Links,TEXT("subscribestar"),Out.SubscribeStar)
        && ReadString(*Links,TEXT("kofi"),Out.Kofi);
}

const TCHAR* SocialIconResourcePath(uint8 Platform) {
    switch (Platform) {
    case 0: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/onlyfansicon.onlyfansicon");
    case 1: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/fanlsyicon.fanlsyicon");
    case 2: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/twittericon.twittericon");
    case 3: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/linktreeicon.linktreeicon");
    case 4: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/manyvidsicon.manyvidsicon");
    case 5: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/redgifsicon.redgifsicon");
    case 6: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/discordicon.discordicon");
    case 7: return TEXT("/Game/Recovery/Resources/UI/SocialIcons/patreonicon.patreonicon");
    case 8: return TEXT("/Game/Recovery/Resources/UI/Materials/SubscribeStarLogo.SubscribeStarLogo");
    case 9: return TEXT("/Game/Recovery/Resources/UI/Materials/KofiLogo.KofiLogo");
    default: return nullptr;
    }
}

FSlateBrush MakeSocialIconBrush(UObject* Resource,const FLinearColor& Tint) {
    FSlateBrush Brush;
    Brush.DrawAs=ESlateBrushDrawType::Image;
    Brush.ImageSize=FVector2D(32.0f,32.0f);
    Brush.TintColor=FSlateColor(Tint);
    Brush.SetResourceObject(Resource);
    return Brush;
}

double GetStoreTime(const UUserWidget* Widget) {
    return Widget && Widget->GetWorld()
        ? static_cast<double>(UGameplayStatics::GetTimeSeconds(Widget))
        : FPlatformTime::Seconds();
}

}

void URecoveredPackEntryWidget::ConfigureEntry(
    const FString& InPackID,
    UTexture2D* InPreviewTexture,
    bool bInUnlocked,
    bool bInPatreonExclusive,
    bool bInPatron,
    bool bInEnabled) {
    PackID=InPackID;
    PreviewTexture=InPreviewTexture;
    // Cooked source assigns PackInfo.bUnlocked into the field called bIsLocked.
    bIsLocked=bInUnlocked;
    bIsPatreonExclusive=bInPatreonExclusive;
    bIsPatron=bInPatron;
    bPackEnabled=bInEnabled;
    ApplyPresentation();
}

ESlateVisibility URecoveredPackEntryWidget::GetLockIconVisibility() const {
    if (bIsLocked) return ESlateVisibility::Collapsed;
    return bIsPatreonExclusive && !bIsPatron ? ESlateVisibility::Collapsed : ESlateVisibility::Visible;
}

ESlateVisibility URecoveredPackEntryWidget::GetPatreonLockIconVisibility() const {
    return !bIsLocked && bIsPatreonExclusive && !bIsPatron ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
}

void URecoveredPackEntryWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindSourceEvents(true);
    ApplyPresentation();
}

void URecoveredPackEntryWidget::NativeDestruct() {
    BindSourceEvents(false);
    EntryTooltip=nullptr;
    Super::NativeDestruct();
}

void URecoveredPackEntryWidget::BindSourceTree() {
    if (!SourceButton) SourceButton=Cast<UButton>(GetWidgetFromName(TEXT("Button")));
    if (!SourceLockIcon) SourceLockIcon=Cast<UImage>(GetWidgetFromName(TEXT("LockIcon")));
    if (!SourcePatreonLockIcon) SourcePatreonLockIcon=Cast<UImage>(GetWidgetFromName(TEXT("PatreonLockIcon")));
    if (!SourcePreviewImage) SourcePreviewImage=Cast<UImage>(GetWidgetFromName(TEXT("PreviewImage")));
}

void URecoveredPackEntryWidget::BindSourceEvents(bool bBind) {
    BindSourceTree();
    if (!SourceButton) return;
    if (bBind) {
        SourceButton->OnClicked.AddUniqueDynamic(this,&URecoveredPackEntryWidget::HandleClicked);
        SourceButton->OnHovered.AddUniqueDynamic(this,&URecoveredPackEntryWidget::HandleHovered);
        SourceButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredPackEntryWidget::HandleUnhovered);
    } else {
        SourceButton->OnClicked.RemoveDynamic(this,&URecoveredPackEntryWidget::HandleClicked);
        SourceButton->OnHovered.RemoveDynamic(this,&URecoveredPackEntryWidget::HandleHovered);
        SourceButton->OnUnhovered.RemoveDynamic(this,&URecoveredPackEntryWidget::HandleUnhovered);
    }
}

void URecoveredPackEntryWidget::ApplyTooltip() {
    if (!SourceButton || !GetWorld()) return;
    UClass* TooltipClass=LoadClass<URecoveredTooltip>(nullptr,TooltipClassPath);
    if (!TooltipClass) return;
    if (!EntryTooltip || !EntryTooltip->IsA(TooltipClass)) EntryTooltip=CreateWidget<URecoveredTooltip>(GetWorld(),TooltipClass);
    if (!EntryTooltip) return;
    EntryTooltip->SetTitleAndDescription(
        FText::FromString(DisplayPackID(PackID)),
        FText::FromString(bIsLocked ? TEXT("Unlocked") : TEXT("Locked")));
    SourceButton->SetToolTip(EntryTooltip);
}

void URecoveredPackEntryWidget::ApplyPresentation() {
    BindSourceTree();
    if (SourcePreviewImage) SourcePreviewImage->SetBrushFromTexture(PreviewTexture,false);
    if (SourceLockIcon) SourceLockIcon->SetVisibility(GetLockIconVisibility());
    if (SourcePatreonLockIcon) SourcePatreonLockIcon->SetVisibility(GetPatreonLockIconVisibility());
    if (SourceButton) {
        // Exact source entry-state colors from the pack batching graph.
        SourceButton->SetBackgroundColor(
            bIsLocked && bPackEnabled
                ? FLinearColor(0.018919000402092934f,1.0f,0.0f,1.0f)
                : FLinearColor(1.0f,0.0f,0.009282000362873077f,1.0f));
    }
    ApplyTooltip();
}

void URecoveredPackEntryWidget::PlaySourceSound(const TCHAR* AssetPath,float Volume,float Pitch) const {
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,AssetPath)) {
        if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,Volume,Pitch,0.0f,nullptr,nullptr,true);
    }
}

void URecoveredPackEntryWidget::HandleClicked() {
    PlaySourceSound(EntryClickSoundPath);
    PlayRecoveredAnimation(TEXT("Click"));
    OnPackClicked.Broadcast(PackID);
}

void URecoveredPackEntryWidget::HandleHovered() {
    PlayRecoveredAnimation(TEXT("OnHoverAnim"));
    PlaySourceSound(EntryHoverSoundPath);
    OnPackHovered.Broadcast(PackID);
}

void URecoveredPackEntryWidget::HandleUnhovered() {
    PlayRecoveredAnimation(TEXT("OnUnHoverAnim"));
    OnPackUnhovered.Broadcast();
}

void URecoveredUnlockStoreSocialIconWidget::SetURLAndIcon(const FString& InURL,uint8 InPlatform) {
    ButtonURL=InURL;
    Platform=InPlatform;
    ApplySourceStyle();
    ApplyTooltip();
}

void URecoveredUnlockStoreSocialIconWidget::NativeConstruct() {
    Super::NativeConstruct();
    BindSourceEvents(true);
    ApplySourceStyle();
    ApplyTooltip();
}

void URecoveredUnlockStoreSocialIconWidget::NativeDestruct() {
    BindSourceEvents(false);
    SocialTooltip=nullptr;
    Super::NativeDestruct();
}

void URecoveredUnlockStoreSocialIconWidget::BindSourceTree() {
    if (!SourceSocialButton) SourceSocialButton=Cast<UButton>(GetWidgetFromName(TEXT("SocialButton")));
}

void URecoveredUnlockStoreSocialIconWidget::BindSourceEvents(bool bBind) {
    BindSourceTree();
    if (!SourceSocialButton) return;
    if (bBind) {
        SourceSocialButton->OnClicked.AddUniqueDynamic(this,&URecoveredUnlockStoreSocialIconWidget::HandleClicked);
        SourceSocialButton->OnHovered.AddUniqueDynamic(this,&URecoveredUnlockStoreSocialIconWidget::HandleHovered);
        SourceSocialButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredUnlockStoreSocialIconWidget::HandleUnhovered);
    } else {
        SourceSocialButton->OnClicked.RemoveDynamic(this,&URecoveredUnlockStoreSocialIconWidget::HandleClicked);
        SourceSocialButton->OnHovered.RemoveDynamic(this,&URecoveredUnlockStoreSocialIconWidget::HandleHovered);
        SourceSocialButton->OnUnhovered.RemoveDynamic(this,&URecoveredUnlockStoreSocialIconWidget::HandleUnhovered);
    }
}

void URecoveredUnlockStoreSocialIconWidget::ApplySourceStyle() {
    BindSourceTree();
    if (!SourceSocialButton) return;
    UObject* Resource=nullptr;
    if (const TCHAR* Path=SocialIconResourcePath(Platform)) Resource=StaticLoadObject(UObject::StaticClass(),nullptr,Path);
    FButtonStyle Style;
    Style.Normal=MakeSocialIconBrush(Resource,FLinearColor::White);
    Style.Hovered=MakeSocialIconBrush(Resource,FLinearColor(0.7230550050735474f,0.7230550050735474f,0.7230550050735474f,1.0f));
    Style.Pressed=MakeSocialIconBrush(Resource,FLinearColor(0.3864299952983856f,0.3864299952983856f,0.3864299952983856f,1.0f));
    Style.Disabled=FSlateNoResource();
    Style.NormalForeground=FSlateColor::UseForeground();
    Style.HoveredForeground=FSlateColor::UseForeground();
    Style.PressedForeground=FSlateColor::UseForeground();
    Style.DisabledForeground=FSlateColor::UseForeground();
    Style.NormalPadding=FMargin(0.0f);
    Style.PressedPadding=FMargin(0.0f);
    SourceSocialButton->SetStyle(Style);
}

void URecoveredUnlockStoreSocialIconWidget::ApplyTooltip() {
    BindSourceTree();
    if (!SourceSocialButton || !GetWorld()) return;
    UClass* TooltipClass=LoadClass<URecoveredTooltip>(nullptr,TooltipClassPath);
    if (!TooltipClass) return;
    if (!SocialTooltip || !SocialTooltip->IsA(TooltipClass)) SocialTooltip=CreateWidget<URecoveredTooltip>(GetWorld(),TooltipClass);
    if (!SocialTooltip) return;
    SocialTooltip->SetTitleAndDescription(FText::FromString(TEXT("Creator Link")),FText::FromString(ButtonURL));
    SourceSocialButton->SetToolTip(SocialTooltip);
}

void URecoveredUnlockStoreSocialIconWidget::HandleClicked() {
    if (!ButtonURL.IsEmpty()) FPlatformProcess::LaunchURL(*ButtonURL,nullptr,nullptr);
}

void URecoveredUnlockStoreSocialIconWidget::HandleHovered() {
    PlayRecoveredAnimation(TEXT("HoverSocial"));
}

void URecoveredUnlockStoreSocialIconWidget::HandleUnhovered() {
    PlayRecoveredAnimation(TEXT("UnHoverSocial"));
}

void URecoveredUnlockStoreWidget::NativeConstruct() {
    Super::NativeConstruct();
    IsInit=true;
    BindSourceEvents(true);
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        Instance->PlayRecoveredBackgroundMedia(TEXT("backgroundmenuloop"),SourceBackgroundImage);
    }
    if (!LoadRecoveredPackCatalog()) return;
    if (SourceEnableDisablePacksBox) SourceEnableDisablePacksBox->SetVisibility(IsPatron() ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    CurrentPackIndex=0;
    OnEntryClicked(BasePackID);
    UpdateButtonDisplay(BasePackID,false);
    UpdateInfoPanel(BasePackID);
    StartPackBatchTimer();
}

void URecoveredUnlockStoreWidget::NativeDestruct() {
    StopPackBatchTimer();
    BindSourceEvents(false);
    for (URecoveredPackEntryWidget* Entry:PackEntries) {
        if (!Entry) continue;
        Entry->OnPackClicked.RemoveDynamic(this,&URecoveredUnlockStoreWidget::OnEntryClicked);
        Entry->OnPackHovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::OnEntryHovered);
        Entry->OnPackUnhovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::OnEntryUnhovered);
    }
    PackEntries.Reset();
    SocialIconEntries.Reset();
    Super::NativeDestruct();
}

void URecoveredUnlockStoreWidget::BindSourceTree() {
    if (!SourceBackButton) SourceBackButton=Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
    if (!SourceEnablePacksButton) SourceEnablePacksButton=Cast<UButton>(GetWidgetFromName(TEXT("EnablePacksButton")));
    if (!SourceDisablePacksButton) SourceDisablePacksButton=Cast<UButton>(GetWidgetFromName(TEXT("DisablePacksButton_1")));
    if (!SourceInteractionButton) SourceInteractionButton=Cast<UButton>(GetWidgetFromName(TEXT("InteractionButton")));
    if (!SourcePackUniformGrid) SourcePackUniformGrid=Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("PackUniformGrid")));
    if (!SourceEnableDisablePacksBox) SourceEnableDisablePacksBox=Cast<UVerticalBox>(GetWidgetFromName(TEXT("EnableDisablePacksButton")));
    if (!SourceSocialIconsHoriBox) SourceSocialIconsHoriBox=Cast<UHorizontalBox>(GetWidgetFromName(TEXT("SocialIconsHoriBox")));
    if (!SourceBackgroundImage) SourceBackgroundImage=Cast<UImage>(GetWidgetFromName(TEXT("BackgroundImage")));
    if (!SourceImagePreview) SourceImagePreview=Cast<UImage>(GetWidgetFromName(TEXT("ImagePreview")));
    if (!SourcePackNameText) SourcePackNameText=Cast<UTextBlock>(GetWidgetFromName(TEXT("PackNameText")));
    if (!SourceAuthorNameText) SourceAuthorNameText=Cast<UTextBlock>(GetWidgetFromName(TEXT("AuthorNameText")));
    if (!SourceDescriptionText) SourceDescriptionText=Cast<UTextBlock>(GetWidgetFromName(TEXT("DescriptionText")));
    if (!SourceTotalCardsText) SourceTotalCardsText=Cast<UTextBlock>(GetWidgetFromName(TEXT("TotalCardsText")));
    if (!SourceInteractionButtonTextBlock) SourceInteractionButtonTextBlock=Cast<UTextBlock>(GetWidgetFromName(TEXT("InteractionButtonTextBlock")));
    if (!UnlockPointsText) UnlockPointsText=Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_393")));
}

void URecoveredUnlockStoreWidget::BindSourceEvents(bool bBind) {
    BindSourceTree();
#define BIND_UNLOCK_STORE(Button,Method) \
    if (Button) { \
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::Method); \
        else Button->OnClicked.RemoveDynamic(this,&URecoveredUnlockStoreWidget::Method); \
    }
    BIND_UNLOCK_STORE(SourceBackButton,HandleBackClicked)
    BIND_UNLOCK_STORE(SourceEnablePacksButton,EnableAllPacks)
    BIND_UNLOCK_STORE(SourceDisablePacksButton,DisableAllPacks)
    BIND_UNLOCK_STORE(SourceInteractionButton,HandleInteractionClicked)
#undef BIND_UNLOCK_STORE
    if (SourceBackButton) {
        if (bBind) {
            SourceBackButton->OnHovered.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::HandleBackHovered);
            SourceBackButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::HandleBackUnhovered);
        } else {
            SourceBackButton->OnHovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::HandleBackHovered);
            SourceBackButton->OnUnhovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::HandleBackUnhovered);
        }
    }
    if (SourceInteractionButton) {
        if (bBind) {
            SourceInteractionButton->OnHovered.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::HandleInteractionHovered);
            SourceInteractionButton->OnUnhovered.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::HandleInteractionUnhovered);
        } else {
            SourceInteractionButton->OnHovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::HandleInteractionHovered);
            SourceInteractionButton->OnUnhovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::HandleInteractionUnhovered);
        }
    }
}

bool URecoveredUnlockStoreWidget::LoadRecoveredPackCatalog() {
    FString Json;
    const FString ContentCatalog=FPaths::ProjectContentDir()/StoreCatalogRelativePath;
    const FString EvidenceCatalog=FPaths::ProjectDir()/StoreEvidenceCatalogRelativePath;
    if (!FFileHelper::LoadFileToString(Json,*ContentCatalog) && !FFileHelper::LoadFileToString(Json,*EvidenceCatalog)) {
        LastStoreAction=TEXT("Pack catalog unavailable");
        return false;
    }
    TSharedPtr<FJsonObject> Root;
    if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Json),Root) || !Root.IsValid()) {
        LastStoreAction=TEXT("Pack catalog invalid");
        return false;
    }
    const TArray<TSharedPtr<FJsonValue>>* Records=nullptr;
    if (!Root->TryGetArrayField(TEXT("packs"),Records) || !Records || Records->Num()!=14) {
        LastStoreAction=TEXT("Pack catalog incomplete");
        return false;
    }
    TArray<FRecoveredPackInfo> Parsed;
    Parsed.Reserve(Records->Num());
    for (const TSharedPtr<FJsonValue>& Value:*Records) {
        const TSharedPtr<FJsonObject> Record=Value.IsValid() ? Value->AsObject() : nullptr;
        FRecoveredPackInfo Pack;
        if (!ReadString(Record,TEXT("pack_id"),Pack.PackID)
            || !ReadString(Record,TEXT("name"),Pack.DisplayName)
            || !ReadString(Record,TEXT("author"),Pack.Author)
            || !ReadString(Record,TEXT("description"),Pack.Description)
            || !ReadString(Record,TEXT("asset_path"),Pack.PreviewAssetPath)
            || !ReadInteger(Record,TEXT("unlock_cost"),Pack.UnlockCost)
            || !ReadInteger(Record,TEXT("total_media_count"),Pack.TotalMediaCount)
            || !ReadBoolean(Record,TEXT("patreon_exclusive"),Pack.bPatreonExclusive)
            || !ReadSocialLinks(Record,Pack.SocialLinks)) {
            LastStoreAction=TEXT("Pack catalog record invalid");
            return false;
        }
        ReadString(Record,TEXT("challenge_name"),Pack.ChallengeName);
        ReadInteger(Record,TEXT("image_count"),Pack.ImageCount);
        ReadInteger(Record,TEXT("video_count"),Pack.VideoCount);
        Parsed.Add(MoveTemp(Pack));
    }
    if (!Parsed.ContainsByPredicate([](const FRecoveredPackInfo& Pack) { return Pack.PackID==BasePackID; })) {
        LastStoreAction=TEXT("Base pack absent from catalog");
        return false;
    }
    AvailablePacks=MoveTemp(Parsed);
    ApplyEntryStates();
    LastStoreAction=TEXT("Pack catalog loaded");
    return true;
}

void URecoveredUnlockStoreWidget::ApplyEntryStates() {
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    const URecoveredSaveGame* Save=Instance ? Instance->CurrentSave.Get() : nullptr;
    const TArray<FString> Unlocked=Save && Save->HasSetting(UnlockedPacksKey) ? Save->GetStringArraySetting(UnlockedPacksKey) : TArray<FString>{BasePackID};
    const TArray<FString> Enabled=Save && Save->HasSetting(EnabledPacksKey) ? Save->GetStringArraySetting(EnabledPacksKey) : TArray<FString>{BasePackID};
    for (FRecoveredPackInfo& Pack:AvailablePacks) {
        Pack.bUnlocked=SavedPackContains(Unlocked,Pack.PackID);
        Pack.bEnabled=Pack.bUnlocked && SavedPackContains(Enabled,Pack.PackID);
    }
}

const FRecoveredPackInfo* URecoveredUnlockStoreWidget::FindPack(const FString& PackID) const {
    return AvailablePacks.FindByPredicate([&PackID](const FRecoveredPackInfo& Pack) { return EquivalentPackID(Pack.PackID,PackID); });
}

FRecoveredPackInfo* URecoveredUnlockStoreWidget::FindMutablePack(const FString& PackID) {
    return AvailablePacks.FindByPredicate([&PackID](const FRecoveredPackInfo& Pack) { return EquivalentPackID(Pack.PackID,PackID); });
}

bool URecoveredUnlockStoreWidget::IsPatron() const {
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    return Instance && Instance->CurrentSave && Instance->CurrentSave->GetBoolSetting(PatronKey);
}

bool URecoveredUnlockStoreWidget::IsChallengeReward(const FRecoveredPackInfo& Pack) const {
    return !Pack.ChallengeName.IsEmpty();
}

bool URecoveredUnlockStoreWidget::IsPackUnlocked(const FString& PackID) const {
    if (const FRecoveredPackInfo* Pack=FindPack(PackID)) return Pack->bUnlocked;
    return false;
}

bool URecoveredUnlockStoreWidget::IsPackEnabled(const FString& PackID) const {
    if (const FRecoveredPackInfo* Pack=FindPack(PackID)) return Pack->bUnlocked && Pack->bEnabled;
    return false;
}

int32 URecoveredUnlockStoreWidget::GetUnlockPoints() const {
    const auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    return Instance && Instance->CurrentSave
        ? FMath::Max(0,static_cast<int32>(Instance->CurrentSave->GetNumberSetting(UnlockPointsKey,5)))
        : 5;
}

void URecoveredUnlockStoreWidget::SetUnlockPoints(int32 Points) {
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) Instance->CurrentSave->SetNumberSetting(UnlockPointsKey,FMath::Max(0,Points));
    }
    UpdateUnlockPointsText();
}

void URecoveredUnlockStoreWidget::PersistStoreState() {
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) {
        if (Instance->CurrentSave) Instance->SaveRecoveredState();
    }
}

bool URecoveredUnlockStoreWidget::SetPackUnlocked(const FString& PackID,bool bUnlocked) {
    FRecoveredPackInfo* Pack=FindMutablePack(PackID);
    if (!Pack) return false;
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) {
        Pack->bUnlocked=bUnlocked;
        if (!bUnlocked) Pack->bEnabled=false;
        return true;
    }
    TArray<FString> Unlocked=Instance->CurrentSave->GetStringArraySetting(UnlockedPacksKey);
    const int32 Index=FindSavedPackIndex(Unlocked,Pack->PackID);
    if (bUnlocked && Index==INDEX_NONE) Unlocked.Add(Pack->PackID);
    if (!bUnlocked && Index!=INDEX_NONE) Unlocked.RemoveAt(Index);
    const bool bSaved=Instance->CurrentSave->SetStringArraySetting(UnlockedPacksKey,Unlocked);
    Pack->bUnlocked=bUnlocked;
    if (!bUnlocked) SetPackEnabled(Pack->PackID,false);
    return bSaved;
}

bool URecoveredUnlockStoreWidget::SetPackEnabled(const FString& PackID,bool bEnabled) {
    FRecoveredPackInfo* Pack=FindMutablePack(PackID);
    if (!Pack || (!Pack->bUnlocked && bEnabled)) return false;
    auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave) {
        TArray<FString> Enabled=Instance->CurrentSave->GetStringArraySetting(EnabledPacksKey);
        const int32 Index=FindSavedPackIndex(Enabled,Pack->PackID);
        if (bEnabled && Index==INDEX_NONE) Enabled.Add(Pack->PackID);
        if (!bEnabled && Index!=INDEX_NONE) Enabled.RemoveAt(Index);
        Instance->CurrentSave->SetStringArraySetting(EnabledPacksKey,Enabled);
    }
    Pack->bEnabled=bEnabled;
    if (auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr) {
        Manager->SetMediaPackEnabled(Pack->PackID,bEnabled);
    }
    return true;
}

void URecoveredUnlockStoreWidget::UpdateUnlockPointsText() {
    BindSourceTree();
    if (UnlockPointsText) UnlockPointsText->SetText(FText::FromString(FString::Printf(TEXT("UP: %d"),GetUnlockPoints())));
}

bool URecoveredUnlockStoreWidget::SelectPack(const FString& PackID) {
    if (const FRecoveredPackInfo* Pack=FindPack(PackID)) {
        SelectedPackInfo=*Pack;
        return true;
    }
    return false;
}

void URecoveredUnlockStoreWidget::ClearAndRefreshPacks() {
    IsInit=true;
    StopPackBatchTimer();
    if (!LoadRecoveredPackCatalog()) return;
    BindSourceTree();
    for (URecoveredPackEntryWidget* Entry:PackEntries) {
        if (!Entry) continue;
        Entry->OnPackClicked.RemoveDynamic(this,&URecoveredUnlockStoreWidget::OnEntryClicked);
        Entry->OnPackHovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::OnEntryHovered);
        Entry->OnPackUnhovered.RemoveDynamic(this,&URecoveredUnlockStoreWidget::OnEntryUnhovered);
    }
    PackEntries.Reset();
    if (SourcePackUniformGrid) SourcePackUniformGrid->ClearChildren();
    for (int32 Index=0;Index<AvailablePacks.Num();++Index) CreatePackEntry(AvailablePacks[Index],Index,false);
    IsInit=false;
}

void URecoveredUnlockStoreWidget::StartPackBatchTimer() {
    if (!GetWorld() || CurrentPackIndex>=AvailablePacks.Num()) {
        IsInit=false;
        return;
    }
    GetWorld()->GetTimerManager().SetTimer(PackBatchTimerHandle,this,&URecoveredUnlockStoreWidget::CreatePackBatch,0.016f,true);
}

void URecoveredUnlockStoreWidget::StopPackBatchTimer() {
    if (GetWorld()) GetWorld()->GetTimerManager().ClearTimer(PackBatchTimerHandle);
}

void URecoveredUnlockStoreWidget::CreatePackBatch() {
    BindSourceTree();
    if (SourcePackUniformGrid) SourcePackUniformGrid->SetSlotPadding(FMargin(4.0f));
    const int32 BatchEnd=FMath::Min(CurrentPackIndex+FMath::Max(1,PacksPerFrame),AvailablePacks.Num());
    for (;CurrentPackIndex<BatchEnd;++CurrentPackIndex) {
        CreatePackEntry(AvailablePacks[CurrentPackIndex],CurrentPackIndex,true);
    }
    if (CurrentPackIndex>=AvailablePacks.Num()) {
        StopPackBatchTimer();
        IsInit=false;
    }
}

void URecoveredUnlockStoreWidget::CreatePackEntry(const FRecoveredPackInfo& Pack,int32 GridIndex,bool bAssignAccessState) {
    UClass* EntryClass=LoadClass<URecoveredPackEntryWidget>(nullptr,EntryClassPath);
    URecoveredPackEntryWidget* Entry=EntryClass
        ? CreateWidget<URecoveredPackEntryWidget>(this,EntryClass)
        : CreateWidget<URecoveredPackEntryWidget>(this,URecoveredPackEntryWidget::StaticClass());
    if (!Entry) return;
    UTexture2D* Preview=LoadObject<UTexture2D>(nullptr,*Pack.PreviewAssetPath);
    Entry->ConfigureEntry(
        Pack.PackID,
        Preview,
        Pack.bUnlocked,
        bAssignAccessState ? Pack.bPatreonExclusive : false,
        bAssignAccessState ? IsPatron() : false,
        Pack.bEnabled);
    Entry->OnPackClicked.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::OnEntryClicked);
    Entry->OnPackHovered.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::OnEntryHovered);
    Entry->OnPackUnhovered.AddUniqueDynamic(this,&URecoveredUnlockStoreWidget::OnEntryUnhovered);
    if (SourcePackUniformGrid) SourcePackUniformGrid->AddChildToUniformGrid(Entry,GridIndex/GridColumns,GridIndex%GridColumns);
    PackEntries.Add(Entry);
}

void URecoveredUnlockStoreWidget::CreateSocialIcons(const FRecoveredPackSocialLinks& Links) {
    BindSourceTree();
    SocialIconEntries.Reset();
    if (!SourceSocialIconsHoriBox || !GetWorld()) return;
    SourceSocialIconsHoriBox->ClearChildren();
    UClass* EntryClass=LoadClass<URecoveredUnlockStoreSocialIconWidget>(nullptr,SocialIconClassPath);
    if (!EntryClass) return;
    const auto AddLink=[this,EntryClass](const FString& URL,uint8 Platform) {
        if (URL.IsEmpty() || SocialIconEntries.Num()>=4) return;
        URecoveredUnlockStoreSocialIconWidget* Entry=CreateWidget<URecoveredUnlockStoreSocialIconWidget>(this,EntryClass);
        if (!Entry) return;
        Entry->SetURLAndIcon(URL,Platform);
        if (UHorizontalBoxSlot* Slot=SourceSocialIconsHoriBox->AddChildToHorizontalBox(Entry)) Slot->SetPadding(FMargin(16.0f,0.0f,16.0f,0.0f));
        SocialIconEntries.Add(Entry);
    };
    AddLink(Links.Fansly,1);
    AddLink(Links.Twitter,2);
    AddLink(Links.Linktree,3);
    AddLink(Links.ManyVids,4);
    AddLink(Links.Redgifs,5);
    AddLink(Links.Discord,6);
    AddLink(Links.Patreon,7);
    AddLink(Links.SubscribeStar,8);
    AddLink(Links.Kofi,9);
    AddLink(Links.OnlyFans,0);
}

void URecoveredUnlockStoreWidget::UpdateInfoPanel(const FString& PackID) {
    const FRecoveredPackInfo* Pack=FindPack(PackID);
    if (!Pack) return;
    BindSourceTree();
    UTexture2D* Preview=LoadObject<UTexture2D>(nullptr,*Pack->PreviewAssetPath);
    if (SourcePackNameText) SourcePackNameText->SetText(FText::FromString(DisplayPackID(Pack->PackID)));
    if (SourceAuthorNameText) SourceAuthorNameText->SetText(FText::FromString(TEXT("Author: ")+Pack->Author));
    if (SourceDescriptionText) SourceDescriptionText->SetText(FText::FromString(Pack->Description));
    if (SourceImagePreview) SourceImagePreview->SetBrushFromTexture(Preview,false);
    CreateSocialIcons(Pack->SocialLinks);
    if (SourceTotalCardsText) SourceTotalCardsText->SetText(FText::FromString(FString::Printf(TEXT("Total Cards: %d"),Pack->TotalMediaCount)));
    PlayRecoveredAnimation(TEXT("OnUpdateInfo"));
    if (Pack->bPatreonExclusive && !IsPatron() && SourceInteractionButtonTextBlock) SourceInteractionButtonTextBlock->SetText(FText::FromString(TEXT("Become a Patron")));
}

void URecoveredUnlockStoreWidget::UpdateDetails(const FString& PackID) {
    SelectPack(PackID);
}

void URecoveredUnlockStoreWidget::UpdateButtonDisplay(const FString& PackID,bool bPatreonExclusive) {
    (void)bPatreonExclusive;
    const FRecoveredPackInfo* Pack=FindPack(PackID);
    if (!Pack) return;
    BindSourceTree();
    FString Label;
    if (!IsPatron() && Pack->bPatreonExclusive) Label=TEXT("Become a Patron");
    else if (Pack->bUnlocked) Label=Pack->bEnabled ? TEXT("Pack Enabled") : TEXT("Pack Disabled");
    else if (IsChallengeReward(*Pack)) Label=FString::Printf(TEXT("Unlock Via Challenge:\r\n\"%s\""),*Pack->ChallengeName);
    else Label=FString::Printf(TEXT("Unlock: (%d UP)"),Pack->UnlockCost);
    if (SourceInteractionButtonTextBlock) SourceInteractionButtonTextBlock->SetText(FText::FromString(Label));
}

void URecoveredUnlockStoreWidget::OnEntryClicked(const FString& PackID) {
    const double Now=GetStoreTime(this);
    const bool bDoubleClick=EquivalentPackID(LastClickedPack,PackID) && Now-LastClickTime<=DoubleClickWindowSeconds;
    if (bDoubleClick && IsPackUnlocked(PackID)) {
        const bool bEnable=!IsPackEnabled(PackID);
        if (!SetPackEnabled(PackID,bEnable)) return;
        PersistStoreState();
        ApplyEntryStates();
        SelectPack(PackID);
        UpdateButtonDisplay(PackID,false);
        if (IsInit) return;
        const FRecoveredPackInfo* Pack=FindPack(PackID);
        for (URecoveredPackEntryWidget* Entry:PackEntries) {
            if (!Entry || !Pack || !EquivalentPackID(Entry->PackID,PackID)) continue;
            Entry->ConfigureEntry(Pack->PackID,LoadObject<UTexture2D>(nullptr,*Pack->PreviewAssetPath),true,Entry->bIsPatreonExclusive,Entry->bIsPatron,bEnable);
        }
        PlayRecoveredAnimation(bEnable ? TEXT("EnablePackAnim") : TEXT("DisablePackAnim"));
        PlaySourceSound(EntryClickSoundPath,0.5f);
        LastStoreAction=bEnable ? TEXT("Pack enabled") : TEXT("Pack disabled");
        return;
    }
    LastClickedPack=PackID;
    LastClickTime=Now;
    UpdateInfoPanel(PackID);
    UpdateButtonDisplay(PackID,false);
    SelectPack(PackID);
}

void URecoveredUnlockStoreWidget::OnEntryHovered(const FString& PackID) {
    (void)PackID;
}

void URecoveredUnlockStoreWidget::OnEntryUnhovered() {
}

bool URecoveredUnlockStoreWidget::TryUnlockSelectedPack() {
    const FRecoveredPackInfo* Pack=FindPack(SelectedPackInfo.PackID);
    if (!Pack || Pack->bUnlocked || IsChallengeReward(*Pack)) return false;
    if (Pack->bPatreonExclusive && !IsPatron()) return false;
    const int32 Points=GetUnlockPoints();
    if (Points<Pack->UnlockCost) return false;
    const FString PackID=Pack->PackID;
    if (!SetPackUnlocked(PackID,true)) return false;
    SetPackEnabled(PackID,true);
    SetUnlockPoints(Points-Pack->UnlockCost);
    PersistStoreState();
    ApplyEntryStates();
    SelectPack(PackID);
    return true;
}

void URecoveredUnlockStoreWidget::HandleInteractionClicked() {
    const FRecoveredPackInfo* Pack=FindPack(SelectedPackInfo.PackID);
    if (!Pack) return;
    const FString PackID=Pack->PackID;
    if (!IsPatron() && Pack->bPatreonExclusive) {
        if (SourceInteractionButtonTextBlock) SourceInteractionButtonTextBlock->SetText(FText::FromString(TEXT("Become a Patron")));
        FPlatformProcess::LaunchURL(PatreonURL,nullptr,nullptr);
        LastStoreAction=TEXT("Patron access requested");
        return;
    }
    if (Pack->bUnlocked) {
        const bool bEnable=!Pack->bEnabled;
        if (SetPackEnabled(PackID,bEnable)) {
            PersistStoreState();
            ApplyEntryStates();
            SelectPack(PackID);
            UpdateButtonDisplay(PackID,false);
            PlayRecoveredAnimation(bEnable ? TEXT("EnablePackAnim") : TEXT("DisablePackAnim"));
            PlaySourceSound(EntryClickSoundPath,0.5f);
            LastStoreAction=bEnable ? TEXT("Pack enabled") : TEXT("Pack disabled");
        }
        return;
    }
    if (IsChallengeReward(*Pack) || !TryUnlockSelectedPack()) {
        PlayRecoveredAnimation(TEXT("BuyPackFailed"));
        PlaySourceSound(StoreFailureSoundPath);
        LastStoreAction=IsChallengeReward(*Pack) ? TEXT("Challenge reward required") : TEXT("Insufficient unlock points");
        return;
    }
    UpdateButtonDisplay(PackID,false);
    ClearAndRefreshPacks();
    PlayRecoveredAnimation(TEXT("BuyPackSuccess"));
    PlaySourceSound(StoreSuccessSoundPath);
    LastStoreAction=TEXT("Pack unlocked");
}

void URecoveredUnlockStoreWidget::EnableAllPacks() {
    ApplyEntryStates();
    for (const FRecoveredPackInfo& Pack:AvailablePacks) if (Pack.bUnlocked) SetPackEnabled(Pack.PackID,true);
    PersistStoreState();
    ApplyEntryStates();
    const FString SelectedID=LastClickedPack.IsEmpty() ? SelectedPackInfo.PackID : LastClickedPack;
    SelectPack(SelectedID);
    UpdateButtonDisplay(SelectedID,false);
    ClearAndRefreshPacks();
    PlaySourceSound(EntryClickSoundPath,0.5f);
    LastStoreAction=TEXT("All unlocked packs enabled");
}

void URecoveredUnlockStoreWidget::DisableAllPacks() {
    ApplyEntryStates();
    for (const FRecoveredPackInfo& Pack:AvailablePacks) if (Pack.bUnlocked) SetPackEnabled(Pack.PackID,false);
    PersistStoreState();
    ApplyEntryStates();
    const FString SelectedID=LastClickedPack.IsEmpty() ? SelectedPackInfo.PackID : LastClickedPack;
    SelectPack(SelectedID);
    UpdateButtonDisplay(SelectedID,false);
    ClearAndRefreshPacks();
    PlaySourceSound(EntryClickSoundPath,0.5f);
    LastStoreAction=TEXT("All unlocked packs disabled");
}

void URecoveredUnlockStoreWidget::HandleBackClicked() {
    CloseUnlockStore();
}

void URecoveredUnlockStoreWidget::HandleBackHovered() {
    PlayRecoveredAnimation(TEXT("BackButtonHover"));
}

void URecoveredUnlockStoreWidget::HandleBackUnhovered() {
    PlayRecoveredAnimation(TEXT("BackButtonUnhover"));
}

void URecoveredUnlockStoreWidget::HandleInteractionHovered() {
    PlayRecoveredAnimation(TEXT("OnInteractionButtonHover"));
}

void URecoveredUnlockStoreWidget::HandleInteractionUnhovered() {
    PlayRecoveredAnimation(TEXT("OnInteractionButtonUnhover"));
}

void URecoveredUnlockStoreWidget::CloseUnlockStore() {
    if (auto* Instance=Cast<URecoveredGameInstance>(GetGameInstance())) Instance->RefreshRecoveredMainMenuBackground();
    StopPackBatchTimer();
    RemoveFromParent();
    LastStoreAction=TEXT("Store closed");
}

void URecoveredUnlockStoreWidget::PlaySourceSound(const TCHAR* AssetPath,float Volume,float Pitch) const {
    if (USoundBase* Sound=LoadObject<USoundBase>(nullptr,AssetPath)) {
        if (GetWorld()) UGameplayStatics::PlaySound2D(this,Sound,Volume,Pitch,0.0f,nullptr,nullptr,true);
    }
}

FString URecoveredUnlockStoreWidget::GetInteractionLabel() const {
    return SourceInteractionButtonTextBlock ? SourceInteractionButtonTextBlock->GetText().ToString() : FString();
}

int32 URecoveredUnlockStoreWidget::GetCreatedPackEntryCount() const {
    return PackEntries.Num();
}

int32 URecoveredUnlockStoreWidget::GetCreatedSocialIconCount() const {
    return SocialIconEntries.Num();
}
