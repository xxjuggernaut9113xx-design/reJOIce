#include "RecoveredContentPaths.h"
#include "HAL/FileManager.h"
#include "Misc/AutomationTest.h"
#include "Misc/FileHelper.h"
#include "Misc/Guid.h"
#include "Misc/Paths.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredContentLayoutsTest, "CockHero.Recovery.ContentSourceLayouts", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredContentLayoutsTest::RunTest(const FString& Parameters) {
    const FString Root = FPaths::ProjectSavedDir() / TEXT("Automation/ContentLayouts") / FGuid::NewGuid().ToString(EGuidFormats::Digits);
    const FString Legacy = Root / TEXT("Extracted/Base_Game_CG/manifest.json");
    const FString Newer = Root / TEXT("CockHero/Extracted/Base_Game_CG/manifest.json");
    TestTrue(TEXT("Empty root does not select current-directory content"), FRecoveredContentPaths::FindBaseManifest(FString()).IsEmpty());
    TestEqual(TEXT("Missing manifest retains selected source root"), FRecoveredContentPaths::FindBaseManifest(Root), Newer);
    if (!TestTrue(TEXT("Create legacy layout"), IFileManager::Get().MakeDirectory(*FPaths::GetPath(Legacy), true))) return false;
    TestTrue(TEXT("Create legacy manifest fixture"), FFileHelper::SaveStringToFile(TEXT("{}"), *Legacy));
    TestEqual(TEXT("Previous layout remains usable"), FRecoveredContentPaths::FindBaseManifest(Root), Legacy);
    TestTrue(TEXT("Create newer layout"), IFileManager::Get().MakeDirectory(*FPaths::GetPath(Newer), true));
    TestTrue(TEXT("Create newer manifest fixture"), FFileHelper::SaveStringToFile(TEXT("{}"), *Newer));
    TestEqual(TEXT("Current layout wins within explicitly selected build"), FRecoveredContentPaths::FindBaseManifest(Root), Newer);
    TestTrue(TEXT("Remove isolated fixtures"), IFileManager::Get().DeleteDirectory(*Root, false, true));
    return true;
}
#endif
