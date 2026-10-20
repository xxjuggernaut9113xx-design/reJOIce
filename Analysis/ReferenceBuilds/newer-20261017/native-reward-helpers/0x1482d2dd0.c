// Selected newer-build routine; caller-supplied label: SuccuModifierAlreadySelected
// Address: 0x1482d2dd0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: SuccuModifierAlreadySelected */

undefined1 FUN_1482d2dd0(longlong *param_1,char param_2)

{
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  char cVar4;
  undefined1 uVar5;
  longlong lVar6;
  undefined1 auStackX_10 [8];
  
  if (param_2 == '\x16') {
LAB_1482d2e27:
    uVar5 = 0;
  }
  else {
    param_1 = (longlong *)*param_1;
    lVar6 = *param_1;
    lVar3 = param_1[1];
    lVar1 = lVar6 + (longlong)(int)lVar3 * 8;
    while( true ) {
      if ((int)param_1[1] != (int)lVar3) {
        auStackX_10[0] = 0;
        cVar4 = FUN_14be5bf10(auStackX_10);
        if (cVar4 != '\0') {
          pcVar2 = (code *)swi(3);
          uVar5 = (*pcVar2)();
          return uVar5;
        }
      }
      if (lVar6 == lVar1) goto LAB_1482d2e27;
      if (*(char *)(lVar6 + 2) == param_2) break;
      lVar6 = lVar6 + 8;
    }
    uVar5 = 1;
  }
  return uVar5;
}

