"""Create a separate editable recovery project. Never modifies shipped assets."""
from pathlib import Path
import json
import shutil

ROOT = Path(__file__).parent
PROJECT = ROOT / 'UnrealReconstruction'
MODULE = 'CockHeroRecovered'
SOURCE = PROJECT / 'Source' / MODULE
rules = json.loads((ROOT / 'game-rules-draft.json').read_text(encoding='utf-8'))

def write(path, content):
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists():
        return  # Preserve later manual edits to the reconstructed project.
    path.write_text(content, encoding='utf-8')

write(PROJECT / f'{MODULE}.uproject', json.dumps({
    'FileVersion': 3, 'EngineAssociation': '5.3',
    'Category': 'Recovery', 'Description': 'Editable partial reconstruction of recovered CockHero V0.04 data and verified logic; not full gameplay parity.',
    'Modules': [{'Name': MODULE, 'Type': 'Runtime', 'LoadingPhase': 'Default'}],
    'Plugins': [{'Name': 'PythonScriptPlugin', 'Enabled': True}, {'Name': 'EditorScriptingUtilities', 'Enabled': True}]
}, indent=2))
compat_argument = r'''        bOverrideBuildEnvironment = true;
        AdditionalCompilerArguments = "/FI\"" + System.IO.Path.Combine(ProjectFile.Directory.FullName, "Source", "CompilerCompatibility.h") + "\"";'''
write(PROJECT / 'Source' / 'CompilerCompatibility.h', '''#pragma once
#if defined(_MSC_VER) && !defined(__clang__) && !defined(__has_feature)
#define __has_feature(x) 0
#endif
''')
for name, target in [(MODULE, 'Game'), (MODULE + 'Editor', 'Editor')]:
    write(PROJECT / 'Source' / f'{name}.Target.cs', f'''using UnrealBuildTool;
public class {name}Target : TargetRules {{
    public {name}Target(TargetInfo Target) : base(Target) {{
        Type = TargetType.{target};
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("{MODULE}");
{compat_argument}
    }}
}}
''')
write(SOURCE / f'{MODULE}.Build.cs', '''using UnrealBuildTool;
public class CockHeroRecovered : ModuleRules {
    public CockHeroRecovered(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "Json", "JsonUtilities"});
    }
}
''')
write(SOURCE / 'CockHeroRecovered.cpp', '''#include "Modules/ModuleManager.h"
IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, CockHeroRecovered, "CockHeroRecovered");
''')

def struct(name, fields, base=''):
    inheritance = ' : public ' + base if base else ''
    body = '\n'.join(f'    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") {typ} {field}{initial};' for typ, field, initial in fields)
    return f'USTRUCT(BlueprintType)\nstruct COCKHERORECOVERED_API F{name}{inheritance} {{\n    GENERATED_BODY()\n{body}\n}};\n'

