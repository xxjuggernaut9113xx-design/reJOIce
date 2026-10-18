// Newer reference PDB symbol: GetCurrentAudioTime_UMusicModeManager
// Address: 0x1482e9b40
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Matched newer-build PDB public symbol: GetCurrentAudioTime_UMusicModeManager */

double FUN_1482e9b40(longlong param_1)

{
  longlong alStackX_8 [4];
  
  if (*(char *)(param_1 + 0x568) != '\0') {
    if (*(char *)(param_1 + 0x569) != '\0') {
      return *(double *)(param_1 + 0x660);
    }
    if (*(char *)(param_1 + 0x648) != '\0') {
      QueryPerformanceCounter(alStackX_8);
      return ((((double)alStackX_8[0] * _DAT_14ed8b438 + _DAT_14bf2ec28) -
              *(double *)(param_1 + 0x638)) - *(double *)(param_1 + 0x668)) +
             *(double *)(param_1 + 0x678);
    }
    if (*(char *)(param_1 + 0x649) != '\0') {
      QueryPerformanceCounter(alStackX_8);
      return ((double)alStackX_8[0] * _DAT_14ed8b438 + _DAT_14bf2ec28) -
             *(double *)(param_1 + 0x640);
    }
  }
  return 0.0;
}

