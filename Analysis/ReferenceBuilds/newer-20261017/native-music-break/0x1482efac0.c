// Selected newer-build routine; caller-supplied label: GetEffectiveMaxBreakCharges_UMusicModeManager
// Address: 0x1482efac0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label:
   GetEffectiveMaxBreakCharges_UMusicModeManager */

ulonglong FUN_1482efac0(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  int iVar4;
  double dVar5;
  
  iVar4 = 5;
  if (*(int *)(param_1 + 0x46c) < 5) {
    iVar4 = *(int *)(param_1 + 0x46c);
  }
  iVar1 = 1;
  if (1 < iVar4) {
    iVar1 = iVar4;
  }
  dVar5 = (double)FUN_1482f8d50(param_1,1,iVar1);
  uVar2 = (longlong)ROUND(dVar5 * _DAT_14bf71e50 + _DAT_14bf2ec00) >> 1;
  uVar3 = uVar2 & 0xffffffff;
  if ((longlong)uVar2 < 1) {
    uVar3 = 1;
  }
  return uVar3;
}

