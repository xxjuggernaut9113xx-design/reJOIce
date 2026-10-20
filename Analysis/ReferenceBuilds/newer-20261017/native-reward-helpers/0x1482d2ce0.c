// Selected newer-build routine; caller-supplied label: RewardTypeAlreadySelected
// Address: 0x1482d2ce0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: RewardTypeAlreadySelected */

undefined1 FUN_1482d2ce0(undefined8 *param_1,char param_2)

{
  char *pcVar1;
  int iVar2;
  code *pcVar3;
  char cVar4;
  undefined1 uVar5;
  char *pcVar6;
  undefined1 auStackX_8 [8];
  
  param_1 = (undefined8 *)*param_1;
  pcVar6 = (char *)*param_1;
  iVar2 = *(int *)(param_1 + 1);
  pcVar1 = pcVar6 + (longlong)iVar2 * 8;
  while( true ) {
    if (*(int *)(param_1 + 1) != iVar2) {
      auStackX_8[0] = 0;
      cVar4 = FUN_14be5bf10(auStackX_8);
      if (cVar4 != '\0') {
        pcVar3 = (code *)swi(3);
        uVar5 = (*pcVar3)();
        return uVar5;
      }
    }
    if (pcVar6 == pcVar1) break;
    if (*pcVar6 == param_2) {
      return 1;
    }
    pcVar6 = pcVar6 + 8;
  }
  return 0;
}

