#include "RecoveredModesWidget.h"
#include "RecoveredStoreItem.h"
#include "RecoveredSuccuShopWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ScopeExit.h"
#include "Widgets/SWidget.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNativeWidgetTest,"CockHero.Recovery.NativeWidgetSlateRoots",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNativeWidgetTest::RunTest(const FString& Parameters) {
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    if (!TestNotNull(TEXT("Isolated widget world"),World)) return false;
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { GEngine->DestroyWorldContext(World); World->DestroyWorld(false); };
    UClass* Classes[]={URecoveredModesWidget::StaticClass(),URecoveredStoreItemWidget::StaticClass(),URecoveredSuccuShopWidget::StaticClass()};
    for (UClass* Class:Classes) {
        auto* Widget=NewObject<UUserWidget>(World,Class);
        if (!TestTrue(*FString::Printf(TEXT("Initialize %s"),*Class->GetName()),Widget->Initialize())) continue;
        TSharedRef<SWidget> Slate=Widget->TakeWidget();
        UWidget* Root=Widget->GetRootWidget();
        if (TestNotNull(*FString::Printf(TEXT("Native root exists for %s"),*Class->GetName()),Root)) {
            TestTrue(*FString::Printf(TEXT("Native root participates in Slate for %s"),*Class->GetName()),Root->GetCachedWidget().IsValid());
            if (Root->GetCachedWidget().IsValid()) TestFalse(TEXT("Native screen is not an empty spacer"),Root->GetCachedWidget()->GetTypeAsString()==TEXT("SSpacer"));
        }
    }
    return true;
}
#endif