assignments = rules['difficulty_configuration'][0]['assignments']
field_names = {k: k.replace('PlayerVariablesStruct.', '') for k in assignments}
header = '''#pragma once
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredRules.generated.h"

UENUM(BlueprintType)
enum class ERecoveredDifficulty : uint8 { EasyMode = 0, NormalMode = 1, InsaneMode = 2 };
'''
header += struct('RecoveredDifficultyConfig', [('double', field_names[k], ' = 0.0') for k in assignments])
header += struct('RecoveredBeatPattern', [('FString', 'PatternName', ''), ('TArray<double>', 'IntervalMultipliers', ''), ('TArray<FString>', 'Tags', ''), ('FString', 'Notes', '')])
header += struct('RecoveredEventRecord', [('int32', 'EventName', ' = 0'), ('double', 'BaseWeight', ' = 0'), ('double', 'WeightMultiplier', ' = 1'), ('bool', 'IsEligible', ' = false'), ('double', 'CooldownDuration', ' = 0'), ('bool', 'IsOnCooldown', ' = false'), ('FText', 'EventDescription', '')])
header += struct('RecoveredEventEntry', [('FString', 'Event', ''), ('int32', 'EntryOffset', ' = 0'), ('int32', 'EntryStatement', ' = 0')])
header += struct('RecoveredRequirement', [('FString', 'MetricType', ''), ('int32', 'TargetValue', ' = 0'), ('FString', 'ComparisonType', ''), ('int32', 'CurrentValue', ' = 0')])
header += struct('RecoveredCondition', [('FString', 'ConditionType', ''), ('FString', 'ConditionValue', '')])
header += struct('RecoveredReward', [('FString', 'RewardType', ''), ('int32', 'Value', ' = 0'), ('FString', 'ItemIdentifier', '')])
header += struct('RecoveredChallengeRow', [('FString', 'ChallengeID', ''), ('FText', 'DisplayName', ''), ('FText', 'Description', ''), ('FString', 'Icon', ''), ('FLinearColor', 'IconTint', ' = FLinearColor::White'), ('TArray<FRecoveredRequirement>', 'Requirements', ''), ('FString', 'Scope', ''), ('TArray<FRecoveredCondition>', 'Conditions', ''), ('TArray<FRecoveredReward>', 'Rewards', ''), ('int32', 'XPReward', ' = 0'), ('int32', 'UnlockPointsReward', ' = 0'), ('bool', 'bHidden', ' = false')], 'FTableRowBase')
header += struct('RecoveredLevelRow', [('int32', 'Level', ' = 0'), ('int32', 'XPRequired', ' = 0'), ('int32', 'UnlockPointsReward', ' = 0'), ('TArray<FString>', 'ContentUnlocks', ''), ('FText', 'TitleUnlock', ''), ('FString', 'LevelIcon', '')], 'FTableRowBase')
header += struct('RecoveredPlayerCardRow', [('FString', 'CardID', ''), ('FText', 'CardName', ''), ('FString', 'CardImage', ''), ('FString', 'RequiredChallengeID', ''), ('int32', 'RequiredLevel', ' = 0'), ('FLinearColor', 'CardColor', ' = FLinearColor::White')], 'FTableRowBase')

header += '''
UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredDefinitionAsset : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered") FString SourceClass;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered", meta=(MultiLine="true")) FString SerializedDefaultsJson;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered", meta=(MultiLine="true")) FString DeclaredPropertiesJson;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered") TMap<FString, FString> DecodedFunctionBodies;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evidence") bool bFullGameplayParityVerified = false;
};

UCLASS(BlueprintType)
class COCKHERORECOVERED_API URecoveredRulesAsset : public UDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Recovered") TArray<FRecoveredDifficultyConfig> DifficultyProfiles;
'''
for bank in rules['beat_pattern_banks']:
    header += f'    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Patterns") TArray<FRecoveredBeatPattern> {bank};\n'
header += '''    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events") TArray<FRecoveredEventRecord> EventRecords;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Events") TArray<FRecoveredEventEntry> EventEntries;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Evidence", meta=(MultiLine="true")) FString BlueprintEnumsJson;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evidence") FString SourceGameSHA256 = TEXT("c645757d1112491952b67bf29502b4721133ba6940a9cfb08358f0dde127560f");
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Evidence") bool bFullGameplayParityVerified = false;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Difficulty") static FRecoveredDifficultyConfig GetDifficultyConfig(ERecoveredDifficulty Difficulty);
    UFUNCTION(BlueprintPure, Category="Recovered|Heat") static double CalculateHeat(double Heat, double HeatAdd, double HeatGainMultiplier);
    UFUNCTION(BlueprintPure, Category="Recovered|Draw") static bool EvaluateChance(double Roll, double Chance);
    UFUNCTION(BlueprintPure, Category="Recovered|Timing") static float ClampBeatInterval(float Interval);
    UFUNCTION(BlueprintPure, Category="Recovered|Timing") static float ClampSpeedItemMultiplier(float Multiplier);
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetChallengeRowStruct();
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetLevelRowStruct();
    UFUNCTION(BlueprintPure, Category="Recovered|Progression") static UScriptStruct* GetPlayerCardRowStruct();
    UFUNCTION(BlueprintCallable, Category="Recovered|Progression") static FString ExportTableJson(UDataTable* Table);
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API ARecoveredManager : public AActor {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API ARecoveredGlobalManager : public AGameModeBase {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredRulesAsset> Rules;
    ARecoveredGlobalManager();
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") ERecoveredDifficulty CurrentDifficulty = ERecoveredDifficulty::NormalMode;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") double HeatLevel = 10.0;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Recovered") FRecoveredDifficultyConfig ActiveDifficulty;
    UFUNCTION(BlueprintCallable, Category="Recovered") void ApplyDifficulty(ERecoveredDifficulty Difficulty);
    UFUNCTION(BlueprintCallable, Category="Recovered") void AddHeat(double HeatAdd);
    // The original startup/session/outcome graph is not reconstructed here.
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredGameInstance : public UGameInstance {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
};

UCLASS(Blueprintable)
class COCKHERORECOVERED_API URecoveredSaveGame : public USaveGame {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered") TObjectPtr<URecoveredDefinitionAsset> RecoveredDefinition;
    // This does not implement original GVAS migration or restore original saves.
};
'''
write(SOURCE / 'RecoveredRules.h', header)
cpp = '''#include "RecoveredRules.h"
#include "DataTableUtils.h"

FRecoveredDifficultyConfig URecoveredRuleLibrary::GetDifficultyConfig(ERecoveredDifficulty Difficulty) {
    FRecoveredDifficultyConfig Result;
    switch (Difficulty) {
'''
for config in rules['difficulty_configuration']:
    cpp += f"    case ERecoveredDifficulty::{config['display_label']}:\n"
    for key, value in config['assignments'].items():
        cpp += f'        Result.{field_names[key]} = {float(value)!r};\n'
    cpp += '        break;\n'
