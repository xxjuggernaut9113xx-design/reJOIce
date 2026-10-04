#include "RecoveredVideoSettings.h"
#include "RecoveredRules.h"
#include "Components/ComboBoxString.h"
#include "Components/Button.h"
#include "GameFramework/GameUserSettings.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

namespace {
// Names, fields, and option values come from VideoSettingsMenu/InitDefaultsFromSaveGame.json.
enum class EPreferenceKind { Bool, String, BeatCount, Multiplier };
struct FPreference { const TCHAR* Widget; const TCHAR* Key; EPreferenceKind Kind; };
const FPreference Preferences[] = {
    {TEXT("HealthBarAndTextComboBox"), TEXT("bHealthBarUIEnabled?"), EPreferenceKind::Bool},
    {TEXT("MoanSFXComboBox"), TEXT("bMoanSFXEnabled?"), EPreferenceKind::Bool},
    {TEXT("ScreenshakeComboBox"), TEXT("IsScreenShakeEnabled"), EPreferenceKind::Bool},
    {TEXT("VoicelinesComboBox"), TEXT("bVoiceLinesEnabled?"), EPreferenceKind::Bool},
    {TEXT("OnomatopoeiaComboBox_1"), TEXT("bOnomatopoeiasEnabled?"), EPreferenceKind::Bool},
    {TEXT("DynamicBackgroundsComboBox"), TEXT("bColoredBackgroundEnabled?"), EPreferenceKind::Bool},
    {TEXT("AutoToggleBrainMelterSuccubusComboBox"), TEXT("AutoBMToggledSuccubusEvent?"), EPreferenceKind::Bool},
    {TEXT("AutoToggleBrainMelterCumComboBox"), TEXT("AutoBMToggledCumEvent?"), EPreferenceKind::Bool},
    {TEXT("LootDropComboBox"), TEXT("AreLootDropsEnabled?"), EPreferenceKind::Bool},
    {TEXT("AssFrenzyComboBox"), TEXT("AssFrenzyEnabled?"), EPreferenceKind::Bool},
    {TEXT("BoobFrenzyComboBox"), TEXT("BoobFrenzyEnabled?"), EPreferenceKind::Bool},
    {TEXT("BackgroundMusicComboBox"), TEXT("IsDynamicMusicEnabled?"), EPreferenceKind::Bool},
    {TEXT("NotificationBoxesComboBox"), TEXT("AreNotificationBoxesEnabled?"), EPreferenceKind::Bool},
    {TEXT("ContextualBeatSFXComboBox"), TEXT("AreContextualBeatSFXEnabled?"), EPreferenceKind::Bool},
    {TEXT("TaskModifiersToggleComboBox"), TEXT("TaskModifiersEnabled?"), EPreferenceKind::Bool},
    {TEXT("BallRubbingComboBox"), TEXT("Modifier_BallRubbingEnabled?"), EPreferenceKind::Bool},
    {TEXT("BreathplayComboBox"), TEXT("Modifier_HoldBreathEnabled?"), EPreferenceKind::Bool},
    {TEXT("NippleRubbingComboBox"), TEXT("Modifier_NippleRubbingEnabled?"), EPreferenceKind::Bool},
    {TEXT("TipOnlyComboBox"), TEXT("TipOnlyModifierEnabled?"), EPreferenceKind::Bool},
    {TEXT("ShaftOnlyComboBox"), TEXT("ShaftOnlyModifierEnabled?"), EPreferenceKind::Bool},
    {TEXT("SyncShortVideosToBeatComboBox"), TEXT("bMediaSyncEnabled"), EPreferenceKind::Bool},
    {TEXT("FPSLimitComboBOx"), TEXT("FPSLimit"), EPreferenceKind::String},
    {TEXT("ScreenmodeComboBox"), TEXT("FullScreenMode"), EPreferenceKind::String},
    {TEXT("ResolutionComboBox"), TEXT("ResolutionSelection"), EPreferenceKind::String},
    {TEXT("BrainMelterMediaSwapComboBox"), TEXT("BrainMelterMediaBeatSwapInterval"), EPreferenceKind::BeatCount},
    {TEXT("EdgePacingMultiplier"), TEXT("EdgePacingMultiplierEnum"), EPreferenceKind::Multiplier},
    {TEXT("StrokeCountMultiplier"), TEXT("StrokeMultiplierEnum"), EPreferenceKind::Multiplier},
};
const FPreference* FindPreference(FName Name) {
    for (const auto& Entry : Preferences) if (Name==FName(Entry.Widget)) return &Entry;
    return nullptr;
}
const TArray<FString> Multipliers={TEXT("1x"),TEXT("2x"),TEXT("3x"),TEXT("4x"),TEXT("8x")};
}

