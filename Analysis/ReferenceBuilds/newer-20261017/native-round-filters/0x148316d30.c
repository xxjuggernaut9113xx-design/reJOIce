// Selected newer-build routine; caller-supplied label: TrackRecentObjective_URoundManager
// Address: 0x148316d30
// Static inferred pseudocode; external calls/types may be unresolved.


/* Selected newer-build routine; caller-supplied label: TrackRecentObjective_URoundManager */

void FUN_148316d30(longlong param_1,undefined1 param_2)

{
  ulonglong *puVar1;
  undefined1 *puVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  undefined8 unaff_retaddr;
  undefined1 auStackX_10 [8];
  
  puVar1 = (ulonglong *)(param_1 + 0x368);
  puVar2 = (undefined1 *)*puVar1;
  auStackX_10[0] = param_2;
  if (((puVar2 <= auStackX_10) && (auStackX_10 < puVar2 + *(int *)(param_1 + 0x374))) &&
     (cVar4 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                            auStackX_10,puVar2,(longlong)*(int *)(param_1 + 0x374),
                            (longlong)*(int *)(param_1 + 0x370),1), cVar4 != '\0')) {
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  iVar5 = *(int *)(param_1 + 0x370);
  *(uint *)(param_1 + 0x370) = iVar5 + 1U;
  if (*(uint *)(param_1 + 0x374) < iVar5 + 1U) {
    FUN_14830b750(puVar1,iVar5);
  }
  *(undefined1 *)((longlong)iVar5 + *puVar1) = auStackX_10[0];
  iVar5 = *(int *)(param_1 + 0x370);
  while (3 < iVar5) {
    iVar5 = *(int *)(param_1 + 0x370) + -1;
    if (iVar5 != 0) {
      func_0x00014ba120ea(*puVar1,*puVar1 + 1,(longlong)iVar5);
    }
    *(int *)(param_1 + 0x370) = *(int *)(param_1 + 0x370) + -1;
    FUN_14830bbc0(puVar1);
    iVar5 = *(int *)(param_1 + 0x370);
  }
  return;
}

