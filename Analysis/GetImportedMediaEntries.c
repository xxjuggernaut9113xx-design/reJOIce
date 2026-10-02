/* 14819b570 ?GetImportedMediaEntries@UFileImportManager@@QEBA?AV?$TArray@UFCHPackMediaEntry@@V?$TSizedDefaultAllocator@$0CA@@@@@XZ */

ulonglong *
_GetImportedMediaEntries_UFileImportManager__QEBA_AV__TArray_UFCHPackMediaEntry__V__TSizedDefaultAllocator__0CA_____XZ
          (longlong param_1,ulonglong *param_2)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  ulonglong *puVar4;
  longlong *plVar5;
  longlong **pplVar6;
  ulonglong uVar7;
  undefined8 *puVar8;
  undefined8 *puVar9;
  int iVar10;
  longlong lVar11;
  longlong *plVar12;
  undefined8 unaff_retaddr;
  undefined1 auStackX_8 [8];
  ulonglong *puStackX_10;
  uint uStackX_18;
  longlong *plStackX_20;
  longlong lStack_c8;
  ulonglong uStack_c0;
  longlong lStack_b8;
  ulonglong uStack_b0;
  longlong *plStack_a8;
  longlong *plStack_a0;
  longlong lStack_98;
  undefined8 uStack_90;
  undefined4 uStack_88;
  undefined8 *puStack_80;
  longlong *plStack_78;
  int iStack_70;
  undefined8 *puStack_68;
  longlong alStack_60 [4];
  
  *param_2 = 0;
  param_2[1] = 0;
  uStack_88 = 1;
  plVar12 = *(longlong **)(param_1 + 0x28);
  uStackX_18 = *(uint *)(param_1 + 0x30);
  uVar7 = (ulonglong)(int)uStackX_18;
  plVar5 = plVar12 + uVar7 * 3;
  puStackX_10 = param_2;
  plStackX_20 = plVar5;
  while( true ) {
    if (*(int *)(param_1 + 0x30) != (int)uVar7) {
      auStackX_8[0] = 0;
      cVar3 = func_0x00014bc1cef0(auStackX_8);
      if (cVar3 != '\0') {
        pcVar2 = (code *)swi(3);
        puVar4 = (ulonglong *)(*pcVar2)();
        return puVar4;
      }
    }
    if (plVar12 == plVar5) break;
    if ((char)plVar12[2] != '\0') {
      lStack_c8 = 0;
      uStack_c0 = 0;
      lStack_b8 = 0;
      uStack_b0 = 0;
      plStack_a8 = (longlong *)0x0;
      plStack_a0 = (longlong *)0x0;
      lStack_98 = 0;
      uStack_90 = 0;
      plVar5 = (longlong *)func_0x00014106f2a0(alStack_60,plVar12);
      if (&lStack_c8 != plVar5) {
        if (lStack_c8 != 0) {
          func_0x000140e282f0();
        }
        lStack_c8 = *plVar5;
        *plVar5 = 0;
        uStack_c0 = plVar5[1];
        plVar5[1] = 0;
      }
      if (alStack_60[0] != 0) {
        func_0x000140e282f0();
      }
      if (&lStack_98 != plVar12) {
        iVar10 = (int)plVar12[1];
        lVar1 = *plVar12;
        uStack_90 = CONCAT44(uStack_90._4_4_,iVar10);
        if ((iVar10 == 0) && (uStack_90._4_4_ == 0)) {
          uStack_90 = 0;
        }
        else {
          func_0x000140ca39a0(&lStack_98,iVar10);
          if (iVar10 != 0) {
            func_0x00014b89502e(lStack_98,lVar1,(longlong)iVar10 * 2);
          }
        }
      }
      pplVar6 = (longlong **)func_0x0001481982d0(&plStack_78,plVar12);
      plVar5 = plStack_78;
      iVar10 = iStack_70;
      if (&plStack_a8 != pplVar6) {
        plVar5 = plStack_a8;
        for (iVar10 = (int)plStack_a0; iVar10 != 0; iVar10 = iVar10 + -1) {
          if (*plVar5 != 0) {
            func_0x000140e282f0();
          }
          plVar5 = plVar5 + 2;
        }
        if (plStack_a8 != (longlong *)0x0) {
          func_0x000140e282f0(plStack_a8);
        }
        plStack_a8 = *pplVar6;
        *pplVar6 = (longlong *)0x0;
        plStack_a0 = pplVar6[1];
        pplVar6[1] = (longlong *)0x0;
        plVar5 = plStack_78;
        iVar10 = iStack_70;
      }
      for (; iVar10 != 0; iVar10 = iVar10 + -1) {
        if (*plVar5 != 0) {
          func_0x000140e282f0();
        }
        plVar5 = plVar5 + 2;
      }
      if (plStack_78 != (longlong *)0x0) {
        func_0x000140e282f0(plStack_78);
      }
      plVar5 = (longlong *)*param_2;
      if (((plVar5 <= &lStack_c8) &&
          (&lStack_c8 < plVar5 + (longlong)*(int *)((longlong)param_2 + 0xc) * 8)) &&
         (cVar3 = func_0x000140f8dfd0(&UNK_14bce6eb8,&UNK_14cf27ac0,0x63e,unaff_retaddr,
                                      &UNK_14bce6d80,&lStack_c8,plVar5,
                                      (longlong)*(int *)((longlong)param_2 + 0xc),
                                      (longlong)(int)param_2[1],0x40), cVar3 != '\0')) {
        pcVar2 = (code *)swi(3);
        puVar4 = (ulonglong *)(*pcVar2)();
        return puVar4;
      }
      iVar10 = (int)param_2[1];
      *(uint *)(param_2 + 1) = iVar10 + 1U;
      if (*(uint *)((longlong)param_2 + 0xc) < iVar10 + 1U) {
        func_0x0001481939b0(param_2,iVar10);
      }
      lVar1 = lStack_c8;
      puVar8 = (undefined8 *)((longlong)iVar10 * 0x40 + *param_2);
      *puVar8 = 0;
      lVar11 = (longlong)(int)uStack_c0;
      *(int *)(puVar8 + 1) = (int)uStack_c0;
      puStack_68 = puVar8;
      if ((int)uStack_c0 == 0) {
        *(undefined4 *)((longlong)puVar8 + 0xc) = 0;
      }
      else {
        puStack_80 = puVar8;
        func_0x000140ca39a0(puVar8,uStack_c0 & 0xffffffff,0);
        func_0x00014b89502e(*puVar8,lVar1,lVar11 * 2);
      }
      lVar1 = lStack_b8;
      puVar9 = puVar8 + 2;
      *puVar9 = 0;
      lVar11 = (longlong)(int)uStack_b0;
      *(int *)(puVar8 + 3) = (int)uStack_b0;
      if ((int)uStack_b0 == 0) {
        *(undefined4 *)((longlong)puVar8 + 0x1c) = 0;
      }
      else {
        puStack_80 = puVar9;
        func_0x000140ca39a0(puVar9,uStack_b0 & 0xffffffff,0);
        func_0x00014b89502e(*puVar9,lVar1,lVar11 * 2);
      }
      puStack_80 = puVar8 + 4;
      *puStack_80 = 0;
      func_0x000140c64610(puStack_80,plStack_a8,(ulonglong)plStack_a0 & 0xffffffff,0);
      lVar1 = lStack_98;
      puVar9 = puVar8 + 6;
      *puVar9 = 0;
      *(int *)(puVar8 + 7) = (int)uStack_90;
      puStack_80 = puVar9;
      if ((int)uStack_90 == 0) {
        *(undefined4 *)((longlong)puVar8 + 0x3c) = 0;
      }
      else {
        func_0x000140ca39a0(puVar9,uStack_90 & 0xffffffff,0);
        func_0x00014b89502e(*puVar9,lVar1);
      }
      if (lStack_98 != 0) {
        func_0x000140e282f0();
      }
      plVar5 = plStack_a8;
      for (iVar10 = (int)plStack_a0; iVar10 != 0; iVar10 = iVar10 + -1) {
        if (*plVar5 != 0) {
          func_0x000140e282f0();
        }
        plVar5 = plVar5 + 2;
      }
      if (plStack_a8 != (longlong *)0x0) {
        func_0x000140e282f0(plStack_a8);
      }
      if (lStack_b8 != 0) {
        func_0x000140e282f0();
      }
      plVar5 = plStackX_20;
      if (lStack_c8 != 0) {
        func_0x000140e282f0();
        plVar5 = plStackX_20;
      }
    }
    plVar12 = plVar12 + 3;
    uVar7 = (ulonglong)uStackX_18;
  }
  return param_2;
}




/* Resolved referenced strings:
{
  "14bce6d80": "Attempting to use a container element (%p) which already comes from the container being modified (%p, ArrayMax: %lld, ArrayNum: %lld, SizeofElement: %d)!",
  "14bce6eb8": "Addr < GetData() || Addr >= (GetData() + ArrayMax)",
  "14cf27ac0": "C:\\Program Files\\Epic Games\\UE_5.3\\Engine\\Source\\Runtime\\Core\\Public\\Containers\\Array.h"
}
*/