bool URecoveredVideoSettingsMenu::WritePreference(URecoveredSaveGame* Save, FName Name, const FString& Value) {
    const auto* Entry=FindPreference(Name); if (!Save || !Entry) return false;
    switch (Entry->Kind) {
        case EPreferenceKind::Bool:
            if (Value!=TEXT("On") && Value!=TEXT("Off")) return false;
            return Save->SetBoolSetting(Entry->Key,Value==TEXT("On"));
        case EPreferenceKind::Multiplier: {
            const int32 Index=Multipliers.Find(Value); if (Index==INDEX_NONE) return false;
            return Save->SetNumberSetting(Entry->Key,Index);
        }
        case EPreferenceKind::BeatCount:
            for (int32 Count=1;Count<=4;++Count) if (Value==FString::Printf(TEXT("Every %d Beat%s"),Count,Count==1 ? TEXT("") : TEXT("s"))) return Save->SetNumberSetting(Entry->Key,Count);
            return false;
        default: return Save->SetStringSetting(Entry->Key,Value);
    }
}
FString URecoveredVideoSettingsMenu::ReadPreference(URecoveredSaveGame* Save,FName Name,const FString& Fallback) {
    const auto* Entry=FindPreference(Name); if (!Save || !Entry || !Save->HasSetting(Entry->Key)) return Fallback;
    switch (Entry->Kind) {
        case EPreferenceKind::Bool: return Save->GetBoolSetting(Entry->Key,Fallback==TEXT("On")) ? TEXT("On") : TEXT("Off");
        case EPreferenceKind::Multiplier: {
            const double Value=Save->GetNumberSetting(Entry->Key,-1);
            return Value>=0 && Value<5 && Value==FMath::FloorToDouble(Value) ? Multipliers[static_cast<int32>(Value)] : Fallback;
        }
        case EPreferenceKind::BeatCount: {
            const double Value=Save->GetNumberSetting(Entry->Key,-1);
            if (Value<1 || Value>4 || Value!=FMath::FloorToDouble(Value)) return Fallback;
            return FString::Printf(TEXT("Every %d Beat%s"),static_cast<int32>(Value),Value==1 ? TEXT("") : TEXT("s"));
        }
        default: return Save->GetStringSetting(Entry->Key,Fallback);
    }
}
FString URecoveredVideoSettingsMenu::SettingNameForCombo(FName ComboName) {
    const auto* Entry=FindPreference(ComboName); return Entry ? FString(Entry->Key) : FString();
}

void URecoveredVideoSettingsMenu::BindControls(bool bBind) {
    for (const auto& Preference : Preferences) {
        const TCHAR* ComboPtr=Preference.Widget;
        auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(ComboPtr));
        if (!Combo) continue;
        if (bBind) {
            Combo->OnSelectionChanged.AddUniqueDynamic(this, &URecoveredVideoSettingsMenu::OnComboSelectionChanged);
        } else {
            Combo->OnSelectionChanged.RemoveAll(this);
        }
    }
    if (auto* Button = Cast<UButton>(GetWidgetFromName(TEXT("ClearFavoritesButton")))) {
        if (bBind) Button->OnClicked.AddUniqueDynamic(this, &URecoveredVideoSettingsMenu::OnClearFavoritesClicked);
        else Button->OnClicked.RemoveDynamic(this, &URecoveredVideoSettingsMenu::OnClearFavoritesClicked);
    }
    if (auto* Button=Cast<UButton>(GetWidgetFromName(TEXT("OpenLatencyCalibrationUI")))) {
        if (bBind) Button->OnClicked.AddUniqueDynamic(this,&URecoveredVideoSettingsMenu::OpenCalibration);
        else Button->OnClicked.RemoveDynamic(this,&URecoveredVideoSettingsMenu::OpenCalibration);
    }

}

