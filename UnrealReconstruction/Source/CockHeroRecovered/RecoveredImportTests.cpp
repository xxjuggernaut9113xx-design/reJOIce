#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "UObject/Package.h"

#include "WidgetBlueprint.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Misc/ScopeExit.h"
#include "RecoveredFileImportManager.h"
#include "RecoveredImportFileEntryWidget.h"
#include "RecoveredImportWidget.h"
#include "RecoveredRules.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredImportParityTest,
    "CockHero.Recovery.ImportParity",
    EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool FRecoveredImportParityTest::RunTest(const FString& Parameters) {
    const FString SavedRoot = FPaths::ConvertRelativePathToFull(FPaths::ProjectSavedDir());
    const FString Scratch = FPaths::Combine(SavedRoot, TEXT("Automation"), FString::Printf(TEXT("ImportParity_%s"), *FGuid::NewGuid().ToString(EGuidFormats::Digits)));
    const FString Nested = FPaths::Combine(Scratch, TEXT("nested"));
    const FString MediaDirectory = FPaths::Combine(Scratch, TEXT("media"));
    if (!TestTrue(TEXT("Import fixture directory is created"), IFileManager::Get().MakeDirectory(*Nested, true))) return false;
    if (!TestTrue(TEXT("Base media directory is created"), IFileManager::Get().MakeDirectory(*MediaDirectory, true))) return false;
    ON_SCOPE_EXIT {
        if (FPaths::IsUnderDirectory(Scratch, SavedRoot)) IFileManager::Get().DeleteDirectory(*Scratch, false, true);
    };

    const TArray<FString> ImageFiles = {
        FPaths::Combine(Scratch, TEXT("image_slow.png")),
        FPaths::Combine(Scratch, TEXT("image_medium.jpg")),
        FPaths::Combine(Scratch, TEXT("image_fast.jpeg")),
        FPaths::Combine(Nested, TEXT("image_bmp.bmp")),
        FPaths::Combine(Nested, TEXT("image_gif.gif")),
        FPaths::Combine(Nested, TEXT("image_webp.webp"))
    };
    const TArray<FString> VideoFiles = {
        FPaths::Combine(Scratch, TEXT("video_slow.mp4")),
        FPaths::Combine(Scratch, TEXT("video_medium.webm")),
        FPaths::Combine(Nested, TEXT("video_fast.mov"))
    };
    const FString UnsupportedFile = FPaths::Combine(Scratch, TEXT("unsupported.mkv"));
    for (const FString& File : ImageFiles) {
        if (!TestTrue(*FString::Printf(TEXT("Image fixture writes: %s"), *File), FFileHelper::SaveStringToFile(TEXT("fixture"), *File))) return false;
    }
    for (const FString& File : VideoFiles) {
        if (!TestTrue(*FString::Printf(TEXT("Video fixture writes: %s"), *File), FFileHelper::SaveStringToFile(TEXT("fixture"), *File))) return false;
    }
    if (!TestTrue(TEXT("Unsupported fixture writes"), FFileHelper::SaveStringToFile(TEXT("fixture"), *UnsupportedFile))) return false;

    TestTrue(TEXT("Source PNG extension is accepted"), URecoveredFileImportManager::IsSupportedMediaFile(ImageFiles[0]));
    TestTrue(TEXT("Source MOV extension is accepted"), URecoveredFileImportManager::IsSupportedMediaFile(VideoFiles[2]));
    TestFalse(TEXT("Source MKV extension is excluded"), URecoveredFileImportManager::IsSupportedMediaFile(UnsupportedFile));

    URecoveredFileImportManager* Manager = NewObject<URecoveredFileImportManager>(GetTransientPackage());
    TArray<FString> Selected = ImageFiles;
    Selected.Append(VideoFiles);
    Selected.Add(UnsupportedFile);
    Manager->AddFiles(Selected);
    TestEqual(TEXT("All nine source extensions are retained"), Manager->ImportedFiles.Num(), 9);
    TestEqual(TEXT("Source image count includes every enabled image extension"), Manager->GetImageCount(), 6);
    TestEqual(TEXT("Source video count includes every enabled video extension"), Manager->GetVideoCount(), 3);
    TestEqual(TEXT("Source count presentation is exact"), Manager->GetMediaCountText(), FString(TEXT("FOUND: 6 IMAGES, 3 VIDEOS")));
    Manager->AddFiles({ImageFiles[0], VideoFiles[0]});
    TestEqual(TEXT("Duplicate input does not create new records"), Manager->ImportedFiles.Num(), 9);

    const FString MissingButSupported = FPaths::Combine(Scratch, TEXT("not_created.mp4"));
    Manager->AddFiles({MissingButSupported});
    TestEqual(TEXT("AddFiles does not require the source file to exist"), Manager->ImportedFiles.Num(), 10);
    Manager->RemoveFile(FPaths::ConvertRelativePathToFull(MissingButSupported));
    TestEqual(TEXT("Missing test record is removable"), Manager->ImportedFiles.Num(), 9);

    const FString DisabledImage = FPaths::ConvertRelativePathToFull(ImageFiles[0]);
    Manager->SetFileEnabled(DisabledImage, false);
    TestEqual(TEXT("Disabled images are omitted from the image count"), Manager->GetImageCount(), 5);
    TArray<FRecoveredMediaEntry> EnabledEntries = Manager->GetImportedMediaEntries();
    TestEqual(TEXT("Disabled entries are omitted from imported media"), EnabledEntries.Num(), 8);
    TestFalse(TEXT("Disabled path is absent from media output"), EnabledEntries.ContainsByPredicate([&DisabledImage](const FRecoveredMediaEntry& Entry) {
        return Entry.FullPath == DisabledImage;
    }));

    Manager->ClearAllData();
    TestEqual(TEXT("Clear removes imported records"), Manager->ImportedFiles.Num(), 0);
    TestEqual(TEXT("Clear removes watched directories"), Manager->WatchedDirectories.Num(), 0);
    Manager->WatchedDirectories.Add(Scratch);
    Manager->ScanCurrentPaths();
    TestEqual(TEXT("Recursive scan restores only source-supported files"), Manager->ImportedFiles.Num(), 9);
    TestEqual(TEXT("Recursive scan restores all images"), Manager->GetImageCount(), 6);
    TestEqual(TEXT("Recursive scan restores all videos"), Manager->GetVideoCount(), 3);

    URecoveredSaveGame* Save = NewObject<URecoveredSaveGame>(GetTransientPackage());
    if (!TestTrue(TEXT("Import save initializes source defaults"), Save->InitializeRecoveredDefaults())) return false;
    if (!TestTrue(TEXT("Manager binds its save state"), Manager->LoadFromSave(Save))) return false;
    Manager->AddFiles(Selected);
    Manager->SetFileEnabled(DisabledImage, false);
    TestFalse(TEXT("Single-character preset names are rejected"), Manager->SavePresetToSaveGame(TEXT("A"), Save));
    TestTrue(TEXT("Two-character whitespace preset names follow the native length check"), Manager->SavePresetToSaveGame(TEXT("  "), Save));
    TestTrue(TEXT("Source preset saves current directories and file states"), Manager->SavePresetToSaveGame(TEXT("Validation Preset"), Save));
    Manager->SetFileEnabled(DisabledImage, true);
    TestTrue(TEXT("Source preset loads"), Manager->LoadPresetFromSaveGame(TEXT("Validation Preset"), Save));
    const FRecoveredImportedFile* RestoredDisabled = Manager->ImportedFiles.FindByPredicate([&DisabledImage](const FRecoveredImportedFile& File) {
        return File.FilePath == DisabledImage;
    });
    TestTrue(TEXT("Preset restores per-file enabled state"), RestoredDisabled && !RestoredDisabled->bEnabled);
    TestTrue(TEXT("Preset list exposes saved name"), Manager->GetAllPresetNamesFromSaveGame(Save).Contains(TEXT("Validation Preset")));

    const FString RemovedBeforeLoad = FPaths::Combine(Scratch, TEXT("removed_before_load.png"));
    if (!TestTrue(TEXT("Deleted-preset fixture writes"), FFileHelper::SaveStringToFile(TEXT("fixture"), *RemovedBeforeLoad))) return false;
    Manager->AddFiles({RemovedBeforeLoad});
    TestTrue(TEXT("Second preset persists file list"), Manager->SavePresetToSaveGame(TEXT("Removed File Preset"), Save));
    TestTrue(TEXT("Preset fixture deletes before load"), IFileManager::Get().Delete(*RemovedBeforeLoad));
    TestTrue(TEXT("Second preset loads"), Manager->LoadPresetFromSaveGame(TEXT("Removed File Preset"), Save));
    const FString NormalizedRemoved = FPaths::ConvertRelativePathToFull(RemovedBeforeLoad);
    TestFalse(TEXT("Preset skips files no longer present"), Manager->ImportedFiles.ContainsByPredicate([&NormalizedRemoved](const FRecoveredImportedFile& File) {
        return File.FilePath == NormalizedRemoved;
    }));
    TestTrue(TEXT("Import state serializes after source operations"), Manager->SaveToSave(Save));

    URecoveredFileImportManager* RestoredManager = NewObject<URecoveredFileImportManager>(GetTransientPackage());
    TestTrue(TEXT("Import state restores from generic save state"), RestoredManager->LoadFromSave(Save));
    TestTrue(TEXT("Restored manager retains saved presets"), RestoredManager->GetAllPresetNamesFromSaveGame(Save).Contains(TEXT("Validation Preset")));
    TestEqual(TEXT("Source save restores presets without a live import selection"), RestoredManager->ImportedFiles.Num(), 0);
    TestTrue(TEXT("Restored manager loads the selected source preset"), RestoredManager->LoadPresetFromSaveGame(TEXT("Removed File Preset"), Save));
    TestEqual(TEXT("Loaded source preset restores its media count"), RestoredManager->GetMediaCountText(), Manager->GetMediaCountText());
    TestTrue(TEXT("Source preset deletion removes the saved map entry"), RestoredManager->DeletePresetFromSaveGame(TEXT("Validation Preset"), Save));
    TestFalse(TEXT("Deleted source preset no longer appears"), RestoredManager->GetAllPresetNamesFromSaveGame(Save).Contains(TEXT("Validation Preset")));

    const FString ImportSlow = FPaths::Combine(Scratch, TEXT("import_slow.png"));
    const FString ImportFast = FPaths::Combine(Scratch, TEXT("import_fast.mp4"));
    const FString BaseSlow = FPaths::Combine(MediaDirectory, TEXT("base_slow.png"));
    const FString Manifest = FPaths::Combine(Scratch, TEXT("base_manifest.json"));
    if (!TestTrue(TEXT("Slow import fixture writes"), FFileHelper::SaveStringToFile(TEXT("fixture"), *ImportSlow))) return false;
    if (!TestTrue(TEXT("Fast import fixture writes"), FFileHelper::SaveStringToFile(TEXT("fixture"), *ImportFast))) return false;
    if (!TestTrue(TEXT("Base media fixture writes"), FFileHelper::SaveStringToFile(TEXT("fixture"), *BaseSlow))) return false;
    if (!TestTrue(TEXT("Base manifest writes"), FFileHelper::SaveStringToFile(TEXT("{\"media\":[{\"file\":\"base_slow.png\",\"type\":\"image\"}]}"), *Manifest))) return false;

    URecoveredGameInstance* Instance = NewObject<URecoveredGameInstance>(GEngine);
    if (!TestNotNull(TEXT("Import integration game instance creates"), Instance)) return false;
    Instance->InitializeStandalone(NAME_None);
    UWorld* World = Instance->GetWorld();
    if (!TestNotNull(TEXT("Import integration world creates"), World)) {
        Instance->Shutdown();
        return false;
    }
    ON_SCOPE_EXIT {
        Instance->Shutdown();
        World->DestroyWorld(false);
        GEngine->DestroyWorldContext(World);
    };

    URecoveredSaveGame* IntegrationSave = NewObject<URecoveredSaveGame>(Instance);
    if (!TestTrue(TEXT("Integration save initializes"), IntegrationSave->InitializeRecoveredDefaults())) return false;
    URecoveredFileImportManager* IntegrationManager = NewObject<URecoveredFileImportManager>(Instance);
    Instance->CurrentSave = IntegrationSave;
    Instance->FileImportManager = IntegrationManager;
    if (!TestTrue(TEXT("Integration manager binds before media staging"), IntegrationManager->LoadFromSave(IntegrationSave))) return false;
    IntegrationManager->AddFiles({ImportSlow, ImportFast});
    World->InitializeActorsForPlay(FURL());
    ARecoveredGlobalManager* GlobalManager = World->SpawnActor<ARecoveredGlobalManager>();
    if (!TestNotNull(TEXT("Global manager spawns for import integration"), GlobalManager)) return false;
    TestTrue(TEXT("Base media and imports load through the source deck route"), GlobalManager->LoadMediaPack(Manifest, {}));
    if (!TestNotNull(TEXT("Merged deck state exists"), GlobalManager->MediaDeckState.Get())) return false;
    const TArray<FRecoveredMediaEntry>& SlowDeck = GlobalManager->MediaDeckState->Master.Slow;
    TestEqual(TEXT("Merged slow deck retains imported and base entries"), SlowDeck.Num(), 2);
    TestEqual(TEXT("Imported cards precede enabled-pack cards"), SlowDeck.IsValidIndex(0) ? SlowDeck[0].FullPath : FString(), FPaths::ConvertRelativePathToFull(ImportSlow));
    TestEqual(TEXT("Base card remains after imported card"), SlowDeck.IsValidIndex(1) ? SlowDeck[1].File : FString(), FString(TEXT("base_slow.png")));
    TestTrue(TEXT("Imported video enters its tagged deck"), GlobalManager->MediaDeckState->Master.Fast.ContainsByPredicate([&ImportFast](const FRecoveredMediaEntry& Entry) {
        return Entry.FullPath == FPaths::ConvertRelativePathToFull(ImportFast);
    }));

    IntegrationManager->WatchedDirectories.Add(Scratch);
    UClass* ImportMenuClass = LoadClass<URecoveredImportWidget>(nullptr, TEXT("/Game/Recovery/UI/ImportMenuWidget.ImportMenuWidget_C"));
    if (!TestNotNull(TEXT("Source ImportMenu class resolves"), ImportMenuClass)) return false;
    TestTrue(TEXT("Source ImportMenu inherits the recovered bridge"), ImportMenuClass->IsChildOf(URecoveredImportWidget::StaticClass()));
    TestEqual(TEXT("Integration fixture retains records before ImportMenu construction"), IntegrationManager->ImportedFiles.Num(), 2);
    URecoveredImportWidget* ImportMenu = CreateWidget<URecoveredImportWidget>(World, ImportMenuClass);
    if (!TestNotNull(TEXT("Source ImportMenu instantiates"), ImportMenu)) return false;
    ImportMenu->TakeWidget();
    ImportMenu->NativeConstruct();
    TestTrue(TEXT("Source ImportMenu retains its integration world"), ImportMenu->GetWorld() == World);
    TestTrue(TEXT("Source ImportMenu resolves the integration game instance"), ImportMenu->GetGameInstance() == Instance);
    TestTrue(TEXT("Integration game instance retains the fixture manager"), Instance->FileImportManager == IntegrationManager);
    TestEqual(TEXT("Source ImportMenu construct retains shared import records"), IntegrationManager->ImportedFiles.Num(), 2);
    TestEqual(TEXT("Source row batch size is restored"), ImportMenu->GetFilesPerFrame(), 10);
    TestEqual(TEXT("Source ImportMenu reads the shared import manager"), ImportMenu->GetImportedCount(), 2);
    for (const TCHAR* Name : {TEXT("AddButton"), TEXT("AddDirectoryButton"), TEXT("ScanButton"), TEXT("ClearButton"), TEXT("SavePresetButton"), TEXT("DeletePresetButton"), TEXT("BackButton"), TEXT("EntryScrollBox"), TEXT("MediaFoundText")}) {
        TestNotNull(*FString::Printf(TEXT("Source ImportMenu control survives: %s"), Name), ImportMenu->GetWidgetFromName(Name));
    }
    ImportMenu->CreateFileBatch();
    World->Tick(LEVELTICK_All, 0.02f);
    auto* ImportedRows = Cast<UScrollBox>(ImportMenu->GetWidgetFromName(TEXT("EntryScrollBox")));
    if (!TestNotNull(TEXT("Source ImportMenu row list resolves"), ImportedRows)) return false;
    TestEqual(TEXT("Source ImportMenu stages imported rows in the scroll list"), ImportedRows->GetChildrenCount(), 2);
    auto* FirstRow = Cast<URecoveredImportFileEntryWidget>(ImportedRows->GetChildAt(0));
    if (!TestNotNull(TEXT("Source ImportMenu first row resolves"), FirstRow)) return false;
    auto* FirstEnabled = Cast<UCheckBox>(FirstRow->GetWidgetFromName(TEXT("EnableCheckBox")));
    if (!TestNotNull(TEXT("Source ImportMenu first row checkbox resolves"), FirstEnabled)) return false;
    TestTrue(TEXT("Source ImportMenu checkbox binds the recovered row handler"), FirstEnabled->OnCheckStateChanged.Contains(FirstRow, TEXT("OnEnabledChanged")));
    FirstEnabled->SetIsChecked(false);
    FirstEnabled->OnCheckStateChanged.Broadcast(false);
    const FString NormalizedImportSlow = FPaths::ConvertRelativePathToFull(ImportSlow);
    const FRecoveredImportedFile* DisabledImport = IntegrationManager->ImportedFiles.FindByPredicate([&NormalizedImportSlow](const FRecoveredImportedFile& File) {
        return File.FilePath == NormalizedImportSlow;
    });
    TestTrue(TEXT("Source ImportMenu toggle writes the shared import manager"), DisabledImport && !DisabledImport->bEnabled);
    auto* SecondRow = Cast<URecoveredImportFileEntryWidget>(ImportedRows->GetChildAt(1));
    if (!TestNotNull(TEXT("Source ImportMenu second row resolves"), SecondRow)) return false;
    auto* RowRemove = Cast<UButton>(SecondRow->GetWidgetFromName(TEXT("RemoveButton")));
    if (!TestNotNull(TEXT("Source ImportMenu remove control resolves"), RowRemove)) return false;
    TestTrue(TEXT("Source ImportMenu remove control binds the recovered row handler"), RowRemove->OnClicked.Contains(SecondRow, TEXT("OnRemoveClicked")));
    RowRemove->OnClicked.Broadcast();
    World->Tick(LEVELTICK_All, 0.02f);
    TestEqual(TEXT("Source ImportMenu row removal updates the shared import manager"), IntegrationManager->ImportedFiles.Num(), 1);
    auto* Clear = Cast<UButton>(ImportMenu->GetWidgetFromName(TEXT("ClearButton")));
    if (!TestNotNull(TEXT("Source ImportMenu clear control resolves"), Clear)) return false;
    TestTrue(TEXT("Source ImportMenu clear control binds the recovered handler"), Clear->OnClicked.Contains(ImportMenu, TEXT("OnClearClicked")));
    Clear->OnClicked.Broadcast();
    World->Tick(LEVELTICK_All, 0.02f);
    TestEqual(TEXT("Source ImportMenu clear removes only imported files"), IntegrationManager->ImportedFiles.Num(), 0);
    TestEqual(TEXT("Source ImportMenu clear retains watched directories"), IntegrationManager->WatchedDirectories.Num(), 1);
    ImportMenu->RemoveFromParent();

    UClass* FileEntryClass = LoadClass<URecoveredImportFileEntryWidget>(nullptr, TEXT("/Game/Recovery/UI/FileEntry.FileEntry_C"));
    if (!TestNotNull(TEXT("Source FileEntry class resolves"), FileEntryClass)) return false;
    TestTrue(TEXT("Source FileEntry inherits the recovered bridge"), FileEntryClass->IsChildOf(URecoveredImportFileEntryWidget::StaticClass()));
    URecoveredImportFileEntryWidget* FileEntry = NewObject<URecoveredImportFileEntryWidget>(GetTransientPackage(), FileEntryClass);
    if (!TestTrue(TEXT("Source FileEntry initializes"), FileEntry->Initialize())) return false;
    FileEntry->TakeWidget();
    FileEntry->Configure(nullptr, ImportSlow, true);
    auto* Enabled = Cast<UCheckBox>(FileEntry->GetWidgetFromName(TEXT("EnableCheckBox")));
    auto* PathText = Cast<UTextBlock>(FileEntry->GetWidgetFromName(TEXT("FilePathTextUMG")));
    auto* Remove = Cast<UButton>(FileEntry->GetWidgetFromName(TEXT("RemoveButton")));
    TestNotNull(TEXT("Source enable checkbox survives reparent"), Enabled);
    TestNotNull(TEXT("Source path text survives reparent"), PathText);
    TestNotNull(TEXT("Source remove button survives reparent"), Remove);
    TestTrue(TEXT("Source FileEntry carries enabled state"), Enabled && Enabled->IsChecked());
    TestEqual(TEXT("Source FileEntry displays the complete path"), PathText ? PathText->GetText().ToString() : FString(), ImportSlow);
    return true;
}

#endif
