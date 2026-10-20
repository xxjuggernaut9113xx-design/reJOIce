#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredStoreItem.h"
#include "RecoveredRules.h"
#include "RecoveredNewerInventoryAdapter.h"
#include "RecoveredNewerInventory.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Misc/AutomationTest.h"
#include "Misc/ConfigCacheIni.h"
#include "Misc/ScopeExit.h"
#include "Widgets/SWidget.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredNewerStoreTransactionTest,"CockHero.Recovery.NewerInventory.StoreTransactions",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredNewerStoreTransactionTest::RunTest(const FString& Parameters) {
    bool Previous=false;
    const bool HadSetting=GConfig->GetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),Previous,GGameIni);
    GConfig->SetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),true,GGameIni);
    ON_SCOPE_EXIT { if (HadSetting) GConfig->SetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),Previous,GGameIni); else GConfig->RemoveKey(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),GGameIni); };
    const auto Initialization=UWorld::InitializationValues().AllowAudioPlayback(false).CreatePhysicsScene(false).CreateNavigation(false).CreateAISystem(false).ShouldSimulatePhysics(false).SetTransactional(false);
    UWorld* World=UWorld::CreateWorld(EWorldType::Game,false,NAME_None,nullptr,true,ERHIFeatureLevel::Num,&Initialization);
    FWorldContext& Context=GEngine->CreateNewWorldContext(EWorldType::Game);
    Context.SetCurrentWorld(World);
    ON_SCOPE_EXIT { World->DestroyWorld(false); GEngine->DestroyWorldContext(World); };
    auto* Instance=NewObject<URecoveredGameInstance>();
    World->SetGameInstance(Instance);
    Instance->NewerInventory=NewObject<URecoveredNewerInventory>(Instance);
    Instance->NewerInventory->HotbarItems.Init(ERecoveredShopItemType::None,5);
    World->InitializeActorsForPlay(FURL());
    auto* Manager=World->SpawnActor<ARecoveredGlobalManager>();
    auto* Item=NewObject<URecoveredStoreItemWidget>(World);
    if (!TestNotNull(TEXT("Store manager"),Manager) || !TestNotNull(TEXT("Native store item"),Item)) return false;
    if (!TestTrue(TEXT("Synthetic world-owned store initializes"),Item->Initialize())) return false;
    if (!TestTrue(TEXT("Store resolves synthetic world"),Item->GetWorld()==World) || !TestTrue(TEXT("Manager resolves active newer inventory"),RecoveredNewerInventoryAdapter::GetInventory(*Manager)==Instance->NewerInventory.Get())) return false;
    Item->ItemID=TEXT("Slowdown");
    const TSharedRef<SWidget> Slate=Item->TakeWidget();
    Manager->PlayerVariables.PlayerCoins=1000;
    TestFalse(TEXT("Unowned upgrade rejected before charging"),Item->TryUpgrade());
    TestEqual(TEXT("Rejected upgrade preserves balance"),Manager->PlayerVariables.PlayerCoins,1000);
    TestTrue(TEXT("Rejected upgrade preserves ownership"),Instance->NewerInventory->OwnedItems.IsEmpty());
    TestTrue(TEXT("Purchase unlocks and grants item"),Item->TryBuy());
    TestEqual(TEXT("Newer price is seventy-five"),Manager->PlayerVariables.PlayerCoins,925);
    TestEqual(TEXT("Purchase charge available"),Instance->NewerInventory->GetItemState(ERecoveredShopItemType::Slowdown).Charges,1);
    TestTrue(TEXT("Owned upgrade succeeds"),Item->TryUpgrade());
    TestEqual(TEXT("Upgrade uses source hundred coin cost"),Manager->PlayerVariables.PlayerCoins,825);
    TestEqual(TEXT("Newer one-based level advances"),Instance->NewerInventory->GetItemState(ERecoveredShopItemType::Slowdown).Level,2);
    GConfig->SetBool(TEXT("Recovery.Content"),TEXT("UseNewerProgression"),false,GGameIni);
    TestNull(TEXT("Baseline selection cannot consume persisted newer inventory"),RecoveredNewerInventoryAdapter::GetInventory(*Manager));
    return true;
}
#endif
