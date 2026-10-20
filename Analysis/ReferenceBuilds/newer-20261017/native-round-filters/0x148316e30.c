// Selected newer-build routine; caller-supplied label: TrackRecentPack_URoundManager
// Address: 0x148316e30
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: TrackRecentPack_URoundManager */

void FUN_148316e30(longlong param_1,undefined8 *param_2)

{
  ulonglong *puVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  undefined8 *puVar6;
  undefined8 unaff_retaddr;
  
  puVar1 = (ulonglong *)(param_1 + 0x358);
  puVar6 = (undefined8 *)*puVar1;
  if (((puVar6 <= param_2) && (param_2 < puVar6 + (longlong)*(int *)(param_1 + 0x364) * 2)) &&
     (cVar4 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,param_2
                            ,puVar6,(longlong)*(int *)(param_1 + 0x364),
                            (longlong)*(int *)(param_1 + 0x360),0x10), cVar4 != '\0')) {
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  iVar5 = *(int *)(param_1 + 0x360);
  *(uint *)(param_1 + 0x360) = iVar5 + 1U;
  if (*(uint *)(param_1 + 0x364) < iVar5 + 1U) {
    FUN_140ca5230(puVar1,iVar5);
  }
  puVar6 = (undefined8 *)((longlong)iVar5 * 0x10 + *puVar1);
  *puVar6 = 0;
  iVar5 = *(int *)(param_2 + 1);
  uVar2 = *param_2;
  *(int *)(puVar6 + 1) = iVar5;
  if (iVar5 == 0) {
    *(undefined4 *)((longlong)puVar6 + 0xc) = 0;
  }
  else {
    FUN_140ca40a0(puVar6,iVar5,0);
    func_0x00014ba120de(*puVar6,uVar2,(longlong)iVar5 * 2);
  }
  iVar5 = *(int *)(param_1 + 0x360);
  while (3 < iVar5) {
    if (*(longlong *)*puVar1 != 0) {
      FUN_140e289f0();
    }
    iVar5 = *(int *)(param_1 + 0x360) + -1;
    if (iVar5 != 0) {
      func_0x00014ba120ea(*puVar1,*puVar1 + 0x10,(longlong)iVar5 << 4);
    }
    *(int *)(param_1 + 0x360) = *(int *)(param_1 + 0x360) + -1;
    FUN_140d78a80(puVar1);
    iVar5 = *(int *)(param_1 + 0x360);
  }
  return;
}