void URecoveredVideoSettingsMenu::NativeConstruct() {
    Super::NativeConstruct();
    PopulateComboDefaults();
    for (const auto& Preference : Preferences) {
        const TCHAR* Name=Preference.Widget;
        if (auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(Name))) LastSelections.Add(FName(Name), Combo->GetSelectedOption());
    }
    BindControls(true);
}

void URecoveredVideoSettingsMenu::NativeDestruct() {
    BindControls(false);
    Super::NativeDestruct();
}

void URecoveredVideoSettingsMenu::CommitComboValue(FName ComboName, const FString& SelectedItem) {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && WritePreference(Instance->CurrentSave, ComboName, SelectedItem)) {
        Instance->SaveRecoveredState();
    }
}

void URecoveredVideoSettingsMenu::PopulateComboDefaults() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    for (const auto& Preference : Preferences) {
        const TCHAR* ComboPtr=Preference.Widget;
        auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(ComboPtr));
        if (!Combo) continue;
        const FString Saved = ReadPreference(Instance->CurrentSave,FName(ComboPtr),Combo->GetSelectedOption());
        Combo->SetSelectedOption(Saved);
    }
}

void URecoveredVideoSettingsMenu::OnClearFavoritesClicked() {
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (Instance && Instance->CurrentSave && Instance->CurrentSave->SetStringArraySetting(TEXT("FavoriteMedia"), TArray<FString>())) {
        Instance->SaveRecoveredState();
    }
}

void URecoveredVideoSettingsMenu::OnComboSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType) {
    if (SelectionType == ESelectInfo::Direct) return;
    auto* Instance = Cast<URecoveredGameInstance>(GetGameInstance());
    if (!Instance || !Instance->CurrentSave) return;
    bool bChanged = false;
    for (const auto& Preference : Preferences) {
        const TCHAR* Name=Preference.Widget;
        if (auto* Combo = Cast<UComboBoxString>(GetWidgetFromName(Name))) {
            const FString Key = SettingNameForCombo(FName(Name));
            const FString Value = Combo->GetSelectedOption();
            if (LastSelections.FindRef(FName(Name)) != Value) {
                bChanged |= WritePreference(Instance->CurrentSave,FName(Name),Value);
                LastSelections.Add(FName(Name), Value);
                ApplyGraphicsSetting(Key, Value);
            }
        }
    }
    if (bChanged) Instance->SaveRecoveredState();
}

void URecoveredVideoSettingsMenu::ApplyGraphicsSetting(const FString& Key, const FString& Value) {
    // Applies resolution, screen mode, and FPS limit immediately.
    if (Key == TEXT("ResolutionSelection")) {
        FString W, H;
        if (Value.Split(TEXT("x"), &W, &H)) {
            const int32 ResX = FCString::Atoi(*W);
            const int32 ResY = FCString::Atoi(*H);
            if (ResX > 0 && ResY > 0) {
                UGameUserSettings* Settings = GEngine ? GEngine->GetGameUserSettings() : nullptr;
                if (Settings) {
                    Settings->SetScreenResolution(FIntPoint(ResX, ResY));
                    Settings->ApplySettings(false);
                }
            }
        }
    } else if (Key == TEXT("FullScreenMode")) {
        UGameUserSettings* Settings = GEngine ? GEngine->GetGameUserSettings() : nullptr;
        if (Settings) {
            EWindowMode::Type Mode = EWindowMode::Windowed;
            if (Value == TEXT("Fullscreen")) Mode = EWindowMode::Fullscreen;
            else if (Value == TEXT("Borderless")) Mode = EWindowMode::WindowedFullscreen;
            Settings->SetFullscreenMode(Mode);
            Settings->ApplySettings(false);
        }
    } else if (Key == TEXT("FPSLimit")) {
        UGameUserSettings* Settings = GEngine ? GEngine->GetGameUserSettings() : nullptr;
        if (Settings) {
            const float FPS = FCString::Atof(*Value);
            Settings->SetFrameRateLimit(FPS);
            Settings->ApplySettings(false);
        }
    }
}

void URecoveredVideoSettingsMenu::OpenCalibration() {
    auto* Manager=GetWorld() ? Cast<ARecoveredGlobalManager>(UGameplayStatics::GetGameMode(this)) : nullptr;
    if (Manager) Manager->LaunchCalibrationFlow();
}
