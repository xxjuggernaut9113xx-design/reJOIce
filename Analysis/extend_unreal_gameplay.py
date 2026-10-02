"""Generate reflected state types from recovered field definitions."""
from pathlib import Path
import json
import re
import shutil

root = Path(__file__).parent
project = root / 'UnrealReconstruction'
dest = project / 'Source/CockHeroRecovered/RecoveredGameplay.h'
classes = json.loads((root / 'blueprint-class-fields.json').read_text())['classes']
rules = json.loads((root / 'game-rules-draft.json').read_text())
defaults = rules['serialized_class_defaults']['BP_GlobalManager_C']['PlayerVariablesStruct']
native = json.loads((root / 'native-reflection-schemas.json').read_text())['SessionStats']
enums = json.loads((root / 'native-reflection-enums.json').read_text())['EMetricType']

def clean(name):
    return re.sub(r'_\d+_[A-Fa-f0-9]{32}$', '', name)

def identifier(name, boolean=False):
    name = re.sub('[^A-Za-z0-9_]', '', name)
    return ('b' + name) if boolean and not name.startswith('b') else name

header = '''#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecoveredGameplay.generated.h"

UENUM(BlueprintType)
enum class ERecoveredMetric : uint8 {
'''
for entry in enums:
    header += f"    {entry['name'].split('::')[-1]} = {entry['value']},\n"
header += '''};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPlayerVariables {
    GENERATED_BODY()
'''
legacy = next(c for c in classes if c['class'] == 'LegacyStats')
field_map = {}
for prop in legacy['properties']:
    original = clean(prop['name'])
    bool_type = prop['type'] == 'BoolProperty'
    name = identifier(original, bool_type)
    field_map[original] = name
    typ = {'IntProperty':'int32', 'DoubleProperty':'double', 'BoolProperty':'bool', 'ArrayProperty':'TArray<int32>'}[prop['type']]
    default = defaults[original]
    initializer = '' if isinstance(default, list) else ' = ' + (str(bool(default)).lower() if bool_type else str(default))
    header += f'    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Player", meta=(DisplayName="{original}")) {typ} {name}{initializer};\n'
header += '''};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredSessionStats {
    GENERATED_BODY()
'''
for prop in native:
    if prop['kind'] == 21:
        continue
    typ = {3:'int32', 12:'bool', 22:'TArray<FString>'}[prop['kind']]
    initializer = '' if prop['kind'] == 22 else ' = false' if prop['kind'] == 12 else ' = 0'
    header += f'    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Recovered Session") {typ} {prop["name"]}{initializer};\n'
header += '''};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredDeviceState {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bLovense = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bHandy = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bButtplugVibrators = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bButtplugStrokers = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Device State") bool bFullStrokePerBeat = false;
};

USTRUCT(BlueprintType)
struct COCKHERORECOVERED_API FRecoveredPitchPair {
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pitch") double BeatPitch = 0;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pitch") double MoanPitch = 0;
};

UCLASS()
class COCKHERORECOVERED_API URecoveredStateRuleLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Recovered|Preferences") static double GetPreferenceMultiplier(uint8 Index, double Previous);
    UFUNCTION(BlueprintPure, Category="Recovered|Combo") static uint8 DetermineComboTier(int32 ComboCount, uint8 PreviousTier);
    UFUNCTION(BlueprintPure, Category="Recovered|Timing") static double GetMinimumBeatInterval(uint8 Difficulty, const FRecoveredDeviceState& Devices, double Previous);
    UFUNCTION(BlueprintPure, Category="Recovered|Audio") static FRecoveredPitchPair CalculateBeatPitch(int32 TotalBeats, int32 RemainingBeats);
    UFUNCTION(BlueprintCallable, Category="Recovered|Resources") static int32 AddCoinsToState(UPARAM(ref) FRecoveredPlayerVariables& Player, int32 Coins);
    UFUNCTION(BlueprintPure, Category="Recovered|Resources") static double AddToCumMeter(double Current, double Amount);
    UFUNCTION(BlueprintPure, Category="Recovered|Resources") static double AddToLootBar(double Current, double Amount, double Multiplier);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void RecordSessionMetric(UPARAM(ref) FRecoveredSessionStats& Stats, ERecoveredMetric Metric, int32 Amount);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void SetSessionMetric(UPARAM(ref) FRecoveredSessionStats& Stats, ERecoveredMetric Metric, int32 Value);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void SetMaximumCombo(UPARAM(ref) FRecoveredSessionStats& Stats, int32 Combo);
    UFUNCTION(BlueprintCallable, Category="Recovered|Metrics") static void AdvanceSessionDuration(UPARAM(ref) FRecoveredPlayerVariables& Player, UPARAM(ref) FRecoveredSessionStats& Stats, double Heat);
    UFUNCTION(BlueprintPure, Category="Recovered|Arithmetic") static int32 AddInt32Wrapping(int32 A, int32 B);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredMetricUpdateRequested, ERecoveredMetric, Metric, int32, Amount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRecoveredCoinsAdded, int32, Earned, int32, Total);
'''
dest.write_text(header, encoding='utf-8')
(project / 'RecoveryEvidence/player-field-map.json').write_text(json.dumps(field_map, indent=2), encoding='utf-8')
shutil.copy2(root / 'state-rule-traces.json', project / 'RecoveryEvidence/state-rule-traces.json')
shutil.copy2(root / 'startup-outcome-pseudocode.txt', project / 'RecoveryEvidence/startup-outcome-pseudocode.txt')
print('Generated', len(legacy['properties']), 'player fields and native session state')
