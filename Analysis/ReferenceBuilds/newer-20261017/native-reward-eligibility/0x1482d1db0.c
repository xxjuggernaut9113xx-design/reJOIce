// Selected newer-build routine; caller-supplied label: AddEligibleWeightedRewardCategory
// Address: 0x1482d1db0
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: AddEligibleWeightedRewardCategory */

void FUN_1482d1db0(undefined8 *param_1,undefined1 param_2,float param_3)

{
  int iVar1;
  ulonglong *puVar2;
  undefined4 *puVar3;
  code *pcVar4;
  char cVar5;
  undefined8 unaff_retaddr;
  undefined4 uStack_28;
  float fStack_24;
  
  if (0.0 < param_3) {
    cVar5 = FUN_1482d1490(*param_1);
    if (cVar5 != '\0') {
      uStack_28 = CONCAT31(uStack_28._1_3_,param_2);
      puVar2 = (ulonglong *)param_1[1];
      puVar3 = (undefined4 *)*puVar2;
      fStack_24 = param_3;
      if ((puVar3 <= &uStack_28) &&
         (&uStack_28 < puVar3 + (longlong)*(int *)((longlong)puVar2 + 0xc) * 2)) {
        cVar5 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                              &uStack_28,puVar3,(longlong)*(int *)((longlong)puVar2 + 0xc),
                              (longlong)(int)puVar2[1],8);
        if (cVar5 != '\0') {
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
      }
      iVar1 = (int)puVar2[1];
      *(uint *)(puVar2 + 1) = iVar1 + 1U;
      if (*(uint *)((longlong)puVar2 + 0xc) < iVar1 + 1U) {
        FUN_14830b4b0(puVar2,iVar1);
      }
      *(ulonglong *)(*puVar2 + (longlong)iVar1 * 8) = CONCAT44(fStack_24,uStack_28);
    }
  }
  return;
}

