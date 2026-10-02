from pathlib import Path
import re
root = Path(__file__).parent
source = (root/'ghidra-native/integration-decompiled.c').read_text()
names = ['BuildBeatQueue', 'RebuildQueueFromCurrentState', 'Tick', 'StartPattern', 'PauseSequence', 'ResumeSequence', 'StopSequence', 'GetBeatsRemaining', 'GetTotalBeatsInQueue', 'OnBeatReachedCenter', 'GetMasterTimelinePosition']
headers = list(re.finditer(r'/\* [0-9a-f]+ \?([^@]+)@([^@]+)@@[^\n]*\*/', source))
for i, match in enumerate(headers):
    if match.group(1) not in names or match.group(2) != 'UBeatSpawnerManager':
        continue
    end = headers[i+1].start() if i+1 < len(headers) else len(source)
    (root/(match.group(1)+'-beat.c')).write_text(source[match.start():end],encoding='utf-8')
