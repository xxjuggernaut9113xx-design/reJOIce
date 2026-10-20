// Selected newer-build routine; caller-supplied label: UpgradeQuantityForTier
// Address: 0x1482d1a40
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: UpgradeQuantityForTier */

int FUN_1482d1a40(undefined8 *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)*param_1;
  if (5 < iVar1) {
    iVar1 = 1;
    if (1 < *(int *)(param_1[1] + 0x268)) {
      iVar1 = *(int *)(param_1[1] + 0x268);
    }
    return iVar1;
  }
  if (*(char *)param_1[2] == '\x02') {
    if (*(int *)(param_1[1] + 0x25c) <= iVar1) {
      iVar1 = *(int *)(param_1[1] + 600);
      iVar2 = 1;
      if (1 < iVar1) {
        iVar2 = iVar1;
      }
      return iVar2;
    }
  }
  else if ((*(char *)param_1[2] == '\x01') && (*(int *)(param_1[1] + 0x264) <= iVar1)) {
    iVar1 = *(int *)(param_1[1] + 0x260);
    iVar2 = 1;
    if (1 < iVar1) {
      iVar2 = iVar1;
    }
    return iVar2;
  }
  return 1;
}