cpp += '''    default: return GetDifficultyConfig(ERecoveredDifficulty::NormalMode);
    }
    return Result;
}

double URecoveredRuleLibrary::CalculateHeat(double Heat, double HeatAdd, double HeatGainMultiplier) {
    return FMath::Clamp(Heat + HeatAdd * HeatGainMultiplier, 0.0, 100.0);
}
bool URecoveredRuleLibrary::EvaluateChance(double Roll, double Chance) { return Roll <= Chance; }
float URecoveredRuleLibrary::ClampBeatInterval(float Interval) { return Interval <= 0.01f ? 0.01f : Interval; }
float URecoveredRuleLibrary::ClampSpeedItemMultiplier(float Multiplier) {
    if (5.0f <= Multiplier) Multiplier = 5.0f;
    if (Multiplier <= 0.1f) Multiplier = 0.1f;
    return Multiplier;
}
UScriptStruct* URecoveredRuleLibrary::GetChallengeRowStruct() { return FRecoveredChallengeRow::StaticStruct(); }
UScriptStruct* URecoveredRuleLibrary::GetLevelRowStruct() { return FRecoveredLevelRow::StaticStruct(); }
UScriptStruct* URecoveredRuleLibrary::GetPlayerCardRowStruct() { return FRecoveredPlayerCardRow::StaticStruct(); }
FString URecoveredRuleLibrary::ExportTableJson(UDataTable* Table) {
    return Table ? Table->GetTableAsJSON(EDataTableExportFlags::UseJsonObjectsForStructs | EDataTableExportFlags::UseSimpleText) : TEXT("[]");
}
ARecoveredGlobalManager::ARecoveredGlobalManager() {
    ActiveDifficulty = URecoveredRuleLibrary::GetDifficultyConfig(CurrentDifficulty);
}
void ARecoveredGlobalManager::ApplyDifficulty(ERecoveredDifficulty Difficulty) {
    CurrentDifficulty = Difficulty;
    ActiveDifficulty = URecoveredRuleLibrary::GetDifficultyConfig(Difficulty);
}
void ARecoveredGlobalManager::AddHeat(double HeatAdd) {
    HeatLevel = URecoveredRuleLibrary::CalculateHeat(HeatLevel, HeatAdd, ActiveDifficulty.DifficultyHeatGainMultiplier);
}
'''
write(SOURCE / 'RecoveredRules.cpp', cpp)

tests = '''#include "RecoveredRules.h"
#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredRulesTest, "CockHero.Recovery.VerifiedRules", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FRecoveredRulesTest::RunTest(const FString& Parameters) {
'''
for config in rules['difficulty_configuration']:
    label = config['display_label']
    tests += f'    const auto {label} = URecoveredRuleLibrary::GetDifficultyConfig(ERecoveredDifficulty::{label});\n'
    for key, value in config['assignments'].items():
        tests += f'    TestEqual(TEXT("{label}: {key}"), {label}.{field_names[key]}, {float(value)!r});\n'
