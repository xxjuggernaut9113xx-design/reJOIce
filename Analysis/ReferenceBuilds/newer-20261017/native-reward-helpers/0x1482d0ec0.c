// Selected newer-build routine; caller-supplied label: GrantUnlockOrUpgradeCategory
// Address: 0x1482d0ec0
// Static inferred pseudocode; external calls/types may be unresolved.


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* Selected newer-build routine; caller-supplied label: GrantUnlockOrUpgradeCategory */

ulonglong FUN_1482d0ec0(longlong *param_1,undefined1 param_2,undefined8 *param_3,int param_4)

{
  char *pcVar1;
  int iVar2;
  ulonglong *puVar3;
  undefined1 *puVar4;
  code *pcVar5;
  char cVar6;
  uint uVar7;
  uint uVar8;
  ulonglong in_RAX;
  ulonglong uVar9;
  longlong lVar10;
  char *pcVar11;
  undefined8 unaff_retaddr;
  undefined1 auStackX_18 [8];
  int iStackX_20;
  char acStack_58 [8];
  undefined1 uStack_50;
  char cStack_4f;
  undefined1 uStack_4e;
  undefined1 uStack_4d;
  int iStack_4c;
  char *pcStack_48;
  undefined8 uStack_40;
  
  if ((*(int *)(param_3 + 1) < 1) ||
     (iStackX_20 = param_4, in_RAX = FUN_1482d2ce0(param_1[1]), (char)in_RAX != '\0')) {
    uVar9 = in_RAX & 0xffffffffffffff00;
  }
  else {
    pcStack_48 = (char *)0x0;
    uStack_40 = 0;
    pcVar11 = (char *)*param_3;
    iVar2 = *(int *)(param_3 + 1);
    pcVar1 = pcVar11 + iVar2;
    while( true ) {
      if (*(int *)(param_3 + 1) != iVar2) {
        auStackX_18[0] = 0;
        cVar6 = FUN_14be5bab0(auStackX_18);
        if (cVar6 != '\0') {
          pcVar5 = (code *)swi(3);
          uVar9 = (*pcVar5)();
          return uVar9;
        }
      }
      if (pcVar11 == pcVar1) break;
      acStack_58[0] = *pcVar11;
      if ((acStack_58[0] != '\b') && (cVar6 = FUN_1482d2d50(param_1[2]), cVar6 == '\0')) {
        if (pcStack_48 <= acStack_58) {
          if (acStack_58 < pcStack_48 + (int)uStack_40._4_4_) {
            cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                  acStack_58,pcStack_48,(longlong)(int)uStack_40._4_4_,
                                  (longlong)(int)uStack_40,1);
            if (cVar6 != '\0') {
              pcVar5 = (code *)swi(3);
              uVar9 = (*pcVar5)();
              return uVar9;
            }
          }
        }
        uVar9 = uStack_40;
        lVar10 = (longlong)(int)uStack_40;
        uVar7 = (int)uStack_40 + 1;
        uStack_40 = CONCAT44(uStack_40._4_4_,uVar7);
        if (uStack_40._4_4_ < uVar7) {
          FUN_14830b7f0(&pcStack_48,uVar9 & 0xffffffff);
        }
        pcStack_48[lVar10] = acStack_58[0];
      }
      pcVar11 = pcVar11 + 1;
    }
    iVar2 = (int)uStack_40;
    if ((int)uStack_40 < 1) {
      uVar9 = 0;
    }
    else {
      uStack_4e = 0x16;
      uVar7 = (int)uStack_40 - 1;
      uStack_50 = param_2;
      if ((int)uStack_40 < 1) {
        uVar7 = 0;
      }
      else {
        uVar8 = rand();
        uVar8 = (uint)((float)(uVar8 & 0x7fff) * (float)iVar2 * _DAT_14bf3cd14);
        if ((int)uVar8 < (int)uVar7) {
          uVar7 = uVar8;
        }
      }
      uVar8 = 0;
      if ((int)uVar7 < (int)uStack_40) {
        uVar8 = ~uVar7 >> 0x1f;
      }
      if ((uVar8 == 0) &&
         (cVar6 = FUN_140f8e6d0(&UNK_14bf26168,&UNK_14d166cc0,0x303,unaff_retaddr,&UNK_14bf260f0,
                                (longlong)(int)uVar7,(longlong)(int)uStack_40), cVar6 != '\0')) {
        pcVar5 = (code *)swi(3);
        uVar9 = (*pcVar5)();
        return uVar9;
      }
      cStack_4f = pcStack_48[(int)uVar7];
      iStack_4c = iStackX_20;
      if (iStackX_20 < 1) {
        iStack_4c = 1;
      }
      puVar3 = (ulonglong *)*param_1;
      puVar4 = (undefined1 *)*puVar3;
      if (((puVar4 <= &uStack_50) &&
          (&uStack_50 < puVar4 + (longlong)*(int *)((longlong)puVar3 + 0xc) * 8)) &&
         (cVar6 = FUN_140f8e6d0(&UNK_14bf260b8,&UNK_14d166cc0,0x63e,unaff_retaddr,&UNK_14bf25f80,
                                &uStack_50,puVar4,(longlong)*(int *)((longlong)puVar3 + 0xc),
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
           CONCAT44(iStack_4c,CONCAT13(uStack_4d,CONCAT12(uStack_4e,CONCAT11(cStack_4f,uStack_50))))
      ;
      uVar9 = 1;
    }
    if (pcStack_48 != (char *)0x0) {
      FUN_140e289f0();
    }
  }
  return uVar9;
}

