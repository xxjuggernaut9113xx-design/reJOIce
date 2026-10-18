$ErrorActionPreference = 'Stop'
$taskRoot = 'D:\reJOIce\Analysis\ReferenceBuilds\newer-20261017'
$taskSource = Join-Path $taskRoot 'blueprint-legacy\CockHero\Content'
$taskOutput = Join-Path $taskRoot 'decoded-blueprints'
New-Item -ItemType Directory -Force -Path $taskOutput | Out-Null
$taskNames = @('BP_CHGameInstance','BP_CardManager','BP_DialogueManager','BP_DrawManager','BP_EdgeManager','UI_Manager','GameModeCustomizationScreen_WIDGET','PostCumContinue_Widget','RestWidget','StoreWidget','WBP_SuccuStoreItem','WBP_StoreItem_Standard','ModularInventoryHotbar_Widget','VideoSettingsMenuV2','NotificationBoxWidget','RewindFastForwardOverlay_Widget','VolumeSwitchOverlay_Widget','NormalEdgeOverlay_Widget','CummingEarlyOverlay_Widget','CummingOnTimeOverlay_Widget')
foreach ($taskName in $taskNames) {
    $taskAsset = Get-ChildItem -LiteralPath $taskSource -Filter ($taskName+'.uasset') -Recurse | Select-Object -First 1
    if ($null -eq $taskAsset) { Write-Warning "Missing $taskName"; continue }
    $taskDestination = Join-Path $taskOutput ($taskName+'-functions.json')
    $taskProcess = Start-Process -FilePath 'C:\Users\webma\analysis\cockhero-v004\tools\uassetgui\UAssetGUI.exe' -ArgumentList 'tojson',$taskAsset.FullName,$taskDestination,'VER_UE5_3','FunctionOnly' -WindowStyle Hidden -Wait -PassThru
    if ($taskProcess.ExitCode -ne 0 -or !(Test-Path -LiteralPath $taskDestination)) { throw "Decode failed: $taskName" }
    Write-Output "Decoded $taskName"
}
