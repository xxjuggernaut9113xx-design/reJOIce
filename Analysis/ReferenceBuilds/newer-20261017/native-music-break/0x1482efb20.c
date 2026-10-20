// Selected newer-build routine; caller-supplied label: GetEffectiveStrokesToGrantBreak_UMusicModeManager
// Address: 0x1482efb20
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label:
   GetEffectiveStrokesToGrantBreak_UMusicModeManager */

ulonglong FUN_1482efb20(longlong param_1)

{
  int iVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  int iVar4;
  double dVar5;
  
  iVar1 = 5;
  if (*(int *)(param_1 + 0x470) < 5) {
    iVar1 = *(int *)(param_1 + 0x470);
  }
  iVar4 = 1;
  if (1 < iVar1) {
    iVar4 = iVar1;
  }
  dVar5 = (double)FUN_1482f8d50(param_1,CONCAT71((uint7)(uint3)((uint)iVar1 >> 8),2),iVar4);
  uVar2 = (longlong)ROUND(dVar5 * _DAT_14bf71e50 + _DAT_14bf2ec00) >> 1;
  uVar3 = uVar2 & 0xffffffff;
  if ((longlong)uVar2 < 1) {
    uVar3 = 1;
  }
  return uVar3;
}

