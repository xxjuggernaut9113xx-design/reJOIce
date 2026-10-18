$ErrorActionPreference = 'Stop'
$taskRoot = 'D:\reJOIce\Analysis\ReferenceBuilds\newer-20261017'
$taskOutput = Join-Path $taskRoot 'decoded-data'
New-Item -ItemType Directory -Force -Path $taskOutput | Out-Null
$taskPackages = Get-ChildItem -LiteralPath (Join-Path $taskRoot 'data-legacy') -Recurse -Filter '*.uasset' | Where-Object {$_.BaseName -match 'DT_|DataTable|_DT$|Struct$|Entry$|ENUM$|Classification$|VoicePacksInfo$'}
$taskPackages += Get-ChildItem -LiteralPath (Join-Path $taskRoot 'blueprint-legacy-retry\CockHero\Content\NewSetup\Enums') -Filter '*.uasset'
$taskPackages += Get-ChildItem -LiteralPath (Join-Path $taskRoot 'blueprint-legacy\CockHero\Content\Widgets') -Recurse -Filter 'DialogueLineStruct.uasset'
foreach ($taskAsset in $taskPackages) {
    $taskDestination = Join-Path $taskOutput ($taskAsset.BaseName+'-raw.json')
    $taskProcess = Start-Process -FilePath 'C:\Users\webma\analysis\cockhero-v004\tools\uassetgui\UAssetGUI.exe' -ArgumentList 'tojson',$taskAsset.FullName,$taskDestination,'VER_UE5_3','FunctionOnly' -WindowStyle Hidden -Wait -PassThru
    if ($taskProcess.ExitCode -ne 0 -or !(Test-Path -LiteralPath $taskDestination)) { throw "Decode failed: $taskAsset" }
    Write-Output "Decoded $($taskAsset.BaseName)"
}
