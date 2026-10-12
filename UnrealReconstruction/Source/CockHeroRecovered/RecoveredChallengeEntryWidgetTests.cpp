#include "RecoveredChallengeEntryWidget.h"
#include "RecoveredChallengeTracker.h"
#include "RecoveredChallengeWidget.h"
#include "RecoveredProgression.h"
#include "RecoveredRules.h"

#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/HorizontalBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Dom/JsonObject.h"
#include "Engine/DataTable.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "MovieScene.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
namespace {

const FLinearColor ChallengeCompletedColor(0.0f,0.5209959745407104f,0.12477199733257294f,1.0f);
const FLinearColor ChallengeIncompleteColor(1.0f,0.015208999626338482f,0.01298299990594387f,1.0f);
const TCHAR* ChallengeIconPath=TEXT("/Game/Recovery/Resources/ChallengeIcons/QuickshotIcon.QuickshotIcon");
const TCHAR* ChallengePackPreviewPath=TEXT("/Game/Recovery/Resources/Packs/anal_vol.anal_vol");
const TCHAR* SourceIconPath=TEXT("/Game/ChallengeIcons/QuickshotIcon.QuickshotIcon");

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

FRecoveredChallengeRow MakeChallengeRow(FName ChallengeID,const FString& DisplayName,bool bRewards) {
    FRecoveredChallengeRow Row;
    Row.ChallengeID=ChallengeID.ToString();
    Row.DisplayName=FText::FromString(DisplayName);
    Row.Description=FText::FromString(DisplayName+TEXT(" description"));
    Row.Icon=SourceIconPath;
    Row.Scope=TEXT("EChallengeScope::Session");
    FRecoveredRequirement Requirement;
    Requirement.MetricType=TEXT("EMetricType::Strokes");
    Requirement.ComparisonType=TEXT("EComparisonType::GreaterOrEqual");
    Requirement.TargetValue=10;
    Row.Requirements.Add(Requirement);
    if (bRewards) {
        FRecoveredReward Reward;
        Reward.RewardType=TEXT("XP");
        Reward.Value=37;
        Row.Rewards.Add(Reward);
        FRecoveredReward PackReward;
        PackReward.RewardType=TEXT("UnlockPack");
        PackReward.ItemIdentifier=TEXT("anal_vol._1");
        Row.Rewards.Add(PackReward);
    }
    return Row;
}

URecoveredChallengeEntryWidget* FindEntry(const URecoveredChallengeWidget* Tab,FName ChallengeID) {
    if (!Tab) return nullptr;
    for (const TObjectPtr<URecoveredChallengeEntryWidget>& EntryPointer:Tab->RecoveredChallengeEntries) {
        URecoveredChallengeEntryWidget* Entry=EntryPointer.Get();
        if (Entry && Entry->ChallengeID==ChallengeID) return Entry;
    }
    return nullptr;
}

bool SameNames(const TArray<FName>& Actual,const TArray<FName>& Expected) {
    if (Actual.Num()!=Expected.Num()) return false;
    for (int32 Index=0;Index<Expected.Num();++Index) {
        if (Actual[Index]!=Expected[Index]) return false;
    }
    return true;
}

}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredChallengeEntryWidgetTest,"CockHero.Recovery.ChallengeEntryWidget",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredChallengeEntryWidgetTest::RunTest(const FString& Parameters) {
    FString EntryEvidenceText;
    TSharedPtr<FJsonObject> EntryEvidence;
    const FString EntryEvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/challenge-entry-widget-recovery.json");
    if (!FFileHelper::LoadFileToString(EntryEvidenceText,*EntryEvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(EntryEvidenceText),EntryEvidence)) {
        AddError(TEXT("Missing challenge entry recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Challenge entry source execution remains unclaimed"),EntryEvidence->GetBoolField(TEXT("source_executed")));
    const TSharedPtr<FJsonObject> EntryLayout=EntryEvidence->GetObjectField(TEXT("layout"));
    TestEqual(TEXT("Challenge entry source layout component count"),int32(EntryLayout->GetIntegerField(TEXT("components"))),24);
    TestEqual(TEXT("Challenge entry source root"),EntryLayout->GetStringField(TEXT("root")),FString(TEXT("SizeBox_1")));
    TestTrue(TEXT("Challenge entry source payload layout round-trips"),EntryLayout->GetBoolField(TEXT("byte_identical_component_payloads")));
    const TSharedPtr<FJsonObject> SourceArtwork=EntryEvidence->GetObjectField(TEXT("source_artwork"));
    TestEqual(TEXT("Challenge entry source artwork count"),int32(SourceArtwork->GetIntegerField(TEXT("expected_icons"))),55);
    TestTrue(TEXT("Challenge entry source artwork imports completely"),SourceArtwork->GetBoolField(TEXT("all_imported")));

    FString PackEvidenceText;
    TSharedPtr<FJsonObject> PackEvidence;
    const FString PackEvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/challenge-pack-preview-recovery.json");
    if (!FFileHelper::LoadFileToString(PackEvidenceText,*PackEvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(PackEvidenceText),PackEvidence)) {
        AddError(TEXT("Missing challenge pack preview recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Challenge pack preview source execution remains unclaimed"),PackEvidence->GetBoolField(TEXT("source_executed")));
    TestEqual(TEXT("Challenge pack preview source count"),int32(PackEvidence->GetIntegerField(TEXT("expected_pack_rewards"))),9);
    TestEqual(TEXT("Challenge pack preview imported count"),int32(PackEvidence->GetIntegerField(TEXT("imported_previews"))),9);
    TestTrue(TEXT("Challenge pack preview asset properties verify"),PackEvidence->GetBoolField(TEXT("asset_properties_verified")));
    const TArray<TSharedPtr<FJsonValue>>& PackRecords=PackEvidence->GetArrayField(TEXT("previews"));
    TestEqual(TEXT("Challenge pack preview evidence record count"),PackRecords.Num(),9);
    for (const TSharedPtr<FJsonValue>& Value:PackRecords) {
        const TSharedPtr<FJsonObject> Record=Value.IsValid() ? Value->AsObject() : nullptr;
        if (!TestNotNull(TEXT("Challenge pack preview evidence record"),Record.Get())) continue;
        TestTrue(*FString::Printf(TEXT("Challenge pack preview copied: %s"),*Record->GetStringField(TEXT("pack_id"))),Record->GetBoolField(TEXT("copied")));
        TestTrue(*FString::Printf(TEXT("Challenge pack preview imported: %s"),*Record->GetStringField(TEXT("pack_id"))),Record->GetBoolField(TEXT("imported")));
        UTexture2D* Texture=LoadObject<UTexture2D>(nullptr,*Record->GetStringField(TEXT("recovered_asset")));
        if (!TestNotNull(*FString::Printf(TEXT("Challenge pack preview texture: %s"),*Record->GetStringField(TEXT("pack_id"))),Texture)) continue;
        TestEqual(*FString::Printf(TEXT("Challenge pack preview width: %s"),*Record->GetStringField(TEXT("pack_id"))),Texture->GetImportedSize().X,int32(Record->GetIntegerField(TEXT("width"))));
        TestEqual(*FString::Printf(TEXT("Challenge pack preview height: %s"),*Record->GetStringField(TEXT("pack_id"))),Texture->GetImportedSize().Y,int32(Record->GetIntegerField(TEXT("height"))));
    }

    FString IconEvidenceText;
    TSharedPtr<FJsonObject> IconEvidence;
    const FString IconEvidencePath=FPaths::ProjectDir()/TEXT("RecoveryEvidence/challenge-icon-recovery.json");
    if (!FFileHelper::LoadFileToString(IconEvidenceText,*IconEvidencePath) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(IconEvidenceText),IconEvidence)) {
        AddError(TEXT("Missing challenge icon recovery evidence"));
        return false;
    }
    TestFalse(TEXT("Challenge icon source execution remains unclaimed"),IconEvidence->GetBoolField(TEXT("source_executed")));
    TestEqual(TEXT("Challenge icon source count"),int32(IconEvidence->GetIntegerField(TEXT("expected_icons"))),55);
    TestEqual(TEXT("Challenge icon exported count"),int32(IconEvidence->GetIntegerField(TEXT("exported_icons"))),55);
    const TArray<TSharedPtr<FJsonValue>>& IconRecords=IconEvidence->GetArrayField(TEXT("textures"));
    TestEqual(TEXT("Challenge icon evidence record count"),IconRecords.Num(),55);
    TSet<FString> RecoveredIconPaths;
    for (const TSharedPtr<FJsonValue>& Value:IconRecords) {
        const TSharedPtr<FJsonObject> Record=Value.IsValid() ? Value->AsObject() : nullptr;
        if (!TestNotNull(TEXT("Challenge icon evidence record"),Record.Get())) continue;
        const FString Original=Record->GetStringField(TEXT("original"));
        const FString Recovered=Record->GetStringField(TEXT("recovered_asset"));
        TestTrue(*FString::Printf(TEXT("Challenge icon exported: %s"),*Original),Record->GetBoolField(TEXT("exported")));
        TestTrue(*FString::Printf(TEXT("Challenge icon decoded: %s"),*Original),Record->GetBoolField(TEXT("decoded")));
        TestTrue(*FString::Printf(TEXT("Challenge icon imported: %s"),*Original),Record->GetBoolField(TEXT("imported")));
        TestEqual(*FString::Printf(TEXT("Challenge icon width: %s"),*Original),int32(Record->GetIntegerField(TEXT("width"))),512);
        TestEqual(*FString::Printf(TEXT("Challenge icon height: %s"),*Original),int32(Record->GetIntegerField(TEXT("height"))),512);
        TestTrue(*FString::Printf(TEXT("Challenge icon recovery path: %s"),*Original),Recovered.StartsWith(TEXT("/Game/Recovery/Resources/ChallengeIcons/")));
        RecoveredIconPaths.Add(Recovered);
        TestNotNull(*FString::Printf(TEXT("Challenge icon texture asset: %s"),*Original),LoadObject<UTexture2D>(nullptr,*Recovered));
    }
    TestEqual(TEXT("Challenge icon recovered asset uniqueness"),RecoveredIconPaths.Num(),55);

    UClass* EntryClass=LoadClass<URecoveredChallengeEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/ChallengeEntryWidget.ChallengeEntryWidget_C"));
    if (!TestNotNull(TEXT("Challenge entry recovered class"),EntryClass)) return false;
    if (!TestTrue(TEXT("Challenge entry uses recovered native parent"),EntryClass->IsChildOf(URecoveredChallengeEntryWidget::StaticClass()))) return false;

    const UWidgetBlueprintGeneratedClass* EntryGenerated=Cast<UWidgetBlueprintGeneratedClass>(EntryClass);
    if (!TestNotNull(TEXT("Challenge entry preserves generated animation container"),EntryGenerated)) return false;
    TestEqual(TEXT("Challenge entry restores every source animation"),EntryGenerated->Animations.Num(),3);
    for (const TCHAR* Name:{TEXT("ButtonHover"),TEXT("ButtonUnhover"),TEXT("ButtonClick")}) {
        TestTrue(*FString::Printf(TEXT("Challenge entry animation restored: %s"),Name),HasSourceAnimation(EntryGenerated,FName(Name)));
    }

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };

    auto* Instance=NewObject<URecoveredGameInstance>();
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Challenge test save initializes"),Save->InitializeRecoveredDefaults())) return false;
    Instance->CurrentSave=Save;
    Instance->ProgressionManager=NewObject<URecoveredProgressionManager>(Instance);
    Instance->ChallengeTracker=NewObject<URecoveredChallengeTracker>(Instance);
    Instance->ChallengeTracker->RewardManager=Instance->ProgressionManager;

    const FName FirstID(TEXT("rookie_edger"));
    const FName SecondID(TEXT("master_edger"));
    const FName ThirdID(TEXT("quickshot"));
    const FName CompletedID(TEXT("like_a_rabbit"));
    UDataTable* Table=NewObject<UDataTable>(Instance);
    Table->RowStruct=FRecoveredChallengeRow::StaticStruct();
    Table->AddRow(FirstID,MakeChallengeRow(FirstID,TEXT("Rookie Edger"),false));
    Table->AddRow(SecondID,MakeChallengeRow(SecondID,TEXT("Master Edger"),false));
    Table->AddRow(ThirdID,MakeChallengeRow(ThirdID,TEXT("Quickshot"),false));
    Table->AddRow(CompletedID,MakeChallengeRow(CompletedID,TEXT("Like a Rabbit"),true));
    Instance->ChallengeTracker->ChallengeTable=Table;
    Instance->ProgressionManager->ChallengeDataTable=Table;
    if (!TestTrue(TEXT("Challenge test tracker initializes"),Instance->ChallengeTracker->InitializeChallenges())) return false;
    if (!TestTrue(TEXT("Completed test challenge enters source completion state"),Instance->ChallengeTracker->CompleteChallenge(CompletedID,1.0f))) return false;

    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    UTexture2D* Icon=LoadObject<UTexture2D>(nullptr,ChallengeIconPath);
    if (!TestNotNull(TEXT("Challenge entry source icon exists"),Icon)) return false;
    auto* SourceEntry=CreateWidget<URecoveredChallengeEntryWidget>(World,EntryClass);
    if (!TestNotNull(TEXT("Challenge entry instantiates"),SourceEntry)) return false;
    SourceEntry->TakeWidget();

    auto* EntryRoot=Cast<USizeBox>(SourceEntry->GetWidgetFromName(TEXT("SizeBox_1")));
    auto* EntryButton=Cast<UButton>(SourceEntry->GetWidgetFromName(TEXT("ChallengeEntryButton")));
    auto* TrackButton=Cast<UButton>(SourceEntry->GetWidgetFromName(TEXT("TrackButton")));
    auto* EntryIcon=Cast<UImage>(SourceEntry->GetWidgetFromName(TEXT("ChallengeIcon")));
    auto* EntryStatus=Cast<UTextBlock>(SourceEntry->GetWidgetFromName(TEXT("ChallengeCompletionStatus")));
    auto* EntryTitle=Cast<UTextBlock>(SourceEntry->GetWidgetFromName(TEXT("ChallengeTitle")));
    auto* EntryTrackText=Cast<UTextBlock>(SourceEntry->GetWidgetFromName(TEXT("TrackButtonText")));
    if (!TestNotNull(TEXT("Challenge entry source root"),EntryRoot) ||
        !TestNotNull(TEXT("Challenge entry source select button"),EntryButton) ||
        !TestNotNull(TEXT("Challenge entry source track button"),TrackButton) ||
        !TestNotNull(TEXT("Challenge entry source icon"),EntryIcon) ||
        !TestNotNull(TEXT("Challenge entry source completion label"),EntryStatus) ||
        !TestNotNull(TEXT("Challenge entry source title label"),EntryTitle) ||
        !TestNotNull(TEXT("Challenge entry source tracking label"),EntryTrackText)) return false;
    const TArray<FRecoveredReward> NoRewards;
    SourceEntry->PopulateChallengeEntry(ThirdID,FText::FromString(TEXT("Quickshot")),Icon,false,NoRewards,false,1,false);
    TestTrue(TEXT("Challenge entry hover binding"),EntryButton->OnHovered.IsBound());
    TestTrue(TEXT("Challenge entry unhover binding"),EntryButton->OnUnhovered.IsBound());
    TestTrue(TEXT("Challenge entry select binding"),EntryButton->OnClicked.IsBound());
    TestTrue(TEXT("Challenge entry track binding"),TrackButton->OnClicked.IsBound());
    TestEqual(TEXT("Challenge entry title populates"),EntryTitle->GetText().ToString(),FString(TEXT("Quickshot")));
    TestEqual(TEXT("Challenge entry icon populates"),EntryIcon->GetBrush().GetResourceObject(),static_cast<UObject*>(Icon));
    TestEqual(TEXT("Incomplete source status"),EntryStatus->GetText().ToString(),FString(TEXT("Incomplete")));
    TestEqual(TEXT("Incomplete source status color"),EntryStatus->GetColorAndOpacity().GetSpecifiedColor(),ChallengeIncompleteColor);
    TestEqual(TEXT("Untracked source label"),EntryTrackText->GetText().ToString(),FString(TEXT("Track 1/2")));

    SourceEntry->PopulateChallengeEntry(ThirdID,FText::FromString(TEXT("Quickshot")),Icon,false,NoRewards,true,2,false);
    TestEqual(TEXT("Tracked source label"),EntryTrackText->GetText().ToString(),FString(TEXT("Untrack 2/2")));

    SourceEntry->PopulateChallengeEntry(CompletedID,FText::FromString(TEXT("Like a Rabbit")),Icon,true,NoRewards,false,2,false);
    TestEqual(TEXT("Unclaimed source status"),EntryStatus->GetText().ToString(),FString(TEXT("Claim Rewards")));
    TestEqual(TEXT("Unclaimed source status color"),EntryStatus->GetColorAndOpacity().GetSpecifiedColor(),ChallengeCompletedColor);

    SourceEntry->PopulateChallengeEntry(CompletedID,FText::FromString(TEXT("Like a Rabbit")),Icon,true,NoRewards,false,2,true);
    TestEqual(TEXT("Claimed source status"),EntryStatus->GetText().ToString(),FString(TEXT("Completed")));
    TestEqual(TEXT("Claimed source status color"),EntryStatus->GetColorAndOpacity().GetSpecifiedColor(),ChallengeCompletedColor);
    TestEqual(TEXT("Claimed source track label"),EntryTrackText->GetText().ToString(),FString(TEXT("Done")));

    UClass* TabClass=LoadClass<URecoveredChallengeWidget>(nullptr,TEXT("/Game/Recovery/UI/ChallengesTabWidget.ChallengesTabWidget_C"));
    if (!TestNotNull(TEXT("Challenges tab recovered class"),TabClass)) return false;
    if (!TestTrue(TEXT("Challenges tab uses recovered native parent"),TabClass->IsChildOf(URecoveredChallengeWidget::StaticClass()))) return false;
    auto* Tab=CreateWidget<URecoveredChallengeWidget>(World,TabClass);
    if (!TestNotNull(TEXT("Challenges tab instantiates"),Tab)) return false;
    Tab->SetRecoveredChallengeGameInstance(Instance);
    Tab->TakeWidget();
    Tab->RefreshChallengeList();

    auto* ChallengeList=Cast<UVerticalBox>(Tab->GetWidgetFromName(TEXT("ChallengesVerticalBox")));
    auto* Interaction=Cast<UButton>(Tab->GetWidgetFromName(TEXT("InteractionButton")));
    auto* InteractionText=Cast<UTextBlock>(Tab->GetWidgetFromName(TEXT("InteractionButtonText")));
    auto* RewardsBody=Cast<UTextBlock>(Tab->GetWidgetFromName(TEXT("RewardsBody")));
    if (!TestNotNull(TEXT("Challenges tab source list"),ChallengeList) || !TestNotNull(TEXT("Challenges tab source interaction button"),Interaction) || !TestNotNull(TEXT("Challenges tab source interaction text"),InteractionText) || !TestNotNull(TEXT("Challenges tab source rewards body"),RewardsBody)) return false;
    TestEqual(TEXT("Recovered source metric progress text"),InteractionText->GetText().ToString(),FString(TEXT("0/10 strokes")));
    TestEqual(TEXT("Challenges tab preserves every tracker row"),Tab->GetChallengeEntryCount(),4);
    TestEqual(TEXT("Challenges tab mounts every recovered entry"),ChallengeList->GetChildrenCount(),4);
    const TArray<FName> ExpectedOrder={FirstID,SecondID,ThirdID,CompletedID};
    for (int32 Index=0;Index<ExpectedOrder.Num();++Index) {
        URecoveredChallengeEntryWidget* Entry=Tab->RecoveredChallengeEntries.IsValidIndex(Index) ? Tab->RecoveredChallengeEntries[Index].Get() : nullptr;
        if (!TestNotNull(*FString::Printf(TEXT("Recovered challenge entry %d"),Index),Entry)) continue;
        TestEqual(*FString::Printf(TEXT("Recovered source challenge order %d"),Index),Entry->ChallengeID,ExpectedOrder[Index]);
        TestEqual(*FString::Printf(TEXT("Recovered source entry class %d"),Index),Entry->GetClass(),EntryClass);
        TestTrue(*FString::Printf(TEXT("Recovered select delegate %d"),Index),Entry->OnChallengeClicked.IsBound());
        TestTrue(*FString::Printf(TEXT("Recovered track delegate %d"),Index),Entry->OnTrackButtonClicked.IsBound());
    }

    URecoveredChallengeEntryWidget* FirstEntry=FindEntry(Tab,FirstID);
    if (!TestNotNull(TEXT("First recovered challenge entry"),FirstEntry)) return false;
    auto* FirstSelect=Cast<UButton>(FirstEntry->GetWidgetFromName(TEXT("ChallengeEntryButton")));
    auto* FirstTrack=Cast<UButton>(FirstEntry->GetWidgetFromName(TEXT("TrackButton")));
    if (!TestNotNull(TEXT("Recovered first select button"),FirstSelect) || !TestNotNull(TEXT("Recovered first track button"),FirstTrack)) return false;
    Tab->SelectedChallengeID=NAME_None;
    FirstSelect->OnClicked.Broadcast();
    TestEqual(TEXT("Recovered select delegate changes detail target"),Tab->SelectedChallengeID,FirstID);
    FirstTrack->OnClicked.Broadcast();
    TestTrue(TEXT("Recovered track delegate tracks incomplete entry"),Tab->GetTrackedChallenges().Contains(FirstID));

    Instance->ChallengeTracker->TrackedChallenges={FirstID,SecondID};
    Tab->RefreshChallengeList();
    Tab->RunChallengeAction(ThirdID);
    const TArray<FName> ExpectedEviction={SecondID,ThirdID};
    TestTrue(TEXT("Recovered tracking cap evicts oldest entry"),SameNames(Tab->GetTrackedChallenges(),ExpectedEviction));
    Tab->RunChallengeAction(CompletedID);
    TestTrue(TEXT("Recovered completed entry cannot enter tracking queue"),SameNames(Tab->GetTrackedChallenges(),ExpectedEviction));

    URecoveredChallengeEntryWidget* CompletedEntry=FindEntry(Tab,CompletedID);
    if (!TestNotNull(TEXT("Recovered completed challenge entry"),CompletedEntry)) return false;
    auto* CompletedTrack=Cast<UButton>(CompletedEntry->GetWidgetFromName(TEXT("TrackButton")));
    auto* CompletedTrackText=Cast<UTextBlock>(CompletedEntry->GetWidgetFromName(TEXT("TrackButtonText")));
    if (!TestNotNull(TEXT("Recovered completed track button"),CompletedTrack) || !TestNotNull(TEXT("Recovered completed track label"),CompletedTrackText)) return false;
    CompletedTrack->OnClicked.Broadcast();
    TestEqual(TEXT("Recovered completed track action reports done"),CompletedTrackText->GetText().ToString(),FString(TEXT("Done")));
    TestTrue(TEXT("Recovered completed track action leaves queue unchanged"),SameNames(Tab->GetTrackedChallenges(),ExpectedEviction));

    Tab->SelectChallenge(ThirdID);
    Tab->RefreshChallengeList();
    TestEqual(TEXT("Recovered refresh selects first source entry"),Tab->SelectedChallengeID,FirstID);
    Tab->SelectChallenge(FirstID);
    const TArray<FName> TrackingBeforeIncompleteDetail=Tab->GetTrackedChallenges();
    Interaction->OnClicked.Broadcast();
    TestTrue(TEXT("Recovered incomplete detail action does not mutate tracking"),SameNames(Tab->GetTrackedChallenges(),TrackingBeforeIncompleteDetail));

    Tab->SelectChallenge(CompletedID);
    TestEqual(TEXT("Recovered completed detail interaction text"),InteractionText->GetText().ToString(),FString(TEXT("CLAIM REWARDS")));
    TestEqual(TEXT("Recovered source reward details text"),RewardsBody->GetText().ToString(),FString(TEXT("+ 37 XP\r\n+ anal vol. 1 pack\r\n")));
    TestTrue(TEXT("Recovered detail interaction binding"),Interaction->OnClicked.IsBound());
    const TArray<FName> TrackingBeforeClaim=Tab->GetTrackedChallenges();
    Interaction->OnClicked.Broadcast();
    const FRecoveredChallengeProgress* ClaimedProgress=Instance->ChallengeTracker->SessionProgress.Find(CompletedID);
    if (!TestNotNull(TEXT("Recovered claimed challenge progress"),ClaimedProgress)) return false;
    TestTrue(TEXT("Recovered detail interaction claims completed reward"),ClaimedProgress->bRewardsClaimed);
    TestTrue(TEXT("Recovered detail claim leaves tracking queue unchanged"),SameNames(Tab->GetTrackedChallenges(),TrackingBeforeClaim));
    TestEqual(TEXT("Recovered detail claim grants source reward once"),Instance->ProgressionManager->TotalXPEarned,37);
    UUserWidget* RewardOverlay=Tab->GetActiveRewardOverlay();
    if (!TestNotNull(TEXT("Recovered source reward overlay"),RewardOverlay)) return false;
    auto* OverlayRewards=Cast<UHorizontalBox>(RewardOverlay->GetWidgetFromName(TEXT("RewardsHorBox")));
    if (!TestNotNull(TEXT("Recovered source reward row"),OverlayRewards)) return false;
    TestEqual(TEXT("Recovered source reward row count"),OverlayRewards->GetChildrenCount(),2);
    auto* RewardEntry=Cast<UUserWidget>(OverlayRewards->GetChildAt(0));
    auto* RewardTitle=RewardEntry ? Cast<UTextBlock>(RewardEntry->GetWidgetFromName(TEXT("RewardTitle"))) : nullptr;
    if (!TestNotNull(TEXT("Recovered source reward title"),RewardTitle)) return false;
    TestEqual(TEXT("Recovered source XP overlay text"),RewardTitle->GetText().ToString(),FString(TEXT("+ 37 \r\nLevel XP")));
    auto* PackEntry=Cast<UUserWidget>(OverlayRewards->GetChildAt(1));
    auto* PackTitle=PackEntry ? Cast<UTextBlock>(PackEntry->GetWidgetFromName(TEXT("RewardTitle"))) : nullptr;
    auto* PackImage=PackEntry ? Cast<UImage>(PackEntry->GetWidgetFromName(TEXT("RewardImage"))) : nullptr;
    if (!TestNotNull(TEXT("Recovered source pack reward title"),PackTitle) || !TestNotNull(TEXT("Recovered source pack reward image"),PackImage)) return false;
    UTexture2D* PackPreview=LoadObject<UTexture2D>(nullptr,ChallengePackPreviewPath);
    if (!TestNotNull(TEXT("Recovered source pack preview"),PackPreview)) return false;
    TestEqual(TEXT("Recovered source pack overlay text"),PackTitle->GetText().ToString(),FString(TEXT("Anal Vol. 1 Pack")));
    TestEqual(TEXT("Recovered source pack overlay preview"),PackImage->GetBrush().GetResourceObject(),static_cast<UObject*>(PackPreview));
    auto* OverlayClose=Cast<UButton>(RewardOverlay->GetWidgetFromName(TEXT("InteractionButton")));
    if (!TestNotNull(TEXT("Recovered source reward overlay close"),OverlayClose)) return false;
    OverlayClose->OnClicked.Broadcast();
    TestNull(TEXT("Recovered source reward overlay closes"),Tab->GetActiveRewardOverlay());
    Tab->SelectChallenge(CompletedID);
    Interaction->OnClicked.Broadcast();
    TestEqual(TEXT("Recovered claimed detail action cannot grant reward twice"),Instance->ProgressionManager->TotalXPEarned,37);
    return true;
}
#endif