tests += '''    TestEqual(TEXT("Heat gain uses difficulty"), URecoveredRuleLibrary::CalculateHeat(10, 2, 3), 16.0);
    TestEqual(TEXT("Heat caps at 100"), URecoveredRuleLibrary::CalculateHeat(99, 2, 3), 100.0);
    TestEqual(TEXT("Heat floors at 0"), URecoveredRuleLibrary::CalculateHeat(1, -2, 3), 0.0);
    TestTrue(TEXT("Chance equality is inclusive"), URecoveredRuleLibrary::EvaluateChance(25, 25));
    TestFalse(TEXT("Chance rejects higher roll"), URecoveredRuleLibrary::EvaluateChance(25.01, 25));
    TestEqual(TEXT("Beat interval minimum"), URecoveredRuleLibrary::ClampBeatInterval(-1), 0.01f);
    TestEqual(TEXT("Beat interval preserved"), URecoveredRuleLibrary::ClampBeatInterval(0.5f), 0.5f);
    TestEqual(TEXT("Speed floor"), URecoveredRuleLibrary::ClampSpeedItemMultiplier(-1), 0.1f);
    TestEqual(TEXT("Speed ceiling"), URecoveredRuleLibrary::ClampSpeedItemMultiplier(10), 5.0f);
    return true;
}
#endif
'''
write(SOURCE / 'RecoveredRulesTests.cpp', tests)
write(PROJECT / 'Config' / 'DefaultEngine.ini', '''[/Script/EngineSettings.GameMapsSettings]
EditorStartupMap=/Game/Recovery/RecoveryWorkspace
GameDefaultMap=/Game/Recovery/RecoveryWorkspace
GlobalDefaultGameMode=/Game/NewSetup/BP_GlobalManager.BP_GlobalManager_C
GameInstanceClass=/Game/NewSetup/BP_CHGameInstance.BP_CHGameInstance_C

[/Script/WindowsTargetPlatform.WindowsTargetSettings]
DefaultGraphicsRHI=DefaultGraphicsRHI_DX11

[/Script/Engine.RendererSettings]
r.DefaultFeature.AutoExposure=False
r.DynamicGlobalIlluminationMethod=0
r.ReflectionMethod=0
''')
write(PROJECT / 'Config' / 'DefaultGame.ini', '''[/Script/EngineSettings.GeneralProjectSettings]
ProjectName=CockHero Recovered
ProjectVersion=0.04-recovery-draft
Description=Partial editable reconstruction; gameplay parity remains unverified.
''')
write(PROJECT / '.gitignore', 'Binaries/\nIntermediate/\nSaved/\nDerivedDataCache/\n.vs/\n*.sln\n')

evidence = PROJECT / 'RecoveryEvidence'
evidence.mkdir(parents=True, exist_ok=True)
for filename in ['game-rules-draft.json', 'blueprint-class-fields.json', 'default-roundtrip-check.json', 'difficulty-branch-traces.json', 'main-event-graph.json', 'progression-roundtrip-check.json', 'native-function-evidence.json', 'RULES_SPEC_DRAFT.md']:
    shutil.copy2(ROOT / filename, evidence / filename)
shutil.copytree(ROOT / 'blueprint-functions', evidence / 'blueprint-functions', dirs_exist_ok=True)
shutil.copy2(ROOT / 'ghidra-native' / 'integration-decompiled.c', evidence / 'native-decompiled.c')
write(PROJECT / 'README.md', '''# CockHero recovered Unreal project

Open `CockHeroRecovered.uproject` with Unreal Engine 5.3.2. This is a separate, editable partial reconstruction, not the original source project or a finished full-game recreation.

Recovered content: three difficulty profiles; 62 pattern slots; 31 event records; 60 named event entry points; 55 challenge, 20 level and 36 player-card rows; eight manager/save default definitions; selected decoded function bodies. The C++ rule library implements checked difficulty assignments, heat updates, inclusive chance comparison and native timing clamps. Newly created Blueprint classes expose these C++ parents and recovered evidence. Original Blueprint graph layouts are not recoverable from this cooked build.

`Content/Recovery` contains editable data assets and tables. `Content/NewSetup` contains rebuilt Blueprint shells, whose original event graphs are not yet restored. `RecoveryEvidence` preserves source data, decoded bytecode and native pseudocode. Soft asset references are preserved as original path strings: original images, sound and maps have not been imported or recreated. The workspace level is a development inspection scene, not the original game map.

Remaining: startup and session state machine, all event/card/resource interactions, weighted selection, outcome/postgame logic, timing/audio/media integration, original presentation, progression execution, save compatibility and device adapters. No full-game completion is claimed. No AvtoHmver or original game/save files are modified.
''')
print(PROJECT)
