#include "RecoveredImportWidget.h"
#include "Components/TextBlock.h"
#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredImportFailureTest,
    "CockHero.Recovery.ImportFailureVisibility",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRecoveredImportFailureTest::RunTest(const FString& Parameters) {
    UClass* Class = LoadClass<URecoveredImportWidget>(nullptr,
        TEXT("/Game/Recovery/UI/ImportMenuWidget.ImportMenuWidget_C"));
    if (!TestNotNull(TEXT("Importer class"), Class)) return false;
    auto* Widget = NewObject<URecoveredImportWidget>(GetTransientPackage(), Class);
    if (!TestTrue(TEXT("Importer tree initializes"), Widget->Initialize())) return false;
    auto Slate = Widget->TakeWidget();
    auto* Status = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("MediaFoundText")));
    if (!TestNotNull(TEXT("Visible status control"), Status)) return false;

    TestFalse(TEXT("Unavailable session cannot report a successful import"), Widget->RebuildImportedMediaDeck());
    const FString Failure = Widget->GetLastImportStatus();
    TestFalse(TEXT("Failure has an actionable message"), Failure.IsEmpty());
    Widget->RefreshImportedFileList();
    TestEqual(TEXT("Refreshing rows preserves failure"), Status->GetText().ToString(), Failure);
    TestFalse(TEXT("Missing input is rejected"), Widget->AddMediaFile(TEXT("")));
    TestEqual(TEXT("Rejected input leaves list empty"), Widget->GetImportedCount(), 0);
    Widget->OnScanClicked();
    TestEqual(TEXT("Empty scan explains prerequisite"), Widget->GetLastImportStatus(),
        FString(TEXT("Add a media directory before scanning")));
    Widget->RefreshImportedFileList();
    TestEqual(TEXT("Visible status matches recorded status"), Status->GetText().ToString(), Widget->GetLastImportStatus());
    return true;
}
#endif
