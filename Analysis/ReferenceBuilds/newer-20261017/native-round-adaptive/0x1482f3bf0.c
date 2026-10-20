// Selected newer-build routine; caller-supplied label: GetOpeningCalibrationTier_URoundManager
// Address: 0x1482f3bf0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: GetOpeningCalibrationTier_URoundManager */

ulonglong FUN_1482f3bf0(longlong param_1,uint param_2)

{
  code *pcVar1;
  char cVar2;
  uint uVar3;
  ulonglong uVar4;
  uint uVar5;
  undefined8 unaff_retaddr;
  
  if (*(int *)(param_1 + 0x230) == 0) {
    return 1;
  }
  uVar3 = *(int *)(param_1 + 0x230) - 1;
  if ((int)param_2 < (int)uVar3) {
    uVar3 = param_2;
  }
  uVar5 = 0;
  if (0 < (int)uVar3) {
    uVar5 = uVar3;
  }
  uVar3 = 0;
  if ((int)uVar5 < *(int *)(param_1 + 0x230)) {
    uVar3 = ~uVar5 >> 0x1f;
  }
  if (uVar3 == 0) {
    cVar2 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                          (longlong)(int)uVar5,(longlong)*(int *)(param_1 + 0x230));
    if (cVar2 != '\0') {
      pcVar1 = (code *)swi(3);
      uVar4 = (*pcVar1)();
      return uVar4;
    }
  }
  uVar3 = *(uint *)(*(longlong *)(param_1 + 0x228) + (longlong)(int)uVar5 * 4);
  uVar5 = 5;
  if ((int)uVar3 < 5) {
    uVar5 = uVar3;
  }
  uVar3 = 1;
  if (1 < (int)uVar5) {
    uVar3 = uVar5;
  }
  return (ulonglong)uVar3;
}

