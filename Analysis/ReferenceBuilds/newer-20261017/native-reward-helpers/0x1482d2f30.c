// Selected newer-build routine; caller-supplied label: AddCurrencyReward
// Address: 0x1482d2f30
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: AddCurrencyReward */

ulonglong FUN_1482d2f30(longlong *param_1,undefined1 param_2,int param_3)

{
  int iVar1;
  ulonglong *puVar2;
  undefined1 *puVar3;
  code *pcVar4;
  undefined8 uVar5;
  char cVar6;
  ulonglong uVar7;
  undefined8 unaff_retaddr;
  undefined1 uStack_18;
  undefined2 uStack_17;
  undefined1 uStack_15;
  int iStack_14;
  
  uVar7 = FUN_1482d2ce0(param_1[1]);
  if ((char)uVar7 != '\0') {
    return uVar7 & 0xffffffffffffff00;
  }
  uStack_17 = 0x1608;
  if (param_3 < 1) {
    param_3 = 1;
  }
  puVar2 = (ulonglong *)*param_1;
  puVar3 = (undefined1 *)*puVar2;
  uStack_18 = param_2;
  iStack_14 = param_3;
  if ((puVar3 <= &uStack_18) &&
     (&uStack_18 < puVar3 + (longlong)*(int *)((longlong)puVar2 + 0xc) * 8)) {
    cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                          &uStack_18,puVar3,(longlong)*(int *)((longlong)puVar2 + 0xc),
                          (longlong)(int)puVar2[1],8);
    if (cVar6 != '\0') {
      pcVar4 = (code *)swi(3);
      uVar7 = (*pcVar4)();
      return uVar7;
    }
  }
  iVar1 = (int)puVar2[1];
  *(uint *)(puVar2 + 1) = iVar1 + 1U;
  if (*(uint *)((longlong)puVar2 + 0xc) < iVar1 + 1U) {
    FUN_14830b210(puVar2,iVar1);
  }
  uVar5 = CONCAT44(iStack_14,CONCAT13(uStack_15,CONCAT21(uStack_17,uStack_18)));
  *(undefined8 *)(*puVar2 + (longlong)iVar1 * 8) = uVar5;
  return CONCAT71((int7)((ulonglong)uVar5 >> 8),1);
}

