// Selected newer-build routine; caller-supplied label: AddSuccuModifierReward
// Address: 0x1482d11b0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: AddSuccuModifierReward */

ulonglong FUN_1482d11b0(longlong *param_1,undefined8 *param_2)

{
  char *pcVar1;
  int iVar2;
  ulonglong *puVar3;
  undefined2 *puVar4;
  code *pcVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  ulonglong in_RAX;
  ulonglong uVar9;
  uint uVar10;
  longlong lVar11;
  char *pcVar12;
  undefined8 unaff_retaddr;
  undefined1 auStackX_10 [8];
  char acStack_48 [8];
  undefined2 uStack_40;
  char cStack_3e;
  undefined1 uStack_3d;
  undefined4 uStack_3c;
  char *pcStack_38;
  undefined8 uStack_30;
  
  if ((*(int *)(param_2 + 1) < 1) || (in_RAX = FUN_1482d2ce0(param_1[1],5), (char)in_RAX != '\0')) {
    uVar9 = in_RAX & 0xffffffffffffff00;
  }
  else {
    pcStack_38 = (char *)0x0;
    uStack_30 = 0;
    pcVar12 = (char *)*param_2;
    iVar2 = *(int *)(param_2 + 1);
    pcVar1 = pcVar12 + iVar2;
    while( true ) {
      if (*(int *)(param_2 + 1) != iVar2) {
        auStackX_10[0] = 0;
        cVar6 = FUN_14be5bb00(auStackX_10);
        if (cVar6 != '\0') {
          pcVar5 = (code *)swi(3);
          uVar9 = (*pcVar5)();
          return uVar9;
        }
      }
      if (pcVar12 == pcVar1) break;
      acStack_48[0] = *pcVar12;
      if ((acStack_48[0] != '\x16') && (cVar6 = FUN_1482d2dd0(param_1[2]), cVar6 == '\0')) {
        if (pcStack_38 <= acStack_48) {
          if (acStack_48 < pcStack_38 + (int)uStack_30._4_4_) {
            cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  acStack_48,pcStack_38,(longlong)(int)uStack_30._4_4_,
                                  (longlong)(int)uStack_30,1);
            if (cVar6 != '\0') {
              pcVar5 = (code *)swi(3);
              uVar9 = (*pcVar5)();
              return uVar9;
            }
          }
        }
        uVar9 = uStack_30;
        lVar11 = (longlong)(int)uStack_30;
        uVar7 = (int)uStack_30 + 1;
        uStack_30 = CONCAT44(uStack_30._4_4_,uVar7);
        if (uStack_30._4_4_ < uVar7) {
          FUN_14830b890(&pcStack_38,uVar9 & 0xffffffff);
        }
        pcStack_38[lVar11] = acStack_48[0];
      }
      pcVar12 = pcVar12 + 1;
    }
    iVar2 = (int)uStack_30;
    if ((int)uStack_30 < 1) {
      uVar9 = 0;
    }
    else {
      uStack_40 = 0x805;
      uVar10 = (int)uStack_30 - 1;
      uVar7 = 0;
      if (0 < (int)uStack_30) {
        uVar7 = rand();
        uVar8 = (uint)((float)(uVar7 & 0x7fff) * (float)iVar2 * _DAT_14bf3cd14);
        uVar7 = uVar10;
        if ((int)uVar8 < (int)uVar10) {
          uVar7 = uVar8;
        }
      }
      uVar10 = 0;
      if ((int)uVar7 < (int)uStack_30) {
        uVar10 = ~uVar7 >> 0x1f;
      }
      if ((uVar10 == 0) &&
         (cVar6 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                (longlong)(int)uVar7,(longlong)(int)uStack_30), cVar6 != '\0')) {
        pcVar5 = (code *)swi(3);
        uVar9 = (*pcVar5)();
        return uVar9;
      }
      cStack_3e = pcStack_38[(int)uVar7];
      uStack_3c = 1;
      puVar3 = (ulonglong *)*param_1;
      puVar4 = (undefined2 *)*puVar3;
      if (((puVar4 <= &uStack_40) &&
          (&uStack_40 < puVar4 + (longlong)*(int *)((longlong)puVar3 + 0xc) * 4)) &&
         (cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                &uStack_40,puVar4,(longlong)*(int *)((longlong)puVar3 + 0xc),
                                (longlong)(int)puVar3[1],8), cVar6 != '\0')) {
        pcVar5 = (code *)swi(3);
        uVar9 = (*pcVar5)();
        return uVar9;
      }
      iVar2 = (int)puVar3[1];
      *(uint *)(puVar3 + 1) = iVar2 + 1U;
      if (*(uint *)((longlong)puVar3 + 0xc) < iVar2 + 1U) {
        FUN_14830b210(puVar3,iVar2);
      }
      *(ulonglong *)(*puVar3 + (longlong)iVar2 * 8) =
           CONCAT44(uStack_3c,CONCAT13(uStack_3d,CONCAT12(cStack_3e,uStack_40)));
      uVar9 = 1;
    }
    if (pcStack_38 != (char *)0x0) {
      FUN_140e289f0();
    }
  }
  return uVar9;
}

