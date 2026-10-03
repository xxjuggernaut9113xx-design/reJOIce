#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredEventWidgets.h"
#include "WidgetBlueprint.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Animation/WidgetAnimation.h"
#include "Animation/MovieScene2DTransformSection.h"
#include "MovieScene.h"
#include "MovieSceneSection.h"
#include "Channels/MovieSceneChannelProxy.h"
#include "Sections/MovieSceneEventTriggerSection.h"
#include "Channels/MovieSceneFloatChannel.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Serialization/JsonSerializer.h"
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredAnimationTest,"CockHero.Recovery.SerializedBeatAnimations",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredAnimationTest::RunTest(const FString& Parameters) {
    auto* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,TEXT("/Game/Recovery/UI/UMG_BeatIcon.UMG_BeatIcon"));
    if (!TestNotNull(TEXT("Beat widget blueprint reloads"),Blueprint)) return false;
    TestTrue(TEXT("Beat callback parent restored"),Blueprint->GeneratedClass->IsChildOf(URecoveredBeatWidget::StaticClass()));
    TestEqual(TEXT("Three authoring animations survive reload"),Blueprint->Animations.Num(),3);
    auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Blueprint->GeneratedClass);
    if (!TestNotNull(TEXT("Generated widget class"),Generated)) return false;
    TestEqual(TEXT("Three runtime animations survive reload"),Generated->Animations.Num(),3);
    TSet<FName> ExpectedNames={TEXT("SpawnBeatAnim_INST"),TEXT("SpawnFastBeatAnim_INST"),TEXT("SpawnMediumBeatAnim_INST")};
    for (UWidgetAnimation* Animation:Generated->Animations) {
        if (!TestNotNull(TEXT("Runtime animation"),Animation)) continue;
        TestTrue(TEXT("Runtime animation retains its source name"),ExpectedNames.Contains(Animation->GetFName()));
        UMovieScene* Scene=Animation->GetMovieScene();
        if (!TestNotNull(TEXT("Serialized movie scene"),Scene)) continue;
        TestTrue(TEXT("Positive animation duration"),Animation->GetEndTime()>Animation->GetStartTime());
        TestTrue(TEXT("Widget bindings restored"),!Animation->AnimationBindings.IsEmpty());
        int32 TransformKeys=0,Events=0;
        for (UMovieSceneSection* Section:Scene->GetAllSections()) {
            if (auto* Transform=Cast<UMovieScene2DTransformSection>(Section)) {
                for (const FMovieSceneFloatChannel* Channel:Transform->GetChannelProxy().GetChannels<FMovieSceneFloatChannel>()) TransformKeys+=Channel->GetNumKeys();
            }
            if (auto* Event=Cast<UMovieSceneEventTriggerSection>(Section)) {
                for (const auto& Value:Event->EventChannel.GetData().GetValues()) {
                    ++Events;
                    if (TestNotNull(TEXT("Sequence event resolves after compilation and reload"),Value.Ptrs.Function.Get())) TestTrue(TEXT("Event callback belongs to the native beat widget"),Value.Ptrs.Function->GetOuter()==URecoveredBeatWidget::StaticClass());
                }
            }
        }
        TestTrue(TEXT("Original transform channel keys preserved"),TransformKeys>0);
        TestTrue(TEXT("Original sequence completion key preserved"),Events>0);
    }
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredStoreBindingTest,"CockHero.Recovery.StoreNavigationAndCountdown",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredStoreBindingTest::RunTest(const FString& Parameters) {
    UClass* Class=LoadClass<URecoveredStoreWidget>(nullptr,TEXT("/Game/Recovery/UI/StoreWidget.StoreWidget_C"));
    if (!TestNotNull(TEXT("Store class"),Class)) return false;
    auto* Store=NewObject<URecoveredStoreWidget>(GetTransientPackage(),Class);
    if (!TestTrue(TEXT("Store initializes"),Store->Initialize())) return false;
    auto Slate=Store->TakeWidget();
    auto* Close=Cast<UButton>(Store->GetWidgetFromName(TEXT("Close")));
    if (TestNotNull(TEXT("Source close button"),Close)) TestTrue(TEXT("Close handler bound"),Close->OnClicked.Contains(Store,TEXT("CloseStore")));
    TestEqual(TEXT("Source countdown duration"),Store->RemainingTimeOpen,30.0);
    Store->UpdateTimer();
    TestEqual(TEXT("Source countdown step"),Store->RemainingTimeOpen,29.95);
    auto* Bar=Cast<UProgressBar>(Store->GetWidgetFromName(TEXT("ProgressBar_168")));
    if (TestNotNull(TEXT("Source timer bar"),Bar)) TestEqual(TEXT("Timer drives bar"),Bar->GetPercent(),float(29.95/30));
    Store->RemainingTimeOpen=0;Store->UpdateTimer();
    TestFalse(TEXT("Timeout disables duplicate close"),Store->bButtonPressEnabled);
    return true;
}
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredAllAnimationsTest,"CockHero.Recovery.RestoredAnimationAssetReload",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredAllAnimationsTest::RunTest(const FString& Parameters) {
    FString Text;TSharedPtr<FJsonObject> Report;
    if (!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/animation-reload-expectations.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Report)) { AddError(TEXT("Missing animation recovery report"));return false; }
    int32 Screens=0,Animations=0;
    for (const auto& Pair:Report->Values) {
        auto Result=Pair.Value->AsObject();if (!Result->GetBoolField(TEXT("saved_assets"))) continue;
        ++Screens;const FString Path=TEXT("/Game/Recovery/UI/")+Pair.Key+TEXT(".")+Pair.Key;
        auto* Blueprint=LoadObject<UWidgetBlueprint>(nullptr,*Path);
        if (!TestNotNull(*Path,Blueprint)) continue;
        const int32 Expected=Result->GetIntegerField(TEXT("animation_count"));Animations+=Expected;
        TestEqual(*FString::Printf(TEXT("%s editable animation count"),*Pair.Key),Blueprint->Animations.Num(),Expected);
        auto* Generated=Cast<UWidgetBlueprintGeneratedClass>(Blueprint->GeneratedClass);
        if (!TestNotNull(TEXT("Generated animation class"),Generated)) continue;
        TestEqual(TEXT("Runtime animation count"),Generated->Animations.Num(),Expected);
        for (UWidgetAnimation* Animation:Generated->Animations) {
            if (!TestNotNull(TEXT("Runtime animation survives reload"),Animation) || !TestNotNull(TEXT("Movie scene survives reload"),Animation->GetMovieScene())) continue;
            for (UMovieSceneSection* Section:Animation->GetMovieScene()->GetAllSections()) if (auto* Events=Cast<UMovieSceneEventTriggerSection>(Section)) for (const auto& Event:Events->EventChannel.GetData().GetValues()) TestNotNull(TEXT("Saved event callback survives reload"),Event.Ptrs.Function.Get());
        }
    }
    TestTrue(TEXT("Recovered animation coverage does not regress"),Screens>=72 && Animations>=357);
    return true;
}
#endif
