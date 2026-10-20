# Source loadout lifecycle

Recovered from the original newer UE5.3 IoStore UI assets, not inferred from item descriptions. `loadout-legacy/CockHero/Content/UI/LoadoutEquipScreen_Widget.uasset` and `WBP_LoadoutSlot.uasset` were extracted with retoc `to-legacy --filter Loadout --no-shaders --version UE5_3`, decoded with UAssetGUI FunctionOnly, and normalized by `Analysis/scripts/normalize_loadout_functions.py`. Retained normalized graphs are under `functions/LoadoutEquipScreen_Widget` and `functions/WBP_LoadoutSlot`.

## Fresh setup

`LoadoutEquipScreen_Widget.ExecuteUbergraph` offsets2725..2825 checks `IsFreshEquipStart`, resets the hotbar when fresh, then calls `PopulateEquipSlots` followed by `PopulateOwnedItems`. Fresh `PopulateOwnedItems` clears the owned map at5672. Classic branch calls `UnlockAllItems` at6572. Tower branch calls `Unlock Random Items` at5870 and clears `IsFreshEquipStart` at5906.

`BP_CHGameInstance.UnlockAllItems` unlocks each DT_ItemInformation row. The eleven row types in source order are1,3,4,5,6,7,9,11,12,13,10. Each new state is unlocked, level1, charges0. Old keys are not permanent profile unlocks.

`BP_CHGameInstance.Unlock Random Items` resets hotbar, clears the map, removes Resupply(type7) from the table row-name array, and shuffles that array once(offset623). It scans the same shuffled array first for Classification0(offset1069) then Classification1(offset1684), breaking after one match per scan. Defensive types are1,3,4,6,7,13,10; offensive types5,9,11,12. Resupply exclusion leaves exactly one of six defenses and one of four offenses. Both states start unlocked, level1, charges0. No slots are automatically filled.

The recovery chooser uses five existing source hotbar slots and exposes only unlocked pool items plus None(type8). Its combo controls replace unavailable source drag/drop assets; pool generation and state are source behavior.

## Classic selection persistence

`PopulateEquipSlots` Classic branch at140 calls `CLASSIC - Populate Saved Items` unconditionally. That function copies `CurrentSave.LastSavedHotBarItems` to `HotBarItems`. `BP_CHGameInstance.UpdateHotbarItem` writes the changed array back to that save field for Classic and calls `SaveAllData`. Recovery uses the same JSON key, bounds it to five slots, and replaces invalid/non-table enum values with None.

The NextButton wrapper jumps directly to graph offset2826. That handler switches on GameModeSelection and routes to Classic or Tower setup without a populated-slot count gate. Empty loadouts are allowed.

## Run resets and music

`ResetItemStates` resets existing map states to locked, level1, charges0 while preserving keys and hotbar. Its source manager currencies become0. This is distinct from the subsequent fresh chooser map-clear/population operation. Native StartRoundSession0x148314ce0 copies the caller map then marks every copied state unlocked and clamps level to at least1, preserving charges. Within-run progression is retained.

Music source `SetRhythmModeHotbar` clears existing slots then sets slot0 to Break(type4) with Array_Set size-to-fit=false. `PopulateOwnedItemsFromHotbar` calls pure UnlockItem, preserving existing-key no-op semantics. An absent Break therefore starts unlocked, level1, charges0. The GlobalManager GrantItem(4,1) at95345 is reached from event Type9 dispatch at95804..95844; it is not an initial charge grant. Music upgrade default maximum is1, with Bigger Pockets adding1 separately.

Regression coverage: `CockHero.Recovery.NewerInventory.FreshRunLifecycle` checks preserved reset keys/hotbar, copy-only Tower normalization, within-run state, Classic eleven-row replacement,64 seeded Tower class-diverse two-item pools, zero charges, five-slot saved Classic restoration, and music Break/cap composition.
