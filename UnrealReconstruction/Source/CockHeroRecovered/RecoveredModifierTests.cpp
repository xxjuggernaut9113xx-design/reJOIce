#include "RecoveredProgression.h"
#include "RecoveredRules.h"
#include "RecoveredMenu.h"
#include "RecoveredModifierCardEntryWidget.h"
#include "RecoveredModifierWidget.h"
#include "Animation/WidgetAnimation.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/Widget.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "MovieScene.h"

#if WITH_DEV_AUTOMATION_TESTS
namespace {
struct FRecoveredModifierConflictFixture {
    const TCHAR* Modifier;
    const TCHAR* const* Conflicts;
    int32 ConflictCount;
};

static const TCHAR* Pheromones[] = { TEXT("Slow and Steady"), TEXT("Succufrenzy") };
static const TCHAR* MrMoneyBandz[] = { TEXT("Succufrenzy"), TEXT("Sacrificial") };
static const TCHAR* AssFanatic[] = { TEXT("Boobs Fanatic"), TEXT("Feet Fanatic") };
static const TCHAR* BoobsFanatic[] = { TEXT("Ass Fanatic"), TEXT("Feet Fanatic") };
static const TCHAR* HungrySuccubi[] = { TEXT("Succufrenzy"), TEXT("Slow and Steady"), TEXT("Demon Proof"), TEXT("Deal With The Devil") };
static const TCHAR* Succufrenzy[] = { TEXT("Slow and Steady"), TEXT("Sacrificial"), TEXT("Hungry Succubi"), TEXT("Raw Dog"), TEXT("Demon Proof"), TEXT("All or Nothing"), TEXT("Double Time"), TEXT("Pheromones"), TEXT("Mr. Money Bandz"), TEXT("Deal With The Devil") };
static const TCHAR* SlowAndSteady[] = { TEXT("Hungry Succubi"), TEXT("Succufrenzy"), TEXT("Hivemind"), TEXT("Deal With The Devil"), TEXT("Double Time"), TEXT("Pheromones"), TEXT("Iron Man") };
static const TCHAR* Sacrificial[] = { TEXT("Mr. Money Bandz"), TEXT("Deal With The Devil"), TEXT("Succufrenzy") };
static const TCHAR* FeetFanatic[] = { TEXT("Ass Fanatic"), TEXT("Boobs Fanatic") };
static const TCHAR* IronMan[] = { TEXT("Slow and Steady") };
static const TCHAR* RawDog[] = { TEXT("Succufrenzy"), TEXT("All or Nothing") };
static const TCHAR* DemonProof[] = { TEXT("Deal With The Devil"), TEXT("Hivemind"), TEXT("Succufrenzy"), TEXT("Hungry Succubi") };
static const TCHAR* AllOrNothing[] = { TEXT("Succufrenzy"), TEXT("Raw Dog") };
static const TCHAR* Hivemind[] = { TEXT("Demon Proof"), TEXT("Slow and Steady") };
static const TCHAR* DealWithTheDevil[] = { TEXT("Demon Proof"), TEXT("Hungry Succubi"), TEXT("Sacrificial"), TEXT("Slow and Steady"), TEXT("Succufrenzy") };
static const TCHAR* DoubleTime[] = { TEXT("Succufrenzy"), TEXT("Slow and Steady") };

static const FRecoveredModifierConflictFixture NativeConflictFixtures[] = {
    { TEXT("Pheromones"), Pheromones, UE_ARRAY_COUNT(Pheromones) },
    { TEXT("Mr. Money Bandz"), MrMoneyBandz, UE_ARRAY_COUNT(MrMoneyBandz) },
    { TEXT("Ass Fanatic"), AssFanatic, UE_ARRAY_COUNT(AssFanatic) },
    { TEXT("Boobs Fanatic"), BoobsFanatic, UE_ARRAY_COUNT(BoobsFanatic) },
    { TEXT("Hungry Succubi"), HungrySuccubi, UE_ARRAY_COUNT(HungrySuccubi) },
    { TEXT("Succufrenzy"), Succufrenzy, UE_ARRAY_COUNT(Succufrenzy) },
    { TEXT("Slow and Steady"), SlowAndSteady, UE_ARRAY_COUNT(SlowAndSteady) },
    { TEXT("Sacrificial"), Sacrificial, UE_ARRAY_COUNT(Sacrificial) },
    { TEXT("Feet Fanatic"), FeetFanatic, UE_ARRAY_COUNT(FeetFanatic) },
    { TEXT("Iron Man"), IronMan, UE_ARRAY_COUNT(IronMan) },
    { TEXT("Raw Dog"), RawDog, UE_ARRAY_COUNT(RawDog) },
    { TEXT("Demon Proof"), DemonProof, UE_ARRAY_COUNT(DemonProof) },
    { TEXT("All or Nothing"), AllOrNothing, UE_ARRAY_COUNT(AllOrNothing) },
    { TEXT("Hivemind"), Hivemind, UE_ARRAY_COUNT(Hivemind) },
    { TEXT("Deal With The Devil"), DealWithTheDevil, UE_ARRAY_COUNT(DealWithTheDevil) },
    { TEXT("Double Time"), DoubleTime, UE_ARRAY_COUNT(DoubleTime) },
};

bool ChallengeContainsModifier(const FRecoveredChallengeRow& Challenge, FName ModifierID) {
    return Challenge.Conditions.ContainsByPredicate([ModifierID](const FRecoveredCondition& Condition) {
        return Condition.ConditionType == TEXT("modifier") && FName(*Condition.ConditionValue) == ModifierID;
    });
}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredModifierLinksTest,"CockHero.Recovery.ModifierConflictAndChallengeLinks",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredModifierLinksTest::RunTest(const FString& Parameters) {
    auto* Manager = NewObject<URecoveredProgressionManager>();
    Manager->ModifierDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Recovery/Progression/DT_Modifiers.DT_Modifiers"));
    if (!TestNotNull(TEXT("Source modifier data table"), Manager->ModifierDataTable.Get())) return false;
    TestEqual(TEXT("All source modifiers retained"), Manager->ModifierDataTable->GetRowMap().Num(), 16);

    int32 ResolvedModifierTitles = 0;
    for (const auto& Pair : Manager->ModifierDataTable->GetRowMap()) {
        const auto* Source = reinterpret_cast<const FRecoveredModifierRow*>(Pair.Value);
        if (!TestNotNull(TEXT("Modifier table row"), Source)) return false;
        const FName ModifierID(*Source->ModifierTitle.ToString());
        FRecoveredModifierRow Resolved;
        TestTrue(FString::Printf(TEXT("Display-title lookup resolves %s"), *ModifierID.ToString()), Manager->GetModifierData(ModifierID, Resolved));
        TestEqual(FString::Printf(TEXT("Display-title lookup preserves %s"), *ModifierID.ToString()), Resolved.ModifierTitle.ToString(), Source->ModifierTitle.ToString());
        TestEqual(FString::Printf(TEXT("Display-title canonicalizes %s"), *ModifierID.ToString()), Manager->GetCanonicalModifierID(ModifierID), ModifierID);
        ++ResolvedModifierTitles;
    }
    TestEqual(TEXT("Every modifier resolves through its display title"), ResolvedModifierTitles, 16);
    FRecoveredModifierRow InvalidRowLookup;
    TestFalse(TEXT("Serialized data-table row names are not modifier identities"), Manager->GetModifierData(TEXT("NewRow"), InvalidRowLookup));

    for (const FRecoveredModifierConflictFixture& Fixture : NativeConflictFixtures) {
        const TArray<FName> Actual = Manager->GetAllConflictsForModifier(FName(Fixture.Modifier));
        TestEqual(FString::Printf(TEXT("%s has native conflict count"), Fixture.Modifier), Actual.Num(), Fixture.ConflictCount);
        for (int32 Index = 0; Index < Fixture.ConflictCount; ++Index) {
            TestTrue(FString::Printf(TEXT("%s native conflict %d"), Fixture.Modifier, Index), Actual.IsValidIndex(Index) && Actual[Index] == FName(Fixture.Conflicts[Index]));
        }
    }
    TestTrue(TEXT("Non-registry modifier has no conflict targets"), Manager->GetAllConflictsForModifier(TEXT("Against The Clock")).IsEmpty());

    Manager->EnabledModifiers.Reset();
    TestTrue(TEXT("Native CanEnableModifier has no unlock side condition"), Manager->CanEnableModifier(TEXT("Pheromones")));
    Manager->EnabledModifiers.Add(TEXT("Succufrenzy"));
    const TArray<FName> ActiveConflicts = Manager->GetConflictingModifiers(TEXT("Pheromones"));
    TestEqual(TEXT("Only active conflict is returned"), ActiveConflicts.Num(), 1);
    TestTrue(TEXT("Active conflict is canonical Succufrenzy"), ActiveConflicts.Contains(TEXT("Succufrenzy")));
    TestFalse(TEXT("Active native conflict prevents enabling"), Manager->CanEnableModifier(TEXT("Pheromones")));

    Manager->ChallengeDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Recovery/Progression/DT_Challenges.DT_Challenges"));
    if (!TestNotNull(TEXT("Source challenge data table"), Manager->ChallengeDataTable.Get())) return false;
    int32 ModifierConditionCount = 0;
    for (const auto& Pair : Manager->ChallengeDataTable->GetRowMap()) {
        const auto* Source = reinterpret_cast<const FRecoveredChallengeRow*>(Pair.Value);
        if (!Source) continue;
        for (const FRecoveredCondition& Condition : Source->Conditions) {
            if (Condition.ConditionType != TEXT("modifier")) continue;
            const FName ModifierID(*Condition.ConditionValue);
            const FName LinkedChallengeID = Manager->GetChallengeForModifier(ModifierID);
            TestFalse(FString::Printf(TEXT("Modifier condition resolves %s"), *ModifierID.ToString()), LinkedChallengeID.IsNone());
            bool bLinkedDefinitionMatches = false;
            for (const auto& CandidatePair : Manager->ChallengeDataTable->GetRowMap()) {
                const auto* Candidate = reinterpret_cast<const FRecoveredChallengeRow*>(CandidatePair.Value);
                if (Candidate && FName(*Candidate->ChallengeID) == LinkedChallengeID && ChallengeContainsModifier(*Candidate, ModifierID)) {
                    bLinkedDefinitionMatches = true;
                    break;
                }
            }
            TestTrue(FString::Printf(TEXT("Linked challenge retains modifier condition %s"), *ModifierID.ToString()), bLinkedDefinitionMatches);
            ++ModifierConditionCount;
        }
    }
    TestTrue(TEXT("Source challenges include modifier links"), ModifierConditionCount > 0);

    auto* IsolatedChallenges = NewObject<UDataTable>();
    IsolatedChallenges->RowStruct = FRecoveredChallengeRow::StaticStruct();
    FRecoveredChallengeRow Unrelated; Unrelated.ChallengeID = TEXT("unrelated");
    IsolatedChallenges->AddRow(TEXT("SourceRowA"), Unrelated);
    FRecoveredChallengeRow Linked; Linked.ChallengeID = TEXT("slow_and_steady_challenge");
    FRecoveredCondition ModifierCondition; ModifierCondition.ConditionType = TEXT("modifier"); ModifierCondition.ConditionValue = TEXT("Slow and Steady");
    Linked.Conditions.Add(ModifierCondition);
    IsolatedChallenges->AddRow(TEXT("SourceRowB"), Linked);
    Manager->ChallengeDataTable = IsolatedChallenges;
    TestEqual(TEXT("Modifier challenge link returns ChallengeID rather than row name"), Manager->GetChallengeForModifier(TEXT("Slow and Steady")), FName(TEXT("slow_and_steady_challenge")));
    TestTrue(TEXT("Unlinked modifier returns no challenge"), Manager->GetChallengeForModifier(TEXT("Raw Dog")).IsNone());
    return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredModifierCardContractTest,"CockHero.Recovery.ModifierCardContract",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredModifierCardContractTest::RunTest(const FString& Parameters) {
    UClass* EntryClass=LoadClass<URecoveredModifierCardEntryWidget>(nullptr,TEXT("/Game/Recovery/UI/ModifierCardEntryWidget.ModifierCardEntryWidget_C"));
    if (!TestNotNull(TEXT("Recovered modifier entry class"),EntryClass)) return false;
    if (!TestTrue(TEXT("Modifier entry uses recovered native owner"),EntryClass->IsChildOf(URecoveredModifierCardEntryWidget::StaticClass()))) return false;
    const UWidgetBlueprintGeneratedClass* EntryGenerated=Cast<UWidgetBlueprintGeneratedClass>(EntryClass);
    if (!TestNotNull(TEXT("Modifier entry preserves generated animation container"),EntryGenerated)) return false;
    TestEqual(TEXT("Modifier entry restores every source animation"),EntryGenerated->Animations.Num(),5);
    for (const TCHAR* Name:{TEXT("ClickButton"),TEXT("HoverButton"),TEXT("HoverModifier"),TEXT("UnHoverButton"),TEXT("UnHoverModifier")}) {
        const FName Expected(Name);
        const FName Instance(*FString::Printf(TEXT("%s_INST"),Name));
        const bool bFound=EntryGenerated->Animations.ContainsByPredicate([Expected,Instance](const UWidgetAnimation* Animation) {
            const UMovieScene* Scene=Animation ? Animation->GetMovieScene() : nullptr;
            return Animation && (Animation->GetFName()==Expected || Animation->GetFName()==Instance || (Scene && (Scene->GetFName()==Expected || Scene->GetFName()==Instance)));
        });
        TestTrue(*FString::Printf(TEXT("Modifier source animation restored: %s"),Name),bFound);
    }

    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };

    auto* Instance=NewObject<URecoveredGameInstance>();
    auto* Save=NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Modifier test save initializes"),Save->InitializeRecoveredDefaults())) return false;
    auto* Progression=NewObject<URecoveredProgressionManager>(Instance);
    Progression->ModifierDataTable=LoadObject<UDataTable>(nullptr,TEXT("/Game/Recovery/Progression/DT_Modifiers.DT_Modifiers"));
    if (!TestNotNull(TEXT("Modifier source table"),Progression->ModifierDataTable.Get())) return false;
    const FName PheromonesID(TEXT("Pheromones"));
    const FName SuccufrenzyID(TEXT("Succufrenzy"));
    Progression->UnlockedModifiers.Add(PheromonesID);
    Progression->UnlockedModifiers.Add(SuccufrenzyID);
    Instance->CurrentSave=Save;
    Instance->ProgressionManager=Progression;
    World->SetGameInstance(Instance);
    World->InitializeActorsForPlay(FURL());

    UClass* TabClass=LoadClass<URecoveredModifierWidget>(nullptr,TEXT("/Game/Recovery/UI/ModifiersTabWidget.ModifiersTabWidget_C"));
    if (!TestNotNull(TEXT("Recovered modifier tab class"),TabClass)) return false;
    if (!TestTrue(TEXT("Modifier tab uses recovered native owner"),TabClass->IsChildOf(URecoveredModifierWidget::StaticClass()))) return false;
    auto* Tab=CreateWidget<URecoveredModifierWidget>(World,TabClass);
    if (!TestNotNull(TEXT("Modifier tab instantiates"),Tab)) return false;
    Tab->SetRecoveredModifierGameInstance(Instance);
    Tab->TakeWidget();
    Tab->RefreshModifierList();
    auto* Grid=Cast<UUniformGridPanel>(Tab->GetWidgetFromName(TEXT("UniformGridPanel_94")));
    if (!TestNotNull(TEXT("Modifier source grid"),Grid)) return false;
    TestEqual(TEXT("Modifier source grid entry count"),Grid->GetChildrenCount(),16);

    URecoveredModifierCardEntryWidget* Entry=nullptr;
    int32 EntryIndex=INDEX_NONE;
    for (int32 Index=0;Index<Grid->GetChildrenCount();++Index) {
        auto* Candidate=Cast<URecoveredModifierCardEntryWidget>(Grid->GetChildAt(Index));
        if (Candidate) Candidate->TakeWidget();
        auto* Title=Candidate ? Cast<UTextBlock>(Candidate->GetWidgetFromName(TEXT("ModifierTitle"))) : nullptr;
        if (Title && Title->GetText().ToString()==PheromonesID.ToString()) {
            Entry=Candidate;
            EntryIndex=Index;
            break;
        }
    }
    if (!TestNotNull(TEXT("Recovered Pheromones entry"),Entry)) return false;
    auto* Toggle=Cast<UButton>(Entry->GetWidgetFromName(TEXT("ToggleModifierButton")));
    auto* Background=Cast<UButton>(Entry->GetWidgetFromName(TEXT("BackgroundButton")));
    auto* ToggleText=Cast<UTextBlock>(Entry->GetWidgetFromName(TEXT("ButtonText")));
    if (!TestNotNull(TEXT("Modifier source toggle button"),Toggle) || !TestNotNull(TEXT("Modifier source background button"),Background) || !TestNotNull(TEXT("Modifier source toggle text"),ToggleText)) return false;
    TestTrue(TEXT("Source modifier delegate is bound by its tab"),Entry->OnCardClicked.IsBound());
    TestFalse(TEXT("Background button remains free of a state-toggle binding"),Background->OnClicked.IsBound());

    Entry->PopulateDetails(true,false,FText::FromString(TEXT("Pheromones")),nullptr,FText::FromString(TEXT("Source modifier description")),FText::FromString(TEXT("Source challenge")),FText::FromString(TEXT("Source locked description")));
    for (const TCHAR* TargetName:{TEXT("SizeBox_15"),TEXT("VerticalBox_149"),TEXT("LockOverlay"),TEXT("Overlay_388")}) {
        UWidget* Target=Entry->GetWidgetFromName(TargetName);
        if (!TestNotNull(*FString::Printf(TEXT("Source tooltip target: %s"),TargetName),Target)) continue;
        auto* Tooltip=Cast<URecoveredTooltip>(Target->GetToolTip());
        if (!TestNotNull(*FString::Printf(TEXT("Source tooltip mounted: %s"),TargetName),Tooltip)) continue;
        TestEqual(*FString::Printf(TEXT("Source unlocked tooltip title: %s"),TargetName),Tooltip->TooltipTitle.ToString(),FString(TEXT("Pheromones - Unlocked")));
        TestEqual(*FString::Printf(TEXT("Source unlocked tooltip description: %s"),TargetName),Tooltip->TooltipDescription.ToString(),FString(TEXT("Source modifier description")));
    }
    Entry->PopulateDetails(false,false,FText::FromString(TEXT("Pheromones")),nullptr,FText::FromString(TEXT("Source modifier description")),FText::FromString(TEXT("Source challenge")),FText::FromString(TEXT("Source locked description")));
    if (auto* Tooltip=Cast<URecoveredTooltip>(Entry->GetWidgetFromName(TEXT("LockOverlay"))->GetToolTip())) {
        TestEqual(TEXT("Source locked tooltip title"),Tooltip->TooltipTitle.ToString(),FString(TEXT("Pheromones - Locked")));
        TestEqual(TEXT("Source locked tooltip description"),Tooltip->TooltipDescription.ToString(),FString(TEXT("Source locked description")));
    } else AddError(TEXT("Source locked tooltip is missing"));
    Entry->PopulateDetails(true,false,FText::FromString(TEXT("Pheromones")),nullptr,FText::FromString(TEXT("Source modifier description")),FText::FromString(TEXT("Source challenge")),FText::FromString(TEXT("Source locked description")));

    UWidget* OriginalEntry=Grid->GetChildAt(EntryIndex);
    Toggle->OnClicked.Broadcast();
    TestTrue(TEXT("Source toggle enables selected modifier"),Progression->EnabledModifiers.Contains(PheromonesID));
    TestEqual(TEXT("Source toggle changes label in place"),ToggleText->GetText().ToString(),FString(TEXT("Enabled")));
    TestEqual(TEXT("Source direct toggle preserves entry instance"),Grid->GetChildAt(EntryIndex),OriginalEntry);
    Toggle->OnClicked.Broadcast();
    TestFalse(TEXT("Source toggle disables selected modifier"),Progression->EnabledModifiers.Contains(PheromonesID));
    TestEqual(TEXT("Source toggle restores label in place"),ToggleText->GetText().ToString(),FString(TEXT("Disabled")));
    TestEqual(TEXT("Source direct disable preserves entry instance"),Grid->GetChildAt(EntryIndex),OriginalEntry);

    Progression->EnabledModifiers.Add(SuccufrenzyID);
    Toggle->OnClicked.Broadcast();
    TestTrue(TEXT("Source conflict leaves requested modifier disabled"),!Progression->EnabledModifiers.Contains(PheromonesID));
    TestTrue(TEXT("Source conflict tracks pending confirmation"),Tab->HasPendingModifierConflicts());
    TestEqual(TEXT("Source conflict retains the existing card until confirmation"),Grid->GetChildAt(EntryIndex),OriginalEntry);
    TestTrue(TEXT("Source conflict confirmation completes"),Tab->ConfirmModifierConflicts());
    TestTrue(TEXT("Source conflict removes active conflict"),!Progression->EnabledModifiers.Contains(SuccufrenzyID));
    TestTrue(TEXT("Source conflict enables selected modifier"),Progression->EnabledModifiers.Contains(PheromonesID));
    TestFalse(TEXT("Source conflict clears pending state"),Tab->HasPendingModifierConflicts());
    TestNotEqual(TEXT("Source conflict confirmation repopulates modifier cards"),Grid->GetChildAt(EntryIndex),OriginalEntry);
    return true;
}
#endif
